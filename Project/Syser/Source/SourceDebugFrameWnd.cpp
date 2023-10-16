#include "StdAfx.h"
#include "Syser.h"
#include "SourceDebugFrameWnd.h"


WISP_TOOLBAR_RES_ITEM SourceDebugToolbar[]=
{
	{EVENT_ID_STEP,			0,			WISP_TBIS_BUTTON,WSTR("Step"),						0,WISP_WS_DISABLED},
	{EVENT_ID_PROCEED,		1,			WISP_TBIS_BUTTON,WSTR("Proceed"),					0,WISP_WS_DISABLED},
	{EVENT_ID_RETURN,		2,			WISP_TBIS_BUTTON,WSTR("Return"),					0,WISP_WS_DISABLED},
	{EVENT_ID_CONTINUE,		3,			WISP_TBIS_BUTTON,WSTR("Continue"),					0,WISP_WS_DISABLED},
	WISP_TOOLBAR_RES_SEPARATOR,
	{EVENT_ID_BREAK_POINT,	4,			WISP_TBIS_BUTTON,WSTR("Break point")},
	{EVENT_ID_GOTOLINE,		16*16+11,	WISP_TBIS_BUTTON,WSTR("Go To Line Ctrl+G"),			0,WISP_WS_DISABLED},
	WISP_TOOLBAR_RES_SEPARATOR,
	{EVENT_ID_BOOKMARK_TOGGLE,	13*16,	WISP_TBIS_BUTTON,WSTR("Toggle BookMark Ctrl+K"),	0,WISP_WS_DISABLED},
	{EVENT_ID_BOOKMARK_NEXT,	13*16+1,WISP_TBIS_BUTTON,WSTR("Next BookMark Ctrl+N"),		0,WISP_WS_DISABLED},
	{EVENT_ID_BOOKMARK_PREV,	13*16+2,WISP_TBIS_BUTTON,WSTR("Previous BookMark Ctrl+P"),	0,WISP_WS_DISABLED},
	{EVENT_ID_BOOKMARK_CLEAR,	13*16+3,WISP_TBIS_BUTTON,WSTR("Clear BookMark Ctrl+L"),		0,WISP_WS_DISABLED},
	WISP_TOOLBAR_RES_END
};

WISP_MENU_RES_ITEM SourceDebugMenu[]=
{
	{WSTR("Continue      F5"),		EVENT_ID_CONTINUE,3,WISP_MIS_DISABLED},
	{WSTR("Return        F6"),		EVENT_ID_RETURN,2,WISP_MIS_DISABLED},
	{WSTR("Step          F8"),		EVENT_ID_STEP,0,WISP_MIS_DISABLED},
	{WSTR("Proceed       F10"),		EVENT_ID_PROCEED,1,WISP_MIS_DISABLED},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Break point   Ctrl+F9"),	EVENT_ID_BREAK_POINT,4},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM SourceDebugMonitorMenu[]=
{
	{WSTR("Register View                 Alt+G"),		EVENT_ID_REG_VIEW,		52},
	{WSTR("Data View                     Alt+D"),		EVENT_ID_DATA_VIEW_FORM,89},
	{WSTR("Call Stack                    Alt+C"),		EVENT_ID_CALL_STACK,	18},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM SourceDebugViewMenu[]=
{
	{WSTR("Toggle   BookMark    Ctrl+K"),EVENT_ID_BOOKMARK_TOGGLE,13*16,WISP_MIS_DISABLED},
	{WSTR("Next     BookMark    Ctrl+N"),EVENT_ID_BOOKMARK_NEXT,13*16+1,WISP_MIS_DISABLED},
	{WSTR("Previous BookMark    Ctrl+P"),EVENT_ID_BOOKMARK_PREV,13*16+2,WISP_MIS_DISABLED},
	{WSTR("Clear    BookMark    Ctrl+L"),EVENT_ID_BOOKMARK_CLEAR,13*16+3,WISP_MIS_DISABLED},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Go To Line           Ctrl+G"),EVENT_ID_GOTOLINE,16*16+11,WISP_MIS_DISABLED},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM SourceMenu[]=
{
	{WSTR("Debug"),0,57,WISP_MIS_POPUP,SourceDebugMenu},
	{WSTR("Monitor"),0,53,WISP_MIS_POPUP,SourceDebugMonitorMenu},
	{WSTR("View"),0,126,WISP_MIS_POPUP,SourceDebugViewMenu},
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CSourceDebugFrameWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispSplitWnd)

WISP_MSG_CMD_MAP_BEGIN(CSourceDebugFrameWnd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CSourceDebugFrameWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_REG_VIEW,OnEventRegView)
	WISP_MSG_EVENT_MAP(EVENT_ID_DATA_VIEW_FORM,OnEventDataViewForm)
	WISP_MSG_EVENT_MAP(EVENT_ID_CALL_STACK,OnEventCallStack)
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTOLINE,OnEventGoToLine)
	WISP_MSG_EVENT_MAP(EVENT_ID_STEP,OnEventStep)
	WISP_MSG_EVENT_MAP(EVENT_ID_PROCEED,OnEventProceed)
	WISP_MSG_EVENT_MAP(EVENT_ID_RETURN,OnEventReturn)
	WISP_MSG_EVENT_MAP(EVENT_ID_CONTINUE,OnEventContinue)
	WISP_MSG_EVENT_MAP(EVENT_ID_BREAK_POINT,OnEventBreakPoint)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_TOGGLE,OnEventToggleBookMark)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_NEXT,OnEventNextBookMark)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_PREV,OnEventPrevBookMark)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_CLEAR,OnEventClearBookMark)
	WISP_MSG_EVENT_MAP(EVENT_ID_SDS_MODULE_LIST,OnHotKeyEventSDSModule)
	WISP_MSG_EVENT_MAP(EVENT_ID_WATCH_LIST,OnHotKeyEventWatchList)
	WISP_MSG_EVENT_MAP(EVENT_ID_CONSOLE_VIEW,OnHotKeyEventConsole)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_DEBUG,			OnHotKeyEventMenuDebug)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_VIEW,			OnHotKeyEventMenuView)
	WISP_MSG_EVENT_MAP(EVENT_ID_MENU_MONITOR,		OnHotKeyEventMenuMonitor)
