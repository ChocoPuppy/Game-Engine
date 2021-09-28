#pragma once
#include "Transform2D.h"
#include "AssetManager.h"
#include "ICollider.h"
#include <memory>
class PhysicsObject
{
public:
	PhysicsObject();

	virtual void simulatePhysics( unsigned long millisecondsToSimulate );
	void rawMove( Vector2D toPosition );

	std::shared_ptr<Transform2D> transform();
	Vector2D & velocity();

	bool affectedByGravity() const;
	bool isKinematic() const;
	float getMass() const;
	Vector2D getForce() const;
	Vector2D getAcceleration() const;

	void setIsAffectedByGravity( bool value );
	void setIsKinematic( bool value );
	void setMass( float value );

	void impulse( Vector2D velocity );
	void addForce( Vector2D force );

	void push( Vector2D force );

	template<class ColliderType = Collision::ICollider>
	ColliderType * getCollider()
	{
		return dynamic_cast<ColliderType *>( _collider );
	}
private:
	std::shared_ptr<Transform2D> _transform;
	Vector2D _velocity;
	Vector2D _force;
	bool _useGravity;
	bool _isKinematic;
	float _mass;

	Collision::ICollider * _collider;

	void _clearForce();
};