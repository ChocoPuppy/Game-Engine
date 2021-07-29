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

double Joystick::clampToMinMaxSize( double number )
{
	return CustomMaths::clamp( number, MAX_SIZE, MIN_SIZE );
}

void Joystick::setRawValue( double value )
{
	_value = clampToMinMaxSize( value );
}

void Joystick::pushValue( double push )
{
	setRawValue( getRawValue() + push );
}

void Joystick::updateGravity( unsigned long )
{
	double value = getRawValue();
	double gravity = getGravity();//* millisecondsToSimulate

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

Joystick::Joystick() : _value( 0 ), _dead( 0 )
{}

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

bool Joystick::isValuePositive() const
{
	return getRawValue() > 0;
}

bool Joystick::isValueNegative() const
{
	return getRawValue() < 0;
}

double Joystick::getDead() const
{
	return _dead;
}

double Joystick::getGravity() const
{
	return _gravity;
}

void Joystick::setDead( double value )
{
	_dead = value;
}

void Joystick::setGravity( double value )
{
	_gravity = value;
}