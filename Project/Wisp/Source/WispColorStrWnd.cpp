#include "StdAfx.h"
#include "WispColorStrWnd.h"

WISP_MSG_MAP_BEGIN(CWispColorStrWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_SCROLL_EVENT,OnScrollEvent)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_EVENT_MAP_BEGIN(CWispColorStrWnd)
	WISP_MSG_EVENT_MAP(WISP_ID_COPY,OnEventCopy)
WISP_MSG_EVENT_MAP_END

CWispColorStrWnd::CWispColorStrWnd(void)
{
	m_MaxLines = m_MaxChars = 0;
	m_Margin = WISP_COLOR_STR_MARGIN;
}

CWispColorStrWnd::~CWispColorStrWnd(void)
{
}

bool CWispColorStrWnd::OnCreate(IN WISP_MSG*pMsg)
{
	m_bSelect = false;
	return true;
}

bool CWispColorStrWnd::OnEventCopy(IN WISP_MSG*pMsg)
{
	int Length;
	WISP_CHAR szBuffer[MAX_LINE_CHAR+1];
	WISP_COLOR_CHAR	CSBuffer[MAX_LINE_CHAR+1];
	if(m_bSelect==false)
		return false;
	CWispString ClipboardString;
	ClipboardString.Empty();
	for(int ScrPosY=m_pSelStartPos->y;ScrPosY<=m_pSelEndPos->y;ScrPosY++)
	{
		if(ScrPosY!=m_pSelStartPos->y)
			ClipboardString+=WSTR("\r\n");
		*CSBuffer=0;
		GetLineStr(ScrPosY,CSBuffer);
		TStrCpy(szBuffer,CSBuffer);
		if(m_pSelStartPos->y == m_pSelEndPos->y)
		{
			Length = m_pSelEndPos->x - m_pSelStartPos->x + 1;
			if(Length>0)
			{
				szBuffer[m_pSelStartPos->x+Length]=0;
				ClipboardString+=&szBuffer[m_pSelStartPos->x];
			}
		}
		else if(ScrPosY<m_pSelEndPos->y)
		{
			if(ScrPosY == m_pSelStartPos->y)
			{
				ClipboardString+=&szBuffer[m_pSelStartPos->x];
			}
			else
			{
				ClipboardString+=szBuffer;
			}			
		}
		else if(ScrPosY==m_pSelEndPos->y)
		{
			szBuffer[m_pSelEndPos->x+1]=0;
			ClipboardString+=szBuffer;
		}
	}
	m_pWispBase->SetClipboardString(ClipboardString);
	m_bSelect = false;
	UpdateClient();
	return true;
}

bool CWispColorStrWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	BYTE BKClr;
	WISP_RECT Rect;
	int Length,ScrPosX,ScrPosY;
	WISP_COLOR_CHAR	CSBuffer[MAX_LINE_CHAR+1],Char;
	CWispWnd::OnUpdateClient(pMsg);
	for(int n=0;n<m_nLinesPerPage;n++)
	{
		*CSBuffer=0;
		ScrPosY=m_ScrPos.y+n;
		if(BKClr=GetLineStr(ScrPosY,CSBuffer))
		{
			Rect.x = 0;
			Rect.y = m_Margin+n*m_ClientDC.m_pFont->m_Height;
			Rect.cx = m_ClientRect.cx;
			Rect.cy = m_ClientDC.m_pFont->m_Height;
			m_ClientDC.DrawFullRect(&Rect,SYS_COLOR[BKClr]);
		}
		Length=TStrLen(CSBuffer);
		if(Length>0)
		{
			if((m_Style & WISP_WCSS_SELECT_STRING) && m_bSelect && ScrPosY>=m_pSelStartPos->y && ScrPosY<=m_pSelEndPos->y)
			{
				ScrPosX = m_Margin - m_ClientDC.m_pFont->m_Width * m_ScrPos.x;
				for(int nx=0;nx<Length;nx++)
				{
					if(IsSelectChar(m_ScrPos.x+(ScrPosX-m_Margin)/m_ClientDC.m_pFont->m_Width,ScrPosY))
					{
						Char = (CSBuffer[m_ScrPos.x+nx]&0xFFFF)+(SC_WHITE<<16)+(SC_SELECT_BG<<24);
						ScrPosX+=m_ClientDC.DrawColorString(ScrPosX,m_Margin+n*m_ClientDC.m_pFont->m_Height,&Char,1,m_ScrPos.x+nx);
					}
					else
					{
						ScrPosX+=m_ClientDC.DrawColorString(ScrPosX,m_Margin+n*m_ClientDC.m_pFont->m_Height,&CSBuffer[m_ScrPos.x+nx],1,m_ScrPos.x+nx);
					}
				}
			}
			else
			{
				m_ClientDC.DrawColorString(m_Margin - m_ClientDC.m_pFont->m_Width * m_ScrPos.x,m_Margin+n*m_ClientDC.m_pFont->m_Height,CSBuffer,Length);
			}
		}
	}
	return false;
}

