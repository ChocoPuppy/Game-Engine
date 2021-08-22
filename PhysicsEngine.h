#include <set>
#include <vector>
#include <SmartEvent/EventHandle.h>
#include "OverlapEvent.h"

class PhysicsObject;
namespace Collision
{
	class ICollider;
}

namespace
{
	using namespace Collision;
}

class PhysicsEngine
{
	friend ICollider;
	//I was instead considering some fuckery with weak_ptr's and shared_ptr's so that the colliders don't need to reference back here to remove themselves upon destruction, but that seems far too complicated and I've already done enough with weird data type storage in the SmartEvent package. This is good enough (although it sadly is against functional programming style).
	std::vector<ICollider *> _colliders;
	Event::SmartEvent::EventHandle<OverlapEvent> _overlapEvent;

	void _addCollider( ICollider * collider );
	void _removeCollider( ICollider * collider );

	std::vector<Collision::ICollider *> & _getColliders();
public:
	void updatePhysics( unsigned long millisecondsToSimulate, std::vector<PhysicsObject *> physicsObjects );
};