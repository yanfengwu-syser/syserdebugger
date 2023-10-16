#ifndef _CALL_STACK_WND_
#define _CALL_STACK_WND_

class CCallStackWnd : public CWispList
{
public:
	CCallStackWnd();
	~CCallStackWnd();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	void	ItemDBClickNotify(HANDLE hItem,int Col);
	void	Popup();
	void	UpdateContext();
	HANDLE	m_hCurFrameItem;
	void	UpdateFrame(HANDLE hItem);
};

#endif //_CALL_STACK_WND_