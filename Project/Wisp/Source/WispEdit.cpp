#include "StdAfx.h"
#include "WispEdit.h"

WISP_MSG_MAP_BEGIN(CWispEdit)
	WISP_MSG_MAP(WISP_WM_CHAR,OnChar)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_UPDATE_BORDER,OnUpdateBorder)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent);
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_LOST_FOCUS,OnLostFocus)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_EVENT_MAP_BEGIN(CWispEdit)
	WISP_MSG_EVENT_MAP(WISP_ID_COPY,OnEventCopy)
	WISP_MSG_EVENT_MAP(WISP_ID_PASTE,OnEventPaste)
WISP_MSG_EVENT_MAP_END


bool CWispEdit::OnCreate(IN WISP_MSG*pMsg)
{
	m_crCaret = SYS_COLOR[SC_BLACK];
	return true;
}

bool CWispEdit::OnGetFocus(IN WISP_MSG* pMsg)
{
	WISP_CHAR *pData = m_WndText;
	SendCmdMsg(WISP_CMD_EN_SETFOCUS,0,pData);
	return true;
}
bool CWispEdit::OnLostFocus(IN WISP_MSG*pMsg)
{
	WISP_CHAR *pData = m_WndText;
	SendCmdMsg(WISP_CMD_EN_KILLFOCUS,0,pData);
	if(m_CurrentInputStat==SELECT_STATE)
	{
		m_CurrentInputStat=EDIT_STATE;
		m_bSelectFlag=false;
	}
	return true;
}
bool CWispEdit::OnMouseLeave(IN WISP_MSG*pMsg)
{
	if(m_CurrentInputStat==SELECT_STATE)
	{
		if(pMsg->bMsgLBTDown)
		{
			return false;
		}
		m_CurrentInputStat=EDIT_STATE;
		m_bSelectFlag=false;
		return true;
	}
	return true;
}
bool CWispEdit::OnMouseEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
		return true;
	if(pMsg->KeyEvent.bKeyDown == false)
		return OnMouseLeftButtonUp(pMsg);
	else
		return OnMouseLeftButtonDown(pMsg);
	return true;
}

bool CWispEdit::OnMouseLeftButtonUp(IN WISP_MSG*pMsg)
{
	int index;
	WISP_POINT point,CaretPosPT;
	if(m_bSelectFlag)
	{
		GetCaretPos(&CaretPosPT);
		index = GetCharIndexByPoint(pMsg->MsgMouseWndPT,point);
		if(index!=m_CurrentCaretHot)
		{
			SetCaretPos(point.x,CaretPosPT.y);
		}
		m_CurrentCaretHot=index;
		m_SelectEnd=index;				
		Update();
	}
	m_CurrentInputStat=EDIT_STATE;
	return true;
}

bool CWispEdit::OnMouseMove(IN WISP_MSG*pMsg)
{
	int index;
	WISP_POINT point,CaretPosPT;
	if(pMsg->bMsgLBTDown==false)
		return true;

	GetCaretPos(&CaretPosPT);
	index = GetCharIndexByPoint(pMsg->MsgMouseWndPT,point);
	m_SelectRect.y = CaretPosPT.y;
	if(point.x > CaretPosPT.x)
	{
		m_SelectRect.x = CaretPosPT.x;
		m_SelectRect.cx = point.x-CaretPosPT.x;
	}
	else
	{
		m_SelectRect.x = point.x;
		m_SelectRect.cx = CaretPosPT.x-point.x;
	}
	m_SelectRect.cy = 12;
	m_SelectEnd=index;

	if(m_SelectBegin!=index)
	{
		if((m_Style&WISP_ES_READONLY)==0)
			m_bSelectFlag=true;
	}
	else
	{
		m_bSelectFlag=false;
	}
	Update();
	return true;
}
bool CWispEdit::OnMouseLeftButtonDown(IN WISP_MSG*pMsg)
{
	int index;
	WISP_POINT point,CaretPosPT;
	
	if(m_bSelectFlag)
		m_bSelectFlag=false;
	GetCaretPos(&CaretPosPT);
	index = GetCharIndexByPoint(pMsg->MsgMouseWndPT,point);			
	if(index!=m_CurrentCaretHot)
	{
		SetCaretPos(point.x,CaretPosPT.y);
	}
	m_CurrentCaretHot=index;
	m_SelectBegin=index;		
	m_SelectEnd=index;
	m_CurrentInputStat=SELECT_STATE;
	Update();	
	return true;
}
int CWispEdit::GetCharIndexByPoint(WISP_POINT point,WISP_POINT& retpoint)
{
	int x,i;
	int CurCharWidth=0;
	
	x = m_CurrentShowRect.x;	
	for(i = 0; i < m_WndText.m_Length;i++)
	{
		CurCharWidth=m_ClientDC.GetTextExtent(m_WndText+i,1);
		x += CurCharWidth;
		if(x > point.x)
			break;	
	}	
	if(x > point.x)	
		retpoint.x = x-CurCharWidth;
	else
		retpoint.x = x;
	retpoint.y=point.y;
	return i;
}


