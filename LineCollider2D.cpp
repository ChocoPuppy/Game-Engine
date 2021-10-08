#include "LineCollider2D.h"

Collision::LineCollider2D::LineCollider2D( Line2D line, bool isRay, std::shared_ptr<Transform2D const> attatchedTo ) : ICollider( attatchedTo ), _isRay( isRay )
{
	setShape( line );
}

Line2D Collision::LineCollider2D::getLine() const
{
	return getShape<Line2D>();
}

bool Collision::LineCollider2D::isRay() const
{
	return _isRay;
}

void Collision::LineCollider2D::setLine( Line2D line )
{
	setShape( line );
}

void Collision::LineCollider2D::setIsRay( bool isRay )
{
	_isRay = isRay;
}

std::string Collision::LineCollider2D::getTextureID() const
{
	return "Debug.Collider.Line";
}

Rect2D Collision::LineCollider2D::extentsOfCollider() const
{
	Vector2D const lineDirection = getLine().getDirection();
	Vector2D LineLengthFromCenter{};
	LineLengthFromCenter.x = lineDirection.x / 2;
	LineLengthFromCenter.y = lineDirection.y / 2;
	return Rect2D( LineLengthFromCenter );
}