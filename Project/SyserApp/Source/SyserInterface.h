#ifndef _SYSER_INTERFACE_
#define _SYSER_INTERFACE_

#include "Process.h"
#include "../../SerialNumber/Source/Validate.h"
#include "DXTest.h"

#define WM_SYSER_UNINSTALL				(WM_USER+0x201)
#define WM_SYSER_GET_CLIPBOARD_STRING	(WM_USER+0x202)
#define WM_SYSER_UPDATE_DBG_MSG			(WM_USER+0x203)
#define WM_SYSER_UPDATE_DRV_STATE		(WM_USER+0x204)

enum
{
	GROUP_SYSLANG_ORDER=0x1,
	GROUP_SDBGMSG_ORDER,
	GROUP_SYSBOOT_ORDER,
	GROUP_SYSER_ORDER,
	GROUP_RESERVES2_ORDER,
};

typedef struct _STGROUPORDERLIST
{
	BYTE Count;
	DWORD Order1; 
	DWORD Order2; 
	DWORD Order3; 
	DWORD Order4; 
	DWORD Order5;
	BYTE Padding[3];
}STGROUPORDERLIST,*PSTGROUPORDERLIST;


class CSyserInterface
{
public:
	CSyserInterface(void);
	~CSyserInterface(void);
public:
	bool	Init();
	void	Release();
	bool	InstallDependDriver(PCSTR ServiceName,PCSTR FileName,UINT StartType = SERVICE_BOOT_START,PCSTR GroupName=NULL,DWORD Tag=-1);
	bool	TranslateExportSymbolFile(IN PCSTR szFileName,OUT PSTR szSymbolFileName);
	bool	InstallServiceEventLog(PCSTR ServiceName,PCSTR MessageDllName,DWORD TypesSupported=7,bool bSystemIoLog=true);
	bool	UninstallServiceEventLog(PCSTR ServiceName);
	bool	RemoveDependData(PCSTR FileNameList);
	void	IsSysBootFrameBufferAvailable();
	bool	StartSyserDriver();
	void	StopSyserDriver();
	bool	StopSyser();
	void	SaveSyserHistroys(PCSTR Filename);
	void	SaveSyserComments();
	bool	LoadModule(PCSTR szFilename,PCSTR szCmdLine,DWORD Style);
	bool	LoadDepModuleSDS(PCSTR szMainModule,bool bDriver);
	bool	GetModuleFullPath(PCSTR szModuleName,PCSTR szMainModule,PSTR szFullName);
	bool	LaunchAppForDebugging(PCSTR FileName,PCSTR szCmdLine,DWORD Style);
	bool	LaunchDriverForDebugging(IN PCSTR FileName,DWORD Style);
	bool	LoadModuleExportSymbols(IN PCSTR szFileName);
	bool	LoadModuleIDAMapFile(IN PCSTR szIDAMapFile,IN PCSTR szModuleName);
	bool	LoadSDS(IN PCSTR SymbolModuleFileName);
	bool	UnloadSDS(IN PCSTR SymbolModuleFileName);
	bool	TranslateSymbolFile(IN PCSTR szFileName,OUT PSTR szSymbolFileName,bool bOverWrite);
	void	UpdateDriverStatus();
	void	ReloadConfig();
	void	UpdateDbgMsg(HANDLE hDevice);
	void	ChangeMsgFilter();
	bool	IsSyserRuning();
	bool	InstallSyser();
	bool	UninstallSyser();
	bool	InstallServiceGroupOrderList();
	bool	UninstallServiceGroupOrderList();
	bool	InstallFileExtAssociate();
	bool	UninstallFileExtAssociate();
	void	SendClipboardString();
	void	RecvClipboardString();
	void	UpdateWindow();
	static void	MsgUpdateThread();
	static void	TranslateThread();
	static void UpdateThread();
	static void ProgressSetRange(int Range);
	static void ProgressSetPos(int Pos);
public:
	char		m_LoadDllName[MAX_FN_LEN];
	OSVERSIONINFOA m_VerInfo;
	bool		m_bRecvClipboard;
	bool		m_bSyserDriverStatus;
	bool		m_bCaptureDbgMsg;
	bool		m_bAttachFrameBuffer;
	CProcess	m_Process;
	HANDLE		m_hMutex;
	HANDLE		m_hDbgMsgDevice;
	SYSER_SN_TYPE	m_VerType;
	CSyserDX	m_SyserDX;
};


#endif
