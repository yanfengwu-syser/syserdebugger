#ifndef _CONTROL_WND_H_
#define _CONTROL_WND_H_


enum
{
	CTRL_EDIT_ID,
	CTRL_BT_OK_ID,
	CTRL_BT_MSG_BOX_ID,
	CTRL_BT_STEP_IT_ID,
	CTRL_LIST_ID,
	CTRL_MAIN_MENU_ID,
};

class CControlWnd : public CWispWnd
{
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnOK);
	DECLARE_WISP_MSG_EVENT(OnMsgBox);
	DECLARE_WISP_MSG_EVENT(OnStepIt);
public:
	CWispDIB	m_OKDIB;
	CWispEdit	m_Edit;
	CWispButton	m_BTOK, m_BTMsgBox, m_BtnStepIt;
	CWispProgress	m_Progress;
	CWispCheckBox	m_CheckBox;
	CWispComboBox	m_ComboBox;
	CWispList	m_ListCtrl;
	HANDLE m_hItem;
};

#endif
