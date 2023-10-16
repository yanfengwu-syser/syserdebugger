#include "StdAfx.h"
#include "Syser.h"
#include "FunctionListWnd.h"

WISP_MSG_MAP_BEGIN(CFunctionListWnd) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CFunctionListWnd)
WISP_MSG_EVENT_MAP_END

CFunctionListWnd::CFunctionListWnd()
{

}
CFunctionListWnd::~CFunctionListWnd()
{

}
bool CFunctionListWnd::OnCreate(IN WISP_MSG* pMsg)
{
	InsertColumn(WSTR("Function Name"),110);
	InsertColumn(WSTR("Start"),60);
	InsertColumn(WSTR("Length"),60);
	UpdateContext();
	return true;
}
void CFunctionListWnd::UpdateContext()
{

}

bool CFunctionListWnd::OnClose(IN WISP_MSG* pMsg)
{
	Show(WISP_SH_HIDDEN);
	return false;
}

bool CFunctionListWnd::ItemExpandingNotify(HANDLE hItem)
{
	return true;
}

void CFunctionListWnd::ItemUnexpandedNotify(HANDLE hItem)
{
}

void CFunctionListWnd::ItemClickNotify(HANDLE hItem,int Col)
{
}
