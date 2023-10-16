#include "StdAfx.h"
#include "WispTipWnd.h"

WISP_MSG_MAP_BEGIN(CWispTipWnd)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
WISP_MSG_MAP_END(CWispWnd)

CWispTipWnd::CWispTipWnd()
{
	m_CtrlType = WISP_CTRL_TIP_WND;
	m_pTipHelpWnd = NULL;
}

bool CWispTipWnd::OnUpdate(IN WISP_MSG*pMsg)
{
	CWispRect rc(m_WindowRect);
	m_WindowDC.DrawFrameRect(&rc);
	rc.DeflateRect(1,1);
	m_WindowDC.DrawFullRect(&rc,SYS_COLOR[SC_UNNAMED_17]);
	if(m_WndText.m_Length)
	{
		rc.DeflateRect(2,1);
		m_WindowDC.DrawString(m_WndText,&rc,0);
	}
	return false;
}

void CWispTipWnd::AutoAdjustPostion(CWispBaseWnd*pTipHelpWnd)
{
	WISP_RECT rc;
	WISP_RECT CalcRect;
	m_WindowDC.DrawString(m_WndText,&CalcRect,WISP_DT_CALCRECT);
	CalcRect.cy+=5;
	CalcRect.cx+=8;
	m_pTipHelpWnd = pTipHelpWnd;
	rc.y = m_pWispBase->m_MousePT.y+20;
	rc.cy = m_WindowDC.m_pFont->m_Height+5;
	rc.cx = m_WindowDC.GetTextExtent(m_WndText)+8;
	rc.x = m_pWispBase->m_MousePT.x-rc.cx/2;
	CalcRect.x = m_pWispBase->m_MousePT.x-CalcRect.cx/2;
	CalcRect.y = m_pWispBase->m_MousePT.y+20;
	if(CalcRect.x<=0)
		CalcRect.x = 10;
	if(CalcRect.y <= 10)
		CalcRect.y = 10;
	if(rc.x <= 0)
		rc.x = 10;
	if(rc.y <= 0)
		rc.y = 10;
	if(CalcRect.x+CalcRect.cx - 1 >= m_pWispBase->m_FrameBuffer.Width)
		CalcRect.x = m_pWispBase->m_FrameBuffer.Width - CalcRect.cx - 10;
	if(rc.x+rc.cx - 1>= m_pWispBase->m_FrameBuffer.Width)
		rc.x = m_pWispBase->m_FrameBuffer.Width - rc.cx - 10;
	if(CalcRect.y+CalcRect.cy - 1>= m_pWispBase->m_FrameBuffer.Height)
		CalcRect.y = m_pWispBase->m_MousePT.y-30;
	if(rc.y+rc.cy - 1>= m_pWispBase->m_FrameBuffer.Height)
		rc.y = m_pWispBase->m_MousePT.y-30;
	MoveToScreen(CalcRect.x,CalcRect.y);
	Resize(CalcRect.cx,CalcRect.cy);
	Top();
}