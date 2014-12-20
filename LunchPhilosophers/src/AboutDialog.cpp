#include "stdafx.h"
#include "..\resource.h"

extern HINSTANCE g_hInstance;

INT_PTR CALLBACK AboutDlg(HWND   hDlg,
					      UINT   Message,
					      WPARAM wParam,
					      LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	switch (Message) {

		case WM_INITDIALOG:
			return (INT_PTR)TRUE;			

		/*
		case WM_PAINT:
			{
				HBITMAP hBitmap;

				HDC hDC, hMemDC;
				
				hDC    = GetDC( hDlg );
				hMemDC = CreateCompatibleDC( hDC );
				hBitmap = LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_BITMAP) );
				SelectObject( hMemDC, hBitmap );

				BitBlt( hDC, 10, 10, 200, 200, hMemDC, 0, 0, SRCCOPY );

     	        DeleteDC( hMemDC ) ;
	            DeleteObject( hBitmap );
				
				ReleaseDC( hDlg, hDC );
			}
			break;*/

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}

	return (INT_PTR)FALSE;
}
