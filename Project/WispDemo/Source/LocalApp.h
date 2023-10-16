#ifndef _LOCALAPP_HEADER_
#define _LOCALAPP_HEADER_

#include "MainFrame.h"

class CLocalApp : public CWinWisp
{
public:
	CLocalApp(void);
	~CLocalApp(void);
	virtual bool	InitInstance();
	virtual int		ExitInstance();
};

extern CLocalApp	theApp;

#endif

