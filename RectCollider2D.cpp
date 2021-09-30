#include "RectCollider2D.h"

using namespace Collision;

std::string Collision::RectCollider2D::getTextureID() const
{
	return "Texture.Debug.Rectangle";
}

Rect2D RectCollider2D::extentsOfCollider() const
{
	return getSize();
}

Collision::RectCollider2D::RectCollider2D( std::shared_ptr<Transform2D> transform, Rect2D rectangle ) : ICollider( transform )
{
	setSize( rectangle );
}

Rect2D Collision::RectCollider2D::getSize() const
{
	return _rect;
}

void Collision::RectCollider2D::setSize( Rect2D size )
{
	_rect = size;
}