WISP_MSG_EVENT_MAP_END

CSourceDebugFrameWnd::CSourceDebugFrameWnd(void)
{
}

CSourceDebugFrameWnd::~CSourceDebugFrameWnd(void)
{
}

bool CSourceDebugFrameWnd::OnCreate(IN WISP_MSG* pMsg)
{
	m_IconDIBList.Load("\\SyserIcon\\SourceCodeIcon.bmp",16,16,80);

	m_WndMenu.CreateWndMenu(this,WISP_ID_MAIN_MENU,SourceMenu,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_WndMenu.SetOwner(this);
	m_Toolbar.CreateEx(this,m_WndMenu.m_WindowRect.cy,-1,WISP_ID_MAIN_TOOLBAR,WISP_WS_NULL);
	m_Toolbar.LoadToolbar(WispTKDIBList("\\Toolbar.bmp",16,16),SourceDebugToolbar);
	m_Toolbar.SetOwner(this);
	int MenuToolbarHeight = m_Toolbar.m_WindowRect.cy+m_WndMenu.m_WindowRect.cy;
	if(m_VertSplitWnd.Create(NULL,0,MenuToolbarHeight,m_ClientRect.cx,m_ClientRect.cy-MenuToolbarHeight,this,CMD_ID_SOURCE_VERT_SPLIT,WISP_SWS_VERT)==false)
		return false;
	if(m_HorzSplitWnd.Create(NULL,0,0,0,0,&m_VertSplitWnd,CMD_ID_SOURCE_HORZ_SPLIT,WISP_SWS_HORZ)==false)
		return false;
	m_ExplorerTabWnd.Create(NULL,0,0,0,0,&m_HorzSplitWnd,0,WISP_TWS_BUTTOM);
	m_MultiSourceCodeView.Create(NULL,0,0,0,0,&m_HorzSplitWnd,WND_CHILD_SOURCEFILETABWND,WISP_TWS_CLOSE_BT);
	m_SDSModuleList.Create(NULL,0,0,0,0,&m_ExplorerTabWnd,WND_CHILD_SDS_MODULE_LIST,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT);
	m_ExplorerTabWnd.InsertWnd(WSTR("SDS Modules ALT+S"),&m_SDSModuleList,WispTKDIBListDIB("\\Toolbar.bmp",16,16,13*16+5));
	
	m_HorzSplitWnd.InsertWnd(&m_MultiSourceCodeView,0,m_ClientRect.cx/3*2);
	m_HorzSplitWnd.InsertWnd(&m_ExplorerTabWnd,0,m_ClientRect.cx/3*1);
	m_HorzSplitWnd.AdjustWndPos();

	m_MonitorTabWnd.Create(NULL,0,0,0,0,&m_VertSplitWnd,0,WISP_TWS_TOP);
	m_SourceVariableWatchWnd.Create(NULL,0,0,0,0,&m_MonitorTabWnd,WND_CHILD_SOURCE_CODE_WATCH_LIST,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT);
	if(m_TerminalWnd.Create(NULL,CWispRect(0,0,0,0),&m_MonitorTabWnd,CMD_ID_TERMINAL_WND,WISP_WS_NULL)==false)
		return false;
	m_TerminalWnd.AttachConsole(&gpSyser->m_MainFrame.m_ConsoleWnd);
	m_MonitorTabWnd.InsertWnd(WSTR("Watch ALT+W"),&m_SourceVariableWatchWnd,WispTKDIBListDIB("\\Toolbar.bmp",16,16,53));
	m_MonitorTabWnd.InsertWnd(WSTR("Console F1"),&m_TerminalWnd,WispTKDIBListDIB("\\Toolbar.bmp",16,16,63));

	m_VertSplitWnd.InsertWnd(&m_HorzSplitWnd,0,m_ClientRect.cy-200);
	m_VertSplitWnd.InsertWnd(&m_MonitorTabWnd,0,200);
	m_VertSplitWnd.AdjustWndPos();

	gpSyser->AttachHotKey(EVENT_ID_CONTINUE,this);
	gpSyser->AttachHotKey(EVENT_ID_STEP,this);
	gpSyser->AttachHotKey(EVENT_ID_PROCEED,this);
	gpSyser->AttachHotKey(EVENT_ID_STEP_BRANCH,this);
	gpSyser->AttachHotKey(EVENT_ID_RETURN,this);
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_TOGGLE,this);
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_NEXT,this);
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_PREV,this);
	gpSyser->AttachHotKey(EVENT_ID_BOOKMARK_CLEAR,this);

	RegisterHotKey(EVENT_ID_SDS_MODULE_LIST,WISP_VK_S,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_WATCH_LIST,WISP_VK_W,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_CONSOLE_VIEW,WISP_VK_F1,0);
	RegisterHotKey(EVENT_ID_GOTOLINE,WISP_VK_G,WISP_MOD_CTRL);

	RegisterHotKey(EVENT_ID_MENU_DEBUG,WISP_VK_D,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_MONITOR,WISP_VK_M,WISP_MOD_ALT);
	RegisterHotKey(EVENT_ID_MENU_VIEW,WISP_VK_V,WISP_MOD_ALT);
	return true;
}

