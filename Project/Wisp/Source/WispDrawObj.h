#ifndef _WISP_DRAW_OBJ_H_
#define _WISP_DRAW_OBJ_H_

class CWispDC;

enum SYSTEM_COLOR
{
	SC_BLACK			= 0,
	SC_WHITE			,
	SC_RED				,
	SC_LIGHT_RED		,
	SC_GREEN			,
	SC_LIGHT_GREEN		,
	SC_BLUE				,
	SC_LIGHT_BLUE		,
	SC_BROWN			,
	SC_LIGHT_BROWN		,
	SC_CYAN				,
	SC_LIGHT_CYAN		,
	SC_GRAY				,
	SC_LIGHT_GRAY		,
	SC_YELLOW			,
	SC_LIGHT_YELLOW		,//15
	SC_ORANGE_RED		,
	SC_LIGHT_ORANGE_RED ,
	SC_DESKTOP_BG		, // 
	SC_DISABLE_BG		, // 
	SC_CLIENT_BG		, // 
	SC_CLIENT_TEXT		, // 
	SC_CAPTION_TEXT		, // 
	SC_CAPTION_BG		, // 
	SC_CAPTION_LIGHT_BG	, // 
	SC_SELECT_BG		, // 
	SC_SCROLL_SLIDE_BG	, //
	SC_SCROLL_SLIDE_DARK_BG	,//
	SC_BORDER_BG		, // 
	SC_BRIGHT			, // 
	SC_SHADOW			, // 
	SC_SHADOW_LIGHT		, // 
	SC_SCROLL_BG		, // 
	SC_SCROLL_BT_BG		, // 
	SC_CURSOR			,

	// all ctrls
	SC_CTRL_NORMAL_BORDER_TOPLEFT		,
	SC_CTRL_NORMAL_BORDER_BOTTOMRIGHT	,
	SC_CTRL_NORMAL_DARK_BORDER			,	// CheckBox边框色，Button边框色
	SC_CTRL_NORMAL_CLIENT_BG			,
	SC_CTRL_NORMAL_DARK_CLIENT_BG		,	// Button未按下时，Tab非激活时
	SC_CTRL_NORMAL_DARK_CLIENT_BG2		,	// Button按下时
	SC_CTRL_SELECTED_BG		,
	SC_CTRL_SELECTED_LIGHT_BG,
	SC_CTRL_HOVER_BG		,
	SC_CTRL_HOVER_LIGHT_BG	,
	SC_CTRL_SELECTED_TEXT	,
	SC_CTRL_NORMAL_TEXT		,
	SC_CTRL_HOVER_TEXT		,
	SC_CTRL_NORMAL_FOCUS	,
	SC_CTRL_HOVER_FOCUS		,

	SC_MENU_BG		,
	SC_MENU_LIGHT_BG,
	SC_MENU_BORDER	,
	SC_STDICON_NORMAL_BORDER	,	// 标准图标边框，包括List中的收缩按钮和选择按钮,close,minimaize,maxmize
	SC_STDICON_HOVER_BORDER		,
	SC_STDICON_DOWN_BORDER		,
	SC_STDICON_NORMAL_CHECKMARK	,	// CheckBox等控件中勾的颜色
	SC_STDICON_NORMAL_PLUS		,	// CheckBox等控件中加减号的颜色
	SC_SCROLL_NORMAL_BUTTON		,
	SC_SCROLL_HOVER_BUTTON		,
	SC_SCROLL_DOWN_BUTTON		,

	SC_FRAME_NORMAL_BG		, // Header
	SC_FRAME_NORMAL_LEFT	, // 
	SC_FRAME_NORMAL_RIGHT	, // 
	SC_FRAME_NORMAL_BOTTOM1	, // 
	SC_FRAME_NORMAL_BOTTOM2	, // 
	SC_FRAME_NORMAL_BOTTOM3	, // 
	SC_FRAME_HOVER_BG		, // 
	SC_FRAME_HOVER_BOTTOM1	, // 
	SC_FRAME_HOVER_BOTTOM2	, // 
	SC_FRAME_HOVER_BOTTOM3	, // 

	SC_GRADIENT_GREEN_1		, // Progress, Cursor
	SC_GRADIENT_GREEN_2		, // 
	SC_GRADIENT_GREEN_3		, // 
	SC_GRADIENT_GREEN_4		, // 
	SC_GRADIENT_GREEN_5		, // 
	SC_GRADIENT_GREEN_6		, // 
	SC_GRADIENT_GREEN_7		, // 

