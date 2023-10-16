#include "StdAfx.h"
#include "WispHeader.h"

// CWispHeader
WISP_MSG_MAP_BEGIN(CWispHeader)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_UPDATE_BORDER,OnUpdateBorder)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_BEGIN_DRAG,OnBeginDrag)
	WISP_MSG_MAP(WISP_WM_DRAG_MOVE,OnDragMove)
	WISP_MSG_MAP(WISP_WM_END_DRAG,OnEndDrag)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispWnd)


CWispHeader::CWispHeader()
{
	m_ColumnDrag = false;
	m_RestoreCursor=false;
	m_ColumnOrgIndex=NULL;
	m_ColumnIndexCounter=0;
	m_LButtonDownEventType = MAX_LBUTTONDOWN_TYPE;
	m_CtrlType = WISP_CTRL_HEADER;
}

CWispHeader::~CWispHeader()
{
}

bool CWispHeader::OnUpdateBorder(IN WISP_MSG*pMsg)
{
	return false;
}

bool CWispHeader::OnUpdateClient(IN WISP_MSG*pMsg)
{
	WISP_POINT point = pMsg->MsgMouseScrPT;
	ScreenToClient(&point);
	DrawScreen(point,pMsg);
	return false;
}

bool CWispHeader::OnKeyEvent(IN WISP_MSG* pMsg)
{
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
		if(pMsg->KeyEvent.bKeyDown)
			return OnMouseLButtonDown(pMsg);
		else
			return OnMouseLButtonUp(pMsg);
	return true;
}

bool CWispHeader::OnMouseLeave(IN WISP_MSG* pMsg)
{
	if(m_ColumnDrag)
	{
		if(pMsg->bMsgLBTDown==false)
		{
			EndDrag();
			gpCurWisp->RestorCursorType();
			m_RestoreCursor=false;
			Update();
			return true;
		}
		OnDragMove(pMsg);
		Update();
		return false;
	}
	else
	{
		if(m_RestoreCursor)
		{
			gpCurWisp->RestorCursorType();
			m_RestoreCursor=false;
			Update();
			return false;
		}
		Update();
		return true;
	}
}

int CWispHeader::PointInItemIndex(IN WISP_POINT point,int *xdel,int *ydel)
{
	int i,j,nColCount = GetItemCount();
	WISP_RECT	rect={0, 0, 0, m_WindowRect.cy},rcText;	
		
	rcText.cy = m_WindowRect.cy;
	rcText.y = rect.y;
	for(j=0; j<nColCount; j++)
	{
		i=GetItemIndex(j);
		rect.cx	= m_vColumns[i]->nWidth;
		if(rect.cx <=0 && i!=(nColCount-1))
			continue;
		if( rect.cx > m_ClientRect.cx )
			rect.cx = m_ClientRect.cx;
		rcText.x = rect.x;
		rcText.cx = rect.cx;
		if(PtInRect(&rcText,point))
		{
			if(xdel)
				*xdel=point.x-rcText.x;
			if(ydel)
				*ydel=point.y-rcText.y;
			return i;
		}
		rect.x+=m_vColumns[i]->nWidth;
	}
	return i;
}

bool CWispHeader::OnMouseMove(IN WISP_MSG *pMsg)
{	
	int i,j,nColCount = GetItemCount();	
	WISP_RECT	rect={0, 0, 0, m_WindowRect.cy},rcText;
	WISP_POINT point = pMsg->MsgMouseScrPT;

	ScreenToClient(&point);
	rcText.cx = HEADER_MARGIN;
	rcText.cy = m_WindowRect.cy;
	rcText.y = rect.y;
	for(j=0; j<nColCount; j++)
	{
		i = GetItemIndex(j);
		rect.cx	= m_vColumns[i]->nWidth;
		if(rect.cx <=0 && j!=(nColCount-1))
			continue;
		if( rect.cx > m_ClientRect.cx )
			rect.cx = m_ClientRect.cx;
		rcText.x = rect.x;
		if(PtInRect(&rcText,point))
		{
			if(j!=0)
			{
				gpCurWisp->ChangeCursorType(WISP_CT_RESIZE_HORZ);			
				m_RestoreCursor=true;
				return false;
			}
		}
		rcText.x = rect.x + m_vColumns[i]->nWidth - HEADER_MARGIN;
		if(PtInRect(&rcText,point))
		{
			gpCurWisp->ChangeCursorType(WISP_CT_RESIZE_HORZ);
			m_RestoreCursor=true;
			return false;
		}
		rect.x += m_vColumns[i]->nWidth;
	}
	rcText.x = rect.x;
	rcText.cx = HEADER_MARGIN;
	rcText.cy = m_WindowRect.cy;
	rcText.y = rect.y;
	if(PtInRect(&rcText,point))
	{	
		if(j!=0)
		{				
			gpCurWisp->ChangeCursorType(WISP_CT_RESIZE_HORZ);			
			m_RestoreCursor=true;
			return false;
		}
	}
	if(m_RestoreCursor)
	{
		gpCurWisp->RestorCursorType();
		m_RestoreCursor=false;
	}
	Update();
	return true;
}

