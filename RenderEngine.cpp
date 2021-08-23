#include "RenderEngine.h"
#include "Transform2D.h"
#include "Texture.h"
#include "TextureWrapper.h"

RenderEngine::RenderEngine( SDL::Window * window ) : SDL::Renderer( window ) {}

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
	texture.render( const_cast<SDL::Renderer *>( static_cast<SDL::Renderer const *>( this ) ), clip, destination, transform.rotation );
}