#include "StdAfx.h"
#include "WispWnd.h"
#include "WispBase.h"
#include "WispTipWnd.h"


WISP_MSG_MAP_BEGIN(CWispBaseWnd)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
	WISP_MSG_MAP(WISP_WM_LOST_FOCUS,OnLostFocus)
	WISP_MSG_MAP(WISP_WM_MOUSE_ENTER,OnMouseEnter)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_BEGIN_MOVE,OnBeginMove)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_TIMER,OnTimer)
WISP_BASE_WND_MSG_MAP_END

bool CWispBaseWnd::OnClose(IN WISP_MSG*pMsg)
{
	return Destroy();
}

bool CWispBaseWnd::OnGetFocus(IN WISP_MSG*pMsg)
{
	if(SendCmdMsg(WISP_CMD_CTRL_GET_FOCUS)==false)
		return false;
	Top();
	return true;
}

bool CWispBaseWnd::OnKeyEvent(WISP_MSG*pMsg)
{
	if((m_AdvStyle & WISP_WAS_HELP_TIP) && pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON && pMsg->KeyEvent.bKeyDown)
	{
		RemoveTimer(WISP_ID_HELP_TIP);
		m_pWispBase->m_pHelpTipWnd->Show(WISP_SH_HIDDEN);
		m_pWispBase->m_pHelpTipWnd->m_pTipHelpWnd = NULL;
	}
	if(m_OwnerWnd && m_OwnerWnd->m_CtrlType == WISP_CTRL_FORM)
	{
		SendCmdMsg(pMsg->KeyEvent.bKeyDown?WISP_CMD_ITEM_KEY_DOWN:WISP_CMD_ITEM_KEY_UP,(int)pMsg->KeyEvent.KeyType,this);
	}
	return true;
}

bool CWispBaseWnd::OnLostFocus(IN WISP_MSG*pMsg)
{
	return SendCmdMsg(WISP_CMD_CTRL_LOST_FOCUS,0,pMsg->hOtherWnd);
}

bool CWispBaseWnd::OnBeginMove(IN WISP_MSG*pMsg)
{
	if((m_AdvStyle & WISP_WAS_HELP_TIP) && m_pWispBase->m_pHelpTipWnd->IsWindow())
	{
		RemoveTimer(WISP_ID_HELP_TIP);
		m_pWispBase->m_pHelpTipWnd->Show(WISP_SH_HIDDEN);
		m_pWispBase->m_pHelpTipWnd->m_pTipHelpWnd = NULL;
	}
	return true;
}

bool CWispBaseWnd::OnTimer(IN WISP_MSG*pMsg)
{
	if(m_AdvStyle & WISP_WAS_HELP_TIP && pMsg->Timer.ID == WISP_ID_HELP_TIP && PtInRect(&m_ScrWindowRect,&m_pWispBase->m_MousePT))
	{
		RemoveTimer(WISP_ID_HELP_TIP);
		if(IsDisabled()==false)
		{
			m_pWispBase->m_pHelpTipWnd->SetWindowText(m_HelpTipString);
			m_pWispBase->m_pHelpTipWnd->AutoAdjustPostion(this);
			m_pWispBase->m_pHelpTipWnd->Show();
		}
	}
	return true;
}

bool CWispBaseWnd::OnMouseLeave(IN WISP_MSG*pMsg)
{
	m_pWispBase->CaptureMouseEvent((CWispBaseWnd*)pMsg->MouseEvent.hWndMouseAt);
	if(m_AdvStyle & WISP_WAS_HELP_TIP)
	{
		RemoveTimer(WISP_ID_HELP_TIP);
		m_pWispBase->m_pHelpTipWnd->Show(WISP_SH_HIDDEN);
		m_pWispBase->m_pHelpTipWnd->m_pTipHelpWnd = NULL;
	}
	return true;
}

bool CWispBaseWnd::OnMouseEnter(IN WISP_MSG*pMsg)
{
	if(m_AdvStyle & WISP_WAS_HELP_TIP)
	{
		InsertTimer(WISP_ID_HELP_TIP,WISP_TIP_PERIOD,0,NULL);
	}
	return true;
}

bool CWispBaseWnd::SendCmdMsg(UINT CmdMsg,int CmdParam1,void*CmdParam2)
{
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.hSrcWnd = this;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = CmdMsg;
	Msg.Command.CtrlType = m_CtrlType;
	Msg.Command.Param1 = CmdParam1;
	Msg.Command.Param2 = CmdParam2;
	return SEND_MSG(&Msg);
}

