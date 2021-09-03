#include "Player.h"
#include <iostream>
Player::Player( std::string ID ) : AnimatedGameObject( ID, "Texture.Player.Running" ), _xInput( 0.9 ), _yInput( 0.9 ), _speed( 1 )
{
	transform()->position.x = 200;
	transform()->position.y = 200;
	transform()->scale.x = 100;
	transform()->scale.y = 100;

	_xInput.setGravity( 0.5 );
	_xInput.setDead( 0.01 );
	//	_xInput.setWillSnap( true );
	_yInput.setGravity( 0.5 );
	_yInput.setDead( 0.01 );
	//	_yInput.setWillSnap( true );
	std::cout << "Player has spawned" << std::endl;
}

void Player::simulateAI( unsigned long millisecondsToSimulate, AssetManager * )
{
	Vector2D movement = Vector2D{};
	movement.x = _xInput.getValue();
	movement.y = -_yInput.getValue();
	//	std::cout << _xInput.getValue() << std::endl;
		//	std::cout << movement.magnitude() << std::endl;
	constexpr double ANTI_NYOOM_COEFFICIENT = 0.000000002;
	Vector2D pushVelocity = movement.normalize() * (float)getSpeed() * (float)ANTI_NYOOM_COEFFICIENT * millisecondsToSimulate;
	push( pushVelocity );
	//	std::cout << movement.x << std::endl;
	_xInput.updateGravity( millisecondsToSimulate );
	_yInput.updateGravity( millisecondsToSimulate );
}