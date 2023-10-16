#ifndef _COMMENT_LIST_H_
#define _COMMENT_LIST_H_

class CCommentList : public CWispList
{
public:
	CCommentList();
	void Popup();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnMouseDBClick);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventGoto)	
	DECLARE_WISP_MSG_EVENT(OnEventRemove)
	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	void	UpdateContext();
	CWispMenu m_PopupMenu;
	HANDLE	m_hSelectItem;
	HANDLE	m_hGotoMenuItem;
};

#endif
