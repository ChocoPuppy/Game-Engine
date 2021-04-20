#include "Renderer.h"
#include "SDLError.h"
SDL_Renderer * SDL::Renderer::getRenderer()
{
	return _renderer;
}

SDL::Renderer::Renderer( Window * window )
{
	_renderer = SDL_CreateRenderer( window->getWindow(), -1, 0 );
	if (_renderer == nullptr)
	{
		SDL::passSDLError( "Failed to create SDL renderer" );
	}
}

SDL::Renderer::~Renderer()
{
	SDL_DestroyRenderer( getRenderer() );
}

void SDL::Renderer::setDrawColor( Color color )
{
	int rendererDrawResult = SDL_SetRenderDrawColor( getRenderer(), (Uint8)color.red(), (Uint8)color.green(), (Uint8)color.blue(), (Uint8)color.alpha() );
	if (rendererDrawResult != SDL::SDLGenericSuccessCode) SDL::passSDLError( "Failed to set the base color of the renderer" );
}

void SDL::Renderer::clear()
{
	const int rendererClearResult = SDL_RenderClear( getRenderer() );
	if (rendererClearResult != SDL::SDLGenericSuccessCode) SDL::passSDLError( "Failed to clear renderer" );
}

void SDL::Renderer::present()
{
	SDL_RenderPresent( getRenderer() );
}