#include "ICollider.h"
namespace Collision
{
	class RectCollider2D : public ICollider
	{
		Rect2D _rect;
	public:
		virtual std::string getTextureID() const override;

		virtual Rect2D extentsOfCollider() const override;

		RectCollider2D( std::shared_ptr<Transform2D> transform, Rect2D rectangle = Rect2D( { 100,100 } ) );

		Rect2D getSize() const;
		void setSize( Rect2D size );
	};
	template<>
	struct TestForSpecificOverlap<RectCollider2D, RectCollider2D>
	{
		//Since the generic test is the same as this, don't actually bother testing. This is just explicitly stated since, well, there IS a rectangle on rectangle test. It just happened to have already happened.
		void operator()( RectCollider2D const &, RectCollider2D const &, CollisionData & )
		{
			//			std::cout << "Rectangle test!" << std::endl;
		}
	};
}
