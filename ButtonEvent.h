#pragma once
#include <SmartEvent/SmartEvent.h>
#include "Button.h"
class InputManager;

//using ButtonEvent =

class ButtonEvent final : public Event::SmartEvent::SmartEvent<InputManager *>
{};

/*class ButtonPressedEvent final : public ButtonEvent
{};

class ButtonReleasedEvent final : public ButtonEvent
{};*/
