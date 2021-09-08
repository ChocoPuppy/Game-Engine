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

	static constexpr float PI = 3.14159265f;
	bool faceLeft = false;
	if (velocity().magnitude() > 0)
	{
		//If the velocity is facing left, flip the image left.
		if (abs( velocity().angle() ) > ( PI / 2.f ))
		{
			faceLeft = true;
		}
	}
	SDL_RendererFlip flip = ( faceLeft ) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	renderer->renderTexture( *transform(), *assets->getAsset<Texture>( textureID() ), flip );
}