#pragma once
#include <SmartEvent/ASmartObserver.h>
#include "ButtonEvent.h"
class ExitHandler : Event::SmartEvent::ASmartObserver<ButtonEvent>
{
	virtual void update( InputManager * ) override;
};