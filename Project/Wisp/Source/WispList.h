#ifndef _WISP_LIST_H_
#define _WISP_LIST_H_

#include "WispEdit.h"
#include "WispTipWnd.h"

//ListCtrl Attribute
#define WISP_WLS_COLUMN_TITLE		0x00010000
#define WISP_WLS_TREE				0x00020000
#define WISP_WLS_OPTION_TREE		0x00060000				//带灰白条的List
#define WISP_WLS_CHECK_BOX			0x00400000
#define WISP_WLS_MULTI_SELECT		0x00800000
#define WISP_WLS_EMPTY_SEL_RECT		0x01000000
#define WISP_WLS_VERT_LINE			0x02000000
#define WISP_WLS_HORZ_LINE			0x04000000
#define WISP_WLS_TREE_LINE			0x08000000
#define WISP_WLS_FOLLOW_SEL			0x10000000
#define WISP_WLS_SELECTED_ALWAYS	0x40000000
#define WISP_WLS_HIDE_SELECTED		0x80000000


//ListItem Attribute
#define WISP_WLIS_NULL				0x00000000
#define WISP_WLIS_NORMAL			0x00000000
#define WISP_WLIS_EXPANDED			0x00000001
#define WISP_WLIS_CHECKED			0x00000002
#define WISP_WLIS_SEMI_CHECKED		0x00000004
#define WISP_WLIS_CHECKED_MASK		(WISP_WLIS_CHECKED|WISP_WLIS_SEMI_CHECKED)
#define WISP_WLIS_SELECTED			0x00000008
#define WISP_WLIS_COLOR_LINE		0x00000010

//ListColumn Attribute
#define WISP_WLCS_NORMAL			0x00000000
#define WISP_WLCS_EDITABLE			0x00000001
#define WISP_WLCS_FIXED				0x00000002

#define WISP_MAX_LIST_TIP_LEN		0x200

enum WISP_WLI_CMD_ID
{
	WISP_WLI_EDIT_CMD_ID	=	WISP_WM_SYS_START,
	WISP_WLI_TIP_CMD_ID,
	WISP_WLI_TIMER_ID
};

class CWispListItemCell
{
public:
	CWispString		szText;
	CWispDIB*		pIcon;
	NUM_PTR			Data;
	COLORREF		FontColor;
};

class CWispListItem
{
public:
	typedef TList<CWispListItem>		CItemList;
	typedef TList<CWispListItemCell>	CItemListCell;
public:
	CItemList		ChildItemList;
	CItemListCell	ItemCellList;
	CWispListItem*	pParent;
	UINT			Style;
	COLORREF		LineColor;
	int				nChecked;
	int				nSemiChecked;
	int		GetLevel();
	int		GetDispLine();
	bool	IsParentOf(HANDLE hItem);
};

class CWispColumnItem
{
public:
	CWispString		szText;
	CWispDIB*		pIcon;
	int				Width;
	int				OrgWidth;
	UINT			Style;
	WISP_RECT		ColRect;
	WISP_RECT		SplitRect;
	WISP_RECT		TestSplitRect;
	NUM_PTR			Data;
};

enum WISP_LI_POS
{
	LI_POS_NON_AREA = -1,
	LI_POS_CELL_AREA_START = 0,
	LI_POS_CELL_AREA_END = 0x00001000,
	LI_POS_TREE_BT,
	LI_POS_CHECK_BOX,
	LI_POS_COLUMN,
	LI_POS_SPACE_AREA,
};

typedef TList<CWispColumnItem>		CColumnList;
typedef TList<CWispListItem>		CItemList;
typedef TList<CWispListItemCell>	CItemListCell;

class CWispList : public CWispWnd
{
public:
	CWispList();
	virtual ~CWispList();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnPrecreate)
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnMouseMove)
	DECLARE_WISP_MSG(OnMouseLeave)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnBeginDrag)
	DECLARE_WISP_MSG(OnDragMove)
	DECLARE_WISP_MSG(OnEndDrag)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnLostFocus)
	DECLARE_WISP_MSG(OnScrollEvent)
	DECLARE_WISP_MSG(OnTimer)
	DECLARE_WISP_MSG(OnMouseDBClick);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnEditCommand)
