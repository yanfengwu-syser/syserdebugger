#ifndef _SYSER_OPTION_APP_H_
#define _SYSER_OPTION_APP_H_

#include "MainFrame.h"

class CObjectViewApp : public CLocalWispApp
{
public:
	CObjectViewApp(void);
	~CObjectViewApp(void);
	virtual bool	InitInstance();
	virtual int		ExitInstance();
	CMainFrame		m_MainFrame;
	HANDLE			m_hMutex;
};

extern CObjectViewApp	theApp;

#endif
