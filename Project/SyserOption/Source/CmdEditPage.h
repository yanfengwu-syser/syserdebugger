#ifndef _CMD_EDIT_PAGE_H_
#define _CMD_EDIT_PAGE_H_

class CCmdEditPage : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	CCmdEditPage(){m_pFormRes = m_FormRes;}
};


#endif
