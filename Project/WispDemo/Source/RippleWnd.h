#ifndef _RIPPLE_WND_H_
#define _RIPPLE_WND_H_


class CRippleWnd : public CWispWnd
{
public:
	CRippleWnd(void);
	~CRippleWnd(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnTimer);
	DECLARE_WISP_MSG(OnMouseMove);
public:
	CWispDIB	m_OrgDIB;
	CWispDIB	m_RippleDIB;
	CRipple		m_Ripple;
};


#endif
