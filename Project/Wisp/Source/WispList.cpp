#include "StdAfx.h"
#include "WispList.h"

WISP_MSG_MAP_BEGIN(CWispList)
	WISP_MSG_MAP(WISP_WM_PRECREATE,OnPrecreate)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_BEGIN_DRAG,OnBeginDrag)
	WISP_MSG_MAP(WISP_WM_DRAG_MOVE,OnDragMove)
	WISP_MSG_MAP(WISP_WM_END_DRAG,OnEndDrag)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_LOST_FOCUS,OnLostFocus)
	WISP_MSG_MAP(WISP_WM_SCROLL_EVENT,OnScrollEvent)
	WISP_MSG_MAP(WISP_WM_TIMER,OnTimer)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_CMD_MAP_BEGIN(CWispList)
	WISP_MSG_CMD_MAP(WISP_WLI_EDIT_CMD_ID,OnEditCommand)
WISP_MSG_CMD_MAP_END


CWispList::CWispList()
{
	m_TextMargin = 3;
	m_ButtonSize.cx = 12;
	m_ButtonSize.cy = 16;
	m_RootItem.Style = WISP_WLIS_EXPANDED;
	m_RootItem.pParent = NULL;
	m_RootItem.nChecked = 0;
	m_OldTitleHeight = m_TitleHeight = 0;
	m_CtrlType = WISP_CTRL_LIST;
	m_TipPeriod = 700;
}

CWispList::~CWispList()
{
}

int	CWispListItem::GetLevel()
{
	CWispListItem*pItemParent;
	int Count=0;
	pItemParent = pParent;
	while(pItemParent)
	{
		pItemParent = pItemParent->pParent;
		Count++;
	}
	return Count-1;
}

int	CWispListItem::GetDispLine()
{
	int Count=ChildItemList.Count();
	for(CItemList::IT Iter = ChildItemList.Begin();Iter!=ChildItemList.End();Iter++)
	{
		if(Iter->Style & WISP_WLIS_EXPANDED)
			Count+=Iter->GetDispLine();
	}
	return Count;
}

bool CWispListItem::IsParentOf(HANDLE hItem)
{
	CWispListItem*pItem = (CWispListItem*)hItem;
	while(pItem->pParent)
	{
		pItem = pItem->pParent;
		if(pItem==this)
			return true;
	}
	return false;
}

bool CWispList::OnTimer(IN WISP_MSG*pMsg)
{
	if(pMsg->Timer.ID == WISP_WLI_TIMER_ID)
	{
		if(m_LastMousePos.x == pMsg->MsgMouseCltPT.x && m_LastMousePos.y == pMsg->MsgMouseCltPT.y)
		{
			CItemList::IT ItemIter;
			int Pos = PointToItem(m_LastMousePos,ItemIter);
			if(Pos>=LI_POS_CELL_AREA_START && Pos< LI_POS_CELL_AREA_END)
			{
				if(ShowItemTip(&(*ItemIter),Pos,GetItemText(&(*ItemIter),Pos))==false)
					HideItemTip();
			}
		}
	}
	return true;
}

bool CWispList::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	if(m_LastSelectIter==m_RootItem.ChildItemList.End())
		return true;
	ItemDBClickNotify(&(*m_LastSelectIter),m_LastClickCol);
	if(pMsg->KeyEvent.KeyType==WISP_VK_LBUTTON)
		SendCmdMsg(WISP_CMD_ITEM_LDBCLICK,m_LastClickCol,&(*m_LastSelectIter));
	else if(pMsg->KeyEvent.KeyType==WISP_VK_RBUTTON)
		SendCmdMsg(WISP_CMD_ITEM_RDBCLICK,m_LastClickCol,&(*m_LastSelectIter));
	return true;
}

bool CWispList::OnScrollEvent(IN WISP_MSG*pMsg)
{
	if(CWispWnd::OnScrollEvent(pMsg)==false)
		return false;
	if(pMsg->ScrollEvent.SBType == WISP_SB_VERT)
	{
		UpdateCurScrItem((int)pMsg->ScrollEvent.Delta);
		if(pMsg->ScrollEvent.Event==WISP_SB_PAGE_DOWN)
		{
			if(m_LastSelectIter!=m_RootItem.ChildItemList.End())
			{
				CItemList::IT ItemIter = m_CurItemIter;
				if(pMsg->ScrollEvent.Delta==0)
				{
					for(int n=1;n<m_nLinePerPage;n++)
						if(GetNextLineItem(ItemIter)==false)
							break;
				}
				if(ItemIter!=m_RootItem.ChildItemList.End())
					SelectItem(&(*ItemIter));
			}
		}
		if(pMsg->ScrollEvent.Event==WISP_SB_PAGE_UP)
		{
			if(m_LastSelectIter!=m_RootItem.ChildItemList.End())
			{
				CItemList::IT ItemIter = m_CurItemIter;
				if(pMsg->ScrollEvent.Delta<0)
				{
					for(int n=1;n<m_nLinePerPage;n++)
						if(GetNextLineItem(ItemIter)==false)
							break;
				}
				if(ItemIter!=m_RootItem.ChildItemList.End())
					SelectItem(&(*ItemIter));
			}
		}
	}
	return false;
}

HANDLE CWispList::InsertColumn(const WISP_CHAR*szText,int Width,UINT Style,CWispDIB*pIcon,int Pos)
{
	CColumnList::IT Iter;
	if(Pos<0)
	{
		if(m_ColumnList.Count()>0)
		{
			Iter = m_ColumnList.Last();
			Iter->Width = Iter->OrgWidth;
		}
		Iter = m_ColumnList.End();
	}
	else
		Iter = m_ColumnList[Pos];
	Iter = m_ColumnList.InsertBefore(Iter);
	Iter->szText = szText;
	Iter->Style = Style;
	Iter->pIcon = pIcon;
	if(Width<0)
		Iter->Width = m_ClientDC.GetTextExtent(szText)+m_TextMargin*2+2;
	else
		Iter->Width = Width;
	Iter->OrgWidth = Iter->Width;
	RecalcLayout();
	return &(*Iter);
}

bool CWispList::RemoveColumn(int Pos)
{
	if(Pos<0 || Pos>=m_ColumnList.Count())
		return false;
	CColumnList::IT Iter = m_ColumnList[Pos];
	m_ColumnList.Remove(Iter);
	RecalcLayout();
	return true;
}

HANDLE CWispList::InsertItem(const WISP_CHAR*szText,HANDLE hParent,UINT Style,CWispDIB*pIcon,int Pos)
{
	CWispListItem*pParentItem;
	if(hParent==NULL)
		pParentItem = &m_RootItem;
	else
		pParentItem = (CWispListItem*)hParent;
	if(pParentItem->Style&WISP_WLIS_CHECKED)
		Style|=WISP_WLIS_CHECKED;
	CItemList::IT ItemIter = pParentItem->ChildItemList.InsertBefore(pParentItem->ChildItemList[Pos]);
	CItemListCell::IT CellIter = ItemIter->ItemCellList.Append();
	CellIter->szText = szText;
	CellIter->pIcon = pIcon;
	CellIter->FontColor = m_FontColor;
	ItemIter->pParent = (CWispListItem*)pParentItem;
	ItemIter->Style = Style&(~WISP_WLIS_CHECKED);
	ItemIter->nSemiChecked = ItemIter->nChecked = 0;
	if(Style&WISP_WLIS_CHECKED)
		CheckItem(&(*ItemIter));
	if(pParentItem->Style & WISP_WLIS_EXPANDED)
		AdjustScrollBarMaxPos(WISP_SB_VERT,1);
	if(m_CurItemIter==m_RootItem.ChildItemList.End())
		m_CurItemIter = ItemIter;
	return &(*ItemIter);
}

bool CWispList::RemoveItem(HANDLE hItem)
{
	CWispListItem*pItem,*pParentItem;
	pItem = (CWispListItem*)hItem;
	if(pItem->Style&WISP_WLIS_CHECKED)
		pItem->pParent->nChecked--;
	if(pItem->Style&WISP_WLIS_SEMI_CHECKED)
		pItem->pParent->nSemiChecked--;
	UpdateItemTreeCheckState(pItem);
	if(&(*m_CurItemIter) == pItem || pItem->IsParentOf(&(*m_CurItemIter)))
	{
		CItemList :: IT CurItemIter = m_CurItemIter;
		if(GetPrevItem(m_CurItemIter)==false)
		{
			m_CurItemIter = CurItemIter;
			if(GetNextItem(m_CurItemIter)==false)
				m_CurItemIter = m_RootItem.ChildItemList.End();
		}
	}
	if(&(*m_LastSelectIter)==m_hCurHoverItem)
		HideItemTip();
	if(&(*m_LastSelectIter) == pItem || (m_LastSelectIter != m_RootItem.ChildItemList.End() && pItem->IsParentOf(&(*m_LastSelectIter))) )
		m_LastSelectIter = m_RootItem.ChildItemList.End();
	AdjustScrollBarMaxPos(WISP_SB_VERT,-pItem->GetDispLine());
	pParentItem = pItem->pParent;
	pParentItem->ChildItemList.Remove(*pItem);
	if(pParentItem != &m_RootItem && pParentItem->ChildItemList.Count()==0 && (pParentItem->Style&WISP_WLIS_EXPANDED))
		pParentItem->Style&=~WISP_WLIS_EXPANDED;
	return true;
}


HANDLE CWispList::InsertItemA(const char*szText,HANDLE hParent,UINT Style,CWispDIB*pIcon,int Pos)
{
	WISP_CHAR szBuffer[512];
	if(szText)
		TStrCpyLimit(szBuffer,szText,512);
	else
		szBuffer[0]=0;
	return InsertItem(szBuffer,hParent,Style,pIcon,Pos);
}

HANDLE CWispList::InsertItemW(const WCHAR*szText,HANDLE hParent,UINT Style,CWispDIB*pIcon,int Pos)
{
	WISP_CHAR szBuffer[512];
	TStrCpyLimit(szBuffer,szText,512);
	return InsertItem(szBuffer,hParent,Style,pIcon,Pos);
}

HANDLE CWispList::InsertItem(UINT Num,HANDLE hParent,WISP_CHAR*szFormat,UINT Style,CWispDIB*pIcon,int Pos)
{
	CWispListItemCell*pCell;
	HANDLE hItem = InsertItem(NULL,hParent,Style,pIcon,Pos);
	pCell = GetItemCell(hItem);
	pCell->szText.Format(szFormat,Num);
	return hItem;
}

