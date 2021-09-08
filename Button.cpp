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
	case Button::SPRINT:
		return "Sprint";
	case Button::DEBUG_INCREASE_SPEED:
		return "Increase speed (Debug)";
	case Button::DEBUG_DECREASE_SPEED:
		return "Decrease speed (Debug)";
	case Button::DEBUG_TELEPORT_TO_00:
		return "Teleport player to 0,0 (Debug)";
	default:
		return "And you think to yourself \"how did I get here?\"? Because I have no clue how you triggered this text to display.";
	}
}