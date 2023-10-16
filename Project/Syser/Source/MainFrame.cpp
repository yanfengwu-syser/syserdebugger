#include "StdAfx.h"
#include "Syser.h"
#include "SystemIoctl.h"
#ifdef CODE_OS_WIN
#include "SyserApp.h"
#endif
extern DWORD dwgErrorCode;
#define MAX_TIP_WIDTH			400

WISP_MSG_MAP_BEGIN(CMainFrame)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(EVENT_ID_DEBUG_PLUNGE,OnDebugPlunge)
	WISP_MSG_MAP(EVENT_ID_DEBUG_TERMINATE,OnDebugTerminate)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_BEGIN_MOVE,OnBeginMove)
	WISP_MSG_MAP(WISP_WM_END_MOVE,OnEndMove)
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_EVENT_MAP_BEGIN(CMainFrame)
	WISP_MSG_EVENT_MAP(EVENT_ID_REG_VIEW,OnEventRegView)
	WISP_MSG_EVENT_MAP(EVENT_ID_DATA_VIEW_FORM,OnEventDataViewForm)
	WISP_MSG_EVENT_MAP(EVENT_ID_CALL_STACK,OnEventCallStack)
	WISP_MSG_EVENT_MAP(EVENT_ID_BREAK_POINT,OnEventBreakPoint)
	WISP_MSG_EVENT_MAP(EVENT_ID_CONTINUE,OnEventContinue)
	WISP_MSG_EVENT_MAP(EVENT_ID_RETURN,OnEventReturn)
	WISP_MSG_EVENT_MAP(EVENT_ID_STEP,OnEventStep)
	WISP_MSG_EVENT_MAP(EVENT_ID_PROCEED,OnEventProceed)
	WISP_MSG_EVENT_MAP(EVENT_ID_STEP_BRANCH,OnEventStepBranch)
WISP_MSG_EVENT_MAP_DEFAULT_END(OnMenuEventPluginItem)

CMainFrame::CMainFrame()
{
	m_pRegWnd=NULL;
}

CMainFrame::~CMainFrame()
{
	if(m_pRegWnd)
		delete []m_pRegWnd;
}

bool CMainFrame::OnMenuEventPluginItem(IN WISP_MSG*pMsg)
{
	return true;
}

bool CMainFrame::OnDebugPlunge(IN WISP_MSG*pMsg)
{
	gpSyser->m_SyserUI.m_SyserDI.OnDebugPlunge(pMsg->Command.Param1);
	return true;
}

bool CMainFrame::OnDebugTerminate(IN WISP_MSG*pMsg)
{
	gpSyser->m_SyserUI.m_SyserDI.OnDebugTerminate(pMsg->Command.Param1!=0);
	return true;
}

bool CMainFrame::OnCreate(IN WISP_MSG*pMsg)
{
	dwgErrorCode=903;
	AttachTitleDIB(WispTKDIB("\\SyserIcon\\Syser.ico",0));
	if(m_MainTabWnd.Create(NULL,CWispRect(0,0,m_ClientRect.cx,m_ClientRect.cy),this,0,WISP_TWS_BUTTOM)==false)
		return false;
	if(m_SystemExplorer.Create(NULL,CWispRect(0,0,0,0),&m_MainTabWnd,CMD_ID_SYSTEM_EXPLORER,WISP_WS_VIRTUAL)==false)
		return false;
	if(m_ConsoleWnd.Create(NULL,CWispRect(0,0,0,0),&m_MainTabWnd,CMD_ID_CONSOLE,WISP_WS_NULL)==false)
		return false;
	dwgErrorCode=905;
	m_SourceDebugFrameWnd.Create(NULL,&m_MainTabWnd.m_ClientRect,&m_MainTabWnd,0,WISP_WS_NULL|WISP_SWS_HORZ|WISP_WS_VIRTUAL);
	m_ConsoleWnd.Printf(WISP_STR("Wisp Syser Console\n"));
	m_MainTabWnd.InsertWnd(WISP_STR("System Explorer Ctrl+1"),&m_SystemExplorer,WispTKDIBListDIB("\\Toolbar.bmp",16,16,62));
	m_MainTabWnd.InsertWnd(WISP_STR("Command Console Ctrl+2"),&m_ConsoleWnd,WispTKDIBListDIB("\\Toolbar.bmp",16,16,63));
	m_MainTabWnd.InsertWnd(WISP_STR("Source Explorer Ctrl+3"),&m_SourceDebugFrameWnd,WispTKDIBListDIB("\\Toolbar.bmp",16,16,15*16+6));
#ifdef CODE_OS_NT_DRV
	m_CloseBT.Create(NULL,m_ClientRect.cx-18,2,16,16,NULL,WISP_ID_CLOSE,WISP_BS_NORMAL);
	m_CloseBT.SetDIBList(WispDIBList("\\Skin\\Default\\Close.bmp",16,16));
	m_CloseBT.SetOwner(this);
#endif
	m_TipStr.Create(NULL,m_ClientRect.cx-MAX_TIP_WIDTH,m_ClientRect.cy-16,MAX_TIP_WIDTH,16,&m_MainTabWnd,0,WISP_WS_NULL);
#ifdef CODE_OS_NT_DRV
	gpSyser->m_SysInfo.UpdateHostSN();
#endif
	HookKeyEvent();
	gpSyser->AttachHotKey(EVENT_ID_REG_VIEW,this);
	gpSyser->AttachHotKey(EVENT_ID_DATA_VIEW_FORM,this);
	gpSyser->AttachHotKey(EVENT_ID_CALL_STACK,this);
	gpSyser->AttachHotKey(EVENT_ID_BREAK_POINT,this);
	gpSyser->AttachHotKey(EVENT_ID_CONTINUE,this);
	gpSyser->AttachHotKey(EVENT_ID_RETURN,this);
	gpSyser->AttachHotKey(EVENT_ID_STEP,this);
	gpSyser->AttachHotKey(EVENT_ID_PROCEED,this);
	gpSyser->AttachHotKey(EVENT_ID_STEP_BRANCH,this);
	return true;
}

