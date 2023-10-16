#ifndef _WISP_STATIC_H_
#define _WISP_STATIC_H_

#include "WispBaseWnd.h"

class CWispStaticStr : public CWispBaseWnd
{
public:
	CWispStaticStr();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate);
};

class CWispStaticDIB : public CWispBaseWnd
{
public:
	CWispStaticDIB();
	bool Create(CWispDIB*pDIB,int x,int y,CWispBaseWnd* pParentWnd, UINT nID = WISP_ID_STATIC_DIB);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate);
public:
	CWispDIB*	m_pDIB;
};

class CWispStaticGroup : public CWispBaseWnd
{
public:
	CWispStaticGroup();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate);
	DECLARE_WISP_MSG(OnGetFocus)
};


class CWispStaticURL : public CWispBaseWnd
{
public:
	CWispStaticURL();
public:
	bool		m_bHover;
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnMouseEnter);
	DECLARE_WISP_MSG(OnMouseLeave);
};

#endif

