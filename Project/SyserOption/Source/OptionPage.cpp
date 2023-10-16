#include "StdAfx.h"
#include "OptionPage.h"
#include "SyserOptionApp.h"

extern int	SyserAppOptionRef;
extern int	SyserOptionRef;
//Form Resource
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//Option List
WISP_PCSTR OnOffList[]=
{
	WISP_STR("Off"),
	WISP_STR("On"),
	NULL
};
WISP_PCSTR NoYesList[]=
{
	WISP_STR("No"),
	WISP_STR("Yes"),
	NULL
};

WISP_PCSTR DisableEnableList[]=
{
	WISP_STR("Disable"),
	WISP_STR("Enable"),
	NULL
};

WISP_PCSTR StartPageList[]=
{
	WISP_STR("Console"),
	WISP_STR("Process Moniter"),
	WISP_STR("Symbol Download"),
	WISP_STR("Option"),
	NULL
};

WISP_PCSTR SyserDebuggerFollowModeList[]=
{
	WISP_STR("Automatic (Relative to EIP)"),
	WISP_STR("System Explorer"),
	WISP_STR("Source Explorer"),
	NULL
};
WISP_PCSTR SyserI3hereStatus[]=
{
	WISP_STR("I3Here is off"),
	WISP_STR("I3Here is on"),
	WISP_STR("I3Here is on for device drivers (addr > 2G)"),
	NULL
};

WISP_PCSTR AutoActionList[]=
{
	WISP_STR("No"),
	WISP_STR("Yes"),
	WISP_STR("Query User"),
	NULL
};

WISP_PCSTR ConnectList[]=
{
	WISP_STR("Disable"),
	WISP_STR("Serial Port"),
	NULL
};

WISP_PCSTR DirSelectList[]=
{
	WISP_STR("Browse"),
	WISP_STR("Edit"),
	WISP_STR("Current Path & Edit"),
	NULL
};

WISP_PCSTR BootTypeList[]=
{
	WISP_STR("%dBoot"),
	WISP_STR("System"),
	WISP_STR("Automatic"),
	WISP_STR("Manual"),
	NULL
};

WISP_PCSTR SyserVideoAttachType[]=
{
	WISP_STR("Auto (If you don't care)"),
	WISP_STR("User Mode (High Compatibility)"),
	WISP_STR("Kernel Mode (Supports DirectX)"),
	NULL
};

WISP_PCSTR SyserKeyboardLayerType[]=
{
	WISP_STR("Normal"),
	WISP_STR("Azerty"),
	NULL
};


bool TValueTestWidth(void*pValue)
{
	int Value = *(int*)pValue;
	return Value >= 640 && Value <= SyserOption.iMaxWndWidth;
}

bool TValueTestHeight(void*pValue)
{
	int Value = *(int*)pValue;
	return Value >= 480 && Value <= SyserOption.iMaxWndHeight;
}

WISP_OPTION_ITEM SyserDebuggerOption[]=
{
	{WSTR("Start Syser Debugger when SyserApp launch"),		OPTION_SELECT_INT,	&SyserAppOption.iAutoStart,		sizeof(int),AutoActionList,NULL,&SyserAppOptionRef},
	{WSTR("Stop Syser Debugger when SyserApp exit"),		OPTION_SELECT_INT,	&SyserAppOption.iAutoStop ,		sizeof(int),AutoActionList,NULL,&SyserAppOptionRef},
	{WSTR("Video Detect Mode (Restart Syser to apply)"),	OPTION_SELECT_INT,	&SyserOption.iVideoDetectMode,	sizeof(int),SyserVideoAttachType,NULL,&SyserOptionRef},
	{WSTR("Big Font (Restart Syser to apply)"),				OPTION_SELECT_INT,	&SyserOption.iBigFont,			sizeof(int),NoYesList,NULL,&SyserOptionRef},
	{WSTR("EIP Follow Mode"),								OPTION_SELECT_INT,	&SyserOption.iFollowMode,		sizeof(int),SyserDebuggerFollowModeList,NULL,&SyserOptionRef},
	{WSTR("Show Full Symbol (Include Module Name)"),		OPTION_SELECT_INT,	&SyserOption.iShowFullSym,		sizeof(int),NoYesList,NULL,&SyserOptionRef},
	{WSTR("Mouse Sensitivity (1 - 30)"),					OPTION_INT,			&SyserOption.iMouseSensitivity,	sizeof(int),NULL,TValueTest<int,1,30>,&SyserOptionRef},
	{WSTR("Command Histroy lines [100 - 10000]"),			OPTION_INT,			&SyserOption.iHistroyLines,		sizeof(int),NULL,TValueTest<int,100,10000>,&SyserOptionRef},
	{WSTR("Start window width  [640 - Max window width ]"),	OPTION_INT,			&SyserOption.iStartWndWidth,	sizeof(int),NULL,TValueTestWidth,&SyserOptionRef},
	{WSTR("Start window height [480 - Max window height]"),	OPTION_INT,			&SyserOption.iStartWndHeight,	sizeof(int),NULL,TValueTestHeight,&SyserOptionRef},
	{WSTR("Keyboard layer"),								OPTION_SELECT_INT,	&SyserOption.iKeyboardLayer,	sizeof(int),SyserKeyboardLayerType,NULL,&SyserOptionRef},
	{WSTR("i3here command default status"),					OPTION_SELECT_INT,	&SyserOption.i3here,			sizeof(int),SyserI3hereStatus,NULL,&SyserOptionRef},
	{WSTR("i1here command default status"),					OPTION_SELECT_INT,	&SyserOption.i1here,			sizeof(int),OnOffList,NULL,&SyserOptionRef},
	{WSTR("faults command default status"),					OPTION_SELECT_INT,	&SyserOption.ifaults,			sizeof(int),OnOffList,NULL,&SyserOptionRef},

	{NULL}
};

