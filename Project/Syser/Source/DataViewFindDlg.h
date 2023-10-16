#ifndef _DATAVIEWFINDDLG_H_
#define _DATAVIEWFINDDLG_H_
typedef struct _FINDDATATYPE
{
	WCHAR* TypeName;
	DWORD	TypeID;
}FINDDATATYPE;
class CDataViewFindDlg:public CWispForm
{
public:
	CDataViewFindDlg();
	~CDataViewFindDlg();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnTypeListCmd)
	DECLARE_WISP_MSG_EVENT(OnOKButtonEvent)
	DECLARE_WISP_MSG_EVENT(OnCancelButtonEvent)
	DECLARE_WISP_MSG_EVENT(OnInRangeRadioBoxEvent)
	DECLARE_WISP_MSG_EVENT(OnInModuleRadioBoxEvent)
	bool CreateForm(CWispBaseWnd* pParentWnd,UINT ShowMode,UINT BeginAddr);
public:	
	CWispComboBox* m_TypeComboBox;
	CWispButton*   m_OKButton;
	CWispButton*   m_CancelButton;
	CWispRadioBox* m_AsciiRadioBox;
	CWispRadioBox* m_UnicodeRadioBox;
	CWispRadioBox* m_EitherRadioBox;
	CWispRadioBox* m_InModuleRadioBox;
	CWispRadioBox* m_InRangeRadioBox;
	CWispRadioBox* m_DownRadioBox;
	CWispRadioBox* m_UpRadioBox;
	CWispCheckBox* m_AllInstanceCheckBox;
	CWispCheckBox* m_CaseCheckBox;
	CWispEdit* m_BeginAddressEdit;
	CWispEdit* m_EndAddressEdit;
	CWispEdit* m_HexEdit;
	CWispEdit* m_ValueEdit;
	static FINDDATATYPE m_FindDataType[12];
	DWORD		m_BeginAddress;
};
#endif //_DATAVIEWFINDDLG_H_