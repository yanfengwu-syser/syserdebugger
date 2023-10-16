#include "StdAfx.h"
#include "SyserOptionApp.h"
#include "ExportModulePage.h"


enum CExportModulePage::WISP_FORM_ID
{
	CMD_ID_EXPMOD_FILE_LIST = WISP_ID_USER_START,
	CMD_ID_STATIC_GROUP,
	CMD_ID_EXPMOD_ADD,
	CMD_ID_EXPMOD_REMOVE,
	CMD_ID_EXPMOD_APPLY,
	CMD_ID_EXPMOD_RELOAD,
	CMD_ID_EXPMOD_DEFAULT,
};

WISP_FORM_RES_ITEM CExportModulePage::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,540,400},
		WISP_ID_NULL,
		WISP_WS_NULL,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,530,300},
		CMD_ID_STATIC_GROUP,
		WISP_WS_NULL,
		WSTR("Load their export symbols after syser initialization."),
	},
	{
		WISP_CTRL_LIST,
		{20,30,400,260},
		CMD_ID_EXPMOD_FILE_LIST,
		WISP_WS_THIN_BORDER,
	},
	{
		WISP_CTRL_BUTTON,
		{430,40,100,20},
		CMD_ID_EXPMOD_ADD,
		WISP_BS_NORMAL,
		WSTR("Add"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,80,100,20},
		CMD_ID_EXPMOD_REMOVE,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Remove"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,340,100,20},
		CMD_ID_EXPMOD_APPLY,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Save"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{10,340,100,20},
		CMD_ID_EXPMOD_RELOAD,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Reload"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{120,340,100,20},
		CMD_ID_EXPMOD_DEFAULT,
		WISP_BS_NORMAL,
		WSTR("Default"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CExportModulePage)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnResize)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CExportModulePage)
	WISP_MSG_CMD_MAP(CMD_ID_EXPMOD_FILE_LIST,OnFileListCommand)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CExportModulePage)
	WISP_MSG_EVENT_MAP(CMD_ID_EXPMOD_ADD,OnButtonAdd)
	WISP_MSG_EVENT_MAP(CMD_ID_EXPMOD_REMOVE,OnButtonRemove)
	WISP_MSG_EVENT_MAP(CMD_ID_EXPMOD_APPLY,OnButtonSave)
	WISP_MSG_EVENT_MAP(CMD_ID_EXPMOD_RELOAD,OnButtonReload)
	WISP_MSG_EVENT_MAP(CMD_ID_EXPMOD_DEFAULT,OnButtonDefault)
WISP_MSG_EVENT_MAP_END

CExportModulePage::CExportModulePage()
{
	m_pFormRes = m_FormRes;
	GetSystemDirectory(m_ExpModFileName,MAX_FN_LEN);
	TStrCat(m_ExpModFileName,"\\drivers\\ModExSym.lst");
	GetWindowsDirectoryW(m_szSystemRootDir,MAX_FN_LEN);
}

bool CExportModulePage::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pGroup = (CWispStaticGroup*) GetFormItem(CMD_ID_STATIC_GROUP);
	m_pFileList = (CWispList*) GetFormItem(CMD_ID_EXPMOD_FILE_LIST);
	m_pSaveBT = (CWispButton*) GetFormItem(CMD_ID_EXPMOD_APPLY);
	m_pDefaultBT = (CWispButton*) GetFormItem(CMD_ID_EXPMOD_DEFAULT);
	m_pReloadBT = (CWispButton*) GetFormItem(CMD_ID_EXPMOD_RELOAD);
	m_pAddBT = (CWispButton*) GetFormItem(CMD_ID_EXPMOD_ADD);
	m_pRemoveBT = (CWispButton*) GetFormItem(CMD_ID_EXPMOD_REMOVE);
	m_pFileList->InsertColumn(NULL,0,WISP_WLCS_EDITABLE);
	LoadExpModFileList();
	return true;
}

bool CExportModulePage::OnResize(IN WISP_MSG*pMsg)
{
	m_pGroup->Resize(m_ClientRect.cx-20,m_ClientRect.cy-50);
	m_pFileList->Resize(m_pGroup->m_WindowRect.cx-130,m_pGroup->m_WindowRect.cy-30);
	m_pRemoveBT->MoveToWindow(m_pFileList->m_WindowRect.cx+30,m_pRemoveBT->m_ScrWindowRect.y - m_ScrWindowRect.y);
	m_pAddBT->MoveToWindow(m_pFileList->m_WindowRect.cx+30,m_pAddBT->m_ScrWindowRect.y - m_ScrWindowRect.y);
	m_pReloadBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x-m_ScrWindowRect.x,m_pGroup->m_ScrWindowRect.y-m_ScrWindowRect.y+m_pGroup->m_WindowRect.cy+10);
	m_pDefaultBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x-m_ScrWindowRect.x+m_pReloadBT->m_WindowRect.cx+10,m_pGroup->m_ScrWindowRect.y-m_ScrWindowRect.y+m_pGroup->m_WindowRect.cy+10);
	m_pSaveBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x + m_pGroup->m_ScrWindowRect.cx - m_pSaveBT->m_WindowRect.cx - m_ScrWindowRect.x,m_pReloadBT->m_ScrWindowRect.y-m_ScrWindowRect.y);
	return true;
}

