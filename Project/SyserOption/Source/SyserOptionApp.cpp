#include "StdAfx.h"
#include "SyserOptionApp.h"

CSyserOptionApp	theApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return theApp.WinMainStart(hInstance,lpCmdLine,nCmdShow);
}

CSyserOptionApp::CSyserOptionApp(void)
{
	STZeroMemory(m_VersionInfo);
	m_VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&m_VersionInfo);

	GetModulePath(m_szSyserAppCfgFN);
	TStrCat(m_szSyserAppCfgFN,"SyserApp.cfg");

	GetSystemDirectoryA(m_szSyserCfgFN,MAX_FN_LEN);
	TStrCat(m_szSyserCfgFN,"\\drivers\\Syser.cfg");

	GetSystemDirectoryA(m_szColorCfgFN,MAX_FN_LEN);
	TStrCat(m_szColorCfgFN,"\\drivers\\SyserColor.cfg");

	OrgSyserOption.CRCCode = GetCRCCode(RT_PBYTE(&OrgSyserOption,sizeof(DWORD)),sizeof(OrgSyserOption)-sizeof(DWORD));
	OrgSyserAppOption.CRCCode = GetCRCCode(RT_PBYTE(&OrgSyserAppOption,sizeof(DWORD)),sizeof(OrgSyserAppOption)-sizeof(DWORD));
	OrgColorOption.CRCCode = GetCRCCode(RT_PBYTE(&OrgColorOption,sizeof(DWORD)),sizeof(OrgColorOption)-sizeof(DWORD));
}

CSyserOptionApp::~CSyserOptionApp(void)
{
}


void CSyserOptionApp::InitEnv()
{
	__try
	{
		m_MainFrame.m_OptionPage.FillOptionTreeValue(NULL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{//值非法重置
		SaveSyserOption(m_szSyserAppCfgFN,&OrgSyserAppOption,sizeof(OrgSyserAppOption));
		SyserAppOption = OrgSyserAppOption;
		SaveSyserOption(m_szSyserCfgFN,&OrgSyserOption,sizeof(OrgSyserOption));
		SyserOption = OrgSyserOption;		
		SaveSyserOption(m_szColorCfgFN,&OrgColorOption,sizeof(OrgColorOption));
		ColorOption = OrgColorOption;
		m_MainFrame.m_OptionPage.FillOptionTreeValue(NULL);
	}
}

void CSyserOptionApp::LoadCFG()
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
	if(LoadSyserOption(m_szColorCfgFN,&ColorOption,sizeof(ColorOption))==false)
	{
		SaveSyserOption(m_szColorCfgFN,&OrgColorOption,sizeof(OrgColorOption));
		ColorOption = OrgColorOption;
	}
}

void CSyserOptionApp::SendSyserMsg(DWORD Msg)
{
	HANDLE hSyser = CreateFile("\\\\.\\Syser",GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hSyser!=INVALID_HANDLE_VALUE)
	{
		DWORD cbReturn;
		DeviceIoControl(hSyser,Msg,NULL,0,NULL,0,&cbReturn,NULL);
		CloseHandle(hSyser);
	}
}

void CSyserOptionApp::SendSyserAppMsg(DWORD Msg)
{
	HWND hWnd = FindWindow(NULL,MAIN_WND_NAME);
	if(hWnd)
	{
		::SendMessage(hWnd,WM_SYSER_APP_RELOAD_CFG,0,0);
	}
}

bool CSyserOptionApp::InitInstance()
{
	//////////////////////////////////////////////////////////////////////////////
	//设置数据文件目录
	GetSystemDirectory(m_CurDir,MAX_FN_LEN);
	TStrCat(m_CurDir,"\\drivers\\");
	//
	//////////////////////////////////////////////////////////////////////////////
	m_pszDiskList = "Wisp.dat;Syser.dat";
	if(CLocalWispApp::InitInstance()==false)
		return false;
	LoadCFG();
	m_bHideMouse = true;
	m_hIcon = LoadIcon(m_hLocalInst,MAKEINTRESOURCE(IDI_ICON_SYSER_OPTION));
	m_FrameStyle&=~WS_VISIBLE;
	m_FrameStyleEx|=WS_EX_TOPMOST;

	if(TStrIStr(m_pCmdLine,"/boot"))
	{
		m_FrameStyle&=~(WS_MAXIMIZEBOX|WS_THICKFRAME);
		CreateFrame(WSTR("Boot Mode"),200,300,0);
		m_BootOptionForm.CreateForm();
		m_BootOptionForm.Resize(m_FrameBuffer.Width,m_FrameBuffer.Height);
		ShowWindow(m_hLocalWnd,SW_NORMAL);
		return true;
	}
	else if(TStrIStr(m_pCmdLine,"/video"))
	{
		m_FrameStyle&=~(WS_MAXIMIZEBOX|WS_THICKFRAME);
		CreateFrame(WSTR("Syser Video Detect Mode"),300,300,0);
		m_VideoModeForm.CreateForm();
		m_VideoModeForm.Resize(m_FrameBuffer.Width,m_FrameBuffer.Height);
		ShowWindow(m_hLocalWnd,SW_NORMAL);
	}
	else
	{
		CreateFrame(WSTR("Syser Option"),560,400,0);
		m_MainFrame.Create(NULL,0,0,0,0,NULL,WISP_ID_MAIN_FRAME,WISP_WS_NULL);
		m_MainFrame.Resize(m_FrameBuffer.Width,m_FrameBuffer.Height);
		ShowWindow(m_hLocalWnd,SW_NORMAL);
		InitEnv();
	}
	return true;
}

int	CSyserOptionApp::ExitInstance()
{
	m_MainFrame.Destroy();
	DestroyFrame();
	return CLocalWispApp::ExitInstance();
}

