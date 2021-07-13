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

void GameObject::simulatePhysics( unsigned long, AssetManager * )
{}

void GameObject::render( unsigned long, AssetManager * assets, SDL::Renderer * renderer )
{
	Texture * texture = assets->getAsset<Texture>( _textureID );
	Size textureSize = texture->getSize();
	SDL_Rect clip{};
	clip.h = textureSize.height();
	clip.w = textureSize.width();
	SDL_Rect destination{};
	destination.x = (int)transform.position.x();
	destination.y = (int)transform.position.y();
	destination.w = (int)transform.scale.x();
	destination.h = (int)transform.scale.y();

	texture->render( renderer, clip, destination );
	//	std::cout << ID() << " rendered." << std::endl;
}

void GameObject::rawMove( Vector2D toPosition )
{
	transform.position = toPosition;
}