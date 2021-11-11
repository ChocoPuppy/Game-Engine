#pragma once
#include "SurfaceWrapper.h"
#include "AnimationProperties.h"
class AnimatedSurface : public Surface
{
	AnimationProperties _animationProperties;
public:
	AnimatedSurface( std::string ID, std::string path, AnimationProperties properties );

	AnimationProperties getAnimationProperties() const;
	void setAnimationProperties( AnimationProperties properties );
};