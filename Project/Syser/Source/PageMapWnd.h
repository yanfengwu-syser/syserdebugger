#ifndef _PAGEMAPWND_H_
#define _PAGEMAPWND_H_

enum
{
	WND_ID_PAGEDIRECTLIST = WISP_ID_USER_START,
	WND_ID_PAGETABLELIST,
};

class CPageMapWnd :	public CWispSplitWnd
{
	bool			m_PAE;
public:
	CPageMapWnd();
	~CPageMapWnd();
	void	Popup();
	void	UpdateContext();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnClose);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG(OnCommand);
	bool	InsertPageTableList(IN WISP_MSG *pMsg);
	CWispList m_PageDirectList;
	CWispList m_PageTableList;
	DWORD*			m_PageDirectBaseAddress;
	DWORD*			m_PageTableBaseAddress;
	
};

#endif

