#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <boost/thread.hpp>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "ws2_32.lib" )
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
typedef int SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#endif

#define LISTENING_PORT	8080
#define MAX_BUF 800000
#define MAX_CONNECTION_TRY 5

void parseDomainNameAndPortFromUrl( const char * url, char * domain_name, unsigned short & port )
{
	for ( int i = 0 ; url[i] != '\0'; ++ i )
	{
		if ( url[i] == '/' && url[i+1] == '/' )
		{
			for ( int j = i + 2; url[j] != '\0'; ++j )
			{
				if ( url[j] == ':' || url[j] == '/' )
				{
					memset( domain_name, 0, strlen(url) );
					memcpy( domain_name, url + i + 2, j - i - 2 );
					if ( url[j] == ':' )
					{
						port = 0;
						for ( int k = j+1 ; url[k] != '/' ; ++ k )
						{
							port *= 10;
							port += url[k] - '0';
						}
					}
					else
						port = 80;
					return;
				}
			}
			throw 400;
			return;
		}
	}
	throw 400;
}

struct sockaddr_in GetAddrFromHttpHeader( const char * HttpHeader )
{
	const char * method_end = strchr( HttpHeader, ' ' );
	const char * url_end = strchr( 1 + method_end, ' ' );

	char * method = new char[method_end - HttpHeader + 1 ];
	memset( method, 0, method_end - HttpHeader + 1 );
	strncpy( method, HttpHeader, method_end - HttpHeader );
	if ( !strcmp( method, "CONNECT" ) )
	{
		delete [] method;
		method = NULL;
		throw 405;
	}
	delete [] method;
	method = NULL;

	char * url = new char[url_end - method_end + 1];
	memset( url, 0, url_end - method_end + 1 );
	strncpy( url, method_end + 1, url_end - method_end - 1 );
	char * domain_name = new char[strlen(url)];
	unsigned short port;
	try
	{
		parseDomainNameAndPortFromUrl( url, domain_name, port );
	}
	catch( int errorCode )
	{
		delete [] url;
		delete [] domain_name;
		throw errorCode;
	}
	
	hostent * host = gethostbyname( domain_name );
	if ( host == NULL )
	{
		delete [] url;
		delete [] domain_name;
		throw 502;
	}
	struct sockaddr_in SockAddr;
	memset( &SockAddr, 0, sizeof(SockAddr) );
	SockAddr.sin_family = host->h_addrtype;
#ifdef _WIN32
	SockAddr.sin_addr.s_net = (unsigned char)(host->h_addr_list[0][0]);
	SockAddr.sin_addr.s_host = (unsigned char)(host->h_addr_list[0][1]);
	SockAddr.sin_addr.s_lh = (unsigned char)(host->h_addr_list[0][2]);
	SockAddr.sin_addr.s_impno = (unsigned char)(host->h_addr_list[0][3]);
#else
	((unsigned char *)&(SockAddr.sin_addr))[0] = (unsigned char)(host->h_addr_list[0][0]);
	((unsigned char *)&(SockAddr.sin_addr))[1] = (unsigned char)(host->h_addr_list[0][1]);
	((unsigned char *)&(SockAddr.sin_addr))[2] = (unsigned char)(host->h_addr_list[0][2]);
	((unsigned char *)&(SockAddr.sin_addr))[3] = (unsigned char)(host->h_addr_list[0][3]);
#endif
	SockAddr.sin_port = htons( port );

	printf( "Domain name: %s\n", domain_name );
	printf( "Server IP: %s\n", inet_ntoa(SockAddr.sin_addr) );
	printf( "Port: %hu\n", port );

	delete [] domain_name;
	delete [] url;

	return SockAddr;
}

