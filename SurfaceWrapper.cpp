#include "SurfaceWrapper.h"

bool Surface::isAnimation() const
{
	return getAnimationProperties();
}

OptionalAnimProperties Surface::getAnimationProperties() const
{
	return _animationProperties;
}

void Surface::setAnimationProperties( OptionalAnimProperties newProperties )
{
	_animationProperties = newProperties;
}