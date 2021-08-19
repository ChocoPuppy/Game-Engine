#include "CollisionTester.h"
#include "Vector2D.h"
#include "Rect2D.h"
#include "ICollider.h"
#include "CircleCollider2D.h"

Collision::Collision Collision::testForGenericOverlap( ColliderAtPosition<ICollider> const colA, ColliderAtPosition<ICollider> const colB )
{
	Collision collision = Collision();
	Vector2D colABottomRight;
	Vector2D colATopLeft;
	Vector2D colBBottomRight;
	Vector2D colBTopLeft;
	{
		Rect2D colAExtents = colA.collider.extentsOfCollider();
		Rect2D colBExtents = colB.collider.extentsOfCollider();

		colABottomRight = relativeColliderPositionToWorldPosition( colAExtents.BottomRightCorner(), colA.position );
		colATopLeft = relativeColliderPositionToWorldPosition( colAExtents.TopLeftCorner(), colA.position );
		colBBottomRight = relativeColliderPositionToWorldPosition( colBExtents.BottomRightCorner(), colB.position );
		colBTopLeft = relativeColliderPositionToWorldPosition( colBExtents.TopLeftCorner(), colB.position );
	}

	bool isColARightPastColBLeft = colABottomRight < colBTopLeft;
	bool isColALeftBeforeColBRight = colATopLeft > colBBottomRight;
	if (isColARightPastColBLeft && isColALeftBeforeColBRight)
	{
		collision.intersectDistance = ( colA.position - colB.position ).magnitude();
	}

	return collision;
}

Vector2D Collision::relativeColliderPositionToWorldPosition( Vector2D relativePosition, Vector2D worldPosition )
{
	return relativePosition + worldPosition;
}