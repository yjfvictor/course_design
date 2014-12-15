/***
*core.c - WinSock functions
*
*		Copyright (C) 2011, Victor Jianfei Ye and Zhou Kaifeng. All rights reserved.
*
*Purpose:
*		defines WinSock functions
*
*******************************************************************************/

#include <stdio.h>
#include <winsock2.h>
#include "resource.h"
#include "core.h"
#include "common.h"
#pragma comment(lib,"ws2_32.lib")

volatile int status = 0 ;
volatile int bEnd = 0 ;
volatile SOCKET cltSck;

extern char IP[20] ;
extern HWND hMainDlg ;
extern char szTitle[102] ;
extern HANDLE hThread ;

/***
*DWORD WINAPI connection ( LPVOID threadNum ) - connect to the server by WinSock technology
*
*Purpose:
*		Connect to the server.
*
*Entry:
*		LPVOID		threadNum		- the pointer to the handle of this instance
*
*Exit:
*		Success:  0
*
*Exceptions:
*
*******************************************************************************/

DWORD WINAPI connection ( LPVOID threadNum )
{
	HINSTANCE hInstance = * ( (HINSTANCE *)threadNum ) ;
	char szConnectionMessage[50] , szRecvBuf[65500] ;
	WSADATA wsaData;
	SOCKADDR_IN clientService;
	DWORD arg = 1 ;
	HWND hGetText = NULL ;
	int MinPos , MaxPos ;
	int bytesRecv = SOCKET_ERROR ;

	// Initialize
	int iResult = WSAStartup ( MAKEWORD (2,2), &wsaData );

	if ( iResult != NO_ERROR )
	{
		LoadString ( hInstance , IDS_SOCKET_INIT_ERROR , szConnectionMessage , sizeof ( szConnectionMessage ) ) ;
		print ( szConnectionMessage ) ;
		ExitProcess ( 1 ) ;
	}

	// Create socket
	cltSck = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if ( cltSck == INVALID_SOCKET )
	{
		WSACleanup() ;
		LoadString ( hInstance , IDS_SOCKET_CREATION_ERROR , szConnectionMessage , sizeof ( szConnectionMessage ) ) ;
		print ( szConnectionMessage );
		return 1 ;
	}

	// setup non-blocking mode
	//if ( ioctlsocket ( cltSck , FIONBIO , &arg ) == SOCKET_ERROR  )
	//{
	//	closesocket ( cltSck ) ;
	//	WSACleanup ( ) ;
	//	LoadString ( hInstance , IDS_NON_BLOCKING_MODE_ERROR , szConnectionMessage , sizeof ( szConnectionMessage ) ) ;
	//	print ( szConnectionMessage ) ;
	//	ExitProcess ( 1 ) ;
	//}

	// Connect to server

	clientService.sin_family = AF_INET ;
	clientService.sin_addr.s_addr = inet_addr( IP ) ;
	clientService.sin_port = htons( 2007 ) ;

	while ( connect ( cltSck, (SOCKADDR*) &clientService, sizeof(clientService)) == SOCKET_ERROR )
	{
		;
	}


	// Send and receive messages
	status = 1 ;

	while ( bEnd == 0 )
	{
		bytesRecv = recv ( cltSck, szRecvBuf, sizeof ( szRecvBuf ), 0 ) ;
		if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET )
		{
			shutdown ( cltSck , SD_BOTH ) ;
			closesocket ( cltSck ) ;
			WSACleanup ( ) ;
			LoadString ( hInstance , IDS_CONNECTION_CLOSED , szConnectionMessage , sizeof ( szConnectionMessage ) ) ;
			MessageBox ( hMainDlg , szConnectionMessage , szTitle , MB_ICONWARNING ) ;
			SendMessage ( hMainDlg, WM_CLOSE , 0 , 0 ) ;
			return 0 ;
		}
		else if ( bytesRecv != SOCKET_ERROR )
		{
			szRecvBuf[bytesRecv] = '\0' ;
			strcat ( szRecvBuf , "\r\n\r\n" ) ;
			receive_msg ( szRecvBuf , hInstance ) ;
			hGetText = GetDlgItem ( hMainDlg , IDC_GET_TEXT ) ;
			if ( GetScrollRange ( hGetText , SB_VERT , &MinPos , & MaxPos ) )
			{
				SetScrollPos ( hGetText , SB_VERT , MaxPos , TRUE ) ;
				SendMessage ( hGetText , WM_VSCROLL , MAKEWPARAM ( SB_BOTTOM , 0 ), (LPARAM)NULL ) ;
			}
		}
	}
	shutdown ( cltSck , SD_BOTH ) ;
	closesocket ( cltSck ) ;
	WSACleanup ( ) ;
	return 0 ;
}

/***
*void CloseConnection ( void ) - close the connection to the server
*
*Purpose:
*		Close the connection to the server.
*
*Exceptions:
*
*******************************************************************************/

void CloseConnection ( void )
{
	send ( cltSck,"\a", strlen("\a") , 0 ) ;
	TerminateThread ( hThread , 0 ) ;
	shutdown ( cltSck , SD_BOTH ) ;
	closesocket ( cltSck ) ;
	WSACleanup ( ) ;
}
