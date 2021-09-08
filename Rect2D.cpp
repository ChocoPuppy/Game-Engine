#include "Rect2D.h"

Vector2D Rect2D::BottomRightCorner()
{
	return _sizeFromMiddle;
}

Vector2D Rect2D::TopLeftCorner()
{
	return -BottomRightCorner();
}

Vector2D Rect2D::getSize()
{
	return _sizeFromMiddle * 2;
}

void Rect2D::setSize( Vector2D value )
{
	_sizeFromMiddle = value / 2;
}