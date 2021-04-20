#pragma once
#include "InputManager.h"
#include "ISmartObserver.h"
class ExitHandler : Event::SmartEvent::ASmartObserver<ButtonPressedEvent, InputManager *, const Button>
{
	virtual void update( InputManager * manager, const Button button ) override;
};