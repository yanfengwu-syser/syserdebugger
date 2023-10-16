#include "stdafx.h"
#include "DataOperatorDlg.h"
#include "Syser.h"

const WCHAR* CDataOperatorDlg::DataOperatorDescription[20]={
	WSTR("Fips the byte order of you data. For example, the \nword 0xABCD would become 0xCDAB."),
	WSTR("Inverts the bits of your data. For example, the \nvalue 0x35 (00110101 in binary) would become 0xCA\n(11001010 in binary)."),
	WSTR("Shift the bits of your data to the left. For \nexample,the value 0x08 (00001000 in binary) would \nbecome 0x10 (00010000 in binary)."),
	WSTR("Shift the bits of your data to the right. For \nexample,the value 0x08(00001000 in binary) would \nbecome 0x04 (00000100 in binary)."),
	WSTR("Rotates the bits of your data to the left. For\nexample,the value 0x98 (10011000 in binary) would \nbecome 0x31 (00110001 in binary)."),
	WSTR("Rotates the bits of your data to the right. For\nexampel,the value 0x61 (01100001 in binary) would \nbecome 0xB0 (10110000 in binary)."),
	WSTR("Shift the bits of your data to the left across byte\n boundaries. For example,the value 0x08(00001000 \nin binary) would become 0x10 (00010000 in binary)."),
	WSTR("Shift the bits of your data to right across byte\nboundaries. For example,the value 0x08 (00001000 in\nbinary) would become 0x04 (00000100 in binary)."),
	WSTR("Performs a XOR operation. For example,the value\n0xFO (11110000 in binary) XOR 0xAA (10101010 in \nbinary) is 0x5A (01011010 in binary)."),
	WSTR("Performs an OR operation. For example,the value\n0xF0 (11110000 in binary) OR 0xAA (10101010 in \nbinary) is 0xFA (11111010 in binary)."),
	WSTR("Performs an AND operation. For example,the value\n0xF0 (11110000 in binary) AND 0xAA (10101010 in \nbinary) is 0xA0 (10100000 in binary)."),
	WSTR("Change the sign of your data. For example,a value of\n5 would become -5 or a value of -5 would become 5."),
	WSTR("Replaces your data with your data plus another value\n(data = data + value)."),
	WSTR("Replaces your data with your data minus another\nvalue (data = data - value)."),
	WSTR("Replaces your data with your data multiplied by \nanother value (data = data * value)."),
	WSTR("Replaces your data with your data divided by another\nvalue (data = data / value)."),
	WSTR("Replaces your data with your data mod another value\n(data = data % value)."),
	WSTR("Replaces your character data with all upper case\ncharacters. For example,the text \"Test String\"\nwould become \"TEST STRING\"."),
	WSTR("Replaces your character data with all lower case\ncharacters. For example,the text \"Test String\"\nwould become \"test string\"."),
	WSTR("Replaces your character data with the inverse \ncharacter case. For example, the next \"Test String\" would\nbecome \"tEST sTRING\"."),
};
const WCHAR* CDataOperatorDlg::DataOperatorTitle[20]={
	WSTR("ByteFlip Operation"),
	WSTR("Inverse Bits Operation"),
	WSTR("Shift Left Operation"),
	WSTR("Shift Right Operation"),
	WSTR("Rotate Left Operation"),
	WSTR("Rotate Right Operation"),
	WSTR("Block Shift Left Operation"),
	WSTR("Block Shift Right Operation"),
	WSTR("XOR Operation"),
	WSTR("OR Operation"),
	WSTR("AND Operation"),
	WSTR("Change Sign Operation"),
	WSTR("Add Operation"),
	WSTR("Subtract Operation"),
	WSTR("Multiply Operation"),
	WSTR("Divide Operation"),
	WSTR("Mod Operation"),
	WSTR("Upper Case Operation"),
	WSTR("Lower Case Operation"),
	WSTR("Inverse Case Operation"),
};
FPDATAOPERATION CDataOperatorDlg::m_Func[20]=
{
&CDataOperatorDlg::ByteFlip,
&CDataOperatorDlg::InverseBits,
&CDataOperatorDlg::ShiftLeft,
&CDataOperatorDlg::ShiftRight,
&CDataOperatorDlg::RotateLeft,
&CDataOperatorDlg::RotateRight,
&CDataOperatorDlg::BlockShiftLeft,
&CDataOperatorDlg::BlockShiftRight,
&CDataOperatorDlg::XOR,
&CDataOperatorDlg::AND,
&CDataOperatorDlg::OR,
&CDataOperatorDlg::ChangeSign,
&CDataOperatorDlg::Add,
&CDataOperatorDlg::Subtract,
&CDataOperatorDlg::Multiply,
&CDataOperatorDlg::Divide,
&CDataOperatorDlg::Mod,
&CDataOperatorDlg::UpperCase,
&CDataOperatorDlg::LowerCase,
&CDataOperatorDlg::InverseCase,
};
enum CDataOperatorDlg::WISP_FORM_ID
{
	CMD_ID_BUTTON_OK=WISP_ID_USER_START,
	CMD_ID_BUTTON_CANCEL,
	CMD_ID_RADIOBOX_BYTE,
	CMD_ID_RADIOBOX_WORD,
	CMD_ID_RADIOBOX_DWORD,
	CMD_ID_RADIOBOX_QWORD,
	CMD_ID_STATICSTR_DESCRIPTION,
	CMD_ID_RADIOBOX_HEX,
	CMD_ID_RADIOBOX_DECIMAL,
	CMD_ID_STATICSTR_VALUE,
	CMD_ID_STATICSTR_ENDADDRESS,
	CMD_ID_EDIT_BEGIN_ADDRESS,
	CMD_ID_EDIT_END_ADDRESS,
	CMD_ID_EDIT_VALUE,
	CMD_ID_CHECKBOX_COUNT,
};

