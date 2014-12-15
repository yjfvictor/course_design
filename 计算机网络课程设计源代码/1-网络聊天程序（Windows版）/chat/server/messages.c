/***
*messages.c - messages treating functions
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		defines messages treating functions
*
*******************************************************************************/

#include <windows.h>
#include "resource.h"
#include "client_structs.h"
void refresh ( void );

#define BUFLEN 65500

char buf_server[BUFLEN]="\0";
extern volatile BOOL state ;

pclient getlist_head(void) ;
void operate_msg (pclient clt,char *msg) ;
void getsocket(client clt,SOCKET *sck) ;
pclient next(pclient bef);
void sendall(const char *bufer) ;
BOOL ShowMessage ( LPCTSTR szMessage ) ;

/***
*DWORD APIENTRY GetMessageFromClient(LPVOID threadNum) - get message from client
*
*Purpose:
*		Get message from client.
*
*Entry:
*		LPVOID		threadNum			- the thread number pass to the thread, useless.
*
*Exit:
*		Return 0
*
*Exceptions:
*
*******************************************************************************/

DWORD APIENTRY GetMessageFromClient(LPVOID threadNum)
{
	pclient pclt;
	SOCKET sck;
	int bytesRecv ;
	char szBufferFromClient[BUFLEN] = "\0" ;
	while(state)
	{
		pclt = getlist_head();
		while (pclt)
		{
			getsocket((*pclt),&sck);
			bytesRecv = recv (sck,szBufferFromClient,sizeof(szBufferFromClient),0) ;
			if (bytesRecv == 0 || bytesRecv == WSAECONNRESET || szBufferFromClient[0]== '\a' )
			{
				pclt->state= FALSE ;
				szBufferFromClient[0] = '0' ;
				refresh();
			}
			else if( bytesRecv != -1 )
			{
				szBufferFromClient[bytesRecv-1] = '\0' ;
				operate_msg (pclt,szBufferFromClient) ;
			}
			pclt = next(pclt);
		}
		Sleep(10);
	}
	return 0 ;
}

/***
*void SendMessageToClient( HINSTANCE hInstance , const char *szMessageFromServer) - send message from client
*
*Purpose:
*		Send message from client.
*
*Entry:
*		HINSTANCE		hInstance				- the handle to this instance
*		const char *	szMessageFromServer		- the constant character pointer to the message from server
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void SendMessageToClient( HINSTANCE hInstance , const char *szMessageFromServer)
{
	char szBufferServer[BUFLEN] = "\0" ;
	LoadString ( hInstance , IDS_SERVER_PROMPT , szBufferServer , sizeof (szBufferServer) ) ;
	strcat(szBufferServer, szMessageFromServer );
	ShowMessage ( szBufferServer ) ;
	sendall(szBufferServer);
}
