#include "TextureWrapper.h"
#include "AnimatedTexture.h"
Texture::Texture( std::shared_ptr<Surface> const & surface, SDL::Renderer * renderer ) : SDL::Texture( surface.get(), renderer ), _surface( surface ) {}

std::shared_ptr<Surface const> const & Texture::getSurface() const
{
	return _surface;
}

std::unique_ptr<Texture> TextureFactory::result( std::shared_ptr<Surface> const & surface, SDL::Renderer * renderer )
{
	Texture * constructedTexture;
	AnimatedSurface * animatedSurface = dynamic_cast<AnimatedSurface *>( surface.get() );
	if (animatedSurface == nullptr)
	{
		constructedTexture = _constructTexture<Texture>( surface, renderer );
	}
	else
	{
		constructedTexture = _constructTexture<AnimatedTexture>( surface, renderer );
	}
	return std::unique_ptr<Texture>( constructedTexture );
}