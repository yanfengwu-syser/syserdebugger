#include "StdAfx.h"
#include "Process.h"

CProcess::CProcess()
{
	m_ProcessID=0;
	m_ProcessHandle=NULL;
}

CProcess::~CProcess()
{
}


bool CProcess::GetPrivilege(PCSTR privName)
{
	bool rc;
	HANDLE hToken;
	LUID privValue;
	TOKEN_PRIVILEGES tkp;
	if(!OpenProcessToken( GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
		return false;
	if(!LookupPrivilegeValue( NULL, privName, &privValue ) )
	{
		CloseHandle(hToken);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = privValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	rc = AdjustTokenPrivileges( hToken, FALSE, &tkp,sizeof tkp,NULL,NULL)!=FALSE;
	CloseHandle( hToken );
	return rc;
}


//获取进程的用户名
bool CProcess::GetProcessUser(HANDLE hProcess, WCHAR*szUserName,int MaxLen)
{
	SID_NAME_USE sn;
	WCHAR szDomainName[MAX_FN_LEN];
	DWORD Length,NameLen;
	bool Result;
	HANDLE hToken;
	TOKEN_USER*pTokenUser;
	*szUserName=0;
	if(OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)==FALSE)
	{
		return false;
	}
	Length=0;
	GetTokenInformation(hToken,TokenUser, NULL, 0, &Length);
	if(Length==0)
	{
		CloseHandle(hToken);
		return false;
	}
	pTokenUser = (TOKEN_USER*)new BYTE[Length];
	if(GetTokenInformation(hToken,TokenUser,pTokenUser,Length,&Length)==false)
	{
		delete pTokenUser;
		CloseHandle(hToken);
		return false;
	}
	Length = MAX_FN_LEN;
	NameLen = MaxLen;
	Result = LookupAccountSidW(NULL,pTokenUser->User.Sid,szUserName,&NameLen,szDomainName,&Length,&sn)!=FALSE;
	delete pTokenUser;
	CloseHandle(hToken);
	return Result;
}

bool CProcess::Start(IN PCSTR ProcessName,PCSTR szCmdLine,IN bool bSuspend,PCSTR szDir)
{
	char szAppCmdLine[1024];
	bool Result;
	DWORD dwCreationFlags;
	STARTUPINFO	StartInfo;
	PROCESS_INFORMATION ProcInfo;
	//启动进程
	ZeroMemory(&StartInfo,sizeof(STARTUPINFO));
	ZeroMemory(&ProcInfo,sizeof(PROCESS_INFORMATION));
	StartInfo.cb = sizeof(STARTUPINFO);
	StartInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartInfo.wShowWindow = SW_SHOWDEFAULT;
	strcpy(m_ProcessName,ProcessName);
	dwCreationFlags = NORMAL_PRIORITY_CLASS;
	if(bSuspend)
		dwCreationFlags|=CREATE_SUSPENDED;
	*szAppCmdLine=0;
	if(szCmdLine && *szCmdLine)
	{
		TStrCpy(szAppCmdLine," ");
		TStrCat(szAppCmdLine,szCmdLine);
	}
	Result=CreateProcess(ProcessName,szAppCmdLine,NULL,NULL,FALSE, dwCreationFlags,NULL,szDir,&StartInfo,&ProcInfo)!=FALSE;
	if(Result==false)
		return false;
	m_ProcessID=ProcInfo.dwProcessId;
	m_ProcessHandle=ProcInfo.hProcess;
	return Result;
}

bool CProcess::Terminate()
{
	return TerminateProcess(m_ProcessHandle,0x0)!=FALSE;
}

bool CProcess::SuspendAllThread(IN bool bSuspend)
{
	HANDLE hThread,hThreadSnap;
	DWORD  Result,nThread;
	THREADENTRY32 TE32;

	hThreadSnap=CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
	if(hThreadSnap==INVALID_HANDLE_VALUE)
		return FALSE;

	TE32.dwSize=sizeof(THREADENTRY32);
	nThread=0;
	if(Thread32First(hThreadSnap,&TE32))
	{
		do
		{
			if(m_ProcessID!=TE32.th32OwnerProcessID)
				continue;
			nThread++;
			hThread=OpenThread(THREAD_ALL_ACCESS,TRUE,TE32.th32ThreadID);
			if(hThread==NULL)
				return FALSE;
			if(bSuspend)
				Result=SuspendThread(hThread);
			else
				Result=ResumeThread(hThread);
			if(Result==-1)
			{
				CloseHandle(hThread);
				return FALSE;
			}			
			CloseHandle(hThread);
		}while(Thread32Next(hThreadSnap,&TE32));
	}
	return TRUE;
}

bool CProcess::ReadMemory(ULPOS Address,void*Buffer,int Size)
{
	SIZE_T cbReturn;
	cbReturn = 0;
	ReadProcessMemory(m_ProcessHandle,NUM_TO_PTR(Address),Buffer,Size,&cbReturn);
	return cbReturn==Size;
}

bool CProcess::WriteMemory(ULPOS Address,void*Buffer,int Size)
{
	SIZE_T cbReturn;
	cbReturn = 0;
	WriteProcessMemory(m_ProcessHandle,NUM_TO_PTR(Address),Buffer,Size,&cbReturn);
	return cbReturn==Size;	
}




