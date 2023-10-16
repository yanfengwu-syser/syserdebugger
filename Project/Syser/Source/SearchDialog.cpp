#include "stdafx.h"
#include "SearchDialog.h"
#include "ModuleListWnd.h"
#include "Syser.h"

PCWSTR CSearchDialog::m_FindDataType[]=
{
	WSTR("Text (Ansi)"),
	WSTR("Text (Unicode)"),
	WSTR("BYTE (s)"),
	WSTR("WORD  Value"),
	WSTR("DWORD Value"),
	WSTR("QWORD Value"),
	NULL
};

enum CSearchDialog::WISP_FORM_ID
{
	CMD_ID_COMBOBOX_TYPE = WISP_ID_USER_START,
	CMD_ID_EDIT_VALUE,
	CMD_ID_CASE_CHECK,
	CMD_ID_RADIOBOX_DIRECTION_DOWN,
	CMD_ID_RADIOBOX_DIRECTION_UP,
	CMD_ID_EDIT_BEGIN_ADDRESS,
	CMD_ID_EDIT_END_ADDRESS,
	CMD_ID_BUTTON_SELECT_MODULE,
	CMD_ID_BUTTON_FIND,
	CMD_ID_BUTTON_FIND_NEXT,
};

WISP_FORM_RES_ITEM CSearchDialog::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,391,220},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Search"),
		"\\Toolbar.bmp#16#16:119",
		NULL,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,364,80},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Search Method")
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,32,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:119"
	},
	{
		WISP_CTRL_STATIC_STRING,
		{40,32,45,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Type"),
		NULL,
	},
	{
		WISP_CTRL_COMBO_BOX,
		{80,30,135,20},
		CMD_ID_COMBOBOX_TYPE,
		WISP_ES_EDIT_NORMAL|WISP_ES_READONLY,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_CHECK_BOX,
		{230,30,100,20},
		CMD_ID_CASE_CHECK,
		WISP_CBS_NORMAL,
		WSTR("Match case"),
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,62,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:5"
	},
	{
		WISP_CTRL_STATIC_STRING,
		{40,62,45,18},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Value"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{80,60,280,18},
		CMD_ID_EDIT_VALUE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,116,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:13*16+12"
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,95,364,50},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Range")
	},
	{
		WISP_CTRL_STATIC_STRING,
		{40,116,40,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Begin"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{80,115,70,16},
		CMD_ID_EDIT_BEGIN_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{160,116,25,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("End"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{190,115,70,16},
		CMD_ID_EDIT_END_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{270,113,90,20},
		CMD_ID_BUTTON_SELECT_MODULE,
		WISP_BS_NORMAL,
		WSTR("Select Module"),
	},
	{
		WISP_CTRL_BUTTON,
		{100,160,68,20},
		CMD_ID_BUTTON_FIND,
		WISP_BS_NORMAL,
		WSTR("Find"),
	},
	{
		WISP_CTRL_BUTTON,
		{210,160,68,20},
		CMD_ID_BUTTON_FIND_NEXT,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Find Next"),
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CSearchDialog)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CSearchDialog)
	WISP_MSG_CMD_MAP(CMD_ID_COMBOBOX_TYPE,OnTypeComboxCmd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CSearchDialog)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_SELECT_MODULE,OnButtonSelectModule)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_FIND,OnButtonFind)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_FIND_NEXT,OnButtonFindNext)
WISP_MSG_EVENT_MAP_END

CSearchDialog::CSearchDialog()
{
	m_pFormRes = m_FormRes;
}

CSearchDialog::~CSearchDialog()
{
}

void CSearchDialog::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		CreateForm(NULL);
		Center();
	}
}

bool CSearchDialog::OnFormCreate(IN WISP_MSG* pMsg)
{	
	m_BeginAddressEdit	=	(CWispEdit*)GetFormItem(CMD_ID_EDIT_BEGIN_ADDRESS);
	m_EndAddressEdit	=	(CWispEdit*)GetFormItem(CMD_ID_EDIT_END_ADDRESS);
	m_ValueEdit			=	(CWispEdit*)GetFormItem(CMD_ID_EDIT_VALUE);
	m_TypeComboBox		=	(CWispComboBox*)GetFormItem(CMD_ID_COMBOBOX_TYPE);
	m_pCaseCheckBox		=	(CWispCheckBox*)GetFormItem(CMD_ID_CASE_CHECK);

	for(int i=0;m_FindDataType[i];i++)
		m_TypeComboBox->m_ComboList.InsertItem(m_FindDataType[i]);
	m_TypeComboBox->SelectItem(0);

	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(*X86_REG_PTR.pEIP);
	if(pDbgModule==NULL)
		pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModule(*X86_REG_PTR.pEIP);
	if(pDbgModule)
	{
		WCHAR szBuffer[32];
		uNumToStr(pDbgModule->m_ModuleBase,szBuffer);
		m_BeginAddressEdit->SetWindowText(szBuffer);
		uNumToStr(pDbgModule->m_ModuleBase+pDbgModule->m_ModuleSize,szBuffer);
		m_EndAddressEdit->SetWindowText(szBuffer);
	}
	return true;
}

