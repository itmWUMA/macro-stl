#define _CRT_SECURE_NO_WARNINGS
#define QUEUE

#ifndef DEQUE
#include "deque.hpp"
#endif // !DEQUE


namespace mstl_itm
{
	template <class _ValueT>
	class Queue
	{
	public:
		using ValueType = _ValueT;		// ����Ԫ��ֵ
		using Reference = _ValueT&;	// ����Ԫ������

	private:
		Deque<ValueType> base;	// �ײ�����

	public:
		// �����Ƿ�Ϊ��
		bool IsEmpty() { return base.IsEmpty(); }

		// ���д�С
		size_t Size() { return base.Size(); }

		// ����Ԫ��
		Reference Top() { return base.Front(); }

		// ��βԪ��
		Reference Back() { return base.Back(); }

		// ���
		void Enqueue(const ValueType& val) { base.PushBack(val); }

		// ����
		ValueType Dequeue() { return base.PopFront(); }
	};
}