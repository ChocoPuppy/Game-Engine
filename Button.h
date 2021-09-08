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
	SPRINT
};

namespace ButtonHelper
{
	std::string buttonToString( Button button );
}