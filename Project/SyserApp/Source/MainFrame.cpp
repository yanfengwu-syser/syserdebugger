#include "StdAfx.h"
#include "SyserApp.h"

WISP_MSG_MAP_BEGIN(CMainFrame)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_CMD_MAP_BEGIN(CMainFrame)
	WISP_MSG_CMD_MAP(WISP_ID_MAIN_TAB,OnMainTabCommand)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CMainFrame)
	WISP_MSG_EVENT_MAP(EVENT_ID_UPDATE_DRIVER_STATE,OnUpdateDriverState)
	WISP_MSG_EVENT_MAP(EVENT_ID_LOAD_MODULE,OnMenuEventLoadModule)
	WISP_MSG_EVENT_MAP(EVENT_ID_LOAD_EXPORT_SYMBOLS,OnMenuEventLoadExportSymbols)
	WISP_MSG_EVENT_MAP(EVENT_ID_LOAD_SYMBOL_SYSERAPP,OnMenuEventLoadSymbol)
	WISP_MSG_EVENT_MAP(EVENT_ID_LOAD_IDA_MAP,OnMenuEventLoadIDAMap)	
	WISP_MSG_EVENT_MAP(EVENT_ID_TRANSLATE_SYMBOL,OnMenuEventTranslateSymbol)
	WISP_MSG_EVENT_MAP(EVENT_ID_START_SYSER,OnMenuEventStartSyser)
	WISP_MSG_EVENT_MAP(EVENT_ID_STOP_SYSER,OnMenuEventStopSyser)
	WISP_MSG_EVENT_MAP(EVENT_ID_OPTION,OnMenuEventOption)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOT_OPTION,OnMenuEventBootOption)
	WISP_MSG_EVENT_MAP(EVENT_ID_VIDEO_DETECT_MODE,OnMenuEventVideoDetectMode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SYMBIL_DOWNLOADER,OnMenuEventSymDownloader)
	WISP_MSG_EVENT_MAP(EVENT_ID_DRV_LOADER,OnMenuEventDrvLoader)
	WISP_MSG_EVENT_MAP(EVENT_ID_VEUNPACK,OnMenuEventVEUnpack)
	WISP_MSG_EVENT_MAP(EVENT_ID_EXIT,OnMenuEventExit)
	WISP_MSG_EVENT_MAP(EVENT_ID_CHECKNEWVERSION,OnMenuEventCheckNewVersion)
	WISP_MSG_EVENT_MAP(EVENT_ID_SEND_CLIPBOARD,OnMenuEventSendClipboard)
	WISP_MSG_EVENT_MAP(EVENT_ID_RECV_CLIPBOARD,OnMenuEventRecvClipboard)
	WISP_MSG_EVENT_MAP(EVENT_ID_DEBUG_MESSAGE,OnMenuEventDebugMessage)
	WISP_MSG_EVENT_MAP(EVENT_ID_DEBUG_MESSAGE_CLEAR,OnMenuEventClearDebugMessage)
	WISP_MSG_EVENT_MAP(EVENT_ID_DEBUG_MESSAGE_FILTER,OnMenuEventDebugMessageFilter)
	WISP_MSG_EVENT_MAP(EVENT_ID_BUYNOW,OnMenuEventBuyNow)
	WISP_MSG_EVENT_MAP(EVENT_ID_REGISTER,OnMenuEventRegister)
	WISP_MSG_EVENT_MAP(EVENT_ID_COMMAND_REFERENCE,OnMenuEventCmdRef)
	WISP_MSG_EVENT_MAP(EVENT_ID_DEBUG_HELP,OnMenuEventDebugHelp)
	WISP_MSG_EVENT_MAP(EVENT_ID_ABOUT_SYSERAPP,OnMenuEventAboutSyserApp)
	WISP_MSG_EVENT_MAP(EVENT_ID_SAVE_HISTROYS,OnMenuEventSaveHistroys)
	WISP_MSG_EVENT_MAP(EVENT_ID_SAVE_SYSER_HISTROYS,OnMenuEventSaveSyserHistroys)
	WISP_MSG_EVENT_MAP(EVENT_ID_SAVE_COMMENTS,OnMenuEventSaveComments)
