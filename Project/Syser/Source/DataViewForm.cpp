#include "StdAfx.h"
#include "DataViewForm.h"
#include "Syser.h"

enum CDataViewForm::WISP_FORM_ID
{
	CMD_ID_EDIT_TEXT = WISP_ID_USER_START,
	CMD_ID_STATIC_GROUP,
	CMD_ID_DATA_VIEW,
	CMD_ID_GOTO
};

WISP_FORM_RES_ITEM CDataViewForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,500,300},
		WISP_ID_NULL,
		WISP_WFS_DIALOG | WISP_WS_BT_MIN | WISP_WS_SIZABLE,
		WSTR("Data View")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,470,40},
		CMD_ID_STATIC_GROUP,
		WISP_WS_NULL,
		WSTR("Address"),
	},
	{
		WISP_CTRL_EDIT,
		{20,25,400,16},
		CMD_ID_EDIT_TEXT,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,25,40,16},
		CMD_ID_GOTO,
		WISP_BS_NORMAL,
		WSTR("Goto"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CDataViewForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_SIZE ,OnSize)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CDataViewForm)
	WISP_MSG_CMD_MAP(CMD_ID_EDIT_TEXT,OnCmdAddressEdit)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CDataViewForm)
	WISP_MSG_EVENT_MAP(CMD_ID_GOTO,OnGoto)
WISP_MSG_EVENT_MAP_END

CDataViewForm::CDataViewForm()
{
	m_pFormRes = m_FormRes;
}

CDataViewForm::~CDataViewForm()
{
}

bool CDataViewForm::OnFormCreate(WISP_MSG*pMsg)
{
	if(m_Style & WISP_WS_CAPTION)
		AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,89));
	int y;
	m_pAddrEdit = (CWispEdit*) GetFormItem(CMD_ID_EDIT_TEXT);
	m_pGroupCtrl = (CWispStaticGroup*) GetFormItem(CMD_ID_STATIC_GROUP);
	m_pButton = (CWispButton*) GetFormItem(CMD_ID_GOTO);
	y = m_pAddrEdit->m_ScrWindowRect.x-m_ScrWindowRect.x+30;
	m_DataView.Create(NULL,10,y,m_pGroupCtrl->m_WindowRect.cx,m_ClientRect.cy - y - 10,this,CMD_ID_DATA_VIEW,WISP_WS_NULL);
	OnSize(NULL);
	return true;
}

bool CDataViewForm::OnClose(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

bool CDataViewForm::OnSize(WISP_MSG*pMsg)
{
	m_pGroupCtrl->Resize(m_ClientRect.cx-20,m_pGroupCtrl->m_WindowRect.cy);
	m_pAddrEdit->Resize(m_pGroupCtrl->m_WindowRect.cx - m_pButton->m_WindowRect.cx - 30,m_pAddrEdit->m_WindowRect.cy);
	m_pButton->MoveToWindow(m_pGroupCtrl->m_ScrWindowRect.x-m_ScrWindowRect.x+m_pGroupCtrl->m_WindowRect.cx-50,m_pButton->m_ScrWindowRect.y - m_ScrWindowRect.y);
	m_DataView.Resize(m_pGroupCtrl->m_WindowRect.cx,m_ClientRect.cy - m_pAddrEdit->m_ScrWindowRect.x+m_ScrWindowRect.x-40);
	return true;
}

bool CDataViewForm::OnGoto(WISP_MSG*pMsg)
{
	UpdateContext();
	return false;
}

bool CDataViewForm::OnCmdAddressEdit(WISP_MSG*pMsg)
{
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_EN_INPUT_KEY_DOWN:
		switch(pMsg->Command.Param1)
		{
		case WISP_VK_RETURN:
			UpdateContext();
			break;
		}
		break;
	}
	return true;
}

void CDataViewForm::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		CreateForm();
		Center();
	}
}

void  CDataViewForm::UpdateContext()
{
	ULPOS Address;
	if(IsVisible()==false)
		return;
	if(CALCEXP(m_pAddrEdit->GetWindowText(),&Address))
	{
		SetWindowText(m_pAddrEdit->GetWindowText());
		m_DataView.ViewAddress(Address);
	}
}
