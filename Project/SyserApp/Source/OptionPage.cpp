#include "StdAfx.h"
#include "OptionPage.h"

extern int	SyserAppOptionRef;
extern int	SyserOptionRef;
//Form Resource
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//Option List
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

WISP_PCSTR SyserDebuggerStartPageList[]=
{
	WISP_STR("System Explorer"),
	WISP_STR("Console"),
	WISP_STR("Source Explorer"),
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



WISP_OPTION_ITEM WindowOption[]=
{
	{WSTR("Start Page"),OPTION_SELECT_INT,&SyserAppOption.iStartPage,sizeof(int),StartPageList,NULL,&SyserAppOptionRef},
	{WSTR("Syser Debugger Start Page"),OPTION_SELECT_INT,&SyserOption.iStartPage,sizeof(int),SyserDebuggerStartPageList,NULL,&SyserOptionRef},
	{WSTR("Stays in system tray"),OPTION_SELECT_INT,&SyserAppOption.iSystemTray,sizeof(int),NoYesList,NULL,&SyserAppOptionRef},
	{WSTR("Top Most"),OPTION_SELECT_INT,&SyserAppOption.iTopMost,sizeof(int),NoYesList,NULL,&SyserAppOptionRef},
	{WSTR("Show Syser start splash"),OPTION_SELECT_INT,&SyserAppOption.iShowStartSplash,sizeof(int),NoYesList,NULL,&SyserAppOptionRef},
	{NULL}
};

WISP_OPTION_ITEM DebuggerOption[]=
{
	{WSTR("Start Syser Debugger when SyserApp launch"),OPTION_SELECT_INT,&SyserAppOption.iAutoStart,sizeof(int),AutoActionList,NULL,&SyserAppOptionRef},
	{WSTR("Stop Syser Debugger when SyserApp exit"),OPTION_SELECT_INT,&SyserAppOption.iAutoStop ,sizeof(int),AutoActionList,NULL,&SyserAppOptionRef},
	{WSTR("Show Full Symbol (Include Module Name)"),OPTION_SELECT_INT,&SyserOption.iShowFullSym,sizeof(int),NoYesList,NULL,&SyserOptionRef},
	{WSTR("Show DbgMsg Source Process Name"),OPTION_SELECT_INT,&SyserOption.iShowDbgMsgProcName,sizeof(int),NoYesList,NULL,&SyserOptionRef},	
	{WSTR("Mouse Sensitivity (1 - 30)"),OPTION_INT,&SyserOption.iMouseSensitivity,sizeof(int),NULL,TValueTest<int,1,30>,&SyserOptionRef},
	{NULL}
};

WISP_OPTION_ITEM SymbolDownloadOption[]=
{
	{WSTR("Symbol Server Site"),OPTION_STRING,&SyserAppOption.szSymbolSite,128,NULL,NULL,&SyserAppOptionRef},
	{WSTR("Local Symbol Path"),OPTION_DIR_NAME,&SyserAppOption.szDownloadSymbolPath,MAX_FN_LEN,DirSelectList,NULL,&SyserAppOptionRef},
	{WSTR("Converted SDS Path"),OPTION_DIR_NAME,&SyserAppOption.szConvertedSDSPath,MAX_FN_LEN,DirSelectList,NULL,&SyserAppOptionRef},
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
	{WSTR("Heap Size [10240 - 40960 (KB) ]"),OPTION_INT,&SyserOption.iHeapSize,sizeof(int),NULL,TValueTest<int,10240,40960>,&SyserOptionRef},
	{WSTR("Addition Heap Size [1024 - 40960 (KB)]"),OPTION_INT,&SyserOption.iAddiHeapSize,sizeof(int),NULL,TValueTest<int,1024,40960>,&SyserOptionRef},
	{WSTR("Enable Hardware Timer"),OPTION_SELECT_INT,&SyserOption.iHardTimerEnable,sizeof(int),DisableEnableList,NULL,&SyserOptionRef},
	{NULL}
};

WISP_OPTION_ITEM MainOption[]=
{
	{WSTR("Window"),OPTION_TITLE,WindowOption},
	{WSTR("Debugger"),OPTION_TITLE,DebuggerOption},
	{WSTR("Symbol Download"),OPTION_TITLE,SymbolDownloadOption},
	{WSTR("Source Code Debugger"),OPTION_TITLE,SourceDebuggerOption},
	{WSTR("Developer Advance Option"),OPTION_TITLE,SyserAdvanceOption},
	//{WSTR("Remote Debugger"),OPTION_TITLE,RemoteDebuggerOption},
	{NULL}
};

COptionPage::COptionPage()
{
	m_pOptionItem = MainOption;
}


void COptionPage::OptionApplyNotify()
{
	if(SyserAppOptionRef)
	{
		SyserAppOptionRef = 0;
		SaveSyserOption("SyserApp.cfg",&SyserAppOption,sizeof(SyserAppOption));
	}
	if(SyserOptionRef)
	{
		SyserOptionRef = 0;
		SaveSyserOption("Syser.cfg",&SyserOption,sizeof(SyserOption));
	}
}
