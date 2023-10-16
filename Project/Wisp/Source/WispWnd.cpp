#include "StdAfx.h"
#include "WispWnd.h"
#include "WispButton.h"
#include "WispTipWnd.h"

enum 
{
	WISP_HIT_SCROLL_CTRL_INC_BT = 0,
	WISP_HIT_SCROLL_CTRL_DEC_BT,
	WISP_HIT_SCROLL_CTRL_SLIDE_RECT,
	WISP_HIT_SCROLL_CTRL_SPACE_RECT,
	WISP_HIT_SCROLL_CTRL_SCROLL_RECT,
	WISP_HIT_SCROLL_CTRL_COUNT
};

enum
{
	WISP_SCROLL_CTRL_ID_PAGE_UP= 0,
	WISP_SCROLL_CTRL_ID_PAGE_DOWN,
	WISP_SCROLL_CTRL_ID_SLIDE,
	WISP_SCROLL_CTRL_ID_DEC_BT,
	WISP_SCROLL_CTRL_ID_INC_BT,
	WISP_SCROLL_CTRL_COUNT
};

UINT ScrollCtrlID[][WISP_SCROLL_CTRL_COUNT]=
{
	{
		WISP_ID_VPAGE_UP,
		WISP_ID_VPAGE_DOWN,
		WISP_ID_VSLIDE,
		WISP_ID_VSPIN_DEC,
		WISP_ID_VSPIN_INC,
	},
	{
		WISP_ID_HPAGE_UP,
		WISP_ID_HPAGE_DOWN,
		WISP_ID_HSLIDE,
		WISP_ID_HSPIN_DEC,
		WISP_ID_HSPIN_INC,
	},
};


UINT ScrollHitCtrlType[][WISP_HIT_SCROLL_CTRL_COUNT]=
{
	{
		WISP_HIT_CTRL_VERT_INC_BT,
		WISP_HIT_CTRL_VERT_DEC_BT,
		WISP_HIT_CTRL_VERT_SLIDE_RECT,
		WISP_HIT_CTRL_VERT_SPACE_RECT,
		WISP_HIT_CTRL_VERT_SCROLL_RECT,
	},
	{
		WISP_HIT_CTRL_HORZ_INC_BT,
		WISP_HIT_CTRL_HORZ_DEC_BT,
		WISP_HIT_CTRL_HORZ_SLIDE_RECT,
		WISP_HIT_CTRL_HORZ_SPACE_RECT,
		WISP_HIT_CTRL_HORZ_SCROLL_RECT,
	},
};

WISP_MSG_MAP_BEGIN(CWispWnd)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_PRECREATE,OnPrecreate)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_UPDATE,OnUpdate)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_UPDATE_CAPTION,OnUpdateCaption)
	WISP_MSG_MAP(WISP_WM_UPDATE_BORDER,OnUpdateBorder)
	WISP_MSG_MAP(WISP_WM_UPDATE_CARET,OnUpdateCaret)
	WISP_MSG_MAP(WISP_WM_UPDATE_HORZ_SCROLL,OnUpdateHorzScrollBar)
	WISP_MSG_MAP(WISP_WM_UPDATE_VERT_SCROLL,OnUpdateVertScrollBar)
	WISP_MSG_MAP(WISP_WM_SCROLL_EVENT,OnScrollEvent)
	WISP_MSG_MAP(WISP_WM_HORZ_SCROLL_MOVE,OnHorzScrollMove)
	WISP_MSG_MAP(WISP_WM_VERT_SCROLL_MOVE,OnVertScrollMove)
	WISP_MSG_MAP(WISP_WM_MOVING,OnMoving)
	WISP_MSG_MAP(WISP_WM_SIZING,OnSizing)
	WISP_MSG_MAP(WISP_WM_MOVE,OnMove)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_HIT_TEST,OnHitTest)
	WISP_MSG_MAP(WISP_WM_MOUSE_WHEEL,OnMouseWheel)
	WISP_MSG_MAP(WISP_WM_TIMER,OnTimer)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
	WISP_MSG_MAP(WISP_WM_LOST_FOCUS,OnLostFocus)
WISP_MSG_MAP_END(CWispBaseWnd)

WISP_MSG_CMD_MAP_BEGIN(CWispWnd)
	WISP_MSG_CMD_MAP(WISP_ID_CLOSE,OnCmdClose)
	WISP_MSG_CMD_MAP(WISP_ID_MAX,OnCmdMax)
	WISP_MSG_CMD_MAP(WISP_ID_MIN,OnCmdMin)
	WISP_MSG_CMD_MAP(WISP_ID_HPAGE_UP,OnCmdScrollPageUp)
	WISP_MSG_CMD_MAP(WISP_ID_HPAGE_DOWN,OnCmdScrollPageDown)
	WISP_MSG_CMD_MAP(WISP_ID_HSPIN_INC,OnCmdScrollSpinInc)
	WISP_MSG_CMD_MAP(WISP_ID_HSPIN_DEC,OnCmdScrollSpinDec)
	WISP_MSG_CMD_MAP(WISP_ID_HSLIDE,OnCmdScrollSlide)
	WISP_MSG_CMD_MAP(WISP_ID_VPAGE_UP,OnCmdScrollPageUp)
	WISP_MSG_CMD_MAP(WISP_ID_VPAGE_DOWN,OnCmdScrollPageDown)
	WISP_MSG_CMD_MAP(WISP_ID_VSPIN_INC,OnCmdScrollSpinInc)
	WISP_MSG_CMD_MAP(WISP_ID_VSPIN_DEC,OnCmdScrollSpinDec)
	WISP_MSG_CMD_MAP(WISP_ID_VSLIDE,OnCmdScrollSlide)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CWispWnd)
WISP_MSG_EVENT_MAP_END


bool CWispWnd::OnPrecreate(IN WISP_MSG*pMsg)
{
	if(m_pWispBase->m_pRootWnd==this)
	{
		m_pWispBase->m_pTopMostRootWnd=new CWispWnd;
		m_pWispBase->m_pTopMostRootWnd->Create(NULL,m_WindowRect,this,WISP_ID_TOP_MOST_ROOT,WISP_WS_VIRTUAL,WISP_SH_NORMAL);
		m_pWispBase->m_pTopMostRootWnd->m_AdvStyle |= WISP_WAS_AUTO_DELETE;
		m_pWispBase->m_pHelpTipWnd = new CWispTipWnd;
		m_pWispBase->m_pHelpTipWnd->Create(NULL,0,0,0,0,NULL,WISP_ID_HELP_TIP,WISP_WS_THIN_BORDER,WISP_SH_HIDDEN);
		m_pWispBase->m_pHelpTipWnd->m_AdvStyle |= WISP_WAS_AUTO_DELETE;
	}
	return true;
}

bool CWispWnd::OnGetFocus(IN WISP_MSG*pMsg)
{
	if(m_Caret.bEnable)
	{
		//InsertTimer(WISP_ID_CARET_BLINK_TIMER,m_Caret.BlinkTime);
	}
	return true;
}

bool CWispWnd::OnLostFocus(IN WISP_MSG*pMsg)
{
	if(m_Caret.bEnable)
	{
		//RemoveTimer(WISP_ID_CARET_BLINK_TIMER);
	}
	return true;
}

bool CWispWnd::OnTimer(IN WISP_MSG*pMsg)
{
	WISP_RECT CaretRect,*RectBak;
	if(pMsg->Timer.ID == WISP_ID_CARET_BLINK_TIMER)
	{
		CaretRect.x = m_Caret.x;
		CaretRect.y = m_Caret.y;
		CaretRect.cx = m_Caret.pDIB->Width();
		CaretRect.cy = m_Caret.pDIB->Height();
		RectBak = m_pUpdateRect;
		m_pUpdateRect = &CaretRect;
		OnUpdateCaret(pMsg);
		CaretRect.x+=m_ScrWindowRect.x;
		CaretRect.y+=m_ScrWindowRect.y;
		m_pWispBase->EndDraw(&CaretRect);
		m_pUpdateRect = RectBak;
	}
	return true;
}

bool CWispWnd::OnMouseWheel(IN WISP_MSG*pMsg)
{
	if(pMsg->MouseEvent.DeltaZ<0)
		SendScrollEvent(WISP_SB_VERT,WISP_SB_INC);
	else
		SendScrollEvent(WISP_SB_VERT,WISP_SB_DEC);
	return true;
}

bool CWispWnd::OnCmdClose(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg==WISP_CMD_BT_UP)
	{
		WISP_MSG Msg;
		Msg.Msg = WISP_WM_CLOSE;
		Msg.hWnd = this;
		return !SEND_MSG(&Msg);
	}
	return true;
}

bool CWispWnd::OnCmdMax(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg==WISP_CMD_BT_UP && (m_State&WISP_WST_MIN)==0)
	{
		if(m_State&WISP_WST_MAX)
		{
			MoveToScreen(m_NormalRect.x,m_NormalRect.y);
			Resize(m_NormalRect.cx,m_NormalRect.cy);
			m_State&=~WISP_WST_MAX;
			Update();
		}
		else
		{
			if(m_ParentWnd)
			{
				m_NormalRect=m_ScrWindowRect;
				MoveToWindow(0,0);
				Resize(((CWispWnd*)m_ParentWnd)->m_ClientRect.cx,((CWispWnd*)m_ParentWnd)->m_ClientRect.cy);
				m_State|=WISP_WST_MAX;
				Update();
			}
		}
	}
	return true;
}

bool CWispWnd::OnCmdMin(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg==WISP_CMD_BT_UP && (m_State&WISP_WST_MAX)==0)
	{
		if(m_State&WISP_WST_MIN)
		{
			Resize(m_NormalRect.cx,m_NormalRect.cy);
			m_State&=~WISP_WST_MIN;
			Update();
		}
		else
		{
			m_NormalRect=m_ScrWindowRect;
			Resize(m_MinWndSize.cx,m_MinWndSize.cy);
			m_State|=WISP_WST_MIN;
			Update();
		}
	}
	return true;
}

bool CWispWnd::OnCmdScrollPageUp(IN WISP_MSG*pMsg)
{
	WISP_SB_TYPE Type = (WISP_SB_TYPE)pMsg->Command.Param1;
	if(m_ScrollBar[Type] && pMsg->Command.CmdMsg==WISP_CMD_BT_DOWN)
	{
		SendScrollEvent(Type,WISP_SB_PAGE_UP);
	}
	return true;
}

bool CWispWnd::OnCmdScrollPageDown(IN WISP_MSG*pMsg)
{
	WISP_SB_TYPE Type = (WISP_SB_TYPE)pMsg->Command.Param1;
	if(m_ScrollBar[Type] && pMsg->Command.CmdMsg==WISP_CMD_BT_DOWN)
	{
		SendScrollEvent(Type,WISP_SB_PAGE_DOWN);
	}
	return true;
}

