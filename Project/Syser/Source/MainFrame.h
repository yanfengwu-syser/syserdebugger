#ifndef _SYSER_ROOT_WND_H_
#define _SYSER_ROOT_WND_H_

#include "ConsoleWnd.h"
#include "SystemExplorer.h"
#include "SourceDebugFrameWnd.h"
#include "CallStackWnd.h"
#include "DataViewForm.h"
#include "PEExplorer.h"
#include "IBMAsciiWnd.h"
#include "KeyMappingPage.h"
#include "HwndWnd.h"
#include "WndStringReference.h"

class CMainFrame : public CWispWnd
{
public:
	CMainFrame();
	~CMainFrame();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnDebugPlunge)
	DECLARE_WISP_MSG(OnDebugTerminate)
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnClose)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnBeginMove)
	DECLARE_WISP_MSG(OnEndMove)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventRegView)
	DECLARE_WISP_MSG_EVENT(OnEventDataViewForm)
	DECLARE_WISP_MSG_EVENT(OnEventCallStack)
	DECLARE_WISP_MSG_EVENT(OnEventBreakPoint)
	DECLARE_WISP_MSG_EVENT(OnEventContinue)
	DECLARE_WISP_MSG_EVENT(OnEventReturn)
	DECLARE_WISP_MSG_EVENT(OnEventStep)
	DECLARE_WISP_MSG_EVENT(OnEventProceed)
	DECLARE_WISP_MSG_EVENT(OnEventStepBranch)
	DECLARE_WISP_MSG_EVENT(OnMenuEventPluginItem)
public:
	void	SetDefaultFocus();
	CWispButton				m_CloseBT;
	CWispTabWnd				m_MultiCPURegView;
	CGeneRegList*			m_pRegWnd;
	CDataViewForm			m_DataViewForm;
	CSystemExplorer			m_SystemExplorer;
	CConsoleWnd				m_ConsoleWnd;
	CSourceDebugFrameWnd	m_SourceDebugFrameWnd;
	CWispTabWnd				m_MainTabWnd;
	CWispProgressForm		m_ProgressForm;
	CDebuggerSelectForm		m_DebuggerSelectForm;
	CPluginListForm			m_PluginListForm;
	CKeyMappingPage			m_KeyMapForm;
	CWispSoftKeyboard		m_SoftKeyboard;
	CBreakPointForm			m_BreakPointForm;
	CPageMapWnd				m_PageMapWnd;
	CX86RegHelpTabWnd		m_RegHelpWnd;
	CWispCalcWnd			m_WispCalcWnd;
	CObjectDirectoryWnd		m_ObjectWnd;
	CDataOperatorDlg		m_DataOperatorDlg;
	CCrossReferenceForm		m_CrossReferenceForm;
	CCommentList			m_CommentList;
	CCallStackWnd			m_CallStackWnd;
	CRunTraceWnd			m_RunTraceWnd;
	CModuleListWnd			m_ModuleList;
	CHwndListWnd			m_HwndListWnd;
	CHwndPropertyForm		m_HwndPropertyForm;
	CProcessList			m_ProcessList;
	CIDTWnd					m_IDTWnd;
	CGDTWnd					m_GDTWnd;
	CWispStaticStr			m_TipStr;
	CStringReferenceList	m_StringReferenceWnd;
	CFindListWnd			m_FindListWnd;
	CPEExplorerForm			m_PEExplorerForm;
	CIBMAsciiWnd			m_IBMAsciiWnd;
	CIBMAsciiWnd			m_EBEDICWnd;
	CIBMAsciiWnd			m_ANSIAsciiWnd;
private:
	void ProcessMoveFrame();
};

#endif

