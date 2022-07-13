#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define LIST

#ifndef ALLOCATOR
#include "allocator.hpp"
#endif // !ALLOCATOR
#ifndef ITERATOR
#include "iterator.hpp"
#endif // !ITERATOR
#ifndef ALGORITHM
#include "algorithm.hpp"
#endif // !ALGORITHM

namespace mstl_itm
{
	template <class _ValueT>
	class List
	{
	public:
		using ValueType = _ValueT;		// Ԫ������
		using Reference = _ValueT&;	// Ԫ����������
		using Pointer = _ValueT*;	// Ԫ��ָ������

	private:
		// ������
		struct ListNode
		{
			using NodePtr = ListNode*;	// ���ָ������

			NodePtr next;		// ��ָ��
			NodePtr prior;		// ǰָ��
			ValueType data;	// Ԫ��ֵ

			ListNode() : next(nullptr), prior(nullptr), data(ValueType()) {}
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

	private:
		NodePtr dummyHead;	// �����ͷ���

	public:
		// ��ȡ��ʼ������
		Iterator Begin() { return Iterator(dummyHead->next); }

		// ��ȡ��ֹ������
		Iterator End() { return Iterator(dummyHead); }

		// �ж��Ƿ�Ϊ��
		bool IsEmpty() { return dummyHead->next == dummyHead; }

		// ��ȡ����Ԫ�ظ���
		size_t Size() { return Algorithm::Distance(Begin(), End()); }

		// ��Ԫ��
		Reference Front() { return *Begin(); }

		// βԪ��
		Reference Back() { return *(--End()); }

	private:
		// ����һ�����
		NodePtr CreateNode() { return Allocator<ListNode>::Allocate(); }
		NodePtr CreateNode(const ValueType& elem)
		{
			NodePtr p = CreateNode();
			p->data = elem;
			return p;
		}

		// �ͷ�һ�����
		void DeleteNode(NodePtr p) { Allocator<ListNode>::Deallocate(p); }

	public:
		// Ĭ�Ϲ���
		List()
		{
			dummyHead = CreateNode();
			dummyHead->next = dummyHead;
			dummyHead->prior = dummyHead;
		}

		// �������
		void Clear()
		{
			NodePtr curNode = dummyHead->next, nextNode;
			// �����ͷź������
			while (curNode != dummyHead)
			{
				nextNode = curNode->next;
				DeleteNode(curNode);
				curNode = nextNode;
			}
			dummyHead->next = dummyHead;
			dummyHead->prior = dummyHead;
		}

		// ����
		~List()
		{
			// ���
			Clear();
			// �ͷ�dummyHead
			DeleteNode(dummyHead);
			dummyHead = nullptr;
		}

		// ������
		Iterator Insert(Iterator pos, const ValueType& val)
		{
			// �������
			NodePtr newNode = CreateNode(val);
			// ����ָ��
			newNode->next = pos.node;
			newNode->prior = (pos.node)->prior;
			newNode->prior->next = newNode;
			(pos.node)->prior = newNode;
			return Iterator(newNode);
		}

		// β����
		void PushBack(const ValueType& val) { Insert(End(), val); }

		// ͷ����
		void PushFront(const ValueType& val) { Insert(Begin(), val); }

		// �������
		Iterator Erase(Iterator pos)
		{
			NodePtr priorNode = (pos.node)->prior;
			NodePtr nextNode = (pos.node)->next;
			priorNode->next = nextNode;
			nextNode->prior = priorNode;
			DeleteNode(pos.node);
			return Iterator(nextNode);
		}

		// βɾ
		ValueType PopBack()
		{
			Iterator temp = End();
			ValueType res = (--temp).node->data;
			Erase(temp);
			return res;
		}

		// ͷɾ
		ValueType PopFront()
		{
			Iterator temp = Begin();
			ValueType res = temp.node->data;
			Erase(temp);
			return res;
		}

		// �Ƴ�ָ��Ԫ��
		void Remove(const ValueType& elem)
		{
			for (auto iter = Begin(); iter != End();)
			{
				if ((iter.node)->data == elem)
					iter = Erase(iter);
				else
					iter++;
			}
		}
	};
}