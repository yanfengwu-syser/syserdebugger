#ifndef _DATA_VIEW_FORM_H_
#define _DATA_VIEW_FORM_H_

#include "DataView.h"

class CDataViewForm : public CWispForm
{
public:
	CDataViewForm();
	~CDataViewForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnSize);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnCmdAddressEdit)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnGoto)
	void		Popup();
	void		UpdateContext();
	CDataView	m_DataView;
	CWispEdit*	m_pAddrEdit;
	CWispButton*m_pButton;
	CWispStaticGroup*m_pGroupCtrl;
};


#endif
