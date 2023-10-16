// SymRecvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SymRecv.h"
#include "SymRecvDlg.h"
#include "../../SyserApp/Source/SourceDebug.h"
#include "../../SyserApp/Source/NoPDBSymbol.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_UPDATE_DOWNLOAD_STATE			WM_USER+0x200

// CSymRecvDlg dialog

bool CSymRecvDlg::InitDbgHelp()
{
	m_DbgHelpModule = LoadLibrary("DbgHelp.dll");
	if(m_DbgHelpModule==NULL)
		return false;
	m_SymFindFileInPath =(fpSymFindFileInPath) GetProcAddress(m_DbgHelpModule,"SymFindFileInPath");
	m_SymSetOptions = (fpSymSetOptions)GetProcAddress(m_DbgHelpModule,"SymSetOptions");
	m_SymGetOptions = (fpSymGetOptions)GetProcAddress(m_DbgHelpModule,"SymGetOptions");
	return true;
}

CSymRecvDlg::CSymRecvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSymRecvDlg::IDD, pParent)
	, m_strSymSite(_T(""))
	, m_strPDBPath(_T(""))
	, m_strSDSPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_SDSSavePathIndex=0;
	m_PDBSavePathIndex=0;
	m_GetSymbolThread=false;
	m_Stop=false;

	InitializeCriticalSection(&m_CriticalSection);
}

CSymRecvDlg::~CSymRecvDlg()
{
	DeleteCriticalSection(&m_CriticalSection);	
}

void CSymRecvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SYM_SITE, m_strSymSite);
	DDV_MaxChars(pDX, m_strSymSite, 260);
	DDX_Text(pDX, IDC_EDIT_PDB_PATH, m_strPDBPath);
	DDV_MaxChars(pDX, m_strPDBPath, 260);
	DDX_Text(pDX, IDC_EDIT_SDS_PATH, m_strSDSPath);
	DDV_MaxChars(pDX, m_strSDSPath, 260);
	DDX_Control(pDX, IDC_LIST_MODULE, m_ModuleList);
}

BEGIN_MESSAGE_MAP(CSymRecvDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_GET_SYM, OnBnClickedButtonGetSym)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_PDB, OnBnClickedButtonBrowsePdb)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_SDS, OnBnClickedButtonBrowseSds)
	ON_BN_CLICKED(IDC_BUTTON_PDB_OPEN, OnBnClickedButtonPdbOpen)
	ON_BN_CLICKED(IDC_BUTTON_SDS_OPEN, OnBnClickedButtonSdsOpen)
END_MESSAGE_MAP()


// CSymRecvDlg message handlers

BOOL CSymRecvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(InitDbgHelp()==false)
		return FALSE;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_ModuleList.InsertColumn(0,"FileName",LVCFMT_LEFT,250);
	m_ModuleList.InsertColumn(1,"Status",LVCFMT_LEFT,100);

	m_strSymSite = theApp.m_strSymSite;
	m_strPDBPath = theApp.m_strPDBPath;
	m_strSDSPath = theApp.m_strSDSPath;
	UpdateData(FALSE);
	GetDlgItem(IDC_BUTTON_ADD)->GetFocus();

	ShowWindow(SW_NORMAL);	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSymRecvDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSymRecvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSymRecvDlg::OnBnClickedButtonAdd()
{
	CHAR szFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hInstance;
	OpenFileName.hwndOwner = theApp.GetMainWnd()->m_hWnd;
	OpenFileName.lpstrFilter = "Execute Files\0*.exe;*.dll;*.cpl;*.sys;*.scr;*.ocx\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	*szFileName = 0;
	if(GetOpenFileName(&OpenFileName)==false)
		return;

	WORKFILELIST::IT FindIT;
	FindIT = m_CurrentFileList.InsertUnique(szFileName);
	if(FindIT!=m_CurrentFileList.End())
	{
		(*FindIT).FileName = FindIT.Key();
		m_ModuleList.InsertItem(0,szFileName);
		m_ModuleList.SetItemData(0,0);
	}
}

void CSymRecvDlg::OnBnClickedButtonRemove()
{
	int Index;
	CHAR Name[MAX_FN_LEN];
	WORKFILELIST::IT FindIT;
	Index = m_ModuleList.GetNextItem(-1,LVNI_SELECTED);
	if(Index==-1)
		return;	
	m_ModuleList.GetItemText(Index,0,Name,MAX_FN_LEN);
	FindIT = m_CurrentFileList.Find(Name);
	if(FindIT!=m_CurrentFileList.End())
	{
		m_CurrentFileList.Remove(FindIT);
	}
	m_ModuleList.DeleteItem(Index);
}