bool CSourceDebugFrameWnd::OnHotKeyEventMenuDebug(IN WISP_MSG*pMsg)
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
bool CSourceDebugFrameWnd::OnHotKeyEventMenuView(IN WISP_MSG*pMsg)
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
bool CSourceDebugFrameWnd::OnHotKeyEventMenuMonitor(IN WISP_MSG*pMsg)
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

bool CSourceDebugFrameWnd::OnHotKeyEventSDSModule(IN WISP_MSG* pMsg)
{
	m_SDSModuleList.Focus();
	return true;
}

bool CSourceDebugFrameWnd::OnHotKeyEventWatchList(IN WISP_MSG* pMsg)
{
	m_MonitorTabWnd.SetActiveWnd(0);
	m_SourceVariableWatchWnd.Focus();
	return true;
}

bool CSourceDebugFrameWnd::OnHotKeyEventConsole(IN WISP_MSG* pMsg)
{
	m_MonitorTabWnd.SetActiveWnd(1);	
	m_TerminalWnd.Focus();
	return true;
}

bool CSourceDebugFrameWnd::OnEventDataViewForm(IN WISP_MSG* pMsg)
{	
	gpSyser->m_MainFrame.m_SystemExplorer.OnEventDataViewForm(pMsg);
	return true;
}

bool CSourceDebugFrameWnd::OnEventRegView(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.m_SystemExplorer.OnEventRegView(pMsg);
	return true;
}

bool CSourceDebugFrameWnd::OnDestroy(IN WISP_MSG* pMsg)
{
	m_IconDIBList.Destroy();
	return true;
}

bool CSourceDebugFrameWnd::OnSize(IN WISP_MSG*pMsg)
{
	m_Toolbar.Resize(pMsg->Resize.NewSize.cx,m_Toolbar.m_WindowRect.cy);
	m_VertSplitWnd.Resize(m_ClientRect.cx,m_ClientRect.cy-m_Toolbar.m_WindowRect.cy-m_WndMenu.m_WindowRect.cy);
	AdjustSplitViewSize();
	return true;
}


