#pragma once
#include "TextureWrapper.h"
#include "Size.h"
class AnimatedTexture : public Texture
{
public:
	AnimatedTexture( std::string ID, std::string path, SDL::Renderer * renderer, int frameCount, unsigned long frameDurationMilliseconds );
	~AnimatedTexture();

	void updateFrame( unsigned long millisecondsToSimulate );
	virtual void render( SDL::Renderer * renderer, SDL_Rect clip, SDL_Rect  destination, double rotation = 0 ) const override;
private:
	int _frameCount;
	unsigned long _frameDurationMilliseconds;
	unsigned long _totalTimeMilliseconds = 0;
	int _currentFrame = 0;
};
