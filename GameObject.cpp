#include "GameObject.h"
#include "TextureWrapper.h"
#include "RenderEngine.h"
#include "Config.h"
#include "SurfaceWrapper.h"
GameObject::GameObject( std::string ID, std::string textureID ) : _ID( ID ), _textureID( textureID )
{}

GameObject::~GameObject()
{}

std::string GameObject::ID()
{
	return _ID;
}

void GameObject::render( unsigned long, AssetManager * assets, RenderEngine * renderer )
{
	if (_getTextureID() != _getTexture()->getID())
	{
		refreshTexture( assets, renderer );
	}
	if (Config::displayColliders)
	{
		getCollider()->render( *renderer );
	}

	SDL_RendererFlip flip = ( isFacingLeft() ) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	renderer->renderTexture( *transform(), *_texture.get(), flip );
}

std::string GameObject::_getTextureID() const
{
	return _textureID;
}

void GameObject::_setTextureID( std::string ID )
{
	_textureID = ID;
}

Texture * GameObject::_getTexture()
{
	return _texture.get();
}

void GameObject::refreshTexture( AssetManager * assets, RenderEngine * renderer )
{
	_texture = std::make_unique<Texture>( _getTextureID(), assets->getAsset<Surface>( _getTextureID() ), renderer );
}