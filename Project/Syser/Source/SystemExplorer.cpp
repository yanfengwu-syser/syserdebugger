#include "StdAfx.h"
#include "Syser.h"
#include "SystemExplorer.h"

#define  DEFAULT_MONITOR_VIEW_SIZE			250

//#define	 SYSER_SCREEN_SHOT

WISP_MENU_RES_ITEM CharacterSetTableMenu[]=
{
	{WSTR("IBM ASCII"),EVENT_ID_IBM_ASCII,16*6+7},	
	{WSTR("ANSI ASCII"),EVENT_ID_ANSI_ASCII,16*6+7},
	{WSTR("EBCDIC"),EVENT_ID_EBCDIC,16*6+7},
	WISP_MENU_RES_END
};
WISP_MENU_RES_ITEM RecentFileMenu[]=
{
	{WSTR("Empty"),EVENT_ID_RECENT_FILE,132},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM FileMenu[]=
{
	{WSTR("Open"),EVENT_ID_OPEN,8,WISP_MIS_DISABLED},
	{WSTR("Close"),EVENT_ID_CLOSE,9,WISP_MIS_DISABLED},
	{WSTR("Load Symbol Files"),EVENT_ID_LOAD_SYMBOL,10},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Recent Files"),0,36,WISP_MIS_POPUP,RecentFileMenu},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Save Comments"),EVENT_ID_SAVE_COMMENT,9*16+3,WISP_MIS_DISABLED},
	{WSTR("Load Comments"),EVENT_ID_LOAD_COMMENT,9*16+3,WISP_MIS_DISABLED},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM DebugMenu[]=
{
#ifdef CODE_OS_WIN
	{WSTR("Reset"),EVENT_ID_RESET,16},
#endif
	{WSTR("Continue      F5"),EVENT_ID_CONTINUE,3},
	{WSTR("Return        F6"),EVENT_ID_RETURN,2},
	{WSTR("Step          F8"),EVENT_ID_STEP,0},
	{WSTR("Proceed       F10"),EVENT_ID_PROCEED,1},
	{WSTR("Step Branch   F11"),EVENT_ID_STEP_BRANCH,0},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Break Point   Ctrl+F9"),EVENT_ID_BREAK_POINT,4},
	{WSTR("Eanble All Breakpoints"),EVENT_ID_ENABLE_BP_ALL,15*16+3},
	{WSTR("Disable All Breakpoints"),EVENT_ID_DISABLE_BP_ALL,15*16+4},
	{WSTR("Remove All Breakpoints"),EVENT_ID_REMOVE_BP_ALL,15*16+2},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM MonitorMenu[]=
{
	{WSTR("Register View                 Alt+G"),		EVENT_ID_REG_VIEW,		52},
	{WSTR("Data View                     Alt+D"),		EVENT_ID_DATA_VIEW_FORM,89},
	{WSTR("Call Stack                    Alt+C"),		EVENT_ID_CALL_STACK,	18},
	{WSTR("Run Trace List"),							EVENT_ID_RUN_TRACE_WND,	181},
	{WSTR("Comment List"),								EVENT_ID_COMMENT_LIST,	9*16+3},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM ViewMenu[]=
{
	{WSTR("Save Position                 Shift+Enter"),	EVENT_ID_SAVE_POS,16*1+8},
	{WSTR("Jump To Previous Position     Backspace"),	EVENT_ID_PREV_POS,16*1+5},
	{WSTR("Jump To Next Position         Ctrl+Enter"),	EVENT_ID_NEXT_POS,16*1+4},
	{WSTR("Empty Position List"),						EVENT_ID_EMPTY_POS_LIST,38},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Toggle   BookMark             Ctrl+K"),EVENT_ID_BOOKMARK_TOGGLE,13*16},
	{WSTR("Previous BookMark             Ctrl+P"),EVENT_ID_BOOKMARK_PREV,13*16+2},
	{WSTR("Next     BookMark             Ctrl+N"),EVENT_ID_BOOKMARK_NEXT,13*16+1},
	{WSTR("Clear    BookMark             Ctrl+L"),EVENT_ID_BOOKMARK_CLEAR,13*16+3},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM OptionMenu[]=
{
	{WSTR("Option"),			EVENT_ID_DEBUGGER_OPTION,51},
	{WSTR("Debugger Select"),	EVENT_ID_DEBUGGER_SELECT,53},
	{WSTR("Plugin List"),		EVENT_ID_PLUGIN_LIST,29},

	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM ToolsMenu[]=
{
	{WSTR("Memory Search"),		EVENT_ID_MEMORY_SEARCH,	13*16+15},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Calculator"),EVENT_ID_CALC,6},
	{WSTR("Soft Keyboard"),EVENT_ID_SOFT_KB,7},

	{WSTR("Set HotKey"),EVENT_ID_HOTKEY_CONFIGURE,7},

	WISP_MENU_RES_SEPARATOR,
	{WSTR("PE Explorer"),EVENT_ID_PE_EXPLORER,14},	
	{WSTR("Character Set Tables"),0,36,WISP_MIS_POPUP,CharacterSetTableMenu},	
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM HelpMenu[]=
{
	{WSTR("Register Help"),EVENT_ID_REG_HELP,52},
#ifdef CODE_OS_WIN
	{WSTR("Check New Version"),	EVENT_ID_CHECK_NEW_VERSION,104},
#endif
	{WSTR("About Syser"),EVENT_ID_ABOUT,				62},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM InfoMenu[]=
{
#ifndef CODE_OS_WIN
	{WSTR("IDT"),EVENT_ID_IDT,26},
	{WSTR("GDT"),EVENT_ID_GDT,26},
	{WSTR("LDT"),EVENT_ID_LDT,26},
	{WSTR("Page Map"),EVENT_ID_PAGE_MAP,51},
	WISP_MENU_RES_SEPARATOR,
#endif
	{WSTR("String References"),EVENT_ID_STRING_REFERENCE,15},
	{WSTR("Processes"),EVENT_ID_PROCESS,15},
	{WSTR("Threads"),EVENT_ID_THREAD,13*16+4},
	{WSTR("Modules"),EVENT_ID_MODULE,13*16+12},
	//{WSTR("Objects"),EVENT_ID_OBJECTWND,17},
	//{WSTR("Functions"),EVENT_ID_FUNCTIONS_WND,13*16+12},
#ifndef CODE_OS_WIN
	{WSTR("HWND"),EVENT_ID_HWNDLIST_WND,13*16+12},
#endif
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM MainMenu[]=
{
#ifndef SYSER_SCREEN_SHOT
#ifdef CODE_OS_WIN
	{WSTR("File"),0,61,WISP_MIS_POPUP,FileMenu},
#endif
#endif
	{WSTR("Debug"),0,57,WISP_MIS_POPUP,DebugMenu},
	{WSTR("Monitor"),0,53,WISP_MIS_POPUP,MonitorMenu},
	{WSTR("View"),0,126,WISP_MIS_POPUP,ViewMenu},
	{WSTR("Information"),0,95,WISP_MIS_POPUP,InfoMenu},
#ifndef SYSER_SCREEN_SHOT
#ifdef CODE_OS_WIN
	{WSTR("Option"),0,51,WISP_MIS_POPUP,OptionMenu},
#endif
#endif
	{WSTR("Tools"),0,118,WISP_MIS_POPUP,ToolsMenu},
	{WSTR("Help"),0,30,WISP_MIS_POPUP,HelpMenu},
	WISP_MENU_RES_END
};

WISP_TOOLBAR_RES_ITEM SystemExplorerToolbar[]=
{
#ifndef SYSER_SCREEN_SHOT
#ifdef CODE_OS_WIN
	{EVENT_ID_OPEN,			8,WISP_TBIS_BUTTON,WSTR("File -> Open"),0,WISP_WS_DISABLED},
	{EVENT_ID_CLOSE,		9,WISP_TBIS_BUTTON,WSTR("File -> Close"),0,WISP_WS_DISABLED},
	{EVENT_ID_RESET,		16,WISP_TBIS_BUTTON,WSTR("Debug -> Reset"),0,WISP_WS_DISABLED},
	WISP_TOOLBAR_RES_SEPARATOR,
#endif
#endif
	{EVENT_ID_STEP,			0,WISP_TBIS_BUTTON,WSTR("Debug -> Step F8")},
	{EVENT_ID_PROCEED,		1,WISP_TBIS_BUTTON,WSTR("Debug -> Proceed F10")},
	{EVENT_ID_RETURN,		2,WISP_TBIS_BUTTON,WSTR("Debug -> Return F6")},
	{EVENT_ID_CONTINUE,		3,WISP_TBIS_BUTTON,WSTR("Debug -> Continue F5")},
	WISP_TOOLBAR_RES_SEPARATOR,
	{EVENT_ID_SAVE_POS,		 16*1+8,WISP_TBIS_BUTTON,WSTR("View -> Save Position     Shift+Enter"),				0,WISP_WS_DISABLED},
	{EVENT_ID_PREV_POS,		 16*1+5,WISP_TBIS_BUTTON,WSTR("View -> Jump To Previous Position    Backspace<-"),	0,WISP_WS_DISABLED},
	{EVENT_ID_NEXT_POS,		 16*1+4,WISP_TBIS_BUTTON,WSTR("View -> Jump To Next Position    Ctrl+Enter"),		0,WISP_WS_DISABLED},
	{EVENT_ID_EMPTY_POS_LIST,38,	WISP_TBIS_BUTTON,WSTR("View -> Empty Position List"),						0,WISP_WS_DISABLED},
	WISP_TOOLBAR_RES_SEPARATOR,
	{EVENT_ID_BREAK_POINT,	4,WISP_TBIS_BUTTON,WSTR("Debug -> Break point Ctrl+F9")},
	{EVENT_ID_CALL_STACK,	18,		WISP_TBIS_BUTTON,WSTR("Monitor -> Call Stack ALT+C")},
	{EVENT_ID_RUN_TRACE_WND,181,	WISP_TBIS_BUTTON,WSTR("Monitor -> Run Trace List")},
	{EVENT_ID_COMMENT_LIST,	9*16+3,	WISP_TBIS_BUTTON,WSTR("Monitor -> Comment List")},
	WISP_TOOLBAR_RES_SEPARATOR,
	{EVENT_ID_BOOKMARK_TOGGLE,	13*16,	WISP_TBIS_BUTTON,WSTR("View -> Toggle BookMark Ctrl+K"),0,WISP_WS_DISABLED},
	{EVENT_ID_BOOKMARK_PREV,	13*16+2,WISP_TBIS_BUTTON,WSTR("View -> Previous BookMark Ctrl+P"),0,WISP_WS_DISABLED},
	{EVENT_ID_BOOKMARK_NEXT,	13*16+1,WISP_TBIS_BUTTON,WSTR("View -> Next BookMark Ctrl+N"),0,WISP_WS_DISABLED},
	{EVENT_ID_BOOKMARK_CLEAR,	13*16+3,WISP_TBIS_BUTTON,WSTR("View -> Clear BookMark Ctrl+L"),0,WISP_WS_DISABLED},
	WISP_TOOLBAR_RES_SEPARATOR,
	{EVENT_ID_MEMORY_SEARCH,13*16+15,	WISP_TBIS_BUTTON,WSTR("Tools -> Memory Search")},
	{EVENT_ID_CALC,			6,			WISP_TBIS_BUTTON,WSTR("Tools -> Calculator")},
	{EVENT_ID_SOFT_KB,		7,			WISP_TBIS_BUTTON,WSTR("Tools -> Soft keyboard")},
	////////////////////////////////////////////////////////////////////////////////
	{CMD_ID_INSTR_INFO,	0,WISP_TBIS_EDIT|WISP_TBIS_RIGHT_ALIGN,WSTR("Instruction Information"),300,
	WISP_ES_READONLY|WISP_WS_BORDER|WISP_ES_CENTER|WISP_WS_DISABLED|WISP_WS_BACK_TRANS},
	WISP_TOOLBAR_RES_STATIC_DIB(30),
	////////////////////////////////////////////////////////////////////////////////
	WISP_TOOLBAR_RES_END
};

WISP_MSG_MAP_BEGIN(CSystemExplorer)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_CMD_MAP_BEGIN(CSystemExplorer)
	WISP_MSG_CMD_MAP(CMD_ID_SYSTEM_MAIN_SPLIT,OnCommandMainSplit)
	WISP_MSG_CMD_MAP(CMD_ID_SYSTEM_VIEW_SPLIT,OnCommandViewSplit)
	WISP_MSG_CMD_MAP(CMD_ID_SYSTEM_MONITOR_SPLIT,OnCommandMonitorSplit)
	WISP_MSG_CMD_MAP(CMD_ID_MODULE_LIST_WND,OnCommandModuleWnd)
	WISP_MSG_CMD_MAP(EVENT_ID_FUNCTIONS_WND,OnCommandFunctionWnd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CSystemExplorer)
	///////////////////////////////////////////////////////////////////
	//File
	WISP_MSG_EVENT_MAP(EVENT_ID_OPEN,			OnEventOpen)
	WISP_MSG_EVENT_MAP(EVENT_ID_CLOSE,			OnEventClose)
	WISP_MSG_EVENT_MAP(EVENT_ID_LOAD_SYMBOL,	OnEventLoadSymbolFile)
	WISP_MSG_EVENT_MAP(EVENT_ID_SAVE_COMMENT,	OnEventSaveComment)
	WISP_MSG_EVENT_MAP(EVENT_ID_LOAD_COMMENT,	OnEventLoadComment)
	//File
	///////////////////////////////////////////////////////////////////
	//Debug
	WISP_MSG_EVENT_MAP(EVENT_ID_RESET,			OnEventReset)
	WISP_MSG_EVENT_MAP(EVENT_ID_CONTINUE,		OnEventContinue)
	WISP_MSG_EVENT_MAP(EVENT_ID_RETURN,			OnEventReturn)
	WISP_MSG_EVENT_MAP(EVENT_ID_STEP,			OnEventStep)
	WISP_MSG_EVENT_MAP(EVENT_ID_PROCEED,		OnEventProceed)
	WISP_MSG_EVENT_MAP(EVENT_ID_STEP_BRANCH,	OnEventStepBranch)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_BREAK_POINT,	OnEventBreakPoint)
	WISP_MSG_EVENT_MAP(EVENT_ID_ENABLE_BP_ALL,	OnEventEnableAllBreakpoint)
	WISP_MSG_EVENT_MAP(EVENT_ID_DISABLE_BP_ALL,	OnEventDisableAllBreakpoint)
	WISP_MSG_EVENT_MAP(EVENT_ID_REMOVE_BP_ALL,	OnEventRemoveAllBreakpoint)
	//Debug
	/////////////////////////////////////////////////////////////////////////
	//Analyze
	WISP_MSG_EVENT_MAP(EVENT_ID_MEMORY_SEARCH,	OnEventMemorySearch)
	//Analyze
	/////////////////////////////////////////////////////////////////////////
	//View
	WISP_MSG_EVENT_MAP(EVENT_ID_REG_VIEW,		OnEventRegView)
	WISP_MSG_EVENT_MAP(EVENT_ID_DATA_VIEW_FORM,	OnEventDataViewForm)
	WISP_MSG_EVENT_MAP(EVENT_ID_CALL_STACK,		OnEventCallStack)
	WISP_MSG_EVENT_MAP(EVENT_ID_RUN_TRACE_WND,	OnEventRunTraceWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_COMMENT_LIST,	OnEventCommentList)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_NEXT_POS,		OnEventNextPos)
	WISP_MSG_EVENT_MAP(EVENT_ID_PREV_POS,		OnEventPrevPos)
	WISP_MSG_EVENT_MAP(EVENT_ID_SAVE_POS,		OnEventSavePos)
	WISP_MSG_EVENT_MAP(EVENT_ID_EMPTY_POS_LIST,	OnEventEmptyPosList)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_TOGGLE,OnEventToggleBookMark)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_NEXT,	OnEventNextBookMark)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_PREV,	OnEventPrevBookMark)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_CLEAR,	OnEventClearBookMark)
	//View
	/////////////////////////////////////////////////////////////////////////
	//Option
	WISP_MSG_EVENT_MAP(EVENT_ID_DEBUGGER_OPTION,OnEventDebuggerOption)
	WISP_MSG_EVENT_MAP(EVENT_ID_DEBUGGER_SELECT,OnEventDebuggerSelect)
	WISP_MSG_EVENT_MAP(EVENT_ID_PLUGIN_LIST,	OnEventPluginList)
	//Option
	/////////////////////////////////////////////////////////////////////////
	//Tools
	WISP_MSG_EVENT_MAP(EVENT_ID_CALC,			OnEventCalc)
	WISP_MSG_EVENT_MAP(EVENT_ID_SOFT_KB,		OnEventSoftKB)
	WISP_MSG_EVENT_MAP(EVENT_ID_HOTKEY_CONFIGURE,OnEventSetHotKey)
	WISP_MSG_EVENT_MAP(EVENT_ID_PE_EXPLORER,	OnEventPEExplorer)
	WISP_MSG_EVENT_MAP(EVENT_ID_IBM_ASCII,		OnEventIBMAscii)
	WISP_MSG_EVENT_MAP(EVENT_ID_ANSI_ASCII,		OnEventANSIAscii)
	WISP_MSG_EVENT_MAP(EVENT_ID_EBCDIC,			OnEventEBCDIC)
	//Tools
	/////////////////////////////////////////////////////////////////////////
	//Information
	WISP_MSG_EVENT_MAP(EVENT_ID_IDT,			OnEventIDT)
	WISP_MSG_EVENT_MAP(EVENT_ID_GDT,			OnEventGDT)
	WISP_MSG_EVENT_MAP(EVENT_ID_LDT,			OnEventLDT)
	WISP_MSG_EVENT_MAP(EVENT_ID_PAGE_MAP,		OnEventPageMap)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_PROCESS,		OnEventProcess)
	WISP_MSG_EVENT_MAP(EVENT_ID_THREAD,			OnEventThreadWindow)
	WISP_MSG_EVENT_MAP(EVENT_ID_MODULE,			OnEventModuleWindow)
	WISP_MSG_EVENT_MAP(EVENT_ID_HWNDLIST_WND,	OnEventHwndListWindow)
	WISP_MSG_EVENT_MAP(EVENT_ID_FUNCTIONS_WND,	OnEventFunctionWindow)
	WISP_MSG_EVENT_MAP(EVENT_ID_OBJECTWND,		OnEventObjectWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_STRING_REFERENCE,OnEventStringReference)

	//Information
	/////////////////////////////////////////////////////////////////////////
	//Help
	WISP_MSG_EVENT_MAP(EVENT_ID_REG_HELP,		OnEventRegHelp)
