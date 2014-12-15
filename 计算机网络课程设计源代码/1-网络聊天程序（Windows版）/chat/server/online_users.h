/***
*online_users.h - declarations the structure
*
*		Copyright (C) 2011, Victor Jianfei Ye. All rights reserved.
*
*Purpose:
*		This file declares the structure containing the handle to the
*		two controls of the place to show people online.
*
****/

#ifndef _ONLINE_USER_H
#define _ONLINE_USER_H

typedef struct tagHOnlineUserInfo
{
	HWND hLableOnlinePeople ;
	HWND hOnlineUserList ;
} HOnlineUserInfo , *PHOnlineUserInfo ;

#endif
