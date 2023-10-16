#ifndef _SEARCH_DIALOG_H_
#define _SEARCH_DIALOG_H_

enum
{
	FIND_DATA_TYPE_TEXT_ANSI = 0,
	FIND_DATA_TYPE_TEXT_UNI,
	FIND_DATA_TYPE_BYTES,
	FIND_DATA_TYPE_WORD,
	FIND_DATA_TYPE_DWORD,
	FIND_DATA_TYPE_QWORD,
	MAX_FIND_DATA_TYPE
};

#define MAX_SEARCH_DATA_LENGTH		64

class CSearchDialog : public CWispForm
{
public:
	CSearchDialog();
	~CSearchDialog();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnTypeComboxCmd)
	DECLARE_WISP_MSG_EVENT(OnButtonSelectModule)
	DECLARE_WISP_MSG_EVENT(OnButtonFind)
	DECLARE_WISP_MSG_EVENT(OnButtonFindNext)
	void	Popup();
public:	
	CWispComboBox*	m_TypeComboBox;
	CWispEdit*		m_BeginAddressEdit;
	CWispEdit*		m_EndAddressEdit;
	CWispEdit*		m_ValueEdit;
	CWispCheckBox*	m_pCaseCheckBox;
	ULPOS			m_BeginAddress;
	ULPOS			m_EndAddress;
	ULPOS			m_CurPos;
	bool			m_bCase;
	BYTE			m_FindData[MAX_SEARCH_DATA_LENGTH];
	int				m_FindDataLength;
	static PCWSTR	m_FindDataType[];
};
#endif //_DATAVIEWFINDDLG_H_