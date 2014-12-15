/***
*client_structs.h - definition of the structure of the client
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		This file defines the structure of the client.
*
****/

#ifndef _CLIENT_STRUCTS_H
#define _CLIENT_STRUCTS_H

typedef volatile struct client
{
   SOCKET sck;
   SOCKADDR_IN addr;
   volatile BOOL state;
   SYSTEMTIME starttime;
   SYSTEMTIME latesttime;
   struct client volatile *next;
} client,*pclient;

typedef struct list
{
	int total_online;
	int total;
	pclient head;
	pclient tail;
}list , *plist;


#endif
