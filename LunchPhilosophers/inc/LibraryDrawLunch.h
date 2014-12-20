#ifndef __LIBRARY_DRAW_LUNCH_H__
#define __LIBRARY_DRAW_LUNCH_H__

#include "Shared.h"

// structura DrawData
typedef struct _DrawData {

	HDC     hDC;
	HDC     hCompatibleDC;

	HFONT   hFont;
	HBITMAP hBmpChicken;
	HBITMAP hBmpOld;
	HBITMAP hBmpTable;
	HBRUSH  hBrTable;
	
	HPEN    hPenHeadFork;
	HPEN    hPenFootFork;

	int rTable;
	int rPlate;

	int   Xc;
	int   Yc;
	int   Radius;
	float fDeltaAngle;

} DrawData;

// global
extern DrawData  g_drawData;
extern HINSTANCE g_hInstance;

void InitLibraryDrawLunch( HWND hWnd );
void DeinitLibraryDrawLunch( HWND hWnd );

void DrawTable();
void DrawPlates(); 
void DrawForks();
void DrawChair();

#endif // __LIBRARY_DRAW_LUNCH_H__