#include "PhysicsObject.h"

void PhysicsObject::simulatePhysics( unsigned long, AssetManager * )
{}

void PhysicsObject::rawMove( Vector2D toPosition )
{
	transform().position = toPosition;
}

Transform2D & PhysicsObject::transform()
{
	return _transform;
}

Vector2D & PhysicsObject::velocity()
{
	return _velocity;
}