#include "Joystick.h"
#include "CustomMaths.h"
double Joystick::_spaceFromMax() const
{
	return MAX_SIZE - getRawValue();
}

double Joystick::_spaceFromMin() const
{
	return MIN_SIZE - getRawValue();
}

double Joystick::_clampToMinMaxSize( double number ) const
{
	return CustomMaths::clamp( number, MAX_SIZE, MIN_SIZE );
}

void Joystick::setRawValue( double value )
{
	_value = _clampToMinMaxSize( value );
}

void Joystick::pushValue( double push )
{
	setRawValue( getRawValue() + push );
}

void Joystick::updateGravity()
{
	double value = getRawValue();
	double gravity = getGravity();

	if (value > 0)
		if (( value - gravity ) < 0)
			_value = 0;
		else
			pushValue( -gravity );
	else if (value < 0)
		if (( value + gravity ) > 0)
			_value = 0;
		else
			pushValue( gravity );
	//If the value is 0, gravity doesn't need to do anything.
	else if (value == 0)
		return;
}

double Joystick::getValue() const
{
	double value = getRawValue();
	if (( value < getDead() ) && ( value > -getDead() ))
		return 0;
	else
		return value;
}

double Joystick::getRawValue() const
{
	return _value;
}

double Joystick::getDead() const
{
	return _dead;
}

double Joystick::getGravity() const
{
	return _gravity;
}

bool Joystick::getWillSnap() const
{
	return _willSnap;
}

void Joystick::setDead( double value )
{
	_dead = value;
}

void Joystick::setGravity( double value )
{
	_gravity = value;
}

void Joystick::setWillSnap( bool value )
{
	_willSnap = value;
}