void HTTP_proxy( SOCKET * pBrowserSocket )
{
	char buffer[MAX_BUF+1];
	int bytesSent, bytesRecv;
#ifdef _WIN32
	int timeout = 1000;
#else
	struct timeval timeout = {3,0};
#endif
	setsockopt( *pBrowserSocket, SOL_SOCKET, SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
	memset( buffer, 0, sizeof(buffer) );
	if ( ( bytesRecv = recv( *pBrowserSocket, buffer, MAX_BUF, 0 ) ) <= 0 )
	{
#ifdef _WIN32
		shutdown( *pBrowserSocket, SD_BOTH );
		closesocket( *pBrowserSocket );
#else
		shutdown( *pBrowserSocket, SHUT_RDWR );
		close( *pBrowserSocket );
#endif
		delete pBrowserSocket;
		return;
	}
	buffer[bytesRecv] = '\0';
	try
	{
		SOCKET clientSocketOfWebServer = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if ( clientSocketOfWebServer == INVALID_SOCKET )
		{
#ifdef _WIN32
			shutdown( *pBrowserSocket, SD_BOTH );
			closesocket( *pBrowserSocket );
#else
			shutdown( *pBrowserSocket, SHUT_RDWR );
			close( *pBrowserSocket );
#endif
			delete pBrowserSocket;
			return;
		}
		struct sockaddr_in WebServerSockAddr;
		WebServerSockAddr = GetAddrFromHttpHeader( buffer );
		setsockopt( clientSocketOfWebServer, SOL_SOCKET, SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
		int connectResult;
		for ( int i = 0 ; i < MAX_CONNECTION_TRY ; i ++ )
		{
			connectResult = connect( clientSocketOfWebServer, (const struct sockaddr *)&WebServerSockAddr,
				sizeof(WebServerSockAddr) );
			if ( connectResult != SOCKET_ERROR )
				break;
		}
		if ( connectResult == SOCKET_ERROR )
		{
#ifdef _WIN32
			shutdown( *pBrowserSocket, SD_BOTH );
			shutdown( clientSocketOfWebServer, SD_BOTH );
			closesocket( *pBrowserSocket );
			closesocket( clientSocketOfWebServer );
#else
			shutdown( *pBrowserSocket, SHUT_RDWR );
			shutdown( clientSocketOfWebServer, SHUT_RDWR );
			close( *pBrowserSocket );
			close( clientSocketOfWebServer );
#endif
			delete pBrowserSocket;
			return;
		}
		bytesSent = send( clientSocketOfWebServer, buffer, bytesRecv, 0 );
		if ( bytesSent <= 0 )
		{
#ifdef _WIN32
			shutdown( *pBrowserSocket, SD_BOTH );
			shutdown( clientSocketOfWebServer, SD_BOTH );
			closesocket( *pBrowserSocket );
			closesocket( clientSocketOfWebServer );
#else
			shutdown( *pBrowserSocket, SHUT_RDWR );
			shutdown( clientSocketOfWebServer, SHUT_RDWR );
			close( *pBrowserSocket );
			close( clientSocketOfWebServer );
#endif
			delete pBrowserSocket;
			return;
		}
		while ( ( bytesRecv = recv( clientSocketOfWebServer, buffer, MAX_BUF, 0 ) ) > 0 )
		{
			bytesSent = send( *pBrowserSocket, buffer, bytesRecv, 0 );
			if ( bytesSent <= 0 )
				break;
		}
#ifdef _WIN32
		shutdown( clientSocketOfWebServer, SD_BOTH );
		closesocket( clientSocketOfWebServer );
#else
		shutdown( clientSocketOfWebServer, SHUT_RDWR );
		close( clientSocketOfWebServer );
#endif
	}
	catch ( int num )
	{
		const char * sendBuf = NULL;
		if ( num == 400 )
		{
			puts( "400 Bad Request" );
			sendBuf = "HTTP/1.0 400 Bad Request\r\n"
				"Content-Type: text/plain; charset=UTF-8\r\n"
				"Connection: close\r\n"
				"Content-Length: 0\r\n\r\n";
		}
		else if ( num == 502 )
		{
			puts( "502 Bad Gatway" );
			sendBuf = "HTTP/1.0 502 Bad Gateway\r\n"
				"Content-Type: text/plain; charset=UTF-8\r\n"
				"Connection: close\r\n"
				"Content-Length: 0\r\n\r\n";
		}
		else if ( num == 405 )
		{
			puts( "405 Method Not Allowed" );
			sendBuf = "HTTP/1.0 405 Method Not Allowed\r\n"
				"Content-Type: text/plain; charset=UTF-8\r\n"
				"Connection: close\r\n"
				"Content-Length: 0\r\n\r\n";
		}
		else
		{
			puts( "503 Service Unavailable" );
			sendBuf = "HTTP/1.0 503 Service Unavailable\r\n"
				"Content-Type: text/plain; charset=UTF-8\r\n"
				"Connection: close\r\n"
				"Content-Length: 0\r\n\r\n";
		}
		bytesSent = send( *pBrowserSocket, sendBuf, strlen(sendBuf), 0 );
	}
	catch( ... )
	{
		const char * sendBuf = "HTTP/1.0 503 Service Unavailable\r\n"
			"Content-Type: text/plain; charset=UTF-8\r\n"
			"Connection: close\r\n"
			"Content-Length: 0\r\n\r\n";
		bytesSent = send( *pBrowserSocket, sendBuf, strlen(sendBuf), 0 );
	}
#ifdef _WIN32
	shutdown( *pBrowserSocket, SD_BOTH );
	closesocket( *pBrowserSocket );
#else
	shutdown( *pBrowserSocket, SHUT_RDWR );
	close( *pBrowserSocket );
#endif
	delete pBrowserSocket;
}

int main()
{
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = ::WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
		return EXIT_FAILURE;
	if ( LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1 )
	{
		fputs( "WSAStartup failed\n", stderr );
		::WSACleanup();
		return EXIT_FAILURE;
	}
#endif
	SOCKET proxyServerSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( proxyServerSocket == INVALID_SOCKET )
	{
		fputs( "Socket initailizing failed\n", stderr );
#ifdef _WIN32
		::WSACleanup();
#endif
		return EXIT_FAILURE;
	}
	struct sockaddr_in proxyServerSockAddr;
	memset( &proxyServerSockAddr, 0, sizeof(proxyServerSockAddr) );
	proxyServerSockAddr.sin_family = AF_INET;
	proxyServerSockAddr.sin_addr.s_addr = INADDR_ANY;
	proxyServerSockAddr.sin_port = htons( LISTENING_PORT );
	if ( bind( proxyServerSocket, (struct sockaddr *)&proxyServerSockAddr,
		sizeof(proxyServerSockAddr) ) == SOCKET_ERROR )
	{
		fputs( "Bind failed\n", stderr );
#ifdef _WIN32
		shutdown( proxyServerSocket, SD_BOTH );
		closesocket( proxyServerSocket );
		::WSACleanup();
#else
		shutdown( proxyServerSocket, SHUT_RDWR );
		close( proxyServerSocket );
#endif
		return EXIT_FAILURE;
	}
	if ( listen( proxyServerSocket, 1 ) == SOCKET_ERROR )
	{
		fputs( "Listen failed\n", stderr );
#ifdef _WIN32
		shutdown( proxyServerSocket, SD_BOTH );
		closesocket( proxyServerSocket );
		::WSACleanup();
#else
		shutdown( proxyServerSocket, SHUT_RDWR );
		close( proxyServerSocket );
#endif
		return EXIT_FAILURE;
	}
#ifndef _WIN32
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction( SIGPIPE, &sa, 0 );
#endif
	SOCKET * pBrowserSocket;
	while ( true )
	{
		pBrowserSocket = new SOCKET;
		do
		{
			*pBrowserSocket = accept ( proxyServerSocket, NULL, NULL );
			if ( *pBrowserSocket != SOCKET_ERROR )
				puts( "Browser connected" );
		} while ( *pBrowserSocket == SOCKET_ERROR );
		try
		{
			boost::thread thrd(HTTP_proxy, pBrowserSocket);
		}
		catch( ... )
		{
		}
	}
#ifdef _WIN32
	::WSACleanup();
#endif
	return EXIT_SUCCESS;
}
