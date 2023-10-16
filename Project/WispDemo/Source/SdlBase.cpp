#include "StdAfx.h"
#include "SdlBase.h"
#include "LocalApp.h"
#include <signal.h>
	CLocalBase	LocalBase;
typedef void (*TimerCallBack)(int);
int SetTimer(int nTime, TimerCallBack cb)
{
	struct itimerval iValue,oValue;
	struct sigaction siga;
	siga.sa_handler=cb;
	siga.sa_flags=0;
	memset(&siga.sa_mask,0,sizeof(sigset_t));
	sigaction(SIGALRM,&siga,0);

	iValue.it_value.tv_sec=0;
	iValue.it_value.tv_usec=nTime;
	iValue.it_interval.tv_sec=0;
	iValue.it_interval.tv_usec=nTime;
	setitimer(ITIMER_REAL,&iValue,&oValue);
	return 0;
}

void OnTimer(int i)
{
	LocalBase.OnTimer(50);
}
int  main(int argc,char *argv[])
{
	bool bExit;
	SDL_Event Event;
	pthread_t pid,scanvirus;
	void *retval;

	LocalBase.AttachApp(&theApp);
	if(theApp.InitInstance()==FALSE)
		return 0;
	pid = (pthread_t)CreateThread(CLocalBase::WispMsgThread);
	SetTimer(50000,OnTimer);
	bExit=FALSE;
	while(!bExit)
	{
		if(SDL_WaitEvent(&Event))
		{
			switch (Event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				LocalBase.OnKeyEvent(WISP_VK_LBUTTON,TRUE);
				break;
			case SDL_MOUSEBUTTONUP:
				LocalBase.OnKeyEvent(WISP_VK_LBUTTON,FALSE);
				break;
			case SDL_MOUSEMOTION:
				LocalBase.OnMousePosChg(Event.motion.x, Event.motion.y);
				break;
			case SDL_KEYDOWN:
				{
					if(Event.key.keysym.sym == WISP_VK_ESCAPE)
					{
						LocalBase.OnKeyEvent(WISP_VK_ESCAPE,TRUE);

						bExit = TRUE;
					}
					break;
				}
			default:
				break;
			}			
		}
	}

	return 	theApp.ExitInstance();
}

CLocalBase::CLocalBase(void)
{
	m_SleepStat = FALSE;
}

CLocalBase::~CLocalBase(void)
{
}

bool CLocalBase::Init()
{	
	WISP_SCREEN_INFO ScrInfo;
	if(CWispBase::Init()==FALSE)
		return FALSE;
	SDL_Init(SDL_INIT_VIDEO);

	if(GetSupportMode(WISP_MODE_640X480X32,&ScrInfo)==FALSE)
		return FALSE;

	return SetScreenMode(&ScrInfo);
}


void CLocalBase::Release()
{
	SDL_Quit();
	return CWispBase::Release();
}

//////////////////////////////////////////////////////////
//设置显示模式
//////////////////////////////////////////////////////////
bool CLocalBase::SetScreenMode(IN WISP_SCREEN_INFO*pInfo)
{
	WISP_SCREEN_INFO Info;
	m_pScreen = SDL_SetVideoMode(pInfo->ScreenWidth, pInfo->ScreenHeight, pInfo->Bpp, SDL_SWSURFACE);
	if(m_pScreen == NULL)
		return FALSE;
	printf("SetScreenMod\n");
	fflush(stdout);
	Info=*pInfo;
	SDL_ShowCursor(FALSE);
	Info.Bpp=m_pScreen->format->BytesPerPixel * 8;
	Info.LineDistance = m_pScreen->pitch;
	Info.ScreenWidth=m_pScreen->w;
	Info.ScreenHeight=m_pScreen->h;
	Info.VideoBuffer=m_pScreen->pixels;
	return CWispBase::SetScreenMode(&Info);
}


bool CLocalBase::BeginDraw()
{
	if(SDL_MUSTLOCK(m_pScreen))
		if(SDL_LockSurface(m_pScreen) < 0)
			return FALSE;
	return TRUE;
}

bool CLocalBase::EndDraw()
{
	if(SDL_MUSTLOCK(m_pScreen))
		SDL_UnlockSurface(m_pScreen);
	SDL_UpdateRect(m_pScreen, 0,0,m_pScreen->w,m_pScreen->h);
	return TRUE;
}

//////////////////////////////////////////////////////////
// Message thread
//////////////////////////////////////////////////////////
bool CLocalBase::InitMsgThread()
{	
	pthread_mutex_init(&m_ThreadLock,NULL);
	pthread_cond_init(&m_MsgNull,NULL);
	return TRUE;
}

bool CLocalBase::WakeUpMsgThread()
{
	if(m_SleepStat)
	pthread_cond_signal(&m_MsgNull);
	return TRUE;
}

bool CLocalBase::SleepMsgThread()
{
	pthread_mutex_lock(&m_ThreadLock);
	m_SleepStat = TRUE;
	pthread_cond_wait(&m_MsgNull,&m_ThreadLock);
	m_SleepStat = FALSE;
	pthread_mutex_unlock(&m_ThreadLock);
	return TRUE;
}

void CLocalBase::ExitMsgThread()
{
}

void CLocalBase::WispMsgThread()
{
	printf("TheApp.Run()\n");
	fflush(stdout);
	theApp.Run();
}


