#pragma once
#include <string>
namespace SDL
{
	constexpr int SDLGenericSuccessCode = 0;

	void passSDLError( std::string message );
};
