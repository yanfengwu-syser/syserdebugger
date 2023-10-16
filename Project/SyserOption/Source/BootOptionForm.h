#ifndef _BOOT_OPTION_FORM_H_
#define _BOOT_OPTION_FORM_H_

class CBootOptionForm : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnOK);
	CBootOptionForm(){m_pFormRes = m_FormRes;m_BootType = -1;}
	CWispRadioBox*	m_pSystemBT;
	CWispRadioBox*	m_pAutoBT;
	CWispRadioBox*	m_pManualBT;
	int				m_BootType;
	int				m_OldBootType;
};


#endif
