#ifndef _STACK_WATCH_LIST_H_
#define _STACK_WATCH_LIST_H_

typedef DWORD	VALUE_TYPE;

enum STACK_WATCH_ADDR_MOD
{
	STACK_WATCH_ADDRESS_MOD = 0,
	STACK_WATCH_OFFSET_MOD,
	STACK_WATCH_REL_TO_ESP_MOD,
	STACK_WATCH_REL_TO_EBP_MOD
};

typedef enum _COMMENT_TYPE
{
	CT_ASCII=0,
	CT_UINCODE=1,
	CT_SYMBOLS,
	CT_RETURN_ADDRESS
}COMMENT_TYPE;

class CStackWatchList : public CWispList
{

	typedef struct _SEH_STR
	{
		DWORD dwNext;
		DWORD SEHHandler;
	}SEH_STR;
	typedef TMap<DWORD,DWORD> SEH_MAP;

	//typedef bool (CStackWatchList::*STACK_HOTKEY_FP)(IN UINT Index);

	//class CStackHotKey
	//{
	//public:
	//	UINT m_ColIndex;
	//	STACK_HOTKEY_FP m_fpHotKey;
	//	CStackHotKey(){};
	//	CStackHotKey(UINT Index,STACK_HOTKEY_FP fpHotKey):m_ColIndex(Index),m_fpHotKey(fpHotKey){};
	//	~CStackHotKey(){}
	//};

	typedef TMap<UINT,UINT> STACKHOTKEYMAP;
public:
	CStackWatchList();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnScrollEvent)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnGetFocus)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG(OnCmdVSlide)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventShowEBP)
	DECLARE_WISP_MSG_EVENT(OnEventShowESP)
	DECLARE_WISP_MSG_EVENT(OnEventShowCode)
	DECLARE_WISP_MSG_EVENT(OnEventShowData)
	DECLARE_WISP_MSG_EVENT(OnEventAddressModeHex)
	DECLARE_WISP_MSG_EVENT(OnEventOffsetModeHex)
	DECLARE_WISP_MSG_EVENT(OnEventRelativeToESP)
	DECLARE_WISP_MSG_EVENT(OnEventRelativeToEBP)
	DECLARE_WISP_MSG_EVENT(OnEventToggleAddressOrder)
	DECLARE_WISP_MSG_EVENT(OnShowCodeByAddress)
	DECLARE_WISP_MSG_EVENT(OnShowDataByAddress)

public:
	void	ItemClickNotify(HANDLE hItem,int Col);
	void	GetAddressString(ULPOS Address,WISP_PSTR szBuffer);
	void	UpdateContext(ULPOS Address,bool bRelocal=false);
	void	ResetContext();
	
	bool	GetValueSym(ULPOS Address,VALUE_TYPE Value,WISP_COLOR_CHAR* szBuffer,int ccLen,COMMENT_TYPE* CommentType);
	void	GetSEHSym(ULPOS Address,VALUE_TYPE Value,WISP_COLOR_CHAR* szColorBuffer,int ccLen);
	bool	BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool	EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	void	PopupMenu(IN WISP_MSG* pMsg);
	void	AttachShortcutKey();
	DWORD	FindShortcutKey(DWORD CmdID);
	void	InitSEHMap();
	int		m_ScrollSpace;
	ULPOS	m_CurAddr;
	HANDLE	m_hMenuShowCode;
	HANDLE	m_hMenuShowData;
	HANDLE	m_hAddrLowToHigh;
	CWispMenu m_PopupMenu;
	STACK_WATCH_ADDR_MOD	m_AddrShowMode;
	ULPOS		m_BaseActiveAddress;
	WISP_POINT m_RightMenuPoint;
	/*******************************************************************************************/
	/* m_AddrLowToHigh = true 地址的显示从低地址到高地址                                       */
	/*******************************************************************************************/
	bool	m_AddrLowToHigh;   
	STACKHOTKEYMAP m_HotKeyMap;
	SEH_MAP m_SehMap;
	SEH_MAP m_RSehMap;
};

#endif
