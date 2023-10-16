#include "StdAfx.h"
#include "Syser.h"
#include "ModuleListWnd.h"

WISP_MSG_MAP_BEGIN(CModuleListWnd) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CModuleListWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTO,OnEventGoto)
	WISP_MSG_EVENT_MAP(EVENT_ID_PE_EXPLORER,OnEventPEExplorer)
WISP_MSG_EVENT_MAP_END

WISP_MENU_RES_ITEM ModuleListMenu[]=
{
	{WSTR("Goto Module Base "),EVENT_ID_GOTO,8,WISP_MIS_NORMAL},
	{WSTR("PE Explorer "),EVENT_ID_PE_EXPLORER,14,WISP_MIS_NORMAL},
	WISP_MENU_RES_END
};

CModuleListWnd::CModuleListWnd()
{
	m_pDbgModule = NULL;
	m_bSelectModule = false;
}

CModuleListWnd::~CModuleListWnd()
{

}

void CModuleListWnd::ItemClickNotify(HANDLE hItem,int Col)
{
	if(m_bSelectModule)
	{
		m_pDbgModule=(CDbgModule*)GetItemData(hItem);
		Destroy();
	}
}

bool CModuleListWnd::OnCreate(IN WISP_MSG* pMsg)
{
	AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,13*16+12));
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	m_Style|=WISP_WLS_EMPTY_SEL_RECT;
	m_PopupMenu.CreatePopupMenu(ModuleListMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	InsertColumn(WSTR("Name"),100);
	InsertColumn(WSTR("Base"),60);
	InsertColumn(WSTR("Size"),68);
	InsertColumn(WSTR("Symbols"),50);
	InsertColumn(WSTR("Path"),150);
	UpdateContext();
	return true;
}

bool CModuleListWnd::OnClose(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

bool CModuleListWnd::OnDestroy(IN WISP_MSG* pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CModuleListWnd::OnKeyEvent(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	if(pMsg->KeyEvent.bKeyDown && pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
	{
		hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
		if(hItem)
			m_PopupMenu.Popup();
	}
	return true;
}

void CModuleListWnd::Popup(bool	bSelectModule)
{
	if(bSelectModule)
	{
		m_bSelectModule = true;
		Create(WSTR("Modules"),0,0,500,350,NULL,CMD_ID_MODULE_LIST_WND,WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WS_NORMAL);
		SetOwner(&gpSyser->m_MainFrame.m_SystemExplorer);
		Center();
		Show(WISP_SH_MODAL_BLOCK);
	}
	else
	{
		if(IsWindow())
		{
			Destroy();
		}
		else
		{
			Create(WSTR("Modules"),0,0,500,350,NULL,CMD_ID_MODULE_LIST_WND,WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WS_NORMAL);
			SetOwner(&gpSyser->m_MainFrame.m_SystemExplorer);
			Center();
		}
	}
}

void CModuleListWnd::UpdateContext()
{
	int Count;
	HANDLE hItem;
	WCHAR szBuffer[MAX_FN_LEN];
	if(gpSyser->m_pDebugger==NULL)
		return;
	ClearChildItem();
	CDbgModuleMap::IT Iter = gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();
	while(Iter.IsExist())
	{
		hItem = InsertItemA(Iter->m_ModuleTitle);
		uNumToStr(Iter->m_ModuleBase,szBuffer);
		SetItemText(hItem,1,szBuffer);
		SetItemNum(hItem,2,Iter->m_ModuleSize,WSTR("%08X"));
		Count = 0;
		if(Iter->m_pSymbolModule)
			Count = Iter->m_pSymbolModule->m_SymbolMap.Count();
		SetItemNum(hItem,3,Count,WSTR("%d"));
		SetItemTextA(hItem,4,Iter->m_ModuleFullName);
		SetItemData(hItem,0,(NUM_PTR)&(*Iter));
		SetItemData(hItem,1,Iter->m_ModuleBase);
		Iter++;
	}
	if(gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
	{
		Iter = gpSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.Begin();
		while(Iter.IsExist())
		{
			hItem = InsertItemA(Iter->m_ModuleTitle);
			uNumToStr(Iter->m_ModuleBase,szBuffer);
			SetItemText(hItem,1,szBuffer);
			uNumToStr(Iter->m_ModuleSize,szBuffer);
			SetItemNum(hItem,2,Iter->m_ModuleSize,WSTR("%08X"));
			Count = 0;
			if(Iter->m_pSymbolModule)
				Count = Iter->m_pSymbolModule->m_SymbolMap.Count();
			uNumToStr(Count,szBuffer,10);
			SetItemNum(hItem,3,Count,WSTR("%d"));
			SetItemTextA(hItem,4,Iter->m_ModuleFullName);
			SetItemData(hItem,0,(NUM_PTR)&(*Iter));
			SetItemData(hItem,1,Iter->m_ModuleBase);
			Iter++;
		}
	}
}
bool CModuleListWnd::OnEventPEExplorer(IN WISP_MSG*pMsg)
{
	ULPOS ModuleBase;
	HANDLE hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ModuleBase = (ULPOS)GetItemData(hItem,1);
	gpSyser->m_MainFrame.m_PEExplorerForm.Popup();
	gpSyser->m_MainFrame.m_PEExplorerForm.UpdateContext(ModuleBase);
	return true;
}
bool CModuleListWnd::OnEventGoto(IN WISP_MSG*pMsg)
{
	ULPOS ModuleBase;
	HANDLE hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ModuleBase = (ULPOS)GetItemData(hItem,1);
	gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveAddress(ModuleBase);
	return true;
}


