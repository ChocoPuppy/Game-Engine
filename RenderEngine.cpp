#include "RenderEngine.h"
#include "Transform2D.h"
#include "Texture.h"
#include "TextureWrapper.h"

Vector2D RenderEngine::_getCameraClip() const
{
	return _cameraClip;
}

RenderEngine::RenderEngine( SDL::Window * window ) : SDL::Renderer( window ), _window( *window ) {}

SDL::Window const & RenderEngine::getWindow() const noexcept
{
	return _window;
}

void RenderEngine::renderTexture( Transform2D const & transform, Texture const & texture, SDL_RendererFlip flip ) const
{
	SDL_Rect destination{};

	destination.x = (int)( transform.position.x );
	destination.y = (int)( transform.position.y );
	destination.w = (int)( transform.scale.x );
	destination.h = (int)( transform.scale.y );

	SDL_Rect clip{};
	{
		Size textureSize = texture.getSize();

		clip.w = textureSize.width();
		clip.h = textureSize.height();
	}
	texture.render( const_cast<SDL::Renderer *>( static_cast<SDL::Renderer const *>( this ) ), clip, destination, flip );
}

Vector2D RenderEngine::worldPosToScreenPos( Vector2D worldPos ) const
{
	Vector2D screenPos{};
	screenPos.x = worldPos.x / _getCameraClip().x;
	screenPos.y = worldPos.y / _getCameraClip().y;
	return screenPos;
}

Coordinates RenderEngine::worldPosToPixelPos( Vector2D worldPos ) const
{
	return { (int)worldPos.x,(int)worldPos.y };
}

Vector2D RenderEngine::screenPosToWorldPos( Vector2D screenPos ) const
{
	Vector2D worldPos{};
	worldPos.x = screenPos.x * _getCameraClip().x;
	worldPos.y = screenPos.y * _getCameraClip().y;
	return worldPos;
}