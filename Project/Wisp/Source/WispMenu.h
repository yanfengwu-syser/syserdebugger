#ifndef WISP_MENU_H_
#define WISP_MENU_H_

#include "WispWnd.h"

#define WISP_WMS_POPUP		0x00010000

#define WISP_MIS_NORMAL		0x00000000
#define WISP_MIS_POPUP		0x00000001
#define WISP_MIS_CHECKBOX	0x00000002
#define WISP_MIS_SEPARATOR	0x00000004
#define WISP_MIS_CHECKED	0x00080000
#define WISP_MIS_DISABLED	0x00100000


#define WISP_MENU_RES_SEPARATOR		{NULL,0,NULL,WISP_MIS_SEPARATOR}
#define WISP_MENU_RES_END			{NULL,0,0,NULL,NULL}

class CWispMenu;

struct WISP_MENU_RES_ITEM
{
	WISP_PCSTR	szText;
	UINT		CmdID;
	int			DIBIndex;
	UINT		Style;
	void*		pMenuItem;
};

struct WISP_MENU_ITEM
{
	CWispString	szText;
	CWispDIB*	pIcon;
	UINT		CmdID;
	UINT		Style;
	WISP_RECT	ItemRC;
	COLORREF	TextClr;
	union
	{
		NUM_PTR	Data;
		CWispMenu*pSubMenu;
	};
};

typedef TList<WISP_MENU_ITEM>	CMenuItemList;

class CWispMenu : public CWispWnd
{
protected:
	CMenuItemList m_ItemList;
	int		m_PopupItemHeight;
	int		m_WndItemHeight;
	CMenuItemList::IT m_HoverIter;
	int		m_MenuStartSpace;
	int		m_MenuIconSpace;
	int		m_MenuEndSpace;
	int		m_MenuMarge;
	int		m_PopupMenuTopSpace;
	int		m_PopupMenuBottomSpace;
	int		m_WndMenuHeight;
	int		m_WndMenuItemWidth;
	bool	m_bExpandMenu;
public:
	CWispMenu();
	~CWispMenu();
public:
	bool	InitWnd();
	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnMouseMove)
	DECLARE_WISP_MSG(OnMouseLeave)
	DECLARE_WISP_MSG(OnParentResize)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnUpdateBorder)
	DECLARE_WISP_MSG(OnLostFocus)
	DECLARE_WISP_MSG(OnRecalcLayout)
	DECLARE_WISP_MSG(OnDestroy)
	//Notify
	virtual bool ClickItemNotify(HANDLE hMenuItem,UINT CmdID){return true;}

	bool	CreateWndMenu(CWispWnd*pParentWnd,UINT CmdID,WISP_MENU_RES_ITEM*pResItem,CWispDIBList*pDIBList = NULL);
	bool	CreatePopupMenu(WISP_MENU_RES_ITEM*pResItem,CWispBaseWnd*pOwnerWnd,CWispDIBList*pDIBList = NULL);
	void	SetOwner(CWispBaseWnd*pOwnerWnd);
	bool	Popup(WISP_POINT*pPT = NULL,bool bSelectItem = true);
	bool	IsPopupMenu(){ return (m_Style&WISP_WMS_POPUP)!=0;}
	HANDLE	InsertItem(int Pos,WISP_PCSTR szText,UINT Style,UINT CmdID,CWispDIB*pIcon=NULL,NUM_PTR MenuData = 0);
	bool	InsertSubMenu(int Pos,WISP_PCSTR szText,CWispMenu*pMenu,CWispDIB*pIcon = NULL);
	bool	SetItemColor(UINT CmdID,COLORREF TextColor);
	void	AdjustPopupMenuSize();
	bool	RemoveItemByPos(int Pos);
	bool	RemoveItem(UINT CmdID);
	bool	RemoveItem(HANDLE hItem);
	int		RemoveAllItem();
	HANDLE	GetItemByName(WISP_PCSTR Name);
	HANDLE	GetItemByPos(int Pos);
	HANDLE	GetItem(UINT CmdID);
	HANDLE	GetNextItem(HANDLE hItem,UINT Style=0);
	HANDLE	GetPrevItem(HANDLE hItem,UINT Style=0);
	bool	SetHoverItem(HANDLE hItem);
	CWispString&GetItemText(HANDLE hItem);
	CWispDIB*GetItemIcon(HANDLE hItem);
	UINT	GetItemStyle(HANDLE hItem);
	NUM_PTR	GetItemData(HANDLE hItem);

	bool	SetItemInfo(HANDLE hItem,UINT Style,WISP_PCSTR szText,CWispDIB*pIcon,NUM_PTR Data);
	bool	SetItemText(HANDLE hItem,WISP_PCSTR szText);
	bool	SetItemIcon(HANDLE hItem,CWispDIB*pIcon);
	bool	SetItemStyle(HANDLE hItem,UINT Style);
	bool	SetItemData(HANDLE hItem,NUM_PTR Data);
	//HANDLE
	bool	IsItemChecked(HANDLE hItem);
	bool	ToggleCheckItem(HANDLE hItem);
	bool	CheckItem(HANDLE hItem);
	bool	UncheckItem(HANDLE hItem);
	
	bool	IsItemDisabled(HANDLE hItem);
	bool	ToggleDisableItem(HANDLE hItem);
	bool	EnableItem(HANDLE hItem);
	bool	DisableItem(HANDLE hItem);

	bool INLINE CheckItem(HANDLE hItem,bool bCheck){ return bCheck?CheckItem(hItem):UncheckItem(hItem);}
	bool INLINE EnableItem(HANDLE hItem,bool bEnable){ return bEnable?EnableItem(hItem):DisableItem(hItem);}
	//CmdID
	bool	IsItemChecked(UINT CmdID);
	bool	ToggleCheckItem(UINT CmdID);
	bool	CheckItem(UINT CmdID);
	bool	UncheckItem(UINT CmdID);

	bool	IsItemDisabled(UINT CmdID);
	bool	ToggleDisableItem(UINT CmdID);
	bool	EnableItem(UINT CmdID);
	bool	DisableItem(UINT CmdID);

	bool INLINE CheckItem(UINT CmdID,bool bCheck){ return bCheck?CheckItem(CmdID):UncheckItem(CmdID);}
	bool INLINE EnableItem(UINT CmdID,bool bEnable){ return bEnable?EnableItem(CmdID):DisableItem(CmdID);}
private:
	void	DrawWndMenu();
	void	DrawPopupMenu();
	void	HoverItemChanged(const CMenuItemList::IT&Iter);
	void	PopupItemMenu(WISP_MENU_ITEM*pMenuItem,bool bSelectItem = true);
	bool	IsChildMenu(CWispBaseWnd*pMenu);
	CWispMenu*GetTopMenu();
	void	HideMenuTree();
	void	MenuNextSelect();
	void	MenuPrevSelect();
	void	ClickItem(WISP_MENU_ITEM*pMenuItem);
public:
	CWispMenu*m_pParentMenu;
};


#endif
