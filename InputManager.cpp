#include "InputManager.h"

using namespace Event::SmartEvent;

InputManager::InputManager() : _buttonDownEvent(), _buttonPressedEvent(), _buttonReleasedEvent()
{
	_keyBoundToButton.emplace( SDL_SCANCODE_W, Button::UP );
	_keyBoundToButton.emplace( SDL_SCANCODE_S, Button::DOWN );
	_keyBoundToButton.emplace( SDL_SCANCODE_A, Button::LEFT );
	_keyBoundToButton.emplace( SDL_SCANCODE_D, Button::RIGHT );
}

void InputManager::updateInputs()
{
	std::unordered_set<Button> hasBeenPushedThisFrame;
	Button currentlySelectedButton;
	SDL_Event checkEvent;
	while (SDL_PollEvent( &checkEvent ))
	{
		switch (checkEvent.type)
		{
		case SDL_QUIT:
			_buttonStates[Button::QUIT] = ButtonState::DOWN;
			hasBeenPushedThisFrame.emplace( Button::QUIT );
			break;
		case SDL_KEYDOWN:
			if (_keyBoundToButton.find( checkEvent.key.keysym.scancode ) != _keyBoundToButton.cend())
			{
				currentlySelectedButton = _keyBoundToButton[checkEvent.key.keysym.scancode];
				pushButton( currentlySelectedButton );
				hasBeenPushedThisFrame.emplace( currentlySelectedButton );
			}
		}
	}
	liftUnpressedButtons( hasBeenPushedThisFrame );
	//This is called at the end of the function instead of as pressed buttons are found so that all the other buttons are confirmed to be updated (for example, dual key combos like ctrl+v might not trigger depending on which key has been pressed first)
	updateAllButtonEvents();
}

InputManager::ButtonState InputManager::checkButton( Button button ) const
{
	if (_buttonStates.find( button ) == _buttonStates.cend())
	{
		_buttonStates[button] = ButtonState::UP;
	}
	return _buttonStates[button];
}

bool InputManager::isButtonState( Button button, ButtonState state ) const
{
	return checkButton( button ) == state;
}

void InputManager::pushButton( Button button )
{
	ButtonState state = _buttonStates[button];
	switch (state)
	{
		[[__fallthrough]]
	case ButtonState::UP:
	case ButtonState::RELEASED:
		_buttonStates[button] = ButtonState::PRESSED;
		break;
	case ButtonState::PRESSED:
		_buttonStates[button] = ButtonState::DOWN;
		break;
	default:
		break;
	}
}

void InputManager::liftButton( Button button )
{
	switch (_buttonStates[button])
	{
		//If pressed or down, set to release. The fallthrough tag just tells the compiler to not complain about the lack of a break on the first case.
		[[__fallthrough]]
	case ButtonState::PRESSED:
	case ButtonState::DOWN:
		_buttonStates[button] = ButtonState::RELEASED;
		break;
	case ButtonState::RELEASED:
		_buttonStates[button] = ButtonState::UP;
		break;
	default:
		break;
	}
}

void InputManager::liftUnpressedButtons( std::unordered_set<Button> pressedButtons )
{
	for (auto & button : _buttonStates)
	{
		//If the button hasn't been pushed this frame, Lift it.
		if (pressedButtons.find( button.first ) == pressedButtons.cend())
		{
			liftButton( button.first );
		}
	}
}

void InputManager::updateAllButtonEvents()
{
	for (auto & buttonStatePair : _buttonStates)
	{
		//	std::cout << "getting to update events." << std::endl;

		Button button = buttonStatePair.first;
		if (isButtonDown( button ))
		{
			std::cout << ButtonHelper::buttonToString( button ) << " is down." << std::endl;
			_buttonDownEvent.update( this, button );
		}
		if (isButtonPressed( button ))
		{
			std::cout << ButtonHelper::buttonToString( button ) << " is pressed." << std::endl;
			_buttonPressedEvent.update( this, button );
		}
		if (isButtonReleased( button ))
		{
			std::cout << ButtonHelper::buttonToString( button ) << " has been released." << std::endl;
			_buttonReleasedEvent.update( this, button );
		}
	}
}

bool InputManager::isButtonDown( Button button ) const
{
	return isButtonState( button, ButtonState::DOWN ) || isButtonState( button, ButtonState::PRESSED );
}

bool InputManager::isButtonPressed( Button button ) const
{
	return isButtonState( button, ButtonState::PRESSED );
}

bool InputManager::isButtonReleased( Button button ) const
{
	return isButtonState( button, ButtonState::RELEASED );
}