#include "Surface.h"
#include "SDLError.h"
#include <SDL_image.h>
SDL_Surface const * SDL::Surface::_getData() const
{
	return _data.get();
}
SDL_Surface * SDL::Surface::_getData()
{
	return _data.get();
}
SDL::Surface::Surface( std::string path )
{
	if (path.find( ".bmp" ) != std::string::npos)
	{
		_data = std::unique_ptr<SDL_Surface>( SDL_LoadBMP( path.c_str() ) );
	}
	else if (path.find( ".png" ) != std::string::npos)
	{
		_data = std::unique_ptr<SDL_Surface>( IMG_Load( path.c_str() ) );
	}
	else
	{
		SDL::passSDLError( "Unknown image format. Path: " + path );
	}
	if (_data == NULL)
	{
		SDL::passSDLError( "Failed to load image. Path: " + path );
	}
}

SDL::Surface::~Surface()
{
	SDL_FreeSurface( _data.get() );
}

Size SDL::Surface::getSize() const
{
	Size textureSize{};
	textureSize.width() = _getData()->w;
	textureSize.height() = _getData()->h;
	return textureSize;
}