#include <winsock2.h>
#include "common.h"
#include "resource.h"
#include "client_structs.h"

volatile BOOL state = FALSE ;
volatile HWND hCurDlg = NULL ;

void refresh(void) ;
int init_clients(void);                            // initialize users' linklist
void set_client(client *clt,SOCKET sck,SOCKADDR_IN addr,char *user,char *password,char *nickname,int state,SYSTEMTIME time,struct client * next) ;
int ins_clients(client vertex);               // insert a user into a linklist
int dst_clients(void);                             //destroy the users' linklist

DWORD APIENTRY GetMessageFromClient(LPVOID threadNum) ;

DWORD APIENTRY WinSock ( LPVOID threadNum )
{
	// call Socket library (initialize)
	WSADATA sd;
	SYSTEMTIME nowtime;
	WORD ver=0x0101;
	SOCKET svrSck,sck;
	DWORD arg;
	SOCKADDR_IN addr;
	fd_set rfd,efd;
	SOCKADDR_IN ad;
	struct timeval timeout;
	int len;
	char szMessage[1000];
	client clt;
	HINSTANCE hInstance = *(HINSTANCE *) threadNum ;

	HANDLE hThread = NULL ;
	DWORD ThreadID = 0L ;
	

	init_clients(); // Initialize users' list
	if(WSAStartup(ver,&sd))
	{
		LoadString ( hInstance , IDS_INIT_FAILURE , szMessage , sizeof (szMessage ) ) ;
		MessageBox ( hCurDlg , szMessage , szCaption , MB_ICONERROR ) ;
		ExitProcess ( EXIT_FAILURE ) ;
	}
	// Create Socket
	svrSck=socket(AF_INET,SOCK_STREAM,0);
	if(svrSck==INVALID_SOCKET)
	{
		WSACleanup ( );
		LoadString ( hInstance , IDS_CREATION_FAILED , szMessage , sizeof ( szMessage ) ) ;
		MessageBox ( hCurDlg , szMessage , szCaption , MB_ICONERROR ) ;
		ExitProcess ( EXIT_FAILURE ) ;
	}
	// Set Socket running mode
	arg=1;
	ioctlsocket(svrSck,FIONBIO,&arg); // Set non-blocking mode
	// bind
	addr.sin_family=AF_INET;
	addr.sin_port=htons(2007);
	addr.sin_addr.s_addr = htonl(ADDR_ANY);
	if(bind(svrSck,(SOCKADDR*)&addr,sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		shutdown(svrSck,SD_BOTH);
		closesocket(svrSck);
		WSACleanup();
		LoadString ( hInstance , IDS_BIND_FAILED , szMessage , sizeof ( szMessage ) ) ;
		MessageBox ( hCurDlg , szMessage , szCaption , MB_ICONERROR ) ;
		ExitProcess ( EXIT_FAILURE ) ;
	}
	// start listening
	if( listen(svrSck,10) == SOCKET_ERROR )
	{
		closesocket ( svrSck ) ;
		LoadString ( hInstance , IDS_LISTEN_FALED , szMessage , sizeof ( szMessage ) ) ;
		MessageBox ( hCurDlg , szMessage , szCaption , MB_ICONERROR ) ;
		ExitProcess ( EXIT_FAILURE ) ;
	}

	state = TRUE ;
	hThread = CreateThread (NULL, 0, GetMessageFromClient, 0, 0, &ThreadID) ;
	while ( state ) // Wait for client connection
	{
		FD_ZERO(&rfd); // used for judging whether there is connection
		FD_ZERO(&efd); // used for judging whether there's any error
		FD_SET(svrSck,&rfd) ;
		FD_SET(svrSck,&efd) ;
		timeout.tv_sec=0 ;
		timeout.tv_usec=10000 ; // set timeout as 10 second
		if( select(0,&rfd,NULL,&efd,&timeout) )
		{
			if(FD_ISSET(svrSck,&rfd)) // if there's a connction
			{
				len = sizeof(SOCKADDR_IN);
				sck = accept(svrSck,(SOCKADDR*)&ad,&len);
				if( sck != INVALID_SOCKET )
				{
					GetLocalTime(&nowtime);
					set_client (&clt,sck,ad,"","","",TRUE,nowtime,NULL);
					ins_clients(clt);
					refresh( ) ;
				}
			}
			else if( FD_ISSET( svrSck,&efd ) ) // Something goes wrong
			{
				shutdown(svrSck,SD_BOTH);
				closesocket(svrSck);
				WSACleanup();
				LoadString ( hInstance , IDS_SOCKET_ERROR , szMessage , sizeof ( szMessage ) ) ;
				MessageBox ( hCurDlg , szMessage , szCaption , MB_ICONERROR ) ;
				ExitProcess ( EXIT_FAILURE ) ;
			}
		}
		Sleep(10);
	}
	TerminateThread ( hThread , 0 ) ;
	CloseHandle ( hThread ) ;
	hThread = NULL ;
	dst_clients( );
	shutdown(svrSck,SD_BOTH);
	closesocket(svrSck);
	WSACleanup();
	return 0L;
}