void CSourceDebugFrameWnd::AdjustSplitViewSize()
{
	m_VertSplitWnd.ResizeWndSpace(0,m_ClientRect.cy*7/10);
	m_VertSplitWnd.AdjustWndPos();
	m_HorzSplitWnd.ResizeWndSpace(0,m_ClientRect.cx*7/10);
	m_HorzSplitWnd.AdjustWndPos();
}


bool CSourceDebugFrameWnd::OnGetFocus(IN WISP_MSG*pMsg)
{
	CWispWnd*pActiveWnd = m_MultiSourceCodeView.GetActiveWnd();
	if(pActiveWnd)
	{
		pActiveWnd->Focus();
		return false;
	}
	return true;	
}

void CSourceDebugFrameWnd::UpdateAllView(bool bShowEIPDoc)
{
	if(bShowEIPDoc)
	{
		CSDSModule*pSDSModule = gpSyser->m_SyserUI.GetSDSModule(*X86_REG_PTR.pEIP);
		if(pSDSModule)
		{
			m_SDSModuleList.SetActiveModule(pSDSModule);
			SDLINELIST LineList;
			if(pSDSModule->GetLineFromRva(*X86_REG_PTR.pEIP-pSDSModule->m_pCurDbgModule->m_ModuleBase,&LineList))
				ShowSourceFile(pSDSModule,(*LineList[0])->FileID,(*LineList[0])->LineNumber);
		}
	}
	m_MultiSourceCodeView.UpdateAllView();
	m_SourceVariableWatchWnd.UpdateContext();
}

bool CSourceDebugFrameWnd::OnEventBreakPoint(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_BreakPointForm.Popup();
	if(pMsg->Command.CmdMsg == WISP_CMD_HOTKEY)
		return false;
	return true;
}

bool CSourceDebugFrameWnd::OnEventCallStack(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_CallStackWnd.Popup();
	return true;
}

bool CSourceDebugFrameWnd::OnEventGoToLine(IN WISP_MSG* pMsg)
{
	CSourceCodeWnd*pSourceCodeWnd = (CSourceCodeWnd*)m_MultiSourceCodeView.GetActiveWnd();
	if(pSourceCodeWnd)
	{
		return pSourceCodeWnd->OnEventGoToLine(pMsg);
	}
	return true;
}

bool CSourceDebugFrameWnd::OnEventStep(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("st"));
	return false;
}

bool CSourceDebugFrameWnd::OnEventProceed(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("sp"));
	return false;
}

bool CSourceDebugFrameWnd::OnEventReturn(IN WISP_MSG*pMsg)
{	
	RUNCMD(WSTR("p ret"));
	return false;
}

bool CSourceDebugFrameWnd::OnEventContinue(IN WISP_MSG*pMsg)
{
	RUNCMD(WSTR("x"));
	return false;
}

CSourceCodeWnd* CSourceDebugFrameWnd::ShowSourceFile(CSDSModule*pSDSModule,DWORD FileID,DWORD LineNum)
{
	WCHAR Name[MAX_FN_LEN];
	PSDSOURCEFILEID pSDSourceFileId;
	SOURCE_CODE_WND_ID SourceFileID;
	SourceFileID.FileID = FileID;
	SourceFileID.pSDSModule = pSDSModule;
	TSet<SOURCE_CODE_WND_ID>::IT Iter = m_MultiSourceCodeView.m_OpenedSourceCodeWnd.Find(SourceFileID);
	if(Iter.IsExist())
	{
		if(Iter->pSourceCodeWnd)
			m_MultiSourceCodeView.ChangeActiveWnd(Iter->pSourceCodeWnd);
		Iter->pSourceCodeWnd->SetBeginLine(LineNum);
		Iter->pSourceCodeWnd->LoadModuleImage();
		if(Iter->pSourceCodeWnd->UpdateView() && SyserOption.iFollowMode==SYSER_FM_AUTOMATIC)
			gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
	}
	else
	{
		pSDSourceFileId = pSDSModule->GetSourceFileByID(FileID);
		if(pSDSourceFileId->FileLen==0)
			return NULL;
		Iter = m_MultiSourceCodeView.m_OpenedSourceCodeWnd.Insert(SourceFileID);
		if(Iter.IsExist()==false)
			return NULL;
		Iter->pSourceCodeWnd = new CSourceCodeWnd;
		Iter->pSourceCodeWnd->m_pSDSModule = pSDSModule;
		Iter->pSourceCodeWnd->m_CurrentFileID = FileID;
		Iter->pSourceCodeWnd->Create(NULL,0,0,0,0,&m_MultiSourceCodeView,WISP_WM_USER_START+FileID,WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS);
		Iter->pSourceCodeWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
		TStrCpy(Name,TGetFileName(pSDSourceFileId->uName.Name));
		m_MultiSourceCodeView.InsertWnd(Name,Iter->pSourceCodeWnd);
		Iter->pSourceCodeWnd->LoadSourceFile(*(char**)&pSDSourceFileId->OffsetAtFile,pSDSourceFileId->FileLen,pSDSourceFileId);
		m_MultiSourceCodeView.ChangeActiveWnd(Iter->pSourceCodeWnd);
		Iter->pSourceCodeWnd->SetBeginLine(LineNum);
		if(Iter->pSourceCodeWnd->UpdateView() && SyserOption.iFollowMode==SYSER_FM_AUTOMATIC)
			gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
	}
	Update();
	return Iter->pSourceCodeWnd;
}

