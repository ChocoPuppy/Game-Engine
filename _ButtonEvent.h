#pragma once
#include "Button.h"
#include <Event/SmartEvent/ASmartEvent.h>

class InputManager;

using genericButtonEvent = Event::SmartEvent::SmartEvent<InputManager *, Button>;

class ButtonDownEvent : genericButtonEvent {};

class ButtonPressedEvent : genericButtonEvent {};

class ButtonReleasedEvent : genericButtonEvent {};