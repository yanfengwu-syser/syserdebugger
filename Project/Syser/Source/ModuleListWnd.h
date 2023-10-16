#ifndef _MODULE_LIST_WND_
#define _MODULE_LIST_WND_

class CModuleListWnd : public CWispList
{
public:
	CModuleListWnd();
	~CModuleListWnd();
	void	Popup(bool	bSelectModule=false);
	void	UpdateContext();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventGoto)
	DECLARE_WISP_MSG_EVENT(OnEventPEExplorer)
	
	void	ItemClickNotify(HANDLE hItem,int Col);
public:	
	bool	m_bSelectModule;
	CWispMenu	m_PopupMenu;
	CDbgModule*	m_pDbgModule;
};

#endif //_MODULE_LIST_WND_