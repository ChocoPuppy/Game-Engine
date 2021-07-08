#include "ExitHandler.h"

void ExitHandler::update( InputManager *, const Button button )
{
	switch (button)
	{
	case Button::QUIT:
		exit( 0 );
		break;
	default:
		return;
	}
}