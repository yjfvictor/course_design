/***
*main_dialog.c - main_dialog callback functions
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines main_dialog callback functions
*
*******************************************************************************/

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "online_users.h"
#include "resource.h"

PHOnlineUserInfo phOnlineUserInfo ;
extern volatile HWND hCurDlg ;
extern volatile BOOL state ;

BOOL SaveMessages ( HWND hDlg , LPCTSTR pstrBuffer ) ;
DWORD APIENTRY SetOnlinePeople ( LPVOID threadNum ) ;
void SendMessageToClient ( HINSTANCE hInstance , const char *szMessageFromServer) ;

HWND hShowMessage = NULL ;

/***
*BOOL ShowMessage ( LPCTSTR szMessage ) - show the messages in the edit box
*
*Purpose:
*		Show the messages in the edit box
*
*Entry:
*		LPCTSTR		szMessage		- the constant character pointer to the C-style string of the message
*
*Exit:
*		Success:  TRUE
*		Failure:  FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL ShowMessage ( LPCTSTR szMessage )
{
	int cchTextMax = 0 ;
	PTSTR lpszText = NULL ;
	PTSTR lpszTextTemp = NULL ;
	int MinPos =0 , MaxPos =0 ;
	cchTextMax = 1 + SendMessage ( hShowMessage , WM_GETTEXTLENGTH , 0 , 0 ) ;
	lpszText = (PTSTR) malloc ( cchTextMax * sizeof(TCHAR) ) ;
	if ( lpszText == NULL )
	{
		return FALSE ;
	}
	else
	{
		SendMessage ( hShowMessage , WM_GETTEXT , (WPARAM) cchTextMax , (LPARAM) lpszText ) ;
		lpszTextTemp = (PTSTR) realloc ( lpszText , (cchTextMax + strlen (szMessage)+4) * sizeof (TCHAR) ) ;
		if ( lpszTextTemp == NULL )
		{
			free ( lpszText ) ;
			lpszText = NULL ;
			return FALSE ;
		}
		else
		{
			lpszText = lpszTextTemp ;
			strcat ( lpszText , szMessage ) ;
			strcat ( lpszText , "\r\n\r\n" ) ;
			SendMessage( hShowMessage , WM_SETTEXT , 0 , (LPARAM)(LPCTSTR)lpszText ) ;
			if ( GetScrollRange ( hShowMessage , SB_VERT , &MinPos , & MaxPos ) )
			{
				SetScrollPos ( hShowMessage , SB_VERT , MaxPos , TRUE ) ;
				SendMessage ( hShowMessage , WM_VSCROLL , MAKEWPARAM ( SB_BOTTOM , 0 ), (LPARAM)NULL ) ;
				Sleep ( 30 ) ;
				free ( lpszText ) ;
				lpszText = NULL ;
				return TRUE ;
			}
			else
			{
				free ( lpszText ) ;
				lpszText = NULL ;
				return FALSE ;
			}
		}
	}
}

/***
*BOOL CALLBACK MainDialogProc ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam ) - the callback function of the main dialog
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

BOOL CALLBACK MainDialogProc ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	static HINSTANCE hInstance = NULL ;
	HICON hIcon = NULL ;
	HWND hDlgItem = NULL ;
	int iLength = 0 ;
	PTSTR pstrBuffer = NULL ;
	TCHAR szMsgBuffer[100] = TEXT("\0") ;

	static HANDLE hThreadSetOnlinePeople = NULL ;
	static DWORD ThreadIDSetOnlinePeople = 0L ;
	static HOnlineUserInfo hOnlineUserInfo ;

	//static HANDLE hThread = NULL ;
	//static DWORD ThreadID = 0L ;
	//static HANDLE hThread = NULL ;
	//static DWORD ThreadID = 0L ;

	switch ( uMsg )
	{
	case WM_INITDIALOG:
		hInstance = *(HINSTANCE *) lParam ;
		hIcon = LoadIcon ( hInstance , MAKEINTRESOURCE ( IDI_ICON ) ) ;
		SendMessage ( hDlg, WM_SETICON , TRUE , (LPARAM) hIcon ) ;
		SendMessage ( hDlg, WM_SETICON , FALSE , (LPARAM) hIcon ) ;
		hCurDlg = hDlg ;

		hShowMessage = GetDlgItem ( hDlg , IDC_MESSAGES ) ;
		if ( hShowMessage == NULL )  // fail to get the handle to the message textbox
		{
			LoadString ( hInstance , IDS_UNKNOWN_SYSTEM_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
			MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONERROR ) ;
			ExitProcess ( EXIT_FAILURE ) ;
		}

		hDlgItem = GetDlgItem ( hDlg , IDC_ONLINE_PEOPLE ) ;
		if ( hDlgItem == NULL )  // fail to get the handle to the online_people label
		{
			LoadString ( hInstance , IDS_UNKNOWN_SYSTEM_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
			MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONERROR ) ;
			ExitProcess ( EXIT_FAILURE ) ;
		}
		else
		{
			hOnlineUserInfo.hLableOnlinePeople = hDlgItem ;
			hDlgItem = GetDlgItem ( hDlg , IDC_ONLINE_USER_LIST ) ;
			if ( hDlgItem == NULL )  // fail to get the handle to the online_people label
			{
				LoadString ( hInstance , IDS_UNKNOWN_SYSTEM_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
				MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONERROR ) ;
				ExitProcess ( EXIT_FAILURE ) ;
			}
			else
			{
				hOnlineUserInfo.hOnlineUserList = hDlgItem ;
				phOnlineUserInfo = &hOnlineUserInfo ;
				hThreadSetOnlinePeople = CreateThread ( NULL , 0 , SetOnlinePeople , NULL , 0 , &ThreadIDSetOnlinePeople ) ;
			}
		}

		return FALSE ;
	case WM_COMMAND:
		switch ( LOWORD ( wParam ) )
		{
		case IDC_CLEAR:
			SetDlgItemText ( hDlg , IDC_MESSAGES , TEXT("") ) ;
			break ;
		case IDC_SAVE:
			hDlgItem = GetDlgItem ( hDlg , IDC_MESSAGES ) ;
			if ( hDlgItem == NULL )  // fail to get the handle to the message dialog
			{
				LoadString ( hInstance , IDS_UNKNOWN_SYSTEM_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
				MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONERROR ) ;
			}
			else   // succeed in getting the handle to the message dialog
			{
				iLength = (int)SendMessage ( hDlgItem , WM_GETTEXTLENGTH , 0 , 0 ) ;
				pstrBuffer = (PTSTR) malloc ( (iLength+1) * sizeof (TCHAR) ) ;
				if ( pstrBuffer == NULL )
				{
					LoadString ( hInstance , IDS_MEMORY_FAILED , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
					MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONERROR ) ;
				}
				else
				{
					if ( GetDlgItemText ( hDlg , IDC_MESSAGES , pstrBuffer , iLength+1 ) )
					{
						if ( !SaveMessages ( hDlg , pstrBuffer ) )
						{
							free ( pstrBuffer ) ;
							pstrBuffer = NULL ;
							LoadString ( hInstance , IDS_FILE_OPEN_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
							MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONERROR ) ;
						}
						else   // fail to write the file
						{
							free ( pstrBuffer ) ;
							pstrBuffer = NULL ;
						}
					}
					else  // no chatting records
					{
						free (pstrBuffer) ;
						pstrBuffer = NULL ;
						LoadString ( hInstance , IDS_NO_TEXT , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
						MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONWARNING ) ;
					}
				}
			}
			break ;
		case IDC_SEND:
			hDlgItem = GetDlgItem ( hDlg , IDC_COMMAND_LINE ) ;
			if ( hDlgItem == NULL )  // fail to get the handle to the message dialog
			{
				LoadString ( hInstance , IDS_UNKNOWN_SYSTEM_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
				MessageBox ( hDlg , szMsgBuffer , szCaption , MB_ICONERROR ) ;
			}
			else   // succeed in getting the handle to the message dialog
			{
				iLength = (int)SendMessage ( hDlgItem , WM_GETTEXTLENGTH , 0 , 0 ) ;
				pstrBuffer = (PTSTR) malloc ( (iLength+1) * sizeof (TCHAR) ) ;
				SendMessage ( hDlgItem , WM_GETTEXT , (WPARAM)(iLength+1) , (LPARAM)pstrBuffer ) ;
				SendMessageToClient ( hInstance , pstrBuffer ) ;
				Sleep (20) ;
				free ( pstrBuffer ) ;
				pstrBuffer = NULL ;
				SendMessage ( hDlgItem , WM_SETTEXT , (WPARAM)0 , (LPARAM)(LPCTSTR)"\0" ) ;
			}
			break ;
		default:
			break ;
		}
		return FALSE ;

	case WM_CLOSE:
		TerminateThread ( hThreadSetOnlinePeople , 0 ) ;
		state = FALSE ;
		CloseHandle ( hThreadSetOnlinePeople ) ;
		hThreadSetOnlinePeople = NULL ;
		EndDialog ( hDlg , 0 ) ;
		return FALSE ;
	default:
		return FALSE ;
	}
}
