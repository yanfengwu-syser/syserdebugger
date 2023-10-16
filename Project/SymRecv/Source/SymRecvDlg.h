// SymRecvDlg.h : header file
//

#pragma once

#include "afxcmn.h"


typedef struct _STPATHNAME
{
	PCSTR Name;
	bool operator ==(const struct _STPATHNAME dest)const
	{
		return TStrCmp(Name,dest.Name)==0;
	}
}STPATHNAME,*PSTPATHNAME;


class CGetSymbolStat
{
public:	
	DWORD Stat;
	CString SDSSavePath;
	CString PDBSavePath;
	CString FindPath;
	CString FileName;
	CGetSymbolStat()
	{
		Stat=0;
	}
};

typedef TMap<CStrA,CGetSymbolStat> WORKFILELIST;
typedef TList<STPATHNAME> SDSSAVEPATHLIST;
typedef TList<STPATHNAME> PDBSAVEPATHLIST;
typedef TList<STPATHNAME> SYMFINDPATHLIST;
#define IMAGEAPI_POINTER __stdcall
typedef BOOL 
(IMAGEAPI_POINTER* fpSymFindFileInPath)(
										HANDLE hprocess,
										PCSTR SearchPath,
										PCSTR FileName,
										PVOID id,
										DWORD two,
										DWORD three,
										DWORD flags,
										PSTR FoundFile,
										PFINDFILEINPATHCALLBACK callback,
										PVOID context
										);
typedef DWORD 
(IMAGEAPI_POINTER*fpSymSetOptions)(
								   DWORD SymOptions
								   );
typedef DWORD
(IMAGEAPI_POINTER* fpSymGetOptions)(void);




// CSymRecvDlg dialog
class CSymRecvDlg : public CDialog
{
// Construction
public:
	CSymRecvDlg(CWnd* pParent = NULL);	// standard constructor
	~CSymRecvDlg();
// Dialog Data
	enum { IDD = IDD_SYMRECV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
////////////////////////////////////////////////////////////////////////////
	fpSymSetOptions m_SymSetOptions;
	fpSymGetOptions m_SymGetOptions;
	fpSymFindFileInPath m_SymFindFileInPath;
	HMODULE m_DbgHelpModule;
	DWORD m_GetSymbolThreadID;
	friend DWORD WINAPI GetSymbolThread(LPVOID lpParameter);
	CRITICAL_SECTION m_CriticalSection;
	bool m_Stop;
	bool m_GetSymbolThread;
	DWORD	m_SDSSavePathIndex;
	DWORD	m_PDBSavePathIndex;
	SDSSAVEPATHLIST m_SDSSavePathList;
	PDBSAVEPATHLIST m_PDBSavePathList;
	SYMFINDPATHLIST m_SymFindPathList;
	WORKFILELIST m_CurrentFileList;
	bool	InitDbgHelp();
	bool	DownLoadSymbol(CGetSymbolStat& SymbolStat );
	bool	GetDebugCodeviewByDbg(char* DbgFileName,PPE_DEBUG_CODEVIEW DebugCodeView);
	bool	TranslateSymbolFile(IN int Type,IN PCSTR pExeFileName,OUT char* pSymbolFileName);
	bool	OnUpdateDownLoadState(WPARAM wParam,LPARAM lParam);
////////////////////////////////////////////////////////////////////////////
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strSymSite;
	CString m_strPDBPath;
	CString m_strSDSPath;
	CListCtrl m_ModuleList;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonGetSym();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonBrowsePdb();
	afx_msg void OnBnClickedButtonBrowseSds();
	afx_msg void OnBnClickedButtonPdbOpen();
	afx_msg void OnBnClickedButtonSdsOpen();
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
