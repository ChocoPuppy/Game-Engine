#include "GameObject.h"
#include "TextureWrapper.h"
#include "RenderEngine.h"
#include "Config.h"
#include "SurfaceWrapper.h"
GameObject::GameObject( std::string ID, std::string textureID, AssetManager * manager, RenderEngine * renderer ) : _ID( ID )
{
	_texture = std::make_unique<SDL::Texture>( manager->getAsset<Surface>( textureID ), renderer );
}

GameObject::~GameObject()
{}

std::string GameObject::ID()
{
	return _ID;
}

void GameObject::render( unsigned long, RenderEngine * renderer )
{
	if (Config::displayColliders)
	{
		getCollider()->render( *renderer );
	}

	SDL_RendererFlip flip = ( isFacingLeft() ) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	renderer->renderTexture( *transform(), *_texture.get(), flip );
}