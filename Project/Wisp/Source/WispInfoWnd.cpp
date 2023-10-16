#include "StdAfx.h"
#include "WispInfoWnd.h"

WISP_MSG_MAP_BEGIN(CWispInfoWnd)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
WISP_MSG_MAP_END(CWispBaseWnd)

CWispInfoWnd::CWispInfoWnd(void)
{
}

CWispInfoWnd::~CWispInfoWnd(void)
{
}

bool CWispInfoWnd::OnUpdate(IN WISP_MSG*pMsg)
{
	m_WindowDC.DrawFrameRect(&m_WindowRect);
	if(m_WndText.m_Length)
		m_WindowDC.DrawString(m_WndText,&m_WindowRect, 0);
	return true;
}

