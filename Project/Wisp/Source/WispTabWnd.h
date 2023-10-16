#ifndef _WISP_TAB_WND_
#define _WISP_TAB_WND_

#include "WispButton.h"

#define WISP_MAX_TAB_STR		32

#define WISP_TWS_TOP				0x00010000
#define WISP_TWS_BUTTOM				0x00020000
#define WISP_TWS_LEFT				0x00040000
#define WISP_TWS_RIGHT				0x00080000
#define WISP_TWS_POS_MASK			0x000F0000
#define WISP_TWS_FIXED_WIDTH		0x00100000
#define WISP_TWS_CLOSE_BT			0x00200000
#define WISP_TWS_MULTI_VIEW_STYLE	0x00400000
#define WISP_TWS_HIDE_TAB_SINGLE	0x00800000

#define	WISP_ID_TAB_CLOSE_BT	WISP_ID_SYS_START

struct WISP_TAB_WND_ITEM
{
	CWispWnd*pWnd;
	WISP_CHAR Name[WISP_MAX_TAB_STR];
	WISP_RECT TabRC;
	CWispDIB* pDIB;
	CWispButton*pClsBT;
};

typedef TList<WISP_TAB_WND_ITEM>	CTabWndList;

class CWispTabWnd : public CWispWnd
{
public:
	CWispTabWnd();
public:
	CTabWndList		m_WndList;
	CWispWnd*		m_pActiveWnd;
	int				m_ActiveWndIndex;
	int				m_nHoverIndex;
	int				m_TabHeight;
	int				m_TabSpaceHeight;
	int				m_TabTailSpace;
	WISP_RECT		m_FullTabRect;
	int				m_FixedTabWidth;
	int				m_TabItemWidth;
public://œ˚œ¢”≥…‰
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnRecalcLayout)
	DECLARE_WISP_MSG(OnGetFocus)
	DECLARE_WISP_MSG(OnMouseMove)
	DECLARE_WISP_MSG(OnMouseLeave)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventCloseBT)
public:
	virtual bool InitWnd();
	virtual	void InsertTabWnd(INOUT WISP_TAB_WND_ITEM*pTabItem,IN const WISP_CHAR*Name,IN CWispWnd*pWnd,IN CWispDIB*pTabDIB);
	virtual void RemoveTabWnd(WISP_TAB_WND_ITEM*pItem,bool bDestroyWnd = true);
	virtual bool OnCloseTabWnd(CWispWnd*pWnd){return true;}
	virtual void OnClosedTabWnd(){}
	virtual void OnTabChanged(CWispWnd*pWnd){}
	void	DrawTabTop();
	void	DrawTabButtom();
	void	DrawTabLeft();
	void	DrawTabRight();
	UINT	InsertWnd(IN const WISP_CHAR*Name, IN CWispWnd*pWnd,IN CWispDIB*pTabDIB = NULL);
	UINT	InsertWndAfter(IN int Index, IN WISP_CHAR*Name, IN CWispWnd*pWnd,IN CWispDIB*pTabDIB = NULL);
	UINT	InsertWndBefore(IN int Index, IN WISP_CHAR*Name,IN CWispWnd*pWnd,IN CWispDIB*pTabDIB = NULL);
	UINT	RemoveWnd(IN int Index,IN bool bDestroyWnd = true);
	UINT	RemoveWnd(IN CWispWnd*pWnd,IN bool bDestroyWnd = true);
	void	RemoveAllWnd(IN bool bDestroyWnd = true);
	CWispWnd*GetActiveWnd();
	UINT	GetActiveWndIndex();
	CWispWnd*SetActiveWnd(IN UINT Index);
	bool	SetTabText(IN UINT Index,IN const WISP_CHAR*pStr);
	void	ChangeActiveWnd(IN CWispWnd*pActiveWnd);
	CWispWnd*GetWnd(UINT Index);
	void	ActiveNextPage();
	void	ActivePrevPage();
	UINT	GetWndCount();
	CWispButton*GetCloseButton(int Index);
	CWispButton*GetCloseButton(CWispWnd*pWnd);
	WISP_SIZE	m_CloseBTSize;
	CWispDIBList*m_pClsBTDIB;
	COLORREF m_FocusWndNameClr;
private:
	void	OnTopRecalcLayout();
	void	OnButtomRecalcLayout();
	void	OnLeftRecalcLayout();
	void	OnRightRecalcLayout();
};

#endif
