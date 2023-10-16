#ifndef _SYSER_APP_H_
#define _SYSER_APP_H_ 

#define CMoveFramMenu			CWispMenu

#include "SyserUI.h"
#include "MainFrame.h"

typedef TMap<CStrW,SYSER_PLUGIN_MODULE> CPluginMap;

struct RECENT_HISTROY_ITEM
{
	CIStrA	FileName;
	DWORD	Style;
	bool	operator==(const RECENT_HISTROY_ITEM &Obj)const
	{
		return FileName==Obj.FileName;
	}
};
typedef TList<KEY_PAIR> HOTKEYLIST;
typedef TMap<DWORD,HOTKEYLIST> CMDHOTKEYMAP;

class CSyser : public CLocalWispApp
{
public:
	CSyser(void);
	~CSyser(void);
public:
	virtual bool	InitInstance();
	virtual int		ExitInstance();
	void	LoadCFG();
	bool	LoadDebugger(WCHAR*szModuleName);
	void	UnloadDebugger();
	int		LoadPlugin();
	void	UnloadPlugin();
	static	XSCAN_RES XScanPlugin(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParem);
	CPluginMap		m_PluginMap;
	
	HMODULE			m_hDebuggerModule;
	CX86Debugger*	m_pDebugger;
	CX86Debugger*	m_pSysDebugger;
	HCURSOR			m_hCursorCurEIP;
	CStrW			m_szDbgFileNameFilter;
	CMainFrame		m_MainFrame;
	CSyserUI		m_SyserUI;
	CSourceDebug	m_SourceDebug;
	CCurrentFunction m_CurrentFunctionContext;
	int				m_TimeZoneBias;
	DWORD m_OSMajorVersion;
	DWORD m_OSMinorVersion;
	DWORD	m_PopupThread;				// Syser Active 时当前线程 KTHREAD
	DWORD	m_PopupProcess;				// Syser Active 时当前进程 KPROCESS
	DWORD	m_PopupThreadID;				// Syser Active 时当前线程 ID
	DWORD	m_PopupProcessID;				// Syser Active 时当前进程 ID
	SOUCEDEBUGCALLSTACKLIST m_SourceDebugCallStackList;
	virtual	bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool m_bInitializeOK;
	TList<RECENT_HISTROY_ITEM>	m_HistroyList;
	bool						m_bHistroyModified;
	void	LoadHistroy();
	void	SaveHistroy();
	void	InsertHistroy(PCSTR szFileName,DWORD Style);
	CMDHOTKEYMAP m_CmdHotKeyMap;
	void InitHotKeyInfo();
	void SetActiveHotKey(DWORD FuncKeyCode,DWORD SecondKeyCode);
	void	AttachHotKey(DWORD dwCmdID,CWispWnd* pWnd);	
	DWORD AttachShortcutKey(DWORD dwCmdID,TMap<UINT,UINT> & pMap);
	TMap<UINT,UINT> m_ShortcutKeyMap;
	DWORD			m_OSHwndRoot;
	bool InitOSHwndRoot();
};

extern CSyser*			gpSyser;
extern ULONG gCPUNumbers;
#endif

