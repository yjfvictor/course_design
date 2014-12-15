/***
*message_process.c - message_process functions
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines message_process functions
*
*******************************************************************************/

#include <windows.h>
#include <string.h>
#include "common.h"
#include "resource.h"

extern volatile HWND hMainDlg ;
extern SOCKET cltSck;
extern char szTitle[102] ;
extern char *receive_text ;

/***
*BOOL receive_msg ( const char *rec_msg , HINSTANCE hInstance ) - the function to receive the message from the server
*
*Purpose:
*		Receive the messages from the server and send to the IDC_GET_TEXT edit box.
*
*Entry:
*		const char *	rec_msg			- the string received from the server
*		HINSTANCE		hInstance		- the handle to this instance 
*
*Exit:
*		Success: TRUE
*		Failure: FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL receive_msg ( const char *rec_msg , HINSTANCE hInstance )
{
	long length = 0 ;
	char *temp = NULL ;
	char szSevereWarning[15] ;
	char szMemoryError[200] ;
	if ( rec_msg[0] == '\a' )
		return FALSE ;
	if ( ( length = SendMessage ( GetDlgItem ( hMainDlg , IDC_GET_TEXT ) , WM_GETTEXTLENGTH , 0 , 0 ) ) > 165536 )
	{
		temp = (char *) realloc ( receive_text , ( length + 65536 ) * sizeof(char) ) ;
		if ( temp != NULL )
			receive_text = temp ;
		else
		{
			LoadString ( hInstance , IDS_SEVERE_WARNING , szSevereWarning , sizeof ( szSevereWarning ) ) ;
			LoadString ( hInstance , IDS_MEMORY_ERROR , szMemoryError , sizeof ( szMemoryError ) ) ;
			if ( MessageBox ( hMainDlg , szMemoryError , szSevereWarning , MB_YESNO|MB_ICONWARNING ) == IDYES )
			{
				strcpy ( receive_text , "" ) ;
				free ( receive_text ) ;
				receive_text = (char *) malloc ( 165536 * sizeof(char) ) ;
			}
			else
			{
				free ( receive_text ) ;
				receive_text = NULL ;
				ExitProcess ( 0 ) ;
			}
		}
	}
	GetDlgItemText ( hMainDlg , IDC_GET_TEXT , receive_text , 100000 ) ;
	strcat ( receive_text , rec_msg ) ;
	return SetDlgItemText ( hMainDlg , IDC_GET_TEXT , receive_text ) ;
}

/***
*BOOL send_msg ( HINSTANCE hInstance ) - the function of sending the message to the server
*
*Purpose:
*		Send the messages to the server from the IDC_SEND_TEXT edit box.
*
*Entry:
*		HINSTANCE		hInstance		- the handle to this instance 
*
*Exit:
*		Success: TRUE
*		Failure: FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL send_msg ( HINSTANCE hInstance )
{
	char send_text [60000] , szSendingError[50] ;
	HWND hWnd = GetDlgItem ( hMainDlg , IDC_SEND_TEXT ) ;
	SetFocus ( hWnd ) ;
	GetDlgItemText ( hMainDlg , IDC_SEND_TEXT , send_text , sizeof(send_text) ) ;
	SetDlgItemText ( hMainDlg , IDC_SEND_TEXT , "" ) ;
	if ( send ( cltSck,send_text, strlen(send_text)+1 , 0 ) == SOCKET_ERROR )
	{
		LoadString ( hInstance , IDS_SENDING_ERROR , szSendingError , sizeof ( szSendingError ) ) ;
		MessageBox ( hMainDlg , szSendingError , szTitle , MB_ICONERROR ) ;
		return FALSE ;
	}
	Sleep(10) ;
	
	return TRUE ;
}

/***
*int print ( const char *msg ) - the function to show a message box from the given string
*
*Purpose:
*		Show a message box from the given string.
*
*Entry:
*		const char *	msg		- the pointer to the given string
*
*Exit:
*		Return IDOK
*
*Exceptions:
*
*******************************************************************************/

int print ( const char *msg )
{
	return MessageBox ( hMainDlg , msg , szTitle , MB_ICONERROR ) ;
}
