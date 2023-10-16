#include "StdAfx.h"
#include "SyserApp.h"
#include "MainFrame.h"
#include "DXTest.h"
#include "ModifyBoot.h"

CSyserApp	theApp;

#ifdef CODE_OS_WIN

enum
{
	COPYDATA_CMD_LOAD_SDS=0x100,
	COPYDATA_CMD_UNLOAD_SDS,
	COPYDATA_CMD_TRANSLATE_SDS,
	COPYDATA_CMD_LOAD,
	COPYDATA_CMD_MAXCMD,
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return theApp.WinMainStart(hInstance,lpCmdLine,nCmdShow);
}

#endif

int OldiSystemTray;
CSyserApp::CSyserApp(void)
{
	GetModulePath(m_szSyserAppCfgFN);
	TStrCat(m_szSyserAppCfgFN,"SyserApp.cfg");
	GetSystemDirectoryA(m_szSyserCfgFN,MAX_FN_LEN);
	TStrCat(m_szSyserCfgFN,"\\drivers\\Syser.cfg");
	GetSystemDirectoryA(m_szSyserColorCfgFN,MAX_FN_LEN);
	TStrCat(m_szSyserColorCfgFN,"\\drivers\\SyserColor.cfg");
}

CSyserApp::~CSyserApp(void)
{
}

void CSyserApp::InitEnv()
{
}

void CSyserApp::LoadCFG()
{
	if(LoadSyserOption(m_szSyserAppCfgFN,&SyserAppOption,sizeof(SyserAppOption))==false)
	{
		SaveSyserOption(m_szSyserAppCfgFN,&OrgSyserAppOption,sizeof(OrgSyserAppOption));
		SyserAppOption = OrgSyserAppOption;
	}
	if(LoadSyserOption(m_szSyserCfgFN,&SyserOption,sizeof(SyserOption))==false)
	{
		SaveSyserOption(m_szSyserCfgFN,&OrgSyserOption,sizeof(OrgSyserOption));
		SyserOption = OrgSyserOption;
	}
}

bool InstallDependData(PCSTR FileNameList)
{
	HANDLE hSrcFile,hDesFile;
	char szDesFile[MAX_FN_LEN],szSrcFile[MAX_FN_LEN],szFileName[MAX_FN_LEN],*pszDesFile,*pszSrcFile;
	FILETIME DesTime,SrcTime;
	PCSTR szBegin,szEnd;
	GetSystemDirectory(szDesFile,MAX_FN_LEN);
	TStrCat(szDesFile,"\\drivers\\");
	pszDesFile = szDesFile+TStrLen(szDesFile);
	pszSrcFile = szSrcFile+GetModulePath(szSrcFile);
	szBegin = FileNameList;
	while(*szBegin)
	{
		szEnd = TStrChr(szBegin,';');
		if(szEnd)
		{
			TStrCpyLimit(szFileName,szBegin,(int)(szEnd-szBegin)+1);
			szEnd++;
		}
		else
		{
			TStrCpy(szFileName,szBegin);
			szEnd = &szBegin[TStrLen(szBegin)];
		}
		TStrCpy(pszDesFile,szFileName);
		TStrCpy(pszSrcFile,szFileName);
		SrcTime.dwLowDateTime = SrcTime.dwHighDateTime =
			DesTime.dwLowDateTime = DesTime.dwHighDateTime = 0;
		if(gpFileIO->OpenFile(szSrcFile,&hSrcFile))
		{
			GetFileTime(hSrcFile,NULL,NULL,&SrcTime);
			gpFileIO->CloseHandle(hSrcFile);
		}
		if(gpFileIO->OpenFile(szDesFile,&hDesFile))
		{
			GetFileTime(hDesFile,NULL,NULL,&DesTime);
			gpFileIO->CloseHandle(hDesFile);
		}
		if(SrcTime.dwLowDateTime || SrcTime.dwHighDateTime)
		{
			if(SrcTime.dwHighDateTime != DesTime.dwHighDateTime || SrcTime.dwLowDateTime != DesTime.dwLowDateTime)
			{
				CopyFile(szSrcFile,szDesFile,FALSE);
			}
		}
		szBegin = szEnd;
	}
	return true;
}

