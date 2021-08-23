#pragma once
#include <map>
#include <set>
namespace Collision
{
	struct CollisionData;
	class ICollider;
	class PhysicsEngine;

	struct CollisionsThisFrame : std::map<std::pair<ICollider *, ICollider *>, CollisionData *>
	{
		friend PhysicsEngine;

		using BaseMap = std::map<std::pair<ICollider *, ICollider *>, CollisionData *>;

		std::set<std::pair<ICollider *, ICollider *>> getCollisionsInvolvingCollider( ICollider * collider );

		CollisionData & dataOfCollision( std::pair<ICollider *, ICollider *> * key );

	private:

		std::multimap<ICollider *, std::pair<ICollider *, ICollider *>> _associatedCollisionsCache;

		CollisionsThisFrame( BaseMap && collisions );
		void _recalculateCache();
	};
}