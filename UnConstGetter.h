#pragma once
#include <type_traits>

/// @brief a shorthand way of casting a const value into a non-const value. For easily setting up const and non-const overrides of a getter. BE CAREFUL WITH THIS FUNCTION. DO NOT USE THIS FOR FUNCTIONS OUTSIDE OF YOUR OWN OBJECT. YOU HAVE BEEN WARNED.
/// @tparam ReturnType The non-const type you want to return.
/// @tparam ConstReturnType The const version of the type you want to return. I don't reccomend overriding this template argument, but I physically cannot stop you so just be very sure you want to do that before you do it.
/// @param constGet the return from the const version of your getter. This forces the const version of the getter to be called so you don't end up accidentally making a recursive loop.
/// @return The non-const version of constGet.
template<typename ConstReturnType, typename ReturnType = std::remove_const_t<ConstReturnType> >
ReturnType _unConstGetter( ConstReturnType constGet )
{
	return const_cast<ReturnType>( constGet );
}

/*template <typename ConstReturnType, typename ReturnType = std::remove_const_t<ConstReturnType>>
typename std::enable_if_t < std::is_same_v<ReturnType, ConstReturnType>, ReturnType>
_unConstGetter<ReturnType, ConstReturnType>( ConstReturnType constGet )
{
	return _unConstGetter<ReturnType, ConstReturnType>( constGet );
}*/