bool CWispWnd::OnCmdScrollSpinInc(IN WISP_MSG*pMsg)
{
	WISP_SB_TYPE Type = (WISP_SB_TYPE)pMsg->Command.Param1;
	if(m_ScrollBar[Type])
	{
		if(pMsg->Command.CmdMsg==WISP_CMD_BT_DOWN)
		{
			if(m_ScrollBar[Type]->BTSpinIncState != STATUS_DOWN)
			{
				m_ScrollBar[Type]->BTSpinIncState = STATUS_DOWN;
				m_pWispBase->StartMouseKeyRep(WISP_VK_LBUTTON);
			}
			SendScrollEvent(Type,WISP_SB_INC);
		}
		else
			m_ScrollBar[Type]->BTSpinIncState = STATUS_NORMAL;
	}
	return true;
}

bool CWispWnd::OnCmdScrollSpinDec(IN WISP_MSG*pMsg)
{
	WISP_SB_TYPE Type = (WISP_SB_TYPE)pMsg->Command.Param1;
	if(m_ScrollBar[Type])
	{
		if(pMsg->Command.CmdMsg==WISP_CMD_BT_DOWN)
		{
			if(m_ScrollBar[Type]->BTSpinDecState != STATUS_DOWN)
			{
				m_ScrollBar[Type]->BTSpinDecState = STATUS_DOWN;
				m_pWispBase->StartMouseKeyRep(WISP_VK_LBUTTON);
			}
			SendScrollEvent(Type,WISP_SB_DEC);
		}
		else
			m_ScrollBar[Type]->BTSpinDecState = STATUS_NORMAL;
	}
	return true;
}

bool CWispWnd::OnCmdScrollSlide(IN WISP_MSG*pMsg)
{
	WISP_SB_TYPE Type = (WISP_SB_TYPE)pMsg->Command.Param1;
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_BT_DOWN:
		if(m_ScrollBar[Type]->Style&WISP_SS_DRAGED_CHANGING)
		{
			m_ScrollBar[Type]->StartPos = m_ScrollBar[Type]->CurPos;
		}
		m_ScrollBar[Type]->State = STATUS_DOWN;
		m_pWispBase->SetMouseCaptureNotify();
		break;
	case WISP_CMD_BT_UP:
		if(m_ScrollBar[Type]->Style&WISP_SS_DRAGED_CHANGING)
		{
			WISP_MSG Msg;
			Msg.hWnd = this;
			Msg.Msg = WISP_WM_SCROLL_EVENT;
			Msg.ScrollEvent.Event = WISP_SB_POS_CHANGE;
			Msg.ScrollEvent.SBType = Type;
			Msg.ScrollEvent.CurPos = m_ScrollBar[Type]->CurPos;
			Msg.ScrollEvent.Delta = m_ScrollBar[Type]->CurPos - m_ScrollBar[Type]->StartPos;
			SEND_MSG(&Msg);
		}
		m_ScrollBar[Type]->State = STATUS_NORMAL;
		m_pWispBase->ReleaseMouseCaptureNotify();
		break;
	}
	return true;
}

CWispWnd::CWispWnd()
{
	m_crBGColor	= 0;
	m_bBGColor	= false;
	m_pBKDIB = NULL;
	m_CtrlType = WISP_CTRL_WND;
}

CWispWnd::~CWispWnd()
{
}

UINT CWispWnd::IsPointInCaptionBT(IN const WISP_POINT&ScrMousePT)
{
	WISP_POINT pt;
	if(PtInRect(&m_ScrCaptionRect,&ScrMousePT)==false)
		return WISP_ID_NULL;
	pt=ScrMousePT;
	if((m_Style & WISP_WS_CAPTION)==0)
		return WISP_ID_NULL;
	PointToRect(&pt,&m_ScrCaptionRect);	
	if((m_Style & WISP_WS_BT_CLOSE) && PtInRect(&m_CloseBTRect,&pt))
		return WISP_ID_CLOSE;
	if((m_Style & WISP_WS_BT_MAX) && PtInRect(&m_MaxBTRect,&pt))
		return WISP_ID_MAX;
	if((m_Style & WISP_WS_BT_MIN) && PtInRect(&m_MinBTRect,&pt))
		return WISP_ID_MIN;
	return WISP_ID_NULL;
}

bool CWispWnd::OnHitTest(IN WISP_MSG*pMsg)
{
	int Space;
	WISP_POINT WndPT;
	if((m_Style & WISP_WS_SIZABLE) && m_State==WISP_WST_NORMAL)
	{
		WndPT=pMsg->MsgMouseScrPT;
		PointToRect(&WndPT,&m_ScrWindowRect);
		Space = m_BorderSize+m_pWispBase->m_Metrics[WISP_SM_RESIZE_SPACE];
		if(WndPT.x<Space && WndPT.y<Space)
		{
			pMsg->HitTest.HitAreaType = WISP_HIT_WND_RESIZE_LEFT_TOP;
			return true;
		}
		if(WndPT.x>m_WindowRect.cx-Space && WndPT.y<Space)
		{
			pMsg->HitTest.HitAreaType = WISP_HIT_WND_RESIZE_RIGHT_TOP;
			return true;
		}
		if(WndPT.x<Space && WndPT.y>m_WindowRect.cy-Space)
		{
			pMsg->HitTest.HitAreaType = WISP_HIT_WND_RESIZE_LEFT_BOTTOM;
			return true;
		}
		if(WndPT.x>m_WindowRect.cx-Space && WndPT.y>m_WindowRect.cy-Space)
		{
			pMsg->HitTest.HitAreaType = WISP_HIT_WND_RESIZE_RIGHT_BOTTOM;
			return true;
		}
		if(WndPT.x<m_BorderSize)
			pMsg->HitTest.HitAreaType |= WISP_HIT_WND_RESIZE_LEFT;
		if(WndPT.y<m_BorderSize)
			pMsg->HitTest.HitAreaType |= WISP_HIT_WND_RESIZE_TOP;
		if(WndPT.x>m_WindowRect.cx-m_BorderSize)
			pMsg->HitTest.HitAreaType |= WISP_HIT_WND_RESIZE_RIGHT;
		if(WndPT.y>m_WindowRect.cy-m_BorderSize)
			pMsg->HitTest.HitAreaType |= WISP_HIT_WND_RESIZE_BOTTOM;
		if(pMsg->HitTest.HitAreaType)
			return true;
	}
	if((m_Style & WISP_WS_CAPTION ) && PtInRect(&m_ScrCaptionRect,&pMsg->MsgMouseScrPT))
	{
		if(pMsg->HitTest.bKeyDown)
		{
			UINT CapBTID=IsPointInCaptionBT(pMsg->MsgMouseScrPT);
			switch(CapBTID)
			{
			case WISP_ID_CLOSE:
				pMsg->HitTest.HitAreaType=WISP_HIT_WND_BT_CLOSE;
				m_CloseBTState = STATUS_DOWN;
				break;
			case WISP_ID_MAX:
				pMsg->HitTest.HitAreaType=WISP_HIT_WND_BT_MAX;
				m_MaxBTState = STATUS_DOWN;
				break;
			case WISP_ID_MIN:
				pMsg->HitTest.HitAreaType=WISP_HIT_WND_BT_MIN;
				m_MinBTState = STATUS_DOWN;
				break;
			default:
				pMsg->HitTest.HitAreaType=WISP_HIT_WND_MOVE;
				return true;
			}
			Update(&m_CaptionRect);
			WISP_MSG Msg;
			Msg.hWnd = this;
			Msg.Msg	= WISP_WM_COMMAND;
			Msg.Command.CtrlType= WISP_CTRL_SYS_TYPE;
			Msg.Command.CmdID	= CapBTID;
			Msg.Command.CmdMsg	= WISP_CMD_BT_DOWN;
			SEND_MSG(&Msg);
		}
		else
		{
			pMsg->HitTest.HitAreaType=WISP_HIT_WND_MOVE;
		}
		return true;
	}
	for(int Type=0;Type<WISP_SB_COUNT;Type++)
	{
		if(m_ScrollBar[Type] && m_ScrollBar[Type]->bHide==false && PtInRect(&m_ScrollBar[Type]->ScrollRect,&pMsg->MsgMouseWndPT))
		{
			pMsg->HitTest.HitAreaType = WISP_HIT_WND_NON_CLIENT;
			if(PtInRect(&m_ScrollBar[Type]->SlideRect,&pMsg->MsgMouseWndPT))
			{
				pMsg->HitTest.HitCtrlType= ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_SLIDE_RECT];
			}
			else if(PtInRect(&m_ScrollBar[Type]->SpaceRect,&pMsg->MsgMouseWndPT))
			{
				pMsg->HitTest.HitCtrlType=ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_SPACE_RECT];
			}
			else if(PtInRect(&m_ScrollBar[Type]->DecBTRect,&pMsg->MsgMouseWndPT))
			{
				pMsg->HitTest.HitCtrlType=ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_DEC_BT];
			}
			else if(PtInRect(&m_ScrollBar[Type]->IncBTRect,&pMsg->MsgMouseWndPT))
			{
				pMsg->HitTest.HitCtrlType=ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_INC_BT];
			}
			else
				pMsg->HitTest.HitCtrlType=ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_SCROLL_RECT];
			return true;
		}
	}
	if(PtInRect(&m_ScrClientRect,&pMsg->MsgMouseScrPT))
	{
		pMsg->HitTest.HitAreaType=WISP_HIT_WND_CLIENT;
	}
	else
	{
		if(	pMsg->MsgMouseScrPT.x > m_ClientRect.x+m_ClientRect.cx|| 
			pMsg->MsgMouseScrPT.y > m_ClientRect.y+m_ClientRect.cy)
			pMsg->HitTest.HitAreaType=WISP_HIT_WND_NON_CLIENT;
	}
	return true;
}

bool CWispWnd::OnSizing(IN WISP_MSG*pMsg)
{
	if(m_pWispBase->m_pRootWnd==this)
	{
		m_pWispBase->m_Metrics[WISP_SM_SCREEN_CX]=pMsg->Resize.NewSize.cx;
		m_pWispBase->m_Metrics[WISP_SM_SCREEN_CY]=pMsg->Resize.NewSize.cy;
		if(m_pWispBase->ResizingFrame(pMsg->Resize.NewSize.cx,pMsg->Resize.NewSize.cy)==false)
			return false;
	}
	return pMsg->Resize.NewSize.cx>=m_MinWndSize.cx && pMsg->Resize.NewSize.cy>=m_MinWndSize.cy;
}

