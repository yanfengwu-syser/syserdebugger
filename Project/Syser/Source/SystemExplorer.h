#ifndef _SYSTEM_EXPLORER_H_
#define _SYSTEM_EXPLORER_H_

#include "IDTWnd.h"
#include "GDTWnd.h"
#include "PageMapWnd.h"
#include "X86RegHelpTabWnd.h"
#include "ProcessList.h"
#include "ObjectDirectoryWnd.h"
#include "BreakPointForm.h"
#include "DebuggerSelectForm.h"
#include "PluginListForm.h"
#include "DataOperatorDlg.h"
#include "CrossReferenceForm.h"
#include "RunTrace.h"
#include "RunTraceWnd.h"
#include "ModuleListWnd.h"
#include "ThreadListWnd.h"
#include "CallStackWnd.h"
#include "FunctionListWnd.h"
#include "ErrorCodeWnd.h"
#include "SEHChainWnd.h"
#include "CommentList.h"
#include "MultiCodeView.h"
#include "MultiDataView.h"
#include "GeneRegList.h"
#include "WatchList.h"
#include "StackWatchList.h"
#include "FpuRegisterList.h"
#include "SSERegisterList.h"
#include "TypeViewerWnd.h"
#include "SearchDialog.h"
#include "SyserAboutForm.h"
#include "Analyzer.h"

class CSystemExplorer : public CWispWnd
{
public:
	CSystemExplorer();
	~CSystemExplorer();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG(OnSize);
	DECLARE_WISP_MSG(OnGetFocus);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnCommandMainSplit)
	DECLARE_WISP_MSG_CMD(OnCommandViewSplit)
	DECLARE_WISP_MSG_CMD(OnCommandMonitorSplit)
	DECLARE_WISP_MSG_CMD(OnCommandModuleWnd)
	DECLARE_WISP_MSG_CMD(OnCommandFunctionWnd)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventRegView)
	DECLARE_WISP_MSG_EVENT(OnEventDataViewForm)
	DECLARE_WISP_MSG_EVENT(OnEventCallStack)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventGeneReg)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventFPUReg)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventXMMReg)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventStack)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventWatch)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventCodeView)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventDataView)

	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuFile)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuDebug)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuView)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuMonitor)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuInformation)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuOption)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuTools)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuHelp)
	DECLARE_WISP_MSG_EVENT(OnHotKeySetting)

	DECLARE_WISP_MSG_EVENT(OnEventOpen)
	DECLARE_WISP_MSG_EVENT(OnEventLoadSymbolFile)
	DECLARE_WISP_MSG_EVENT(OnEventClose)
	DECLARE_WISP_MSG_EVENT(OnEventSaveComment)
	DECLARE_WISP_MSG_EVENT(OnEventLoadComment)
	DECLARE_WISP_MSG_EVENT(OnEventMemorySearch)
	DECLARE_WISP_MSG_EVENT(OnEventIDT)
	DECLARE_WISP_MSG_EVENT(OnEventGDT)
	DECLARE_WISP_MSG_EVENT(OnEventLDT)
	DECLARE_WISP_MSG_EVENT(OnEventProcess)
	DECLARE_WISP_MSG_EVENT(OnEventPageMap)
	DECLARE_WISP_MSG_EVENT(OnEventRegHelp)
	DECLARE_WISP_MSG_EVENT(OnEventObjectWnd)
	DECLARE_WISP_MSG_EVENT(OnEventContinue)
	DECLARE_WISP_MSG_EVENT(OnEventReset)
	DECLARE_WISP_MSG_EVENT(OnEventStep)
	DECLARE_WISP_MSG_EVENT(OnEventStepBranch)
	DECLARE_WISP_MSG_EVENT(OnEventProceed)
	DECLARE_WISP_MSG_EVENT(OnEventReturn)
	DECLARE_WISP_MSG_EVENT(OnEventBreakPoint)
	DECLARE_WISP_MSG_EVENT(OnEventDebuggerOption)
	DECLARE_WISP_MSG_EVENT(OnEventDebuggerSelect)
	DECLARE_WISP_MSG_EVENT(OnEventPluginList)
	DECLARE_WISP_MSG_EVENT(OnEventCalc)
	DECLARE_WISP_MSG_EVENT(OnEventSoftKB)
	DECLARE_WISP_MSG_EVENT(OnEventSetHotKey)	
	DECLARE_WISP_MSG_EVENT(OnEventPEExplorer)	
	DECLARE_WISP_MSG_EVENT(OnEventIBMAscii)
	DECLARE_WISP_MSG_EVENT(OnEventEBCDIC)
	DECLARE_WISP_MSG_EVENT(OnEventANSIAscii)
	DECLARE_WISP_MSG_EVENT(OnEventModuleWindow)
	DECLARE_WISP_MSG_EVENT(OnEventFunctionWindow)
	DECLARE_WISP_MSG_EVENT(OnEventThreadWindow)
	DECLARE_WISP_MSG_EVENT(OnEventHwndListWindow)
	DECLARE_WISP_MSG_EVENT(OnEventCallStackView)
	DECLARE_WISP_MSG_EVENT(OnEventSEHChainWindow)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBookMark)
	DECLARE_WISP_MSG_EVENT(OnEventNextBookMark)
	DECLARE_WISP_MSG_EVENT(OnEventPrevBookMark)
	DECLARE_WISP_MSG_EVENT(OnEventClearBookMark)
	DECLARE_WISP_MSG_EVENT(OnEventCommentList)
	DECLARE_WISP_MSG_EVENT(OnEventNextPos)
	DECLARE_WISP_MSG_EVENT(OnEventPrevPos)
	DECLARE_WISP_MSG_EVENT(OnEventSavePos)
	DECLARE_WISP_MSG_EVENT(OnEventEmptyPosList)
	DECLARE_WISP_MSG_EVENT(OnEventRunTraceWnd)
	DECLARE_WISP_MSG_EVENT(OnEventRecentFile)
	DECLARE_WISP_MSG_EVENT(OnEventEnableAllBreakpoint)
	DECLARE_WISP_MSG_EVENT(OnEventDisableAllBreakpoint)
	DECLARE_WISP_MSG_EVENT(OnEventRemoveAllBreakpoint)
	DECLARE_WISP_MSG_EVENT(OnMenuEventAboutSyser)
	DECLARE_WISP_MSG_EVENT(OnEventStringReference)
	DECLARE_WISP_MSG_EVENT(OnGetPrevTrace)
	DECLARE_WISP_MSG_EVENT(OnGetNextTrace)	
