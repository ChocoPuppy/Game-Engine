#pragma once
#include "Transform2D.h"
#include "AssetManager.h"
#include "ICollider.h"
#include <memory>
class PhysicsObject
{
public:
	PhysicsObject();
	virtual ~PhysicsObject();

	virtual void simulatePhysics( unsigned long millisecondsToSimulate );
	virtual bool isFacingLeft() const;
	void rawMove( Vector2D toPosition );

	std::shared_ptr<Transform2D const> transform() const;
	std::shared_ptr<Transform2D> transform();
	Vector2D const & velocity() const;
	Vector2D & velocity();

	bool affectedByGravity() const;
	bool isStatic() const;
	bool isActive() const;
	float getMass() const;

	void setIsAffectedByGravity( bool value );
	void setIsStatic( bool value );
	void setIsActive( bool value );
	void setMass( float value );
	void setCollider( Collision::ICollider * collider );
	//For moving owned colliders between objects atomically. Helps emphasise that the Collider stored in here is owned by this object and that colliders should usually be only owned by a singular object (as opposed to transforms).
	void setCollider( std::unique_ptr<Collision::ICollider> && collider );

	void impulse( Vector2D velocity );
	void push( Vector2D force );
	void setRotationalVelocity( float velocity ) { _rotationalVelocity = velocity; }
	float & rotationalVelocity();

	template<class ColliderType = Collision::ICollider>
	ColliderType const * getCollider() const
	{
		return  dynamic_cast<ColliderType const *>( _collider.get() );
	}

	template<class ColliderType = Collision::ICollider>
	ColliderType * getCollider()
	{
		return  dynamic_cast<ColliderType *>( _collider.get() );
	}
private:
	std::shared_ptr<Transform2D> _transform;
	Vector2D _velocity;
	float _rotationalVelocity;
	bool _useGravity;
	bool _isStatic;
	bool _isActive;
	float _mass;

	std::unique_ptr<Collision::ICollider> _collider;
};