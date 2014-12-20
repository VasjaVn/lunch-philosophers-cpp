#include "stdafx.h"
#include "HandleMsgs.h"
#include "AboutDialog.h"
#include "SettingDialog.h"
#include "Lunch.h"
#include "LibraryDrawLunch.h"

//Global
DrawData g_drawData = { 0 };
HANDLE   g_hOut     = NULL;

/*
TimeoutDate g_tmData[COUNT_PHILOSOPHERS] = {   200,  400, 
										      1000, 3000, 
											   300,  300, 
											   400,  100, 
											  1500,  200  };
*/
/*****************************************************************************************/

void Cls_OnPaint( HWND hWnd )
{	
	PAINTSTRUCT ps;
	HDC	        hDC;
	
	hDC = BeginPaint(hWnd, &ps);

	DrawTable();
	DrawPlates();
	DrawForks();
	DrawChair();

	EndPaint(hWnd, &ps);
}


/*****************************************************************************************/

BOOL Cls_OnCreate( HWND hWnd, LPCREATESTRUCT lpCreateStruct )
{
	InitLibraryDrawLunch( hWnd );

	EnableMenuItem( GetMenu(hWnd), IDM_PAUSE, MF_DISABLED );
	EnableMenuItem( GetMenu(hWnd), IDM_RESUME, MF_DISABLED );
	EnableMenuItem( GetMenu(hWnd), IDM_STOP,  MF_DISABLED );

	EnableMenuItem( GetMenu(hWnd), IDM_FREE_CONSOLE,  MF_DISABLED );

	return TRUE;
}


/*****************************************************************************************/

void Cls_OnDestroy( HWND hWnd )
{
	DeinitLibraryDrawLunch( hWnd );

	PostQuitMessage(0);
}


/*****************************************************************************************/

void Cls_OnCommand( HWND hWnd,
				    int  id,
					HWND hWndCtl,
					UINT codeNotify )
{
	static CLunch* s_pLunch = NULL;

	switch ( id ) {

		case IDM_START:
			s_pLunch = CLunch::getInstance();
			if ( s_pLunch != NULL ) {
				s_pLunch->setHWND( hWnd );
				s_pLunch->start();

				EnableMenuItem( GetMenu(hWnd), IDM_START, MF_DISABLED );
				EnableMenuItem( GetMenu(hWnd), IDM_PAUSE, MF_ENABLED );
				EnableMenuItem( GetMenu(hWnd), IDM_STOP,  MF_ENABLED );			
				EnableMenuItem( GetMenu(hWnd), IDM_SETTING, MF_DISABLED );
			}
			break;

		case IDM_STOP:
			if ( s_pLunch != NULL ) {
				s_pLunch->stop();
				delete s_pLunch;
				s_pLunch = NULL;

				EnableMenuItem( GetMenu(hWnd), IDM_START, MF_ENABLED );
				EnableMenuItem( GetMenu(hWnd), IDM_PAUSE, MF_DISABLED );
				EnableMenuItem( GetMenu(hWnd), IDM_RESUME, MF_DISABLED );
				EnableMenuItem( GetMenu(hWnd), IDM_STOP,  MF_DISABLED );
				EnableMenuItem( GetMenu(hWnd), IDM_SETTING, MF_ENABLED );
			}
			break;

		case IDM_PAUSE:
			s_pLunch->pause();
			EnableMenuItem( GetMenu(hWnd), IDM_PAUSE, MF_DISABLED );
			EnableMenuItem( GetMenu(hWnd), IDM_RESUME, MF_ENABLED );
			EnableMenuItem( GetMenu(hWnd), IDM_STOP,  MF_DISABLED );			
			break;

		case IDM_RESUME:
			s_pLunch->resume();
			EnableMenuItem( GetMenu(hWnd), IDM_PAUSE, MF_ENABLED );
			EnableMenuItem( GetMenu(hWnd), IDM_RESUME, MF_DISABLED );
			EnableMenuItem( GetMenu(hWnd), IDM_STOP,  MF_ENABLED );			
			break;

		case IDM_SETTING:
			DialogBox( g_hInstance, MAKEINTRESOURCE(IDD_SETTINGBOX), hWnd, SettingDlg );
			break;

		case IDM_ALLOC_CONSOLE:
			AllocConsole();
			SetConsoleTitle( _T("Console") );
			g_hOut = GetStdHandle( STD_OUTPUT_HANDLE );
			SetConsoleTextAttribute( g_hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			EnableMenuItem( GetMenu(hWnd), IDM_ALLOC_CONSOLE, MF_DISABLED );
			EnableMenuItem( GetMenu(hWnd), IDM_FREE_CONSOLE,  MF_ENABLED );
			break;

		case IDM_FREE_CONSOLE:
			FreeConsole();
			EnableMenuItem( GetMenu(hWnd), IDM_ALLOC_CONSOLE, MF_ENABLED );
			EnableMenuItem( GetMenu(hWnd), IDM_FREE_CONSOLE,  MF_DISABLED );
			break;

		case IDM_ABOUT:
			DialogBox( g_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutDlg );
			break;

		case IDM_EXIT:
			if ( s_pLunch != NULL ) {
				s_pLunch->stop();
				delete s_pLunch;
			}
			DestroyWindow(hWnd);
			break;

		default:
			FORWARD_WM_COMMAND( hWnd, id, hWndCtl, codeNotify, DefWindowProc );
	}
}