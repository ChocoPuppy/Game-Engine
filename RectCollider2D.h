#include "ICollider.h"

namespace Collision
{
	class RectCollider2D : public ICollider
	{
		virtual std::string getTextureID() const override;
		virtual void render( Transform2D const & transform, AssetManager const & assets, RenderEngine const & renderer ) const override;

		virtual Rect2D extentsOfCollider() const override;
	};
}
