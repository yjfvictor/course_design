/***
*main.c - WinMain function
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines WinMain function
*
*******************************************************************************/

#include <windows.h>
#include "resource.h"

HANDLE hThread = NULL ;
TCHAR szCaption[100] = TEXT("\0") ;

BOOL CALLBACK MainDialogProc ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam ) ;
BOOL CALLBACK SocketDlgProc ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam ) ;

/***
*int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nShowCmd ) - the entrance of this program
*
*Purpose:
*		Startup this program and call the other functions, called by the Windows operating system.
*
*Entry:
*		HINSTANCE	hInstance		- the handle to this instance
*		HINSTANCE	hPrevInstance	- the handle to the previous instance, it must be NULL under Win32 platform 
*		LPSTR		lpCmdLine		- the command-line parameter
*		int			nShowCmd		- the startup message of the way of the style of the program
*
*Exit:
*		Success:  EXIT_SUCCESS
*		Failure:  EXIT_FAILURE
*
*Exceptions:
*
*******************************************************************************/

int APIENTRY WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine, int nCmdShow )
{
	TCHAR szMsgBuffer[100] = TEXT("\0") ;
	LoadString ( hInstance , IDS_CAPTION , szCaption , sizeof (szCaption ) ) ;

	if ( -1 == DialogBoxParam ( hInstance , MAKEINTRESOURCE(IDD_SOCKET_INIT) , NULL , (DLGPROC)SocketDlgProc , (LPARAM)&hInstance ) )
	{
		LoadString ( hInstance , IDS_DIALOGBOX_INIT_ERROR , szMsgBuffer , sizeof (szMsgBuffer) ) ;
		MessageBox ( NULL , szMsgBuffer , szCaption , MB_ICONERROR ) ;
		return EXIT_FAILURE ;
	}

	if ( -1 == DialogBoxParam ( hInstance , MAKEINTRESOURCE(IDD_MAINDIALOG) , NULL , (DLGPROC)MainDialogProc , (LPARAM)&hInstance ) )
	{
		LoadString ( hInstance , IDS_DIALOGBOX_INIT_ERROR , szMsgBuffer , sizeof (szMsgBuffer) ) ;
		MessageBox ( NULL , szMsgBuffer , szCaption , MB_ICONERROR ) ;
		return EXIT_FAILURE ;
	}

	WaitForSingleObject ( hThread , 5000 ) ;
	TerminateThread ( hThread , 0 ) ;
	CloseHandle ( hThread ) ;
	hThread = NULL ;

	return EXIT_SUCCESS ;
}