#ifdef CODE_OS_WIN
	WISP_MSG_EVENT_MAP(EVENT_ID_CHECK_NEW_VERSION,OnMenuEventCheckNewVersion)
#endif
	WISP_MSG_EVENT_MAP(EVENT_ID_ABOUT,			OnMenuEventAboutSyser)
	//Help
	/////////////////////////////////////////////////////////////////////////
	//HotKey
	WISP_MSG_EVENT_MAP(EVENT_ID_SEH_CHAIN,		OnEventSEHChainWindow)
	WISP_MSG_EVENT_MAP(EVENT_ID_GEN_REG,		OnHotKeyEventGeneReg)
	WISP_MSG_EVENT_MAP(EVENT_ID_FPU_REG,		OnHotKeyEventFPUReg)
	WISP_MSG_EVENT_MAP(EVENT_ID_XMM_REG,		OnHotKeyEventXMMReg)
	WISP_MSG_EVENT_MAP(EVENT_ID_STACK_WATCH_LIST,OnHotKeyEventStack)
	WISP_MSG_EVENT_MAP(EVENT_ID_WATCH_LIST,		OnHotKeyEventWatch)
	WISP_MSG_EVENT_MAP(EVENT_ID_CODEVIEW,		OnHotKeyEventCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_DATAVIEW,		OnHotKeyEventDataView)

	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_FILE,			OnHotKeyEventMenuFile)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_DEBUG,			OnHotKeyEventMenuDebug)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_VIEW,			OnHotKeyEventMenuView)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_MONITOR,		OnHotKeyEventMenuMonitor)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_INFORMATION,	OnHotKeyEventMenuInformation)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_OPTION,		OnHotKeyEventMenuOption)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_TOOL,			OnHotKeyEventMenuTools)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_HELP,			OnHotKeyEventMenuHelp)
	WISP_MSG_EVENT_MAP(EVENT_ID_GETNEXTTRACE,		OnGetNextTrace)
	WISP_MSG_EVENT_MAP(EVENT_ID_GETPREVTRACE,		OnGetPrevTrace)
	//HotKey
	/////////////////////////////////////////////////////////////////////////
