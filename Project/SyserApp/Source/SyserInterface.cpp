#include "StdAfx.h"
#include "SyserApp.h"
#include "SyserInterface.h"
#include "LoadSourceFile.h"
#include "ModifyBoot.h"
#include "SNCheck.h"

CSyserInterface::CSyserInterface(void)
{
	m_bCaptureDbgMsg = true;
	m_bRecvClipboard = false;
	m_bAttachFrameBuffer = false;
	GetModulePath(m_LoadDllName);
	TStrCat(m_LoadDllName,"LoadDll.exe");
	m_VerType = SN_ERROR;
}

CSyserInterface::~CSyserInterface(void)
{
}

void CSyserInterface::UpdateDbgMsg(HANDLE hDevice)
{
	WCHAR szBufferW[1024];
	CHAR szBuffer[1024];
	int cbReturn = 0;
	CWispConsoleWnd*pConsoleWnd = &((CMainFrame*)theApp.m_pRootWnd)->m_ConsoleWnd;
	do
	{
		ReadFile(hDevice,szBuffer,sizeof(szBuffer),(DWORD*)&cbReturn,NULL);
		if(cbReturn)
		{
			AnsiToUnicode(szBuffer,szBufferW,sizeof(szBuffer));
			pConsoleWnd->m_pWispBase->EnterCriticalSection();
			pConsoleWnd->LockUpdate();
			pConsoleWnd->Output(szBufferW);
			pConsoleWnd->EnsureInputVisible();
			pConsoleWnd->UnlockUpdate();
			pConsoleWnd->Update();
			pConsoleWnd->m_pWispBase->LeaveCriticalSection();
		}
	}while(cbReturn==sizeof(szBuffer));
}

void CSyserInterface::ChangeMsgFilter()
{
	if(theApp.m_SyserInterface.m_hDbgMsgDevice == INVALID_HANDLE_VALUE)
	{
		OUTPUT(WSTR("%<F>SyserLoad : Fail to change debug message filter !\n"));
		return;
	}
	DWORD dummy;
	DeviceIoControl(theApp.m_SyserInterface.m_hDbgMsgDevice,IOCTL_SDBGMSG_RELOAD_CFG,NULL,NULL,NULL,NULL,&dummy,NULL);	
}

void CSyserInterface::UpdateWindow()
{
	InvalidateRect(GetTopWindow(NULL),NULL,TRUE);
}

