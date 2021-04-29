#pragma once
#include "ASmartObserver.h"
#include "ButtonEvent.h"
class ExitHandler : Event::SmartEvent::ASmartObserver<AnyButtonPressedEvent>
{
	virtual void update( InputManager * manager, const Button button ) override;

public:
	ExitHandler();
};