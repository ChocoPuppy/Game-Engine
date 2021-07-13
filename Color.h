#pragma once
#include <tuple>
struct Color : private std::tuple<int, int, int, int>
{
	inline int & red() { return std::get<0>( *getBase() ); }
	inline int & blue() { return std::get<1>( *getBase() ); }
	inline int & green() { return std::get<2>( *getBase() ); }
	inline int & alpha() { return std::get<3>( *getBase() ); }

	constexpr Color( int red, int green, int blue, int alpha = 255 ) : Base( red, green, blue, alpha ) {}

	inline static constexpr Color White() { return Color( 255, 255, 255 ); }
	inline static constexpr Color Purple() { return Color( 255, 255, 0 ); }
	inline static constexpr Color Yellow() { return Color( 255, 0, 255 ); }
	inline static constexpr Color Red() { return Color( 255, 0, 0 ); }
	inline static constexpr Color Cyan() { return Color( 0, 255, 255 ); }
	inline static constexpr Color Green() { return Color( 0, 255, 0 ); }
	inline static constexpr Color Blue() { return Color( 0, 0, 255 ); }
	inline static constexpr Color Black() { return Color( 0, 0, 0 ); }

private:
	using Base = std::tuple<int, int, int, int>;
	Base * getBase()
	{
		return static_cast<Base *>( this );
	};
};