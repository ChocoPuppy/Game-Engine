#include "PhysicsEngine.h"
#include "ICollider.h"
#include "CollisionTester.h"
#include <utility>
#include <algorithm>
#include "PhysicsObject.h"
#include "CollisionTesterExperimental.h"
using namespace Collision;

/*void PhysicsEngine::_addCollider(ICollider * collider)
{
	_getColliders().push_back( collider );
}

void PhysicsEngine::_removeCollider( ICollider * collider )
{
	auto position = std::find( _getColliders().begin(), _colliders.end(), collider );
	_getColliders().erase( position );
}*/

/*std::vector<ICollider *> PhysicsEngine::_getColliders() const
{
	return _colliders;
}*/

std::vector<ICollider *> Collision::PhysicsEngine::_getColliders()
{
	auto colliders = std::vector<ICollider *>();
	_getColliderEvent.update( &colliders );
	return colliders;
}

void PhysicsEngine::_updateOverlapEvent( CollisionsThisFrame & overlapCollisions )
{
	_overlapEvent.update( &overlapCollisions );
}

void PhysicsEngine::_updatePhysicsEvent( CollisionsThisFrame & physicsCollisions )
{
	_physicsEvent.update( &physicsCollisions );
}

Collision::CollisionsThisFrame PhysicsEngine::_getOverlapCollisions( std::vector<ICollider *> colliders ) const
{
	CollisionsThisFrame::BaseMap collisions{};
	//Basically tests every element against each other, but it's just optimised so it doesn't pull out already checked pairs. We don't need to check x against itself, so we check every element after x against it. We know every element less than x has already been checked against every other element, so we don't bother checking them.
	for (size_t x = 0; x < colliders.size(); x++)
		for (size_t y = x + 1; y < colliders.size(); y++)
		{
			ICollider * colX = colliders[x];
			ICollider * colY = colliders[y];

			CollisionData collisionData = Experimental::testForOverlap( *colX, *colY );
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

void Collision::PhysicsEngine::_resolvePhysicsCollisions( CollisionsThisFrame & physicsCollisions, std::vector<PhysicsObject *> const & physicsObjects )
{
	auto colToObj = _mapColliderToPhysicsObject( physicsObjects );
	for (auto & colliderPair : physicsCollisions.getCollisions())
	{
		auto collisionData = physicsCollisions.dataOfCollision( colliderPair );
		PhysicsObject & objA = *colToObj.at( colliderPair.first );
		PhysicsObject & objB = *colToObj.at( colliderPair.second );
		_resolvePhysicsCollision( objA, objB, collisionData );
	}

	//Old, less efficient version.
	/*for (PhysicsObject * obj : physicsObjects)
	{
		auto relatedCollisions = physicsCollisions.getCollisionsInvolvingCollider( obj->getCollider() );
		for (auto & collision : relatedCollisions)
		{
			auto collisionData = physicsCollisions.dataOfCollision( *collision );
			if (!obj->isStatic())
			{
				ICollider * otherCollider = ( obj->getCollider() != collision->first ) ? collision->first : collision->second;
				Vector2D otherColliderToCollider = obj->getCollider()->getWorldPosition() - otherCollider->getWorldPosition();
				Vector2D normalizedOtherColliderToCollider = otherColliderToCollider.normalize();
				Vector2D pushForceToResolveCollision = normalizedOtherColliderToCollider * collisionData.intersectDistance;

				obj->push( pushForceToResolveCollision );
			}
		}
	}*/
}

std::map<ICollider *, PhysicsObject *> Collision::PhysicsEngine::_mapColliderToPhysicsObject( std::vector<PhysicsObject *> const & physicsObjects )
{
	std::map<ICollider *, PhysicsObject *> mapping{};
	for (auto & obj : physicsObjects)
	{
		mapping.emplace( obj->getCollider(), obj );
	}
	return mapping;
}

void Collision::PhysicsEngine::_resolvePhysicsCollision( PhysicsObject & objA, PhysicsObject & objB, CollisionData & collisionData )
{
	_resolveCollisionWithPhysicsObject( objA, objB, collisionData );
	_resolveCollisionWithPhysicsObject( objB, objA, collisionData );
}

void Collision::PhysicsEngine::_resolveCollisionWithPhysicsObject( PhysicsObject & object, PhysicsObject const & otherObject, CollisionData collisionData )
{
	if (!object.isStatic())
	{
		const Vector2D otherColliderToCollider = object.getCollider()->getWorldPosition() - otherObject.getCollider()->getWorldPosition();
		const Vector2D normalizedOtherColliderToCollider = otherColliderToCollider.normalize();
		const Vector2D pushForceToResolveCollision = normalizedOtherColliderToCollider * collisionData.intersectDistance;

		object.push( pushForceToResolveCollision );
	}
}

void PhysicsEngine::updatePhysics( unsigned long millisecondsToSimulate, std::vector<PhysicsObject *> & physicsObjects )
{
	auto colliders = _getColliders();
	CollisionsThisFrame overlapCollisions = _getOverlapCollisions( colliders );
	CollisionsThisFrame physicsCollisions = _getPhysicsCollisions( overlapCollisions, physicsObjects );

	_resolvePhysicsCollisions( physicsCollisions, physicsObjects );

	_updateOverlapEvent( overlapCollisions );
	_updatePhysicsEvent( physicsCollisions );
	for (PhysicsObject * object : physicsObjects)
	{
		object->simulatePhysics( millisecondsToSimulate );
	}
}