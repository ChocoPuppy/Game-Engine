#pragma once
#include <map>
#include <set>
#include <type_traits>

namespace Collision
{
	struct CollisionData;
	class ICollider;
	class PhysicsEngine;

	struct CollisionsThisFrame : std::map<std::pair<ICollider *, ICollider *>, CollisionData >
	{
		friend PhysicsEngine;

		using ColliderPair = std::pair<ICollider *, ICollider *>;
		using BaseMap = std::map<ColliderPair, CollisionData >;

		std::set<ColliderPair *> getCollisionsInvolvingCollider( ICollider const * collider ) const;

		CollisionData dataOfCollision( ColliderPair key ) const;

	private:

		mutable std::multimap<ICollider const *, ColliderPair> _associatedCollisionsCache;

		CollisionsThisFrame( BaseMap && collisions );
		void _recalculateCache();
	};
}