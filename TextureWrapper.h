#pragma once
#include "Texture.h"
#include "SurfaceWrapper.h"
#include <string>

class Texture : public SDL::Texture
{
	friend class TextureFactory;
	std::shared_ptr<Surface const> _surface;

protected:

	Texture( std::shared_ptr<Surface> surface, SDL::Renderer * renderer ) : SDL::Texture( surface.get(), renderer ), _surface( surface ) {}
public:
	std::shared_ptr<Surface const> getSurface() const;
};

class TextureFactory
{
	template<class TextureType>
	Texture * _constructTexture( std::shared_ptr<Surface> surface, SDL::Renderer * renderer )
	{
		return new TextureType( surface, renderer );
	}
public:
	std::unique_ptr<Texture> result( std::shared_ptr<Surface> surface, SDL::Renderer * renderer );
};
