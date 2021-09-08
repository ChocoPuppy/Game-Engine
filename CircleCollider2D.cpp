#include "CircleCollider2D.h"

Collision::CircleCollider2D::CircleCollider2D( std::shared_ptr<Transform2D const> transform, Circle2D circle ) : ICollider( transform ), _circle( circle )
{}

std::string Collision::CircleCollider2D::getTextureID() const
{
	return "Texture.Debug.Circle";
}

Rect2D Collision::CircleCollider2D::extentsOfCollider() const
{
	const float circleDiameter = getCircle().diameter();
	return Rect2D( { circleDiameter,circleDiameter } );
}