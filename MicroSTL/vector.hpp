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
		using ValueType		= _ValueT;		// Ԫ������
		using Pointer			= _ValueT*;		// Ԫ������ָ��
		using DifferenceType = size_t;		// ָ���������
		using Iterator			= Pointer;		// Vector������

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
	};
}