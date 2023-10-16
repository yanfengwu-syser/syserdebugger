#ifndef _WISP_TIP_WND_H_
#define _WISP_TIP_WND_H_

#include "WispWnd.h"

class CWispTipWnd : public CWispWnd
{
public:
	CWispTipWnd();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate);
	void	AutoAdjustPostion(CWispBaseWnd*pTipHelpWnd = NULL);
	CWispBaseWnd*m_pTipHelpWnd;
};

#endif