void CSymRecvDlg::OnBnClickedButtonGetSym()
{
	PDBSAVEPATHLIST::IT PDBIT;
	SDSSAVEPATHLIST::IT SDSIT;
	SYMFINDPATHLIST::IT SYMIT;
	STPATHNAME stPDBName;
	STPATHNAME stSDSName;
	STPATHNAME stSymFindPathName;
	WORKFILELIST::IT BeginIT,EndIT;

	UpdateData(TRUE);

	EnterCriticalSection(&m_CriticalSection);

	stSymFindPathName.Name = m_strSymSite;
	SYMIT = m_SymFindPathList.Find(stSymFindPathName);
	if(SYMIT==m_SymFindPathList.End())
	{
		m_SymFindPathList.Append(stSymFindPathName);
	}
	else
	{
		stSymFindPathName=*SYMIT;
	}

	stPDBName.Name = m_strPDBPath;
	PDBIT = m_PDBSavePathList.Find(stPDBName);
	if(PDBIT==m_PDBSavePathList.End())
	{
		m_PDBSavePathList.Append(stPDBName);
	}
	else
	{
		stPDBName=*PDBIT;
	}
	
	stSDSName.Name = m_strSDSPath;
	SDSIT = m_SDSSavePathList.Find(stSDSName);
	if(SDSIT==m_SDSSavePathList.End())
	{
		m_PDBSavePathList.Append(stSDSName);
	}
	else
	{
		stSDSName=*SDSIT;
	}
	BeginIT=m_CurrentFileList.Begin();
	EndIT=m_CurrentFileList.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		if((*BeginIT).Stat==0)
		{
			(*BeginIT).Stat=1;
			(*BeginIT).PDBSavePath=stPDBName.Name;
			(*BeginIT).SDSSavePath=stSDSName.Name;
			(*BeginIT).FindPath=stSymFindPathName.Name;
		}
	}
	if(m_GetSymbolThread==false)
	{
		::CreateThread(NULL,0x100000,GetSymbolThread,this,0,&m_GetSymbolThreadID);
	}
	LeaveCriticalSection(&m_CriticalSection);
}

void CSymRecvDlg::OnBnClickedButtonStop()
{
	m_Stop=true;
}

void CSymRecvDlg::OnBnClickedButtonReset()
{
	m_strSymSite = theApp.m_strSymSite;
	m_strPDBPath = theApp.m_strPDBPath;
	m_strSDSPath = theApp.m_strSDSPath;
	UpdateData(FALSE);
}

void CSymRecvDlg::OnBnClickedButtonBrowsePdb()
{
	CHAR szDir[MAX_FN_LEN];
	bool Result;
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;
	if(SHGetMalloc(&pMalloc) != NOERROR)
		return;
	bi.hwndOwner=theApp.GetMainWnd()->m_hWnd;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=NULL;
	bi.lpszTitle="Select Directory";
	bi.ulFlags=BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn=NULL;
	bi.lParam=0;
	Result = false;
	if((pidl=SHBrowseForFolder(&bi)) != NULL)
	{
		Result = SHGetPathFromIDList(pidl, szDir)!=FALSE;
		pMalloc->Free(pidl);
	}
	pMalloc->Release();
	if(Result)
	{
		m_strPDBPath = szDir;
		UpdateData(FALSE);
	}
}

void CSymRecvDlg::OnBnClickedButtonBrowseSds()
{
	CHAR szDir[MAX_FN_LEN];
	bool Result;
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;
	if(SHGetMalloc(&pMalloc) != NOERROR)
		return;
	bi.hwndOwner=theApp.GetMainWnd()->m_hWnd;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=NULL;
	bi.lpszTitle="Select Directory";
	bi.ulFlags=BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn=NULL;
	bi.lParam=0;
	Result = false;
	if((pidl=SHBrowseForFolder(&bi)) != NULL)
	{
		Result = SHGetPathFromIDList(pidl, szDir)!=FALSE;
		pMalloc->Free(pidl);
	}
	pMalloc->Release();
	if(Result)
	{
		m_strSDSPath = szDir;
		UpdateData(FALSE);
	}
}

void CSymRecvDlg::OnBnClickedButtonPdbOpen()
{
	UpdateData(TRUE);
	gpFileIO->CreateDir(m_strPDBPath);
	ShellExecute(NULL,"open","explorer",m_strPDBPath,NULL,SW_NORMAL);
}

void CSymRecvDlg::OnBnClickedButtonSdsOpen()
{
	UpdateData(TRUE);
	gpFileIO->CreateDir(m_strSDSPath);
	ShellExecute(NULL,"open","explorer",m_strSDSPath,NULL,SW_NORMAL);
}

