#include "stdafx.h"
#include "DataViewFindDlg.h"
FINDDATATYPE CDataViewFindDlg::m_FindDataType[12]=
{
	{WSTR("Hex Values"),0},
	{WSTR("Text String"),1},
	{WSTR("8 Bit Signed Byte"),2},
	{WSTR("8 Bit Unsigned Byte"),3},
	{WSTR("16 Bit Signed Short"),4},
	{WSTR("16 Bit Unsigned Short"),5},
	{WSTR("32 Bit Signed Long"),6},
	{WSTR("32 Bit Unsigned Long"),7},
	{WSTR("64 Bit Signed Quad"),8},
	{WSTR("64 Bit Unsigned Quad"),9},
	{WSTR("32 Float"),10},
	{WSTR("64 Double"),11},
};
enum CDataViewFindDlg::WISP_FORM_ID
{
	CMD_ID_BUTTON_OK=WISP_ID_USER_START,
	CMD_ID_BUTTON_CANCEL,
	
	CMD_ID_STATICGROUP_FIND_WATH,
	CMD_ID_STATICSTR_TYPE,
	CMD_ID_COMBOBOX_TYPE,
	CMD_ID_STATICSTR_VALUE,
	CMD_ID_EDIT_VALUE,
	CMD_ID_STATICSTR_HEX,	
	CMD_ID_EDIT_HEX,

	CMD_ID_STATICGROUP_DIRECTORY,
	CMD_ID_RADIOBOX_DIRECTION_DOWN,
	CMD_ID_RADIOBOX_DIRECTION_UP,

	CMD_ID_STATICGROUP_OPTIONS,
	CMD_ID_CHECKBOX_ALL_INSTANCES,
	CMD_ID_CHECKBOX_CASE,
	CMD_ID_RADIOBOX_ASCII_STR,
	CMD_ID_RADIOBOX_UNICODE_STR,
	CMD_ID_RADIOBOX_EITHER,

