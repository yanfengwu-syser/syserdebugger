#ifndef _SOURCEDEBUGSTARTPAGE_H_
#define _SOURCEDEBUGSTARTPAGE_H_

class CSourceDebugStartPageWnd:public CWispWnd
{
	enum CSOURCEDEBUGSTARTWND_CHILD_WND_ID
	{
		SYMBOLMODULE_CHILD_WND_ID =WISP_WM_USER_START,
	};
public:
	CSourceDebugStartPageWnd(void);
	~CSourceDebugStartPageWnd(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnRecalcLayout)
	DECLARE_WISP_MSG_CMD_MAP	
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD(OnSelectSymbolModule)
	CWispList m_SymbolModuleList;
	void InsertSymbolModule(char*ModuleName,void*pData);
	bool RemoveSymbolModule(void*pData);
};
#endif //_SOURCEDEBUGSTARTPAGE_H_