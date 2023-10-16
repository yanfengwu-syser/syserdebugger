#ifndef _WISP_TOOLBAR_
#define _WISP_TOOLBAR_

#include "WispWnd.h"

struct WISP_TOOLBAR_ITEM
{
	CWispBaseWnd*	pItemWnd;
	CWispDIB*		pDIB;
	UINT			ItemStyle;
};

struct WISP_TOOLBAR_RES_ITEM
{
	UINT		CmdID;
	int			DIBIndex;
	UINT		ItemStyle;
	WISP_CHAR*	pTipString;
	int			Width;
	int			CtrlStyle;
};

#define WISP_TBIS_BUTTON					0x00000000
#define WISP_TBIS_EDIT						0x00000001
#define WISP_TBIS_STATIC_DIB				0x00000002
#define WISP_TBIS_STATIC_STR				0x00000004
#define WISP_TBIS_SPEARATOR					0x00010000
#define WISP_TBIS_RIGHT_ALIGN				0x00020000

#define WISP_TBS_WINDOW						0x00010000

#define WISP_TOOLBAR_RES_STATIC_DIB(nDIB)	{WISP_ID_STATIC_DIB,nDIB,WISP_TBIS_STATIC_DIB|WISP_TBIS_RIGHT_ALIGN,NULL}
#define WISP_TOOLBAR_RES_STATIC_STR(Str)	{WISP_ID_STATIC_STR,0,WISP_TBIS_STATIC_STR|WISP_TBIS_RIGHT_ALIGN,Str}
#define WISP_TOOLBAR_RES_SEPARATOR			{0,0,WISP_TBIS_SPEARATOR}
#define WISP_TOOLBAR_RES_END				{0,0,0,NULL,0}

typedef	TList<WISP_TOOLBAR_ITEM>			CBTList;

class CWispToolbar : public CWispWnd
{
public:
	CWispToolbar();
	~CWispToolbar();
public:
	CBTList	m_BTList;
	CWispDIBList*m_pDIBList;
	int		m_Margin;
	int		m_SeparatorWitdh;
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnRecalcLayout);
	DECLARE_WISP_MSG(OnParentResize);
	DECLARE_WISP_MSG(OnDestroy);
public:
	bool	CreateEx(CWispWnd*pParentWnd,int y,int Height,UINT CmdID,UINT Style);
	bool	LoadToolbar(CWispDIBList*pDIBList,WISP_TOOLBAR_RES_ITEM*pResItem);
	bool	InsertButton(int Pos,UINT ItemStyle,UINT CmdID,UINT Style,CWispDIB*pWispDIB,WISP_CHAR*HelpString=NULL);
	bool	InsertEdit(int Pos,UINT ItemStyle,int Width,UINT CmdID,UINT Style,WISP_CHAR*HelpString=NULL);
	bool	InsertSeparator(int Pos,UINT ItemStyle);
	bool	InsertStaticDIB(int Pos,UINT ItemStyle,UINT CmdID,CWispDIB*pWispDIB);
	bool	InsertStaticStr(int Pos,UINT ItemStyle,UINT CmdID,WISP_PCSTR String);
	bool	RemoveItem(int Pos);
	CWispBaseWnd*GetToolbarItemByPos(int Pos);
	CWispBaseWnd*GetToolbarItem(UINT CmdID);
	virtual	void SetOwner(CWispBaseWnd*pOwnerWnd);
	bool	EnableItemByPos(int Pos,bool State);
	bool	EnableItem(UINT CmdID,bool State);
};

#endif


