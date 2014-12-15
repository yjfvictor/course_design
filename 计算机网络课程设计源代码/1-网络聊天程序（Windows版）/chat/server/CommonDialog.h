/***
*CommonDialog.h - declarations for Common Dialog
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		This file declare three important functions of the common dialog.
*
****/

#ifndef _MODULE_DIALOG_H
#define _MODULE_DIALOG_H

#ifndef _WINDOWS_
#include <windows.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif

BOOL SaveAsDlg ( HWND hWnd , LPCTSTR pstrFilter , PTSTR pstrFilePath , PTSTR pstrFileName , LPCTSTR lpstrDefExt ) ;
BOOL OpenDlg ( HWND hWnd , LPCTSTR pstrFilter , PTSTR pstrFilePath , PTSTR pstrFileName ) ;
BOOL BrowseForFolder ( HWND hWnd , LPCTSTR pszTitle , LPTSTR pszPathName ) ;

#ifdef  __cplusplus
}
#endif


#endif
