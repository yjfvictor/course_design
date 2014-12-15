/***
*main.c - main function
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines WinMain function
*
*******************************************************************************/

#include <windows.h>
#include "resource.h"
#include "main_dialog.h"
#include "server_ip.h"

char szTitle[102] ;
extern HANDLE hThread ;
extern volatile int bEnd ;

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

int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nShowCmd )
{
	char szWindowCreationFailure[102] ;
	LoadString ( hInstance , IDS_WINDOW_CREATION_FAILURE , szWindowCreationFailure , sizeof ( szWindowCreationFailure ) ) ;
	LoadString ( hInstance , IDS_TITLE , szTitle , sizeof ( szTitle ) ) ;
	if ( -1 == DialogBoxParam ( hInstance, MAKEINTRESOURCE ( IDD_SEVER_IP ) , NULL , (DLGPROC)SeverIp , (LPARAM)hInstance ) )
	{
		MessageBox ( NULL, szWindowCreationFailure , szTitle , MB_ICONERROR) ;
		return EXIT_FAILURE ;
	}
	if ( -1 == DialogBoxParam ( hInstance, MAKEINTRESOURCE ( IDD_MAIN_DIALOG ) , NULL , (DLGPROC)MainDialog , (LPARAM)hInstance ) )
	{
		MessageBox ( NULL, szWindowCreationFailure , szTitle , MB_ICONERROR) ;
		return EXIT_FAILURE ;
	}
	bEnd = 1 ;
	WaitForSingleObject ( hThread , INFINITE ) ;
	return EXIT_SUCCESS ;
}
