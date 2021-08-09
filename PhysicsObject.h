#pragma once
#include "Transform2D.h"
#include "AssetManager.h"

class PhysicsObject
{
public:
	PhysicsObject();

	virtual void simulatePhysics( unsigned long millisecondsToSimulate, AssetManager * assets );
	void rawMove( Vector2D toPosition );

	Transform2D & transform();
	Vector2D & velocity();
	bool affectedByGravity();

	void SetIsAffectedByGravity( bool value );
private:
	Transform2D _transform;
	Vector2D _velocity;
	bool _useGravity;
};