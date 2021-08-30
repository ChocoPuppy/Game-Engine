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
		Transform2D inheritedTransform = *transform();
		inheritedTransform.position = getCollider()->getWorldPosition();
		//		constexpr float ANTI_THICC_COEFFICIENT = 0.01f;
		inheritedTransform.rotation = 0;
		inheritedTransform.scale.x /= getCollider()->extentsOfCollider().getSize().x;
		inheritedTransform.scale.y /= getCollider()->extentsOfCollider().getSize().y;

		renderer->renderTexture( *transform(), *assets->getAsset<Texture>( getCollider()->getTextureID() ) );
	}

	renderer->renderTexture( *transform(), *assets->getAsset<Texture>( textureID() ) );
}