#ifndef _FUNCTION_LIST_WND_
#define _FUNCTION_LIST_WND_

class CFunctionListWnd:public CWispList
{
public:
	CFunctionListWnd();
	~CFunctionListWnd();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG_EVENT_MAP
public:
	bool ItemExpandingNotify(HANDLE hItem);
	void ItemUnexpandedNotify(HANDLE hItem);
	void ItemClickNotify(HANDLE hItem,int Col);

	void UpdateContext();

};

#endif