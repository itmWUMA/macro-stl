#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define LIST

#include "allocator.hpp"
#include "iterator.hpp"

namespace mstl_itm
{
	template <class _ValueT>
	class List
	{
	public:
		using ValueType = _ValueT;		// Ԫ������
		using Reference = _ValueT&;	// Ԫ����������
		using Pointer	 = _ValueT*;	// Ԫ��ָ������

	private:
		// ������
		struct ListNode
		{
			using NodePtr = ListNode*;	// ���ָ������

			NodePtr next;		// ��ָ��
			NodePtr prior;		// ǰָ��
			ValueType data;	// Ԫ��ֵ
		};

		// ���������
		struct ListIterator : public BidirectionalIterator<ValueType>
		{
			using ValueType = ValueType;
			using NodePtr = ListNode*;

			NodePtr node;	// �������ڴ���һ��ָ�룬ָ��������

			ListIterator(NodePtr node) : node(node) {}
			ListIterator() : node(nullptr) {}
			ListIterator(const ListIterator& iter) : node(iter.node) {}

			bool operator==(const ListIterator& iter) const { return node == iter.node; }
			bool operator!=(const ListIterator& iter) const { return !(*this == iter); }

			// *iterator => �õ�����data
			Reference operator*() const { return (*node).data; }
			Pointer operator->() const { return &(operator*()); }

			// ǰ��++
			ListIterator& operator++()
			{
				node = node->next;
				return *this;
			}
			// ����++
			ListIterator operator++(int)
			{
				ListIterator temp = *this;
				node = node->next;
				return temp;
			}
			// ǰ��--
			ListIterator& operator--()
			{
				node = node->prior;
				return *this;
			}
			// ����--
			ListIterator operator--(int)
			{
				ListIterator temp = *this;
				node = node->prior;
				return temp;
			}
		};

	public:
		using NodePtr = ListNode*;		// ���ָ������
		using Iterator = ListIterator;	// ������
	};
}