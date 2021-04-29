#pragma once
#include "ASmartEvent.h"
#include "Button.h"
//You probably want to include ButtonEvent.h instead of this. That includes the actual definition of InputManager itself, which is important since you're probably going to be using it.
class InputManager;
namespace
{
	using GenericButtonEvent = Event::SmartEvent::SmartEvent<InputManager *, Button>;
}

class AnyButtonDownEvent : public GenericButtonEvent
{};

class AnyButtonPressedEvent : public GenericButtonEvent
{};

class AnyButtonReleasedEvent :public GenericButtonEvent
{};
