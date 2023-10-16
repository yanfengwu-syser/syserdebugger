#include "StdAfx.h"
#include ".\wispfilewnd.h"

WISP_MSG_MAP_BEGIN(CWispFileWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_COMMAND,OnCommand)
WISP_MSG_MAP_END(CWispSplitWnd)

CWispFileWnd::CWispFileWnd(void)
{
}

CWispFileWnd::~CWispFileWnd(void)
{
}

bool CWispFileWnd::OnCreate(IN WISP_MSG*pMsg)
{
	m_FolderTree.Create(NULL, 0,0,0,0, this, ID_FOLDER_TREE, WISP_WS_BORDER|LTS_NORMAL_SYTLE|LTS_SHOW_BUTTONS, WISP_SH_NORMAL);//|PLS_SHOW_CHECKBOXES|PLS_ENABLE_AUTOCHECK
	m_FolderList.Create(NULL, 0,0,0,0, this, ID_FOLDER_LIST, WISP_WS_BORDER|LTS_NORMAL_SYTLE|LTS_ENABLE_EDITLABLE|LTS_ENABLE_FR_HOVER, WISP_SH_NORMAL);

	InsertWnd(&m_FolderTree, 0, 200);
	InsertWnd(&m_FolderList, 0, 200);

	m_FolderList.InsertColumn(WSTR("File name"), 100);
	m_FolderList.InsertColumn(WSTR("Size"), 80);
	m_FolderList.InsertColumn(WSTR("Type"), 80);
	m_FolderList.InsertColumn(WSTR("Last write time"), 120);

	m_FolderTree.InsertColumn(WSTR("Folders"), 200);

	CLocalFileIO cFileIO;
	DWORD dwLogicDrivers = cFileIO.GetLogicalDrives();
	WISP_CHAR	wcDriver[MAX_PATH]={'A', ':', '\0'};
	int nDriver=0;
	while(dwLogicDrivers && nDriver<=32)
	{
		if(dwLogicDrivers&1)
		{
			wcDriver[0] = 'A'+nDriver;
			CListStringItem* pItem = m_FolderTree.InsertItem(wcDriver);
			m_FolderTree.InsertItem(WSTR("..."), NULL, pItem);
			m_FolderTree.Expand(pItem);
		}
		nDriver++;
		dwLogicDrivers=dwLogicDrivers>>1;
	}

	return TRUE;
}
bool CWispFileWnd::OnCommand(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CtrlType==WISP_CTRL_LIST)
	{
		// FolderTree
		if(pMsg->Command.CmdID==ID_FOLDER_TREE)
		{
			CListStringItem* pItem = (CListStringItem*)pMsg->Command.Param2;
			if(pMsg->Command.CmdMsg==WISP_CMD_PL_EXPANDED)
			{
				m_FolderTree.DeleteAllChildrenItems(pItem);
				FillFolderTree(pItem);
			}
			else if(pMsg->Command.CmdMsg==WISP_CMD_PL_COLLAPSED)
			{
				m_FolderTree.DeleteAllChildrenItems(pItem);
				m_FolderTree.InsertItem(WSTR("..."), NULL, pItem);
			}
			else if(pMsg->Command.CmdMsg==WISP_CMD_PL_SELCHANGED)
			{
				m_FolderList.DeleteAllItems();
				FillFolderList(pItem);
			}
		}
	}
	return TRUE;
}

int CWispFileWnd::FillFolderTree(CListStringItem* pItem)
{
	CHAR szPath[MAX_PATH]={0};
	WISP_CHAR wcPath[MAX_PATH]={0};
	m_FolderTree.GetItemFullName(pItem, wcPath);
	TStrToStr(wcPath, szPath);
	TStrCat(szPath, "*.*");

	int nFileCount = 0;
	int nFolderCount = 0;

	FILE_FIND_DATA FindFileData;
	CLocalFileIO	cFile;
	bool bContinue = cFile.FindFirstFile(szPath, &FindFileData);
	while(bContinue)
	{
		if(FindFileData.FileName[0]!='.')
		{
			if(FindFileData.FileAttribute&FIO_FA_DIR)
			{
				nFolderCount++;
				TStrToStr(FindFileData.FileName, wcPath);
				CListStringItem* pNewItem = m_FolderTree.InsertItem(wcPath, NULL, pItem);
				m_FolderTree.InsertItem(WSTR("..."), NULL, pNewItem);
			}
			else
			{
				nFileCount++;
			}
		}

		if (!cFile.FindNextFile(&FindFileData)) 
			bContinue = false;
	}

	cFile.FindClose(&FindFileData);
//	sprintf(szPath, "总共%d个对象，%d个文件，%d个目录。", nFileCount+nFolderCount, nFileCount, nFolderCount);
//	m_StatusWnd.SetWindowText(szPath);
	return nFileCount;

}

int CWispFileWnd::FillFolderList(CListStringItem* pItem)
{
	CHAR szPath[MAX_PATH]={0};
	WISP_CHAR wcPath[MAX_PATH]={0};
	m_FolderTree.GetItemFullName(pItem, wcPath);
	TStrToStr(wcPath, szPath);
	TStrCat(szPath, "*.*");

	int nFileCount = 0;
	int nFolderCount = 0;

	FILE_FIND_DATA FindFileData;
	CLocalFileIO	cFile;
	bool bContinue = cFile.FindFirstFile(szPath, &FindFileData);
	while(bContinue)
	{
		if(FindFileData.FileName[0]!='.')
		{
			WISP_CHAR Buf[64];
			// file name
			TStrToStr(FindFileData.FileName, wcPath);
			CListStringItem* pNewItem = m_FolderList.InsertItem(wcPath);

			// file size
			if(FindFileData.FileLength<1024)
				TSPrintf(Buf, WSTR("%d bytes"), FindFileData.FileLength);
			else if(FindFileData.FileLength<1024*1024)
				TSPrintf(Buf, WSTR("%d KB"), FindFileData.FileLength/1024);
			else
				TSPrintf(Buf, WSTR("%d MB"), FindFileData.FileLength/(1024*1024));

			if(FindFileData.FileAttribute&FIO_FA_DIR)
			{
				nFolderCount++;
				// file type
				m_FolderList.SetItemText(pNewItem, 2, WSTR("Folder"));
			}
			else
			{
				nFileCount++;
				// file size
				m_FolderList.SetItemText(pNewItem, 1, Buf);
				// file type
				m_FolderList.SetItemText(pNewItem, 2, WSTR("File"));
			}

			// modify date
			//SYSTEMTIME stSysTime;
			//FileTimeToSystemTime(&FindFileData.ftLastWriteTime, &stSysTime);
			//SystemTimeToTzSpecificLocalTime(NULL, &stSysTime, &stSysTime);
			//sprintf(Buf, "%d-%d-%d %d:%02d", stSysTime.wYear, stSysTime.wMonth, stSysTime.wDay, stSysTime.wHour, stSysTime.wMinute);
			TSPrintf(Buf, WSTR("%d-%d-%d %d:%02d"), 0, 0, 0, 0, 0, 0);
			m_FolderList.SetItemText(pNewItem, 3, Buf);
		}

		if (!cFile.FindNextFile(&FindFileData)) 
			bContinue = false;
	}

	cFile.FindClose(&FindFileData);
//	sprintf(szPath, "总共%d个对象，%d个文件，%d个目录。", nFileCount+nFolderCount, nFileCount, nFolderCount);
//	m_StatusWnd.SetWindowText(szPath);
	return nFileCount;
}
