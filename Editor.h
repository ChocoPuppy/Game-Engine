#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

class InputManager;
class Scene;
class Editor
{
	HWND _window;
	HMENU _menu;

public:
	Editor( LPCWSTR windowName );
	~Editor();

	void update( InputManager * input, Scene * scene );
};