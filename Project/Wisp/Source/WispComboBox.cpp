#include "StdAfx.h"
#include "WispComboBox.h"
#include "WispDIBLib.h"

enum WISP_COMBO_BOX
{
	WISP_ID_COMBO_BT = WISP_ID_DEVELOP_START,
	WISP_ID_COMBO_LIST,
};

WISP_MSG_MAP_BEGIN(CWispComboBox)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate);
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy);
WISP_MSG_MAP_END(CWispEdit)

WISP_MSG_EVENT_MAP_BEGIN(CWispComboBox)
	WISP_MSG_EVENT_MAP(WISP_ID_COMBO_BT,OnComboBT);
	WISP_MSG_EVENT_MAP(WISP_ID_COMBO_LIST,OnComboListEvent);
WISP_MSG_EVENT_MAP_END


WISP_MSG_CMD_MAP_BEGIN(CWispComboBox)
	WISP_MSG_CMD_MAP(WISP_ID_COMBO_LIST,OnComboListCmd);
WISP_MSG_CMD_MAP_END


CWispComboBox::CWispComboBox()
{
	m_CtrlType = WISP_CTRL_COMBO_BOX;
	m_CurSelIndex = -1;
}

bool CWispComboBox::OnCreate(IN WISP_MSG*pMsg)
{
	WISP_SIZE BTSize;
	CWispDIBList*pDIBList=WispDIBList("\\Skin\\Default\\VertInc.bmp",16,16);
	BTSize.cx = pDIBList->m_DIBList->Width();
	BTSize.cy = pDIBList->m_DIBList->Height();
	m_ComboButton.CreateEx(pDIBList,m_ClientRect.cx-BTSize.cx,0,this,WISP_ID_COMBO_BT);
	m_ComboList.Create(NULL,0,0,m_WindowRect.cx,BTSize.cy,NULL,WISP_ID_COMBO_LIST,WISP_WS_THIN_BORDER|WISP_WLS_FOLLOW_SEL,WISP_SH_HIDDEN);
	m_ComboList.SetOwner(this);
	m_ComboList.InsertColumn(NULL,-1);
	return true;
}

bool CWispComboBox::OnDestroy(IN WISP_MSG*pMsg)
{
	m_ComboList.Destroy();
	return true;
}

bool CWispComboBox::OnComboBT(IN WISP_MSG*pMsg)
{
	if(m_ComboList.IsVisible())
	{
		m_ComboList.Show(WISP_SH_HIDDEN);
	}
	else
	{
		m_ComboList.MoveToScreen(m_ScrWindowRect.x,m_ScrWindowRect.y+m_ScrWindowRect.cy,false);
		m_ComboList.Resize(m_ComboList.m_WindowRect.cx,m_ComboList.GetItemCount()*m_ComboList.m_ButtonSize.cy+m_BorderSize*2,false);
		m_ComboList.Show();
		m_ComboList.Top();
		m_ComboList.Focus();
	}
	return true;
}

bool CWispComboBox::OnComboListEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_CTRL_CLICK)
	{
		HANDLE hItem = pMsg->Command.Param2;
		m_CurSelIndex = m_ComboList.GetItemIndex(hItem);
		SetWindowText(m_ComboList.GetItemText(hItem));
		m_ComboList.Show(WISP_SH_HIDDEN);
		Focus();
		SendCmdMsg(WISP_CMD_COMBOX_SELCHANGE,m_CurSelIndex,hItem);
	}
	return true;
}

bool CWispComboBox::OnComboListCmd(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_CTRL_LOST_FOCUS && pMsg->Command.Param2 != &m_ComboButton)
	{
		m_ComboList.Show(WISP_SH_HIDDEN);
	}
	return true;
}

void CWispComboBox::SelectItem(int Index)
{
	HANDLE hItem = m_ComboList.GetItem(Index);
	if(hItem)
	{
		SetWindowText(m_ComboList.GetItemText(hItem));
		m_CurSelIndex = Index;
		Update();
	}
}

int	CWispComboBox::GetCurSelItem()
{
	return m_CurSelIndex;
}