bool CWispBaseWnd::PostEventMsg(UINT CmdMsg,int CmdParam1,void*CmdParam2)
{
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.hSrcWnd = this;
	Msg.Msg = WISP_WM_EVENT;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = CmdMsg;
	Msg.Command.CtrlType = m_CtrlType;
	Msg.Command.Param1 = CmdParam1;
	Msg.Command.Param2 = CmdParam2;
	return POST_MSG(&Msg);
}

void CWispBaseWnd::PostCloseMsg()
{
	WISP_MSG Msg;
	Msg.hWnd = this;
	Msg.Msg = WISP_WM_CLOSE;
	POST_MSG(&Msg);
}

bool  CWispBaseWnd::SendCloseMsg()
{
	WISP_MSG Msg;
	Msg.hWnd = this;
	Msg.Msg = WISP_WM_CLOSE;
	return SEND_MSG(&Msg);
}

CWispBaseWnd::CWispBaseWnd()
{
	m_Style=0;
	m_ShowMode=WISP_SH_NULL;
	m_State=WISP_WST_INVAILD;
	m_ParentWnd = NULL;
	m_CtrlType = WISP_CTRL_BASE_WND;
	m_pUpdateRect=NULL;
	m_WndFlag = 0;
}

CWispBaseWnd::~CWispBaseWnd()
{
}

bool CWispBaseWnd::Create(	IN WISP_PCSTR Name,IN const CWispRect&Rect,IN CWispBaseWnd*pParentWnd,
							IN UINT CmdID,IN UINT Style,IN UINT ShowMode)
{
	return Create(Name,Rect.x,Rect.y,Rect.cx,Rect.cy,pParentWnd,CmdID,Style,ShowMode);
}

bool CWispBaseWnd::Create(	IN WISP_PCSTR Name,IN int x,IN int y,IN int cx,IN int cy,
							IN CWispBaseWnd*pParentWnd,IN UINT CmdID,IN UINT Style,IN UINT ShowMode)
{
	WISP_MSG Msg;
	m_pWispBase = gpCurWisp;
	CODE_ASSERT(IsWindow()==false);
	if(pParentWnd==NULL)
	{
		if(m_pWispBase->m_pRootWnd==NULL)
		{
			m_pWispBase->m_pRootWnd=(CWispWnd*)this;
			m_pWispBase->m_pMouseEventWnd=this;
			m_pWispBase->m_pFocusWnd=this;
			pParentWnd=(CWispBaseWnd*)m_pWispBase->m_pRootWnd;
			m_pWispBase->m_Metrics[WISP_SM_SCREEN_CX]=cx;
			m_pWispBase->m_Metrics[WISP_SM_SCREEN_CY]=cy;
			m_pWispBase->SetMousePos(m_pWispBase->m_FrameBuffer.Width/2,m_pWispBase->m_FrameBuffer.Height/2);
			STZeroMemory(m_pWispBase->m_LastMouseRect);
			m_pWispBase->ChangeCursorType(WISP_CT_ARROW);
			m_pWispBase->OnFrameBufferBppChg(m_pWispBase->m_FrameBuffer.Bpp);
		}
		else
			pParentWnd=(CWispBaseWnd*)m_pWispBase->m_pTopMostRootWnd;
	}
	if((CWispBaseWnd*)m_pWispBase->m_pRootWnd==this)
	{
		m_ScrWindowRect.x=x;
		m_ScrWindowRect.y=y;
	}
	else
	{
		m_ScrWindowRect.x=((CWispWnd*)pParentWnd)->m_ScrClientRect.x+x;
		m_ScrWindowRect.y=((CWispWnd*)pParentWnd)->m_ScrClientRect.y+y;
	}
	m_WindowRect.x = m_WindowRect.y = 0;
	m_WindowRect.cx = m_ScrWindowRect.cx=cx;
	m_WindowRect.cy = m_ScrWindowRect.cy=cy;
	m_Style=Style;
	m_State=WISP_WST_NORMAL;
	m_CmdID=CmdID;
	m_PrevModalWnd=m_PrevWnd=m_NextWnd=m_ChildWnd=m_ChildTopWnd=m_ParentWnd=NULL;
	m_pWispBase->InsertWnd(pParentWnd,this);
	m_OwnerWnd = m_ParentWnd;
	if(m_WindowDC.AttachWnd(this,&m_ScrWindowRect)==false)
		return false;
	if(Name)
		m_WndText = Name;
	if((m_Style & WISP_WS_ADV_WND)==0)
	{
		if(InitWnd()==false)
		{
			m_WndText.Empty();
			return false;
		}
		m_WndFlag = WISP_WND_EXIST_FLAG;
		Msg.hWnd=this;
		Msg.Msg=WISP_WM_CREATE;
		if(SEND_MSG(&Msg)==false)
		{
			Destroy();
			return false;
		}
		Show(ShowMode);
	}
	else
		m_WndFlag = WISP_WND_EXIST_FLAG;
	return true;
}

