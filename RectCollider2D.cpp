#include "RectCollider2D.h"

using namespace Collision;

Rect2D RectCollider2D::extentsOfCollider() const
{
	return getSize();
}

Rect2D Collision::RectCollider2D::getSize() const
{
	return _rect;
}

void Collision::RectCollider2D::setSize( Rect2D size )
{
	_rect = size;
}