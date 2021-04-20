#include "ExitHandler.h"

void ExitHandler::update( InputManager *, const Button button )
{
	//If it's not the button we're looking for, exit immediatly.
	if (button != Button::QUIT) return;
	exit( 0 );
}