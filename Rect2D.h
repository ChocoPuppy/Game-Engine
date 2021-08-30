#pragma once
#include "Vector2D.h"
#include <algorithm>
/// @brief All vector2D's from and going into this object is assumed to be relative to the center of the rectangle being at 0,0.
struct Rect2D
{
	constexpr Rect2D( Vector2D size = { 1,1 } )
	{
		setSize( size );
	}

	constexpr float rightEdge() const { return _sizeFromMiddle.x; }

	constexpr float leftEdge() const { return -_sizeFromMiddle.x; }

	constexpr float topEdge() const { return _sizeFromMiddle.y; }

	constexpr float bottomEdge() const { return -_sizeFromMiddle.y; }

	/// @brief Gives the total width and height of the rectangle.
	/// @return The distance between TopLeftCornerPos and BottomRightCornerPos.
	constexpr Vector2D getSize() const
	{
		return _sizeFromMiddle * 2;
	}

	/// @brief Sets the width and height of the rectangle.
	/// @param value Changes the distance between TopleftCornerPos and BottomRightCornerPos.
	constexpr void setSize( Vector2D value )
	{
		_sizeFromMiddle = value;
		_sizeFromMiddle.x /= 2;
		_sizeFromMiddle.y /= 2;
	}

	constexpr float distanceFromPoint( Vector2D point )
	{
		Vector2D difference{};
		difference.x = std::max( { (float)( leftEdge() - point.x ),0.0f, (float)( point.x - rightEdge() ) } );
		difference.y = std::max( { (float)( bottomEdge() - point.y ),0.0f, (float)( point.y - topEdge() ) } );

		return difference.magnitude();
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

	constexpr bool operator==( Rect2D rhs )
	{
		return _sizeFromMiddle == rhs._sizeFromMiddle;
	}

	constexpr bool operator<( Rect2D rhs )
	{
		return _sizeFromMiddle < rhs._sizeFromMiddle;
	}

private:
	//The amount the rectangle extends from its center.
	Vector2D _sizeFromMiddle;
};