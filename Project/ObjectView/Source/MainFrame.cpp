#include "StdAfx.h"
#include "MainFrame.h"

WISP_MSG_MAP_BEGIN(CMainFrame)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
WISP_MSG_MAP_END(CWispWnd)

bool CMainFrame::OnCreate(IN WISP_MSG*pMsg)
{
	m_Style|=WISP_WS_BACK_TRANS;
	m_ObjectWnd.Create(WSTR("Object Directory Wnd"),CWispRect(0,0,400,300),this,0,WISP_SWS_HORZ|WISP_WS_NULL);
	return true;
}

bool CMainFrame::OnSize(IN WISP_MSG*pMsg)
{
	m_ObjectWnd.Resize(m_ClientRect.cx,m_ClientRect.cy);
	return true;
}
