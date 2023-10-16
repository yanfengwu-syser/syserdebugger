#include "StdAfx.h"
#include "Syser.h"
#include "CodeBPEdit.h"

enum CCodeBPEdit::WISP_FORM_ID
{
	CMD_ID_EDIT_ADDRESS = WISP_ID_USER_START,
	CMD_ID_EDIT_NAME,
	CMD_ID_CHECK_ENABLE,
	CMD_ID_EDIT_CONDITION,
	CMD_ID_EDIT_DO_COMMAND,
};

WISP_FORM_RES_ITEM CCodeBPEdit::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,385,280},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("Code break point")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,325,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Address")
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,25,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:243"
	},
	{
		WISP_CTRL_EDIT,
		{40,25,285,16},
		CMD_ID_EDIT_ADDRESS,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("Address of break point")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,60,325,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Name")
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,75,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:10"
	},
	{
		WISP_CTRL_EDIT,
		{40,75,285,16},
		CMD_ID_EDIT_NAME,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("Name of break point (if needed)")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,110,325,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Condition"),
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,125,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:29"
	},
	{
		WISP_CTRL_EDIT,
		{40,125,285,16},
		CMD_ID_EDIT_CONDITION,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("break condition when break point touched")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,160,325,40},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Do Command (Use ; to delimit command lines)"),
	},
	{
		WISP_CTRL_STATIC_DIB,
		{20,175,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\Toolbar.bmp#16#16:63"
	},
	{
		WISP_CTRL_EDIT,
		{40,175,285,16},
		CMD_ID_EDIT_DO_COMMAND,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		WSTR("Do command when break point touched")
	},
	{
		WISP_CTRL_CHECK_BOX,
		{20,210,60,20},
		CMD_ID_CHECK_ENABLE,
		WISP_CBS_NORMAL,
		WSTR("Enabled"),
		NULL,
		WSTR("Is break point enabled")
	},
	{
		WISP_CTRL_BUTTON,
		{275,210,55,20},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
		NULL,
		WSTR("Save modify setting")
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CCodeBPEdit)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CCodeBPEdit)
	WISP_MSG_CMD_MAP(CMD_ID_EDIT_ADDRESS,OnAddressChg)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END

CCodeBPEdit::CCodeBPEdit(void)
{
	m_pFormRes = m_FormRes;
	m_pModuleBP = NULL;
	m_pBP = NULL;
}

CCodeBPEdit::~CCodeBPEdit(void)
{
}

bool CCodeBPEdit::OnFormCreate(IN WISP_MSG*pMsg)
{
	WISP_CHAR szBuffer[256];
	m_pNameEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_NAME);
	m_pAddrEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_ADDRESS);
	m_pConditionEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_CONDITION);
	m_pDoCmdEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_DO_COMMAND);
	m_pEnableChkBox = (CWispCheckBox*)GetFormItem(CMD_ID_CHECK_ENABLE);
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
	}
	else if(m_pModuleBP)
	{
		CModuleBPMap::IT Iter = *m_pModuleBP;
		uNumToStr(Iter.Key(),szBuffer);
		m_pAddrEdit->SetWindowText(szBuffer);
		AnsiToUnicode(m_pModuleBP->Name,szBuffer,256);
		m_pNameEdit->SetWindowText(szBuffer);
		AnsiToUnicode(m_pModuleBP->Condition,szBuffer,256);
		m_pConditionEdit->SetWindowText(szBuffer);
		AnsiToUnicode(m_pModuleBP->DoCmd,szBuffer,256);
		m_pDoCmdEdit->SetWindowText(szBuffer);
		m_bEnable = m_pModuleBP->State!=BP_STATE_DISABLE;
	}
	m_pEnableChkBox->Check(m_bEnable);
	return true;
}

bool CCodeBPEdit::OnOK(IN WISP_MSG*pMsg)
{
	ULPOS ConditionValue;
	CHAR szBuffer[256];
	if(pMsg->Command.CmdMsg!=WISP_CMD_BT_UP)
		return true;
	BREAK_POINT BreakPoint;
	if(CALCEXP(m_pAddrEdit->m_WndText,&BreakPoint.Address)==false)
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
	if(m_pBP)
	{
		if(BreakPoint.Address==m_pBP->Address && BreakPoint.State==m_pBP->State)
		{
			m_pBP->Name = BreakPoint.Name;
			m_pBP->Condition = BreakPoint.Condition;
			m_pBP->DoCmd = BreakPoint.DoCmd;
			return true;
		}
		if(gpSyser->m_SyserUI.RemoveCodeBP(m_pBP->Address)==false)
			goto ErrorExit;
	}
	else if(m_pModuleBP)
	{
		CModuleBPMap::IT Iter = *m_pModuleBP;
		if(BreakPoint.Address==Iter.Key() && BreakPoint.State==m_pModuleBP->State)
		{
			m_pModuleBP->Name = BreakPoint.Name;
			m_pModuleBP->Condition = BreakPoint.Condition;
			m_pModuleBP->DoCmd = BreakPoint.DoCmd;
			return true;
		}
		if(gpSyser->m_SyserUI.RemoveCodeBP(Iter.Key())==false)
			goto ErrorExit;
	}
	if(gpSyser->m_SyserUI.InsertCodeBP(BreakPoint.Address,BreakPoint.Name,BreakPoint.Condition,BreakPoint.DoCmd)==false)
		goto ErrorExit;
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	return true;
ErrorExit:
	gpCurWisp->MsgBox(WSTR("Fail to insert breakpoint !"),WSTR("Error"),WISP_MB_OK|WISP_MB_ICONERROR);
	return false;
}

bool CCodeBPEdit::OnAddressChg(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_EN_CHANGED)
	{
		m_pNameEdit->SetWindowText(m_pAddrEdit->m_WndText);
	}
	return true;
}

