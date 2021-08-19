#include <set>
#include <vector>
#include <map>
#include <SmartEvent/EventHandle.h>
#include "OverlapEvent.h"
#include "PhysicsEvent.h"
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
		Event::SmartEvent::EventHandle<PhysicsEvent> _physicsEvent;

		void _addCollider( ICollider * collider );
		void _removeCollider( ICollider * collider );

		std::vector<Collision::ICollider *> _getColliders() const;

		void _updateOverlapEvent( CollisionsThisFrame & overlapCollisions );
		void _updatePhysicsEvent( CollisionsThisFrame & physicsCollisions );

		CollisionsThisFrame _getOverlapCollisions() const;
		CollisionsThisFrame _getPhysicsCollisions( CollisionsThisFrame const & overlapCollisions, std::vector<PhysicsObject *> const & physicsObjects ) const;

		void _collideVelocities( PhysicsObject & obj1, PhysicsObject & obj2 );
		void _resolvePhysicsCollisions( CollisionsThisFrame & physicsCollisions, std::vector<PhysicsObject *> & physicsObjects );
	public:
		void updatePhysics( unsigned long millisecondsToSimulate, std::vector<PhysicsObject *> & physicsObjects );
	};
}
