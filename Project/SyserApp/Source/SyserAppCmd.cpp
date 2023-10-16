#include "StdAfx.h"
#include "SyserApp.h"
#include "SyserAppCmd.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SyserAppCmd

void OutputLastErrorMsg()
{
	WCHAR szBuffer[256];
	*szBuffer=0;
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),szBuffer,256,NULL);
	OUTPUT(WSTR("Error : %s\n"),szBuffer);
}

SYSER_APP_CMD_ENTRY	SyserAppCmdTable[]=
{
	{WSTR("cmd"),			WSTR("run windows command !"),				run_command},
	{WSTR("start"),			WSTR("start driver!"),						start_command},
	{WSTR("stop"),			WSTR("stop driver!"),						stop_command},
	{WSTR("rldcfg"),		WSTR("reload registry config"),				reloadconfig_command},
	{WSTR("loadsds"),		WSTR("load SDS symbols file"),				loadsds_command},
	{WSTR("unloadsds"),		WSTR("unload SDS symbols file"),			unloadsds_command},
	{WSTR("tsf"),			WSTR("Translate Symbol File"),				tsf_command},
	{WSTR("load"),			WSTR("Load module to debug"),				load_command},
	{WSTR("scrshot"),		WSTR("Save Syser Debugger ScreenShot"),		scrshot_command},
	{WSTR("rmsptd"),		WSTR("Disabled Daemon Tools SPTD"),			rmsptd_command},
	{WSTR("install"),		NULL,										install_command},
	{WSTR("uninstall"),		NULL,										uninstall_command},
	{NULL,NULL,NULL}
};

int rmsptd_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	DWORD Start = 3;
	if(SetRegValueEx("HKLM\\SYSTEM\\CurrentControlSet\\Services\\sptd\\Start",&Start,REG_DWORD))
	{
		if(MessageBox(theApp.m_hLocalWnd,"Do you want to reboot ?","SPTD Disabled !!!",MB_YESNO)==IDYES)
		{
			CProcess::GetPrivilege(SE_SHUTDOWN_NAME);
			ExitWindowsEx(EWX_REBOOT,0);
		}
	}
	return 0;
}

int scrshot_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	int Length;
	char szBuffer[MAX_FN_LEN];
	Length = TStrCpy(szBuffer,"\\??\\");

	if(argc<2)
	{
		Length+= GetModulePath(&szBuffer[Length]);
		Length+= TStrCpy(&szBuffer[Length],"Syser.bmp");
	}
	else
	{
		Length+=UnicodeToAnsi(argv[1],&szBuffer[Length],MAX_FN_LEN-Length);
	}
	HANDLE hDevice = CreateFile(DRIVER_RING3_NAME,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(hDevice == INVALID_HANDLE_VALUE)
		return 0;
	DWORD dummy;
	DeviceIoControl(hDevice,IOCTL_SYSER_SCREEN_SHOT,szBuffer,Length+1,NULL,NULL,&dummy,NULL);
	CloseHandle(hDevice);
	return 0;
}

int install_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	pSyser->m_SyserInterface.InstallSyser();
	return 0;
}

int uninstall_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	pSyser->m_SyserInterface.UninstallSyser();
	return 0;
}


int tsf_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	char FileName[MAX_FN_LEN];
	char SymbolFileName[MAX_FN_LEN];
	int i;
	if(argc==1)
	{
		OUTPUT(WSTR("Usage: tsf PE filename\n"));
		return 1;
	}
	if(theApp.m_SyserInterface.IsSyserRuning()==false)
	{
		theApp.m_MainFrame.OnMenuEventStartSyser(NULL);
	}
	for(i = 1; i < argc;i++)
	{
		TStrCpy(FileName,argv[i]);
		if(theApp.m_SyserInterface.TranslateSymbolFile(FileName,SymbolFileName,true)==false)
		{
			OUTPUT(WSTR("Translate '%s' error!\n"),argv[i]);
		}
	}
	
	return 0;
}

int load_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	char szFileName[MAX_FN_LEN],CmdLine[256];
	if(argc==1)
	{
		OUTPUT(WSTR("Usage: %s FileFullPathName\n"),argv[0]);
		return 1;
	}
	if(theApp.m_SyserInterface.IsSyserRuning()==false)
	{
		theApp.m_SyserInterface.StartSyserDriver();
	}
	TStrCpy(szFileName,argv[1]);
	if(argc>2)
	{
		UnicodeToAnsi(&szCommandLine[argv[2]-argv[0]],CmdLine,sizeof(CmdLine));
	}
	else
	{
		*CmdLine=0;
	}
	if(theApp.m_SyserInterface.LoadModule(szFileName,CmdLine,SDP_LOAD_SDS|SDP_AUTO_UNLOAD_SDS)==false)
	{
		OUTPUT(WSTR("Fail to launch %s!"),szFileName);
		return 1;
	}
	return 0;
}

int loadsds_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	char FileName[MAX_FN_LEN];
	if(argc==1)
	{
		OUTPUT(WSTR("Usage: loadsds sds_filename\n"));
		return 1;
	}
	if(theApp.m_SyserInterface.IsSyserRuning()==false)
	{
		theApp.m_SyserInterface.StartSyserDriver();
	}
	UnicodeToAnsi(&szCommandLine[argv[1]-argv[0]],FileName,MAX_FN_LEN);
	theApp.m_SyserInterface.LoadSDS(FileName);
	return 0;
}

