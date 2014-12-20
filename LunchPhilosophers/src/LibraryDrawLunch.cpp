#include "stdafx.h"
#include "LibraryDrawLunch.h"
#include "Philosopher.h"
#include "..\resource.h"


#define WIDTH_FOOT_PEN                  6
#define WIDTH_HEAD_PEN                 10
#define RADIUS_PLATE                   50
#define WIDTH_PLATE_AND_END_TABLE      20
#define DELTA_RADIUS_IN_AND_OUT_PLATE  12

/******************************************************************************************/


void InitLibraryDrawLunch( HWND hWnd )
{

	RECT Rect = { 0 };
	GetClientRect( hWnd, &Rect );

	g_drawData.hDC           = GetDC( hWnd );
	g_drawData.hCompatibleDC = CreateCompatibleDC( g_drawData.hDC );
	g_drawData.hFont         = CreateFont( 70, 30, 0, 0, 700, 3, 4, 0, 
		                                   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
										   CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
										   DEFAULT_PITCH | FF_DONTCARE,
										   _T("Arial") );
 
	g_drawData.hBmpChicken   = LoadBitmap( g_hInstance, MAKEINTRESOURCE( IDB_BITMAP_CHICKEN ) );
	g_drawData.hBmpOld       = (HBITMAP)SelectObject( g_drawData.hCompatibleDC, g_drawData.hBmpChicken );
	
	g_drawData.hBmpTable     = LoadBitmap( g_hInstance, MAKEINTRESOURCE( IDB_BITMAP_TABLE ) );
	g_drawData.hBrTable      = CreatePatternBrush( g_drawData.hBmpTable );
	
	g_drawData.hPenFootFork  = CreatePen( PS_SOLID, WIDTH_FOOT_PEN, RGB( 255, 255, 255 ) );
	g_drawData.hPenHeadFork  = CreatePen( PS_SOLID, WIDTH_HEAD_PEN, RGB( 255, 255, 255 ) );

	g_drawData.rPlate = RADIUS_PLATE;
	g_drawData.rTable = (int) ( Rect.bottom / 3 );

	g_drawData.Xc          = Rect.right / 2;
	g_drawData.Yc          = Rect.bottom / 2;
	g_drawData.Radius      = (int)( Rect.bottom / 3 ) - RADIUS_PLATE - WIDTH_PLATE_AND_END_TABLE;
	g_drawData.fDeltaAngle = (float) ( 2.0 * M_PI / COUNT_PHILOSOPHERS );

}


/******************************************************************************************/

void DeinitLibraryDrawLunch( HWND hWnd )
{
	SelectObject( g_drawData.hCompatibleDC, g_drawData.hBmpOld );
	DeleteObject( g_drawData.hBmpChicken );

	DeleteObject( g_drawData.hFont );

	DeleteObject( g_drawData.hPenHeadFork );
	DeleteObject( g_drawData.hPenFootFork );

	DeleteObject( g_drawData.hBrTable );
	DeleteObject( g_drawData.hBmpTable );

	DeleteDC( g_drawData.hCompatibleDC );
	ReleaseDC( hWnd, g_drawData.hDC );
}

/******************************************************************************************/

void DrawTable()
{	
	HBRUSH hBrushTable = g_drawData.hBrTable;

	HBRUSH hOldBrush = (HBRUSH)SelectObject( g_drawData.hDC, hBrushTable );

	int x1 = g_drawData.Xc - g_drawData.rTable;
	int y1 = g_drawData.Yc - g_drawData.rTable;
	int x2 = g_drawData.Xc + g_drawData.rTable;
	int y2 = g_drawData.Yc + g_drawData.rTable;

	Ellipse( g_drawData.hDC, x1, y1, x2, y2 );

	SelectObject( g_drawData.hDC, hOldBrush );
}


/******************************************************************************************/

void DrawPlates() 
{
	int Xc             = g_drawData.Xc;
	int Yc             = g_drawData.Yc;
	int Radius         = g_drawData.Radius;
	float fDeltaAngle  = g_drawData.fDeltaAngle;

	int   X, Y;
	float fAngle;

	int rPlate   = g_drawData.rPlate;
	int rPlateIn = g_drawData.rPlate - DELTA_RADIUS_IN_AND_OUT_PLATE; 

	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {

		fAngle = fDeltaAngle * i; 
		X = (int) ( Xc + Radius * sin( fAngle ) );
		Y = (int) ( Yc + Radius * cos( fAngle ) );

		Ellipse( g_drawData.hDC, X - rPlate, Y - rPlate, X + rPlate, Y + rPlate );

		Ellipse( g_drawData.hDC, X - rPlateIn, Y - rPlateIn, X + rPlateIn, Y + rPlateIn );

		if ( CPhilosopher::s_state[i] == EATING ) {
				BitBlt( g_drawData.hDC, X - 47, Y - 28, 100, 60, g_drawData.hCompatibleDC, 0, 0, SRCAND );		
		}
	}
}


