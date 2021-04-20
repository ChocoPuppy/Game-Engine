#include "SDLMain.h"
#include "SDLBase.h"

unsigned long SDL::getTicks()
{
	return SDL_GetTicks();
}