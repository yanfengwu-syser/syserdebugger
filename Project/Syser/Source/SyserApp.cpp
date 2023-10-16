#include "StdAfx.h"
#include "Syser.h"
DWORD dwgErrorCode=0;

CSyser*	gpSyser;
CSyser	Syser;
CSyserPluginUI*gpSyserPluginUI;

void DbgPrint(PCSTR szMsg,...)
{
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	gpSyser = &Syser;
	return Syser.WinMainStart(hInstance,lpCmdLine,nCmdShow);
}

CSyser::CSyser(void)
{
	m_hDebuggerModule = NULL;
	m_pDebugger = NULL;
	gpSyserPluginUI = &m_SyserUI;
	m_bInitializeOK=true;	
	TIME_ZONE_INFORMATION TimeZoneInfo;
	GetTimeZoneInformation(&TimeZoneInfo);
	m_TimeZoneBias = TimeZoneInfo.Bias*60;
}

CSyser::~CSyser(void)
{
}

void CSyser::LoadCFG()
{
	char szCfgFN[MAX_FN_LEN];
	//GetSystemDirectoryA(szCfgFN,MAX_FN_LEN);
	//TStrCat(szCfgFN,"\\drivers\\Syser.cfg");
	GetModulePath(szCfgFN);
	TStrCat(szCfgFN,"Syser.cfg");
	if(LoadSyserOption(szCfgFN,&SyserOption,sizeof(SyserOption))==false)
	{
		SaveSyserOption(szCfgFN,&OrgSyserOption,sizeof(OrgSyserOption));
		SyserOption = OrgSyserOption;
	}
	char szColorCfgFN[MAX_FN_LEN];
	GetSystemDirectoryA(szColorCfgFN,MAX_FN_LEN);
	TStrCat(szColorCfgFN,"\\drivers\\SyserColor.cfg");
	if(LoadSyserOption(szColorCfgFN,&ColorOption,sizeof(ColorOption))==false)
	{
		SaveSyserOption(szColorCfgFN,&OrgColorOption,sizeof(OrgColorOption));
		ColorOption = OrgColorOption;
	}

}

bool CSyser::LoadDebugger(WCHAR*szModuleName)
{
	FPGetFileFilter fGetFileFilter;
	FPCreateDebugger fCreateDebugger;
	FPGetInfo fGetInfo;
	char szFullName[MAX_FN_LEN];
	UnloadDebugger();
	GetModulePath(szFullName);
	int Legnth = TStrLen(szFullName);
	if(Legnth>MAX_FN_LEN)return false;
	UnicodeToAnsi(szModuleName,&szFullName[Legnth],MAX_FN_LEN - Legnth);
	m_hDebuggerModule = LoadLibrary(szFullName);
	if(m_hDebuggerModule==NULL)
		return false;
	(FARPROC&)fCreateDebugger = GetProcAddress(m_hDebuggerModule,"CreateDebugger");
	if(fCreateDebugger==NULL)
		return false;
	(FARPROC&)fGetFileFilter = GetProcAddress(m_hDebuggerModule,"GetFileFilter");
	(FARPROC&)fGetInfo = GetProcAddress(m_hDebuggerModule,"GetInfo");
	if(fGetFileFilter)
	{
		WCHAR szBuffer[MAX_FN_LEN];
		fGetFileFilter(szBuffer);
		gpSyser->m_szDbgFileNameFilter = szBuffer;
	}
	if(fGetInfo)
	{
		char szBuffer[256];
		TStrCpy(szBuffer,"Syser Debugger - ");
		fGetInfo(&szBuffer[TStrLen(szBuffer)]);
		SetWindowText(m_hLocalWnd,szBuffer);
	}
	m_pDebugger = (CX86Debugger*)fCreateDebugger(&m_SyserUI);
	if(m_pDebugger==NULL)
	{
		FreeLibrary(m_hDebuggerModule);
		m_hDebuggerModule = NULL;
		return false;
	}
	m_pSysDebugger = m_pDebugger;
	m_pDebugger->Init(&gpSyser->m_SyserUI.m_SyserDI);
	m_MainFrame.m_SystemExplorer.AttachDebugger(m_pDebugger);

	m_MainFrame.m_SystemExplorer.UpdateItemState();
	m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
	return true;
}

