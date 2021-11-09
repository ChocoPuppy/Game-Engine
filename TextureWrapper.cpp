#include "TextureWrapper.h"
#include "AnimatedTexture.h"
std::shared_ptr<Surface const> Texture::getSurface() const
{
	return _surface;
}

std::unique_ptr<Texture> TextureFactory::result( std::shared_ptr<Surface> surface, SDL::Renderer * renderer )
{
	Texture * constructedTexture;
	if (surface->isAnimation())
	{
		constructedTexture = _constructTexture<Texture>( surface, renderer );
	}
	else
	{
		constructedTexture = _constructTexture<AnimatedTexture>( surface, renderer );
	}
	return std::unique_ptr<Texture>( constructedTexture );
}