bool CMainFrame::OnClose(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_NT_DRV
	gpSyser->Exit();
	return false;
#else
	return true;
#endif
}

bool CMainFrame::OnDestroy(IN WISP_MSG*pMsg)
{
	DetachTitleDIB();
	return true;
}

bool CMainFrame::OnSize(IN WISP_MSG*pMsg)
{
	int TipSize = m_ClientRect.cx - m_MainTabWnd.m_TabItemWidth;
	MAX_LIMIT(TipSize,MAX_TIP_WIDTH);
	MIN_LIMIT(TipSize,0);
	m_TipStr.MoveToClient(m_ClientRect.cx-TipSize,m_ClientRect.cy-16);
	m_TipStr.Resize(TipSize,m_TipStr.m_WindowRect.cy);
	m_MainTabWnd.Resize(m_ClientRect.cx,m_ClientRect.cy);
#ifdef CODE_OS_NT_DRV
	m_CloseBT.MoveToClient(m_ClientRect.cx-18,2);
#endif
	return true;
}

bool CMainFrame::OnBeginMove(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_NT_DRV
	gpSyser->LockUpdate();
	gpSyser->m_RootPosBackup = gpSyser->m_RootPos;
	gpSyser->m_bMovingFrame = true;
#endif
	return true;
}

bool CMainFrame::OnEndMove(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_NT_DRV
	gpSyser->RestoreMovingFrame();
	WISP_POINT NewPos;
	gpSyser->UnlockUpdate();
	NewPos = gpSyser->m_RootPos;
	gpSyser->m_RootPos = gpSyser->m_RootPosBackup;
	gpSyser->RestoreScreen();
	gpSyser->m_RootPos = NewPos;
	gpSyser->BackupScreen();
	Update();
	gpSyser->UpdateFrameBuffer();
	gpSyser->m_bMovingFrame = false;
#endif
	return true;
}

void CMainFrame::ProcessMoveFrame()
{
	int xDelta,yDelta;
	xDelta=0;yDelta=0;
	if(gpCurWisp->m_KeyMap[WISP_VK_LEFT])
		xDelta-=20;
	if(gpCurWisp->m_KeyMap[WISP_VK_RIGHT])
		xDelta+=20;
	if(gpCurWisp->m_KeyMap[WISP_VK_UP])
		yDelta-=20;
	if(gpCurWisp->m_KeyMap[WISP_VK_DOWN])
		yDelta+=20;
	gpSyser->MoveFrame(xDelta,yDelta);
}

