#include "StdAfx.h"
#include "WispTabWnd.h"

WISP_MSG_MAP_BEGIN(CWispTabWnd)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent);
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_EVENT_MAP_BEGIN(CWispTabWnd)
	WISP_MSG_EVENT_MAP(WISP_ID_TAB_CLOSE_BT,OnEventCloseBT)
WISP_MSG_EVENT_MAP_END

bool CWispTabWnd::InitWnd()
{
	if(CWispWnd::InitWnd()==false)
		return false;
	if((m_Style & WISP_TWS_POS_MASK)==0)
		m_Style |= WISP_TWS_TOP;
	m_FixedTabWidth = 0;
	m_TabTailSpace = 0;
	m_pClsBTDIB = WispTKDIBList("\\Skin\\Default\\MiniClose.bmp",10,10);
	m_CloseBTSize.cx = m_CloseBTSize.cy = 10;
	if(m_Style&WISP_TWS_CLOSE_BT)
		m_TabTailSpace += m_CloseBTSize.cx;
	m_TabItemWidth = 0;
	m_FocusWndNameClr = SYS_COLOR[SC_GRADIENT_YELLOW_1];
	return true;
}

bool CWispTabWnd::OnMouseMove(IN WISP_MSG*pMsg)
{
	UINT Index=0;
	CTabWndList::IT WndIt=m_WndList.Begin();
	while(WndIt!=m_WndList.End())
	{
		if(PtInRect(&WndIt->TabRC,pMsg->MsgMouseCltPT))
		{
			m_nHoverIndex = Index;
			Update(&m_FullTabRect);
			return false;
		}
		WndIt++;
		Index++;
	}
	if(m_nHoverIndex!=-1)
	{
		Update(&m_FullTabRect);
		m_nHoverIndex = -1;
	}
	return true;
}

bool CWispTabWnd::OnMouseLeave(IN WISP_MSG*pMsg)
{
	if(m_nHoverIndex!=-1)
	{
		Update(&m_FullTabRect);
		m_nHoverIndex = -1;
	}
	return true;
}

bool CWispTabWnd::OnEventCloseBT(IN WISP_MSG*pMsg)
{
	WISP_TAB_WND_ITEM*pItem = (WISP_TAB_WND_ITEM*)pMsg->hSrcWnd->m_WndData;
	if(pItem==NULL)
		return false;
	RemoveTabWnd(pItem,(pItem->pWnd->m_AdvStyle&WISP_WAS_AUTO_DELETE)!=0);
	Update();
	return true;
}

bool CWispTabWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.bKeyDown==false)
		return true;
	switch(pMsg->KeyEvent.KeyType)
	{
	case WISP_VK_LBUTTON:
		{
			UINT Index=0;
			CTabWndList::IT WndIt=m_WndList.Begin();
			while(WndIt!=m_WndList.End())
			{
				if(PtInRect(&WndIt->TabRC,pMsg->MsgMouseCltPT))
				{
					if(Index!=m_ActiveWndIndex)
					{
						SetActiveWnd(Index);
						Update();
					}
					return true;
				}
				WndIt++;
				Index++;
			}
		}
		break;
	case WISP_VK_TAB:
		if(m_WndList.Count())
		{
			if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
				ActivePrevPage();
			else
				ActiveNextPage();
			Update();
		}
		break;
	}
	return true;
}

