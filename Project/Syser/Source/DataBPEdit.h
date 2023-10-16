#ifndef _DATA_BP_EDIT_H_
#define _DATA_BP_EDIT_H_

class CDataBPEdit : public CWispForm
{
public:
	CDataBPEdit(void);
	~CDataBPEdit(void);
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnAddressChg);
	DECLARE_WISP_MSG_CMD(OnOK)
	BREAK_POINT*m_pBP;
	CWispEdit*	m_pNameEdit;
	CWispEdit*	m_pAddrEdit;
	CWispEdit*	m_pConditionEdit;
	CWispEdit*	m_pDoCmdEdit;
	CWispCheckBox*m_pEnableChkBox;
	CWispRadioBox*m_pWriteRadioBox;
	CWispRadioBox*m_pReadWriteRadioBox;
	CWispRadioBox*m_pExecuteRadioBox;
	CWispRadioBox*m_pIORadioBox;
	CWispCheckBox*m_pAllChkBox;
	CWispCheckBox*m_pByteChkBox;
	CWispCheckBox*m_pWordChkBox;
	CWispCheckBox*m_pDwordChkBox;
	bool		m_bEnable;
	UINT		m_Type;
};


#endif

