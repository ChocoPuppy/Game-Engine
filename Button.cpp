#include "Button.h"

std::string ButtonHelper::buttonToString( Button button )
{
	switch (button)
	{
	case Button::NONE:
		return "None";
	case Button::QUIT:
		return "Quit";
	case Button::UP:
		return "Up";
	case Button::DOWN:
		return "Down";
	case Button::LEFT:
		return "Left";
	case Button::RIGHT:
		return "Right";
	default:
		return "And you think to yourself \"how did I get here?\"? Because I have no clue how you triggered this text to display.";
	}
}