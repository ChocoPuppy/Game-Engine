#pragma once
#include "SDLVideo.h"
#include "Window.h"
#include "Color.h"
namespace SDL
{
	class Renderer
	{
		friend class Texture;
	private:
		mutable SDL_Renderer * _renderer;

		//Since SDL functions require non-const passing for functions that don't need it, I've either gotta add a bunch of boiler plate to all of the const code here, or just return the non-const value as I just did. Keep in mind you can violate constness with this function if not careful!
		SDL_Renderer * _getRenderer() const;
	public:
		Renderer( Window * window );
		~Renderer();

		Size getResolution() const;

		void setDrawColor( Color color );

		void clear();
		void present();
	};
}
