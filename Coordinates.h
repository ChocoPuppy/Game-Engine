#pragma once
#include <utility>
struct Vector2D;
struct Coordinates : std::pair<int, int>
{
public:
	int & x;
	int & y;

	constexpr Coordinates( int x = 0, int y = 0 ) : std::pair<int, int>( x, y ), x( first ), y( second ) {};
	constexpr Coordinates( Coordinates const & other ) : Coordinates( other.x, other.y ) {};
	explicit Coordinates( Vector2D const & vector2D );
};
