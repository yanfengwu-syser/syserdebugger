#include "StdAfx.h"
#include "SymbolDownloader.h"
#include "NoPDBSymbol.h"
#ifdef CODE_OS_WIN
#include <shlobj.h>
#ifdef _SYSER_
#include "../Syser/SyserApp.h"
#else
#include "SyserApp.h"
CSyserApp* gpSyser=&theApp;
#endif

#endif

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
	CMD_ID_UPDATEDOWNLOADSTATE,
	CMD_ID_STATIC_SYMBOL_SITE,
	CMD_ID_STATIC_PDB_PATH,
	CMD_ID_STATIC_SDS_PATH,
	CMD_ID_STATIC_MAIN_DIB,
};

WISP_MSG_MAP_BEGIN(CSymbolDownloaderDlg)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnResize)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CSymbolDownloaderDlg)
	WISP_MSG_CMD_MAP(CMD_ID_UPDATEDOWNLOADSTATE,OnCmdUpdateDownLoadState)
WISP_MSG_CMD_MAP_END

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
		{0,0,500,400},
		WISP_ID_NULL,
		WISP_WS_NULL,
	},
	{
		WISP_CTRL_LIST,
		{10,10,390,220},
		CMD_ID_LIST_FILE,
		WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER|WISP_WLS_SELECTED_ALWAYS,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,50,100,20},
		CMD_ID_BUTTON_ADDFILE,
		WISP_BS_NORMAL,
		WSTR("Add File(s)"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,80,100,20},
		CMD_ID_BUTTON_DELFILE,
		WISP_BS_NORMAL,
		WSTR("Del File(s)"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,110,100,20},
		CMD_ID_BUTTON_GETSYMBOL,
		WISP_BS_NORMAL,
		WSTR("Get Symbols"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,140,100,20},
		CMD_ID_BUTTON_STOP,
		WISP_BS_NORMAL,
		WSTR("Stop"),
		NULL,
	},
	{
		WISP_CTRL_STATIC_DIB,
		{460,180,32,32},
		CMD_ID_STATIC_MAIN_DIB,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Syser.ico:1"
	},
	{
		WISP_CTRL_STATIC_STRING,
		{10,240,70,20},
		CMD_ID_STATIC_SYMBOL_SITE,
		WISP_WS_NULL,
		WSTR("Symbol Site"),
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{10,270,110,20},
		CMD_ID_STATIC_PDB_PATH,
		WISP_WS_NULL,
		WSTR("Download PDB Path"),
		NULL,
	},
	{
		WISP_CTRL_STATIC_STRING,
		{10,300,110,20},
		CMD_ID_STATIC_SDS_PATH,
		WISP_WS_NULL,
		WSTR("Converted SDS Path"),
		NULL,
	},
	
	{
		WISP_CTRL_EDIT,
		{130,240,270,20},
		CMD_ID_EDIT_SYMBOLSITE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{130,270,270,20},
		CMD_ID_EDIT_PDBSAVEPATH,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{130,300,270,20},
		CMD_ID_EDIT_SDSSAVEPATH,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,240,100,20},
		CMD_ID_BUTTON_RESETSYMBOLSITE,
		WISP_BS_NORMAL,
		WSTR("Reset"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,270,100,20},
		CMD_ID_BUTTON_BROWSEPDBSAVEPATH,
		WISP_BS_NORMAL,
		WSTR("Browse"),
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{420,300,100,20},
		CMD_ID_BUTTON_BROWSESDSSAVEPATH,
		WISP_BS_NORMAL,
		WSTR("Browse"),
		NULL,
	},
	{WISP_CTRL_NULL}
};

CSymbolDownloaderDlg::CSymbolDownloaderDlg()
{
	m_SDSSavePathIndex=0;
	m_PDBSavePathIndex=0;
	m_pFormRes = m_FormRes;
	m_GetSymbolThread=false;
	m_Stop=false;
	InitializeCriticalSection(&m_CriticalSection);
}

CSymbolDownloaderDlg::~CSymbolDownloaderDlg()
{
	SDSSAVEPATHLIST::IT BeginIT,EndIT;
	BeginIT = m_SDSSavePathList.Begin();
	EndIT = m_SDSSavePathList.End();
	for(;BeginIT!=EndIT;BeginIT++)
		delete (*BeginIT).Name;
	PDBSAVEPATHLIST::IT BeginIT1,EndIT1;
	BeginIT1 = m_PDBSavePathList.Begin();
	EndIT1 = m_PDBSavePathList.End();
	for(;BeginIT1!=EndIT1;BeginIT1++)
		delete (*BeginIT1).Name;
	SYMFINDPATHLIST::IT  BeginIT2,EndIT2;
	BeginIT2 = m_SymFindPathList.Begin();
	EndIT2 = m_SymFindPathList.End();
	for(;BeginIT2!=EndIT2;BeginIT2++)
		delete (*BeginIT2).Name;
	DeleteCriticalSection(&m_CriticalSection);
}

