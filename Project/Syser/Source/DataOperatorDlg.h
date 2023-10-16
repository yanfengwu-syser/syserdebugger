#ifndef _DATAOPERATOR_H_
#define _DATAOPERATOR_H_
class CDataOperatorDlg;
typedef  void (CDataOperatorDlg::*FPDATAOPERATION)(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);

class CDataOperatorDlg:public CWispForm
{

public:
	CDataOperatorDlg();
	~CDataOperatorDlg();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnLineTextCmd)
	DECLARE_WISP_MSG_CMD(OnValueEditCmd)
	DECLARE_WISP_MSG_EVENT(OnOKButtonEvent)
	DECLARE_WISP_MSG_EVENT(OnCancelButtonEvent)
	DECLARE_WISP_MSG_EVENT(OnCountCheckBoxCmd)
	bool CreateForm(CWispBaseWnd* pParentWnd,UINT ShowMode,UINT BeginAddr,UINT EndAddr,UINT DataWidth,DWORD OperationType=0);
public:
	CWispStaticStr* m_DesciptionStr;
	CWispButton*   m_OKButton;
	CWispButton*   m_CancelButton;
	CWispRadioBox* m_BYTERadioBox;
	CWispRadioBox* m_WORDRadioBox;
	CWispRadioBox* m_DWORDRadioBox;
	CWispRadioBox* m_QWORDRadioBox;
	CWispRadioBox* m_DecimalRadioBox;
	CWispRadioBox* m_HexRadioBox;
	CWispCheckBox* m_CountCheckBox;
	CWispStaticStr* m_ValueStr;
	CWispEdit* m_BeginAddressEdit;
	CWispEdit* m_EndAddressEdit;
	CWispEdit* m_ValueEdit;
	DWORD m_BeginAddr;
	DWORD m_EndAddr;
	DWORD m_DataWidth;
	DWORD m_OperationType;
	static const WCHAR* DataOperatorDescription[20];
	static const WCHAR* DataOperatorTitle[20];
	static FPDATAOPERATION m_Func[20];
	void ByteFlip(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void InverseBits(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void ShiftLeft(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void ShiftRight(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void RotateLeft(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void RotateRight(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void BlockShiftLeft(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void BlockShiftRight(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void XOR(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void OR(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void AND(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void ChangeSign(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void Add(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void Subtract(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void Multiply(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void Divide(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void Mod(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void UpperCase(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void LowerCase(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	void InverseCase(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam);
	DWORD GetDataWidth();
	typedef union _DATAVALUE
	{
		ULONGLONG ullValue;
		DWORD DwordValue;
		WORD WordValue;
		BYTE ByteValue;
		BYTE ByteArray[8];
	}DATAVALUE;
	typedef union _DATAVALUEPOINTER
	{
		ULONGLONG* ullPtr;
		DWORD *dwPtr;
		WORD *wdPtr;
		BYTE *ptr;
		DWORD Address;
	}DATAVALUEPOINTER;
};

#endif //_DATAOPERATOR_H_