WISP_MSG_EVENT_MAP_DEFAULT_END(OnEventRecentFile)

CSystemExplorer::CSystemExplorer()
{
	m_pCurCodeView = NULL;
	m_CPUNumbers=1;
}

CSystemExplorer::~CSystemExplorer()
{
}

bool CSystemExplorer::OnEventStringReference(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_FindListWnd.Create(WSTR("String Reference"),0,0,564,344,NULL,EVENT_ID_STRING_REFERENCE_WISPLIST,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL|WISP_WLS_TREE);
	return true;
}

bool CSystemExplorer::CreateRegWindows(IN WISP_MSG*pMsg)
{
	int j=gCPUNumbers,i;
	WCHAR WndText[30];
	m_CPUNumbers=gCPUNumbers;
	m_pWndRegTab = new CWispTabWnd[j];
	if(m_pWndRegTab==NULL)
		return false;
	m_pWndFpuReg=new CFpuRegisterList[j];	
	m_pWndESSReg=new CSSERegisterList[j];
	m_pWndGeneReg=new CGeneRegList[j];
	if(m_pWndFpuReg==NULL || m_pWndESSReg==NULL || m_pWndGeneReg==NULL)
	{
		delete []m_pWndRegTab;
		if(m_pWndFpuReg)
			delete []m_pWndFpuReg;
		if(m_pWndESSReg)
			delete []m_pWndESSReg;
		if(m_pWndGeneReg)
			delete []m_pWndGeneReg;
		return false;
	}
	if(m_MultiCPUTabWnd.Create(WSTR(""),0,0,170,310,&m_MonitorSplitWnd,0,WISP_TWS_TOP)==false)
	{
		delete []m_pWndRegTab;
		delete []m_pWndFpuReg;
		delete []m_pWndESSReg;
		delete []m_pWndGeneReg;
		return false;
	}
	for(i=0;i<j;i++)
	{		
		if(m_pWndRegTab[i].Create(WSTR("Reg"),CWispRect(0,0,170,310),&m_MultiCPUTabWnd,0,WISP_TWS_BUTTOM)==false)
			return false;
		if(m_pWndGeneReg[i].Create(NULL,CWispRect(0,0,0,0),&m_pWndRegTab[i],CMD_ID_GENERAL_REGISTER_WND,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT)==false)
			return false;
		m_pWndGeneReg[i].SetOwner(this);
		m_pWndGeneReg[i].SetCPUIndex(i);
		if(m_pWndFpuReg[i].Create(NULL,CWispRect(0,0,0,0),&m_pWndRegTab[i],CMD_ID_FPU_REGISTER_WND,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT)==false)
			return false;
		m_pWndFpuReg[i].SetOwner(this);
		m_pWndFpuReg[i].SetCPUIndex(i);
		if(m_pWndESSReg[i].Create(NULL,CWispRect(0,0,0,0),&m_pWndRegTab[i],CMD_ID_ESS_REGISTER_WND,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT)==false)
			return false;
		m_pWndESSReg[i].SetOwner(this);
		m_pWndESSReg[i].SetCPUIndex(i);
		m_pWndRegTab[i].InsertWnd(WSTR("REG ALT+R"),&m_pWndGeneReg[i],WispTKDIBListDIB("\\Toolbar.bmp",16,16,52));
		m_pWndRegTab[i].InsertWnd(WSTR("FPU ALT+F"),&m_pWndFpuReg[i],WispTKDIBListDIB("\\Toolbar.bmp",16,16,58));
		m_pWndRegTab[i].InsertWnd(WSTR("XMM ALT+X"),&m_pWndESSReg[i],WispTKDIBListDIB("\\Toolbar.bmp",16,16,48));
		TSPrintf(WndText,WSTR(" CPU %d "),i);
		m_MultiCPUTabWnd.InsertWnd(WndText,&m_pWndRegTab[i]);
	}
	
	return true;
}
bool CSystemExplorer::OnCreate(IN WISP_MSG*pMsg)
{
	WISP_CHAR szBuffer[256];
	m_WndMenu.CreateWndMenu(this,WISP_ID_MAIN_MENU,MainMenu,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_WndMenu.SetOwner(this);
	m_ContextStr.Create(WSTR(""),680,m_WndMenu.m_ClientRect.cy-16,138,16,&m_WndMenu,0,WISP_WS_NULL);	
	m_VersionStr.Create(NULL,530,m_WndMenu.m_ClientRect.cy-16,138,16,&m_WndMenu,0,WISP_WS_NULL);
	m_VersionStr.m_WindowDC.m_TextColor=WISP_RGB(0xff,0,0);
	TStrCpy(szBuffer,"Ver: ");
	TStrCat(szBuffer,VER_PRODUCTVERSION_STR);
	m_VersionStr.SetWindowText(szBuffer);
	m_Toolbar.CreateEx(this,m_WndMenu.m_WindowRect.cy,-1,WISP_ID_MAIN_TOOLBAR,WISP_WS_NULL);
	m_Toolbar.LoadToolbar(WispTKDIBList("\\Toolbar.bmp",16,16),SystemExplorerToolbar);
	m_Toolbar.SetOwner(this);
	m_pInfoMsgWnd = m_Toolbar.GetToolbarItem(CMD_ID_INSTR_INFO);
	if(m_pInfoMsgWnd==NULL)
		return false;
	if(m_MainSplitWnd.Create(NULL,CWispRect(0,m_Toolbar.m_WindowRect.cy+m_WndMenu.m_WindowRect.cy,m_ClientRect.cx,m_ClientRect.cy-m_Toolbar.m_WindowRect.cy-m_WndMenu.m_WindowRect.cy),this,CMD_ID_SYSTEM_MAIN_SPLIT,WISP_SWS_HORZ)==false)
		return false;
	if(m_ViewSplitWnd.Create(NULL,CWispRect(0,0,0,0),&m_MainSplitWnd,CMD_ID_SYSTEM_VIEW_SPLIT,WISP_SWS_VERT)==false)
		return false;
	m_ViewSplitWnd.SetOwner(this);
	if(m_MonitorSplitWnd.Create(NULL,CWispRect(0,0,0,0),&m_MainSplitWnd,CMD_ID_SYSTEM_MONITOR_SPLIT,WISP_SWS_VERT)==false)
		return false;
	m_MonitorSplitWnd.SetOwner(this);
	m_MainSplitWnd.InsertWnd(&m_MonitorSplitWnd,0,DEFAULT_MONITOR_VIEW_SIZE);
	m_MainSplitWnd.InsertWnd(&m_ViewSplitWnd,0,200);
	m_MainSplitWnd.AdjustWndPos();
	if(m_MultiDataView.Create(NULL,CWispRect(0,0,0,0),&m_ViewSplitWnd,CMD_ID_MULTI_DATA_VIEW_TAB,WISP_TWS_TOP|WISP_TWS_CLOSE_BT|WISP_TWS_MULTI_VIEW_STYLE|WISP_TWS_HIDE_TAB_SINGLE)==false)
		return false;
	if(m_MultiCodeView.Create(NULL,CWispRect(0,0,0,0),&m_ViewSplitWnd,CMD_ID_MULTI_CODE_VIEW_TAB,WISP_TWS_TOP|WISP_TWS_CLOSE_BT|WISP_TWS_MULTI_VIEW_STYLE|WISP_TWS_HIDE_TAB_SINGLE)==false)
		return false;
	if(m_TerminalWnd.Create(NULL,CWispRect(0,0,0,0),&m_ViewSplitWnd,CMD_ID_TERMINAL_WND,WISP_WS_NULL)==false)
		return false;
	m_TerminalWnd.AttachConsole(&gpSyser->m_MainFrame.m_ConsoleWnd);
	m_TerminalWnd.SetHistoryLines(350);
	m_ViewSplitWnd.InsertWnd(&m_MultiDataView,0,90);
	m_ViewSplitWnd.InsertWnd(&m_MultiCodeView,0,gpCurWisp->m_pRootWnd->m_ClientRect.cy/2);
	m_ViewSplitWnd.InsertWnd(&m_TerminalWnd,0,30);
	m_ViewSplitWnd.AdjustWndPos();
	
	if(CreateRegWindows(pMsg)==false)
		return false;
	
	if(m_ContextTabWnd.Create(WSTR("Context"),CWispRect(0,0,170,200),&m_MonitorSplitWnd,0,WISP_TWS_BUTTOM)==false)
		return false;
	if(m_WatchList.Create(NULL,CWispRect(0,0,0,0),&m_ContextTabWnd,0,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT)==false)
		return false;
	if(m_StackWatchList.Create(NULL,CWispRect(0,0,0,0),&m_ContextTabWnd,0,WISP_WLS_COLUMN_TITLE|WISP_WLS_EMPTY_SEL_RECT)==false)
		return false;
	m_ContextTabWnd.InsertWnd(WSTR("Stack ALT+S"),&m_StackWatchList,WispTKDIB("\\SyserIcon\\Stack.bmp",0));
	m_ContextTabWnd.InsertWnd(WSTR("Watch ALT+W"),&m_WatchList,WispTKDIB("\\SyserIcon\\Watch.bmp",0));

	
	m_MonitorSplitWnd.InsertWnd(&m_MultiCPUTabWnd,0,m_MultiCPUTabWnd.m_WindowRect.cy);
	//m_MonitorSplitWnd.InsertWnd(&m_RegTabWnd,0,m_RegTabWnd.m_WindowRect.cy);
	m_MonitorSplitWnd.InsertWnd(&m_ContextTabWnd,0,m_ContextTabWnd.m_WindowRect.cy);
	m_MonitorSplitWnd.AdjustWndPos();

	RegisterHotKey(EVENT_ID_GEN_REG,WISP_VK_R,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_FPU_REG,WISP_VK_F,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_XMM_REG,WISP_VK_X,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_WATCH_LIST,WISP_VK_W,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_STACK_WATCH_LIST,WISP_VK_S,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_CODEVIEW,WISP_VK_F1,0);
	RegisterHotKey(EVENT_ID_DATAVIEW,WISP_VK_F1,WISP_MOD_SHIFT);
	
	RegisterHotKey(EVENT_ID_MENU_FILE,WISP_VK_F,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_DEBUG,WISP_VK_D,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_MONITOR,WISP_VK_M,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_VIEW,WISP_VK_V,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_INFORMATION,WISP_VK_I,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_OPTION,WISP_VK_O,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_TOOL,WISP_VK_T,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_HELP,WISP_VK_H,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_GETNEXTTRACE,WISP_VK_ADD,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_GETPREVTRACE,WISP_VK_SUBTRACT,WISP_MOD_ALT);
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_TOGGLE,this);	
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_NEXT,this);
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_PREV,this);
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_CLEAR,this);
	
	return true;
}

