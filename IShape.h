#pragma once
#include "Vector2D.h"
//Interface for a shape with all positions entered and returned relative to the shape, which is always assumed to be 0,0.
struct IShape
{
	virtual ~IShape() = default;
	virtual Vector2D getSupportPointOf( Vector2D point ) const noexcept = 0;
	/// @brief Gives the distance from the edge of the shape to the given (relative) point.
	/// @param point The point we're finding the distance to.
	/// @return a vector of the remaining distance between our point and the edge of the shape.
	Vector2D distanceFromPoint( Vector2D point ) const noexcept { return point - getSupportPointOf( point ); }
};