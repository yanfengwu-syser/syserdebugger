// SymRecv.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define DEFAULT_SYM_SITE	"http://msdl.microsoft.com/download/symbols"
#define DEFAULT_PDB_PATH	"Download Symbols"
#define DEFAULT_SDS_PATH	"Download Converted SDS"

// CSymRecvApp:
// See SymRecv.cpp for the implementation of this class
//

class CSymRecvApp : public CWinApp
{
public:
	CSymRecvApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation
	CString m_strSymSite;
	CString m_strPDBPath;
	CString m_strSDSPath;
	DECLARE_MESSAGE_MAP()
};

extern CSymRecvApp theApp;