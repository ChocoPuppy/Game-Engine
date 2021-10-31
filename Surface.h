#pragma once
#include "SDLVideo.h"
#include <string>
#include "Size.h"
#include <memory>
namespace SDL
{
	class Texture;
	class Surface
	{
		friend Texture;
		std::unique_ptr<SDL_Surface> _data;
		SDL_Surface const * _getData() const;
		SDL_Surface * _getData();
	public:
		Surface( std::string path );
		~Surface();

		Size getSize() const;
	};
}