bool CWispWnd::OnMoving(IN WISP_MSG*pMsg)
{
	if(m_pWispBase->m_pRootWnd==this)
	{
		m_pWispBase->m_MousePT.x-=pMsg->Move.DeltaX;
		m_pWispBase->m_MousePT.y-=pMsg->Move.DeltaY;
		m_pWispBase->m_PrevMousePT.x-=pMsg->Move.DeltaX;
		m_pWispBase->m_PrevMousePT.y-=pMsg->Move.DeltaY;
		m_pWispBase->MoveFrame(pMsg->Move.DeltaX,pMsg->Move.DeltaY);
		return false;
	}
	return true;
}

bool CWispWnd::OnMove(IN WISP_MSG*pMsg)
{
	if(m_Style & WISP_WS_CAPTION)
		ProcessCaptionBTMouseMove(pMsg->MsgMouseScrPT);
	return true;
}

bool CWispWnd::OnSize(IN WISP_MSG*pMsg)
{
	if(m_pWispBase->m_pRootWnd==this)
	{
		if(m_State!=WISP_WST_SIZING && m_pWispBase->ResizeHostFrame(m_ClientRect.cx,m_ClientRect.cy)==false)
			return false;
		if(m_pWispBase->m_pTopMostRootWnd->Resize(m_ClientRect.cx,m_ClientRect.cy)==false)
			return false;
	}
	if(m_Style & WISP_WS_CAPTION)
		ProcessCaptionBTMouseMove(pMsg->MsgMouseScrPT);
	return true;
}


bool CWispWnd::OnHorzScrollMove(IN WISP_MSG*pMsg)
{
	if(m_ScrollBar[WISP_SB_HORZ]==NULL)
		return false;
	if(m_ScrollBar[WISP_SB_HORZ]->bHide==false)
		ProcessScrollBTSpinKey(WISP_SB_HORZ,pMsg);
	ProcessHorzScrollMouseMove(pMsg);
	return false;
}

bool CWispWnd::OnVertScrollMove(IN WISP_MSG*pMsg)
{
	if(m_ScrollBar[WISP_SB_VERT]==NULL)
		return false;
	ProcessVertScrollMouseMove(pMsg);
	return false;
}

bool CWispWnd::OnScrollEvent(IN WISP_MSG*pMsg)
{
	WISP_SB_TYPE Type = pMsg->ScrollEvent.SBType;
	WISP_SCROLL_LONG CurPos = m_ScrollBar[Type]->CurPos;
	switch(pMsg->ScrollEvent.Event)
	{
		case WISP_SB_DEC:
			m_ScrollBar[Type]->CurPos--;
			break;
		case WISP_SB_INC:
			m_ScrollBar[Type]->CurPos++;
			break;
		case WISP_SB_PAGE_UP:
			m_ScrollBar[Type]->CurPos-=m_ScrollBar[Type]->AdjustPage;
			break;
		case WISP_SB_PAGE_DOWN:
			m_ScrollBar[Type]->CurPos+=m_ScrollBar[Type]->AdjustPage;
			break;
		default:
			Update();
			return true;
	}
	LimitScrollInfo(Type,false);
	pMsg->ScrollEvent.Delta = m_ScrollBar[Type]->CurPos-CurPos;
	CalcScrollSlideWithPos(Type);
	Update();
	return true;
}

void CWispWnd::CalcScrollSlideWithPos(WISP_SB_TYPE Type)
{
	switch(Type)
	{
	case WISP_SB_HORZ:
		CalcHorzScrollSlideWithPos();
		break;
	case WISP_SB_VERT:
		CalcVertScrollSlideWithPos();
		break;
	}
}

void CWispWnd::CalcVertScrollSlideWithPos()
{
	if(m_ScrollBar[WISP_SB_VERT]==NULL)
		return;
	m_ScrollBar[WISP_SB_VERT]->DecBTRect.cx = m_ScrollBar[WISP_SB_VERT]->DecBTRect.cy = 
	m_ScrollBar[WISP_SB_VERT]->IncBTRect.cx = m_ScrollBar[WISP_SB_VERT]->IncBTRect.cy = 
	m_ScrollBar[WISP_SB_VERT]->BarSize;

	m_ScrollBar[WISP_SB_VERT]->IncBTRect.x = 
	m_ScrollBar[WISP_SB_VERT]->DecBTRect.x =
	m_ScrollBar[WISP_SB_VERT]->ScrollRect.x = m_ClientRect.x+m_ClientRect.cx;
	m_ScrollBar[WISP_SB_VERT]->DecBTRect.y =
	m_ScrollBar[WISP_SB_VERT]->ScrollRect.y = m_ClientRect.y;
	m_ScrollBar[WISP_SB_VERT]->ScrollRect.cx = m_ScrollBar[WISP_SB_VERT]->BarSize;
	m_ScrollBar[WISP_SB_VERT]->ScrollRect.cy = m_ClientRect.cy;
	m_ScrollBar[WISP_SB_VERT]->IncBTRect.y = m_ScrollBar[WISP_SB_VERT]->ScrollRect.y + m_ScrollBar[WISP_SB_VERT]->ScrollRect.cy - m_ScrollBar[WISP_SB_VERT]->IncBTRect.cy;

	m_ScrollBar[WISP_SB_VERT]->SpaceRect.x = m_ClientRect.x+m_ClientRect.cx;
	m_ScrollBar[WISP_SB_VERT]->SpaceRect.y = m_ClientRect.y+m_ScrollBar[WISP_SB_VERT]->BarSize;
	m_ScrollBar[WISP_SB_VERT]->SpaceRect.cx = m_ScrollBar[WISP_SB_VERT]->BarSize;
	m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy = m_ClientRect.cy-m_ScrollBar[WISP_SB_VERT]->BarSize*2;

	m_ScrollBar[WISP_SB_VERT]->SlideRect.x = m_ScrollBar[WISP_SB_VERT]->SpaceRect.x+1;
	m_ScrollBar[WISP_SB_VERT]->SlideRect.cx = m_ScrollBar[WISP_SB_VERT]->SpaceRect.cx-2;
	m_ScrollBar[WISP_SB_VERT]->SlideRect.y = m_ScrollBar[WISP_SB_VERT]->SpaceRect.y;
	m_ScrollBar[WISP_SB_VERT]->SlideRect.cy = m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy;

	if(m_ScrollBar[WISP_SB_VERT]->MaxPos - m_ScrollBar[WISP_SB_VERT]->MinPos)
	{
		m_ScrollBar[WISP_SB_VERT]->SlideRect.cy = (int)(m_ScrollBar[WISP_SB_VERT]->SlideRect.cy*m_ScrollBar[WISP_SB_VERT]->AdjustPage/(m_ScrollBar[WISP_SB_VERT]->MaxPos - m_ScrollBar[WISP_SB_VERT]->MinPos));
		MIN_LIMIT(m_ScrollBar[WISP_SB_VERT]->SlideRect.cy,WISP_SCROLL_MIN_SLIDE_SIZE);
		MAX_LIMIT(m_ScrollBar[WISP_SB_VERT]->SlideRect.cy,m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy);

		if(m_ScrollBar[WISP_SB_VERT]->CurPos==m_ScrollBar[WISP_SB_VERT]->MaxPos-m_ScrollBar[WISP_SB_VERT]->AdjustPage)
			m_ScrollBar[WISP_SB_VERT]->SlideRect.y+=m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy-m_ScrollBar[WISP_SB_VERT]->SlideRect.cy;
		else
			m_ScrollBar[WISP_SB_VERT]->SlideRect.y+=(int)(m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy*m_ScrollBar[WISP_SB_VERT]->CurPos/(m_ScrollBar[WISP_SB_VERT]->MaxPos - m_ScrollBar[WISP_SB_VERT]->MinPos));

		if(m_ScrollBar[WISP_SB_VERT]->SlideRect.y+m_ScrollBar[WISP_SB_VERT]->SlideRect.cy>m_ScrollBar[WISP_SB_VERT]->SpaceRect.y+m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy)
			m_ScrollBar[WISP_SB_VERT]->SlideRect.y=(int)(m_ScrollBar[WISP_SB_VERT]->SpaceRect.y+m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy-m_ScrollBar[WISP_SB_VERT]->SlideRect.cy);
	}
	else
	{
		m_ScrollBar[WISP_SB_VERT]->SlideRect.cy=m_ScrollBar[WISP_SB_VERT]->SlideRect.cx=0;
	}
}

void CWispWnd::CalcHorzScrollSlideWithPos()
{
	if(m_ScrollBar[WISP_SB_HORZ]==NULL)
		return;
	m_ScrollBar[WISP_SB_HORZ]->IncBTRect.cx = m_ScrollBar[WISP_SB_HORZ]->IncBTRect.cy =
	m_ScrollBar[WISP_SB_HORZ]->DecBTRect.cx = m_ScrollBar[WISP_SB_HORZ]->DecBTRect.cy =
	m_ScrollBar[WISP_SB_HORZ]->BarSize;

	m_ScrollBar[WISP_SB_HORZ]->DecBTRect.x =
	m_ScrollBar[WISP_SB_HORZ]->ScrollRect.x = m_ClientRect.x;
	m_ScrollBar[WISP_SB_HORZ]->IncBTRect.x = m_ScrollBar[WISP_SB_HORZ]->ScrollRect.x + m_ScrollBar[WISP_SB_HORZ]->ScrollRect.cx - m_ScrollBar[WISP_SB_HORZ]->IncBTRect.cx;

	m_ScrollBar[WISP_SB_HORZ]->IncBTRect.y =
	m_ScrollBar[WISP_SB_HORZ]->DecBTRect.y =
	m_ScrollBar[WISP_SB_HORZ]->ScrollRect.y = m_ClientRect.y+m_ClientRect.cy;
	m_ScrollBar[WISP_SB_HORZ]->ScrollRect.cx = m_ClientRect.cx;
	m_ScrollBar[WISP_SB_HORZ]->ScrollRect.cy = m_ScrollBar[WISP_SB_HORZ]->BarSize;

	m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x=m_ClientRect.x+m_ScrollBar[WISP_SB_HORZ]->BarSize;
	m_ScrollBar[WISP_SB_HORZ]->SpaceRect.y=m_ClientRect.y+m_ClientRect.cy;
	m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx=m_ClientRect.cx-m_ScrollBar[WISP_SB_HORZ]->BarSize*2;
	m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cy=m_ScrollBar[WISP_SB_HORZ]->BarSize;

	m_ScrollBar[WISP_SB_HORZ]->SlideRect.x=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x;
	m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx;

	m_ScrollBar[WISP_SB_HORZ]->SlideRect.y=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.y+1;
	m_ScrollBar[WISP_SB_HORZ]->SlideRect.cy=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cy-2;

	if(m_ScrollBar[WISP_SB_HORZ]->MaxPos - m_ScrollBar[WISP_SB_HORZ]->MinPos)
	{
		m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx=(int)(m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx*m_ScrollBar[WISP_SB_HORZ]->AdjustPage/(m_ScrollBar[WISP_SB_HORZ]->MaxPos - m_ScrollBar[WISP_SB_HORZ]->MinPos));
		MIN_LIMIT(m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx,WISP_SCROLL_MIN_SLIDE_SIZE);
		MAX_LIMIT(m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx,m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx);
		if(m_ScrollBar[WISP_SB_HORZ]->CurPos==m_ScrollBar[WISP_SB_HORZ]->MaxPos-m_ScrollBar[WISP_SB_HORZ]->AdjustPage)
			m_ScrollBar[WISP_SB_HORZ]->SlideRect.x+=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx-m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx;
		else
			m_ScrollBar[WISP_SB_HORZ]->SlideRect.x+=(int)(m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx*m_ScrollBar[WISP_SB_HORZ]->CurPos/(m_ScrollBar[WISP_SB_HORZ]->MaxPos - m_ScrollBar[WISP_SB_HORZ]->MinPos));
		if(m_ScrollBar[WISP_SB_HORZ]->SlideRect.x+m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx>m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x+m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx)
			m_ScrollBar[WISP_SB_HORZ]->SlideRect.x=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x+m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx-m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx;
	}
	else
	{
		m_ScrollBar[WISP_SB_HORZ]->SlideRect.cy=m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx=0;
	}
}

