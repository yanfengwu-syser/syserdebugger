#include "StdAfx.h"
#include "Syser.h"
#include "PluginListForm.h"

enum CPluginListForm::WISP_FORM_ID
{
	CMD_ID_PLUGIN_LIST = WISP_ID_USER_START,
};

WISP_FORM_RES_ITEM CPluginListForm::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,400,200},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Plugin List"),
		"\\SyserIcon\\Plugin.ico",
		WSTR("Syser Plugin List !"),
	},
	{
		WISP_CTRL_LIST,
		{5,5,300,160},
		CMD_ID_PLUGIN_LIST,
		WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER,
		NULL,
	},
	{
		WISP_CTRL_STATIC_DIB,
		{315,30,64,64},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Plugin.ico"
	},
	{
		WISP_CTRL_BUTTON,
		{312,120,70,20},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
	},
	{WISP_CTRL_NULL}
};

CPluginListForm::CPluginListForm()
{
	m_pFormRes = m_FormRes;
}

CPluginListForm::~CPluginListForm()
{
}

WISP_MSG_MAP_BEGIN(CPluginListForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

void CPluginListForm::Popup()
{
	if(IsWindow())
	{
		UpdateContext();
		Show();
	}
	else
		CreateForm();
}

void CPluginListForm::UpdateContext()
{
	HANDLE hItem;
	for(CPluginMap::IT It=gpSyser->m_PluginMap.Begin();It!=gpSyser->m_PluginMap.End();It++)
	{
		hItem=m_pPluginList->InsertItem((PCWSTR)It.Key());
		m_pPluginList->SetItemText(hItem,1,It->PluginInfo);
	}
}

bool CPluginListForm::OnFormCreate(WISP_MSG*pMsg)
{
	m_pPluginList = (CWispList*)GetFormItem(CMD_ID_PLUGIN_LIST);
	m_pPluginList->InsertColumn(WSTR("Module Name"),100);
	m_pPluginList->InsertColumn(WSTR("Information"),190);
	UpdateContext();
	return true;
}
