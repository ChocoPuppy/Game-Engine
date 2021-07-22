#pragma once
#include "Joystick.h"
#include <SmartEvent/ASmartObserver.h>
#include "ButtonEvent.h"

template<Button positiveButton, Button negativeButton>
class VirtualInputJoystick :
	public Joystick
{
	struct _VirtualInputJoystickObserver : Event::SmartEvent::ASmartObserver<ButtonDownEvent>
	{
		VirtualInputJoystick & _parent;
		_VirtualInputJoystickObserver( VirtualInputJoystick & parent ) : _parent( parent ) {}

		virtual void update( InputManager *, Button input ) override
		{
			switch (input)
			{
			case positiveButton:
				_parent._pushOnInput( true );
			case negativeButton:
				_parent._pushOnInput( false );
			}
		}
	};

	_VirtualInputJoystickObserver inputObserver;

	double _pushForce;
	double _willSnap;

	VirtualInputJoystick( double pushForce ) : inputObserver( *this ), _pushForce( pushForce ) {}

	void _pushOnInput( bool positivePush )
	{
		double toPush = ( positivePush ) ? getPushForce() : -getPushForce();
		if (getWillSnap())
			_snap( positivePush );
		pushValue( toPush );
	}

	void _snap( bool pushIsPositive )
	{
		bool pushingAgainstPositive = isValuePositive() && !pushIsPositive;
		bool pushingAgainstNegative = isValueNegative() && pushIsPositive;
		if (pushingAgainstPositive || pushingAgainstNegative)
			setRawValue( 0 );
	}
protected:
	void setPushForce( double value ) { _pushForce = clampToMinMaxSize( value ); }
public:
	using Joystick::updateGravity;

	void setWillSnap( bool value ) { _willSnap = value; }

	double getPushForce() const { return _pushForce; }
	bool getWillSnap() const { return _willSnap; }
};