void CWispWnd::ProcessScrollBTSpinKey(IN WISP_SB_TYPE Type,IN WISP_MSG*pMsg)
{
	if(pMsg->MouseEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_DEC_BT])
	{
		if(m_ScrollBar[Type]->BTSpinDecState == STATUS_NORMAL)
		{
			m_ScrollBar[Type]->BTSpinDecState = STATUS_HOVER;
			Update(&m_ScrollBar[Type]->ScrollRect);
		}
	}
	else
	{
		if(m_ScrollBar[Type]->BTSpinDecState != STATUS_NORMAL)
		{
			m_ScrollBar[Type]->BTSpinDecState = STATUS_NORMAL;
			if(m_pWispBase->m_RepKeyIndex==WISP_VK_LBUTTON)
				m_pWispBase->StopMouseKeyRep();
			Update(&m_ScrollBar[Type]->ScrollRect);
		}
	}
	if(pMsg->MouseEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_INC_BT])
	{
		if(m_ScrollBar[Type]->BTSpinIncState == STATUS_NORMAL)
		{
			m_ScrollBar[Type]->BTSpinIncState = STATUS_HOVER;
			Update(&m_ScrollBar[Type]->ScrollRect);
		}
	}
	else
	{
		if(m_ScrollBar[Type]->BTSpinIncState != STATUS_NORMAL)
		{
			m_ScrollBar[Type]->BTSpinIncState = STATUS_NORMAL;
			if(m_pWispBase->m_RepKeyIndex==WISP_VK_LBUTTON)
				m_pWispBase->StopMouseKeyRep();
			Update(&m_ScrollBar[Type]->ScrollRect);
		}
	}
	if(pMsg->bMsgLBTDown==false && m_pWispBase->m_RepKeyIndex==WISP_VK_LBUTTON)
		m_pWispBase->m_RepKeyIndex=WISP_VK_NULL;
}

void CWispWnd::ProcessHorzScrollMouseMove(IN WISP_MSG*pMsg)
{
	WISP_SCROLL_LONG CurPos;
	if(pMsg->MsgMouseWndPT.x<m_ScrollBar[WISP_SB_HORZ]->SlideRect.x + m_ScrollBar[WISP_SB_HORZ]->HotPos && pMsg->MouseEvent.DeltaX>0)
		return;
	if(pMsg->MsgMouseWndPT.x>m_ScrollBar[WISP_SB_HORZ]->SlideRect.x + m_ScrollBar[WISP_SB_HORZ]->HotPos && pMsg->MouseEvent.DeltaX<0)
		return;
	WISP_MSG Msg;
	Msg.hWnd = this;
	Msg.Msg = WISP_WM_SCROLL_EVENT;
	Msg.ScrollEvent.Event = WISP_SB_POS_CHANGE;
	Msg.ScrollEvent.SBType = WISP_SB_HORZ;

	m_ScrollBar[WISP_SB_HORZ]->SlideRect.x+=pMsg->MouseEvent.DeltaX;
	if(m_ScrollBar[WISP_SB_HORZ]->SlideRect.x+m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx>=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x+m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx)
	{
		m_ScrollBar[WISP_SB_HORZ]->SlideRect.x=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x+m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx-m_ScrollBar[WISP_SB_HORZ]->SlideRect.cx;
		CurPos = m_ScrollBar[WISP_SB_HORZ]->MaxPos - m_ScrollBar[WISP_SB_HORZ]->AdjustPage;
	}
	else if(m_ScrollBar[WISP_SB_HORZ]->SlideRect.x<m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x)
	{
		m_ScrollBar[WISP_SB_HORZ]->SlideRect.x=m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x;
		CurPos = m_ScrollBar[WISP_SB_HORZ]->MinPos;
	}
	else 
	{
#ifdef WISP_SCROLL_LONGLONG
		CurPos = (m_ScrollBar[WISP_SB_HORZ]->SlideRect.x - m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x) * (m_ScrollBar[WISP_SB_HORZ]->MaxPos - m_ScrollBar[WISP_SB_HORZ]->MinPos) / m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx;
#else
		CurPos = (LONG)((LONGLONG)(m_ScrollBar[WISP_SB_HORZ]->SlideRect.x - m_ScrollBar[WISP_SB_HORZ]->SpaceRect.x) * (LONGLONG)(m_ScrollBar[WISP_SB_HORZ]->MaxPos - m_ScrollBar[WISP_SB_HORZ]->MinPos) / (LONGLONG)m_ScrollBar[WISP_SB_HORZ]->SpaceRect.cx);
#endif
	}	
	if(m_ScrollBar[WISP_SB_HORZ]->Style&WISP_SS_DRAGED_CHANGING)
	{
		m_ScrollBar[WISP_SB_HORZ]->CurPos = CurPos;
		Update(&m_ScrollBar[WISP_SB_HORZ]->ScrollRect);
	}
	else
	{
		Msg.ScrollEvent.Delta = CurPos - m_ScrollBar[WISP_SB_HORZ]->CurPos;
		Msg.ScrollEvent.CurPos = m_ScrollBar[WISP_SB_HORZ]->CurPos = CurPos;
		SEND_MSG(&Msg);
		Update();
	}
	return;
}

void CWispWnd::ProcessVertScrollMouseMove(IN WISP_MSG*pMsg)
{
	WISP_SCROLL_LONG CurPos;
	if(pMsg->MouseEvent.DeltaY==0)
		return;
	if(pMsg->MsgMouseWndPT.y<m_ScrollBar[WISP_SB_VERT]->SlideRect.y + m_ScrollBar[WISP_SB_VERT]->HotPos && pMsg->MouseEvent.DeltaY>0)
		return;
	if(pMsg->MsgMouseWndPT.y>m_ScrollBar[WISP_SB_VERT]->SlideRect.y + m_ScrollBar[WISP_SB_VERT]->HotPos && pMsg->MouseEvent.DeltaY<0)
		return;
	WISP_MSG Msg;
	Msg.hWnd = this;
	Msg.Msg = WISP_WM_SCROLL_EVENT;
	Msg.ScrollEvent.Event = WISP_SB_POS_CHANGE;
	Msg.ScrollEvent.SBType = WISP_SB_VERT;

	m_ScrollBar[WISP_SB_VERT]->SlideRect.y+=pMsg->MouseEvent.DeltaY;
	if(m_ScrollBar[WISP_SB_VERT]->SlideRect.y+m_ScrollBar[WISP_SB_VERT]->SlideRect.cy>=m_ScrollBar[WISP_SB_VERT]->SpaceRect.y+m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy)
	{
		m_ScrollBar[WISP_SB_VERT]->SlideRect.y = m_ScrollBar[WISP_SB_VERT]->SpaceRect.y+m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy-m_ScrollBar[WISP_SB_VERT]->SlideRect.cy;
		CurPos = m_ScrollBar[WISP_SB_VERT]->MaxPos - m_ScrollBar[WISP_SB_VERT]->AdjustPage;
	}
	else if(m_ScrollBar[WISP_SB_VERT]->SlideRect.y<m_ScrollBar[WISP_SB_VERT]->SpaceRect.y)
	{
		m_ScrollBar[WISP_SB_VERT]->SlideRect.y=m_ScrollBar[WISP_SB_VERT]->SpaceRect.y;
		CurPos = m_ScrollBar[WISP_SB_VERT]->MinPos;
	}
	else
	{
#ifdef WISP_SCROLL_LONGLONG
		CurPos =(LONG)((LONGLONG)(m_ScrollBar[WISP_SB_VERT]->SlideRect.y - m_ScrollBar[WISP_SB_VERT]->SpaceRect.y)*(LONGLONG)(m_ScrollBar[WISP_SB_VERT]->MaxPos - m_ScrollBar[WISP_SB_VERT]->MinPos) / (LONGLONG)m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy);
#else
		CurPos = (m_ScrollBar[WISP_SB_VERT]->SlideRect.y - m_ScrollBar[WISP_SB_VERT]->SpaceRect.y)*(m_ScrollBar[WISP_SB_VERT]->MaxPos - m_ScrollBar[WISP_SB_VERT]->MinPos) / m_ScrollBar[WISP_SB_VERT]->SpaceRect.cy;
#endif
	}
	if(m_ScrollBar[WISP_SB_VERT]->Style&WISP_SS_DRAGED_CHANGING)
	{
		m_ScrollBar[WISP_SB_VERT]->CurPos = CurPos;
		Update(&m_ScrollBar[WISP_SB_VERT]->ScrollRect);
	}
	else
	{
		Msg.ScrollEvent.Delta = CurPos - m_ScrollBar[WISP_SB_VERT]->CurPos;		
		Msg.ScrollEvent.CurPos = m_ScrollBar[WISP_SB_VERT]->CurPos = CurPos;
		SEND_MSG(&Msg);
		Update();
	}
	return;
}

