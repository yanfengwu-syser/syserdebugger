#ifndef _MULTISOURCECODEVIEW_H_
#define _MULTISOURCECODEVIEW_H_

#include "SourceCodeWnd.h"

typedef struct stCmdSelectSourceCodeLine
{
	DWORD SourceFileId;
	DWORD LineNum;
}CMDSELECTSOURCECODELINE,*PCMDSELECTSOURCECODELINE;


struct SOURCE_CODE_WND_ID
{
	DWORD FileID;
	CSDSModule*pSDSModule;
	CSourceCodeWnd*pSourceCodeWnd;
	bool operator==(const SOURCE_CODE_WND_ID&WndID)const
	{
		return WndID.FileID == FileID && WndID.pSDSModule == pSDSModule;
	}
	bool operator<(const SOURCE_CODE_WND_ID&WndID)const
	{
		if(FileID<WndID.FileID)
			return true;
		if(FileID>WndID.FileID)
			return false;
		return PTR_TO_NUM(pSDSModule)<PTR_TO_NUM(WndID.pSDSModule);
	}
};

class CMultiSourceCodeView:public CWispMultiTabView
{
public:
	CWispDIBList* m_SourceLineStateDIBList;
	TSet<SOURCE_CODE_WND_ID> m_OpenedSourceCodeWnd;
#ifdef CODE_OS_WIN
	HCURSOR m_HCurrentEIPCursor;
	HCURSOR m_HDragEIPCurosr;
#endif
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnCmdAddrChg)
	bool OnCloseTabWnd(CWispWnd*pWnd);
	void OnClosedTabWnd();
	void OnTabChanged(CWispWnd*pWnd);
	void UpdateAllView();
};

#endif
