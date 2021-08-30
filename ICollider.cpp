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

void ICollider::render( AssetManager const & assets, RenderEngine const & renderer ) const
{
	Transform2D transformData = *attatchedToTransform();
	transformData.position += getOffsetFromTransform();
	renderer.renderTexture( transformData, *assets.getAsset<Texture>( getTextureID() ) );
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