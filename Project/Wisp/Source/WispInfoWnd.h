#ifndef _WISP_INFO_WND_H_
#define _WISP_INFO_WND_H_

#include "WispWnd.h"

class CWispInfoWnd : public CWispBaseWnd
{
public:
	CWispInfoWnd(void);
	virtual ~CWispInfoWnd(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate);
};

#endif

