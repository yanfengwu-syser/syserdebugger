#ifndef _WISP_TASK_PANEL_H_
#define _WISP_TASK_PANEL_H_

#include "WispWnd.h"


class CWispTaskPanel : public CWispWnd
{
public:
	CWispTaskPanel();
	~CWispTaskPanel();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnRecalcLayout);
public:
};

#endif
