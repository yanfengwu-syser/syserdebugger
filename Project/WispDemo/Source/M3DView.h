#ifndef _M3D_VIEW_H_
#define _M3D_VIEW_H_

class CM3DView : public CWispWnd
{
public:
	CM3DView(void);
	~CM3DView(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnMouseMove);
};

#endif
