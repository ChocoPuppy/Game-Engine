#pragma once
#include <utility>
struct Vector2D : std::pair<double,double>
{
	double & x();
	double & y();
};