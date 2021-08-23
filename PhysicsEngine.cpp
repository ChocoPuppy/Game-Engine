#include "PhysicsEngine.h"
#include "ICollider.h"
#include "CollisionTester.h"
#include <utility>
#include <algorithm>
#include "PhysicsObject.h"

using namespace Collision;

void PhysicsEngine::_addCollider( ICollider * collider )
{
	_getColliders().push_back( collider );
}

void PhysicsEngine::_removeCollider( ICollider * collider )
{
	auto position = std::find( _getColliders().begin(), _colliders.end(), collider );
	_getColliders().erase( position );
}

std::vector<ICollider *> & PhysicsEngine::_getColliders()
{
	return _colliders;
}

void PhysicsEngine::updatePhysics( unsigned long millisecondsToSimulate, std::vector<PhysicsObject *> physicsObjects )
{
	//Basically tests every element against each other, but it's just optimised so it doesn't pull out a pair already checked. We don't need to check x against itself, so we check every element after x against it. We know every element less than x has already been checked against every other element.
	for (size_t x = 0; x < _getColliders().size(); x++)
		for (size_t y = x + 1; y < _getColliders().size(); y++)
		{
			CollisionData collision = Collision::testForOverlap( _getColliders()[x], _getColliders()[y] );
			if (collision.intersectDistance != 0)
			{
				_overlapEvent.update( collision, _getColliders()[x], _getColliders()[y] );
			}
		}

	for (PhysicsObject * object : physicsObjects)
	{
		object->simulatePhysics( millisecondsToSimulate );
	}
}