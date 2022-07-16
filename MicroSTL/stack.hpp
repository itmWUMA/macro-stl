#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define STACK

#ifndef DEQUE
#include "deque.hpp"
#endif // !DEQUE


namespace mstl_itm
{
	template <class _ValueT>
	class Stack
	{
	public:
		using ValueType = _ValueT;		// ����Ԫ��ֵ
		using Reference = _ValueT&;	// ����Ԫ������

	private:
		Deque<ValueType> base;	// �ײ�����

	public:
		// ջ�Ƿ�Ϊ��
		bool IsEmpty() { return base.IsEmpty(); }
		
		// ջ��С
		size_t Size() { return base.Size(); }

		// ջ��Ԫ��
		Reference Top() { return base.Back(); }

		// ѹջ
		void Push(const ValueType& val) { base.PushBack(val); }

		// ��ջ
		ValueType Pop() { return base.PopBack(); }
	};
}