#include "StdAfx.h"
#include "DebuggerSelectForm.h"
#include "Syser.h"

enum CDebuggerSelectForm::WISP_FORM_ID
{
	CMD_ID_DEBUGGER_LIST = WISP_ID_USER_START,
	CMD_ID_BT_PLUGIN,
	CMD_ID_BT_REFRESH,
};

WISP_FORM_RES_ITEM CDebuggerSelectForm::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,400,200},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Debugger Select ..."),
		"\\SyserIcon\\Syser.ico",
		WSTR("Select Debugger Plugin Module!"),
	},
	{
		WISP_CTRL_LIST,
		{5,5,300,160},
		CMD_ID_DEBUGGER_LIST,
		WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER|WISP_WLS_SELECTED_ALWAYS,
		NULL,
	},
	{
		WISP_CTRL_STATIC_DIB,
		{315,20,64,64},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Syser.ico"
	},
	{
		WISP_CTRL_BUTTON,
		{312,100,70,20},
		CMD_ID_BT_PLUGIN,
		WISP_BS_NORMAL,
		WSTR("Plugin"),
		NULL,
		WSTR("Plug Debugger into Syser")
	},
	{
		WISP_CTRL_BUTTON,
		{312,140,70,20},
		CMD_ID_BT_REFRESH,
		WISP_BS_NORMAL,
		WSTR("Refresh"),
		NULL,
		WSTR("Refresh Debugger Module list")
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CDebuggerSelectForm)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_EVENT_MAP_BEGIN(CDebuggerSelectForm)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_PLUGIN,OnPlugin)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_REFRESH,OnRefresh)
WISP_MSG_EVENT_MAP_END


CDebuggerSelectForm::CDebuggerSelectForm()
{
	m_pFormRes = m_FormRes;
}

CDebuggerSelectForm::~CDebuggerSelectForm()
{

}

void CDebuggerSelectForm::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
		CreateForm();
}

bool CDebuggerSelectForm::OnFormCreate(WISP_MSG*pMsg)
{
	m_pDebuggerList = (CWispList*)GetFormItem(CMD_ID_DEBUGGER_LIST);
	m_pDebuggerList->InsertColumn(WSTR("Module Name"),95);
	m_pDebuggerList->InsertColumn(WSTR("Information"),200);
	OnRefresh(NULL);
	return true;
}

bool CDebuggerSelectForm::OnPlugin(WISP_MSG*pMsg)
{
	HANDLE hItem;
	hItem = m_pDebuggerList->GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;	
#ifdef CODE_OS_WIN
	gpSyser->LoadDebugger(m_pDebuggerList->GetItemCell(hItem)->szText);
#endif
	Destroy();
	return true;
}

bool CDebuggerSelectForm::OnRefresh(WISP_MSG*pMsg)
{
	m_pDebuggerList->ClearChildItem();
#ifdef CODE_OS_WIN
	HANDLE hItem;
	FPGetInfo fGetInfo;
	FPCreateDebugger fCreateDebugger;
	HMODULE hDll;
	FILE_FIND_DATA	FileFindData;
	char szName[MAX_FN_LEN],szDllName[MAX_FN_LEN],szBuffer[MAX_LONG_NAME_LEN];
	WCHAR szModuleName[MAX_NAME_LEN],szInfo[MAX_LONG_NAME_LEN];
	GetModulePath(szName);
	TStrCpy(szDllName,szName);
	TStrCat(szDllName,"*.dll");
	if(gpFileIO->FindFirstFile(szDllName,&FileFindData))
	{
		do
		{
			TStrCpy(szDllName,szName);
			TStrCat(szDllName,FileFindData.FileName);
			if(hDll = LoadLibrary(szDllName))
			{
				(FARPROC&)fGetInfo = GetProcAddress(hDll,"GetInfo");
				(FARPROC&)fCreateDebugger = GetProcAddress(hDll,"CreateDebugger");
				if(fGetInfo && fCreateDebugger)
				{
					AnsiToUnicode(FileFindData.FileName,szModuleName,MAX_NAME_LEN);
					hItem=m_pDebuggerList->InsertItem(szModuleName);
					fGetInfo(szBuffer);
					AnsiToUnicode(szBuffer,szInfo,MAX_LONG_NAME_LEN);
					m_pDebuggerList->SetItemText(hItem,1,szInfo);
					if(gpSyser->m_hDebuggerModule==hDll)
						m_pDebuggerList->SetItemTextColor(hItem,-1,SYS_COLOR[SC_LIGHT_RED]);
				}
				FreeLibrary(hDll);
			}
		}while(gpFileIO->FindNextFile(&FileFindData));
	}
	gpFileIO->FindClose(&FileFindData);
#endif
	return true;
}