void CWispWnd::ProcessCaptionBTMouseMove(IN const WISP_POINT&ScrMousePT)
{
	WISP_POINT pt;
	pt=ScrMousePT;
	PointToRect(&pt,&m_ScrCaptionRect);
	if(m_Style & WISP_WS_BT_CLOSE)
	{
		if(PtInRect(&m_CloseBTRect,&pt))
		{
			if(m_CloseBTState==STATUS_NORMAL)
			{
				m_CloseBTState = STATUS_HOVER;
				Update(&m_CaptionRect);
			}
		}
		else
		{
			if(m_CloseBTState!=STATUS_NORMAL)
			{
				m_CloseBTState = STATUS_NORMAL;
				Update(&m_CaptionRect);
			}
		}
	}
	if(m_Style & WISP_WS_BT_MAX)
	{
		if(PtInRect(&m_MaxBTRect,&pt))
		{
			if(m_MaxBTState==STATUS_NORMAL)
			{
				m_MaxBTState = STATUS_HOVER;
				Update(&m_CaptionRect);
			}
		}
		else
		{
			if(m_MaxBTState!=STATUS_NORMAL)
			{
				m_MaxBTState = STATUS_NORMAL;
				Update(&m_CaptionRect);
			}
		}
	}
	if(m_Style & WISP_WS_BT_MIN)
	{
		if(PtInRect(&m_MinBTRect,&pt))
		{
			if(m_MinBTState==STATUS_NORMAL)
			{
				m_MinBTState = STATUS_HOVER;
				Update(&m_CaptionRect);
			}
		}
		else
		{
			if(m_MinBTState!=STATUS_NORMAL)
			{
				m_MinBTState = STATUS_NORMAL;
				Update(&m_CaptionRect);
			}
		}
	}
}

bool CWispWnd::OnMouseMove(IN WISP_MSG*pMsg)
{
	if(m_Style & WISP_WS_CAPTION)
		ProcessCaptionBTMouseMove(pMsg->MsgMouseScrPT);
	for(UINT Type = WISP_SB_START;Type < WISP_SB_COUNT ;Type++)
	{
		if(m_ScrollBar[Type] && m_ScrollBar[Type]->bHide==false)
			ProcessScrollBTSpinKey((WISP_SB_TYPE)Type,pMsg);
	}
	return true;
}

bool CWispWnd::OnMouseLeave(IN WISP_MSG*pMsg)
{
	bool Result = true;
	if(m_Style & WISP_WS_CAPTION)
		ProcessCaptionBTMouseMove(pMsg->MsgMouseScrPT);
	for(UINT Type = WISP_SB_START;Type < WISP_SB_COUNT ;Type++)
	{
		if(m_ScrollBar[Type] && m_ScrollBar[Type]->bHide==false)
		{
			ProcessScrollBTSpinKey((WISP_SB_TYPE)Type,pMsg);
			if(m_ScrollBar[Type]->State == STATUS_DOWN)
				Result = false;
		}
	}
	return Result;
}

void CWispWnd::ProcessScrollMouseKey(IN WISP_SB_TYPE Type,IN WISP_MSG*pMsg)
{
	bool bPageUp;
	WISP_MSG Msg;
	if(pMsg->KeyEvent.bKeyDown)
	{
		if(pMsg->KeyEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_DEC_BT])
		{
			Msg.hWnd = this;
			Msg.Msg	= WISP_WM_COMMAND;
			Msg.Command.CtrlType= WISP_CTRL_SYS_TYPE;
			Msg.Command.CmdID	= ScrollCtrlID[Type][WISP_SCROLL_CTRL_ID_DEC_BT];
			Msg.Command.CmdMsg	= WISP_CMD_BT_DOWN;
			Msg.Command.Param1 = (int)Type;
			SEND_MSG(&Msg);
		}
		if(pMsg->KeyEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_INC_BT])
		{
			Msg.hWnd = this;
			Msg.Msg	= WISP_WM_COMMAND;
			Msg.Command.CtrlType= WISP_CTRL_SYS_TYPE;
			Msg.Command.CmdID	= ScrollCtrlID[Type][WISP_SCROLL_CTRL_ID_INC_BT];
			Msg.Command.CmdMsg	= WISP_CMD_BT_DOWN;
			Msg.Command.Param1 = (int)Type;
			SEND_MSG(&Msg);
		}
		if(m_ScrollBar[Type] && pMsg->KeyEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_SPACE_RECT])
		{//垂直翻页
			Msg.hWnd = this;
			Msg.Msg	= WISP_WM_COMMAND;
			Msg.Command.CtrlType= WISP_CTRL_SYS_TYPE;
			bPageUp = false;
			switch(Type)
			{
			case WISP_SB_VERT:
				bPageUp = pMsg->MsgMouseWndPT.y < m_ScrollBar[WISP_SB_VERT]->SlideRect.y;
				break;
			case WISP_SB_HORZ:
				bPageUp = pMsg->MsgMouseWndPT.x < m_ScrollBar[WISP_SB_HORZ]->SlideRect.x;
				break;
			}
			Msg.Command.CmdID = bPageUp?ScrollCtrlID[Type][WISP_SCROLL_CTRL_ID_PAGE_UP]:ScrollCtrlID[Type][WISP_SCROLL_CTRL_ID_PAGE_DOWN];
			Msg.Command.CmdMsg	= WISP_CMD_BT_DOWN;
			Msg.Command.Param1 = (int)Type;
			SEND_MSG(&Msg);
		}
		if(m_ScrollBar[Type]->State!=STATUS_DOWN && pMsg->KeyEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_SLIDE_RECT])
		{//垂直滚动置位
			switch(Type)
			{
			case WISP_SB_VERT:
				m_ScrollBar[WISP_SB_VERT]->HotPos = pMsg->MsgMouseWndPT.y - m_ScrollBar[WISP_SB_VERT]->SlideRect.y;
				break;
			case WISP_SB_HORZ:
				m_ScrollBar[WISP_SB_HORZ]->HotPos = pMsg->MsgMouseWndPT.x - m_ScrollBar[WISP_SB_HORZ]->SlideRect.x;
				break;
			}
			Msg.hWnd = this;
			Msg.Msg	= WISP_WM_COMMAND;
			Msg.Command.CtrlType= WISP_CTRL_SYS_TYPE;
			Msg.Command.CmdID	= ScrollCtrlID[Type][WISP_SCROLL_CTRL_ID_SLIDE];
			Msg.Command.CmdMsg	= WISP_CMD_BT_DOWN;
			Msg.Command.Param1 = (int)Type;
			SEND_MSG(&Msg);
		}
	}
	else
	{
		if(pMsg->KeyEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_DEC_BT])
		{
			m_ScrollBar[Type]->BTSpinDecState = STATUS_HOVER;
			Update(&m_ScrollBar[Type]->ScrollRect);
		}
		if(pMsg->KeyEvent.HitCtrlType == ScrollHitCtrlType[Type][WISP_HIT_SCROLL_CTRL_INC_BT])
		{
			m_ScrollBar[Type]->BTSpinIncState = STATUS_HOVER;
			Update(&m_ScrollBar[Type]->ScrollRect);
		}
		if(m_ScrollBar[Type]->State==STATUS_DOWN)
		{
			WISP_MSG Msg;
			Msg.hWnd = this;
			Msg.Msg	= WISP_WM_COMMAND;
			Msg.Command.CtrlType= WISP_CTRL_SYS_TYPE;
			Msg.Command.CmdID	= ScrollCtrlID[Type][WISP_SCROLL_CTRL_ID_SLIDE];
			Msg.Command.CmdMsg	= WISP_CMD_BT_UP;
			Msg.Command.Param1 = (int)Type;
			SEND_MSG(&Msg);
		}
	}
}

void CWispWnd::ProcessCaptionBTMouseKeyUp(IN const WISP_POINT&ScrMousePT)
{
	bool bSendCmd;
	UINT CapBTID=IsPointInCaptionBT(ScrMousePT);

	switch(CapBTID)
	{
	case WISP_ID_CLOSE:
		bSendCmd = m_CloseBTState == STATUS_DOWN;
		m_CloseBTState = STATUS_HOVER;
		break;
	case WISP_ID_MAX:
		bSendCmd = m_MaxBTState == STATUS_DOWN;
		m_MaxBTState = STATUS_HOVER;
		break;
	case WISP_ID_MIN:
		bSendCmd = m_MinBTState == STATUS_DOWN;
		m_MinBTState = STATUS_HOVER;
		break;
	default:
		return;
	}
	Update(&m_CaptionRect);
	if(bSendCmd==false)
		return;
	WISP_MSG Msg;
	Msg.hWnd = this;
	Msg.Msg	= WISP_WM_COMMAND;
	Msg.Command.CtrlType= WISP_CTRL_SYS_TYPE;
	Msg.Command.CmdID	= CapBTID;
	Msg.Command.CmdMsg	= WISP_CMD_BT_UP;
	if(SEND_MSG(&Msg))
	{
		Msg.hWnd=this;
		Msg.Msg=WISP_WM_EVENT;
		SEND_MSG(&Msg);
	}
}

bool CWispWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	switch(pMsg->KeyEvent.KeyType)
	{
		case WISP_VK_LBUTTON:
			//处理滚动条
			for(UINT Type = WISP_SB_START;Type<WISP_SB_COUNT;Type++)
			{
				if(m_ScrollBar[Type] && m_ScrollBar[Type]->bHide==false)
					ProcessScrollMouseKey((WISP_SB_TYPE)Type,pMsg);
			}
			if(pMsg->KeyEvent.bKeyDown)
			{
			}
			else
			{
				ProcessCaptionBTMouseKeyUp(pMsg->MsgMouseScrPT);
				if(m_ScrollBar[WISP_SB_VERT] && m_ScrollBar[WISP_SB_VERT]->State==STATUS_DOWN)
					m_ScrollBar[WISP_SB_VERT]->State=STATUS_NORMAL;
				if(m_ScrollBar[WISP_SB_HORZ] && m_ScrollBar[WISP_SB_HORZ]->State==STATUS_DOWN)
					m_ScrollBar[WISP_SB_HORZ]->State=STATUS_NORMAL;
			}
			break;
		case WISP_MOD_CTRL|WISP_VK_UP:
			if(pMsg->KeyEvent.bKeyDown && m_ScrollBar[WISP_SB_VERT] && m_ScrollBar[WISP_SB_VERT]->bHide == false)
			{
				SendScrollEvent(WISP_SB_VERT,WISP_SB_DEC);
				return false;
			}
			break;
		case WISP_MOD_CTRL|WISP_VK_DOWN:
			if(pMsg->KeyEvent.bKeyDown && m_ScrollBar[WISP_SB_VERT] && m_ScrollBar[WISP_SB_VERT]->bHide == false)
			{
				SendScrollEvent(WISP_SB_VERT,WISP_SB_INC);
				return false;
			}
			break;
		case WISP_MOD_CTRL|WISP_VK_LEFT:
			if(pMsg->KeyEvent.bKeyDown && m_ScrollBar[WISP_SB_HORZ] && m_ScrollBar[WISP_SB_HORZ]->bHide == false)
			{
				SendScrollEvent(WISP_SB_HORZ,WISP_SB_DEC);
				return false;
			}
			break;
		case WISP_MOD_CTRL|WISP_VK_RIGHT:
			if(pMsg->KeyEvent.bKeyDown && m_ScrollBar[WISP_SB_HORZ] && m_ScrollBar[WISP_SB_HORZ]->bHide == false)
			{
				SendScrollEvent(WISP_SB_HORZ,WISP_SB_INC);
				return false;
			}
			break;
		case WISP_VK_PAGE_UP:
			if(pMsg->KeyEvent.bKeyDown)
				SendScrollEvent(WISP_SB_VERT,WISP_SB_PAGE_UP);
			break;
		case WISP_VK_PAGE_DOWN:
			if(pMsg->KeyEvent.bKeyDown)
				SendScrollEvent(WISP_SB_VERT,WISP_SB_PAGE_DOWN);
			break;
		default:
			break;
	}
	return true;
}