bool CSourceDebugFrameWnd::OnEventToggleBookMark(IN WISP_MSG*pMsg)
{
	CSourceCodeWnd*pSourceCodeWnd = (CSourceCodeWnd*) m_MultiSourceCodeView.GetActiveWnd();
	if(pSourceCodeWnd)
		pSourceCodeWnd->ToggleBookMark();
	return true;
}

bool CSourceDebugFrameWnd::OnEventNextBookMark(IN WISP_MSG*pMsg)
{
	CSourceCodeWnd*pSourceCodeWnd = (CSourceCodeWnd*) m_MultiSourceCodeView.GetActiveWnd();
	if(pSourceCodeWnd)
		pSourceCodeWnd->GotoNextBookMark();
	return true;
}

bool CSourceDebugFrameWnd::OnEventPrevBookMark(IN WISP_MSG*pMsg)
{
	CSourceCodeWnd*pSourceCodeWnd = (CSourceCodeWnd*) m_MultiSourceCodeView.GetActiveWnd();
	if(pSourceCodeWnd)
		pSourceCodeWnd->GotoPrevBookMark();
	return true;
}

bool CSourceDebugFrameWnd::OnEventClearBookMark(IN WISP_MSG*pMsg)
{
	CSourceCodeWnd*pSourceCodeWnd = (CSourceCodeWnd*) m_MultiSourceCodeView.GetActiveWnd();
	if(pSourceCodeWnd)
		pSourceCodeWnd->ClearAllBookMark();
	return true;
}

void CSourceDebugFrameWnd::UpdateItemState()
{
	CSourceCodeWnd*pSourceCodeWnd = (CSourceCodeWnd*)m_MultiSourceCodeView.GetActiveWnd();
	bool bState;
	bState = pSourceCodeWnd!=NULL;
	m_WndMenu.EnableItem(EVENT_ID_GOTOLINE,bState);
	m_Toolbar.EnableItem(EVENT_ID_GOTOLINE,bState);

	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_TOGGLE,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_TOGGLE,bState);

	bState = pSourceCodeWnd?pSourceCodeWnd->m_BookMark.Count()>0:false;
	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_NEXT,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_NEXT,bState);
	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_PREV,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_PREV,bState);
	m_WndMenu.EnableItem(EVENT_ID_BOOKMARK_CLEAR,bState);
	m_Toolbar.EnableItem(EVENT_ID_BOOKMARK_CLEAR,bState);

	bState = gpSyser->m_SyserUI.m_CodeDoc.IsOpened();
	m_WndMenu.EnableItem(EVENT_ID_STEP,bState);
	m_Toolbar.EnableItem(EVENT_ID_STEP,bState);
	m_WndMenu.EnableItem(EVENT_ID_PROCEED,bState);
	m_Toolbar.EnableItem(EVENT_ID_PROCEED,bState);
	m_WndMenu.EnableItem(EVENT_ID_RETURN,bState);
	m_Toolbar.EnableItem(EVENT_ID_RETURN,bState);
	m_WndMenu.EnableItem(EVENT_ID_CONTINUE,bState);
	m_Toolbar.EnableItem(EVENT_ID_CONTINUE,bState);

	m_Toolbar.Update();
}

void CSourceDebugFrameWnd::UnloadSDSModule(CSDSModule*pSDSModule)
{	
	if(pSDSModule==NULL)
		return;
	m_SourceVariableWatchWnd.UnloadSDSModule(pSDSModule);	
}