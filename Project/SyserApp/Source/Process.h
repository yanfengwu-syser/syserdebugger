#ifndef  _PROCESS_H_
#define  _PROCESS_H_

#include "Tlhelp32.h"

class CProcess
{
public:
	CProcess();
	~CProcess();
public:	
	static	bool	GetProcessUser(HANDLE hProcess, WCHAR*szUserName,int MaxLen);
	static	bool	GetPrivilege(PCSTR privName);
	bool	Start(IN PCSTR ProcessName,PCSTR szCmdLine,IN bool bSuspend = true,PCSTR szDir = NULL);	//创建新进程
	bool	Terminate();											//结束当前进程
	bool	SuspendAllThread(IN bool bSuspend = true);				//TRUE :挂起所有线程 FALSE:恢复所有线程
	bool	ReadMemory(ULPOS Address,void*Buffer,int Size);
	bool	WriteMemory(ULPOS Address,void*Buffer,int Size);
public:
	CHAR	m_ProcessName[MAX_PATH];				//当前进程名
	DWORD	m_ProcessID;							//当前进程ID号
	HANDLE	m_ProcessHandle;						//当前进程句柄
};

#endif
