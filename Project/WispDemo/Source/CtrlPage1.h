#ifndef _CTRL_PAGE1_H_
#define _CTRL_PAGE1_H_


class CCtrlPage1 : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	CCtrlPage1(){m_pFormRes = m_FormRes;}
};

#endif
