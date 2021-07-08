#pragma once
#include "SDLBase.h"
#include "Renderer.h"
namespace SDL
{
	class Texture
	{
		SDL_Texture * _data;
		SDL_Texture const * _getData() const;
		SDL_Texture * _getData();
	public:
		Texture( std::string path, Renderer * renderer );
		~Texture();

		virtual void render( Renderer * renderer, SDL_Rect clip, SDL_Rect destination );

		Size getSize() const;
	};
}