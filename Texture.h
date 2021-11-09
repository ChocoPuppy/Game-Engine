#pragma once
#include "SDLVideo.h"
#include "Renderer.h"

namespace SDL
{
	class Surface;
	class Texture
	{
		SDL_Texture * _data;
		SDL_Texture const * _getData() const;
		SDL_Texture * _getData();
	public:
		Texture( SDL::Surface * parent, Renderer * renderer );
		virtual ~Texture();

		virtual void render( Renderer * renderer, SDL_Rect clip, SDL_Rect destination, double rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE ) const;

		Size getSize() const;
	};
}