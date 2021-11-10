#include "AnimatedTexture.h"
#include "SDLError.h"
AnimatedTexture::AnimatedTexture( std::shared_ptr<Surface> const & surface, SDL::Renderer * renderer ) : Texture( surface, renderer )
{}

AnimatedTexture::~AnimatedTexture()
{}

void AnimatedTexture::updateFrame( unsigned long millisecondsToSimulate )
{
	_totalTimeMilliseconds += millisecondsToSimulate;
	_currentFrame = ( _totalTimeMilliseconds / getAnimationProperties().frameDurationMilliseconds ) % getAnimationProperties().frameCount;
}

void AnimatedTexture::render( SDL::Renderer * renderer, SDL_Rect clip, SDL_Rect destination, double rotation, SDL_RendererFlip flip ) const
{
	Size textureSize = getSize();
	const int frameWidth = textureSize.width() / getAnimationProperties().frameCount;
	SDL_Rect frameClip{};
	frameClip.w = std::max( frameWidth, clip.w );
	frameClip.h = std::max( textureSize.height(), clip.h );
	frameClip.x = ( _currentFrame - 1 ) * frameWidth + clip.x;
	frameClip.y = clip.y;

	Texture::render( renderer, frameClip, destination, rotation, flip );
}

AnimationProperties AnimatedTexture::getAnimationProperties() const
{
	AnimationProperties properties;
	if (_animationPropertiesOverride.has_value())
	{
		properties = _animationPropertiesOverride.value();
	}
	else
	{
		properties = getAnimatedSurface()->getAnimationProperties();
	}
	return properties;
}

void AnimatedTexture::overrideAnimProperties( OptionalAnimProperties properties )
{
	_animationPropertiesOverride = properties;
}

void AnimatedTexture::clearAnimationPropertiesOverride()
{
	overrideAnimProperties( std::nullopt );
}

std::shared_ptr<AnimatedSurface const> AnimatedTexture::getAnimatedSurface() const
{
	return std::dynamic_pointer_cast<AnimatedSurface const>( getSurface() );
}