DWORD WINAPI GetSymbolThread(LPVOID lpParameter)
{
	PDBSAVEPATHLIST::IT PDBIT;
	SDSSAVEPATHLIST::IT SDSIT;
	STPATHNAME stPDBName;
	STPATHNAME stSDSName;
	WORKFILELIST::IT BeginIT,EndIT;
	CGetSymbolStat CurSymbolStat;

	CSymRecvDlg* pDlg = (CSymRecvDlg*)lpParameter;
	pDlg->m_GetSymbolThread=true;
	pDlg->m_Stop=false;
	for(;pDlg->m_Stop==false;)
	{
		EnterCriticalSection(&pDlg->m_CriticalSection);
		BeginIT=pDlg->m_CurrentFileList.Begin();
		EndIT=pDlg->m_CurrentFileList.End();
		for(;BeginIT!=EndIT;BeginIT++)
		{
			if((*BeginIT).Stat>=2)
				continue;
			break;
		}
		if(BeginIT==EndIT)
		{
			LeaveCriticalSection(&pDlg->m_CriticalSection);
			pDlg->m_GetSymbolThread=false;
			break;
		}
		if((*BeginIT).Stat==0)
		{
			stPDBName.Name = pDlg->m_strPDBPath;
			PDBIT = pDlg->m_PDBSavePathList.Find(stPDBName);
			if(PDBIT==pDlg->m_PDBSavePathList.End())
			{
				pDlg->m_PDBSavePathList.Append(stPDBName);
			}
			else
			{
				stPDBName=*PDBIT;
			}
			stSDSName.Name = pDlg->m_strSDSPath;
			SDSIT = pDlg->m_SDSSavePathList.Find(stSDSName);
			if(SDSIT==pDlg->m_SDSSavePathList.End())
			{
				pDlg->m_PDBSavePathList.Append(stSDSName);
			}
			else
			{
				stSDSName=*SDSIT;
			}
			(*BeginIT).Stat=1;
			(*BeginIT).PDBSavePath=stPDBName.Name;
			(*BeginIT).SDSSavePath=stSDSName.Name;
		}
		(*BeginIT).Stat=2;
		CurSymbolStat=(*BeginIT);
		LeaveCriticalSection(&pDlg->m_CriticalSection);
		WIN32_FIND_DATA FindData;
		HANDLE hFindHandle;
		hFindHandle = FindFirstFile(CurSymbolStat.PDBSavePath,&FindData);
		if(hFindHandle == INVALID_HANDLE_VALUE)
		{
			CreateDirectory(CurSymbolStat.PDBSavePath,NULL);
		}else
			FindClose(hFindHandle);
		hFindHandle = FindFirstFile(CurSymbolStat.SDSSavePath,&FindData);
		if(hFindHandle == INVALID_HANDLE_VALUE)
		{
			CreateDirectory(CurSymbolStat.SDSSavePath,NULL);
		}else
			FindClose(hFindHandle);
		pDlg->DownLoadSymbol(CurSymbolStat);
	}
	return 0;
}

