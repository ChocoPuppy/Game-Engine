#pragma once
#include <utility>
#include <math.h>
struct Vector2D : std::pair<double, double>
{
	constexpr Vector2D( double x = 0, double y = 0 ) noexcept : std::pair<double, double>{ x,y }, x( first ), y( second ) {}
	constexpr Vector2D( Vector2D const & vector2D ) noexcept : Vector2D( vector2D.x, vector2D.y ) {}
	constexpr Vector2D( Vector2D && vector2D ) noexcept : Vector2D( vector2D.x, vector2D.y ) {}

	constexpr Vector2D & operator=( Vector2D const & vector2D ) noexcept { x = vector2D.x; y = vector2D.y; return *this; }

	double & x;
	double & y;

	constexpr Vector2D normalize() const
	{
		Vector2D normalizedVector{ x,y };
		const float mag = magnitude();

		if (mag > 0)
		{
			normalizedVector.x /= mag;
			normalizedVector.y /= mag;
		}
		return normalizedVector;
	}

	constexpr Vector2D abs() const { return { std::abs( x ),std::abs( y ) }; }

	constexpr float angle() const { return -atan2f( y, x ); }
	constexpr bool isAngledLeft() const
	{
		constexpr float PI = 3.14159265f;
		bool const isMoving = magnitude() > 0;
		bool const isMovingLeft = std::abs( angle() ) > ( PI / 2.f );
		return isMoving && isMovingLeft;
	}

	constexpr float magnitude() const
	{
		return sqrtf( ( dotProduct( *this ) );
	}

	constexpr float distance( Vector2D point ) const noexcept
	{
		const Vector2D difference = *this - point;
		return difference.magnitude();
	}

	constexpr Vector2D scalar( float scale ) const noexcept { return { x * scale, y * scale }; }
	/// @brief Cross product of this and rhs.
	/// @param rhs The other vector2D to cross product with.
	/// @return The magnitude of a vector (the cross product of the 3D version of these two vectors) at a right angle to both values.
	constexpr float crossProduct( Vector2D const & rhs ) const noexcept { return ( x * rhs.y ) - ( y * rhs.x ); }
	constexpr float dotProduct( Vector2D const & rhs ) const noexcept { return x * rhs.x + y * rhs.y; }

	constexpr Vector2D & operator+=( Vector2D const & rhs ) noexcept { x += rhs.x; y += rhs.y; return *this; }
	constexpr Vector2D & operator-=( Vector2D const & rhs ) noexcept { x -= rhs.x; y -= rhs.y; return *this; }

	friend constexpr Vector2D operator+( Vector2D lhs, Vector2D const & rhs ) noexcept { return lhs += rhs; }
	friend constexpr Vector2D operator-( Vector2D lhs, Vector2D const & rhs ) noexcept { return lhs -= rhs; }
	friend constexpr Vector2D operator-( Vector2D lhs ) noexcept { lhs.x = -lhs.x; lhs.y = -lhs.y; return lhs; }

	/// @brief An unsided non-assigning scalar multiplication.
	/// @detail The compiler, when reading operators, doesn't consider arguments in any specific order (so writing float * Vector2D is exactly the same as writing Vector2D * float to the compiler). When interpreting operators, it considered operator overrides of the lhs first if the lhs has a valid override, it'll call lhs.operator*(rhs), if the lhs has no valid operator overrides, then it considers global operator overrides, however it never tries to find any overrides in the rhs, so even if the right hand symbol has a perfectly valid operator override, it will never call rhs.operator*(lhs). As of such, by writing this as a friend function (friend functions are actually global unless specified otherwise and only connects to the class it's in in that it can access private members, so this function can't actually be called via Vector2D.operator*())
	/// @param lhs
	/// @param rhs
	/// @return a Vector2D with all values multiplied by rhs.
	friend constexpr Vector2D operator*( Vector2D const & lhs, float rhs ) noexcept { return lhs.scalar( rhs ); }

	//	friend Vector2D operator/( Vector2D lhs, float rhs );
};