#include "StdAfx.h"
#include "SNCheck.h"
#include "SyserApp.h"

#define SYSER_CHECK_PORT	80

void SNCheckThread()
{
	char szBuffer[128],LicName[128];
	int	BufSize,Length;
	BOOL bBroadCast;
	SOCKET Socket;
	SOCKADDR_IN RecvAddr,SendAddr;	
	WSADATA wsaData;

	*LicName = 0;
	if(GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\LicName",LicName,sizeof(LicName))==false)
		return;
	if(WSAStartup(MAKEWORD(1,1),&wsaData)!=0) 
		return;

	Socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	bBroadCast = true;
	setsockopt(Socket,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadCast,sizeof(bBroadCast));

	RecvAddr.sin_family=AF_INET;
	RecvAddr.sin_port=htons(SYSER_CHECK_PORT);
	RecvAddr.sin_addr.S_un.S_addr=htonl(INADDR_BROADCAST);

	BufSize=TSPrintf(szBuffer,"Syser:%s",LicName)+1;
	sendto(Socket,szBuffer,BufSize,MSG_DONTROUTE,(const sockaddr *)&RecvAddr,sizeof(RecvAddr));		
	closesocket(Socket);

	Socket = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&SendAddr, 0, sizeof(SendAddr));
	SendAddr.sin_family = AF_INET;
	SendAddr.sin_port = htons(SYSER_CHECK_PORT);
	SendAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(Socket,(const sockaddr *)&SendAddr, sizeof(SendAddr)) == SOCKET_ERROR) 
	{
		closesocket(Socket);
		return;
	}
	Length = sizeof(RecvAddr);
	while(TRUE)
	{
		BufSize = recvfrom(Socket, szBuffer, sizeof(szBuffer)-1,0,(sockaddr *)&RecvAddr,&Length);
		if(BufSize>6 && TStrNICmp(szBuffer,"Syser:",6)==0)
		{
			if(TStrICmp(&szBuffer[6],LicName)==0)
			{
				sprintf(szBuffer,"Found another copmputer use same license user name !\nUser Name [%s]  IP %d.%d.%d.%d\nSyser will be terminated !",
					LicName,
					RecvAddr.sin_addr.S_un.S_un_b.s_b1,
					RecvAddr.sin_addr.S_un.S_un_b.s_b2,
					RecvAddr.sin_addr.S_un.S_un_b.s_b3,
					RecvAddr.sin_addr.S_un.S_un_b.s_b4);
				MessageBox(NULL,szBuffer,"Warning",MB_OK);
				theApp.m_SyserInterface.StopSyserDriver();
				::PostMessage(theApp.m_hLocalWnd,WM_QUIT,0,0);
				break;
			}
		}
	}
	closesocket(Socket);
	WSACleanup();
}
