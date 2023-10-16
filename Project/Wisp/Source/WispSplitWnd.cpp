#include "StdAfx.h"
#include "WispSplitWnd.h"

WISP_MSG_MAP_BEGIN(CWispSplitWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_PARENT_RESIZE,OnParentResize)
WISP_MSG_MAP_END(CWispWnd)

CWispSplitWnd::CWispSplitWnd()
{
	m_SplitBorderSize = 4;
	m_CtrlType = WISP_CTRL_SPLIT_WND;
}

CWispSplitWnd::~CWispSplitWnd()
{
}

bool CWispSplitWnd::OnCreate(IN WISP_MSG*pMsg)
{
	m_DeltaSize.cx = m_ParentWnd->m_WindowRect.cx - m_WindowRect.cx;
	m_DeltaSize.cy = m_ParentWnd->m_WindowRect.cy - m_WindowRect.cy;
	return true;
}

bool CWispSplitWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	m_WndList.Clear();
	return true;
}

bool CWispSplitWnd::OnUpdate(IN WISP_MSG*pMsg)
{
	WISP_SPLIT_WND*pWSWnd;
	CWSWndList::IT Iter;
	Iter=m_WndList.Begin();
	while(Iter!=m_WndList.End())
	{
		pWSWnd=&(*Iter);
		m_pWispBase->m_pCurDrawObj->DrawSplitRect(&m_WindowDC,&pWSWnd->SplitRect,(m_Style & WISP_SWS_HORZ)!=0);
		Iter++;
	}
	return true;
}

bool CWispSplitWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	return false;
}

bool CWispSplitWnd::OnParentResize(IN WISP_MSG*pMsg)
{
	if(m_Style & WISP_SWS_AUTO_RESIZE)
	{
		Resize(pMsg->Resize.NewSize.cx-m_DeltaSize.cx,pMsg->Resize.NewSize.cy-m_DeltaSize.cy);
	}
	return true;
}


bool CWispSplitWnd::OnSize(IN WISP_MSG*pMsg)
{
	if(m_Style & WISP_SWS_AUTO_RESIZE)
	{
		m_DeltaSize.cx = m_ParentWnd->m_WindowRect.cx - m_WindowRect.cx;
		m_DeltaSize.cy = m_ParentWnd->m_WindowRect.cy - m_WindowRect.cy;
	}	
	AdjustWndPos();
	return true;
}

bool CWispSplitWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.KeyType==WISP_VK_LBUTTON)
	{
		if(pMsg->KeyEvent.bKeyDown)
		{
			WISP_POINT MouseCltPT;
			MouseCltPT = pMsg->MsgMouseWndPT;
			PointToRect(&MouseCltPT,&m_ClientRect);

			CWSWndList::IT Iter;
			Iter=m_WndList.Begin();
			while(Iter!=m_WndList.End())
			{
				if(PtInRect(&Iter->SplitRect,&pMsg->MsgMouseWndPT))
				{
					m_CurSplitWndIt = Iter;
					break;
				}
				Iter++;
			}
		}
		else
		{			
			m_CurSplitWndIt = NULL;
		}
	}
	return true;
}

bool CWispSplitWnd::OnMouseLeave(IN WISP_MSG*pMsg)
{
	int Delta = (m_Style & WISP_SWS_HORZ)?pMsg->MouseEvent.DeltaX:pMsg->MouseEvent.DeltaY;

	if(m_CurSplitWndIt!=NULL)
	{		
		bool bMove;
		if(m_Style & WISP_SWS_HORZ)
			bMove = (Delta>=0 && pMsg->MsgMouseWndPT.x>=m_CurSplitWndIt->SplitRect.x) || (Delta< 0 && pMsg->MsgMouseWndPT.x<m_CurSplitWndIt->SplitRect.x+m_CurSplitWndIt->SplitRect.cx);
		else
			bMove = (Delta>=0 && pMsg->MsgMouseWndPT.y>=m_CurSplitWndIt->SplitRect.y) || (Delta< 0 && pMsg->MsgMouseWndPT.y<m_CurSplitWndIt->SplitRect.y+m_CurSplitWndIt->SplitRect.cy);
		if(bMove)
		{
			m_NextSplitWndIt = m_CurSplitWndIt+1;
			if(	m_NextSplitWndIt!=m_WndList.End()&&  
				m_CurSplitWndIt->SizeXorY+Delta>0 && 
				m_NextSplitWndIt->SizeXorY-Delta>0)
			{
				m_CurSplitWndIt->SizeXorY+=Delta;
				if(m_NextSplitWndIt!=m_WndList.End())
					(*m_NextSplitWndIt).SizeXorY-=Delta;
				AdjustWndPos();
			}
		}
		return false;
	}
	else
	{
		m_pWispBase->ChangeCursorType(WISP_CT_ARROW);
		return true;
	}
}

