#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define DEQUE

#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR
#ifndef ALLOCATOR
#include "allocator.hpp"
#endif // !ALLOCATOR
#ifndef ALGORITHM
#include "algorithm.hpp"
#endif // !ALGORITHM


namespace mstl_itm
{
	template <class _ValueT, size_t _BufSize = 0>
	class Deque
	{
	public:
		using ValueType = _ValueT;		// Ԫ������
		using Pointer = _ValueT*;	// Ԫ������ָ��
		using Reference = _ValueT&;	// Ԫ����������

	private:
		using MapPointer = Pointer*;	// �п���ָ��

	private:
		MapPointer map;	// �п���
		size_t mapSize;	// �п��������ָ��ĸ���

	private:
		// ���㻺����Ԫ�ظ���
		static size_t GetBufferSize()
		{
			return _BufSize != 0 ? _BufSize :
				(sizeof(ValueType) < 512 ? (512 / sizeof(ValueType)) : 1);
		}

	private:
		// Deque������
		struct DequeIterator : public RandomAcessIterator<ValueType>
		{
			typedef DequeIterator Iterator;
			typedef ValueType ValueType;

			Pointer m_cur;		// ��������ǰָ��Ԫ��
			Pointer m_first;	// ��ǰ��������ͷ
			Pointer m_last;	// ��ǰ��������β
			MapPointer m_node;	// ָ���п������

			// �ɵ�ǰ������ָ����һ������ JUMP
			void operator>>(MapPointer newNode)
			{
				this->m_node = newNode;
				this->m_first = *newNode;
				this->m_last = this->m_first + GetBufferSize();
			}

			Reference operator*() const { return *m_cur; }
			Pointer operator->() const { return &(operator*()); }

			size_t operator-(const Iterator& iter) const
			{
				return GetBufferSize() * (this->m_node - iter.m_node - 1) +
					(this->m_cur - this->m_first) + (iter.m_last - iter.m_cur);
			}

			Iterator& operator++()
			{
				++m_cur;
				// ��������������������һ������
				if (m_cur == m_last)
				{
					operator>>(m_node + 1);
					m_cur = m_first;
				}
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator temp = *this;
				++(*this);
				return temp;
			}

			Iterator& operator--()
			{
				// ��������������������һ������
				if (m_cur == m_first)
				{
					operator>>(m_node - 1);
					m_cur = m_last;
				}
				--m_cur;
				return *this;
			}

			Iterator operator--(int)
			{
				Iterator temp = *this;
				--(*this);
				return temp;
			}

			Iterator& operator+=(int n)
			{
				int offset = n + (m_cur - m_first);
				// Ŀ����ͬһ������
				if (offset >= 0 && offset < (int)GetBufferSize())
					m_cur += n;
				// Ŀ�겻��ͬһ������
				else
				{
					size_t nodeOffset = offset > 0 ? offset / GetBufferSize() :
						-((-offset - 1) / (int)GetBufferSize()) - 1;
					// ������ȷ�Ļ�����
					operator>>(m_node + nodeOffset);
					// �л�����ȷ��Ԫ��
					m_cur = m_first + (offset - nodeOffset * GetBufferSize());
				}

				return *this;
			}

			Iterator operator+(int n) const
			{
				Iterator temp = *this;
				return temp += n;
			}

			Iterator& operator-=(int n)
			{
				return *this += -n;
			}

			Iterator operator-(int n) const
			{
				Iterator temp = *this;
				return temp -= n;
			}

			Reference operator[](size_t i) const { return *(*this + i); }
			bool operator==(const Iterator& iter) const { return m_cur == iter.m_cur; }
			bool operator!=(const Iterator& iter) const { return !(*this == iter); }
			bool operator<(const Iterator& iter) const
			{
				return m_node == iter.m_node ? m_cur < iter.m_cur : m_node < iter.m_node;
			}
		};

	public:
		using Iterator = DequeIterator;

	private:
		Iterator start;	// ָ���һ����������ͷ���
		Iterator finish;	// ָ�����һ����������β���

	public:
		// ��ʼ������
		Iterator Begin() { return start; }

		// ��ֹ������
		Iterator End() { return finish; }

		// ������
		Reference operator[](size_t i) { return start[i]; }

		// ��Ԫ��
		Reference Front() { return *start; }

		// βԪ��
		Reference Back() { return *(finish - 1); }

		// Ԫ�ظ���
		size_t Size() { return finish - start; }

		// �ж��Ƿ�Ϊ��
		bool IsEmpty() { return start == finish; }

