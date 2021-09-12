#include "VirtualInputJoystick.h"
#include <Windows.h>
#include <functional>
class CreditsWindow
{
	HWND _dialogHandle;
	INT_PTR _windowClosedWithCode;
	std::function<INT_PTR( HWND, UINT, WPARAM, LPARAM )> _DialogProcFunction;
	INT_PTR CALLBACK _Dialog_Proc( HWND hwnd, UINT message, WPARAM wParam, LPARAM );
	void _closeWindow( INT_PTR closeCode ) { _windowClosedWithCode = closeCode; }
public:
	bool isDirty() const { return _windowClosedWithCode != -1; }
	CreditsWindow( HWND window );
	~CreditsWindow();
};