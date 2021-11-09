#pragma once
#include "Asset.h"
#include "Texture.h"
#include <string>
class Texture : public Asset, public SDL::Texture
{
public:
	Texture( std::string ID, SDL::Surface * surface, SDL::Renderer * renderer ) : Asset( ID ), SDL::Texture( surface, renderer ) {}
};
