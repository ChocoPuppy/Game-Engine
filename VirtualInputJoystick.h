#pragma once
#include "Joystick.h"
#include <SmartEvent/ASmartObserver.h>
#include "ButtonEvent.h"

template<Button positiveButton, Button negativeButton>
class VirtualInputJoystick :
	public Joystick
{
	struct _VirtualInputJoystickObserver : Event::SmartEvent::ASmartObserver<ButtonPressedEvent>, Event::SmartEvent::ASmartObserver<ButtonDownEvent>
	{
		VirtualInputJoystick & _parent;
		_VirtualInputJoystickObserver( VirtualInputJoystick & parent ) : _parent( parent ) {}

		virtual void update( InputManager *, Button input ) override
		{
			switch (input)
			{
			case positiveButton:
				_parent._inputPush( true );
				break;
			case negativeButton:
				_parent._inputPush( false );
				break;
			}
		}
	};

	_VirtualInputJoystickObserver inputObserver;

	double _pushForce;
	double _willSnap;

	void _inputPush( bool positivePush )
	{
		if (getWillSnap())
			_snap( positivePush );
		pushValue( getPushForce( positivePush ) );
	}

	void _snap( bool pushIsPositive )
	{
		bool pushingAgainstPositive = isValuePositive() && !pushIsPositive;
		bool pushingAgainstNegative = isValueNegative() && pushIsPositive;
		if (pushingAgainstPositive || pushingAgainstNegative)
		{
			//			std::cout << "Snap!" << std::endl;
			setRawValue( 0 );
		}
	}
protected:
	void setPushForce( double value ) { _pushForce = clampToMinMaxSize( value ); }
public:
	using Joystick::updateGravity;

	VirtualInputJoystick( double pushForce ) : inputObserver( *this ), _pushForce( pushForce ) {}

	void setWillSnap( bool value ) { _willSnap = value; }

	double getPushForce( bool positivePush = true ) const { return ( positivePush ) ? _pushForce : -_pushForce; }
	bool getWillSnap() const { return _willSnap; }
};
