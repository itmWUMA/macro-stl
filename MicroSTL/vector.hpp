#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define VECTOER

#include "allocator.hpp"
#include "iterator.hpp"

namespace mstl_itm
{
	template <class _ValueT>
	class Vector
	{
	public:
		using ValueType = _ValueT;		// Ԫ������
		using Pointer = _ValueT*;		// Ԫ������ָ��
		using Reference = _ValueT&;
		using DifferenceType = size_t;		// ָ���������
		using Iterator = Pointer;		// Vector������

	private:
		Iterator m_start;				// Ŀǰʹ�ÿռ��ͷ��
		Iterator m_finish;			// Ŀǰʹ�ÿռ��β��
		Iterator m_endOfStorage;	// Ŀǰ���ÿռ��β��

	public:
		// Ĭ�Ϲ���
		Vector()
		{
			Pointer p = Allocator<ValueType>::AllocateRange(1);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + 1;
		}

		// ָ����������
		Vector(int capcity)
		{
			Pointer p = Allocator<ValueType>::AllocateRange(capcity);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + capcity;
		}

		// ���乹��
		Vector(InputIterator<ValueType> first, InputIterator<ValueType> last)
		{
			DifferenceType cap = last - first;
			Pointer p = Allocator<ValueType>::AllocateRange(cap);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + cap;

			for (auto iter = first; iter != last; iter++, m_finish++)
				*m_finish = *iter;
		}

		// ��������
		Vector(const Vector& v)
		{
			DifferenceType cap = v.m_endOfStorage - v.m_start;
			Pointer p = Allocator<ValueType>::AllocateRange(cap);
			m_start = p;
			m_finish = p;
			m_endOfStorage = p + cap;

			for (auto iter = v.m_start; iter != v.m_finish; iter++, m_finish++)
				*m_finish = *iter;
		}

		// ����
		~Vector()
		{
			Allocator<ValueType>::DeallocateRange(m_start);
			m_start = nullptr;
			m_endOfStorage = nullptr;
			m_finish = nullptr;
		}

		// ��ȡ��ʼ������
		Iterator Begin() { return m_start; }

		// ��ȡ����������
		Iterator End() { return m_finish; }

		// ��ȡ�����С
		size_t Size() { return m_finish - m_start; }

		// ��ȡ��������
		size_t Capcity() { return m_endOfStorage - m_start; }

		// �ж������Ƿ�Ϊ��
		bool IsEmpty() { return (m_start == m_finish); }

		// ��ȡ��Ԫ��
		ValueType Front() { return *m_start; }

		// ��ȡĩԪ��
		ValueType Back() { return *(m_finish - 1); }

		// ������
		Reference operator[](size_t index) { return *(m_start + index); }

	private:
		// vector���ݻ���
		void _Append()
		{
			size_t cap = Capcity();
			Allocator<ValueType>::Append(m_start, cap, 2 * cap);
			// ����3��ָ��
			m_finish = m_start + cap;
			m_endOfStorage = m_start + 2 * cap;
		}

	public:
		// ���Ԫ��
		void PushBack(const ValueType& elem)
		{
			// ������Ա
			if (Size() == Capcity())
			{
				// ����
				_Append();
			}
			*m_finish = elem;
			m_finish++;
		}

		// ����Ԫ��
		void Insert(int pos, const ValueType& elem)
		{
			if (pos < 0 || pos > (int)this->Size()) throw;
			// ������Ա
			if (Size() == Capcity())
			{
				// ����
				_Append();
			}

			// ������
			Iterator iter = m_finish;
			for (int i = this->Size(); i > pos; i--, iter--)
				*iter = *(iter - 1);
			// ����Ԫ��
			*(m_start + pos) = elem;
			// ����ָ��
			m_finish++;
		}

		// ɾ��β��Ԫ��
		ValueType PopBack()
		{
			if (IsEmpty())	throw;
			return *--m_finish;
		}

		// ɾ��Ԫ��
		ValueType Erase(int pos)
		{
			if (pos < 0 || pos > (int)this->Size() || IsEmpty()) throw;
			ValueType res = *(m_start + pos);
			// ��ǰ����
			for (auto iter = m_start + pos; iter != m_finish - 1; iter++)
				*iter = *(iter + 1);
			// ����ָ��
			m_finish--;
			
			return res;
		}
	};
}