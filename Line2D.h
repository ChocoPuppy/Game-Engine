#pragma once
#include "IShape.h"
class Line2D : public IShape
{
	Vector2D _direction;
public:
	Line2D( Vector2D direction ) : _direction( direction ) {}

	virtual Vector2D getSupportPointOf( Vector2D point ) const noexcept override;

	Vector2D getDirection() const { return _direction; }
	void setDirection( Vector2D direction ) { _direction = direction; }
};