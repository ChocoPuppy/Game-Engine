#include "Player.h"
#include <iostream>
Player::Player( std::string ID ) : AnimatedGameObject( ID, "Texture.Player.Running" ), _speed( 1 ), _xInput( 0.9 ), _yInput( 0.9 )
{
	transform.position.x() = 200;
	transform.position.y() = 200;
	transform.scale.x() = 100;
	transform.scale.y() = 100;

	_xInput.setGravity( 0.09 );
	_xInput.setDead( 0.001 );
	_xInput.setWillSnap( true );
	_yInput.setGravity( 0.09 );
	_yInput.setDead( 0.001 );
	_yInput.setWillSnap( true );
	std::cout << "Player has spawned" << std::endl;
}

void Player::simulateAI( unsigned long millisecondsToSimulate, AssetManager * )
{
	Vector2D movement = Vector2D{};
	movement.x() = _xInput.getValue() * getSpeed() * ( millisecondsToSimulate / 1000.0 ) * ANTI_NYOOM_COEFFICIENT;
	movement.y() = -_yInput.getValue() * getSpeed() * ( millisecondsToSimulate / 1000.0 ) * ANTI_NYOOM_COEFFICIENT;

	//	std::cout << _xInput.getValue() << std::endl;

	transform.position.x() += movement.x();
	transform.position.y() += movement.y();

	_xInput.updateGravity( millisecondsToSimulate );
	_yInput.updateGravity( millisecondsToSimulate );
}