	SC_GRADIENT_YELLOW,
	SC_GRADIENT_YELLOW_1	, // Button, Header, Tab
	SC_GRADIENT_YELLOW_2	, // 
	SC_GRADIENT_YELLOW_3	, // 

	SC_GRADIENT_BULE_1		, // Caption
	SC_GRADIENT_BULE_2		,
	SC_GRADIENT_BULE_3		,
	SC_GRADIENT_BULE_4		,
	SC_GRADIENT_BULE_5		,
	SC_GRADIENT_BULE_6		,
	SC_GRADIENT_BULE_7		,
	SC_GRADIENT_BULE_8		,

	SC_RAV_1				,
	SC_RAV_2				,
	SC_RAV_3				,
	SC_RAV_4				,
	SC_RAV_5				,
	SC_UNNAMED_1			,
	SC_UNNAMED_2			,
	SC_UNNAMED_3			,
	SC_UNNAMED_4			,
	SC_UNNAMED_5			,
	SC_UNNAMED_6			,
	SC_UNNAMED_7			,
	SC_UNNAMED_8			,
	SC_UNNAMED_9			,
	SC_UNNAMED_10			,
	SC_UNNAMED_11			,
	SC_UNNAMED_12			,
	SC_UNNAMED_13			,
	SC_UNNAMED_14			,
	SC_UNNAMED_15			,
	SC_UNNAMED_16			,
	SC_UNNAMED_17			,
	SC_UNNAMED_18			,
	SC_UNNAMED_19			,
	SC_UNNAMED_20			,
	SC_UNNAMED_21			,
	MAX_SYSTEM_COLOR
};

#define 	SC_GRADIENT_GREEN_BEGIN		SC_GRADIENT_GREEN_1
#define 	SC_GRADIENT_GREEN_END		SC_GRADIENT_GREEN_7

#define 	SC_GRADIENT_BLUE_BEGIN		SC_GRADIENT_BULE_1
#define 	SC_GRADIENT_BLUE_END		SC_GRADIENT_BULE_8

