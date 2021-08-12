#pragma once
#include "SDLBase.h"

//Initialize the video subsystem at startup if included and quit it at program end (object destruction)
namespace
{
	struct _SDLVideo
	{
		_SDLVideo()
		{
			SDL_InitSubSystem( SDL_INIT_VIDEO );
		}

		~_SDLVideo()
		{
			SDL_QuitSubSystem( SDL_INIT_VIDEO );
		}
	};

	_SDLVideo _sdlVideo = _SDLVideo();
}

namespace SDL
{
	class Texture;
	class Window;
	class WindowBuilder;
	class Renderer;
}