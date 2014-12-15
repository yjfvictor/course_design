/***
*control_clients.c - control_clients functions
*
*		Copyright (C) 2011, Zhou Kaifeng. All rights reserved.
*
*Purpose:
*		defines control_clients functions
*
*******************************************************************************/

#include"control_clients.h"
#pragma warning( disable : 4090 4022 )

list clients;
const plist client_list = &clients;

BOOL ShowMessage ( LPCTSTR szMessage ) ;

int init_clients(void) // initialize users' linklist
{
	client_list->total=0;
	client_list->head=NULL;
	client_list->tail=NULL;
	return TRUE;
}

BOOL ins_clients(client vertex) // insert a user into the linklist
{
	pclient pot=(pclient)malloc(sizeof(client));
	if(pot)
	{
		(*pot) = vertex;
		pot->next=NULL;
		if(client_list->head==NULL)
			client_list->head=pot;
		if(client_list->tail!=NULL)
			client_list->tail->next=pot;
		client_list->tail=pot;
		(client_list->total_online)++;
		(client_list->total)++;
		return TRUE;	
	}
	else
		return FALSE;
}

int del_clients(void) // delete offline users
{
	pclient pot=client_list->head,p,top,head;
	head=pot;
	top=pot;
	while(pot)
	{
		p=pot->next;
		if(!(pot->state)) // judge whether the user is online or not
		{
			if(pot==top)
				top=p;
			if(pot==head)
				head=p;
			else top->next=p;
			shutdown(pot->sck,SD_BOTH);
			closesocket(pot->sck);
			free(pot);
			(client_list->total_online)--;
		}
		else
			top=pot;
		pot=p;	
	}
	client_list->tail=top;
	client_list->head=head;
	if(client_list->tail!=NULL)client_list->tail->next=NULL;
    return	TRUE;
}

BOOL dst_clients(void) // log off users' linklist
{
	pclient pot=client_list->head,p=NULL;
	if(client_list->head != NULL)
	{
		pot=pot->next;
		shutdown(client_list->head->sck,SD_BOTH);
		closesocket(client_list->head->sck);
		free(client_list->head);
	}
	if(pot != NULL)
	{
		p=pot->next;
		while( p != NULL )
		{
			shutdown(pot->sck,SD_BOTH);
			closesocket(pot->sck);
			free(pot);
			pot=p;
			p=pot->next;
		}
		shutdown(pot->sck,SD_BOTH);
		closesocket(pot->sck);
		free(pot);
	}
	client_list->total=0;
	client_list->total_online=0;
	return TRUE;
}
void sendall(const char *bufer)
{
	pclient pclt;
	SOCKET sck;
	pclt=getlist_head();
	while(pclt)
	{ 
		getsocket((*pclt),&sck);
		if ( send ( sck , bufer , strlen(bufer)+1 , 0 ) == SOCKET_ERROR )
		{
			// sending error
		}
		pclt = next(pclt);
	}
}


pclient next(pclient bef) // visit the next user
{
	if(bef)
		return bef->next;
	else return NULL;
}

// create and initialize a user

void set_client(client *clt,SOCKET sck,SOCKADDR_IN addr , BOOL state , SYSTEMTIME time , pclient next)
{
	clt->sck=sck;
	clt->addr=addr;
	clt->state=state;
	clt->starttime=time;
	clt->latesttime=time;
	clt->next=next;
}

void getaddr(client clt,char *addr_str,unsigned short *port)// get user's IP and port
{
	strcpy(addr_str,inet_ntoa(clt.addr.sin_addr));
	*port=ntohs(clt.addr.sin_port);
}

pclient getlist_head(void) // get the first user in the user list. If no users, return NULL
{
	return (client_list->head);
}

int get_online_count(void) // get the population of the online users
{
	return client_list->total_online;
}


void getsocket(client clt,SOCKET *sck) // get user's Socket
{
	(*sck)=clt.sck;
}

void getstate(client clt,char *state) // get user's online state
{
	*state=clt.state;
}

void getOnlineUserList (char* szOnlineUserList)
{
	char addr_str[20] ="\0" ;
	char port_str[5] = "\0" ;
	unsigned short port = (unsigned short)0 ;
	pclient p=client_list->head ;
	strcpy ( szOnlineUserList , "\0" ) ;
	while(p)
	{
		if(p->state)
		{
			getaddr ( *p , addr_str , &port ) ;
			sprintf ( port_str , "%hu" ,port ) ;
			strcat(szOnlineUserList,addr_str);
			strcat(szOnlineUserList,":");
			strcat(szOnlineUserList,port_str);
			strcat(szOnlineUserList,"\r\n") ;
		}
		p=p->next;
	}
}

BOOL headmatch(const char *n,const char *m) // match the first few letters of the string
{
	int i,len1=strlen(m),len2=strlen(n);
	if(len2<len1)
		return FALSE;
	else
	{
		for(i=0;i<len1;i++)
		{
			if(n[i] != m[i])
				return FALSE;
		}
	}
	return TRUE;
}
void getsubstr(char *s,char *sub,int begin,int end) // get the designated string
{
	int i;
	if(begin<=end)
	{
		for(i=begin;i<=end;i++)
			sub[i-begin]=s[i];
		sub[i-begin]='\0';
	}
}


void operate_msg(pclient clt,char *msg) // operate the message of the client
{
	char szBufSend[BUFLEN+100]="\0",ip[16]="\0";
	char list[5000]="",adr[16];
	unsigned short port;
	getaddr ( (*clt) , adr , &port ) ;
	sprintf(szBufSend,"%s:%d:\r\n%s",adr,port,msg);
	sendall(szBufSend);
	ShowMessage ( szBufSend ) ;
}
