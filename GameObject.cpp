#include "GameObject.h"
#include "TextureWrapper.h"
#include "RenderEngine.h"
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
	renderer->renderTexture( *transform(), *assets->getAsset<Texture>( textureID() ) );
}