#pragma once
#include "SDLBase.h"
#include "Renderer.h"
namespace SDL
{
	class Texture
	{
		SDL_Texture * _data;
	protected:
		SDL_Texture const * getData() const;
		SDL_Texture * getData();
	public:
		Texture( std::string path, Renderer * renderer );
		~Texture();

		virtual void render( Renderer * renderer, SDL_Rect clip, SDL_Rect destination );

		Size getSize() const;
	};
}