bool CWispBaseWnd::InitWnd()
{
	m_WndData = NULL;
	m_ShowMode = WISP_SH_NULL;
	m_AdvStyle = WISP_WAS_NULL;
	m_pUpdateRect = NULL;
	m_LockUpdateRef = 0;
	return true;
}

bool CWispBaseWnd::Destroy()
{
	WISP_MSG Msg;
	CWispBaseWnd*pWispWnd,*pDelWispWnd;
	if(IsWindow()==false)
		return false;
	Msg.Msg = WISP_WM_DESTROY;
	Msg.hWnd = this;
	if(SEND_MSG(&Msg)==false)
		return false;
	if(m_pWispBase->m_pMouseEventWnd==this)
		m_pWispBase->m_pMouseEventWnd=(CWispBaseWnd*)m_pWispBase->m_pRootWnd;
	pWispWnd=m_ChildWnd;
	while(pWispWnd)
	{
		pDelWispWnd=pWispWnd;
		pWispWnd=pWispWnd->m_NextWnd;
		if(pDelWispWnd->Destroy()==false)
			return false;
	}
	m_pWispBase->RemoveWndMsg(this);
	m_pWispBase->RemoveWnd(this);
	m_WindowDC.Detach();
	if(m_pWispBase->m_pFocusWnd==this)
	{
		if((CWispBaseWnd*)m_pWispBase->m_pRootWnd==this)
			m_pWispBase->m_pFocusWnd=NULL;
		else
			m_pWispBase->m_pFocusWnd=(CWispBaseWnd*)m_pWispBase->m_pRootWnd;
	}
	if(m_pWispBase->m_pModalWnd==this)
	{
		m_pWispBase->m_pModalWnd = m_PrevModalWnd;
		m_PrevModalWnd = NULL;
	}
	CTimerMap::IT Iter=m_pWispBase->m_TimerMap.Begin();
	while(Iter!=m_pWispBase->m_TimerMap.End())
	{
		if(Iter.Key().hWnd==this)
		{
			CTimerMap::IT DelIter=Iter;
			Iter++;
			m_pWispBase->m_TimerMap.Remove(DelIter);
		}
		else
		{
			Iter++;
		}
	}
	UnhookKeyEvent();
	UnhookMouseMoveEvent();
	m_WndText.Empty();
	if(m_pWispBase->m_pHelpTipWnd==this)
		m_pWispBase->m_pHelpTipWnd = NULL;
	if(	m_pWispBase->m_pHelpTipWnd &&
		m_pWispBase->m_pHelpTipWnd->m_pTipHelpWnd==this &&
		m_pWispBase->m_pHelpTipWnd->m_ShowMode != WISP_SH_HIDDEN)
	{
		m_pWispBase->m_pHelpTipWnd->Show(WISP_SH_HIDDEN);
		m_pWispBase->m_pHelpTipWnd->m_pTipHelpWnd = NULL;
	}
	if(	m_pWispBase->m_pRootWnd!=this && m_pWispBase->m_pRootWnd && m_ShowMode!=WISP_SH_HIDDEN)
	{
		m_pWispBase->m_pRootWnd->UpdateSelfAndChild(&m_ScrWindowRect,this);
		m_pWispBase->RedrawNextTime();
	}
	m_State=WISP_WST_INVAILD;
	m_WndFlag = 0;
	m_ShowMode=WISP_SH_NULL;
	if((m_Style & WISP_WS_ADV_WND)==0&&(m_AdvStyle&WISP_WAS_AUTO_DELETE))
		delete this;
	return true;
}

void CWispBaseWnd::RecalcLayout()
{
	m_WindowRect.x=m_WindowRect.y=0;
	m_WindowRect.cx=m_ScrWindowRect.cx;
	m_WindowRect.cy=m_ScrWindowRect.cy;
}

