// ��װһЩ���õķº�����������ϵ��º����͹�ϣ����
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define FUNCTOR

#include <functional>

namespace mstl_itm
{
	template <class _ValueT>
	struct Less
	{
		bool operator()(const _ValueT& t1, const _ValueT& t2) const { return t1 < t2; }
	};

	template <class _ValueT>
	struct Greater
	{
		bool operator()(const _ValueT& t1, const _ValueT& t2) const { return t1 > t2; }
	};

	// ��ϣ����
	template <typename T>
	void CombineHash(size_t& seed, const T& t)
	{
		seed ^= std::hash<T>()(t) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	template <typename T>
	void GetHash(size_t& seed, const T& t)
	{
		CombineHash(seed, t);
	}

	template <typename T, typename... _Types>
	void GetHash(size_t& seed, const T& t, const _Types&... types)
	{
		CombineHash(seed, t);
		GetHash(seed, types...);
	}

	template <typename... _Types>
	size_t GetHash(const _Types&... types)
	{
		size_t seed = 0;
		GetHash(seed, types...);
		return seed;
	}
}