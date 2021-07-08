#pragma once
#include <utility>
struct Vector2D : std::pair<double, double>
{
	Vector2D( double x = 0, double y = 0 ) : std::pair<double, double>{ x,y } {}

	double const & x() const;
	double & x();
	double const & y() const;
	double & y();

	float magnitude() const;
	Vector2D normalize() const;

	Vector2D & operator+=( Vector2D const & rhs );
	Vector2D & operator-=( Vector2D const & rhs );
	Vector2D & operator*=( float rhs );

	friend Vector2D operator+( Vector2D lhs, Vector2D const & rhs );
	friend Vector2D operator-( Vector2D lhs, Vector2D const & rhs );

	friend Vector2D operator*( Vector2D lhs, float rhs );
};