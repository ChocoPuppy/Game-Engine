#include "SDLError.h"

#include <iostream>
#include "SDL.h"
using namespace SDL;

using std::cout;
using std::cerr;
using std::endl;

void SDL::passSDLError( std::string message )
{
	cout << message << endl;
	cerr << "SDL Error: " << SDL_GetError() << endl;
	exit( 1 );
}