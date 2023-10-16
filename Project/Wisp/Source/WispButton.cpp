#include "StdAfx.h"
#include "WispButton.h"

WISP_MSG_MAP_BEGIN(CWispButton)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_MOVE,OnMove)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
WISP_MSG_MAP_END(CWispBaseWnd)

bool CWispButton::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.KeyType==WISP_VK_LBUTTON || pMsg->KeyEvent.KeyType==WISP_VK_RETURN)
	{
		if(pMsg->KeyEvent.bKeyDown)
		{
			if(m_bPressed==false)
			{
				m_bPressed	= true;
				Update();
				WISP_MSG Msg;
				Msg.hWnd = m_OwnerWnd;
				Msg.hSrcWnd = this;
				Msg.Msg	= WISP_WM_COMMAND;
				Msg.Command.CtrlType= WISP_CTRL_BUTTON;
				Msg.Command.CmdID	= m_CmdID;
				Msg.Command.CmdMsg	= WISP_CMD_BT_DOWN;
				SEND_MSG(&Msg);
			}
		}
		else
		{
			if(m_bPressed)
			{
				m_bPressed = false;
				Update();
				WISP_MSG Msg;
				Msg.hWnd = m_OwnerWnd;
				Msg.hSrcWnd = this;
				Msg.Msg = WISP_WM_COMMAND;
				Msg.Command.CtrlType= WISP_CTRL_BUTTON;
				Msg.Command.CmdID = m_CmdID;
				Msg.Command.CmdMsg = WISP_CMD_BT_UP;
				if(SEND_MSG(&Msg))
				{
					Msg.hWnd=m_OwnerWnd;
					Msg.Msg=WISP_WM_EVENT;
					POST_MSG(&Msg);
				}
				return true;
			}
		}
	}
	return true;
}

void CWispButton::RecalcLayout()
{
	CWispBaseWnd::RecalcLayout();
	if(IsDisabled())
	{
		if(m_bMouseInBTRect)
		{
			m_bMouseInBTRect=false;
		}
		return;
	}
	if(PtInRect(&m_ScrWindowRect, &m_pWispBase->m_MousePT)!=m_bMouseInBTRect)
	{
		m_bMouseInBTRect=!m_bMouseInBTRect;
		Update();
	}
}