bool CSystemExplorer::OnDestroy(IN WISP_MSG*pMsg)
{
	m_WndMenu.Destroy();
	return true;
}

bool CSystemExplorer::OnEventRecentFile(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_WIN
	int Index;
	if(pMsg->Command.CmdID>EVENT_ID_RECENT_FILE && pMsg->Command.CmdID<=EVENT_ID_RECENT_FILE_END)
	{
		Index = pMsg->Command.CmdID-EVENT_ID_RECENT_FILE-1;
		TList<RECENT_HISTROY_ITEM>::IT Iter = gpSyser->m_HistroyList[Index];
		if(Iter!=gpSyser->m_HistroyList.End())
		{
			gpSyser->m_SyserUI.m_CodeDoc.Close();
			gpSyser->m_SyserUI.m_CodeDoc.Open(Iter->FileName);
		}
	}
#endif
	return true;
}

bool CSystemExplorer::OnEventRunTraceWnd(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_RunTraceWnd.Popup();
	return true;
}
ULSIZE	PEFileRead(ULPOS Address,void*Buffer,ULSIZE Size,void*Param)
{
	CX86Debugger* pDebug=(CX86Debugger* )Param;
	return pDebug->ReadMemory(Address,Buffer,Size);
}
bool CSystemExplorer::OnEventOpen(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_WIN
	if(gpSyser->m_pDebugger==NULL)
		return true;
	char szBuffer[MAX_FN_LEN],szFileName[MAX_FN_LEN];
	if(gpSyser->m_szDbgFileNameFilter.Length())
	{
		OPENFILENAME OpenFileName;
		STZeroMemory(OpenFileName);
		OpenFileName.lStructSize = sizeof(OPENFILENAME);
		OpenFileName.hInstance = gpSyser->m_hLocalInst;
		OpenFileName.hwndOwner = gpSyser->m_hLocalWnd;
		UnicodeToAnsi(gpSyser->m_szDbgFileNameFilter,szBuffer,sizeof(szBuffer));
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
		TStrCpy(szFileName,OpenFileName.lpstrFile);
	}
	else
	{
		*szFileName=0;
	}
	if(gpSyser->m_SyserUI.m_CodeDoc.Open(szFileName)==false)
		SYSEXPLR_OUTPUT(WSTR("Fail to open file !\n"));
	
#endif
	return true;
}

bool CSystemExplorer::OnEventClose(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("close"));
	return true;
}

bool CSystemExplorer::OnEventEnableAllBreakpoint(IN WISP_MSG* pMsg)
{
	RUNCMD(WSTR("be *"));
	return true;
}

bool CSystemExplorer::OnEventDisableAllBreakpoint(IN WISP_MSG* pMsg)
{
	RUNCMD(WSTR("bd *"));
	return true;
}

bool CSystemExplorer::OnEventRemoveAllBreakpoint(IN WISP_MSG* pMsg)
{
	RUNCMD(WSTR("bc *"));
	return true;
}

bool CSystemExplorer::OnEventLoadComment(IN WISP_MSG*pMsg)
{
	gpSyser->m_SyserUI.LoadComment();
	return true;
}

bool CSystemExplorer::OnEventSaveComment(IN WISP_MSG*pMsg)
{
	gpSyser->m_SyserUI.SaveComment();
	return true;
}

bool CSystemExplorer::OnEventMemorySearch(IN WISP_MSG*pMsg)
{
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return true;
	m_SearchDialog.CreateForm(NULL);
	return true;
}

bool CSystemExplorer::OnEventCommentList(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_CommentList.Popup();
	return true;
}

