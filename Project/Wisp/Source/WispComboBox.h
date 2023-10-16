#ifndef _WISP_COMBOBOX_H_
#define _WISP_COMBOBOX_H_

#include "WispList.h"
#include "WispButton.h"

class CWispComboBox : public CWispEdit
{
public:
	CWispComboBox();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnDestroy)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnComboBT)
	DECLARE_WISP_MSG_EVENT(OnComboListEvent)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnComboListCmd)
public:
	int			m_CurSelIndex;
	CWispList	m_ComboList;
	CWispButton	m_ComboButton;
	void		SelectItem(int Index);
	int			GetCurSelItem();
};

#endif


