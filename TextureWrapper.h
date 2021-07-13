#pragma once
#include "Asset.h"
#include "Texture.h"
#include <string>
class Texture : public Asset, public SDL::Texture
{
public:
	Texture( std::string ID, std::string path, SDL::Renderer * renderer ) : Asset( ID ), SDL::Texture( path, renderer ) {}
};
