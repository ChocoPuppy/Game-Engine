#pragma once
#include "Surface.h"
#include "Asset.h"
class Surface : public SDL::Surface, public Asset
{
	Surface( std::string ID, std::string path ) : Asset( ID ), SDL::Surface( path )
	{}
};