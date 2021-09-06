#pragma once
#include "ICollider.h"
#include "Circle2D.h"
#include "TextureWrapper.h"
#include "CollisionTester.h"
namespace Collision
{
	class CircleCollider2D : public ICollider
	{
	public:

		CircleCollider2D( std::shared_ptr<Transform2D const> transform = std::make_shared<Transform2D>(), Circle2D circle = Circle2D( 100 ) );

		virtual std::string getTextureID() const override;

		virtual Rect2D extentsOfCollider() const override;

		Circle2D getCircle() const { return _circle; }

		void setCircle( Circle2D circle ) { _circle = circle; }
	private:
		Circle2D _circle;
	};

	template<>
	struct TestForSpecificOverlap<CircleCollider2D, CircleCollider2D>
	{
		void operator()( CircleCollider2D const & colA, CircleCollider2D const & colB, CollisionData & data )
		{
			//			std::cout << "Circle collision" << std::endl;
			const float distance = ( colA.getWorldPosition() - colB.getWorldPosition() ).magnitude();
			const float colliderRadiusCombined = colA.getCircle().radius + colB.getCircle().radius;

			data.intersectDistance = ( distance < colliderRadiusCombined ) ? colliderRadiusCombined - distance : 0;
		}
	};
}