	private:
		// ���������п���
		void CreateMapAndNodes(size_t elemCount)
		{
			// ���軺��������
			size_t nodeCount = elemCount / GetBufferSize() + 1;
			// �п�����С
			mapSize = nodeCount > 8 ? nodeCount + 2 : 8;	// �п�����СҪ���8��������
			// �����п����Ŀռ�
			map = Allocator<Pointer>::AllocateRange(mapSize);

			// ���п�����������map���м�
			MapPointer nstart = map + ((mapSize - nodeCount) >> 1);
			MapPointer nfinish = nstart + nodeCount - 1;
			MapPointer cur;
			// ���뻺�����Ŀռ�
			for (cur = nstart; cur <= nfinish; cur++)
				*cur = Allocator<ValueType>::AllocateRange(GetBufferSize());

			// ���µ�ǰ��Ա
			start >> nstart;
			finish >> nfinish;
			start.m_cur = start.m_first;
			finish.m_cur = finish.m_first + elemCount % GetBufferSize();
		}

		// β�������п���
		void AppendMap(size_t addNodeCount = 1, bool isAddFront = true)
		{
			// ���п�����С����
			size_t newMapSize = mapSize + Algorithm::Max(mapSize, addNodeCount) + 2;
			size_t oldNumNodes = finish.m_node - start.m_node + 1;
			size_t newNumNodes = oldNumNodes + addNodeCount;

			// �������п����Ŀռ�
			MapPointer newMap = Allocator<Pointer>::AllocateRange(newMapSize);
			MapPointer newNstrart = newMap + ((newMapSize - newNumNodes) >> 1) +
				(isAddFront ? addNodeCount : 0);
			
			// ����ԭmap����
			for (MapPointer i = start.m_node, j = finish.m_node, k = newNstrart;
				i < j + 1; i++, k++) 
			{
				*k = *i;
			}

			// �ͷ�ԭmap
			Allocator<Pointer>::DeallocateRange(map);

			// ���³�Ա����
			map = newMap;
			mapSize = newMapSize;
			start >> newNstrart;
			finish >> (newNstrart + oldNumNodes - 1);
		}

	public:
		// Ĭ�Ϲ���
		Deque() { CreateMapAndNodes(0); }

		// ��乹��
		Deque(int elemCount, const ValueType& val) 
		{ 
			// ���ɽṹ
			CreateMapAndNodes(elemCount); 
			
			// ���
			for (Iterator iter = start; iter != finish; iter++)
				*(iter.m_cur) = val;
		}

		// TODO: ��������

		// TODO: ��ֵ����

		// ����
		~Deque()
		{
			// �ͷŻ�����
			for (MapPointer p = start.m_node; p < finish.m_node + 1; p++)
				Allocator<ValueType>::DeallocateRange(*p);

			// �ͷ��п���
			Allocator<Pointer>::DeallocateRange(map);
			map = nullptr;
		}

		// β��
		void PushBack(const ValueType& val)
		{
			// ��󻺳��������������ϵı��û������ռ�
			if (finish.m_cur != finish.m_last - 1)
			{
				*(finish.m_cur) = val;
				++(finish.m_cur);
			}
			// ��ʣ��һ�����û������ռ�
			else
			{
				// �п����ռ䲻��
				if (finish.m_node - map == mapSize - 1)
				{
					// ����map
					AppendMap(1, false);
				}

				// �����µĻ�����
				*(finish.m_node + 1) = Allocator<ValueType>::AllocateRange(GetBufferSize());
				*(finish.m_cur) = val;
				// ���µ�����
				finish >> (finish.m_node + 1);
				finish.m_cur = finish.m_first;
			}
		}

		// ͷ��
		void PushFront(const ValueType& val)
		{
			// ��һ�������б��û������ռ�
			if (start.m_cur != start.m_first)
			{
				*(start.m_cur - 1) = val;
				start.m_cur--;
			}
			// ��һ�������ޱ��û������ռ�
			else
			{
				// �п����ռ䲻��
				if (start.m_node == map)
				{
					// ����map
					AppendMap();
				}

				*(start.m_node - 1) = Allocator<ValueType>::AllocateRange(GetBufferSize());
				start >> (start.m_node - 1);
				start.m_cur = start.m_last - 1;
				*(start.m_cur) = val;
			}
		}

		// βɾԪ��
		ValueType PopBack()
		{
			// ��������1�����ϵ�Ԫ��
			if (finish.m_cur != finish.m_first)
			{
				--finish.m_cur;
				ValueType res = *finish;
				return res;
			}
			// ��󻺳������κ�Ԫ��
			else
			{
				// �ͷŻ�����
				Allocator<ValueType>::DeallocateRange(finish.m_cur);
				finish >> (finish.m_node - 1);
				finish.m_cur = finish.m_last - 1;
				ValueType res = *finish;
				return res;
			}
		}

		// ͷɾԪ��
		ValueType PopFront()
		{
			// ��һ����������������Ԫ��
			if (start.m_cur != start.m_last - 1)
			{
				ValueType res = *start;
				++start.m_cur;
				return res;
			}
			// ��һ����������һ��Ԫ��
			else
			{
				ValueType res = *start;
				Allocator<ValueType>::DeallocateRange(start.m_first);
				start >> (start.m_node + 1);
				start.m_cur = start.m_first;
				return res;
			}
		}

		// TODO: Insert | Erase
	};
}