WISP_FORM_RES_ITEM CDataOperatorDlg::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,340,240},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Data Operation"),
		"\\SyserIcon\\Plugin.ico",
		NULL,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{11,6,313,53},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Description")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{11,64,313,80},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Data Width")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{11,151,234,55},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Length")
	},
	{
		WISP_CTRL_RADIO_BOX,
		{25,76,96,16},
		CMD_ID_RADIOBOX_BYTE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("BYTE (Bit 8)"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{180,76,110,16},
		CMD_ID_RADIOBOX_WORD,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("WORD (Bit 16)"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{25,96,110,16},
		CMD_ID_RADIOBOX_DWORD,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("DWORD (Bit 32)"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{180,96,110,16},
		CMD_ID_RADIOBOX_QWORD,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("QWORD (Bit 64)"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_STRING,
		{14,20,310,50},
		CMD_ID_STATICSTR_DESCRIPTION,
		WISP_WS_NULL,
		WSTR(""),
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{25,120,40,16},
		CMD_ID_STATICSTR_VALUE,
		WISP_WS_NULL,
		WSTR("Value:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{65,120,105,16},
		CMD_ID_EDIT_VALUE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_RADIO_BOX,
		{180,119,65,16},
		CMD_ID_RADIOBOX_DECIMAL,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Decimal"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{250,119,110,16},
		CMD_ID_RADIOBOX_HEX,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Hex"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_STRING,
		{16,167,90,16},
		CMD_ID_STATICSTR_ENDADDRESS,
		WISP_WS_NULL,
		WSTR("Begin Address:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{105,166,80,16},
		CMD_ID_EDIT_BEGIN_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{16,185,90,16},
		CMD_ID_STATICSTR_ENDADDRESS,
		WISP_WS_NULL,
		WSTR("  End Address:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{105,185,80,16},
		CMD_ID_EDIT_END_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_CHECK_BOX,
		{190,184,60,16},
		CMD_ID_CHECKBOX_COUNT,
		WISP_CBS_NORMAL,
		WSTR("Count"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{255,155,68,20},
		CMD_ID_BUTTON_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
	},
	{
		WISP_CTRL_BUTTON,
		{255,185,68,20},
		CMD_ID_BUTTON_CANCEL,
		WISP_BS_NORMAL,
		WSTR("Cancel"),
	},
	{WISP_CTRL_NULL}
};
WISP_MSG_MAP_BEGIN(CDataOperatorDlg)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CDataOperatorDlg)
//WISP_MSG_CMD_MAP(CMD_ID_EDIT_LINE,OnLineTextCmd)
WISP_MSG_CMD_MAP(CMD_ID_CHECKBOX_COUNT,OnCountCheckBoxCmd)
WISP_MSG_CMD_MAP(CMD_ID_EDIT_VALUE,OnValueEditCmd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CDataOperatorDlg)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_OK,OnOKButtonEvent)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_CANCEL,OnCancelButtonEvent)
WISP_MSG_EVENT_MAP_END
CDataOperatorDlg::CDataOperatorDlg()
{
	m_pFormRes = m_FormRes;
}
CDataOperatorDlg::~CDataOperatorDlg()
{
}
bool CDataOperatorDlg::CreateForm(CWispBaseWnd* pParentWnd,UINT ShowMode,UINT BeginAddr,UINT EndAddr,UINT DataWidth,DWORD OperationType)
{
	m_BeginAddr=BeginAddr;
	m_EndAddr=EndAddr;
	m_DataWidth=DataWidth;
	m_OperationType=OperationType-DATAOPERATOR_ID_BYTEFLIP;
	return CWispForm::CreateForm(pParentWnd,ShowMode);
}
bool CDataOperatorDlg::OnFormCreate(IN WISP_MSG* pMsg)
{
	WCHAR Buffer[20];
	DWORD CmdID;
	m_OKButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_OK);
	m_CancelButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_CANCEL);
	m_BYTERadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_BYTE);
	m_WORDRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_WORD);
	m_DWORDRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_DWORD);
	m_QWORDRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_QWORD);
	m_DesciptionStr=(CWispStaticStr*)GetFormItem(CMD_ID_STATICSTR_DESCRIPTION);
	m_DecimalRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_DECIMAL);
	m_HexRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_HEX);
	m_CountCheckBox=(CWispCheckBox*)GetFormItem(CMD_ID_CHECKBOX_COUNT);
	m_ValueStr=(CWispStaticStr*)GetFormItem(CMD_ID_STATICSTR_VALUE);
	m_BeginAddressEdit=(CWispEdit*)GetFormItem(CMD_ID_EDIT_BEGIN_ADDRESS);
	m_EndAddressEdit=(CWispEdit*)GetFormItem(CMD_ID_EDIT_END_ADDRESS);
	m_ValueEdit=(CWispEdit*)GetFormItem(CMD_ID_EDIT_VALUE);
	TSPrintf(Buffer,WSTR("%x"),m_BeginAddr);
	m_BeginAddressEdit->SetWindowText(Buffer);
	TSPrintf(Buffer,WSTR("%x"),m_EndAddr);
	m_EndAddressEdit->SetWindowText(Buffer);
	if(m_DataWidth==1)
		m_BYTERadioBox->Check();
	if(m_DataWidth==2)
		m_WORDRadioBox->Check();
	if(m_DataWidth==4)
		m_DWORDRadioBox->Check();
	m_DesciptionStr->SetWindowText(DataOperatorDescription[m_OperationType]);
	SetWindowText(DataOperatorTitle[m_OperationType]);
	CmdID = m_OperationType + DATAOPERATOR_ID_BYTEFLIP;
	m_HexRadioBox->Check();
	if(CmdID==DATAOPERATOR_ID_BYTEFLIP ||
		CmdID==DATAOPERATOR_ID_INVERSEBITS ||
		CmdID==DATAOPERATOR_ID_CHANGESIGN ||
		CmdID==DATAOPERATOR_ID_UPPERCASE ||
		CmdID==DATAOPERATOR_ID_LOWERCASE ||
		CmdID==DATAOPERATOR_ID_INVERSECASE
		)
	{
		m_ValueEdit->EnableWindow(false);
		m_DecimalRadioBox->EnableWindow(false);
		m_HexRadioBox->EnableWindow(false);
	}
	else
	{
		m_OKButton->EnableWindow(false);
	}
	return true;
}
bool CDataOperatorDlg::OnDestroy(IN WISP_MSG* pMsg)
{
	return true;
}
DWORD CDataOperatorDlg::GetDataWidth()
{
	if(m_WORDRadioBox->IsChecked())
		return 2;
	if(m_DWORDRadioBox->IsChecked())
		return 4;
	if(m_QWORDRadioBox->IsChecked())
		return 8;
	return 1;
}
bool CDataOperatorDlg::OnOKButtonEvent(IN WISP_MSG* pMsg)
{
	WCHAR* Buffer;
	DWORD BeginAddress,EndAddress,DataWidth;
	ULONGLONG Param1=0;
	Buffer = m_BeginAddressEdit->GetWindowText();
	if(SHexStrToNum(Buffer,&BeginAddress)==false)
	{
		BeginAddress = m_BeginAddr;
	}
	Buffer = m_EndAddressEdit->GetWindowText();
	DataWidth =GetDataWidth();
	if(SHexStrToNum(Buffer,&EndAddress)==false)
	{
		EndAddress=m_EndAddr;
	}
	if(m_ValueEdit->GetWindowText().IsEmpty()==false)
	{
		Buffer=m_ValueEdit->GetWindowText();
		if(m_HexRadioBox->IsChecked())
		{
			if(SHexStrToNum(Buffer,&Param1)==false)
				Param1=0;
		}
		else
		{
			if(SDecStrToNum(Buffer,&Param1)==false)
				Param1=0;
		}
	}
	(this->*m_Func[m_OperationType])(*(void**)&BeginAddress,*(void**)&EndAddress,DataWidth,*(void**)&Param1);
	//UPDATE_MEMORY_VIEW();
	UPDATE_CONTEXT();
	PostCloseMsg();
	return true;
}
bool CDataOperatorDlg::OnCancelButtonEvent(IN WISP_MSG* pMsg)
{
	PostCloseMsg();
	return true;
}
bool CDataOperatorDlg::OnCountCheckBoxCmd(IN WISP_MSG* pMsg)
{
	return true;
}
bool CDataOperatorDlg::OnValueEditCmd(IN WISP_MSG* pMsg)
{
	WCHAR* Buffer;
	DWORD Value;
	bool bOk;
	switch(pMsg->Command.CmdMsg) {
	case WISP_CMD_EN_INPUT_KEY_DOWN:
		if((pMsg->Command.Param1>='g' && pMsg->Command.Param1 <= 'z')||
			(pMsg->Command.Param1>='G' && pMsg->Command.Param1 <= 'Z'))
			return false;
		if(m_HexRadioBox->IsChecked()==false)
		{
			if((pMsg->Command.Param1>='a' && pMsg->Command.Param1 <= 'f')||
				(pMsg->Command.Param1>='A' && pMsg->Command.Param1 <= 'F'))
				return false;
		}
		break;
	case WISP_CMD_EN_CHANGED:
		Buffer = m_ValueEdit->GetWindowText();
		if(m_HexRadioBox->IsChecked())
			bOk = SHexStrToNum(Buffer,&Value);
		else
			bOk = SDecStrToNum(Buffer,&Value);
		m_OKButton->EnableWindow(bOk);
		break;
	}
	return true;
}

