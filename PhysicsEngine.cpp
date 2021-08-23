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

std::vector<ICollider *> PhysicsEngine::_getColliders() const
{
	return _colliders;
}

void PhysicsEngine::_updateOverlapEvent( CollisionsThisFrame & overlapCollisions )
{
	_overlapEvent.update( &overlapCollisions );
}

void PhysicsEngine::_updatePhysicsEvent( CollisionsThisFrame & physicsCollisions )
{
	_physicsEvent.update( &physicsCollisions );
}

Collision::CollisionsThisFrame PhysicsEngine::_getOverlapCollisions() const
{
	CollisionsThisFrame::BaseMap collisions{};
	//Basically tests every element against each other, but it's just optimised so it doesn't pull out already checked pairs. We don't need to check x against itself, so we check every element after x against it. We know every element less than x has already been checked against every other element, so we don't bother checking them.
	for (size_t x = 0; x < _getColliders().size(); x++)
		for (size_t y = x + 1; y < _getColliders().size(); y++)
		{
			ICollider * colX = _getColliders()[x];
			ICollider * colY = _getColliders()[y];
			CollisionData collisionData = testForOverlap( *colX, *colY );
			if (collisionData.intersectDistance != 0)
			{
				collisions.emplace( std::make_pair( colX, colY ), collisionData );
			}
		}
	return collisions;
}

Collision::CollisionsThisFrame PhysicsEngine::_getPhysicsCollisions( CollisionsThisFrame const & overlapCollisions, std::vector<PhysicsObject *> const & physicsObjects ) const
{
	CollisionsThisFrame::BaseMap physicsCollisions{};
	for (auto & obj : physicsObjects)
		for (auto & collision : overlapCollisions.getCollisionsInvolvingCollider( obj->getCollider() ))
			physicsCollisions.emplace( *collision, overlapCollisions.dataOfCollision( *collision ) );
	return physicsCollisions;
}

void Collision::PhysicsEngine::_resolvePhysicsCollisions( CollisionsThisFrame & physicsCollisions, std::vector<PhysicsObject *> & physicsObjects )
{
	for (PhysicsObject * obj : physicsObjects)
	{
		auto relatedCollisions = physicsCollisions.getCollisionsInvolvingCollider( obj->getCollider() );
		for (auto & collision : relatedCollisions)
		{
			auto collisionData = physicsCollisions.dataOfCollision( *collision );
			if (!obj->isKinematic())
			{
				ICollider * otherCollider = ( obj->getCollider() == collision->first ) ? collision->second : collision->first;
				Vector2D otherColliderToCollider = obj->transform()->position - otherCollider->getWorldPosition();
				Vector2D normalizedOtherColliderToCollider = otherColliderToCollider.normalize();
				Vector2D pushForceToResolveCollision = normalizedOtherColliderToCollider * collisionData.intersectDistance;

				Vector2D pushForceModulatedByMass = pushForceToResolveCollision / obj->getMass();

				obj->push( pushForceModulatedByMass );
			}
		}
	}
}

void PhysicsEngine::updatePhysics( unsigned long millisecondsToSimulate, std::vector<PhysicsObject *> & physicsObjects )
{
	CollisionsThisFrame overlapCollisions = _getOverlapCollisions();
	CollisionsThisFrame physicsCollisions = _getPhysicsCollisions( overlapCollisions, physicsObjects );

	_resolvePhysicsCollisions( physicsCollisions, physicsObjects );

	_updateOverlapEvent( overlapCollisions );
	_updatePhysicsEvent( physicsCollisions );
	for (PhysicsObject * object : physicsObjects)
	{
		object->simulatePhysics( millisecondsToSimulate );
	}
}