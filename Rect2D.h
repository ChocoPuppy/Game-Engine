#pragma once
#include "Vector2D.h"
/// @brief This rectangle returns all values as if the center of the rectangle is at 0,0, to get it's actual position in the world, just offset/add it to wherever the center is.
struct Rect2D : Vector2D
{
	Vector2D BottomRightCorner();
	Vector2D TopLeftCorner();

	/// @brief Gives the total width and height of the rectangle.
	/// @return The distance between TopLeftCornerPos and BottomRightCornerPos.
	Vector2D getSize();

	/// @brief Sets the width and height of the rectangle.
	/// @param value Changes the distance between TopleftCornerPos and BottomRightCornerPos.
	void setSize( Vector2D value );

private:
	Vector2D _sizeFromMiddle;
};