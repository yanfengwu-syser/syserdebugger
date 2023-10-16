#include "StdAfx.h"
#include "Syser.h"
#include "CallStackWnd.h"

WISP_MSG_MAP_BEGIN(CCallStackWnd) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

CCallStackWnd::CCallStackWnd()
{
}

CCallStackWnd::~CCallStackWnd()
{
}

bool CCallStackWnd::OnCreate(IN WISP_MSG* pMsg)
{
	AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,18));
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	m_SelectBKColor = ColorOption.clrSelectedFrame;
	InsertColumn(WSTR("Call Return"),100);
	InsertColumn(WSTR("Function"),200);
	m_Style|=WISP_WLS_VERT_LINE|WISP_WLS_EMPTY_SEL_RECT;
	return true;
}

bool CCallStackWnd::OnClose(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

void CCallStackWnd::ItemDBClickNotify(HANDLE hItem,int Col)
{
	ULPOS Address;
	UpdateFrame(hItem);
	CALL_FRAME*pCallFrame = (CALL_FRAME*)GetItemData(m_hCurFrameItem);
	Address = pCallFrame->CallReturn;
	CSDSModule*pSDSModule = gpSyser->m_SyserUI.GetSDSModule(Address);
	if(pSDSModule)
	{
		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.SetActiveModule(pSDSModule);
		SDLINELIST LineList;
		if(pSDSModule->GetLineFromRva(Address-pSDSModule->m_pCurDbgModule->m_ModuleBase,&LineList))
		{
			gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
			if(gpSyser->m_MainFrame.m_SourceDebugFrameWnd.ShowSourceFile(pSDSModule,(*LineList[0])->FileID,(*LineList[0])->LineNumber))
				return;
		}
	}
	gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SYSTEM_EXPLORER_VIEW);
	CENTER_VIEW_CODE(Address);
}

void CCallStackWnd::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WSTR("Call Stack"),0,0,400,200,NULL,CMD_ID_CALL_STACK,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL);
		Center();
		UpdateContext();
	}
}

void CCallStackWnd::UpdateContext()
{
	WCHAR szBuffer[128];
	HANDLE hItem;
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false || IsVisible()==false)
		return;
	m_hCurFrameItem = NULL;
	ClearChildItem();
	for(TList<CALL_FRAME>::IT Iter=gpSyser->m_SyserUI.m_CallStack.m_CallFrameList.Begin();
		Iter!=gpSyser->m_SyserUI.m_CallStack.m_CallFrameList.End();Iter++)
	{
		TSPrintf(szBuffer,WSTR("  %08X"),Iter->CallReturn);
		hItem = InsertItem(szBuffer);
		SetItemTextA(hItem,1,Iter->FuncName);
		SetItemData(hItem,0,(NUM_PTR)&(*Iter));
		if(gpSyser->m_SyserUI.m_CallStack.m_pCurCallFrame ==&(*Iter))
			UpdateFrame(hItem);
	}
}

void CCallStackWnd::UpdateFrame(HANDLE hItem)
{
	CALL_FRAME*pCallFrame;
	WCHAR szBuffer[128];
	if(hItem == m_hCurFrameItem)
		return;
	if(m_hCurFrameItem)
	{
		SetItemTextColor(m_hCurFrameItem,-1,ColorOption.clrText);
		pCallFrame = (CALL_FRAME*)GetItemData(m_hCurFrameItem);
		TSPrintf(szBuffer,WSTR("  %08X"),pCallFrame->CallReturn);
		SetItemText(m_hCurFrameItem,0,szBuffer);		
	}
	m_hCurFrameItem = hItem;
	SetItemTextColor(m_hCurFrameItem,-1,ColorOption.clrSpeicalText);
	pCallFrame = (CALL_FRAME*)GetItemData(m_hCurFrameItem);
	TSPrintf(szBuffer,WSTR("->%08X"),pCallFrame->CallReturn);
	SetItemText(hItem,0,szBuffer);
}