bool CWispEdit::OnKeyEvent(IN WISP_MSG*pMsg)
{
	UINT key;
	WISP_MSG Msg;
	bool Down;
	if(m_Style&WISP_ES_READONLY)
		return true;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON || pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
		return OnMouseEvent(pMsg);
	Down = pMsg->KeyEvent.bKeyDown;
	if(Down)
	{
		if(SendCmdMsg(WISP_CMD_EN_INPUT_KEY_DOWN,pMsg->KeyEvent.KeyType)==false)
			return false;
	}
	else
	{
		if(SendCmdMsg(WISP_CMD_EN_INPUT_KEY_UP,pMsg->KeyEvent.KeyType)==false)
			return false;
		if(pMsg->KeyEvent.KeyType==WISP_VK_SHIFT)
		{
			m_CurrentInputStat=EDIT_STATE;
			if(m_bSelectFlag)
			{
				m_SelectEnd=m_CurrentCaretHot;				
			}
			//OutputDebugString("shift Up...\n");
			Update();			
		}
		return true;
	}
	key=pMsg->KeyEvent.KeyType;
	switch(key)
	{	
	case WISP_VK_SHIFT|WISP_MOD_SHIFT:
		if(Down)
		{
			if(m_CurrentInputStat!=SELECT_STATE)
			{
				m_CurrentInputStat=SELECT_STATE;				
				m_SelectBegin=m_CurrentCaretHot;		
				m_SelectEnd=m_CurrentCaretHot;
			}
			//OutputDebugString("shift down...\n");
		}		
		Update();
		return false;
		
	case WISP_VK_A|WISP_MOD_CTRL:		
		if(m_WndText.m_Length)
			SelectText(0,m_WndText.m_Length);
		Update();
		return false;
		
	case WISP_VK_V|WISP_MOD_CTRL:
	case WISP_MOD_CTRL|WISP_VK_INSERT:
		Msg.hWnd = this;
		Msg.Msg = WISP_WM_EVENT;
		Msg.Command.CmdID = WISP_ID_PASTE;
		POST_MSG(&Msg);
		return false;
	
	case WISP_MOD_SHIFT|WISP_VK_INSERT:
	case WISP_VK_C|WISP_MOD_CTRL:
		Msg.hWnd = this;
		Msg.Msg = WISP_WM_EVENT;
		Msg.Command.CmdID = WISP_ID_COPY;
		POST_MSG(&Msg);
		return false;
		
	case WISP_VK_LEFT|WISP_MOD_SHIFT:
	case WISP_VK_LEFT|WISP_MOD_CTRL:
	case WISP_VK_LEFT:
		if(m_pWispBase->m_KeyMap[WISP_VK_CONTROL])
			OnHomeKey(pMsg);
		else
			OnLeftKey(pMsg);
		break;
	case WISP_VK_RIGHT|WISP_MOD_SHIFT:
	case WISP_VK_RIGHT|WISP_MOD_CTRL:
	case WISP_VK_RIGHT:
		if(m_pWispBase->m_KeyMap[WISP_VK_CONTROL])
			OnEndKey(pMsg);
		else
			OnRightKey(pMsg);
		break;
	case WISP_VK_BACK:
		OnBackKey(pMsg);
		break;
	case WISP_VK_HOME|WISP_MOD_SHIFT:
		
	case WISP_VK_HOME:
		OnHomeKey(pMsg);
		break;
	case WISP_VK_END|WISP_MOD_SHIFT:

	case WISP_VK_END:
		OnEndKey(pMsg);
		break;
	case WISP_VK_DELETE:
		OnDeleteKey(pMsg);
		break;

	default:
		break;	
	}
	Update();
	return true;
}

bool CWispEdit::IsInsertChar(WISP_CHAR wch)
{
	const WISP_CHAR *pData = m_WndText;
	int nCharNum,nCurrentCharWidth,nCaretLineCharNum = 0;
	int nSelectWidth=0;
	nCurrentCharWidth = m_ClientDC.GetTextExtent(&wch,1);
	if(m_WndText.IsEmpty())
		return true;
	if(m_Style & (WISP_ES_AUTOHSCROLL | WISP_ES_HSCROLL))
		return true;
	if(m_bSelectFlag&& m_SelectBegin!=m_SelectEnd)
	{
		int a = MAX(m_SelectBegin,m_SelectEnd);
		int b = MIN(m_SelectBegin,m_SelectEnd);
		nSelectWidth = m_ClientDC.GetTextExtent(pData+b,a-b);
	}
	nCharNum = m_ClientDC.GetTextExtent(pData)-nSelectWidth;
	return ((nCharNum + nCurrentCharWidth) <= m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width);	
}

