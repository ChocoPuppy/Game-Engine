#include "Vector2D.h"
#include <math.h>
double const & Vector2D::x() const
{
	return first;
}

double & Vector2D::x()
{
	return const_cast<double &>( const_cast<Vector2D const *>( this )->x() );
}

double const & Vector2D::y() const
{
	return second;
}

double & Vector2D::y()
{
	return const_cast<double &>( const_cast<Vector2D const *>( this )->y() );
}

float Vector2D::magnitude() const
{
	return sqrtf( x() * x() + y() * y() );
}

Vector2D Vector2D::normalize() const
{
	Vector2D normalizedVector;
	float mag = magnitude();

	if (mag > 0)
	{
		normalizedVector.x() /= mag;
		normalizedVector.y() /= mag;
	}
}

void Vector2D::operator+=( Vector2D const & rhs )
{
	x() += rhs.x();
	y() += rhs.y();
}

void Vector2D::operator-=( Vector2D const & rhs )
{
	x() -= rhs.x();
	y() -= rhs.y();
}

void Vector2D::operator*=( float rhs )
{
	x() *= rhs;
	y() *= rhs;
}

Vector2D operator+( Vector2D lhs, Vector2D const & rhs )
{
	return lhs += rhs;
}

Vector2D operator-( Vector2D lhs, Vector2D const & rhs )
{
	return lhs -= rhs;
}