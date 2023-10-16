#ifndef _VIDEO_MODE_FORM_H_
#define _VIDEO_MODE_FORM_H_

class CVideoModeForm : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnOK);
	CVideoModeForm(){m_pFormRes = m_FormRes;m_VideoModeType = -1;}
	CWispRadioBox*	m_pAutoBT;
	CWispRadioBox*	m_pUserBT;
	CWispRadioBox*	m_pKernelBT;
	int				m_VideoModeType;
	int				m_OldVideoModeType;
};


#endif
