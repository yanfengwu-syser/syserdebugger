#ifndef _SYS_DEP_H_
#define _SYS_DEP_H_

NAME_SPACE_BEGIN
////////////////////////////////////////////////////
//线程
////////////////////////////////////////////////////
typedef void (*THREAD_PROC)();

DWORD	CreateThread(THREAD_PROC pFunc);
bool	SuspendThread(DWORD ThreadID);
bool	ResumeThread(DWORD ThreadID);
bool	TerminateThread(DWORD ThreadID);
#ifdef	CODE_OS_UNIX
DWORD	CreateThreadDetach(THREAD_PROC pFunc);
#include <pthread.h>
typedef struct _CRITICAL_SECTION
{
	pthread_mutex_t LockSemaphore;
}CRITICAL_SECTION,*LPCRITICAL_SECTION;
void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
void DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
bool TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
#endif //CODE_OS_UNIX

////////////////////////////////////////////////////
//同步
////////////////////////////////////////////////////
extern DWORD dwCPUMHz;
extern ULONGLONG TmpDrvCurTickCount;
extern ULONGLONG TmpDrvPrevTickCount;
void	InitTickCount();
void	UpdateTickCount(ULONGLONG*pTickCount);
DWORD	GetRandom(DWORD MinNum,DWORD MaxNum);
void	SetRandomMem(void*Buffer,int Size);
void	InitStaticRandom(DWORD Seed);
DWORD	GetStaticRandom(DWORD MinNum,DWORD MaxNum);
////////////////////////////////////////////////////
//文件名
////////////////////////////////////////////////////
int GetModulePath(PSTR szPathName,bool bSeparator = true);
int GetModulePath(PWSTR szPathName,bool bSeparator = true);

int	CodeDebugPrintf(PCSTR Format,...);
bool ReadDwordValueRegistry(WCHAR *pValue,DWORD *pdwRetValue,WCHAR *pKey);
bool WriteDwordValueRegistry(WCHAR *pValue,DWORD dwValue,WCHAR *pKey);
bool WriteStringValueRegistry(WCHAR *pValue,WCHAR* szValue,WCHAR *pKey);
bool GetSystemRootPath(WCHAR* RegistryServiceName,WCHAR* SystemPathBuffer ,ULONG SystemPathLen);
NAME_SPACE_END

#endif

