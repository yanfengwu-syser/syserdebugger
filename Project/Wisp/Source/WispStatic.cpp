#include "StdAfx.h"
#include "WispStatic.h"

WISP_MSG_MAP_BEGIN(CWispStaticStr)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)	
WISP_MSG_MAP_END(CWispBaseWnd)

CWispStaticStr::CWispStaticStr()
{
	m_CtrlType = WISP_CTRL_STATIC_STRING;
}

bool CWispStaticStr::OnUpdate(IN WISP_MSG*pMsg)
{
	COLORREF OrgTextColor;
	if(m_WndText.m_Length)
	{
		if(IsDisabled())
		{
			OrgTextColor = m_WindowDC.GetTextColor();
			m_WindowDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRAY]);
		}
		m_WindowDC.DrawString(m_WndText,&m_WindowRect, 0);
		if(IsDisabled())
			m_WindowDC.SetTextColor(OrgTextColor);
	}
	return true;
}

WISP_MSG_MAP_BEGIN(CWispStaticDIB)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
WISP_MSG_MAP_END(CWispBaseWnd)

CWispStaticDIB::CWispStaticDIB()
{
	m_CtrlType = WISP_CTRL_STATIC_DIB;
}

bool CWispStaticDIB::Create(CWispDIB*pDIB,int x,int y,CWispBaseWnd* pParentWnd, UINT nID)
{
	m_pDIB = pDIB;
	return CWispBaseWnd::Create(NULL, x, y,m_pDIB->m_FrameBuffer.Width,m_pDIB->m_FrameBuffer.Height,pParentWnd, nID,WISP_WS_NULL);
}

bool CWispStaticDIB::OnUpdate(IN WISP_MSG*pMsg)
{
	m_WindowDC.DrawDIB(0,0,m_pDIB);
	return true;
}


WISP_MSG_MAP_BEGIN(CWispStaticGroup)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
WISP_MSG_MAP_END(CWispBaseWnd)

CWispStaticGroup::CWispStaticGroup()
{
	m_CtrlType = WISP_CTRL_STATIC_GROUP;
}

bool CWispStaticGroup::OnGetFocus(IN WISP_MSG*pMsg)
{
	return false;
}

bool CWispStaticGroup::OnUpdate(IN WISP_MSG*pMsg)
{
	int nTextLen = m_WindowDC.GetTextExtent(m_WndText);
	COLORREF color = m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT];
	CWispRect rc(m_WindowRect);
	rc.y += m_WindowDC.m_pFont->m_Height/2;
	rc.cy-= m_WindowDC.m_pFont->m_Height/2;
	m_WindowDC.DrawCircleLeftTop(rc.x+5,rc.y+5,5,color);
	m_WindowDC.DrawCircleLeftBottom(rc.x+5,rc.y2()-5,5,color);
	m_WindowDC.DrawCircleRightTop(rc.x2()-5,rc.y+5,5,color);
	m_WindowDC.DrawCircleRightBottom(rc.x2()-5,rc.y2()-5,5,color);
	m_WindowDC.DrawVLine(rc.x,		rc.y+5,	rc.y2()-5, color);
	m_WindowDC.DrawVLine(rc.x2(),	rc.y+5,	rc.y2()-5, color);
	m_WindowDC.DrawHLine(rc.x+nTextLen?nTextLen+15:nTextLen+5, rc.x2()-5, rc.y, color);
	m_WindowDC.DrawHLine(rc.x+5,	rc.x2()-5, rc.y2(), color);
	rc.SetRect(rc.x+10,rc.y-m_WindowDC.m_pFont->m_Height/2,nTextLen,m_WindowDC.m_pFont->m_Height);
	if(m_WndText.m_Length)
		m_WindowDC.DrawString(m_WndText, &rc, WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	return false;
}

WISP_MSG_MAP_BEGIN(CWispStaticURL)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_ENTER,OnMouseEnter)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
WISP_MSG_MAP_END(CWispBaseWnd)

CWispStaticURL::CWispStaticURL()
{
	m_CtrlType = WISP_CTRL_STATIC_URL;
	m_bHover = false;
}

bool CWispStaticURL::OnUpdate(IN WISP_MSG*pMsg)
{
	if(m_WndText.m_Length)
	{
		if(IsDisabled())
		{
			m_WindowDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRAY]);
			m_WindowDC.DrawString(m_WndText,&m_WindowRect, 0);
			m_WindowDC.RestoreTextColor();
		}
		else
		{
			if(m_bHover)
				m_WindowDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_LIGHT_BLUE]);
			m_WindowDC.DrawString(m_WndText,&m_WindowRect, 0);
			if(m_bHover)
			{
				m_WindowDC.DrawHLine(0,m_WindowDC.GetTextExtent(m_WndText),
					m_WindowRect.y+m_WindowDC.GetTextHeight(),m_pWispBase->m_pCurDrawObj->m_crSystem[SC_LIGHT_BLUE]);
				m_WindowDC.RestoreTextColor();
			}
		}
	}
	return true;
}

bool CWispStaticURL::OnKeyEvent(IN WISP_MSG*pMsg)
{
	WISP_MSG Msg;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON && pMsg->KeyEvent.bKeyDown == false)
	{
#ifdef CODE_OS_WIN
		char szBuffer[MAX_FN_LEN];
		UnicodeToAnsi(GetWindowText(),szBuffer,sizeof(szBuffer));
		ShellExecute(NULL,"open",szBuffer,NULL,NULL,SW_SHOWMAXIMIZED);
#endif
		Msg.hWnd = m_OwnerWnd;
		Msg.Msg = WISP_WM_COMMAND;
		Msg.Command.CmdID = m_CmdID;
		Msg.Command.CmdMsg = WISP_CMD_STATIC_URL_CLICK;
		Msg.Command.Param1 = 0;
		Msg.Command.Param2 = NULL;
		if(SEND_MSG(&Msg)==false)
			return false;
	}
	
	return true;
}

bool CWispStaticURL::OnMouseEnter(IN WISP_MSG*pMsg)
{
	m_bHover = true;
	Update();
	return true;
}

bool CWispStaticURL::OnMouseLeave(IN WISP_MSG*pMsg)
{
	m_bHover = false;
	Update();
	return true;
}



