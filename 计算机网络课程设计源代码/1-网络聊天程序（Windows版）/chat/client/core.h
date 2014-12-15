/***
*core.h - declarations for WinSock functions
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		This file declare the WinSock functions.
*
****/

#ifndef CORE_H
#define CORE_H

BOOL send_msg ( HINSTANCE hInstance ) ;
BOOL receive_msg ( const char *rec_msg , HINSTANCE hInstance ) ;
DWORD WINAPI connection (LPVOID threadNum) ;
void CloseConnection ( void ) ;

#endif
