#include "stdafx.h"

#include <commctrl.h>

#include "..\resource.h"
#include "TimeoutData.h"
#include "Shared.h"

#define PHLSPHR_N_1			0
#define PHLSPHR_N_2			1
#define PHLSPHR_N_3			2
#define PHLSPHR_N_4			3
#define PHLSPHR_N_5			4


#define MIN_RANGE_SLIDER   10 // in ms.
#define MAX_RANGE_SLIDER 2000 // in ms.

TimeoutData g_tmData[COUNT_PHILOSOPHERS] = { 
		 									   200,  500,
											   200,  500,
											   200,  500,
											   200,  500,
										       200,  500
                                           };

INT_PTR CALLBACK SettingDlg( HWND   hDlg,
					         UINT   Message,
					         WPARAM wParam,
					         LPARAM lParam )
{
	UNREFERENCED_PARAMETER( lParam );

	TCHAR szBuffer[10] = { 0 };

	static HWND s_hSlider11, s_hSlider12;
	static HWND s_hSlider21, s_hSlider22;
	static HWND s_hSlider31, s_hSlider32;
	static HWND s_hSlider41, s_hSlider42;
	static HWND s_hSlider51, s_hSlider52;

	switch ( Message ) {

		case WM_INITDIALOG: 
			{
				s_hSlider11 = GetDlgItem( hDlg, IDC_SLIDER_11 );
				s_hSlider12 = GetDlgItem( hDlg, IDC_SLIDER_12 );
				s_hSlider21 = GetDlgItem( hDlg, IDC_SLIDER_21 );
				s_hSlider22 = GetDlgItem( hDlg, IDC_SLIDER_22 );
				s_hSlider31 = GetDlgItem( hDlg, IDC_SLIDER_31 );
				s_hSlider32 = GetDlgItem( hDlg, IDC_SLIDER_32 );
				s_hSlider41 = GetDlgItem( hDlg, IDC_SLIDER_41 );
				s_hSlider42 = GetDlgItem( hDlg, IDC_SLIDER_42 );
				s_hSlider51 = GetDlgItem( hDlg, IDC_SLIDER_51 );
				s_hSlider52 = GetDlgItem( hDlg, IDC_SLIDER_52 );

				// 1
				SendMessage( s_hSlider11, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider11, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_1].tmThink );
				SendMessage( s_hSlider12, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider12, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_1].tmEat );
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_1].tmThink );
				SetDlgItemText( hDlg, IDC_STATIC_11, szBuffer ); 
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_1].tmEat );
				SetDlgItemText( hDlg, IDC_STATIC_12, szBuffer ); 
				
				// 2
				SendMessage( s_hSlider21, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider21, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_1].tmThink );
				SendMessage( s_hSlider22, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider22, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_2].tmEat );
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_2].tmThink );
				SetDlgItemText( hDlg, IDC_STATIC_21, szBuffer ); 
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_2].tmEat );
				SetDlgItemText( hDlg, IDC_STATIC_22, szBuffer ); 

				// 3
				SendMessage( s_hSlider31, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider31, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_3].tmThink );
				SendMessage( s_hSlider32, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider32, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_3].tmEat );
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_3].tmThink );
				SetDlgItemText( hDlg, IDC_STATIC_31, szBuffer ); 
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_3].tmEat );
				SetDlgItemText( hDlg, IDC_STATIC_32, szBuffer ); 

				// 4
				SendMessage( s_hSlider41, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider41, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_4].tmThink );
				SendMessage( s_hSlider42, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider42, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_4].tmEat );
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_4].tmThink );
				SetDlgItemText( hDlg, IDC_STATIC_41, szBuffer ); 
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_4].tmEat );
				SetDlgItemText( hDlg, IDC_STATIC_42, szBuffer ); 

				// 5
				SendMessage( s_hSlider51, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider51, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_5].tmThink );
				SendMessage( s_hSlider52, TBM_SETRANGE, TRUE, MAKELONG( MIN_RANGE_SLIDER, MAX_RANGE_SLIDER ) );
				SendMessage( s_hSlider52, TBM_SETPOS, TRUE, g_tmData[PHLSPHR_N_5].tmEat );
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_5].tmThink );
				SetDlgItemText( hDlg, IDC_STATIC_51, szBuffer ); 
				_stprintf_s( szBuffer, _T("%d ms."), g_tmData[PHLSPHR_N_5].tmEat );
				SetDlgItemText( hDlg, IDC_STATIC_52, szBuffer ); 

				return (INT_PTR)TRUE;
			}

		case WM_HSCROLL:
			{
				int newValue = SendMessage( (HWND)lParam, TBM_GETPOS, 0, 0 );

				switch ( GetDlgCtrlID( (HWND)lParam ) ) {

					case IDC_SLIDER_11:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_11, szBuffer ); 
						break;

					case IDC_SLIDER_12:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_12, szBuffer ); 
						break;

					case IDC_SLIDER_21:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_21, szBuffer ); 
						break;

					case IDC_SLIDER_22:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_22, szBuffer ); 
						break;

					case IDC_SLIDER_31:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_31, szBuffer ); 
						break;

					case IDC_SLIDER_32:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_32, szBuffer ); 
						break;

					case IDC_SLIDER_41:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_41, szBuffer ); 
						break;

					case IDC_SLIDER_42:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_42, szBuffer ); 
						break;

					case IDC_SLIDER_51:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_51, szBuffer ); 
						break;

					case IDC_SLIDER_52:
						_stprintf_s( szBuffer, _T("%d ms."), newValue );
						SetDlgItemText( hDlg, IDC_STATIC_52, szBuffer ); 
						break;
				}
			}
			break;

		case WM_COMMAND:
			{
				switch ( LOWORD( wParam ) ) {
					case IDOK:
						{
							g_tmData[PHLSPHR_N_1].tmThink = GetDlgItemInt( hDlg, IDC_STATIC_11, NULL, FALSE );
							g_tmData[PHLSPHR_N_1].tmEat   = GetDlgItemInt( hDlg, IDC_STATIC_12, NULL, FALSE );
						
							g_tmData[PHLSPHR_N_2].tmThink = GetDlgItemInt( hDlg, IDC_STATIC_21, NULL, FALSE );
							g_tmData[PHLSPHR_N_2].tmEat   = GetDlgItemInt( hDlg, IDC_STATIC_22, NULL, FALSE );
						
							g_tmData[PHLSPHR_N_3].tmThink = GetDlgItemInt( hDlg, IDC_STATIC_31, NULL, FALSE );
							g_tmData[PHLSPHR_N_3].tmEat   = GetDlgItemInt( hDlg, IDC_STATIC_32, NULL, FALSE );
						
							g_tmData[PHLSPHR_N_4].tmThink = GetDlgItemInt( hDlg, IDC_STATIC_41, NULL, FALSE );
							g_tmData[PHLSPHR_N_4].tmEat   = GetDlgItemInt( hDlg, IDC_STATIC_42, NULL, FALSE );
						
							g_tmData[PHLSPHR_N_5].tmThink = GetDlgItemInt( hDlg, IDC_STATIC_51, NULL, FALSE );
							g_tmData[PHLSPHR_N_5].tmEat   = GetDlgItemInt( hDlg, IDC_STATIC_52, NULL, FALSE );
						
						}
						//break;

					case IDCANCEL:
						EndDialog(hDlg, LOWORD(wParam));
						return (INT_PTR)TRUE;
				}
			}
			break;
	}

	return (INT_PTR)FALSE;
}
