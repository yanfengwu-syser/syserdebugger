#ifndef _RUN_TRACE_WND_H
#define _RUN_TRACE_WND_H

class CRunTraceWnd:public CWispList
{
public:
	CRunTraceWnd();
	~CRunTraceWnd();
	void Popup();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnMouseDBClick);
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventCopy)
	COLORREF	m_ColorTable[MAX_COLOR];
	void UpdateContext();
};

#endif //_RUN_TRACE_WND_H