void CSyser::UnloadDebugger()
{
	if(m_pDebugger == NULL || m_hDebuggerModule == NULL)
		return;
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		gpSyser->m_SyserUI.m_CodeDoc.Close();
	m_pDebugger->Release();
	m_pDebugger = NULL;
	FreeLibrary(m_hDebuggerModule);
	m_hDebuggerModule = NULL;
	gpSyser->m_szDbgFileNameFilter.Empty();
	m_MainFrame.m_SystemExplorer.DetachDebugger();
	UnloadPlugin();
	m_MainFrame.m_SystemExplorer.UpdateItemState();
	m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
}

XSCAN_RES CSyser::XScanPlugin(CFileIO*pFileIO,PCSTR FileName,ULSIZE FileSize,void*CBParem)
{
	if(TIMultiMatchWithPattern("*.dll",FileName)==false)
		return XSCAN_RES_IGNORE;
	LoadLibrary(FileName);
	return XSCAN_RES_CONTINUE;
}

int CSyser::LoadPlugin()
{
	char szPlugin[MAX_FN_LEN];	
	GetModulePath(szPlugin);
	TStrCat(szPlugin,"Plugin\\i386\\*");
	return gpFileIO->XScan(szPlugin,XScanPlugin,NULL,false);
}

void CSyser::UnloadPlugin()
{
	m_PluginMap.Clear();
}

bool CSyser::InitInstance()
{
	m_pszDiskList = "Wisp.dat;Syser.dat";
	LoadCFG();
	
	//m_DefaultFontType = WISP_FONT_8X16;
	if(CWispApp::InitInstance()==FALSE)
		return false;
#ifdef CODE_OS_WIN
	m_FrameStyleEx|=WS_EX_ACCEPTFILES;
#endif
	m_bHideMouse = true;
	m_hIcon = LoadIcon(m_hLocalInst,MAKEINTRESOURCE(IDI_ICON_SYSER));
	m_hCursorCurEIP = LoadCursor(m_hLocalInst,MAKEINTRESOURCE(IDC_CURSOR_CUR_EIP));
	CreateFrame(WSTR("Syser Debugger"),
				MAX(GetSystemMetrics(SM_CXFULLSCREEN)*5/6,0x2D0),
				MAX(GetSystemMetrics(SM_CYFULLSCREEN)*5/6,190),0);
	InitHotKeyInfo();
	
	m_MainFrame.Create(NULL,0,0,m_FrameBuffer.Width,m_FrameBuffer.Height,NULL,WISP_ID_MAIN_FRAME,WISP_WS_BACK_TRANS);
	m_MainFrame.AddAdvStyle(WISP_WAS_DRAG_WND);
	m_MainFrame.m_pWispBase->SetKeyboardLayer(0);
	LoadPlugin();
	gpSyser->LoadDebugger(SyserOption.szDebuggerFileName);
	if(m_pDebugger==NULL)
		m_MainFrame.m_DebuggerSelectForm.CreateForm(NULL,WISP_SH_MODAL_BLOCK);

	m_SyserUI.LoadAPIDefine();
	LoadHistroy();
	m_MainFrame.m_ConsoleWnd.RunModulePathBat("Syser.cmd",NULL);
	return true;
}

int	CSyser::ExitInstance()
{
	UnloadDebugger();
	UnloadPlugin();
	m_MainFrame.Destroy();
	DestroyFrame();
	DestroyIcon(m_hIcon);
	DestroyIcon(m_hCursorCurEIP);
	return CWispApp::ExitInstance();
}

bool CSyser::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char	szBuffer[MAX_FN_LEN];
	HDROP	hDrop;
	switch(message)
	{
	case WM_DROPFILES:
		hDrop = (HDROP)wParam;
		DragQueryFile(hDrop,0,szBuffer,MAX_FN_LEN);
		if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
			gpSyser->m_SyserUI.m_CodeDoc.Close();
		if(gpSyser->m_SyserUI.m_CodeDoc.Open(szBuffer)==false)
			OUTPUT(WSTR("Error : Fail to open dropped file !\n"));
		break;
	default:
		return CLocalWispApp::WndProc(hWnd,message,wParam,lParam);
	}
	return false;
}

