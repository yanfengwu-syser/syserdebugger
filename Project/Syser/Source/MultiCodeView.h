#ifndef _MULTI_CODE_VIEW_H_
#define _MULTI_CODE_VIEW_H_

#include "CodeView.h"

#define CODE_VIEW_COUNT		4


class CMultiCodeView : public CWispMultiTabView
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	void	OnTabChanged(CWispWnd*pWnd);
	void	SetActiveAddress(ULPOS Address,bool bRecordAddr=true);
	ULPOS	GetActiveAddress();
	void	ToggleBookMark(ULPOS Address);
	void	ToggleBookMark();
	void	GotoNextBookMark();
	void	GotoPrevBookMark();
	void	ClearAllBookMark();
	bool	IsBookMark(ULPOS Address);
	CCodeView*	InsertView(CCodeView*pSrcWnd = NULL);
	void	RemoveView(CCodeView*pRemoveWnd);
	void	UpdateAllView();
	void	ResetContext();
	TSet<ULPOS> m_BookMark;
};

#endif