bool CWispEdit::OnChar(IN WISP_MSG*pMsg)
{
	const WISP_CHAR *pData;
	int nCurrentCharWidth,nStringWidth,nCharWidth,nCharWidth2;
	int k,l;	
	WISP_POINT point;
	WISP_CHAR nKeyValue;
	if(m_Style&WISP_ES_READONLY)
		return true;
	//if(m_CurrentInputStat==SELECT_STATE)
	///	return true;
	pData = m_WndText;
	
	nKeyValue = pMsg->Char.Char;
	if(nKeyValue == WISP_VK_BACK)
	{
		Update();
		return false;
	}
	if(nKeyValue == WISP_VK_RETURN)
	{
		Update();
		return false;
	}
	if(nKeyValue == '\n')
	{
			return false;
		if(IsInsertChar(nKeyValue))
		{
			InsertChar(&nKeyValue);
			Update();
			m_CurrentCaretHot++;
		}
	
	}
	nCurrentCharWidth = m_ClientDC.GetTextExtent(&nKeyValue,1);
	if(IsInsertChar(nKeyValue) == false)
	{
		Update();
		return false;
	}
	InsertChar(&nKeyValue);
	nCharWidth = m_ClientDC.GetTextExtent(m_WndText,m_CurrentCaretHot+1);
	nCharWidth2 = m_ClientDC.GetTextExtent(m_WndText,m_CurrentCaretHot);
	nCurrentCharWidth = nCharWidth-nCharWidth2;
	GetCaretPos(&point);
	if(m_Style & WISP_ES_LEFT)
	{			
		if(point.x + nCurrentCharWidth > m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
		{
			point.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width;
			if(m_Style & WISP_ES_AUTOHSCROLL)//×ó¶ÔÆë
			{
				if(m_CurrentCaretHot != m_WndText.m_Length)
					point.x = (m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width) / 4 * 3;					
			}
		}
		else
		{		
			point.x += nCurrentCharWidth;
		}
	}		
		
	pData=m_WndText;
	m_CurrentCaretHot++;
	l = GetCurrentLinePosition();
	k = GetLineWidth(&pData[m_CurrentCaretHot-l]);
	nStringWidth = m_ClientDC.GetTextExtent(&pData[m_CurrentCaretHot-l],k);
	

	if(nStringWidth < m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
	{
		if(m_Style & WISP_ES_CENTER)
			point.x = (m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width - nStringWidth) / 2 + m_ClientDC.GetTextExtent(pData,m_CurrentCaretHot);
		else if(m_Style & WISP_ES_RIGHT)
			point.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width;
	}

	SetCaretPos(point.x,point.y);
	UpdateClient();
	return false;
}

bool CWispEdit::SetWindowText(const WISP_CHAR* pString)
{	
	if(pString==NULL)
		return false;
	m_WndText = pString;
	int x=0,y=0;
	if(!(m_Style & WISP_ES_MULTILINE))
		y = (m_ClientRect.cy - m_Caret.pDIB->m_FrameBuffer.Height)/2;
	else
		y = 0;
	m_CurrentStringLen = TStrLen(pString);
	if(m_Style & WISP_ES_CENTER)
	{
		m_CurrentLineCharIndex=m_CurrentStringLen/2;
		m_CurrentCaretHot=m_CurrentLineCharIndex;
		if(m_CurrentStringLen%2)
			x=(m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width-m_ClientDC.GetTextExtent(&pString[m_CurrentLineCharIndex],1))/2;
		else
			x=(m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)/2;
	}
	else
	{
		m_CurrentLineCharIndex=0;
		m_CurrentCaretHot=0;
	}
	SetCaretPos(x,y);
	UpdateClient();
	return true;
}

bool CWispEdit::OnRecalcLayout(IN WISP_MSG*pMsg)
{
	return true;
}

bool CWispEdit::OnUpdateClient(IN WISP_MSG*pMsg)
{	
	WISP_POINT point;
	int nTmp = 0,nLineCurrentPosition = 0;
	int ShowBegin,ShowEnd;
	int len=0 ;
	WISP_RECT tempRc;
	ShowBegin=0;
	ShowEnd=0;
	if((m_Style&WISP_WS_BACK_TRANS)==0)
	{
		if( !(m_ParentWnd->m_CtrlType == WISP_CTRL_FORM && (m_Style & WISP_ES_READONLY)) )
			m_pWispBase->m_pCurDrawObj->DrawCtrlClient(&m_WindowDC, &m_ClientRect);
	}

	if(m_WndText.IsEmpty())
		return false;
	GetCaretPos(&point);
	if(!(m_Style & WISP_ES_MULTILINE))
		m_CurrentShowRect.y=0;
	else
		m_CurrentShowRect.y = point.y;
	m_CurrentShowRect.cy = m_ClientRect.cy;
	m_CurrentShowRect.x = point.x - m_ClientDC.GetTextExtent(m_WndText,m_CurrentCaretHot);
	m_CurrentShowRect.cx = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width-m_CurrentShowRect.x;
	tempRc = m_CurrentShowRect;
	if(m_bSelectFlag&&m_SelectBegin!=m_SelectEnd)
	{
		ShowBegin=MIN(m_SelectBegin,m_SelectEnd);
		ShowEnd=MAX(m_SelectBegin,m_SelectEnd);
	}
	if(ShowBegin)
	{
		m_ClientDC.SetTextStyle(WISP_TEXT_TRANS);
		m_ClientDC.DrawString(m_WndText,&m_CurrentShowRect,WISP_DT_SINGLELINE|WISP_DT_VCENTER,ShowBegin);
		len = m_ClientDC.GetTextExtent(m_WndText,ShowBegin);
	}
	if(ShowEnd-ShowBegin)
	{
		m_ClientDC.SetTextStyle(WISP_TEXT_OPAQUE);
		m_ClientDC.SetTextBKColor(m_BSelColor);				
		tempRc.x += len;
		tempRc.cx -= len;		
		m_ClientDC.DrawString(m_WndText+ShowBegin,&tempRc,WISP_DT_SINGLELINE|WISP_DT_VCENTER,ShowEnd-ShowBegin );
		len = m_ClientDC.GetTextExtent(m_WndText+ShowBegin,ShowEnd-ShowBegin);
	}
	if(ShowEnd!=m_WndText.m_Length)
	{		
		tempRc.x += len;
		tempRc.cx -= len;				
		m_ClientDC.SetTextStyle(WISP_TEXT_TRANS);
		m_ClientDC.DrawString(m_WndText+ShowEnd,&tempRc,WISP_DT_SINGLELINE|WISP_DT_VCENTER);
	}
	return false;	
}

bool CWispEdit::OnUpdateBorder(IN WISP_MSG*pMsg)
{
	if(m_Style & WISP_WS_BORDER)
	{
		m_pWispBase->m_pCurDrawObj->DrawCtrlBorder(&m_WindowDC, &m_WindowRect, m_BorderSize);
	}		
	return false;
}

CWispEdit::CWispEdit(void)
{
	m_CurrentCaretHot = 0;
	m_DebugValue = 0;
	m_CtrlType = WISP_CTRL_EDIT;
}
CWispEdit::~CWispEdit(void)
{
}

int CWispEdit::GetMaxShowCharNum(WISP_CHAR* lpszString, int nWidth,OUT int *nLength, bool isMultiLine)
{
	int i, nCount;
	int nRetLength = 0;
	CODE_ASSERT(lpszString);
	nCount = TStrLen(lpszString);
	if(nCount == 0)
	{
		if(nLength)
			*nLength = 0;
		return 0;
	}	
	if(isMultiLine)
	{
		for (i = 0; i < nCount; i++)
		{
			if(lpszString[i] == '\n' || lpszString[i] == '\r')
			{
				if(i + 1 < nCount)
				{
					if(lpszString[i+1] == '\n' || lpszString[i+1] == 'r')
					{
						if(lpszString[i] != lpszString[i+1])
							i++;
					}
				}
				i++;
				break;
			}
			if(nRetLength + m_ClientDC.GetTextExtent(&lpszString[i],1) > nWidth)
				break;
			else
				nRetLength += m_ClientDC.GetTextExtent(&lpszString[i],1);
		}
	}else
	{
		for (i = 0; i < nCount; i++)
			if(nRetLength + m_ClientDC.GetTextExtent(&lpszString[i],1) > nWidth)
				break;
			else
				nRetLength += m_ClientDC.GetTextExtent(&lpszString[i],1);
	}
	if(nLength)
		*nLength = nRetLength;
	return i;
}
bool CWispEdit::Create( IN WISP_CHAR*Name,IN const CWispRect&Rect,IN CWispBaseWnd*pParentWnd,IN UINT CmdID,	IN UINT Style,IN UINT ShowMode)
{
	return Create(Name,Rect.x,Rect.y,Rect.cx,Rect.cy,pParentWnd,CmdID,Style,ShowMode);
}
bool CWispEdit::Create(IN WISP_RECT&RectAtWnd,IN UINT Style,IN CWispBaseWnd*pParentWnd,IN UINT CmdID)
{
	return Create(NULL,RectAtWnd.x,RectAtWnd.y,RectAtWnd.cx,RectAtWnd.cy,pParentWnd,CmdID,Style);
}

bool CWispEdit::Create(IN WISP_CHAR* Name,IN INT x,IN INT y,IN INT cx,IN INT cy,IN CWispBaseWnd*pParentWnd,IN UINT CmdID,IN UINT Style,IN UINT ShowMode)
{
	if(!(Style & WISP_ES_MULTILINE))
		Style &= ~(WISP_ES_AUTOVSCROLL | WISP_ES_VSCROLL);
	else if(Style & (WISP_ES_RIGHT | WISP_ES_CENTER))
	{
		Style = Style & ~(WISP_ES_AUTOHSCROLL | WISP_ES_HSCROLL);
	}
	if((Style & (WISP_ES_RIGHT | WISP_ES_CENTER))==false)
		Style|=WISP_ES_LEFT;
	if(CWispWnd::Create(Name,x, y, cx, cy,pParentWnd,CmdID,Style & (~WISP_WS_CAPTION),ShowMode) == false)
		return false;
	if(Style & (WISP_ES_AUTOHSCROLL | WISP_ES_AUTOVSCROLL | WISP_ES_VSCROLL | WISP_ES_VSCROLL))
		m_StringMaxLen = WISP_EDIT_MAX_TEXT_LEN+1;
	else
		m_StringMaxLen = 0;

	if( Style & WISP_WS_BORDER )
		m_BorderSize = 2;
	else
		m_BorderSize = 0;

	if(Style & WISP_ES_VSCROLL)
		EnableScrollBar(WISP_SB_VERT);
	if(Style & WISP_ES_HSCROLL)
		EnableScrollBar(WISP_SB_HORZ);
	CreateCaret(WISP_DI_CARET);
	if(Style & WISP_ES_MULTILINE)
		m_LineMaxLen = 1024;
	else
		m_LineMaxLen = 0;
	if(Style & WISP_ES_RIGHT)
	{
		m_Caret.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width;
	}
	else if(Style & WISP_ES_CENTER)
	{
		m_Caret.x = m_ClientRect.cx / 2;
	}
	else
	{
		m_Caret.x = 0;
	}
	if(!(Style & WISP_ES_MULTILINE))
		m_Caret.y = (m_ClientRect.cy - m_Caret.pDIB->m_FrameBuffer.Height)/2;
	else
		m_Caret.y = 0;
	if((m_Style &WISP_ES_READONLY)==0)
		ShowCaret(true);
	m_bSelectFlag=false;
	m_SelectBegin=0;
	m_SelectEnd=0;
	m_CurrentInputStat=EDIT_STATE;
	m_BSelColor=SYS_COLOR[SC_CTRL_HOVER_FOCUS];
	return true;
		
}

void CWispEdit::OnLeftKey(IN WISP_MSG *pMsg)
{
	const WISP_CHAR *pData=m_WndText;
	int nLeftLen;
	WISP_POINT point;
	int nPrevCharWidth;
	//int nCurrentLinePos;
	
	GetCaretPos(&point);
	if(m_CurrentCaretHot == 0)
	{
		if(m_bSelectFlag&&m_pWispBase->m_KeyMap[WISP_VK_SHIFT]==0)
			m_bSelectFlag=false;
		return;
	}
	nPrevCharWidth = m_ClientDC.GetTextExtent(&pData[m_CurrentCaretHot-1],1);
		
	if(point.x - nPrevCharWidth < 0)
	{
		nLeftLen = m_ClientDC.GetTextExtent(pData,m_CurrentCaretHot-1);
		if( nLeftLen < m_ClientRect.cx / 4)		
			point.x = nLeftLen;		
		else
			point.x = m_ClientRect.cx / 4;
	}
	else	
		point.x -= m_ClientDC.GetTextExtent(&pData[m_CurrentCaretHot-1],1);	
	SetCaretPos(point.x,point.y);
	if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
	{
		if(m_bSelectFlag&&m_SelectBegin==m_CurrentCaretHot-1)
			m_bSelectFlag=false;
		else
		{
			if(m_bSelectFlag==false)			
				m_SelectBegin=m_CurrentCaretHot;
			m_SelectEnd=m_CurrentCaretHot-1;
			m_bSelectFlag=true;
		}
	}
	else
		m_bSelectFlag=false;
	m_CurrentCaretHot--;
}
void CWispEdit::OnRightKey(IN WISP_MSG *pMsg)
{
	const WISP_CHAR *pData=m_WndText;
	WISP_POINT point;
	int nPrevCharWidth;
	
	if(m_CurrentCaretHot == m_WndText.m_Length)
	{
		if(m_bSelectFlag&&m_pWispBase->m_KeyMap[WISP_VK_SHIFT]==0)
			m_bSelectFlag=false;
		return;
	}
	nPrevCharWidth = m_ClientDC.GetTextExtent(&pData[m_CurrentCaretHot],1);
	GetCaretPos(&point);		
	if(m_CurrentCaretHot >= m_WndText.m_Length)
		return;
	if(point.x +m_ClientDC.GetTextExtent(&pData[m_CurrentCaretHot],1) > m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
		point.x = m_ClientRect.cx / 4 * 3;
	else
		point.x += m_ClientDC.GetTextExtent(&pData[m_CurrentCaretHot],1);
	
	SetCaretPos(point.x,point.y);	
	if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
	{
		if(m_bSelectFlag&&m_SelectBegin==m_CurrentCaretHot+1)
			m_bSelectFlag=false;
		else
		{
			if(m_bSelectFlag==false)			
				m_SelectBegin=m_CurrentCaretHot;
			m_SelectEnd=m_CurrentCaretHot+1;
			m_bSelectFlag=true;
		}
	}
	else
		m_bSelectFlag=false;
	m_CurrentCaretHot++;	
}

void CWispEdit::OnReturnKey(IN WISP_MSG *pMsg)
{
}

void CWispEdit::OnHomeKey(IN WISP_MSG *pMsg)
{
	const WISP_CHAR *pData = m_WndText;
	WISP_POINT point;
	int nStringWidth;
	if(m_CurrentCaretHot == 0)
	{
		if(m_bSelectFlag&&m_pWispBase->m_KeyMap[WISP_VK_SHIFT]==0)
			m_bSelectFlag=false;
		return ;	
	}
	
	nStringWidth = m_ClientDC.GetTextExtent(pData);
	GetCaretPos(&point);
	point.x = 0;
	if(nStringWidth < m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
	{
		if(m_Style & WISP_ES_CENTER)
			point.x = (m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width - nStringWidth) / 2;
		else if(m_Style & WISP_ES_RIGHT)
			point.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width - nStringWidth;
	}
	SetCaretPos(point.x,point.y);
	if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
	{
		if(m_bSelectFlag&&m_SelectBegin==0)
		{
			m_bSelectFlag=false;
		}
		else
		{
			if(m_bSelectFlag==false)
				m_SelectBegin=m_CurrentCaretHot;
			m_SelectEnd=0;		
			m_bSelectFlag=true;
		}		
	}
	else
	{
		m_bSelectFlag=false;
	}
	m_CurrentCaretHot = 0;
}
void CWispEdit::OnEndKey(IN WISP_MSG *pMsg)
{
	const WISP_CHAR *pData = m_WndText;
	WISP_POINT point;
	GetCaretPos(&point);
	int nStringWidth = 0;
	nStringWidth = m_ClientDC.GetTextExtent(pData);
	
	if(nStringWidth > m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
	{
		point.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width;
	}
	else
	{
		if(m_Style & WISP_ES_CENTER)
			point.x = (m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width - nStringWidth) / 2 + m_ClientDC.GetTextExtent(pData);
		else if(m_Style & WISP_ES_RIGHT)
			point.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width;
		else
			point.x = nStringWidth;
	}	
	SetCaretPos(point.x, point.y);
	if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
	{
		if(m_bSelectFlag&&m_SelectBegin==m_WndText.m_Length)
		{
			m_bSelectFlag=false;
		}else
		{
			if(m_bSelectFlag==false)
				m_SelectBegin=m_CurrentCaretHot;
			m_SelectEnd=m_WndText.m_Length;
			m_bSelectFlag=true;
		}		
	}
	else
		m_bSelectFlag=false;
	m_CurrentCaretHot = m_WndText.m_Length;
}
void CWispEdit::OnBackKey(IN WISP_MSG *pMsg)
{
	if(m_CurrentCaretHot == 0 || m_CurrentCaretHot > m_WndText.m_Length)
		return;			
	DeleteChar(m_CurrentCaretHot,1,pMsg);		
}

void CWispEdit::OnDeleteKey(IN WISP_MSG *pMsg)
{
	int nStringWidth;
	WISP_POINT point;
	if(m_bSelectFlag&&m_SelectBegin!=m_SelectEnd)
	{
		WISP_POINT CaretPoint;
		GetCaretPos(&CaretPoint);
		int begin = MIN(m_SelectBegin,m_SelectEnd);
		int end = MAX(m_SelectBegin,m_SelectEnd);
		WISP_POINT point = GetPositionByIndex(begin);
		m_WndText.Delete(begin,end-begin);
		m_CurrentCaretHot=begin;
		if(point.x<0)
			point.x=0;
		CaretPoint.x = point.x;		
		SetCaretPos(CaretPoint.x,CaretPoint.y);
		m_bSelectFlag=false;
		m_SelectBegin=0;
		m_SelectEnd=0;
		return;
	}
	if(m_CurrentCaretHot == m_WndText.m_Length)
		return;
	GetCaretPos(&point);
	nStringWidth = m_ClientDC.GetTextExtent(m_WndText+m_CurrentCaretHot+1);
	if(nStringWidth > m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width - point.x)
	{
		m_WndText.Delete(m_CurrentCaretHot);
	}
	else
	{
		nStringWidth = m_ClientDC.GetTextExtent(m_WndText,m_CurrentCaretHot);
		if(nStringWidth > point.x)
		{
			nStringWidth = m_ClientDC.GetTextExtent(m_WndText+m_CurrentCaretHot+1,1);
			m_WndText.Delete(m_CurrentCaretHot);
			point.x += nStringWidth;			
		}
		else
		{
			m_WndText.Delete(m_CurrentCaretHot);
		}
	}
	nStringWidth = m_ClientDC.GetTextExtent(m_WndText);
	if(nStringWidth < m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
	{
		if(m_Style & WISP_ES_CENTER)
			point.x = (m_ClientRect.cx - nStringWidth - m_Caret.pDIB->m_FrameBuffer.Width) / 2 + m_ClientDC.GetTextExtent(m_WndText,m_CurrentCaretHot);
		else if(m_Style & WISP_ES_RIGHT)
			point.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width;
	}
	SetCaretPos(point.x,point.y);	
}
int CWispEdit::InsertChar(IN WISP_CHAR *pChar,IN int nPosition,IN int Counter)
{
	int nret=0;
	//int nStringWidth;
	WISP_POINT CaretPoint;
	if(SendCmdMsg(WISP_CMD_EN_CHANGING)==false)
		return nret;
	if(m_bSelectFlag&&m_SelectBegin!=m_SelectEnd)
	{
		
		GetCaretPos(&CaretPoint);
		int begin = MIN(m_SelectBegin,m_SelectEnd);
		int end = MAX(m_SelectBegin,m_SelectEnd);
		WISP_POINT point = GetPositionByIndex(begin);
		m_WndText.Delete(begin,end-begin);
		m_CurrentCaretHot=begin;
		CaretPoint.x = point.x;
		SetCaretPos(CaretPoint.x,CaretPoint.y);
		m_bSelectFlag=false;
		m_SelectBegin=0;
		m_SelectEnd=0;
	}
	if(nPosition==-1)
		nPosition = m_CurrentCaretHot;	
	if(Counter==1)
		nret = m_WndText.Insert(nPosition, *pChar);
	else
		m_WndText.Insert(nPosition,pChar);
	
	
	SendCmdMsg(WISP_CMD_EN_CHANGED);
	return nret;
}
int CWispEdit::DeleteChar(int nPosition,int nCount,WISP_MSG *pMsg)
{
	int nret=0;
	if(nPosition == -1)
		nPosition = m_CurrentCaretHot;	
	
	if(SendCmdMsg(WISP_CMD_EN_CHANGING))
	{
		if(nPosition==m_WndText.m_Length)
			nPosition--;
		OnLeftKey(pMsg);
		m_WndText.Delete(nPosition, nCount);
		SendCmdMsg(WISP_CMD_EN_CHANGED);
	}
	else
		return 0;
	return nCount;
}
int CWispEdit::GetCurrentLinePosition(OUT int nIndex)
{
	const WISP_CHAR *pData = m_WndText;
	WISP_POINT point;
	int i,j,sum,k,n;
	if(!(m_Style & WISP_ES_MULTILINE))
			return m_CurrentCaretHot;

	GetCaretPos(&point);
	for(j = 0, i =  m_CurrentCaretHot - 1; i>= 0;i--, j++)
	{
		if(pData[i] == '\n' || pData[i] == '\r')
			break;
	}
	if(m_Style & (WISP_ES_AUTOHSCROLL | WISP_ES_HSCROLL))
	{
		i = j;
		j = j % WISP_EDIT_MAX_LINETEXT_LEN;
		if(j == 0 && i != 0)
			j = WISP_EDIT_MAX_LINETEXT_LEN;
		return j;
	}
	for(n = 0, i = 0, sum = 0; i < j; i++,n++)
	{
		k = m_ClientDC.GetTextExtent(&pData[m_CurrentCaretHot - j + i],1);
		if(sum + k < m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
			sum+=k;
		else
		{
			sum = k;
			n = -1;
		}
	}
	return n;
}
int CWispEdit::GetPrevLineBeginPosition(int nEndPostion,int *nStringLen)
{
	const WISP_CHAR *pData = m_WndText;
	int nRet,k,i,j,sum;
	
	int oldEnd = nEndPostion;
	if(pData[nEndPostion] == '\n' || pData[nEndPostion] == '\r')
		if(pData[nEndPostion-1] == '\n' || pData[nEndPostion-1] == '\r')
		{
			if(pData[nEndPostion-1] != pData[nEndPostion])
				nEndPostion -= 2;
			else
				nEndPostion -= 1;
		}else
			nEndPostion -= 1;

	if(m_Style & (WISP_ES_AUTOHSCROLL | WISP_ES_HSCROLL))
	{
		for(j = 0,i = nEndPostion;i >= 0;i--,j++)
		{
			if(pData[i] == '\n' || pData[i] == '\r')
				break;
		}
		j = j % WISP_EDIT_MAX_LINETEXT_LEN;		
	}
	else
	{
		for(sum = 0,j = 0, i = nEndPostion;i>=0;i--,j++)
		{
			if(pData[i] != '\n' && pData[i] != '\r')
			{	
				k = m_ClientDC.GetTextExtent(&pData[i],1);
				sum += k;
				if(sum > m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
				{
					sum -= k;
					break;
				}
			}else
				break;
		}
	}
	nRet = nEndPostion - j + 1;
	if(nStringLen)
	{
		for(sum = 0,i = nRet; i <= oldEnd; i++)
		{
			if(pData[i] != '\n' && pData[i] != '\r')
				sum += m_ClientDC.GetTextExtent(&pData[i],1);
		}
		*nStringLen = sum;
	}
	return nRet;
}
int CWispEdit::GetCaretLineCharWidth()
{
	const WISP_CHAR *pData = m_WndText;
	if(m_Style & WISP_ES_MULTILINE)	
		return GetCurrentLinePosition();	
	return m_ClientDC.GetTextExtent(pData);
}
int CWispEdit::GetLineWidth(const WISP_CHAR *pSrc)
{	
	int i;
	for(i = 0; pSrc[i];i++)
	{
		if(pSrc[i] == '\n' && pSrc[i] == '\r')
		{
			if(i + 1 < m_WndText.m_Length)
			{
				if(pSrc[i+1] == '\n' || pSrc[i+1] == '\r')
					i++;
			}
			i++;
			break;
		}		
	}
	return i;
}
int CWispEdit::CalcLineNum(const WISP_CHAR *pSrc,int nCount,int nPerLineMaxCharNum)
{
	int i,j,nLineNum,nCharNum;
	if(nCount == -1)
		nCount = TStrLen(pSrc);
	if(nCount == 0)
		return 0;
	nCharNum = 0;
	for(nLineNum = 1, j = 0, i = 0; i < nCount; i++)
	{
		if(pSrc[i] == '\r' || pSrc[i] == '\n')
		{			
			if(i != nCount-1)
			{
				if(pSrc[i + 1] == '\r' || pSrc[i + 1] == '\n')
					i++;
			}
			nLineNum++;
			nLineNum = nLineNum + nCharNum / nPerLineMaxCharNum;
			if(((nCharNum % nPerLineMaxCharNum) == 0) && (nCharNum != 0))
				nLineNum -= 1;
			nCharNum = 0;
		}
		else
			nCharNum++;
	}
	nLineNum = nLineNum + nCharNum / nPerLineMaxCharNum;
	if(((nCharNum % nPerLineMaxCharNum) == 0) && (nCharNum != 0))
		nLineNum -= 1;
	return nLineNum;
}
int CWispEdit::CalcLineNumForWidth(const WISP_CHAR *pSrc,int nCount,int nLineWidth)
{
	int i,j,nLineNum,nCharNum,nCharWidth;
	if(nCount == -1)
		nCount = TStrLen(pSrc);
	if(nCount == 0)
		return 0;
	nCharNum = 0;
	for(nLineNum = 1, j = 0, i = 0; i < nCount; i++)
	{
		if(pSrc[i] == '\r' || pSrc[i] == '\n')
		{			
			if(i != nCount-1)
			{
				if(pSrc[i + 1] == '\r' || pSrc[i + 1] == '\n')
					i++;
			}
			nLineNum++;
			nCharNum = 0;
		}
		else
		{
			nCharWidth = m_ClientDC.GetTextExtent(&pSrc[i],1);
			if(nCharNum + nCharWidth > nLineWidth)
			{
				nLineNum++;
				nCharNum = nCharWidth;
			}else
			{
				nCharNum+=nCharWidth;
			}
		}
	}
	return nLineNum;
}
int CWispEdit::CaretLeftMove()
{
	const WISP_CHAR *pData = m_WndText;
	if(m_CurrentCaretHot == 0)
		return 0;
	if(pData[m_CurrentCaretHot-1] !=  '\n' && pData[m_CurrentCaretHot-1] !=  '\r')
		m_CurrentCaretHot--;
	else
	{
		if(m_CurrentCaretHot - 2 >= 0 && (pData[m_CurrentCaretHot-2] == '\n' || pData[m_CurrentCaretHot-2] == '\r'))
			m_CurrentCaretHot--;
		m_CurrentCaretHot--;
		return 1;
	}
	return 0;
}
int CWispEdit::CaretRightMove()
{
	const WISP_CHAR *pData = m_WndText;
	if(m_CurrentCaretHot >= m_WndText.m_Length)
		return 0;
	if(pData[m_CurrentCaretHot] != '\n' && pData[m_CurrentCaretHot] != '\r')
	{
		m_CurrentCaretHot++;
	}else
	{
		if((m_CurrentCaretHot+1 < m_WndText.m_Length) && (pData[m_CurrentCaretHot+1] == '\n' || pData[m_CurrentCaretHot+1] == '\r'))		
			m_CurrentCaretHot++;
		m_CurrentCaretHot++;
		return 1;
	}
	return 0;
}

int CWispEdit::GetCurrentPosition(OUT int nIndex,OUT int *nLineLen)
{
	const WISP_CHAR *pData = m_WndText;
	int i,j,k;
			
	for(j = 0, i =  nIndex - 1; i>= 0;i--, j++)
	{
		if(pData[i] == '\n' || pData[i] == '\r')
			break;
	}				
	if(nLineLen)
	{
		for(k = 0,i = nIndex; i < m_WndText.m_Length; i++,k++)
			if(pData[i] == '\n' || pData[i] == '\r')
				break;
		*nLineLen = j+k;
	}
	return j;
}

WISP_POINT CWispEdit::GetPositionByIndex(IN int index)
{
	WISP_POINT Point;
	Point.x = 0;
	Point.y = 0;
	if(index <= m_WndText.m_Length)
	{
		int Width = m_ClientDC.GetTextExtent(m_WndText,index);
		Point.x = m_CurrentShowRect.x + Width;
		Point.y = m_CurrentShowRect.y;
	}
	return Point;
}

int CWispEdit::SelectText(int SelectBegin,int SelectEnd)
{
	int nCaretPos = SelectEnd;
	if(m_WndText.Length()<MAX(SelectBegin,SelectEnd))
		return 0;
	m_SelectBegin=MIN(SelectBegin,SelectEnd);
	m_SelectEnd=MAX(SelectBegin,SelectEnd);
	m_bSelectFlag=true;
	m_CurrentCaretHot=nCaretPos;
	Update();
	return m_SelectEnd-m_SelectBegin+1;
}
bool CWispEdit::CharIsVisible(int index)
{
	WISP_POINT CaretPoint;
	if(m_CurrentCaretHot==index)
		return true;
	GetCaretPos(&CaretPoint);
	
	int x1 = m_ClientDC.GetTextExtent(m_WndText,m_CurrentCaretHot);
	int x2 = m_ClientDC.GetTextExtent(m_WndText,index);
	if(m_CurrentCaretHot>index)
	{
		if(x1-x2>CaretPoint.x)
			return false;		
	}
	else
	{
		if(x2-x1 > m_ClientRect.cx-CaretPoint.x)
			return false;
	}
	return true;
}
void  CWispEdit::EnableVisible(int index)
{
	if(CharIsVisible(index))
		return;

}
bool CWispEdit::OnEventPaste(IN WISP_MSG*pMsg)
{
	int nStringWidth;
	INT Counter;
	WISP_POINT CaretPoint;
	if(m_Style&WISP_ES_READONLY)
		return true;
	if(m_pWispBase->m_ClipboardString.IsEmpty()==false)
	{
		Counter=m_pWispBase->m_ClipboardString.m_Length;
		InsertChar(m_pWispBase->m_ClipboardString,-1,Counter);
		GetCaretPos(&CaretPoint);
		nStringWidth = m_ClientDC.GetTextExtent(m_WndText,Counter,m_CurrentCaretHot);

		if(m_Style & WISP_ES_LEFT)
		{			
			if(CaretPoint.x+nStringWidth > m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width)
			{
				CaretPoint.x = m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width;
				if(m_Style & WISP_ES_AUTOHSCROLL)//×ó¶ÔÆë
				{
					if(m_CurrentCaretHot != m_WndText.m_Length)
						CaretPoint.x = (m_ClientRect.cx - m_Caret.pDIB->m_FrameBuffer.Width) / 4 * 3;					
				}
			}
			else
			{		
				CaretPoint.x += nStringWidth;
			}
			m_CurrentCaretHot+=Counter;
			SetCaretPos(CaretPoint.x,CaretPoint.y);
		}		
		Update();
	}
	return true;
}

bool CWispEdit::OnEventCopy(IN WISP_MSG*pMsg)
{
	CWispString ClipboardString;

	ClipboardString.Empty();
	int begin,end;
	const WISP_CHAR *pData;
	pData = m_WndText;
	if(m_bSelectFlag==false)
		return false;
	begin = MIN(m_SelectBegin,m_SelectEnd);
	end=MAX(m_SelectBegin,m_SelectEnd);
	ClipboardString+=&pData[begin];
	ClipboardString.Delete(end-begin,ClipboardString.m_Length-(end-begin));
	m_pWispBase->SetClipboardString(ClipboardString);	
	
	return true;
}