int unloadsds_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	char FileName[MAX_FN_LEN];
	if(argc==1)
	{
		OUTPUT(WSTR("Usage: unloadsds sds_filename\n"));
		return 1;
	}
	if(theApp.m_SyserInterface.IsSyserRuning()==false)
	{
		theApp.m_SyserInterface.StartSyserDriver();
	}
	UnicodeToAnsi(&szCommandLine[argv[1]-argv[0]],FileName,MAX_FN_LEN);
	theApp.m_SyserInterface.UnloadSDS(FileName);
	return 0;
}

int reloadconfig_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	if(argc==2&&TStrCmp(argv[1],"-h")==0)
	{
		OUTPUT(WSTR("SofticeExistCheck\n"));
		OUTPUT(WSTR("TimerInterrupt\n"));
		OUTPUT(WSTR("UsbMouse\n"));
		OUTPUT(WSTR("DebugRegisterMontior\n"));
		OUTPUT(WSTR("KeyboardLedProgram\n"));
		OUTPUT(WSTR("DisableDisplay\n"));
		OUTPUT(WSTR("DisableDDrawHook\n"));
		OUTPUT(WSTR("DisableDbgMsg\n"));
		OUTPUT(WSTR("DebugKeyboardInterrupt\n"));
		OUTPUT(WSTR("PatchKeBugCheck\n"));
		OUTPUT(WSTR("m_ExceptionDebugInfo\n"));
		return true;
	}
	theApp.m_SyserInterface.ReloadConfig();
	return 0;
}
int run_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	int Length;
	char szBuffer[MAX_FN_LEN];
	Length=TStrCpy(szBuffer,"cmd /c ");
	UnicodeToAnsi(&szCommandLine[TStrLen(*argv)+1],&szBuffer[Length],MAX_FN_LEN-Length);
	WinExec(szBuffer,SW_HIDE);
	return 0;
}

int start_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	char szBuffer[MAX_FN_LEN];
	if(argc!=2)
	{
		OUTPUT(WSTR("Usage : %s Name\n"),argv[0]);
		return -1;
	}
	UnicodeToAnsi(argv[1],szBuffer,sizeof(szBuffer));
	if(IsDriverActive(szBuffer))
	{
		OUTPUT(WSTR("Driver has already started!\n"));
		return 0;
	}
	if(StartDriver(szBuffer))
		OUTPUT(WSTR("Driver started!\n"));
	else
	{
		OutputLastErrorMsg();
	}
	if(TStrICmp(szBuffer,"syser")==0)
		theApp.m_SyserInterface.UpdateDriverStatus();
	return 0;
}

int stop_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	char szBuffer[MAX_FN_LEN];
	if(argc!=2)
	{
		OUTPUT(WSTR("Usage : %s Name\n"),argv[0]);
		return -1;
	}
	UnicodeToAnsi(argv[1],szBuffer,sizeof(szBuffer));
	if(IsDriverActive(szBuffer)==false)
	{
		OUTPUT(WSTR("Driver isn't actived!\n"));
		return 0;
	}
	if(StopDriver(szBuffer))
		OUTPUT(WSTR("Driver Stopped!\n"));
	else
		OUTPUT(WSTR("Fail to Stop %s Driver!\n"),argv[1]);
	if(TStrICmp(szBuffer,"syser")==0)
		theApp.m_SyserInterface.UpdateDriverStatus();
	return 0;
}

int fio_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyserApp*pSyser)
{
	DWORD cbSize;
	WCHAR szBuffer[256],CmdChar;
	HANDLE hFile;
	if(argc<3)
		goto ShowUsage;
	CmdChar = *argv[2];
	MAKE_CHAR_LOWER(CmdChar);
	ZeroMemory(szBuffer,sizeof(szBuffer));
	if(CmdChar=='r')
	{
		if(argc!=3)
			goto ShowUsage;
		hFile = CreateFileW(argv[1],GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			goto ErrorExit;
		ReadFile(hFile,szBuffer,sizeof(szBuffer)-2,&cbSize,NULL);
		OUTPUT(WSTR("%s\n"),szBuffer);
		CloseHandle(hFile);
	}
	else if(CmdChar=='w')
	{
		hFile = CreateFileW(argv[1],GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			goto ErrorExit;
		WriteFile(hFile,argv[3],TStrLen(argv[3])*sizeof(WCHAR),&cbSize,NULL);
		CloseHandle(hFile);
	}
	else
		goto ShowUsage;
	return 0;
ShowUsage:
	OUTPUT(WSTR("Usage : fio name [r|w] \"string\"\n"));
	return 0;
ErrorExit:
	OutputLastErrorMsg();
	return -1;
}


//SyserAppCmd
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CConsoleWnd
WISP_MSG_MAP_BEGIN (CConsoleWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispConsoleWnd)


bool CConsoleWnd::OnCreate(IN WISP_MSG*pMsg)
{
	for(int n=0;SyserAppCmdTable[n].CmdStr;n++)
	{
		InsertCmd(SyserAppCmdTable[n].CmdStr,(CMDPROC)SyserAppCmdTable[n].CmdProc,&theApp,SyserAppCmdTable[n].CmdCmt,NULL);
	}
	SetHistoryLines(SyserAppOption.iHistroyLines);
	m_Option.RegisterValueAry(SyserAppOptVal);
	return TRUE;
}

//CConsoleWnd
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
