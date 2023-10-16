#include "StdAfx.h"
#include "SourceExplorer.h"

WISP_MSG_MAP_BEGIN(CSourceExplorer) 
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispWnd)


CSourceExplorer::CSourceExplorer()
{

}

CSourceExplorer::~CSourceExplorer()
{

}


bool CSourceExplorer::OnCreate(IN WISP_MSG*pMsg)
{
	return true;
}

bool CSourceExplorer::OnDestroy(IN WISP_MSG*pMsg)
{
	return true;
}
