#ifndef _REGISTER_FORM_H_
#define _REGISTER_FORM_H_

class CRegisterForm : public CWispForm
{
public:
	CRegisterForm();
	~CRegisterForm();
	CWispString		m_StrName;
	CWispString		m_StrSN;
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnOK)
};


#endif
