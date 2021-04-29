#pragma once

#include "SDLBase.h"
#include <unordered_map>
#include <unordered_set>
#include "EventHandle.h"
#include "_ButtonEvent.h"

class InputManager
{
	friend int main();
	friend class GameEngine;
	InputManager();
	void updateAllButtonEvents();

	enum class ButtonState
	{
		UP,
		PRESSED,
		DOWN,
		RELEASED
	};

	mutable std::unordered_map<Button, ButtonState> _buttonStates;
	std::unordered_map<SDL_Scancode, Button> _keyBoundToButton;

	Event::SmartEvent::EventHandle<AnyButtonDownEvent> _AnyButtonDownEvent;
	Event::SmartEvent::EventHandle<AnyButtonPressedEvent> _AnyButtonPressedEvent;
	Event::SmartEvent::EventHandle<AnyButtonReleasedEvent> _AnyButtonReleasedEvent;

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