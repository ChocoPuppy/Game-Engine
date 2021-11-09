#include "AnimatedSurface.h"

AnimationProperties AnimatedSurface::getAnimationProperties() const
{
	return _animationProperties;
}

void AnimatedSurface::setAnimationProperties( AnimationProperties properties )
{
	_animationProperties = properties;
}