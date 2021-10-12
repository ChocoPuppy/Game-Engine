#pragma once
#include "IShape.h"
class Line2D : public IShape
{
	Vector2D _direction;
public:
	Line2D( Vector2D direction ) : _direction( direction ) {}

	virtual Vector2D getSupportPointOf( Vector2D point ) const noexcept override;

	Vector2D getDirection() const { return _direction; }
	void setDirection( Vector2D direction ) { _direction = direction; }

	/// @brief
	/// @param t The point on the line to return. 1 will return getDirection(), aka the lines size, 0 will return 0,0. Values greater than 1 will return points off in the direction the line points.
	/// @return a point on the line at (t * 100)% of the distance.
	Vector2D lerp( double t ) const;
};