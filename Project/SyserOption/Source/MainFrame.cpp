#include "StdAfx.h"
#include "SyserOptionApp.h"

WISP_MSG_MAP_BEGIN(CMainFrame)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
WISP_MSG_MAP_END(CWispWnd)

bool CMainFrame::OnCreate(IN WISP_MSG*pMsg)
{
	m_Style|=WISP_WS_BACK_TRANS;
	m_MainTabWnd.Create(NULL,0,0,m_ClientRect.cx,m_ClientRect.cy,this,WISP_ID_MAIN_TAB,WISP_TWS_TOP);
	m_OptionPage.CreateForm(&m_MainTabWnd);
	m_GUIColorPage.CreateForm(&m_MainTabWnd);
	m_SDSFilePage.CreateForm(&m_MainTabWnd);
	m_ExportModulePage.CreateForm(&m_MainTabWnd);
	m_KeyMappingPage.CreateForm(&m_MainTabWnd);

	m_MainTabWnd.InsertWnd(WSTR("Option"),&m_OptionPage,WispTKDIBListDIB("\\Toolbar.bmp",16,16,29));
	m_MainTabWnd.InsertWnd(WSTR("Module Export Symbols"),&m_ExportModulePage,WispTKDIBListDIB("\\Toolbar.bmp",16,16,50));
	m_MainTabWnd.InsertWnd(WSTR("SDS Symbols"),&m_SDSFilePage,WispTKDIBListDIB("\\Toolbar.bmp",16,16,17));
	m_MainTabWnd.InsertWnd(WSTR("Color"),&m_GUIColorPage,WispTKDIBListDIB("\\Toolbar.bmp",16,16,55));
	m_MainTabWnd.InsertWnd(WSTR("Key Mapping"),&m_KeyMappingPage,WispTKDIBListDIB("\\Toolbar.bmp",16,16,7)); 
	return true;
}

bool CMainFrame::OnSize(IN WISP_MSG*pMsg)
{
	m_MainTabWnd.Resize(m_ClientRect.cx,m_ClientRect.cy);
	return true;
}
