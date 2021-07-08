#pragma once
#include <utility>
struct Size : std::pair<int, int>
{
public:
	inline int & width() { return first; }
	inline int & height() { return second; }

	constexpr Size( int width = 0, int height = 0 ) : std::pair<int, int>( width, height ) {}
};