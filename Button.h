#pragma once
#include <string>
enum class Button
{
	QUIT,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

namespace ButtonHelper
{
	std::string buttonToString( Button button );
}