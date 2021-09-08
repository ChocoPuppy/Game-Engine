#include "RenderEngine.h"
#include "Transform2D.h"
#include "Texture.h"
#include "TextureWrapper.h"
#include <iostream>

RenderEngine::RenderEngine( SDL::Window * window ) : SDL::Renderer( window ) {}

void RenderEngine::renderTexture( Transform2D const & transform, Texture const & texture, SDL_RendererFlip flip ) const
{
	Size textureSize = texture.getSize();
	SDL_Rect clip{};

	clip.w = textureSize.width();
	clip.h = textureSize.height();

	SDL_Rect destination{};

	Vector2D centerPos = transform.position;
	//	Vector2D topLeftCornerPos{};
		//	Vector2D screenPos = worldPosToScreenPos( centerPos );
		//	std::cout << screenPos.x << " " << screenPos.y << std::endl;
	//	topLeftCornerPos.x = centerPos.x - textureSize.width();
	//	topLeftCornerPos.y = centerPos.y - textureSize.height();

	destination.x = (int)std::round( centerPos.x );
	destination.y = (int)std::round( centerPos.y );
	destination.w = (int)std::round( transform.scale.x );
	destination.h = (int)std::round( transform.scale.y );

	texture.render( const_cast<SDL::Renderer *>( static_cast<SDL::Renderer const *>( this ) ), clip, destination, transform.rotation, flip );
}