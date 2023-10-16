#ifndef _MAIN_TAB_WND_H_
#define _MAIN_TAB_WND_H_

#include "CtrlPage1.h"

enum MAIN_TAB_WND_IDX
{
	MAIN_TAB_CONTROL = 0,
	MAIN_TAB_CONSOLE,
	MAIN_TAB_CODE_WND,
	MAIN_TAB_FILE_WND
};

class CMainTabWnd : public CWispTabWnd
{
public:
	CMainTabWnd(void);
	~CMainTabWnd(void);
public:
	CWispRGBSelect	m_RGBSelect;
	CWispConsoleWnd	m_ConsoleWnd;
	CCtrlPage1		m_CtrlPage1;
	CWispHexWnd		m_DataWnd;
	CWispDIB		m_TabDIB;
public:
	DECLARE_WISP_MSG_MAP
	bool		OnCreate(IN WISP_MSG*pMsg);
	bool		OnDestroy(IN WISP_MSG*pMsg);
};


#endif
