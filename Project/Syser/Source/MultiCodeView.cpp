#include "StdAfx.h"
#include "Syser.h"
#include "MultiCodeView.h"

WISP_MSG_MAP_BEGIN(CMultiCodeView)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispMultiTabView)

bool CMultiCodeView::OnCreate(IN WISP_MSG*pMsg)
{
	InsertView(NULL);
	SetOwner(this);
	return true;
}

void CMultiCodeView::OnTabChanged(CWispWnd*pWnd)
{
	gpSyser->m_MainFrame.m_SystemExplorer.m_pCurCodeView = (CCodeView*) pWnd;
	gpSyser->m_MainFrame.m_SystemExplorer.UpdateItemState();
}

void CMultiCodeView::SetActiveAddress(ULPOS Address,bool bRecordAddr)
{
	CCodeView*pActiveView=(CCodeView*)GetActiveWnd();
	if(pActiveView)
		pActiveView->SetStartAddress(Address,bRecordAddr);
}

ULPOS CMultiCodeView::GetActiveAddress()
{
	CCodeView*pActiveView=(CCodeView*)GetActiveWnd();
	if(pActiveView)
		return pActiveView->m_CurAddr;
	else
		return 0;
}

CCodeView* CMultiCodeView::InsertView(CCodeView*pSrcWnd)
{
	if(m_WndList.Count()>=9)
		return NULL;
	CCodeView*pCodeView;
	pCodeView = new CCodeView;
	pCodeView->Create(NULL,0,0,0,0,this,CMD_ID_CODE_VIEW_START+m_WndList.Count(),WISP_WLS_EMPTY_SEL_RECT|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS);
	pCodeView->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	pCodeView->m_pCodeDoc =&gpSyser->m_SyserUI.m_CodeDoc;
	InsertWnd(WISP_STR("????????"),pCodeView,WispTKDIBListDIB("\\Toolbar.bmp",16,16,126));
	SetActiveWnd(m_WndList.Count()-1);
	if(pSrcWnd)
		pCodeView->SetStartAddress(pSrcWnd->m_CurAddr);
	return pCodeView;
}

void CMultiCodeView::RemoveView(CCodeView*pRemoveWnd)
{
	if(m_WndList.Count()<2)
		return;
	RemoveWnd(pRemoveWnd);
}

void CMultiCodeView::UpdateAllView()
{
	CCodeView*pCodeView;
	CTabWndList::IT WndIt=m_WndList.Begin();
	while(WndIt!=m_WndList.End())
	{
		pCodeView = (CCodeView*)WndIt->pWnd;
		pCodeView->UpdateView();
		WndIt++;
	}
}

void CMultiCodeView::ResetContext()
{
	RemoveAllWnd();
	InsertView(NULL);
}

bool CMultiCodeView::IsBookMark(ULPOS Address)
{
	TSet<ULPOS>::IT Iter = m_BookMark.Find(Address);
	return Iter!=m_BookMark.End();
}

void CMultiCodeView::ToggleBookMark(ULPOS Address)
{
	TSet<ULPOS>::IT Iter;
	Iter = m_BookMark.Find(Address);
	if(Iter==m_BookMark.End())
		m_BookMark.InsertUnique(Address);
	else
		m_BookMark.Remove(Iter);
	UpdateAllView();
}

void CMultiCodeView::ToggleBookMark()
{
	CCodeView*pCodeView=(CCodeView*)GetActiveWnd();
	if(pCodeView==NULL)
		return;
	HANDLE hItem = pCodeView->GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return;
	ToggleBookMark((ULPOS)pCodeView->GetItemData(hItem,1));
	SYSTEM_EXPLORER.UpdateItemState();
}

void CMultiCodeView::GotoNextBookMark()
{
	CCodeView*pActiveView=(CCodeView*)GetActiveWnd();
	if(pActiveView==NULL)
		return;
	TSet<ULPOS>::IT Iter=m_BookMark.FindAlmost(pActiveView->m_CurAddr);
	if(Iter.IsExist())
		Iter++;
	if(Iter.IsExist()==false)
		Iter = m_BookMark.Begin();
	if(Iter.IsExist())
		VIEW_CODE(*Iter);
}

void CMultiCodeView::GotoPrevBookMark()
{
	CCodeView*pActiveView=(CCodeView*)GetActiveWnd();
	if(pActiveView==NULL)
		return;
	TSet<ULPOS>::IT Iter=m_BookMark.FindAlmost(pActiveView->m_CurAddr);
	if(Iter.IsExist() && pActiveView->m_CurAddr == *Iter)
		Iter--;
	if(Iter.IsExist()==false)
		Iter = m_BookMark.Last();
	if(Iter.IsExist())
		VIEW_CODE(*Iter);
}

void CMultiCodeView::ClearAllBookMark()
{
	m_BookMark.Clear();
	UpdateAllView();
	SYSTEM_EXPLORER.UpdateItemState();
}
