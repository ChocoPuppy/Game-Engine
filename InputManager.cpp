#include "InputManager.h"
#include "resource.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <SDL_syswm.h>
#include <string>
#include "SDLMain.h"
using namespace Event::SmartEvent;

InputManager::InputManager() : _buttonEvent()
{
	_regenerateButtonKeyPairings();
}

void InputManager::_updateInputs()
{
	SDL_Event checkEvent;
	while (SDL_PollEvent( &checkEvent ))
	{
		switch (checkEvent.type)
		{
		case SDL_SYSWMEVENT:
			switch (checkEvent.syswm.msg->msg.win.msg)
			{
			case WM_COMMAND:
				auto keyPressed = LOWORD( checkEvent.syswm.msg->msg.win.wParam );
				Button currentlySelectedButton = _getButtonBoundToSystemKey( keyPressed );
				if (currentlySelectedButton != Button::NONE)
				{
					_pushButton( currentlySelectedButton );
					_systemKeysToUnpressAtStartOfFrame.emplace( keyPressed );
				}
				break;
			}
			break;
		case SDL_QUIT:
			_pushButton( Button::QUIT );
			break;
		case SDL_KEYDOWN:
			if (checkEvent.key.state == SDL_PRESSED && _keyBoundToButton.find( checkEvent.key.keysym.scancode ) != _keyBoundToButton.cend())
			{
				Button currentlySelectedButton = _keyBoundToButton[checkEvent.key.keysym.scancode];
				_pushButton( currentlySelectedButton );
			}
		case SDL_KEYUP:
			if (checkEvent.key.state == SDL_RELEASED && _keyBoundToButton.find( checkEvent.key.keysym.scancode ) != _keyBoundToButton.cend())
			{
				Button currentlySelectedButton = _keyBoundToButton[checkEvent.key.keysym.scancode];
				_liftButton( currentlySelectedButton );
			}
		}
	}
}

void InputManager::_updateMouse()
{
	SDL_PumpEvents();
	Uint32 mouseStateMask = SDL_GetMouseState( &_currentMousePosition.x, &_currentMousePosition.y );
	for (Button mouseButton : ButtonHelper::mouseButtons())
	{
		unsigned int const maskForButton = _getMaskBoundToMouseButton( mouseButton );
		unsigned int const isMaskSet = mouseStateMask & maskForButton;
		bool const isButtonPressed = isMaskSet != 0;
		if (isButtonPressed)
			_pushButton( mouseButton );
		else
			_liftButton( mouseButton );
	}
}

void InputManager::_update()
{
	_unpressSystemKeys();
	_updateInputs();
	_updateMouse();
	//This is called at the end of the function instead of as pressed buttons are found so that all the other buttons are confirmed to be updated (for example, dual key combos like ctrl+v might not trigger depending on which key has been pressed first)
	_updateAllButtonEvents();
}

Button InputManager::_getButtonBoundToSystemKey( long systemButtonWord ) const
{
	bool const isKeyBoundToButton = _systemKeyBoundToButton.find( systemButtonWord ) != _systemKeyBoundToButton.cend();
	return ( isKeyBoundToButton ) ? _systemKeyBoundToButton.at( systemButtonWord ) : Button::NONE;
}

unsigned int InputManager::_getMaskBoundToMouseButton( Button mouseButton ) const
{
	switch (mouseButton)
	{
	case Button::LEFT_MOUSE:
		return SDL_BUTTON_LMASK;
	case Button::MIDDLE_MOUSE:
		return SDL_BUTTON_MMASK;
	case Button::RIGHT_MOUSE:
		return SDL_BUTTON_RMASK;
	default:
		return 0;
	}
}

InputManager::_ButtonState InputManager::_checkButton( Button button ) const
{
	if (_buttonStates.find( button ) == _buttonStates.cend())
	{
		_buttonStates.emplace( button, _ButtonStatus{ _ButtonState::UP } );
	}
	return _buttonStates.at( button ).state;
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
	//	if (_canButtonBeUpdated( button ))
	//	{
	//		_buttonStates[button].lastUpdatedAtMillisecond = SDL::getTicks();

	switch (_checkButton( button ))
	{
		__fallthrough;
	case _ButtonState::UP:
	case _ButtonState::RELEASED:
		_buttonStates.at( button ).state = _ButtonState::PRESSED;
		break;
	case _ButtonState::PRESSED:
		_buttonStates.at( button ).state = _ButtonState::DOWN;
		break;
	case _ButtonState::DOWN:
		break;
	}
	//	}
}

void InputManager::_liftButton( Button button )
{
	//	if (_canButtonBeUpdated( button ))
	//	{
	//		_buttonStates[button].lastUpdatedAtMillisecond = SDL::getTicks();
	switch (_checkButton( button ))
	{
		//If pressed or down, set to release. The fallthrough tag just tells the compiler to not complain about the lack of a break on the first case.
		__fallthrough;
	case _ButtonState::PRESSED:
	case _ButtonState::DOWN:
		_buttonStates.at( button ).state = _ButtonState::RELEASED;
		break;
	case _ButtonState::RELEASED:
		_buttonStates.at( button ).state = _ButtonState::UP;
		break;
	case _ButtonState::UP:
		break;
	}
	//	}
}

void InputManager::_regenerateButtonKeyPairings()
{
	_keyBoundToButton.clear();
	_keyBoundToButton.emplace( SDL_SCANCODE_W, Button::UP );
	_keyBoundToButton.emplace( SDL_SCANCODE_S, Button::DOWN );
	_keyBoundToButton.emplace( SDL_SCANCODE_A, Button::LEFT );
	_keyBoundToButton.emplace( SDL_SCANCODE_D, Button::RIGHT );
	_keyBoundToButton.emplace( SDL_SCANCODE_LSHIFT, Button::SPRINT );
	_systemKeyBoundToButton.emplace( ID_FILE_EXIT, Button::QUIT );
	_systemKeyBoundToButton.emplace( ID_SPEED_INCREASE, Button::DEBUG_INCREASE_SPEED );
	_systemKeyBoundToButton.emplace( ID_SPEED_DECREASE, Button::DEBUG_DECREASE_SPEED );
	_systemKeyBoundToButton.emplace( ID_PLAYER_TELEPORTTO0, Button::DEBUG_TELEPORT_TO_00 );
	_systemKeyBoundToButton.emplace( ID_CREDITS_DEVELOPER, Button::SHOW_CREDITS );
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

Vector2D InputManager::getMousePosition() const
{
	return Vector2D( _currentMousePosition.x, _currentMousePosition.y );
}

void InputManager::_unpressSystemKeys()
{
	while (!_systemKeysToUnpressAtStartOfFrame.empty())
	{
		long const keyToUnpress = _systemKeysToUnpressAtStartOfFrame.top();
		Button const buttonToUnpress = _getButtonBoundToSystemKey( keyToUnpress );
		_liftButton( buttonToUnpress );
		_systemKeysToUnpressAtStartOfFrame.pop();
	}
}