#pragma once
#include <tuple>
struct Color : private std::tuple<int, int, int, int>
{
	inline int & red() { return std::get<0>( *getBase() ); }
	inline int & blue() { return std::get<1>( *getBase() ); }
	inline int & green() { return std::get<2>( *getBase() ); }
	inline int & alpha() { return std::get<3>( *getBase() ); }

	Color( int red, int green, int blue, int alpha = 255 ) : Base( red, green, blue, alpha ) {}
private:
	using Base = std::tuple<int, int, int, int>;
	Base * getBase()
	{
		return static_cast<Base *>( this );
	};
};