bool CSyserApp::InitInstance()
{
	WCHAR wszBuffer[256];
	HWND hWnd;
	HANDLE hMutex;
	SYSTEM_INFO SystemInfo;
	COPYDATASTRUCT CopyData;
	LRESULT rs;
	bool bStartAgain=false;
StartAgain:
	CopyData.dwData=COPYDATA_CMD_MAXCMD;
	if(TStrIStr(m_pCmdLine,"/Uninstall"))
	{
		m_SyserInterface.UninstallSyser();
		return false;
	}
	else if(TStrIStr(m_pCmdLine,"/Install"))
	{
		m_SyserInterface.InstallSyser();
		return false;
	}
	else if(TStrIStr(m_pCmdLine,"/Stop"))
	{
		m_SyserInterface.StopSyser();
		return false;
	}
	else if(TStrNICmp(m_pCmdLine,"/load ",6)==0)
	{
		CopyData.dwData=COPYDATA_CMD_LOAD;
		CopyData.cbData = TStrLen(&m_pCmdLine[6])+1;
		CopyData.lpData=&m_pCmdLine[6];
	}
	else if(TStrNICmp(m_pCmdLine,"/unloadsds ",11)==0)
	{
		CopyData.dwData=COPYDATA_CMD_UNLOAD_SDS;
		CopyData.cbData = TStrLen(&m_pCmdLine[11])+1;
		CopyData.lpData=&m_pCmdLine[11];
	}
	else if(TStrNICmp(m_pCmdLine,"/loadsds ",9)==0)
	{
		CopyData.dwData=COPYDATA_CMD_LOAD_SDS;
		CopyData.cbData = TStrLen(&m_pCmdLine[9])+1;
		CopyData.lpData=&m_pCmdLine[9];
	}
	else if(TStrNICmp(m_pCmdLine,"/tr ",4)==0)
	{
		CopyData.dwData=COPYDATA_CMD_TRANSLATE_SDS;
		CopyData.cbData = TStrLen(&m_pCmdLine[4])+1;
		CopyData.lpData=&m_pCmdLine[4];
	}
	hMutex = OpenMutex(MUTEX_ALL_ACCESS,false,"Syser Interface");
	if(hMutex)
	{
		hWnd = ::FindWindow("WispWindowClass",MAIN_WND_NAME);
		if(hWnd && CopyData.dwData!=COPYDATA_CMD_MAXCMD)
			rs = ::SendMessage(hWnd,WM_COPYDATA,(WPARAM)m_hLocalWnd,(LPARAM)&CopyData);
		CloseHandle(hMutex);
		return false;
	}
	InstallDependData("Syser.dat;Wisp.dat;libfunc.fdc;APIDef.lib");
	//////////////////////////////////////////////////////////////////////////////
	//设置数据文件目录
	GetSystemDirectory(m_CurDir,MAX_FN_LEN);
	TStrCat(m_CurDir,"\\drivers\\");
	//
	//////////////////////////////////////////////////////////////////////////////
	m_pszDiskList = "Wisp.dat;Syser.dat";
	if(CLocalWispApp::InitInstance()==false)
	{
		if(bStartAgain==false)
		{
			bStartAgain = true;
			m_SyserInterface.InstallSyser();
			goto StartAgain;
		}
		return false;
	}
	LoadCFG();
	GetSystemInfo(&SystemInfo);
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	if(statex.ullTotalPhys / (1024*1024) < 128)
	{
		if(MessageBox(NULL,"Physical memory is less than 128 MB,Syser maybe start fail!","Warning",MB_OK)==IDNO)
			return false;
	}
	//提升到Debug级别
	CProcess::GetPrivilege(SE_DEBUG_NAME);
	m_bHideMouse = true;
	m_FrameStyle&=~WS_VISIBLE;
	m_hIcon = LoadIcon(m_hLocalInst,MAKEINTRESOURCE(IDI_ICON_SYSERAPP));
	if(SyserAppOption.iTopMost!=0)
		m_FrameStyleEx|=WS_EX_TOPMOST;
	TStrCpy(wszBuffer,MAIN_WND_NAME);
	CreateFrame(wszBuffer,620,430,0);
	m_MainFrame.Create(NULL,0,0,m_FrameBuffer.Width,m_FrameBuffer.Height,NULL,WISP_ID_MAIN_FRAME,WISP_WS_NULL);
	m_hNotifyMenu = LoadMenu(m_hLocalInst,MAKEINTRESOURCE(IDR_MENU_NOTIFY_ICON));
	m_hSubNotifyMenu = GetSubMenu(m_hNotifyMenu,0);
	GetClipboardString();
	if(m_SyserInterface.Init()==false)
	{
		DestroyMenu(m_hNotifyMenu);
		return false;
	}
	LoadHistroy();
	theApp.m_MainFrame.m_ConsoleWnd.RunModulePathBat("SyserApp.cmd","-sb");
	OldiSystemTray = SyserAppOption.iSystemTray;
	if(OldiSystemTray)
	{
		if(m_SyserInterface.m_bSyserDriverStatus)
			InsertNotifyIcon(MAIN_WND_NAME,IDI_ICON_SYSERAPP);
		else
			InsertNotifyIcon(MAIN_WND_NAME,IDI_ICON_SYSER_OFF);
	}
	if(CopyData.dwData!=COPYDATA_CMD_MAXCMD)
		::SendMessage(m_hLocalWnd,WM_COPYDATA,(WPARAM)m_hLocalWnd,(LPARAM)&CopyData);
	InitEnv();
	m_UpdateNewVersionDownload.StartupWinsock();
	if(m_SyserInterface.m_bAttachFrameBuffer==false && SyserOption.iVideoDetectMode!=SYSER_VDM_USER)
	{
		OUTPUT(WSTR("%<F>SyserLoader : Syser Kernel Debugger can't recognise your display driver !\n"));
		OUTPUT(WSTR("%<F>SyserLoader : Please change Video Display Detect Mode to \"User Mode\" than restart Syser\n"));
	}
	ShowWindow(m_hLocalWnd,SW_NORMAL);
	return true;
}