class CWispDrawObj
{
public:
	CWispDrawObj();
	virtual ~CWispDrawObj();
	COLORREF	m_crSystem[MAX_SYSTEM_COLOR];
public:
	virtual bool Init();
	virtual void Release();
	virtual void InitSystemColor();
	virtual void DrawBorder(CWispDC*pDC,WISP_RECT*pRect,int nSize);
	virtual void DrawCaption(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawToolbarBK(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawClient(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawCtrlBorder(CWispDC* pDC, WISP_RECT* pRect, int nSize);
	virtual void DrawCtrlClient(CWispDC* pDC, WISP_RECT* pRect);
	virtual void DrawCtrlStaticEdge(CWispDC* pDC, WISP_RECT* pRect);
	virtual void DrawCtrlClientEdge(CWispDC* pDC, WISP_RECT* pRect);
	virtual void DrawCtrlModalFrame(CWispDC* pDC, WISP_RECT* pRect);
	virtual void DrawCtrlFocusRect(CWispDC* pDC, WISP_RECT* pRect);
	virtual void DrawVertScrollRect(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawVertScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawHorzScrollRect(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawHorzScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawSplitRect(CWispDC*pDC,WISP_RECT*pRect,bool bHorz);
	virtual void DrawButtonClient(CWispDC*pDC,WISP_RECT*pRect,UINT State);
	virtual void DrawButtonFrameRect(CWispDC*pDC,WISP_RECT*pRect,UINT State);
	virtual void DrawTabBackground(CWispDC* pDC, WISP_RECT* pRect);
	virtual void DrawTabItem(CWispDC* pDC, WISP_RECT* pRect, UINT State);
	virtual void DrawHeaderFrameRect(CWispDC*pDC,WISP_RECT*pRect,UINT State);
	virtual void DrawProgress(CWispDC* pDC, WISP_RECT* pRect, UINT uStyle, int nPrecent);
	virtual void DrawSystemStandardIcon(CWispDC* pDC,const WISP_RECT* pRect, UINT uStyle, UINT State=STATUS_NORMAL);
	virtual void DrawCursorArrow(CWispDC* pClipDC,WISP_POINT* pHotPT);
	virtual void DrawCursorDrag(CWispDC*pClipDC,WISP_POINT*pHotPT);
	virtual void DrawCursorResizeVert(CWispDC* pClipDC,WISP_POINT* pHotPT);
	virtual void DrawCursorResizeHorz(CWispDC* pClipDC,WISP_POINT* pHotPT);
	virtual void DrawCursorResizeLeftLean(CWispDC* pClipDC,WISP_POINT* pHotPT);
	virtual void DrawCursorResizeRightLean(CWispDC* pClipDC,WISP_POINT* pHotPT);
	virtual void DrawListColumnTitleBK(CWispDC* pClipDC,WISP_RECT*pRc);
	virtual void DrawListSelectedItemBK(CWispDC* pClipDC,WISP_RECT*pRc);
	virtual void DrawMenuIconSpaceBK(CWispDC* pClipDC,WISP_RECT*pRc);
	virtual void DrawMenuBK(CWispDC* pClipDC,WISP_RECT*pRc,UINT Status);
	virtual void DrawMenuString(CWispDC* pClipDC,WISP_RECT*pRc,WISP_PCSTR String,UINT Status);
	virtual void DrawMenuTopFrame(CWispDC* pClipDC,WISP_RECT*pRc);
	virtual void DrawMenuBottomFrame(CWispDC* pClipDC,WISP_RECT*pRc);
public:
	void DrawCursor(WISP_POINT* pHotPT, CWispDC* pClipDC,UINT CursorType,CWispDIB*pDIB);
};

class CWispDIBDrawObj : public CWispDrawObj
{
public:
	CWispDIBDrawObj();
	virtual ~CWispDIBDrawObj();
	CWispDIBList	m_DIBVertIncSpin;
	CWispDIBList	m_DIBVertDecSpin;
	CWispDIBList	m_DIBHorzIncSpin;
	CWispDIBList	m_DIBHorzDecSpin;
	CWispDIBList	m_DIBClose;
	CWispDIBList	m_DIBMin;
	CWispDIBList	m_DIBMax;
	CWispDIBList	m_DIBRestore;
	CWispDIBList	m_DIBRedioBoxIcon;
	CWispDIB		m_DIBArrow;
	CWispDIB		m_DIBHResize;
	CWispDIB		m_DIBVResize;
	CWispDIB		m_DIBLResize;
	CWispDIB		m_DIBRResize;
	CWispDIB		m_DIBDrag;
	const	char*	m_szSkinDir;
public:
	virtual bool Init();
	virtual void Release();
	virtual void DrawBorder(CWispDC*pDC,WISP_RECT*pRect,int nSize);
	virtual void DrawCaption(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawToolbarBK(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawSystemStandardIcon(CWispDC* pDC,const WISP_RECT* pRect, UINT uStyle, UINT State);
	virtual void DrawCursorArrow(CWispDC*pClipDC,WISP_POINT*pHotPT);
	virtual void DrawCursorDrag(CWispDC*pClipDC,WISP_POINT*pHotPT);
	virtual void DrawCursorResizeVert(CWispDC*pClipDC,WISP_POINT*pHotPT);
	virtual void DrawCursorResizeHorz(CWispDC*pClipDC,WISP_POINT*pHotPT);
	virtual void DrawSplitRect(CWispDC*pDC,WISP_RECT*pRect,bool bHorz);
	virtual void DrawCursorResizeLeftLean(CWispDC* pClipDC,WISP_POINT* pHotPT);
	virtual void DrawCursorResizeRightLean(CWispDC* pClipDC,WISP_POINT* pHotPT);
	virtual void DrawVertScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawHorzScrollSlideRect(CWispDC*pDC,WISP_RECT*pRect);
	virtual void DrawListColumnTitleBK(CWispDC* pClipDC,WISP_RECT*pRc);
	virtual void DrawListSelectedItemBK(CWispDC* pClipDC,WISP_RECT*pRc);
	virtual void DrawMenuIconSpaceBK(CWispDC* pClipDC,WISP_RECT*pRc);
	virtual void DrawMenuBK(CWispDC* pClipDC,WISP_RECT*pRc,UINT Status);
	virtual void DrawMenuString(CWispDC* pClipDC,WISP_RECT*pRc,WISP_PCSTR String,UINT Status);
};


#endif
