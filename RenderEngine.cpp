#include "RenderEngine.h"
#include "Transform2D.h"
#include "Texture.h"
#include <cmath>

Vector2D RenderEngine::_getCameraClip() const
{
	return _cameraClip;
}

RenderEngine::RenderEngine( SDL::Window * window ) : SDL::Renderer( window ), _window( *window ) {}

SDL::Window const & RenderEngine::getWindow() const noexcept
{
	return _window;
}

void RenderEngine::renderTexture( Transform2D const & transform, SDL::Texture const & texture, SDL_RendererFlip flip )
{
	SDL_Rect destination{};
	{
		Coordinates pixelPos = worldPosToPixelPos( transform.position );
		destination.x = pixelPos.x;
		destination.y = pixelPos.y;

		Coordinates pixelScale = worldPosToPixelPos( transform.scale );
		destination.w = pixelScale.x;
		destination.h = pixelScale.y;
	}

	SDL_Rect clip{};
	{
		Size textureSize = texture.getSize();

		clip.w = textureSize.width();
		clip.h = textureSize.height();
	}
	texture.render( this, clip, destination, flip );
}

Vector2D RenderEngine::worldPosToScreenPos( Vector2D worldPos ) const
{
	Vector2D screenPos{};
	screenPos.x = worldPos.x / _getCameraClip().x;
	screenPos.y = worldPos.y / _getCameraClip().y;
	return screenPos;
}

Vector2D RenderEngine::worldPosToSubPixelPos( Vector2D worldPos ) const
{
	//At the moment this conversion does nothing as world positions are equivalent to subPixel positions, however if I change it to become different, this should become the body of this function
	/*
	Vector2D const screenPos = worldPosToScreenPos( worldPos );
	Vector2D const subPixelPos = screenPosToSubPixelPos( screenPos );
	return subPixelPos;
	*/

	return worldPos;
}

Coordinates RenderEngine::worldPosToPixelPos( Vector2D worldPos ) const
{
	Vector2D const subPixelPos = worldPosToSubPixelPos( worldPos );
	Coordinates const pixelPos{ subPixelPos };
	return pixelPos;
}

Vector2D RenderEngine::screenPosToSubPixelPos( Vector2D screenPos ) const
{
	Vector2D subPixelPos{};
	subPixelPos.x = _getCameraClip().x * screenPos.x;
	subPixelPos.y = _getCameraClip().y * screenPos.y;
	return subPixelPos;
}

Vector2D RenderEngine::screenPosToWorldPos( Vector2D screenPos ) const
{
	Vector2D worldPos{};
	worldPos.x = _getCameraClip().x * screenPos.x;
	worldPos.y = _getCameraClip().y * screenPos.y;
	return worldPos;
}