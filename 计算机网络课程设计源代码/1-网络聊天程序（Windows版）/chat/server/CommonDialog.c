/***
*CommonDialog.c - common dialog functions
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines common dialog functions
*
*******************************************************************************/

#include <windows.h>
#include <shlobj.h>

#ifdef _DEBUG
#pragma comment (linker, "/NODEFAULTLIB:\"LIBC\"" )
#else
#pragma comment (linker, "/OPT:NOREF" )
#endif

/***
*BOOL SaveAsDlg ( HWND hWnd , LPCTSTR pstrFilter , PTSTR pstrFilePath , PTSTR pstrFileName , LPCTSTR lpstrDefExt ) - show a "Save As" dialog
*
*Purpose:
*		Show a "Save As" dialog
*
*Entry:
*		HWND		hWnd			- the window that owns the dialog box
*		LPCTSTR		pstrFilter		- The first string in each pair 
*		is a display string that describes 
*		the filter (for example, "Text Files"), 
*		and the second string specifies the 
*		filter pattern (for example, "*.TXT").
*		e.g. TEXT ("Text Files (*.txt)\0*.txt\0") \
*				TEXT ("All Files (*.*)\0*.*\0" ) \
*				TEXT ("\0");
*		PTSTR		pstrFilePath	- returns the full file path
*		PTSTR		pstrFileName	- returns the file name
*		LPCTSTR		lpstrDefExt		- the default extension name
*
*Exit:
*		Success:  TRUE
*		Failure:  FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL SaveAsDlg ( HWND hWnd , LPCTSTR pstrFilter , PTSTR pstrFilePath , PTSTR pstrFileName , LPCTSTR lpstrDefExt )
{
	OPENFILENAME ofn ;
	pstrFilePath[0] = (TCHAR)'\0' ;
	pstrFileName[0] = (TCHAR)'\0' ;
	ofn.lStructSize = sizeof ( OPENFILENAME ) ;
	ofn.hwndOwner = hWnd ;
	ofn.hInstance = GetModuleHandle( NULL ) ;
	ofn.lpstrFilter = pstrFilter ;		// file filter
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0L ;
	ofn.nFilterIndex = 0L ;
	ofn.lpstrFile = pstrFilePath ;
	ofn.nMaxFile = MAX_PATH ;
	ofn.lpstrFileTitle = pstrFileName ;
	ofn.nMaxFileTitle = MAX_PATH ;
	ofn.lpstrInitialDir = NULL ;
	ofn.lpstrTitle = NULL ;		// the title bar of the dialog box
	ofn.Flags = OFN_OVERWRITEPROMPT ;
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = lpstrDefExt ;	// the default extension
	ofn.lCustData = 0L ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
	return GetSaveFileName ( &ofn ) ;
}

/***
*BOOL OpenDlg ( HWND hWnd , LPCTSTR pstrFilter , PTSTR pstrFilePath , PTSTR pstrFileName ) - show an "Open" dialog
*
*Purpose:
*		Show an "Open" dialog
*
*Entry:
*		HWND		hWnd			- the window that owns the dialog box
*		LPCTSTR		pstrFilter		- The first string in each pair 
*		is a display string that describes 
*		the filter (for example, "Text Files"), 
*		and the second string specifies the 
*		filter pattern (for example, "*.TXT").
*		e.g. TEXT ("Text Files (*.txt)\0*.txt\0") \
*				TEXT ("All Files (*.*)\0*.*\0" ) \
*				TEXT ("\0");
*		PTSTR		pstrFilePath	- returns the full file path
*		PTSTR		pstrFileName	- returns the file name
*
*Exit:
*		Success:  TRUE
*		Failure:  FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL OpenDlg ( HWND hWnd , LPCTSTR pstrFilter , PTSTR pstrFilePath , PTSTR pstrFileName )
{
	OPENFILENAME ofn ;
	pstrFilePath[0] = (TCHAR)'\0' ;
	pstrFileName[0] = (TCHAR)'\0' ;
	ofn.lStructSize = sizeof (OPENFILENAME) ;
	ofn.hwndOwner = hWnd ;
	ofn.hInstance = GetModuleHandle( NULL ) ;
	ofn.lpstrFilter = pstrFilter ;		// file filter
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter = 0L ;
	ofn.nFilterIndex = 0L ;
	ofn.lpstrFile = pstrFilePath ;
	ofn.nMaxFile = MAX_PATH ;
	ofn.lpstrFileTitle = pstrFileName ;
	ofn.nMaxFileTitle = MAX_PATH ;
	ofn.lpstrInitialDir = NULL ;
	ofn.lpstrTitle = NULL ;		// the title bar of the dialog box
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;
	ofn.nFileOffset = 0 ;
	ofn.nFileExtension = 0 ;
	ofn.lpstrDefExt = NULL ;	// the default extension
	ofn.lCustData = 0L ;
	ofn.lpfnHook = NULL ;
	ofn.lpTemplateName = NULL ;
	return GetOpenFileName ( &ofn ) ;
}

/***
*BOOL BrowseForFolder ( HWND hWnd , LPCTSTR pszTitle , LPTSTR pszPathName )
*
*Purpose:
*		Show an "browse for folder" dialog
*
*Entry:
*		HWND		hWnd			- the window that owns the dialog box
*		LPCTSTR		pszTitle		- The prompt in the browse-for-folder dialog box
*		LPTSTR		pszPathName		- returns the full folder path
*
*Exit:
*		Success:  TRUE
*		Failure:  FALSE
*
*Exceptions:
*
*******************************************************************************/

BOOL BrowseForFolder ( HWND hWnd , LPCTSTR pszTitle , LPTSTR pszPathName )
{
	BROWSEINFO browseInfo ;
	LPITEMIDLIST lpItemIDList;
	pszPathName[0] = '\0' ;
	browseInfo.hwndOwner = hWnd ;
	browseInfo.pidlRoot = 0 ;
	browseInfo.pszDisplayName = pszPathName ;
	browseInfo.lpszTitle = pszTitle ;
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS ;
	browseInfo.lpfn = NULL ;
	browseInfo.iImage = 0 ;
	if ( ( lpItemIDList = SHBrowseForFolder ( &browseInfo ) ) != NULL )
	{
		if ( SHGetPathFromIDList ( lpItemIDList , pszPathName ) )
			return TRUE ;
		else
			return FALSE ;
	}
	return FALSE ;
}