bool CSearchDialog::OnTypeComboxCmd(IN WISP_MSG* pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_COMBOX_SELCHANGE)
	{
		m_pCaseCheckBox->EnableWindow(pMsg->Command.Param1<=FIND_DATA_TYPE_TEXT_UNI);
	}
	return true;
}

bool CSearchDialog::OnButtonSelectModule(IN WISP_MSG* pMsg)
{
	CModuleListWnd ModuleList;
	ModuleList.Popup(true);
	if(ModuleList.m_pDbgModule)
	{
		WCHAR szBuffer[32];
		uNumToStr(ModuleList.m_pDbgModule->m_ModuleBase,szBuffer);
		m_BeginAddressEdit->SetWindowText(szBuffer);
		uNumToStr(ModuleList.m_pDbgModule->m_ModuleBase+ModuleList.m_pDbgModule->m_ModuleSize,szBuffer);
		m_EndAddressEdit->SetWindowText(szBuffer);
		UpdateClient();
	}
	return true;
}

bool CSearchDialog::OnButtonFind(IN WISP_MSG* pMsg)
{
	int Index = m_TypeComboBox->GetCurSelItem();
	if(Index==-1)
		return true;
	if(m_ValueEdit->m_WndText.Length()==0)
		goto ErrorExit;
	if( USHexStrToNum((PCWSTR)m_BeginAddressEdit->GetWindowText(),&m_BeginAddress)==false ||
		USHexStrToNum((PCWSTR)m_EndAddressEdit->GetWindowText(),&m_EndAddress)==false || m_BeginAddress>=m_EndAddress)
	{
		gpCurWisp->MsgBox(WSTR("Invalid Search Range !"),WSTR("Error"),WISP_MB_OK|WISP_MB_ICONERROR);
		return true;
	}
	m_bCase = true;
	ZeroMemory(m_FindData,sizeof(m_FindData));
	switch(Index)
	{
		case FIND_DATA_TYPE_TEXT_ANSI:
			m_FindDataLength = UnicodeToAnsi(m_ValueEdit->m_WndText,(PSTR)m_FindData,sizeof(m_FindData));
			m_bCase = m_pCaseCheckBox->IsChecked();
			break;
		case FIND_DATA_TYPE_TEXT_UNI:
			m_FindDataLength = TStrCpyLimit((PWSTR)m_FindData,(PCWSTR)m_ValueEdit->m_WndText,sizeof(m_FindData)/2)*2;
			m_bCase = m_pCaseCheckBox->IsChecked();
			break;
		case FIND_DATA_TYPE_BYTES:
			m_FindDataLength = THexStrToBytes((PCWSTR)m_ValueEdit->m_WndText,m_FindData,sizeof(m_FindData));
			if(m_FindDataLength==0)
				goto ErrorExit;
			break;
		case FIND_DATA_TYPE_WORD:
			if(USHexStrToNum((PCWSTR)m_ValueEdit->GetWindowText(),(WORD *)m_FindData)==false)
				goto ErrorExit;
			m_FindDataLength = 2;
			break;
		case FIND_DATA_TYPE_DWORD:
			if(USHexStrToNum((PCWSTR)m_ValueEdit->GetWindowText(),(DWORD*)m_FindData)==false)
				goto ErrorExit;
			m_FindDataLength = 4;
			break;
		case FIND_DATA_TYPE_QWORD:
			if(USHexStrToNum((PCWSTR)m_ValueEdit->GetWindowText(),(QWORD*)m_FindData)==false)
				goto ErrorExit;
			m_FindDataLength = 8;
			break;
	}
	m_CurPos = gpSyser->m_pDebugger->SearchMem(m_BeginAddress,m_EndAddress-m_BeginAddress,m_FindData,m_FindDataLength,m_bCase);
	if(m_CurPos==-1)
	{
		gpCurWisp->MsgBox(WSTR("The special data was not found !"),WSTR("Data Search"),WISP_MB_OK|WISP_MB_ICONERROR);
	}
	else
	{
		GetFormItem(CMD_ID_BUTTON_FIND_NEXT)->EnableWindow(true);
		VIEW_DATA(m_CurPos,m_FindDataLength);
	}
	return true;
ErrorExit:
	gpCurWisp->MsgBox(WSTR("Invalid Search Data !"),WSTR("Error"),WISP_MB_OK|WISP_MB_ICONERROR);
	return true;
}

bool CSearchDialog::OnButtonFindNext(IN WISP_MSG* pMsg)
{
	m_CurPos = gpSyser->m_pDebugger->SearchMem(m_CurPos+m_FindDataLength,m_EndAddress-m_CurPos,m_FindData,m_FindDataLength,m_bCase);
	if(m_CurPos==-1)
	{
		GetFormItem(CMD_ID_BUTTON_FIND_NEXT)->EnableWindow(false);
		gpCurWisp->MsgBox(WSTR("The special data was not found !"),WSTR("Data Search"),WISP_MB_OK|WISP_MB_ICONERROR);
	}
	else
	{
		VIEW_DATA(m_CurPos,m_FindDataLength);
	}
	return true;
}
