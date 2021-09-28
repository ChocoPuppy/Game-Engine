#pragma once
#include "Vector2D.h"
#include <algorithm>
/// @brief All vector2D's from and going into this object is assumed to be relative to the center of the rectangle being at 0,0.
struct Rect2D
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
	constexpr Vector2D supportPointOf( Vector2D point )
	{
		Vector2D difference{};
		difference.x = std::max( { (float)( leftEdge() - point.x ),0.0f, (float)( point.x - rightEdge() ) } );
		difference.y = std::max( { (float)( bottomEdge() - point.y ),0.0f, (float)( point.y - topEdge() ) } );
		return difference;
	}

	constexpr float distanceFromPoint( Vector2D point )
	{
		return supportPointOf( point ).magnitude();
	}

	/// @brief Figures the minimum distance between two rectangles.
	/// @param otherRect The other rectangle to consider.
	/// @param otherRectCenterRelative The center of the other rectangle relative to our center.
	/// @return The distance between the closest spot on our rectangle to the closest spot on the other rectangle.
	constexpr float distanceFromRectangle( Rect2D otherRect, Vector2D otherRectCenterRelative )
	{
		const float distanceBetweenOtherRectCenterToUs = distanceFromPoint( otherRectCenterRelative );
		const float distanceBetweenRectangleCenters = otherRectCenterRelative.abs().magnitude();
		const float distanceBetweenOurCenterToOurEdge = distanceBetweenRectangleCenters - distanceBetweenOtherRectCenterToUs;
		float distanceBetweenRectangleEdges = 0;
		//If the other rectangle is the same size as us, don't bother calculating their internal distance, it's the exact same as ours. The line inside their rectangle will be the mirror of the line inside ours. Because Maths.
		if (otherRect.getSize() == getSize())
		{
			distanceBetweenRectangleEdges = distanceBetweenRectangleCenters - ( distanceBetweenOurCenterToOurEdge * 2 );
		}
		else
		{
			//If it's x, y from our center (0,0), then we must be -x,-y from them
			const Vector2D CenterRelativeToOtherRectangleCenter = -otherRectCenterRelative;
			const float distanceBetweenUsToOtherRectCenter = std::abs( otherRect.distanceFromPoint( CenterRelativeToOtherRectangleCenter ) );
			const float distanceFromOthersCenterToOthersEdge = distanceBetweenRectangleCenters - distanceBetweenUsToOtherRectCenter;
			distanceBetweenRectangleEdges = distanceBetweenRectangleCenters - ( distanceBetweenOurCenterToOurEdge + distanceFromOthersCenterToOthersEdge );
		}

		return distanceBetweenRectangleEdges;
	}

	constexpr bool operator==( Rect2D rhs ) noexcept
	{
		return Rect2D::_sizeFromMiddle == rhs._sizeFromMiddle;
	}

	constexpr bool operator<( Rect2D rhs ) noexcept
	{
		return _sizeFromMiddle < rhs._sizeFromMiddle;
	}

private:
	//The amount the rectangle extends from its center.
	Vector2D _sizeFromMiddle;
};