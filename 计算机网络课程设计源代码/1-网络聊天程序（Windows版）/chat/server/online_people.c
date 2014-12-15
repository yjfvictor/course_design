/***
*online_people.c - functions that show the people online
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines the functions that show the people online
*
*******************************************************************************/

#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include "online_users.h"

extern PHOnlineUserInfo phOnlineUserInfo ;
extern volatile BOOL state ;

int del_clients(void) ;
int get_online_count(void);
void getOnlineUserList (char* szOnlineUserList) ;

/***
*void refresh ( void ) - refresh the people online
*
*Purpose:
*		Refresh the people online
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void refresh ( void )
{
	char szOnlineUsers[30] = "\0" ;
	char szOnlineUserList[10000] = "\0" ;
	getOnlineUserList (szOnlineUserList) ;
	sprintf ( szOnlineUsers , "%d\0" , get_online_count () ) ;
	SendMessage ( phOnlineUserInfo->hLableOnlinePeople , WM_SETTEXT , 0 , (LPARAM)(PCSTR)szOnlineUsers ) ;
	SendMessage ( phOnlineUserInfo->hOnlineUserList , WM_SETTEXT , 0 , (LPARAM)(PCSTR)szOnlineUserList ) ;
}

/***
*DWORD APIENTRY SetOnlinePeople ( LPVOID threadNum ) - a thread that shows the people online
*
*Purpose:
*		Shows the people online every six seconds.
*
*Entry:
*		LPVOID		threadNum		- the parameter that pass to this thread, useless.
*
*Exit:
*		Return 0
*
*Exceptions:
*
*******************************************************************************/

DWORD APIENTRY SetOnlinePeople ( LPVOID threadNum )
{
	while(state)
	{
		del_clients( ) ;
		refresh ( ) ;
		Sleep ( 6000 ) ;
	}
	return 0 ;
}
