#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

#include "ProcessList.h"
#include "SyserAppCmd.h"
#include "DbgMsgFilter.h"
#include "OpenFileForm.h"
#include "LoadIDAMapFile.h"
#include "RegisterForm.h"
#include "..\..\Syser\Source\SyserAboutForm.h"

#define	MAX_TIP_WIDTH	500

class CMainFrame : public CWispWnd
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnSize);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnMainTabCommand)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnUpdateDriverState)
	DECLARE_WISP_MSG_EVENT(OnMenuEventLoadModule)
	DECLARE_WISP_MSG_EVENT(OnMenuEventLoadExportSymbols);
	DECLARE_WISP_MSG_EVENT(OnMenuEventLoadSymbol)
	DECLARE_WISP_MSG_EVENT(OnMenuEventLoadIDAMap)	
	DECLARE_WISP_MSG_EVENT(OnMenuEventTranslateSymbol)
	DECLARE_WISP_MSG_EVENT(OnMenuEventStartSyser)
	DECLARE_WISP_MSG_EVENT(OnMenuEventStopSyser)
	DECLARE_WISP_MSG_EVENT(OnMenuEventSendClipboard)
	DECLARE_WISP_MSG_EVENT(OnMenuEventRecvClipboard)
	DECLARE_WISP_MSG_EVENT(OnMenuEventDebugMessage)
	DECLARE_WISP_MSG_EVENT(OnMenuEventClearDebugMessage)
	DECLARE_WISP_MSG_EVENT(OnMenuEventDebugMessageFilter)
	DECLARE_WISP_MSG_EVENT(OnMenuEventExit)
	DECLARE_WISP_MSG_EVENT(OnMenuEventOption)
	DECLARE_WISP_MSG_EVENT(OnMenuEventBootOption)
	DECLARE_WISP_MSG_EVENT(OnMenuEventVideoDetectMode)
	DECLARE_WISP_MSG_EVENT(OnMenuEventSymDownloader)
	DECLARE_WISP_MSG_EVENT(OnMenuEventDrvLoader)
	DECLARE_WISP_MSG_EVENT(OnMenuEventVEUnpack)
	DECLARE_WISP_MSG_EVENT(OnMenuEventCheckNewVersion)
	DECLARE_WISP_MSG_EVENT(OnMenuEventBuyNow);
	DECLARE_WISP_MSG_EVENT(OnMenuEventRegister)
	DECLARE_WISP_MSG_EVENT(OnMenuEventCmdRef)
	DECLARE_WISP_MSG_EVENT(OnMenuEventDebugHelp)
	DECLARE_WISP_MSG_EVENT(OnMenuEventAboutSyserApp)
	DECLARE_WISP_MSG_EVENT(OnMenuEventRecentFile)
	DECLARE_WISP_MSG_EVENT(OnMenuEventSaveHistroys);
	DECLARE_WISP_MSG_EVENT(OnMenuEventSaveSyserHistroys);
	DECLARE_WISP_MSG_EVENT(OnMenuEventSaveComments);
public:
	CRegisterForm	m_RegForm;
	CWispMenu		m_MainMenu;
	CWispToolbar	m_MainToolBar;
	CWispTabWnd		m_MainTabWnd;
	CConsoleWnd		m_ConsoleWnd;
	//CProcessList	m_ProcessList;
	CWispProgressForm m_ProgressForm;
	WISP_SIZE		m_OldFrameSize;
	CWispStaticStr	m_TipStr;
	void	GetVersionString();
	void	UpdateSyserDriverItem(bool bEnable);
};

#endif