WISP_MSG_EVENT_MAP_DEFAULT_END(OnMenuEventRecentFile)

bool CMainFrame::OnMainTabCommand(IN WISP_MSG*pMsg)
{
	return true;
}

bool CMainFrame::OnMenuEventLoadModule(IN WISP_MSG*pMsg)
{
	DWORD Style;
	COpenFileForm	OpenFileForm;
	OpenFileForm.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	OpenFileForm.Destroy();
	if(OpenFileForm.m_Result!=WISP_ID_OK)
		return true;
	Style = SDP_NULL;
	if(OpenFileForm.m_bTransSym)
		Style|=SDP_LOAD_SDS;
	if(OpenFileForm.m_bLoadDepSym)
		Style|=SDP_LOAD_DEP_SDS;
	if(OpenFileForm.m_bAutoUnloadSym)
		Style|=SDP_AUTO_UNLOAD_SDS;
	theApp.m_SyserInterface.LoadModule(OpenFileForm.m_Filename,OpenFileForm.m_CmdLine,Style);
	return true;
}

bool CMainFrame::OnMenuEventLoadExportSymbols(IN WISP_MSG*pMsg)
{
	char szBuffer[MAX_FN_LEN],szFileName[MAX_FN_LEN];
	char szSymbolFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "PE Module(exe;scr;dll;sys)\0*.exe;*.scr;*.dll;*.sys\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	GetSystemDirectory(szBuffer,MAX_FN_LEN);
	OpenFileName.lpstrInitialDir = szBuffer;
	*szFileName = 0;
	if(GetOpenFileName(&OpenFileName)==false)
		return true;
	szSymbolFileName[0]=0;
	if(theApp.m_SyserInterface.TranslateExportSymbolFile(szFileName,szSymbolFileName))
	{
		theApp.m_SyserInterface.LoadSDS(szSymbolFileName);
	}	
	else
	{
		OUTPUT(WSTR("%<3>Error : Failed to load export symbols!\n"));
	}
	//theApp.m_SyserInterface.LoadModuleExportSymbols(szFileName);
	return true;
}

