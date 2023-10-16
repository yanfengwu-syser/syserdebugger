#include "StdAfx.h"
#include "RegisterForm.h"

enum CRegisterForm::WISP_FORM_ID
{
	CMD_ID_EDIT_NAME = WISP_ID_USER_START,
	CMD_ID_EDIT_SN,
	CMD_ID_STATIC_TEXT
};

WISP_FORM_RES_ITEM CRegisterForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,260,180},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("Please Input Register Informattion")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,230,50},
		CMD_ID_STATIC_TEXT,
		WISP_WS_NULL,
		WSTR("User/Company  Name"),
	},
	{
		WISP_CTRL_EDIT,
		{20,30,200,16},
		CMD_ID_EDIT_NAME,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,70,230,50},
		CMD_ID_STATIC_TEXT,
		WISP_WS_NULL,
		WSTR("SN"),
	},
	{
		WISP_CTRL_EDIT,
		{20,90,200,16},
		CMD_ID_EDIT_SN,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{110,130,40,16},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CRegisterForm)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CRegisterForm)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END

CRegisterForm::CRegisterForm()
{
	m_pFormRes = m_FormRes;
}

CRegisterForm::~CRegisterForm()
{
}

bool CRegisterForm::OnOK(IN WISP_MSG*pMsg)
{
	char szBuffer[256];
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		m_StrName = GetFormItem(CMD_ID_EDIT_NAME)->GetWindowText();
		m_StrSN = GetFormItem(CMD_ID_EDIT_SN)->GetWindowText();
		m_StrSN.MakeUpper();
		TStrCpyLimit(szBuffer,(PCWSTR)m_StrSN,sizeof(szBuffer));
		if(IsSerialNumber(szBuffer)==false)
		{
			MsgBox(WSTR("Invalid SN !\nPlease input again"),WSTR("Error"));
			return false;
		}
	}
	return true;
}

