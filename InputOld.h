#pragma once
#include <unordered_map>
#include <unordered_set>
#include "SDLBase.h"

#include "Button.h"
class Input {
public:
	Input();
//	~Input();

	void getInput();
	bool isButtonDown(Button type) const;

private:

	enum class ButtonState {
		UP,
		PRESSED,
		DOWN,
		RELEASED
	};

	mutable std::unordered_map<Button, ButtonState> _buttonStates;
	std::unordered_map<SDL_Scancode, Button> _keyBoundToButton;
	
	void _pushButton(Button type);
	void _liftUnpressedButtons( std::unordered_set<Button> const & pressedButtons );

};