bool CWispHeader::OnMouseLButtonDown(IN WISP_MSG* pMsg)
{
	int i,j,nColCount = GetItemCount();	
	WISP_RECT	rect={0, 0, 0, m_WindowRect.cy},rcText,rcDrag;
	WISP_POINT point = pMsg->MsgMouseScrPT;

	ScreenToClient(&point);
	rcText.cx = HEADER_MARGIN;
	rcText.cy = m_WindowRect.cy;
	rcText.y = rect.y;
	rcDrag.y = rect.y;
	rcDrag.cy = m_WindowRect.cy;
	for(j=0; j<nColCount; j++)
	{
		i = GetItemIndex(j);
		rect.cx = m_vColumns[i]->nWidth;
		if(rect.cx <=0)
			continue;
		if( rect.cx > m_ClientRect.cx )
			rect.cx = m_ClientRect.cx;
		rcText.x = rect.x;
		if(PtInRect(&rcText,point))
		{
			if(j!=0)
			{
				m_DragColumnIndex = GetItemIndex(j - 1);
				m_LButtonDownEventType=MODIFY_ITEM_WIDTH;
				BeginDrag();
				return false;
			}
		}
		rcText.x = rect.x + m_vColumns[i]->nWidth - HEADER_MARGIN;
		if(PtInRect(&rcText,point))
		{
			m_LButtonDownEventType=MODIFY_ITEM_WIDTH;
			m_DragColumnIndex = i;
			BeginDrag();
			return false;
		}
		rcDrag.x = rect.x+HEADER_MARGIN;
		rcDrag.cx = rect.cx - 2 * HEADER_MARGIN;
		if(rcDrag.cx>0)
		{
			if(PtInRect(&rcDrag,point))
			{
				m_LButtonDownEventType=EXCHANGE_ITEM_POSITION;
				m_DragColumnIndex=i;
				BeginDrag();
				return false;
			}
		}
		rect.x += m_vColumns[i]->nWidth;
	}
	rcText.x = rect.x;
	rcText.cx = HEADER_MARGIN;
	rcText.cy = m_WindowRect.cy;
	rcText.y = rect.y;
	if(PtInRect(&rcText,point))
	{
		if(j!=0)
		{
			m_DragColumnIndex = GetItemIndex(j - 1);						
			m_LButtonDownEventType=MODIFY_ITEM_WIDTH;
			BeginDrag();
			return false;
		}
	}
	return true;
}

bool CWispHeader::OnMouseLButtonUp(IN WISP_MSG* pMsg)
{
	if(m_ColumnDrag)
	{
		EndDrag();
		if(m_LButtonDownEventType==EXCHANGE_ITEM_POSITION)
		{
			WISP_POINT point = pMsg->MsgMouseScrPT;
			int x,i;
			ScreenToClient(&point);
			i = PointInItemIndex(point,&x);
			if( i !=m_DragColumnIndex)
			{
				if(m_DragBeginPt.x >pMsg->MsgMouseWndPT.x)
				{
					if(x > (m_vColumns[i]->nWidth/2))
						return true;
				}else
					if(x < (m_vColumns[i]->nWidth/2))
						return true;
				int n=GetItemCount();

				for(int j=0;j<n;j++)
				{
					if(m_ColumnOrgIndex[j]==i)
						m_ColumnOrgIndex[j]=m_DragColumnIndex;
					else if(m_ColumnOrgIndex[j]==m_DragColumnIndex) 
						m_ColumnOrgIndex[j]=i;
				}

				WISP_MSG Msg;
				Msg.hWnd=m_OwnerWnd;
				Msg.Msg=WISP_WM_COMMAND;
				Msg.Command.CmdID=m_CmdID;
				Msg.Command.CtrlType= WISP_CTRL_HEADER;
				Msg.Command.CmdMsg=WISP_CMD_HD_EXCHANGE_ITEM;
				gpCurWisp->SendMessage(&Msg);
			}			
		}
		return false;
	}
	return true;
}

