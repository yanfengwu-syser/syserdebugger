#ifndef __SYSERABOUTFORM_H_
#define __SYSERABOUTFORM_H_

class CAboutForm : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	CAboutForm(){m_pFormRes = m_FormRes;}
};

#endif //__SYSERABOUTFORM_H_