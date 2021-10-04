#pragma once
#include "RectCollider2D.h"
#include "LineCollider2D.h"

namespace Collision
{
	struct TestForSpecificOverlap<RectCollider2D, LineCollider2D>
	{
		void operator()( RectCollider2D const & col1, LineCollider2D const & col2, CollisionData & data )
		{
			Vector2D linePositionRelativeToRectangle = col1.worldPositionToRelativePosition( col2.getWorldPosition() );
		}
	};
}