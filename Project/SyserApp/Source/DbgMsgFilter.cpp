#include "StdAfx.h"
#include "SyserApp.h"
#include "DbgMsgFilter.h"


enum CDbgMsgFilterForm::WISP_FORM_ID
{
	CMD_ID_EDIT_CONTAIN_TEXT = WISP_ID_USER_START,
	CMD_ID_EDIT_NOT_CONTAIN_TEXT,
	CMD_ID_BT_RESET,
	CMD_ID_STATIC_TEXT
};

WISP_FORM_RES_ITEM CDbgMsgFilterForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,400,180},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("Debug Message Filter (Supported ?*)")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,370,50},
		CMD_ID_STATIC_TEXT,
		WISP_WS_NULL,
		WSTR("Display only message contain one or more of these"),
	},
	{
		WISP_CTRL_EDIT,
		{20,30,350,16},
		CMD_ID_EDIT_CONTAIN_TEXT,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,70,370,50},
		CMD_ID_STATIC_TEXT,
		WISP_WS_NULL,
		WSTR("Don't show message contain one or more of these"),
	},
	{
		WISP_CTRL_EDIT,
		{20,90,350,16},
		CMD_ID_EDIT_NOT_CONTAIN_TEXT,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{125,130,60,18},
		CMD_ID_BT_RESET,
		WISP_BS_NORMAL,
		WSTR("Reset"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{215,130,60,18},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CDbgMsgFilterForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_EVENT_MAP_BEGIN(CDbgMsgFilterForm)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_RESET,OnReset)
WISP_MSG_EVENT_MAP_END

WISP_MSG_CMD_MAP_BEGIN(CDbgMsgFilterForm)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END

CDbgMsgFilterForm::CDbgMsgFilterForm()
{
	m_pFormRes = m_FormRes;
}

CDbgMsgFilterForm::~CDbgMsgFilterForm()
{

}

bool CDbgMsgFilterForm::OnFormCreate(IN WISP_MSG*pMsg)
{
	WISP_CHAR wszBuffer[256];
	m_pContainWnd = GetFormItem(CMD_ID_EDIT_CONTAIN_TEXT);
	m_pNotContainWnd = GetFormItem(CMD_ID_EDIT_NOT_CONTAIN_TEXT);

	TStrCpy(m_szContain,"*");
	GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\SDbgMsg\\Inc",m_szContain,sizeof(m_szContain));
	AnsiToUnicode(m_szContain,wszBuffer,256);
	m_pContainWnd->SetWindowText(wszBuffer);

	*m_szNotContain = 0;
	GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\SDbgMsg\\Exc",m_szNotContain,sizeof(m_szNotContain));
	AnsiToUnicode(m_szNotContain,wszBuffer,256);
	m_pNotContainWnd->SetWindowText(wszBuffer);
	return true;
}


bool CDbgMsgFilterForm::OnReset(IN WISP_MSG*pMsg)
{
	m_pContainWnd->SetWindowText(WSTR("*"));
	m_pNotContainWnd->SetWindowText(WSTR(""));
	return true;
}

bool CDbgMsgFilterForm::OnOK(IN WISP_MSG*pMsg)
{
	CWispString*pStr;
	char szContain[256];
	char szNotContain[256];
	if(pMsg->Command.CmdMsg != WISP_CMD_BT_UP)
		return true;
	pStr = &m_pContainWnd->GetWindowText();
	UnicodeToAnsi(*pStr,szContain,256);
	pStr = &m_pNotContainWnd->GetWindowText();
	UnicodeToAnsi(*pStr,szNotContain,256);
	if(TStrICmp(szContain,m_szContain)==0 && TStrICmp(szNotContain,m_szNotContain)==0)
		return true;
	if(TStrICmp(szContain,"*")==0 && *szNotContain==0)
	{
		DelRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\SDbgMsg\\Inc");
		DelRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\SDbgMsg\\Exc");
	}
	else
	{
		SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\SDbgMsg\\Inc",szContain,REG_SZ);
		SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\SDbgMsg\\Exc",szNotContain,REG_SZ);
	}
	theApp.m_SyserInterface.ChangeMsgFilter();
	return true;
}
