#include "Button.h"

std::string ButtonHelper::buttonToString( Button button )
{
	switch (button)
	{
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
		return "Wait what? how did you get a nonexistant button?";
	}
}
