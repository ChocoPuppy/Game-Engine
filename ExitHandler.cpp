#include "ExitHandler.h"
#include "InputManager.h"
void ExitHandler::update( InputManager * input )
{
	if (input->isButtonPressed( Button::QUIT ))
	{
		exit( 0 );
	}
}