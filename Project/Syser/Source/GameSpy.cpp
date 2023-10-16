#include "stdafx.h"
#include "GameSpy.h"

WISP_MSG_MAP_BEGIN(CGameSpyFrameWnd) 
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispWnd)


CGameSpyFrameWnd::CGameSpyFrameWnd()
{

}

CGameSpyFrameWnd::~CGameSpyFrameWnd()
{

}


bool CGameSpyFrameWnd::OnCreate(IN WISP_MSG*pMsg)
{
	return true;
}

bool CGameSpyFrameWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	return true;
}
