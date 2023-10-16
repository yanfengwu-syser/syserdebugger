#include "StdAfx.h"
#include "SymbolDownloader.h"
#include "NoPDBSymbol.h"
#ifdef CODE_OS_WIN
#include <shlobj.h>
#include "SyserApp.h"
#endif

char* CSymbolDownloaderDlg::m_SymbolSiteDefaultPath="http://msdl.microsoft.com/download/symbols";
enum CSymbolDownloaderDlg::WISP_FORM_ID
{
	CMD_ID_BUTTON_ADDFILE = WISP_ID_USER_START,
		CMD_ID_BUTTON_DELFILE,
		CMD_ID_BUTTON_GETSYMBOL,
		CMD_ID_BUTTON_STOP,
		CMD_ID_LIST_FILE,
		CMD_ID_EDIT_SYMBOLSITE,
		CMD_ID_BUTTON_RESETSYMBOLSITE,
		CMD_ID_EDIT_PDBSAVEPATH,
		CMD_ID_BUTTON_BROWSEPDBSAVEPATH,
		CMD_ID_EDIT_SDSSAVEPATH,
		CMD_ID_BUTTON_BROWSESDSSAVEPATH,
};
WISP_MSG_MAP_BEGIN(CSymbolDownloaderDlg)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
//WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

//WISP_MSG_CMD_MAP_BEGIN(CSymbolDownloaderDlg)
//WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CSymbolDownloaderDlg)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_RESETSYMBOLSITE,OnEventButtonResetSymbolSite)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_BROWSEPDBSAVEPATH,OnEventButtonBrowsePDBSavePath)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_BROWSESDSSAVEPATH,OnEventButtonBrowseSDSSavePath)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_STOP,OnEventButtonStop)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_ADDFILE,OnEventButtonAddFile)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_DELFILE,OnEventButtonDelFile)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_GETSYMBOL,OnEventButtonGetSymbol)
WISP_MSG_EVENT_MAP_END

WISP_FORM_RES_ITEM CSymbolDownloaderDlg::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,680,600},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL//WSTR("Symbol Downloader")
	},
	{
		WISP_CTRL_BUTTON,
		{520,40,76,24},
		CMD_ID_BUTTON_ADDFILE,
		WISP_BS_NORMAL,
		WSTR("Add File(s)"),
		NULL,
		NULL//WSTR("增加文件到列表")
	},
	{
		WISP_CTRL_BUTTON,
		{520,75,76,24},
		CMD_ID_BUTTON_DELFILE,
		WISP_BS_NORMAL,
		WSTR("Del File(s)"),
		NULL,
		NULL//WSTR("删除列表中被选种的文件")
	},
	{
		WISP_CTRL_BUTTON,
		{520,110,76,24},
		CMD_ID_BUTTON_GETSYMBOL,
		WISP_BS_NORMAL,
		WSTR("Get Symbols"),
		NULL,
		NULL//WSTR("下载与列表中文件相关的符号文件")
	},
	{
		WISP_CTRL_BUTTON,
		{520,145,76,24},
		CMD_ID_BUTTON_GETSYMBOL,
		CMD_ID_BUTTON_STOP,
		WSTR("Stop"),
		NULL,
		NULL//WSTR("下载与列表中文件相关的符号文件")
	},
	{
		WISP_CTRL_LIST,
		{16,40,500,360},
		CMD_ID_LIST_FILE,
		WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER,
		NULL,
		NULL,
		NULL//WSTR("文件列表")
	},
	{
		WISP_CTRL_STATIC_STRING,
		{36,440,68,16},
		0xffffffff,
		WISP_WS_NULL,
		WSTR("Symbol Site"),
		NULL,
		NULL//WSTR("符号服务器的地址")
	},
	{
		WISP_CTRL_STATIC_STRING,
		{36,467,68,16},
		0xffffffff,
		WISP_WS_NULL,
		WSTR("Local PDB"),
		NULL,
		NULL//WSTR("保存符号文件的本地目录")
	},
	{
		WISP_CTRL_STATIC_STRING,
		{36,494,68,16},
		0xffffffff,
		WISP_WS_NULL,
		WSTR("Path to SDS"),
		NULL,
		NULL//WSTR("Syser Debugger 符号文件保存目录")
	},
	{
		WISP_CTRL_EDIT,
		{110,435,370,24},
		CMD_ID_EDIT_SYMBOLSITE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL//WSTR("break condition when break point touched")
	},
	{
		WISP_CTRL_EDIT,
		{110,462,370,24},
		CMD_ID_EDIT_PDBSAVEPATH,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL//WSTR("break condition when break point touched")
	},
	{
		WISP_CTRL_EDIT,
		{110,489,370,24},
		CMD_ID_EDIT_SDSSAVEPATH,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL//WSTR("break condition when break point touched")
	},
	{
		WISP_CTRL_BUTTON,
		{490,435,76,24},
		CMD_ID_BUTTON_RESETSYMBOLSITE,
		WISP_BS_NORMAL,
		WSTR("Reset"),
		NULL,
		NULL//WSTR("设置为缺省值")
	},
	{
		WISP_CTRL_BUTTON,
		{490,462,76,24},
		CMD_ID_BUTTON_BROWSEPDBSAVEPATH,
		WISP_BS_NORMAL,
		WSTR("Browse"),
		NULL,
		NULL//WSTR("删除列表中被选种的文件")
	},
	{
		WISP_CTRL_BUTTON,
		{490,489,76,24},
		CMD_ID_BUTTON_BROWSESDSSAVEPATH,
		WISP_BS_NORMAL,
		WSTR("Browse"),
		NULL,
		NULL//WSTR("下载与列表中文件相关的符号文件")
	},
	{WISP_CTRL_NULL}
};

