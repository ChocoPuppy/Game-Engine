#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() : _transform( std::make_shared<Transform2D>() ), _useGravity( true ) {}

void PhysicsObject::simulatePhysics( unsigned long millisecondsToSimulate )
{
	transform()->position += velocity() * (float)millisecondsToSimulate;
}

void PhysicsObject::rawMove( Vector2D toPosition )
{
	transform()->position = toPosition;
}

std::shared_ptr<Transform2D> PhysicsObject::transform()
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