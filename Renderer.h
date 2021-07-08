#pragma once
#include "Window.h"
#include "Color.h"
namespace SDL
{
	class Renderer
	{
		friend class Texture;
	private:
		SDL_Renderer * _renderer;

		SDL_Renderer * _getRenderer();
	public:
		Renderer( Window * window );
		~Renderer();

		void setDrawColor( Color color );
		void clear();
		void present();
	};
}
