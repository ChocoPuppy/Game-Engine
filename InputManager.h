#pragma once
#include "ASmartEvent.h"
#include "Button.h"
#include "SDLBase.h"
#include <unordered_map>
#include <unordered_set>
#include "ButtonEvent.h"
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

	ButtonDownEvent * _buttonDownEvent;
	ButtonPressedEvent * _buttonPressedEvent;
	ButtonReleasedEvent * _buttonReleasedEvent;

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