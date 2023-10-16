#ifndef _WISP_FORM_H_
#define _WISP_FORM_H_

#include "WispWnd.h"

#define WISP_WFS_DIALOG		(WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER)

class CWispForm : public CWispWnd
{
public:
	CWispForm(void);
	virtual ~CWispForm(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnBTCmdDefault)
	DECLARE_WISP_MSG_CMD(OnCmdClose)
	DECLARE_WISP_MSG_CMD(OnCmdCancel)
	DECLARE_WISP_MSG_CMD(OnCmdOK)
public:
	bool	CreateForm(CWispBaseWnd*pParenWnd = NULL,UINT ShowMode = WISP_SH_NORMAL);
	bool	LoadForm(WISP_FORM_RES_ITEM*ItemAry);
	bool	Destroy();
	CWispBaseWnd*GetFormItem(UINT CmdID);
	TMap<UINT,CWispBaseWnd*>m_FormItemMap;
	UINT	GetFormResult(){return m_Result;}
public:
	UINT	m_Result;
	WISP_FORM_RES_ITEM*m_pFormRes;
};


#endif
