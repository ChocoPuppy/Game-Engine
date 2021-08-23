#include <set>
#include <vector>
#include <map>
#include <SmartEvent/EventHandle.h>
#include "OverlapEvent.h"
#include "CollisionTester.h"
#include "CollisionsThisFrame.h"
class PhysicsObject;
namespace Collision
{
	struct PhysicsCollisionData : public CollisionData
	{};
	class PhysicsEngine
	{
		friend ICollider;
		//I was instead considering some fuckery with weak_ptr's and shared_ptr's so that the colliders don't need to reference back here to remove themselves upon destruction, but that seems far too complicated and I've already done enough with weird data type storage in the SmartEvent package. This is good enough (although it sadly is against functional programming style).
		std::vector<ICollider *> _colliders;
		Event::SmartEvent::EventHandle<OverlapEvent> _overlapEvent;

		void _addCollider( ICollider * collider );
		void _removeCollider( ICollider * collider );

		std::vector<Collision::ICollider *> & _getColliders();

		void _updateOverlapEvent( CollisionsThisFrame & overlaps );

		CollisionsThisFrame _updateOverlapCollisions();

		void _updatePhysicsCollisions( CollisionsThisFrame overlapCollisions, std::vector<PhysicsObject *> physicsObjects );
	public:
		void updatePhysics( unsigned long millisecondsToSimulate, std::vector<PhysicsObject *> physicsObjects );
	};
}
