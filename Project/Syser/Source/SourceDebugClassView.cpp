#include "StdAfx.h"
#include "SourceDebugClassView.h"

WISP_MENU_RES_ITEM SourceDebugClassViewMenu[]=
{
	{WSTR("Find"),EVENT_ID_SOURCEDEBUGCLASSVIEW_FIND,15*16+5},
	WISP_MENU_RES_END
};


WISP_MSG_MAP_BEGIN(CSourceDebugClassViewList) 
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CSourceDebugClassViewList)
	WISP_MSG_EVENT_MAP(EVENT_ID_SOURCEDEBUGCLASSVIEW_FIND,OnFindDlg);
WISP_MSG_EVENT_MAP_END

bool CSourceDebugClassViewList::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.bKeyDown==false)
	{
		if(pMsg->KeyEvent.KeyType == WISP_VK_F3)
			return OnFindDlg(pMsg);
		if(pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
			m_PopupMenu.Popup();
	}
	return true;
}
bool CSourceDebugClassViewList::OnFindDlg(IN WISP_MSG* pMsg)
{
	m_FindDlg.CreateForm(NULL,WISP_SH_MODAL);
	m_FindDlg.SetContextList(this);
	return true;
}
bool CSourceDebugClassViewList::OnCreate(IN WISP_MSG* pMsg)
{
	m_PopupMenu.CreatePopupMenu(SourceDebugClassViewMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	return true;
}
void CSourceDebugClassViewList::FindItemByName(WCHAR* Name)
{
	CWispString* pText;
	WCHAR* pTextName;
	if(Name==NULL)
		return;
	if(m_CurrentFindItem==NULL)
		m_CurrentFindItem = GetItem(0);
	if(m_CurrentFindItem==NULL)
		return;
	for(;m_CurrentFindItem;)
	{
		pText = &GetItemText(m_CurrentFindItem);
		if(pText==NULL)
			continue;
		pTextName = *pText;
		if(TStrStr(pTextName,Name))
		{
			EnableVisible(m_CurrentFindItem,0);
			SelectItem(m_CurrentFindItem);
			m_CurrentFindItem = GetNextItem(m_CurrentFindItem);
			break;
		}
		m_CurrentFindItem = GetNextItem(m_CurrentFindItem);
	}
	return;
}
enum CClassViewFindForm::WISP_FORM_ID
{
	CMD_ID_BUTTON_FIND = WISP_ID_USER_START,
	CMD_ID_BUTTON_CLOSE,
	CMD_ID_EDIT_FINDTEXT,
};
WISP_FORM_RES_ITEM CClassViewFindForm::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,320,120},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Find"),
		"\\SyserIcon\\Plugin.ico",
		WSTR("Find"),
	},
	{
		WISP_CTRL_STATIC_STRING,
		{10,18,70,20},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Find what:  "),
		NULL,
		NULL
	},
	{
		WISP_CTRL_EDIT,
		{80,15,220,20},
		CMD_ID_EDIT_FINDTEXT,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{54,50,78,21},
		CMD_ID_BUTTON_FIND,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Find Next"),

	},
	{
		WISP_CTRL_BUTTON,
		{186,50,78,21},
		WISP_ID_CANCEL,
		WISP_BS_NORMAL,
		WSTR("Close"),
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CClassViewFindForm)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CClassViewFindForm)
WISP_MSG_CMD_MAP(CMD_ID_EDIT_FINDTEXT,OnFindTextCmd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CClassViewFindForm)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_FIND,OnFindButtonEvent)
WISP_MSG_EVENT_MAP_END

CClassViewFindForm::CClassViewFindForm()
{
	m_pFormRes = m_FormRes;
}
CClassViewFindForm::~CClassViewFindForm()
{

}
bool CClassViewFindForm::OnFormCreate(IN WISP_MSG* pMsg)
{
	m_FindButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_FIND);
	m_CloseButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_CLOSE);
	m_FindEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_FINDTEXT);
	return true;
}
bool CClassViewFindForm::OnFindTextCmd(IN WISP_MSG* pMsg)
{
	CWispString* FindText;
	switch(pMsg->Command.CmdMsg) {
	case WISP_CMD_EN_INPUT_KEY_DOWN:
		if(pMsg->Command.Param1==WISP_VK_RETURN)
		{
			m_FindButton->Focus();
			return OnFindButtonEvent(NULL);
		}
		break;
	case WISP_CMD_EN_INPUT_KEY_UP:
		if(pMsg->Command.Param1==WISP_VK_RETURN)
			return false;
		break;
	case WISP_CMD_EN_CHANGED:
		FindText = &m_FindEdit->GetWindowText();
		m_FindButton->EnableWindow(FindText->IsEmpty()==false);
		m_FindButton->Update();
		break;
	}
	return true;
}
bool CClassViewFindForm::OnFindButtonEvent(IN WISP_MSG* pMsg)
{
	WCHAR* pFindText;
	if(m_pContextList==NULL)
		return false;
	pFindText = m_FindEdit->GetWindowText();
	m_pContextList->FindItemByName(pFindText);
	return true;
}
void CClassViewFindForm::SetContextList(CSourceDebugClassViewList* pContextList)
{
	m_pContextList = pContextList;
	return;
}
bool CClassViewFindForm::OnDestroy(IN WISP_MSG* pMsg)
{
	if(m_pContextList)
		m_pContextList->Focus();
	return true;
}