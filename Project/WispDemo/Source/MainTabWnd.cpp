#include "StdAfx.h"
#include "MainTabWnd.h"

WISP_MSG_MAP_BEGIN(CMainTabWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispTabWnd)

CMainTabWnd::CMainTabWnd(void)
{
}

CMainTabWnd::~CMainTabWnd(void)
{
}

bool CMainTabWnd::OnCreate(IN WISP_MSG*pMsg)
{
	m_RGBSelect.CreateForm();
	m_CtrlPage1.CreateForm(this);
	m_ConsoleWnd.Create(NULL,CWispRect(0,0,400,300),this,MAIN_TAB_CONSOLE,WISP_WS_NULL,WISP_SH_NORMAL);
	m_DataWnd.Create(NULL,CWispRect(200,200,400,300),this,MAIN_TAB_CODE_WND,WISP_WS_NULL,WISP_SH_NORMAL);
	//InsertWnd(WISP_STR("RGB"),&m_RGBSelect);
	InsertWnd(WISP_STR("Control"),&m_CtrlPage1);
	InsertWnd(WISP_STR("Console"),&m_ConsoleWnd);
	InsertWnd(WISP_STR("Code"),&m_DataWnd);
	m_ConsoleWnd.Printf(WSTR("%<B>Wisp%<1>平台无关图形系统\n"));
	return TRUE;
}

bool CMainTabWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	m_TabDIB.Destroy();
	return true;
}