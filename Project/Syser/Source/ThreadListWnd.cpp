#include "StdAfx.h"
#include "Syser.h"
#include "ThreadListWnd.h"
#include "OSProcessThread.h"


WISP_MENU_RES_ITEM ThreadMenu[]=
{
	
	{WSTR("Goto KTHREAD    Enter"),			EVENT_ID_GOTO_THREAD_STRUCT,7*16+7},
	{WSTR("Goto KPROCESS   Shift+Enter"),	EVENT_ID_GOTO_PROCESS_STRUCT,		7*16+7},
	{WSTR("Goto thread eip"),				EVENT_ID_GOTO_THREAD_EIP,		7*16+7},
	{WSTR("Goto thread StartAddress   "),	EVENT_ID_GOTO_START_ADDRESS,		7*16+7},
	{WSTR("Set breakpoint at thread   "),	EVENT_ID_SET_BREAKPOINT_AT_THREAD,		7*16+7},
	{WSTR("Set breakpoint at process   "),	EVENT_ID_SET_BREAKPOINT_AT_PROCESS,		7*16+7},
	
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CThreadListWnd) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CThreadListWnd)
WISP_MSG_EVENT_MAP(EVENT_ID_GOTO_THREAD_STRUCT,		OnEventGotoThreadStruct)
WISP_MSG_EVENT_MAP(EVENT_ID_GOTO_PROCESS_STRUCT,		OnEventGotoProcessStruct)
WISP_MSG_EVENT_MAP(EVENT_ID_GOTO_START_ADDRESS,			OnEventGotoStartAddress)
WISP_MSG_EVENT_MAP(EVENT_ID_GOTO_THREAD_EIP,			OnEventGotoThreadEIP)
WISP_MSG_EVENT_MAP(EVENT_ID_SET_BREAKPOINT_AT_THREAD,			OnEventSetBreakpointAtThread)
WISP_MSG_EVENT_MAP(EVENT_ID_SET_BREAKPOINT_AT_PROCESS,			OnEventSetBreakpointAtProcess)
WISP_MSG_EVENT_MAP_END


CThreadListWnd::CThreadListWnd()
{

}
CThreadListWnd::~CThreadListWnd()
{

}

bool CThreadListWnd::OnEventSetBreakpointAtThread(IN WISP_MSG*pMsg)
{
	DWORD Address;
	bool bOK1;
	WCHAR CmdString[50];
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = (DWORD)GetItemData(hItem,TL_THREAD_ID);
	TSPrintf(CmdString,WSTR("bpt %x"),Address);
	RUNCMD(CmdString);
	return true;
}

bool CThreadListWnd::OnEventSetBreakpointAtProcess(IN WISP_MSG*pMsg)
{
	DWORD Address;
	bool bOK1;
	WCHAR CmdString[50];
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = (DWORD)GetItemData(hItem,TL_PROCESS_ID);
	TSPrintf(CmdString,WSTR("bpp %x"),Address);
	RUNCMD(CmdString);
	return true;
}

bool CThreadListWnd::OnEventGotoThreadStruct(IN WISP_MSG*pMsg)
{
	DWORD Value;
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	DWORD Address;
	
	Address = (DWORD)GetItemData(hItem,TL_THREAD_ID);
	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		VIEW_DATA(Address);
	return true;
}

bool CThreadListWnd::OnEventGotoProcessStruct(IN WISP_MSG*pMsg)
{
	DWORD Value;
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	DWORD Address;
	Address = (DWORD)GetItemData(hItem,TL_PROCESS_ID);
	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		VIEW_DATA(Address);
	return true;
}

bool CThreadListWnd::OnEventGotoStartAddress(IN WISP_MSG*pMsg)
{
	DWORD Value;
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	DWORD Address;
	Address = (DWORD)GetItemData(hItem,TL_STARTADDRESS);	
	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		VIEW_CODE(Address,true);
	return true;
}

bool CThreadListWnd::OnEventGotoThreadEIP(IN WISP_MSG*pMsg)
{
	DWORD Value;
	PSYSER_KTRAP_FRAME pTrapFrame;
	bool bOK1;
	SYSER_THREAD pThread;
	memset(&pThread,0,sizeof(pThread));
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	DWORD Address;
	Address = (DWORD)GetItemData(hItem,TL_THREAD_ID);	
	bOK1 = GetThreadInfoByETHREAD((DWORD)Address,&pThread);
	if(bOK1==false)
		return true;

	if(pThread.TrapFrame==0)
		return true;
	pTrapFrame = (PSYSER_KTRAP_FRAME)pThread.TrapFrame;
	Address = (DWORD)&pTrapFrame->Eip;
	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		VIEW_CODE(Value,true);
	return true;
}


bool CThreadListWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{	
	//HANDLE hItem;
	THREADHOTKEYMAP::IT FindIT;

	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return true;
	if(pMsg->KeyEvent.bKeyDown)
	{
		FindIT = m_HotKeyMap.Find(pMsg->KeyEvent.KeyType);
		if(FindIT!=m_HotKeyMap.End())
		{			
			WISP_MSG Msg;
			memset(&Msg,0,sizeof(Msg));
			Msg.Command.CmdID=*FindIT;
			return OnEvent(&Msg);
		}
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_VK_RBUTTON:
			m_PopupMenu.Popup();
			break;
		case WISP_VK_F2:

			break;
		}
	}
	return true;
}


