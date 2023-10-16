#ifndef _WISP_DC_H_
#define _WISP_DC_H_

#include "WispBase.h"
#include "WispFont.h"

//DrawText() Format Flags
#define WISP_DT_TOP						0x00000000
#define WISP_DT_LEFT					0x00000000
#define WISP_DT_CENTER					0x00000001
#define WISP_DT_RIGHT					0x00000002
#define WISP_DT_VCENTER					0x00000004
#define WISP_DT_BOTTOM					0x00000008
#define WISP_DT_WORDBREAK				0x00000010
#define WISP_DT_SINGLELINE				0x00000020
#define WISP_DT_EXPANDTABS				0x00000040
#define WISP_DT_TABSTOP					0x00000080
#define WISP_DT_NOCLIP					0x00000100
#define WISP_DT_EXTERNALLEADING			0x00000200
#define WISP_DT_CALCRECT				0x00000400
#define WISP_DT_NOPREFIX				0x00000800
#define WISP_DT_INTERNAL				0x00001000
#define WISP_DT_EDITCONTROL				0x00002000
#define WISP_DT_PATH_ELLIPSIS			0x00004000
#define WISP_DT_END_ELLIPSIS			0x00008000
#define WISP_DT_MODIFYSTRING			0x00010000
#define WISP_DT_RTLREADING				0x00020000
#define WISP_DT_WORD_ELLIPSIS			0x00040000
#define WISP_DT_NOFULLWIDTHCHARBREAK	0x00080000
#define WISP_DT_HIDEPREFIX				0x00100000
#define WISP_DT_PREFIXONLY				0x00200000
#define WISP_DT_AUTONEWLINE				0x00400000
#define WISP_DT_MAXCHAR					0x00800000

//DrawString() Format Flag
#define WISP_TEXT_TRANS					0x00000000
#define WISP_TEXT_OPAQUE				0x00000001

//DrawSystemStandardIcon define
#define WISP_SSI_EXPANDBUTTON_SIZE		9
#define WISP_SSI_CHECKBOX_SIZE			11

enum WISP_SSI_ENUM
{
	WISP_SSI_VERT_INC_SPIN = 0,
	WISP_SSI_VERT_DEC_SPIN,
	WISP_SSI_HORZ_INC_SPIN,
	WISP_SSI_HORZ_DEC_SPIN,
	WISP_SSI_CLOSE,
	WISP_SSI_MINIMIZE,
	WISP_SSI_MAXIMIZE,
	WISP_SSI_RESTORE,
	WISP_SSI_DISABLED,
	WISP_SSI_EXPANDBUTTON_EXPAND,
	WISP_SSI_EXPANDBUTTON_COLLAPSE,
	WISP_SSI_CHECKBOX_UNCHECKED,
	WISP_SSI_CHECKBOX_CHECKED,
	WISP_SSI_CHECKBOX_SEMICHECKED,
	WISP_SSI_CHECKBOX_CHECKMARK,
	WISP_SSI_REDIOBOX_SELECTED,
	WISP_SSI_REDIOBOX_UNSELECTED,
	WISP_SSI_REDIOBOX_SELECTED_DRAK,
	WISP_SSI_REDIOBOX_UNSELECTED_DRAK,
};


#define MAX_TAB_ALIGN		32

class CWispBaseWnd;
class CWispBase;

class CWispDC
{
public:
	CWispDC();
	CWispDC(CWispDIB*pDIB);
	CWispDC(WISP_FRAME_BUFFER*pFrameBuffer,WISP_RECT*pRect);
	CWispBaseWnd*	m_pWispWnd;
	CWispBase*		m_pWispBase;
	WISP_FRAME_BUFFER*m_pFrameBuffer;
	WISP_RECT*	m_pRect;
	COLORREF*	m_ColorTable;
	CWispFont*	m_pFont;
	COLORREF	m_TextColor;
	COLORREF	m_TextShadowColor;
	COLORREF	m_TextBKColor;
	COLORREF	m_OldTextColor;
	COLORREF	m_OldTextShadowColor;
	COLORREF	m_OldTextBKColor;
	UINT		m_TextStyle;
	WISP_RECT*	m_pClipRect;
	int			m_TabAlign;
	COLORREF	GetTextColor(void){return m_TextColor;}
	COLORREF	GetTextShadowColor(void){return m_TextShadowColor;}
	COLORREF	GetTextBKColor(void){return m_TextBKColor;}

