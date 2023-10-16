#ifndef __OSPROCESSTHREAD__H__
#define __OSPROCESSTHREAD__H__


typedef struct _SYSER_KTRAP_FRAME /* sizeof 0000008c 140 */
{
	/* off 0x0000 */	unsigned long	DbgEbp;
	/* off 0x0004 */	unsigned long	DbgEip;
	/* off 0x0008 */	unsigned long	DbgArgMark;
	/* off 0x000c */	unsigned long	DbgArgPointer;
	/* off 0x0010 */	unsigned short	TempSegCs;
	/* off 0x0012 */	unsigned char	Logging;
	/* off 0x0013 */	unsigned char	Reserved;
	/* off 0x0014 */	unsigned long	TempEsp;
	/* off 0x0018 */	unsigned long	Dr0;
	/* off 0x001c */	unsigned long	Dr1;
	/* off 0x0020 */	unsigned long	Dr2;
	/* off 0x0024 */	unsigned long	Dr3;
	/* off 0x0028 */	unsigned long	Dr6;
	/* off 0x002c */	unsigned long	Dr7;
	/* off 0x0030 */	unsigned long	SegGs;
	/* off 0x0034 */	unsigned long	SegEs;
	/* off 0x0038 */	unsigned long	SegDs;
	/* off 0x003c */	unsigned long	Edx;
	/* off 0x0040 */	unsigned long	Ecx;
	/* off 0x0044 */	unsigned long	Eax;
	/* off 0x0048 */	unsigned long	PreviousPreviousMode;
	///* off 0x004c */	struct _EXCEPTION_REGISTRATION_RECORD*	ExceptionList;
	/* off 0x004c */	void*			ExceptionList;
	/* off 0x0050 */	unsigned long	SegFs;
	/* off 0x0054 */	unsigned long	Edi;
	/* off 0x0058 */	unsigned long	Esi;
	/* off 0x005c */	unsigned long	Ebx;
	/* off 0x0060 */	unsigned long	Ebp;
	/* off 0x0064 */	unsigned long	ErrCode;
	/* off 0x0068 */	unsigned long	Eip;
	/* off 0x006c */	unsigned long	SegCs;
	/* off 0x0070 */	unsigned long	EFlags;
	/* off 0x0074 */	unsigned long	HardwareEsp;
	/* off 0x0078 */	unsigned long	HardwareSegSs;
	/* off 0x007c */	unsigned long	V86Es;
	/* off 0x0080 */	unsigned long	V86Ds;
	/* off 0x0084 */	unsigned long	V86Fs;
	/* off 0x0088 */	unsigned long	V86Gs;
}SYSER_KTRAP_FRAME,*PSYSER_KTRAP_FRAME;

