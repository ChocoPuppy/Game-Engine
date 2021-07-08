#pragma once
#include "Button.h"
#include "SDLBase.h"
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "ButtonEvent.h"
#include "Event/SmartEvent/EventHandle.h"

namespace
{
	using Event::SmartEvent::EventHandle;
}
class InputManager
{
	friend int main();
	friend class GameEngine;

	InputManager();
	void updateAllButtonEvents();
public:

private:

	enum class ButtonState
	{
		UP,
		PRESSED,
		DOWN,
		RELEASED
	};

	mutable std::unordered_map<Button, ButtonState> _buttonStates;
	std::unordered_map<SDL_Scancode, Button> _keyBoundToButton;

	EventHandle<ButtonDownEvent> _buttonDownEvent;
	EventHandle<ButtonPressedEvent> _buttonPressedEvent;
	EventHandle<ButtonReleasedEvent> _buttonReleasedEvent;

	void pushButton( Button button );
	void liftButton( Button button );

	void liftUnpressedButtons( std::unordered_set<Button> pressedButtons );

	void updateInputs();

	ButtonState checkButton( Button button ) const;
	bool isButtonState( Button button, ButtonState state ) const;
public:
	bool isButtonDown( Button button ) const;
	bool isButtonPressed( Button button ) const;
	bool isButtonReleased( Button button ) const;
};