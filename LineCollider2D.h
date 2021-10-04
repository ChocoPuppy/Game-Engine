#pragma once
#include "ICollider.h"
#include "Line2D.h"
#define LINE_COLLIDER_INCLUDED
#if RECT_COLLIDER_INCLUDED
#include "RectLineCollisionTest.h"
#endif
namespace Collision
{
	class LineCollider2D : public ICollider
	{
		bool _isRay;
	public:

		Line2D getLine() const;
		//When doing collisions for this object, don't collide with objects past the closest collided one.
		bool isRay() const;

		void setLine( Line2D line );
		void setIsRay( bool isRay );

		virtual std::string getTextureID() const override;
		virtual Rect2D extentsOfCollider() const override;
	};

	template<>
	struct TestForSpecificOverlap<LineCollider2D, LineCollider2D>
	{
		void operator()( LineCollider2D const & lineA, LineCollider2D const & lineB, CollisionData & data )
		{
			Vector2D const lineBRelativeToLineA = lineA.worldPositionToRelativePosition( lineB.getWorldPosition() );
		}
	};
}
