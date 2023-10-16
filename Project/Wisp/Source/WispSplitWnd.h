#ifndef _WISP_SPLIT_WND_H_
#define _WISP_SPLIT_WND_H_

#include "WispWnd.h"

//用于SplitWnd本身
#define WISP_SWS_VERT			0x00010000
#define WISP_SWS_HORZ			0x00020000
#define WISP_SWS_AUTO_RESIZE	0x00040000
//用于子窗口
#define WISP_SWS_TITLE			0x10000000

struct WISP_SPLIT_WND
{
	CWispWnd*	pWnd;
	int			SizeXorY;
	UINT		Style;
	WISP_RECT	SplitRect;
};

typedef TList<WISP_SPLIT_WND>	CWSWndList;

class CWispSplitWnd : public CWispWnd
{
public:
	CWispSplitWnd();
	~CWispSplitWnd();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG(OnUpdate);
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnMouseMove);
	DECLARE_WISP_MSG(OnMouseLeave);
	DECLARE_WISP_MSG(OnMouseDBClick);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnSize);
	DECLARE_WISP_MSG(OnParentResize);
public:
	WISP_SIZE		m_DeltaSize;
	int				m_SplitBorderSize;
	CWSWndList		m_WndList;
	CWSWndList::IT	m_CurSplitWndIt;
	CWSWndList::IT	m_NextSplitWndIt;
	bool	InsertWnd(IN CWispWnd*pWnd,IN UINT Style,IN int SizeXorY,IN int InsertPos = -1);
	bool	RemoveWnd(IN CWispWnd*pWnd);
	bool	ResizeWndSpace(int Pos,int SizeXorY);
	bool	GetWndSpace(int Pos,int& SizeXorY)const ;
	void	AdjustWndPos();
	void	ExpandWnd(int Pos);
};


#endif
