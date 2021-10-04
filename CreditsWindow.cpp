#include "CreditsWindow.h"
#include "resource.h"
INT_PTR CALLBACK CreditsWindow::_Dialog_Proc( HWND hwnd, UINT message, WPARAM wParam, LPARAM )
{
	switch (message)
	{
	case WM_INITDIALOG:
		_dialogHandle = hwnd;
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD( wParam ))
		{
		case IDOK:
			_closeWindow( IDOK );
			break;
		}
		break;
	case WM_CLOSE:
		_closeWindow( WM_CLOSE );
	default:
		return FALSE;
	}
	return TRUE;
}

CreditsWindow::CreditsWindow( HWND ) : _windowClosedWithCode( -1 )
{
	using namespace std::placeholders;
	//	auto contextBoundDialogProc = ;
//	_DialogProcFunction = std::function<INT_PTR( HWND, UINT, WPARAM, LPARAM )>( std::bind( _Dialog_Proc, this, _1, _2, _3, _4 ) );
//	auto contextBoundDialogProcPointer = _DialogProcFunction.target< INT_PTR( HWND, UINT, WPARAM, LPARAM )>();
//	DialogBox( GetModuleHandle( 0 ), MAKEINTRESOURCE( IDD_DIALOG1 ), window, (DLGPROC)contextBoundDialogProcPointer );
}

CreditsWindow::~CreditsWindow()
{
	EndDialog( _dialogHandle, IDOK );
}