void CDataOperatorDlg::ByteFlip(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i,j,k;
	if(DataWidth==1||Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	j = DataWidth-1;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth); 
		if(Length!=DataWidth)
			return;
		for(k = 0; k <= j; k++)
			SecondValue.ByteArray[k]=FirstValue.ByteArray[j-k];
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&SecondValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::InverseBits(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = *(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1;
	DATAVALUE FirstValue;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,1); 
		if(Length!=1)
			return;
		FirstValue.ByteValue^=0xff;
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,1)!=1)
			return;
		DataPtr.Address+=1;
	}
}
void CDataOperatorDlg::ShiftLeft(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DWORD ShiftCount = *(DWORD*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue<<=ShiftCount;
			break;
		case 2:
			FirstValue.WordValue<<=ShiftCount;
			break;
		case 4:
			FirstValue.DwordValue<<=ShiftCount;
			break;
		case 8:
			FirstValue.ullValue<<=ShiftCount;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::ShiftRight(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DWORD ShiftCount = *(DWORD*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue>>=ShiftCount;
			break;
		case 2:
			FirstValue.WordValue>>=ShiftCount;
			break;
		case 4:
			FirstValue.DwordValue>>=ShiftCount;
			break;
		case 8:
			FirstValue.ullValue>>=ShiftCount;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::RotateLeft(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue;
	DWORD ShiftCount = *(DWORD*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD BitSize;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	BitSize = 8 * DataWidth;
	ShiftCount %= BitSize;
	if(ShiftCount==0)
		return;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		SecondValue=FirstValue;
		switch(DataWidth) {
		case 1:
			SecondValue.ByteValue>>=(BitSize-ShiftCount);
			FirstValue.ByteValue<<=ShiftCount;
			FirstValue.ByteValue|=SecondValue.ByteValue;
			break;
		case 2:
			SecondValue.WordValue>>=(BitSize-ShiftCount);
			FirstValue.WordValue<<=ShiftCount;
			FirstValue.WordValue|=SecondValue.WordValue;
			break;
		case 4:
			SecondValue.DwordValue>>=(BitSize-ShiftCount);
			FirstValue.DwordValue<<=ShiftCount;
			FirstValue.DwordValue|=SecondValue.DwordValue;
			break;
		case 8:
			SecondValue.ullValue>>=(BitSize-ShiftCount);
			FirstValue.ullValue<<=ShiftCount;
			FirstValue.ullValue|=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::RotateRight(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue;
	DWORD ShiftCount = *(DWORD*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD BitSize;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	BitSize = 8 * DataWidth;
	ShiftCount %= BitSize;
	if(ShiftCount==0)
		return;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		SecondValue=FirstValue;
		switch(DataWidth) {
		case 1:
			SecondValue.ByteValue<<=(BitSize-ShiftCount);
			FirstValue.ByteValue>>=ShiftCount;
			FirstValue.ByteValue|=SecondValue.ByteValue;
			break;
		case 2:
			SecondValue.WordValue<<=(BitSize-ShiftCount);
			FirstValue.WordValue>>=ShiftCount;
			FirstValue.WordValue|=SecondValue.WordValue;
			break;
		case 4:
			SecondValue.DwordValue<<=(BitSize-ShiftCount);
			FirstValue.DwordValue>>=ShiftCount;
			FirstValue.DwordValue|=SecondValue.DwordValue;
			break;
		case 8:
			SecondValue.ullValue<<=(BitSize-ShiftCount);
			FirstValue.ullValue>>=ShiftCount;
			FirstValue.ullValue|=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::BlockShiftLeft(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = *(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1;
	DATAVALUE FirstValue;
	DWORD ShiftCount = *(DWORD*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;DataWidth=1;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		FirstValue.ByteValue<<=ShiftCount;
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::BlockShiftRight(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = *(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1;
	DATAVALUE FirstValue;
	DWORD ShiftCount = *(DWORD*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;DataWidth=1;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		FirstValue.ByteValue>>=ShiftCount;
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::XOR(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue^=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue^=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue^=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue^=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::OR(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue|=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue|=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue|=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue|=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::AND(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue&=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue&=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue&=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue&=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::ChangeSign(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue=0-FirstValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue=0-FirstValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue=0-FirstValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue=0-FirstValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::Add(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue+=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue+=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue+=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue+=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}

}
void CDataOperatorDlg::Subtract(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue-=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue-=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue-=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue-=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::Multiply(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue*=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue*=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue*=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue*=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::Divide(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	if(SecondValue.ullValue==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue/=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue/=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue/=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue/=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::Mod(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = (*(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1)/DataWidth;
	DATAVALUE FirstValue;
	DATAVALUE SecondValue=*(DATAVALUE*)&OwnerParam;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	if(SecondValue.ullValue==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		switch(DataWidth) {
		case 1:
			FirstValue.ByteValue%=SecondValue.ByteValue;
			break;
		case 2:
			FirstValue.WordValue%=SecondValue.WordValue;
			break;
		case 4:
			FirstValue.DwordValue%=SecondValue.DwordValue;
			break;
		case 8:
			FirstValue.ullValue%=SecondValue.ullValue;
			break;
		}
		if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
			return;
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::UpperCase(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = *(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1;
	DATAVALUE FirstValue;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;DataWidth=1;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		if(FirstValue.ByteValue >= 'a' && FirstValue.ByteValue <= 'z')
		{
			FirstValue.ByteValue -= ('a' - 'A');
			if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
				return;
		}
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::LowerCase(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = *(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1;
	DATAVALUE FirstValue;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;DataWidth=1;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		if(FirstValue.ByteValue >= 'A' && FirstValue.ByteValue <= 'Z')
		{
			FirstValue.ByteValue += ('a' - 'A');
			if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
				return;
		}
		DataPtr.Address+=DataWidth;
	}
}
void CDataOperatorDlg::InverseCase(void* BeginAddr,void* EndAddr,DWORD DataWidth,void* OwnerParam)
{
	DWORD Count = *(DWORD*)&EndAddr - *(DWORD*)&BeginAddr+1;
	DATAVALUE FirstValue;
	DATAVALUEPOINTER DataPtr;
	DWORD Length;
	DWORD i;
	if(Count==0)
		return;
	DataPtr.ptr =(BYTE*)BeginAddr;DataWidth=1;
	for(i = 0; i < Count; i++)
	{
		Length = gpSyser->m_pDebugger->ReadMemory(DataPtr.Address,&FirstValue,DataWidth);
		if(Length!=DataWidth)
			return;
		if((FirstValue.ByteValue >= 'A' && FirstValue.ByteValue <= 'Z') || (FirstValue.ByteValue >= 'a' && FirstValue.ByteValue <= 'z'))
		{
			FirstValue.ByteValue ^= ('a' - 'A');
			if(gpSyser->m_pDebugger->WriteMemory(DataPtr.Address,&FirstValue,DataWidth)!=DataWidth)
				return;
		}
		DataPtr.Address+=DataWidth;
	}
}
