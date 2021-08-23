#pragma once
#include "Vector2D.h"
#include "Rect2D.h"
#include <string>
#include "Transform2D.h"
#include <memory>
class AssetManager;

class RenderEngine;

namespace Collision
{
	class PhysicsEngine;
	class ICollider
	{
		PhysicsEngine & _engine;
		std::shared_ptr<Transform2D const> _attatchedToTransform;
		Vector2D _offset;
	public:
		ICollider( PhysicsEngine & engine, std::shared_ptr<Transform2D const> attatchedTo = std::make_shared<Transform2D>() );
		virtual ~ICollider();

		virtual std::string getTextureID() const = 0;
		/// @brief Returns the minimum size of rectangle that can fit the entire collider in it.
		/// @return The smallest possible rectangle that can fit the collider in it.
		virtual Rect2D extentsOfCollider() const = 0;

		virtual void render( AssetManager const & assets, RenderEngine const & renderer ) const;

		std::shared_ptr<Transform2D const> attatchedToTransform() const;
		Vector2D getOffsetFromTransform() const;
		Vector2D getWorldPosition() const;

		/// @brief Translates the position relative to this collider into the world position.
		/// @param relativePosition
		/// @return
		Vector2D relativePositionToWorldPosition( Vector2D relativePosition ) const;
		/// @brief Translates the world position into a position relative to this collider.
		/// @param worldPosition
		/// @return
		Vector2D worldPositionToRelativePosition( Vector2D worldPosition ) const;

		void attatchToTransform( std::shared_ptr<Transform2D const> transform );
		void setOffsetFromTransform( Vector2D offset );
	};
}