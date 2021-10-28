#pragma once
#include <string>
#include <set>
enum class Button
{
	NONE,
	QUIT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPRINT,
	LEFT_MOUSE,
	MIDDLE_MOUSE,
	RIGHT_MOUSE,
	DEBUG_INCREASE_SPEED,
	DEBUG_DECREASE_SPEED,
	DEBUG_TELEPORT_TO_00,
	SHOW_CREDITS
};

namespace ButtonHelper
{
	std::string buttonToString( Button button );
	std::set<Button> const mouseButtons();
}