public:
	virtual	bool	InitWnd();
	virtual bool	Destroy();
	virtual	void	RecalcLayout();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Column
	HANDLE	InsertColumn(const WISP_CHAR*szText,int Width,UINT Style = WISP_WLCS_NORMAL,CWispDIB*pIcon = NULL,int Pos = -1);
	bool	RemoveColumn(int Pos);
	HANDLE	GetColumn(int Pos);
	bool	SetColumnWidth(int Col,int Width);
	bool	SetColumnWidth(HANDLE hColumn,int Width);
	bool	SetColumnText(HANDLE hColumn,WISP_PCSTR szText);
	bool	SetColumnIcon(HANDLE hColumn,CWispDIB*pDIB);
	bool	SetColumnData(HANDLE hColumn,NUM_PTR Data);
	bool	SetColumnInfo(HANDLE hColumn,WISP_PCSTR szText,CWispDIB*pDIB,NUM_PTR Data);
//Item
	HANDLE	InsertItem(const WISP_CHAR*szText,HANDLE hParent = NULL,UINT Style = WISP_WLIS_NORMAL,CWispDIB*pIcon = NULL,int Pos = -1);
	HANDLE	InsertItemA(const char*szText,HANDLE hParent = NULL,UINT Style = WISP_WLIS_NORMAL,CWispDIB*pIcon = NULL,int Pos = -1);
	HANDLE	InsertItemW(const WCHAR*szText,HANDLE hParent = NULL,UINT Style = WISP_WLIS_NORMAL,CWispDIB*pIcon = NULL,int Pos = -1);
	HANDLE	InsertItem(UINT Num,HANDLE hParent = NULL,WISP_CHAR*szFormat = WSTR("%X"),UINT Style = WISP_WLIS_NORMAL,CWispDIB*pIcon = NULL,int Pos = -1);

	bool	RemoveItem(int Pos,HANDLE hParent = NULL);
	bool	RemoveItem(HANDLE hItem);

	CWispListItemCell*GetItemCell(HANDLE hItem,int Col=0);
	CWispString&GetItemText(HANDLE hItem,int Col=0);
	int			GetItemText(HANDLE hItem,int Col,WISP_PSTR szString,int MaxLength);
	CWispDIB*	GetItemIcon(HANDLE hItem,int Col=0);
	NUM_PTR		GetItemData(HANDLE hItem,int Col=0);
	COLORREF	GetItemTextColor(HANDLE hItem,int Col=0);
	COLORREF	GetItemLineColor(HANDLE hItem);
	UINT		GetItemStyle(HANDLE hItem);
	int			GetItemLevel(HANDLE hItem);
	bool		IsParentOfItem(HANDLE hItem,HANDLE hChildItem);
	//Item Notify
	virtual	void	ItemClickNotify(HANDLE hItem,int Col){};
	virtual	void	ItemRClickNotify(HANDLE hItem,int Col){};
	virtual	void	TitleRClickNotify(int Col){};
	virtual	void	TitleClickNotify(int Col){};
	virtual	void	ItemDBClickNotify(HANDLE hItem,int Col){};
	virtual	bool	ItemShowTipNotify(HANDLE hItem,int Col,int*pX,int*pY,WISP_PSTR szTip);
	virtual	bool	ItemHideTipNotify(HANDLE hItem,int Col,WISP_PSTR szTip){return true;}
	//Edit Notify
	virtual	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String){return true;}
	virtual	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String){return true;}
	virtual	void	ItemChangedNotify(HANDLE hItem,int Col,CWispString&String){}
	CWispString&	GetItemEditString(){ return m_EditCtrl.m_WndText;}
	//Expand Notify
	virtual bool	ItemExpandingNotify(HANDLE hItem){return true;}
	virtual void	ItemExpandedNotify(HANDLE hItem){}
	virtual bool	ItemUnexpandingNotify(HANDLE hItem){return true;}
	virtual void	ItemUnexpandedNotify(HANDLE hItem){}
	//Select Notify
	virtual bool	ItemSelectingNotify(HANDLE hItem){return true;}
	virtual void	ItemSelectedNotify(HANDLE hItem){}
	virtual bool	ItemUnselectingNotify(HANDLE hItem){return true;}
	virtual void	ItemUnselectedNotify(HANDLE hItem){}
	//Check Notify
	virtual bool	ItemCheckingNotify(HANDLE hItem){return true;}
	virtual void	ItemCheckedNotify(HANDLE hItem){}
	virtual bool	ItemUncheckingNotify(HANDLE hItem){return true;}
	virtual void	ItemUncheckedNotify(HANDLE hItem){}
	virtual void	OnHide();
	//Item Operation
	bool	SetItemText(HANDLE hItem,int Col,const WISP_CHAR*szText);
	bool	SetItemTextA(HANDLE hItem,int Col,const CHAR*szText);
	bool	SetItemColorText(HANDLE hItem,int Col,const WISP_COLOR_CHAR*szText);
	bool	SetItemData(HANDLE hItem,int Col,NUM_PTR Data);
	bool	SetItemNum(HANDLE hItem,int Col,UINT Num,const WISP_CHAR*szFormat = WSTR("%X"));//设置数字
	bool	SetItemIcon(HANDLE hItem,int Col,CWispDIB*pIcon);								//设置文本图标
	bool	SetItemTextColor(HANDLE hItem,int Col,COLORREF Color);							//设置某项文本颜色
	bool	SetDefaultTextColor(COLORREF Color){m_FontColor = Color;return true;}			//设置默认文本颜色
	bool	SetItemLineColor(HANDLE hItem,COLORREF Color);									//设置彩色行
	bool	ModifyItemStyle(HANDLE hItem,UINT AddStyle,UINT RemoveStyle = 0);				//设置Item属性
	bool	ClearChildItem(HANDLE hItem = NULL);
	int		EmptyChildItemContext(HANDLE hItem = NULL);
	void	EmptyItemContext(HANDLE hItem);
	void	EnableVisible(HANDLE hItem,int nPrevLine = -1);	//使Item可见
	bool	IsItemVisible(HANDLE hItem);
	bool	IsItemTextFullVisible(HANDLE hItem,int Col);
	int		SetItemChildCount(HANDLE hItem,int Count);
	bool	ShowColumnTitle(bool bShow = true);