bool CMainFrame::OnMenuEventLoadSymbol(IN WISP_MSG*pMsg)
{	
	char szFileName[MAX_FN_LEN],szDir[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "Symbol Files(*.sds)\0*.sds\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	OpenFileName.lpstrInitialDir = NULL;
	GetModulePath(szDir);
	TStrCat(szDir,"Symbols");
	*szFileName = 0;
	if(GetOpenFileName(&OpenFileName)==false)
		return true;
	theApp.m_SyserInterface.LoadSDS(szFileName);
	return true;
}

bool CMainFrame::OnMenuEventLoadIDAMap(IN WISP_MSG*pMsg)
{	
#ifndef __DEMO__VERSION__
	CLoadIDAMapForm	LoadIDAMapForm;
	LoadIDAMapForm.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	LoadIDAMapForm.Destroy();
	if(LoadIDAMapForm.m_Result!=WISP_ID_OK)
		return true;
	theApp.m_SyserInterface.LoadModuleIDAMapFile(LoadIDAMapForm.m_MapFileName,LoadIDAMapForm.m_FileModuleName);
#else
	theApp.MsgBox(WSTR("Evaluation version limited."),WSTR("Warnning.."));
#endif
	return true;
}



bool CMainFrame::OnMenuEventTranslateSymbol(IN WISP_MSG*pMsg)
{
	WCHAR wszBuffer[MAX_FN_LEN];
	char szBuffer[MAX_FN_LEN],szFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "PE Files(exe;dll;ocx;scr;sys)\0*.exe;*.dll;*.ocx;*.scr;*.sys\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	*szFileName = 0;
	if(GetOpenFileName(&OpenFileName)==false)
		return true;
	if(theApp.m_SyserInterface.TranslateSymbolFile(szFileName,szBuffer,true))
	{
		AnsiToUnicode(szBuffer,wszBuffer,MAX_FN_LEN);
		OUTPUT(WSTR("Translate debugging data to %s\n"),wszBuffer);
	}
	else
	{
		OUTPUT(WSTR("Counldn't find this module's debugging data !\n"));
	}
	return true;
}

bool CMainFrame::OnMenuEventRecentFile(IN WISP_MSG*pMsg)
{
	int Index;
	if(pMsg->Command.CmdID>EVENT_ID_RECENT_FILE_SYSERAPP && pMsg->Command.CmdID<=EVENT_ID_RECENT_FILE_SYSERAPP_END)
	{
		Index = pMsg->Command.CmdID-EVENT_ID_RECENT_FILE_SYSERAPP-1;
		TList<RECENT_HISTROY_ITEM>::IT Iter = theApp.m_HistroyList[Index];
		theApp.m_SyserInterface.LoadModule(Iter->FileName,NULL,Iter->Style);
	}
	return true;
}

bool CMainFrame::OnMenuEventSendClipboard(IN WISP_MSG*pMsg)
{
	theApp.m_SyserInterface.SendClipboardString();
	return true;
}

bool CMainFrame::OnMenuEventRecvClipboard(IN WISP_MSG*pMsg)
{
	theApp.m_SyserInterface.RecvClipboardString();
	return true;
}

bool CMainFrame::OnMenuEventDebugMessage(IN WISP_MSG*pMsg)
{
	theApp.m_SyserInterface.m_bCaptureDbgMsg = m_MainMenu.IsItemChecked(EVENT_ID_DEBUG_MESSAGE);
	return true;
}

bool CMainFrame::OnMenuEventClearDebugMessage(IN WISP_MSG*pMsg)
{
	theApp.m_MainFrame.m_ConsoleWnd.ClearScreen();
	return true;
};

bool CMainFrame::OnMenuEventDebugMessageFilter(IN WISP_MSG*pMsg)
{
	CDbgMsgFilterForm DbgMsgFilterForm;
	DbgMsgFilterForm.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	return true;
}

bool CMainFrame::OnMenuEventStartSyser(IN WISP_MSG*pMsg)
{
	theApp.m_SyserInterface.StartSyserDriver();
	return true;
}

bool CMainFrame::OnMenuEventStopSyser(IN WISP_MSG*pMsg)
{
	theApp.m_SyserInterface.StopSyserDriver();
	return true;
}

bool CMainFrame::OnMenuEventOption(IN WISP_MSG*pMsg)
{
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS,false,"Syser Option");
	if(hMutex)
	{
		HWND hWnd = FindWindow(NULL,"Syser Option");
		if(hWnd)
			BringWindowToTop(hWnd);
		CloseHandle(hMutex);
		return true;
	}
	CHAR szFileName[MAX_FN_LEN];
	STARTUPINFO	StartInfo;
	PROCESS_INFORMATION ProcInfo;
	memset(&StartInfo,0,sizeof(STARTUPINFO));
	memset(&ProcInfo,0,sizeof(PROCESS_INFORMATION));
	StartInfo.cb = sizeof(STARTUPINFO);
	StartInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartInfo.wShowWindow = SW_SHOWDEFAULT;
	GetModulePath(szFileName);
	TStrCat(szFileName,"SyserOption.exe");
	CreateProcess(szFileName,NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&StartInfo,&ProcInfo);
	return true;
}

bool CMainFrame::OnUpdateDriverState(IN WISP_MSG*pMsg)
{
	theApp.m_SyserInterface.UpdateDriverStatus();
	return true;
}

