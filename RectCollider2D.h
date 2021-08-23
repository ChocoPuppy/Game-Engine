#include "ICollider.h"
#include "CollisionTester.h"
namespace Collision
{
	class RectCollider2D : public ICollider
	{
		Rect2D _rect;
	public:
		virtual std::string getTextureID() const override;

		virtual Rect2D extentsOfCollider() const override;

		Rect2D getSize() const;
		void setSize( Rect2D size );
	};
	template<>
	class TestForSpecificOverlap<RectCollider2D, RectCollider2D>
	{
		//Since the generic test is the same as this, don't actually bother testing. This is just explicitly stated so people don't get confused.
		bool test( RectCollider2D const & colliderA, RectCollider2D const & colliderB, CollisionData & data )
		{
			return true;
		}
	};
}
