#pragma once
#include "Surface.h"
#include "Asset.h"
class Surface : public SDL::Surface, public Asset
{
public:
	Surface( std::string ID, std::string path ) : SDL::Surface( path ), Asset( ID )
	{}
};