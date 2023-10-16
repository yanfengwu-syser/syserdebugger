#include "StdAfx.h"
#include "SDSModuleList.h"
#include "Syser.h"


WISP_MENU_RES_ITEM SDSModuleMenu[]=
{
	{WSTR("Set As Active Module"),EVENT_ID_SET_AS,56},
	{WSTR("Unload"),EVENT_ID_REMOVE,23},
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CSDSModuleList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CSDSModuleList)
	WISP_MSG_EVENT_MAP(EVENT_ID_REMOVE,OnEventRemove)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_AS,OnEventSetAsActiveModule)
WISP_MSG_EVENT_MAP_END

CSDSModuleList::CSDSModuleList()
{
}

CSDSModuleList::~CSDSModuleList()
{
}

bool CSDSModuleList::OnCreate(IN WISP_MSG* pMsg)
{
	CWispDIBList*pDIBList = WispTKDIBList("\\Toolbar.bmp",16,16);
	m_SelectBKColor = ColorOption.clrSelectedFrame;
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	m_pIconCFile=pDIBList->GetDIB(15*16+8);
	m_pIconCPPFile=pDIBList->GetDIB(15*16+6);;
	m_pIconHFile=pDIBList->GetDIB(15*16+7);;
	m_pIconModule=pDIBList->GetDIB(14*16+3);;
	m_SDSModulePopupMenu.CreatePopupMenu(SDSModuleMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	InsertColumn(WSTR("Module Name"),150);
	InsertColumn(WSTR("File Count / Size"),150);
	SetOwner(this);
	m_hActiveModule = NULL;
	return true;
}

bool CSDSModuleList::OnDestroy(IN WISP_MSG* pMsg)
{
	m_SDSModulePopupMenu.Destroy();
	return true;
}

bool CSDSModuleList::OnKeyEvent(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	if(pMsg->KeyEvent.KeyType ==WISP_VK_RETURN && pMsg->KeyEvent.bKeyDown && GetItemLevel(hItem)==1)
	{
		ItemDBClickNotify(hItem,1);
	}
	if(pMsg->KeyEvent.KeyType ==WISP_VK_RBUTTON && pMsg->KeyEvent.bKeyDown==false && GetItemLevel(hItem)==0)
	{
		PopupMenu();
	}
	return true;
}

void CSDSModuleList::PopupMenu()
{
	HANDLE hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	m_SDSModulePopupMenu.EnableItem(EVENT_ID_SET_AS,hItem && hItem!=m_hActiveModule);
	m_SDSModulePopupMenu.Popup();
}

bool CSDSModuleList::OnEventSetAsActiveModule(IN WISP_MSG* pMsg)
{
	HANDLE hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	if(GetItemLevel(hItem)==0)
	{
		SetActiveModule((CSDSModule*)GetItemData(hItem));
	}
	return true;
}

bool CSDSModuleList::OnEventRemove(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	if(GetItemLevel(hItem)==0)
	{
		gpSyser->m_SyserUI.UnloadSDSModule((CSDSModule*)GetItemData(hItem));
	}
	return true;
}

void CSDSModuleList::ItemDBClickNotify(HANDLE hItem,int Col)
{
	int Level = GetItemLevel(hItem);
	if(Level==0)
	{
		if(m_pActiveSDSModule!=(CSDSModule*)GetItemData(hItem))
			SetActiveModule(hItem);
	}
	if(Level==1)
	{
		CSDSModule*pSDSModule = (CSDSModule*) GetItemData(hItem);
		DWORD SourceFileId = (DWORD)GetItemData(hItem,1);
		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.ShowSourceFile(pSDSModule,SourceFileId,1);
		Focus();
	}
}

void CSDSModuleList::InsertSymbolModule(CSDSModule*pSDSModule)
{
	PCSTR ModuleName;
	ModuleName = TGetFileName((PCSTR)pSDSModule->m_ModuleFileName);
	HANDLE hItem = InsertItemA(ModuleName,NULL,WISP_WLIS_NORMAL,m_pIconModule);
	SetItemNum(hItem,1,pSDSModule->GetSourceFileCountInPackages(),WSTR("%d Source Code File(s)"));
	SetItemData(hItem,0,(NUM_PTR)pSDSModule);
	if(m_pActiveSDSModule==NULL)
	{
		SetActiveModule(hItem);
	}
	UpdateModuleFileList(hItem,pSDSModule);
}

void CSDSModuleList::SetActiveModule(HANDLE hItem)
{
	if(m_hActiveModule)
	{
		SetItemTextColor(m_hActiveModule,0,m_FontColor);
		UnexpandItem(m_hActiveModule);
	}
	m_hActiveModule = hItem;
	m_pActiveSDSModule = (CSDSModule*)GetItemData(hItem);
	SetItemTextColor(m_hActiveModule,0,ColorOption.clrSelectedFrame);
	ExpandItem(m_hActiveModule);
}

CSDSModule* CSDSModuleList::GetActiveModule()const
{
	return m_pActiveSDSModule;
}

void CSDSModuleList::SetActiveModule(CSDSModule*pSDSModule)
{
	HANDLE hItem;
	if(m_pActiveSDSModule==pSDSModule)
		return;
	hItem = GetNextItem(NULL);
	while(hItem)
	{
		if(pSDSModule==(CSDSModule*)GetItemData(hItem))
		{
			SetActiveModule(hItem);
			return;
		}
		hItem = GetNextItem(hItem);
	}
}

bool CSDSModuleList::RemoveSymbolModule(CSDSModule*pSDSModule)
{
	HANDLE hItem;
	hItem = GetNextItem(NULL);
	while(hItem)
	{
		if(pSDSModule==(CSDSModule*)GetItemData(hItem))
		{
			if(m_pActiveSDSModule==pSDSModule)
			{
				m_pActiveSDSModule = NULL;
				m_hActiveModule = NULL;
			}
			TSet<SOURCE_CODE_WND_ID>::IT Iter = gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_MultiSourceCodeView.m_OpenedSourceCodeWnd.Begin();
			while(Iter.IsExist())
			{
				if(Iter->pSDSModule==pSDSModule)
				{
					CSourceCodeWnd*pSrcWnd = Iter->pSourceCodeWnd;
					Iter++;
					gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_MultiSourceCodeView.RemoveWnd(pSrcWnd);
					gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UnloadSDSModule(pSDSModule);
				}
				else
					Iter++;
			}
			RemoveItem(hItem);
			if(gpSyser->m_bActive)
				Update();
			return true;
		}
		hItem = GetNextItem(hItem);
	}
	return false;
}

void CSDSModuleList::UpdateModuleFileList(HANDLE hModuleItem,CSDSModule*pSDSModule)
{
	CWispDIB*pTypeDIB;
	PSDSOURCEFILEID pSourceFileList;
	DWORD SourceFileCount;
	HANDLE hItem;
	DWORD dwDIBIndex;
	DWORD i;
	pSourceFileList=pSDSModule->GetSourceFileList(&SourceFileCount);
	if(pSourceFileList)
	{
		for(i = 0; i <SourceFileCount;i++)
		{
			if(pSourceFileList[i].FileLen==0)
				continue;
			char* ExtName;
			char *Name=TStrRChr(pSourceFileList[i].uName.Name,'\\');
			ExtName = TGetFileExt(&Name[1]);
			dwDIBIndex=15*16+9;
			if(ExtName)
			{
				if(TStrICmp(ExtName,"c")==0)
					pTypeDIB=m_pIconCFile;
				else if(TStrICmp(ExtName,"cpp")==0)
					pTypeDIB=m_pIconCPPFile;
				else if(TStrICmp(ExtName,"h")==0 || TStrICmp(ExtName,"hpp")==0)
					pTypeDIB=m_pIconHFile;
				else
					pTypeDIB=NULL;
			}
			else
			{
				pTypeDIB=m_pIconHFile;
			}
			if(Name)
				hItem = InsertItemA(&Name[1],hModuleItem,WISP_WLIS_NORMAL,pTypeDIB);
			else
				hItem = InsertItemA(pSourceFileList[i].uName.Name,hModuleItem,WISP_WLIS_NORMAL,pTypeDIB);

			SetItemNum(hItem,1,pSourceFileList[i].FileLen,WSTR("%d Byte(s)"));
			SetItemData(hItem,0,(NUM_PTR)pSDSModule);
			SetItemData(hItem,1,pSourceFileList[i].FileID);
		}
	}
}

