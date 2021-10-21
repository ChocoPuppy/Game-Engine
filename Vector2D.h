#pragma once
#include <utility>
#include <math.h>
#include "TransversalDirections.h"
struct Vector2D : std::pair<double, double>
{
	constexpr Vector2D( double x = 0, double y = 0 ) noexcept : std::pair<double, double>{ x,y }, x( first ), y( second ) {}
	constexpr Vector2D( TransversalDirection dir ) noexcept : Vector2D( transversalDirectionToVector( dir ) ) {}
	constexpr Vector2D( Vector2D const & vector2D ) noexcept : Vector2D( vector2D.x, vector2D.y ) {}
	constexpr Vector2D( Vector2D && vector2D ) noexcept : Vector2D( vector2D.x, vector2D.y ) {}

	constexpr Vector2D & operator=( Vector2D const & vector2D ) noexcept { x = vector2D.x; y = vector2D.y; return *this; }

	double & x;
	double & y;

	constexpr Vector2D normalize() const noexcept
	{
		Vector2D normalizedVector = *this;
		const float mag = magnitude();
		if (mag > 0) normalizedVector / mag;
		return normalizedVector;
	}

	constexpr Vector2D abs() const noexcept { return { std::abs( x ),std::abs( y ) }; }

	constexpr float angle() const { return -atan2f( y, x ); }
	constexpr bool isAngledLeft() const noexcept
	{
		constexpr float PI = 3.14159265f;
		bool const isMoving = magnitude() > 0;
		bool const isMovingLeft = std::abs( angle() ) > ( PI / 2.f );
		return isMoving && isMovingLeft;
	}

	constexpr float magnitude() const noexcept
	{
		float const selfDotProduct = dotProduct( *this );
		float const absoluteSelfDotProduct = std::abs( selfDotProduct );
		float const magnitude = sqrt( absoluteSelfDotProduct );
		return magnitude;
	}

	constexpr float distance( Vector2D point ) const noexcept
	{
		const Vector2D difference = *this - point;
		return difference.magnitude();
	}

	constexpr Vector2D scalar( float scale ) const noexcept { return ( *this ) * scale; }
	constexpr Vector2D divisionScalar( float scale ) const noexcept { return ( *this ) / scale; }
	/// @brief Cross product of this and rhs.
	/// @param rhs The other vector2D to cross product with.
	/// @return The magnitude of a vector (the cross product of the 3D version of these two vectors) at a right angle to both values.
	constexpr float crossProduct( Vector2D const & rhs ) const noexcept { return ( x * rhs.y ) - ( y * rhs.x ); }
	constexpr float dotProduct( Vector2D const & rhs ) const noexcept { return x * rhs.x + y * rhs.y; }

	static constexpr Vector2D transversalDirectionToVector( TransversalDirection direction ) noexcept
	{
		using TD = TransversalDirection;
		switch (direction)
		{
		case TD::NONE: return none();
		case TD::UP: return up();
		case TD::DOWN: return down();
		case TD::LEFT: return left();
		case TD::RIGHT: return right();
		}
	}
	//Static constant constructors for basic directions. Can be added and normalized to form diagonal directions.
	static constexpr Vector2D up() noexcept { return { 0,1 }; }
	static constexpr Vector2D down() noexcept { return { 0,-1 }; }
	static constexpr Vector2D left() noexcept { return { -1,0 }; }
	static constexpr Vector2D right() noexcept { return { 1,0 }; }
	static constexpr Vector2D none() noexcept { return { 0,0 }; }

	constexpr Vector2D & operator+=( Vector2D const & rhs ) noexcept { return _add( rhs ); }
	constexpr Vector2D & operator-=( Vector2D const & rhs ) noexcept { return _subtract( rhs ); }
	constexpr Vector2D & operator*=( float rhs ) noexcept { return _scalar( rhs ); }
	constexpr Vector2D & operator/=( float rhs ) noexcept { return _divisionScalar( rhs ); }

	friend constexpr Vector2D operator+( Vector2D lhs, Vector2D const & rhs ) noexcept { return lhs += rhs; }
	friend constexpr Vector2D operator-( Vector2D lhs, Vector2D const & rhs ) noexcept { return lhs -= rhs; }

	friend constexpr Vector2D operator*( Vector2D lhs, float rhs ) noexcept { return lhs *= rhs; }

	friend constexpr Vector2D operator-( Vector2D lhs ) noexcept { lhs.x = -lhs.x; lhs.y = -lhs.y; return lhs; }

	constexpr Vector2D operator/( float rhs ) const noexcept { Vector2D scaledVector = *this; scaledVector /= rhs; return scaledVector; }

private:
	Vector2D & _add( Vector2D const & rhs ) noexcept { x += rhs.x; y += rhs.y; return *this; }
	Vector2D & _subtract( Vector2D const & rhs ) noexcept { return _add( -rhs ); }
	Vector2D & _scalar( float rhs ) noexcept { x *= rhs; y *= rhs; return *this; }
	Vector2D & _divisionScalar( float rhs ) noexcept { x /= rhs; y /= rhs; return *this; }
};