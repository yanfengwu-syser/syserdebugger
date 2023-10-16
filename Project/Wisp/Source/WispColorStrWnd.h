#ifndef _WISP_COLOR_STR_WND_
#define _WISP_COLOR_STR_WND_

#include "WispWnd.h"

#define MAX_LINE_CHAR				256
#define WISP_COLOR_STR_MARGIN		5

#define WISP_WCSS_FREE_CARET		0x00010000
#define WISP_WCSS_SELECT_STRING		0x00020000

class CWispColorStrWnd : public CWispWnd
{
public:
	CWispColorStrWnd(void);
	virtual ~CWispColorStrWnd(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnScrollEvent)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnRecalcLayout)
	DECLARE_WISP_MSG(OnMouseMove)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventCopy)
public:
	virtual bool InitWnd();
	virtual BYTE GetLineStr(IN int LineIndex,OUT WISP_COLOR_CHAR*pColorStr)=0;
	virtual void SetMaxLines(IN int nLine);
	virtual void SetMaxChars(IN int nChar);
	void	CalcPonitStrPos(IN WISP_POINT*pPoint,WISP_POINT*pStrPT);
	void	UpdateCaretState();
	void	ClearSelect();
public:
	WISP_POINT	m_ScrPos;
	WISP_POINT	m_CaretPos;
	WISP_POINT	m_RealSelStartPos;
	WISP_POINT	m_RealSelEndPos;
	WISP_POINT*	m_pSelStartPos;
	WISP_POINT*	m_pSelEndPos;
	bool		m_bSelect;
	int			m_Margin;
	int			m_nCharsPerLine;
	int			m_nLinesPerPage;
	int			m_MaxChars;
	int			m_MaxLines;
private:
	bool inline	IsSelectChar(int ScrX,int ScrY);
};

#endif


