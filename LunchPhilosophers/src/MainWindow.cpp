#include "stdafx.h"
#include "MainWindow.h"
#include "HandleMsgs.h"

/*---------------------------------------------------------------*/

#define MAX_LOADSTRING 100

HINSTANCE g_hInstance;

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

/*---------------------------------------------------------------*/

int APIENTRY _tWinMain( HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPTSTR    lpCmdLine,
                        int       nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	g_hInstance = hInstance;

	HWND       hWnd;
 	MSG        Msg;
	HACCEL     hAccelTable;
	WNDCLASSEX WndClassEx;
	TCHAR      szTitle[MAX_LOADSTRING];
	TCHAR      szWindowClass[MAX_LOADSTRING];

	HBITMAP    hBitmap       = LoadBitmap( hInstance, MAKEINTRESOURCE( IDB_BITMAP_PLUTKA ) );
	HBRUSH     hbrBackground = CreatePatternBrush( hBitmap );

	LoadString( hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING );
	LoadString( hInstance, IDC_LUNCHPHILOSOPHERS, szWindowClass, MAX_LOADSTRING );

	WndClassEx.cbSize        = sizeof(WNDCLASSEX);
	WndClassEx.style		 = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc	 = WndProc;
	WndClassEx.cbClsExtra	 = 0;
	WndClassEx.cbWndExtra	 = 0;
	WndClassEx.hInstance	 = hInstance;
	WndClassEx.hIcon	 	 = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_LUNCHPHILOSOPHERS) );
	WndClassEx.hCursor		 = LoadCursor( NULL, IDC_ARROW );
	WndClassEx.hbrBackground = hbrBackground;
	WndClassEx.lpszMenuName	 = MAKEINTRESOURCE(IDC_LUNCHPHILOSOPHERS);
	WndClassEx.lpszClassName = szWindowClass;
	WndClassEx.hIconSm		 = LoadIcon( WndClassEx.hInstance, MAKEINTRESOURCE(IDI_SMALL) );

	if ( !RegisterClassEx(&WndClassEx) ) {
		return -1;
	}

    hWnd = CreateWindow( szWindowClass, szTitle,
						 WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
                         CW_USEDEFAULT, CW_USEDEFAULT,
						 600, 600,//850, 450,
						 NULL, NULL,
						 hInstance,
						 NULL );

    if ( !hWnd ) {
       return -2;
    }

    ShowWindow( hWnd, nCmdShow );
    UpdateWindow( hWnd );

	hAccelTable = LoadAccelerators( hInstance, MAKEINTRESOURCE(IDC_LUNCHPHILOSOPHERS) );

	while ( GetMessage(&Msg, NULL, 0, 0) ) {

		if ( !TranslateAccelerator(Msg.hwnd, hAccelTable, &Msg) ) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	DeleteObject( hbrBackground );
	DeleteObject( hBitmap );

	return (int) Msg.wParam;
}


/*---------------------------------------------------------------*/

LRESULT CALLBACK WndProc( HWND   hWnd,
						  UINT   Message,
						  WPARAM wParam,
						  LPARAM lParam )
{
	switch ( Message )
	{
		HANDLE_MSG( hWnd, WM_CREATE,  Cls_OnCreate );
		HANDLE_MSG( hWnd, WM_COMMAND, Cls_OnCommand );
		HANDLE_MSG( hWnd, WM_PAINT,   Cls_OnPaint );
		HANDLE_MSG( hWnd, WM_DESTROY, Cls_OnDestroy ); 

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
}