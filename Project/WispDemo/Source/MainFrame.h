#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

#include "MainTabWnd.h"
#include "RippleWnd.h"
#include "M3DView.h"


class CMainFrame : public CWispWnd
{
public:
	CMainFrame(void);
	~CMainFrame(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG(OnCommand)
	DECLARE_WISP_MSG(OnKeyEvent)
	CWispToolbar	m_Toolbar;
	CMainTabWnd		m_MainTabWnd;
	CWispCalcWnd	m_CalcWnd;
	CWispSoftKeyboard m_SoftKB;
	CRippleWnd		m_RippleWnd;
	CM3DView		m_M3DView;
	CWispTaskPanel	m_TaskPanel;
	CWispMenu		m_PopupMenu;
	CWispMenu		m_MainMenu;
	CWispProgressForm	m_ProgressForm;
};

#endif