bool CWispColorStrWnd::OnScrollEvent(IN WISP_MSG*pMsg)
{
	CWispWnd::OnScrollEvent(pMsg);
	if(pMsg->ScrollEvent.SBType == WISP_SB_HORZ)
	{
		m_ScrPos.x = (int)m_ScrollBar[WISP_SB_HORZ]->CurPos;

	}
	else
	{
		m_ScrPos.y = (int)m_ScrollBar[WISP_SB_VERT]->CurPos;
	}
	UpdateCaretState();
	UpdateClient();
	return false;
}


bool CWispColorStrWnd::OnMouseMove(IN WISP_MSG*pMsg)
{
	if(PtInRect(&m_ClientRect,pMsg->MsgMouseWndPT)==false)
		return true;
	if(pMsg->bMsgLBTDown)
	{
		if((m_Style & WISP_WCSS_SELECT_STRING) && m_RealSelStartPos.x>=0 && m_RealSelStartPos.y>=0)
		{
			CalcPonitStrPos(&pMsg->MsgMouseWndPT,&m_RealSelEndPos);
			if(m_RealSelEndPos.x>=0&&m_RealSelEndPos.y>=0&&m_RealSelStartPos.x>=0&&m_RealSelStartPos.y>=0)
			{
				m_bSelect = true;
				if(m_RealSelEndPos.y < m_RealSelStartPos.y || (m_RealSelEndPos.y == m_RealSelStartPos.y && m_RealSelEndPos.x < m_RealSelStartPos.x) )
				{
					m_pSelStartPos = &m_RealSelEndPos;
					m_pSelEndPos = &m_RealSelStartPos;
				}
				else
				{
					m_pSelStartPos = &m_RealSelStartPos;
					m_pSelEndPos = &m_RealSelEndPos;
				}
				Update();				
			}
		}
	}
	return true;
}

void CWispColorStrWnd::ClearSelect()
{
	if(m_bSelect)
	{
		m_bSelect = false;
		m_RealSelEndPos.x = m_RealSelEndPos.y = m_RealSelStartPos.x = m_RealSelStartPos.y = -1;
	}	
}


bool CWispColorStrWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	WISP_MSG Msg;
	if(pMsg->KeyEvent.bKeyDown)
	{
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_VK_RBUTTON:
		case WISP_MOD_CTRL|WISP_VK_C:
		case WISP_MOD_SHIFT|WISP_VK_INSERT:
			Msg.hWnd = this;
			Msg.Msg = WISP_WM_EVENT;
			Msg.Command.CmdID = WISP_ID_COPY;
			POST_MSG(&Msg);
			return false;
		case WISP_MOD_CTRL|WISP_VK_V:
		case WISP_MOD_CTRL|WISP_VK_INSERT:
			Msg.hWnd = this;
			Msg.Msg = WISP_WM_EVENT;
			Msg.Command.CmdID = WISP_ID_PASTE;
			POST_MSG(&Msg);
			return false;
		}
		if(m_Style & WISP_WCSS_SELECT_STRING && pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
		{
			m_bSelect = false;
			CalcPonitStrPos(&pMsg->MsgMouseWndPT,&m_RealSelStartPos);
			m_pSelStartPos = &m_RealSelStartPos;
			m_RealSelEndPos.x = m_RealSelEndPos.y = -1;
			m_pSelEndPos = &m_RealSelEndPos;
			Update();
		}
		if(m_Style&WISP_WCSS_FREE_CARET)
		{
			if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
			{
				ClearSelect();
				m_CaretPos.x=pMsg->MsgMouseWndPT.x-pMsg->MsgMouseWndPT.x%m_ClientDC.m_pFont->m_Width;
				m_CaretPos.x/=m_ClientDC.m_pFont->m_Width;
				m_CaretPos.y=pMsg->MsgMouseWndPT.y-pMsg->MsgMouseWndPT.y%m_ClientDC.m_pFont->m_Height;
				m_CaretPos.y/=m_ClientDC.m_pFont->m_Height;
				SetCaretPos(m_CaretPos.x*m_ClientDC.m_pFont->m_Width,m_CaretPos.y*m_ClientDC.m_pFont->m_Height);
				m_CaretPos.y+=m_ScrPos.y;
				m_CaretPos.x+=m_ScrPos.x;
				RecalcLayout();
				Update();
			}
			switch(pMsg->KeyEvent.KeyType)
			{
			case WISP_VK_UP:
				ClearSelect();
				if(m_CaretPos.y>0)
				{
					if(m_CaretPos.y<=m_ScrPos.y)
						SendScrollEvent(WISP_SB_VERT,WISP_SB_DEC);
					m_CaretPos.y--;
					RecalcLayout();
					Update();
				}
				break;
			case WISP_VK_LEFT:
				ClearSelect();
				if(m_CaretPos.x>0)
				{
					if(m_CaretPos.x<=m_ScrPos.x)
						SendScrollEvent(WISP_SB_HORZ,WISP_SB_DEC);
					m_CaretPos.x--;
					RecalcLayout();
					Update();
				}
				break;
			case WISP_VK_DOWN:
				ClearSelect();
				if(m_CaretPos.y+1<m_MaxLines)
				{
					if(m_CaretPos.y+1>=m_ScrPos.y+m_nLinesPerPage)
						SendScrollEvent(WISP_SB_VERT,WISP_SB_INC);
					m_CaretPos.y++;
					RecalcLayout();
					Update();
				}
				break;
			case WISP_VK_RIGHT:
				ClearSelect();
				if(m_CaretPos.x+1<m_MaxChars)
				{
					if(m_CaretPos.x+1>=m_ScrPos.x+m_nCharsPerLine)
						SendScrollEvent(WISP_SB_HORZ,WISP_SB_INC);
					m_CaretPos.x++;
					RecalcLayout();
					Update();
				}
				break;
			}
		}
	}
	else
	{

	}
	return true;
}

