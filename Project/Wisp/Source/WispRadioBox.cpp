#include "StdAfx.h"
#include "WispRadioBox.h"
#include "WispForm.h"

WISP_MSG_MAP_BEGIN(CWispRadioBox)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
WISP_MSG_MAP_END(CWispBaseWnd)

CWispRadioBox::CWispRadioBox(void)
{
	m_bIsMultiLine = false;
	m_bMouseDown = false;	
	m_bMouseIn = false;
	m_CtrlType = WISP_CTRL_RADIO_BOX;
}

bool CWispRadioBox::InitWnd()
{
	if(CWispBaseWnd::InitWnd()==false)
		return false;
	m_Style &= ~(WISP_WS_CAPTION|WISP_WS_BT_MAX|WISP_WS_SIZABLE|WISP_WS_BT_MIN|WISP_WS_BT_CLOSE|WISP_WS_BORDER);
	if(m_Style & WISP_RBS_PUSHLIKE)
		m_Style |= WISP_WS_THIN_BORDER;
	m_Style|=WISP_WS_BACK_TRANS;
	if(m_Style & WISP_RBS_MULTILINE)
		m_bIsMultiLine = true;
	if(m_Style & WISP_RBS_PUSHLIKE)
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
		if(m_Style & WISP_RBS_RIGHT)
		{
			m_CheckBoxRect.x = m_WindowRect.x + m_WindowRect.cx - WISP_CHECKBOX_WIDTH-4;
			m_CheckBoxRect.cx = WISP_CHECKBOX_WIDTH;
			m_CheckBoxRect.cy = WISP_CHECKBOX_HEIGH;
			m_CheckBoxRect.y = m_WindowRect.y + (m_WindowRect.cy - WISP_CHECKBOX_HEIGH) / 2;
			if(m_Style & WISP_RBS_TOP)
				m_CheckBoxRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_RBS_BOTTOM)
					m_CheckBoxRect.y = m_WindowRect.y + m_WindowRect.cy - WISP_CHECKBOX_HEIGH;	
			m_TextRect.x = m_WindowRect.x;
			m_TextRect.y = m_WindowRect.y + (m_WindowRect.cy - WISP_CHECKBOX_HEIGH) / 2;
			if(m_Style & WISP_RBS_TOP)
				m_TextRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_RBS_BOTTOM)
					m_TextRect.y = m_WindowRect.y + m_WindowRect.cy - m_WindowDC.m_pFont->m_Height;	
			m_TextRect.cx = m_CheckBoxRect.x - m_TextRect.x - WISP_TEXT_CHECKBOX_DISTANCE;
			if(m_Style & WISP_RBS_MULTILINE)				
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
			if(m_Style & WISP_RBS_TOP)
				m_CheckBoxRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_RBS_BOTTOM)
					m_CheckBoxRect.y = m_WindowRect.y + m_WindowRect.cy - WISP_CHECKBOX_HEIGH;	
			m_TextRect.x = m_CheckBoxRect.x + m_CheckBoxRect.cx + WISP_TEXT_CHECKBOX_DISTANCE;
			m_TextRect.y = m_WindowRect.y + (m_WindowRect.cy - WISP_CHECKBOX_HEIGH) / 2;
			if(m_Style & WISP_RBS_TOP)
				m_TextRect.y = m_WindowRect.y;
			else
				if(m_Style & WISP_RBS_BOTTOM)
					m_TextRect.y = m_WindowRect.y + m_WindowRect.cy - m_WindowDC.m_pFont->m_Height;	
			m_TextRect.cx = m_WindowRect.cx - (m_TextRect.x - m_WindowRect.x);
			if(m_Style & WISP_RBS_MULTILINE)
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

bool CWispRadioBox::OnUpdate(IN WISP_MSG*pMsg)
{
	if( (m_Style&WISP_WS_BACK_TRANS)==0)
		m_pWispBase->m_pCurDrawObj->DrawCtrlClient(&m_WindowDC, &m_WindowRect);
	if((m_Style & WISP_RBS_PUSHLIKE)==0)
	{
		UINT DIBIndex;
		if(IsChecked())
			DIBIndex = (m_bMouseDown && m_bMouseIn)?WISP_SSI_REDIOBOX_SELECTED_DRAK:WISP_SSI_REDIOBOX_SELECTED;
		else
			DIBIndex = (m_bMouseDown && m_bMouseIn)?WISP_SSI_REDIOBOX_UNSELECTED_DRAK:WISP_SSI_REDIOBOX_UNSELECTED;
		m_WindowDC.DrawSystemStandardIcon(m_CheckBoxRect,DIBIndex);
	}
	DrawCaption();
	return false;
}

