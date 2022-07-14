#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define DEQUE

#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR


namespace mstl_itm
{
	template <class _ValueT, size_t _BufSize = 0>
	class Deque
	{
	public:
		using ValueType = _ValueT;		// Ԫ������
		using Pointer	 = _ValueT*;	// Ԫ������ָ��
		using Reference = _ValueT&;	// Ԫ����������

	private:
		using MapPointer = Pointer*;	// �п���ָ��

	private:
		MapPointer map;	// �п���
		size_t mapSize;	// �п��������ָ��ĸ���

	private:
		// ���㻺����Ԫ�ظ���
		size_t GetBufferSize()
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

			Iterator& operator+=(size_t n)
			{
				size_t offset = n + (m_cur - m_first);
				// Ŀ����ͬһ������
				if (offset >= 0 && offset < GetBufferSize())
					m_cur += n;
				// Ŀ�겻��ͬһ������
				else
				{
					size_t nodeOffset = offset > 0 ? offset / GetBufferSize() :
						-((-offset - 1) / GetBufferSize()) - 1;
					// ������ȷ�Ļ�����
					operator>>(m_node + nodeOffset);
					// �л�����ȷ��Ԫ��
					m_cur = m_first + (offset - nodeOffset * GetBufferSize());
				}

				return *this;
			}

			Iterator operator+(size_t n) const
			{
				Iterator temp = *this;
				return temp += n;
			}

			Iterator& operator-=(size_t n)
			{
				return *this += -n;
			}

			Iterator operator-(size_t n) const
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
	};
}