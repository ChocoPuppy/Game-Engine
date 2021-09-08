#include "Player.h"
#include <iostream>
void Player::_pushState( _State state, AssetManager * assets )
{
	_exitState( _state.top(), assets );

	_state.push( state );
	_enterState( state, assets );
}

void Player::_popState( AssetManager * assets )
{
	_exitState( _state.top(), assets );

	_state.pop();
	_enterState( _state.top(), assets );
}

void Player::_enterState( _State state, AssetManager * )
{
	switch (state)
	{
	case _State::IDLE:
		_textureID = "Texture.Player.Idle";
		break;
	case _State::WALKING:
		_textureID = "Texture.Player.Walking";
		_speed = 1;
		break;
	case _State::RUNNING:
		_textureID = "Texture.Player.Running";
		_speed = 1.5;
		std::cout << "Player is running!" << std::endl;
		break;
	}
}
void Player::_exitState( _State state, AssetManager * )
{
	switch (state)
	{
	case _State::IDLE:
		break;
	case _State::WALKING:
		break;
	case _State::RUNNING:
		std::cout << "Player has stopped running!" << std::endl;
		break;
	}
}
void Player::_simulateState( unsigned long, Vector2D movement, AssetManager * assets )
{
	switch (_state.top())
	{
	case _State::IDLE:
		if (_sprintInput.getValue() > 0 && movement.magnitude() > 0)
		{
			_pushState( _State::RUNNING, assets );
		}
		else if (movement.magnitude() > 0)
		{
			_pushState( _State::WALKING, assets );
		}
		break;
	case _State::WALKING:
		if (movement.magnitude() == 0)
		{
			_popState( assets );
		}
		else if (_sprintInput.getValue() > 0)
		{
			_pushState( _State::RUNNING, assets );
		}
		break;
	case _State::RUNNING:
		if (movement.magnitude() == 0)
		{
			_popState( assets );
		}
		else if (_sprintInput.getValue() == 0)
		{
			_popState( assets );
		}
		break;
	}
}
Player::Player( std::string ID ) : AnimatedGameObject( ID, "Texture.Player.Idle" ), _xInput( 0.9 ), _yInput( 0.9 ), _sprintInput( 1 ), _speed( 1 )
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
	_sprintInput.setGravity( 1 );

	_state.push( _State::IDLE );
	std::cout << "Player has spawned" << std::endl;
}

void Player::simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets )
{
	Vector2D movement = Vector2D{};
	movement.x = _xInput.getValue();
	movement.y = -_yInput.getValue();
	_simulateState( millisecondsToSimulate, movement, assets );
	//	std::cout << _xInput.getValue() << std::endl;
		//	std::cout << movement.magnitude() << std::endl;
	constexpr double ANTI_NYOOM_COEFFICIENT = 0.000000002;
	Vector2D pushVelocity = movement.normalize() * (float)getSpeed() * (float)ANTI_NYOOM_COEFFICIENT * millisecondsToSimulate;
	push( pushVelocity );
	//	std::cout << movement.x << std::endl;
	_xInput.updateGravity( millisecondsToSimulate );
	_yInput.updateGravity( millisecondsToSimulate );
	_sprintInput.updateGravity( millisecondsToSimulate );
}