bool CSymbolDownloaderDlg::OnResize(IN WISP_MSG*pMsg)
{
	m_FileList->Resize(m_ClientRect.cx - m_AddFileButton->m_WindowRect.cx - 60 ,m_ClientRect.cy-120,false);
	m_AddFileButton->MoveToClient(m_ClientRect.cx - m_AddFileButton->m_WindowRect.cx - 20,m_AddFileButton->m_ScrWindowRect.y - m_ScrWindowRect.y,false);
	m_DelFileButton->MoveToClient(m_ClientRect.cx - m_DelFileButton->m_WindowRect.cx - 20,m_DelFileButton->m_ScrWindowRect.y - m_ScrWindowRect.y,false);
	m_GetSymbolButton->MoveToClient(m_ClientRect.cx - m_GetSymbolButton->m_WindowRect.cx - 20,m_GetSymbolButton->m_ScrWindowRect.y - m_ScrWindowRect.y,false);
	m_StopButton->MoveToClient(m_ClientRect.cx - m_StopButton->m_WindowRect.cx - 20,m_StopButton->m_ScrWindowRect.y - m_ScrWindowRect.y,false);
	m_MainStaticDIB->MoveToClient(m_ClientRect.cx - m_MainStaticDIB->m_WindowRect.cx - 50,m_MainStaticDIB->m_ScrWindowRect.y - m_ScrWindowRect.y,false);
	m_SymbolSiteStatic->MoveToClient(10,m_ClientRect.cy - 90,false);
	m_PDBPathStatic->MoveToClient(10,m_ClientRect.cy - 60,false);
	m_SDSPathStatic->MoveToClient(10,m_ClientRect.cy - 30,false);
	m_SymbolSiteEdit->MoveToClient(150,m_SymbolSiteStatic->m_ScrWindowRect.y-m_ScrWindowRect.y-5,false);
	m_SymbolSiteEdit->Resize(m_FileList->m_WindowRect.cx- m_SymbolSiteEdit->m_ScrWindowRect.x +m_FileList->m_ScrWindowRect.x,m_SymbolSiteEdit->m_WindowRect.cy,false);
	m_PDBSavePathEdit->MoveToClient(150,m_PDBPathStatic->m_ScrWindowRect.y-m_ScrWindowRect.y-5,false);
	m_PDBSavePathEdit->Resize(m_FileList->m_WindowRect.cx- m_PDBSavePathEdit->m_ScrWindowRect.x +m_FileList->m_ScrWindowRect.x,m_PDBSavePathEdit->m_WindowRect.cy,false);
	m_SDSSavePathEdit->MoveToClient(150,m_SDSPathStatic->m_ScrWindowRect.y-m_ScrWindowRect.y-5,false);
	m_SDSSavePathEdit->Resize(m_FileList->m_WindowRect.cx- m_SDSSavePathEdit->m_ScrWindowRect.x +m_FileList->m_ScrWindowRect.x,m_SDSSavePathEdit->m_WindowRect.cy,false);
	m_SymbolSiteResetButton->MoveToClient(m_ClientRect.cx-m_SymbolSiteResetButton->m_WindowRect.cx-20,m_SymbolSiteStatic->m_ScrWindowRect.y-m_ScrWindowRect.y-5,false);
	m_BrowsePDBSavePathButton->MoveToClient(m_ClientRect.cx-m_BrowsePDBSavePathButton->m_WindowRect.cx-20,m_PDBPathStatic->m_ScrWindowRect.y-m_ScrWindowRect.y-5,false);
	m_BrowseSDSSavePathButton->MoveToClient(m_ClientRect.cx-m_BrowseSDSSavePathButton->m_WindowRect.cx-20,m_SDSPathStatic->m_ScrWindowRect.y-m_ScrWindowRect.y-5,false);
	return true;
}

bool CSymbolDownloaderDlg::OnEventButtonResetSymbolSite(IN WISP_MSG*pMsg)
{
	m_SymbolSiteEdit->SetWindowText(OrgSyserAppOption.szSymbolSite);
	m_SymbolSiteEdit->Update();
	return true;
}

bool CSymbolDownloaderDlg::OnEventButtonBrowsePDBSavePath(IN WISP_MSG*pMsg)
{
	WCHAR szPathName[MAX_FN_LEN];
	if(m_pWispBase->SelectDirForm(szPathName,WSTR("Please select PDB Save Path"))==false)
		return true;
	m_PDBSavePathEdit->SetWindowText(szPathName);
	m_PDBSavePathEdit->Update();
	return true;
}

bool CSymbolDownloaderDlg::OnEventButtonBrowseSDSSavePath(IN WISP_MSG*pMsg)
{
	WCHAR szPathName[MAX_FN_LEN];
	if(m_pWispBase->SelectDirForm(szPathName,WSTR("Please select Converted SDS Save Path"))==false)
		return true;
	m_SDSSavePathEdit->SetWindowText(szPathName);
	m_SDSSavePathEdit->Update();
	return true;
}

