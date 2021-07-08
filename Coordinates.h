#pragma once
#include <utility>
struct Coordinates : std::pair<int, int>
{
public:
	inline int & x() { return first; }
	inline int & y() { return second; }

	constexpr Coordinates( int x = 0, int y = 0 ) : std::pair<int, int>( x, y ) {}
};