WISP_OPTION_ITEM SyserLoaderOption[]=
{
	{WSTR("Stays in system tray"),							OPTION_SELECT_INT,	&SyserAppOption.iSystemTray,	sizeof(int),NoYesList,NULL,&SyserAppOptionRef},
	{WSTR("Top Most"),										OPTION_SELECT_INT,	&SyserAppOption.iTopMost,		sizeof(int),NoYesList,NULL,&SyserAppOptionRef},
	{WSTR("Show Syser start splash"),						OPTION_SELECT_INT,	&SyserOption.iShowStartSplash,	sizeof(int),NoYesList,NULL,&SyserOptionRef},
	{WSTR("Histroy lines [100 - 1000]"),					OPTION_INT,			&SyserAppOption.iHistroyLines,	sizeof(int),NULL,TValueTest<int,100,1000>,&SyserAppOptionRef},
	{NULL}
};

WISP_OPTION_ITEM SourceDebuggerOption[]=
{
	{WSTR("Syntax Color"),OPTION_SELECT_INT,&SyserOption.iSourceCodeSyntaxColors,sizeof(int),NoYesList,NULL,&SyserOptionRef},
	{WSTR("Show Tips"),OPTION_SELECT_INT,&SyserOption.iSourceCodeShowTips ,sizeof(int),NoYesList,NULL,&SyserOptionRef},
	{WSTR("Show Line Numbers"),OPTION_SELECT_INT,&SyserOption.iSourceCodeShowLineNumbers ,sizeof(int),NoYesList,NULL,&SyserOptionRef},
	{NULL}
};

WISP_OPTION_ITEM SerialPortOption[]=
{
	{WSTR("COM Port"),OPTION_INT,&SyserOption.iComPort,sizeof(int),NULL,TValueTest<int,1,255>,&SyserOptionRef},
	{NULL}
};

WISP_OPTION_ITEM RemoteDebuggerOption[]=
{
	{WSTR("Connect Type"),OPTION_SELECT_INT,&SyserOption.iConnectType,sizeof(int),ConnectList,NULL,&SyserOptionRef},
	{WSTR("Serial Port Configure"),OPTION_TITLE,SerialPortOption},
	{NULL}
};

WISP_OPTION_ITEM SyserAdvanceOption[]=
{
	{WSTR("Geneal heap size [15 - 40]M"),OPTION_INT,&SyserOption.iHeapSizeM,sizeof(int),NULL,TValueTest<int,MIN_MAIN_HEAP,MAX_MAIN_HEAP>,&SyserOptionRef},
	{WSTR("Source Code heap size [6 - 40]M"),OPTION_INT,&SyserOption.iSourceCodeHeapSizeM,sizeof(int),NULL,TValueTest<int,MIN_SOURCE_CODE_HEAP,MAX_SOURCE_CODE_HEAP>,&SyserOptionRef},
	{WSTR("Stack size [512 - 4096]K"),OPTION_INT,&SyserOption.iStackSizeK,sizeof(int),NULL,TValueTest<int,512,4096>,&SyserOptionRef},
	{WSTR("Enable Hardware Timer"),OPTION_SELECT_INT,&SyserOption.iHardTimerEnable,sizeof(int),DisableEnableList,NULL,&SyserOptionRef},
	{WSTR("Max window width  [640 - 2048]"),OPTION_INT,&SyserOption.iMaxWndWidth ,sizeof(int),NULL,TValueTest<int,640,2048>,&SyserOptionRef},
	{WSTR("Max window height [480 - 2048]"),OPTION_INT,&SyserOption.iMaxWndHeight ,sizeof(int),NULL,TValueTest<int,480,2048>,&SyserOptionRef},
	{NULL}
};

