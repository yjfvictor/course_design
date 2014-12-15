/***
*server_ip.c - server_ip dialog function
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines the server_ip dialog function
*
*******************************************************************************/

#include <windows.h>
#include <string.h>
#include <commctrl.h>
#include "resource.h"
#include "server_ip.h"
#include "core.h"
#pragma comment ( lib ,  "comctl32.lib" )

HANDLE hThread = NULL ;
char IP[20] ;

extern volatile int status ;
extern volatile HWND hMainDlg ;

/***
*BOOL CALLBACK MainDialog ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam ) - the callback function of the main dialog
*
*Purpose:
*		Deal with the messages that send to the main dialog.
*
*Entry:
*		HWND		hDlg			- the handle to the main dialog
*		UINT		uMsg			- the type of the message 
*		WPARAM		wParam			- the value passed as a parameter to a window procedure or callback function
*		int			nShowCmd		- the 32-bit value passed as a parameter to a window procedure or callback function
*
*Exit:
*		Return FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL CALLBACK SeverIp ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	HWND hWnd ;
	static HINSTANCE hInstance = NULL ;
	char szStaticIpText[50] ;
	char szButtonText[15] ;
	char szOKCancel[10] ;
	static DWORD ThreadID = 0 ;
	HICON hIcon ;
	hMainDlg = hDlg ;
	if ( status )
		EndDialog ( hDlg , 0 ) ;
	switch ( uMsg )
	{
	case WM_INITDIALOG :
		hInstance = (HINSTANCE)lParam ;
		hIcon = LoadIcon ( hInstance , MAKEINTRESOURCE ( IDI_ICON ) ) ;
		SendMessage ( hDlg, WM_SETICON , TRUE , (LPARAM) hIcon ) ;
		SendMessage ( hDlg, WM_SETICON , FALSE , (LPARAM) hIcon ) ;
		InitCommonControls ( ) ;
		SetDlgItemText ( hDlg , IDC_IPADDRESS , "0.0.0.0" ) ;
		return FALSE ;
	case WM_COMMAND :
		switch ( LOWORD (wParam) )
		{
		case IDC_OK_CANCEL:
			GetDlgItemText ( hDlg , IDC_OK_CANCEL , szButtonText , 18 ) ;
			LoadString ( hInstance , IDS_OK , szOKCancel , 8 ) ;
			if ( !strcmp ( szButtonText , szOKCancel ) )
			{
				GetDlgItemText ( hDlg , IDC_IPADDRESS , IP , 18 ) ;
				hWnd = GetDlgItem (hDlg , IDC_IPADDRESS );
				EnableWindow ( hWnd , FALSE ) ;
				LoadString ( hInstance , IDS_IP_CONNECTION , szStaticIpText , 40 ) ;
				SendMessage ( hDlg , WM_SETTEXT , 0 , (LPARAM)szStaticIpText );
				strcat ( szStaticIpText , IP ) ;
				hWnd = GetDlgItem ( hDlg , IDC_STATIC_IP ) ;
				SendMessage ( hWnd , WM_SETTEXT , 0 ,   (LPARAM)szStaticIpText );
				LoadString ( hInstance , IDS_CANCEL , szOKCancel , 8 ) ;
				SetDlgItemText ( hDlg , IDC_OK_CANCEL , szOKCancel ) ;
				hThread = CreateThread ( NULL, 0, connection , (LPVOID)&hInstance , 0 , &ThreadID ) ;
			}
			else
			{
				ExitProcess ( 0 ) ;
			}
			break ;
		}
		return FALSE ;
	case WM_CLOSE :
		ExitProcess ( 0 ) ;
		return FALSE ;
	}
	return FALSE ;
}