bool CWispColorStrWnd::OnRecalcLayout(IN WISP_MSG*pMsg)
{
	m_nCharsPerLine = (m_ClientRect.cx-m_Margin*2)/m_ClientDC.m_pFont->m_Width;
	MIN_LIMIT(m_nCharsPerLine,0);
	m_nLinesPerPage = (m_ClientRect.cy-m_Margin) /m_ClientDC.m_pFont->m_Height;
	MIN_LIMIT(m_nLinesPerPage,0);
	if(m_nLinesPerPage>=m_MaxLines && m_ScrPos.y!=0)
		m_ScrPos.y = 0;
	SetScrollBarInfo(WISP_SB_VERT,m_ScrPos.y,m_MaxLines,m_nLinesPerPage);
	SetScrollBarInfo(WISP_SB_HORZ,m_ScrPos.x,m_MaxChars,m_nCharsPerLine);
	UpdateCaretState();
	return true;
}

void CWispColorStrWnd::CalcPonitStrPos(IN WISP_POINT*pPoint,WISP_POINT*pStrPT)
{
	int x,y;
	x = pPoint->x - m_Margin;
	y = pPoint->y - m_Margin;
	pStrPT->x=x-x%m_ClientDC.m_pFont->m_Width;
	pStrPT->x/=m_ClientDC.m_pFont->m_Width;
	if(x<m_ClientDC.m_pFont->m_Width/2 && pStrPT->x>0)
		pStrPT->x--;
	pStrPT->y=y-y%m_ClientDC.m_pFont->m_Height;
	pStrPT->y/=m_ClientDC.m_pFont->m_Height;
	pStrPT->y+=m_ScrPos.y;
	pStrPT->x+=m_ScrPos.x;
}

void CWispColorStrWnd::SetMaxLines(IN int nLine)
{
	m_MaxLines = nLine;
}

void CWispColorStrWnd::SetMaxChars(IN int nChar)
{
	m_MaxChars = nChar;
}

bool CWispColorStrWnd::InitWnd()
{
	if(CWispWnd::InitWnd()==false)
		return false;
	m_CaretPos.x = m_CaretPos.y = m_ScrPos.x = m_ScrPos.y = 0;
	return true;
}

void CWispColorStrWnd::UpdateCaretState()
{
	if(m_CaretPos.x>=m_ScrPos.x&&m_CaretPos.x<m_ScrPos.x+m_nCharsPerLine&&m_CaretPos.y>=m_ScrPos.y&&m_CaretPos.y<m_ScrPos.y+m_nLinesPerPage)
	{
		SetCaretPos(m_Margin+(m_CaretPos.x-m_ScrPos.x)*m_ClientDC.m_pFont->m_Width,m_Margin+(m_CaretPos.y-m_ScrPos.y)*m_ClientDC.m_pFont->m_Height);
		ShowCaret(true);
	}
	else
	{
		ShowCaret(false);
	}
}

bool CWispColorStrWnd::IsSelectChar(int ScrX,int ScrY)
{
	if(m_pSelEndPos->x==-1 || m_pSelEndPos->y==-1)
		return false;
	if(ScrY<m_pSelStartPos->y || ScrY>m_pSelEndPos->y)
		return false;
	if(ScrY==m_pSelStartPos->y && ScrX<m_pSelStartPos->x)
		return false;
	if(ScrY==m_pSelEndPos->y && ScrX>m_pSelEndPos->x)
		return false;
	return true;
}

