#include "StdAfx.h"
#include "Syser.h"
#include "DataBPEdit.h"

enum CDataBPEdit::WISP_FORM_ID
{
	CMD_ID_EDIT_ADDRESS = WISP_ID_USER_START,
	CMD_ID_EDIT_NAME,
	CMD_ID_CHECK_ENABLE,
	CMD_ID_RADIO_WRITEONLY,
	CMD_ID_RADIO_READWRITE,
	CMD_ID_RADIO_EXECUTE,
	CMD_ID_RADIO_IO,
	CMD_ID_EDIT_CONDITION,
	CMD_ID_EDIT_DO_COMMAND,
	CMD_ID_RADIO_BYTE,
	CMD_ID_RADIO_WORD,
	CMD_ID_RADIO_DWORD,
	CMD_ID_RADIO_ALL,
};

WISP_FORM_RES_ITEM CDataBPEdit::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,355,290},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("Data break point")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,5,80,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Address")
	},
	{
		WISP_CTRL_EDIT,
		{20,20,60,16},
		CMD_ID_EDIT_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("Address of break point")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{100,5,100,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Name")
	},
	{
		WISP_CTRL_EDIT,
		{110,20,80,16},
		CMD_ID_EDIT_NAME,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("Name of break point (if needed)")
	},
	{
		WISP_CTRL_CHECK_BOX,
		{210,17,60,20},
		CMD_ID_CHECK_ENABLE,
		WISP_CBS_NORMAL,
		WSTR("Enabled"),
		NULL,
		WSTR("Is break point enabled")
	},
	{
		WISP_CTRL_BUTTON,
		{280,20,55,20},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
		NULL,
		WSTR("Save modify setting")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,50,325,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Type"),
	},
	{
		WISP_CTRL_RADIO_BOX,
		{20,65,75,20},
		CMD_ID_RADIO_READWRITE,
		WISP_RBS_NORMAL,
		WSTR("ReadWrite"),
		NULL,
		WSTR("break on access memory")
	},
	{
		WISP_CTRL_RADIO_BOX,
		{100,65,75,20},
		CMD_ID_RADIO_WRITEONLY,
		WISP_RBS_NORMAL,
		WSTR("WriteOnly"),
		NULL,
		WSTR("break on write memory")
	},
	{
		WISP_CTRL_RADIO_BOX,
		{180,65,75,20},
		CMD_ID_RADIO_EXECUTE,
		WISP_RBS_NORMAL,
		WSTR("Execute"),
		NULL,
		WSTR("break on execute")
	},
	{
		WISP_CTRL_RADIO_BOX,
		{260,65,75,20},
		CMD_ID_RADIO_IO,
		WISP_RBS_NORMAL,
		WSTR("I/O"),
		NULL,
		WSTR("break on IO access,address is IO Num")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,95,325,45},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Length"),
	},
	{
		WISP_CTRL_RADIO_BOX,
		{20,110,75,20},
		CMD_ID_RADIO_ALL,
		WISP_RBS_NORMAL,
		WSTR("ALL"),
	},
	{
		WISP_CTRL_RADIO_BOX,
		{100,110,75,20},
		CMD_ID_RADIO_BYTE,
		WISP_RBS_NORMAL,
		WSTR("BYTE"),
	},
	{
		WISP_CTRL_RADIO_BOX,
		{180,110,75,20},
		CMD_ID_RADIO_WORD,
		WISP_RBS_NORMAL,
		WSTR("WORD"),
	},
	{
		WISP_CTRL_RADIO_BOX,
		{260,110,75,20},
		CMD_ID_RADIO_DWORD,
		WISP_RBS_NORMAL,
		WSTR("DWORD"),
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,150,325,50},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Condition"),
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,170,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:29"
	},
	{
		WISP_CTRL_EDIT,
		{40,170,285,16},
		CMD_ID_EDIT_CONDITION,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("break condition when break point touched")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,210,325,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Do Command  (Use ; to delimit command lines)"),
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,225,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:63"
	},
	{
		WISP_CTRL_EDIT,
		{40,225,285,16},
		CMD_ID_EDIT_DO_COMMAND,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("Do command when break point touched")
	},
	{WISP_CTRL_NULL}
};


