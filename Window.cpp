#include "Window.h"

#include "SDLError.h"
SDL::WindowBuilder::WindowBuilder()
{
	reset();
}
void SDL::WindowBuilder::setPosition( Coordinates coords )
{
	_window->setPosition( coords );
}

void SDL::WindowBuilder::setSize( Size size )
{
	_window->setSize( size );
}

void SDL::WindowBuilder::setIsFullscreen( bool state )
{
	_window->setIsFullscreen( state );
}

void SDL::WindowBuilder::setIsDesktopFullscreen( bool state )
{
	_window->setIsDesktopFullscreen( state );
}

void SDL::WindowBuilder::setIsBorderless( bool state )
{
	_window->setIsBorderless( state );
}

void SDL::WindowBuilder::setIsResizable( bool state )
{
	_window->setIsResizable( state );
}

void SDL::WindowBuilder::setHighDPI( bool )
{}

void SDL::WindowBuilder::setTitle( const std::string & title )
{
	_window->setTitle( title );
}

void SDL::WindowBuilder::reset()
{
	_window = std::unique_ptr<Window>( new Window() );
	//	_window->hide();
}

SDL::Window * SDL::WindowBuilder::getWindow()
{
	SDL::Window * result = _window.release();
	if (result->getWindow() == nullptr)
	{
		SDL::passSDLError( "Failed to create SDL window" );
	}
	reset();
	//	_window->show();
	return result;
}

SDL::Window::Window()
{
	_window = SDL_CreateWindow( NULL, 0, 0, 0, 0, 0 );
	if (_window == NULL) { passSDLError( "Failed to create window" ); }
}

SDL::Window::~Window()
{
	SDL_DestroyWindow( getWindow() );
}

SDL_Window * SDL::Window::getWindow()
{
	return _window;
}

Uint32 SDL::Window::getFlags()
{
	const Uint32 flags = SDL_GetWindowFlags( getWindow() );
	return flags;
}

SDL_bool SDL::Window::convertBool( bool input )
{
	return ( input ) ? SDL_TRUE : SDL_FALSE;
}

void SDL::Window::setPosition( Coordinates coords )
{
	SDL_SetWindowPosition( getWindow(), coords.x(), coords.y() );
}

void SDL::Window::setSize( Size size )
{
	SDL_SetWindowSize( getWindow(), size.height(), size.width() );
}

void SDL::Window::setIsFullscreen( bool state )
{
	int result = SDL_SetWindowFullscreen( getWindow(), ( state ) ? SDL_WINDOW_FULLSCREEN : 0 );
	if (result != SDLGenericSuccessCode) { passSDLError( "Failed to make window fullscreen." ); }
}

void SDL::Window::setIsDesktopFullscreen( bool state )
{
	int result = SDL_SetWindowFullscreen( getWindow(), ( state ) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );
	if (result != SDLGenericSuccessCode) { passSDLError( "Failed to make window desktop fullscreen." ); }
}

void SDL::Window::setIsBorderless( bool state )
{
	SDL_SetWindowBordered( getWindow(), convertBool( state ) );
}

void SDL::Window::setIsResizable( bool state )
{
	SDL_SetWindowResizable( getWindow(), convertBool( state ) );
}

void SDL::Window::setTitle( const std::string & title )
{
	SDL_SetWindowTitle( getWindow(), title.c_str() );
}

void SDL::Window::minimize()
{
	SDL_MinimizeWindow( getWindow() );
}

void SDL::Window::maximize()
{
	SDL_MaximizeWindow( getWindow() );
}

void SDL::Window::hide()
{
	SDL_HideWindow( getWindow() );
}

void SDL::Window::show()
{
	SDL_ShowWindow( getWindow() );
}

void SDL::Window::restore()
{
	SDL_RestoreWindow( getWindow() );
}

Coordinates SDL::Window::getPosition()
{
	Coordinates coords;
	SDL_GetWindowPosition( getWindow(), &coords.x(), &coords.y() );
	return coords;
}

Size SDL::Window::getSize()
{
	Size size;
	SDL_GetWindowSize( getWindow(), &size.width(), &size.height() );
	return size;
}

bool SDL::Window::getIsFullscreen()
{
	return ( getFlags() & SDL_WINDOW_FULLSCREEN ) > 0;
}

bool SDL::Window::getIsDesktopFullscreen()
{
	return getFlags() & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

bool SDL::Window::getIsBorderless()
{
	return getFlags() & SDL_WINDOW_BORDERLESS;
}

bool SDL::Window::getIsResizable()
{
	return getFlags() & SDL_WINDOW_RESIZABLE;
}

bool SDL::Window::getIsMinimised()
{
	return getFlags() & SDL_WINDOW_MINIMIZED;
}

bool SDL::Window::getIsMaximised()
{
	return getFlags() & SDL_WINDOW_MAXIMIZED;
}