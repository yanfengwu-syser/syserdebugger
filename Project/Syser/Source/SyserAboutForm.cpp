#include "StdAfx.h"
#include "SyserAboutForm.h"


enum CAboutForm::WISP_FORM_ID
{
	CMD_ID_VERSION_EDIT = WISP_ID_USER_START,
};

WISP_FORM_RES_ITEM CAboutForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,300,250},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("About Syser")
	},
	{
		WISP_CTRL_STATIC_DIB,
		{10,10,32,32},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Syser.ico:2"
	},
	{
		WISP_CTRL_STATIC_DIB,
		{85,20,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Explorer.ico:1"
	},
	{
		WISP_CTRL_STATIC_URL,
		{110,20,180,20},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("http://www.sysersoft.com"),
	},
	{
		WISP_CTRL_STATIC_DIB,
		{85,50,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Email.ico:1"
	},
	{
		WISP_CTRL_STATIC_URL,
		{110,50,180,20},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("mailto:support@sysersoft.com"),
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,80,270,110},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Vesion Info"),
	},
	{
		WISP_CTRL_STATIC_STRING,
		{20,100,250,90},
		CMD_ID_VERSION_EDIT,
		WISP_WS_NULL,
		NULL,
		NULL,
		WSTR("Syser Version")
	},
	{
		WISP_CTRL_BUTTON,
		{120,200,50,18},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
	},
	{WISP_CTRL_NULL}
};


WISP_MSG_MAP_BEGIN(CAboutForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

bool CAboutForm::OnFormCreate(IN WISP_MSG*pMsg)
{
	WCHAR szBuffer[512],szVer[32],szDate[32];
	CWispBaseWnd*pWnd;
	pWnd = GetFormItem(CMD_ID_VERSION_EDIT);
	if(pWnd)
	{
		TStrCpy(szVer,VER_PRODUCTVERSION_STR);
		TStrCpy(szDate,__DATE__);
		TSPrintf(szBuffer,WSTR("Syser version : %s \nBuild Date    : %s \n\nSyser Development Team\n\nwuyanfeng  ÎâÑÒ·å\nchenjunhao ³Â¿¡ºÀ"),szVer,szDate,VER_PRODUCTBUILD_QFE);
		pWnd->SetWindowText(szBuffer);
	}
	return true;
}