bool CSymRecvDlg::DownLoadSymbol(CGetSymbolStat& SymbolStat)
{
	CPEFile PEFile;
	DWORD Index;
	PE_DEBUG_MISC DebugMisc;
	PE_DEBUG_PDB DebugPDB;
	PE_DEBUG_CODEVIEW DebugCodeView;
	PPE_DEBUG_DIRECTORY pDebugDirectory;
	PE_DATA_DIR DebugDataDirectory;
	DWORD DebugDirecotryNum=0;
	DWORD Signature;
	BOOL bRet;
	DWORD ErrorCode=0;
	DWORD SymbolFileType = 0xffffffff;
	DWORD ReadLen;
	DWORD PathLen;
	BYTE * Buffer=NULL;
	TList<char*>DeleteFileList;
	char* NoPathFileName;
	char FindPath[MAX_PATH+1];
	char FileName[MAX_PATH+1];
	char FindFileName[MAX_PATH+1];
	char SymbolFileName[MAX_PATH+1];

	memset(&DebugDataDirectory,0,sizeof(PE_DATA_DIR));
	if(PEFile.Open(SymbolStat.FileName)==false)
		return false;
	if(PEFile.GetDataDirectory(6,&DebugDataDirectory)==false)
		goto local_quit;
	if(DebugDataDirectory.VirtualAddress ==0)
		goto local_quit;
	if(DebugDataDirectory.Size>0x10000||DebugDataDirectory.Size==0)
		goto local_quit;
	NoPathFileName = TGetFileName((PCSTR)SymbolStat.FileName);
	PathLen = *(DWORD*)&NoPathFileName-*(DWORD*)&SymbolStat.FileName;
	Buffer=new BYTE[DebugDataDirectory.Size];
	memset(Buffer,0,DebugDataDirectory.Size);
	ReadLen = PEFile.ReadImageMemory(DebugDataDirectory.VirtualAddress+PEFile.m_PEHead.ImageBase,Buffer,DebugDataDirectory.Size);
	if(ReadLen!=DebugDataDirectory.Size)
		goto local_quit;
	pDebugDirectory =(PPE_DEBUG_DIRECTORY) Buffer;
	DebugDirecotryNum = DebugDataDirectory.Size / sizeof(PE_DEBUG_DIRECTORY);
	for(Index = 0; Index<DebugDirecotryNum;Index++)
	{
		if(pDebugDirectory[Index].Type==IMAGE_DEBUG_TYPE_CODEVIEW&&pDebugDirectory[Index].PointerToRawData)
		{
			if(PEFile.ReadFile(pDebugDirectory[Index].PointerToRawData,&Signature,sizeof(Signature))==false)
				continue;
			if(Signature==0x53445352)
			{
				if(PEFile.ReadFile(pDebugDirectory[Index].PointerToRawData,&DebugPDB,sizeof(DebugPDB))==false)
					continue;
				SymbolFileType=3;
			}
			else if(Signature==0x3031424e)
			{
				if(PEFile.ReadFile(pDebugDirectory[Index].PointerToRawData,&DebugCodeView,sizeof(DebugCodeView))==false)
					continue;
				SymbolFileType=2;
			}
			continue;
		}
		if(pDebugDirectory[Index].Type==IMAGE_DEBUG_TYPE_MISC&&pDebugDirectory[Index].PointerToRawData)
		{
			if(PEFile.ReadFile(pDebugDirectory[Index].PointerToRawData,&DebugMisc,sizeof(PE_DEBUG_MISC))==false)
				continue;
			SymbolFileType=1;
			continue;
		}
	}
	SendMessage(WM_UPDATE_DOWNLOAD_STATE,3,(LPARAM)(PCSTR)SymbolStat.FileName);
	sprintf(FindPath,"srv*%s*%s",SymbolStat.PDBSavePath,SymbolStat.FindPath);
local_001:
	switch(SymbolFileType)
	{
	case 1:
		TStrCpy(FileName,DebugMisc.Data);
		bRet = m_SymFindFileInPath(0,FindPath,FileName,(PVOID)(*(DWORD**)&PEFile.m_PEHead.TimeDateStamp),PEFile.m_PEHead.SizeOfImage,0,SSRVOPT_DWORD,FindFileName,NULL,0);
		if(bRet)
		{
			if(GetDebugCodeviewByDbg(FindFileName,&DebugCodeView))
			{
				memset(FileName,0,sizeof(FileName));
				TStrNCpy(FileName,(PCSTR)SymbolStat.FileName,PathLen);
				TStrCat(FileName,TGetFileName(FindFileName));
				if(TStrICmp(FileName,FindFileName))
				{
					if(CopyFile(FindFileName,FileName,false))
					{
						char* DeleteFileName = new char[TStrLen(FileName)+1];
						TStrCpy(DeleteFileName,FileName);
						DeleteFileList.Append(DeleteFileName);
					}
				}
				SymbolFileType=2;
				goto local_001;
			}
		}
		break;
	case 2:
		TStrCpy(FileName,DebugCodeView.Name);
		bRet = m_SymFindFileInPath(0,FindPath,FileName,(PVOID)(*(DWORD**)&DebugCodeView.TimeDateStamp),DebugCodeView.Age,0,SSRVOPT_DWORD,FindFileName,NULL,0);
		break;
	case 3:
		TStrCpy(FileName,DebugPDB.Name);
		bRet = m_SymFindFileInPath(0,FindPath,FileName,&DebugPDB.Guid,DebugPDB.Age,0,SSRVOPT_GUIDPTR,FindFileName,NULL,0);
		break;
	default:
		bRet=false;
		break;
	}
	if(bRet==false)
	{
		SendMessage(WM_UPDATE_DOWNLOAD_STATE,2,(LPARAM)(PCSTR)SymbolStat.FileName);
	}
	else
	{
		memset(FileName,0,sizeof(FileName));
		TStrNCpy(FileName,(PCSTR)SymbolStat.FileName,PathLen);
		TStrCat(FileName,TGetFileName(FindFileName));
		if(TStrICmp(FileName,FindFileName))
		{
			if(CopyFile(FindFileName,FileName,false))
			{
				char* DeleteFileName = new char[TStrLen(FileName)+1];
				TStrCpy(DeleteFileName,FileName);
				DeleteFileList.Append(DeleteFileName);
			}
		}
		SendMessage(WM_UPDATE_DOWNLOAD_STATE,4,(LPARAM)(PCSTR)SymbolStat.FileName);
		if(TranslateSymbolFile(SymbolFileType,SymbolStat.FileName,SymbolFileName))
		{
			memset(FileName,0,sizeof(FileName));
			TStrCpy(FileName,(PCSTR)SymbolStat.SDSSavePath);
			if(FileName[TStrLen(FileName)-1]!=PATH_SEPARATOR_CHAR)
				TStrCat(FileName,"\\");
			TStrCat(FileName,TGetFileName(SymbolFileName));
			if(TStrICmp(SymbolFileName,FileName))
			{
				DeleteFile(FileName);
				MoveFile(SymbolFileName,FileName);
			}
		}
		TList<char*>::IT BeginIT,EndIT;
		BeginIT=DeleteFileList.Begin();
		EndIT=DeleteFileList.End();
		for(;BeginIT!=EndIT;BeginIT++)
		{
			BOOL bretf=false;
			bretf = ::DeleteFile(*BeginIT);
			if(bretf==false)
				::MessageBox(NULL,*BeginIT,"Delete File Error!",MB_OK);
			delete *BeginIT;
		}
		DeleteFileList.Clear();
		SendMessage(WM_UPDATE_DOWNLOAD_STATE,1,(LPARAM)(PCSTR)SymbolStat.FileName);
	}
local_quit:
	if(Buffer)
		delete []Buffer;
	PEFile.Close();
	return true;
}

