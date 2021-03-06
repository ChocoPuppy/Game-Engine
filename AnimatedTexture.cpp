#include "AnimatedTexture.h"
#include "SDLError.h"
AnimatedTexture::AnimatedTexture( std::string ID, std::string path, SDL::Renderer * renderer, int frameCount, unsigned long frameDurationMilliseconds ) : Texture( ID, path, renderer ), _frameCount( frameCount ), _frameDurationMilliseconds( frameDurationMilliseconds )
{}

AnimatedTexture::~AnimatedTexture()
{}

void AnimatedTexture::updateFrame( unsigned long millisecondsToSimulate )
{
	_totalTimeMilliseconds += millisecondsToSimulate;
	_currentFrame = ( _totalTimeMilliseconds / _frameDurationMilliseconds ) % _frameCount;
}

void AnimatedTexture::render( SDL::Renderer * renderer, SDL_Rect, SDL_Rect destination, double rotation, SDL_RendererFlip flip ) const
{
	Size textureSize = getSize();
	const int frameWidth = textureSize.width() / _frameCount;
	SDL_Rect frameClip{};
	frameClip.w = frameWidth;
	frameClip.h = textureSize.height();
	frameClip.x = _currentFrame * frameWidth;
	frameClip.y = 0;

	Texture::render( renderer, frameClip, destination, rotation, flip );
}