#pragma once
#include "InputManager.h"
#include "ISmartObserver.h"
class ExitHandler : Event::SmartEvent::ASmartObserver<ButtonPressedEvent>
{
	virtual void update( InputManager * manager, const Button button ) override;
};