bool CMainFrame::OnMenuEventBootOption(IN WISP_MSG*pMsg)
{
	CHAR szFileName[MAX_FN_LEN];
	STARTUPINFO	StartInfo;
	PROCESS_INFORMATION ProcInfo;
	memset(&StartInfo,0,sizeof(STARTUPINFO));
	memset(&ProcInfo,0,sizeof(PROCESS_INFORMATION));
	StartInfo.cb = sizeof(STARTUPINFO);
	StartInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartInfo.wShowWindow = SW_SHOWDEFAULT;
	GetModulePath(szFileName);
	TStrCat(szFileName,"SyserOption.exe /boot");
	CreateProcess(NULL,szFileName,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&StartInfo,&ProcInfo);
	return true;
}

bool CMainFrame::OnMenuEventVideoDetectMode(IN WISP_MSG*pMsg)
{
	CHAR szFileName[MAX_FN_LEN];
	STARTUPINFO	StartInfo;
	PROCESS_INFORMATION ProcInfo;
	memset(&StartInfo,0,sizeof(STARTUPINFO));
	memset(&ProcInfo,0,sizeof(PROCESS_INFORMATION));
	StartInfo.cb = sizeof(STARTUPINFO);
	StartInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartInfo.wShowWindow = SW_SHOWDEFAULT;
	GetModulePath(szFileName);
	TStrCat(szFileName,"SyserOption.exe /video");
	CreateProcess(NULL,szFileName,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&StartInfo,&ProcInfo);
	return true;
}

bool CMainFrame::OnMenuEventSymDownloader(IN WISP_MSG*pMsg)
{
	char szPathName[MAX_FN_LEN];
	GetModulePath(szPathName);
	TStrCat(szPathName,"SymRecv.exe");
	ShellExecute(NULL,NULL,szPathName,NULL,NULL,SW_NORMAL);
	return true;
}

bool CMainFrame::OnMenuEventDrvLoader(IN WISP_MSG*pMsg)
{
	char szPathName[MAX_FN_LEN];
	GetModulePath(szPathName);
	TStrCat(szPathName,"Drvloader.exe");
	ShellExecute(NULL,NULL,szPathName,NULL,NULL,SW_NORMAL);
	return true;
}

bool CMainFrame::OnMenuEventVEUnpack(IN WISP_MSG*pMsg)
{
	char szPathName[MAX_FN_LEN];
	GetModulePath(szPathName);
	TStrCat(szPathName,"VEUnpack.exe");
	ShellExecute(NULL,NULL,szPathName,NULL,NULL,SW_NORMAL);
	return true;
}

bool CMainFrame::OnMenuEventExit(IN WISP_MSG*pMsg)
{
	Destroy();
	return true;
}

bool CMainFrame::OnMenuEventCmdRef(IN WISP_MSG*pMsg)
{
	char szPathName[MAX_FN_LEN];
	GetModulePath(szPathName);
	TStrCat(szPathName,"SyserCommand.chm");
	ShellExecute(NULL,NULL,szPathName,NULL,NULL,SW_MAXIMIZE);
	return true;
}

bool CMainFrame::OnMenuEventDebugHelp(IN WISP_MSG*pMsg)
{
	char szPathName[MAX_FN_LEN];
	GetModulePath(szPathName);
	TStrCat(szPathName,"DebuggerHelp.chm");
	ShellExecute(NULL,NULL,szPathName,NULL,NULL,SW_MAXIMIZE);
	return true;
}

