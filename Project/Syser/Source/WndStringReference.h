#ifndef __STRING_REFERENCE_LIST__H__
#define __STRING_REFERENCE_LIST__H__

typedef DWORD	VALUE_TYPE;

class CStringReferenceList;

class CFindStringForm : public CWispForm
{
public:
	CFindStringForm();
	~CFindStringForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnFindTextCmd)
	DECLARE_WISP_MSG_EVENT(OnFindButtonEvent)
public:
	
	CWispButton* m_FindButton;
	CWispButton* m_CloseButton;
	CWispEdit* m_FindEdit;
	CStringReferenceList *m_pContextList;
	void SetContextList(CStringReferenceList* pContextList);
};


class CStringReferenceList : public CWispList
{
	typedef TMap<UINT,UINT> SRHOTKEYMAP;
public:

	CStringReferenceList();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnGetFocus)
	DECLARE_WISP_MSG(OnChar)	
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventSearchAgain)
	DECLARE_WISP_MSG_EVENT(OnEventSearch)
	DECLARE_WISP_MSG(OnMouseDBClick)
public:
	void	ItemClickNotify(HANDLE hItem,int Col);
	void	UpdateContext(ULPOS Address,bool bRelocal=false);
	void	ResetContext();
	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	void	PopupMenu();
	void	SetWndType(int Type){m_TypeWnd=Type;}
	int		m_TypeWnd;
	int		m_MaxMatchLen;
	CWispMenu m_PopupMenu;      
	CWispString m_SearchString;
	SRHOTKEYMAP m_HotKeyMap;
	void			AttachShortcutKey();
	CFindStringForm m_FindDlg;
	bool FindString(WISP_CHAR* pSearch=NULL);
	HANDLE m_MenuSearchAgain;
	
};


class CStatusWnd : public CWispWnd
{
public:
	CStatusWnd(){}
	virtual ~CStatusWnd(){}

	DECLARE_WISP_MSG_MAP	
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnUpdateBorder)
	DECLARE_WISP_MSG(OnCreate)
	
	CWispString m_StatusString;
};


class CFindListWnd : public CWispWnd
{
public:
	CFindListWnd(){}
	virtual ~CFindListWnd(){}
	CStatusWnd m_StatusWnd;
	CStringReferenceList m_ListWnd;
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnListWndCmd)
	void	SetWndType(int Type){m_TypeWnd=Type;}
	int		m_TypeWnd;
};




#endif  /__STRING_REFERENCE_LIST__H__
