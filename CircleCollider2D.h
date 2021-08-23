#pragma once
#include "ICollider.h"
#include "Circle2D.h"
#include "TextureWrapper.h"
namespace Collision
{
	class CircleCollider2D :public ICollider, public Circle2D
	{
	public:
		virtual std::string getTextureID() const override;

		virtual Rect2D extentsOfCollider() const override;
	};
}