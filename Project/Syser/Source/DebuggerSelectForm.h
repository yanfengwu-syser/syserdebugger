#ifndef _DEBUGGER_SELECT_FORM_H_
#define _DEBUGGER_SELECT_FORM_H_

class CDebuggerSelectForm : public CWispForm
{
public:
	CDebuggerSelectForm();
	~CDebuggerSelectForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	void	Popup();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnPlugin)
	DECLARE_WISP_MSG_EVENT(OnRefresh)
public:
	CWispList*m_pDebuggerList;
};



#endif
