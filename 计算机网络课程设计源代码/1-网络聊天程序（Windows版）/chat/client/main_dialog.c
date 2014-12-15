/***
*main_dialog.c - main_dialog function
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines main_dialog function
*
*******************************************************************************/

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "resource.h"
#include "main_dialog.h"
#include "core.h"
#include "common.h"
#include "SaveMessage.h"

volatile HWND hMainDlg = NULL ;
char *receive_text = NULL ;
extern char szTitle[102] ;

extern int bEnd ;

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

BOOL CALLBACK MainDialog ( HWND hDlg , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	static HINSTANCE hInstance = NULL ;
	HICON hIcon ;
	HWND hGetText = NULL ;
	char szMsgBuffer[100] = "\0" ;
	int iLength = 0 ;
	PTSTR pstrBuffer = NULL ;

	switch ( uMsg )
	{
	case WM_INITDIALOG :
		hInstance = (HINSTANCE)lParam ;
		hIcon = LoadIcon ( hInstance , MAKEINTRESOURCE ( IDI_ICON ) ) ;
		SendMessage ( hDlg, WM_SETICON , TRUE , (LPARAM) hIcon ) ;
		SendMessage ( hDlg, WM_SETICON , FALSE , (LPARAM) hIcon ) ;
		receive_text = (char *) malloc ( 165536 * sizeof(char) ) ;
		hMainDlg = hDlg ;
		return FALSE ;
	case WM_COMMAND :
		switch ( LOWORD (wParam) )
		{
		case IDC_SEND:
			send_msg ( hInstance ) ;
			break ;
		case IDC_CLEAR:
			SetDlgItemText ( hDlg , IDC_GET_TEXT , "" ) ;
			break ;
		case IDC_SAVE:
			hGetText = GetDlgItem ( hDlg , IDC_GET_TEXT ) ;
			if ( hGetText == NULL )  // fail to get the handle to the message dialog
			{
				LoadString ( hInstance , IDS_UNKNOWN_SYSTEM_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
				MessageBox ( hDlg , szMsgBuffer , szTitle , MB_ICONERROR ) ;
			}
			else   // succeed in getting the handle to the message dialog
			{
				iLength = (int)SendMessage ( hGetText , WM_GETTEXTLENGTH , 0 , 0 ) ;
				pstrBuffer = (PTSTR) malloc ( (iLength+1) * sizeof (TCHAR) ) ;
				if ( pstrBuffer == NULL )
				{
					LoadString ( hInstance , IDS_MEMORY_FAILED , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
					MessageBox ( hDlg , szMsgBuffer , szTitle , MB_ICONERROR ) ;
				}
				else
				{
					if ( GetDlgItemText ( hDlg , IDC_GET_TEXT , pstrBuffer , iLength+1 ) )
					{
						if ( !SaveMessages ( hDlg , pstrBuffer ) )
						{
							free ( pstrBuffer ) ;
							pstrBuffer = NULL ;
							LoadString ( hInstance , IDS_FILE_OPEN_ERROR , szMsgBuffer , sizeof ( szMsgBuffer )  ) ;
							MessageBox ( hDlg , szMsgBuffer , szTitle , MB_ICONERROR ) ;
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
						MessageBox ( hDlg , szMsgBuffer , szTitle , MB_ICONWARNING ) ;
					}
				}
			}
			break ;
		case IDC_CLOSE:
			bEnd = 1 ;
			SendMessage ( hDlg, WM_CLOSE , 0 , 0 ) ;
			break ;
		}
		return FALSE ;
	case WM_CLOSE :
		CloseConnection ( ) ;
		EndDialog ( hDlg , 0 ) ;
		return FALSE ;
	}
	return FALSE ;
}

