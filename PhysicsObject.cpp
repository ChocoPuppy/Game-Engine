#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() :_transform( std::make_shared<Transform2D>() ), _rotationalVelocity( 0 ), _useGravity( true ) {}

void PhysicsObject::simulatePhysics( unsigned long millisecondsToSimulate )
{
	if (!isKinematic())
	{
		transform()->position += velocity() * (float)millisecondsToSimulate;
		transform()->rotation += _rotationalVelocity;
	}
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

float & PhysicsObject::rotationalVelocity()
{
	return _rotationalVelocity;
}

bool PhysicsObject::affectedByGravity() const
{
	return _useGravity;
}
bool PhysicsObject::isKinematic() const
{
	return _isKinematic;
}
float PhysicsObject::getMass() const
{
	return _mass;
}
void PhysicsObject::setIsAffectedByGravity( bool value )
{
	_useGravity = value;
}

void PhysicsObject::setIsKinematic( bool value )
{
	_isKinematic = value;
}

void PhysicsObject::setMass( float value )
{
	_mass = value;
}

void PhysicsObject::impulse( Vector2D velocity )
{
	_velocity += velocity;
}

void PhysicsObject::push( Vector2D force )
{
	if (!isKinematic())
		transform()->position += force;
}