bool CWispBaseWnd::Show(IN UINT ShowMode)
{
	if(m_ShowMode==ShowMode)
		return true;
	if(m_ShowMode==WISP_SH_HIDDEN && ShowMode!=WISP_SH_HIDDEN)
		OnShow();
	m_ShowMode=ShowMode;
	if(ShowMode == WISP_SH_MODAL)
	{
		if(m_pWispBase->m_pModalWnd!=this)
		{
			m_PrevModalWnd = m_pWispBase->m_pModalWnd;
			m_pWispBase->m_pModalWnd = this;
		}
		Top();
		Update();
		return true;
	}
	else if(ShowMode == WISP_SH_MODAL_BLOCK)
	{
		if(m_pWispBase->m_pModalWnd!=this)
		{
			m_PrevModalWnd = m_pWispBase->m_pModalWnd;
			m_pWispBase->m_pModalWnd = this;
			Top();
			Update();
			m_pWispBase->BlockPump(this);
			return true;
		}
	}
	else
	{
		if(m_pWispBase->m_pModalWnd==this)
		{
			m_pWispBase->m_pModalWnd = m_PrevModalWnd;
			m_PrevModalWnd = NULL;
		}
	}
	if(m_ShowMode==WISP_SH_HIDDEN)
	{
		if(m_pWispBase->m_pMouseEventWnd==this)
		{
			WISP_MSG Msg;
			Msg.hWnd = this;
			Msg.Msg = WISP_WM_MOUSE_LEAVE;
			Msg.MouseEvent.DeltaX = Msg.MouseEvent.DeltaY = 0;
			Msg.MouseEvent.HitAreaType = WISP_HIT_WND_NON;
			Msg.MouseEvent.HitCtrlType = WISP_HIT_CTRL_NON;
			Msg.MouseEvent.hWndMouseAt = this;
			SEND_MSG(&Msg);			
		}
		OnHide();
	}
	Update();
	return true;
}

void CWispBaseWnd::Top(bool bUpdate)
{
	CWispBaseWnd*pParentWnd;
	if(m_ParentWnd ==NULL || this==m_ParentWnd)
		return;
	pParentWnd=m_ParentWnd;
	m_pWispBase->RemoveWnd(this);
	m_pWispBase->InsertWnd(pParentWnd,this);
	pParentWnd->Top(bUpdate);
	if(m_pWispBase->m_pTopMostRootWnd && 
		pParentWnd==(CWispBaseWnd*)m_pWispBase->m_pRootWnd && 
		this!=(CWispBaseWnd*)m_pWispBase->m_pTopMostRootWnd)
		m_pWispBase->m_pTopMostRootWnd->Top(bUpdate);
	if(bUpdate)
		Update();
}

void CWispBaseWnd::UpdateSelfAndChild(IN const WISP_RECT*pRect,CWispBaseWnd*pExcChildWnd)
{
	WISP_RECT UpdateRect,NewUpdateRect;
	if(pRect)
	{
		if(m_pUpdateRect)
		{
			NewUpdateRect = *pRect;
			UpdateRect = *m_pUpdateRect;
			m_pUpdateRect=&m_UpdateRect;
			MergeRect(&UpdateRect,&NewUpdateRect,m_pUpdateRect);
		}
		else
		{
			m_UpdateRect=*pRect;
			m_pUpdateRect=&m_UpdateRect;
		}
		/*@@*/
		if(m_pUpdateRect==NULL)
			return;
		if(ClipRect(m_pUpdateRect,&m_WindowRect)==false)
		{
			m_pUpdateRect=NULL;
			return;
		}
	}
	else
	{
		m_pUpdateRect=&m_WindowRect;
	}
	CWispBaseWnd*pUpdateWnd=m_ChildWnd;
	while(pUpdateWnd)
	{
		if(pUpdateWnd!=pExcChildWnd && m_pUpdateRect /*@@*/)
		{
			UpdateRect = *m_pUpdateRect;
			UpdateRect.x+=m_ScrWindowRect.x - pUpdateWnd->m_ScrWindowRect.x;
			UpdateRect.y+=m_ScrWindowRect.y - pUpdateWnd->m_ScrWindowRect.y;
			if(pUpdateWnd->m_pUpdateRect)
			{
				MergeRect(&UpdateRect,pUpdateWnd->m_pUpdateRect,&NewUpdateRect);
				pUpdateWnd->UpdateSelfAndChild(&NewUpdateRect,pExcChildWnd);
			}
			else
			{
				pUpdateWnd->UpdateSelfAndChild(&UpdateRect,pExcChildWnd);
			}
		}
		pUpdateWnd=pUpdateWnd->m_NextWnd;
	}
}

