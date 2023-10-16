#include "StdAfx.h"
#include "ErrorCodeTable.h"
#include "ErrorCodeWnd.h"

WISP_MSG_MAP_BEGIN(CErrorCodeWnd) 
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)
WISP_MSG_EVENT_MAP_BEGIN(CErrorCodeWnd)

WISP_MSG_EVENT_MAP_END

CErrorCodeWnd::CErrorCodeWnd()
{

}
CErrorCodeWnd::~CErrorCodeWnd()
{

}
bool CErrorCodeWnd::OnCreate(IN WISP_MSG* pMsg)
{
	InsertColumn(WSTR("Code"),140);
	InsertColumn(WSTR("Name"),345);
	InsertColumn(WSTR("Description"),345);
	UpdateContext();
	return true;
}
void CErrorCodeWnd::UpdateContext()
{
	HANDLE hItem;
	WCHAR Buffer[50];
	for(int i=0; ErrorCodes[i].Name;i++)
	{
		TSPrintf(Buffer,WSTR("0x%08X [%d]"),ErrorCodes[i].Code,ErrorCodes[i].Code);
		hItem = InsertItem(Buffer);
		SetItemTextA(hItem,1,ErrorCodes[i].Name);
		SetItemTextA(hItem,2,ErrorCodes[i].Description);
	}
}
bool CErrorCodeWnd::OnClose(IN WISP_MSG* pMsg)
{
	Show(WISP_SH_HIDDEN);
	return false;
}