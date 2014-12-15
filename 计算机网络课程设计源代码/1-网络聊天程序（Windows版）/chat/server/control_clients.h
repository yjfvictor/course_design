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

#define PEMTERLEN 255 //设定命令的长度
#define BUFLEN 65535  //缓冲区的长度
#define TIME  1000      //更新的时间间隔
#define SERVERLEN  2000 //服务器方的最大发送长度

#include "client_structs.h"

int init_clients(void);                            //初始化用户链表
BOOL ins_clients(client vertex) ;               //插入一个用户到链表中
int del_clients(void);                             //删除已断线的用户
BOOL dst_clients(void);                             //注销用户链表
void getsocket(client clt,SOCKET *sck);						    //得到用户的socket;
void getstate(client clt,char *state);                          //得到用户的在线状态
void getaddr(client clt,char *addr_str,unsigned short *port);   //得到用户的ip和端口
pclient next(pclient bef);                                      //访问下一个用户
int get_online_count(void);                        //得到在线用户的数量
pclient getlist_head(void);                        //得到用户列表的第一个用户，没有用户时返回为空
BOOL headmatch(const char *n,const char *m) ;                                //字符串首部匹配
void getsubstr(char *s,char *sub,int begin,int end);            //得到指定的字串
void show(pclient clt);                                         //显示用户信息
void sendall(const char *bufer) ;				    //发送给所有用户信息
void operate_msg(pclient clt,char *msg);      //客户端消息处理
//建立并初始化一个用户
void set_client(client *clt,SOCKET sck,SOCKADDR_IN addr , BOOL state , SYSTEMTIME time , pclient next) ;
#endif