bool CSystemExplorer::OnEventLoadSymbolFile(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_WIN
	char szFileName[MAX_FN_LEN],szDir[MAX_FN_LEN];
	OPENFILENAME OpenFileName;
	STZeroMemory(OpenFileName);
	OpenFileName.lStructSize = sizeof(OPENFILENAME);
	OpenFileName.hInstance = gpSyser->m_hLocalInst;
	OpenFileName.hwndOwner = gpSyser->m_hLocalWnd;
	OpenFileName.lpstrFilter = "Symbol Files\0*.sds\0";
	OpenFileName.nMaxFile = sizeof(szFileName);
	OpenFileName.lpstrFile = szFileName;
	GetModulePath(szDir);
	TStrCat(szDir,"Symbols");
	OpenFileName.lpstrInitialDir = szDir;
	*szFileName = 0;
	gpSyser->LockTimer();
	if(GetOpenFileName(&OpenFileName)==false)
	{
		gpSyser->UnlockTimer();
		return true;
	}
	gpSyser->UnlockTimer();
	gpSyser->m_SyserUI.LoadSDSModule(szFileName);
#endif
	return true;
}

bool CSystemExplorer::OnEventPrevPos(IN WISP_MSG*pMsg)
{
	m_pCurCodeView->OnEventPrevPos(pMsg);
	return true;
}

bool CSystemExplorer::OnEventNextPos(IN WISP_MSG*pMsg)
{
	m_pCurCodeView->OnEventNextPos(pMsg);
	return true;
}

bool CSystemExplorer::OnEventSavePos(IN WISP_MSG*pMsg)
{
	m_pCurCodeView->OnEventSavePos(pMsg);
	return true;
}

bool CSystemExplorer::OnEventEmptyPosList(IN WISP_MSG*pMsg)
{
	m_pCurCodeView->OnEventEmptyPosList(pMsg);
	return true;
}


bool CSystemExplorer::OnEventIDT(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_IDTWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventGDT(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_GDTWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventLDT(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_GDTWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventProcess(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_ProcessList.Popup();
	return true;
}

bool CSystemExplorer::OnEventModuleWindow(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.m_ModuleList.Popup();
	return true;
}
bool CSystemExplorer::OnEventHwndListWindow(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.m_HwndListWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventFunctionWindow(IN WISP_MSG* pMsg)
{
	if(m_FunctionWnd.IsWindow()==false)
	{
		m_FunctionWnd.Create(WSTR("Functions"),0,0,500,350,NULL,EVENT_ID_FUNCTIONS_WND,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL);
		m_FunctionWnd.SetOwner(this);
		m_FunctionWnd.InsertColumn(WSTR("Function name"),240);
		m_FunctionWnd.InsertColumn(WSTR("Start"),80);
		m_FunctionWnd.InsertColumn(WSTR("Length"),80);
		m_FunctionWnd.InsertColumn(WSTR("BP based frame"),80);
		/*
		CDbgModule* pMod=	gpSyser->m_pDebugger->m_ModuleList.GetModule(*gpSyser->m_pDebugger->m_pExecutePoint);
		CDbgModuleMap::IT DbgIT = gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();
		DbgIT++;
		pMod =& *DbgIT;

		m_Analyzer.Open(pMod->m_ModuleBase,pMod->m_ModuleSize,PEFileRead,gpSyser->m_pDebugger);
		m_Analyzer.AnalyzerFromExportFunction(100,1000);
		//m_Analyzer.AnalyzerFromEntryPoint(100,1000);
		TFuncMap::IT BeginIT,EndIT;
		BeginIT = m_Analyzer.m_FuncMap.Begin();
		EndIT=m_Analyzer.m_FuncMap.End();
		HANDLE hItem;
		for(;BeginIT!=EndIT;BeginIT++)
		{
			hItem = m_FunctionWnd.InsertItemW(BeginIT->m_Name,NULL);
			m_FunctionWnd.SetItemNum(hItem,1,BeginIT->m_Start,WSTR("%08X"));
			m_FunctionWnd.SetItemData(hItem,1,BeginIT->m_Start);
			m_FunctionWnd.SetItemNum(hItem,2,BeginIT->m_End-BeginIT->m_Start,WSTR("%x"));
		}
		m_Analyzer.Close();
		*/
		m_FunctionWnd.Center();
	}
	else
	{
		m_FunctionWnd.Show(WISP_SH_NORMAL);
		m_FunctionWnd.Center();
	}
	return true;
}
bool CSystemExplorer::OnEventThreadWindow(IN WISP_MSG* pMsg)
{
	if(m_ThreadListWnd.IsWindow()==false)
	{
		m_ThreadListWnd.Create(WSTR("Threads"),0,0,500,350,NULL,CMD_ID_THREAD_LIST_WND,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL);
		m_ThreadListWnd.UpdateContext();
		m_ThreadListWnd.Center();
		m_ThreadListWnd.Focus();
	}
	else
	{
		m_ThreadListWnd.Show(WISP_SH_NORMAL);
		m_ThreadListWnd.UpdateContext();
		m_ThreadListWnd.Center();
		m_ThreadListWnd.Focus();
	}
	return true;
}

bool CSystemExplorer::OnEventPageMap(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_PageMapWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventObjectWnd(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_ObjectWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventRegHelp(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_RegHelpWnd.Popup();
	return true;
}

bool CSystemExplorer::OnMenuEventAboutSyser(IN WISP_MSG*pMsg)
{
	CAboutForm	AboutForm;
	AboutForm.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	AboutForm.Destroy();
	return true;
}

#ifdef CODE_OS_WIN
bool CSystemExplorer::OnMenuEventCheckNewVersion(IN WISP_MSG*pMsg)
{
	ShellExecute(NULL,"open","http://www.sysersoft.com/queryw32version.php?version=" VER_PRODUCTVERSION_STR "&date=" __DATE__,NULL,NULL,SW_SHOWMAXIMIZED);
	return true;
}
#endif

bool CSystemExplorer::OnEventContinue(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("x"));
	return true;
}

bool CSystemExplorer::OnEventReset(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("reset"));
	return true;
}

bool CSystemExplorer::OnEventStep(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("t"));
	return true;
}

bool CSystemExplorer::OnEventStepBranch(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("tb"));
	return true;
}

bool CSystemExplorer::OnEventProceed(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("p"));
	return true;
}

bool CSystemExplorer::OnEventReturn(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("p ret"));
	return true;
}

bool CSystemExplorer::OnEventBreakPoint(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_BreakPointForm.Popup();
	if(pMsg->Command.CmdMsg == WISP_CMD_HOTKEY)
		return false;
	return true;
}

bool CSystemExplorer::OnEventDebuggerSelect(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_WIN
	gpSyser->m_MainFrame.m_DebuggerSelectForm.Popup();
#endif
	return true;
}

bool CSystemExplorer::OnEventDebuggerOption(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_WIN
	if(m_SyserOptionForm.IsWindow())
		m_SyserOptionForm.Show();
	else
		m_SyserOptionForm.CreateForm();
#endif
	return true;
}

bool CSystemExplorer::OnEventPluginList(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_PluginListForm.Popup();
	return true;
}

