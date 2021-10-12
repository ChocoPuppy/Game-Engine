#include "Line2D.h"
#include <algorithm>
Vector2D Line2D::getSupportPointOf( Vector2D point ) const noexcept
{
	static constexpr Vector2D origin = { 0,0 };
	//If the ray has no direction, it's just a point. So the support point will always be 0,0.
	if (getDirection() == origin) return origin;

	bool isDirectionPositive = getDirection() > origin;

	Vector2D const normalizedDirection = getDirection().normalize();
	float const perpendicularLineDistance = point.dotProduct( normalizedDirection );
	Vector2D const potentialSupportPoint = normalizedDirection * perpendicularLineDistance;
	Vector2D supportPoint;
	//If the support point is calculated to be greater than the line/ray itself, just clamp it to the end of the line.
	if (isDirectionPositive)
	{
		supportPoint = std::min( getDirection(), potentialSupportPoint );
	}
	else
	{
		supportPoint = std::max( getDirection(), potentialSupportPoint );
	}

	return supportPoint;
}

Vector2D Line2D::lerp( double t ) const
{
	Vector2D const lerpValue = getDirection().scalar( t );
	return lerpValue;
}