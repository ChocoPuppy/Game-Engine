#include "GameObject.h"
#include "TextureWrapper.h"
GameObject::GameObject( std::string ID, std::string textureID ) : _ID( ID ), _textureID( textureID )
{}

GameObject::~GameObject()
{}

std::string GameObject::ID()
{
	return _ID;
}

void GameObject::render( unsigned long, AssetManager * assets, SDL::Renderer * renderer )
{
	SDL_Rect destination{};
	destination.x = (int)transform().position.x();
	destination.y = (int)transform().position.y();
	destination.w = (int)transform().scale.x();
	destination.h = (int)transform().scale.y();

	Texture * texture = assets->getAsset<Texture>( _textureID );
	Size textureSize = texture->getSize();

	SDL_Rect clip{};
	clip.w = textureSize.width();
	clip.h = textureSize.height();

	texture->render( renderer, clip, destination );
}