	void	SetColorTable(COLORREF*ColorTable){m_ColorTable = ColorTable;}
	void	SetTextColor(COLORREF Color){m_OldTextColor=m_TextColor;m_TextColor=Color;}
	void	SetShadowTextColor(COLORREF Color){m_OldTextShadowColor=m_TextShadowColor;m_TextShadowColor=Color;}
	void	SetTextBKColor(COLORREF Color){m_OldTextBKColor=m_TextBKColor;m_TextBKColor=Color;}
	void	SetTabAlign(int Length){m_TabAlign = Length;}
	void	RestoreTextColor(){m_TextColor=m_OldTextColor;}
	void	RestoreShadowTextColor(){m_TextShadowColor=m_OldTextShadowColor;}
	void	RestoreTextBKColor(){m_TextBKColor=m_OldTextBKColor;}

	void	SetTextStyle(UINT Style){m_TextStyle=Style;}
	void	SetTextType(UINT Type);
public:
	bool	AttachDIB(CWispDIB*pDIB);
	bool	AttachFrameBuffer(WISP_FRAME_BUFFER*pFrameBuffer,WISP_RECT*pRect);
	bool	AttachWnd(IN CWispBaseWnd*pWispWnd,IN WISP_RECT*pRect);
	void	InitParam();
	void	Detach();
	bool	ClipDCRect(INOUT WISP_RECT*pRect);
	bool	ClipDCLine(INOUT int*pX1,INOUT int*pY1,INOUT int*pX2,INOUT int*pY2);
	bool	ClipDCPoint(IN WISP_POINT*pPT);
	void	EnableClipRect(WISP_RECT*pClipRect){ m_pClipRect = pClipRect; pClipRect->x += m_pRect->x;pClipRect->y += m_pRect->y;}
	void	DisableClipRect(){ m_pClipRect=NULL; }
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//绘图
	//////////////////////////////////////////////////////////////////////////////////////////////////
public://作裁减
	//绘制字符串
	int		DrawString(IN int x,IN int y,IN const WISP_CHAR*string,IN int Len = -1,int LineIndex = 0,int Flags=0);
	int		DrawString(IN WISP_CHAR* lpString,INOUT WISP_RECT* lpRect,IN UINT uFormat,IN UINT nShowLen = 0,IN int nPreLineMaxCharNum=-1);

