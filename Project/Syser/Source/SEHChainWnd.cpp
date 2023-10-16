#include "StdAfx.h"
#include "SEHChainWnd.h"
#include "Syser.h"

WISP_MSG_MAP_BEGIN(CSEHChainWnd) 
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)
WISP_MSG_EVENT_MAP_BEGIN(CSEHChainWnd)

WISP_MSG_EVENT_MAP_END

CSEHChainWnd::CSEHChainWnd()
{

}
CSEHChainWnd::~CSEHChainWnd()
{

}
bool CSEHChainWnd::OnCreate(IN WISP_MSG* pMsg)
{
	InsertColumn(WSTR("Address"),70);
	InsertColumn(WSTR("SE Handler"),200);
	UpdateContext();
	return true;
}
void CSEHChainWnd::UpdateContext()
{
	X86_CPU_REG_PTR RegPtr;
	SEHCHAIN SEHChain;
	HANDLE hItem;
	WCHAR Buffer[20];
	DWORD Address,Size;
	gpSyser->m_pDebugger->GetX86RegPtr( &RegPtr);
	gpSyser->m_pDebugger->GetSegRegBase(*RegPtr.pFS,&Address,&Size);
	

	if(gpSyser->m_pDebugger->ReadMemory(Address,&SEHChain,sizeof(SEHCHAIN))!=sizeof(SEHCHAIN))
		return;
	while(SEHChain.Next!=0xffffffff)
	{
		Address=SEHChain.Next;
		if(gpSyser->m_pDebugger->ReadMemory(Address,&SEHChain,sizeof(SEHCHAIN))!=sizeof(SEHCHAIN))
			break;
		TSPrintf(Buffer,WSTR("%08X"),Address);
		hItem  = InsertItem(Buffer);
		SetItemNum(hItem,1,SEHChain.Handler);
	}


}
bool CSEHChainWnd::OnClose(IN WISP_MSG* pMsg)
{
	Show(WISP_SH_HIDDEN);
	return false;
}