void CWispTabWnd::DrawTabTop()
{
	CWispRect TabRC;
	int StrLen;
	TabRC.x=TabRC.y=0;
	TabRC.cx=m_ClientRect.cx;
	TabRC.cy=m_TabSpaceHeight;
	m_pWispBase->m_pCurDrawObj->DrawTabBackground(&m_ClientDC, &TabRC);
	m_ClientDC.DrawHLine(TabRC.x, TabRC.x2(), TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BORDER_BG]);

	UINT Index=0;
	CTabWndList::IT WndIt=m_WndList.Begin();
	while(WndIt!=m_WndList.End())
	{
		StrLen = TStrLen(WndIt->Name);
		TabRC = WndIt->TabRC;
		m_ClientDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_TEXT]);
		UINT uState;
		if(Index==m_ActiveWndIndex)
			uState = STATUS_DOWN;
		else if(Index==m_nHoverIndex)
			uState = STATUS_HOVER;
		else
			uState = STATUS_NORMAL;

		switch(uState)
		{
		case STATUS_NORMAL:
			m_ClientDC.DrawVLine(TabRC.x, TabRC.y+1, TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawVLine(TabRC.x2(), TabRC.y+1, TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			TabRC.DeflateRect(1, 1);
			break;
		case STATUS_HOVER:
			m_ClientDC.DrawVLine(TabRC.x, TabRC.y+3, TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawVLine(TabRC.x2(), TabRC.y+3, TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawHLine(TabRC.x+2, TabRC.x2()-2, TabRC.y, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_1]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y+1, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_2]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y+2, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_3]);
			TabRC.x += 1;
			TabRC.cx -= 2;
			TabRC.y += 3;
			TabRC.cy -= 4;
			break;
		case STATUS_DOWN:
			m_ClientDC.DrawVLine(TabRC.x, TabRC.y+3, TabRC.y2()-3, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawVLine(TabRC.x2(), TabRC.y+3, TabRC.y2()-3, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawHLine(TabRC.x+2, TabRC.x2()-2, TabRC.y, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_1]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y+1, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_2]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y+2, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_3]);
			TabRC.x += 1;
			TabRC.cx -= 2;
			TabRC.y += 3;
			TabRC.cy -= 3;
			break;
		}
		if(uState==STATUS_DOWN)
			m_ClientDC.DrawFullRect(&TabRC, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_CLIENT_BG]);
		else
			m_ClientDC.DrawFullRect(&TabRC, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG]);

		if(WndIt->pDIB)
		{
			m_ClientDC.DrawDIB(TabRC.x + 2 ,TabRC.y+CENTER_ALGN(WndIt->pDIB->m_FrameBuffer.Height,TabRC.cy),WndIt->pDIB);
			TabRC.x+=WndIt->pDIB->m_FrameBuffer.Width;
			TabRC.cx-=WndIt->pDIB->m_FrameBuffer.Width;
		}
		TabRC.x+=4;
		TabRC.cx-=4;
		TabRC.cx-=m_TabTailSpace;
		if(m_pWispBase->m_pFocusWnd && (m_pWispBase->m_pFocusWnd == WndIt->pWnd || m_pWispBase->m_pFocusWnd->IsChildWndOf(WndIt->pWnd)))
		{
			m_ClientDC.SetTextColor(m_FocusWndNameClr);
			m_ClientDC.DrawShadowString(&TabRC,WndIt->Name);
			m_ClientDC.RestoreTextColor();
		}
		else
			m_ClientDC.DrawString(&TabRC,WndIt->Name);
		WndIt++;
		Index++;
	}
}

