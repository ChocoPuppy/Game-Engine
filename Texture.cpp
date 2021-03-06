#include "Texture.h"

#include <SDL_image.h>
#include <iostream>

#include "SDLError.h"
#include "UnConstGetter.h"
using namespace SDL;

Texture::Texture( std::string path, Renderer * renderer )
{
	SDL_Surface * textureSurface = nullptr;
	if (path.find( ".bmp" ) != std::string::npos)
	{
		textureSurface = SDL_LoadBMP( path.c_str() );
	}
	else if (path.find( ".png" ) != std::string::npos)
	{
		textureSurface = IMG_Load( path.c_str() );
	}
	else
	{
		SDL::passSDLError( "Unknown image format. Path: " + path );
	}
	if (textureSurface == NULL)
	{
		SDL::passSDLError( "Failed to load image. Path: " + path );
	}
	_data = SDL_CreateTextureFromSurface( renderer->_getRenderer(), textureSurface );
	if (_data == NULL)
	{
		SDL::passSDLError( "Failed to convert image to texture. Path: " + path );
	}
	SDL_FreeSurface( textureSurface );
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