bool CSystemExplorer::OnEventCalc(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_WispCalcWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventSoftKB(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_SoftKeyboard.Popup();
	return true;
}

bool CSystemExplorer::OnEventSetHotKey(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_KeyMapForm.Popup(); 
	return true;
}

bool CSystemExplorer::OnEventPEExplorer(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_PEExplorerForm.Popup();
	return true;
}
bool CSystemExplorer::OnEventIBMAscii(IN WISP_MSG*pMsg)
{

	gpSyser->m_MainFrame.m_IBMAsciiWnd.Popup();		
	gpSyser->m_MainFrame.m_IBMAsciiWnd.SetFont(2);
	gpSyser->m_MainFrame.m_IBMAsciiWnd.Update();
	return true;
}

bool CSystemExplorer::OnEventANSIAscii(IN WISP_MSG*pMsg)
{
	
	gpSyser->m_MainFrame.m_ANSIAsciiWnd.Popup();			
	gpSyser->m_MainFrame.m_ANSIAsciiWnd.SetFont(4);
	gpSyser->m_MainFrame.m_ANSIAsciiWnd.Update();
	return true;
}

bool CSystemExplorer::OnEventEBCDIC(IN WISP_MSG*pMsg)
{	
	gpSyser->m_MainFrame.m_EBEDICWnd.Popup();			
	gpSyser->m_MainFrame.m_EBEDICWnd.SetFont(3);
	gpSyser->m_MainFrame.m_EBEDICWnd.Update();
	return true;
}

bool CSystemExplorer::OnEventToggleBookMark(IN WISP_MSG*pMsg)
{
	m_MultiCodeView.ToggleBookMark();
	return true;
}

bool CSystemExplorer::OnEventNextBookMark(IN WISP_MSG*pMsg)
{
	m_MultiCodeView.GotoNextBookMark();
	return true;
}

bool CSystemExplorer::OnEventPrevBookMark(IN WISP_MSG*pMsg)
{
	m_MultiCodeView.GotoPrevBookMark();
	return true;
}

bool CSystemExplorer::OnEventClearBookMark(IN WISP_MSG*pMsg)
{
	m_MultiCodeView.ClearAllBookMark();
	return true;
}

void CSystemExplorer::UpdateItemState()
{
	bool bState;
#ifdef CODE_OS_WIN//驱动里没这些菜单项或者没必要修改
	bState = gpSyser->m_SyserUI.m_CodeDoc.IsOpened();

	m_Toolbar.EnableItem(EVENT_ID_OPEN,!bState);
	m_WndMenu.EnableItem(EVENT_ID_OPEN,!bState);

	m_Toolbar.EnableItem(EVENT_ID_CLOSE,bState);
	m_WndMenu.EnableItem(EVENT_ID_CLOSE,bState);

	m_Toolbar.EnableItem(EVENT_ID_RESET,bState);
	m_WndMenu.EnableItem(EVENT_ID_RESET,bState);

	m_Toolbar.EnableItem(EVENT_ID_CONTINUE,bState);
	m_WndMenu.EnableItem(EVENT_ID_CONTINUE,bState);

	m_Toolbar.EnableItem(EVENT_ID_RETURN,bState);
	m_WndMenu.EnableItem(EVENT_ID_RETURN,bState);

	m_Toolbar.EnableItem(EVENT_ID_STEP,bState);
	m_WndMenu.EnableItem(EVENT_ID_STEP,bState);

	m_Toolbar.EnableItem(EVENT_ID_PROCEED,bState);
	m_WndMenu.EnableItem(EVENT_ID_PROCEED,bState);

	m_Toolbar.EnableItem(EVENT_ID_STEP_BRANCH,bState);
	m_WndMenu.EnableItem(EVENT_ID_STEP_BRANCH,bState);

	m_Toolbar.EnableItem(EVENT_ID_SAVE_COMMENT,bState);
	m_WndMenu.EnableItem(EVENT_ID_SAVE_COMMENT,bState);

	m_Toolbar.EnableItem(EVENT_ID_LOAD_COMMENT,bState);
	m_WndMenu.EnableItem(EVENT_ID_LOAD_COMMENT,bState);

	m_Toolbar.EnableItem(EVENT_ID_RECENT_FILE,bState);
	m_WndMenu.EnableItem(EVENT_ID_RECENT_FILE,bState);
#endif
	bState = gpSyser->m_SyserUI.m_CodeDoc.IsOpened();
	m_Toolbar.EnableItem(EVENT_ID_SAVE_POS,bState);
	m_WndMenu.EnableItem(EVENT_ID_SAVE_POS,bState);

	bState = m_pCurCodeView->m_AddrIter!=m_pCurCodeView->m_AddrList.Begin()	&& gpSyser->m_SyserUI.m_CodeDoc.IsOpened();
	m_Toolbar.EnableItem(EVENT_ID_PREV_POS,bState);
	m_WndMenu.EnableItem(EVENT_ID_PREV_POS,bState);

	bState=m_pCurCodeView->m_AddrIter!=m_pCurCodeView->m_AddrList.Last() && gpSyser->m_SyserUI.m_CodeDoc.IsOpened();
	m_Toolbar.EnableItem(EVENT_ID_NEXT_POS,bState);
	m_WndMenu.EnableItem(EVENT_ID_NEXT_POS,bState);

	bState = (m_pCurCodeView->m_AddrList.Count() > 1) && gpSyser->m_SyserUI.m_CodeDoc.IsOpened();
	m_Toolbar.EnableItem(EVENT_ID_EMPTY_POS_LIST,bState);
	m_WndMenu.EnableItem(EVENT_ID_EMPTY_POS_LIST,bState);

	bState = gpSyser->m_SyserUI.m_CodeDoc.IsOpened();
	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_TOGGLE,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_TOGGLE,bState);

	bState = m_MultiCodeView.m_BookMark.Count()>0 && gpSyser->m_SyserUI.m_CodeDoc.IsOpened();

	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_NEXT,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_NEXT,bState);

	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_PREV,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_PREV,bState);

	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_CLEAR,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_CLEAR,bState);

	m_Toolbar.Update();
}


void CSystemExplorer::InsertRunTrace()
{
	CCodeView*pCodeView;
	UINT CodeViewIndex;
	pCodeView=(CCodeView*)m_MultiCodeView.GetActiveWnd();
	if(pCodeView==NULL)
		return;
	CodeViewIndex = m_MultiCodeView.GetActiveWndIndex();
	m_TraceCount = m_RunTrace.Insert(pCodeView->m_CurAddr,*X86_REG_PTR.pEIP,CodeViewIndex);
	m_TraceMoveIndex = m_TraceCount;
	for(DWORD i=0;i<m_CPUNumbers;i++)
	{
		m_pWndGeneReg[i].EnableWindow(true);
	}
	//REG_LIST.EnableWindow(true);
}

void CSystemExplorer::OnHide()
{
	CCodeView*pActiveWnd=(CCodeView*)m_MultiCodeView.GetActiveWnd();
	if(pActiveWnd && pActiveWnd->m_TipFullItemTextWnd.IsVisible())
	{
		pActiveWnd->HideItemTip();
	}
}

bool CSystemExplorer::SetRunTrace(UINT Index)
{
	PSTRUNTRACE pTrace;
	m_TraceMoveIndex=Index+2;
	pTrace = GetPrevTrace();
	if(pTrace==NULL)return false;
	CCodeView*pCodeView;
	pCodeView=(CCodeView*)m_MultiCodeView.GetActiveWnd();
	if(pCodeView==NULL)
		return false;
	pCodeView->SetStartAddress(pTrace->CodeViewStartAddress);
	pCodeView->SetSelectItemByAddress(pTrace->CodeViewStartAddress+pTrace->EIPOffset);
	return true;
}

PSTRUNTRACE CSystemExplorer::GetNextTrace()
{
	DWORD EIP=0;
	PSTRUNTRACE pTrace;
	X86_REG_CONTEXT RegContext;
	DWORD RegModifyMask,i;
	if(m_TraceMoveIndex==m_TraceCount)
		return NULL;
	m_TraceMoveIndex++;
	if(m_TraceMoveIndex==m_TraceCount)
	{
		for(i=0;i<m_CPUNumbers;i++)
		{
			m_pWndGeneReg[i].EnableWindow(true);
		}
	}else
	{
		for(i=0;i<m_CPUNumbers;i++)
		{
			if(m_pWndGeneReg[i].IsDisabled()==false)
				m_pWndGeneReg[i].EnableWindow(false);
		}
	}
	pTrace = m_RunTrace.GetTraceByIndex(m_TraceMoveIndex-1);
	if(pTrace==NULL)
		return pTrace;
	EIP = pTrace->CodeViewStartAddress+pTrace->EIPOffset;
	m_RunTrace.GetRegisterContext(m_TraceMoveIndex-1,&RegContext,&RegModifyMask);
	CWispTabWnd* pWndRegTab = (CWispTabWnd*)m_MultiCPUTabWnd.GetActiveWnd();
	CGeneRegList* pWndGeneReg;
	if(pWndRegTab)
	{
		pWndGeneReg = (CGeneRegList*)pWndRegTab->GetWnd(0);
		pWndGeneReg->RunTraceUpdateContext(RegModifyMask,&RegContext,EIP);
		pWndGeneReg->Update();
	}

	return pTrace;
}

PSTRUNTRACE CSystemExplorer::GetPrevTrace()
{
	PSTRUNTRACE pTrace;
	DWORD EIP=0;
	X86_REG_CONTEXT RegContext;
	DWORD RegModifyMask,i;
	if(m_TraceMoveIndex==1)
		return NULL;
	m_TraceMoveIndex--;

	for(i=0;i<m_CPUNumbers;i++)
	{
		if(m_pWndGeneReg[i].IsDisabled()==false)
			m_pWndGeneReg[i].EnableWindow(false);
	}

	if(m_TraceMoveIndex==m_TraceCount)
	{
		for(i=0;i<m_CPUNumbers;i++)
		{			
			m_pWndGeneReg[i].EnableWindow(true);
		}
	}
	pTrace = m_RunTrace.GetTraceByIndex(m_TraceMoveIndex-1);
	if(pTrace==NULL)
		return pTrace;
	EIP = pTrace->CodeViewStartAddress+pTrace->EIPOffset;
	m_RunTrace.GetRegisterContext(m_TraceMoveIndex-1,&RegContext,&RegModifyMask);

	CWispTabWnd* pWndRegTab = (CWispTabWnd*)m_MultiCPUTabWnd.GetActiveWnd();
	CGeneRegList* pWndGeneReg;
	if(pWndRegTab)
	{
		pWndGeneReg = (CGeneRegList*)pWndRegTab->GetWnd(0);
		pWndGeneReg->RunTraceUpdateContext(RegModifyMask,&RegContext,EIP);
		pWndGeneReg->Update();
	}
	return pTrace;

}

