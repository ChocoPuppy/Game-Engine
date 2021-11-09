#include "ICollider.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "TextureWrapper.h"
#include "Transform2D.h"
#include "Size.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"

using namespace Collision;

ICollider::ICollider( std::shared_ptr<Transform2D const> attatchedTo ) : _census( this ), _attatchedToTransform( attatchedTo )
{}

ICollider::~ICollider()
{}

void ICollider::render( AssetManager & assets, RenderEngine & renderer )
{
	Transform2D inheritedTransform{};
	inheritedTransform.position = getWorldPosition();
	//		constexpr float ANTI_THICC_COEFFICIENT = 0.01f;
	inheritedTransform.rotation = 0;
	inheritedTransform.scale = attatchedToTransform()->scale;
	Vector2D colliderScale{};
	colliderScale.x = extentsOfCollider().getSize().x / 2;
	colliderScale.y = extentsOfCollider().getSize().y / 2;
	inheritedTransform.position.x -= colliderScale.x / 2;
	inheritedTransform.position.y -= colliderScale.y / 2;
	std::shared_ptr<Texture const> colliderTexture = assets.getAsset<Texture>( getTextureID() );
	inheritedTransform.scale.x += colliderScale.x / colliderTexture->getSize().width();
	inheritedTransform.scale.y += colliderScale.y / colliderTexture->getSize().height();
	//		std::cout << inheritedTransform.scale.x << " " << inheritedTransform.scale.y << std::endl;

	renderer.renderTexture( inheritedTransform, *colliderTexture );
}

Vector2D ICollider::getWorldPosition() const
{
	return _attatchedToTransform->position + getOffsetFromTransform();
}

std::shared_ptr<Transform2D const> ICollider::attatchedToTransform() const
{
	return _attatchedToTransform;
}

Vector2D ICollider::getOffsetFromTransform() const
{
	return _offset;
}

Vector2D Collision::ICollider::relativePositionToWorldPosition( Vector2D relativePosition ) const
{
	return getWorldPosition() + relativePosition;
}

Vector2D Collision::ICollider::worldPositionToRelativePosition( Vector2D worldPosition ) const
{
	return  worldPosition - getWorldPosition();
}

void ICollider::attatchToTransform( std::shared_ptr<Transform2D const> transform )
{
	_attatchedToTransform = transform;
}

void ICollider::setOffsetFromTransform( Vector2D offset )
{
	_offset = offset;
}

Collision::ICollider::ColliderCensus::ColliderCensus( ICollider * collider ) : _collider( collider )
{}

void Collision::ICollider::ColliderCensus::update( std::vector<ICollider *> * census )
{
	//	std::cout << "Collider registered." << std::endl;
	census->emplace_back( _collider );
}