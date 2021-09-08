#include "RenderEngine.h"
#include "Transform2D.h"
#include "Texture.h"
#include "TextureWrapper.h"

RenderEngine::RenderEngine( SDL::Window * window ) : SDL::Renderer( window ), _window( *window ) {}

SDL::Window const & RenderEngine::getWindow() const noexcept
{
	return _window;
}

Vector2D RenderEngine::worldPosToScreenPos( Vector2D worldPos ) const
{
	//	static constexpr Vector2D anchorOfWorldPos = { 0.5,0.5 };
	Vector2D screenPos{};
	Size resolution = getWindow().getSize();
	screenPos.x = worldPos.x / resolution.width();
	screenPos.y = worldPos.y / resolution.height();
	return screenPos;
}

Vector2D RenderEngine::worldPosToSubPixelPos( Vector2D worldPos ) const
{
	return worldPos;
}

Coordinates RenderEngine::worldPosToPixelPos( Vector2D worldPos ) const
{
	Vector2D const subPixelPos = worldPosToSubPixelPos( worldPos );
	Coordinates const pixelPos = { (int)std::round( subPixelPos.x ),(int)std::round( subPixelPos.y ) };
	return pixelPos;
}

Vector2D RenderEngine::screenPosToSubPixelPos( Vector2D screenPos ) const
{
	Vector2D subPixelPos{};
	//	Size screenSize = getWindow().getSize();
	Size resolution = getResolution();
	subPixelPos.x = screenPos.x * resolution.width();
	subPixelPos.y = screenPos.y * resolution.height();
	return subPixelPos;
}

Vector2D RenderEngine::screenPosToWorldPos( Vector2D screenPos ) const
{
	Vector2D worldPos{};
	Size screenSize = getWindow().getSize();
	worldPos.x = screenPos.x * screenSize.width();
	worldPos.y = screenPos.y * screenSize.height();
	return screenPos;
}

void RenderEngine::renderTexture( Transform2D const & transform, Texture const & texture ) const
{
	SDL_Rect destination{};

	destination.x = (int)transform.position.x();
	destination.y = (int)transform.position.y();
	destination.w = (int)transform.scale.x();
	destination.h = (int)transform.scale.y();

	SDL_Rect clip{};
	{
		Size textureSize = texture.getSize();

		clip.w = textureSize.width();
		clip.h = textureSize.height();
	}
	texture.render( const_cast<SDL::Renderer *>( static_cast<SDL::Renderer const *>( this ) ), clip, destination );
}