#include "StdAfx.h"
#include "CommentList.h"
#include "Syser.h"

WISP_MENU_RES_ITEM CommentMenu[]=
{
	{WSTR("Goto"),	EVENT_ID_GOTO,8*16},
	{WSTR("Remove"),EVENT_ID_REMOVE,12*16+10},
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CCommentList) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CCommentList)
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTO,OnEventGoto);
	WISP_MSG_EVENT_MAP(EVENT_ID_REMOVE,OnEventRemove);
WISP_MSG_EVENT_MAP_END

CCommentList::CCommentList()
{

}

void CCommentList::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WSTR("Comment List"),0,0,400,380,NULL,CMD_ID_COMMENT_LIST,WISP_WLS_TREE|WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL);
		Center();
	}
}

bool CCommentList::OnCreate(IN WISP_MSG*pMsg)
{
	m_hSelectItem = NULL;
	m_PopupMenu.CreatePopupMenu(CommentMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_hGotoMenuItem = m_PopupMenu.GetItem(EVENT_ID_GOTO);
	AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,9*16+3));
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	InsertColumn(WSTR("Module/Offset"),120);
	InsertColumn(WSTR("TimeStamp/Comment"),150,WISP_WLCS_EDITABLE);
	UpdateContext();
	return true;
}

bool CCommentList::OnClose(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

bool CCommentList::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CCommentList::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	ULPOS Address;
	HANDLE hModuleItem;
	CDbgModule*pDbgModule;
	CCommentModule*pCommentModule;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{
		m_hSelectItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
		if(m_hSelectItem && GetItemLevel(m_hSelectItem)==1)
		{
			Address = (ULPOS)GetItemData(m_hSelectItem,1);
			hModuleItem = GetParentItem(m_hSelectItem);
			pCommentModule = (CCommentModule*)GetItemData(hModuleItem,0);
			pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(pCommentModule->m_ModuleName);
#ifdef CODE_OS_NT_DRV
			if(pDbgModule==NULL)
				pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(pCommentModule->m_ModuleName);
#endif
			if(pDbgModule)
				VIEW_CODE(Address+pDbgModule->m_ModuleBase);
		}
	}
	return true;
}

bool CCommentList::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return true;
	if(pMsg->KeyEvent.bKeyDown==false)
	{
		if(pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
		{
			m_hSelectItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
			m_PopupMenu.EnableItem(EVENT_ID_GOTO,GetItemLevel(m_hSelectItem)==1);
			if(m_hSelectItem)
				m_PopupMenu.Popup();
		}
	}
	return true;
}

bool CCommentList::OnEventGoto(IN WISP_MSG*pMsg)
{
	ULPOS Address;
	HANDLE hModuleItem;
	CDbgModule*pDbgModule;
	CCommentModule*pCommentModule;
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return true;
	Address = (ULPOS)GetItemData(m_hSelectItem,1);
	hModuleItem = GetParentItem(m_hSelectItem);
	pCommentModule = (CCommentModule*)GetItemData(hModuleItem,0);
	pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(pCommentModule->m_ModuleName);
#ifdef CODE_OS_NT_DRV
	if(pDbgModule==NULL)
		pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(pCommentModule->m_ModuleName);
#endif
	if(pDbgModule)
		VIEW_CODE(Address+pDbgModule->m_ModuleBase,true);
	return true;
}

bool CCommentList::OnEventRemove(IN WISP_MSG*pMsg)
{
	CCmtStr*pStr;
	CCommentModule*pCommentModule;
	int Level = GetItemLevel(m_hSelectItem);
	if(Level==0)
	{
		pCommentModule = (CCommentModule*) GetItemData(m_hSelectItem,0);
		if(pCommentModule)
		{
			gpSyser->m_SyserUI.DetachCommentModuleToProcess(pCommentModule);
			RemoveItem(m_hSelectItem);
		}
	}
	else
	{
		pStr = (CCmtStr*) GetItemData(m_hSelectItem,0);
		CCommentMap::IT Iter = *pStr;
		HANDLE hParent = GetParentItem(m_hSelectItem);
		pCommentModule = (CCommentModule*) GetItemData(hParent,0);
		pCommentModule->m_CommentMap.Remove(Iter);
		RemoveItem(m_hSelectItem);
	}
	UPDATE_CODE_VIEW();
	return true;
}

void CCommentList::UpdateContext()
{
	HANDLE hItem,hModuleItem;
	if(IsWindow()==false)
		return;
	ClearChildItem();
	for(CCommentContainer::IT ModuleIter=gpSyser->m_SyserUI.m_CommentContainer.Begin();ModuleIter!=gpSyser->m_SyserUI.m_CommentContainer.End();ModuleIter++)
	{
		hModuleItem = InsertItemA(TGetFileName((PCSTR)ModuleIter->m_ModuleName));
		SetItemNum(hModuleItem,1,(DWORD)ModuleIter->m_ModuleID,WSTR("%08X"));
		SetItemData(hModuleItem,0,(NUM_PTR)&(*ModuleIter));
		for(CCommentMap::IT Iter=ModuleIter->m_CommentMap.Begin();Iter!=ModuleIter->m_CommentMap.End();Iter++)
		{
			hItem=InsertItem(Iter.Key(),hModuleItem,WSTR("%08X"));
			SetItemTextA(hItem,1,(PCSTR)(*Iter));
			SetItemData(hItem,0,(NUM_PTR)&(*Iter));
			SetItemData(hItem,1,(NUM_PTR)Iter.Key());
		}
	}
}

bool CCommentList::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	if(Col!=1||GetItemLevel(hItem)!=1)
		return false;
	return true;
}

bool CCommentList::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	char szBuffer[256];
	CCmtStr*pStr;
	if(Col!=1||GetItemLevel(hItem)!=1)
		return false;
	pStr = (CCmtStr*)GetItemData(hItem,0);
	UnicodeToAnsi(String,szBuffer,sizeof(szBuffer));
	*pStr=szBuffer;
	UPDATE_CODE_VIEW();
	return true;
}

