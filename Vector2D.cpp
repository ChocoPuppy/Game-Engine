#include "Vector2D.h"

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