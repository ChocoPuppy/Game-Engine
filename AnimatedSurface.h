#pragma once
#include "SurfaceWrapper.h"
#include "AnimationProperties.h"
class AnimatedSurface : public Surface
{
	AnimationProperties _animationProperties;
public:
	AnimationProperties getAnimationProperties() const;
	void setAnimationProperties( AnimationProperties properties );
};