void CSyser::LoadHistroy()
{
	DWORD Style;
	WCHAR szBuffer[MAX_FN_LEN];
	char szFileName[MAX_FN_LEN],*pStr;
	RECENT_HISTROY_ITEM Item;
	CTXTFile TXTFile;
	GetModulePath(szFileName);
	TStrCat(szFileName,"Histroy.lst");
	if(TXTFile.Open(szFileName)==false)
		return;
	m_HistroyList.Clear();
	for(TTXTStrList::IT Iter = TXTFile.m_StrList.Begin();Iter!=TXTFile.m_StrList.End();Iter++)
	{
		Style = SDP_NULL;
		pStr = TStrRChr(*Iter,'|');
		if(pStr)
		{
			*pStr++=0;
			if(USHexStrToNum(pStr,&Style)==false)
				Style=SDP_NULL;
		}
		Item.FileName = *Iter;
		Item.Style = Style;
		if(gpFileIO->IsFileExist(Item.FileName))
			m_HistroyList.Append(Item);
	}
	TXTFile.Close();
	m_bHistroyModified = false;
	WISP_MENU_ITEM*pMenuItem = (WISP_MENU_ITEM*)m_MainFrame.m_SystemExplorer.m_WndMenu.GetItemByName(WSTR("Recent Files"));
	if(pMenuItem && m_HistroyList.Count())
	{
		CWispMenu*pMenu = pMenuItem->pSubMenu;
		pMenu->RemoveAllItem();
		int CmdID=EVENT_ID_RECENT_FILE+1;
		for(TList<RECENT_HISTROY_ITEM>::IT Iter = m_HistroyList.Begin();Iter!=m_HistroyList.End()&&CmdID<=EVENT_ID_RECENT_FILE_END;Iter++)
		{
			AnsiToUnicode(Iter->FileName,szBuffer,MAX_FN_LEN);
			CWispDIB*pTypeDIB;
			PCSTR pExtName = TGetFileExt((PCSTR)Iter->FileName);
			if(pExtName && TStrICmp(pExtName,"exe")==0)
				pTypeDIB = WispTKDIBListDIB("\\Toolbar.bmp",16,16,22);
			else
				pTypeDIB = WispTKDIBListDIB("\\Toolbar.bmp",16,16,15);
			pMenu->InsertItem(-1,szBuffer,WISP_MIS_NORMAL,CmdID,pTypeDIB);
			CmdID++;
		}
		pMenu->AdjustPopupMenuSize();
	}
}

void CSyser::SaveHistroy()
{
	char szBuffer[256];
	char szFileName[MAX_FN_LEN];
	CImageFileStream File;
	GetModulePath(szFileName);
	TStrCat(szFileName,"Histroy.lst");
	if(File.Create(szFileName)==false)
		return;
	int n=0;
	for(TList<RECENT_HISTROY_ITEM>::IT Iter = m_HistroyList.Begin();Iter!=m_HistroyList.End();Iter++)
	{
		File.Puts(Iter->FileName.m_pData,Iter->FileName.Length());
		File.Puts(szBuffer,TSPrintf(szBuffer,"|%X\r\n",Iter->Style));
		n++;
	}
	File.Close();
}

void CSyser::InsertHistroy(PCSTR szFileName,DWORD Style)
{
	RECENT_HISTROY_ITEM Item;
	TList<RECENT_HISTROY_ITEM>::IT Iter;
	Item.FileName = szFileName;
	Item.Style = Style;
	Iter = m_HistroyList.Find(Item);
	if(Iter!=m_HistroyList.End())
	{
		if(Iter->Style == Style)
			return;
		m_HistroyList.Remove(Iter);
	}
	if(m_HistroyList.Count()<EVENT_ID_RECENT_FILE_END-EVENT_ID_RECENT_FILE)
	{
		if(m_HistroyList.Count()==0)
			m_HistroyList.Append(Item);
		else
			m_HistroyList.InsertBefore(m_HistroyList.Begin(),Item);
	}
	else
	{
		m_HistroyList.InsertBefore(m_HistroyList.Begin(),Item);
		m_HistroyList.Remove(m_HistroyList.Last());
	}
	m_bHistroyModified = true;
	SaveHistroy();
	LoadHistroy();
}

