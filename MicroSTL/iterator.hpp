// �������ӿ�: ���Զ���4�ֵ�������������ع�ϵ
#define _CRT_SECURE_NO_WARNINGS

namespace mstl_itm
{
	template <class _ValueT>
	class InputIterator
	{
	public:
		using ValueType		= _ValueT;	// ������ָ��ֵ������
		using IterType			= InputIterator;
	};

	// ������ʵ���������
	template <class _ValueT>
	class ForwardIterator : public InputIterator<_ValueT>
	{
	public:
		using IterType			= ForwardIterator;
	};

	// ˫����ʵ���������
	template <class _ValueT>
	class BidirectionalIterator : public ForwardIterator<_ValueT>
	{
	public:
		using IterType			= BidirectionalIterator;
	};

	// ������ʵ���������
	template <class _ValueT>
	class RandomAcessIterator : public BidirectionalIterator<_ValueT>
	{
	public:
		using IterType			= RandomAcessIterator;
	};

	// ������������ȡ��
	template <class _Iter>
	class IteratorTraits
	{
	public:
		using ValueType			= typename _Iter::ValueType;	// ������ָ��ֵ������
		using IterType				= typename _Iter::IterType;	// ����������
		using DifferenceType		= size_t;	// ����������������
	};

	template <class _Iter>
	class IteratorTraits<_Iter*>
	{
	public:
		using ValueType		= _Iter;
		using IterType			= RandomAcessIterator<ValueType>;
		using DifferenceType = size_t;
	};
}