bool CWispList::RemoveItem(int Pos,HANDLE hParent)
{
	CWispListItem*pParentItem;
	if(hParent==NULL)
		pParentItem = &m_RootItem;
	CItemList::IT Iter = pParentItem->ChildItemList[Pos];
	return RemoveItem((HANDLE)&(*Iter));
}

HANDLE CWispList::GetColumn(int Pos)
{
	if(Pos < 0 || Pos > m_ColumnList.Count())
		return NULL;
	return (HANDLE)&(*m_ColumnList[Pos]);
}

bool CWispList::SetColumnWidth(int Col,int Width)
{
	HANDLE hColumn;
	hColumn = GetColumn(Col);
	if(hColumn==NULL)
		return false;
	return SetColumnWidth(hColumn,Width);
}

bool CWispList::SetColumnWidth(HANDLE hColumn,int Width)
{
	CWispColumnItem*pColItem = (CWispColumnItem*)hColumn;
	pColItem->Width = Width;
	RecalcLayout();
	return true;
}

bool CWispList::SetColumnText(HANDLE hColumn,WISP_PCSTR szText)
{
	CWispColumnItem*pColItem = (CWispColumnItem*)hColumn;
	pColItem->szText = szText;
	return true;
}

bool CWispList::SetColumnIcon(HANDLE hColumn,CWispDIB*pDIB)
{
	CWispColumnItem*pColItem = (CWispColumnItem*)hColumn;
	pColItem->pIcon = pDIB;
	return true;
}

bool CWispList::SetColumnData(HANDLE hColumn,NUM_PTR Data)
{
	CWispColumnItem*pColItem = (CWispColumnItem*)hColumn;
	pColItem->Data = Data;
	return true;
}

bool CWispList::SetColumnInfo(HANDLE hColumn,WISP_PCSTR szText,CWispDIB*pDIB,NUM_PTR Data)
{
	CWispColumnItem*pColItem = (CWispColumnItem*)hColumn;
	pColItem->szText = szText;
	pColItem->pIcon = pDIB;
	pColItem->Data = Data;
	return true;
}

bool CWispList::SetItemTextA(HANDLE hItem,int Col,const CHAR*szText)
{
	WISP_CHAR szBuffer[512];
	TStrCpyLimit(szBuffer,szText,512);
	return SetItemText(hItem,Col,szBuffer);
}

bool CWispList::SetItemText(HANDLE hItem,int Col,const WISP_CHAR*szText)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	CODE_ASSERT(pCell);
	if(pCell==NULL)
		return false;
	pCell->szText = szText;
	return true;
}

bool CWispList::SetItemColorText(HANDLE hItem,int Col,const WISP_COLOR_CHAR*szText)
{
	WISP_CHAR*pszText;
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	CODE_ASSERT(pCell);
	if(pCell==NULL)
		return false;
	int Length = (TStrLen(szText)+1)*2;
	pCell->szText.Preallocate(Length+2);
	pszText = pCell->szText;
	memcpy(&pszText[2],szText,Length*2);
	pCell->szText[0] = 0xFFFF;
	pCell->szText[1] = 0xFFFF;
	pCell->szText.m_Length = Length/2-1;
	return true;
}

bool CWispList::SetItemData(HANDLE hItem,int Col,NUM_PTR Data)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	CODE_ASSERT(pCell);
	if(pCell==NULL)
		return false;
	pCell->Data = Data;
	return true;
}

bool CWispList::SetItemNum(HANDLE hItem,int Col,UINT Num,const WISP_CHAR*szFormat)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	CODE_ASSERT(pCell);
	if(pCell==NULL)
		return false;
	pCell->szText.Format(szFormat,Num);
	return true;
}

bool CWispList::SetItemIcon(HANDLE hItem,int Col,CWispDIB*pIcon)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	CODE_ASSERT(pCell);
	if(pCell==NULL)
		return false;
	pCell->pIcon = pIcon;
	return true;
}

bool CWispList::SetItemTextColor(HANDLE hItem,int Col,COLORREF Color)
{
	if(Col>=0)
	{
		CWispListItemCell*pCell = GetItemCell(hItem,Col);
		CODE_ASSERT(pCell);
		if(pCell==NULL)
			return false;
		pCell->FontColor = Color;
	}
	else
	{
		CWispListItem*pItem = (CWispListItem*)hItem;
		for(CItemListCell::IT Iter = pItem->ItemCellList.Begin();Iter!=pItem->ItemCellList.End();Iter++)
		{
			Iter->FontColor = Color;
		}
	}
	return true;
}

bool CWispList::SetItemLineColor(HANDLE hItem,COLORREF Color)
{
	((CWispListItem*)hItem)->LineColor = Color;
	return true;
}

bool CWispList::ModifyItemStyle(HANDLE hItem,UINT AddStyle,UINT RemoveStyle)
{
	CWispListItem*pItem = (CWispListItem*)hItem;
	if(AddStyle)
		pItem->Style|=AddStyle;
	if(RemoveStyle)
		pItem->Style&=~RemoveStyle;
	return true;
}

bool CWispList::ClearChildItem(HANDLE hItem)
{
	if(hItem == NULL)
	{
		if(m_LastSelectIter!=m_RootItem.ChildItemList.End() && m_RootItem.IsParentOf(&(*m_LastSelectIter)))
			m_LastSelectIter = m_RootItem.ChildItemList.End();
		m_RootItem.ChildItemList.Clear();
		m_CurItemIter = m_RootItem.ChildItemList.End();
		m_RootItem.nSemiChecked = m_RootItem.nChecked = 0;
		SetScrollBarInfo(WISP_SB_VERT,0,0,m_ScrollBar[WISP_SB_VERT]->Page);
		return true;
	}
	CWispListItem*pItem = (CWispListItem*)hItem;
	if(pItem->Style&WISP_WLIS_EXPANDED)
		AdjustScrollBarMaxPos(WISP_SB_VERT,-pItem->GetDispLine());
	if(m_LastSelectIter!=m_RootItem.ChildItemList.End() && pItem->IsParentOf(&(*m_LastSelectIter)))
		m_LastSelectIter = m_RootItem.ChildItemList.End();
	if(m_CurItemIter!=m_RootItem.ChildItemList.End() && pItem->IsParentOf(&(*m_CurItemIter)))
		m_CurItemIter = *pItem;
	pItem->ChildItemList.Clear();
	pItem->nSemiChecked = pItem->nChecked = 0;
	pItem->Style&=~WISP_WLIS_EXPANDED;
	return true;
}

int CWispList::EmptyChildItemContext(HANDLE hItem)
{
	CWispListItem*pItem = (CWispListItem*)hItem;
	if(pItem==NULL)
		pItem = &m_RootItem;
	for(CItemList::IT Iter=pItem->ChildItemList.Begin();Iter!=pItem->ChildItemList.End();Iter++)
	{
		EmptyItemContext(&(*Iter));
	}
	return pItem->ChildItemList.Count();
}

void CWispList::EmptyItemContext(HANDLE hItem)
{
	CWispListItem*pItem = (CWispListItem*)hItem;
	for(CItemListCell::IT Iter=pItem->ItemCellList.Begin();Iter!=pItem->ItemCellList.End();Iter++)
	{
		Iter->szText.Empty();
		Iter->FontColor = m_FontColor;
		Iter->Data = 0;
	}
}

int CWispList::SetItemChildCount(HANDLE hItem,int Count)
{
	HANDLE hChildItem,hDelItem;
	int Delta;
	if(Count<0)
		return 0;
	if(hItem==NULL)
		hItem = &m_RootItem;
	Delta = Count - GetItemCount(hItem,false);
	if(Delta<0)
	{
		hChildItem = GetItem(Count,hItem);
		while(Delta<0)
		{
			hDelItem = hChildItem;
			hChildItem = GetNextItem(hChildItem);
			RemoveItem(hDelItem);
			Delta++;
		}
	}
	if(Delta>0)
	{
		while(Delta>0)
		{
			InsertItem((WISP_PCSTR)NULL,hItem);
			Delta--;
		}
	}
	return Delta;
}

bool CWispList::ShowColumnTitle(bool bShow)
{
	if((m_Style & WISP_WLS_COLUMN_TITLE)==0)
		return false;
	if(bShow)
	{
		if(m_TitleHeight>0)
			return true;
		m_OldTitleHeight = m_TitleHeight;
		m_TitleHeight = 0;
	}
	else
	{
		if(m_TitleHeight<=0)
			return true;
		m_TitleHeight = m_OldTitleHeight;
	}
	RecalcLayout();
	return true;
}

void CWispList::EnableVisible(HANDLE hItem,int nPrevLine)
{
	int Index;
	CWispListItem*pItem = (CWispListItem*)hItem;
	while(pItem->pParent!=&m_RootItem)
	{
		if((pItem->pParent->Style & WISP_WLIS_EXPANDED)==0)
			ExpandItem(pItem->pParent);
		pItem = pItem->pParent;
	}
	pItem = (CWispListItem*)hItem;
	CItemList::IT ItemIter = *pItem;
	if(nPrevLine<0)
		nPrevLine = m_nLinePerPage/2;
	while(nPrevLine>0 && GetPrevLineItem(ItemIter))
	{
		pItem = &(*ItemIter);
		nPrevLine--;
	}
	Index = 0;
	ItemIter = m_RootItem.ChildItemList.Begin();
	while(ItemIter!=m_RootItem.ChildItemList.End())
	{
		if(&(*ItemIter) == pItem)
		{
			SetScrollBarCurPos(WISP_SB_VERT,Index);
			return;
		}
		if(GetNextLineItem(ItemIter)==false)
			return;
		Index++;
	}
}

bool CWispList::IsItemVisible(HANDLE hItem)
{
	CWispListItem*pItem = (CWispListItem*)hItem;
	CItemList::IT Iter = m_CurItemIter;
	for(int n=0;n<m_nLinePerPage;n++)
	{
		if(&(*Iter)==pItem)
			return true;
		if(GetNextLineItem(Iter)==false)
			break;
	}
	return false;
}

bool CWispList::IsItemTextFullVisible(HANDLE hItem,int Col)
{
	int TextWidth;
	CWispListItemCell*pCell;
	pCell = GetItemCell(hItem,Col);
	TextWidth = m_ClientDC.GetTextExtent(pCell->szText)+m_TextMargin+m_TextMargin;
	if(Col==0)
	{
		if(m_Style&WISP_WLS_TREE)
			TextWidth += m_ButtonSize.cx;
		if(m_Style&WISP_WLS_CHECK_BOX)
			TextWidth += m_ButtonSize.cx;
	}
	if(pCell->pIcon)
		TextWidth += pCell->pIcon->Width();
	return TextWidth<=m_ColumnList[Col]->ColRect.cx;
}

