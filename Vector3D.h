#pragma once
#include "Vector2D.h"

struct Vector3D : Vector2D
{
	using Vector2D::x;
	using Vector2D::y;

	double z;

	constexpr Vector3D( double x = 0, double y = 0, double z = 0 ) noexcept : Vector2D( x, y ), z( z ) {}
	constexpr Vector3D( Vector2D xy, double z = 0 ) noexcept : Vector2D( xy ), z( z ) {}

	constexpr Vector3D abs() const noexcept { return { Vector2D::abs(),std::abs( z ) }; }
	constexpr Vector3D crossProduct( Vector3D const & rhs ) const noexcept
	{
		Vector3D crossProduct{};
		crossProduct.x = Vector2D::crossProduct( rhs );
		crossProduct.y = y * rhs.z;
		crossProduct.z = z * rhs.x;

		return crossProduct;
	}
	constexpr Vector3D normalize() const noexcept
	{
		Vector3D normalized = *this;
		if (magnitude() > 0)
		{
			normalized.x /= magnitude();
			normalized.y /= magnitude();
			normalized.z /= magnitude();
		}
		return normalized;
	}
	constexpr Vector3D scalar( float scale ) const noexcept { return { Vector2D::scalar( scale ),z * scale }; }

	constexpr float dotProduct( Vector3D const & rhs ) const noexcept { return Vector2D::dotProduct( rhs ) + z * rhs.z; }
	constexpr float magnitude() const noexcept { return sqrtf( dotProduct( *this ) ); }

	constexpr Vector3D & operator+=( Vector3D const & rhs ) noexcept { *static_cast<Vector2D *>( this ) += rhs; z += rhs.z; return *this; }
	constexpr Vector3D & operator-=( Vector3D const & rhs ) noexcept { x -= rhs.x; y -= rhs.y; return *this; }

	friend constexpr Vector3D operator+( Vector3D lhs, Vector3D const & rhs ) noexcept { return lhs += rhs; }
	friend constexpr Vector3D operator-( Vector3D lhs, Vector3D const & rhs ) noexcept { return lhs -= rhs; }
	friend constexpr Vector3D operator-( Vector3D lhs ) noexcept { return { -static_cast<Vector2D>( lhs ),-lhs.z }; }
};