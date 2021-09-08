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

	double _speed;
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

	virtual void render( unsigned long millisecondsToSimulate, AssetManager * assets, RenderEngine * renderer ) override;

	virtual bool isFacingLeft() const override;

	double getSpeed() { return _speed; }
};