#include "PhysicsEngine.h"
#include "ICollider.h"
void PhysicsEngine::_addCollider( Collision::ICollider * collider )
{
	_colliders.insert( collider );
}

void PhysicsEngine::_removeCollider( Collision::ICollider * collider )
{
	_colliders.erase( collider );
}