#pragma once
#include "Texture.h"
#include "SurfaceWrapper.h"
#include <string>

class Texture : public SDL::Texture
{
	friend class TextureFactory;
	std::shared_ptr<Surface const> _surface;

protected:

	Texture( std::shared_ptr<Surface> const & surface, SDL::Renderer * renderer );
public:
	std::shared_ptr<Surface const> const & getSurface() const;
};

class TextureFactory
{
	template<class TextureType>
	Texture * _constructTexture( std::shared_ptr<Surface> const & surface, SDL::Renderer * renderer )
	{
		return new TextureType( surface, renderer );
	}
public:
	std::unique_ptr<Texture> result( std::shared_ptr<Surface> const & surface, SDL::Renderer * renderer );
};