bool CThreadListWnd::OnDestroy(IN WISP_MSG* pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}
bool CThreadListWnd::OnCreate(IN WISP_MSG* pMsg)
{
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,13*16+4));
	InsertColumn(WSTR("TID"),60);
	InsertColumn(WSTR("PID"),60);
	InsertColumn(WSTR("KernelStack"),60);
	//InsertColumn(WSTR("InitialStack"),60);
	//
	//InsertColumn(WSTR("StackLimit"),60);
	InsertColumn(WSTR("ServiceTable"),60);
	InsertColumn(WSTR("StartAddress"),60);
	InsertColumn(WSTR("TrapFrame"),60);
	InsertColumn(WSTR("ESP"),60);
	InsertColumn(WSTR("EIP"),60);
InsertColumn(WSTR("Name"),60);
	AttachShortcutKey();
	m_PopupMenu.CreatePopupMenu(ThreadMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	return true;
}

void	CThreadListWnd::AttachShortcutKey()
{
	if(gpSyser->AttachShortcutKey(EVENT_ID_GOTO_THREAD_STRUCT,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_RETURN,EVENT_ID_GOTO_THREAD_STRUCT);
	if(gpSyser->AttachShortcutKey(EVENT_ID_GOTO_PROCESS_STRUCT,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL | WISP_VK_RETURN,EVENT_ID_GOTO_PROCESS_STRUCT);
	if(gpSyser->AttachShortcutKey(EVENT_ID_GOTO_START_ADDRESS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_RETURN,EVENT_ID_GOTO_START_ADDRESS);
	//if(gpSyser->AttachShortcutKey(EVENT_ID_SHOW_CODE_BY_ADDRESS,m_HotKeyMap)==0)
	//	m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_RETURN,EVENT_ID_SHOW_CODE_BY_ADDRESS);
}

void CThreadListWnd::UpdateContext()
{
#ifdef CODE_OS_NT_DRV	
	SYSER_PROCESS pProcess;
	SYSER_THREAD pThread;
	HANDLE hItem;
	WCHAR Name[17]; 
		WCHAR Name1[17]; 
	DWORD dwCurThread,dwCurProcess;
	bool bOK,bOK1;

	if(GetCurrentProcessAndThread(&dwCurProcess,&dwCurThread)==false)
		return ;
	
	bOK = GetFirstProcess(&pProcess);
	while(bOK)
	{				
		TStrCpyLimit(Name1,pProcess.ImageFileName,16);
		memset(&pThread,0,sizeof(pThread));
		bOK1 = GetThreadInfoByETHREAD((DWORD)pProcess.ThreadHead,&pThread);
		while(bOK1)
		{
			TSPrintf(Name,WSTR("%X"),pThread.ThreadID);
			hItem = InsertItem(Name);
			SetItemData(hItem,TL_THREAD_ID,*(int*)&pThread.OSThread);
			SetItemNum(hItem,TL_PROCESS_ID,*(int*)&pProcess.UniqueProcessId,WSTR("%X"));
			SetItemData(hItem,TL_PROCESS_ID,*(int*)&pProcess.OSProcess);
			
			//SetItemNum(hItem,TL_INITIALSTACK,*(int*)&pThread.InitialStack,WSTR("%08X"));

			SetItemNum(hItem,TL_KERNELSTACK,*(int*)&pThread.KernelStack,WSTR("%08X"));
			SetItemData(hItem,TL_KERNELSTACK,*(int*)&pThread.KernelStack);
			//SetItemNum(hItem,TL_STACKLIMIT,*(int*)&pThread.StackLimit,WSTR("%08X"));
			//SetItemData(hItem,TL_STACKLIMIT,*(int*)&pThread.StackLimit);
			SetItemNum(hItem,TL_SERVICETABLE,*(int*)&pThread.ServiceTable,WSTR("%08X"));
			SetItemData(hItem,TL_SERVICETABLE,*(int*)&pThread.ServiceTable);
			SetItemNum(hItem, TL_STARTADDRESS,*(int*)&pThread.StartAddress,WSTR("%08X"));			
			SetItemData(hItem,TL_STARTADDRESS,*(int*)&pThread.StartAddress);
		
			SetItemNum(hItem, TL_TRAPFRAME,*(int*)&pThread.TrapFrame,WSTR("%08X"));			
			SetItemData(hItem,TL_TRAPFRAME,*(int*)&pThread.TrapFrame);

			DWORD Value,Address;
			PSYSER_KTRAP_FRAME pTrapFrame;
			pTrapFrame = (PSYSER_KTRAP_FRAME)pThread.TrapFrame;
			Address = (DWORD)&pTrapFrame->Eip;
			Value=0;
			gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value));			
			SetItemNum(hItem, TL_EIP,Value,WSTR("%08X"));			
			SetItemData(hItem,TL_EIP,Value);
			
			Address = (DWORD)&pTrapFrame->HardwareEsp;
			Value=0;
			gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value));			
			SetItemNum(hItem, TL_ESP,Value,WSTR("%08X"));			
			SetItemData(hItem,TL_ESP,Value);
			SetItemText(hItem,TL_PROCESS_NAME,Name1);
			
			//SetItemNum(TL_SUSPEND,*(int*)&pThread.KernelStack,WSTR("%08X"));
			bOK1=GetNextThread(&pThread);
		}
		bOK = GetNextProcess(&pProcess);
	}
#endif
}
