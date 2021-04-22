#pragma once
/// @brief Some fuckery to pass around parameter packs. I didn't write this, I kinda stole it from this answer: https://stackoverflow.com/a/45288512
/// @tparam ...Parameters
template <typename ... Parameters>
struct ParameterPack
{
	template<template<class...> class Template> using apply = Template<Parameters...>;
};