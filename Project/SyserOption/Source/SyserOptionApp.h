#ifndef _SYSER_OPTION_APP_H_
#define _SYSER_OPTION_APP_H_

#include "MainFrame.h"
#include "BootOptionForm.h"
#include "VideoModeForm.h"

class CSyserOptionApp : public CLocalWispApp
{
public:
	CSyserOptionApp(void);
	~CSyserOptionApp(void);
	virtual bool	InitInstance();
	virtual int		ExitInstance();
	void	InitEnv();
	void	LoadCFG();
	void	SendSyserMsg(DWORD Msg);
	void	SendSyserAppMsg(DWORD Msg);
	char	m_szColorCfgFN[MAX_FN_LEN];
	char	m_szSyserCfgFN[MAX_FN_LEN];
	char	m_szSyserAppCfgFN[MAX_FN_LEN];
	CMainFrame		m_MainFrame;
	COptionPage		m_OptionPage;
	CBootOptionForm m_BootOptionForm;
	CVideoModeForm	m_VideoModeForm;
	OSVERSIONINFO	m_VersionInfo;
};

extern CSyserOptionApp	theApp;

#endif
