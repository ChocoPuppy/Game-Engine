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

	const int frameCount = getAnimationProperties().frameCount;
	const int totalTextureWidth = textureSize.width();
	const int frameMaxWidth = totalTextureWidth / frameCount;
	const int frameMaxHeight = textureSize.height();
	SDL_Rect frameClip{};
	{
		const int manualClipWidth = clip.w;
		const int clipWidth = std::min( frameMaxWidth, manualClipWidth );
		frameClip.w = clipWidth;
	}
	{
		const int manualClipHeight = clip.h;
		const int clipHeight = std::min( frameMaxHeight, manualClipHeight );
		frameClip.h = clipHeight;
	}
	{
		//		const int zeroBasedFrame = _currentFrame - 1;
		const int clipXPos = frameClip.w;
		const int frameClipXPos = _currentFrame * clipXPos;
		const int manualClipX = clip.x;
		const int frameClipXPosPlusManualClip = frameClipXPos + manualClipX;
		frameClip.x = frameClipXPosPlusManualClip;
	}
	{
		const int manualClipY = clip.y;
		frameClip.y = manualClipY;
	}

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
		auto animatedSurface = getAnimatedSurface();
		properties = animatedSurface->getAnimationProperties();
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
	auto & surface = getSurface();
	return std::dynamic_pointer_cast<AnimatedSurface const>( surface );
}