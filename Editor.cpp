#include "Editor.h"

#include "SDLMain.h"
#include <iostream>
#include "resource.h"
#include "InputManager.h"
#include "Scene.h"
#include "CreditsWindow.h"

Editor::Editor( LPCWSTR windowName ) : _creditsWindow( nullptr ), _showCreditsInputHandler( 1 )
{
	_window = FindWindow( NULL, windowName );
	if (_window == NULL)
	{
		//		std::cout << "Failed to find window. Window name: " << windowName << std::endl;
		exit( 1 );
	}

	_menu = LoadMenu( GetModuleHandle( 0 ), MAKEINTRESOURCE( IDR_MENU1 ) );
	if (_menu == NULL)
	{
		std::cout << "Failed to create menu." << std::endl;
		exit( 1 );
	}
	BOOL setMenuResult = SetMenu( _window, _menu );
	if (setMenuResult == 0)
	{
		std::cout << "Failed to set menu" << std::endl;
		exit( 1 );
	}

	Uint8 eventStateResult = SDL_EventState( SDL_SYSWMEVENT, SDL_ENABLE );
	Uint8 eventStateSuccess = SDL_DISABLE;
	if (eventStateResult != eventStateSuccess)
	{
		std::cout << "Failed to enable windows event state" << std::endl;
		exit( 1 );
	}
}

Editor::~Editor()
{}

void Editor::update( InputManager *, Scene * )
{
	bool isCreditsWindowOpen = _creditsWindow != nullptr;
	bool shouldOpenCreditsWindow = _showCreditsInputHandler.getValue() > 0;
	if (isCreditsWindowOpen && _creditsWindow->isDirty())
	{
		delete( _creditsWindow );
	}
	else if (!isCreditsWindowOpen && shouldOpenCreditsWindow)
	{
		_creditsWindow = new CreditsWindow( _window );
	}
}