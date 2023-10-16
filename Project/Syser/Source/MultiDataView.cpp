#include "StdAfx.h"
#include "Syser.h"

WISP_MSG_MAP_BEGIN(CMultiDataView)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispMultiTabView)

WISP_MSG_EVENT_MAP_BEGIN(CMultiDataView)
	WISP_MSG_EVENT_MAP(WISP_MULTI_TAB_CMD_EXPAND_VIEW,OnEventExpandView)
	WISP_MSG_EVENT_MAP(WISP_MULTI_TAB_CMD_NEW_VIEW,OnEventNewView)
WISP_MSG_EVENT_MAP_END

bool CMultiDataView::OnEventExpandView(IN WISP_MSG*pMsg)
{
	if(m_WindowRect.cy>((CWispSplitWnd*)m_ParentWnd)->m_WindowRect.cy-20)
		gpSyser->m_MainFrame.m_SystemExplorer.AdjustSplitViewSize();
	else
		((CWispSplitWnd*)m_ParentWnd)->ExpandWnd(0);
	return true;
}

bool CMultiDataView::OnEventNewView(IN WISP_MSG*pMsg)
{
	CDataView*pActiveView;
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		pActiveView=(CDataView*)GetActiveWnd();
		InsertView(pActiveView);
	}
	return true;
}

bool CMultiDataView::OnCreate(IN WISP_MSG*pMsg)
{
	InsertView(NULL);
	return true;
}

void CMultiDataView::SetActiveDataWidth(int Width)
{
	CDataView*pActiveView=(CDataView*)GetActiveWnd();
	if(pActiveView)
		pActiveView->SetDataWidth(Width);
}

int CMultiDataView::GetActiveDataWidth()
{
	CDataView*pActiveView=(CDataView*)GetActiveWnd();
	if(pActiveView)
		return pActiveView->GetDataWidth();
	return 1; //默认的宽度是 byte
}

void CMultiDataView::SetActiveAddress(DWORD Address,WCHAR* pCmdString)
{
	CDataView*pActiveView=(CDataView*)GetActiveWnd();
	if(pActiveView)
	{
		pActiveView->ViewAddress(Address);
		if(pCmdString!=NULL)
			pActiveView->SetFloatCmdString(pCmdString);
	}
}

DWORD CMultiDataView::GetActiveAddress()
{
	CDataView*pActiveView=(CDataView*)GetActiveWnd();
	if(pActiveView)
		return (DWORD)pActiveView->m_CurAddr;
	else
		return 0;
}

CDataView* CMultiDataView::InsertView(CDataView*pSrcWnd)
{
	if(m_WndList.Count()>=9)
		return NULL;
	CDataView*pNewView = new CDataView;
	pNewView->Create(NULL,CWispRect(0,0,0,0),this,CMD_ID_DATA_VIEW_START+m_WndList.Count(),WISP_WS_NULL);
	pNewView->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	InsertWnd(WISP_STR("????????"),pNewView,WispTKDIBListDIB("\\Toolbar.bmp",16,16,127));
	SetActiveWnd(m_WndList.Count()-1);
	SetActiveAddress(pSrcWnd?(DWORD)pSrcWnd->m_CurAddr:0);
	if(pSrcWnd)
		pNewView->m_ShowLength = pSrcWnd->m_ShowLength;
	return pNewView;
}

void CMultiDataView::RemoveView(CDataView*pRemoveWnd)
{
	if(m_WndList.Count()<2)
		return;
	RemoveWnd(pRemoveWnd);
}

void CMultiDataView::UpdateAllView()
{
	CDataView*pDataView;
	CTabWndList::IT WndIt=m_WndList.Begin();
	while(WndIt!=m_WndList.End())
	{
		pDataView = (CDataView*)WndIt->pWnd;
		pDataView->Update();
		WndIt++;
	}
}

void CMultiDataView::SaveContextAllView()
{
	CDataView*pDataView;
	CTabWndList::IT WndIt=m_WndList.Begin();
	while(WndIt!=m_WndList.End())
	{
		pDataView = (CDataView*)WndIt->pWnd;
		pDataView->SaveContext();
		WndIt++;
	}
}

void CMultiDataView::ResetContext()
{
	RemoveAllWnd();
	InsertView(NULL);
}