bool CWispButton::OnUpdate(IN WISP_MSG*pMsg)
{
	UINT State;
	COLORREF OrgTextColor;
	State = STATUS_NORMAL;
	if(m_bMouseInBTRect)
		State = STATUS_HOVER;
	if(m_bPressed)
		State = STATUS_DOWN;
	CWispRect	rcBtn(m_WindowRect);
	// client background
	if((m_Style & WISP_WS_BACK_TRANS)==0)
	{
		m_pWispBase->m_pCurDrawObj->DrawButtonClient(&m_WindowDC, &m_WindowRect, State);
	}
	// back dib
	if(*m_DIBList)
	{
		int x,y;
		if(IsDisabled())
		{
			if(m_DIBList[WISP_BT_DIB_DISABLE])
			{
				x = CENTER_ALGN(m_DIBList[WISP_BT_DIB_DISABLE]->m_FrameBuffer.Width,m_WindowRect.cx);
				y = CENTER_ALGN(m_DIBList[WISP_BT_DIB_DISABLE]->m_FrameBuffer.Height,m_WindowRect.cy);
				m_WindowDC.DrawDIB(x,y,m_DIBList[WISP_BT_DIB_DISABLE]);
			}
			else
			{
				x = CENTER_ALGN(m_DIBList[WISP_BT_DIB_NORMAL]->m_FrameBuffer.Width,m_WindowRect.cx);
				y = CENTER_ALGN(m_DIBList[WISP_BT_DIB_NORMAL]->m_FrameBuffer.Height,m_WindowRect.cy);
				m_WindowDC.DrawGrayDIB(x,y,m_DIBList[WISP_BT_DIB_NORMAL]);
			}
		}
		else if(m_bPressed)
		{
			if(m_DIBList[WISP_BT_DIB_DOWN])
			{
				x = CENTER_ALGN(m_DIBList[WISP_BT_DIB_DOWN]->m_FrameBuffer.Width,m_WindowRect.cx);
				y = CENTER_ALGN(m_DIBList[WISP_BT_DIB_DOWN]->m_FrameBuffer.Height,m_WindowRect.cy);
				m_WindowDC.DrawDIB(x,y,m_DIBList[WISP_BT_DIB_DOWN]);
			}
			else
			{
				x = CENTER_ALGN(m_DIBList[WISP_BT_DIB_NORMAL]->m_FrameBuffer.Width,m_WindowRect.cx)+1;
				y = CENTER_ALGN(m_DIBList[WISP_BT_DIB_NORMAL]->m_FrameBuffer.Height,m_WindowRect.cy)+1;
				m_WindowDC.DrawDIB(x,y,m_DIBList[WISP_BT_DIB_NORMAL]);
			}
		}
		else if(m_bMouseInBTRect && m_DIBList[WISP_BT_DIB_HOVER])
		{
			x = CENTER_ALGN(m_DIBList[WISP_BT_DIB_HOVER]->m_FrameBuffer.Width,m_WindowRect.cx);
			y = CENTER_ALGN(m_DIBList[WISP_BT_DIB_HOVER]->m_FrameBuffer.Height,m_WindowRect.cy);
			m_WindowDC.DrawDIB(x,y,m_DIBList[WISP_BT_DIB_HOVER]);
		}
		else
		{
			x = CENTER_ALGN(m_DIBList[WISP_BT_DIB_NORMAL]->m_FrameBuffer.Width,m_WindowRect.cx);
			y = CENTER_ALGN(m_DIBList[WISP_BT_DIB_NORMAL]->m_FrameBuffer.Height,m_WindowRect.cy);
			m_WindowDC.DrawDIB(x,y,m_DIBList[WISP_BT_DIB_NORMAL]);
		}
	}
	// border
	if(m_Style & WISP_BS_TOOLBAR_BT)
	{
		switch(State)
		{
		case STATUS_HOVER:
			m_WindowDC.DrawFrameRect(&m_WindowRect);
			break;
		case STATUS_DOWN:
			m_WindowDC.DrawFrameRect(&m_WindowRect,false);
			break;
		}
	}
	else if((m_Style & WISP_BS_NOBORDER)==0)
	{
		if(m_DIBList[State]==NULL)
			m_pWispBase->m_pCurDrawObj->DrawButtonFrameRect(&m_WindowDC, &rcBtn, State);
		if(State == STATUS_HOVER)
			rcBtn.DeflateRect(3, 3);
		else
			rcBtn.DeflateRect(1, 1);
	}
	// text
	if(m_WndText.m_Length)
	{
		if(m_bSetTextPos)
			rcBtn = m_TextRect;
		if(State != STATUS_HOVER)
			rcBtn.DeflateRect(2, 2);
		UINT uStyle = WISP_DT_SINGLELINE|WISP_DT_VCENTER;
		switch(m_Style & WISP_BS_TEXT_POS_MASK)
		{
			case WISP_BS_TEXT_LEFT:
				uStyle|=WISP_DT_LEFT;
				break;
			case WISP_BS_TEXT_RIGHT:
				uStyle|=WISP_DT_RIGHT;
				break;
			default://WISP_BS_TEXT_CENTER
				uStyle|=WISP_DT_CENTER;
				break;
		}
		if(IsDisabled())
		{
			OrgTextColor = m_WindowDC.GetTextColor();
			m_WindowDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRAY]);
		}
		if(State == STATUS_DOWN)
		{
			rcBtn.x++;
			rcBtn.y++;
		}
		
		m_WindowDC.DrawString(m_WndText, &rcBtn, uStyle);
		if(IsDisabled())
		{			
			m_WindowDC.SetTextColor(OrgTextColor);
		}
	}
	return false;
}

