#pragma once
#include "TextureWrapper.h"
#include "SDLBase.h"
namespace
{
	using OptionalAnimProperties = std::optional<AnimationProperties>;
}
class AnimatedTexture : public Texture
{
public:
	AnimatedTexture( std::string ID, std::shared_ptr<Surface> surface, SDL::Renderer * renderer, int frameCount, unsigned long frameDurationMilliseconds );
	~AnimatedTexture();

	void updateFrame( unsigned long millisecondsToSimulate );
	virtual void render( SDL::Renderer * renderer, SDL_Rect clip, SDL_Rect  destination, double rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE ) const override;

	AnimationProperties getAnimationProperties();
	void overrideAnimProperties( OptionalAnimProperties properties );
	void clearAnimationPropertiesOverride();
private:
	OptionalAnimProperties _animationPropertiesOverride;
	unsigned long _totalTimeMilliseconds = 0;
	int _currentFrame = 0;
};
