#include "server.h"

list clients;
plist client_list=&clients;
int state=1;
char buf_server[BUFLEN]="";
	
DWORD WINAPI getMessage(LPVOID threadNum){ //接受客户端信息并保存和转发
	pclient pclt;
	SOCKET sck;
	int res;
	char s[BUFLEN];
	while(state){
		pclt=getlist_head(client_list);
		while(pclt){
				getsocket((*pclt),&sck);
				res=recv(sck,s,sizeof(s),0);
				if(res==0||res==WSAECONNRESET||s[0]=='\a')
				{
					pclt->state=0;
					s[0]='0';
				}
				else if(res!=-1)
				{
					s[res]='\0';
					operate_msg(client_list,pclt,s);
				}
				pclt=next(pclt);
		}
		Sleep(10);
	}
	return 0 ;
}

DWORD WINAPI showcount(LPVOID threadNum){
	while(state){
		del_clients(client_list); //更新用户列表，删除已断线的用户；
		Sleep(TIME);
	}
	return 0;
}

DWORD WINAPI sendMessage(LPVOID threadNum){ //服务器方发送信息
	char cmd[SERVERLEN];
	while(state){ 
			gets(cmd);
			msg_log(cmd,"server:");
			if(!strcmp(cmd,"#exit"))
				state=0;
			else if(!strcmp(cmd,"#help"))showcmd();
			else if(cmd[0]=='#'&&cmd[1]!='#')
				exccmd(cmd,client_list);
			else if(cmd[0]!='\0'){ 
				strcpy(buf_server,"\a\a服务器端提示：\r\n");
				strcat(buf_server,cmd);
				sendall(client_list,buf_server);
			}
	}
	return 0 ;
}



int smain(void)
{
	///调入SOCKET库（初始化）
	client clt;
	WSADATA sd;
	SYSTEMTIME nowtime;
	WORD ver=0x0101;
	SOCKET svrSck,sck;
	DWORD arg;
	SOCKADDR_IN addr;
	HANDLE hThread1=NULL,hThread2=NULL,hThread3=NULL;	// 用于调用进度条函数的句柄
	DWORD ThreadID1=0,ThreadID2,ThreadID3;		// 用于记录线程编
	fd_set rfd,efd;
	SOCKADDR_IN ad;
	struct timeval timeout;
	int len;
	char hostname[255];
	struct hostent *h;
	char szMessage[1000];
	HINSTANCE hInstance = GetModuleHandle ( NULL ) ;
	LoadString ( hInstance , IDS_PROMPT , szMessage , sizeof ( szMessage ) ) ;
	puts(szMessage);
	hThread1=CreateThread(NULL, 0, getMessage, 0, 0, &ThreadID1);
    hThread2=CreateThread(NULL, 0, sendMessage, 0, 0, &ThreadID2);
	hThread3=CreateThread(NULL, 0, showcount, 0, 0, &ThreadID3);
	init_clients(client_list); //初始化用户列表
	if(WSAStartup(ver,&sd))
	{
		LoadString ( hInstance , IDS_INIT_FAILURE , szMessage , sizeof (szMessage ) ) ;
		puts(szMessage);
		return 1 ;
	}
	//创建SOCKET
	svrSck=socket(AF_INET,SOCK_STREAM,0);
	if(svrSck==INVALID_SOCKET)
	{
		LoadString ( hInstance , IDS_CREATION_FAILED , szMessage , sizeof ( szMessage ) ) ;
		puts(szMessage);
		return 1 ;
	}
	//设置SOCKET运行模式
	arg=1;
	ioctlsocket(svrSck,FIONBIO,&arg); //设置非阻塞模式
	//绑定
	addr.sin_family=AF_INET;
	addr.sin_port=htons(2007);
	gethostname(hostname,sizeof(hostname));
	if((h=gethostbyname(hostname))==NULL)
	{
		printf("获取主机ip地址失败\n");
		Sleep(2000);
		return 0;
	}
	addr.sin_addr=*((struct in_addr *)h->h_addr_list[0]);//htonl(ADDR_ANY);
	if(bind(svrSck,(SOCKADDR*)&addr,sizeof(SOCKADDR))==SOCKET_ERROR)
	{
		printf("绑定失败!");
		closesocket(svrSck);
		return 1 ;
	}
	//监听
	if(listen(svrSck,10)==SOCKET_ERROR)
	{
		printf("监听失败!");
		closesocket(svrSck);
		return 1 ;
	}
	printf("服务器程序正常启动，正在2007端口监听...\n");
	msg_log("server_startup","server:");
	while(state) //等待客户端连接
	{
		
		FD_ZERO(&rfd); //用来判断是否有连接
		FD_ZERO(&efd); //用来判断是否出错
		FD_SET(svrSck,&rfd);
		FD_SET(svrSck,&efd);
		timeout.tv_sec=0;
		timeout.tv_usec=10000; //10秒超时
		if(select(0,&rfd,NULL,&efd,&timeout))
		{
			if(FD_ISSET(svrSck,&rfd)) //有连接进来
			{
				len=sizeof(SOCKADDR_IN);
			    sck=accept(svrSck,(SOCKADDR*)&ad,&len);
				if(sck!=INVALID_SOCKET)
				{
					GetLocalTime(&nowtime);
					printf("\n新建连接%s:%d\n", inet_ntoa(ad.sin_addr),ntohs(ad.sin_port));	
					set_client(&clt,sck,ad,"","","",1,nowtime,NULL);
					ins_clients(client_list,clt); 	
				}
			}
			else if(FD_ISSET(svrSck,&efd))//出现错误
			{
				printf("出现错误!\n");
				closesocket(svrSck);
				break;
			}
		}
		Sleep(10);
	}
	dst_clients(client_list);//释放用户
	shutdown(svrSck,SD_BOTH);
	closesocket(svrSck);
	WSACleanup();
	return 0;
}