bool CWispButton::OnMouseMove(IN WISP_MSG*pMsg)
{
	if(m_bMouseInBTRect)
		return true;
	HoverNotify();
	SendCmdMsg(WISP_CMD_ITEM_HOVER);
	m_bMouseInBTRect = true;
	Update();
	return true;
}

bool CWispButton::OnMouseLeave(IN WISP_MSG*pMsg)
{
	m_bPressed = m_bMouseInBTRect = false;
	UnhoverNotify();
	SendCmdMsg(WISP_CMD_ITEM_UNHOVER);
	Update();
	return true;
}

bool CWispButton::OnMove(IN WISP_MSG*pMsg)
{
	if(m_bMouseInBTRect)
	{
		m_bMouseInBTRect = PtInRect(&m_ScrWindowRect, &m_pWispBase->m_MousePT);
		Update();
	}
	return true;
}

CWispButton::CWispButton()
{
	m_CtrlType = WISP_CTRL_BUTTON;
	m_bSetTextPos=false;
}

CWispButton::~CWispButton()
{
}

bool CWispButton::InitWnd()
{
	if(CWispBaseWnd::InitWnd()==false)
		return false;
	m_bPressed=false;
	m_bMouseInBTRect = PtInRect(&m_ScrWindowRect, &m_pWispBase->m_MousePT);
	ZeroMemory(m_DIBList,sizeof(m_DIBList));
	return true;
}

bool CWispButton::CreateEx(CWispDIB* pDib, int x, int y, IN CWispWnd*pParentWnd, IN UINT CmdID,IN UINT Style)
{
	if( Create(NULL, x, y, pDib->m_FrameBuffer.Width, pDib->m_FrameBuffer.Height, pParentWnd, CmdID, Style, WISP_SH_NORMAL) )
	{
		SetDIB(pDib);
		return true;
	}
	return false;
}

bool CWispButton::CreateEx(CWispDIBList* pDibList, int x, int y, IN CWispWnd*pParentWnd, IN UINT CmdID,IN UINT Style)
{
	if( Create(NULL, x, y, pDibList->m_DIBList->m_FrameBuffer.Width, pDibList->m_DIBList->m_FrameBuffer.Height, pParentWnd, CmdID, Style, WISP_SH_NORMAL) )
	{
		SetDIBList(pDibList);
		return true;
	}
	return false;
}

bool CWispButton::SetDIB(CWispDIB*pDIB,WISP_BT_DIB ID)
{
	m_DIBList[ID]=pDIB;
	return true;
}

bool CWispButton::SetDIBList(CWispDIBList*pDIBList)
{
	for(int n=0;n<WISP_BT_DIB_COUNT;n++)
	{
		m_DIBList[n]=pDIBList->GetDIB(n);
	}
	return true;
}

void CWispButton::SetTextPos(IN WISP_POINT Point)
{
	if(Point.x < m_WindowRect.cx && Point.y < m_WindowRect.cy)
	{
		m_bSetTextPos=true;
		m_TextRect.x = Point.x;
		m_TextRect.y = Point.y;
		m_TextRect.cx = m_WindowRect.cx - Point.x;
		m_TextRect.cy = m_WindowRect.cy - Point.y;
	}
}
void CWispButton::SetTextRect(IN WISP_RECT TextRect)
{
	if(TextRect.x < m_WindowRect.cx && TextRect.y < m_WindowRect.cy)
	{
		m_bSetTextPos=true;
		m_TextRect = TextRect;
		if(m_TextRect.x + m_TextRect.cx > m_WindowRect.cx)
			m_TextRect.cx = m_WindowRect.cx - m_TextRect.x;
		if(m_TextRect.y + m_TextRect.cy > m_WindowRect.cy)
			m_TextRect.cy = m_WindowRect.cy - m_TextRect.y;
	}
}