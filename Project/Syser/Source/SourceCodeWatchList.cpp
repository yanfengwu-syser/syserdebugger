#include "StdAfx.h"
#include "Syser.h"
#include "SourceCodeWatchList.h"

WISP_MENU_RES_ITEM SourceWatchMenu[]=
{
	{WSTR("Add"),EVENT_ID_ADD,8*16},
	{WSTR("Remove"),EVENT_ID_REMOVE,12*16+10},
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CSourceCodeWatchList) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CSourceCodeWatchList)
	WISP_MSG_EVENT_MAP(EVENT_ID_ADD,OnEventAdd);
	WISP_MSG_EVENT_MAP(EVENT_ID_REMOVE,OnEventRemove);
WISP_MSG_EVENT_MAP_END

CSourceCodeWatchList::CSourceCodeWatchList(void)
{
	m_hLastItem = NULL;
}

CSourceCodeWatchList::~CSourceCodeWatchList(void)
{
}

bool CSourceCodeWatchList::OnCreate(IN WISP_MSG*pMsg)
{
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	m_Style|=WISP_WLS_VERT_LINE;
	m_PopupMenu.CreatePopupMenu(SourceWatchMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_hRemoveItem = m_PopupMenu.GetItem(EVENT_ID_REMOVE);
	InsertColumn(WISP_STR("Expression[F2]"),90,WISP_WLCS_EDITABLE);
	InsertColumn(WISP_STR("Value"),70);
	InsertColumn(WISP_STR("Context"),60);
	ResetContext();
	return true;
}

bool CSourceCodeWatchList::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CSourceCodeWatchList::OnEventAdd(IN WISP_MSG*pMsg)
{
	BeginEditItem(m_hLastItem,0);
	return true;
}

bool CSourceCodeWatchList::OnEventRemove(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem && hItem!=m_hLastItem)
		RemoveItem(hItem);
	return true;
}

bool CSourceCodeWatchList::OnKeyEvent(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return true;
	if(pMsg->KeyEvent.bKeyDown==false)
	{
		if(pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
		{
			hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
			m_PopupMenu.EnableItem(m_hRemoveItem,hItem!=NULL && hItem!=m_hLastItem);
			m_PopupMenu.Popup();
		}
		else if(pMsg->KeyEvent.KeyType == WISP_VK_F2)
		{
			hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
			if(hItem!=NULL)
			{
				BeginEditItem(hItem,0);
			}
		}
	}
	return true;
}

bool CSourceCodeWatchList::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return false;
	return true;
}

bool CSourceCodeWatchList::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	if(hItem==m_hLastItem)
	{
		if(String.Length())
		{
			m_hLastItem = InsertItem((WISP_PCSTR)NULL);
			return true;
		}
		return false;
	}
	if(String.Length()==0)
	{
		RemoveItem(hItem);
		return false;
	}
	return true;
}

void CSourceCodeWatchList::ItemChangedNotify(HANDLE hItem,int Col,CWispString&String)
{
	if(Col==0)
		CalcLineExp(hItem);
}

void CSourceCodeWatchList::UpdateContext()
{
	HANDLE hItem=GetItem(0);
	while(hItem)
	{
		if(hItem==m_hLastItem)
			break;
		CalcLineExp(hItem);
		hItem = GetNextItem(hItem);
	}
	UpdateClient();
}

void CSourceCodeWatchList::ResetContext()
{
	ClearChildItem();
	m_hLastItem = InsertItem((WISP_PCSTR)NULL);
	SelectItem(m_hLastItem);
}

void CSourceCodeWatchList::CalcLineExp(HANDLE hItem)
{
	CHAR  szBuffer[256];
	WCHAR szSymbol[256];
	PCWSTR pszSym;
	DWORD Result;
	pszSym = NULL;
	if(CALCEXP(GetItemText(hItem),&Result))
	{
		SetItemNum(hItem,1,Result);
		if(GETSYM(Result,szBuffer))
		{
			TStrCpy(szSymbol,szBuffer);
			pszSym = szSymbol;
	}
	}
	else
		SetItemText(hItem,1,WSTR("????????"));
	SetItemText(hItem,2,pszSym);
}
