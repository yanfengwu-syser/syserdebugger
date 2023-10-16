#include "StdAfx.h"
#include "LocalApp.h"
#include "MainFrame.h"

enum
{
	MENU_EVENT_ITEM1 = WISP_ID_USER_START,
	MENU_EVENT_ITEM2,
	MENU_EVENT_ITEM3,
	MENU_EVENT_ITEM4,
	MENU_EVENT_ITEM5,
	MENU_EVENT_ITEM6,
	MENU_EVENT_ITEM7,
	MENU_EVENT_ITEM8,
	MENU_EVENT_ITEM9,
	MENU_EVENT_ITEM10,
	MENU_EVENT_ITEM11,
	MENU_EVENT_ITEM12,
	MENU_EVENT_ITEM13,
	MENU_EVENT_ITEM14,
};

WISP_MENU_RES_ITEM PupupMenuRes2[]=
{
	{WSTR("Item9"),MENU_EVENT_ITEM9,-1},
	{WSTR("Item10"),MENU_EVENT_ITEM10,-1},
	{WSTR("Item11"),MENU_EVENT_ITEM11,-1},
	{WSTR("Item12"),MENU_EVENT_ITEM12,-1},
	{NULL,0,0,NULL}
};

WISP_MENU_RES_ITEM PupupMenuRes1[]=
{
	{WSTR("Item5"),	MENU_EVENT_ITEM5,	-1,WISP_MIS_NORMAL|WISP_MIS_CHECKBOX|WISP_MIS_CHECKED},
	{WSTR("Item6"),	MENU_EVENT_ITEM6,	-1,WISP_MIS_NORMAL|WISP_MIS_CHECKBOX},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Item7"),	MENU_EVENT_ITEM7,	-1,WISP_MIS_NORMAL},
	{WSTR("Item8"),	MENU_EVENT_ITEM8,	-1,WISP_MIS_NORMAL},
	{WSTR("->"),	0,					-1,WISP_MIS_POPUP,PupupMenuRes2},
	{NULL,0,0,NULL}
};

WISP_MENU_RES_ITEM PupupMenuRes[]=
{
	{WSTR("Item1"),	MENU_EVENT_ITEM1,	-1},
	{WSTR("Item2"),	MENU_EVENT_ITEM2,	-1},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Item3"),	MENU_EVENT_ITEM3,	-1},
	{WSTR("Item4"),	MENU_EVENT_ITEM4,	-1},
	{WSTR("Popup Item->"),0,-1,WISP_MIS_POPUP,PupupMenuRes1},
	{NULL,0,0,NULL}
};

WISP_MSG_MAP_BEGIN(CMainFrame)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_COMMAND,OnCommand)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispWnd)

CMainFrame::CMainFrame(void)
{
}

CMainFrame::~CMainFrame(void)
{
}

bool CMainFrame::OnCreate(IN WISP_MSG*pMsg)
{
	CWispRect rc;	
	//m_Wnd.Create(WISP_STR("Wisp 3D"),CWispRect(60,60,500,400),this);
	//m_Wnd.LoadBKDIB("\\DlgAbout.bmp");
	m_Toolbar.CreateEx(this,20,0,0,0);
	m_CalcWnd.Create(100,100,this);
	m_SoftKB.Create(150,400,this);
	//m_RippleWnd.Create(WISP_STR("Ripple"),CWispRect(60,60,110+WISP_BORDER_SIZE*2,110+WISP_CAPTION_HEIGHT+WISP_BORDER_SIZE*2),this);
	//m_M3DView.Create(WISP_STR("Wisp 3D"),CWispRect(100,100,400,300),this,0,WISP_WS_NULL);
	m_MainMenu.CreateWndMenu(this,0,PupupMenuRes);
	m_MainTabWnd.Create(WISP_STR("All kind of windows in \"Wisp GUI System\""),CWispRect(50,50,500,400),this,0,WISP_WS_NORMAL | WISP_TWS_BUTTOM);
	m_MainTabWnd.SetActiveWnd(0);
	m_PopupMenu.CreatePopupMenu(PupupMenuRes,this);
//	m_DisplayWnd.Create(WSTR("CHAR"),10,10,200,200);
	m_ProgressForm.CreateForm();
	m_ProgressForm.m_pProgessCtrl->SetStep(10);
	m_ProgressForm.m_pProgessCtrl->StepIt();
	m_ProgressForm.m_pProgessCtrl->StepIt();
	m_ProgressForm.m_pProgessCtrl->StepIt();
	return true;
}

bool CMainFrame::OnCommand(IN WISP_MSG*pMsg)
{
	return true;
}

bool CMainFrame::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CMainFrame::OnKeyEvent(IN WISP_MSG*pMsg)
{

	return true;
}