CSymbolDownloaderDlg::CSymbolDownloaderDlg()
{
	m_pFormRes = m_FormRes;
	memset(m_SymbolSitePath,0,sizeof(m_SymbolSitePath));
	strcpy(m_SymbolSitePath,m_SymbolSiteDefaultPath);
	m_SDSSavePathIndex=0;
	m_PDBSavePathIndex=0;
	memset(m_SDSSavePath,0,sizeof(m_SDSSavePath));
	memset(m_PDBSavePath,0,sizeof(m_PDBSavePath));
	m_GetSymbolThread=false;
	m_Stop=false;
	InitializeCriticalSection(&m_CriticalSection);
}
CSymbolDownloaderDlg::~CSymbolDownloaderDlg()
{

}
bool CSymbolDownloaderDlg::OnEventButtonResetSymbolSite(IN WISP_MSG*pMsg)
{
	WCHAR* Text=new WCHAR[TStrLen(m_SymbolSiteDefaultPath)+1];
	TStrCpy(Text,m_SymbolSiteDefaultPath);
	TStrCpy(m_SymbolSitePath,m_SymbolSiteDefaultPath);
	m_SymbolSiteEdit->SetWindowText(Text);
	m_SymbolSiteEdit->Update();
	return true;
}
int CALLBACK BrowsePDBSavePathCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	char PathName[1024];
	BOOL bRet;
	LPITEMIDLIST lpItemIDList=NULL;
	switch(uMsg) {
	case BFFM_INITIALIZED:
		SendMessage(hwnd,BFFM_SETSELECTIONA,1,lpData);
		break;
	case BFFM_SELCHANGED:
		bRet = SHGetPathFromIDList((LPITEMIDLIST)lpData,PathName);
		if(bRet)
		{
			SendMessage(hwnd,BFFM_SETSTATUSTEXTA,0,(LPARAM)PathName);
		}
		break;
	case BFFM_VALIDATEFAILED:
		return 1;
	}
	return 0;
}
int CALLBACK BrowseCallbackSDSSavePathProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	char PathName[1024];
	BOOL bRet;
	LPITEMIDLIST lpItemIDList=NULL;
	switch(uMsg) {
	case BFFM_INITIALIZED:
		SendMessage(hwnd,BFFM_SETSELECTIONA,1,lpData);
		break;
	case BFFM_SELCHANGED:
		bRet = SHGetPathFromIDList((LPITEMIDLIST)lpData,PathName);
		if(bRet)
		{
			SendMessage(hwnd,BFFM_SETSTATUSTEXTA,0,(LPARAM)PathName);
		}
		break;
	case BFFM_VALIDATEFAILED:
		return 1;
	}
	return 0;
	return 0;
}