bool CWispHeader::OnBeginDrag(IN WISP_MSG* pMsg)
{
	m_PrevDragPoint = pMsg->DragEvent.BeginMouseWndPT;
	m_DragBeginPt = pMsg->DragEvent.BeginMouseWndPT;
	m_ColumnDrag = true;
	m_PrevWidth=0;
	m_DragMoving=false;
	return false;
}

bool CWispHeader::OnDragMove(IN WISP_MSG* pMsg)
{
	int Width;
	if(m_LButtonDownEventType==MODIFY_ITEM_WIDTH)
	{	
		if(m_PrevWidth<0)
			Width = m_PrevWidth + (pMsg->MsgMouseWndPT.x - m_PrevDragPoint.x);
		else
			Width = m_vColumns[m_DragColumnIndex]->nWidth + (pMsg->MsgMouseWndPT.x - m_PrevDragPoint.x);
		if(Width<=0)
			SetItemWidth(0,m_DragColumnIndex);
		else
			SetItemWidth(Width,m_DragColumnIndex);
		m_PrevWidth=Width;
		m_PrevDragPoint = pMsg->MsgMouseWndPT;
	}
	if(m_LButtonDownEventType==EXCHANGE_ITEM_POSITION)
	{
		m_DragMoving=true;
		m_PrevDragPoint = pMsg->MsgMouseWndPT;
	}
	Update();
	return true;
}

bool CWispHeader::OnEndDrag(IN WISP_MSG* pMsg)
{
	m_ColumnDrag = false;
	return false;
}

bool CWispHeader::OnDestroy(IN WISP_MSG*pMsg)
{
	m_vColumns.Clear();
	SafeDelete(m_ColumnOrgIndex);
	m_ColumnIndexCounter=0;
	return true;
}

// CWispHeader message handlers
int CWispHeader::InsertItem(const WHITEM& HeaderItem, int nCol)
{
	int ColumnNum=(int)m_vColumns.Count();
	if(ColumnNum+1>m_ColumnIndexCounter)
	{
		int *pTmpPointer;
		pTmpPointer=new int[m_ColumnIndexCounter+15];
		if(m_ColumnOrgIndex)
		{			
			memcpy(pTmpPointer,m_ColumnOrgIndex,sizeof(int)*m_ColumnIndexCounter);
			delete []m_ColumnOrgIndex;
		}
		m_ColumnOrgIndex=pTmpPointer;
		m_ColumnIndexCounter+=15;
	}
	m_ColumnOrgIndex[ColumnNum]=ColumnNum;
	m_ColumnOrgIndex[ColumnNum]=ColumnNum;
	if( nCol==-1 || nCol>=(int)m_vColumns.Count() )
		m_vColumns.Append(HeaderItem);
	else
		m_vColumns.InsertBefore(m_vColumns[nCol], HeaderItem);
	Update();
	return m_vColumns.Count();
}

int CWispHeader::InsertItem(const WISP_CHAR* lpszHeading, int nWidth, int nFormat, void* pData, int nCol)
{
	WHITEM	stColumn;
	stColumn.strHeading	= lpszHeading;
	stColumn.nFormat	= nFormat;
	stColumn.nWidth		= nWidth==-1?10:nWidth;
	stColumn.pData		= pData;

	return InsertItem(stColumn, nCol);
}

void CWispHeader::SetItemText(const WISP_CHAR* pszHeading, int nCol)
{
	m_vColumns[nCol]->strHeading = pszHeading;
}

void CWispHeader::SetItemWidth(const int nWidth, int nCol)
{
	m_vColumns[nCol]->nWidth = nWidth;
}

