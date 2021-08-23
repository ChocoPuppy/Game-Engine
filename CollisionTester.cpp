#include "CollisionTester.h"
#include "Vector2D.h"
#include "Rect2D.h"
#include "ICollider.h"
#include "CircleCollider2D.h"

Collision::CollisionData Collision::testForGenericOverlap( ICollider const & colA, ICollider const & colB )
{
	CollisionData collision = CollisionData();
	Vector2D colABottomRight;
	Vector2D colATopLeft;
	Vector2D colBBottomRight;
	Vector2D colBTopLeft;
	{
		Rect2D colAExtents = colA.extentsOfCollider();
		Rect2D colBExtents = colB.extentsOfCollider();

		colABottomRight = relativeColliderPositionToWorldPosition( colAExtents.BottomRightCorner(), colA.getWorldPosition() );
		colATopLeft = relativeColliderPositionToWorldPosition( colAExtents.TopLeftCorner(), colA.getWorldPosition() );
		colBBottomRight = relativeColliderPositionToWorldPosition( colBExtents.BottomRightCorner(), colB.getWorldPosition() );
		colBTopLeft = relativeColliderPositionToWorldPosition( colBExtents.TopLeftCorner(), colB.getWorldPosition() );
	}

	bool isColARightPastColBLeft = colABottomRight < colBTopLeft;
	bool isColALeftBeforeColBRight = colATopLeft > colBBottomRight;
	if (isColARightPastColBLeft && isColALeftBeforeColBRight)
	{
		collision.intersectDistance = ( colA.getWorldPosition() - colB.getWorldPosition() ).magnitude();
	}

	return collision;
}

Vector2D Collision::relativeColliderPositionToWorldPosition( Vector2D relativePosition, Vector2D worldPosition )
{
	return relativePosition + worldPosition;
}