bool CSymbolDownloaderDlg::OnEventButtonBrowsePDBSavePath(IN WISP_MSG*pMsg)
{
	char PathName[1024];
	BOOL bRet;
	LPITEMIDLIST lpItemIDList=NULL;
	char DisplayName[]="c:\\";
	BROWSEINFO BrowseInfo;
	LPMALLOC pMalloc;
	memset(&BrowseInfo,0,sizeof(BROWSEINFO));
	if(SHGetMalloc(&pMalloc)==E_FAIL)
		return true;
	BrowseInfo.hwndOwner=gpSyser->m_hLocalWnd;;
	BrowseInfo.pszDisplayName=DisplayName;
	BrowseInfo.lpszTitle="选择一个下载 PDB 文件的存放目录";
	BrowseInfo.pidlRoot=NULL;
	BrowseInfo.ulFlags=	BIF_VALIDATE|BIF_EDITBOX|BIF_RETURNFSANCESTORS|BIF_STATUSTEXT;
	BrowseInfo.lpfn=BrowsePDBSavePathCallbackProc;
	TStrCpy(m_PDBSavePath,"C:\\windows");
	BrowseInfo.lParam=(LPARAM)m_PDBSavePath;
	lpItemIDList = SHBrowseForFolder(&BrowseInfo);
	if(lpItemIDList==NULL)
		return true;
	bRet = SHGetPathFromIDList(lpItemIDList,PathName);
	pMalloc->Free(lpItemIDList);
	pMalloc->Release();
	if(bRet)
	{
		WCHAR* pText = new WCHAR[TStrLen(PathName)+1];
		TStrCpy(pText,PathName);
		m_PDBSavePathEdit->SetWindowText(pText)	;
		delete []pText;
	}
	return true;
}
bool CSymbolDownloaderDlg::OnEventButtonBrowseSDSSavePath(IN WISP_MSG*pMsg)
{
	LPITEMIDLIST lpItemIDList=NULL;
	char PathName[1024];
	BOOL bRet;
	char DisplayName[]="";
	BROWSEINFO BrowseInfo;
	LPMALLOC pMalloc;
	memset(&BrowseInfo,0,sizeof(BROWSEINFO));
	if(SHGetMalloc(&pMalloc)==E_FAIL)
		return true;
	BrowseInfo.hwndOwner=gpSyser->m_hLocalWnd;;
	BrowseInfo.pszDisplayName=DisplayName;
	BrowseInfo.lpszTitle="选择一个转换 SDS 文件的存放目录";
	BrowseInfo.pidlRoot=NULL;
	BrowseInfo.ulFlags=	BIF_VALIDATE|BIF_EDITBOX|BIF_RETURNFSANCESTORS|BIF_STATUSTEXT;
	BrowseInfo.lpfn=BrowseCallbackSDSSavePathProc;
	TStrCpy(m_SDSSavePath,"c:\\windows");
	BrowseInfo.lParam=(LPARAM)m_SDSSavePath;
	lpItemIDList = SHBrowseForFolder(&BrowseInfo);
	if(lpItemIDList==NULL)
		return true;
	bRet = SHGetPathFromIDList(lpItemIDList,PathName);
	pMalloc->Free(lpItemIDList);
	pMalloc->Release();
	if(bRet)
	{
		WCHAR* pText = new WCHAR[TStrLen(PathName)+1];
		TStrCpy(pText,PathName);
		m_SDSSavePathEdit->SetWindowText(pText)	;
		delete []pText;
	}
	return true;
}
bool CSymbolDownloaderDlg::OnEventButtonAddFile(IN WISP_MSG*pMsg)
{

	char szBuffer[MAX_FN_LEN]="Binaries Files|*.exe;*.dll;*.cpl;*.sys;*.scr;*.ocx|All Files|*.*|";
	char szFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = gpSyser->m_hLocalInst;
	OpenFileName.hwndOwner = gpSyser->m_hLocalWnd;
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
	if(GetOpenFileName(&OpenFileName)==false)
	{
		gpSyser->UnlockTimer();
		return true;
	}
	gpSyser->UnlockTimer();
	WORKFILELIST::IT FindIT;
	HANDLE hItem;
	FindIT = m_CurrentFileList.InsertUnique(szFileName);
	if(FindIT!=m_CurrentFileList.End())
	{
		(*FindIT).FileName = FindIT.Key();
		hItem = m_FileList->InsertItemA(szFileName);
		m_FileList->SetItemData(hItem,1,0);
	}
	/*
	FindIT = m_CurrentFileList.Find(szFileName);
	if(FindIT==m_CurrentFileList.End())
	{
		m_CurrentFileList.InsertUnique()
		m_CurrentFileList.Append(szFileName);
	}
	*/
	Update();
	return true;
}
bool CSymbolDownloaderDlg::OnEventButtonStop(IN WISP_MSG*pMsg)
{
	m_Stop=true;
	return true;
}
bool CSymbolDownloaderDlg::OnEventButtonDelFile(IN WISP_MSG*pMsg)
{
	HANDLE hItem,hNextItem;
	WCHAR* pFileName;
	char* Name;
	WORKFILELIST::IT FindIT;
	hItem = m_FileList->GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	do 
	{
		pFileName = m_FileList->GetItemText(hItem);
		Name = new char[TStrLen(pFileName)+1];
		TStrCpy(Name,pFileName);
		FindIT = m_CurrentFileList.Find(Name);
		if(FindIT!=m_CurrentFileList.End())
			m_CurrentFileList.Remove(FindIT);
		hNextItem = m_FileList->GetNextItem(hItem,WISP_WLIS_SELECTED);
		m_FileList->RemoveItem(hItem);
		hItem=hNextItem;
		delete Name;
	} while(hItem);
	Update();
	return true;
}


