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
	case Button::LEFT_MOUSE:
		return "Left mouse";
	case Button::MIDDLE_MOUSE:
		return "Middle mouse";
	case Button::RIGHT_MOUSE:
		return "Right mouse";
	case Button::SPRINT:
		return "Sprint";
	case Button::DEBUG_INCREASE_SPEED:
		return "Increase speed (Debug)";
	case Button::DEBUG_DECREASE_SPEED:
		return "Decrease speed (Debug)";
	case Button::DEBUG_TELEPORT_TO_00:
		return "Teleport player to 0,0 (Debug)";
	case Button::SHOW_CREDITS:
		return "Show Credits";
	default:
		return "Unknown button.";
	}
}

std::set<Button> const ButtonHelper::mouseButtons()
{
	std::set<Button> const mouseButtons = std::set<Button>
	{
		Button::LEFT_MOUSE,
		Button::MIDDLE_MOUSE,
		Button::RIGHT_MOUSE
	};
	return mouseButtons;
}