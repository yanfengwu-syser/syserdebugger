#ifndef _WISP_BUTTON_H_
#define _WISP_BUTTON_H_

#include "WispWnd.h"

//////////////////////////////////////////////
//°´Å¥·ç¸ñ
//////////////////////////////////////////////
#define WISP_BS_NORMAL			0
#define WISP_BS_TEXT_LEFT		0x00010000
#define WISP_BS_TEXT_RIGHT		0x00020000
#define WISP_BS_TEXT_POS_MASK	0x00030000
#define WISP_BS_DIB_LEFT		0x00100000
#define WISP_BS_DIB_RIGHT		0x00200000
#define WISP_BS_DIB_POS_MASK	0x00300000
#define WISP_BS_DISABLE			0x00400000
#define WISP_BS_NOBORDER		0x00800000
#define WISP_BS_TOOLBAR_BT		0x01000000

enum WISP_BT_DIB
{
	WISP_BT_DIB_NORMAL=0,
	WISP_BT_DIB_HOVER,
	WISP_BT_DIB_DOWN,
	WISP_BT_DIB_DISABLE,
	WISP_BT_DIB_COUNT
};


class CWispButton : public CWispBaseWnd
{
	bool		m_bSetTextPos;
	WISP_RECT	m_TextRect;
public:
	CWispButton();
	~CWispButton();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnMove);
	DECLARE_WISP_MSG(OnMouseMove);
	DECLARE_WISP_MSG(OnMouseLeave);
	DECLARE_WISP_MSG(OnUpdate);
public:
	virtual bool	InitWnd();
	virtual void	RecalcLayout();
	virtual void	HoverNotify(){};
	virtual void	UnhoverNotify(){};
	bool		m_bPressed;
	bool		m_bMouseInBTRect;
	CWispDIB*	m_DIBList[WISP_BT_DIB_COUNT];
	bool		CreateEx(IN CWispDIB* pDib, IN int x, IN int y, IN CWispWnd*pParentWnd = NULL, IN UINT CmdID = 0,UINT Style = WISP_BS_NOBORDER);
	bool		CreateEx(IN CWispDIBList* pDibList, IN int x, IN int y, IN CWispWnd*pParentWnd = NULL, IN UINT CmdID = 0,UINT Style = WISP_BS_NOBORDER);
	bool		SetDIB(CWispDIB*pDIB,WISP_BT_DIB ID = WISP_BT_DIB_NORMAL);
	bool		SetDIBList(CWispDIBList*pDIBList);
	void		SetTextPos(IN WISP_POINT Point);
	void		SetTextRect(IN WISP_RECT TextRect);
};

#endif

