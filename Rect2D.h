#pragma once
#include "IShape.h"
#include <algorithm>
/// @brief All vector2D's from and going into this object is assumed to be relative to the center of the rectangle being at 0,0.
struct Rect2D : public IShape
{
	constexpr Rect2D( Vector2D size = { 1,1 } ) noexcept
	{
		setSize( size );
	}

	constexpr float rightEdge() const noexcept { return _sizeFromMiddle.x; }

	constexpr float leftEdge() const noexcept { return -_sizeFromMiddle.x; }

	constexpr float topEdge() const noexcept { return _sizeFromMiddle.y; }

	constexpr float bottomEdge() const noexcept { return -_sizeFromMiddle.y; }

	constexpr Vector2D topLeftCorner() noexcept { return { leftEdge(),topEdge() }; }
	constexpr Vector2D topRightCorner() noexcept { return { rightEdge(),topEdge() }; }
	constexpr Vector2D bottomRightCorner() noexcept { return { rightEdge(),bottomEdge() }; }
	constexpr Vector2D bottomLeftCorner() noexcept { return { leftEdge(), bottomEdge() }; }
	/// @brief Gives the total width and height of the rectangle.
	/// @return The distance between TopLeftCornerPos and BottomRightCornerPos.
	constexpr Vector2D getSize() const noexcept
	{
		return _sizeFromMiddle * 2;
	}

	/// @brief Sets the width and height of the rectangle.
	/// @param value Changes the distance between TopleftCornerPos and BottomRightCornerPos.
	constexpr void setSize( Vector2D value ) noexcept
	{
		_sizeFromMiddle = value;
		_sizeFromMiddle.x /= 2;
		_sizeFromMiddle.y /= 2;
	}

	//Get the closest point in the object to an outside point.
	virtual Vector2D getSupportPointOf( Vector2D point ) const noexcept override
	{
		Vector2D difference{};
		difference.x = std::max( { (float)( leftEdge() - point.x ),0.0f, (float)( point.x - rightEdge() ) } );
		difference.y = std::max( { (float)( bottomEdge() - point.y ),0.0f, (float)( point.y - topEdge() ) } );
		return difference;
	}

	/// @brief Figures the minimum distance between two rectangles.
	/// @param otherRect The other rectangle to consider.
	/// @param otherRectCenterRelative The center of the other rectangle relative to our center.
	/// @return The distance between the closest spot on our rectangle to the closest spot on the other rectangle.
	float distanceFromRectangle( Rect2D otherRect, Vector2D otherRectCenterRelative );

	bool operator==( Rect2D rhs ) noexcept
	{
		return Rect2D::_sizeFromMiddle == rhs._sizeFromMiddle;
	}

	bool operator<( Rect2D rhs ) noexcept
	{
		return _sizeFromMiddle < rhs._sizeFromMiddle;
	}

private:
	//The amount the rectangle extends from its center.
	Vector2D _sizeFromMiddle;
};