#ifdef CODE_OS_WIN
	DECLARE_WISP_MSG_EVENT(OnMenuEventCheckNewVersion)
#endif
public:
	bool		AttachDebugger(CX86Debugger*pDebugger);
	void		DetachDebugger();
	void		LocalEIP(VADDR32 Address);
	void		CenterViewCodeAddress(VADDR32 Address);
	void		ViewCodeAddress(VADDR32 Address,bool bRecord=false);
	void		ViewDataAddress(VADDR32 Address,int SelLen = 0);
	void		UpdateContext();
	void		SaveMemoryContext();
	void		UpdateMemoryView();
	void		ResetContext();
	void		AdjustSplitViewSize();
	void		OnHide();
	void		InsertRunTrace();
	PSTRUNTRACE GetNextTrace();
	PSTRUNTRACE GetPrevTrace();
	bool		SetRunTrace(UINT Index);
	void		UpdateItemState();
	//½¨Á¢ Reg,FPU,XMM ¼Ä´æÆ÷´°¿Ú
	bool		CreateRegWindows(IN WISP_MSG*pMsg);
public:
#ifdef CODE_OS_WIN
	CSyserOptionForm	m_SyserOptionForm;
#endif
	CSearchDialog		m_SearchDialog;
	CMoveFramMenu		m_WndMenu;
	CWispStaticStr		m_VersionStr;
	CWispStaticStr		m_ContextStr;
	CWispBaseWnd*		m_pInfoMsgWnd;
	CWispToolbar		m_Toolbar;
	
	CWatchList			m_WatchList;
	CStackWatchList		m_StackWatchList;
	CWispTabWnd			m_MultiCPUTabWnd;
	

	CWispTabWnd			m_ContextTabWnd;
	CWispSplitWnd		m_ViewSplitWnd;
	CWispSplitWnd		m_MainSplitWnd;
	CWispSplitWnd		m_MonitorSplitWnd;
	CMultiCodeView		m_MultiCodeView;
	CMultiDataView		m_MultiDataView;


	DWORD				m_CPUNumbers;
	CFpuRegisterList*	m_pWndFpuReg;
	CSSERegisterList*	m_pWndESSReg;
	CGeneRegList*		m_pWndGeneReg;
	CWispTabWnd*		m_pWndRegTab;

	CTerminalWnd		m_TerminalWnd;	
	CCodeView*			m_pCurCodeView;

	//////////////////////////////////////////////////////////////////////////////
	///              Run Trace
	CRunTrace			m_RunTrace;
	X86_REG_CONTEXT		m_TracePrevReg;
	ULPOS				m_TraceMoveIndex;
	ULPOS				m_TraceCount;
	///              Run Trace
	//////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////////////////////////////////////////////////////
	///              Module Window
	CThreadListWnd		m_ThreadListWnd;
	CSEHChainWnd		m_SEHChainWnd;
	///              Module Window
	//////////////////////////////////////////////////////////////////////////////
	ULONGLONG		m_StrReferenceModuleID;		
	TMap<DWORD,ULONGLONG> m_StrReferenceMap;

	CAnalyzer m_Analyzer;
	CWispList	m_FunctionWnd;
};





#endif
