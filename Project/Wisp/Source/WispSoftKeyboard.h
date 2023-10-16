#ifndef _WISP_SOFT_KEYBOARD_H_
#define _WISP_SOFT_KEYBOARD_H_

#include "WispStatic.h"
#include "WispWnd.h"


struct WISP_SKB_KEY
{
	WISP_CHAR*	szKeyName;
	UINT		VKCmdID;
	WISP_RECT	BTRect;
};

#define	WISP_SKBS_NORMAL	(WISP_WS_CAPTION | WISP_WS_BT_MIN | WISP_WS_BT_CLOSE | WISP_WS_BORDER)

class CWispSoftKeyboard : public CWispWnd
{
public:
	CWispSoftKeyboard(void);
	virtual ~CWispSoftKeyboard(void);
public:
	static WISP_SKB_KEY m_SoftKeyTable[];
	CWispBaseWnd**	m_BTAry;
	CWispStaticDIB	m_StaticDIB;
	bool	Create(int x,int y,CWispWnd*pParentWnd,
					UINT Style = WISP_SKBS_NORMAL,
					UINT ShowMode = WISP_SH_NORMAL,
					UINT CmdID = WISP_ID_SOFT_KB);
	void Popup();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnGetFocus);
	DECLARE_WISP_MSG_CMD_MAP
};


#endif