void CSyserInterface::MsgUpdateThread()
{
	HANDLE hEvent;
	CWispConsoleWnd*pConsoleWnd = &((CMainFrame*)theApp.m_pRootWnd)->m_ConsoleWnd;
	theApp.m_SyserInterface.m_hDbgMsgDevice = CreateFile("\\\\.\\SyserDbgMsg",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(theApp.m_SyserInterface.m_hDbgMsgDevice == INVALID_HANDLE_VALUE)
		return;
	hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	if(hEvent == NULL)
	{
		CloseHandle(theApp.m_SyserInterface.m_hDbgMsgDevice);
		return;
	}
	DWORD dummy;
	DeviceIoControl(theApp.m_SyserInterface.m_hDbgMsgDevice,IOCTL_SDBGMSG_REG_EVENT,&hEvent,sizeof(hEvent),NULL,NULL,&dummy,NULL);
	while(theApp.m_MainFrame.m_ConsoleWnd.IsWindow())
	{
		if(theApp.m_SyserInterface.m_bCaptureDbgMsg)
		{
			::SendMessage(theApp.m_hLocalWnd,WM_SYSER_UPDATE_DBG_MSG,0,0);
		}
		WaitForSingleObject(hEvent,INFINITE);
	}
	CloseHandle(hEvent);
	CloseHandle(theApp.m_SyserInterface.m_hDbgMsgDevice);
}

void CSyserInterface::ProgressSetRange(int Range)
{
	theApp.m_MainFrame.m_ProgressForm.m_pProgessCtrl->SetRange(1,Range);
	theApp.m_MainFrame.m_ProgressForm.m_pProgessCtrl->SetPos(1);
	theApp.m_MainFrame.m_ProgressForm.Update();
}

void CSyserInterface::ProgressSetPos(int Pos)
{
	theApp.m_MainFrame.m_ProgressForm.m_pProgessCtrl->SetPos(Pos);
	theApp.m_MainFrame.m_ProgressForm.Update();
}

bool CSyserInterface::Init()
{
	UINT StartType;
	m_VerInfo.dwOSVersionInfoSize = sizeof(m_VerInfo);
	GetVersionEx(&m_VerInfo);
	if(m_VerInfo.dwMajorVersion < 5)
	{
		if(MessageBox(theApp.m_hLocalWnd,"Syser isn't support your windows system version!\nContinue?","Error",MB_YESNO)==IDNO)
			return false;
	}
	m_hMutex = OpenMutex(MUTEX_ALL_ACCESS,false,"Syser Interface");
	if(m_hMutex)
	{
		MessageBox(theApp.m_hLocalWnd,"Syser Debugger is already running !","Syser",MB_OK);
		return false;
	}
	m_hMutex = CreateMutex(NULL,false,"Syser Interface");
	if(IsDriverActive("SyserBoot")==false)
	{
		InstallDependDriver("SyserBoot","SysBoot.sys");
		if(MessageBox(NULL,"Syser Boot Module isn't actived !\nYou need to reboot then you can start syser debugger!\nReboot now?","Warnning",MB_YESNO)==IDYES)
		{
			CProcess::GetPrivilege(SE_SHUTDOWN_NAME);
			ExitWindowsEx(EWX_REBOOT,0);
			return false;
		}
		return false;
	}
	if(IsDriverActive("sptd"))
	{
		MessageBox(NULL,"Deamon Tools SPTD isn't compatible with kernel debuggers such as Syser!\n"
						"You can type command \"rmsptd\" to disable it !",
						"Warning",MB_OK);
	}
	if(IsDriverActive("dump_wmimmc"))
	{
		MessageBox(	NULL,
			"nProtect dump_wmimmc.sys isn't compatible with kernel debuggers !\nMaybe cause BSOD !",
			"Warning",MB_OK);
	}
	IsSysBootFrameBufferAvailable();

	m_SyserDX.Init();
	if(m_VerInfo.dwMajorVersion>=6)
	{//Vista开始Basic颜色方案
	}
	UpdateDriverStatus();
	InstallDependDriver("SyserBoot","SysBoot.sys",SERVICE_BOOT_START,DERIVER_GROUP_NAME,GROUP_SYSBOOT_ORDER);
	InstallDependDriver("SyserLanguage","SysLang.sys",SERVICE_BOOT_START,DERIVER_GROUP_NAME,GROUP_SYSLANG_ORDER);
	InstallDependDriver("SDbgMsg","SDbgMsg.sys",SERVICE_BOOT_START,DERIVER_GROUP_NAME,GROUP_SDBGMSG_ORDER);
	if(IsDriverActive(DRIVER_NAME)==false)
	{
		if(IsDriverActive("SyserLanguage")==false)
			StartDriver("SyserLanguage");
		if(IsDriverActive("SDbgMsg")==false)
			StartDriver("SDbgMsg");
	}
	InstallDependData("Syser.dat;Wisp.dat;libfunc.fdc;APIDef.lib");
	if(GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\Start",&StartType,sizeof(StartType))==false)
		StartType = SERVICE_DEMAND_START;
	InstallDependDriver(DRIVER_NAME,"Syser.sys",StartType,DERIVER_GROUP_NAME,GROUP_SYSER_ORDER);
	if(m_bSyserDriverStatus==false && SyserAppOption.iAutoStart!=0)
	{
		if(SyserAppOption.iAutoStart==1 || MessageBox(theApp.m_hLocalWnd,"Start Syser Debugger ?","Syser",MB_YESNO)==IDYES)
			StartSyserDriver();
	}
	CreateThread(MsgUpdateThread);
	return true;
}

void CSyserInterface::Release()
{
	m_SyserDX.UnlockFrameSurfacer();
	m_SyserDX.Release();
	CloseHandle(m_hMutex);
}

void CSyserInterface::IsSysBootFrameBufferAvailable()
{
	DWORD cbReturn;
	HANDLE hDevice;
	SYSER_FRAME_BUFFER FrameBuffer;
	m_bAttachFrameBuffer = false;
	hDevice = CreateFile("\\\\.\\SyserBoot",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(hDevice==INVALID_HANDLE_VALUE)
		return;
	STZeroMemory(FrameBuffer);
	DeviceIoControl(hDevice,IOCTL_SYSER_BOOT_GET_FRAME_BUFFER,NULL,0,&FrameBuffer,sizeof(FrameBuffer),&cbReturn,NULL);
	CloseHandle(hDevice);
	if(FrameBuffer.Buffer)
		m_bAttachFrameBuffer = true;
}

bool CSyserInterface::StartSyserDriver()
{
	if(IsDriverActive(DRIVER_NAME))
		return true;
	InstallDependDriver(DRIVER_NAME,"Syser.sys",-1);
	InstallDependData("Syser.dat;Wisp.dat;libfunc.fdc;APIDef.lib");	
	if(StartDriver(DRIVER_NAME)==false)
	{
		if(m_VerInfo.dwMajorVersion>=6)
		{
			MessageBox(theApp.m_hLocalWnd,"Fail to load Syser !\nPlease run Syser Loader with \"Admin\" !","Error",MB_OK);
		}
		else
		{
			MessageBox(theApp.m_hLocalWnd,"Fail to load Syser !","Error",MB_OK);
		}
		return false;
	}
	if(SyserOption.iVideoDetectMode != SYSER_VDM_KERNEL)
	{
		if(SyserOption.iVideoDetectMode == SYSER_VDM_USER || m_bAttachFrameBuffer==false)
			m_SyserDX.LockFrameSurfacer();
	}
		
	UpdateDriverStatus();
	//多核下可能还有GUI线程在跑,所以手动刷下屏幕
	UpdateWindow();
	if(m_VerType==SN_ERROR)
	{
		DWORD VerType=0;
		GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\VerType",&VerType,sizeof(VerType));
		if(VerType!=SN_ERROR)
		{
			m_VerType = (SYSER_SN_TYPE)VerType;
			theApp.m_MainFrame.m_MainMenu.RemoveItem(EVENT_ID_BUYNOW);
			theApp.m_MainFrame.GetVersionString();
			theApp.m_MainFrame.Update();
		}
	}
	return m_bSyserDriverStatus;
}

void CSyserInterface::StopSyserDriver()
{
	if(DisableDriver(DRIVER_NAME))
		UpdateDriverStatus();
	m_SyserDX.UnlockFrameSurfacer();
}

void CSyserInterface::ReloadConfig()
{
	DWORD cbReturn;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return;
	DeviceIoControl(hSyser,IOCTL_SYSER_RELOAD_CONFIG,NULL,0,NULL,0,&cbReturn,NULL);
	CloseHandle(hSyser);
}

void CSyserInterface::UpdateDriverStatus()
{
	bool bNewState = IsDriverActive(DRIVER_NAME);
	if(bNewState!=m_bSyserDriverStatus)
	{
		m_bSyserDriverStatus = bNewState;
		theApp.m_MainFrame.UpdateSyserDriverItem(m_bSyserDriverStatus);
		EnableMenuItem(theApp.m_hSubNotifyMenu,ID_MENU_ENABLE_SYSER,m_bSyserDriverStatus ? MF_DISABLED|MF_GRAYED:MF_ENABLED);
		EnableMenuItem(theApp.m_hSubNotifyMenu,ID_MENU_DISABLE_SYSER,m_bSyserDriverStatus ? MF_ENABLED:MF_DISABLED|MF_GRAYED);
		theApp.ModifyNotifyIcon(bNewState?IDI_ICON_SYSERAPP:IDI_ICON_SYSER_OFF);
	}
}

bool CSyserInterface::RemoveDependData(PCSTR FileNameList)
{
	char szDesFile[MAX_FN_LEN],szFileName[MAX_FN_LEN],*pszDesFile;
	PCSTR szBegin,szEnd;
	GetSystemDirectory(szDesFile,MAX_FN_LEN);
	TStrCat(szDesFile,"\\drivers\\");
	pszDesFile = szDesFile+TStrLen(szDesFile);
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
		DeleteFile(szDesFile);
		szBegin = szEnd;
	}
	return true;	
}

bool CSyserInterface::InstallServiceEventLog(PCSTR ServiceName,PCSTR MessageDllFullName,DWORD TypesSupported,bool bSystemIoLog)
{
	DWORD Disposition,dwSize;
	HKEY hKey;
	CHAR FullName[260],Value[260];
	strcpy_s(FullName,sizeof(FullName),"SYSTEM\\CurrentControlSet\\Services\\Eventlog\\System\\");
	strcat_s(FullName,sizeof(FullName),ServiceName);
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE,FullName,0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	strcpy_s(Value,sizeof(Value),"%SystemRoot%");
	strcat_s(Value,sizeof(Value),"\\System32\\IoLogMsg.dll;");
	strcat_s(Value,sizeof(Value),MessageDllFullName);
	dwSize = (DWORD)strlen(Value);	
	if(RegSetValueEx(hKey,"EventMessageFile",0,REG_SZ,(BYTE*)Value,dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	if(RegSetValueEx(hKey,"TypesSupported",0,REG_DWORD,(BYTE*)&TypesSupported,sizeof(TypesSupported)) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	RegCloseKey(hKey);
	return true;
}

bool CSyserInterface::UninstallServiceEventLog(PCSTR ServiceName)
{
	DWORD Disposition;
	HKEY hKey;
	CHAR FullName[260];
	strcpy_s(FullName,sizeof(FullName),"SYSTEM\\CurrentControlSet\\Services\\Eventlog\\System\\");
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE,FullName,0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	RegDeleteKey(hKey,ServiceName);
	RegCloseKey(hKey);
	return true;
}

bool CSyserInterface::InstallDependDriver(PCSTR ServiceName,PCSTR FileName,UINT StartType,PCSTR GroupName,DWORD Tag)
{
	char szDriver[MAX_FN_LEN],szNewDriver[MAX_FN_LEN];
	TStrCpy(szDriver,"system32\\drivers\\");
	TStrCat(szDriver,FileName);
	if(StartType!=-1)
		InstallDriver(ServiceName,szDriver,StartType,GroupName,Tag);
 
	GetSystemDirectory(szDriver,sizeof(szDriver));
	TStrCat(szDriver,"\\drivers\\");
	TStrCat(szDriver,FileName);

	GetModulePath(szNewDriver);
	TStrCat(szNewDriver,FileName);

	CPEFile PEFile,NewPEFile;
	if(PEFile.Open(szDriver)==false)
		goto Reinstall;
	if(NewPEFile.Open(szNewDriver)==false)
	{
		PEFile.Close();
		return false;
	}
	PEFile.Close();
	NewPEFile.Close();
	if(PEFile.m_PEHead.TimeDateStamp == NewPEFile.m_PEHead.TimeDateStamp)
		return true;
Reinstall:
	if(CopyFile(szNewDriver,szDriver,FALSE)==FALSE)
		return false;
	return true;
}

void CSyserInterface::SendClipboardString()
{
	int Length;
	char szBuffer[256];
	WCHAR wszBuffer[256];
	DWORD cbReturn;
	PSTR szString;
	HANDLE hClipboard;
	if(m_bRecvClipboard)
		return;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return;
	if(OpenClipboard(theApp.m_hLocalWnd)==FALSE)
	{
		CloseHandle(hSyser);
		return;
	}
	hClipboard = GetClipboardData(CF_TEXT);
	if(hClipboard==NULL)
	{
		CloseClipboard();
		CloseHandle(hSyser);
		return;
	}
	szString =(PSTR)GlobalLock(hClipboard);
	if(szString==NULL)
	{
		GlobalUnlock(hClipboard);
		CloseClipboard();
		CloseHandle(hSyser);
		return;
	}
	Length = TStrCpyLimit(szBuffer,szString,sizeof(szBuffer));
	AnsiToUnicode(szString,wszBuffer,sizeof(wszBuffer)/sizeof(WCHAR));
	theApp.m_ClipboardString = wszBuffer;
	DeviceIoControl(hSyser,IOCTL_SYSER_SET_CLIP_BOARD,szBuffer,Length+1,NULL,0,&cbReturn,NULL);
	GlobalUnlock(hClipboard);
	CloseClipboard();
	CloseHandle(hSyser);
}

void CSyserInterface::RecvClipboardString()
{
	WCHAR wszBuffer[1024];
	char szBuffer[1024];
	DWORD cbReturn;
	if(m_bRecvClipboard)
		return;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return;
	cbReturn = 0;
	*szBuffer = 0;
	DeviceIoControl(hSyser,IOCTL_SYSER_GET_CLIP_BOARD,NULL,NULL,szBuffer,sizeof(szBuffer),&cbReturn,NULL);
	if(cbReturn==0)
	{
		CloseHandle(hSyser);
		return;
	}
	AnsiToUnicode(szBuffer,wszBuffer,1024);
	m_bRecvClipboard = true;
	theApp.SetClipboardString(wszBuffer);
	m_bRecvClipboard = false;
	CloseHandle(hSyser);
}

void CSyserInterface::UpdateThread()
{
	char VersionBuf[200];
	int nRetLen;
	int retval;
	CHttpDownload Download;
	char buffer[200];
	DWORD dwHandle;	 
	DWORD dwSize;
	char* lpData;
	unsigned int nLen;
	void* ptr;
	char SystemPath[MAX_PATH];
	memset(VersionBuf,0,sizeof(VersionBuf));
	memset(buffer,0,sizeof(buffer));
	Download.StartupWinsock();
	retval = Download.DownloadToBuffer("http://www.sysersoft.com/download/version.txt",buffer,sizeof(buffer),&nRetLen);	
	Download.CleanupWinsock();
	if(retval!=0)
		return;
	GetSystemDirectory(SystemPath,sizeof(SystemPath));
	strcat(SystemPath,"\\drivers\\syser.sys");
	dwSize=GetFileVersionInfoSize(SystemPath,&dwHandle);
	if(dwSize==0)
		return;		 
	lpData=new char[dwSize+1];
	if(lpData==NULL)
		return;
	if(GetFileVersionInfo(SystemPath,0,dwSize,lpData)==false)
	{
		delete []lpData;
		return;	
	}
	if(VerQueryValue(lpData,"\\StringFileInfo\\040904B0\\ProductVersion",&ptr,&nLen)==false)
	{
		delete []lpData;
		return;	
	}
	delete []lpData;
	if(strcmp(buffer,(char*)ptr)==0)
	{
		delete []lpData;
		return;	
	}	
}
PCSTR	szTranslateFileName;
PSTR	szTranslateSymbolFileName;
bool	bTranslateResult;

void CSyserInterface::TranslateThread()
{
	theApp.m_SourceDebug.m_pfnSetRange = ProgressSetRange;
	theApp.m_SourceDebug.m_pfnSetPos = ProgressSetPos;
	bTranslateResult = theApp.m_SourceDebug.TranslateSymbolFile(szTranslateFileName,szTranslateSymbolFileName,true);
	theApp.m_MainFrame.m_ProgressForm.Destroy();
}

bool CSyserInterface::TranslateSymbolFile(IN PCSTR szFileName,OUT PSTR szSymbolFileName,bool bOverWrite)
{
	WCHAR wszFileName[MAX_FN_LEN],szBuffer[512];
	if(bOverWrite==false && theApp.m_SourceDebug.IsTranslated(szFileName,szSymbolFileName))
		return true;
	bTranslateResult = false;
	szTranslateFileName = szFileName;
	szTranslateSymbolFileName = szSymbolFileName;
	szSymbolFileName[0]=0;
	theApp.m_MainFrame.m_ProgressForm.CreateForm();
	CreateThread(TranslateThread);
	AnsiToUnicode(TGetFileName(szFileName),wszFileName,MAX_FN_LEN);
	TSPrintf(szBuffer,WSTR("Translate %s symbols to SDS"),wszFileName);
	theApp.m_MainFrame.m_ProgressForm.SetProgressText(szBuffer);
	theApp.m_MainFrame.m_ProgressForm.Show(WISP_SH_MODAL_BLOCK);
	return bTranslateResult;
}


bool CSyserInterface::TranslateExportSymbolFile(IN PCSTR szFileName,OUT PSTR szSymbolFileName)
{
	if(theApp.m_NoPDBSymbol.Init())
		return theApp.m_NoPDBSymbol.TranslateSymbolFile(szFileName,szSymbolFileName);	
	return false;
}

bool CSyserInterface::GetModuleFullPath(PCSTR szModuleName,PCSTR szMainModule,PSTR szFullName)
{
	CHAR szBuffer[MAX_FN_LEN];
	TGetFilePath(szMainModule,szBuffer);
	TStrCat(szBuffer,"\\");
	TStrCat(szBuffer,szModuleName);
	if(gpFileIO->IsFileExist(szBuffer))
	{
		TStrCpy(szFullName,szBuffer);
		return true;
	}
	GetSystemDirectory(szBuffer,MAX_FN_LEN);
	TStrCat(szBuffer,"\\");
	TStrCat(szBuffer,szModuleName);
	if(gpFileIO->IsFileExist(szBuffer))
	{
		TStrCpy(szFullName,szBuffer);
		return true;
	}
	GetWindowsDirectory(szBuffer,MAX_FN_LEN);
	TStrCat(szBuffer,"\\");
	TStrCat(szBuffer,szModuleName);
	if(gpFileIO->IsFileExist(szBuffer))
	{
		TStrCpy(szFullName,szBuffer);
		return true;
	}
	return false;
}

bool CSyserInterface::LoadDepModuleSDS(PCSTR szMainModule,bool bDriver)
{
	CHAR szFileName[MAX_FN_LEN],szSymbolFileName[MAX_FN_LEN];
	CPEFile PEFile;
	if(PEFile.Open(szMainModule)==false)
		return false;
	for(int n=0;n<PEFile.m_ImportModuleCount;n++)
	{
		if(GetModuleFullPath(PEFile.m_ImportModule[n].FileName,szMainModule,szFileName))
		{
			if(TranslateSymbolFile(szFileName,szSymbolFileName,false))
				LoadSDS(szSymbolFileName);
		}
	}
	PEFile.Close();
	return true;
}

bool CSyserInterface::LoadModule(PCSTR szFilename,PCSTR szCmdLine,DWORD Style)
{
	bool Result;
	if(*szFilename==0)
		return false;
	if(m_bSyserDriverStatus==false)
	{
		OUTPUT(WSTR("%<3>Error : Syser isn't actived !\n"));
		return false;
	}
	if(TStrICmp(TGetFileExt(szFilename),"sys")==0)
	{
		Result = theApp.m_SyserInterface.LaunchDriverForDebugging(szFilename,Style);
	}
	else
	{
		Result = theApp.m_SyserInterface.LaunchAppForDebugging(szFilename,szCmdLine,Style);
	}
	if(!Result)
	{
		OUTPUT(WSTR("%<3>Error : Fail to load !\n"));
		return true;
	}
	theApp.InsertHistroy(szFilename,Style);
	return true;
}

bool CSyserInterface::LaunchAppForDebugging(IN PCSTR FileName,PCSTR szCmdLine,DWORD Style)
{
	char szDir[MAX_FN_LEN];
	DWORD cbReturn;
	SYSER_DEBUG_PROCESS SyserDbgProc;
	char NewSymbolFileName[MAX_FN_LEN];
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return false;

	STZeroMemory(SyserDbgProc);
	ZeroMemory(NewSymbolFileName,sizeof(NewSymbolFileName));
	if(_GET_WORD(FileName)=='\\\\')
		*SyserDbgProc.ExeFullPathName=0;
	else
		TStrCpy(SyserDbgProc.ExeFullPathName,"\\??\\");
	TStrCat(SyserDbgProc.ExeFullPathName,FileName);
	if(Style & SDP_LOAD_SDS)
	{
		if(TranslateSymbolFile(FileName,NewSymbolFileName,false))
		{
			if(_GET_WORD(NewSymbolFileName)=='\\\\')
			{
				TStrCpy(SyserDbgProc.SymbolFileName,"\\Device\\LanmanreDirector\\");
				TStrCat(SyserDbgProc.SymbolFileName,&NewSymbolFileName[2]);
			}
			else
			{
				TStrCpy(SyserDbgProc.SymbolFileName,"\\??\\");
				TStrCat(SyserDbgProc.SymbolFileName,NewSymbolFileName);
			}
		}
	}

	TGetFilePath(FileName,szDir);
	PSTR pszExtName = TGetFileExt(FileName);
	if(pszExtName && TStrICmp(pszExtName,"dll")==0)
	{
		if(m_Process.Start(m_LoadDllName,FileName,true,szDir)==false)
		{
			CloseHandle(hSyser);
			return false;
		}
	}
	else
	{
		if(m_Process.Start(FileName,szCmdLine,true,szDir)==false)
		{
			CloseHandle(hSyser);
			return false;
		}
	}
	SyserDbgProc.Style = Style;
	SyserDbgProc.ProcessID = m_Process.m_ProcessID;
	BOOL bRetValue;
	bRetValue = DeviceIoControl(hSyser,IOCTL_SYSER_DEBUG_PROCESS,&SyserDbgProc,sizeof(SYSER_DEBUG_PROCESS),NULL,0,&cbReturn,NULL);
	if(bRetValue==FALSE)
	{
		OUTPUT(WSTR("Syser : Debug application error %08x\n"),GetLastError());
	}
	if(Style & SDP_LOAD_DEP_SDS)
		LoadDepModuleSDS(FileName,false);
	CloseHandle(hSyser);
	theApp.m_MainFrame.Update();
	m_Process.SuspendAllThread(false);
	return true;
}

bool CSyserInterface::LaunchDriverForDebugging(IN PCSTR FileName,DWORD Style)
{	
	DWORD cbReturn;
	SYSER_DEBUG_DRIVER DebugDriver;
	char szDriverName[MAX_FN_LEN],NewSymbolFileName[MAX_FN_LEN];
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return false;
	STZeroMemory(DebugDriver);
	*NewSymbolFileName=0;
	if(Style & SDP_LOAD_SDS)
	{
		if(TranslateSymbolFile(FileName,NewSymbolFileName,false))
		{
			TStrCpy(DebugDriver.SymbolFileName,"\\??\\");
			TStrCat(DebugDriver.SymbolFileName,NewSymbolFileName);
		}
	}
	TGetFileTitle(FileName,szDriverName);
	if(IsDriverActive(szDriverName))
	{
		char szBuffer[512];
		sprintf_s(szBuffer,sizeof(szBuffer),"%s is already actived !\nStop it first?",szDriverName);
		if(MessageBox(theApp.m_hLocalWnd,szBuffer,"Warning",MB_YESNO)==IDYES)
		{
			StopDriver(szDriverName);
		}
		else
		{
			CloseHandle(hSyser);
			return false;
		}
	}
	TStrCpy(DebugDriver.DriverPathName,"\\??\\");
	TStrCat(DebugDriver.DriverPathName,FileName);
	DebugDriver.Style = Style;
	DeviceIoControl(hSyser,IOCTL_SYSER_DEBUG_DRIVER,&DebugDriver,sizeof(SYSER_DEBUG_DRIVER),NULL,0,&cbReturn,NULL);
	if(EnableDriver(szDriverName,FileName)==false)
	{
		CloseHandle(hSyser);
		return false;
	}
	CloseHandle(hSyser);
	return true;
}

bool CSyserInterface::LoadModuleExportSymbols(IN PCSTR szFileName)
{
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return false;
	DWORD cbReturn;
	DeviceIoControl(hSyser,IOCTL_SYSER_LOAD_EXPORT_SYMBOL,(PVOID)szFileName,TStrLen(szFileName)+1,NULL,0,&cbReturn,NULL);
	CloseHandle(hSyser);
	return true;
}

bool CSyserInterface::LoadModuleIDAMapFile(IN PCSTR szIDAMapFile,IN PCSTR szModuleName)
{
	SYSER_LOAD_IDA_MAPFILE LoadIDAMapFile;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return false;
	strcpy_s(LoadIDAMapFile.IDAMapFile,sizeof(LoadIDAMapFile.IDAMapFile),szIDAMapFile);
	strcpy_s(LoadIDAMapFile.ModuleName,sizeof(LoadIDAMapFile.ModuleName),szModuleName);
	DWORD cbReturn;
	DeviceIoControl(hSyser,IOCTL_SYSER_LOAD_IDA_MAPFILE,(PVOID)&LoadIDAMapFile,sizeof(LoadIDAMapFile),NULL,0,&cbReturn,NULL);
	CloseHandle(hSyser);
	return true;
}

bool CSyserInterface::LoadSDS(IN PCSTR SymbolModuleFileName)
{
	DWORD cbReturn;
	SYSER_LOAD_SYMBOL_MODULE LoadSymbolModule;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return false;
	STZeroMemory(LoadSymbolModule);
	if(theApp.m_SourceDebug.IsSymbolFile((char*)SymbolModuleFileName)==false)
	{
		CloseHandle(hSyser);
		return false;
	}
	TStrCpy(LoadSymbolModule.SymbolModuleName,"\\??\\");
	TStrCat(LoadSymbolModule.SymbolModuleName,SymbolModuleFileName);
	DeviceIoControl(hSyser,IOCTL_SYSER_LOAD_SDS	,&LoadSymbolModule,sizeof(LoadSymbolModule),NULL,0,&cbReturn,NULL);
	CloseHandle(hSyser);
	return true;
}

bool CSyserInterface::UnloadSDS(IN PCSTR SymbolModuleFileName)
{
	DWORD cbReturn;
	SYSER_UNLOAD_SYMBOL_MODULE UnloadSymbolModule;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return false;
	cbReturn = sizeof(UnloadSymbolModule);
	ZeroMemory(&UnloadSymbolModule,cbReturn);
	if(theApp.m_SourceDebug.IsSymbolFile(SymbolModuleFileName)==false)
	{
		CloseHandle(hSyser);
		return false;
	}
	TStrCpy(UnloadSymbolModule.SymbolModuleName,"\\??\\");
	TStrCat(UnloadSymbolModule.SymbolModuleName,SymbolModuleFileName);
	DeviceIoControl(hSyser,IOCTL_SYSER_UNLOAD_SDS,&UnloadSymbolModule,cbReturn,NULL,0,&cbReturn,NULL);
	CloseHandle(hSyser);
	return true;
}

bool CSyserInterface::IsSyserRuning()
{
	return m_bSyserDriverStatus;
}

bool CSyserInterface::InstallServiceGroupOrderList()
{
#define MAX_REGISTRY_VALUENAME_LEN 0x4001
#define SWAP_BYTE_ORDER(x) (((x)<<24) | ((x&0xff00)<<16) | ((x&0xff000)>>8)|(x>>24))
	HKEY hKey;
	LONG lOK;
	DWORD dwIndex=0;
	DWORD Disposition,ValueNameLen=MAX_REGISTRY_VALUENAME_LEN;
	STGROUPORDERLIST GroupOrderList;
	if((lOK = RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\GroupOrderList",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition))!=ERROR_SUCCESS)
		return false;
	memset(&GroupOrderList,0,sizeof(STGROUPORDERLIST));
	GroupOrderList.Count=5;
	GroupOrderList.Order1=SWAP_BYTE_ORDER(GROUP_SYSLANG_ORDER);
	GroupOrderList.Order2=SWAP_BYTE_ORDER(GROUP_SDBGMSG_ORDER);
	GroupOrderList.Order3=SWAP_BYTE_ORDER(GROUP_SYSBOOT_ORDER);
	GroupOrderList.Order4=SWAP_BYTE_ORDER(GROUP_SYSER_ORDER);
	GroupOrderList.Order5=SWAP_BYTE_ORDER(GROUP_RESERVES2_ORDER);
	if(RegSetValueEx(hKey,DERIVER_GROUP_NAME,0,REG_BINARY,(BYTE*)&GroupOrderList,sizeof(GroupOrderList)) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	RegCloseKey(hKey);
	return true;
}

bool CSyserInterface::UninstallServiceGroupOrderList()
{
	return DelRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Control\\GroupOrderList\\Syser");
}

bool CSyserInterface::UninstallFileExtAssociate()
{
	HKEY hKey;
	LONG lOK,cbValue;
	char StringBuf[512];
	unsigned char pDataBuf[512];
	char Name[]="SdsFile";
	char Name7[]="InfoTip";
	char Name2[]="Syser Symbol File";
	char Name6[]="prop:FileDescription;Company;FileVersion;Create;Size";
	DWORD dwType,cbData,dwIndex;

	lOK = RegOpenKey(HKEY_CLASSES_ROOT,".sds",&hKey);
	if(lOK==ERROR_SUCCESS)
	{
		cbValue=sizeof(StringBuf);
		lOK = RegQueryValue(hKey,NULL,StringBuf,&cbValue);
		if(lOK==ERROR_SUCCESS)
		{
			if(TStrCmp(StringBuf,Name)==0)
				lOK = RegDeleteValue(hKey,NULL);
			cbData = sizeof(pDataBuf);
			dwIndex=0;
			cbData = sizeof(pDataBuf);
			cbValue=sizeof(StringBuf);
			lOK=RegEnumValue(hKey,dwIndex,StringBuf,(LPDWORD)&cbValue,NULL,&dwType,pDataBuf,&cbData);
			if(lOK==ERROR_NO_MORE_ITEMS)
				lOK = RegDeleteKey(hKey,"");
		}
		lOK = RegCloseKey(hKey);
	}
	lOK = RegOpenKeyEx(HKEY_CLASSES_ROOT,Name,0,KEY_ALL_ACCESS,&hKey);
	if(lOK==ERROR_SUCCESS)
	{
		cbValue=sizeof(StringBuf);
		lOK = RegQueryValue(hKey,NULL,StringBuf,&cbValue);
		if(lOK==ERROR_SUCCESS)
		{
			if(TStrCmp(StringBuf,Name2)==0)
				lOK = RegDeleteValue(hKey,NULL);
		}
		cbData=sizeof(pDataBuf);
		lOK = RegQueryValueEx(hKey,Name7,NULL,&dwType,pDataBuf,&cbData);
		if(lOK==ERROR_SUCCESS)
		{
			if(TStrCmp(pDataBuf,Name6)==0)
				lOK = RegDeleteValue(hKey,Name7);
		}

		cbData = sizeof(pDataBuf);
		dwIndex=0;
		cbData = sizeof(pDataBuf);
		cbValue=sizeof(StringBuf);
		lOK=RegEnumValue(hKey,dwIndex,StringBuf,(LPDWORD)&cbValue,NULL,&dwType,pDataBuf,&cbData);
		if(lOK==ERROR_NO_MORE_ITEMS)
		{
			lOK = RegDeleteKey(hKey,"shell\\open\\command");
			lOK = RegDeleteKey(hKey,"shell\\open");
			lOK = RegDeleteKey(hKey,"shell\\SyserLoad\\command");
			lOK = RegDeleteKey(hKey,"shell\\SyserLoad");
			lOK = RegDeleteKey(hKey,"shell");
			lOK = RegDeleteKey(hKey,"");
		}
		lOK = RegCloseKey(hKey);
	}
	lOK = RegOpenKeyEx(HKEY_CLASSES_ROOT,"exefile\\shell\\ SyserLoad\\command",0,KEY_ALL_ACCESS,&hKey);
	if(lOK==ERROR_SUCCESS)
	{
		lOK = RegDeleteKey(hKey,"");
		lOK = RegCloseKey(hKey);
	}
	lOK = RegOpenKeyEx(HKEY_CLASSES_ROOT,"exefile\\shell\\ SyserLoad",0,KEY_ALL_ACCESS,&hKey);
	if(lOK==ERROR_SUCCESS)
	{
		lOK = RegDeleteKey(hKey,"");
		lOK = RegCloseKey(hKey);
	}
	lOK = RegOpenKeyEx(HKEY_CLASSES_ROOT,"sysfile\\shell\\ SyserLoad\\command",0,KEY_ALL_ACCESS,&hKey);
	if(lOK==ERROR_SUCCESS)
	{
		lOK = RegDeleteKey(hKey,"");
		lOK = RegCloseKey(hKey);
	}
	lOK = RegOpenKeyEx(HKEY_CLASSES_ROOT,"sysfile\\shell\\ SyserLoad",0,KEY_ALL_ACCESS,&hKey);
	if(lOK==ERROR_SUCCESS)
	{
		lOK = RegDeleteKey(hKey,"");
		lOK = RegCloseKey(hKey);
	}
	return true;
}


bool CSyserInterface::InstallFileExtAssociate()
{
	char CommandLine[1024];
	char Name[]="SdsFile";
	char Name2[]="Syser Symbol File";
	char Name3[]="SyserLoad";
	char Name4[]="Load into S&yser";
	char Name5[]="Debug with S&yser";
	char Name6[]="prop:FileDescription;Company;FileVersion;Create;Size";
	DWORD Disposition,dwSize;
	int ModuleFileNameLen;
	HKEY hKey;
	LONG lOK;
	CommandLine[0]='"';
	GetModuleFileNameA(NULL,&CommandLine[1],sizeof(CommandLine));
	ModuleFileNameLen=TStrLen(CommandLine);
	ModuleFileNameLen++;
	TStrCat(CommandLine,"\" /Load \"%1\"");
	if((lOK = RegCreateKeyEx(HKEY_CLASSES_ROOT,".sds",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition))!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)Name,sizeof(Name)) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"SdsFile",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)Name2,sizeof(Name2)) != ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hKey,"InfoTip",0,REG_SZ,(BYTE*)Name6,sizeof(Name6)) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"SdsFile\\shell",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)Name3,sizeof(Name3)) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"SdsFile\\shell",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"SdsFile\\shell\\open",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"SdsFile\\shell\\open\\command",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	dwSize = (DWORD)TStrLen(CommandLine)+1;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)CommandLine,dwSize) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"SdsFile\\shell\\SyserLoad",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)Name4,sizeof(Name4)) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"SdsFile\\shell\\SyserLoad\\command",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	dwSize = (DWORD)TStrLen(CommandLine)+1;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)CommandLine,dwSize) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"exefile\\shell\\ SyserLoad",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)Name5,sizeof(Name5)) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"exefile\\shell\\ SyserLoad\\command",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	CommandLine[ModuleFileNameLen]=0;
	TStrCat(CommandLine," /debugapp \"%1\"");
	dwSize = (DWORD)TStrLen(CommandLine)+1;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)CommandLine,dwSize) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"sysfile\\shell",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"sysfile\\shell\\ SyserLoad",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)Name5,sizeof(Name5)) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	if(RegCreateKeyEx(HKEY_CLASSES_ROOT,"sysfile\\shell\\ SyserLoad\\command",0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	CommandLine[ModuleFileNameLen]=0;
	TStrCat(CommandLine," /debugdriver \"%1\"");
	dwSize = (DWORD)TStrLen(CommandLine)+1;
	if(RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)CommandLine,dwSize) != ERROR_SUCCESS)
		return false;
	RegCloseKey(hKey);
	return true;
}