bool CSystemExplorer::OnEventDataViewForm(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.m_DataViewForm.Popup();
	return true;
}

bool CSystemExplorer::OnEventRegView(IN WISP_MSG* pMsg)
{
	DWORD dwCurrentID=0,i;
	WCHAR WndText[20];
	if(gpSyser->m_MainFrame.m_pRegWnd==NULL)
	{
		gpSyser->m_MainFrame.m_pRegWnd=new CGeneRegList[gCPUNumbers];
	}
#ifdef CODE_OS_NT_DRV	
	dwCurrentID = GetCurrentCPULocalAPICID();
#endif
	
	if(gpSyser->m_MainFrame.m_MultiCPURegView.IsWindow()==false)
	{			
		gpSyser->m_MainFrame.m_MultiCPURegView.Create(WSTR("Register View"),CWispRect(0,0,320,210),NULL,0,WISP_TWS_BUTTOM|WISP_WS_NORMAL);
		for(i=0;i<gCPUNumbers;i++)
		{
			if(gpSyser->m_MainFrame.m_pRegWnd[i].Create(NULL,CWispRect(0,0,0,0),&gpSyser->m_MainFrame.m_MultiCPURegView,CMD_ID_GENERAL_REGISTER_WND,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT)==false)
				return false;
			gpSyser->m_MainFrame.m_pRegWnd[i].SetCPUIndex(i);
			if(i!=dwCurrentID)
				TSPrintf(WndText,WSTR(" CPU %d "),i);
			else
				TSPrintf(WndText,WSTR("*CPU %d "),i);
			gpSyser->m_MainFrame.m_MultiCPURegView.InsertWnd(WndText,&gpSyser->m_MainFrame.m_pRegWnd[i]);
			gpSyser->m_MainFrame.m_pRegWnd[i].UpdateContext();
		}		
	}
	else
	{
		gpSyser->m_MainFrame.m_MultiCPURegView.Destroy();
		for(i=0;i<gCPUNumbers;i++)
		{
			gpSyser->m_MainFrame.m_pRegWnd[i].Destroy();
		}
	}
	
	return true;
}

bool CSystemExplorer::OnEventCallStack(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.m_CallStackWnd.Popup();
	return true;
}

bool CSystemExplorer::OnEventSEHChainWindow(IN WISP_MSG* pMsg)
{
	if(m_SEHChainWnd.IsWindow()==false)
	{
		m_SEHChainWnd.Create(WSTR("SEH Chain"),0,0,620,280,NULL,CMD_ID_SEH_LIST_WND,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL);
		m_SEHChainWnd.Center();
	}
	else
	{
		m_SEHChainWnd.Show(WISP_SH_NORMAL);
		m_SEHChainWnd.Center();
	}
	return true;
}


bool CSystemExplorer::OnHotKeyEventGeneReg(IN WISP_MSG*pMsg)
{
	CWispTabWnd* pWndRegTab = (CWispTabWnd*)m_MultiCPUTabWnd.GetActiveWnd();
	if(pWndRegTab)
		pWndRegTab->SetActiveWnd(0);	
	return false;
}

bool CSystemExplorer::OnHotKeyEventFPUReg(IN WISP_MSG*pMsg)
{
	CWispTabWnd* pWndRegTab = (CWispTabWnd*)m_MultiCPUTabWnd.GetActiveWnd();
	if(pWndRegTab)
		pWndRegTab->SetActiveWnd(1);	

	//m_WndMenu.OnKeyEvent(&Msg);
//m_WndMenu.OnKeyEvent(&Msg);
	return false;
}

bool CSystemExplorer::OnHotKeyEventXMMReg(IN WISP_MSG*pMsg)
{
	CWispTabWnd* pWndRegTab = (CWispTabWnd*)m_MultiCPUTabWnd.GetActiveWnd();
	if(pWndRegTab)
		pWndRegTab->SetActiveWnd(2);
	return false;
}

bool CSystemExplorer::OnHotKeyEventStack(IN WISP_MSG*pMsg)
{
	m_ContextTabWnd.SetActiveWnd(0);
	return false;
}

bool CSystemExplorer::OnHotKeyEventWatch(IN WISP_MSG*pMsg)
{
	m_ContextTabWnd.SetActiveWnd(1);
	return false;
}

