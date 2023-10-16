#ifndef _SOURCEDEBUGFRAMEWND_H_
#define _SOURCEDEBUGFRAMEWND_H_

#include "SyserSymAnalyzer.h"
#include "MultiSourceCodeView.h"
#include "SourceDebugClassView.h"
#include "ObjFileView.h"
#include "SDSModuleList.h"
#include "SourceCodeWatchList.h"
#include "TypeViewerWnd.h"

class CSourceDebugFrameWnd : public CWispSplitWnd
{
	enum SOURCEDEBUGMAINWNDCHILD
	{
		WND_CHILD_FILELISTEXPLORER=WISP_WM_USER_START+200,
		WND_CHILD_FUNCTIONEXPLORER,
		WND_CHILD_IMPORTTABLEVIEW,
		WND_CHILD_EXPORTTABLEVIEW,
		WND_CHILD_WATCHEXPLORER,
		WND_CHILD_SOURCEFILETABWND,
		WND_CHILD_SOURCECODEWND,
		WND_CHILD_SDS_MODULE_LIST,
		WND_CHILD_SOURCE_CODE_WATCH_LIST,
	};
public:
	CSDSModuleList			m_SDSModuleList;
	CWispTabWnd				m_ExplorerTabWnd;
	CWispTabWnd				m_MonitorTabWnd;
	CTerminalWnd			m_TerminalWnd;
	CMultiSourceCodeView	m_MultiSourceCodeView;
	CTypeViewerWnd			m_SourceVariableWatchWnd;
	CWispToolbar			m_Toolbar;
	CMoveFramMenu			m_WndMenu;
	CWispSplitWnd			m_HorzSplitWnd;
	CWispSplitWnd			m_VertSplitWnd;
	CWispDIBList			m_IconDIBList;
	CSourceDebugFrameWnd();
	~CSourceDebugFrameWnd();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnGetFocus)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventBreakPoint)
	DECLARE_WISP_MSG_EVENT(OnEventDataViewForm)
	DECLARE_WISP_MSG_EVENT(OnEventRegView)
	DECLARE_WISP_MSG_EVENT(OnEventCallStack)
	DECLARE_WISP_MSG_EVENT(OnEventGoToLine)
	DECLARE_WISP_MSG_EVENT(OnEventContinue)
	DECLARE_WISP_MSG_EVENT(OnEventStep)
	DECLARE_WISP_MSG_EVENT(OnEventProceed)
	DECLARE_WISP_MSG_EVENT(OnEventReturn)
	DECLARE_WISP_MSG_EVENT(OnEventToggleBookMark)
	DECLARE_WISP_MSG_EVENT(OnEventNextBookMark)
	DECLARE_WISP_MSG_EVENT(OnEventPrevBookMark)
	DECLARE_WISP_MSG_EVENT(OnEventClearBookMark)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventSDSModule);
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventWatchList);
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventConsole);
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuDebug)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuView)
	DECLARE_WISP_MSG_EVENT(OnHotKeyEventMenuMonitor)
	void	AdjustSplitViewSize();
	void	UpdateItemState();
	void	UpdateAllView(bool bShowEIPDoc = false);
	void	UnloadSDSModule(CSDSModule*pSDSModule);
	CSourceCodeWnd* ShowSourceFile(CSDSModule*pSDSModule,DWORD FileID,DWORD LineNum);
};

#endif // _SOURCEDEBUGFRAMEWND_H_ 