void CWispHeader::DrawHeader(WISP_POINT& point,IN WISP_MSG *pMsg)
{
	ACTIVE_STATUS eStatus;
	int nColCount = GetItemCount();
	int i,j;
	WISP_RECT	rect={0, 0, 0, m_WindowRect.cy},rcDrag,rcMouseIn;

	rcMouseIn.cx = 0;rcMouseIn.cy = 0;
	for(j=0; j<nColCount; j++)
	{
		i = GetItemIndex(j);
		rect.cx	= m_vColumns[i]->nWidth;
		if(rect.cx <=0)
			continue;
		if( rect.cx > m_ClientRect.cx )
			rect.cx = m_ClientRect.cx;

		if( PtInRect(&rect,point))
		{
			rcMouseIn = rect;
			eStatus = STATUS_HOVER;
		}
		else 
			eStatus = STATUS_NORMAL;
		if(m_ColumnDrag && m_LButtonDownEventType == EXCHANGE_ITEM_POSITION)
		{
			if(i == m_DragColumnIndex)
			{
				eStatus=STATUS_DOWN;
				rcDrag = rect;
			}
			else
			{
				eStatus = STATUS_NORMAL;
			}
		}
		gpCurWisp->m_pCurDrawObj->DrawHeaderFrameRect(&m_ClientDC, &rect, eStatus);
		WISP_RECT	rcText={rect.x+HEADER_MARGIN, rect.y, rect.cx-2*HEADER_MARGIN, rect.cy};
		m_ClientDC.DrawString(m_vColumns[i]->strHeading,&rcText, WISP_DT_SINGLELINE|WISP_DT_VCENTER|WISP_DT_END_ELLIPSIS);		
		rect.x += m_vColumns[i]->nWidth;
		if( rect.x > m_ClientRect.cx )
			return;
	}
	
	rect.cx = m_ClientRect.cx-rect.x;
	eStatus = STATUS_NORMAL;
	if(rect.cx)			
		gpCurWisp->m_pCurDrawObj->DrawHeaderFrameRect(&m_ClientDC, &rect, eStatus);				
	if(m_ColumnDrag && m_LButtonDownEventType == EXCHANGE_ITEM_POSITION)
	{
		if(m_DragMoving&&rcMouseIn.cx&&rcMouseIn.cy)
		{
			if(pMsg->MsgMouseWndPT.x < rcMouseIn.x + rcMouseIn.cx /2)
			{
				m_ClientDC.DrawVLine(rcMouseIn.x,rcMouseIn.y,rcMouseIn.cy+rcMouseIn.y-1,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_LIGHT_BLUE]);
				if(rcMouseIn.x>0)
					m_ClientDC.DrawVLine(rcMouseIn.x-1,rcMouseIn.y,rcMouseIn.cy+rcMouseIn.y-1,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_LIGHT_BLUE]);
			}
			else
			{
				m_ClientDC.DrawVLine(rcMouseIn.x+rcMouseIn.cx-1,rcMouseIn.y,rcMouseIn.cy+rcMouseIn.y-1,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_LIGHT_BLUE]);
				m_ClientDC.DrawVLine(rcMouseIn.x+rcMouseIn.cx,rcMouseIn.y,rcMouseIn.cy+rcMouseIn.y-1,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_LIGHT_BLUE]);
			}			
		}		
		DrawDragRect(rcDrag);
	}
}

void CWispHeader::DrawScreen(IN WISP_MSG *pMsg)
{
	WISP_POINT point = gpCurWisp->m_MousePT;
	ScreenToClient(&point);
	DrawScreen(point,pMsg);
}

void CWispHeader::DrawScreen(WISP_POINT &point,IN WISP_MSG *pMsg)
{
	DrawHeader(point,pMsg);
}

CWispHeader::WHITEM* CWispHeader::GetItem(int nIndex)
{
	if( nIndex <= (int)m_vColumns.Count() )
		return &(*m_vColumns[m_ColumnOrgIndex[nIndex]]);
	return NULL;
}

void CWispHeader::SetItem(int nIndex, WHITEM& HeaderItem)
{
	if( nIndex <= (int)m_vColumns.Count() )
	*m_vColumns[m_ColumnOrgIndex[nIndex]] = HeaderItem;
	Update();
}
int CWispHeader::GetItemIndex(int col)const
{
	if(col <= (int)m_vColumns.Count())
		return m_ColumnOrgIndex[col];	
	return 0;
}
int CWispHeader::DrawDragRect(WISP_RECT rc)
{	
	rc.x = rc.x + m_PrevDragPoint.x - m_DragBeginPt.x ;
	gpCurWisp->m_pCurDrawObj->DrawHeaderFrameRect(&m_ClientDC, &rc, STATUS_NORMAL);
	WISP_RECT	rcText={rc.x+HEADER_MARGIN, rc.y, rc.cx-2*HEADER_MARGIN, rc.cy};
	m_ClientDC.DrawString(m_vColumns[m_DragColumnIndex]->strHeading,&rcText, WISP_DT_SINGLELINE|WISP_DT_VCENTER|WISP_DT_END_ELLIPSIS);
	return 0;
}

