#pragma once
#include "Event/SmartEvent/ASmartObserver.h"
class ExitHandler : Event::SmartEvent::ASmartObserver<ButtonPressedEvent>
{
	virtual void update( InputManager * manager, const Button button ) override;
};