#include "InputOld.h"
Input::Input()
{
	_keyBoundToButton.emplace( SDL_SCANCODE_W, Button::UP );
	_keyBoundToButton.emplace( SDL_SCANCODE_S, Button::DOWN );
	_keyBoundToButton.emplace( SDL_SCANCODE_A, Button::LEFT );
	_keyBoundToButton.emplace( SDL_SCANCODE_D, Button::RIGHT );
}

void Input::getInput()
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
				_pushButton( currentlySelectedButton );
				hasBeenPushedThisFrame.emplace( currentlySelectedButton );
			}
		}
	}
	_liftUnpressedButtons( hasBeenPushedThisFrame );
}

bool Input::isButtonDown( Button type ) const
{
	if (_buttonStates.find( type ) == _buttonStates.cend())
	{
		_buttonStates[type] = ButtonState::UP;
	}

	switch (_buttonStates[type])
	{
	case ButtonState::DOWN:
		return true;
	case ButtonState::PRESSED:
		return true;
	default:
		return false;
	}
}

void Input::_pushButton( Button type )
{
	ButtonState state = _buttonStates[type];
	switch (state)
	{
		[[__fallthrough]]
	case ButtonState::UP:
	case ButtonState::RELEASED:
		_buttonStates[type] = ButtonState::PRESSED;
		break;
	case ButtonState::PRESSED:
		_buttonStates[type] = ButtonState::DOWN;
		break;
	default:
		break;
	}
}

void Input::_liftUnpressedButtons( std::unordered_set<Button> const & pressedButtons )
{
	for (auto & button : _buttonStates)
	{
		//If the button hasn't been pushed this frame.
		if (pressedButtons.find( button.first ) == pressedButtons.cend())
		{
			switch (button.second)
			{
				//If pressed or down, set to release. The fallthrough just tells the compiler to not complain about the lack of a break on the first case.
				[[__fallthrough]]
			case ButtonState::PRESSED:
			case ButtonState::DOWN:
				button.second = ButtonState::RELEASED;
				break;
			case ButtonState::RELEASED:
				button.second = ButtonState::UP;
				break;
			default:
				break;
			}
		}
	}
}