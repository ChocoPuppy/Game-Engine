#pragma once
#include "IShape.h"
struct Circle2D : public IShape
{
	float radius;

	constexpr Circle2D( float radius = 1 ) noexcept : radius( radius ) {}
	constexpr float diameter() const noexcept { return radius * 2; }
	virtual Vector2D getSupportPointOf( Vector2D point ) const noexcept override { return point.normalize() * radius; }
};