#include "CollisionsThisFrame.h"
#include "CollisionTester.h"
using namespace Collision;

std::set<CollisionsThisFrame::ColliderPair *> CollisionsThisFrame::getCollisionsInvolvingCollider( ICollider const * collider ) const
{
	auto equalRange = _associatedCollisionsCache.equal_range( collider );
	std::set<ColliderPair *> relatedCollisions{};
	for (auto & collision = equalRange.first; collision != equalRange.second; collision++)
	{
		relatedCollisions.emplace( &collision->second );
	}
	return relatedCollisions;
}

CollisionData CollisionsThisFrame::dataOfCollision( ColliderPair key ) const
{
	return at( key );
}

void Collision::CollisionsThisFrame::_recalculateCache()
{
	_associatedCollisionsCache.clear();
	for (auto & pair : *this)
	{
		auto & target = pair.first;
		_associatedCollisionsCache.emplace( target.first, target );
		_associatedCollisionsCache.emplace( target.second, target );
	}
}

CollisionsThisFrame::CollisionsThisFrame( BaseMap && collisions ) : BaseMap( collisions )
{
	_recalculateCache();
}