bool CExportModulePage::OnFileListCommand(IN WISP_MSG*pMsg)
{
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_ITEM_SELECTED:
		m_pRemoveBT->EnableWindow(true);
		break;
	case WISP_CMD_ITEM_UNSELECTED:
		m_pRemoveBT->EnableWindow(false);
		break;
	case WISP_CMD_ITEM_CHANGED:
		m_pSaveBT->EnableWindow(TRUE);
		m_pReloadBT->EnableWindow(TRUE);
		break;
	}
	return true;
}


bool ConvertFileNameByMacro(WCHAR*szFileName,const WCHAR*szMacro,const WCHAR*szMacroStr)
{
	int Len;
	WCHAR szBuffer[MAX_FN_LEN];
	Len = TStrLen(szMacro);
	if(TStrNICmp(szFileName,szMacro,Len)==0)
	{
		TStrCpy(szBuffer,&szFileName[Len]);
		TStrCpy(szFileName,szMacroStr);
		TStrCat(szFileName,szBuffer);
		return true;
	}
	return false;
}

bool CExportModulePage::IsListItem(PCWSTR szName)
{
	HANDLE hItem = m_pFileList->GetFirstItem();
	while(hItem)
	{
		if(m_pFileList->GetItemText(hItem)==szName)
			return true;
		hItem = m_pFileList->GetNextItem(hItem);
	}
	return false;
}

bool CExportModulePage::OnButtonAdd(IN WISP_MSG*pMsg)
{
	char szBuffer[MAX_FN_LEN],szFileName[MAX_FN_LEN];
	WCHAR wszFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "PE Module(exe;scr;dll;sys)\0*.exe;*.scr;*.dll;*.sys\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	GetSystemDirectory(szBuffer,MAX_FN_LEN);
	OpenFileName.lpstrInitialDir = szBuffer;
	*szFileName = 0;
	if(GetOpenFileName(&OpenFileName)==false)
		return true;
	AnsiToUnicode(szFileName,wszFileName,MAX_FN_LEN);
	ConvertFileNameByMacro(wszFileName,m_szSystemRootDir,WSTR("\\SystemRoot"));
	if(IsListItem(wszFileName))
		return true;
	m_pFileList->InsertItem(wszFileName);
	m_pFileList->Update();
	m_pSaveBT->EnableWindow(TRUE);
	m_pReloadBT->EnableWindow(TRUE);
	return true;
}

bool CExportModulePage::OnButtonRemove(IN WISP_MSG*pMsg)
{
	HANDLE hItem = m_pFileList->GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem)
	{
		m_pFileList->RemoveItem(hItem);
		m_pFileList->Update();
		m_pRemoveBT->EnableWindow(false);
		m_pReloadBT->EnableWindow(TRUE);
		m_pSaveBT->EnableWindow(TRUE);
	}
	return true;
}

bool CExportModulePage::OnButtonSave(IN WISP_MSG*pMsg)
{
	if(SaveExpModFileList()==false)
		return true;
	m_pReloadBT->EnableWindow(FALSE);
	m_pSaveBT->EnableWindow(FALSE);
	Update();
	return true;
}

bool CExportModulePage::OnButtonReload(IN WISP_MSG*pMsg)
{
	if(LoadExpModFileList()==false)
		return true;
	m_pReloadBT->EnableWindow(FALSE);
	m_pSaveBT->EnableWindow(FALSE);
	Update();
	return true;
}

bool CExportModulePage::OnButtonDefault(IN WISP_MSG*pMsg)
{
	gpFileIO->WriteToFile(m_ExpModFileName,DefaultPEExportList,TStrLen(DefaultPEExportList));
	OnButtonReload(pMsg);
	return true;
}

bool CExportModulePage::LoadExpModFileList()
{
	CTXTFile	TXTFile;
	if(TXTFile.Open(m_ExpModFileName)==false)
		return false;
	m_pFileList->ClearChildItem();
	for(TTXTStrList::IT Iter = TXTFile.m_StrList.Begin();Iter!=TXTFile.m_StrList.End();Iter++)
	{
		m_pFileList->InsertItemA(*Iter);
	}
	TXTFile.Close();
	return true;
}

bool CExportModulePage::SaveExpModFileList()
{
	CHAR szBuffer[MAX_FN_LEN+2];
	CImageFileStream File;
	HANDLE hItem = m_pFileList->GetFirstItem();
	if(hItem==NULL)
	{
		gpFileIO->DeleteFile(m_ExpModFileName);
		return true;
	}
	if(File.Create(m_ExpModFileName)==false)
		return false;
	while(hItem)
	{
		UnicodeToAnsi(m_pFileList->GetItemText(hItem),szBuffer,MAX_FN_LEN);
		TStrCat(szBuffer,"\r\n");
		File.Puts(szBuffer,TStrLen(szBuffer));
		hItem = m_pFileList->GetNextItem(hItem);
	}
	File.Close();
	return true;
}
