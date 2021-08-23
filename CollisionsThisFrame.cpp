#include "CollisionsThisFrame.h"

using namespace Collision;

std::set<std::pair<ICollider *, ICollider *>> CollisionsThisFrame::getCollisionsInvolvingCollider( ICollider * collider )
{
	auto equalRange = _associatedCollisionsCache.equal_range( collider );
	return std::set<std::pair<ICollider *, ICollider *>>( equalRange.first, equalRange.second );
}

CollisionData & CollisionsThisFrame::dataOfCollision( std::pair<ICollider *, ICollider *> * key )
{
	return *at( *key );
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