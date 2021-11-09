#include "AnimatedGameObject.h"
#include "VirtualInputJoystick.h"
#include <stack>
class Player : public AnimatedGameObject
{
	enum class _State
	{
		IDLE,
		WALKING,
		RUNNING
	};

	VirtualInputJoystick<Button::RIGHT, Button::LEFT> _xInput;
	VirtualInputJoystick<Button::UP, Button::DOWN> _yInput;
	VirtualInputJoystick<Button::SPRINT> _sprintInput;
	VirtualInputJoystick<Button::DEBUG_INCREASE_SPEED, Button::DEBUG_DECREASE_SPEED> _debugSpeedInput;
	VirtualInputJoystick<Button::DEBUG_TELEPORT_TO_00> _debugTeleportInput;

	double _baseSpeed;
	double _additiveSpeed;
	bool _lastMovedLeftwards;
	std::stack<_State> _state;

	void _pushState( _State state, AssetManager * assets );
	void _popState( AssetManager * assets );

	void _enterState( _State state, AssetManager * assets );
	void _exitState( _State state, AssetManager * assets );

	void _simulateState( unsigned long millisecondsToSimulate, Vector2D movement, AssetManager * assets );
public:
	Player( std::string ID );

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) override;

	virtual bool isFacingLeft() const override;

	double getBaseSpeed() { return _baseSpeed; }
	double getAdditiveSpeed() { return _additiveSpeed; }
	double getTotalSpeed() { return _baseSpeed + _additiveSpeed; }

	void AddToAdditiveSpeed( double amount ) { _additiveSpeed += amount; }
};