bool CSymRecvDlg::TranslateSymbolFile(IN int Type,IN PCSTR pExeFileName,OUT char* pSymbolFileName)
{
	if(Type!=1)
	{
		CSourceDebug PDBExplorer;
		return PDBExplorer.TranslateSymbolFile(pExeFileName,pSymbolFileName);
	}
	CNoPDBSymbol NoPDBSymbol;
	NoPDBSymbol.Init();
	return NoPDBSymbol.TranslateSymbolFile(pExeFileName,pSymbolFileName);
}

bool CSymRecvDlg::GetDebugCodeviewByDbg(char* DbgFileName,PPE_DEBUG_CODEVIEW DebugCodeView)
{
	DWORD Signature=('0'<<24)+('1'<<16)+('B'<<8)+'N';
	DWORD i;
	bool bRet=false;
	CImageFile ImageFile;
	BYTE *Buf=NULL;

	if(ImageFile.Open(DbgFileName)==false)
		return false;
	if(ImageFile.m_FileSize<=0x100000*10&&ImageFile.m_FileSize>100)
	{
		Buf = new BYTE[ImageFile.m_FileSize];
		if(ImageFile.ReadFile(0,Buf,ImageFile.m_FileSize)==false)
		{
			goto local_quit;
		}
		for(i = 0;i < ImageFile.m_FileSize-3;i++)
		{
			if(*(DWORD*)&Buf[i]==Signature)
			{
				bRet=true;
				*DebugCodeView =*(PPE_DEBUG_CODEVIEW)&Buf[i];
				break;
			}
		}
	}	
local_quit:
	if(Buf)
		delete []Buf;
	ImageFile.Close();
	return bRet;
}

bool CSymRecvDlg::OnUpdateDownLoadState(WPARAM wParam,LPARAM lParam)
{
	int ItemCount,Index;
	CHAR szFileName[MAX_FN_LEN];
	ItemCount = m_ModuleList.GetItemCount();
	for(Index=0;Index<ItemCount;Index++)
	{
		m_ModuleList.GetItemText(Index,0,szFileName,MAX_FN_LEN);
		if(TStrCmp(szFileName,(PCSTR)lParam)==0)
			break;
	}
	if(Index>=ItemCount)
		return false;
	switch(wParam)
	{
	case 1:
		m_ModuleList.SetItemText(Index,1,"Success");
		break;
	case 2:
		m_ModuleList.SetItemText(Index,1,"Fail !!!");
		break;
	case 3:
		m_ModuleList.SetItemText(Index,1,"Downloading.");
		break;
	case 4:
		m_ModuleList.SetItemText(Index,1,"Analyzing Symbol file...");
		break;
	default:
		break;
	}
	return true;
}


BOOL CSymRecvDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if(message == WM_UPDATE_DOWNLOAD_STATE)
	{
		OnUpdateDownLoadState(wParam,lParam);
		return true;
	}
	return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}
