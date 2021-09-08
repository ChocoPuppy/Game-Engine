#if __GNUC__
#pragma clang system_header
#endif
#pragma once
#define SDL_MAIN_HANDLED

#include <SDL.h>

namespace
{
	//Initializes the SDL system at startup if included and quits it at the end.
	struct _SDL
	{
		_SDL()
		{
			SDL_SetMainReady();
		}

		~_SDL()
		{
			SDL_Quit();
		}
	};

	_SDL _sdl = _SDL();
}