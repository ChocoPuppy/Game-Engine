#pragma once
#include <string>
namespace GemType
{
	enum GemType
	{
		NONE,
		RED,
		BLUE,
		GREEN,
		WHITE,
		RAINBOW,
		BOMB
	};

	std::string toTextureID( GemType type );
}