void CWispTabWnd::DrawTabButtom()
{
	CWispRect TabRC;
	int StrLen;
	TabRC.x=0;
	TabRC.y=m_ClientRect.cy-m_TabSpaceHeight;
	TabRC.cx=m_ClientRect.cx;
	TabRC.cy=m_TabSpaceHeight;
	m_pWispBase->m_pCurDrawObj->DrawTabBackground(&m_ClientDC, &TabRC);
	m_ClientDC.DrawHLine(TabRC.x, TabRC.x2(), TabRC.y, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BORDER_BG]);
	UINT Index=0;
	CTabWndList::IT WndIt=m_WndList.Begin();
	while(WndIt!=m_WndList.End())
	{
		StrLen = TStrLen(WndIt->Name);
		TabRC = WndIt->TabRC;
		m_ClientDC.SetTextColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_TEXT]);
		UINT uState;
		if(Index==m_ActiveWndIndex)
			uState = STATUS_DOWN;
		else if(Index==m_nHoverIndex)
			uState = STATUS_HOVER;
		else
			uState = STATUS_NORMAL;
		switch(uState)
		{
		case STATUS_NORMAL:
			m_ClientDC.DrawVLine(TabRC.x, TabRC.y, TabRC.y2()-1, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawVLine(TabRC.x2(), TabRC.y, TabRC.y2()-1, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			TabRC.DeflateRect(1,1);
			break;
		case STATUS_HOVER:
			m_ClientDC.DrawVLine(TabRC.x, TabRC.y, TabRC.y2()-3, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawVLine(TabRC.x2(), TabRC.y, TabRC.y2()-3, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawHLine(TabRC.x+2, TabRC.x2()-2, TabRC.y2()  , m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_1]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y2()-1, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_2]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y2()-2, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_3]);
			TabRC.x+=1;
			TabRC.cx-=2;
			TabRC.y+=1;
			TabRC.cy-=4;
			break;
		case STATUS_DOWN:
			m_ClientDC.DrawVLine(TabRC.x, TabRC.y, TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawVLine(TabRC.x2(), TabRC.y, TabRC.y2(), m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_BORDER_TOPLEFT]);
			m_ClientDC.DrawHLine(TabRC.x+2, TabRC.x2()-2, TabRC.y2()  , m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_1]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y2()-1, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_2]);
			m_ClientDC.DrawHLine(TabRC.x+1, TabRC.x2()-1, TabRC.y2()-2, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_GRADIENT_YELLOW_3]);
			TabRC.x+=1;
			TabRC.cx-=2;
			TabRC.cy-=3;
			break;
		}
		if(uState==STATUS_DOWN)
			m_ClientDC.DrawFullRect(&TabRC, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_CLIENT_BG]);
		else
			m_ClientDC.DrawFullRect(&TabRC, m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_NORMAL_DARK_CLIENT_BG]);
		if(WndIt->pDIB)
		{
			m_ClientDC.DrawDIB(TabRC.x + 2 ,TabRC.y+CENTER_ALGN(WndIt->pDIB->m_FrameBuffer.Height,TabRC.cy),WndIt->pDIB);
			TabRC.x+=WndIt->pDIB->m_FrameBuffer.Width;
			TabRC.cx-=WndIt->pDIB->m_FrameBuffer.Width;
		}
		TabRC.x+=4;
		TabRC.cx-=4;
		TabRC.cx-=m_TabTailSpace;
		if(m_pWispBase->m_pFocusWnd && (m_pWispBase->m_pFocusWnd == WndIt->pWnd || m_pWispBase->m_pFocusWnd->IsChildWndOf(WndIt->pWnd)))
		{
			m_ClientDC.SetTextColor(m_FocusWndNameClr);
			m_ClientDC.DrawShadowString(&TabRC,WndIt->Name);
			m_ClientDC.RestoreTextColor();
		}
		else
			m_ClientDC.DrawString(&TabRC,WndIt->Name);
		WndIt++;
		Index++;
	}
}

void CWispTabWnd::DrawTabLeft()
{

}

void CWispTabWnd::DrawTabRight()
{

}

bool CWispTabWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	if(m_WndList.Count()==0)
		CWispWnd::OnUpdateClient(pMsg);
	if((m_Style&WISP_TWS_HIDE_TAB_SINGLE) && m_WndList.Count()==1)
		return false;
	switch(m_Style & WISP_TWS_POS_MASK)
	{
	case WISP_TWS_TOP:
		DrawTabTop();
		break;
	case WISP_TWS_BUTTOM:
		DrawTabButtom();
		break;
	case WISP_TWS_LEFT:
		DrawTabLeft();
		break;
	case WISP_TWS_RIGHT:
		DrawTabRight();
		break;
	}
	return false;
}

bool CWispTabWnd::OnRecalcLayout(IN WISP_MSG*pMsg)
{
	switch(m_Style & WISP_TWS_POS_MASK)
	{
	case WISP_TWS_TOP:
		OnTopRecalcLayout();
		break;
	case WISP_TWS_BUTTOM:
		OnButtomRecalcLayout();
		break;
	case WISP_TWS_LEFT:
		OnLeftRecalcLayout();
		break;
	case WISP_TWS_RIGHT:
		OnRightRecalcLayout();
		break;
	default:
		break;
	}
	return true;
}

