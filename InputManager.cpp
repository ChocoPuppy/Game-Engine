#include "InputManager.h"
#include <string>
#include "SDLMain.h"
using namespace Event::SmartEvent;

InputManager::InputManager() : _buttonEvent()
{
	_keyBoundToButton.emplace( SDL_SCANCODE_W, Button::UP );
	_keyBoundToButton.emplace( SDL_SCANCODE_S, Button::DOWN );
	_keyBoundToButton.emplace( SDL_SCANCODE_A, Button::LEFT );
	_keyBoundToButton.emplace( SDL_SCANCODE_D, Button::RIGHT );
}

void InputManager::_updateInputs()
{
	std::unordered_set<Button> hasBeenPushedThisFrame;
	Button currentlySelectedButton;
	SDL_Event checkEvent;
	while (SDL_PollEvent( &checkEvent ))
	{
		switch (checkEvent.type)
		{
		case SDL_QUIT:
			_pushButton( Button::QUIT );
			hasBeenPushedThisFrame.emplace( Button::QUIT );
			break;
		case SDL_KEYDOWN:
			Button button = getButtonBoundToKey( checkEvent.key.keysym.scancode );
			if (button != Button::NONE)
			{
				_pushButton( button );
				hasBeenPushedThisFrame.emplace( button );
			}
		}
	}
	_liftUnpressedButtons( hasBeenPushedThisFrame );
	//This is called at the end of the function instead of as pressed buttons are found so that all the other buttons are confirmed to be updated (for example, dual key combos like ctrl+v might not trigger depending on which key has been pressed first)
	_updateAllButtonEvents();
}

InputManager::_ButtonState InputManager::_checkButton( Button button ) const
{
	if (_buttonStates.find( button ) == _buttonStates.cend())
	{
		_buttonStates[button].state = _ButtonState::UP;
	}
	return _buttonStates[button].state;
}

bool InputManager::_isButtonState( Button button, _ButtonState state ) const
{
	return _checkButton( button ) == state;
}

Button InputManager::getButtonBoundToKey( SDL_Scancode key ) const
{
	Button button = Button::NONE;
	if (_keyBoundToButton.find( key ) != _keyBoundToButton.cend())
	{
		button = _keyBoundToButton.at( key );
	}
	return button;
}

void InputManager::_pushButton( Button button )
{
	_ButtonState & buttonState = _buttonStates[button].state;
	//	if (_canButtonBeUpdated( button ))
	//	{
	//		_buttonStates[button].lastUpdatedAtMillisecond = SDL::getTicks();
	switch (buttonState)
	{
		[[__fallthrough]]
	case _ButtonState::UP:
	case _ButtonState::RELEASED:
		buttonState = _ButtonState::PRESSED;
		break;
	case _ButtonState::PRESSED:
		buttonState = _ButtonState::DOWN;
		break;
	default:
		break;
	}
	//	}
}

void InputManager::_liftButton( Button button )
{
	_ButtonState & buttonState = _buttonStates[button].state;
	//	if (_canButtonBeUpdated( button ))
	//	{
	//		_buttonStates[button].lastUpdatedAtMillisecond = SDL::getTicks();
	switch (buttonState)
	{
		//If pressed or down, set to release. The fallthrough tag just tells the compiler to not complain about the lack of a break on the first case.
		[[__fallthrough]]
	case _ButtonState::PRESSED:
	case _ButtonState::DOWN:
		buttonState = _ButtonState::RELEASED;
		break;
	case _ButtonState::RELEASED:
		buttonState = _ButtonState::UP;
		break;
	default:
		break;
	}
	//	}
}

void InputManager::_liftUnpressedButtons( std::unordered_set<Button> pressedButtons )
{
	//Go through all currently tracked buttons (all buttons we're currently reading the states for, so all buttons that have actually been checked or pushed).
	for (auto & button : _buttonStates)
	{
		//If the button hasn't been pushed this frame, Lift it.
		if (pressedButtons.find( button.first ) == pressedButtons.cend())
		{
			_liftButton( button.first );
		}
	}
}

void InputManager::_updateAllButtonEvents()
{
	_buttonEvent.update( this );
}
//bool InputManager::_canButtonBeUpdated( Button button ) const
//{
	//	std::cout << _buttonStates[button].lastUpdatedAtMillisecond + minimumMillisecondsBetweenButtonUpdates << " vs " << SDL::getTicks() << std::endl;
//	return _buttonStates[button].lastUpdatedAtMillisecond + minimumMillisecondsBetweenButtonUpdates < SDL::getTicks();
//}
bool InputManager::isButtonDown( Button button ) const
{
	return _isButtonState( button, _ButtonState::DOWN );
}

bool InputManager::isButtonPressed( Button button ) const
{
	return _isButtonState( button, _ButtonState::PRESSED );
}

bool InputManager::isButtonDownOrPressed( Button button ) const
{
	return isButtonDown( button ) || isButtonPressed( button );
}

bool InputManager::isButtonReleased( Button button ) const
{
	return _isButtonState( button, _ButtonState::RELEASED );
}