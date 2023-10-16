#include "StdAfx.h"
#include "SourceDebugStartPage.h"
#include "MultiSourceCodeView.h"
#ifndef CODE_OS_NT_DRV
#include "SyserApp.h"
#else
#include "SyserNTDrvApp.h"
#endif


WISP_MSG_MAP_BEGIN(CSourceDebugStartPageWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_EVENT_MAP_BEGIN(CSourceDebugStartPageWnd)
WISP_MSG_EVENT_MAP_END

WISP_MSG_CMD_MAP_BEGIN(CSourceDebugStartPageWnd)
	WISP_MSG_CMD_MAP(SYMBOLMODULE_CHILD_WND_ID,OnSelectSymbolModule)
WISP_MSG_CMD_MAP_END

CSourceDebugStartPageWnd::CSourceDebugStartPageWnd()
{
}

CSourceDebugStartPageWnd::~CSourceDebugStartPageWnd()
{
}

bool CSourceDebugStartPageWnd::OnCreate(IN WISP_MSG* pMsg)
{
	SetBGColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_WHITE]);
	WISP_RECT rc={21,80,474,410};
	m_SymbolModuleList.Create(WSTR(""),&rc,this,SYMBOLMODULE_CHILD_WND_ID,WISP_WS_NULL|WISP_WLS_EMPTY_SEL_RECT);
	m_SymbolModuleList.InsertColumn(WSTR(""),200);
	return true;
}


bool CSourceDebugStartPageWnd::OnUpdateClient(IN WISP_MSG* pMsg)
{
	int i = 0;
	WISP_RECT rc={20,40,225,16},TextRC={25,80,340,20};
	CWispWnd::OnUpdateClient(pMsg);
	
	m_ClientDC.DrawShadowString(&rc,WSTR("Select an exist symbol module"),1);
	rc.y=60;rc.cx=476,rc.cy = m_ClientRect.cy - 60 - 40;
	if(rc.cy < 40)
		rc.cy=40;
	m_ClientDC.DrawRect(&rc,RGB(192,192,192));
	rc.x++,rc.cx-=2,rc.cy=20;
	m_ClientDC.DrawFullRect(&rc,RGB(170,170,170));

	m_ClientDC.DrawString(WSTR(" Name"),&rc,WISP_DT_VCENTER|WISP_DT_LEFT);
	rc.x+=340;
	m_ClientDC.DrawString(WSTR(" Time"),&rc,WISP_DT_VCENTER|WISP_DT_LEFT);
	return false;
}

bool CSourceDebugStartPageWnd::OnRecalcLayout(IN WISP_MSG* pMsg)
{
	CMultiSourceCodeView* pMultiSource = (CMultiSourceCodeView*)m_ParentWnd;
	Resize(pMultiSource->m_ClientRect.cx ,pMultiSource->m_ClientRect.cy);
	return true;
}

bool CSourceDebugStartPageWnd::OnSelectSymbolModule(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	if(pMsg->Command.CmdMsg==WISP_CMD_ITEM_SELECTED)
	{
		hItem = pMsg->Command.Param2;
		NUM_PTR value = m_SymbolModuleList.GetItemData(hItem,0);
		PLOADMODULESYMBOL pLoadModule = (PLOADMODULESYMBOL)value;
		if(pLoadModule)
			gpSyser->m_MainFrame.m_SourceDebugFrameWnd.OnSelectSymbolModule(pLoadModule->pSyserSymAnalyzer);
		else
			gpSyser->m_MainFrame.m_SourceDebugFrameWnd.OnSelectSymbolModule(NULL);
	}
	return true;
}

void CSourceDebugStartPageWnd::InsertSymbolModule(char* ModuleName,void*pData)
{
	HANDLE hItem;
	hItem = m_SymbolModuleList.InsertItemA(ModuleName);
	m_SymbolModuleList.SetItemData(hItem,0,*(DWORD*)&pData);
	
	Update();
}

bool CSourceDebugStartPageWnd::RemoveSymbolModule(void*pData)
{
	HANDLE hItem;
	NUM_PTR value;
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.RemoveSymbolModule(pData);
	hItem = m_SymbolModuleList.GetItem(NULL);
	while(hItem)
	{
		value = m_SymbolModuleList.GetItemData(hItem,0);
		if((void*)value==pData)
		{
			m_SymbolModuleList.RemoveItem(hItem);
			return true;
		}
		hItem = m_SymbolModuleList.GetNextItem(hItem);
	}
	Update();
	return false;
}