WISP_OPTION_ITEM SyserOptionTitle[]=
{
	{WSTR("Syser Debugger"),OPTION_TITLE,SyserDebuggerOption},
	{WSTR("Syser Loader"),OPTION_TITLE,SyserLoaderOption},
	{WSTR("Source Code Debugger"),OPTION_TITLE,SourceDebuggerOption},
	{WSTR("Developer Advance Option (Restart Syser to apply)"),OPTION_TITLE,SyserAdvanceOption},
	//{WSTR("Remote Debugger"),OPTION_TITLE,RemoteDebuggerOption},
	{NULL}
};


WISP_MSG_MAP_BEGIN(COptionPage)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispOptionForm)

COptionPage::COptionPage()
{
	m_pOptionItem = SyserOptionTitle;
}

bool COptionPage::OnFormCreate(IN WISP_MSG*pMsg)
{
	if(CWispOptionForm::OnFormCreate(pMsg)==false)
		return false;
	m_OptionList.ExpandItem(m_OptionList.GetItem(0));
	m_OptionList.ExpandItem(m_OptionList.GetItem(1));
	m_OptionList.ExpandItem(m_OptionList.GetItem(2));
	m_OptionList.ExpandItem(m_OptionList.GetItem(3));
	m_OptionList.ExpandItem(m_OptionList.GetItem(4));
	m_OptionList.ExpandItem(m_OptionList.GetItem(5));
	if(SyserOption.CRCCode == OrgSyserOption.CRCCode && SyserAppOption.CRCCode == OrgSyserAppOption.CRCCode)
		m_pDefaultBT->EnableWindow(false);
	m_OptionList.SetColumnWidth(m_OptionList.GetColumn(0),300);
	return false;
}

bool GetPrivilege(PCSTR privName)
{
	bool rc;
	HANDLE hToken;
	LUID privValue;
	TOKEN_PRIVILEGES tkp;
	if(!OpenProcessToken( GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
		return false;
	if(!LookupPrivilegeValue( NULL, privName, &privValue ) )
	{
		CloseHandle(hToken);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = privValue;
	rc = AdjustTokenPrivileges( hToken, FALSE, &tkp,sizeof tkp,NULL,NULL)!=FALSE;
	CloseHandle( hToken );
	return rc;
}

void COptionPage::OptionApplyNotify()
{
	if(SyserOptionRef)//Syser.cfg被修改
	{
		SyserOptionRef = 0;
		SaveSyserOption(theApp.m_szSyserCfgFN,&SyserOption,sizeof(SyserOption));
	}
	if(SyserAppOptionRef)//SyserApp.cfg被修改
	{
		SyserAppOptionRef = 0;
		SaveSyserOption(theApp.m_szSyserAppCfgFN,&SyserAppOption,sizeof(SyserAppOption));
	}
	//比较配置文件是否和默认的一样,不一样则把Default按钮激活
	if(	SyserOption.CRCCode == OrgSyserOption.CRCCode && SyserAppOption.CRCCode == OrgSyserAppOption.CRCCode)
		m_pDefaultBT->EnableWindow(false);
	theApp.SendSyserMsg(IOCTL_SYSER_RELOAD_CONFIG);
	theApp.SendSyserAppMsg(WM_SYSER_APP_RELOAD_CFG);
}

void COptionPage::OptionDefaultNotify()
{
	SaveSyserOption(theApp.m_szSyserCfgFN,&SyserOption,sizeof(SyserOption));
	SaveSyserOption(theApp.m_szSyserAppCfgFN,&SyserAppOption,sizeof(SyserAppOption));
	theApp.SendSyserMsg(IOCTL_SYSER_RELOAD_CONFIG);
	theApp.SendSyserAppMsg(WM_SYSER_APP_RELOAD_CFG);
}

bool COptionPage::OptionBeforeDefaultNotify()
{
	SyserOption = OrgSyserOption;
	SyserAppOption = OrgSyserAppOption;
	SyserOptionRef = 0;
	SyserAppOptionRef = 0;
	return true;
}