bool CWispList::OnPrecreate(WISP_MSG*pMsg)
{
	m_ListBTIndex = 0;
	m_FontColor = WispColor(SC_BLACK);
	m_SelectFontColor = WispColor(SC_WHITE);
	m_LostFocusSelBKColor = m_SelectBKColor =SYS_COLOR[SC_UNNAMED_13];
	m_HorzLineColor = WispColor(SC_BLACK);
	m_VertLineColor = WispColor(SC_LIGHT_BLUE);
	m_ColTitleFontColor = WispColor(SC_WHITE);
	m_TitleHeight = m_ClientDC.m_pFont->m_Height + 4 + 2;
	EnableScrollBar(WISP_SB_VERT);
	EnableScrollBar(WISP_SB_HORZ);
	return true;
}

bool CWispList::OnCreate(WISP_MSG*pMsg)
{
	if((m_Style&WISP_WLS_COLUMN_TITLE)==0)
		STZeroMemory(m_TitleRect);
	m_EditCtrl.Create(NULL,0,0,0,0,this,WISP_WLI_EDIT_CMD_ID,WISP_ES_LEFT|WISP_ES_AUTOHSCROLL|WISP_WS_BORDER,WISP_SH_HIDDEN);
	m_TipFullItemTextWnd.Create(NULL,0,0,0,0,NULL,WISP_WLI_TIP_CMD_ID,WISP_WS_NULL,WISP_SH_HIDDEN);
	return true;
}

bool CWispList::InitWnd()
{
	m_pDragColumn = NULL;
	m_ColTotalWidth = 0;
	m_nLinePerPage = 0;
	m_HorzScrollSpace = m_ClientDC.m_pFont->GetCharWidth(WISP_STR('0'))/2;
	m_LastSelectIter = m_CurItemIter = m_RootItem.ChildItemList.End();
	m_bSaveItem = true;
	m_bTipTimerSet = false;
	m_LastMousePos.x = m_LastMousePos.y = -1;
	m_LastSelectIter = m_RootItem.ChildItemList.End();
	m_ButtonSize.cy = m_ClientDC.GetTextHeight()+4;
	m_ProcEndEditItem = false;
	return CWispWnd::InitWnd();
}

bool CWispList::Destroy()
{
	m_TipFullItemTextWnd.Destroy();
	m_LastSelectIter = m_RootItem.ChildItemList.End();
	m_RootItem.ChildItemList.Clear();
	m_RootItem.nChecked = 0;
	m_RootItem.nSemiChecked = 0;
	m_RootItem.Style = WISP_WLIS_EXPANDED;
	m_ColumnList.Clear();
	return CWispWnd::Destroy();
}

void CWispList::RecalcLayout()
{
	CWispWnd::RecalcLayout();
	m_TitleRect.x = m_TitleRect.y = 0;
	m_TitleRect.cx = m_ClientRect.cx;
	if(m_Style & WISP_WLS_COLUMN_TITLE)
		m_TitleRect.cy = m_TitleHeight;
	else
		m_TitleRect.cy = 0;
	m_ListRect.x = m_ListRect.y = 0;
	m_ListRect.y += m_TitleRect.cy;
	m_ListRect.cy = m_ClientRect.cy - m_TitleRect.cy;
	m_nLinePerPage = m_ClientRect.cy;
	if(m_Style&WISP_WLS_COLUMN_TITLE)
		m_nLinePerPage-=m_TitleRect.cy;
	m_nLinePerPage +=m_ButtonSize.cy/3;
	m_nLinePerPage /=m_ButtonSize.cy;
	MIN_LIMIT(m_nLinePerPage,0);
	if(m_ScrollBar[WISP_SB_VERT] && m_nLinePerPage!=(int)m_ScrollBar[WISP_SB_VERT]->Page)
		SetScrollBarPage(WISP_SB_VERT,m_nLinePerPage);
	m_TreeSpace = 0;
	if(m_Style&WISP_WLS_TREE)
		m_TreeSpace += m_ButtonSize.cx;
	if(m_Style&WISP_WLS_CHECK_BOX)
		m_TreeSpace += m_ButtonSize.cx;
	if(m_ScrollBar[WISP_SB_HORZ])
	{
		if(m_ClientRect.cx > 0 && m_ScrollBar[WISP_SB_HORZ]->Page != m_ClientRect.cx/m_HorzScrollSpace)
			SetScrollBarPage(WISP_SB_HORZ,m_ClientRect.cx/m_HorzScrollSpace);
	}
	m_ColTotalWidth=0;
	int x=0;
	for(CColumnList::IT Iter = m_ColumnList.Begin();Iter!=m_ColumnList.End();Iter++)
	{
		Iter->ColRect.x = x;
		Iter->ColRect.y = m_TitleRect.y;
		if(Iter == m_ColumnList.Last())
		{
			if(m_ColTotalWidth+Iter->Width<m_ClientRect.cx)
				Iter->Width = m_ClientRect.cx - m_ColTotalWidth;
			m_ColTotalWidth+=Iter->Width;
			if(m_ScrollBar[WISP_SB_HORZ] && m_ColTotalWidth!=m_ScrollBar[WISP_SB_HORZ]->MaxPos*m_HorzScrollSpace)
			{
				if(m_ScrollBar[WISP_SB_HORZ]->bHide && Iter->Width>=Iter->OrgWidth+m_pWispBase->m_Metrics[WISP_SM_SCROLL_BAR_SIZE])
					m_ColTotalWidth-=m_pWispBase->m_Metrics[WISP_SM_SCROLL_BAR_SIZE];
				SetScrollBarRange(WISP_SB_HORZ,m_ColTotalWidth/m_HorzScrollSpace);
			}
		}
		else
			m_ColTotalWidth+=Iter->Width;
		Iter->ColRect.cx = Iter->Width;
		Iter->ColRect.cy = m_TitleRect.cy;
		Iter->SplitRect.x = x + Iter->ColRect.cx - 2;
		Iter->SplitRect.y = m_TitleRect.y+2;
		Iter->SplitRect.cx = 2;
		Iter->SplitRect.cy = m_TitleRect.cy - 4;
		Iter->TestSplitRect.x = Iter->SplitRect.x - 2;
		Iter->TestSplitRect.cx = Iter->SplitRect.cx + 4;
		Iter->TestSplitRect.y = m_TitleRect.y;
		Iter->TestSplitRect.cy = m_TitleRect.cy;
		x+=Iter->Width;
	}
	m_ListRect.cx = m_ColTotalWidth;
	UpdateCurScrItem(0);
}

bool CWispList::OnBeginDrag(WISP_MSG*pMsg)
{
	m_pWispBase->ChangeCursorType(WISP_CT_RESIZE_HORZ);
	return true;
}

