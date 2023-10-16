#ifndef _SYS_INFO_H_
#define _SYS_INFO_H_

#include "DbgProcess.h"

typedef TMap<DWORD,CDbgProcess>			CProcMap;
typedef TString<CHAR,true>				CNtcallStr;
typedef TMap<CNtcallStr,ULONGLONG>		TNtcallMap;
typedef TMap<ULONG,CNtcallStr>			TNtcallNameIDMap;
typedef struct _ORGWINDOWSIDTENTRY
{
	DWORD EntryPoint;
	WORD Attribute;
	WORD Selector;
}ORGWINDOWSIDTENTRY,*PORGWINDOWSIDTENTRY;

typedef struct _SERVICEINDEXANDSYMBOL
{
	char*Name;
	DWORD Index;
}SERVICEINDEXANDSYMBOL,*PSERVICEINDEXANDSYMBOL;

typedef enum _MEMORY_INFORMATION_CLASS {
	MemoryBasicInformation,
	MemoryWorkingSetList,
	MemorySectionName,
	MemoryBasicVlmInformation
} MEMORY_INFORMATION_CLASS;

typedef struct _MEMORY_BASIC_INFORMATION { // Information Class 0
	PVOID BaseAddress;
	PVOID AllocationBase;
	ULONG AllocationProtect;
	ULONG RegionSize;
	ULONG State;
	ULONG Protect;
	ULONG Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

typedef struct _MEMORY_SECTION_NAME { // Information Class 2
	UNICODE_STRING SectionFileName;
} MEMORY_SECTION_NAME, *PMEMORY_SECTION_NAME;

class CSysInfo
{
	typedef NTSTATUS (__stdcall * ZWQUERYVIRTUALMEMORY)(
		IN HANDLE ProcessHandle,
		IN PVOID BaseAddress,
		IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
		OUT PVOID MemoryInformation,
		IN ULONG MemoryInformationLength,
		OUT PULONG ReturnLength OPTIONAL
		);
public:
	CSysInfo();
	~CSysInfo();
public:
	bool		Init();
	void		Release();
	bool		ValidateSN();
	void		UpdateHostSN();
	void		GetSystemInformation();
	bool		GetWin32KServiceTable();
	CDbgProcess*InsertProcess(DWORD PID);				//通过PID加入进程链中
	bool		RemoveProcess(DWORD PID);				//通过PID删除链中一个进程对象
	CDbgProcess*GetProcess(DWORD PID);
	CDbgProcess*GetProcessByCR3(DWORD CR3);
	CDbgProcess*GetProcess(WCHAR*szProcName);
	CDbgProcess*GetProcessByEPROCESS(DWORD EProcess);
	DWORD		SearchMemory(DWORD BaseAddr,DWORD BaseSize,BYTE* Feature,DWORD Size);
	void		OutputEnv();
	bool		GetSystemRoot();
	bool		ConvertFileName(CHAR*szFileName);
	void		GetPathSymbolLinker();
	bool		FindWin32KServiceSymName();
	bool		PatchI8042Driver();
#ifdef CODE_OS_NT_DRV
	bool		GetDllList(CDbgProcess*pProcess);
	bool		GetDllListNew(CDbgProcess*pProcess); //window7 use this function
	bool		GetProcessName(PEPROCESS curproc,WCHAR*ProcessName,int BufCount);
	bool		GetDriverList();
	bool		GetServiceTable();
	bool		NtcallInit();
	bool		GetIDTTable();	
	bool		GetOSKernelName();
#endif
	bool		LoadExpModList();
	bool		LoadSDSList();
public:
	DWORD		m_SystemStartAddr;
	WCHAR		m_szSystemRoot[MAX_FN_LEN];
	WCHAR		m_szSystem32[MAX_FN_LEN];
	WCHAR		m_szSystem32Drivers[MAX_FN_LEN];
	CHAR		m_szSystemRootA[MAX_FN_LEN];
	CHAR		m_szSystem32A[MAX_FN_LEN];
	CHAR		m_szSystem32DriversA[MAX_FN_LEN];
	CHAR		m_szSystemRootMarco[MAX_FN_LEN];
	CHAR		m_OSKernelName[MAX_FN_LEN];
	ULPOS		m_SyserBase;
	ULPOS		m_SyserHighBase;
	int			m_ProcNameOff;
	int			m_ProcCR3dwOff;
	ULONG		m_PEBOffsetOfEPROCESS;
	CProcMap	m_ProcMap;
	ULPOS		m_W32ServiceTableAddress;
	ULPOS*		m_W32ServiceTable;
	ULPOS		m_win32kImageBase;
	ULSIZE		m_win32kImageSize;
	BYTE*		m_W32ServiceArgv;
	DWORD		m_W32ServiceNumbers;
	ULPOS		m_MmUnmapViewOfSection;
	ULPOS		m_HidP_TranslateUsageAndPagesToI8042ScanCodes;
	ZWQUERYVIRTUALMEMORY	m_pZwQueryVirtualMemory;
	DWORD		m_OSKernlBase;
	TNtcallMap	m_NtcallMap;
	TNtcallNameIDMap	m_Win32kNtcallMap;
	DWORD*		m_OrgWindowsServiceArgTable;
	DWORD		m_LoCount;
	DWORD		m_HiCount;
	DWORD*		m_OrgWindowsServiceTable;
	ULONG		m_OSMajorVersion; 
	ULONG		m_OSMinorVersion; 
	ULONG		m_OSBuildNumber;
	BOOLEAN		m_OSCheckBuild;
	PORGWINDOWSIDTENTRY m_OrgWindowIDT;
	static		PCSTR m_gNtoskrnlName[];
	CHAR		m_szExpModListFN[MAX_FN_LEN];
	TList<CStrA>	m_SymbolPathList;
	LARGE_INTEGER  m_CurrentTime;
	LARGE_INTEGER  m_InstallTime;
	bool		m_bSNPass;
	bool		m_bEvlVer;
	//SYSER_SN_TYPE	m_SNType;
	CStrW		m_LicTip;
	CStrA		m_SNStr;
	CStrA		m_LicNameStr;	

};

int	SyserUnicodeToAnsi(const WCHAR*WszBuf,char*szBuf,int MaxLen);
int	SyserAnsiToUnicode(const char*szBuf,WCHAR*WszBuf,int MaxLen);
bool GetPEBOffset(ULONG* PEBOffset);
MODULE_ID GetModuleID(ULPOS ImageBase,ULSIZE ImageSize);

#endif

