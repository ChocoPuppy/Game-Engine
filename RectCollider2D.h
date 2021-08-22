#include "ICollider.h"

namespace Collision
{
	class RectCollider2D : public ICollider
	{
		virtual std::string getTextureID() const override;

		virtual Rect2D extentsOfCollider() const override;
	};
}