bool CWispWnd::OnUpdate(IN WISP_MSG*pMsg)
{
	WISP_MSG Msg;
	CWispBaseWnd*pUpdateWnd;
	if(m_pUpdateRect==NULL)
		return true;
	Msg.hWnd=this;

	if((m_Style & WISP_WS_VIRTUAL)==0)
	{
		if(IsRectVisible(m_pUpdateRect,&m_ClientRect))
		{
			Msg.Msg=WISP_WM_UPDATE_CLIENT;
			SEND_MSG(&Msg);
			if(m_Caret.bEnable)
			{
				Msg.Msg=WISP_WM_UPDATE_CARET;
				SEND_MSG(&Msg);
			}
		}
		if((m_Style & WISP_WS_BORDER) && m_BorderSize)
		{
			if(IsRectVisible(m_pUpdateRect,&m_WindowRect))
			{
				Msg.Msg=WISP_WM_UPDATE_BORDER;
				SEND_MSG(&Msg);
			}
		}
		if(m_ScrollBar[WISP_SB_HORZ] && m_ScrollBar[WISP_SB_HORZ]->bHide==false)
		{
			if(IsRectVisible(m_pUpdateRect,&m_ScrollBar[WISP_SB_HORZ]->ScrollRect))
			{
				Msg.Msg=WISP_WM_UPDATE_HORZ_SCROLL;
				SEND_MSG(&Msg);
			}
		}
		if(m_ScrollBar[WISP_SB_VERT] && m_ScrollBar[WISP_SB_VERT]->bHide==false)
		{
			if(IsRectVisible(m_pUpdateRect,&m_ScrollBar[WISP_SB_VERT]->ScrollRect))
			{
				Msg.Msg=WISP_WM_UPDATE_VERT_SCROLL;
				SEND_MSG(&Msg);
			}
		}
		if(m_ScrollBar[WISP_SB_HORZ] && m_ScrollBar[WISP_SB_VERT])
		{
			WISP_RECT BlankRect;
			BlankRect.x=m_ClientRect.x+m_ClientRect.cx;
			BlankRect.y=m_ClientRect.y+m_ClientRect.cy;
			BlankRect.cx=m_WindowRect.cx-BlankRect.x-m_BorderSize;
			BlankRect.cy=m_WindowRect.cy-BlankRect.y-m_BorderSize;
			m_WindowDC.DrawFullRect(&BlankRect,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BORDER_BG]);
		}
		if(m_Style & WISP_WS_CAPTION)
		{
			if(IsRectVisible(m_pUpdateRect,&m_CaptionRect))
			{
				Msg.Msg=WISP_WM_UPDATE_CAPTION;
				SEND_MSG(&Msg);
			}
		}
	}
	pUpdateWnd=m_ChildWnd;
	while(pUpdateWnd)
	{
		if(pUpdateWnd->m_ShowMode!=WISP_SH_HIDDEN)
		{
			if(pUpdateWnd->m_pUpdateRect && IsRectVisible(pUpdateWnd->m_pUpdateRect,&pUpdateWnd->m_WindowRect))
			{
				Msg.hWnd=pUpdateWnd;
				Msg.Msg=WISP_WM_UPDATE;
				SEND_MSG(&Msg);
				pUpdateWnd->m_pUpdateRect=NULL;
			}
		}
		pUpdateWnd=pUpdateWnd->m_NextWnd;
	}
	m_pUpdateRect=NULL;
	return true;
}

bool CWispWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	if(m_Style & WISP_WS_BACK_TRANS)
		return true;
	if(m_pBKDIB)
	{
		m_ClientDC.DrawDIBTiled(m_pBKDIB);
		return true;
	}
	if(m_bBGColor)
		m_WindowDC.DrawFullRect(&m_ClientRect, m_crBGColor);
	else
		m_pWispBase->m_pCurDrawObj->DrawClient(&m_WindowDC,&m_ClientRect);
	return true;
}

bool CWispWnd::OnUpdateCaption(IN WISP_MSG*pMsg)
{
	int x,y;
	WISP_RECT rc;
	m_pWispBase->m_pCurDrawObj->DrawCaption(&m_WindowDC,&m_CaptionRect);
	x=2;
	if(m_pTitleDIB)
	{
		m_CaptionDC.DrawDIB(x,CENTER_ALGN(m_pTitleDIB->m_FrameBuffer.Height,m_CaptionRect.cy),m_pTitleDIB);
		x+=m_pTitleDIB->m_FrameBuffer.Width;
	}
	x+=m_CaptionDC.m_pFont->m_Width;
	y=(m_CaptionRect.cy-m_CaptionDC.m_pFont->m_Height)/2;
	if(m_WndText.m_Length)
	{
		rc.x = x;
		rc.y = y;
		rc.cx = m_CaptionRect.cx - 60;
		rc.cy = 14;
		m_CaptionDC.DrawString(m_WndText,&rc,WISP_DT_END_ELLIPSIS|WISP_DT_SINGLELINE);
	}
	if(m_Style & WISP_WS_BT_CLOSE)
	{
		m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_CaptionDC,&m_CloseBTRect, WISP_SSI_CLOSE, m_CloseBTState);
	}
	if(m_Style & WISP_WS_BT_MAX)
	{
		m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_CaptionDC,&m_MaxBTRect,m_State&WISP_WST_MAX?WISP_SSI_RESTORE:WISP_SSI_MAXIMIZE,m_State&WISP_WST_MIN?STATUS_DISABLED:m_MaxBTState);
	}
	if(m_Style & WISP_WS_BT_MIN)
	{
		m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_CaptionDC,&m_MinBTRect,m_State&WISP_WST_MIN?WISP_SSI_RESTORE:WISP_SSI_MINIMIZE,m_State&WISP_WST_MAX?STATUS_DISABLED:m_MinBTState);
	}
	return true;
}

bool CWispWnd::OnUpdateBorder(IN WISP_MSG*pMsg)
{
	if((m_Style & WISP_WS_BORDER)==0)
		return false;
	m_pWispBase->m_pCurDrawObj->DrawBorder(&m_WindowDC,&m_WindowRect,m_BorderSize);
	return true;
}

bool CWispWnd::OnUpdateCaret(IN WISP_MSG*pMsg)
{
	if(m_Caret.pDIB==NULL)
		return false;
	if(m_pWispBase->m_pFocusWnd!=this)
		return false;
	m_ClientDC.DrawVLine(m_Caret.x  ,m_Caret.y+1,m_Caret.y+m_ClientDC.m_pFont->m_Height-2,m_crCaret);
	m_ClientDC.DrawVLine(m_Caret.x+1,m_Caret.y+1,m_Caret.y+m_ClientDC.m_pFont->m_Height-2,m_crCaret);
	return true;
}

bool CWispWnd::OnUpdateHorzScrollBar(IN WISP_MSG*pMsg)
{
	m_pWispBase->m_pCurDrawObj->DrawHorzScrollRect(&m_WindowDC,&m_ScrollBar[WISP_SB_HORZ]->SpaceRect);
	m_pWispBase->m_pCurDrawObj->DrawHorzScrollSlideRect(&m_WindowDC,&m_ScrollBar[WISP_SB_HORZ]->SlideRect);

	WISP_RECT	rc = {m_ClientRect.x, m_ClientRect.y+m_ClientRect.cy, m_ScrollBar[WISP_SB_HORZ]->BarSize, m_ScrollBar[WISP_SB_HORZ]->BarSize};
	m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_WindowDC, &rc, WISP_SSI_HORZ_DEC_SPIN, m_ScrollBar[WISP_SB_HORZ]->BTSpinDecState);
	rc.x = m_ClientRect.x+m_ClientRect.cx-m_ScrollBar[WISP_SB_HORZ]->BarSize;
	m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_WindowDC, &rc, WISP_SSI_HORZ_INC_SPIN, m_ScrollBar[WISP_SB_HORZ]->BTSpinIncState);

	return true;
}

bool CWispWnd::OnUpdateVertScrollBar(IN WISP_MSG*pMsg)
{
	m_pWispBase->m_pCurDrawObj->DrawVertScrollRect(&m_WindowDC,&m_ScrollBar[WISP_SB_VERT]->SpaceRect);
	m_pWispBase->m_pCurDrawObj->DrawVertScrollSlideRect(&m_WindowDC,&m_ScrollBar[WISP_SB_VERT]->SlideRect);

	WISP_RECT	rc = {m_ClientRect.x+m_ClientRect.cx, m_ClientRect.y, m_ScrollBar[WISP_SB_VERT]->BarSize, m_ScrollBar[WISP_SB_VERT]->BarSize};
	m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_WindowDC, &rc, WISP_SSI_VERT_DEC_SPIN, m_ScrollBar[WISP_SB_VERT]->BTSpinDecState);
	rc.y = m_ClientRect.y+m_ClientRect.cy-m_ScrollBar[WISP_SB_VERT]->BarSize;
	m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_WindowDC, &rc, WISP_SSI_VERT_INC_SPIN, m_ScrollBar[WISP_SB_VERT]->BTSpinIncState);

	return true;
}

bool CWispWnd::Create(	IN WISP_CHAR*Name,IN const CWispRect&Rect,IN CWispBaseWnd*pParentWnd,IN UINT CmdID,IN UINT Style,IN UINT ShowMode)
{
	return Create(Name,Rect.x,Rect.y,Rect.cx,Rect.cy,pParentWnd,CmdID,Style,ShowMode);
}

