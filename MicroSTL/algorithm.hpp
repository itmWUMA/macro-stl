// �㷨: ����ʵ�ֶ����������ĸ����㷨
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ALGORITHM

#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR

namespace mstl_itm
{
	class Algorithm
	{
	public:
		// ��ȡ�����������
		template <typename _InputIter>
		static typename IteratorTraits<_InputIter>::DifferenceType
			Distance(_InputIter first, _InputIter last)
		{
			typename IteratorTraits<_InputIter>::DifferenceType count = 0;
			// ��һ�ۼƾ���
			while (first != last)
			{
				first++;
				count++;
			}
			return count;
		}
	};
}