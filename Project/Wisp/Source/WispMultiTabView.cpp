#include "StdAfx.h"
#include "WispMultiTabView.h"

WISP_MSG_MAP_BEGIN(CWispMultiTabView)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispTabWnd)

CWispMultiTabView::CWispMultiTabView()
{
	m_pToolbarRes = NULL;
}

bool CWispMultiTabView::OnCreate(IN WISP_MSG*pMsg)
{
	if(m_pToolbarRes)
		m_TabToolbar.CreateEx(this,0,0,WISP_MULTI_TAB_TOOLBAR_CMD_ID,WISP_TBS_WINDOW);
	return true;
}

bool CWispMultiTabView::OnDestroy(IN WISP_MSG*pMsg)
{
	return true;
}

bool CWispMultiTabView::OnSize(IN WISP_MSG*pMsg)
{
	int x,y;
	if(m_Style & WISP_TWS_TOP)
		y = CENTER_ALGN(m_TabToolbar.m_WindowRect.cy,m_TabSpaceHeight);
	else
		y = m_ClientRect.cy - m_TabSpaceHeight + CENTER_ALGN(m_TabToolbar.m_WindowRect.cy,m_TabSpaceHeight);
	x = m_ClientRect.cx - m_TabToolbar.m_WindowRect.cx-2;
	if(m_TabToolbar.IsWindow())
		m_TabToolbar.MoveToClient(x,y);
	return true;
}
