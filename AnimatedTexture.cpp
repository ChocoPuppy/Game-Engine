#include "AnimatedTexture.h"
#include "SDLError.h"
AnimatedTexture::AnimatedTexture( std::string ID, SDL::Surface * surface, SDL::Renderer * renderer, int frameCount, unsigned long frameDurationMilliseconds ) : Texture( ID, surface, renderer ), _frameCount( frameCount ), _frameDurationMilliseconds( frameDurationMilliseconds )
{}

AnimatedTexture::~AnimatedTexture()
{}

void AnimatedTexture::updateFrame( unsigned long millisecondsToSimulate )
{
	_totalTimeMilliseconds += millisecondsToSimulate;
	_currentFrame = ( _totalTimeMilliseconds / _frameDurationMilliseconds ) % _frameCount;
}

void AnimatedTexture::render( SDL::Renderer * renderer, SDL_Rect clip, SDL_Rect destination, double rotation, SDL_RendererFlip flip ) const
{
	Size textureSize = getSize();
	const int frameWidth = textureSize.width() / _frameCount;
	SDL_Rect frameClip{};
	frameClip.w = std::max( frameWidth, clip.w );
	frameClip.h = std::max( textureSize.height(), clip.h );
	frameClip.x = ( _currentFrame - 1 ) * frameWidth + clip.x;
	frameClip.y = clip.y;

	Texture::render( renderer, frameClip, destination, rotation, flip );
}