DWORD* LoadCFGHotKey()
{
	DWORD* Buffer=new DWORD[0x1000/sizeof(DWORD)];
	int i,j,nRealLen;
	DWORD* pEndbuffer;
	char szHotKeyCfgFN[MAX_FN_LEN];	
	
	if(Buffer==NULL)
		return NULL;
	pEndbuffer=Buffer;
	GetSystemDirectoryA(szHotKeyCfgFN,MAX_FN_LEN);
	TStrCat(szHotKeyCfgFN,"\\drivers\\SyserHotKey.cfg");
	if(LoadSyserHotKeyOption(szHotKeyCfgFN,Buffer,0x1000,&nRealLen)==false)
	{
		pEndbuffer++;//skip crc
		pEndbuffer++;//skip total number
		for(i=0,j=0;gDefaultHotkeyInfo[i].KeyName;i++)
		{
			*pEndbuffer++=gDefaultHotkeyInfo[i].CommandID;
			*pEndbuffer++=1;
			*pEndbuffer++=gDefaultHotkeyInfo[i].FuncKeyCode;
			*pEndbuffer++=gDefaultHotkeyInfo[i].SecondKeyCode;
		}
		Buffer[1]=i;
		*pEndbuffer++=0;
		*pEndbuffer++=0;
		*pEndbuffer++=0;
		*pEndbuffer++=0;
	}
	return Buffer;
}
void CSyser::InitHotKeyInfo()
{
	DWORD *Buffer=(DWORD*)LoadCFGHotKey();
	DWORD* OrgBuffer,i,j,k;
	CMDHOTKEYMAP::IT BeginIT;
	HOTKEYLIST* pList;
	KEY_PAIR KeyPair;

	if(Buffer==NULL)
		return;
	OrgBuffer=Buffer;
	Buffer++;//skip crc	
	Buffer++;//skip total number
	HOTKEYLIST TmpList;
	for(i=0;i<OrgBuffer[1];i++)
	{
		::DbgPrint("Syser : Hotkey cmd %d\n",*Buffer);
		BeginIT = m_CmdHotKeyMap.InsertUnique(*Buffer++,TmpList);
		if(BeginIT==m_CmdHotKeyMap.End())
			break;		
		k=*Buffer++;
		for(j=0;j<k;j++)
		{
			KeyPair.FuncKeyCode=*Buffer++;
			KeyPair.SecondKeyCode=*Buffer++;
			pList=&(*BeginIT);
			pList->Append(KeyPair);
		}		
	}
	delete []OrgBuffer;
}

void CSyser::SetActiveHotKey(DWORD FuncKeyCode,DWORD SecondKeyCode)
{

}

void CSyser::AttachHotKey(DWORD dwCmdID,CWispWnd* pWnd)
{	
	CMDHOTKEYMAP::IT FindIT;
	HOTKEYLIST::IT BeginIT;
	if(dwCmdID==0)
		return;
	FindIT=m_CmdHotKeyMap.Find(dwCmdID);
	if(FindIT!=m_CmdHotKeyMap.End())
	{
		BeginIT=FindIT->Begin();
		for(;BeginIT!=FindIT->End();BeginIT++)
		{
			if(BeginIT->SecondKeyCode)
			{			
				pWnd->RegisterHotKey(dwCmdID,BeginIT->SecondKeyCode,BeginIT->FuncKeyCode);
			}
			else
			{				
				pWnd->RegisterHotKey(dwCmdID,BeginIT->FuncKeyCode,0);
			}
		}
	}	
}
ULONG gCPUNumbers=1;


DWORD CSyser::AttachShortcutKey(DWORD dwCmdID,TMap<UINT,UINT> & pMap)
{	
	CMDHOTKEYMAP::IT FindIT;
	HOTKEYLIST::IT BeginIT;
	if(dwCmdID==0)
		return 0;
	FindIT=m_CmdHotKeyMap.Find(dwCmdID);
	if(FindIT!=m_CmdHotKeyMap.End())
	{
		BeginIT=FindIT->Begin();
		for(;BeginIT!=FindIT->End();BeginIT++)
		{
			pMap.InsertUnique(BeginIT->SecondKeyCode|BeginIT->FuncKeyCode,dwCmdID);
		}
		return FindIT->Count();
	}	
	return 0;
}

bool CSyser::InitOSHwndRoot()
{
	return true;
}