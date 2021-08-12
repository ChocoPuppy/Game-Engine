#include "AnimatedGameObject.h"
#include "VirtualInputJoystick.h"
class Player : public AnimatedGameObject
{
	static constexpr double ANTI_NYOOM_COEFFICIENT = 0.000000001;

	VirtualInputJoystick<Button::RIGHT, Button::LEFT> _xInput;
	VirtualInputJoystick<Button::UP, Button::DOWN> _yInput;

	double _speed;
public:
	Player( std::string ID );

	virtual void simulateAI( unsigned long millisecondsToSimulate, AssetManager * assets ) override;

	double getSpeed() { return _speed; }
};