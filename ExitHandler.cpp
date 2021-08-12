#include "ExitHandler.h"
#include "InputManager.h"
void ExitHandler::update( InputManager * input )
{
	if (input->isButtonReleased( Button::QUIT ))
	{
		exit( 0 );
	}
}