DWORD WINAPI GetSymbolThread(LPVOID lpParameter)
{
	PDBSAVEPATHLIST::IT PDBIT;
	SDSSAVEPATHLIST::IT SDSIT;
	STPATHNAME stPDBName;
	STPATHNAME stSDSName;
	WORKFILELIST::IT BeginIT,EndIT;
	WCHAR* PathName;
	char* pStr;
	CGetSymbolStat CurSymbolStat;
	
	CSymbolDownloaderDlg* pDlg = (CSymbolDownloaderDlg*)lpParameter;
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
			PathName = pDlg->m_PDBSavePathEdit->GetWindowText();
			pStr = new char[TStrLen(PathName)+1];
			stPDBName.Name = pStr;
			TStrCpy(pStr,PathName);
			PDBIT = pDlg->m_PDBSavePathList.Find(stPDBName);
			if(PDBIT==pDlg->m_PDBSavePathList.End())
			{
				pDlg->m_PDBSavePathList.Append(stPDBName);
			}
			else
			{
				delete []pStr;
				stPDBName=*PDBIT;
			}
			PathName = pDlg->m_SDSSavePathEdit->GetWindowText();
			pStr = new char[TStrLen(PathName)+1];
			stSDSName.Name = pStr;
			TStrCpy(pStr,PathName);
			SDSIT = pDlg->m_SDSSavePathList.Find(stSDSName);
			if(SDSIT==pDlg->m_SDSSavePathList.End())
			{
				pDlg->m_PDBSavePathList.Append(stSDSName);
			}
			else
			{
				delete []pStr;
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
		if(INVALID_HANDLE_VALUE)
		{
			CreateDirectory(CurSymbolStat.PDBSavePath,NULL);
		}else
			FindClose(hFindHandle);
		hFindHandle = FindFirstFile(CurSymbolStat.SDSSavePath,&FindData);
		if(INVALID_HANDLE_VALUE)
		{
			CreateDirectory(CurSymbolStat.SDSSavePath,NULL);
		}else
			FindClose(hFindHandle);
		pDlg->DownLoadSymbol(CurSymbolStat);
	}
	return 0;
}

