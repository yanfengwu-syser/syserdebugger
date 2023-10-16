#ifndef _SYSER_NT_DRV_APP_H_
#define _SYSER_NT_DRV_APP_H_


class CMoveFramMenu : public CWispMenu
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent)
};

#include "X86Optr.h"
#include "InputDriver.h"
#include "SysInfo.h"
#include "MainFrame.h"
#include "pcidef.h"
#include "Services.h"
#include "SyserUI.h"
#include "SyserConfig.h"
#include "SyserSymAnalyzer.h"
#include "SerialPort.h"
#include "SDServer.h"
#include "PCSystem.h"

#define	MAX_PIXEL_BYTE_COUNT		4
#define	MAX_VIEW_COUNT				4

typedef TMap<CStrW,SYSER_PLUGIN_MODULE> CPluginMap;

struct SYSER_DUMP
{
	BYTE*	DumpData;
	int		DumpSize;
	CStrA	DumpFileName;
};
typedef struct _SERIALNAME
{
	char* Name;
	unsigned __int64 MulVal;
}SERIALNAME,*PSERIALNAME;
typedef TList<SYSER_DUMP>		CSyserDumpList;
typedef TMap<unsigned __int64,CStrA> GSNMAP;

typedef TList<KEY_PAIR> HOTKEYLIST;
typedef TMap<DWORD,HOTKEYLIST> CMDHOTKEYMAP;

