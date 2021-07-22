#pragma once
#include <algorithm>
namespace CustomMaths
{
	/// @brief If value is inbetween min and max: return value. Otherwise return min or max depending on which the value is greater/less than.
	/// @tparam ComparableType The type to clamp. Must have <
	/// @param value The value to check.
	/// @param max The greatest value can be, if value is greater, return max.
	/// @param min The least value can be, if value is less, return min.
	/// @return min if value is less than min, max if value is greater than max or value if neither is true.
	template<class ComparableType>
	constexpr ComparableType const & clamp( ComparableType const & value, ComparableType const & max, ComparableType const & min )
	{
		return std::min( max, std::max( min, value ) );
	}
}