#include "StdAfx.h"
#include "ControlWnd.h"

WISP_MSG_MAP_BEGIN(CControlWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_EVENT_MAP_BEGIN(CControlWnd)
	WISP_MSG_EVENT_MAP(CTRL_BT_OK_ID,OnOK);
	WISP_MSG_EVENT_MAP(CTRL_BT_MSG_BOX_ID,OnMsgBox);
	WISP_MSG_EVENT_MAP(CTRL_BT_STEP_IT_ID,OnStepIt);
WISP_MSG_EVENT_MAP_END


bool CControlWnd::OnCreate(IN WISP_MSG*pMsg)
{
	m_Edit.Create(WISP_STR("Edit"),10,30,300,16,this,CTRL_EDIT_ID,WISP_ES_EDIT_NORMAL);
	m_OKDIB.Load("\\WispApp\\SoftKeyboard\\SoftKeyboard.ico",0);
	m_BTOK.CreateEx(&m_OKDIB,320,50,this,CTRL_BT_OK_ID,WISP_BS_TEXT_LEFT);
	m_BTOK.SetWindowText(WSTR("OK"));
	m_BTMsgBox.Create(WISP_STR("Message"),390,50,60,20,this,CTRL_BT_MSG_BOX_ID,WISP_BS_NORMAL,WISP_SH_NORMAL);
	m_ListCtrl.Create(NULL,CWispRect(10,60,300,200),this,CTRL_LIST_ID,WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_TREE_LINE);
	m_Progress.Create(0, CWispRect(10, 270, 200, 20), this);
	m_Progress.SetPos(2);
	m_BtnStepIt.Create(WISP_STR("Step It"),220,270,60,20,this,CTRL_BT_STEP_IT_ID,WISP_BS_NORMAL,WISP_SH_NORMAL);
	m_CheckBox.Create(WISP_STR("Text check box"), CWispRect(10, 300, 200, 20), this,0 ,WISP_WS_BORDER|WISP_WS_BACK_TRANS|WISP_CBS_FLAT, WISP_SH_NORMAL);
	m_ComboBox.Create(WISP_STR(""),350,180,100,380,this);

	m_ListCtrl.InsertColumn(WSTR("col1"),120,WISP_WLCS_NORMAL,&m_OKDIB);
	m_ListCtrl.InsertColumn(WSTR("col2"),80,WISP_WLCS_EDITABLE);
	m_ListCtrl.InsertColumn(WSTR("col3"),80,WISP_WLCS_EDITABLE);

	HANDLE hItem,hItem1;
	hItem = m_ListCtrl.InsertItem(L"Item\tƒÃ≈£level",NULL,WISP_WLIS_EXPANDED,&m_OKDIB);
	hItem1 = m_ListCtrl.InsertItem(L"Level 1",hItem,WISP_WLIS_EXPANDED,&m_OKDIB,-1);
	m_ListCtrl.InsertItem(L"Level 1",hItem,WISP_WLIS_EXPANDED,&m_OKDIB,-1);

	m_ListCtrl.InsertItem(L"Level 2",hItem1,WISP_WLIS_EXPANDED,&m_OKDIB,-1);
	m_ListCtrl.InsertItem(L"Level 2",hItem1,WISP_WLIS_EXPANDED,&m_OKDIB,-1);
	m_ListCtrl.InsertItem(L"Level 2",hItem1,WISP_WLIS_EXPANDED,&m_OKDIB,-1);

	hItem = m_ListCtrl.InsertItem(L"Item1",NULL,WISP_WLIS_EXPANDED,&m_OKDIB);
	hItem1 = m_ListCtrl.InsertItem(L"Level 1",hItem,WISP_WLIS_EXPANDED,&m_OKDIB,-1);
	m_ListCtrl.InsertItem(L"Level 1",hItem,WISP_WLIS_EXPANDED,&m_OKDIB,-1);

	m_ListCtrl.InsertItem(L"Level 1",hItem1,WISP_WLIS_EXPANDED,&m_OKDIB,-1);
	m_ListCtrl.InsertItem(L"Level 2",hItem1,WISP_WLIS_EXPANDED,&m_OKDIB,-1);
	hItem = m_ListCtrl.InsertItem(L"Level 3",hItem1,WISP_WLIS_EXPANDED,&m_OKDIB,-1);
	return true;
}

bool CControlWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	m_OKDIB.Destroy();
	return true;
}

bool CControlWnd::OnOK(IN WISP_MSG*pMsg)
{
	CWispString Str;
	InputTextForm(100,100,Str,WSTR(""));
	return true;
}

bool CControlWnd::OnMsgBox(IN WISP_MSG*pMsg)
{
	MsgBox(WISP_STR("hi"),WISP_STR("Message Box"), WISP_MB_ICONINFOMATION);
	return true;
}

bool CControlWnd::OnStepIt(IN WISP_MSG*pMsg)
{
	m_Progress.StepIt();
	return true;
}