int	CSyserApp::ExitInstance()
{
	if(OldiSystemTray)
		RemoveNotifyIcon(IDI_ICON_SYSERAPP);
	DestroyMenu(m_hNotifyMenu);
	m_MainFrame.Destroy();
	DestroyFrame();
	m_UpdateNewVersionDownload.CleanupWinsock();
	m_SyserInterface.Release();
	if(m_bHistroyModified)
		SaveHistroy();
	return CLocalWispApp::ExitInstance();
}

bool CSyserApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch (message)
	{
	case WM_CREATE:
		SetClipboardViewer(hWnd);
		return CLocalWispApp::WndProc(hWnd,message,wParam,lParam);
	case WM_CLOSE:
		if(OldiSystemTray==0)
			return CLocalWispApp::WndProc(hWnd,message,wParam,lParam);
		ShowWindow(m_hLocalWnd,SW_HIDE);
		break;
	case WM_DESTROY:
		if(m_SyserInterface.m_bSyserDriverStatus && SyserAppOption.iAutoStop!=0)
		{
#ifndef __DEMO__VERSION__
			if(SyserAppOption.iAutoStop==1 || MessageBox(NULL,"Do you want to unload Syser Debugger ?","Syser",MB_YESNO)==IDYES)
				m_SyserInterface.StopSyserDriver();
#endif
		}
		return CLocalWispApp::WndProc(hWnd,message,wParam,lParam);
	case WM_DISPLAYCHANGE:
		if(SyserOption.iVideoDetectMode != SYSER_VDM_KERNEL)
		{
			if(SyserOption.iVideoDetectMode == SYSER_VDM_USER || theApp.m_SyserInterface.m_bAttachFrameBuffer==false)
				theApp.m_SyserInterface.m_SyserDX.LockFrameSurfacer();
		}
		break;
	case WM_WISP_NOTIFY_ICON:
		{
			switch(lParam)
			{
				case WM_RBUTTONUP:
					m_SyserInterface.UpdateDriverStatus();
					GetCursorPos(&pt);
					SetForegroundWindow(m_hLocalWnd);
					TrackPopupMenu(m_hSubNotifyMenu,0,pt.x,pt.y,0,m_hLocalWnd,NULL);
					return true;
				case WM_LBUTTONDOWN:
					m_SyserInterface.UpdateDriverStatus();
					ShowWindow(m_hLocalWnd,SW_NORMAL);
					BringWindowToTop(m_hLocalWnd);
					SetForegroundWindow(m_hLocalWnd);
					return true;
			}
		}
		break;
	case WM_DRAWCLIPBOARD:
		theApp.GetClipboardString();
		return CLocalWispApp::WndProc(hWnd,message,wParam,lParam);
		break;
	case WM_SYSER_GET_CLIPBOARD_STRING:
		m_SyserInterface.RecvClipboardString();
		break;
	case WM_SHOWWINDOW:
		break;
	case WM_COPYDATA:
		{
			WCHAR CmdBuffer[MAX_FN_LEN+32];
			int Length;
			PCOPYDATASTRUCT pCopyData;
			pCopyData=(PCOPYDATASTRUCT)lParam;
			switch(pCopyData->dwData)
			{
			case COPYDATA_CMD_LOAD_SDS:
				Length = TStrCpy(CmdBuffer,"loadsds ");
				AnsiToUnicode((PCSTR)pCopyData->lpData,&CmdBuffer[Length],sizeof(CmdBuffer)/sizeof(WCHAR)-Length);
				m_MainFrame.m_ConsoleWnd.RunCmd(CmdBuffer);
				break;
			case COPYDATA_CMD_UNLOAD_SDS:
				Length = TStrCpy(CmdBuffer,"unloadsds ");
				AnsiToUnicode((PCSTR)pCopyData->lpData,&CmdBuffer[Length],sizeof(CmdBuffer)/sizeof(WCHAR)-Length);
				m_MainFrame.m_ConsoleWnd.RunCmd(CmdBuffer);
				break;
			case COPYDATA_CMD_TRANSLATE_SDS:
				Length = TStrCpy(CmdBuffer,"tsf ");
				AnsiToUnicode((PCSTR)pCopyData->lpData,&CmdBuffer[Length],sizeof(CmdBuffer)/sizeof(WCHAR)-Length);
				m_MainFrame.m_ConsoleWnd.RunCmd(CmdBuffer);
				break;
			case COPYDATA_CMD_LOAD:
				Length = TStrCpy(CmdBuffer,"load ");
				AnsiToUnicode((PCSTR)pCopyData->lpData,&CmdBuffer[Length],sizeof(CmdBuffer)/sizeof(WCHAR)-Length);
				m_MainFrame.m_ConsoleWnd.RunCmd(CmdBuffer);
				break;
			}
		}
		break;
	case WM_SYSER_UNINSTALL:
		SyserAppOption.iAutoStop = 0;
		PostQuitMessage(0);
		return true;
	case WM_SYSER_UPDATE_DBG_MSG:
		theApp.m_SyserInterface.UpdateDbgMsg(theApp.m_SyserInterface.m_hDbgMsgDevice);
		break;
	case WM_SYSER_UPDATE_DRV_STATE:
		theApp.m_SyserInterface.UpdateDriverStatus();
		break;
	case WM_SYSER_APP_RELOAD_CFG:
		theApp.LoadCFG();
		OUTPUT(WSTR("%<F>SyserLoader : Reload SyserApp.cfg !\n"));
		break;
	case WM_COMMAND:
		{
			switch(wParam)
			{
				case ID_MENU_EXIT:
					DestroyWindow(m_hLocalWnd);
					return true;
				case ID_MENU_SHOW:
					if(IsWindowVisible(m_hLocalWnd))
						ShowWindow(m_hLocalWnd,SW_HIDE);
					else
						ShowWindow(m_hLocalWnd,SW_SHOW);
					return true;
				case ID_MENU_ENABLE_SYSER:
					m_SyserInterface.StartSyserDriver();
					return true;
				case ID_MENU_DISABLE_SYSER:
					m_SyserInterface.StopSyserDriver();
					return true;
			}
		}
		break;
	default:
		return CLocalWispApp::WndProc(hWnd,message,wParam,lParam);
	}
	return true;
}

