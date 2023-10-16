#ifndef _THREAD_LIST_WND_
#define _THREAD_LIST_WND_

class CThreadListWnd:public CWispList
{
	typedef TMap<UINT,UINT> THREADHOTKEYMAP;
	enum{
		TL_THREAD_ID,
		TL_PROCESS_ID,
		//TL_INITIALSTACK,
		TL_KERNELSTACK,
		//TL_STACKLIMIT,
		TL_SERVICETABLE,
		TL_STARTADDRESS,
		TL_TRAPFRAME,
		TL_ESP,
		TL_EIP,
		TL_PROCESS_NAME,
		TL_SUSPEND
	};
public:
	CThreadListWnd();
	~CThreadListWnd();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnDestroy)	
	DECLARE_WISP_MSG_EVENT_MAP

	DECLARE_WISP_MSG_EVENT(OnEventGotoThreadStruct)
	DECLARE_WISP_MSG_EVENT(OnEventGotoProcessStruct)
	DECLARE_WISP_MSG_EVENT(OnEventGotoStartAddress)
	DECLARE_WISP_MSG_EVENT(OnEventGotoThreadEIP)
	DECLARE_WISP_MSG_EVENT(OnEventSetBreakpointAtThread)		
	DECLARE_WISP_MSG_EVENT(OnEventSetBreakpointAtProcess)		

	CWispMenu m_PopupMenu;  
	void	UpdateContext();
	void	AttachShortcutKey();
	THREADHOTKEYMAP m_HotKeyMap;
};
#endif //_MODULE_LIST_WND_