#include "StdAfx.h"
#include "Syser.h"
#include "MultiSourceCodeView.h"

WISP_MSG_MAP_BEGIN(CMultiSourceCodeView)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispMultiTabView)

WISP_MSG_EVENT_MAP_BEGIN(CMultiSourceCodeView)
WISP_MSG_EVENT_MAP_END

bool CMultiSourceCodeView::OnCommand(IN WISP_MSG* pMsg)
{
	if(pMsg->Command.CmdID>=WISP_WM_USER_START+0x1000)
	{
		if(pMsg->Command.CmdMsg==WISP_CMD_ITEM_SELECTED)
		{
#if 0  //不知道什么功能，先注释掉
			CMDSELECTSOURCECODELINE SelectLine;
			CSourceFrameWnd* pSourceFrameWnd=(CSourceFrameWnd*) GetChildWnd(pMsg->Command.CmdID);
			CSourceCodeWnd* pSourceCodeWnd =&pSourceFrameWnd->m_RightWnd;
			SelectLine.LineNum = (DWORD)pSourceCodeWnd->GetItemData(pMsg->Command.Param2,0);
			SelectLine.SourceFileId = pSourceFrameWnd->m_RightWnd.GetSourceFileID() ;
			CSDSModule*pSDSModule=pSourceFrameWnd->m_RightWnd.m_pSDSModule;
			PSDSOURCEFILEID pSourceFileID;
			DWORD Count;
			char buf[200];
			pSourceFileID = pSDSModule->GetSourceFileByID(SelectLine.SourceFileId);
			if(pSourceFileID==NULL)
				return false;
			SDLINELIST LineList;
			Count = pSDSModule->GetLineBySourceFileID(SelectLine.SourceFileId,SelectLine.LineNum,&LineList);
			if(Count==0)
			{
				PSDLINE pLine = pSDSModule->GetContiguityLineBySourceFileID(SelectLine.SourceFileId,SelectLine.LineNum);
				if(pLine)
					LineList.Append(pLine);
			}
			if(LineList.Count())
			{
				SDLINELIST::IT BeginIT,EndIT;
				BeginIT=LineList.Begin();
				EndIT=LineList.End();
				for(;BeginIT!=EndIT;BeginIT++)
				{
					TSPrintf(buf,"%08x %s \n",(*BeginIT)->Rav,pSDSModule->GetFuncNameByRva((*BeginIT)->Rav));
				}
			}
#endif
		}
	}
	return true;
}

bool CMultiSourceCodeView::OnCloseTabWnd(CWispWnd*pWnd)
{
	SOURCE_CODE_WND_ID WndID;
	CSourceCodeWnd*pSourceFrameWnd=(CSourceCodeWnd*)pWnd;
	WndID.FileID = pSourceFrameWnd->m_CurrentFileID;
	WndID.pSDSModule = pSourceFrameWnd->m_pSDSModule;
	TSet<SOURCE_CODE_WND_ID>::IT Iter = m_OpenedSourceCodeWnd.Find(WndID);
	if(Iter!=m_OpenedSourceCodeWnd.End())
		m_OpenedSourceCodeWnd.Remove(WndID);
	HANDLE hItem = gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem&&gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.GetItemLevel(hItem)==1)
	{
		if(Iter->pSDSModule == (CSDSModule*)gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.GetItemData(hItem))
			gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.UnselectItem(hItem);
	}
	return true;
}

void CMultiSourceCodeView::OnClosedTabWnd()
{
	if(m_WndList.Count()==0)
	{
		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
	}
}

void CMultiSourceCodeView::OnTabChanged(CWispWnd*pWnd)
{
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
}

bool CMultiSourceCodeView::OnCreate(IN WISP_MSG*pMsg)
{
	SetBGColor(ColorOption.clrBackground);
	return true;
}

void CMultiSourceCodeView::UpdateAllView()
{
	CSourceCodeWnd*pSourceCodeWnd; 
	CTabWndList::IT WndIt=m_WndList.Begin();
	while(WndIt!=m_WndList.End())
	{
		pSourceCodeWnd = (CSourceCodeWnd*)WndIt->pWnd;
		pSourceCodeWnd->LoadModuleImage();
		pSourceCodeWnd->UpdateView();
		WndIt++;
	}
}