bool CWispSplitWnd::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	//if(pMsg->KeyEvent.KeyType==WISP_VK_LBUTTON)
	{
		WISP_POINT MouseCltPT;
		MouseCltPT = pMsg->MsgMouseWndPT;
		PointToRect(&MouseCltPT,&m_ClientRect);

		int Index;
		CWSWndList::IT Iter;
		Iter=m_WndList.Begin();
		Index = 0;
		while(Iter!=m_WndList.End())
		{
			if(PtInRect(&Iter->SplitRect,&pMsg->MsgMouseWndPT))
			{
				if(pMsg->KeyEvent.KeyType==WISP_VK_LBUTTON)
					SendCmdMsg(WISP_CMD_ITEM_LDBCLICK,Index,&(*Iter));
				else if(pMsg->KeyEvent.KeyType==WISP_VK_RBUTTON)
					SendCmdMsg(WISP_CMD_ITEM_RDBCLICK,Index,&(*Iter));
				break;
			}
			Iter++;
			Index++;
		}
	}
	return true;
}

bool CWispSplitWnd::OnMouseMove(IN WISP_MSG*pMsg)
{
	bool bInResizeArea,bMove;
	WISP_POINT MouseCltPT;
	MouseCltPT = pMsg->MsgMouseWndPT;
	PointToRect(&MouseCltPT,&m_ClientRect);
	int Delta = (m_Style & WISP_SWS_HORZ)?pMsg->MouseEvent.DeltaX:pMsg->MouseEvent.DeltaY;
	if(m_CurSplitWndIt!=NULL)
	{
		if(m_Style & WISP_SWS_HORZ)
			bMove = (Delta>=0 && pMsg->MsgMouseWndPT.x>=m_CurSplitWndIt->SplitRect.x+m_CurSplitWndIt->SplitRect.cx/2) || (Delta< 0 && pMsg->MsgMouseWndPT.x<m_CurSplitWndIt->SplitRect.x+m_CurSplitWndIt->SplitRect.cx/2);
		else
			bMove = (Delta>=0 && pMsg->MsgMouseWndPT.y>=m_CurSplitWndIt->SplitRect.y+m_CurSplitWndIt->SplitRect.cy/2) || (Delta< 0 && pMsg->MsgMouseWndPT.y<m_CurSplitWndIt->SplitRect.y+m_CurSplitWndIt->SplitRect.cy/2);
		if(bMove)
		{
			m_NextSplitWndIt = m_CurSplitWndIt+1;
			if(	m_NextSplitWndIt!=m_WndList.End()&& 
				m_CurSplitWndIt->SizeXorY+Delta>0 && 
				m_NextSplitWndIt->SizeXorY-Delta>0)
			{
				m_CurSplitWndIt->SizeXorY+=Delta;
				if(m_NextSplitWndIt!=m_WndList.End())
					(*m_NextSplitWndIt).SizeXorY-=Delta;
				AdjustWndPos();
			}
		}
	}
	else
	{
		CWSWndList::IT Iter;
		Iter=m_WndList.Begin();
		bInResizeArea = false;
		while(Iter!=m_WndList.End())
		{
			if(PtInRect(&Iter->SplitRect,&pMsg->MsgMouseWndPT))
			{
				bInResizeArea = true;
				m_pWispBase->ChangeCursorType((m_Style & WISP_SWS_HORZ)?WISP_CT_RESIZE_HORZ:WISP_CT_RESIZE_VERT);
				break;
			}
			Iter++;
		}
	}
	return true;
}

