#include "server.h"

list clients;
plist client_list=&clients;
int state=1;
char buf_server[BUFLEN]="";
	
DWORD WINAPI getMessage(LPVOID threadNum){ //���ܿͻ�����Ϣ�������ת��
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
		del_clients(client_list); //�����û��б�ɾ���Ѷ��ߵ��û���
		Sleep(TIME);
	}
	return 0;
}

DWORD WINAPI sendMessage(LPVOID threadNum){ //��������������Ϣ
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
				strcpy(buf_server,"\a\a����������ʾ��\r\n");
				strcat(buf_server,cmd);
				sendall(client_list,buf_server);
			}
	}
	return 0 ;
}



int smain(void)
{
	///����SOCKET�⣨��ʼ����
	client clt;
	WSADATA sd;
	SYSTEMTIME nowtime;
	WORD ver=0x0101;
	SOCKET svrSck,sck;
	DWORD arg;
	SOCKADDR_IN addr;
	HANDLE hThread1=NULL,hThread2=NULL,hThread3=NULL;	// ���ڵ��ý����������ľ��
	DWORD ThreadID1=0,ThreadID2,ThreadID3;		// ���ڼ�¼�̱߳�
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
	init_clients(client_list); //��ʼ���û��б�
	if(WSAStartup(ver,&sd))
	{
		LoadString ( hInstance , IDS_INIT_FAILURE , szMessage , sizeof (szMessage ) ) ;
		puts(szMessage);
		return 1 ;
	}
	//����SOCKET
	svrSck=socket(AF_INET,SOCK_STREAM,0);
	if(svrSck==INVALID_SOCKET)
	{
		LoadString ( hInstance , IDS_CREATION_FAILED , szMessage , sizeof ( szMessage ) ) ;
		puts(szMessage);
		return 1 ;
	}
	//����SOCKET����ģʽ
	arg=1;
	ioctlsocket(svrSck,FIONBIO,&arg); //���÷�����ģʽ
	//��
	addr.sin_family=AF_INET;
	addr.sin_port=htons(2007);
	gethostname(hostname,sizeof(hostname));
	if((h=gethostbyname(hostname))==NULL)
	{
		printf("��ȡ����ip��ַʧ��\n");
		Sleep(2000);
		return 0;
	}
	addr.sin_addr=*((struct in_addr *)h->h_addr_list[0]);//htonl(ADDR_ANY);
	if(bind(svrSck,(SOCKADDR*)&addr,sizeof(SOCKADDR))==SOCKET_ERROR)
	{
		printf("��ʧ��!");
		closesocket(svrSck);
		return 1 ;
	}
	//����
	if(listen(svrSck,10)==SOCKET_ERROR)
	{
		printf("����ʧ��!");
		closesocket(svrSck);
		return 1 ;
	}
	printf("������������������������2007�˿ڼ���...\n");
	msg_log("server_startup","server:");
	while(state) //�ȴ��ͻ�������
	{
		
		FD_ZERO(&rfd); //�����ж��Ƿ�������
		FD_ZERO(&efd); //�����ж��Ƿ����
		FD_SET(svrSck,&rfd);
		FD_SET(svrSck,&efd);
		timeout.tv_sec=0;
		timeout.tv_usec=10000; //10�볬ʱ
		if(select(0,&rfd,NULL,&efd,&timeout))
		{
			if(FD_ISSET(svrSck,&rfd)) //�����ӽ���
			{
				len=sizeof(SOCKADDR_IN);
			    sck=accept(svrSck,(SOCKADDR*)&ad,&len);
				if(sck!=INVALID_SOCKET)
				{
					GetLocalTime(&nowtime);
					printf("\n�½�����%s:%d\n", inet_ntoa(ad.sin_addr),ntohs(ad.sin_port));	
					set_client(&clt,sck,ad,"","","",1,nowtime,NULL);
					ins_clients(client_list,clt); 	
				}
			}
			else if(FD_ISSET(svrSck,&efd))//���ִ���
			{
				printf("���ִ���!\n");
				closesocket(svrSck);
				break;
			}
		}
		Sleep(10);
	}
	dst_clients(client_list);//�ͷ��û�
	shutdown(svrSck,SD_BOTH);
	closesocket(svrSck);
	WSACleanup();
	return 0;
}


