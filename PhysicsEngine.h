#include <set>
#include <vector>
class PhysicsObject;
namespace Collision
{
	class ICollider;
}

class PhysicsEngine
{
	friend Collision::ICollider;
	std::set<Collision::ICollider *> _colliders;

	void _addCollider( Collision::ICollider * collider );
	void _removeCollider( Collision::ICollider * collider );

public:
	void updatePhysics( std::vector<PhysicsObject *> objects )
};