bool CSymbolDownloaderDlg::DownLoadSymbol(CGetSymbolStat& SymbolStat)
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

	
	memset(&DebugDataDirectory,0,sizeof(PE_DATA_DIR));
	if(PEFile.Open(SymbolStat.FileName)==false)
		return false;
	if(PEFile.GetDataDirectory(6,&DebugDataDirectory)==false)
		goto local_quit;
	if(DebugDataDirectory.VirtualAddress ==0)
		goto local_quit;
	if(DebugDataDirectory.Size>0x10000||DebugDataDirectory.Size==0)
		goto local_quit;
	NoPathFileName = TGetFileName(SymbolStat.FileName);
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
				SymbolFileType=2;
				TStrNCpy(FileName,SymbolStat.FileName,PathLen+1);
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
		
		ErrorCode = GetLastError();
		sprintf(FileName,"%08x %d \n",ErrorCode,ErrorCode);
		::MessageBox(NULL,FileName,FileName,MB_OK);
	}
	else
	{
		TStrNCpy(FileName,SymbolStat.FileName,PathLen+1);
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
	}
local_quit:
	if(Buffer)
		delete []Buffer;
	PEFile.Close();
	return true;
}
bool CSymbolDownloaderDlg::TranslateSymbolFile(IN int Type,IN char* pExeFileName,OUT char* pSymbolFileName)
{
	if(Type==1)
	{
		CSourceDebug PDBExplorer;
		return PDBExplorer.TranslateSymbolFile(pExeFileName,pSymbolFileName);
	}
	CNoPDBSymbol NoPDBSymbol;
	NoPDBSymbol.Init();
	return NoPDBSymbol.TranslateSymbolFile(pExeFileName,pSymbolFileName);
}
bool CSymbolDownloaderDlg::GetDebugCodeviewByDbg(char* DbgFileName,PPE_DEBUG_CODEVIEW DebugCodeView)
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
bool CSymbolDownloaderDlg::OnEventButtonGetSymbol(IN WISP_MSG*pMsg)
{
	PDBSAVEPATHLIST::IT PDBIT;
	SDSSAVEPATHLIST::IT SDSIT;
	SYMFINDPATHLIST::IT SYMIT;
	STPATHNAME stPDBName;
	STPATHNAME stSDSName;
	STPATHNAME stSymFindPathName;
	WORKFILELIST::IT BeginIT,EndIT;
	WCHAR* PathName;
	char* pStr;
	
	EnterCriticalSection(&m_CriticalSection);
	PathName = m_SymbolSiteEdit->GetWindowText();
	pStr = new char[TStrLen(PathName)+1];
	stSymFindPathName.Name = pStr;
	TStrCpy(pStr,PathName);
	SYMIT = m_SymFindPathList.Find(stSymFindPathName);
	if(SYMIT==m_SymFindPathList.End())
	{
		m_SymFindPathList.Append(stSymFindPathName);
	}
	else
	{
		delete []pStr;
		stSymFindPathName=*SYMIT;
	}

	PathName = m_PDBSavePathEdit->GetWindowText();
	pStr = new char[TStrLen(PathName)+1];
	stPDBName.Name = pStr;
	TStrCpy(pStr,PathName);
	PDBIT = m_PDBSavePathList.Find(stPDBName);
	if(PDBIT==m_PDBSavePathList.End())
	{
		m_PDBSavePathList.Append(stPDBName);
	}
	else
	{
		delete []pStr;
		stPDBName=*PDBIT;
	}
	PathName = m_SDSSavePathEdit->GetWindowText();
	pStr = new char[TStrLen(PathName)+1];
	stSDSName.Name = pStr;
	TStrCpy(pStr,PathName);
	SDSIT = m_SDSSavePathList.Find(stSDSName);
	if(SDSIT==m_SDSSavePathList.End())
	{
		m_PDBSavePathList.Append(stSDSName);
	}
	else
	{
		delete []pStr;
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
	return true;
}
bool CSymbolDownloaderDlg::OnFormCreate(IN WISP_MSG*pMsg)
{
	InitDbgHelp();
	m_AddFileButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_ADDFILE);
	m_DelFileButton =(CWispButton*)GetFormItem(CMD_ID_BUTTON_DELFILE);
	m_GetSymbolButton =(CWispButton*)GetFormItem(CMD_ID_BUTTON_GETSYMBOL);
	m_FileList = (CWispList*)GetFormItem(CMD_ID_LIST_FILE);
	m_SymbolSiteEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_SYMBOLSITE);
	m_SymbolSiteResetButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_RESETSYMBOLSITE);
	m_PDBSavePathEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_PDBSAVEPATH);
	m_BrowsePDBSavePathButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_BROWSEPDBSAVEPATH);
	m_SDSSavePathEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_SDSSAVEPATH);
	m_BrowseSDSSavePathButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_BROWSESDSSAVEPATH);
	m_FileList->InsertColumn(WSTR("FileName"),400);
	m_FileList->InsertColumn(WSTR("Status"),90);
	m_SymSetOptions(SYMOPT_DEBUG);
	LoadConfigFile();
	return true;
}
bool CSymbolDownloaderDlg::LoadConfigFile()
{
	char Buffer[1024];
	WCHAR wBuffer[1024];
	DWORD Len;
	char ConfigFileName[MAX_PATH];
	BOOL bRet;
	GetModulePath(ConfigFileName);
	TStrCat(ConfigFileName,"SyserApp.ini");
	if(gpFileIO->IsFileExist(ConfigFileName)==false)
	{
		HANDLE hFile;
		gpFileIO->CreateFile(ConfigFileName,&hFile);
		gpFileIO->CloseHandle(hFile);
		bRet = WritePrivateProfileString("main","SymbolSite","http://msdl.microsoft.com/download/symbols",ConfigFileName);
		WritePrivateProfileString("main","SdsSavePath","c:\\DownLoadSymbols",ConfigFileName);
		WritePrivateProfileString("main","PdbSavePath","c:\\SyserSymbols",ConfigFileName);
		WritePrivateProfileString("list","Counter","0",ConfigFileName);
	}

	Len = GetPrivateProfileString("main","SymbolSite","http://msdl.microsoft.com/download/symbols",Buffer,sizeof(Buffer),ConfigFileName);
	TStrCpy(wBuffer,Buffer);
	m_SymbolSiteEdit->SetWindowText(wBuffer);
	Len = GetPrivateProfileString("main","SdsSavePath","c:\\DownLoadSymbols",Buffer,sizeof(Buffer),ConfigFileName);
	TStrCpy(wBuffer,Buffer);
	m_PDBSavePathEdit->SetWindowText(wBuffer);
	Len = GetPrivateProfileString("main","PdbSavePath","c:\\SyserSymbols",Buffer,sizeof(Buffer),ConfigFileName);
	TStrCpy(wBuffer,Buffer);
	m_SDSSavePathEdit->SetWindowText(wBuffer);
	return true;
}

bool CSymbolDownloaderDlg::InitDbgHelp()
{
	m_DbgHelpModule = LoadLibrary("DbgHelp.dll");
	if(m_DbgHelpModule==NULL)
		return false;
	LoadDbgHelpApi();
	return true;
}
void CSymbolDownloaderDlg::ReleaseDbgHelp()
{
	if(m_DbgHelpModule)
		FreeLibrary(m_DbgHelpModule);
}
bool CSymbolDownloaderDlg::LoadDbgHelpApi()
{
	m_SymFindFileInPath =(fpSymFindFileInPath) GetProcAddress(m_DbgHelpModule,"SymFindFileInPath");
	m_SymSetOptions = (fpSymSetOptions)GetProcAddress(m_DbgHelpModule,"SymSetOptions");
	m_SymGetOptions = (fpSymGetOptions)GetProcAddress(m_DbgHelpModule,"SymGetOptions");
/*	m_UnDecorateSymbolName = (fpUnDecorateSymbolName)GetProcAddress(m_DbgHelpModule,"UnDecorateSymbolName");
	*/
	return true;
}