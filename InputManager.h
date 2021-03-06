#pragma once
#include "Button.h"
#include "Framerate.h"
#include "SDLBase.h"
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <stack>
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
		//		unsigned long lastUpdatedAtMillisecond;
	};

	//	static constexpr unsigned long minimumMillisecondsBetweenButtonUpdates = Framerate::minimumFrameTime;

	mutable std::unordered_map<Button, _ButtonStatus> _buttonStates;
	std::unordered_map<SDL_Scancode, Button> _keyBoundToButton;
	std::unordered_map<long, Button> _systemKeyBoundToButton;
	std::stack<long> _systemKeysToUnpressAtStartOfFrame;

	EventHandle<ButtonEvent> _buttonEvent;
	//	EventHandle<ButtonPressedEvent> _buttonPressedEvent;
	//	EventHandle<ButtonReleasedEvent> _buttonReleasedEvent;

	InputManager();

	void _regenerateButtonKeyPairings();
	void _updateAllButtonEvents();
	void _unpressSystemKeys();

	//	bool _canButtonBeUpdated( Button button ) const;

	void _pushButton( Button button );
	void _liftButton( Button button );

	void _updateInputs();
	void _update();

	Button _getButtonBoundToSystemKey( long systemButtonWord ) const;

	_ButtonState _checkButton( Button button ) const;
	bool _isButtonState( Button button, _ButtonState state ) const;
public:
	Button getButtonBoundToKey( SDL_Scancode key ) const;

	bool isButtonDown( Button button ) const;
	bool isButtonPressed( Button button ) const;
	bool isButtonDownOrPressed( Button button ) const;
	bool isButtonReleased( Button button ) const;
};