#pragma once
#include "TextureWrapper.h"
#include <optional>
#include "AnimatedSurface.h"
namespace
{
	using OptionalAnimProperties = std::optional<AnimationProperties>;
}
class AnimatedTexture : public Texture
{
public:
	AnimatedTexture( std::shared_ptr<Surface> const & surface, SDL::Renderer * renderer );
	~AnimatedTexture();

	void updateFrame( unsigned long millisecondsToSimulate );
	virtual void render( SDL::Renderer * renderer, SDL_Rect clip, SDL_Rect  destination, double rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE ) const override;

	std::shared_ptr<AnimatedSurface const> getAnimatedSurface() const;
	AnimationProperties getAnimationProperties() const;
	void overrideAnimProperties( OptionalAnimProperties properties );
	void clearAnimationPropertiesOverride();
private:
	OptionalAnimProperties _animationPropertiesOverride;
	unsigned long _totalTimeMilliseconds = 0;
	int _currentFrame = 0;
};
