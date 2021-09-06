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
		Transform2D inheritedTransform{};
		inheritedTransform.position = getCollider()->getWorldPosition();
		//		constexpr float ANTI_THICC_COEFFICIENT = 0.01f;
		inheritedTransform.rotation = 0;
		inheritedTransform.scale = transform()->scale;
		Vector2D colliderScale{};
		Texture * colliderTexture = assets->getAsset<Texture>( getCollider()->getTextureID() );
		colliderScale.x = getCollider()->extentsOfCollider().getSize().x / 2;
		colliderScale.y = getCollider()->extentsOfCollider().getSize().y / 2;
		inheritedTransform.position.x -= colliderScale.x / 2;
		inheritedTransform.position.y -= colliderScale.y / 2;
		inheritedTransform.scale.x += colliderScale.x / colliderTexture->getSize().width();
		inheritedTransform.scale.y += colliderScale.y / colliderTexture->getSize().height();
		//		std::cout << inheritedTransform.scale.x << " " << inheritedTransform.scale.y << std::endl;

		renderer->renderTexture( inheritedTransform, *colliderTexture );
	}

	renderer->renderTexture( *transform(), *assets->getAsset<Texture>( textureID() ) );
}