	int		DrawString(IN WISP_RECT*pRect,IN const WISP_CHAR*string,IN int Length = -1,int LineIndex = 0);
	int		DrawColorString(IN WISP_RECT*pRect,IN const WISP_COLOR_CHAR*string,IN int Length = -1,int LineIndex = 0);
	//绘制带有阴影的字符串
	int		DrawShadowString(IN int x,IN int y,IN const WISP_CHAR*string,IN int Deep=1,IN int Len = -1,int LineIndex = 0);
	int		DrawShadowString(IN WISP_RECT*pRect,IN const WISP_CHAR*string,IN int Deep=1,IN int Len = -1,int LineIndex = 0);
	//绘制特殊字符
	int		DrawColorString(IN int x,IN int y,IN const WISP_COLOR_CHAR*string,IN int Len = -1,int LineIndex = 0);
	int		DrawRightString(IN int x,IN int y,IN const WISP_CHAR*string,IN int Len = -1,int LineIndex = 0);
	//底层绘制字符串
	int		DrawString(IN CWispFont*pFontInfo,IN int x,IN int y,IN const WISP_CHAR*string,IN COLORREF TextColor,IN WISP_RECT*pClipRect,IN COLORREF*pBKColor=NULL,IN int Len=-1,int LineIndex = 0,int Flags=0);
	int		DrawColorString(IN CWispFont*pLogFont,IN int x,IN int y,IN const WISP_COLOR_CHAR*pStr,IN WISP_RECT*pClipRect,IN int Len = -1,int LineIndex = 0);
	//画点
	void	DrawPixel(IN int x, IN int y, IN COLORREF color);
	//画垂直线
	void	DrawVLine(IN int  x,IN int y1,IN int y2,IN COLORREF color);
	//画水平线
	void	DrawHLine(IN int x1,IN int x2,IN int  y,IN COLORREF color);
	//画垂直短虚线
	void	DrawVDashLine(IN int  x,IN int y1,IN int y2,IN COLORREF color);
	//画水平短虚线
	void	DrawHDashLine(IN int x1,IN int x2,IN int  y,IN COLORREF color);
	//画线
	void	DrawLine(IN int x1,IN int y1,IN int x2,IN int y2,IN COLORREF color);
	//画圆
	void	DrawCircle(IN int x,IN int y,IN int radius,IN COLORREF color);
	//画圆
	void	DrawCircleRightTop(IN int x,IN int y,IN int radius,IN COLORREF color);
	//画圆
	void	DrawCircleRightBottom(IN int x,IN int y,IN int radius,IN COLORREF color);
	//画圆
	void	DrawCircleLeftTop(IN int x,IN int y,IN int radius,IN COLORREF color);
	//画圆
	void	DrawCircleLeftBottom(IN int x,IN int y,IN int radius,IN COLORREF color);
	//绘制矩形
	void	DrawRect(IN WISP_RECT* pRc, IN COLORREF color);
	void	DrawRect(IN int x,IN int y,IN int cx,IN int cy,IN COLORREF color);
	void	DrawRoundRect(IN WISP_RECT* pRc, IN COLORREF color);
	void	Draw3DRect(IN WISP_RECT*pRc,IN COLORREF crTopLeft, COLORREF crBottomRight);
	void	Draw3DRect(IN WISP_RECT*pRc,IN bool bRaised,IN int Deep);
	//绘制短虚线矩形
	void	DrawDashRect(IN WISP_RECT*pRc,IN COLORREF color);
	//绘制填满矩形
	void	DrawFullRect(IN WISP_RECT*pRc,IN COLORREF color);
	void	DrawFullRect(IN int x,IN int y,IN int cx,IN int cy,IN COLORREF color);
	//绘制在X坐标灰度变化的填满窗口
	void	DrawMiddleXGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg);
	void	DrawMiddleXGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc);
	COLORREF	DrawXGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg);
	void		DrawXGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc);
	//绘制在Y坐标灰度变化的填满窗口
	void	DrawMiddleYGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg);
	void	DrawMiddleYGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc);
	COLORREF	DrawYGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg);
	void		DrawYGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc);
	//绘制3D阴影的窗口(bRaised = TRUE 凸 false 凹 Deep 深度)
	void	DrawFrameRect(IN WISP_RECT*pRc,IN bool bRaised=true,IN int Deep=1);
	void	DrawFrameRect(IN int x,IN int y,IN int cx,IN int cy,IN bool bRaised=true,IN int Deep=1);
	//清屏
	void	Clear(IN COLORREF color = 0);
	//贴图
	void	DrawDIBTiled(IN CWispDIB*pDIB,IN WISP_RECT*pRect=NULL);
	void	DrawDIB(IN int x,IN int y,IN CWispDIB*pDIB);
	void	DrawDIB(IN WISP_RECT*pRC,IN CWispDIB*pDIB);
	void	DrawGrayDIB(IN int x,IN int y,IN CWispDIB*pDIB);
	void	DrawGrayDIB(IN WISP_RECT*pRC,IN CWispDIB*pDIB);
	//输出文字
	int		PixelOffToTextOff(const WISP_CHAR* pString,int PixelOff);
	int		GetTextExtent(const WISP_CHAR* pString,int Length=-1,int Index = 0);
	int		GetTextHeight(const WISP_CHAR Char = 0);
	int		GetTextExtentTabExpend(const WISP_CHAR* lpString,int nTabPixelWidth=8*8,int nCount=-1);
	int		GetTextExtentLineTabExpend(const WISP_CHAR* lpString,int nTabPixelWidth=8*8,int nCount=-1);
	//画扩展收缩按钮
	void	DrawSystemStandardIcon(const WISP_RECT&rcBoundary, UINT uStyle, COLORREF color = WISP_RGB(33,162,33));
private:
	int		DrawSingleLineText(IN WISP_CHAR* lpString,IN int nCount,INOUT WISP_RECT* lpRect,IN UINT uFormat);
public:
	int		CalcTextLineNum(WISP_CHAR *lpString,int nCount=-1);
	int		CalcDrawTextRect(WISP_CHAR *lpString,WISP_RECT *lpRect,int nStrLen,UINT uFormat, int nTabPixelWidth);
	void	AdjustNoClipRect(INOUT WISP_RECT *lpRect,IN UINT uFormat);
	int		GetMaxShowCharNum(WISP_CHAR *lpString,int nMaxWidth,  int nTabPixelWidth=0,int nCount=-1);
	int		DrawTabExpendString(int x, int y, WISP_CHAR *lpString,int nStrLen,WISP_RECT rc,int nTabPixelWidth );
public:
	void	CirclePlotPoints(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect);
	void	CirclePlotPointsRightTop(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect);
	void	CirclePlotPointsRightBottom(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect);
	void	CirclePlotPointsLeftTop(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect);
	void	CirclePlotPointsLeftBottom(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect);
	void	DrawCircleRightTop(int xCenter, int yCenter,int radius,COLORREF color,WISP_RECT*pClipRect);
	void	DrawCircleRightBottom(int xCenter, int yCenter,int radius,COLORREF color,WISP_RECT*pClipRect);
	void	DrawCircleLeftTop(int xCenter, int yCenter,int radius,COLORREF color,WISP_RECT*pClipRect);
	void	DrawCircleLeftBottom(int xCenter, int yCenter,int radius,COLORREF color,WISP_RECT*pClipRect);
};

#endif
