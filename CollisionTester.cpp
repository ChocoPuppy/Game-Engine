#include "CollisionTester.h"
#include "Vector2D.h"
#include "Rect2D.h"
#include "ICollider.h"
using namespace Collision;

CollisionData Collision::testForGenericOverlap( ICollider const & colA, ICollider const & colB )
{
	CollisionData collision = CollisionData();

	//	const Vector2D colACenter = colA.getWorldPosition();
		/*float colARight;
		float colABottom;
		float colALeft;
		float colATop;*/

	const Vector2D colBCenter = colB.getWorldPosition();
	/*float colBRight;
	float colBBottom;
	float colBLeft;
	float colBTop;*/

	Rect2D colARectangle = colA.extentsOfCollider();
	Rect2D colBRectangle = colB.extentsOfCollider();

	/* {
			Vector2D colABottomRight = colA.relativePositionToWorldPosition( { colARectangle.rightEdge(),colARectangle.bottomEdge() } ); //
			colARight = colABottomRight.x;
			colABottom = colABottomRight.y;
		}
		{
			Vector2D colATopLeft = colA.relativePositionToWorldPosition( { colARectangle.leftEdge(), colARectangle.topEdge() } ); //
			colALeft = colATopLeft.x;
			colATop = colATopLeft.y;
		}

		{
			Vector2D colBBottomRight = colB.relativePositionToWorldPosition( { colBRectangle.rightEdge(),colBRectangle.topEdge() } ); //
			colBRight = colBBottomRight.x;
			colBBottom = colBBottomRight.y;
		}
		{
			Vector2D colBTopLeft = colB.relativePositionToWorldPosition( { colBRectangle.leftEdge(),colBRectangle.bottomEdge() } ); //
			colBLeft = colBTopLeft.x;
			colBTop = colBTopLeft.y;
		}
		const bool isColBRightPastColALeft = colALeft > colBRight;
		const bool isColBLeftBeforeColARight = colARight < colBLeft;
		const bool isColBBottomPastColATop = colATop > colBBottom;
		const bool isColBTopBeforeColABottom = colABottom < colBTop;*/

	const Vector2D colBCenterRelativeToColA = colA.worldPositionToRelativePosition( colBCenter );
	const float distanceBetweenRectangles = colARectangle.distanceFromRectangle( colBRectangle, colBCenterRelativeToColA );
	//	std::cout << colACenter.x << '-' << colACenter.y << ' ' << colBCenter.x << '-' << colBCenter.y << ' ' << distanceBetweenRectangles << std::endl;
		/*
		const bool isColALeftBeforeColBRight = colALeft < colBRight;
		const bool isColARightPastColBLeft = colARight > colBLeft;
		const bool isColABottomBeforeColBTop = colATop < colBBottom;
		const bool isColATopPastColBBottom = colABottom > colBTop;*/

		//If all tests are false.
	if (distanceBetweenRectangles <= 0)
	{
		collision.intersectDistance = std::abs( distanceBetweenRectangles );
	}

	return collision;
}