#include "StdAfx.h"
#include "SDSFilePage.h"
#include "SyserOptionApp.h"


enum CSDSFilePage::WISP_FORM_ID
{
	CMD_ID_SDS_FILE_LIST = WISP_ID_USER_START,
	CMD_ID_STATIC_GROUP,
	CMD_ID_SDS_ADD,
	CMD_ID_SDS_REMOVE,
	CMD_ID_SDS_APPLY,
	CMD_ID_SDS_RELOAD,
	CMD_ID_SDS_DEFAULT,
};

WISP_FORM_RES_ITEM CSDSFilePage::m_FormRes[]=
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
		WSTR("Load these symbol files after syser initialization"),
	},
	{
		WISP_CTRL_LIST,
		{20,30,400,260},
		CMD_ID_SDS_FILE_LIST,
		WISP_WS_THIN_BORDER,
	},
	{
		WISP_CTRL_BUTTON,
		{430,40,100,20},
		CMD_ID_SDS_ADD,
		WISP_BS_NORMAL,
		WSTR("Add"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,80,100,20},
		CMD_ID_SDS_REMOVE,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Remove"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,340,100,20},
		CMD_ID_SDS_APPLY,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Save"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{10,340,100,20},
		CMD_ID_SDS_RELOAD,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Reload"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CSDSFilePage)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnResize)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CSDSFilePage)
	WISP_MSG_CMD_MAP(CMD_ID_SDS_FILE_LIST,OnFileListCommand)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CSDSFilePage)
	WISP_MSG_EVENT_MAP(CMD_ID_SDS_ADD,OnButtonAdd)
	WISP_MSG_EVENT_MAP(CMD_ID_SDS_REMOVE,OnButtonRemove)
	WISP_MSG_EVENT_MAP(CMD_ID_SDS_APPLY,OnButtonSave)
	WISP_MSG_EVENT_MAP(CMD_ID_SDS_RELOAD,OnButtonReload)
WISP_MSG_EVENT_MAP_END

CSDSFilePage::CSDSFilePage()
{
	m_pFormRes = m_FormRes;
	GetSystemDirectory(m_SDSFileName,MAX_FN_LEN);
	TStrCat(m_SDSFileName,"\\drivers\\SDSInit.lst");
}

bool CSDSFilePage::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pGroup = (CWispStaticGroup*) GetFormItem(CMD_ID_STATIC_GROUP);
	m_pFileList = (CWispList*) GetFormItem(CMD_ID_SDS_FILE_LIST);
	m_pSaveBT = (CWispButton*) GetFormItem(CMD_ID_SDS_APPLY);
	m_pReloadBT = (CWispButton*) GetFormItem(CMD_ID_SDS_RELOAD);
	m_pAddBT = (CWispButton*) GetFormItem(CMD_ID_SDS_ADD);
	m_pRemoveBT = (CWispButton*) GetFormItem(CMD_ID_SDS_REMOVE);
	m_pFileList->InsertColumn(NULL,0,WISP_WLCS_EDITABLE);
	LoadSDSFileList();
	return true;
}

bool CSDSFilePage::OnResize(IN WISP_MSG*pMsg)
{
	m_pGroup->Resize(m_ClientRect.cx-20,m_ClientRect.cy-50);
	m_pFileList->Resize(m_pGroup->m_WindowRect.cx-130,m_pGroup->m_WindowRect.cy-30);
	m_pRemoveBT->MoveToWindow(m_pFileList->m_WindowRect.cx+30,m_pRemoveBT->m_ScrWindowRect.y - m_ScrWindowRect.y);
	m_pAddBT->MoveToWindow(m_pFileList->m_WindowRect.cx+30,m_pAddBT->m_ScrWindowRect.y - m_ScrWindowRect.y);
	m_pReloadBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x-m_ScrWindowRect.x,m_pGroup->m_ScrWindowRect.y-m_ScrWindowRect.y+m_pGroup->m_WindowRect.cy+10);
	m_pSaveBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x + m_pGroup->m_ScrWindowRect.cx - m_pSaveBT->m_WindowRect.cx - m_ScrWindowRect.x,m_pReloadBT->m_ScrWindowRect.y-m_ScrWindowRect.y);
	return true;
}

bool CSDSFilePage::OnFileListCommand(IN WISP_MSG*pMsg)
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

bool CSDSFilePage::OnButtonAdd(IN WISP_MSG*pMsg)
{
	CHAR szFileName[MAX_FN_LEN],szDir[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	GetModulePath(szDir);
	TStrCat(szDir,"Symbols");
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "SDS File(*.sds)\0*.sds\0All Files(*.*)\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	OpenFileName.lpstrInitialDir = szDir;
	*szFileName = 0;
	theApp.LockTimer();
	if(GetOpenFileName(&OpenFileName)==false)
	{
		theApp.UnlockTimer();
		return true;
	}
	theApp.UnlockTimer();
	m_pFileList->InsertItemA(szFileName);
	m_pFileList->Update();
	m_pSaveBT->EnableWindow(TRUE);
	m_pReloadBT->EnableWindow(TRUE);
	return true;
}

bool CSDSFilePage::OnButtonRemove(IN WISP_MSG*pMsg)
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

bool CSDSFilePage::OnButtonSave(IN WISP_MSG*pMsg)
{
	if(SaveSDSFileList()==false)
		return true;
	m_pReloadBT->EnableWindow(FALSE);
	m_pSaveBT->EnableWindow(FALSE);
	Update();
	return true;
}

bool CSDSFilePage::OnButtonReload(IN WISP_MSG*pMsg)
{
	if(LoadSDSFileList()==false)
		return true;
	m_pReloadBT->EnableWindow(FALSE);
	m_pSaveBT->EnableWindow(FALSE);
	Update();
	return true;
}

bool CSDSFilePage::LoadSDSFileList()
{
	CTXTFile	TXTFile;
	if(TXTFile.Open(m_SDSFileName)==false)
		return false;
	m_pFileList->ClearChildItem();
	for(TTXTStrList::IT Iter = TXTFile.m_StrList.Begin();Iter!=TXTFile.m_StrList.End();Iter++)
	{
		m_pFileList->InsertItemA(*Iter);
	}
	TXTFile.Close();
	return true;
}

bool CSDSFilePage::SaveSDSFileList()
{
	CHAR szBuffer[MAX_FN_LEN+2];
	CImageFileStream File;
	HANDLE hItem = m_pFileList->GetFirstItem();
	if(hItem==NULL)
	{
		gpFileIO->DeleteFile(m_SDSFileName);
		return true;
	}
	if(File.Create(m_SDSFileName)==false)
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