WISP_MSG_MAP_BEGIN(CDataBPEdit)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CDataBPEdit)
	WISP_MSG_CMD_MAP(CMD_ID_EDIT_ADDRESS,OnAddressChg)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END

CDataBPEdit::CDataBPEdit(void)
{
	m_pFormRes = m_FormRes;
	m_pBP = NULL;
}

CDataBPEdit::~CDataBPEdit(void)
{
}

bool CDataBPEdit::OnFormCreate(IN WISP_MSG*pMsg)
{
	WISP_CHAR szBuffer[256];
	m_pNameEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_NAME);
	m_pAddrEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_ADDRESS);
	m_pConditionEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_CONDITION);
	m_pDoCmdEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_DO_COMMAND);

	m_pEnableChkBox = (CWispCheckBox*)GetFormItem(CMD_ID_CHECK_ENABLE);
	m_pWriteRadioBox = (CWispRadioBox*)GetFormItem(CMD_ID_RADIO_WRITEONLY);
	m_pReadWriteRadioBox = (CWispRadioBox*)GetFormItem(CMD_ID_RADIO_READWRITE);
	m_pExecuteRadioBox = (CWispRadioBox*)GetFormItem(CMD_ID_RADIO_EXECUTE);
	m_pIORadioBox = (CWispRadioBox*)GetFormItem(CMD_ID_RADIO_IO);

	m_pAllChkBox = (CWispCheckBox*)GetFormItem(CMD_ID_RADIO_ALL);
	m_pByteChkBox = (CWispCheckBox*)GetFormItem(CMD_ID_RADIO_BYTE);
	m_pWordChkBox = (CWispCheckBox*)GetFormItem(CMD_ID_RADIO_WORD);
	m_pDwordChkBox = (CWispCheckBox*)GetFormItem(CMD_ID_RADIO_DWORD);

	m_bEnable = true;
	if(m_pBP)
	{
		uNumToStr(m_pBP->Address,szBuffer);
		m_pAddrEdit->SetWindowText(szBuffer);
		AnsiToUnicode(m_pBP->Name,szBuffer,256);
		m_pNameEdit->SetWindowText(szBuffer);
		AnsiToUnicode(m_pBP->Condition,szBuffer,256);
		m_pConditionEdit->SetWindowText(szBuffer);
		AnsiToUnicode(m_pBP->DoCmd,szBuffer,256);
		m_pDoCmdEdit->SetWindowText(szBuffer);
		m_bEnable = m_pBP->State!=BP_STATE_DISABLE;
		if((m_pBP->Type&BP_TYPE_READWRITE)==BP_TYPE_READWRITE)
			m_pReadWriteRadioBox->Check();
		else if(m_pBP->Type&BP_TYPE_WRITE)
			m_pWriteRadioBox->Check();
		else if(m_pBP->Type&BP_TYPE_EXECUTE)
			m_pExecuteRadioBox->Check();
		else if(m_pBP->Type&BP_TYPE_IO_READWRITE)
			m_pIORadioBox->Check();
		switch(m_pBP->Length)
		{
		case 1:
			m_pByteChkBox->Check();
			break;
		case 2:
			m_pWordChkBox->Check();
			break;
		case 4:
			m_pDwordChkBox->Check();
			break;
		default:
			m_pAllChkBox->Check();
			break;
		}
	}
	else
	{
		m_pAllChkBox->Check();
		m_pReadWriteRadioBox->Check();
	}
	m_pEnableChkBox->Check(m_bEnable);
	return true;
}

