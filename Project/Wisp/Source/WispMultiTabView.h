#ifndef _WISP_MULTI_TAB_VIEW_H_
#define _WISP_MULTI_TAB_VIEW_H_

#include "WispButton.h"
#include "WispTabWnd.h"
#include "WispToolbar.h"

enum
{
	WISP_MULTI_TAB_CMD_EXPAND_VIEW = WISP_ID_DEVELOP_START,
	WISP_MULTI_TAB_CMD_NEW_VIEW,
	WISP_MULTI_TAB_CMD_REMOVE_VIEW,
	WISP_MULTI_TAB_TOOLBAR_CMD_ID
};

class CWispMultiTabView : public CWispTabWnd
{
public:
	CWispMultiTabView();
	WISP_TOOLBAR_RES_ITEM*	m_pToolbarRes;
	CWispToolbar			m_TabToolbar;
public://œ˚œ¢”≥…‰
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnDestroy)
};


#endif

