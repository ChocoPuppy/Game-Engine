#include "PhysicsEngine.h"
#include "ICollider.h"
#include "CollisionTester.h"
#include <utility>
#include <algorithm>
#include "LineCollider2D.h"
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

CollisionsThisFrame Collision::PhysicsEngine::_getOverlapsOfSpecificCollider( ICollider * specificCollider, std::vector<ICollider *> colliders ) const
{
	CollisionsThisFrame::BaseMap collisions{};

	auto furthestFromSpecificCollider = [specificCollider]( ICollider * lhs, ICollider * rhs )
	{
		Vector2D const lhsRelativePos = specificCollider->worldPositionToRelativePosition( lhs->getWorldPosition() );
		Vector2D const rhsRelativePos = specificCollider->worldPositionToRelativePosition( rhs->getWorldPosition() );
		return lhsRelativePos.magnitude() > rhsRelativePos.magnitude();
	};

	//Sorts all other colliders to be in order of closest object to furthest object.
	std::priority_queue<ICollider *, std::vector<ICollider *>, decltype( furthestFromSpecificCollider )> queuedColliders( colliders.begin(), colliders.end(), furthestFromSpecificCollider );

	bool isntRaycastCollider;
	{
		LineCollider2D * potentialLineCollider = dynamic_cast<LineCollider2D *>( specificCollider );
		bool isLineCollider = potentialLineCollider != nullptr;
		isntRaycastCollider = ( isLineCollider ) ? !potentialLineCollider->isRay() : true;
	}
	bool hasntCollidedYet = true;

	//If the target collider isn't a raycast collider and the queuedColliders isn't empty, continue. If the target collider is a raycast collider, hasn't detected a collision yet and there are still queuedColliders, continue. If it is a raycast collider and we've detected a collision or we're out of queued colliders, stop.
	while (!queuedColliders.empty() && ( isntRaycastCollider || hasntCollidedYet ))
	{
		ICollider * rhs = queuedColliders.top();
		queuedColliders.pop();
		//Don't check for collisions if both colliders are the same one, since, we really don't care if it's colliding with itself.
		if (rhs != specificCollider)
		{
			CollisionData collisionData = Experimental::testForOverlap( *specificCollider, *rhs );
			if (collisionData.intersectDistance != 0)
			{
				hasntCollidedYet = false;
				collisions.emplace( std::make_pair( specificCollider, rhs ), collisionData );
			}
		}
	}
	return collisions;
}

Collision::CollisionsThisFrame PhysicsEngine::_getOverlapCollisions( std::vector<ICollider *> const & colliders ) const
{
	CollisionsThisFrame::BaseMap collisions{};

	auto sortedColliderQueue = _sortRaycastsFirst( colliders );

	while (!sortedColliderQueue.empty())
	{
		ICollider * targetCollider = sortedColliderQueue.front();
		sortedColliderQueue.pop();

		auto newCollisions = _getOverlapsOfSpecificCollider( targetCollider, colliders );
		collisions.merge( newCollisions );
	}
	////Basically tests every element against each other, but it's just optimised so it doesn't pull out already checked pairs. We don't need to check x against itself, so we check every element after x against it. We know every element less than x has already been checked against every other element, so we don't bother checking them.
	//for (size_t x = 0; x < colliders.size(); x++)
	//	for (size_t y = x + 1; y < colliders.size(); y++)
	//	{
	//		ICollider * colX = colliders[x];
	//		ICollider * colY = colliders[y];

	//		CollisionData collisionData = Experimental::testForOverlap( *colX, *colY );
	//		if (collisionData.intersectDistance != 0)
	//		{
	//			collisions.emplace( std::make_pair( colX, colY ), collisionData );
	//		}
	//	}
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

float Collision::PhysicsEngine::getDistanceBetweenColliders( ICollider const & obj1, ICollider const & obj2 )
{
	Vector2D minowskiDifferenceOfSupports;
	{
		Vector2D obj1SupportPoint, obj2SupportPoint;
		{
			Vector2D vectorFromObj1CenterToObj2Center;
			{
				Vector2D const obj1WorldPos = obj1.getWorldPosition();
				Vector2D const obj2WorldPos = obj2.getWorldPosition();
				vectorFromObj1CenterToObj2Center = obj1WorldPos - obj2WorldPos;
			}

			obj1SupportPoint = obj1.getSupportPointOf( vectorFromObj1CenterToObj2Center );
			Vector2D const vectorFromObj2CenterToObj1Center = -vectorFromObj1CenterToObj2Center;
			obj2SupportPoint = obj2.getSupportPointOf( -vectorFromObj2CenterToObj1Center );
		}
		minowskiDifferenceOfSupports = obj1SupportPoint - obj2SupportPoint;
	}
	float const distanceBetweenColliders = minowskiDifferenceOfSupports.magnitude();
	return distanceBetweenColliders;
}

std::optional<RaycastCollisionData> Collision::PhysicsEngine::raycast( Vector2D position, Vector2D length )
{
	std::optional<RaycastCollisionData> data = std::nullopt;
	Line2D const line = { length };
	static constexpr bool IS_RAYCAST = true;
	auto otherColliders = _getColliders();
	LineCollider2D raycastCollider = LineCollider2D( line, IS_RAYCAST );
	raycastCollider.setOffsetFromTransform( position );

	auto collisionsWithThisObject = _getOverlapsOfSpecificCollider( &raycastCollider, otherColliders );
	//This should be only one or zero elements, but even if it's somehow more, it just means a random thing gets picked as the collider from the cast, which isn't perfect, but I need to rework this system anyway so this should give me some extra reason to.
	for (CollisionsThisFrame::ColliderPair pair : collisionsWithThisObject.getCollisions())
	{
		CollisionData superData = collisionsWithThisObject.dataOfCollision( pair );
		data.emplace( superData );
		data->collider = pair.second;
	}

	return data;
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

std::queue<ICollider *> Collision::PhysicsEngine::_sortRaycastsFirst( std::vector<ICollider *> colliders )
{
	//Sorts the queue so that raycast colliders go first due to their special nature. I really probably should find a better way to do raycasts, but for now this works.
	std::queue<ICollider *> sortedColliderQueue{};
	{
		std::queue<ICollider *> nonRaycastQueue{};

		for (ICollider *& collider : colliders)
		{
			LineCollider2D * potentialRaycastCollider = dynamic_cast<LineCollider2D *>( collider );
			bool const isLineCollider = potentialRaycastCollider != nullptr;
			bool const isRaycastCollider = ( isLineCollider ) ? potentialRaycastCollider->isRay() : false;
			if (isRaycastCollider)
			{
				sortedColliderQueue.emplace( collider );
			}
			else
			{
				nonRaycastQueue.emplace( collider );
			}
		}
		while (!nonRaycastQueue.empty())
		{
			ICollider * toAddCollider = nonRaycastQueue.front();
			nonRaycastQueue.pop();
			sortedColliderQueue.push( toAddCollider );
		}
	}
	return sortedColliderQueue;
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