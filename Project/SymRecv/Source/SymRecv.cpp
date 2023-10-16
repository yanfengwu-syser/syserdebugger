// SymRecv.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SymRecv.h"
#include "SymRecvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSymRecvApp

BEGIN_MESSAGE_MAP(CSymRecvApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSymRecvApp construction

CSymRecvApp::CSymRecvApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSymRecvApp object

CSymRecvApp theApp;


// CSymRecvApp initialization

BOOL CSymRecvApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	
	CHAR szPath[MAX_FN_LEN],szFileName[MAX_FN_LEN];
	GetModulePath(szPath);

	m_strSymSite = DEFAULT_SYM_SITE;

	TStrCpy(szFileName,szPath);
	TStrCat(szFileName,DEFAULT_PDB_PATH);
	m_strPDBPath = szFileName;

	TStrCpy(szFileName,szPath);
	TStrCat(szFileName,DEFAULT_SDS_PATH);
	m_strSDSPath = szFileName;

	CSymRecvDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
