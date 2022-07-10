// �ռ������: ���Ե����ڴ�
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
namespace mstl_itm
{
	template <class _AllocT>
	class Allocator
	{
	public:
		using AllocType	= _AllocT;	// ����
		using Pointer		= _AllocT*;	// ָ��
		using SizeType		= size_t;	// ��С����

	public:
		// ����һ���ڴ�ռ�
		static Pointer Allocate()
		{
			return new AllocType();
		}

		// ���������ڴ�ռ�
		static Pointer AllocateRange(SizeType size)
		{
			return new AllocType[size];
		}

		// �ͷ�һ���ڴ�ռ�
		static void Deallocate(Pointer p)
		{
			assert(p != nullptr);
			delete p;
		}

		// �ͷ������ڴ�ռ�
		static void DeallocateRange(Pointer p)
		{
			assert(p != nullptr);
			delete[] p;
		}
	};
}