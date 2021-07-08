#pragma once
#include "Asset.h"
#include "Texture.h"
#include <string>
class Texture : public Asset, public SDL::Texture
{
public:
	Texture( std::string path, SDL::Renderer * renderer ) : SDL::Texture( path, renderer ) {}
};
