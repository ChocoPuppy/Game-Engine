#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() : _transform( std::make_shared<Transform2D>() ), _useGravity( true ) {}

void PhysicsObject::simulatePhysics( unsigned long millisecondsToSimulate )
{
	if (!isKinematic())
	{
		velocity() += getAcceleration() * (float)millisecondsToSimulate;
		transform()->position += velocity() * (float)millisecondsToSimulate;
	}
	_clearForce();
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
Vector2D PhysicsObject::getForce() const
{
	return _force;
}
Vector2D PhysicsObject::getAcceleration() const
{
	Vector2D acceleration;
	acceleration.x() = getForce().x() / getMass();
	acceleration.y() = getForce().y() / getMass();
	return acceleration;
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

void PhysicsObject::addForce( Vector2D force )
{
	_force += force;
}

void PhysicsObject::push( Vector2D force )
{
	if (!isKinematic())
		transform()->position += force;
}

void PhysicsObject::_clearForce()
{
	_force = {};
}