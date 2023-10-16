#ifndef _CROSSREFERENCE_FORM_H_
#define _CROSSREFERENCE_FORM_H_
#include "CodeView.h"
class CCrossReferenceForm : public CWispForm
{
public:
	CCrossReferenceForm();
	~CCrossReferenceForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnOkButton)
	DECLARE_WISP_MSG_CMD_MAP 
	DECLARE_WISP_MSG_CMD(OnListCmd)
	//DECLARE_WISP_MSG_EVENT(OnRefresh)
public:
	CWispList* m_AddressReferenceList;
	bool InitReferenceList(CROSSREFERENCELIST* pList,DWORD Address);
	bool InitDataReferenceList(CROSSREFERENCELIST* pList,DWORD Address);
};



#endif