bool CWispWnd::Create(IN WISP_CHAR*Name,IN int x,IN int y,IN int cx,IN int cy,IN CWispBaseWnd*pParentWnd,IN UINT CmdID,IN UINT Style,IN UINT ShowMode)
{
	if(CWispBaseWnd::Create(Name,x,y,cx,cy,pParentWnd,CmdID,Style|WISP_WS_ADV_WND,ShowMode)==false)
		return false;
	if(m_ClientDC.AttachWnd(this,&m_ScrClientRect)==false)
		return false;
	if(m_CaptionDC.AttachWnd(this,&m_ScrCaptionRect)==false)
		return false;
	m_CaptionDC.SetTextColor(SYS_COLOR[SC_WHITE]);
	if(InitWnd()==false)
		return false;
	RecalcLayout();
	m_State = WISP_WST_NORMAL;
	WISP_MSG Msg;
	Msg.hWnd=this;
	Msg.Msg=WISP_WM_PRECREATE;
	if(SEND_MSG(&Msg)==false)
	{
		Destroy();
		return false;
	}
	Msg.Msg = WISP_WM_CREATE;
	if(SEND_MSG(&Msg)==false)
	{
		Destroy();
		return false;
	}
	Show(ShowMode);
	return true;
}

bool CWispWnd::Destroy()
{
	if(CWispBaseWnd::Destroy()==false)
		return false;
	m_ClientDC.Detach();
	m_CaptionDC.Detach();
	SafeDelete(m_ScrollBar[WISP_SB_VERT]);
	SafeDelete(m_ScrollBar[WISP_SB_HORZ]);
	if(m_AdvStyle & WISP_WAS_AUTO_DELETE)
		delete this;
	return true;
}

void CWispWnd::ChangeColor(IN UINT ColorID,IN COLORREF Color)
{
	if(ColorID<MAX_SYSTEM_COLOR)
		m_pWispBase->m_pCurDrawObj->m_crSystem[ColorID]=Color;
}

bool CWispWnd::AttachBKDIB(CWispDIB*pDIB)
{
	m_pBKDIB = pDIB;
	return true;
}

void CWispWnd::DetachBKDIB()
{
	m_pBKDIB = NULL;
}

bool CWispWnd::LoadBKDIB(PCSTR FileName)
{
	return AttachBKDIB(WispDIB(FileName,-1));
}

bool CWispWnd::AttachTitleDIB(CWispDIB*pDIB)
{
	m_pTitleDIB = pDIB;
	return true;
}

void CWispWnd::DetachTitleDIB()
{
	m_pTitleDIB = NULL;
}

bool CWispWnd::LoadTitleDIB(PCSTR FileName,int Index)
{
	return AttachTitleDIB(WispDIB(FileName,Index));
}

CWispBaseWnd* CWispWnd::GetChildWnd(UINT CmdID)
{
	CWispBaseWnd*pWnd = m_ChildWnd;
	while(pWnd)
	{
		if(pWnd->m_CmdID == CmdID)
			return pWnd;
		pWnd = pWnd->m_NextWnd;
	}
	return NULL;
}

void CWispWnd::RecalcMinWndSize()
{
	//计算最小窗口大小
	m_MinWndSize.cx=m_MinWndSize.cy=0;
	if(m_Style & WISP_WS_CAPTION)
	{
		m_MinWndSize.cy+=m_pWispBase->m_Metrics[WISP_SM_CAPTION_CY];
		if(m_pTitleDIB)
		{
			m_MinWndSize.cx+=m_pTitleDIB->Width()+m_CaptionDC.m_pFont->m_Width;			
		}
		if(m_WndText.m_Length)
		{
			m_MinWndSize.cx+=MIN(m_CaptionDC.GetTextExtent(m_WndText)+20,120)+m_CaptionDC.m_pFont->m_Width;
		}
	}
	if(m_Style & WISP_WS_BORDER)
	{
		m_MinWndSize.cy+=m_pWispBase->m_Metrics[WISP_SM_BORDER_SIZE]*2;
		m_MinWndSize.cx+=m_pWispBase->m_Metrics[WISP_SM_BORDER_SIZE]*2;
	}
	if(m_Style & WISP_WS_BT_CLOSE)
		m_MinWndSize.cx+=m_pWispBase->m_Metrics[WISP_SM_CAPTION_BT_SIZE];
	if(m_Style & WISP_WS_BT_MAX)
		m_MinWndSize.cx+=m_pWispBase->m_Metrics[WISP_SM_CAPTION_BT_SIZE];
	if(m_Style & WISP_WS_BT_MIN)
		m_MinWndSize.cx+=m_pWispBase->m_Metrics[WISP_SM_CAPTION_BT_SIZE];
}

void CWispWnd::RecalcLayout()
{
	CWispBaseWnd::RecalcLayout();
	RecalcMinWndSize();

	m_ClientRect.x=m_ClientRect.y=0;
	m_ClientRect.cx=m_ScrWindowRect.cx;
	m_ClientRect.cy=m_ScrWindowRect.cy;
 
	if(m_Style & WISP_WS_BORDER)
	{
		m_ClientRect.x+=m_BorderSize;
		m_ClientRect.cx-=m_BorderSize*2;
		m_ClientRect.y+=m_BorderSize;
		m_ClientRect.cy-=m_BorderSize*2;
	}

	m_CaptionRect=m_ClientRect;
	m_CaptionRect.cy=0;

	if(m_Style & WISP_WS_CAPTION)
	{
		m_ClientRect.y+=m_pWispBase->m_Metrics[WISP_SM_CAPTION_CY];
		m_ClientRect.cy-=m_pWispBase->m_Metrics[WISP_SM_CAPTION_CY];
		m_CaptionRect.cy=m_pWispBase->m_Metrics[WISP_SM_CAPTION_CY];

		if(m_Style & WISP_WS_BT_CLOSE)
		{
			m_CloseBTRect.x = m_CaptionRect.cx-WISP_CAPTION_BT_SIZE-1;
			m_CloseBTRect.y = CENTER_ALGN(WISP_CAPTION_BT_SIZE,m_CaptionRect.cy);
			m_CloseBTRect.cx = WISP_CAPTION_BT_SIZE;
			m_CloseBTRect.cy = WISP_CAPTION_BT_SIZE;
		}
		if(m_Style & WISP_WS_BT_MAX)
		{
			m_MaxBTRect.x = m_CaptionRect.cx-(WISP_CAPTION_BT_SIZE+1)*2;
			m_MaxBTRect.y = CENTER_ALGN(WISP_CAPTION_BT_SIZE,m_CaptionRect.cy);
			m_MaxBTRect.cx = WISP_CAPTION_BT_SIZE;
			m_MaxBTRect.cy = WISP_CAPTION_BT_SIZE;
		}
		if(m_Style & WISP_WS_BT_MIN)
		{
			m_MinBTRect.x = m_CaptionRect.cx-(WISP_CAPTION_BT_SIZE+1)*3;
			m_MinBTRect.y = CENTER_ALGN(WISP_CAPTION_BT_SIZE,m_CaptionRect.cy);
			m_MinBTRect.cx = WISP_CAPTION_BT_SIZE;
			m_MinBTRect.cy = WISP_CAPTION_BT_SIZE;
		}
	}

	if(m_ScrollBar[WISP_SB_VERT] && m_ScrollBar[WISP_SB_VERT]->bHide==false)
		m_ClientRect.cx-=m_ScrollBar[WISP_SB_VERT]->BarSize;
	if(m_ScrollBar[WISP_SB_HORZ] && m_ScrollBar[WISP_SB_HORZ]->bHide==false)
		m_ClientRect.cy-=m_ScrollBar[WISP_SB_HORZ]->BarSize;

	if(m_ScrollBar[WISP_SB_VERT])
		UpdateScrollBarState(WISP_SB_VERT);
	if(m_ScrollBar[WISP_SB_HORZ])
		UpdateScrollBarState(WISP_SB_HORZ);

	CalcVertScrollSlideWithPos();
	CalcHorzScrollSlideWithPos();

	m_ScrClientRect=m_ClientRect;
	m_ScrClientRect.x+=m_ScrWindowRect.x;
	m_ScrClientRect.y+=m_ScrWindowRect.y;
	m_ScrCaptionRect=m_CaptionRect;
	m_ScrCaptionRect.x+=m_ScrWindowRect.x;
	m_ScrCaptionRect.y+=m_ScrWindowRect.y;

	if(m_State!=WISP_WST_INVAILD)
	{
		WISP_MSG Msg;
		Msg.hWnd=this;
		Msg.Msg=WISP_WM_RECALCLAYOUT;
		SEND_MSG(&Msg);		
	}
}

bool CWispWnd::InitWnd()
{
	if(CWispBaseWnd::InitWnd()==false)
		return false;
	m_MaxWndSize.cx =	m_MaxWndSize.cy = 0;
	m_bInResizeArea=false;
	m_ScrollBar[WISP_SB_VERT]=m_ScrollBar[WISP_SB_HORZ]=NULL;
	m_pTitleDIB = m_pBKDIB = NULL;
	m_Caret.x=m_Caret.y=0;
	m_Caret.bEnable=false;
	m_Caret.BlinkTime=300;
	if((m_Style & WISP_WS_THIN_BORDER)==WISP_WS_THIN_BORDER)
		m_BorderSize = m_pWispBase->m_Metrics[WISP_SM_THIN_BORDER_SIZE];
	else
		m_BorderSize=(m_Style & WISP_WS_BORDER)?m_pWispBase->m_Metrics[WISP_SM_BORDER_SIZE]:0;
	m_CloseBTState=m_MaxBTState=m_MinBTState=STATUS_NORMAL;
	m_crCaret = SYS_COLOR[SC_WHITE];
	return true;
}

bool CWispWnd::SetWindowText(const WISP_CHAR* pString)
{
	if(m_Style&WISP_WS_BT_MIN)
	{
		if(CWispBaseWnd::SetWindowText(pString)==false)
			return false;
		RecalcMinWndSize();
		return true;
	}
	return CWispBaseWnd::SetWindowText(pString);
}

bool CWispWnd::CreateCaret(IN UINT ID)
{
	m_Caret.pDIB=m_pWispBase->GetDefDIB(ID);
	m_Caret.bEnable=false;
	return true;
}

bool CWispWnd::SetCaretPos(IN int x,IN int y)
{
	m_Caret.x=x;
	m_Caret.y=y;
	return true;
}

bool CWispWnd::GetCaretPos(OUT WISP_POINT*pPT)
{
	pPT->x=m_Caret.x;
	pPT->y=m_Caret.y;
	return true;
}

void CWispWnd::ShowCaret(IN bool bShow)
{
	if(m_Caret.bEnable==bShow)
		return;
	m_Caret.bEnable=bShow;
	if(m_pWispBase->m_pFocusWnd==this)
	{
		/*
		if(m_Caret.bEnable)
			InsertTimer(WISP_ID_CARET_BLINK_TIMER,m_Caret.BlinkTime);
		else
			RemoveTimer(WISP_ID_CARET_BLINK_TIMER);
		*/
	}
}

