// �ڲ�ʵ�֣��ѽṹ
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HEAP

#ifndef VECTOR
#include "vector.hpp"
#endif // !VECTOR
#ifndef FUNCTOR
#include "functor.hpp"
#endif // !FUNCTOR
#ifndef ALGORITHM
#include "algorithm.hpp"
#endif // !ALGORITHM

#include <stdexcept>

namespace mstl_itm
{
	template <class _ValueT, class _Cmp = Less<_ValueT>>
	class Heap
	{
	public:
		using ValueType = _ValueT;		// Ԫ��ֵ
		using Reference = _ValueT&;	// Ԫ������
		using Comparator = _Cmp;		// �Ƚ���

	private:
		Vector<ValueType> base;		// �ײ�ṹ��vector֧��

	public:
		// �Ѵ�С
		size_t Size() { return base.Size(); }

		// �Ƿ�Ϊ��
		bool IsEmpty() { return base.IsEmpty(); }

		// �õ��Ѷ�Ԫ��
		Reference Top() { return base[0]; }

	private:
		// �ѻ�
		void Heapify(size_t pos)
		{
			size_t left = 2 * pos + 1, right = left + 1;
			size_t heapSize = Size();

			while (left < heapSize)
			{
				// ��������PK
				size_t winIndex = (right < heapSize && (Comparator()(base[left], base[right]))) ?
					right : left;
				// ʤ���뵱ǰ����PK
				winIndex = (Comparator()(base[pos], base[winIndex])) ? winIndex : pos;
				if (winIndex == pos)
					return;
				// ��ǰԪ����Ǳ
				Algorithm::Swap(base[pos], base[winIndex]);
				pos = winIndex;
				left = pos * 2 + 1;
				right = left + 1;
			}
		}

		// �����
		void InsertHeap(const ValueType& val)
		{
			base.PushBack(val);
			size_t heapSize = Size();
			int cur = heapSize - 1,
				parent = (cur - 1) / 2;
			while (parent != cur)
			{
				if (Comparator()(base[cur], base[parent]))
					return;
				Algorithm::Swap(base[parent], base[cur]);
				cur = parent;
				parent = (cur - 1) / 2;
			}
		}

	public:
		// ���
		void Push(const ValueType& val) { InsertHeap(val); }

		// ����
		ValueType Pop()
		{
			if (IsEmpty())
				throw runtime_error("Heap is empty!");

			ValueType res = Top();
			Algorithm::Swap(base[0], base[Size() - 1]);
			base.PopBack();
			// ���¶ѻ�
			Heapify(0);

			return res;
		}
	};
}
