#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() : _useGravity( true ) {}

void PhysicsObject::simulatePhysics( unsigned long millisecondsToSimulate, AssetManager * )
{
	transform().position += velocity() * (float)millisecondsToSimulate;
}

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

bool PhysicsObject::affectedByGravity()
{
	return _useGravity;
}

void PhysicsObject::SetIsAffectedByGravity( bool value )
{
	_useGravity = value;
}