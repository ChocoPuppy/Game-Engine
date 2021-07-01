#pragma once
#include <utility>
struct Vector2D : std::pair<double, double>
{
	Vector2D( double x = 0, double y = 0 ) : std::pair<double, double>{ x,y } {}

	double & x();
	double & y();
};