bool CWispTabWnd::OnGetFocus(IN WISP_MSG*pMsg)
{
	m_pWispBase->m_pFocusWnd = m_pActiveWnd;
	return true;
}

bool CWispTabWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	m_WndList.Clear();
	m_pActiveWnd=NULL;
	m_ActiveWndIndex=m_nHoverIndex=-1;
	return true;
}

bool CWispTabWnd::OnSize(IN WISP_MSG*pMsg)
{
	if(m_pActiveWnd)
	{
		if( (m_Style & WISP_TWS_POS_MASK) < WISP_TWS_LEFT )
		{
			m_pActiveWnd->Resize(m_ClientRect.cx,m_ClientRect.cy-m_TabSpaceHeight);
		}
		else
		{
			m_pActiveWnd->Resize(m_ClientRect.cx-m_TabSpaceHeight,m_ClientRect.cy);
		}
	}
	return true;
}

CWispTabWnd::CWispTabWnd()
{
	m_TabHeight=WISP_FONT_FRAME_HEIGHT;
	m_TabSpaceHeight=m_TabHeight+2;
	m_pActiveWnd=NULL;
	m_ActiveWndIndex=-1;
	m_nHoverIndex=-1;
}

void CWispTabWnd::InsertTabWnd(INOUT WISP_TAB_WND_ITEM*pTabItem,IN const WISP_CHAR*Name,IN CWispWnd*pWnd,IN CWispDIB*pTabDIB)
{
	if((m_Style&WISP_TWS_HIDE_TAB_SINGLE) && m_WndList.Count()==1)
		m_TabSpaceHeight = 0;
	else
		m_TabSpaceHeight = m_TabHeight+2;
	pTabItem->pDIB=pTabDIB;
	pTabItem->pWnd = pWnd;
	if(Name)
		TStrCpy(pTabItem->Name,Name);
	if(m_Style&WISP_TWS_CLOSE_BT)
	{
		pTabItem->pClsBT = new CWispButton;
		pTabItem->pClsBT->CreateEx(m_pClsBTDIB,0,0,this,WISP_ID_TAB_CLOSE_BT);
		pTabItem->pClsBT->AddAdvStyle(WISP_WAS_AUTO_DELETE);
		pTabItem->pClsBT->m_WndData = pTabItem;
	}
	else
	{
		pTabItem->pClsBT = NULL;
	}
	RecalcLayout();
	if(m_WndList.Count()==1)
		SetActiveWnd(0);
	else
		pTabItem->pWnd->Show(WISP_SH_HIDDEN);

	if((m_Style&WISP_TWS_CLOSE_BT) && (m_Style&WISP_TWS_MULTI_VIEW_STYLE))
	{
		if(m_WndList.Count()==1)
			GetCloseButton(0)->EnableWindow(false);
		if(m_WndList.Count()==2)
			GetCloseButton(0)->EnableWindow(true);
	}
}

void CWispTabWnd::RemoveTabWnd(WISP_TAB_WND_ITEM*pItem,bool bDestroyWnd)
{
	if(OnCloseTabWnd(pItem->pWnd)==false)
		return;
	if(pItem->pClsBT)
		pItem->pClsBT->Destroy();
	if(bDestroyWnd)
		pItem->pWnd->Destroy();
	if(pItem->pWnd==m_pActiveWnd)
	{
		m_WndList.Remove(*pItem);
		m_ActiveWndIndex = -1;
		m_pActiveWnd = NULL;
		OnClosedTabWnd();
		if(m_WndList.Count())
			SetActiveWnd(m_WndList.Count()-1);
	}
	else
	{
		m_WndList.Remove(*pItem);
		OnClosedTabWnd();
	}
	if((m_Style&WISP_TWS_CLOSE_BT) && (m_Style&WISP_TWS_MULTI_VIEW_STYLE))
	{
		if(m_WndList.Count()==1)
			GetCloseButton(0)->EnableWindow(false);
	}
	if((m_Style&WISP_TWS_HIDE_TAB_SINGLE) && m_WndList.Count()==1)
	{
		m_TabSpaceHeight = 0;
		m_ActiveWndIndex = -1;
		SetActiveWnd(0);
	}
	RecalcLayout();
	Update(&m_FullTabRect);
}