bool CSystemExplorer::OnHotKeyEventMenuFile(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("File"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}

bool CSystemExplorer::OnHotKeyEventMenuDebug(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("Debug"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}
bool CSystemExplorer::OnHotKeyEventMenuView(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("View"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}
bool CSystemExplorer::OnHotKeyEventMenuMonitor(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("Monitor"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}
bool CSystemExplorer::OnHotKeyEventMenuInformation(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("Information"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}
bool CSystemExplorer::OnHotKeyEventMenuOption(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("Option"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}
bool CSystemExplorer::OnHotKeyEventMenuTools(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("Tools"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}
bool CSystemExplorer::OnHotKeyEventMenuHelp(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_MSG Msg;
	m_WndMenu.Focus();		
	hItem=m_WndMenu.GetItemByName(WSTR("Help"));
	if(hItem)
	{
		m_WndMenu.SetHoverItem(hItem);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RETURN;
		m_WndMenu.OnKeyEvent(&Msg);
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_DOWN;
		m_WndMenu.OnKeyEvent(&Msg);
	}
	return true;
}


bool CSystemExplorer::OnHotKeyEventCodeView(IN WISP_MSG*pMsg)
{
	CCodeView*pCodeView = (CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	if(pCodeView)
		pCodeView->Focus();
	return true;
}

bool CSystemExplorer::OnHotKeyEventDataView(IN WISP_MSG*pMsg)
{
	CDataView*pDataView = (CDataView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();
	if(pDataView)
		pDataView->Focus();
	return true;
}

bool CSystemExplorer::OnCommandMainSplit(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_LDBCLICK && pMsg->Command.Param1 == 0)
	{
		WISP_SPLIT_WND*pSplitWnd = (WISP_SPLIT_WND*)pMsg->Command.Param2; 
		if(pSplitWnd->SizeXorY<DEFAULT_MONITOR_VIEW_SIZE/2)
		{
			m_MainSplitWnd.ResizeWndSpace(0,DEFAULT_MONITOR_VIEW_SIZE);
			m_MainSplitWnd.AdjustWndPos();
		}
		else
		{
			m_MainSplitWnd.ResizeWndSpace(0,0);
			m_MainSplitWnd.AdjustWndPos();
		}
	}
	return true;
}

bool CSystemExplorer::OnCommandModuleWnd(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_LDBCLICK)
	{
		hItem=(HANDLE)pMsg->Command.Param2; 
		//gpSyser->m_MainFrame.m_ModuleList.
	}
	return true;
}
bool CSystemExplorer::OnCommandFunctionWnd(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	NUM_PTR ItemData;
	if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_LDBCLICK)
	{
		hItem=(HANDLE)pMsg->Command.Param2; 
		ItemData = m_FunctionWnd.GetItemData(hItem,1);
		gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.SetActiveAddress((DWORD)ItemData);
	}
	return true;
}
bool CSystemExplorer::OnCommandMonitorSplit(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_LDBCLICK && pMsg->Command.Param1 == 0)
	{
		WISP_SPLIT_WND*pSplitWnd = (WISP_SPLIT_WND*)pMsg->Command.Param2; 
		if(pSplitWnd->SizeXorY<100)
		{
			m_MonitorSplitWnd.ResizeWndSpace(0,300);
			m_MonitorSplitWnd.AdjustWndPos();
		}
		else
		{
			m_MonitorSplitWnd.ResizeWndSpace(0,0);
			m_MonitorSplitWnd.AdjustWndPos();
		}
	}
	else
	{
		if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_RDBCLICK && pMsg->Command.Param1 == 0)
		{
			WISP_SPLIT_WND*pSplitWnd = (WISP_SPLIT_WND*)pMsg->Command.Param2; 
			if(pSplitWnd->SizeXorY>300)
			{
				m_MonitorSplitWnd.ResizeWndSpace(0,300);
				m_MonitorSplitWnd.AdjustWndPos();
			}
			else
			{
				m_MonitorSplitWnd.ResizeWndSpace(0,m_MonitorSplitWnd.m_ClientRect.cy-5);
				m_MonitorSplitWnd.AdjustWndPos();
			}
		}
	}
	return true;
}

bool CSystemExplorer::OnCommandViewSplit(IN WISP_MSG*pMsg)
{
	WISP_SPLIT_WND*pSplitWnd = (WISP_SPLIT_WND*)pMsg->Command.Param2; 
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_ITEM_LDBCLICK:
		if(pMsg->Command.Param1 == 0)
		{
			if(pSplitWnd->SizeXorY>=m_ClientRect.cy*2/10)
			{
				m_ViewSplitWnd.ResizeWndSpace(0,m_ClientRect.cy*2/10);
				m_ViewSplitWnd.AdjustWndPos();
			}
			else
			{

			}
		}
		else if(pMsg->Command.Param1 == 1)
		{
		}
		break;
	case WISP_CMD_ITEM_RDBCLICK:
		break;
	}
	return true;
}

bool CSystemExplorer::OnSize(IN WISP_MSG*pMsg)
{
	m_Toolbar.Resize(pMsg->Resize.NewSize.cx,m_Toolbar.m_WindowRect.cy);
	m_MainSplitWnd.Resize(m_ClientRect.cx,m_ClientRect.cy-m_Toolbar.m_WindowRect.cy-m_WndMenu.m_WindowRect.cy);
	AdjustSplitViewSize();
	return true;
}

void CSystemExplorer::AdjustSplitViewSize()
{
	m_ViewSplitWnd.ResizeWndSpace(0,m_ClientRect.cy*3/20);
	m_ViewSplitWnd.ResizeWndSpace(1,m_ClientRect.cy*12/20);
	m_ViewSplitWnd.ResizeWndSpace(2,m_ClientRect.cy*5/20);
	m_ViewSplitWnd.AdjustWndPos();
}

bool CSystemExplorer::OnGetFocus(IN WISP_MSG*pMsg)
{
	m_TerminalWnd.Focus();
	return false;
}

bool CSystemExplorer::AttachDebugger(CX86Debugger*pDebugger)
{
	return true;
}

void CSystemExplorer::DetachDebugger()
{
	if(gpSyser->m_bActive)
	{
		m_MultiCodeView.RemoveAllWnd();
		m_MultiCodeView.InsertView(NULL);
		m_MultiDataView.RemoveAllWnd();
		m_MultiDataView.InsertView(NULL);
	}
}

void CSystemExplorer::LocalEIP(VADDR32 Address)
{
	DWORD Start,End;
	WISP_CHAR WndTitle[64];
	int CurrentIndex;
	if(gpSyser->m_pDebugger->m_CodeMode!=gpSyser->m_SyserUI.m_CodeDoc.m_Mode)
		gpSyser->m_SyserUI.SetInstrMode(gpSyser->m_pDebugger->m_CodeMode);
	CCodeView*pCodeWnd=(CCodeView*)m_MultiCodeView.GetActiveWnd();
	if(pCodeWnd)
	{
		pCodeWnd->GetCodeRange(&Start,&End);
		TSPrintf(WndTitle,WSTR("%08X"),Address);
		CurrentIndex=m_MultiCodeView.GetActiveWndIndex();
		m_MultiCodeView.SetTabText(CurrentIndex,WndTitle);
		if(Address < Start || Address >= End)
		{
			pCodeWnd->SetStartAddress(Address);
		}
		else
		{
			if(gpSyser->m_SyserUI.m_CodeDoc.IsExecutePointVisible(Start,End-Start)==false)
				pCodeWnd->SetStartAddress(*X86_REG_PTR.pEIP);
		}
	}
}

void CSystemExplorer::CenterViewCodeAddress(VADDR32 Address)
{
	m_pCurCodeView->CenterVisibleAddress(Address);
}

void CSystemExplorer::ViewCodeAddress(VADDR32 Address,bool bRecord)
{
	m_pCurCodeView->SetStartAddress(Address,bRecord);
}

void CSystemExplorer::ViewDataAddress(VADDR32 Address,int SelLen)
{
	CWispHexWnd*pDataWnd=(CWispHexWnd*)m_MultiDataView.GetActiveWnd();
	if(pDataWnd)
	{
		if(SelLen>0)
		{
			pDataWnd->m_bSelect=true;
			pDataWnd->m_SelStart = Address;
			pDataWnd->m_SelEnd = Address+SelLen-1;
		}
		else
		{
			pDataWnd->m_bSelect=false;
		}
		pDataWnd->ViewAddress(Address);
	}
}

void CSystemExplorer::UpdateContext()
{	
	WCHAR szBuffer[MAX_LONG_NAME_LEN];
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return;
	DWORD dwCurrentCpuID=0,i;
#ifdef CODE_OS_NT_DRV	
	dwCurrentCpuID = GetCurrentCPULocalAPICID();
#endif
	CWispBaseWnd* pFocusWnd = m_pWispBase->m_pFocusWnd;
	
	m_MultiCPUTabWnd.SetActiveWnd(dwCurrentCpuID);
	TSPrintf(szBuffer,WSTR("PID:%x TID:%x "),gpSyser->m_PopupProcessID, gpSyser->m_PopupThreadID);
	m_ContextStr.SetWindowText(szBuffer);
	for(i=0;i<gCPUNumbers;i++)
	{						
		m_pWndGeneReg[i].UpdateContext();
		m_pWndFpuReg[i].UpdateContext();
		m_pWndESSReg[i].UpdateContext();		
		if(gCPUNumbers >1 && (m_pWndGeneReg[i].GetCPUIndex()==dwCurrentCpuID))
		{
			TSPrintf(szBuffer,WSTR("*CPU %d "),i);			
		}
		else
		{
			TSPrintf(szBuffer,WSTR(" CPU %d "),i);			
		}
		m_MultiCPUTabWnd.SetTabText(i,szBuffer);

		if(gpSyser->m_MainFrame.m_pRegWnd)
		{
			if(gpSyser->m_MainFrame.m_pRegWnd[i].IsWindow())
			{
				gpSyser->m_MainFrame.m_pRegWnd[i].UpdateContext();
				if(i==dwCurrentCpuID)
					gpSyser->m_MainFrame.m_MultiCPURegView.SetActiveWnd(dwCurrentCpuID);
				gpSyser->m_MainFrame.m_MultiCPURegView.SetTabText(i,szBuffer);
			}
		}		
	}
	
	m_WatchList.UpdateContext();
	m_StackWatchList.UpdateContext(*X86_REG_PTR.pESP);
	m_MultiCodeView.UpdateAllView();
	m_MultiDataView.UpdateAllView();
	gpSyser->m_SyserUI.m_CodeDoc.GetCurInstrInfo(szBuffer);
	m_pInfoMsgWnd->SetWindowText(szBuffer);
	
	gpSyser->m_MainFrame.m_DataViewForm.UpdateContext();
	gpSyser->m_MainFrame.m_RunTraceWnd.UpdateContext();
	pFocusWnd->Focus();
	Update();
}

void CSystemExplorer::UpdateMemoryView()
{
	WCHAR szBuffer[MAX_LONG_NAME_LEN];
	if(gpSyser->m_MainFrame.m_ConsoleWnd.m_IsInBatProcess || gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return;
	gpSyser->m_MainFrame.m_DataViewForm.UpdateContext();
	m_WatchList.UpdateContext();
	m_StackWatchList.UpdateContext(*X86_REG_PTR.pESP);
	m_MultiCodeView.UpdateAllView();
	m_MultiDataView.UpdateAllView();
	gpSyser->m_SyserUI.m_CodeDoc.GetCurInstrInfo(szBuffer);
	m_pInfoMsgWnd->SetWindowText(szBuffer);
	Update();
}
void CSystemExplorer::SaveMemoryContext()
{
	m_MultiDataView.SaveContextAllView();
}
void CSystemExplorer::ResetContext()
{
	for(DWORD i=0;i<gCPUNumbers;i++)
	{
		m_pWndGeneReg[i].ResetContext();
		m_pWndFpuReg[i].ResetContext();
		m_pWndESSReg[i].ResetContext();
	}
	
	m_StackWatchList.ResetContext();
	m_WatchList.ResetContext();
	m_MultiCodeView.ResetContext();
	m_MultiDataView.ResetContext();
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SourceVariableWatchWnd.ResetContext();
}

bool CSystemExplorer::OnGetNextTrace(IN WISP_MSG*pMsg)
{
	PSTRUNTRACE pRunTrace;
	pRunTrace = SYSTEM_EXPLORER.GetNextTrace();
	if(pRunTrace==NULL)
		return false;
	CCodeView*pCodeView = (CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	if(pCodeView)
	{
		pCodeView->SetStartAddress(pRunTrace->CodeViewStartAddress);
		pCodeView->SetSelectItemByAddress(pRunTrace->CodeViewStartAddress+pRunTrace->EIPOffset);
	}
	return true;
}

bool CSystemExplorer::OnGetPrevTrace(IN WISP_MSG*pMsg)
{
	PSTRUNTRACE pRunTrace;
	pRunTrace = SYSTEM_EXPLORER.GetPrevTrace();
	if(pRunTrace==NULL)
		return true;
	CCodeView*pCodeView = (CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	if(pCodeView)
	{
		pCodeView->SetStartAddress(pRunTrace->CodeViewStartAddress);
		pCodeView->SetSelectItemByAddress(pRunTrace->CodeViewStartAddress+pRunTrace->EIPOffset);
	}
	return true;
}