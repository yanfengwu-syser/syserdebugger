#ifndef _PROCESS_LIST_H_
#define _PROCESS_LIST_H_


class CProcessList : public CWispList
{
public:
	CProcessList();
	~CProcessList();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG(OnMenuTerminate)
	DECLARE_WISP_MSG(OnMenuRealTime)
	DECLARE_WISP_MSG(OnMenuHigh)
	DECLARE_WISP_MSG(OnMenuAboveNormal)
	DECLARE_WISP_MSG(OnMenuNormal)
	DECLARE_WISP_MSG(OnMenuBelowNormal)
	DECLARE_WISP_MSG(OnMenuIdle)
	DECLARE_WISP_MSG(OnMenuEmptyWorkingSet)
	DECLARE_WISP_MSG(OnMenuDetail)
public:
	bool	ItemExpandingNotify(HANDLE hItem);
	void	ItemDBClickNotify(HANDLE hItem,int Col);
	HANDLE	GetCurrentSelectProcess(IN DWORD dwDesiredAccess);
	void	SetPriorityClass(DWORD Class);
	bool	UpdatePriorityClassItem();
	HANDLE	m_hRealTimeMenu;
	HANDLE	m_hHighMenu;
	HANDLE	m_hAboveNormalMenu;
	HANDLE	m_hNormalMenu;
	HANDLE	m_hBelowNormalMenu;
	HANDLE	m_hIdleMenu;
	HANDLE	m_hSystemItem;
	CWispMenu	m_PopupMenu;
	bool	ListOSProcess();
};


#endif