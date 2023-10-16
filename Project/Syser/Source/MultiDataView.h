#ifndef _MULTI_DATA_VIEW_H_
#define _MULTI_DATA_VIEW_H_

#include "DataView.h"

class CMultiDataView : public CWispMultiTabView
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventExpandView);
	DECLARE_WISP_MSG_EVENT(OnEventNewView)
	void	SetActiveAddress(DWORD Address,WCHAR* pCmdString=NULL);
	void	SetActiveDataWidth(int Width);
	int		GetActiveDataWidth();
	DWORD	GetActiveAddress();
	CDataView*	InsertView(CDataView*pSrcWnd = NULL);
	void	RemoveView(CDataView*pRemoveWnd);
	void	UpdateAllView();
	void	ResetContext();
	void	SaveContextAllView();//存储所有数据窗口显示的当前数据内容，用来显示 改变高亮
};

#endif