bool CSyserApp::CheckNewVersion()
{
	/*
	INTERNET_PROXY_INFO* pProxy;
	char Proxybuf[128];
	DWORD nProxyPort;
	pProxy = GetIEDefaultProxy(Proxybuf,&nProxyPort);
	if(pProxy)
	{
		m_UpdateNewVersionDownload.SetProxy(Proxybuf,(unsigned short)nProxyPort);
		delete pProxy;
	}
	//char Buffer[1024];
	//int ReturnedLen;
	//int retvalue;
	*/
	ShellExecute(NULL,"open","http://www.sysersoft.com/queryversion.php?version=" VER_PRODUCTVERSION_STR "&date=" __DATE__,NULL,NULL,SW_SHOWMAXIMIZED);
	//retvalue = m_UpdateNewVersionDownload.DownloadToBuffer("http://www.sysersoft.com/queryversion.php?app=syserapp.exe" VER_PRODUCTVERSION_STR ,Buffer,sizeof(Buffer),&ReturnedLen);
	return true;
}

INTERNET_PROXY_INFO* CSyserApp::GetIEDefaultProxy(LPTSTR lpszProxy,DWORD *nProxyPort)
{
	INTERNET_PROXY_INFO* pIProxyInfo;
	DWORD ErrorNum;
	char *StrPort;
	DWORD RetLength=sizeof(INTERNET_PROXY_INFO);
	BOOL bRet;
	if(lpszProxy)
		lpszProxy[0]=0;
	if(nProxyPort)
		*nProxyPort=0;
	pIProxyInfo = (INTERNET_PROXY_INFO*)new char[sizeof(INTERNET_PROXY_INFO)];
	memset(pIProxyInfo,0,RetLength);

	bRet = InternetQueryOption(NULL,INTERNET_OPTION_PROXY,pIProxyInfo,&RetLength);
	if(bRet==false)
	{
		ErrorNum = GetLastError();
		if(ErrorNum==ERROR_INSUFFICIENT_BUFFER)
		{
			pIProxyInfo = (INTERNET_PROXY_INFO*)new char[RetLength];
			memset(pIProxyInfo,0,RetLength);
			bRet = InternetQueryOption(NULL,INTERNET_OPTION_PROXY,pIProxyInfo,&RetLength);
		}
	}
	if(bRet==false)
	{
		delete pIProxyInfo;
		pIProxyInfo=NULL;
	}
	else
	{
		if(pIProxyInfo->dwAccessType==INTERNET_OPEN_TYPE_DIRECT)
		{
			delete pIProxyInfo;
			pIProxyInfo=NULL;
		}else
		{
			if(pIProxyInfo->dwAccessType==INTERNET_OPEN_TYPE_PROXY)
			{
				StrPort=TStrChr(pIProxyInfo->lpszProxy,':');
				if(StrPort==NULL)
				{
					delete pIProxyInfo;
					pIProxyInfo=NULL;
				}else
				{
					if(SDecStrToNum(&StrPort[1],&ErrorNum))
					{
						if(nProxyPort)
							*nProxyPort=ErrorNum;
						if(lpszProxy)
						{
							StrPort[0]=0;
							TStrCpy(lpszProxy,pIProxyInfo->lpszProxy);
							StrPort[0]=':';
						}
					}
					else
					{
						delete pIProxyInfo;
						pIProxyInfo=NULL;
					}
				}
			}
		}
	}
	
	return 	pIProxyInfo;
}

