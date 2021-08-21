#pragma once
#include "Vector2D.h"
#include "Rect2D.h"
#include <string>
struct Transform2D;
class AssetManager;

class RenderEngine;

namespace Collision
{
	class ICollider
	{
		bool _isTrigger;
		Rect2D _extentsOfCollider;
	protected:
	public:
		virtual std::string getTextureID() const = 0;
		/// @brief Returns the minimum size of rectangle that can fit the entire collider in it.
		/// @return The smallest possible rectangle that can fit the collider in it.
		virtual Rect2D extentsOfCollider() const = 0;

		virtual void render( Transform2D const & transform, AssetManager const & assets, RenderEngine const & renderer ) const;
		bool isTrigger() const { return _isTrigger; }
		void setIsTrigger( bool value ) { _isTrigger = value; }

		//		virtual float intersectionDepth( Vector2D point ) const = 0;
				//		virtual Vector2D closestEdgeToPoint( Vector2D point ) const = 0;
	};
}