#pragma once
#include <string>
enum class Button
{
	NONE,
	QUIT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPRINT,
	DEBUG_INCREASE_SPEED,
	DEBUG_DECREASE_SPEED,
	DEBUG_TELEPORT_TO_00,
	SHOW_CREDITS
};

namespace ButtonHelper
{
	std::string buttonToString( Button button );
}