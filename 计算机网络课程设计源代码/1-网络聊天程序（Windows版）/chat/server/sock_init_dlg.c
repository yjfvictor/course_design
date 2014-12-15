/***
*sock_init_dlg.c - Socket-initializing-dialog function
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines the callback function of the socket initializing
*
*******************************************************************************/

#include <windows.h>
#include "common.h"
#include "resource.h"

extern volatile HWND hCurDlg ;
extern volatile BOOL state ;
extern HANDLE hThread ;

DWORD APIENTRY WinSock ( LPVOID threadNum ) ;

/***
*BOOL CALLBACK SocketDlgProc ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam ) - the callback function of the IDD_SOCKET_INIT dialog
*
*Purpose:
*		Deal with the messages that send to the IDD_SOCKET_INIT dialog.
*
*Entry:
*		HWND		hDlg			- the handle to the IDD_SOCKET_INIT dialog
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

BOOL CALLBACK SocketDlgProc ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	
	DWORD ThreadID = 0L ;
	static HINSTANCE hInstance = NULL ;
	HICON hIcon = NULL ;

	if ( state )
	{
		hCurDlg = NULL ;
		EndDialog ( hDlg , 0 ) ;
		return FALSE ;
	}

	switch ( uMsg )
	{
	case WM_INITDIALOG:
		hInstance = *(HINSTANCE *) lParam ;
		hIcon = LoadIcon ( hInstance , MAKEINTRESOURCE ( IDI_ICON ) ) ;
		SendMessage ( hDlg, WM_SETICON , TRUE , (LPARAM) hIcon ) ;
		SendMessage ( hDlg, WM_SETICON , FALSE , (LPARAM) hIcon ) ;
		hCurDlg = hDlg ;

		return FALSE ;

	case WM_SHOWWINDOW:
		hThread = CreateThread ( NULL, 0, WinSock , (LPVOID)&hInstance , 0 , &ThreadID );
	case WM_COMMAND:
		switch ( LOWORD ( wParam ) )
		{
		case IDCANCEL:
			ExitProcess(0);
			return FALSE ;
		default:
			break ;
		}
		return FALSE ;
	case WM_CLOSE:
		hCurDlg = NULL ;
		ExitProcess ( 0 ) ;
		return FALSE ;
	default:
		return FALSE ;
	}
}
