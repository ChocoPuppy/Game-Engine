#include "PhysicsObject.h"
#include "CircleCollider2D.h"
PhysicsObject::PhysicsObject() :_transform( std::make_shared<Transform2D>() ), _velocity{ 0,0 }, _rotationalVelocity( 0 ), _useGravity( true ), _isStatic( false ), _isActive( true ), _mass( 1 )
{
	Circle2D colliderSize = { 50 };
	auto * collider = new Collision::CircleCollider2D( transform(), colliderSize );
	collider->setOffsetFromTransform( { colliderSize.radius / 2,colliderSize.radius / 2 } );
	setCollider( collider );
}

PhysicsObject::~PhysicsObject()
{}

void PhysicsObject::simulatePhysics( unsigned long millisecondsToSimulate )
{
	if (!isStatic() && isActive())
	{
		velocity() += getAcceleration() * (float)millisecondsToSimulate;
		push( velocity() * (float)millisecondsToSimulate );
		transform()->rotation += _rotationalVelocity;
	}
	_clearForce();
}

bool PhysicsObject::isFacingLeft() const
{
	return velocity().isAngledLeft();
}

void PhysicsObject::rawMove( Vector2D toPosition )
{
	transform()->position = toPosition;
}

std::shared_ptr<Transform2D const> PhysicsObject::transform() const
{
	return _transform;
}

std::shared_ptr<Transform2D> PhysicsObject::transform()
{
	return _transform;
}

Vector2D const & PhysicsObject::velocity() const
{
	return _velocity;
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
bool PhysicsObject::isStatic() const
{
	return _isStatic;
}
bool PhysicsObject::isActive() const
{
	return _isActive;
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
	acceleration.x = getForce().x / getMass();
	acceleration.y = getForce().y / getMass();
	return acceleration;
}
void PhysicsObject::setIsAffectedByGravity( bool value )
{
	_useGravity = value;
}

void PhysicsObject::setIsStatic( bool value )
{
	_isStatic = value;
}

void PhysicsObject::setIsActive( bool value )
{
	_isActive = value;
}

void PhysicsObject::setMass( float value )
{
	_mass = value;
}

void PhysicsObject::setCollider( Collision::ICollider * collider )
{
	setCollider( std::unique_ptr<Collision::ICollider>( collider ) );
}

void PhysicsObject::setCollider( std::unique_ptr<Collision::ICollider> && collider )
{
	_collider = std::forward<std::unique_ptr<Collision::ICollider>>( collider );
	_collider->attatchToTransform( transform() );
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
	if (!isStatic())
		rawMove( transform()->position + force );
}

void PhysicsObject::_clearForce()
{
	_force = {};
}