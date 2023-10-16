#ifndef _LOCAL_BASE_
#define _LOCAL_BASE_
#include <SDL/SDL.h>
class CLocalBase : public CWispBase
{
public:
	SDL_Surface*m_pScreen;
	pthread_mutex_t 	m_ThreadLock;
	pthread_cond_t		m_MsgNull;
	bool				m_SleepStat;
public:
	CLocalBase(void);
	~CLocalBase(void);
	bool	Init();
	void	Release();

	bool	SetScreenMode(IN WISP_SCREEN_INFO*pInfo);
	bool	BeginDraw();
	bool	EndDraw();

	bool	InitMsgThread();
	bool	WakeUpMsgThread();
	bool	SleepMsgThread();
	void	ExitMsgThread();

	bool	CreateLocalWindow();

	static void WispMsgThread();

};

#endif /* _LOCAL_BASE_ */
