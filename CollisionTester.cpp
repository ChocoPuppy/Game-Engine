#include "CollisionTester.h"
#include "Vector2D.h"
#include "Rect2D.h"
#include "ICollider.h"

using namespace Collision;

CollisionData Collision::testForGenericOverlap( ICollider const & colA, ICollider const & colB )
{
	CollisionData collision = CollisionData();
	Vector2D colABottomRight;
	Vector2D colATopLeft;
	Vector2D colBBottomRight;
	Vector2D colBTopLeft;
	{
		Rect2D colAExtents = colA.extentsOfCollider();
		Rect2D colBExtents = colB.extentsOfCollider();

		colABottomRight = colA.relativePositionToWorldPosition( colAExtents.BottomRightCorner() );
		colATopLeft = colA.relativePositionToWorldPosition( colAExtents.TopLeftCorner() );
		colBBottomRight = colB.relativePositionToWorldPosition( colBExtents.BottomRightCorner() );
		colBTopLeft = colB.relativePositionToWorldPosition( colBExtents.TopLeftCorner() );
	}

	bool isColARightPastColBLeft = colABottomRight < colBTopLeft;
	bool isColALeftBeforeColBRight = colATopLeft > colBBottomRight;
	if (isColARightPastColBLeft && isColALeftBeforeColBRight)
	{
		collision.intersectDistance = ( colA.getWorldPosition() - colB.getWorldPosition() ).magnitude();
	}

	return collision;
}