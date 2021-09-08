#include "GameObject.h"
#include "TextureWrapper.h"
#include "RenderEngine.h"
#include "Config.h"
GameObject::GameObject( std::string ID, std::string textureID ) : _ID( ID ), _textureID( textureID )
{}

GameObject::~GameObject()
{}

std::string GameObject::ID()
{
	return _ID;
}

std::string GameObject::textureID()
{
	return _textureID;
}

void GameObject::render( unsigned long, AssetManager * assets, RenderEngine * renderer )
{
	if (Config::displayColliders)
	{
		getCollider()->render( *assets, *renderer );
	}

	SDL_RendererFlip flip = ( isFacingLeft() ) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	renderer->renderTexture( *transform(), *assets->getAsset<Texture>( textureID() ), flip );
}