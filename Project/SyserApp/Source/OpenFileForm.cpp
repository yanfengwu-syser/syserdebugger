#include "StdAfx.h"
#include "OpenFileForm.h"
#include "SyserApp.h"

enum COpenFileForm::WISP_FORM_ID
{
	CMD_ID_EDIT_TEXT = WISP_ID_USER_START,
	CMD_ID_COMMAND_LINE_TEXT,
	CMD_ID_STATIC_TEXT,
	CMD_ID_BROWSE,
	CMD_ID_TRANSLATE_SYMBOL,
	CMD_ID_DEPENDENT_SYMBOL,
	CMD_ID_AUTO_UNLOAD_SYMBOL,
};

WISP_FORM_RES_ITEM COpenFileForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,400,260},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("Launch module and break at entry point"),
		"\\SyserIcon\\Syser.ico"
	},
	{
		WISP_CTRL_STATIC_DIB,
		{15,30,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Process.ico"
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,370,50},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Filename"),
	},
	{
		WISP_CTRL_EDIT,
		{40,30,250,16},
		CMD_ID_EDIT_TEXT,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_DIB,
		{15,90,16,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\SrcExplorer.ico"
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,70,370,50},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Command Line (Ignored by sys or dll)"),
	},
	{
		WISP_CTRL_EDIT,
		{40,90,330,16},
		CMD_ID_COMMAND_LINE_TEXT,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{310,30,60,18},
		CMD_ID_BROWSE,
		WISP_BS_NORMAL,
		WSTR("Browse"),
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,125,370,100},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
	},
	{
		WISP_CTRL_CHECK_BOX,
		{20,145,270,20},
		CMD_ID_TRANSLATE_SYMBOL,
		WISP_CBS_NORMAL|WISP_WS_MARKED,
		WSTR("Translate&Load it's SDS"),
		NULL,
	},
	{
		WISP_CTRL_CHECK_BOX,
		{20,170,270,20},
		CMD_ID_DEPENDENT_SYMBOL,
		WISP_CBS_NORMAL,
		WSTR("Translate&Load dependent module's SDS"),
		NULL,
	},
	{
		WISP_CTRL_CHECK_BOX,
		{20,195,270,20},
		CMD_ID_AUTO_UNLOAD_SYMBOL,
		WISP_CBS_NORMAL|WISP_WS_MARKED,
		WSTR("Unload SDS when module unload"),
		NULL,
	},
	{
		WISP_CTRL_STATIC_DIB,
		{325,145,32,32},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Syser.ico:1"
	},
	{
		WISP_CTRL_BUTTON,
		{310,190,60,18},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("Load"),
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(COpenFileForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_EVENT_MAP_BEGIN(COpenFileForm)
	WISP_MSG_EVENT_MAP(CMD_ID_BROWSE,OnEventBrowse)
WISP_MSG_EVENT_MAP_END

WISP_MSG_CMD_MAP_BEGIN(COpenFileForm)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END


bool COpenFileForm::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pFilenameEdit = (CWispEdit*) GetFormItem(CMD_ID_EDIT_TEXT);
	m_pCmdlineEdit  = (CWispEdit*) GetFormItem(CMD_ID_COMMAND_LINE_TEXT);
	m_pTransSymCheckBox = (CWispCheckBox*) GetFormItem(CMD_ID_TRANSLATE_SYMBOL);
	m_pLoadDepSymCheckBox = (CWispCheckBox*) GetFormItem(CMD_ID_DEPENDENT_SYMBOL);
	m_pAutoUnloadSymCheckBox = (CWispCheckBox*) GetFormItem(CMD_ID_AUTO_UNLOAD_SYMBOL);
	*m_CmdLine = 0;
	*m_Filename = 0;
	return true;
}

bool COpenFileForm::OnEventBrowse(IN WISP_MSG*pMsg)
{
	char szFileName[MAX_FN_LEN];
	WCHAR wszFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "Executable Files(exe;dll;scr;sys)\0*.exe;*.dll;*.scr;*.sys\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	*szFileName = 0;
	if(GetOpenFileName(&OpenFileName)==false)
		return true;
	AnsiToUnicode(szFileName,wszFileName,MAX_FN_LEN);
	m_pFilenameEdit->SetWindowText(wszFileName);
	UpdateClient();
	return true;
}

bool COpenFileForm::OnOK(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		UnicodeToAnsi(m_pFilenameEdit->GetWindowText(),m_Filename,MAX_FN_LEN);
		if(*m_Filename==0)
			return false;
		if(m_pCmdlineEdit->GetWindowText().Length())
			UnicodeToAnsi(m_pCmdlineEdit->GetWindowText(),m_CmdLine,sizeof(m_CmdLine));
		else
			*m_CmdLine=0;
		m_bTransSym = (m_pTransSymCheckBox->m_Style&WISP_WS_MARKED)!=0;
		m_bLoadDepSym = (m_pLoadDepSymCheckBox->m_Style&WISP_WS_MARKED)!=0;
		m_bAutoUnloadSym = (m_pAutoUnloadSymCheckBox->m_Style&WISP_WS_MARKED)!=0;
	}
	return true;
}