bool CWispList::OnDragMove(WISP_MSG*pMsg)
{
	int dx;
	bool bDragMove;
	WISP_POINT pt;
	CColumnList::IT Iter;
	pt.x = pMsg->MsgMouseCltPT.x + (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
	pt.y = pMsg->MsgMouseCltPT.y;
	dx = pMsg->DragEvent.DeltaX;
	Iter = *m_pDragColumn;
	if(Iter==m_ColumnList.Last())
	{
		bDragMove = true;
		if(dx<0)
		{
			if(pt.x<Iter->ColRect.x+Iter->TestSplitRect.cx)
			{
				if(Iter->Width > Iter->TestSplitRect.cx)
					dx = Iter->TestSplitRect.cx - Iter->Width;
				else
					bDragMove = false;
			}
		}
		if(bDragMove)
		{
			Iter->Width+=dx;
			m_ColTotalWidth+=dx;
			SetScrollBarRange(WISP_SB_HORZ,m_ColTotalWidth/m_HorzScrollSpace);
			RecalcLayout();
			Update();
		}
		return true;
	}
	Iter++;
	bDragMove = true;
	if(dx>0)
	{
		if(pt.x < m_pDragColumn->SplitRect.x+m_pDragColumn->SplitRect.cx/2)
			bDragMove = false;
		else if(pt.x >= Iter->ColRect.x + Iter->Width - Iter->TestSplitRect.cx)
		{
			if(Iter->Width > Iter->TestSplitRect.cx)
				dx = Iter->Width - Iter->TestSplitRect.cx;
			else
				bDragMove = false;
		}
	}
	else
	{
		if(pt.x >= m_pDragColumn->SplitRect.x+m_pDragColumn->SplitRect.cx/2)
			bDragMove = false;
		else if(pt.x < m_pDragColumn->ColRect.x + m_pDragColumn->TestSplitRect.cx)
		{
			if(m_pDragColumn->Width > m_pDragColumn->TestSplitRect.cx && pt.x > 0)
				dx = m_pDragColumn->TestSplitRect.cx - m_pDragColumn->Width;
			else
				bDragMove = false;
		}
	}
	if(bDragMove)
	{
		m_pDragColumn->Width+=dx;
		Iter->Width-=dx;
		RecalcLayout();
		Update();
	}
	return true;
}

bool CWispList::OnEndDrag(WISP_MSG*pMsg)
{
	m_pWispBase->ChangeCursorType(WISP_CT_ARROW);
	m_pDragColumn = NULL;
	return true;
}

bool CWispList::OnMouseMove(WISP_MSG*pMsg)
{
	WISP_RECT TestRC;
	WISP_POINT pt = pMsg->MsgMouseCltPT;
	if(m_pDragColumn && PtInRect(&m_ClientRect,&pMsg->MsgMouseWndPT)==false)
	{
		m_pWispBase->ChangeCursorType(WISP_CT_ARROW);
		m_pDragColumn = NULL;
		return true;
	}
	pt.x+=(int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
	if(m_Style&WISP_WLS_COLUMN_TITLE)
	{
		m_pDragColumn = NULL;
		if(m_Style&WISP_WLS_VERT_LINE)
		{
			for(CColumnList::IT Iter = m_ColumnList.Begin();Iter!=m_ColumnList.End();Iter++)
			{
				TestRC.x = Iter->TestSplitRect.x;
				TestRC.cx = Iter->TestSplitRect.cx;
				TestRC.y = 0;
				TestRC.cy = m_ClientRect.cy;
				if(pt.x < TestRC.x)
					break;
				if(PtInRect(&TestRC,pt) && (Iter->Style&WISP_WLCS_FIXED)==0)
				{
					m_pDragColumn = &(*Iter);
					break;
				}
			}
		}
		else if(pt.y>=m_TitleRect.y && pt.y<m_TitleRect.y+m_TitleRect.cy)
		{
			for(CColumnList::IT Iter = m_ColumnList.Begin();Iter!=m_ColumnList.End();Iter++)
			{
				if(pt.x < Iter->TestSplitRect.x)
					break;
				if(PtInRect(&Iter->TestSplitRect,pt) && (Iter->Style&WISP_WLCS_FIXED)==0)
				{
					m_pDragColumn = &(*Iter);
					break;
				}
			}
		}
		if(PtInRect(&m_ClientRect,&pMsg->MsgMouseWndPT))
		{
			if(m_pDragColumn && m_pWispBase->m_CursorType != WISP_CT_RESIZE_HORZ)
				m_pWispBase->ChangeCursorType(WISP_CT_RESIZE_HORZ);
			else if(m_pDragColumn ==NULL && m_pWispBase->m_CursorType != WISP_CT_ARROW)
				m_pWispBase->ChangeCursorType(WISP_CT_ARROW);
			m_LastMousePos = pMsg->MsgMouseCltPT;
			if(m_TipFullItemTextWnd.IsVisible() && PtInRect(&m_TipFullItemTextWnd.m_ScrWindowRect,pMsg->MsgMouseScrPT)==false)
				HideItemTip();
			if(m_bTipTimerSet==false)
			{
				InsertTimer(WISP_WLI_TIMER_ID,m_TipPeriod);
				m_bTipTimerSet=true;
			}
		}
	}
	if(m_Style & WISP_WLS_FOLLOW_SEL)
	{
		HANDLE	hItem = PointToItem(pt);
		if(hItem)
		{
			SelectItem(hItem);
		}
	}

	return true;
}

bool CWispList::OnMouseLeave(WISP_MSG*pMsg)
{
	if(m_pDragColumn && m_pWispBase->m_CursorType != WISP_CT_ARROW)
	{
		m_pWispBase->ChangeCursorType(WISP_CT_ARROW);
		m_pDragColumn = NULL;
	}
	if(pMsg->MouseEvent.hWndMouseAt == &m_TipFullItemTextWnd)
		return false;
	else
		HideItemTip();
	return true;
}

bool CWispList::OnKeyEvent(WISP_MSG*pMsg)
{
	int Index,Pos;
	WISP_POINT TmpPoint;
	WISP_POINT pt;
	pt = pMsg->MsgMouseCltPT;
	switch(pMsg->KeyEvent.KeyType)
	{
	case WISP_VK_RBUTTON:
		{
			if(pt.x>m_ClientRect.cx || pt.y>m_ClientRect.cy || pMsg->KeyEvent.bKeyDown==false)
				return true;
			CItemList::IT ItemIter;
			Pos = PointToItem(pMsg->MsgMouseCltPT,ItemIter);
			switch(Pos)
			{
			case LI_POS_COLUMN:
				TmpPoint=pMsg->MsgMouseCltPT;
				TmpPoint.y=m_TitleRect.y + m_TitleRect.cy+1;
				Pos = PointToItem(TmpPoint,ItemIter);
				Index = Pos - LI_POS_CELL_AREA_START;
				TitleRClickNotify(Index);
				PostEventMsg(WISP_CMD_TITLE_RCLICK,Index,NULL);
				break;
			case LI_POS_TREE_BT:
			case LI_POS_CHECK_BOX:			
			case LI_POS_NON_AREA:
				break;
			default:
				Index = Pos - LI_POS_CELL_AREA_START;
				if(ItemIter->Style & WISP_WLIS_SELECTED)
				{
					if(Index >=0 && Index < m_ColumnList.Count() && m_EditCtrl.m_ShowMode==WISP_SH_HIDDEN)
					{
						ItemRClickNotify(&(*ItemIter),Index);
						PostEventMsg(WISP_CMD_CTRL_RCLICK,Index,&(*ItemIter));
					}
				}
				break;
			}
		}
		break;
	case WISP_VK_LBUTTON:
		{
			if(pt.x>m_ClientRect.cx || pt.y>m_ClientRect.cy)
				return true;
			CItemList::IT ItemIter;
			if(m_Style&WISP_WLS_COLUMN_TITLE && m_pDragColumn)
			{
				if(pMsg->KeyEvent.bKeyDown)
					BeginDrag();
				else
					EndDrag();
				return true;
			}
			if(pMsg->KeyEvent.bKeyDown)
			{
				
				Pos = PointToItem(pMsg->MsgMouseCltPT,ItemIter);
				switch(Pos)
				{
				case LI_POS_TREE_BT:
					ToggleExpandItem(&(*ItemIter));
					break;
				case LI_POS_CHECK_BOX:
					ToggleCheckItem(&(*ItemIter));
					break;
				case LI_POS_COLUMN:
					TmpPoint=pMsg->MsgMouseCltPT;
					TmpPoint.y=m_TitleRect.y + m_TitleRect.cy+1;
					Pos = PointToItem(TmpPoint,ItemIter);
					Index = Pos - LI_POS_CELL_AREA_START;
					TitleClickNotify(Index);
					PostEventMsg(WISP_CMD_TITLE_CLICK,Index,NULL);
				case LI_POS_NON_AREA:
					if(m_LastSelectIter!=m_RootItem.ChildItemList.End() && (m_Style & WISP_WLS_SELECTED_ALWAYS)==0)
						UnselectItem(&(*m_LastSelectIter));					
					break;
				default:
					Index = Pos - LI_POS_CELL_AREA_START;
					if(ItemIter->Style & WISP_WLIS_SELECTED)
					{
						if(Index >=0 && Index < m_ColumnList.Count() && m_EditCtrl.m_ShowMode==WISP_SH_HIDDEN)
						{
							if(m_ColumnList[Index]->Style&WISP_WLCS_EDITABLE)
							{
								BeginEditItem(&(*ItemIter),Index);
							}
							else
							{
								ItemClickNotify(&(*ItemIter),Index);
								m_LastClickCol = Index;
								PostEventMsg(WISP_CMD_CTRL_CLICK,Index,&(*ItemIter));
							}
						}
						if((m_Style & WISP_WLS_MULTI_SELECT) && m_pWispBase->m_KeyMap[WISP_VK_CONTROL])
							UnselectItem(&(*ItemIter));
					}
					else
					{
						if((m_Style & WISP_WLS_MULTI_SELECT)==0 || m_pWispBase->m_KeyMap[WISP_VK_CONTROL]==false)
						{
							if(m_LastSelectIter!=m_RootItem.ChildItemList.End())
								UnselectItem(&(*m_LastSelectIter));
						}
						SelectItem(&(*ItemIter));
					}
					break;
				}
			}
			Update();
		}
		break;
	case WISP_VK_UP:
	case WISP_VK_DOWN:
		if(pMsg->KeyEvent.bKeyDown && (m_Style&WISP_WLS_MULTI_SELECT)==0)
		{
			if(m_LastSelectIter!=m_RootItem.ChildItemList.End())
			{
				bool Result;
				if(IsItemVisible(&(*m_LastSelectIter))==false)
				{
					EnableVisible(&(*m_LastSelectIter));
				}
				CItemList :: IT NewSelectIter = m_LastSelectIter;
				if(pMsg->KeyEvent.KeyType==WISP_VK_UP)
				{
					Result = GetPrevLineItem(NewSelectIter);
					if(m_LastSelectIter == m_CurItemIter)
						SendScrollEvent(WISP_SB_VERT,WISP_SB_DEC);
				}
				else
				{
					Result = GetNextLineItem(NewSelectIter);
					if(GetItemScrLine(&(*m_LastSelectIter))==m_nLinePerPage-1)
						SendScrollEvent(WISP_SB_VERT,WISP_SB_INC);
				}
				if(Result)
				{
					SelectItem(&(*NewSelectIter));
					Update();
				}
			}
			else
			{
				if(m_RootItem.ChildItemList.Count())
				{
					SelectItem(&(*m_RootItem.ChildItemList.Begin()));
					EnableVisible(&(*m_LastSelectIter));
					Update();
				}
			}
		}
		break;
	case WISP_VK_LEFT:
		if(pMsg->KeyEvent.bKeyDown && m_LastSelectIter!=m_RootItem.ChildItemList.End() && m_LastSelectIter->GetLevel()>0)
		{
			EnableVisible(m_LastSelectIter->pParent);
			SelectItem(m_LastSelectIter->pParent);
		}
		break;
	case WISP_VK_RIGHT:
		if(pMsg->KeyEvent.bKeyDown && m_LastSelectIter!=m_RootItem.ChildItemList.End())
			ExpandItem(&(*m_LastSelectIter));
		break;
	case WISP_VK_RETURN:
		if(pMsg->KeyEvent.bKeyDown && m_LastSelectIter!=m_RootItem.ChildItemList.End())
			ToggleExpandItem(&(*m_LastSelectIter));
		break;
	case WISP_VK_SPACE:
		if((m_Style & WISP_WLS_CHECK_BOX) && pMsg->KeyEvent.bKeyDown && m_LastSelectIter!=m_RootItem.ChildItemList.End())
			ToggleCheckItem(&(*m_LastSelectIter));
		break;
	}
	HideItemTip();
	return true;
}

bool CWispList::OnEditCommand(WISP_MSG*pMsg)
{
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_EN_INPUT_KEY_DOWN:
		switch(pMsg->Command.Param1)
		{
		case WISP_VK_RETURN:
			EndEditItem(true);
			break;
		case WISP_VK_ESCAPE:
			EndEditItem(false);
			break;
		}
		break;
	case WISP_CMD_EN_KILLFOCUS:
		if(m_ProcEndEditItem==false)
			OnEndEditItem();
		return false;
	default:
		break;
	}
	return true;
}

bool CWispList::OnUpdateClient(WISP_MSG*pMsg)
{
	WISP_RECT rc,SplitRC,ClipRect;
	if( (m_Style & WISP_WS_BACK_TRANS)==0)
	{
		if(m_pBKDIB)
			m_ClientDC.DrawDIBTiled(m_pBKDIB);
		else if(m_bBGColor)
			m_WindowDC.DrawFullRect(&m_ClientRect, m_crBGColor);
		else
			m_pWispBase->m_pCurDrawObj->DrawCtrlClient(&m_WindowDC,&m_ClientRect);
	}
	CItemList::IT ItemIter = m_CurItemIter;
	if(ItemIter!=m_RootItem.ChildItemList.End())
	{
		for(int iLine=0; iLine<m_nLinePerPage;iLine++)
		{
			DrawListItem(iLine,ItemIter);
			if(GetNextLineItem(ItemIter)==false)
			{
				if(m_Style&WISP_WLS_HORZ_LINE)
					m_ClientDC.DrawHLine(0,m_ClientRect.cx-1,m_ListRect.y+(iLine+1)*m_ButtonSize.cy,m_HorzLineColor);
				break;
			}
		}
	}
	if(m_Style&WISP_WLS_COLUMN_TITLE)
	{
		m_ClientDC.SetTextColor(m_ColTitleFontColor);
		m_pWispBase->m_pCurDrawObj->DrawListColumnTitleBK(&m_ClientDC,&m_TitleRect);
		rc = m_TitleRect;
		rc.x = m_TextMargin - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
		for(CColumnList::IT ColIter = m_ColumnList.Begin();ColIter!=m_ColumnList.End();ColIter++)
		{
			ClipRect = ColIter->ColRect;
			ClipRect.x -= (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
			m_ClientDC.EnableClipRect(&ClipRect);
			rc.cx = ColIter->Width - m_TextMargin*2;
			if(ColIter->pIcon)
			{
				m_ClientDC.DrawDIB(rc.x,rc.y + CENTER_ALGN(ColIter->pIcon->m_Rect.cy,rc.cy),ColIter->pIcon);
				int Width = ColIter->pIcon->Width()+m_TextMargin;
				rc.x+=Width;
				rc.cx-=Width;
			}
			DrawColumnItemText(&(*ColIter),&rc);
			rc.x += rc.cx+m_TextMargin*2;
			SplitRC = ColIter->SplitRect;
			SplitRC.x -= (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
			m_ClientDC.DrawFrameRect(&SplitRC,false);
			m_ClientDC.DisableClipRect();
			if(m_Style & WISP_WLS_VERT_LINE)
			{
				SplitRC.cx = 2;
				SplitRC.y = m_ListRect.y+2;
				SplitRC.cy = m_ListRect.cy-4;
				m_ClientDC.DrawFrameRect(&SplitRC,false);
			}
		}
	}
	return false;
}

int CWispList::GetItemScrLine(HANDLE hItem)
{
	int Index = 0;
	CItemList::IT ItemIter;
	ItemIter = m_CurItemIter;
	while(Index < m_nLinePerPage)
	{
		if(&(*ItemIter) == hItem)
			return Index;
		if(GetNextLineItem(ItemIter)==false)
			break;
		Index++;
	}
	if(&(*ItemIter) == hItem)
		return Index;
	return -1;
}

bool CWispList::GetItemCellRect(HANDLE hItem,int Col,WISP_RECT*pRECT)
{
	int nScrLine;
	nScrLine = GetItemScrLine(hItem);
	if(nScrLine<0)
		return false;
	pRECT->y = m_ListRect.y + nScrLine*m_ButtonSize.cy;
	pRECT->cy = m_ButtonSize.cy;
	pRECT->cx = pRECT->x = 0;
	for(CColumnList::IT ColIter=m_ColumnList.Begin();ColIter!=m_ColumnList.End();ColIter++)
	{
		if(Col==0)
		{
			pRECT->x = ColIter->ColRect.x;
			pRECT->cx = ColIter->ColRect.cx;
			break;
		}
		Col--;
	}
	return true;
}

HANDLE CWispList::GetScrStartItem()
{
	if(m_CurItemIter == m_RootItem.ChildItemList.End())
		return NULL;
	return &(*m_CurItemIter);
}

void CWispList::DrawListItem(int iLine,const CItemList::IT&ItemIter)
{
	int LimitX,Level,X,Col;
	WISP_RECT rc;
	CItemListCell::IT CellIter;
	CColumnList::IT ColIter;
	CWispListItem*pParentItem = ItemIter->pParent;
	CWispListItem*pItem = &(*ItemIter);
	Level = pItem->GetLevel();
	rc.y = m_ListRect.y + m_ButtonSize.cy * iLine;
	rc.cy = m_ButtonSize.cy;
	if((m_Style&WISP_WLS_OPTION_TREE)==WISP_WLS_OPTION_TREE)
	{
		if(pItem->ChildItemList.Count())
		{
			rc.x = m_ListRect.x + Level * m_TreeSpace - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
			rc.cx = m_ListRect.cx;
			m_ClientDC.DrawFullRect(&rc,SYS_COLOR[SC_GRAY]);
		}
		for(int n=0;n<=Level;n++)
		{
			if(n%2==0)
			{
				rc.x = m_ListRect.x - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace+m_ButtonSize.cx*n;
				rc.cx = m_ButtonSize.cx;
				m_ClientDC.DrawFullRect(&rc,SYS_COLOR[SC_GRAY]);
			}
		}
	}
	rc.x = m_ListRect.x + Level * m_TreeSpace - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
	ColIter = m_ColumnList.Begin();
	CellIter = ItemIter->ItemCellList.Begin();
	Col = 0;
	while(CellIter!=ItemIter->ItemCellList.End() && ColIter!= m_ColumnList.End())
	{
		WISP_RECT ClipRect;
		ClipRect.x = ColIter->ColRect.x - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
		ClipRect.y = rc.y;
		ClipRect.cx = ColIter->ColRect.cx;
		ClipRect.cy = m_ButtonSize.cy;
		if(Col==0)
		{
			if(ItemIter->Style&WISP_WLIS_COLOR_LINE)
			{
				WISP_RECT BKrc;
				BKrc.x = 0;
				BKrc.y = rc.y;
				BKrc.cx = m_ClientRect.cx;
				BKrc.cy = rc.cy;
				m_ClientDC.DrawFullRect(&BKrc,ItemIter->LineColor);
			}
			if(((m_Style&WISP_WLS_SELECTED_ALWAYS) || IsFocus() ) && (ItemIter->Style&WISP_WLIS_SELECTED) && (m_Style&WISP_WLS_HIDE_SELECTED)==0)
			{
				WISP_RECT BKrc;
				BKrc.x = 0;
				BKrc.y = rc.y;
				BKrc.cx = m_ClientRect.cx;
				BKrc.cy = rc.cy;
				if(m_Style&WISP_WLS_EMPTY_SEL_RECT)
					m_ClientDC.DrawRect(&BKrc,IsFocus() ? m_SelectBKColor : m_LostFocusSelBKColor);
				else
					m_pWispBase->m_pCurDrawObj->DrawListSelectedItemBK(&m_ClientDC,&BKrc);
			}
			m_ClientDC.EnableClipRect(&ClipRect);
			LimitX = ColIter->ColRect.x+ColIter->ColRect.cx-(int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
		}
		else
		{
			m_ClientDC.EnableClipRect(&ClipRect);
			rc.x = 	ColIter->ColRect.x - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
		}
		if(m_ListBTIndex==Col)
		{
			if(m_Style&WISP_WLS_TREE)
			{
				rc.cx = m_ButtonSize.cx;
				if(pItem->ChildItemList.Count())
					m_ClientDC.DrawSystemStandardIcon(rc,(pItem->Style&WISP_WLIS_EXPANDED)?WISP_SSI_EXPANDBUTTON_EXPAND:WISP_SSI_EXPANDBUTTON_COLLAPSE);
				rc.x += m_ButtonSize.cx;
			}
			if(m_Style&WISP_WLS_CHECK_BOX)
			{
				UINT IconIndex;
				rc.cx = m_ButtonSize.cx;
				if(pItem->Style&WISP_WLIS_CHECKED)
					IconIndex = WISP_SSI_CHECKBOX_CHECKED;
				else if(pItem->Style&WISP_WLIS_SEMI_CHECKED)
					IconIndex = WISP_SSI_CHECKBOX_SEMICHECKED;
				else
					IconIndex = WISP_SSI_CHECKBOX_UNCHECKED;
				m_ClientDC.DrawSystemStandardIcon(rc,IconIndex);
				rc.x += m_ButtonSize.cx;
			}
		}
		else
		{
		}
		if(CellIter->pIcon)
		{
			m_ClientDC.DrawDIB(rc.x,rc.y,CellIter->pIcon);
			rc.x += CellIter->pIcon->Width();
		}
		m_ClientDC.DisableClipRect();
		rc.x += m_TextMargin;
		rc.cx = ColIter->ColRect.x+ColIter->ColRect.cx - rc.x - m_TextMargin - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
		m_ClientDC.SetTextColor(CellIter->FontColor);
		DrawCellText(Col,&(*CellIter),&rc);
		ColIter++;
		CellIter++;
		Col++;
	}
	if((m_Style&WISP_WLS_HORZ_LINE)&&iLine>0)
	{
		X = m_ListRect.x - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
		if((m_Style&WISP_WLS_OPTION_TREE)==WISP_WLS_OPTION_TREE)
			X += m_TreeSpace*(Level);
		m_ClientDC.DrawHLine(X,m_ListRect.cx-1,m_ListRect.y+iLine*m_ButtonSize.cy,m_HorzLineColor);
	}
}

bool CWispList::GetPrevListItem(CItemList::IT &ItemIter)
{
	CWispListItem*pParent = ItemIter->pParent;
	if(pParent==NULL)
		return false;
	ItemIter--;
	if(ItemIter==pParent->ChildItemList.End())
	{
		if(pParent != &m_RootItem)
		{
			ItemIter = *pParent;
			return true;
		}
		return false;
	}
	while(ItemIter->ChildItemList.Count())
		ItemIter = ItemIter->ChildItemList.Last();
	return true;
}

bool CWispList::GetPrevLineItem(CItemList::IT &ItemIter)
{
	CODE_ASSERT(ItemIter->pParent && (ItemIter->pParent->Style&WISP_WLIS_EXPANDED));
	CWispListItem*pParent = ItemIter->pParent;
	if(pParent==NULL)
		return false;
	if(ItemIter==pParent->ChildItemList.Begin())
	{
		if(pParent != &m_RootItem)
		{
			ItemIter = *pParent;
			return true;
		}
		return false;
	}
	else
		ItemIter--;
	while((ItemIter->Style & WISP_WLIS_EXPANDED) && ItemIter->ChildItemList.Count())
		ItemIter = ItemIter->ChildItemList.Last();
	return true;
}

bool CWispList::GetNextLineItem(CItemList::IT &ItemIter)
{
	if(m_RootItem.ChildItemList.Count()==0 || ItemIter == m_RootItem.ChildItemList.End())
		return false;
	if((ItemIter->Style&WISP_WLIS_EXPANDED) && ItemIter->ChildItemList.Count())
	{
		ItemIter = ItemIter->ChildItemList.Begin();
		return true;
	}
	CWispListItem*pParent = ItemIter->pParent;
	if(pParent==NULL)
		return false;
	ItemIter++;
	if(ItemIter == pParent->ChildItemList.End())
	{
		while(pParent!=&m_RootItem)
		{
			ItemIter = *pParent;
			pParent = pParent->pParent;
			ItemIter++;
			if(ItemIter != pParent->ChildItemList.End())
				break;
		}
	}
	return ItemIter != pParent->ChildItemList.End();
}

int CWispList::UpdateCurScrItem(int Offset)
{
	int Result = 0;
	if(m_CurItemIter==m_RootItem.ChildItemList.End())
		return 0;
	if(Offset>0)
	{
		while(Offset>0)
		{
			if(GetNextLineItem(m_CurItemIter)==false)
				return Result;
			Offset--;
			Result++;
		}
	}
	else if(Offset<0)
	{
		while(Offset<0)
		{
			if(GetPrevLineItem(m_CurItemIter)==false)
				return Result;
			Offset++;
			Result++;
		}
	}
	return Result;
}

HANDLE CWispList::PointToItem(const WISP_POINT&ClientPT,int*pPos)
{
	CItemList::IT ItemIter;
	int Result = PointToItem(ClientPT,ItemIter);
	if(Result >= LI_POS_CELL_AREA_START)
	{
		if(pPos)
			*pPos=Result;
		return &(*ItemIter);
	}
	if(pPos)
		*pPos=LI_POS_NON_AREA;
	return NULL;
}

int CWispList::PointToItem(const WISP_POINT&ClientPT,CItemList::IT &ItemIter)
{
	int iLine,x,ListX;

	if(ClientPT.y>=m_TitleRect.y && ClientPT.y<m_TitleRect.y+m_TitleRect.cy)
		return LI_POS_COLUMN;
	if(PtInRect(&m_ListRect,ClientPT)==false)
		return LI_POS_NON_AREA;
	iLine = (ClientPT.y - m_ListRect.y) / m_ButtonSize.cy;
	if(iLine>m_ScrollBar[WISP_SB_VERT]->MaxPos)
		return LI_POS_NON_AREA;
	if(m_RootItem.ChildItemList.Count()==0)
		return LI_POS_NON_AREA;
	ItemIter = m_CurItemIter;
	while(iLine>0)
	{
		if(GetNextLineItem(ItemIter)==false)
			return LI_POS_NON_AREA;
		iLine--;
	}
	x = ClientPT.x+(int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
	ListX = m_ListRect.x + ItemIter->GetLevel() * m_TreeSpace;
	if(x<ListX)
		return LI_POS_SPACE_AREA;
	int Index=LI_POS_CELL_AREA_START;
	if(m_ColumnList.Count()==0)
		return LI_POS_NON_AREA;
	int Col=0;
	for(CColumnList::IT ColIter=m_ColumnList.Begin();ColIter!=m_ColumnList.End();ColIter++)
	{
		if(Col == m_ListBTIndex)
		{
			if(m_Style&WISP_WLS_TREE)
			{
				ListX+=m_ButtonSize.cx;
				if(x<ListX)
					return ItemIter->ChildItemList.Count()?LI_POS_TREE_BT:LI_POS_SPACE_AREA;
			}
			if((m_Style&WISP_WLS_CHECK_BOX))
			{
				ListX+=m_ButtonSize.cx;
				if(x<ListX)
					return LI_POS_CHECK_BOX;
			}
		}
		ListX = ColIter->ColRect.x+ColIter->ColRect.cx;
		if(x<ListX)
			return Index;
		Index++;
		Col++;
	}
	return (UINT)Index-1;
}

bool CWispList::ToggleExpandItem(HANDLE hItem)
{
	CWispListItem*pItem=(CWispListItem*)hItem;
	if(pItem->Style & WISP_WLIS_EXPANDED)
	{
		UnexpandItem(pItem);
		return true;
	}
	else
	{
		ExpandItem(pItem);
		return false;
	}
}

bool CWispList::ExpandItem(HANDLE hItem)
{
	CWispListItem*pItem=(CWispListItem*)hItem;
	if(pItem->Style&WISP_WLIS_EXPANDED)
		return true;
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_EXPANDING;
	Msg.Command.Param1 = false;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	if(ItemExpandingNotify(hItem)==false)
		return false;
	pItem->Style|=WISP_WLIS_EXPANDED;
	int Count = pItem->GetDispLine();
	if(Count)
	{
		AdjustScrollBarMaxPos(WISP_SB_VERT,Count);
		RecalcLayout();
		Msg.Command.CmdMsg = WISP_CMD_ITEM_EXPANDED;
		Msg.Command.Param1 = true;
		SEND_MSG(&Msg);
		ItemExpandedNotify(hItem);
		Update();
	}
	return true;
}

bool CWispList::UnexpandItem(HANDLE hItem)
{
	CWispListItem*pItem=(CWispListItem*)hItem;
	if(pItem==NULL)
		pItem = &m_RootItem;
	if((pItem->Style&WISP_WLIS_EXPANDED)==0)
		return true;
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_UNEXPANDING;
	Msg.Command.Param1 = true;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	if(ItemUnexpandingNotify(hItem)==false)
		return false;
	pItem->Style&=~WISP_WLIS_EXPANDED;
	int Count = pItem->GetDispLine();
	if(Count)
	{
		if(m_LastSelectIter!=m_RootItem.ChildItemList.End() && pItem->IsParentOf(&(*m_LastSelectIter)))
			SelectItem(hItem);
		AdjustScrollBarMaxPos(WISP_SB_VERT,-Count);
		RecalcLayout();
		Msg.Command.CmdMsg = WISP_CMD_ITEM_UNEXPANDED;
		Msg.Command.Param1 = false;
		SEND_MSG(&Msg);
		ItemUnexpandedNotify(hItem);
		Update();
	}
	return true;
}

bool CWispList::ToggleSelectItem(HANDLE hItem)
{
	CWispListItem*pItem=(CWispListItem*)hItem;
	if(pItem->Style & WISP_WLIS_SELECTED)
	{
		UnselectItem(pItem);
		return true;
	}
	else
	{
		SelectItem(pItem);
		return false;
	}
}

bool CWispList::SelectItem(HANDLE hItem)
{
	CWispListItem*pItem=(CWispListItem*)hItem;
	if(pItem->Style&WISP_WLIS_SELECTED)
		return true;
	if(((m_Style&WISP_WLS_MULTI_SELECT)==0 || m_pWispBase->m_KeyMap[WISP_VK_CONTROL]==false)
		&& m_LastSelectIter!=m_RootItem.ChildItemList.End() && (&(*m_LastSelectIter))!=pItem)
	{
		UnselectItem(&(*m_LastSelectIter));
	}
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_SELECTING;
	Msg.Command.Param1 = false;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	if(ItemSelectingNotify(hItem)==false)
		return false;
	pItem->Style|=WISP_WLIS_SELECTED;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_SELECTED;
	Msg.Command.Param1 = true;
	SEND_MSG(&Msg);
	m_LastSelectIter = (*pItem);
	ItemSelectedNotify(hItem);
	Update();
	return true;
}

bool CWispList::UnselectItem(HANDLE hItem)
{
	CWispListItem*pItem=(CWispListItem*)hItem;
	if((pItem->Style&WISP_WLIS_SELECTED)==0)
		return true;
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_UNSELECTING;
	Msg.Command.Param1 = true;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	if(ItemUnselectingNotify(hItem)==false)
		return false;
	pItem->Style&=~WISP_WLIS_SELECTED;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_UNSELECTED;
	Msg.Command.Param1 = false;
	SEND_MSG(&Msg);
	if(&(*m_LastSelectIter)==pItem)
		m_LastSelectIter = m_RootItem.ChildItemList.End();
	ItemUnselectedNotify(hItem);
	Update();
	return true;
}

void CWispList::BeginEditItem(HANDLE hItem,int Col)
{
	CWispListItem*pItem;
	CWispListItemCell*pCell;
	WISP_MSG Msg;
	WISP_RECT CellRect;
	int Index;
	if(Col>=m_ColumnList.Count())
		return;
	Index = GetItemScrLine((CWispListItem*)hItem);
	if(Index==-1)
	{
		EnableVisible(hItem);
	}
	CellRect = m_ColumnList[Col]->ColRect;
	CellRect.y = m_ListRect.y + Index * m_ButtonSize.cy;
	CellRect.cy = m_ButtonSize.cy;
	CellRect.x -= (int)m_ScrollBar[WISP_SB_HORZ]->CurPos*m_HorzScrollSpace;
	m_EditCol = Col;
	m_hEditItem = hItem;
	pCell = GetItemCell(m_hEditItem,m_EditCol);
	m_EditCtrl.m_WndText.Empty();
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_BEGIN_EDIT;
	Msg.Command.Param1 = m_EditCol;
	Msg.Command.Param2 = m_hEditItem;
	if(SEND_MSG(&Msg)==false)
		return;
	if(BeginEditItemNotify(m_hEditItem,m_EditCol,pCell->szText)==false)
		return;
	pItem = (CWispListItem*)hItem;
	if(Col==m_ListBTIndex)
	{
		if(m_Style&WISP_WLS_TREE)
		{
			CellRect.x+=m_ButtonSize.cx;
			CellRect.cx-=m_ButtonSize.cx;
		}
		if(m_Style&WISP_WLS_CHECK_BOX)
		{
			CellRect.x+=m_ButtonSize.cx;
			CellRect.cx-=m_ButtonSize.cx;
		}
	}
	if(pCell->pIcon)
	{
		CellRect.x+=pCell->pIcon->Width();
		CellRect.cx-=pCell->pIcon->Width();
	}
	m_EditCtrl.MoveWindowToClient(CellRect);
	if(m_EditCtrl.m_WndText.Length()==0)
		m_EditCtrl.SetWindowText(pCell->szText);
	m_EditCtrl.Show(WISP_SH_NORMAL);
	m_EditCtrl.Focus();
}

void CWispList::EndEditItem(bool bSaveItem)
{
	if(m_pWispBase->m_pFocusWnd!=&m_EditCtrl)
		return;
	m_bSaveItem = bSaveItem;
	Focus();
	UpdateClient();
}

void CWispList::OnEndEditItem()
{
	WISP_MSG Msg;
	m_ProcEndEditItem = true;
	m_EditCtrl.Show(WISP_SH_HIDDEN);
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = m_bSaveItem?WISP_CMD_ITEM_END_EDIT:WISP_CMD_ITEM_CANCEL_EDIT;
	Msg.Command.Param1 = m_EditCol;
	Msg.Command.Param2 = m_hEditItem;
	if(	SEND_MSG(&Msg)==false || EndEditItemNotify(m_hEditItem,m_EditCol,GetItemEditString())==false)
	{
		GetItemEditString().Empty();
	}
	else if(m_bSaveItem)
	{
		CWispListItemCell*pCell = GetItemCell(m_hEditItem,m_EditCol);
		if(pCell->szText != GetItemEditString())
		{
			pCell->szText = GetItemEditString();
			Msg.Command.CmdMsg = WISP_CMD_ITEM_CHANGED;
			SEND_MSG(&Msg);
			ItemChangedNotify(m_hEditItem,m_EditCol,pCell->szText);
		}
	}
	m_bSaveItem = true;
	m_ProcEndEditItem = false;
}

bool CWispList::OnSize(WISP_MSG*pMsg)
{
	if(pMsg->Resize.NewSizeDelta.cx>0 || m_ColumnList.Count()==0)
		return true;
	CWispColumnItem* pCol = &(*m_ColumnList.Last());
	if(pCol->Width > pCol->OrgWidth)
	{
		pCol->Width+=pMsg->Resize.NewSizeDelta.cx;
		m_ColTotalWidth+=pMsg->Resize.NewSizeDelta.cx;
	}
	return true;
}

bool CWispList::OnLostFocus(WISP_MSG*pMsg)
{
	HideItemTip();
	return true;
}

bool CWispList::ToggleCheckItem(HANDLE hItem,bool bUpdateRelation)
{
	CWispListItem*pItem=(CWispListItem*)hItem;
	if(pItem->Style & WISP_WLIS_CHECKED)
	{
		UncheckItem(pItem,bUpdateRelation);
		return true;
	}
	else
	{
		CheckItem(pItem,bUpdateRelation);
		return false;
	}
}

bool CWispList::CheckItem(HANDLE hItem,bool bUpdateRelation)
{
	WISP_MSG Msg;
	CWispListItem*pItem=(CWispListItem*)hItem;
	if(pItem->Style&WISP_WLIS_CHECKED)
		return true;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_CHECKING;
	Msg.Command.Param1 = false;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	if(ItemCheckingNotify(hItem)==false)
		return false;
	if(pItem->Style&WISP_WLIS_SEMI_CHECKED)
	{
		pItem->Style&=~WISP_WLIS_SEMI_CHECKED;
		pItem->pParent->nSemiChecked--;
	}
	pItem->Style|=WISP_WLIS_CHECKED;
	pItem->pParent->nChecked++;
	CODE_ASSERT(pItem->pParent->nSemiChecked+pItem->pParent->nChecked<=pItem->pParent->ChildItemList.Count());
	for(CItemList::IT Iter = pItem->ChildItemList.Begin();Iter!=pItem->ChildItemList.End();Iter++)
		CheckItem(&(*Iter),false);
	if(bUpdateRelation)
	{
		UpdateItemTreeCheckState(pItem);
	}
	else
	{
		pItem->nChecked = pItem->ChildItemList.Count();
		pItem->nSemiChecked = 0;
	}
	Msg.Command.CmdMsg = WISP_CMD_ITEM_CHECKED;
	Msg.Command.Param1 = true;
	SEND_MSG(&Msg);
	ItemCheckedNotify(hItem);
	Update();
	return true;
}

bool CWispList::UncheckItem(HANDLE hItem,bool bUpdateRelation)
{
	WISP_MSG Msg;
	CWispListItem*pItem;
	pItem=(CWispListItem*)hItem;
	if((pItem->Style&WISP_WLIS_CHECKED_MASK)==0)
		return true;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_UNCHECKING;
	Msg.Command.Param1 = true;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	if(ItemUncheckingNotify(hItem)==false)
		return false;
	if(pItem->Style&WISP_WLIS_CHECKED)
	{
		pItem->Style&=~WISP_WLIS_CHECKED;
		pItem->pParent->nChecked--;
	}
	else if(pItem->Style&WISP_WLIS_SEMI_CHECKED)
	{
		pItem->Style&=~WISP_WLIS_SEMI_CHECKED;
		pItem->pParent->nSemiChecked--;
	}
	for(CItemList::IT Iter = pItem->ChildItemList.Begin();Iter!=pItem->ChildItemList.End();Iter++)
		UncheckItem(&(*Iter),false);
	if(bUpdateRelation)
	{
		UpdateItemTreeCheckState(pItem);
	}
	else
	{
		pItem->nChecked = pItem->nSemiChecked = 0;
	}
	Msg.Command.CmdMsg = WISP_CMD_ITEM_UNCHECKED;
	Msg.Command.Param1 = false;
	SEND_MSG(&Msg);
	ItemUncheckedNotify(hItem);
	Update();
	return true;
}

HANDLE CWispList::GetFirstItem(HANDLE hParent,UINT Style)
{
	CWispListItem*pParentItem;
	if(hParent)
		pParentItem = (CWispListItem*)hParent;
	else
		pParentItem = &m_RootItem;

	CItemList::IT ItemIter = pParentItem->ChildItemList.Begin();
	while(ItemIter!=pParentItem->ChildItemList.End())
	{
		if((ItemIter->Style&Style) == Style)
			return &(*ItemIter);
		ItemIter++;
	}
	return NULL;
}

HANDLE CWispList::GetNextItem(HANDLE hItem,UINT Style)
{
	if(hItem==NULL)
		return GetFirstItem(NULL,Style);
	CItemList::IT ItemIter;
	ItemIter = *((CWispListItem*)hItem);
	while(GetNextItem(ItemIter))
	{
		if((ItemIter->Style&Style) == Style)
			return &(*ItemIter);
	}
	return NULL;
}

bool CWispList::GetNextItem(CItemList::IT &ItemIter)
{
	CWispListItem*pParent = ItemIter->pParent;
	if(pParent==NULL)
		return false;
	ItemIter++;
	return ItemIter!=pParent->ChildItemList.End();
}

HANDLE CWispList::GetPrevItem(HANDLE hItem,UINT Style)
{
	CItemList::IT ItemIter;
	ItemIter = *((CWispListItem*)hItem);
	while(GetPrevItem(ItemIter))
	{
		if((ItemIter->Style&Style) == Style)
			return &(*ItemIter);
	}
	return NULL;
}


bool CWispList::GetPrevItem(CItemList::IT &ItemIter)
{
	CWispListItem*pParent = ItemIter->pParent;
	if(pParent==NULL)
		return false;
	ItemIter--;
	return ItemIter!=pParent->ChildItemList.End();
}


HANDLE CWispList::GetNextListItem(HANDLE hItem,UINT Style)
{
	CItemList::IT ItemIter;
	if(hItem)
		ItemIter = *((CWispListItem*)hItem);
	else
		ItemIter = m_RootItem.ChildItemList.Begin();
	if(ItemIter == m_RootItem.ChildItemList.End())
		return NULL;
	if(hItem && GetNextListItem(ItemIter)==false)
		return NULL;
	do
	{
		if((ItemIter->Style&Style) == Style)
			return &(*ItemIter);
	}while(GetNextListItem(ItemIter));
	return NULL;
}

HANDLE CWispList::GetPrevListItem(HANDLE hItem,UINT Style)
{
	CItemList::IT ItemIter;
	if(hItem)
		ItemIter = *((CWispListItem*)hItem);
	else
		ItemIter = m_RootItem.ChildItemList.Last();
	if(ItemIter == m_RootItem.ChildItemList.End())
		return NULL;
	if(hItem && GetPrevListItem(ItemIter)==false)
		return NULL;
	do
	{
		if((ItemIter->Style&Style) == Style)
			return &(*ItemIter);
	}while(GetPrevListItem(ItemIter));
	return NULL;
}

HANDLE CWispList::GetItem(int Index,HANDLE hParent)
{
	CItemList*pItemList;
	if(hParent)
		pItemList = &((CWispListItem*)hParent)->ChildItemList;
	else
		pItemList = &m_RootItem.ChildItemList;
	if(pItemList->Count()==0)
		return NULL;
	if(Index<0 || Index >= pItemList->Count())
		return &(*pItemList->Last());
	return &(*(*pItemList)[Index]);
}

HANDLE CWispList::GetParentItem(HANDLE hItem)
{
	CWispListItem*pItem = (CWispListItem*)hItem;
	return pItem->pParent;
}

int CWispList::GetItemIndex(HANDLE hItem)
{
	HANDLE hFindItem,hParent;
	int Index=0;
	hParent = GetParentItem(hItem);
	if(hParent==NULL)
		return 0;
	hFindItem = GetFirstItem(hParent);
	while(hFindItem)
	{
		if(hFindItem == hItem)
			return Index;
		hFindItem = GetNextItem(hFindItem);
		Index++;
	}
	return -1;
}

int CWispList::GetListItemIndex(HANDLE hItem,HANDLE hParent)
{
	HANDLE hFindItem;
	int Index=0;
	hFindItem = GetNextListItem(hParent);
	while(hFindItem)
	{
		if(hFindItem == hItem)
			return Index;
		hFindItem = GetNextListItem(hItem);
		Index++;
	}
	return -1;
}


int	CWispList::GetItemCount(HANDLE hParent,bool bRecursive)
{
	int Count;
	CItemList*pItemList;
	if(hParent)
		pItemList = &((CWispListItem*)hParent)->ChildItemList;
	else
		pItemList = &m_RootItem.ChildItemList;
	Count = pItemList->Count();
	if(bRecursive)
	{
		for(CItemList::IT Iter= pItemList->Begin();Iter!=pItemList->End();Iter++)
		{
			Count+=GetItemCount((HANDLE)&(*Iter),true);
		}
	}
	return Count;
}

bool CWispList::GetNextListItem(CItemList::IT &ItemIter)
{
	if(ItemIter->ChildItemList.Count())
	{
		ItemIter = ItemIter->ChildItemList.Begin();
		return true;
	}
	CWispListItem*pParent = ItemIter->pParent;
	if(pParent==NULL)
		return false;
	ItemIter++;
	if(ItemIter == pParent->ChildItemList.End())
	{
		while(pParent!=&m_RootItem)
		{
			ItemIter = *pParent;
			pParent = pParent->pParent;
			ItemIter++;
			if(ItemIter != pParent->ChildItemList.End())
				break;
		}
	}
	return ItemIter != pParent->ChildItemList.End();
}

CWispListItemCell* CWispList::GetItemCell(HANDLE hItem,int Col)
{
	CWispListItem*pItem = (CWispListItem*)hItem;
	if(Col >= m_ColumnList.Count())
		return NULL;
	if(pItem->ItemCellList.Count()<=Col)
	{
		CItemListCell::IT Iter;
		for(int n=pItem->ItemCellList.Count();n<=Col;n++)
		{
			Iter = pItem->ItemCellList.Append();
			Iter->Data = 0;
			Iter->pIcon = NULL;
			Iter->FontColor = m_FontColor;
		}
	}
	return &(*pItem->ItemCellList[Col]);
}

CWispString&CWispList::GetItemText(HANDLE hItem,int Col)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	return pCell->szText;
}

int CWispList::GetItemText(HANDLE hItem,int Col,WISP_PSTR szString,int MaxLength)
{
	CWispString*pString = &GetItemText(hItem,Col);
	if(pString==NULL)
		return 0;
	if(pString->Length()==0)
	{
		*szString=0;
		return 0;
	}
	if(IsColorString(pString->m_pData))
	{
		return TStrCpyLimit(szString,GetColorString(pString->m_pData),MaxLength);
	}
	else
	{
		return TStrCpyLimit(szString,pString->m_pData,MaxLength);
	}
}

CWispDIB*CWispList::GetItemIcon(HANDLE hItem,int Col)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	return pCell->pIcon;
}

NUM_PTR	CWispList::GetItemData(HANDLE hItem,int Col)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	return pCell->Data;
}

COLORREF CWispList::GetItemTextColor(HANDLE hItem,int Col)
{
	CWispListItemCell*pCell = GetItemCell(hItem,Col);
	return pCell->FontColor;
}

COLORREF CWispList::GetItemLineColor(HANDLE hItem)
{
	return ((CWispListItem*)hItem)->LineColor;
}

UINT CWispList::GetItemStyle(HANDLE hItem)
{	
	return ((CWispListItem*)hItem)->Style;
}

int CWispList::GetItemLevel(HANDLE hItem)
{
	return ((CWispListItem*)hItem)->GetLevel();
}

bool CWispList::IsParentOfItem(HANDLE hItem,HANDLE hChildItem)
{
	return ((CWispListItem*)hItem)->IsParentOf(hChildItem);
}

int CWispList::GetItemFullPath(HANDLE hItem,int Col,WISP_PSTR szBuffer,UINT MaxLength,WISP_PCSTR SplitStr)
{
	UINT Length;
	CWispListItem*pItem;
	CWispListItemCell*pCell;
	TArray<WISP_PSTR> ItemStrArray;
	ItemStrArray.Resize(GetItemDeep(hItem)-1);
	pItem = (CWispListItem*)hItem;
	if(szBuffer)
		*szBuffer=0;
	Length = 0;
	while(pItem!=&m_RootItem)
	{
		pCell = GetItemCell((HANDLE)pItem,Col);
		ItemStrArray.Append(pCell->szText);
		pItem = pItem->pParent;
	}
	int Count=ItemStrArray.Count();
	for(int n=Count-1;n>=0;n--)
	{
		if(Length<MaxLength)
		{
			if(szBuffer)
				Length+=TStrCpy(&szBuffer[Length],ItemStrArray[n]);
			else
				Length+=TStrLen(ItemStrArray[n]);
		}
		if(n>0 && Length<MaxLength)
		{
			if(szBuffer)
				Length+=TStrCpy(&szBuffer[Length],SplitStr);
			else
				Length+=TStrLen(SplitStr);
		}
	}
	return Length;
}

int CWispList::GetItemDeep(HANDLE hItem)
{
	int Deep = 0;
	CWispListItem*pItem = (CWispListItem*)hItem;
	while(pItem)
	{
		pItem = pItem->pParent;
		Deep++;
	}
	return Deep;
}

bool CWispList::ShowItemTip(HANDLE hItem,int Col,WISP_PCSTR szTip)
{
	WISP_CHAR szTipBuffer[WISP_MAX_LIST_TIP_LEN];
	WISP_POINT Pt;
	int nLine = GetItemScrLine((CWispListItem*)hItem);
	if(nLine<0)
		return false;
	m_hCurHoverItem = hItem;
	m_CurHoverCol = Col;
	Pt.x = m_ColumnList[Col]->ColRect.x - (int)m_ScrollBar[WISP_SB_HORZ]->CurPos * m_HorzScrollSpace;
	Pt.y = m_ListRect.y + m_ButtonSize.cy * nLine;
	Pt.x+=m_ScrWindowRect.x;
	Pt.y+=m_ScrWindowRect.y;
	if(IsColorString(szTip))
		TStrCpy((WISP_COLOR_CHAR*)szTipBuffer,(WISP_COLOR_CHAR*)szTip);
	else
		TStrCpy(szTipBuffer,szTip);
	if(ItemShowTipNotify(hItem,Col,&Pt.x,&Pt.y,szTipBuffer)==false)
		return false;
	if(m_bTipTimerSet)
	{
		RemoveTimer(WISP_WLI_TIMER_ID);
		m_bTipTimerSet = false;
	}
	if(IsColorString(szTipBuffer))
	{
		const WISP_COLOR_CHAR *pszText = GetColorString(szTipBuffer);
		int Length = TStrLen(pszText);
		m_TipFullItemTextWnd.m_WndText.Preallocate(Length+1);
		m_TipFullItemTextWnd.m_WndText.m_Length = Length;
		TStrCpy((WISP_PSTR)m_TipFullItemTextWnd.m_WndText,pszText);
	}
	else
	{
		m_TipFullItemTextWnd.SetWindowText(szTipBuffer);
	}
	m_TipFullItemTextWnd.AutoAdjustPostion(this);
	if(Pt.x+m_TipFullItemTextWnd.m_WindowRect.cx>m_pWispBase->m_pRootWnd->m_WindowRect.cx)
		Pt.x = m_pWispBase->m_pRootWnd->m_WindowRect.cx - m_TipFullItemTextWnd.m_WindowRect.cx;
	MIN_LIMIT(Pt.x,0);
	if(Pt.y+m_TipFullItemTextWnd.m_WindowRect.cy>m_pWispBase->m_pRootWnd->m_WindowRect.cy)
		Pt.y = m_pWispBase->m_pRootWnd->m_WindowRect.cy - m_TipFullItemTextWnd.m_WindowRect.cy;
	MIN_LIMIT(Pt.y,0);
	m_TipFullItemTextWnd.MoveToScreen(Pt.x,Pt.y);	
	m_TipFullItemTextWnd.Show();
	Update();
	return true;
}

bool CWispList::HideItemTip()
{
	if(m_bTipTimerSet)
	{
		RemoveTimer(WISP_WLI_TIMER_ID);
		m_bTipTimerSet=false;
	}
	if(m_TipFullItemTextWnd.IsVisible()==false)
		return false;
	if(ItemHideTipNotify(m_hCurHoverItem,m_CurHoverCol,m_TipFullItemTextWnd.m_WndText)==false)
		return false;
	m_TipFullItemTextWnd.m_WndText.Empty();
	m_TipFullItemTextWnd.Show(WISP_SH_HIDDEN);
	m_hCurHoverItem = NULL;
	m_CurHoverCol = 0;
	Update();
	return true;
}

bool CWispList::ItemShowTipNotify(HANDLE hItem,int Col,int*pX,int*pY,WISP_PSTR szTip)
{
	if(IsItemTextFullVisible(hItem,Col))
		return false;
	TStrCpy(szTip,(WISP_PCSTR)GetItemText(hItem,Col));
	return true;
}

void CWispList::DrawCellText(int Col,CWispListItemCell*pCell,WISP_RECT*pRect)
{
	WISP_CHAR*pszText = pCell->szText;
	if(IsColorString(pszText))
	{
		m_ClientDC.DrawColorString(pRect,GetColorString(pszText));
	}
	else
	{
		m_ClientDC.DrawString(pRect,pCell->szText);
	}
}

void CWispList::DrawColumnItemText(CWispColumnItem*pColItem,WISP_RECT*pRect)
{
	m_ClientDC.DrawShadowString(pRect,pColItem->szText);
}

void CWispList::UpdateItemTreeCheckState(CWispListItem*pItem)
{
	pItem=pItem->pParent;
	while(pItem!=&m_RootItem)
	{
		if(((pItem->nChecked > 0 && pItem->nChecked < pItem->ChildItemList.Count()) || pItem->nSemiChecked > 0) && (pItem->Style&WISP_WLIS_SEMI_CHECKED)==0)
		{
			if(pItem->Style&WISP_WLIS_CHECKED)
			{
				pItem->Style&=~WISP_WLIS_CHECKED;
				pItem->pParent->nChecked--;
			}
			pItem->Style|=WISP_WLIS_SEMI_CHECKED;
			pItem->pParent->nSemiChecked++;
		}
		else if(pItem->nChecked == pItem->ChildItemList.Count() && (pItem->Style&WISP_WLIS_CHECKED)==0)
		{
			if(pItem->Style&WISP_WLIS_SEMI_CHECKED)
			{
				pItem->Style&=~WISP_WLIS_SEMI_CHECKED;
				pItem->pParent->nSemiChecked--;
			}
			pItem->Style|=WISP_WLIS_CHECKED;
			pItem->pParent->nChecked++;
		}
		else if(pItem->nChecked==0 && pItem->nSemiChecked==0)
		{
			if(pItem->Style&WISP_WLIS_CHECKED)
			{
				pItem->Style&=~WISP_WLIS_CHECKED;
				pItem->pParent->nChecked--;
			}
			else if(pItem->Style&WISP_WLIS_SEMI_CHECKED)
			{
				pItem->Style&=~WISP_WLIS_SEMI_CHECKED;
				pItem->pParent->nSemiChecked--;
			}
		}
		CODE_ASSERT(pItem->pParent->nSemiChecked<=pItem->pParent->ChildItemList.Count());
		pItem=pItem->pParent;
	}
}

void CWispList::OnHide()
{
	if(m_TipFullItemTextWnd.IsVisible())
		HideItemTip();
}

