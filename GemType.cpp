#include "GemType.h"

std::string GemType::toString( GemType type )
{
	switch (type)
	{
	case NONE:
		return "None";
	case RED:
		return "Red";
	case BLUE:
		return "Blue";
	case GREEN:
		return "Green";
	case WHITE:
		return "White";
	case RAINBOW:
		return "Rainbow";
	case BOMB:
		return "Bomb";
	default:
		return "Unknown";
	}
}

std::string GemType::toTextureID( GemType type )
{
	static const std::string TEXTURE_PATH_CONSTANT = "Textures.Gem.";
	return TEXTURE_PATH_CONSTANT + toString( type );
}