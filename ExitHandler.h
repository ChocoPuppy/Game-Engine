#pragma once
#include <SmartEvent/ASmartObserver.h>
#include "ButtonEvent.h"
class ExitHandler : Event::SmartEvent::ASmartObserver<ButtonReleasedEvent>
{
	virtual void update( InputManager * manager, const Button button ) override;
};