/******************************************************************************************/

BOOL DrawLine( HDC hDC, int x1, int y1, int x2, int y2 )
{
  POINT pt;
  MoveToEx( hDC, x1, y1, &pt );
  return LineTo( hDC, x2, y2 );
}


/******************************************************************************************/

void DrawForks()
{
	HDC hDC           = g_drawData.hDC;
	HPEN hPenHeadFork = g_drawData.hPenHeadFork;
	HPEN hPenFootFork = g_drawData.hPenFootFork;

	int Xc             = g_drawData.Xc;
	int Yc             = g_drawData.Yc;
	int Radius         = g_drawData.Radius;
	float fDeltaAngle  = g_drawData.fDeltaAngle;
	float fDeltaAngle2 = (float) ( 2.0 * M_PI / 12.0 );
	
	int   lenHeadFork = 10;
	int   lenFootFork = 45;
	int   X1, Y1, X2, Y2, X3, Y3;
	float fAngle;

	HPEN hOldPen = (HPEN)SelectObject( hDC, hPenHeadFork );

	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {
		fAngle = fDeltaAngle * i;
		X1 = (int) ( Xc + ( Radius - lenHeadFork ) * sin( fAngle + fDeltaAngle2 ) );
		Y1 = (int) ( Yc + ( Radius - lenHeadFork ) * cos( fAngle + fDeltaAngle2 ) );

		X2 = (int) ( Xc + Radius * sin( fAngle + fDeltaAngle2 ) );
		Y2 = (int) ( Yc + Radius * cos( fAngle + fDeltaAngle2 ) );

		X3 = (int) ( Xc + ( Radius + lenFootFork ) * sin( fAngle + fDeltaAngle2 ) );
		Y3 = (int) ( Yc + ( Radius + lenFootFork ) * cos( fAngle + fDeltaAngle2 ) );

		DrawLine( hDC, X1, Y1, X2, Y2 ); 
		SelectObject( hDC, hPenFootFork );
		DrawLine( hDC, X2, Y2, X3, Y3 ); 
		SelectObject( hDC, hPenHeadFork );
	}

	SelectObject( hDC, hOldPen );
}


/******************************************************************************************/

void DrawChair()
{
	const int rChair = 60;

	HBRUSH hBrushTable = g_drawData.hBrTable;
	HBRUSH hOldBrush   = (HBRUSH)SelectObject( g_drawData.hDC, hBrushTable );

	COLORREF oldColor  = SetTextColor( g_drawData.hDC, RGB( 255, 255, 255 ) );
    HFONT oldFont      = (HFONT)SelectObject( g_drawData.hDC, g_drawData.hFont );
 
	int Xc             = g_drawData.Xc;
	int Yc             = g_drawData.Yc;
	int Radius         = g_drawData.Radius + 130;
	float fDeltaAngle  = g_drawData.fDeltaAngle;

	int   X, Y;
	float fAngle;
	TCHAR szBuffer[40];

	SetBkMode( g_drawData.hDC, TRANSPARENT ); 


	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {

		fAngle = fDeltaAngle * i; 
		X = (int) ( Xc + Radius * sin( fAngle ) );
		Y = (int) ( Yc + Radius * cos( fAngle ) );

		Ellipse( g_drawData.hDC, X - rChair, Y - rChair, X + rChair, Y + rChair );
	
		szBuffer[0] = _T('\0');
		_stprintf_s( szBuffer, _T("P#%d"), i + 1 );


		TextOut( g_drawData.hDC, X - 55, Y - 40, szBuffer, _tcslen( szBuffer ) );
	}


	SetTextColor( g_drawData.hDC, oldColor );
	SetBkMode( g_drawData.hDC, OPAQUE ); 
    
	SelectObject( g_drawData.hDC, oldFont );
	SelectObject( g_drawData.hDC, hOldBrush );
}