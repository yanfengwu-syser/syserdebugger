#include "StdAfx.h"
#include "CtrlPage1.h"

enum CCtrlPage1::WISP_FORM_ID
{
	CMD_ID_VERSION_EDIT = WISP_ID_USER_START,
	CMD_ID_COMBOBOX_TYPE
};

WISP_FORM_RES_ITEM CCtrlPage1::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,240,150},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Ctrl Page 1")
	},
	{
		WISP_CTRL_STATIC_URL,
		{50,18,150,20},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("http://www.CodeProject.com"),
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{5,50,220,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Vesion Info"),
	},
	{
		WISP_CTRL_STATIC_STRING,
		{15,70,200,16},
		CMD_ID_VERSION_EDIT,
		WISP_WS_NULL,
		NULL,
		NULL,
		WSTR("Wisp Version")
	},
	{
		WISP_CTRL_COMBO_BOX,
		{10,126,135,20},
		CMD_ID_COMBOBOX_TYPE,
		WISP_ES_EDIT_NORMAL,
		NULL,
		NULL,
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CCtrlPage1)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

bool CCtrlPage1::OnFormCreate(IN WISP_MSG*pMsg)
{
	char szBufferA[256];
	WCHAR szBuffer[256];
	CWispBaseWnd*pWnd;
	pWnd = GetFormItem(CMD_ID_VERSION_EDIT);
	if(pWnd)
	{
		TSPrintf(szBufferA,"Syser1.31 Build Date %s",__DATE__);
		TStrCpy(szBuffer,szBufferA);
		pWnd->SetWindowText(szBuffer);
	}
	return true;
}