void CWispBaseWnd::Update(IN const WISP_RECT*pRect)
{
	WISP_RECT UpdateRect,NewUpdateRect;
	if(m_LockUpdateRef>0)
		return;
	UpdateSelfAndChild(pRect);
	if(m_pWispBase->m_pRootWnd && m_pWispBase->m_pRootWnd!=this && m_pUpdateRect)
	{
		UpdateRect = *m_pUpdateRect;
		UpdateRect.x+=m_ScrWindowRect.x;
		UpdateRect.y+=m_ScrWindowRect.y;
		if(m_pWispBase->m_pRootWnd->m_pUpdateRect)
		{
			MergeRect(&UpdateRect,m_pWispBase->m_pRootWnd->m_pUpdateRect,&NewUpdateRect);
			m_pWispBase->m_pRootWnd->UpdateSelfAndChild(&NewUpdateRect,this);
		}
		else
		{
			m_pWispBase->m_pRootWnd->UpdateSelfAndChild(&UpdateRect,this);
		}
	}
	m_pWispBase->RedrawNextTime();
}

bool CWispBaseWnd::IsScrPtIn(WISP_POINT*pPT)
{
	return PtInRect(&m_ScrWindowRect,pPT);
}

void CWispBaseWnd::Move(IN int DeltaX,IN int DeltaY,IN bool bUpdate)
{
	WISP_RECT OldRect,NewRect,UpdateRect;
	CWispBaseWnd*pChildWnd;
	WISP_MSG Msg;
	if(DeltaX==0 && DeltaY==0)
		return;
	Msg.hWnd=this;
	Msg.Msg=WISP_WM_MOVING;
	Msg.Move.DeltaX=DeltaX;
	Msg.Move.DeltaY=DeltaY;
	if(m_ParentWnd)
		OldRect = m_ScrWindowRect;
	if(SEND_MSG(&Msg)==false)
		return;
	m_ScrWindowRect.x+=DeltaX;
	m_ScrWindowRect.y+=DeltaY;
	RecalcLayout();
	pChildWnd=m_ChildWnd;
	while(pChildWnd)
	{
		pChildWnd->Move(DeltaX,DeltaY,false);
		pChildWnd=pChildWnd->m_NextWnd;
	}
	Msg.hWnd=this;
	Msg.Msg=WISP_WM_MOVE;
	Msg.Move.DeltaX=DeltaX;
	Msg.Move.DeltaY=DeltaY;
	SEND_MSG(&Msg);
	RecalcLayout();
	if(bUpdate)
	{
		if(m_ParentWnd)
		{
			NewRect = m_ScrWindowRect;
			MergeRect(&OldRect,&NewRect,&UpdateRect);
			UpdateRect.x-=m_ParentWnd->m_ScrWindowRect.x;
			UpdateRect.y-=m_ParentWnd->m_ScrWindowRect.y;
			m_ParentWnd->Update(&UpdateRect);
		}
		else
		{
			Update();
		}
	}
}

void CWispBaseWnd::MoveToWindow(IN int PosX,IN int PosY,IN bool bUpdate)
{
	if(this==(CWispBaseWnd*)m_pWispBase->m_pRootWnd)
		return;
	if(m_ParentWnd)
		Move(m_ParentWnd->m_ScrWindowRect.x+PosX-m_ScrWindowRect.x,m_ParentWnd->m_ScrWindowRect.y+PosY-m_ScrWindowRect.y,bUpdate);
	else
		Move(PosX-m_ScrWindowRect.x,PosY-m_ScrWindowRect.y,bUpdate);
}

void CWispBaseWnd::MoveToClient(IN int PosX,IN int PosY,IN bool bUpdate)
{
	if(this==(CWispWnd*)m_pWispBase->m_pRootWnd)
		return;
	if(m_ParentWnd)
		Move(((CWispWnd*)m_ParentWnd)->m_ScrClientRect.x+PosX-m_ScrWindowRect.x,((CWispWnd*)m_ParentWnd)->m_ScrClientRect.y+PosY-m_ScrWindowRect.y,bUpdate);
	else
		Move(PosX-m_ScrWindowRect.x,PosY-m_ScrWindowRect.y,bUpdate);
}

void CWispBaseWnd::MoveToScreen(IN int PosX,IN int PosY,IN bool bUpdate)
{
	if(this==(CWispWnd*)m_pWispBase->m_pRootWnd)
		return;
	Move(PosX-m_ScrWindowRect.x,PosY-m_ScrWindowRect.y,bUpdate);
}

bool CWispBaseWnd::MoveWindowToWindow(IN int x,IN int y,IN int cx,IN int cy,IN bool bUpdate)
{
	MoveToWindow(x,y,bUpdate);
	return Resize(cx,cy,bUpdate);
}

