// �ռ������: ���Ե����ڴ�
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
namespace mstl_itm
{
	template <class _AllocT>
	class Allocator
	{
	public:
		using AllocType	= _AllocT;
		using Pointer		= _AllocT*;

	public:
		static Pointer Allocate()
		{
			return new AllocType();
		}

		static void Deallocate(Pointer p)
		{
			assert(p != nullptr);
			delete p;
		}
	};
}