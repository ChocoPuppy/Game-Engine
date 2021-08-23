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

	void SetIsAffectedByGravity( bool value );
	void impulse( Vector2D velocity );

	template<class ColliderType = Collision::ICollider>
	ColliderType * getCollider()
	{
		return dynamic_cast<ColliderType *>( _collider );
	}
private:
	std::shared_ptr<Transform2D> _transform;
	Vector2D _velocity;
	bool _useGravity;

	Collision::ICollider * _collider;
};