void CWispTabWnd::OnTopRecalcLayout()
{
	UINT Index;
	WISP_RECT TabRC;
	TabRC.cx=m_ClientRect.cx;
	TabRC.cy=m_pWispBase->m_Metrics[WISP_SM_FONT_FRAME_HEIGHT];
	TabRC.x=3;
	TabRC.y=m_TabSpaceHeight-TabRC.cy;
	m_FullTabRect = TabRC;
	TabRC.cy=m_TabHeight;
	m_FixedTabWidth = 0;
	if(m_Style & WISP_TWS_FIXED_WIDTH)
	{
		for(CTabWndList::IT WndIt=m_WndList.Begin();WndIt!=m_WndList.End();WndIt++)
		{
			TabRC.cx = m_ClientDC.GetTextExtent(WndIt->Name)+8;
			if(WndIt->pDIB)
				TabRC.cx+=WndIt->pDIB->m_FrameBuffer.Width+4;
			if(m_FixedTabWidth<TabRC.cx)
				m_FixedTabWidth = TabRC.cx;
		}
	}
	Index = 0;
	for(CTabWndList::IT WndIt=m_WndList.Begin();WndIt!=m_WndList.End();WndIt++)
	{
		TabRC.cx = m_ClientDC.GetTextExtent(WndIt->Name)+8+m_TabTailSpace;
		if(WndIt->pDIB)
			TabRC.cx+=WndIt->pDIB->m_FrameBuffer.Width+4;
		if(TabRC.cx<m_FixedTabWidth)
			TabRC.cx = m_FixedTabWidth;
		WndIt->TabRC = TabRC;
		if(Index==m_ActiveWndIndex)
		{
			WndIt->TabRC.y-=2;
			WndIt->TabRC.cy+=2;
			WndIt->TabRC.x-=2;
			WndIt->TabRC.cx+=4;
		}
		if(m_Style&WISP_TWS_CLOSE_BT)
			WndIt->pClsBT->MoveToClient(WndIt->TabRC.x+WndIt->TabRC.cx-WndIt->pClsBT->m_WindowRect.cx-2,WndIt->TabRC.y+CENTER_ALGN(WndIt->pClsBT->m_WindowRect.cy,m_FullTabRect.cy));
		TabRC.x += (TabRC.cx+1);
		Index++;
	}
	m_TabItemWidth = TabRC.x;
}

void CWispTabWnd::OnButtomRecalcLayout()
{
	UINT Index;
	WISP_RECT TabRC;
	TabRC.cx=m_ClientRect.cx;
	TabRC.cy=m_pWispBase->m_Metrics[WISP_SM_FONT_FRAME_HEIGHT];
	TabRC.x=3;
	TabRC.y=m_ClientRect.cy - m_TabSpaceHeight;
	m_FullTabRect = TabRC;
	TabRC.cy=m_TabHeight;
	m_FixedTabWidth = 0;
	if(m_Style&WISP_TWS_FIXED_WIDTH)
	{
		for(CTabWndList::IT WndIt=m_WndList.Begin();WndIt!=m_WndList.End();WndIt++)
		{
			TabRC.cx = m_ClientDC.GetTextExtent(WndIt->Name)+8;
			if(WndIt->pDIB)
				TabRC.cx+=WndIt->pDIB->m_FrameBuffer.Width+4;
			if(m_FixedTabWidth<TabRC.cx)
				m_FixedTabWidth = TabRC.cx;
		}
	}
	Index = 0;
	for(CTabWndList::IT WndIt=m_WndList.Begin();WndIt!=m_WndList.End();WndIt++)
	{
		TabRC.cx = m_ClientDC.GetTextExtent(WndIt->Name)+8+m_TabTailSpace;
		if(WndIt->pDIB)
			TabRC.cx+=WndIt->pDIB->m_FrameBuffer.Width+4;
		if(TabRC.cx<m_FixedTabWidth)
			TabRC.cx = m_FixedTabWidth;
		WndIt->TabRC = TabRC;
		if(Index==m_ActiveWndIndex)
		{
			WndIt->TabRC.cy+=2;
			WndIt->TabRC.x-=2;
			WndIt->TabRC.cx+=4;
		}
		if(m_Style&WISP_TWS_CLOSE_BT)
			WndIt->pClsBT->MoveToClient(WndIt->TabRC.x+WndIt->TabRC.cx-WndIt->pClsBT->m_WindowRect.cx-2,WndIt->TabRC.y+3);
		TabRC.x += (TabRC.cx+1);
		Index++;
	}
	m_TabItemWidth = TabRC.x;
}

