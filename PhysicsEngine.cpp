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

void Collision::PhysicsEngine::_updateOverlapEvent( CollisionsThisFrame & overlaps )
{
	_overlapEvent.update( overlaps );
}

CollisionsThisFrame Collision::PhysicsEngine::_updateOverlapCollisions()
{
	CollisionsThisFrame::BaseMap collisions{};
	//Basically tests every element against each other, but it's just optimised so it doesn't pull out already checked pairs. We don't need to check x against itself, so we check every element after x against it. We know every element less than x has already been checked against every other element, so we don't bother checking them.
	for (size_t x = 0; x < _getColliders().size() - 1; x++)
		for (size_t y = x + 1; y < _getColliders().size(); y++)
		{
			ICollider * colX = _getColliders()[x];
			ICollider * colY = _getColliders()[y];
			CollisionData collisionData = testForOverlap( colX, colY );
			if (collisionData.intersectDistance != 0)
			{
				collisions.emplace( std::make_pair( colX, colY ), collisionData );
			}
		}
	return collisions;
}

void Collision::PhysicsEngine::_updatePhysicsCollisions( CollisionsThisFrame overlapCollisions, std::vector<PhysicsObject *> physicsObjects )
{}

void PhysicsEngine::updatePhysics( unsigned long millisecondsToSimulate, std::vector<PhysicsObject *> physicsObjects )
{
	CollisionsThisFrame overlaps = _updateOverlapCollisions();

	for (PhysicsObject * object : physicsObjects)
	{
		object->simulatePhysics( millisecondsToSimulate );
	}
}