bool CMainFrame::OnCreate(IN WISP_MSG*pMsg)
{
	m_Style|=WISP_WS_BACK_TRANS;
	m_MainMenu.CreateWndMenu(this,WISP_ID_MAIN_MENU,MainMenu,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_MainToolBar.CreateEx(this,0,-1,WISP_ID_MAIN_TOOLBAR,WISP_WS_NULL);
	m_MainToolBar.LoadToolbar(WispTKDIBList("\\Toolbar.bmp",16,16),MainToolbar);
	m_MainToolBar.Move(0,m_MainMenu.m_WindowRect.cy);
	m_MainTabWnd.Create(NULL,0,m_MainMenu.m_WindowRect.cy+m_MainToolBar.m_WindowRect.cy,m_ClientRect.cx,m_ClientRect.cy-m_MainToolBar.m_WindowRect.cy-m_MainMenu.m_WindowRect.cy,this,WISP_ID_MAIN_TAB,WISP_TWS_BUTTOM);
	m_ConsoleWnd.Create(NULL,0,0,0,0,&m_MainTabWnd,0,WISP_WS_NULL);
	m_MainTabWnd.InsertWnd(WSTR("Console & Debug Message"),&m_ConsoleWnd,WispDIB("\\SyserIcon\\Console.ico",0));
	m_MainTabWnd.RecalcLayout();
	int TipSize = m_MainTabWnd.m_ClientRect.cx - m_MainTabWnd.m_TabItemWidth - 5;
	MAX_LIMIT(TipSize,MAX_TIP_WIDTH);
	MIN_LIMIT(TipSize,0);
	m_TipStr.Create(NULL,m_MainTabWnd.m_TabItemWidth + 20,m_MainTabWnd.m_ClientRect.cy-16,TipSize,16,&m_MainTabWnd,0,WISP_WS_NULL);
	DWORD VerType=SN_ERROR;
	GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\VerType",&VerType,sizeof(VerType));
	if(VerType>=SN_MAX)
		VerType = SN_ERROR;
	if(VerType!=SN_ERROR)
		m_MainMenu.RemoveItem(EVENT_ID_BUYNOW);
	else
		m_MainMenu.SetItemColor(EVENT_ID_BUYNOW,SYS_COLOR[SC_LIGHT_RED]);
	theApp.m_SyserInterface.m_VerType = (SYSER_SN_TYPE)VerType;
	GetVersionString();
	return true;
}

PCWSTR szVerString[]=
{
	WSTR("Evaluation Version"),
	WSTR("Personal Version : Licensed to %s"),
	WSTR("Student Version : Licensed to %s"),
	WSTR("Enterprise Version : Licensed to %s"),
};

void CMainFrame::GetVersionString()
{
	CHAR szLicName[256];
	WCHAR wszLicName[256],szBuffer[256];
	if(theApp.m_SyserInterface.m_VerType>=SN_MAX || theApp.m_SyserInterface.m_VerType<SN_ERROR)
	{
		theApp.m_SyserInterface.m_VerType=SN_ERROR;
	}
	*szLicName=0;*wszLicName=0;
	GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\LicName",szLicName,sizeof(szLicName));
	AnsiToUnicode(szLicName,wszLicName,256);
	TSPrintf(szBuffer,szVerString[theApp.m_SyserInterface.m_VerType],wszLicName);
	m_TipStr.SetWindowText(szBuffer);
}

bool CMainFrame::OnSize(IN WISP_MSG*pMsg)
{
	m_MainTabWnd.Resize(m_ClientRect.cx,m_ClientRect.cy-m_MainMenu.m_WindowRect.cy-m_MainToolBar.m_WindowRect.cy);
	int TipSize = m_MainTabWnd.m_ClientRect.cx - m_MainTabWnd.m_TabItemWidth - 5;
	MAX_LIMIT(TipSize,MAX_TIP_WIDTH);
	MIN_LIMIT(TipSize,0);
	m_TipStr.MoveToClient(m_MainTabWnd.m_TabItemWidth + 20,m_MainTabWnd.m_ClientRect.cy-16);
	m_TipStr.Resize(TipSize,m_TipStr.m_WindowRect.cy);
	return true;
}

bool CMainFrame::OnMenuEventCheckNewVersion(IN WISP_MSG*pMsg)
{
	theApp.CheckNewVersion();
	return true;
}

bool CMainFrame::OnMenuEventBuyNow(IN WISP_MSG*pMsg)
{
	ShellExecute(NULL,"open","http://www.sysersoft.com/products.html",NULL,NULL,SW_SHOWMAXIMIZED);
	return true;
}

bool CMainFrame::OnMenuEventRegister(IN WISP_MSG*pMsg)
{
	char szBuffer[256];
	m_RegForm.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	if(m_RegForm.m_Result != WISP_ID_OK)
		return true;	
	TStrCpy(szBuffer,(PCWSTR)m_RegForm.m_StrName);
	SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\LicName",szBuffer,REG_SZ);
	TStrCpy(szBuffer,(PCWSTR)m_RegForm.m_StrSN);
	SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\SN",szBuffer,REG_SZ);
	m_pWispBase->MsgBox(WSTR("You may need to restart syser debugger to validate this key!"),WSTR("Notify"),WISP_MB_OK);
	return true;
}

bool CMainFrame::OnMenuEventAboutSyserApp(IN WISP_MSG*pMsg)
{
	CAboutForm	AboutForm;
	AboutForm.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	AboutForm.Destroy();
	return true;
}

void CMainFrame::UpdateSyserDriverItem(bool bEnable)
{
	m_MainMenu.EnableItem(EVENT_ID_LOAD_MODULE,bEnable);
	m_MainMenu.EnableItem(EVENT_ID_LOAD_EXPORT_SYMBOLS,bEnable);
	m_MainMenu.EnableItem(EVENT_ID_LOAD_SYMBOL_SYSERAPP,bEnable);
	m_MainMenu.EnableItem(EVENT_ID_SAVE_SYSER_HISTROYS,bEnable);
	m_MainMenu.EnableItem(EVENT_ID_SAVE_COMMENTS,bEnable);
	m_MainMenu.EnableItem(EVENT_ID_SEND_CLIPBOARD,bEnable);
	m_MainMenu.EnableItem(EVENT_ID_RECV_CLIPBOARD,bEnable);
	m_MainMenu.EnableItem(EVENT_ID_START_SYSER,!bEnable);
	m_MainMenu.EnableItem(EVENT_ID_STOP_SYSER,bEnable);
	m_MainToolBar.EnableItem(EVENT_ID_LOAD_MODULE,bEnable);
	m_MainToolBar.EnableItem(EVENT_ID_LOAD_EXPORT_SYMBOLS,bEnable);
	m_MainToolBar.EnableItem(EVENT_ID_LOAD_SYMBOL_SYSERAPP,bEnable);
	m_MainToolBar.EnableItem(EVENT_ID_START_SYSER,!bEnable);
	m_MainToolBar.EnableItem(EVENT_ID_STOP_SYSER,bEnable);
	Update();
}

bool CMainFrame::OnMenuEventSaveHistroys(IN WISP_MSG*pMsg)
{
	char szFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "TEXT Files(*.txt)\0*.txt\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	OpenFileName.Flags = OFN_OVERWRITEPROMPT;
	TStrCpy(szFileName,"Histroy.txt");
	if(GetSaveFileName(&OpenFileName)==false)
		return true;
	m_ConsoleWnd.SaveHistroys(szFileName);
	return true;
}

bool CMainFrame::OnMenuEventSaveSyserHistroys(IN WISP_MSG*pMsg)
{
	char szFileName[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = theApp.m_hLocalInst;
	OpenFileName.hwndOwner = theApp.m_hLocalWnd;
	OpenFileName.lpstrFilter = "TEXT Files(*.txt)\0*.txt\0All Files\0*.*\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	OpenFileName.Flags = OFN_OVERWRITEPROMPT;
	TStrCpy(szFileName,"SyserLog.txt");
	if(GetSaveFileName(&OpenFileName)==false)
		return true;
	theApp.m_SyserInterface.SaveSyserHistroys(szFileName);
	return true;
}

bool CMainFrame::OnMenuEventSaveComments(IN WISP_MSG*pMsg)
{
	theApp.m_SyserInterface.SaveSyserComments();
	return true;
}