void CWispTabWnd::OnLeftRecalcLayout()
{

}

void CWispTabWnd::OnRightRecalcLayout()
{

}

UINT CWispTabWnd::InsertWnd(IN const WISP_CHAR*Name,IN CWispWnd*pWnd,IN CWispDIB*pTabDIB)
{
	CTabWndList::IT Iter;
	Iter = m_WndList.Append();
	InsertTabWnd(&(*Iter),Name,pWnd,pTabDIB);
	return m_WndList.Count()-1;
}

UINT CWispTabWnd::InsertWndAfter(IN int Index,IN WISP_CHAR*Name,IN CWispWnd*pWnd,IN CWispDIB*pTabDIB)
{
	CTabWndList::IT Iter;
	if(Index>=m_WndList.Count())
		return -1;
	Iter = m_WndList.InsertAfter(m_WndList[Index]);
	InsertTabWnd(&(*Iter),Name,pWnd,pTabDIB);
	return Index+1;
}

UINT CWispTabWnd::InsertWndBefore(IN int Index,IN WISP_CHAR*Name,IN CWispWnd*pWnd,IN CWispDIB*pTabDIB)
{
	CTabWndList::IT Iter;
	if(Index>=m_WndList.Count())
		return -1;
	Iter = m_WndList.InsertBefore(m_WndList[Index]);
	InsertTabWnd(&(*Iter),Name,pWnd,pTabDIB);
	return Index;
}

UINT CWispTabWnd::RemoveWnd(IN int Index,bool bDestroyWnd)
{
	CTabWndList::IT WndIt;
	if(Index>=m_WndList.Count())
		return m_WndList.Count();
	WndIt=m_WndList[Index];
	RemoveTabWnd(&(*WndIt),bDestroyWnd);
	return m_WndList.Count();
}

UINT CWispTabWnd::RemoveWnd(IN CWispWnd*pWnd,bool bDestroyWnd)
{
	for(CTabWndList::IT WndIt=m_WndList.Begin();WndIt!=m_WndList.End();WndIt++)
	{
		if(pWnd==WndIt->pWnd)
		{
			RemoveTabWnd(&(*WndIt),bDestroyWnd);
			break;
		}
	}
	return m_WndList.Count();
}

CWispWnd*CWispTabWnd::GetActiveWnd()
{
	return m_pActiveWnd;
}

UINT CWispTabWnd::GetActiveWndIndex()
{
	return m_ActiveWndIndex;
}

CWispWnd*CWispTabWnd::SetActiveWnd(IN UINT Index)
{
	CTabWndList::IT WndIt;
	if(Index==m_ActiveWndIndex)
	{
		m_pActiveWnd->Focus();
		return m_pActiveWnd;
	}
	if(Index>=(UINT)m_WndList.Count())
		return NULL;
	WndIt=m_WndList[Index];
	if(WndIt==m_WndList.End())
		return NULL;		
	ChangeActiveWnd(WndIt->pWnd);
	return m_pActiveWnd;
}