bool CDataBPEdit::OnOK(IN WISP_MSG*pMsg)
{
	ULPOS ConditionValue;
	CHAR szBuffer[256];
	if(pMsg->Command.CmdMsg!=WISP_CMD_BT_UP)
		return true;
	BREAK_POINT BreakPoint;
	if(m_pAddrEdit->m_WndText.Length()==0 || CALCEXP((WISP_CHAR*)m_pAddrEdit->m_WndText,&BreakPoint.Address)==false)
	{
		gpCurWisp->MsgBox(WSTR("Invalid Address !"),WSTR("Error"),WISP_MB_OK|WISP_MB_ICONERROR);
		return false;
	}
#ifdef CODE_OS_NT_DRV
	if(BreakPoint.Address >= gpSyser->m_SysInfo.m_SyserBase && BreakPoint.Address < gpSyser->m_SysInfo.m_SyserHighBase)
	{
		gpCurWisp->MsgBox(WSTR("Cann't set breakpoint in Syser !"),WSTR("Error"),WISP_MB_OK|WISP_MB_ICONERROR);
		return false;
	}
#endif
	UnicodeToAnsi(m_pNameEdit->m_WndText,szBuffer,256);
	BreakPoint.Name = szBuffer;
	if(BreakPoint.Name.IsEmpty())
		BreakPoint.Name.Format("%08X",BreakPoint.Address);

	if(CALCEXP(m_pConditionEdit->m_WndText,&ConditionValue)==false)
	{
		gpCurWisp->MsgBox(WSTR("Invalid Condition !"),WSTR("Error"),WISP_MB_OK|WISP_MB_ICONERROR);
		return false;
	}
	UnicodeToAnsi(m_pConditionEdit->m_WndText,szBuffer,256);
	BreakPoint.Condition = szBuffer;
	UnicodeToAnsi(m_pDoCmdEdit->m_WndText,szBuffer,256);
	BreakPoint.DoCmd = szBuffer;

	m_bEnable = m_pEnableChkBox->IsChecked();
	BreakPoint.State = m_bEnable?BP_STATE_ENABLE:BP_STATE_DISABLE;
	BreakPoint.Type = BP_TYPE_HARDWARE;
	if(m_pReadWriteRadioBox->IsChecked())
		BreakPoint.Type |= BP_TYPE_READWRITE;
	else if(m_pWriteRadioBox->IsChecked())
		BreakPoint.Type |= BP_TYPE_WRITE;
	else if(m_pExecuteRadioBox->IsChecked())
		BreakPoint.Type |= BP_TYPE_EXECUTE;
	else if(m_pIORadioBox->IsChecked())
		BreakPoint.Type |= BP_TYPE_IO_READWRITE;
	if(m_pByteChkBox->IsChecked())
		BreakPoint.Length = 1;
	else if(m_pWordChkBox->IsChecked())
		BreakPoint.Length = 2;
	else if(m_pDwordChkBox->IsChecked())
		BreakPoint.Length = 4;
	else
		BreakPoint.Length = 0;

	if(m_pBP)
	{
		if(BreakPoint.Address==m_pBP->Address && BreakPoint.Type==m_pBP->Type && BreakPoint.State==m_pBP->State && BreakPoint.Length==m_pBP->Length)
		{
			m_pBP->Name = BreakPoint.Name;
			m_pBP->Condition = BreakPoint.Condition;
			m_pBP->DoCmd = BreakPoint.DoCmd;
			return true;
		}
		gpSyser->m_pSysDebugger->RemoveDataBP(m_pBP);
	}
	m_pBP = gpSyser->m_pSysDebugger->InsertDataBP(BreakPoint.Address,BreakPoint.Type,BreakPoint.State,BreakPoint.Length);
	if(m_pBP==NULL)
	{
		gpCurWisp->MsgBox(WSTR("Fail to insert breakpoint !"),WSTR("Error"),WISP_MB_OK|WISP_MB_ICONERROR);
		return false;
	}
	else
	{
		m_pBP->Name = BreakPoint.Name;
		m_pBP->Condition = BreakPoint.Condition;
		m_pBP->DoCmd = BreakPoint.DoCmd;
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	return true;
}

bool CDataBPEdit::OnAddressChg(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_EN_CHANGED)
	{
		m_pNameEdit->SetWindowText(m_pAddrEdit->m_WndText);
	}
	return true;
}

