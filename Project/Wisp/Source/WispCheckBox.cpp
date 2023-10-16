#include "StdAfx.h"
#include "WispCheckBox.h"

WISP_MSG_MAP_BEGIN(CWispCheckBox)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
WISP_MSG_MAP_END(CWispBaseWnd)

CWispCheckBox::CWispCheckBox(void)
{
	m_bIsMultiLine = false;
	m_bMouseDown = false;	
	m_bMouseIn = false;
	m_CtrlType = WISP_CTRL_CHECK_BOX;
}

bool CWispCheckBox::InitWnd()
{
	if(CWispBaseWnd::InitWnd()==false)
		return false;
	m_Style &= ~(WISP_WS_CAPTION|WISP_WS_BT_MAX|WISP_WS_SIZABLE|WISP_WS_BT_MIN|WISP_WS_BT_CLOSE|WISP_WS_BORDER);
	m_Style |= WISP_WS_BACK_TRANS;
	if(m_Style & WISP_CBS_PUSHLIKE)
		m_Style |= WISP_WS_THIN_BORDER;
	if(m_Style & WISP_CBS_MULTILINE)
		m_bIsMultiLine = true;
	if(m_Style & WISP_CBS_PUSHLIKE)
	{
		m_TextRect.x = m_WindowRect.x;
		m_TextRect.y = m_WindowRect.y;
		m_TextRect.cx = m_WindowRect.cx;
		m_TextRect.cy = m_WindowRect.cy;
		m_CheckBoxRect.x = m_TextRect.x;
		m_CheckBoxRect.y = m_TextRect.y;
		m_CheckBoxRect.cx = m_TextRect.cx;
		m_CheckBoxRect.cy = m_TextRect.cy;
	}
	else
	{
		if(m_Style & WISP_CBS_RIGHT)
		{
			m_CheckBoxRect.x = m_WindowRect.x + m_WindowRect.cx - WISP_CHECKBOX_WIDTH-4;
			m_CheckBoxRect.cx = WISP_CHECKBOX_WIDTH;
			m_CheckBoxRect.cy = WISP_CHECKBOX_HEIGH;
			m_CheckBoxRect.y = m_WindowRect.y + (m_WindowRect.cy - WISP_CHECKBOX_HEIGH) / 2;
			if(m_Style & WISP_CBS_TOP)
				m_CheckBoxRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_CBS_BOTTOM)
					m_CheckBoxRect.y = m_WindowRect.y + m_WindowRect.cy - WISP_CHECKBOX_HEIGH;
			m_TextRect.x = m_WindowRect.x;
			m_TextRect.y = m_WindowRect.y + (m_WindowRect.cy - WISP_CHECKBOX_HEIGH) / 2;
			if(m_Style & WISP_CBS_TOP)
				m_TextRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_CBS_BOTTOM)
					m_TextRect.y = m_WindowRect.y + m_WindowRect.cy - m_WindowDC.m_pFont->m_Height;
			m_TextRect.cx = m_CheckBoxRect.x - m_TextRect.x - WISP_TEXT_CHECKBOX_DISTANCE;
			if(m_Style & WISP_CBS_MULTILINE)
				m_TextRect.cy = m_WindowRect.cy;
			else
			{
				m_TextRect.cy = m_WindowDC.m_pFont->m_Height;
				if(m_WindowDC.m_pFont->m_Height > WISP_CHECKBOX_HEIGH)
				{
					m_CheckBoxRect.y += (m_WindowDC.m_pFont->m_Height - WISP_CHECKBOX_HEIGH) / 2 ;
				}
			}
		}
		else
		{
			m_CheckBoxRect.x = m_WindowRect.x;
			m_CheckBoxRect.cx = WISP_CHECKBOX_WIDTH;
			m_CheckBoxRect.cy = WISP_CHECKBOX_HEIGH;
			m_CheckBoxRect.y = m_WindowRect.y + (m_WindowRect.cy - WISP_CHECKBOX_HEIGH) / 2;
			if(m_Style & WISP_CBS_TOP)
				m_CheckBoxRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_CBS_BOTTOM)
					m_CheckBoxRect.y = m_WindowRect.y + m_WindowRect.cy - WISP_CHECKBOX_HEIGH;
			m_TextRect.x = m_CheckBoxRect.x + m_CheckBoxRect.cx + WISP_TEXT_CHECKBOX_DISTANCE;
			m_TextRect.y = m_WindowRect.y + (m_WindowRect.cy - WISP_CHECKBOX_HEIGH) / 2;
			if(m_Style & WISP_CBS_TOP)
				m_TextRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_CBS_BOTTOM)
					m_TextRect.y = m_WindowRect.y + m_WindowRect.cy - m_WindowDC.m_pFont->m_Height;
			m_TextRect.cx = m_WindowRect.cx - (m_TextRect.x - m_WindowRect.x);
			if(m_Style & WISP_CBS_MULTILINE)
				m_TextRect.cy = m_WindowRect.cy;
			else
			{
				m_TextRect.cy = m_WindowDC.m_pFont->m_Height;
				if(m_WindowDC.m_pFont->m_Height > WISP_CHECKBOX_HEIGH)
				{
					m_CheckBoxRect.y += (m_WindowDC.m_pFont->m_Height - WISP_CHECKBOX_HEIGH) / 2 ;
				}
			}
		}
	}
	return true;
}

