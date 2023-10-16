#ifndef _SYMBOLDOWNLOADER_H_
#define _SYMBOLDOWNLOADER_H_

typedef struct _STPATHNAME
{
	char* Name;
	bool operator ==(const struct _STPATHNAME dest)const
	{
		return TStrCmp(Name,dest.Name)==0;
	}
}STPATHNAME,*PSTPATHNAME;

class CGetSymbolStat
{
public:	
	DWORD Stat;
	char* SDSSavePath;
	char* PDBSavePath;
	char* FindPath;
	char* FileName;
	CGetSymbolStat()
	{
		Stat=0;
		SDSSavePath=NULL;
		PDBSavePath=NULL;
		FindPath=NULL;
		FileName=NULL;
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
class CSymbolDownloaderDlg:public CWispForm
{
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
	CWispButton* m_AddFileButton;
	CWispButton* m_DelFileButton;
	CWispButton* m_GetSymbolButton;
	CWispButton* m_StopButton;
	CWispList* m_FileList;
	CWispEdit* m_SymbolSiteEdit;
	CWispButton* m_SymbolSiteResetButton;
	CWispEdit* m_PDBSavePathEdit;
	CWispButton* m_BrowsePDBSavePathButton;
	CWispEdit* m_SDSSavePathEdit;
	CWispButton* m_BrowseSDSSavePathButton;
	CWispStaticStr*m_SymbolSiteStatic;
	CWispStaticStr*m_PDBPathStatic;
	CWispStaticStr*m_SDSPathStatic;
	CWispStaticDIB*m_MainStaticDIB;
public:
	CSymbolDownloaderDlg(void);
	~CSymbolDownloaderDlg(void);
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG(OnResize);
	//DECLARE_WISP_MSG(OnTimer)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnCmdUpdateDownLoadState)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventButtonResetSymbolSite)
	DECLARE_WISP_MSG_EVENT(OnEventButtonBrowsePDBSavePath)
	DECLARE_WISP_MSG_EVENT(OnEventButtonBrowseSDSSavePath)
	DECLARE_WISP_MSG_EVENT(OnEventButtonStop)
	DECLARE_WISP_MSG_EVENT(OnEventButtonAddFile)
	DECLARE_WISP_MSG_EVENT(OnEventButtonDelFile)
	DECLARE_WISP_MSG_EVENT(OnEventButtonGetSymbol)
	
	bool DownLoadSymbol(CGetSymbolStat& SymbolStat );
	bool GetDebugCodeviewByDbg(char* DbgFileName,PPE_DEBUG_CODEVIEW DebugCodeView);
	bool TranslateSymbolFile(IN int Type,IN char* pExeFileName,OUT char* pSymbolFileName);
	bool InitDbgHelp();
	void ReleaseDbgHelp();
	bool LoadDbgHelpApi();
	//CWispProgress m_Progress;
};

DWORD WINAPI GetSymbolThread(LPVOID lpParameter);
#endif //_SYMBOLDOWNLOADER_H_