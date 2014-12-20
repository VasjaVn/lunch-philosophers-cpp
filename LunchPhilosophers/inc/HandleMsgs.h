#ifndef __MSG_HANDLES_H__
#define __MSG_HANDLES_H__

#include "..\resource.h"

extern HINSTANCE g_hInstance;

BOOL Cls_OnCreate( HWND hWnd, LPCREATESTRUCT lpCreateStruct );
void Cls_OnCommand( HWND hWnd, int id, HWND hWndCtl, UINT codeNotify );
void Cls_OnPaint( HWND hWnd );
void Cls_OnDestroy( HWND hWnd );

#endif //__MSG_HANDLES_H__