void CWispWnd::BlinkCaret(IN ULONG BlinkTime)
{
	m_Caret.BlinkTime=BlinkTime;
}

void CWispWnd::DestroyCaret()
{
	m_Caret.bEnable=false;
	m_Caret.pDIB=NULL;
}

void CWispWnd::UpdateScrollBarState(WISP_SB_TYPE Type)
{
	if(m_ScrollBar[Type]==NULL || (m_ScrollBar[Type]->Style & WISP_SS_AUTOHIDE)==0)
		return;
	if(m_ScrollBar[Type]->MaxPos-m_ScrollBar[Type]->MinPos <= m_ScrollBar[Type]->Page)
	{
		if(m_ScrollBar[Type]->bHide==false)
		{
			m_ScrollBar[Type]->bHide = true;
			RecalcLayout();
		}
	}
	else
	{
		if(m_ScrollBar[Type]->bHide)
		{
			m_ScrollBar[Type]->bHide = false;
			RecalcLayout();
		}
	}
}

bool CWispWnd::EnableScrollBar(IN WISP_SB_TYPE Type,IN bool bEnable,IN UINT Style)
{
	if(bEnable)
	{
		if(m_ScrollBar[Type])
			return false;
	}
	else
	{
		if(m_ScrollBar[Type]==NULL)
			return false;
	}
	if(m_ScrollBar[Type]==NULL)
	{
		m_ScrollBar[Type]=new WISP_SCROLL_BAR;
		ZeroMemory(m_ScrollBar[Type],sizeof(WISP_SCROLL_BAR));
		m_ScrollBar[Type]->BarSize=m_pWispBase->GetMetrics(WISP_SM_SCROLL_BAR_SIZE);
		m_ScrollBar[Type]->bHide=false;
		m_ScrollBar[Type]->State=STATUS_NORMAL;
		m_ScrollBar[Type]->BTSpinDecState = STATUS_NORMAL;
		m_ScrollBar[Type]->BTSpinIncState = STATUS_NORMAL;
		m_ScrollBar[Type]->Style = Style;
		m_ScrollBar[Type]->Page=m_ScrollBar[Type]->MaxPos=m_ScrollBar[Type]->MinPos=m_ScrollBar[Type]->CurPos=0;
		if(m_pWispBase->m_RepKeyIndex==WISP_VK_LBUTTON)
			m_pWispBase->m_RepKeyIndex=WISP_VK_NULL;
	}
	else
	{
		SafeDelete(m_ScrollBar[Type]);
	}
	RecalcLayout();
	return true;
}

void CWispWnd::LimitScrollInfo(WISP_SB_TYPE Type,bool bChgMsg)
{
	WISP_SCROLL_LONG CurPos = m_ScrollBar[Type]->CurPos;
	MIN_LIMIT(m_ScrollBar[Type]->MaxPos,m_ScrollBar[Type]->MinPos);
	m_ScrollBar[Type]->AdjustPage=MIN(m_ScrollBar[Type]->MaxPos-m_ScrollBar[Type]->MinPos,m_ScrollBar[Type]->Page);
	MIN_LIMIT(m_ScrollBar[Type]->AdjustPage,0);
	MAX_LIMIT(m_ScrollBar[Type]->CurPos,m_ScrollBar[Type]->MaxPos);
	MIN_LIMIT(m_ScrollBar[Type]->CurPos,m_ScrollBar[Type]->MinPos);
	if(m_ScrollBar[Type]->CurPos+m_ScrollBar[Type]->AdjustPage>m_ScrollBar[Type]->MaxPos)
		m_ScrollBar[Type]->CurPos=m_ScrollBar[Type]->MaxPos-m_ScrollBar[Type]->AdjustPage;
	if(bChgMsg && CurPos!=m_ScrollBar[Type]->CurPos)
	{
		WISP_MSG Msg;
		Msg.hWnd = this;
		Msg.Msg = WISP_WM_SCROLL_EVENT;
		Msg.ScrollEvent.Event = WISP_SB_POS_CHANGE;
		Msg.ScrollEvent.SBType = Type;
		Msg.ScrollEvent.Delta = m_ScrollBar[Type]->CurPos-CurPos;
		Msg.ScrollEvent.CurPos = m_ScrollBar[Type]->CurPos;
		SEND_MSG(&Msg);
	}
}

void CWispWnd::SetScrollBarInfo(IN WISP_SB_TYPE Type,IN WISP_SCROLL_LONG CurPos,IN WISP_SCROLL_LONG MaxPos,IN WISP_SCROLL_LONG Page,IN WISP_SCROLL_LONG MinPos,IN bool bChangeEvent)
{
	if(m_ScrollBar[Type]==NULL)
		return;
	m_ScrollBar[Type]->MaxPos = MaxPos;
	m_ScrollBar[Type]->MinPos = MinPos;
	m_ScrollBar[Type]->Page = Page;
	SetScrollBarCurPos(Type,CurPos,bChangeEvent);
}

void CWispWnd::SetScrollBarCurPos(IN WISP_SB_TYPE Type,IN WISP_SCROLL_LONG CurPos,IN bool bChangeEvent)
{
	if(m_ScrollBar[Type]==NULL)
		return;
	WISP_MSG Msg;
	WISP_SCROLL_LONG OldCurPos;
	Msg.hWnd = this;
	Msg.Msg = WISP_WM_SCROLL_EVENT;
	Msg.ScrollEvent.Event = WISP_SB_POS_CHANGE;
	Msg.ScrollEvent.SBType = Type;
	OldCurPos = m_ScrollBar[Type]->CurPos;
	m_ScrollBar[Type]->CurPos = CurPos;
	LimitScrollInfo(Type,false);
	Msg.ScrollEvent.Delta = m_ScrollBar[Type]->CurPos - OldCurPos;
	if(bChangeEvent && Msg.ScrollEvent.Delta!=0)
	{
		Msg.ScrollEvent.CurPos = m_ScrollBar[Type]->CurPos;
		SEND_MSG(&Msg);
	}
	CalcScrollSlideWithPos(Type);
	UpdateScrollBarState(Type);
	Update(&m_ScrollBar[Type]->ScrollRect);
}

void CWispWnd::SetScrollBarRange(IN WISP_SB_TYPE Type,IN WISP_SCROLL_LONG MaxPos,IN WISP_SCROLL_LONG MinPos)
{
	if(m_ScrollBar[Type]==NULL)
		return;
	m_ScrollBar[Type]->MaxPos = MaxPos;
	m_ScrollBar[Type]->MinPos = MinPos;
	LimitScrollInfo(Type);
	CalcScrollSlideWithPos(Type);
	UpdateScrollBarState(Type);
}

void CWispWnd::SetScrollBarPage(IN WISP_SB_TYPE Type,IN WISP_SCROLL_LONG Page)
{
	if(m_ScrollBar[Type]==NULL)
		return;
	m_ScrollBar[Type]->Page = Page;
	LimitScrollInfo(Type);
	CalcScrollSlideWithPos(Type);
	UpdateScrollBarState(Type);
}

void CWispWnd::AdjustScrollBarMaxPos(IN WISP_SB_TYPE Type,IN WISP_SCROLL_LONG Delta)
{
	if(m_ScrollBar[Type]==NULL)
		return;
	m_ScrollBar[Type]->MaxPos+=Delta;
	LimitScrollInfo(Type);
	CalcScrollSlideWithPos(Type);
	UpdateScrollBarState(Type);
}

bool CWispWnd::BeginDrag()
{
	WISP_MSG Msg;
	if(m_pWispBase->m_pDragWnd==this)
		return false;
	m_pWispBase->m_pDragWnd=this;
	m_pWispBase->m_BeginPT = m_pWispBase->m_MousePT;
	PointToRect(&m_pWispBase->m_BeginPT,&m_ScrWindowRect);

	Msg.hWnd = this;
	Msg.Msg=WISP_WM_BEGIN_DRAG;
	Msg.DragEvent.BeginMouseWndPT = m_pWispBase->m_BeginPT;
	SEND_MSG(&Msg);
	m_pWispBase->SetMouseCaptureNotify();
	return true;
}

void CWispWnd::EndDrag()
{
	WISP_MSG Msg;
	if(m_pWispBase->m_pDragWnd==NULL)
		return;
	Msg.hWnd = this;
	Msg.Msg=WISP_WM_END_DRAG;
	Msg.DragEvent.BeginMouseWndPT = m_pWispBase->m_BeginPT;
	PointToRect(&Msg.DragEvent.BeginMouseWndPT,&m_WindowRect);
	SEND_MSG(&Msg);
	m_pWispBase->ReleaseMouseCaptureNotify();
	m_pWispBase->m_pDragWnd=NULL;
}


WISP_SCROLL_LONG CWispWnd::SendScrollEvent(WISP_SB_TYPE Type,WISP_SB_EVENT_TYPE EventType)
{
	if(m_ScrollBar[Type]==NULL)
		return 0;
	WISP_MSG Msg;
	Msg.hWnd = this;
	Msg.Msg = WISP_WM_SCROLL_EVENT;
	Msg.ScrollEvent.Event = EventType;
	Msg.ScrollEvent.SBType = Type;
	Msg.ScrollEvent.CurPos = m_ScrollBar[Type]->CurPos;
	Msg.ScrollEvent.Delta = 0;
	SEND_MSG(&Msg);
	Update();
	return Msg.ScrollEvent.Delta;
}

WISP_MSG_MAP_BEGIN(CWispDIBDCWnd)
	WISP_MSG_MAP(WISP_WM_PRECREATE,OnPrecreate)
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispWnd)

CWispDIBDCWnd::CWispDIBDCWnd()
{
	m_CtrlType = WISP_CTRL_DIB_DC_WND;
}

CWispDIBDCWnd::~CWispDIBDCWnd()
{

}

bool CWispDIBDCWnd::OnPrecreate(IN WISP_MSG*pMsg)
{
	m_DIB.Create(m_ClientRect.cx,m_ClientRect.cy,WISP_DIB_BITMAP);
	ZeroMemory(m_DIB.m_FrameBuffer.Buffer,m_DIB.m_FrameBuffer.BufferSize);
	m_ClientDC.Detach();
	m_ClientDC.AttachDIB(&m_DIB);
	return true;
}

bool CWispDIBDCWnd::OnRecalcLayout(IN WISP_MSG*pMsg)
{
	m_DIB.Resize(m_ClientRect.cx,m_ClientRect.cy);
	return true;
}

bool CWispDIBDCWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	m_WindowDC.DrawDIB(m_ClientRect.x,m_ClientRect.y,&m_DIB);
	return false;
}

bool CWispDIBDCWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	m_DIB.Destroy();
	return true;
}