bool CSymbolDownloaderDlg::OnEventButtonAddFile(IN WISP_MSG*pMsg)
{
	char szFileNameA[MAX_FN_LEN];
	WCHAR szFileName[MAX_FN_LEN];
	if(m_pWispBase->SelectFileForm(NULL,WSTR("Binaries Files|*.exe;*.dll;*.cpl;*.sys;*.scr;*.ocx|All Files|*.*|"),false,szFileName,MAX_FN_LEN)==false)
		return true;
	WORKFILELIST::IT FindIT;
	HANDLE hItem;
	UnicodeToAnsi(szFileName,szFileNameA,MAX_FN_LEN);
	FindIT = m_CurrentFileList.InsertUnique(szFileNameA);
	if(FindIT!=m_CurrentFileList.End())
	{
		(*FindIT).FileName = FindIT.Key();
		hItem = m_FileList->InsertItem(szFileName);
		m_FileList->SetItemData(hItem,1,0);
	}
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
		{
			m_CurrentFileList.Remove(FindIT);
		}
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
	char SymbolFileName[MAX_PATH+1];
	WISP_MSG Msg;
	
	
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
	Msg.Msg=WISP_WM_COMMAND;
	Msg.hWnd=this;
	Msg.Command.CmdID=CMD_ID_UPDATEDOWNLOADSTATE;
	Msg.Command.Param2=SymbolStat.FileName;
	Msg.Command.Param1=3;
	POST_MSG(&Msg);
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
				TStrNCpy(FileName,SymbolStat.FileName,PathLen);
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
		Msg.Command.Param1=2;
		POST_MSG(&Msg);
	}
	else
	{
		memset(FileName,0,sizeof(FileName));
		TStrNCpy(FileName,SymbolStat.FileName,PathLen);
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
		Msg.Command.Param1=4;
		POST_MSG(&Msg);
		if(TranslateSymbolFile(SymbolFileType,SymbolStat.FileName,SymbolFileName))
		{
			memset(FileName,0,sizeof(FileName));
			TStrCpy(FileName,SymbolStat.SDSSavePath);
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
		Msg.Command.Param1=1;
		POST_MSG(&Msg);
	}
local_quit:
	if(Buffer)
		delete []Buffer;
	PEFile.Close();
	return true;
}

bool CSymbolDownloaderDlg::TranslateSymbolFile(IN int Type,IN char* pExeFileName,OUT char* pSymbolFileName)
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
	m_GetSymbolButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_GETSYMBOL);
	m_StopButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_STOP);
	m_FileList = (CWispList*)GetFormItem(CMD_ID_LIST_FILE);
	m_SymbolSiteEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_SYMBOLSITE);
	m_SymbolSiteResetButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_RESETSYMBOLSITE);
	m_PDBSavePathEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_PDBSAVEPATH);
	m_BrowsePDBSavePathButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_BROWSEPDBSAVEPATH);
	m_SDSSavePathEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_SDSSAVEPATH);
	m_BrowseSDSSavePathButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_BROWSESDSSAVEPATH);
	m_SymbolSiteStatic = (CWispStaticStr*)GetFormItem(CMD_ID_STATIC_SYMBOL_SITE);
	m_PDBPathStatic = (CWispStaticStr*)GetFormItem(CMD_ID_STATIC_PDB_PATH);
	m_SDSPathStatic = (CWispStaticStr*)GetFormItem(CMD_ID_STATIC_SDS_PATH);
	m_MainStaticDIB = (CWispStaticDIB*)GetFormItem(CMD_ID_STATIC_MAIN_DIB);
	m_FileList->InsertColumn(WSTR("FileName"),250);
	m_FileList->InsertColumn(WSTR("Status"),90);
	m_SymSetOptions(SYMOPT_DEBUG);

	m_SymbolSiteEdit->SetWindowText(SyserAppOption.szSymbolSite);
	m_PDBSavePathEdit->SetWindowText(SyserAppOption.szDownloadSymbolPath);
	m_SDSSavePathEdit->SetWindowText(SyserAppOption.szConvertedSDSPath);
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
	return true;
}

bool CSymbolDownloaderDlg::OnCmdUpdateDownLoadState(IN WISP_MSG *pMsg)
{
	char* FileName;
	CWispString pString;
	WCHAR * TmpName;
	HANDLE hItem;
	FileName = (char*)pMsg->Command.Param2;
	hItem = m_FileList->GetItem(0);
	for(;hItem;)
	{
		pString = m_FileList->GetItemText(hItem);
		TmpName = pString;
		if(TStrICmp(TmpName,FileName)==0)
			break;
		hItem = m_FileList->GetNextItem(hItem);
	}
	if(hItem==NULL)
		return true;
	switch(pMsg->Command.Param1)
	{
	case 1:
		m_FileList->SetItemText(hItem,1,WSTR("Success"));
		m_FileList->Update();
		break;
	case 2:
		m_FileList->SetItemText(hItem,1,WSTR("Fail !!!"));
		m_FileList->Update();
		break;
	case 3:
		m_FileList->SetItemText(hItem,1,WSTR("Downloading."));
		m_FileList->Update();
		break;
	case 4:
		m_FileList->SetItemText(hItem,1,WSTR("Analyzing Symbol file..."));
		m_FileList->Update();
		break;
	default :
		break;
	}
	return true;
}