bool CWispBaseWnd::MoveWindowToWindow(IN const WISP_RECT&Rect,IN bool bUpdate)
{
	MoveToWindow(Rect.x,Rect.y,bUpdate);
	return Resize(Rect.cx,Rect.cy,bUpdate);
}

bool CWispBaseWnd::MoveWindowToClient(IN int x,IN int y,IN int cx,IN int cy,IN bool bUpdate)
{
	MoveToClient(x,y,bUpdate);
	return Resize(cx,cy,bUpdate);
}

bool CWispBaseWnd::MoveWindowToClient(IN const WISP_RECT&Rect,IN bool bUpdate)
{
	MoveToClient(Rect.x,Rect.y,bUpdate);
	return Resize(Rect.cx,Rect.cy,bUpdate);
}

bool CWispBaseWnd::Resize(IN int cx,IN int cy,IN bool bUpdate)
{
	CWispBaseWnd*pChildWnd;
	WISP_RECT OldRect,NewRect,UpdateRect;
	WISP_MSG Msg;
	if(cx==m_WindowRect.cx && cy==m_WindowRect.cy)
		return true;
	MIN_LIMIT(cx,0);
	MIN_LIMIT(cy,0);
	if(m_Style & WISP_WS_ADV_WND)
	{//当拖动窗口大小到达最大限制时，调整状态
		if(((CWispWnd*)this)->m_MaxWndSize.cx && cx>((CWispWnd*)this)->m_MaxWndSize.cx)
		{
			if(m_State&WISP_WST_SIZING)
				return false;
			cx=((CWispWnd*)this)->m_MaxWndSize.cx;
		}
		if(((CWispWnd*)this)->m_MaxWndSize.cy && cy>((CWispWnd*)this)->m_MaxWndSize.cy)
		{
			if(m_State&WISP_WST_SIZING)
				return false;
			cy=((CWispWnd*)this)->m_MaxWndSize.cy;
		}
	}
	if(cx == -1)
		cx = m_WindowRect.cx;
	if(cy == -1)
		cy = m_WindowRect.cy;
	Msg.hWnd=this;
	Msg.Msg=WISP_WM_SIZING;
	Msg.Resize.NewSize.cx=cx;
	Msg.Resize.NewSize.cy=cy;
	if(m_ParentWnd)
	{
		OldRect = m_ScrWindowRect;
		OldRect.x -= m_ParentWnd->m_ScrWindowRect.x;
		OldRect.y -= m_ParentWnd->m_ScrWindowRect.y;
	}
	Msg.Resize.NewSizeDelta.cx = cx - m_ScrWindowRect.cx;
	Msg.Resize.NewSizeDelta.cy = cy - m_ScrWindowRect.cy;

	if(SEND_MSG(&Msg)==false)
		return false;
	m_ScrWindowRect.cx=cx;
	m_ScrWindowRect.cy=cy;
	RecalcLayout();
	Msg.hWnd=this;
	Msg.Msg=WISP_WM_SIZE;
	SEND_MSG(&Msg);
	RecalcLayout();
	pChildWnd = m_ChildWnd;
	while(pChildWnd)
	{
		Msg.hWnd=pChildWnd;
		Msg.Msg=WISP_WM_PARENT_RESIZE;
		SEND_MSG(&Msg);
		pChildWnd = pChildWnd->m_NextWnd;
	}
	if(bUpdate)
	{
		if(m_ParentWnd)
		{
			NewRect = m_ScrWindowRect;
			NewRect.x -= m_ParentWnd->m_ScrWindowRect.x;
			NewRect.y -= m_ParentWnd->m_ScrWindowRect.y;
			MergeRect(&OldRect,&NewRect,&UpdateRect);
			m_ParentWnd->Update(&UpdateRect);
		}
		else
		{
			Update();
		}
	}
	return true;
}

void CWispBaseWnd::Center(CWispBaseWnd*pCenterWnd)
{
	if(pCenterWnd==NULL)
	{
		pCenterWnd = m_pWispBase->m_pRootWnd;
		MoveToScreen((pCenterWnd->m_WindowRect.cx - m_WindowRect.cx)/2,(pCenterWnd->m_WindowRect.cy - m_WindowRect.cy)/2);
	}
	else
	{
		MoveToWindow((pCenterWnd->m_WindowRect.cx - m_WindowRect.cx)/2 + pCenterWnd->m_ScrWindowRect.x,
					(pCenterWnd->m_WindowRect.cy - m_WindowRect.cy)/2 + pCenterWnd->m_ScrWindowRect.y);
	}
}