bool CWispCheckBox::OnUpdate(IN WISP_MSG*pMsg)
{
	if((m_Style&WISP_WS_BACK_TRANS)==0)
		m_pWispBase->m_pCurDrawObj->DrawCtrlClient(&m_WindowDC, &m_WindowRect);
	if((m_Style & WISP_CBS_PUSHLIKE)==0)
	{
		m_WindowDC.DrawSystemStandardIcon(m_CheckBoxRect,IsMarked()?WISP_SSI_CHECKBOX_CHECKED:WISP_SSI_CHECKBOX_UNCHECKED);
	}
	DrawCaption();
	if(m_Style & WISP_CBS_PUSHLIKE)
	{
		if(IsMarked() || (m_bMouseDown && m_bMouseIn))
			m_WindowDC.DrawFrameRect(&m_WindowRect,false,1);
		else
			m_WindowDC.DrawFrameRect(&m_WindowRect,true,1);
	}
	return false;
}

// 显示文本信息
void CWispCheckBox::DrawCaption(void)
{
	WISP_RECT Rect;
	INT uFormat = WISP_DT_VCENTER;  //缺省的文本显示风格是 横向左对齐,纵向中间对齐.
	Rect.x = m_TextRect.x;
	Rect.y = m_TextRect.y;
	Rect.cx = m_TextRect.cx;
	Rect.cy = m_TextRect.cy;
	if(m_Style & WISP_CBS_PUSHLIKE)
	{
		uFormat |= WISP_DT_CENTER;
		if(m_bMouseDown && m_bMouseIn)
		{
			Rect.x = m_TextRect.x + 1;			
		}
	}
	if(!m_bIsMultiLine)
		uFormat |= WISP_DT_SINGLELINE;
	if(m_Style & WISP_CBS_BOTTOM)
		uFormat |= WISP_DT_BOTTOM;		
	if(IsDisabled())
		m_WindowDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRAY]);
	m_WindowDC.DrawString(m_WndText,&Rect,uFormat);
	if(IsDisabled())
		m_WindowDC.RestoreTextColor();
}

bool CWispCheckBox::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{
		if(pMsg->KeyEvent.bKeyDown)
			OnMouseLDown(pMsg);
		else
		{
			if(OnMouseLUp(pMsg))
			{			
				WISP_MSG Msg;
				Msg.hWnd = m_OwnerWnd;
				Msg.Msg	= WISP_WM_COMMAND;	
				Msg.Command.CtrlType= m_CtrlType;
				Msg.Command.CmdID	= m_CmdID;
				Msg.Command.CmdMsg	= WISP_CMD_CB_CLICK;
				Msg.Command.Param1 = (m_Style&WISP_WS_MARKED)!=0;
				SEND_MSG(&Msg);
			}
		}
		Update();
	}
	return true;
}

bool CWispCheckBox::OnMouseLDown(IN WISP_MSG*pMsg)
{
	m_bMouseDown = true;
	return true;
}

bool CWispCheckBox::OnMouseLUp(IN WISP_MSG*pMsg)
{
	if(m_bMouseIn&&m_bMouseDown)
	{	
		if(IsChecked())
			Check(false);
		else
			Check(true);
		m_bMouseDown = false;
		return true;
	}
	return false;
}

bool CWispCheckBox::OnMouseLeave(IN WISP_MSG*pMsg)
{
	m_bMouseIn = false;
	if(m_bMouseDown)
	{
		if(pMsg->bMsgLBTDown==false)
			m_bMouseDown=false;
		return false;
	}
	return true;
}

bool CWispCheckBox::OnMouseMove(IN WISP_MSG*pMsg)
{
	m_bMouseIn = true;
	return true;
}

void CWispCheckBox::Check(bool bCheck)
{
	if(bCheck)
	{
		m_Style|=WISP_WS_MARKED;
	}
	else
	{
		m_Style&=~WISP_WS_MARKED;
	}
}