class CSyser : public CWispBase
{
public:
	CSyser();
public:	
	CPCSystem		m_PCSystem;
	CSerialPortConnect m_SerialPortConnect;
	CSyserConnect*	m_pSyserConnect;
	CSDServer		m_SDServer;
	CDbgProcess*	m_pSysDebugger;
	CDbgProcess*	m_pDebugger;
	CDbgProcess*	m_pCsrssProcess;
	CDbgProcess*	m_pOrgProcess;
	CSysInfo		m_SysInfo;
	CMainFrame		m_MainFrame;
	CSyserUI		m_SyserUI;
	bool			m_bMovingFrame;
	WISP_POINT		m_RootPos;
	WISP_POINT		m_RootPosBackup;
	WISP_RECT		m_FrameRect;
	CLocalFileIO	m_FileIO;
	COptionValue	m_SyserOption;
	int				m_OrgWindowWidth;
	int				m_OrgWindowHeight;
	bool			m_bShowSplash;
	bool			m_bScrRestored;			//用于F4屏幕恢复
	bool			m_bScrBackup;
	bool			m_bUserScrBackuped;
	bool			m_bHandle;
	bool			m_bExit;
	bool			m_bSaveReg;
	bool			m_bInitSuccess;
	bool			m_bUpdateReg;			//在退出时是否要更新 Reg .
	bool			m_bInterrupt1HereStat;
	bool			m_bFaultsStat;
	bool			m_bDbgRegAccessMon;
	bool			m_bPatchCopyOnWrite;
	bool			m_bCopyOnWriteFastCall;
	DWORD			m_Interrupt3HereStat;	//如果该变量为真时 拦截所有的中断 3 
	DWORD			m_CR0Active;
	PDRIVER_OBJECT	m_DriverObject;
	PDEVICE_OBJECT	m_DeviceObject;
	DWORD			m_Win32KServiceTable;
	DWORD			m_DriverStartAddr;
	DWORD			m_DriverEndAddr;
	WCHAR			m_szImagePath[MAX_FN_LEN];
	UINT			m_OldStyle;
	WISP_SIZE		m_OldFrameSize;
	NTSTATUS		(*m_PsRemoveLoadImageNotifyRoutine)(IN PLOAD_IMAGE_NOTIFY_ROUTINE);
	//ULONG			(*m_RtlGetCurrentDirectory_U)(ULONG MaximumLength, PWSTR Buffer);
public:
	//////////////////////////////////////////////////////
	//界面
	//////////////////////////////////////////////////////
	bool	Init();
	void	Release();
	bool	InitFileIO();
	void	EndDraw(WISP_RECT*pUpdateRect);
	void	Active();
	void	Exit(bool bRestoreScr=true);
	bool	PumpCondition();
	bool	WakeUpMsgThread();
	bool	SleepMsgThread();
	void	IdleEvent();
	void	EnterCriticalSection();
	void	LeaveCriticalSection();
	bool	CreateFrame(WISP_CHAR*WndName,int Width,int Height,int Bpp);
	void	DestroyFrame();
	bool	MoveFrame(int dx,int dy);
	bool	ResizeHostFrame(int Width,int Height);
	bool	ResizingFrame(int Width,int Height);
	void	BackupScreen();
	void	RestoreScreen();
	void	CenterScreen();
	void	RestoreMovingFrame();
	void	DrawMovingFrame();
	void	ReleaseBreakPoint();
	void	InsertDbgMsg(PCWSTR szMsg);
	void	ShowSplash();
	void	HideSplash();
	bool	SetClipboardString(PCSTR String);
	void	OnMouseMove(IN int DeltaX,IN int DeltaY);
	void	ReportMsg(IN const WISP_CHAR* Format,...);
	bool	InitOSHwndRoot();
	UINT	m_OSVer;
	ULONG	m_OSMajorVersion;
	ULONG	m_OSMinorVersion;
	ULONG	m_OSBuildNumber;
	DWORD	m_PopupThread;				// Syser Active 时当前线程 KTHREAD
	DWORD	m_PopupProcess;				// Syser Active 时当前进程 KPROCESS
	DWORD	m_PopupThreadID;				// Syser Active 时当前线程 ID
	DWORD	m_PopupProcessID;				// Syser Active 时当前进程 ID
	BYTE*	m_VideoBufBackup;
	WISP_RECT	m_BackupFrameRect;
	DWORD	m_CriticalEFlag;
	WISP_FRAME_BUFFER m_RealFrameBuffer;
	KSPIN_LOCK m_NotifyLock; 
	KEVENT	m_ImageLoadSyncEvent;
	int m_TimeZoneBias;
	static	void SyserWaitThread(void*);
	void	StartSyserWaitThread();
	void	StopSyserWaitThread();
	//////////////////////////////////////////////////////
	//守护线程，用于一些延迟运行的操作比如Dump
	CSyserDumpList	m_DumpList;
	KEVENT	m_WaitEvent;
	PVOID	m_ThreadPointer;
	bool	m_bWaitThread;
	DWORD	m_OSHwndRoot;
	//////////////////////////////////////////////////////
public:
	//////////////////////////////////////////////////////
	//驱动
	//////////////////////////////////////////////////////
	bool	m_bHardDriverSuccess;
	bool	m_bHookSuccess;
	bool	IntallHardDriver();
	void	RemoveHardDriver();
	bool	InstallHooks();
	void	RemoveHooks();
	bool	InstallDebug();
	bool	UninstallDebug();
	void	ResetInputState();
	void	ClearInputState();
	void	InitRemoteConnect();
	void	ReleaseRemoteConnect();
	void	InitHotKeyInfo();
public:
	//////////////////////////////////////////////////////
	//调试
	//////////////////////////////////////////////////////
	static	ULSIZE	ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size,CSyser*pThis);
	void	DbgPrint(int x,int y,IN WCHAR*Format,...);
	void	MapToProcess(CDbgProcess*pProcess);
	bool	InstallLoadImageHook();
	bool	UninstallLoadImageHook();
	int		LoadPlugin();
	void	UnloadPlugin();
	static	XSCAN_RES XScanPlugin(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParem);
	static  bool RegisterPluginService(PUNICODE_STRING ServiceName,PCSTR DriverFileFullName);
	CPluginMap m_PluginMap;
	CMDHOTKEYMAP m_CmdHotKeyMap;
	void	SetActiveHotKey(DWORD FuncKeyCode,DWORD SecondKeyCode);
	void	AttachHotKey(DWORD CmdList,CWispWnd* hWnd);
	DWORD AttachShortcutKey(DWORD dwCmdID,TMap<UINT,UINT> & pMap);
	void AttachPopupProcess(DWORD dwCR3);
	TMap<UINT,UINT> m_ShortcutKeyMap;
	PROC_RANGE_BP_MAP m_RangeBPList; //内存范围断点

	void ClearBPR(); //在 syser 激活时先清除所有的 bpr 断点
	void ClearProcessBPR(DWORD dwProcess); //在 syser 激活时先清除所有的 bpr 断点
	void SetBPR();//在 syser 退出时要设置 bpr 断点

#ifndef __DEMO__VERSION__
	static SERIALNAME gSerialName[28];
	virtual	PSERIALNAME GetSerialNumber();
	virtual bool CheckSN(char* SerialNum,char* Name);
	GSNMAP		m_GSnMap;
#endif
};



void	LoadCFG();

typedef struct _SERVICETABLE
{
	void**	ServiceTable;
	DWORD	LowCall;
	DWORD	HiCall;
	PVOID*	ArgTable;
}SERVICETABLE,*PSERVICETABLE;


extern	CSyser*gpSyser;
extern	CSyserConfig*gpSyserCfg;
extern	CSyserPluginUI*gpSyserPluginUI;
extern	SYSER_BOOT_DEVICE_EXTENSION*gpSysBootDevEx;
extern	SYSER_LANGUAGE_DEVICE_EXTENSION*gpSysLangDevEx;

extern "C" NTSTATUS KeStackAttachProcess(PEPROCESS pProcess,KAPC_STATE* ApcState);
extern "C" NTSTATUS KeUnstackDetachProcess(KAPC_STATE* ApcState);
extern "C"	PSERVICETABLE	KeServiceDescriptorTable;

#endif