LPTSTR CSyserApp::GetIEDefaultProxyUserName(LPTSTR lpszUserName)
{
	BOOL bRet;
	char Buffer[128];
	DWORD RetLength=sizeof(Buffer);
	lpszUserName[0]=0;
	bRet = InternetQueryOption(NULL,INTERNET_OPTION_PROXY_USERNAME,Buffer,&RetLength);
	if(bRet==false)
		return NULL;
	TStrCpy(lpszUserName,Buffer);
	return lpszUserName;
}

LPTSTR CSyserApp::GetIEDefaultProxyPassword(LPTSTR lpszPassword)
{
	BOOL bRet;
	char Buffer[128];
	DWORD RetLength=sizeof(Buffer);
	lpszPassword[0]=0;
	bRet = InternetQueryOption(NULL,INTERNET_OPTION_PROXY_PASSWORD,Buffer,&RetLength);
	if(bRet==false)
		return NULL;
	TStrCpy(lpszPassword,Buffer);
	return lpszPassword;
}

void CSyserApp::LoadHistroy()
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
		TStrCpyLimit(Item.FileName,(PCSTR)*Iter,MAX_FN_LEN);
		Item.Style = Style;
		if(gpFileIO->IsFileExist(Item.FileName))
			m_HistroyList.Append(Item);
	}
	TXTFile.Close();
	m_bHistroyModified = false;
	WISP_MENU_ITEM*pMenuItem = (WISP_MENU_ITEM*)m_MainFrame.m_MainMenu.GetItemByName(WSTR("Recent Files"));
	if(pMenuItem && m_HistroyList.Count())
	{
		CWispMenu*pMenu = pMenuItem->pSubMenu;
		pMenu->RemoveAllItem();
		int CmdID=EVENT_ID_RECENT_FILE_SYSERAPP+1;
		for(TList<RECENT_HISTROY_ITEM>::IT Iter = m_HistroyList.Begin();Iter!=m_HistroyList.End()&&CmdID<=EVENT_ID_RECENT_FILE_SYSERAPP_END;Iter++)
		{
			AnsiToUnicode(Iter->FileName,szBuffer,MAX_FN_LEN);
			CWispDIB*pTypeDIB;
			PCSTR pExtName = TGetFileExt((PCSTR)Iter->FileName);
			if(pExtName && TStrICmp(pExtName,"exe")==0)
				pTypeDIB = WispTKDIBListDIB("\\Toolbar.bmp",16,16,102);
			else
				pTypeDIB = WispTKDIBListDIB("\\Toolbar.bmp",16,16,15);
			pMenu->InsertItem(-1,szBuffer,WISP_MIS_NORMAL,CmdID,pTypeDIB);
			CmdID++;
		}
		pMenu->AdjustPopupMenuSize();
	}
}

