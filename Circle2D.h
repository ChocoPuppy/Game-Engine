#pragma once
struct Circle2D
{
	float radius;

	constexpr Circle2D( float radius = 1 ) noexcept : radius( radius ) {}
	constexpr float diameter() const noexcept { return radius * 2; }
};