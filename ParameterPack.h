#pragma once
template<typename... Args>
struct ParameterPack
{
public:
	template<template<typename...> class T>
	using apply = T<Args...>;

	//Creates a version of the parameter pack with PrefixArgs before Args in the template parameter pack.
	template<typename... PrefixArgs>
	using Prefix = ParameterPack<PrefixArgs..., Args...>;

	//Creates a version of the parameter pack with PostfixArgs after Args in the template parameter pack.
	template<typename... PostfixArgs>
	using Postfix = ParameterPack<Args..., PostfixArgs...>;
};