#ifndef _ADDTYPEVIEWERDLG_H_
#define _ADDTYPEVIEWERDLG_H_
class CAddTypeViewerDlg:public CWispForm
{
public:
	CAddTypeViewerDlg();
	~CAddTypeViewerDlg();
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
	DECLARE_WISP_MSG_EVENT(OnLockRadioBoxEvent)
	DECLARE_WISP_MSG_EVENT(OnFloatRadioBoxEvent)
	bool CreateForm(CWispBaseWnd* pParentWnd,UINT ShowMode,UINT BeginAddr);
public:	
	void InitTypeList();
	CSDSModule* m_CurrentSymbol;
	CWispStaticStr* m_DesciptionStr;
	CWispStaticStr* m_BeginAddressStr;
	CWispList*		m_TypeList;
	CWispButton*   m_OKButton;
	CWispButton*   m_CancelButton;
	CWispRadioBox* m_FloatRadioBox;
	CWispRadioBox* m_LockRadioBox;
	CWispRadioBox* m_DecimalRadioBox;
	CWispRadioBox* m_HexRadioBox;
	CWispStaticStr* m_ValueStr;
	CWispEdit* m_BeginAddressEdit;
	CWispDIBList m_IconDIBList;
	DWORD		m_BeginAddress;
};
#endif //_ADDTYPEVIEWERDLG_H_