	CMD_ID_STATICGROUP_RANGE,
	CMD_ID_RADIOBOX_IN_MODULE,
	CMD_ID_RADIOBOX_IN_RANGE,
	CMD_ID_STATICSTR_BEGIN_ADDRESS,
	CMD_ID_EDIT_BEGIN_ADDRESS,
	CMD_ID_STATICSTR_END_ADDRESS,
	CMD_ID_EDIT_END_ADDRESS,
};
WISP_FORM_RES_ITEM CDataViewFindDlg::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,391,315},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Find"),
		"\\SyserIcon\\Plugin.ico",
		NULL,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,364,80},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Find What")
	},
	{
		WISP_CTRL_STATIC_STRING,
		{23,26,45,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Type:"),
		NULL,
	},
	
	{
		WISP_CTRL_COMBO_BOX,
		{62,26,135,214},
		CMD_ID_COMBOBOX_TYPE,
		WISP_WS_NORMAL,
		NULL,
		NULL,
	},
	
	{
		WISP_CTRL_STATIC_STRING,
		{17,46,45,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Value:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{62,46,300,16},
		WISP_ID_NULL,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{29,66,45,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Hex:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{62,66,300,16},
		CMD_ID_EDIT_HEX,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,96,364,55},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Range")
	},
	
	{
		WISP_CTRL_RADIO_BOX,
		{16,107,90,16},
		CMD_ID_RADIOBOX_IN_MODULE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("In Module"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{16,125,90,16},
		CMD_ID_RADIOBOX_IN_RANGE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("In Range"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_STRING,
		{110,127,45,16},
		CMD_ID_STATICSTR_BEGIN_ADDRESS,
		WISP_WS_NULL,
		WSTR("Begin:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{160,125,80,16},
		CMD_ID_EDIT_BEGIN_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{250,127,45,16},
		CMD_ID_STATICSTR_END_ADDRESS,
		WISP_WS_NULL,
		WSTR("End:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{280,125,80,16},
		CMD_ID_EDIT_END_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,160,240,95},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Options")
	},
	{
		WISP_CTRL_CHECK_BOX,
		{20,170,120,16},
		WISP_ID_NULL,
		WISP_WS_THIN_BORDER,
		WSTR("Find All Instances"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_CHECK_BOX,
		{150,170,50,16},
		WISP_ID_NULL,
		WISP_WS_THIN_BORDER,
		WSTR("Case"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{20,190,120,16},
		CMD_ID_RADIOBOX_ASCII_STR,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("ASCII String"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{20,210,120,16},
		CMD_ID_RADIOBOX_UNICODE_STR,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Unicode String"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{20,230,120,16},
		CMD_ID_RADIOBOX_EITHER,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Either"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{260,160,114,95},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Direction")
	},
	{
		WISP_CTRL_RADIO_BOX,
		{270,175,90,16},
		CMD_ID_RADIOBOX_DIRECTION_DOWN,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Down"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{270,195,90,16},
		CMD_ID_RADIOBOX_DIRECTION_UP,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Up"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{100,260,68,20},
		CMD_ID_BUTTON_OK,
		WISP_BS_NORMAL,
		WSTR("Find"),
	},
	{
		WISP_CTRL_BUTTON,
		{210,260,68,20},
		CMD_ID_BUTTON_CANCEL,
		WISP_BS_NORMAL,
		WSTR("Close"),
	},
	{WISP_CTRL_NULL}
};
WISP_MSG_MAP_BEGIN(CDataViewFindDlg)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CDataViewFindDlg)
//WISP_MSG_CMD_MAP(CMD_ID_LIST_TYPE,OnTypeListCmd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CDataViewFindDlg)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_OK,OnOKButtonEvent)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_CANCEL,OnCancelButtonEvent)
//WISP_MSG_EVENT_MAP(CMD_ID_RADIOBOX_LOCKTYPE,OnLockRadioBoxEvent)
WISP_MSG_EVENT_MAP(CMD_ID_RADIOBOX_IN_MODULE,OnInModuleRadioBoxEvent)
WISP_MSG_EVENT_MAP(CMD_ID_RADIOBOX_IN_RANGE,OnInRangeRadioBoxEvent)
WISP_MSG_EVENT_MAP_END
CDataViewFindDlg::CDataViewFindDlg()
{
	m_pFormRes = m_FormRes;
}
CDataViewFindDlg::~CDataViewFindDlg()
{
}

bool CDataViewFindDlg::OnFormCreate(IN WISP_MSG* pMsg)
{
	m_OKButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_OK); 
	m_CancelButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_CANCEL);
	m_AsciiRadioBox=	(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_ASCII_STR); 
	m_UnicodeRadioBox=	(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_UNICODE_STR);
	m_EitherRadioBox=	(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_EITHER);
	m_InModuleRadioBox=	(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_IN_MODULE);
	m_InRangeRadioBox=	(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_IN_RANGE);
	m_DownRadioBox=	(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_DIRECTION_DOWN);
	m_UpRadioBox=	(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_DIRECTION_UP);
	m_AllInstanceCheckBox=	(CWispCheckBox*)GetFormItem(CMD_ID_CHECKBOX_ALL_INSTANCES);
	m_CaseCheckBox=	(CWispCheckBox*)GetFormItem(CMD_ID_CHECKBOX_CASE);
	m_BeginAddressEdit=	(CWispEdit*)GetFormItem(CMD_ID_EDIT_BEGIN_ADDRESS);
	m_EndAddressEdit=	(CWispEdit*)GetFormItem(CMD_ID_EDIT_END_ADDRESS);
	m_HexEdit=	(CWispEdit*)GetFormItem(CMD_ID_EDIT_HEX);
	m_ValueEdit=	(CWispEdit*)GetFormItem(CMD_ID_EDIT_VALUE);
	m_TypeComboBox = (CWispComboBox*)GetFormItem(CMD_ID_COMBOBOX_TYPE);
	for(int i = 0; i < sizeof(m_FindDataType)/sizeof(m_FindDataType[0]);i++)
	m_TypeComboBox->InsertItem(m_FindDataType[i].TypeName,m_FindDataType[i].TypeID);
	m_HexEdit->EnableWindow(false);
	return true;
}
bool CDataViewFindDlg::OnInModuleRadioBoxEvent(IN WISP_MSG* pMsg)
{
	m_BeginAddressEdit->EnableWindow(false);
	m_EndAddressEdit->EnableWindow(false);
	Update();
	return true;
}
bool CDataViewFindDlg::OnInRangeRadioBoxEvent(IN WISP_MSG* pMsg)
{
	m_BeginAddressEdit->EnableWindow(true);
	m_EndAddressEdit->EnableWindow(true);
	Update();
	return true;
}
bool CDataViewFindDlg::OnDestroy(IN WISP_MSG* pMsg)
{

	return true;
}
bool CDataViewFindDlg::CreateForm(CWispBaseWnd* pParentWnd,UINT ShowMode,UINT BeginAddr)
{
	return CWispForm::CreateForm(pParentWnd,ShowMode);
}


bool CDataViewFindDlg::OnOKButtonEvent(IN WISP_MSG* pMsg)
{
	
	PostCloseMsg();
	return true;
}
bool CDataViewFindDlg::OnCancelButtonEvent(IN WISP_MSG* pMsg)
{
	PostCloseMsg();
	return true;
}


bool CDataViewFindDlg::OnTypeListCmd(IN WISP_MSG* pMsg)
{

	return true;
}