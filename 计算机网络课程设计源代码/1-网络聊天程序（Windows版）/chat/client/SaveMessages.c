/***
*SaveMessages.c - message-saving function
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines the message-saving function
*
*******************************************************************************/

#include <stdio.h>
#include <windows.h>
#include "CommonDialog.h"

/***
*BOOL SaveMessages ( HWND hDlg , LPCTSTR pstrBuffer ) - the function to save messages to the text file
*
*Purpose:
*		Save messages to the text file.
*
*Entry:
*		HWND			hDlg			- the handle to the dialog
*		LPCTSTR			pstrBuffer		- the constant character pointer to the string of the messages
*
*Exit:
*		Success: TRUE
*		Failure: FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL SaveMessages ( HWND hDlg , LPCTSTR pstrBuffer )
{
	FILE * fp = NULL ;
	TCHAR pstrFilePath[MAX_PATH] = TEXT("\0") ;
	TCHAR pstrFileName[MAX_PATH] = TEXT("\0") ;
	LPCTSTR pstrFilter = TEXT ("Text Files (*.txt)\0*.txt\0") \
							TEXT ("All Files (*.*)\0*.*\0" ) \
							TEXT ("\0") ;

	if ( SaveAsDlg ( hDlg , pstrFilter , pstrFilePath , pstrFileName , TEXT("txt") ) )
	{
		fp = fopen ( pstrFilePath , TEXT("w") ) ;
		if (fp == NULL )
			return FALSE ;
		fprintf ( fp , pstrBuffer ) ;
		fclose (fp) ;
		fp = NULL ;
	}
	return TRUE ;
}
