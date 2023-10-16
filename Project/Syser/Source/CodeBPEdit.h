#ifndef _CODE_BP_EDIT_H_
#define _CODE_BP_EDIT_H_

class CCodeBPEdit : public CWispForm
{
public:
	CCodeBPEdit(void);
	~CCodeBPEdit(void);
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnAddressChg);
	DECLARE_WISP_MSG_CMD(OnOK)
	BREAK_POINT*m_pBP;
	MODULE_BP*	m_pModuleBP;
	CWispEdit*	m_pNameEdit;
	CWispEdit*	m_pAddrEdit;
	CWispEdit*	m_pConditionEdit;
	CWispEdit*	m_pDoCmdEdit;
	CWispCheckBox*m_pEnableChkBox;
	bool		m_bEnable;
};


#endif