bool CSyserInterface::InstallSyser()
{
	InstallServiceGroupOrderList();
	InstallServiceGroup(DERIVER_GROUP_NAME,"Primary Disk");
	InstallDependDriver("SyserBoot","SysBoot.sys",SERVICE_BOOT_START,DERIVER_GROUP_NAME,GROUP_SYSBOOT_ORDER);
	InstallDependDriver("SyserLanguage","SysLang.sys",SERVICE_BOOT_START,DERIVER_GROUP_NAME,GROUP_SYSLANG_ORDER);
	InstallDependDriver("SDbgMsg","SDbgMsg.sys",SERVICE_BOOT_START,DERIVER_GROUP_NAME,GROUP_SDBGMSG_ORDER);
	InstallDependDriver(DRIVER_NAME,"Syser.sys",SERVICE_DEMAND_START,DERIVER_GROUP_NAME,GROUP_SYSER_ORDER);
	InstallServiceEventLog("Syser","%SystemRoot%\\System32\\drivers\\Syser.sys",7,true);
	InstallDependData("Syser.dat;Wisp.dat;libfunc.fdc;APIDef.lib");
	RemoveDependData("Syser.cfg;SyserColor.cfg");
	char szWindows[MAX_FN_LEN];
	GetWindowsDirectory(szWindows,MAX_FN_LEN);
	SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\SystemRoot",szWindows,REG_SZ);
	SaveSyserOption(theApp.m_szSyserAppCfgFN,&OrgSyserAppOption,sizeof(OrgSyserAppOption));
	SaveSyserOption(theApp.m_szSyserCfgFN,&OrgSyserOption,sizeof(OrgSyserOption));
	SaveSyserOption(theApp.m_szSyserColorCfgFN,&OrgColorOption,sizeof(OrgColorOption));
	ULONGLONG InstTime;
	if(GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\InstTime",&InstTime,sizeof(InstTime))==false)
	{
		InstTime = GetCurrentInstallTime();
		if(InstTime)
			SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Syser\\InstTime",&InstTime,REG_QWORD);
	}
	if(IsDriverActive("sptd"))
	{
		MessageBox(	NULL,
					"Daemon Tools SPTD isn't compatible with kernel debuggers !\n"
					"Daemon Tools Uninstaller couldn't clean it !\n"
					"Syser will disable it while installation !",
					"Warning",MB_OK);
	}
	if(IsDriverActive("dump_wmimmc"))
	{
		MessageBox(	NULL,
			"nProtect dump_wmimmc.sys isn't compatible with kernel debuggers !\nMaybe cause BSOD !",
			"Warning",MB_OK);
	}
	DWORD Start = 3;
	DWORD OldStart=0;
	if(GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\Start",&OldStart,REG_DWORD))
	{
		if(OldStart<3)
		{
			SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\Start",&Start,REG_DWORD);		
			SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\OldStart",&OldStart,REG_DWORD);
		}
	}
	
	return true;
}

bool CSyserInterface::UninstallSyser()
{
	char szDir[MAX_FN_LEN],szFile[MAX_FN_LEN];
	GetSystemDirectory(szDir,MAX_FN_LEN);
	TStrCpy(szFile,szDir);
	TStrCat(szFile,"\\drivers\\Syser.cfg");
	DeleteFile(szFile);
	TStrCpy(szFile,szDir);
	TStrCat(szFile,"\\drivers\\SyserColor.cfg");
	DeleteFile(szFile);
	TStrCpy(szFile,szDir);
	TStrCat(szFile,"\\drivers\\ExpMod.lst");
	DeleteFile(szFile);
	TStrCpy(szFile,szDir);
	TStrCat(szFile,"\\drivers\\ModExSym.lst");
	DeleteFile(szFile);
	TStrCpy(szFile,szDir);
	TStrCat(szFile,"\\drivers\\Syser.cmt");
	DeleteFile(szFile);
	if(IsDriverActive(DRIVER_NAME))
		if(DisableDriver(DRIVER_NAME)==false)
			return false;
	UninstallDriver(DRIVER_NAME);
	UninstallDriver("SyserBoot");
	UninstallDriver("SyserLanguage");
	UninstallDriver("SDbgMsg");
	UninstallFileExtAssociate();
	UninstallServiceGroup(DERIVER_GROUP_NAME);
	UninstallServiceGroupOrderList();
	UninstallServiceEventLog("Syser");
	DWORD OldStart;
	if(GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\OldStart",&OldStart,REG_DWORD))
	{
		SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\Start",&OldStart,REG_DWORD);
	}
	else
	{
		if(GetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\Start",&OldStart,REG_DWORD))
		{
			if(OldStart==3)
			{
				OldStart=0;
				SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\Start",&OldStart,REG_DWORD);
			}
		}
	}
	DelRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\OldStart");
	return true;
}

bool CSyserInterface::StopSyser()
{
	HWND hWnd;
	HANDLE hMutex;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS,false,"Syser Interface");
	if(hMutex)
	{
		hWnd=::FindWindow("WispWindowClass",MAIN_WND_NAME);
		if(hWnd)
			::SendMessage(hWnd,WM_SYSER_UNINSTALL,0,0);
	}
	CloseHandle(hMutex);
	return true;
}

void CSyserInterface::SaveSyserHistroys(PCSTR Filename)
{
	DWORD cbReturn;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return;	
	DeviceIoControl(hSyser,IOCTL_SYSER_SAVE_HISTROYS,(void*)Filename,TStrLen(Filename)+1,NULL,0,&cbReturn,NULL);
	CloseHandle(hSyser);
}

void CSyserInterface::SaveSyserComments()
{
	DWORD cbReturn;
	HANDLE hSyser = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser==INVALID_HANDLE_VALUE)
		return;	
	DeviceIoControl(hSyser,IOCTL_SYSER_SAVE_COMMENTS,NULL,0,NULL,0,&cbReturn,NULL);
	CloseHandle(hSyser);
}


