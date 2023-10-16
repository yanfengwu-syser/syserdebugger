#ifndef _SOURCE_CODE_WATCH_LIST_H_
#define _SOURCE_CODE_WATCH_LIST_H_

class CSourceCodeWatchList : public CWispList
{
public:
	CSourceCodeWatchList(void);
	virtual ~CSourceCodeWatchList(void); 
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventAdd)	
	DECLARE_WISP_MSG_EVENT(OnEventRemove)
	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	void	ItemChangedNotify(HANDLE hItem,int Col,CWispString&String);
	void	UpdateContext();
	void	ResetContext();
private:
	HANDLE	m_hLastItem;
	void	CalcLineExp(HANDLE hItem);
	CWispMenu m_PopupMenu;
	HANDLE	m_hRemoveItem;
};


#endif
