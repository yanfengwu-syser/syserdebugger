#ifndef _WISP_POWER_HEADER_H_
#define _WISP_POWER_HEADER_H_

#include "WispWnd.h"

// CWispHeader

#define WHS_ALIGN_LEFT	0x00000000
#define WHS_INVISIBLE	0x00010000
#define WHS_ENABLE_EDIT	0x00020000
#define HEADER_MARGIN	4


class CWispHeader : public CWispWnd
{

public:
	typedef struct stWispHeaderItem
	{
		TWispString	strHeading;
		INT			nFormat;	
		INT			nWidth;		//列宽
		void*		pData;		//用户自定义数据
	}WHITEM;

public:
	CWispHeader();
	virtual ~CWispHeader();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnUpdateBorder);
	DECLARE_WISP_MSG(OnMouseLeave);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnMouseLButtonDown);
	DECLARE_WISP_MSG(OnMouseLButtonUp);
	DECLARE_WISP_MSG(OnDragMove);
	DECLARE_WISP_MSG(OnBeginDrag);
	DECLARE_WISP_MSG(OnEndDrag);
	DECLARE_WISP_MSG(OnMouseMove);
	DECLARE_WISP_MSG(OnDestroy);

	virtual void DrawScreen(IN WISP_MSG *pMsg);
	virtual void DrawScreen(WISP_POINT &point,IN WISP_MSG *pMsg);

	int InsertItem(const WHITEM& HeaderItem, int nCol = -1);
	int InsertItem(const WISP_CHAR* pszHeading, int nWidth = -1, int nFormat = WHS_ALIGN_LEFT, void* pData = 0, int nCol = -1);
	void SetItemText(const WISP_CHAR* pszHeading, int nCol);
	void SetItemWidth(const int nWidth, int nCol);

	int GetItemCount() { return m_vColumns.Count(); }
	WHITEM* GetItem(int nIndex);
	void SetItem(int nIndex, WHITEM& HeaderItem);
	int GetItemIndex(int col)const;

protected:
//	DWORD		m_dwStyle;
//	WISP_RECT	m_rcBoundary;	//最外围边界
//	CWispWnd*	m_pWndParent;
//	UINT		m_nID;			//自身ID
	int		m_DragColumnIndex;
	bool	m_ColumnDrag;
	bool	m_DragMoving;
	bool	m_RestoreCursor;
	WISP_POINT m_PrevDragPoint;
	int		m_PrevWidth;
	TList<WHITEM>		m_vColumns;

	void DrawHeader(WISP_POINT& point,IN WISP_MSG *pMsg);	
	
public:
	int *m_ColumnOrgIndex;
	int m_ColumnIndexCounter;
	WISP_POINT m_DragBeginPt;
	typedef enum{MODIFY_ITEM_WIDTH,EXCHANGE_ITEM_POSITION,MAX_LBUTTONDOWN_TYPE}	HEADER_LBUTTONDOWN_TYPE;
	HEADER_LBUTTONDOWN_TYPE m_LButtonDownEventType;
	int PointInItemIndex(IN WISP_POINT point,int *xdel=NULL,int *ydel=NULL);
	int DrawDragRect(WISP_RECT rc);
};

#endif//_WISP_POWER_HEADER_H_

