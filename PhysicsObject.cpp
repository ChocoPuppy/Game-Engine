#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() : _useGravity( true ), _rotationalVelocity( 0 ) {}

void PhysicsObject::simulatePhysics( unsigned long millisecondsToSimulate, AssetManager * )
{
	transform().position += velocity() * (float)millisecondsToSimulate;
	transform().rotation += _rotationalVelocity;
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

float & PhysicsObject::rotationalVelocity()
{
	return _rotationalVelocity;
}

bool PhysicsObject::affectedByGravity()
{
	return _useGravity;
}

void PhysicsObject::SetIsAffectedByGravity( bool value )
{
	_useGravity = value;
}