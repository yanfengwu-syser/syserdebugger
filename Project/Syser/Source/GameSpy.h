#ifndef _GAME_SPY_H_
#define _GAME_SPY_H_

class CGameSpyFrameWnd : public CWispWnd
{
public:
	CGameSpyFrameWnd();
	~CGameSpyFrameWnd();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
};

#endif
