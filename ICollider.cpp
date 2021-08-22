#include "ICollider.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "TextureWrapper.h"
#include "Transform2D.h"
#include "Size.h"
#include "RenderEngine.h"
#include "PhysicsEngine.h"

Collision::ICollider::ICollider( PhysicsEngine & engine, std::shared_ptr<Transform2D const> attatchedTo ) : _engine( engine ), _attatchedToTransform( attatchedTo )
{
	_engine._addCollider( this );
}

Collision::ICollider::~ICollider()
{
	_engine._removeCollider( this );
}

void Collision::ICollider::render( AssetManager const & assets, RenderEngine const & renderer ) const
{
	Transform2D transformData = *attatchedToTransform();
	transformData.position += getOffsetFromTransform();
	renderer.renderTexture( transformData, *assets.getAsset<Texture>( getTextureID() ) );
}

Vector2D Collision::ICollider::getWorldPosition() const
{
	return _attatchedToTransform->position + getOffsetFromTransform();
}

std::shared_ptr<Transform2D const> Collision::ICollider::attatchedToTransform() const
{
	return _attatchedToTransform;
}

Vector2D Collision::ICollider::getOffsetFromTransform() const
{
	return _offset;
}

void Collision::ICollider::attatchToTransform( std::shared_ptr<Transform2D const> transform )
{
	_attatchedToTransform = transform;
}

void Collision::ICollider::setOffsetFromTransform( Vector2D offset )
{
	_offset = offset;
}