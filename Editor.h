#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <string>
#include "VirtualInputJoystick.h"
class InputManager;
class Scene;
class CreditsWindow;
class Editor
{
	HWND _window;
	HMENU _menu;
	CreditsWindow * _creditsWindow;
	VirtualInputJoystick<Button::SHOW_CREDITS> _showCreditsInputHandler;
public:
	Editor( LPCWSTR windowName );
	~Editor();

	void update( InputManager * input, Scene * scene );
};