// 显示文本信息
void CWispRadioBox::DrawCaption(void)
{
	WISP_RECT Rect;
	INT uFormat = WISP_DT_VCENTER;  //缺省的文本显示风格是 横向左对齐,纵向中间对齐.
	Rect.x = m_TextRect.x;
	Rect.y = m_TextRect.y;
	Rect.cx = m_TextRect.cx;
	Rect.cy = m_TextRect.cy;
	if(m_Style & WISP_RBS_PUSHLIKE)
	{
		uFormat |= WISP_DT_CENTER;
		if(m_bMouseDown && m_bMouseIn)
		{
			Rect.x = m_TextRect.x + 1;			
		}
	}
	if(!m_bIsMultiLine)
		uFormat |= WISP_DT_SINGLELINE;
	if(m_Style & WISP_RBS_BOTTOM)
		uFormat |= WISP_DT_BOTTOM;
	if(IsDisabled())
		m_WindowDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRAY]);
	m_WindowDC.DrawString(m_WndText,&Rect,uFormat);
	if(IsDisabled())
		m_WindowDC.RestoreTextColor();
}

bool CWispRadioBox::OnKeyEvent(IN WISP_MSG*pMsg)
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
				Msg.Command.Param1 = IsChecked();
				if(SEND_MSG(&Msg))
				{
					Msg.hWnd=m_OwnerWnd;
					Msg.Msg=WISP_WM_EVENT;
					POST_MSG(&Msg);
				}
			}
		}
		Update();
	}
	return true;
}

bool CWispRadioBox::OnMouseLDown(IN WISP_MSG*pMsg)
{
	m_bMouseDown = true;
	return true;
}

bool CWispRadioBox::OnMouseLUp(IN WISP_MSG*pMsg)
{
	if(m_bMouseIn&&m_bMouseDown)
	{
		if(IsChecked()==false)
			Check(true);
		m_bMouseDown = false;
		return true;
	}
	return false;
}
bool CWispRadioBox::OnMouseLeave(IN WISP_MSG*pMsg)
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
bool CWispRadioBox::OnMouseMove(IN WISP_MSG*pMsg)
{
	m_bMouseIn = true;
	return true;
}

void CWispRadioBox::DrawBorder()
{	
	if(m_Style & WISP_RBS_FLAT)
	{
		if(IsChecked() || (m_bMouseDown && m_bMouseIn))
			m_WindowDC.DrawFrameRect(&m_WindowRect,false,2);
		else
			m_WindowDC.DrawFrameRect(&m_WindowRect,true,2);
	}
	else
	{
		m_pWispBase->m_pCurDrawObj->DrawCtrlBorder(&m_WindowDC, &m_WindowRect,2);
	}
}

void CWispRadioBox::Check(bool bCheck)
{
	if(bCheck)
	{
		if(IsChecked()==false)
		{
			m_Style|=WISP_WS_MARKED;
			UpdateRelation();
			Update();
		}
	}
	else
	{
		if(IsChecked())
		{
			m_Style&=~WISP_WS_MARKED;
			Update();
		}
	}
}

void CWispRadioBox::UpdateRelation()
{
	CWispForm*pForm;
	if(m_ParentWnd->m_CtrlType!=WISP_CTRL_FORM)
		return;
	pForm = (CWispForm*)m_ParentWnd;
	TMap<UINT,CWispBaseWnd*>::IT Iter=pForm->m_FormItemMap.Find(m_CmdID-1);
	while(Iter!=pForm->m_FormItemMap.End())
	{
		if((*Iter)->m_CtrlType!=WISP_CTRL_RADIO_BOX)
			break;
		CWispRadioBox*pRadioBox = (CWispRadioBox*)*Iter;
		if(pRadioBox->IsChecked())
			pRadioBox->Check(false);
		Iter=pForm->m_FormItemMap.Find(pRadioBox->m_CmdID-1);
	}
	Iter=pForm->m_FormItemMap.Find(m_CmdID+1);
	while(Iter!=pForm->m_FormItemMap.End())
	{
		if((*Iter)->m_CtrlType!=WISP_CTRL_RADIO_BOX)
			break;
		CWispRadioBox*pRadioBox = (CWispRadioBox*)*Iter;
		if(pRadioBox->IsChecked())
			pRadioBox->Check(false);
		Iter=pForm->m_FormItemMap.Find(pRadioBox->m_CmdID+1);
	}

}