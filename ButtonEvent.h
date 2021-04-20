#pragma once
#include "ASmartEvent.h"
#include "Button.h"
class InputManager;

class ButtonEvent : public Event::SmartEvent::ASmartEvent<InputManager *, Button>
{
	friend InputManager;
	using Event::SmartEvent::ASmartEvent<InputManager *, Button>::update;
};

class ButtonDownEvent final : public ButtonEvent
{};

class ButtonPressedEvent final : public ButtonEvent
{};

class ButtonReleasedEvent final :public ButtonEvent
{};
