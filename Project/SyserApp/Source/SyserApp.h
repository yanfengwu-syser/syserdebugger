#ifndef _SYSER_APP_HEADER_
#define _SYSER_APP_HEADER_

#define DECLARE_SYSER_APP_CMD(Name)		int Name(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
#define RUNCMD		theApp.m_MainFrame.m_ConsoleWnd.RunCmd
#define OUTPUT		theApp.m_MainFrame.m_ConsoleWnd.Printf

#include "MainFrame.h"
#include "SyserInterface.h"
#include "SourceDebug.h"
#include "NoPDBSymbol.h"


struct RECENT_HISTROY_ITEM
{
	char	FileName[MAX_FN_LEN];
	DWORD	Style;
	bool	operator==(const RECENT_HISTROY_ITEM &Obj)const
	{
		return TStrICmp(FileName,Obj.FileName)==0;
	}
};

bool	InstallDependData(PCSTR FileNameList);

class CSyserApp : public CLocalWispApp
{
public:
	CSyserApp(void);
	~CSyserApp(void);
	virtual bool	InitInstance();
	virtual int		ExitInstance();
	virtual	bool	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool	CheckNewVersion();
	INTERNET_PROXY_INFO* GetIEDefaultProxy(LPTSTR lpszProxy,DWORD *nProxyPort);
	LPTSTR GetIEDefaultProxyUserName(LPTSTR lpszUserName);
	LPTSTR GetIEDefaultProxyPassword(LPTSTR lpszPassword);
	HMENU	m_hNotifyMenu;
	HMENU	m_hSubNotifyMenu;
	CSyserInterface	m_SyserInterface;
	CSourceDebug	m_SourceDebug;
	CNoPDBSymbol	m_NoPDBSymbol;
	CMainFrame		m_MainFrame;
	void	InitEnv();
	void	LoadCFG();
	CHttpDownload m_UpdateNewVersionDownload;
	char	m_szSyserCfgFN[MAX_FN_LEN];
	char	m_szSyserAppCfgFN[MAX_FN_LEN];
	char	m_szSyserColorCfgFN[MAX_FN_LEN];
	TList<RECENT_HISTROY_ITEM>	m_HistroyList;
	bool						m_bHistroyModified;
	void	LoadHistroy();
	void	SaveHistroy();
	void	InsertHistroy(PCSTR szFileName,DWORD Style);
};

extern CSyserApp	theApp;

#endif