//Edit Item
	void	BeginEditItem(HANDLE hItem,int Col);
	void	EndEditItem(bool bSaveItem = true);
//Expand Item
	bool	ToggleExpandItem(HANDLE hItem);
	bool	ExpandItem(HANDLE hItem);
	bool	UnexpandItem(HANDLE hItem);
	INLINE	bool	IsItemExpanded(HANDLE hItem){ return (((CWispListItem*)hItem)->Style&WISP_WLIS_EXPANDED)!=0; }
//Select Item
	bool	ToggleSelectItem(HANDLE hItem);
	bool	SelectItem(HANDLE hItem);
	bool	UnselectItem(HANDLE hItem);
	INLINE	bool	IsItemSelected(HANDLE hItem){ return (((CWispListItem*)hItem)->Style&WISP_WLIS_SELECTED)!=0; }
//Check Item
	bool	ToggleCheckItem(HANDLE hItem,bool bUpdateRelation = true);
	bool	CheckItem(HANDLE hItem,bool bUpdateRelation = true);
	bool	UncheckItem(HANDLE hItem,bool bUpdateRelation = true);
	INLINE	bool	IsItemChecked(HANDLE hItem){ return (((CWispListItem*)hItem)->Style&WISP_WLIS_CHECKED)!=0; }
	INLINE	bool	IsItemSemiChecked(HANDLE hItem){ return (((CWispListItem*)hItem)->Style&WISP_WLIS_SEMI_CHECKED)!=0; }
	int		GetItemCell();
