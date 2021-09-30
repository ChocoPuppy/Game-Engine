#pragma once
#include "ICollider.h"
namespace Collision
{
	class LineCollider2D : public ICollider
	{
		Vector2D _direction;
		bool _isRay;
	public:

		Vector2D getDirection() const;
		//When doing collisions for this object, don't collide with objects past the closest collided one.
		bool isRay() const;

		void setDirection( Vector2D newDirection );
		void setIsRay( bool isRay );
		virtual std::string getTextureID() const override;
		virtual Rect2D extentsOfCollider() const override;
		virtual Vector2D getSupportPointOf( Vector2D point ) const override;
	};
}
