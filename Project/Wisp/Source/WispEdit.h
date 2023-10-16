#ifndef	_WISP_EDIT_H_
#define _WISP_EDIT_H_

#include "WispWnd.h"
//////////////////////////////////////////////
//编辑框风格
//////////////////////////////////////////////
#define WISP_ES_EDIT_NORMAL			(WISP_ES_LEFT | WISP_WS_THIN_BORDER | WISP_ES_AUTOHSCROLL)
#define WISP_ES_AUTOHSCROLL			0x01000000
#define WISP_ES_AUTOVSCROLL   		0x02000000
#define WISP_ES_CENTER   			0x04000000
#define WISP_ES_LEFT				0x08000000
#define WISP_ES_LOWERCASE			0x10000000
#define WISP_ES_MULTILINE			0x20000000
#define WISP_ES_NOHIDESEL			0x40000000
#define WISP_ES_PASSWORD			0x80000000
#define WISP_ES_RIGHT				0x00010000
#define WISP_ES_UPPERCASE			0x00020000
#define WISP_ES_READONLY			0x00040000
#define WISP_ES_WANTRETURN			0x00080000
#define WISP_ES_HSCROLL				0x00100000
#define WISP_ES_VSCROLL				0x00200000

#define WISP_ES_EX_STATIC_EDGE			0x00000001
#define WISP_EDIT_TEXT_LEN				0x100
//#define WISP_EDIT_BORDER_COLOR		RGB(127,157,185)

#define WISP_EDIT_MAX_TEXT_LEN			30000
#define WISP_EDIT_MAX_LINETEXT_LEN		20

typedef struct _SELECTPOS{
	int begin;
	int end;
}SELECTPOS;


class CWispEdit : public CWispWnd
{
	typedef enum _INPUTSTAT{
		EDIT_STATE=0,
		SELECT_STATE,		
	}INPUTSTATE;
	//保存每个 ASCII 字符的宽度
	INT		m_CharLenArray[0x140];	
	//是脱字符所在的字符串中的位置。
	INT		m_CurrentCaretHot;
	//是脱字符在的行。
	INT		m_CurrentCaretLine;
	//当前编辑控件中字符的个数
	INT		m_CurrentStringLen;
	// 如果编辑控件是多行则该变量为真。
	bool m_bIsMultiLine;
	//编辑控件中允许的最大字符串长度。在 Create 是设置，如果在Create 是没有设置该值则使用默认值 WISP_EDIT_MAX_TEXT_LEN
	//如果在 Style 中没有 WISP_ES_AUTOHSCROLL  WISP_ES_AUTOVSCROLL WISP_ES_VSCROLL WISP_ES_VSCROLL 则根据客户区的大小来计算长度
	INT		m_StringMaxLen;
	//当是多行的编辑控件时当行可显示的最大字符数
	INT		m_LineMaxLen;
	// 编辑控件可容纳的文本的行数
	UINT m_TextRowNum;
	// 编辑控件中每行可容纳的字符的个数
	UINT m_TextColNum;
	// 当前行的开始位置,当前行指的是脱字符所在的行	
	INT m_CurrentLineCharIndex;
	// 当前行号,当前行指的是脱字符所在的行
	INT m_CurrentLineNum;

	WISP_RECT m_CurrentShowRect;
	INT m_DebugValue;
	bool m_bSelectFlag;
	int m_SelectBegin;
	int m_SelectEnd;
	INPUTSTATE m_CurrentInputStat; 
public:
	CWispEdit(void);
	~CWispEdit(void);
public:

	bool	Create( IN WISP_CHAR*Name,IN const CWispRect&Rect,IN CWispBaseWnd*pParentWnd = NULL,IN UINT CmdID = 0,		IN UINT Style=WISP_WS_NORMAL,IN UINT ShowMode=WISP_SH_NORMAL);

	bool	Create(IN WISP_RECT&RectAtWnd,IN UINT Style,IN CWispBaseWnd*pParentWnd,IN UINT CmdID);
	bool	Create(IN WISP_CHAR* Name,IN INT x,IN INT y,IN INT cx,IN INT cy,IN CWispBaseWnd*pParentWnd=NULL,IN UINT CmdID=0,IN UINT Style=WISP_ES_EDIT_NORMAL,IN UINT ShowMode=WISP_SH_NORMAL);
public://消息映射
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnGetFocus)
	DECLARE_WISP_MSG(OnLostFocus)
	DECLARE_WISP_MSG(OnChar)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnUpdateBorder)	
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnMouseLeave)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnMouseEvent)
	DECLARE_WISP_MSG(OnMouseLeftButtonUp)
	DECLARE_WISP_MSG(OnMouseLeftButtonDown)
	DECLARE_WISP_MSG(OnMouseMove)
	DECLARE_WISP_MSG(OnRecalcLayout)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG(OnEventPaste);
	DECLARE_WISP_MSG(OnEventCopy);
public:
	void OnKeyBack(void);	
	void OnLeftKey(IN WISP_MSG *pMsg);
	void OnRightKey(IN WISP_MSG *pMsg);
	void OnReturnKey(IN WISP_MSG *pMsg);
	void OnBackKey(IN WISP_MSG *pMsg);
	void OnHomeKey(IN WISP_MSG *pMsg);
	void OnEndKey(IN WISP_MSG *pMsg);
	void OnDeleteKey(IN WISP_MSG *pMsg);
	
	//计算在给定的宽度内所能容纳的最大字符数。
	//参数是  nLength 被容纳的字符的长度
	int GetMaxShowCharNum(WISP_CHAR* lpszString, INT nWidth,OUT INT *nLength = NULL, bool isMultiLine=FALSE);
	//用来判断编辑控件是否可以插入这个字符
	bool IsInsertChar(IN WISP_CHAR wch);
	INT InsertChar(IN WISP_CHAR *pChar,IN INT nPosition=-1,IN int Counter=1);
	INT DeleteChar(IN INT nPosition=-1,IN INT nCount = 1,IN WISP_MSG *pMsg=NULL);
	//计算脱字符所在的位置。相对于当前行的。
	//int GetCurrentLinePosition();
	INT GetCurrentLinePosition(INT nCharNum = -1);
	INT GetPrevLineBeginPosition(IN INT nEndPostion,OUT INT *nStringLen = NULL);
	//计算脱字符所在的行的长度。
	INT GetCaretLineCharWidth();
	INT GetLineWidth(IN const WISP_CHAR *pSrc);
	//计算行数 nPerLineMaxCharNum 是一行可以容纳的最多字符数
	INT CalcLineNum(IN const WISP_CHAR *pSrc,IN INT nCount = -1,IN INT nPerLineMaxCharNum = 0);
	//计算行数 nLineWidth 是行的象素宽度
	INT CalcLineNumForWidth(IN const WISP_CHAR *pSrc,IN INT nCount = -1,IN INT nLineWidth = -1);
	INT CaretLeftMove();
	INT CaretRightMove();
	INT GetCurrentPosition(OUT INT nIndex,INT *nLineLength=NULL);
	bool SetWindowText(const WISP_CHAR* pString);
	int GetCharIndexByPoint(WISP_POINT point,WISP_POINT&retpoint);
	WISP_POINT GetPositionByIndex(IN int index);
	WISP_RECT m_SelectRect;
	COLORREF m_BSelColor;
	int SelectText(int SelectBegin,int SelectEnd);
	bool CharIsVisible(int index);
	void EnableVisible(int index);
};

#endif