bool CMainFrame::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(m_pWispBase->m_pModalWnd)
		return true;
	if(pMsg->KeyEvent.bKeyDown)
	{
		switch(pMsg->KeyEvent.KeyType)
		{
#ifdef CODE_OS_NT_DRV
		case WISP_MOD_CTRL|WISP_MOD_ALT|WISP_VK_CONTROL:
		case WISP_MOD_CTRL|WISP_MOD_ALT|WISP_VK_ALT:
			if(gpSyser->m_bMovingFrame == false)
				OnBeginMove(NULL);
			break;
		case WISP_MOD_CTRL|WISP_MOD_ALT|WISP_VK_LEFT:
		case WISP_MOD_CTRL|WISP_MOD_ALT|WISP_VK_RIGHT:
		case WISP_MOD_CTRL|WISP_MOD_ALT|WISP_VK_UP:
		case WISP_MOD_CTRL|WISP_MOD_ALT|WISP_VK_DOWN:
			if(gpSyser->m_bMovingFrame)
			{
				ProcessMoveFrame();
				return false;
			}
			break;
#endif
		case WISP_VK_DELETE|WISP_MOD_ALT|WISP_MOD_CTRL:
			RUNCMD(WSTR("hboot"));
			return false;
			break;
		case WISP_VK_ESCAPE:
			if(m_pWispBase->m_pFocusWnd && m_pWispBase->m_pFocusWnd->m_CtrlType!=WISP_CTRL_EDIT)
				SetDefaultFocus();
			break;
		case WISP_VK_1|WISP_MOD_CTRL:
		case WISP_VK_2|WISP_MOD_CTRL:
		case WISP_VK_3|WISP_MOD_CTRL:
		case WISP_VK_4|WISP_MOD_CTRL:
		case WISP_VK_5|WISP_MOD_CTRL:
		case WISP_VK_6|WISP_MOD_CTRL:
		case WISP_VK_7|WISP_MOD_CTRL:
		case WISP_VK_8|WISP_MOD_CTRL:
		case WISP_VK_9|WISP_MOD_CTRL:
			m_MainTabWnd.SetActiveWnd(WISP_VK(pMsg->KeyEvent.KeyType) - WISP_VK_1);
			return false;
			break;
#ifdef CODE_OS_NT_DRV
		case WISP_VK_F4:
			if(gpSyser->m_bScrRestored)
			{
				gpSyser->m_pRootWnd->Update();
				UPDATE_CODE_VIEW();
				UPDATE_DATA_VIEW();
			}
			else
			{
				gpSyser->RestoreScreen();
			}
			break;
#endif
		}
	}
	else
	{
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_MOD_ALT|WISP_VK_CONTROL:
		case WISP_MOD_CTRL|WISP_VK_ALT:
#ifdef CODE_OS_NT_DRV
			if(gpSyser->m_bMovingFrame)
				OnEndMove(NULL);
#endif
			break;
		}
	}
	return true;
}

bool CMainFrame::OnEventRegView(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventRegView(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventRegView(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventDataViewForm(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventDataViewForm(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventDataViewForm(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventCallStack(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventCallStack(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventCallStack(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventBreakPoint(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventBreakPoint(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventBreakPoint(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventContinue(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventContinue(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventContinue(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventReturn(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventReturn(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventReturn(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventStep(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventStep(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventStep(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventProceed(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventProceed(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		m_SourceDebugFrameWnd.OnEventProceed(pMsg);
		break;
	}
	return true;
}

bool CMainFrame::OnEventStepBranch(IN WISP_MSG*pMsg)
{
	UINT Index = m_MainTabWnd.GetActiveWndIndex();
	switch(Index)
	{
	case SYSTEM_EXPLORER_VIEW:
	case CONSOLE_VIEW:
		m_SystemExplorer.OnEventStepBranch(pMsg);
		break;
	case SOURCE_EXPLORER_VIEW:
		break;
	}
	return true;
}

void CMainFrame::SetDefaultFocus()
{
	switch(gpSyser->m_MainFrame.m_MainTabWnd.GetActiveWndIndex())
	{
	case SYSTEM_EXPLORER_VIEW:
		gpSyser->m_MainFrame.m_SystemExplorer.m_TerminalWnd.Focus();
		break;
	case CONSOLE_VIEW:
		gpSyser->m_MainFrame.m_ConsoleWnd.Focus();
		break;
	case SOURCE_EXPLORER_VIEW:
		{
			CSourceCodeWnd*pSourceCodeWnd = (CSourceCodeWnd*) gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_MultiSourceCodeView.GetActiveWnd();
			if(pSourceCodeWnd)
				pSourceCodeWnd->Focus();
			else
				gpSyser->m_MainFrame.m_SourceDebugFrameWnd.Focus();
		}
		break;
	}
}

