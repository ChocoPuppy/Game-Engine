#include "Rect2D.h"

/// @brief Figures the minimum distance between two rectangles.
/// @param otherRect The other rectangle to consider.
/// @param otherRectCenterRelative The center of the other rectangle relative to our center.
/// @return The distance between the closest spot on our rectangle to the closest spot on the other rectangle.

float Rect2D::distanceFromRectangle( Rect2D otherRect, Vector2D otherRectCenterRelative )
{
	const float distanceBetweenOtherRectCenterToUs = distanceFromPoint( otherRectCenterRelative ).magnitude();
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
		const float distanceBetweenUsToOtherRectCenter = std::abs( otherRect.distanceFromPoint( CenterRelativeToOtherRectangleCenter ).magnitude() );
		const float distanceFromOthersCenterToOthersEdge = distanceBetweenRectangleCenters - distanceBetweenUsToOtherRectCenter;
		distanceBetweenRectangleEdges = distanceBetweenRectangleCenters - ( distanceBetweenOurCenterToOurEdge + distanceFromOthersCenterToOthersEdge );
	}

	return distanceBetweenRectangleEdges;
}