void CWispSplitWnd::AdjustWndPos()
{
	int SizeXorY;
	WISP_SPLIT_WND*pWSWnd;
	CWSWndList::IT Iter;
	Iter=m_WndList.Begin();
	SizeXorY=0;
	for(int n=0;n<m_WndList.Count();n++)
	{
		pWSWnd=&(*Iter);
		if(m_Style & WISP_SWS_HORZ)
		{
			if(n==m_WndList.Count()-1)
				pWSWnd->SizeXorY = m_ClientRect.cx-SizeXorY;
			pWSWnd->pWnd->MoveToClient(SizeXorY,0);
			pWSWnd->pWnd->Resize(pWSWnd->SizeXorY,m_ClientRect.cy);
			pWSWnd->SplitRect.y=m_ClientRect.y;
			pWSWnd->SplitRect.cy=m_ClientRect.cy;
			pWSWnd->SplitRect.x=m_ClientRect.x+SizeXorY+pWSWnd->pWnd->m_WindowRect.cx;
			pWSWnd->SplitRect.cx=m_SplitBorderSize;
			SizeXorY+=pWSWnd->SizeXorY+pWSWnd->SplitRect.cx;
		}
		else
		{
			if(n==m_WndList.Count()-1)
				pWSWnd->SizeXorY=m_ClientRect.cy-SizeXorY;
			pWSWnd->pWnd->MoveToClient(0,SizeXorY);
			pWSWnd->pWnd->Resize(m_ClientRect.cx,pWSWnd->SizeXorY);
			pWSWnd->SplitRect.x=m_ClientRect.x;
			pWSWnd->SplitRect.cx=m_ClientRect.cx;
			pWSWnd->SplitRect.y=m_ClientRect.y+SizeXorY+pWSWnd->pWnd->m_WindowRect.cy;
			pWSWnd->SplitRect.cy=m_SplitBorderSize;
			SizeXorY+=pWSWnd->SizeXorY+pWSWnd->SplitRect.cy;
		}
		Iter++;
	}
	Update();
}

bool CWispSplitWnd::InsertWnd(IN CWispWnd*pWnd,IN UINT Style,IN int SizeXorY,IN int InsertPos)
{
	WISP_SPLIT_WND WSWnd;
	CWSWndList::IT Iter;
	if(InsertPos>m_WndList.Count())
		return false;
	WSWnd.pWnd = pWnd;
	WSWnd.Style = Style;
	WSWnd.SizeXorY = SizeXorY;
	if(InsertPos<0)
	{
		Iter=m_WndList.Append(WSWnd);
	}
	else
	{
		if(m_WndList.Count()>0)
			Iter=m_WndList[InsertPos];
		Iter=m_WndList.InsertBefore(Iter,WSWnd);
	}
	return true;
}

bool CWispSplitWnd::RemoveWnd(IN CWispWnd*pWnd)
{
	int DelCount;
	CWSWndList::IT Iter;
	DelCount=0;
	Iter=m_WndList.Begin();
	while(Iter!=m_WndList.End())
	{
		if(Iter->pWnd==pWnd)
		{
			m_WndList.Remove(Iter);
			DelCount++;
		}
		Iter++;
	}
	return DelCount!=0;
}

bool CWispSplitWnd::ResizeWndSpace(int Pos,int SizeXorY)
{
	if(Pos>=m_WndList.Count())
		return false;
	CWSWndList::IT Iter = m_WndList[Pos];
	Iter->SizeXorY = SizeXorY;
	return true;
}

bool CWispSplitWnd::GetWndSpace(int Pos,int& SizeXorY)const 
{
	if(Pos>=m_WndList.Count())
		return false;
	CWSWndList::IT Iter = m_WndList[Pos];
	SizeXorY=Iter->SizeXorY;
	return true;
}

void CWispSplitWnd::ExpandWnd(int Pos)
{
	int Index,TotalSize;
	Index=0;
	TotalSize = (m_Style & WISP_SWS_HORZ)?m_ClientRect.cx:m_ClientRect.cy;
	for(CWSWndList::IT Iter = m_WndList.Begin();Iter!=m_WndList.End();Iter++)
	{
		if(Index==Pos)
		{
			Iter->SizeXorY = TotalSize - (m_WndList.Count()-1)*(m_SplitBorderSize+1);
		}
		else
		{
			Iter->SizeXorY = 1;
		}
		Index++;
	}
	AdjustWndPos();
}