typedef struct _SYSER_PROCESS
{
	void* OSProcess;
	DWORD UniqueProcessId;
	DWORD PDT;
	DWORD LDTBaseAddress;
	DWORD LDTLimit;
	char ImageFileName[16];
	DWORD Next;
	DWORD VadRoot;
	DWORD Peb;
	void* ThreadHead;
	void* ThreadTail;
	DWORD ObjectTable;
}SYSER_PROCESS,*PSYSER_PROCESS;
typedef struct _SYSER_THREAD
{
	void* OSThread;
	DWORD ThreadID;
	DWORD InitialStack;
	DWORD StackLimit;
	DWORD KernelStack;
	DWORD Teb;
	DWORD Process;
	DWORD ServiceTable;
	DWORD NextThread;
	DWORD PrevThread;
	DWORD StartAddress;
	DWORD TrapFrame;
	DWORD State;
}SYSER_THREAD,*PSYSER_THREAD;
bool InitPsActiveProcessHead();
bool GetCurrentProcessAndThread(DWORD* Process,DWORD* Thread);
bool GetIdleProcessAndThread(DWORD* Process,DWORD* Thread);
bool GetNextProcess(PSYSER_PROCESS pProcess);
bool GetFirstProcess(PSYSER_PROCESS pProcess);
bool GetThreadInfoByETHREAD(DWORD pOSThread,PSYSER_THREAD pThread);
bool GetProcessInfoByEPROCESS(DWORD pOSProcess,PSYSER_PROCESS pProcess);
bool GetNextThread(PSYSER_THREAD pThread);
bool GetPrevThread(PSYSER_THREAD pThread);
bool GetThreadByID(DWORD ThreadID,PSYSER_THREAD pThread);
bool GetProcessByThreadID(DWORD ThreadID,PSYSER_PROCESS pProcess);
bool GetProcessByETHREAD(DWORD EThread,PSYSER_PROCESS pProcess);
bool GetCurrentProcessInfo(PSYSER_PROCESS pProcess);
bool GetCurrentThreadInfo(PSYSER_THREAD pThread);
extern DWORD gPsActiveProcessHead;
extern DWORD gPsIdleProcess;
//extern DWORD KTHREAD_ApcState_Process_OFFSET;
//extern DWORD EPROCESS_ActiveProcessLinks_Blink_OFFSET;
//extern DWORD EPROCESS_ActiveProcessLinks_Flink_OFFSET;
typedef struct _OS_OFFSET_INFO
{
	DWORD cbSize;
	DWORD dwFlags;
	DWORD dwMajorVersion;
	DWORD dwMinorVersion;
	DWORD dwBuildNumber;
	DWORD KPROCESS_DirectoryTableBase_OFFSET;
	DWORD KPROCESS_LdtDescriptor_OFFSET;
	DWORD KPROCESS_ThreadListHead_Flink_OFFSET;
	DWORD KPROCESS_ThreadListHead_Blink_OFFSET;
	DWORD EPROCESS_ActiveProcessLinks_Flink_OFFSET;
	DWORD EPROCESS_ActiveProcessLinks_Blink_OFFSET;
	DWORD EPROCESS_VadRoot_OFFSET;
	DWORD EPROCESS_ObjectTable_OFFSET;
	DWORD EPROCESS_Peb_OFFSET;
	DWORD EPROCESS_UniqueProcessId_OFFSET;
	DWORD EPROCESS_ImageFileName_OFFSET;
	DWORD KTHREAD_ApcState_Process_OFFSET;
	DWORD KTHREAD_ThreadListEntry_Flink_OFFSET;
	DWORD KTHREAD_ThreadListEntry_Blink_OFFSET;
	DWORD ETHREAD_Cid_UniqueThread_OFFSET;
	DWORD KTHREAD_InitialStack_OFFSET;
	DWORD KTHREAD_StackLimit_OFFSET;
	DWORD KTHREAD_KernelStack_OFFSET;
	DWORD KTHREAD_Teb_OFFSET;
	DWORD KTHREAD_ServiceTable_OFFSET;
	DWORD KTHREAD_TrapFrame_OFFSET;
	DWORD KTHREAD_State_OFFSET;
	DWORD ETHREAD_StartAddress_OFFSET;
	DWORD TEB_Win32ClientInfo_OFFSET;
	DWORD WIN32CLIENT_hwnd_OFFSET;
}OS_OFFSET_INFO,*POS_OFFSET_INFO;


extern POS_OFFSET_INFO gOSOffsetInfo;
typedef enum _SYSER_VALUE_TYPE {
	VALUE_TYPE_PROCESS_PTR,
	VALUE_TYPE_THREAD_PTR,
	VALUE_TYPE_HWND_PTR,
	VALUE_TYPE_PROCESS_ID,
	VALUE_TYPE_THREAD_ID,
	VALUE_TYPE_HWND_ID,
	VALUE_TYPE_UNKNOW,
}SYSER_VALUE_TYPE;
SYSER_VALUE_TYPE GetValueType(DWORD Value);
bool GetProcessByID(DWORD ProcessID,PSYSER_PROCESS pProcess);
bool GetProcessByEPROCESS(DWORD EProcess,PSYSER_PROCESS pProcess);
bool GetProcessByName(char* Name,PSYSER_PROCESS pProcess);
bool InitOSOffsetInfo(DWORD OSMajorVersion,DWORD OSMinorVersion,DWORD OSBuildNumber);
class CSyser;
int thread_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser);
DWORD  GetEProcessPointer(WCHAR* args);
#endif //__OSPROCESSTHREAD__H__