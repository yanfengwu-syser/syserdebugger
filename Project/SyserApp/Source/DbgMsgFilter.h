#ifndef _DBG_MSG_FILTER_H_
#define _DBG_MSG_FILTER_H_

class CDbgMsgFilterForm : public CWispForm
{
public:
	CDbgMsgFilterForm();
	~CDbgMsgFilterForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnReset)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnOK)
	CWispBaseWnd*m_pContainWnd;
	CWispBaseWnd*m_pNotContainWnd;
	char	m_szContain[256];
	char	m_szNotContain[256];
};

#endif