void CSyserApp::SaveHistroy()
{
	char szBuffer[256];
	char szFileName[MAX_FN_LEN];
	CImageFileStream File;
	GetModulePath(szFileName);
	TStrCat(szFileName,"Histroy.lst");
	if(File.Create(szFileName)==false)
		return;
	for(TList<RECENT_HISTROY_ITEM>::IT Iter = m_HistroyList.Begin();Iter!=m_HistroyList.End();Iter++)
	{
		File.Puts(Iter->FileName,TStrLen(Iter->FileName));
		TSPrintf(szBuffer,"|%X\r\n",Iter->Style);
		File.Puts(szBuffer,TStrLen(szBuffer));
	}
	File.Close();
}

void CSyserApp::InsertHistroy(PCSTR szFileName,DWORD Style)
{
	RECENT_HISTROY_ITEM Item;
	TList<RECENT_HISTROY_ITEM>::IT Iter;
	TStrCpyLimit(Item.FileName,szFileName,MAX_FN_LEN);
	Item.Style = Style;
	Iter = m_HistroyList.Find(Item);
	if(Iter!=m_HistroyList.End())
	{
		if(Iter->Style == Style)
			return;
		m_HistroyList.Remove(Iter);
	}
	if(m_HistroyList.Count()<EVENT_ID_RECENT_FILE_SYSERAPP_END-EVENT_ID_RECENT_FILE_SYSERAPP)
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
