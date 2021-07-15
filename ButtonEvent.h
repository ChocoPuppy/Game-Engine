#pragma once
#include "Button.h"
#include <Event/SmartEvent/ASmartEvent.h>
class InputManager;

using ButtonEvent = Event::SmartEvent::SmartEvent<InputManager *, Button>;

class ButtonDownEvent final : public ButtonEvent
{};

class ButtonPressedEvent final : public ButtonEvent
{};

class ButtonReleasedEvent final :public ButtonEvent
{};