//Find Item
	HANDLE	GetRootItem(){	return &m_RootItem;}
	HANDLE	GetFirstItem(HANDLE hParent=NULL,UINT Style=0);
	HANDLE	GetNextItem(HANDLE hItem=NULL,UINT Style=0);//取同级的Item
	HANDLE	GetPrevItem(HANDLE hItem=NULL,UINT Style=0);

	HANDLE	GetNextListItem(HANDLE hItem=NULL,UINT Style=0);//不分级的取Item
	HANDLE	GetPrevListItem(HANDLE hItem=NULL,UINT Style=0);

	HANDLE	GetItem(int Index,HANDLE hParent= NULL);
	HANDLE	GetParentItem(HANDLE hItem);
	int		GetItemIndex(HANDLE hItem);
	int		GetListItemIndex(HANDLE hItem,HANDLE hParent=NULL);
	int		GetItemCount(HANDLE hParent=NULL,bool bRecursive=true);
	int		GetItemDeep(HANDLE hItem);
	int		GetItemScrLine(HANDLE hItem);
	bool	GetItemCellRect(HANDLE hItem,int Col,WISP_RECT*pRECT);
	HANDLE	GetScrStartItem();
	HANDLE	PointToItem(const WISP_POINT&ClientPT,int*pPos=NULL);
//Item Tip
	bool	ShowItemTip(HANDLE hItem,int Col,WISP_PCSTR szTip);
	bool	HideItemTip();
//Item path
	virtual	int		GetItemFullPath(HANDLE hItem,int Col,WISP_PSTR szBuffer,UINT MaxLength = (UINT)-1,WISP_PCSTR SplitStr=PATH_SEPARATOR_WSTR);
	virtual	void	DrawCellText(int Col,CWispListItemCell*pCell,WISP_RECT*pRect);
	virtual	void	DrawColumnItemText(CWispColumnItem*pColItem,WISP_RECT*pRect);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	CWispTipWnd		m_TipFullItemTextWnd;
	int				m_ListBTIndex;
	int				m_HorzScrollSpace;
	int				m_ColTotalWidth;
	int				m_OldTitleHeight;
	int				m_TitleHeight;
	int				m_EditCol;
	HANDLE			m_hEditItem;
	CWispEdit		m_EditCtrl;
	CWispColumnItem*m_pDragColumn;
	CItemList::IT	m_CurItemIter;
	CItemList::IT	m_LastSelectIter;
	int				m_LastClickCol;
	WISP_POINT		m_LastMousePos;
	HANDLE			m_hCurHoverItem;
	int				m_CurHoverCol;
	int				m_TextMargin;
	WISP_SIZE		m_ButtonSize;
	WISP_RECT		m_TitleRect;
	WISP_RECT		m_ListRect;
	CColumnList		m_ColumnList;
	CWispListItem	m_RootItem;
	int				m_nLinePerPage;
	int				m_TreeSpace;
	COLORREF		m_ColTitleFontColor;
	COLORREF		m_FontColor;
	COLORREF		m_SelectFontColor;
	COLORREF		m_SelectBKColor;
	COLORREF		m_LostFocusSelBKColor;
	COLORREF		m_VertLineColor;
	COLORREF		m_HorzLineColor;
	bool			m_bSaveItem;
	bool			m_ProcEndEditItem;
	bool			m_bTipTimerSet;
	int				m_TipPeriod;
	int		PointToItem(const WISP_POINT&ClientPT,CItemList::IT &ItemIter);
	void	OnEndEditItem();
protected:
	void	DrawListItem(int iLine,const CItemList::IT &ItemIter);
	bool	GetNextLineItem(CItemList::IT &ItemIter);
	bool	GetPrevLineItem(CItemList::IT &ItemIter);
	bool	GetNextListItem(CItemList::IT &ItemIter);
	bool	GetPrevListItem(CItemList::IT &ItemIter);
	bool	GetNextItem(CItemList::IT &ItemIter);
	bool	GetPrevItem(CItemList::IT &ItemIter);
	int		UpdateCurScrItem(int Offset);
	void	UpdateItemTreeCheckState(CWispListItem*pItem);
	void	ProcessItemTip(HANDLE hItem,int Col);
};


#endif

