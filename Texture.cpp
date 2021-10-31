#include "Texture.h"

#include <SDL_image.h>
#include <iostream>

#include "SDLError.h"
#include "UnConstGetter.h"
#include "Surface.h"
using namespace SDL;

Texture::Texture( Surface * parent, Renderer * renderer )
{
	_data = SDL_CreateTextureFromSurface( renderer->_getRenderer(), parent->_getData() );
	if (_data == NULL)
	{
		SDL::passSDLError( "Failed to convert surface to texture." );
	}
}

Texture::~Texture()
{
	SDL_DestroyTexture( _data );
}

SDL_Texture const * SDL::Texture::_getData() const
{
	return _data;
}

SDL_Texture * Texture::_getData()
{
	return _data;
}

void Texture::render( Renderer * render, SDL_Rect clip, SDL_Rect destination, double rotation, SDL_RendererFlip flip ) const
{
	const int renderResult = SDL_RenderCopyEx( render->_getRenderer(), const_cast<SDL_Texture *>( _getData() ), &clip, &destination, rotation, NULL, flip );
	if (renderResult != SDL::SDLGenericSuccessCode)
	{
		SDL::passSDLError( "Failed to render texture" );
	}
}

Size SDL::Texture::getSize() const
{
	Size size = Size();
	//usually you shouldn't do this. But I know SDL_QueryTexture doesn't actually alter any data so I feel safe casting away the const this time.
	SDL_Texture * nonConstData = const_cast<SDL_Texture *>( _getData() );
	SDL_QueryTexture( nonConstData, nullptr, nullptr, &size.width(), &size.height() );
	return size;
}