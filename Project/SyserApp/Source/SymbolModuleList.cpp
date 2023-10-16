#include "stdafx.h"
#include "SymbolModuleList.h"
#include "SyserApp.h"

enum CModuleSymbolForm::WISP_FORM_ID
{
	CMD_ID_BUTTON_DELMODULE = WISP_ID_USER_START,
	CMD_ID_BUTTON_ADDMODULE,
	CMD_ID_LIST_SYMBOLMODULE,
};

WISP_MSG_MAP_BEGIN(CModuleSymbolForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CModuleSymbolForm)
//WISP_MSG_CMD_MAP(CMD_ID_UPDATEDOWNLOADSTATE,OnCmdUpdateDownLoadState)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CModuleSymbolForm)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_DELMODULE,OnEventButtonDelModule)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_ADDMODULE,OnEventButtonAddModule)
WISP_MSG_EVENT_MAP_END

WISP_FORM_RES_ITEM CModuleSymbolForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,500,400},
		WISP_ID_NULL,
		WISP_WS_NULL,
	},
	{
		WISP_CTRL_LIST,
		{10,10,390,220},
		CMD_ID_LIST_SYMBOLMODULE,
		WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER|WISP_WLS_SELECTED_ALWAYS,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,20,100,20},
		CMD_ID_BUTTON_ADDMODULE,
		WISP_BS_NORMAL,
		WSTR("Add"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,50,100,20},
		CMD_ID_BUTTON_DELMODULE,
		WISP_BS_NORMAL,
		WSTR("Delete"),
		NULL,
	},
	{WISP_CTRL_NULL}
};
CModuleSymbolForm::CModuleSymbolForm()
{
	m_pFormRes = m_FormRes;
}
CModuleSymbolForm::~CModuleSymbolForm()
{
}
bool CModuleSymbolForm::OnFormCreate(IN WISP_MSG* pMsg)
{
	m_SymModuleListWnd = (CWispList*)GetFormItem(CMD_ID_LIST_SYMBOLMODULE);
	m_DelModuleButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_DELMODULE);
	m_AddModuleButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_ADDMODULE);
	m_SymModuleListWnd->InsertColumn(WSTR("SDS File List"),250);
	return true;
}
bool CModuleSymbolForm::InsertSymbolModule(const char* SymModuleFullName)
{
	HANDLE hItem;
	char FileTitleName[MAX_FN_LEN]={0};
	SYMMODULEMAP::IT FindIT;
	FindIT = m_SymModuleMap.InsertUnique(SymModuleFullName);
	if(FindIT==m_SymModuleMap.End())
		return false;
	TGetFileTitle(SymModuleFullName,FileTitleName);
	hItem = m_SymModuleListWnd->InsertItemA(FileTitleName);
	*FindIT=hItem;
	return true;
}
bool CModuleSymbolForm::RemoveSymbolModule(const char* SymModuleFullName)
{
	SYMMODULEMAP::IT FindIT;
	FindIT = m_SymModuleMap.Find(SymModuleFullName);
	if(FindIT!=m_SymModuleMap.End())
	{
		m_SymModuleListWnd->RemoveItem(*FindIT);
		m_SymModuleMap.Remove(FindIT);
		return true;
	}
	return false;
}
bool CModuleSymbolForm::OnEventButtonAddModule(IN WISP_MSG* pMsg)
{
	theApp.m_MainFrame.OnMenuEventLoadSymbol(pMsg);
	return true;
}
bool CModuleSymbolForm::OnEventButtonDelModule(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	bool bFind = false;
	SYMMODULEMAP::IT BeginIt,EndIt;
	hItem = m_SymModuleListWnd->GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return false;
	BeginIt = m_SymModuleMap.Begin();
	EndIt = m_SymModuleMap.End();
	for(;BeginIt!=EndIt;BeginIt++)
	{
		if(*BeginIt==hItem)
		{
			bFind=true;
			break;
		}
	}
	if(bFind==false)
		return false;
	theApp.m_SyserInterface.UnloadSymbolModuleFile(BeginIt.Key());
	return true;
}