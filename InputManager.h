#pragma once
#include "Button.h"
#include "Framerate.h"
#include "SDLBase.h"
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "ButtonEvent.h"
#include <SmartEvent/EventHandle.h>

namespace
{
	using Event::SmartEvent::EventHandle;
}
class InputManager
{
	friend int main();
	friend class GameEngine;

private:

	enum class _ButtonState
	{
		UP,
		PRESSED,
		DOWN,
		RELEASED
	};
	struct _ButtonStatus
	{
		_ButtonState state;
		unsigned long lastUpdatedAtMillisecond;
	};

	//	static constexpr unsigned long minimumMillisecondsBetweenButtonUpdates = Framerate::minimumFrameTime;

	mutable std::unordered_map<Button, _ButtonStatus> _buttonStates;
	std::unordered_map<SDL_Scancode, Button> _keyBoundToButton;

	EventHandle<ButtonEvent> _buttonEvent;
	//	EventHandle<ButtonPressedEvent> _buttonPressedEvent;
	//	EventHandle<ButtonReleasedEvent> _buttonReleasedEvent;

	InputManager();

	void _updateAllButtonEvents();

	//	bool _canButtonBeUpdated( Button button ) const;

	void _pushButton( Button button );
	void _liftButton( Button button );

	void _liftUnpressedButtons( std::unordered_set<Button> pressedButtons );

	void _updateInputs();

	_ButtonState _checkButton( Button button ) const;
	bool _isButtonState( Button button, _ButtonState state ) const;
public:
	bool isButtonDown( Button button ) const;
	bool isButtonPressed( Button button ) const;
	bool isButtonReleased( Button button ) const;
};