void CWispTabWnd::ChangeActiveWnd(IN CWispWnd*pActiveWnd)
{
	int ActiveWndIndex=0;
	for(CTabWndList::IT It=m_WndList.Begin();It!=m_WndList.End();It++)
	{
		if(It->pWnd == pActiveWnd)
			break;
		ActiveWndIndex++;
	}
	if(ActiveWndIndex>=m_WndList.Count())
		return;
	OnTabChanged(pActiveWnd);
	if(SendCmdMsg(WISP_CMD_TAB_ACTIVE_CHG,ActiveWndIndex,pActiveWnd)==false)
		return;
	if(m_pActiveWnd)
		m_pActiveWnd->Show(WISP_SH_HIDDEN);
	m_pActiveWnd=pActiveWnd;
	switch(m_Style & WISP_TWS_POS_MASK)
	{
	case WISP_TWS_TOP:
		m_pActiveWnd->MoveToClient(0,m_TabSpaceHeight);
		m_pActiveWnd->Resize(m_ClientRect.cx,m_ClientRect.cy-m_TabSpaceHeight);
		break;
	case WISP_TWS_BUTTOM:
		m_pActiveWnd->MoveToClient(0,0);
		m_pActiveWnd->Resize(m_ClientRect.cx,m_ClientRect.cy-m_TabSpaceHeight);
		break;
	case WISP_TWS_LEFT:
		m_pActiveWnd->MoveToClient(m_TabSpaceHeight,0);
		m_pActiveWnd->Resize(m_ClientRect.cx-m_TabSpaceHeight,m_ClientRect.cy);
		break;
	case WISP_TWS_RIGHT:
		m_pActiveWnd->MoveToClient(0,0);
		m_pActiveWnd->Resize(m_ClientRect.cx-m_TabSpaceHeight,m_ClientRect.cy);
		break;
	}
	m_pActiveWnd->Focus();
	m_pActiveWnd->Show();
	m_ActiveWndIndex = ActiveWndIndex;
	RecalcLayout();
	Update();
}

CWispWnd*CWispTabWnd::GetWnd(UINT Index)
{
	if(Index>=(UINT)m_WndList.Count())
		return NULL;
	return m_WndList[Index]->pWnd;
}

bool CWispTabWnd::SetTabText(UINT Index,const WISP_CHAR*pStr)
{
	CTabWndList::IT WndIt;
	WndIt=m_WndList[Index];
	if(WndIt==m_WndList.End())
		return false;
	TStrOmit(pStr,WndIt->Name,WISP_MAX_TAB_STR);
	Update();
	return true;
}

void CWispTabWnd::ActiveNextPage()
{
	int Index = m_ActiveWndIndex+1;
	if(Index>=m_WndList.Count())
		Index=0;
	SetActiveWnd(Index);
}

void CWispTabWnd::ActivePrevPage()
{
	int Index = m_ActiveWndIndex-1;
	if(Index<0)
		Index=m_WndList.Count()-1;
	SetActiveWnd(Index);
}

UINT CWispTabWnd::GetWndCount()
{
	return (UINT)m_WndList.Count();
}

CWispButton* CWispTabWnd::GetCloseButton(int Index)
{
	if(Index>=m_WndList.Count())
		return NULL;
	CTabWndList::IT Iter = m_WndList[Index];
	if(Iter->pClsBT==NULL)
		return NULL;
	return Iter->pClsBT;
}

CWispButton* CWispTabWnd::GetCloseButton(CWispWnd*pWnd)
{
	for(CTabWndList::IT Iter=m_WndList.Begin();Iter!=m_WndList.End();Iter++)
	{
		if(Iter->pWnd==pWnd)
			return Iter->pClsBT;
	}
	return NULL;
}

void CWispTabWnd::RemoveAllWnd(bool bDestroyWnd)
{
	for(CTabWndList::IT It=m_WndList.Begin();It!=m_WndList.End();It++)
	{
		if(It->pClsBT)
			It->pClsBT->Destroy();
		if(bDestroyWnd)
			It->pWnd->Destroy();
	}
	m_WndList.Clear();
	m_pActiveWnd = NULL;
	m_ActiveWndIndex=m_nHoverIndex=-1;
}

