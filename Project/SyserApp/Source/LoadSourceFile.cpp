#include "StdAfx.h"
#include "LoadSourceFile.h"
#ifdef _SYSER_
#include "../../Syser/Source/Syser.h"
#else
#include "SyserApp.h"
#endif

enum CLoadSourceFileDlg::WISP_FORM_ID
{
	CMD_ID_BUTTON_SKIP=WISP_ID_USER_START,
	CMD_ID_BUTTON_SKIPALL,
	CMD_ID_BUTTON_BROWSE,
	CMD_ID_LIST_TYPE,
	CMD_ID_RADIOBOX_FLOATTYPE,
	CMD_ID_RADIOBOX_LOCKTYPE,
	CMD_ID_RADIOBOX_DWORD,
	CMD_ID_RADIOBOX_QWORD,
	CMD_ID_RADIOBOX_HEX,
	CMD_ID_RADIOBOX_DECIMAL,
	CMD_ID_STATICSTR_FILENAME,
	CMD_ID_STATICSTR_DESCRIPTION,
	CMD_ID_EDIT_END_POSITION,
	CMD_ID_EDIT_VALUE,
	CMD_ID_CHECKBOX_COUNT,
};
WISP_FORM_RES_ITEM CLoadSourceFileDlg::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,285,144},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Attach Type"),
		"\\SyserIcon\\Plugin.ico",
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{13,20,250,16},
		CMD_ID_STATICSTR_DESCRIPTION,
		WISP_WS_NULL,
		WSTR("Unable to locate the following file:"),
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{13,70,250,16},
		CMD_ID_STATICSTR_FILENAME,
		WISP_WS_NULL,
		WSTR(""),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{13,87,75,21},
		CMD_ID_BUTTON_SKIP,
		WISP_BS_NORMAL,
		WSTR("Skip"),
	},
	{
		WISP_CTRL_BUTTON,
		{99,87,75,21},
		CMD_ID_BUTTON_SKIPALL,
		WISP_BS_NORMAL,
		WSTR("Skip All"),
	},
	{
		WISP_CTRL_BUTTON,
		{185,87,75,21},
		CMD_ID_BUTTON_BROWSE,
		WISP_BS_NORMAL,
		WSTR("Browse"),
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CLoadSourceFileDlg)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CLoadSourceFileDlg)

WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CLoadSourceFileDlg)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_SKIP,OnSkipButtonEvent)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_SKIPALL,OnSkipAllButtonEvent)
	WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_BROWSE,OnBrowseButtonEvent)
WISP_MSG_EVENT_MAP_END

CLoadSourceFileDlg::CLoadSourceFileDlg()
{
	m_pFormRes = m_FormRes;
	m_FileName[0]=0;
}
CLoadSourceFileDlg::~CLoadSourceFileDlg()
{
}
bool CLoadSourceFileDlg::OnFormCreate(IN WISP_MSG* pMsg)
{
	m_SkipButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_SKIP);
	m_SkipAllButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_SKIPALL);
	m_BrowseButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_BROWSE);
	m_DesciptionStr=(CWispStaticStr*)GetFormItem(CMD_ID_STATICSTR_DESCRIPTION);
	m_FileNameStr=(CWispStaticStr*)GetFormItem(CMD_ID_STATICSTR_FILENAME);
	m_FileNameStr->SetWindowText(m_FileName);
	return true;
}

bool CLoadSourceFileDlg::OnSkipButtonEvent(IN WISP_MSG* pMsg)
{
	Destroy();
	m_Result=1;
	return true;
}

bool CLoadSourceFileDlg::OnSkipAllButtonEvent(IN WISP_MSG* pMsg)
{
	Destroy();
	m_Result=2;
	return true;
}
#ifdef _SYSER_
bool CLoadSourceFileDlg::OnBrowseButtonEvent(IN WISP_MSG* pMsg)
{
	char szBuffer[MAX_FN_LEN],szFileName[MAX_FN_LEN];
	WCHAR * FileExtName;
	OPENFILENAME OpenFileName;
	m_Result=1;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = gpSyser->m_hLocalInst;
	OpenFileName.hwndOwner = gpSyser->m_hLocalWnd;
	FileExtName = TGetFileName(m_FileName);
	TStrCpy(szBuffer,"Source Files|");
	TStrCat(szBuffer,FileExtName);
	TStrCat(szBuffer,"|");
	m_szFileName[0]=0;
	for(int n = TStrLen(szBuffer);n>=0;n--)
	{
		if(szBuffer[n]=='|')
			szBuffer[n]=0;
	}
	OpenFileName.lpstrFilter = szBuffer;
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	*szFileName = 0;
	gpSyser->LockTimer();
	if(GetOpenFileName(&OpenFileName)==TRUE)
	{
		Destroy();
		m_Result=0;
		TStrCpy(m_szFileName,OpenFileName.lpstrFile);
	}
	gpSyser->UnlockTimer();
	return true;
}
#else
bool CLoadSourceFileDlg::OnBrowseButtonEvent(IN WISP_MSG* pMsg)
{
	char szBuffer[MAX_FN_LEN],szFileName[MAX_FN_LEN];
	WCHAR * FileExtName;
	OPENFILENAME OpenFileName;
	m_Result=1;
	STZeroMemory(OpenFileName);

	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	FileExtName = TGetFileName(m_FileName);
	TStrCpy(szBuffer,"Source Files|");
	TStrCat(szBuffer,FileExtName);
	TStrCat(szBuffer,"|");
	m_szFileName[0]=0;
	for(int n = TStrLen(szBuffer);n>=0;n--)
	{
		if(szBuffer[n]=='|')
			szBuffer[n]=0;
	}
	OpenFileName.lpstrFilter = szBuffer;
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	*szFileName = 0;
	theApp.LockTimer();

	if(GetOpenFileName(&OpenFileName)==TRUE)
	{
		Destroy();
		m_Result=0;
		TStrCpy(m_szFileName,OpenFileName.lpstrFile);
	}
	theApp.UnlockTimer();
	return true;
}
#endif 

bool CLoadSourceFileDlg::CreateForm(IN CWispBaseWnd* pParentWnd,IN UINT ShowMode,IN char* FileName)
{
	TStrCpy(m_FileName,FileName);
	return CWispForm::CreateForm(pParentWnd,ShowMode);
}

int LoadSourceFileCallBack(IN char* OrgFileName,OUT char* NewFileName)
{
	return 2;
	int bRet=0;
	char* pStr;
#ifdef _SYSER_
	if(gpSyser->m_MainFrame.IsWindow()==false)
		return 2;
#else
	if(theApp.m_MainFrame.IsWindow()==false)
		return 2;
#endif
	pStr = TGetFileName(OrgFileName);
	CLoadSourceFileDlg Dlg;
	Dlg.CreateForm(NULL,WISP_SH_MODAL_BLOCK,pStr);
	bRet=Dlg.m_Result;
	if(bRet==0)
	{
		TStrCpy(NewFileName,Dlg.m_szFileName);
	}
	return bRet;
}