void CWispBaseWnd::SetOwner(CWispBaseWnd*pOwnerWnd)
{
	m_OwnerWnd = pOwnerWnd;
}

HANDLE CWispBaseWnd::GetTimer(UINT TimerID)
{
	WISP_TIMER_KEY Key;
	Key.hWnd = this;
	Key.ID = TimerID;
	CTimerMap::IT Iter=m_pWispBase->m_TimerMap.Find(Key);
	if(Iter==m_pWispBase->m_TimerMap.End())
		return NULL;
	return &(*Iter);
}

HANDLE CWispBaseWnd::InsertTimer(UINT TimerID,int Period,UINT UserData,void*UserPtr)
{
	if(GetTimer(TimerID))
		return NULL;
	WISP_TIMER_KEY Key;
	Key.hWnd = this;
	Key.ID = TimerID;
	CTimerMap::IT Iter = m_pWispBase->m_TimerMap.InsertUnique(Key);
	if(Iter==m_pWispBase->m_TimerMap.End())
		return NULL;
	Iter->Period = Period;
	Iter->UserData = UserData;
	Iter->UserPtr = UserPtr;
	Iter->Elapse = 0;
	if(m_pWispBase->InsertTimerNotify((WISP_TIMER*)&(*Iter))==false)
	{
		m_pWispBase->m_TimerMap.Remove(Iter);
		return NULL;
	}
	return &(*Iter);
}

bool CWispBaseWnd::RemoveTimer(UINT TimerID)
{	
	WISP_TIMER_KEY Key;
	Key.hWnd = this;
	Key.ID = TimerID;
	CTimerMap::IT Iter = m_pWispBase->m_TimerMap.Find(Key);
	if(Iter==m_pWispBase->m_TimerMap.End())
		return false;
	if(m_pWispBase->RemoveTimerNotify(&*Iter)==false)
		return false;
	m_pWispBase->m_TimerMap.Remove(Iter);
	return false;
}

bool CWispBaseWnd::RemoveTimer(HANDLE hTimer)
{
	CTimerMap::IT Iter=*(WISP_TIMER*)hTimer;
	m_pWispBase->m_TimerMap.Remove(Iter);
	return true;
}

bool CWispBaseWnd::SetTimerData(HANDLE hTimer,UINT UserData,void*UserPtr)
{
	CTimerMap::IT Iter=*(WISP_TIMER*)hTimer;
	Iter->UserData = UserData;
	Iter->UserPtr = UserPtr;
	return true;
}

bool CWispBaseWnd::SetTimerData(UINT TimerID,UINT UserData,void*UserPtr)
{
	HANDLE hTimer = GetTimer(TimerID);
	if(hTimer==NULL)
		return false;
	return SetTimerData(hTimer,UserData,UserPtr);
}

bool CWispBaseWnd::ModifyTimerPeriod(HANDLE hTimer,int Period)
{
	CTimerMap::IT Iter=*(WISP_TIMER*)hTimer;
	Iter->Period = Period;
	Iter->Elapse%=Period;
	return true;
}

bool CWispBaseWnd::ModifyTimerPeriod(UINT TimerID,int Period)
{
	HANDLE hTimer = GetTimer(TimerID);
	if(hTimer==NULL)
		return false;
	return ModifyTimerPeriod(hTimer,Period);
}

int CWispBaseWnd::MsgBox(WISP_CHAR* pText, WISP_CHAR* pCaption, UINT uType)
{
	return m_pWispBase->MsgBox(pText,pCaption,uType);
}

CWispBaseWnd*CWispBaseWnd::Focus()
{
	WISP_MSG Msg;
	CODE_ASSERT(IsWindow());
	if(m_pWispBase->m_pFocusWnd==this)
		return this;
	Msg.hWnd=this;
	Msg.hOtherWnd = m_pWispBase->m_pFocusWnd;
	Msg.Msg=WISP_WM_GET_FOCUS;
	if(SEND_MSG(&Msg))
	{
		Msg.Msg = WISP_WM_LOST_FOCUS;
		Msg.hWnd = Msg.hOtherWnd;
		Msg.hOtherWnd = this;
		if(SEND_MSG(&Msg))
			m_pWispBase->m_pFocusWnd=this;
	}
	Update();
	m_pWispBase->CaptureMouseEvent(this);
	return m_pWispBase->m_pFocusWnd;
}

bool CWispBaseWnd::IsTopMostWindow()
{
	return this==m_pWispBase->m_pTopMostRootWnd;
}

bool CWispBaseWnd::IsWindow()
{
	return m_WndFlag==WISP_WND_EXIST_FLAG;
}

