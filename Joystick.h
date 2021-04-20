#pragma once
class Joystick
{
	double _value;
	void update( double push );

	double getValue();
};