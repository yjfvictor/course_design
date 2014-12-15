/***
*control_clients.h - declarations for control_clients
*
*		Copyright (C) 2011, Zhou Kaifeng. All rights reserved.
*
*Purpose:
*		This file declares some function about the clients' information.
*
****/

#ifndef CONTROL_CLIENTS_H
#define CONTROL_CLIENTS_H

#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "resource.h"
#pragma comment(lib,"ws2_32.lib")

#define PEMTERLEN 255 //�趨����ĳ���
#define BUFLEN 65535  //�������ĳ���
#define TIME  1000      //���µ�ʱ����
#define SERVERLEN  2000 //��������������ͳ���

#include "client_structs.h"

int init_clients(void);                            //��ʼ���û�����
BOOL ins_clients(client vertex) ;               //����һ���û���������
int del_clients(void);                             //ɾ���Ѷ��ߵ��û�
BOOL dst_clients(void);                             //ע���û�����
void getsocket(client clt,SOCKET *sck);						    //�õ��û���socket;
void getstate(client clt,char *state);                          //�õ��û�������״̬
void getaddr(client clt,char *addr_str,unsigned short *port);   //�õ��û���ip�Ͷ˿�
pclient next(pclient bef);                                      //������һ���û�
int get_online_count(void);                        //�õ������û�������
pclient getlist_head(void);                        //�õ��û��б�ĵ�һ���û���û���û�ʱ����Ϊ��
BOOL headmatch(const char *n,const char *m) ;                                //�ַ����ײ�ƥ��
void getsubstr(char *s,char *sub,int begin,int end);            //�õ�ָ�����ִ�
void show(pclient clt);                                         //��ʾ�û���Ϣ
void sendall(const char *bufer) ;				    //���͸������û���Ϣ
void operate_msg(pclient clt,char *msg);      //�ͻ�����Ϣ����
//��������ʼ��һ���û�
void set_client(client *clt,SOCKET sck,SOCKADDR_IN addr , BOOL state , SYSTEMTIME time , pclient next) ;
#endif