bool CWispBaseWnd::IsChildWndOf(CWispBaseWnd*pParentWnd)
{
	CWispBaseWnd*pWnd = m_ParentWnd;
	while(pWnd)
	{
		if(pWnd==pParentWnd)
			return true;
		pWnd=pWnd->m_ParentWnd;
	}
	return false;
}

bool CWispBaseWnd::HookKeyEvent()
{
	for(CWndList::IT Iter = m_pWispBase->m_KeyHookWndList.Begin();Iter!=m_pWispBase->m_KeyHookWndList.End();Iter++)
	{
		if(*Iter==this)
			return false;
	}
	m_pWispBase->m_KeyHookWndList.Append(this);
	return true;
}

bool CWispBaseWnd::UnhookKeyEvent()
{
	for(CWndList::IT Iter = m_pWispBase->m_KeyHookWndList.Begin();Iter!=m_pWispBase->m_KeyHookWndList.End();Iter++)
	{
		if(*Iter==this)
		{
			m_pWispBase->m_KeyHookWndList.Remove(Iter);
			return true;
		}
	}
	return false;
}

bool CWispBaseWnd::HookMouseMoveEvent()
{
	for(CWndList::IT Iter = m_pWispBase->m_MouseMoveHookWndList.Begin();Iter!=m_pWispBase->m_MouseMoveHookWndList.End();Iter++)
	{
		if(*Iter==this)
			return false;
	}
	m_pWispBase->m_MouseMoveHookWndList.Append(this);
	return true;
}

bool CWispBaseWnd::UnhookMouseMoveEvent()
{
	for(CWndList::IT Iter = m_pWispBase->m_MouseMoveHookWndList.Begin();Iter!=m_pWispBase->m_MouseMoveHookWndList.End();Iter++)
	{
		if(*Iter==this)
		{
			m_pWispBase->m_MouseMoveHookWndList.Remove(Iter);
			return true;
		}
	}
	return false;
}

HANDLE CWispBaseWnd::RegisterHotKey(UINT EventID,UINT KeyType,UINT Modifier,UINT Style)
{
	CHotKeyList::IT Iter = m_pWispBase->m_HotKeyList.Append();
	Iter->EventID = EventID;
	Iter->KeyType = KeyType;
	Iter->Modifier = Modifier;
	Iter->Style = Style;
	Iter->hWnd = this;
	return &(*Iter);
}

bool CWispBaseWnd::UnregisterHotKey(HANDLE	hHotKey)
{
	for(CHotKeyList::IT It = m_pWispBase->m_HotKeyList.Begin();It!=m_pWispBase->m_HotKeyList.End();It++)
	{
		if(&(*It) == (WISP_HOTKEY_ITEM*)hHotKey)
		{
			m_pWispBase->m_HotKeyList.Remove(It);
			return true;
		}
	}
	return false;
}

bool CWispBaseWnd::SetWindowText(const WISP_CHAR* pString)
{
	m_WndText = pString;
	Update();
	return true;
}


bool CWispBaseWnd::EnableWindow(bool bState)
{
	bool OldState = IsEnabled();
	if(bState)
	{
		m_Style&=~WISP_WS_DISABLED;
	}
	else
	{
		m_Style|=WISP_WS_DISABLED;
		if((m_AdvStyle & WISP_WAS_HELP_TIP)&&m_pWispBase->m_pHelpTipWnd->m_pTipHelpWnd==this)
		{
			RemoveTimer(WISP_ID_HELP_TIP);
			m_pWispBase->m_pHelpTipWnd->Show(WISP_SH_HIDDEN);
			m_pWispBase->m_pHelpTipWnd->m_pTipHelpWnd = NULL;
		}
	}
	RecalcLayout();
	if(OldState!=bState)
		Update();
	return OldState;
}

bool CWispBaseWnd::EnableHelpTip(const WISP_CHAR*pString)
{
	if(pString==NULL)
		return false;
	m_HelpTipString = pString;
	m_AdvStyle|=WISP_WAS_HELP_TIP;
	return true;
}

bool CWispBaseWnd::DisableHelpTip()
{
	m_HelpTipString.Empty();
	m_AdvStyle&=~WISP_WAS_HELP_TIP;
	return true;
}

bool CWispBaseWnd::IsVisible()
{
	if(IsWindow()==false)
		return false;
	return m_ShowMode!=WISP_SH_HIDDEN && (m_Style&WISP_WS_VIRTUAL)==0 && m_WindowRect.cx && m_WindowRect.cy;
}

