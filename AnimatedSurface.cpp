#include "AnimatedSurface.h"

AnimatedSurface::AnimatedSurface( std::string ID, std::string path, AnimationProperties properties ) : Surface( ID, path ), _animationProperties( properties )
{}

AnimationProperties AnimatedSurface::getAnimationProperties() const
{
	return _animationProperties;
}

void AnimatedSurface::setAnimationProperties( AnimationProperties properties )
{
	_animationProperties = properties;
}