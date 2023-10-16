#include "StdAfx.h"
#include "SyserApp.h"
#include "ProcessList.h"
#include "Process.h"

WISP_MSG_MAP_BEGIN(CProcessList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CProcessList)
	WISP_MSG_EVENT_MAP(EVENT_ID_TERMINATE,OnMenuTerminate)
	WISP_MSG_EVENT_MAP(EVENT_ID_REAL_TIME,OnMenuRealTime)
	WISP_MSG_EVENT_MAP(EVENT_ID_HIGH,OnMenuHigh)
	WISP_MSG_EVENT_MAP(EVENT_ID_ABOVE_NORMAL,OnMenuAboveNormal)
	WISP_MSG_EVENT_MAP(EVENT_ID_NORMAL,OnMenuNormal)
	WISP_MSG_EVENT_MAP(EVENT_ID_BELOW_NORMAL,OnMenuBelowNormal)
	WISP_MSG_EVENT_MAP(EVENT_ID_IDLE,OnMenuIdle)
	WISP_MSG_EVENT_MAP(EVENT_ID_EMPTY_WORKING_SET,OnMenuEmptyWorkingSet)
	WISP_MSG_EVENT_MAP(EVENT_ID_DETAIL,OnMenuDetail)
WISP_MSG_EVENT_MAP_END

CProcessList::CProcessList()
{
}

CProcessList::~CProcessList()
{
}

void CProcessList::ItemDBClickNotify(HANDLE hItem,int Col)
{
	WCHAR szPath[MAX_FN_LEN];
	if(GetItemCount(hItem)==0)
	{
		GetItemText(hItem,1).GetFilePath(szPath);
		if(ShellExecuteW(NULL,WSTR("explore"),szPath,NULL,NULL,SW_NORMAL))
			ShowWindow(theApp.m_hLocalWnd,SW_MINIMIZE);
	}
}

bool CProcessList::ItemExpandingNotify(HANDLE hItem)
{
	HANDLE  hModuleSnap,hModItem;
	MODULEENTRY32W me32;
	if(hItem == m_hSystemItem)
		return true;
	ClearChildItem(hItem);
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,(DWORD)GetItemData(hItem));
	if(hModuleSnap == INVALID_HANDLE_VALUE)
		return false;
	me32.dwSize = sizeof(MODULEENTRY32W);
	if(Module32FirstW(hModuleSnap,&me32))
	{
		do
		{
			hModItem = InsertItem(TGetFileName(me32.szModule),hItem);
			SetItemText(hModItem,1,me32.szExePath);
			SetItemNum(hModItem,2,PTR_TO_NUM(me32.modBaseAddr),WSTR("0x%X"));
			SetItemNum(hModItem,3,me32.modBaseSize,WSTR("0x%X"));
		}
		while(Module32NextW(hModuleSnap,&me32)); 
	}
	CloseHandle(hModuleSnap);
	return true;
}


HANDLE CProcessList::GetCurrentSelectProcess(IN DWORD dwDesiredAccess)
{
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL || hItem == m_hSystemItem)
		return NULL;
	HANDLE hProcess = OpenProcess(dwDesiredAccess,FALSE,(DWORD)GetItemData(hItem));
	if(hProcess==NULL)
	{
		m_pWispBase->MsgBox(WSTR("Fail to open process !"),WSTR("Error"),WISP_MB_OK);
		return NULL;
	}
	return hProcess;
}

bool CProcessList::UpdatePriorityClassItem()
{
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL || hItem == m_hSystemItem)
		return false;
	int Level = GetItemLevel(hItem);
	if(IsParentOfItem(m_hSystemItem,hItem))
	{
		if(Level>1)
			return false;
	}
	else if(Level>0)
	{
		return false;
	}
	m_PopupMenu.UncheckItem(m_hRealTimeMenu);
	m_PopupMenu.UncheckItem(m_hHighMenu);
	m_PopupMenu.UncheckItem(m_hAboveNormalMenu);
	m_PopupMenu.UncheckItem(m_hNormalMenu);
	m_PopupMenu.UncheckItem(m_hBelowNormalMenu);
	m_PopupMenu.UncheckItem(m_hIdleMenu);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,(DWORD)GetItemData(hItem));
	if(hProcess==NULL)
		return true;
	DWORD Class = GetPriorityClass(hProcess);
	switch(Class)
	{
	case REALTIME_PRIORITY_CLASS:
		m_PopupMenu.CheckItem(m_hRealTimeMenu);
		break;
	case HIGH_PRIORITY_CLASS:
		m_PopupMenu.CheckItem(m_hHighMenu);
		break;
	case ABOVE_NORMAL_PRIORITY_CLASS:
		m_PopupMenu.CheckItem(m_hAboveNormalMenu);
		break;
	case NORMAL_PRIORITY_CLASS:
		m_PopupMenu.CheckItem(m_hNormalMenu);
		break;
	case BELOW_NORMAL_PRIORITY_CLASS:
		m_PopupMenu.CheckItem(m_hBelowNormalMenu);
		break;
	case IDLE_PRIORITY_CLASS:
		m_PopupMenu.CheckItem(m_hIdleMenu);
		break;
	}
	CloseHandle(hProcess);
	return true;
}

void CProcessList::SetPriorityClass(DWORD Class)
{
	HANDLE hProcess = GetCurrentSelectProcess(PROCESS_SET_INFORMATION);
	if(hProcess==NULL)
		return;
	if(::SetPriorityClass(hProcess,Class)==false)
		m_pWispBase->MsgBox(WSTR("Fail to set process priority class !"),WSTR("Error"),WISP_MB_OK);
	CloseHandle(hProcess);
}

bool CProcessList::OnMenuTerminate(IN WISP_MSG*pMsg)
{
	HANDLE hProcess = GetCurrentSelectProcess(PROCESS_TERMINATE);
	if(hProcess==NULL)
		return true;
	if(TerminateProcess(hProcess,0)==false)
	{
		m_pWispBase->MsgBox(WSTR("Fail to terminate process !"),WSTR("Error"),WISP_MB_OK);
	}
	else
	{
		HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
		if(hItem)
		{
			RemoveItem(hItem);
			Update();
		}
	}
	CloseHandle(hProcess);
	return true;
}

bool CProcessList::OnMenuRealTime(IN WISP_MSG*pMsg)
{
	SetPriorityClass(REALTIME_PRIORITY_CLASS);
	return true;
}

bool CProcessList::OnMenuHigh(IN WISP_MSG*pMsg)
{
	SetPriorityClass(HIGH_PRIORITY_CLASS);
	return true;
}

bool CProcessList::OnMenuAboveNormal(IN WISP_MSG*pMsg)
{
	SetPriorityClass(ABOVE_NORMAL_PRIORITY_CLASS);
	return true;
}

bool CProcessList::OnMenuNormal(IN WISP_MSG*pMsg)
{
	SetPriorityClass(NORMAL_PRIORITY_CLASS);
	return true;
}

bool CProcessList::OnMenuBelowNormal(IN WISP_MSG*pMsg)
{
	SetPriorityClass(BELOW_NORMAL_PRIORITY_CLASS);
	return true;
}

bool CProcessList::OnMenuIdle(IN WISP_MSG*pMsg)
{
	SetPriorityClass(IDLE_PRIORITY_CLASS);
	return true;
}

bool CProcessList::OnMenuEmptyWorkingSet(IN WISP_MSG*pMsg)
{
	HANDLE hProcess = GetCurrentSelectProcess(PROCESS_ALL_ACCESS);
	if(hProcess==NULL)
		return true;
	if(EmptyWorkingSet(hProcess)==false)
		m_pWispBase->MsgBox(WSTR("Fail to Release Process Working Pages !"),WSTR("Error"),WISP_MB_OK);
	CloseHandle(hProcess);
	return true;
}

bool CProcessList::OnMenuDetail(IN WISP_MSG*pMsg)
{
	return true;
}

bool CProcessList::OnCreate(IN WISP_MSG*pMsg)
{
	m_PopupMenu.CreatePopupMenu(ProcessPopupMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_hRealTimeMenu = m_PopupMenu.GetItem(EVENT_ID_REAL_TIME);
	m_hHighMenu = m_PopupMenu.GetItem(EVENT_ID_HIGH);
	m_hAboveNormalMenu = m_PopupMenu.GetItem(EVENT_ID_ABOVE_NORMAL);
	m_hNormalMenu = m_PopupMenu.GetItem(EVENT_ID_NORMAL);
	m_hBelowNormalMenu = m_PopupMenu.GetItem(EVENT_ID_BELOW_NORMAL);
	m_hIdleMenu = m_PopupMenu.GetItem(EVENT_ID_IDLE);
	InsertColumn(WISP_STR("Name"),150);
	InsertColumn(WISP_STR("User Name"),80);
	InsertColumn(WISP_STR("ID"),60);
	InsertColumn(WISP_STR("Memory Used"),85);
	m_hSystemItem = InsertItem(WSTR("System Process List"));
	SetItemText(m_hSystemItem,1,WSTR("SYSTEM"));
	SetItemTextColor(m_hSystemItem,0,SYS_COLOR[SC_LIGHT_BLUE]);
	SetItemTextColor(m_hSystemItem,1,SYS_COLOR[SC_LIGHT_BLUE]);
	SetItemTextColor(m_hSystemItem,3,SYS_COLOR[SC_LIGHT_BLUE]);
	ListOSProcess();
	return true;
}

bool CProcessList::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CProcessList::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.bKeyDown == false && (pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON || pMsg->KeyEvent.KeyType == WISP_VK_APPS))
	{
		if(UpdatePriorityClassItem())
			m_PopupMenu.Popup(NULL,pMsg->KeyEvent.KeyType == WISP_VK_APPS);
	}
	return true;
}

bool CProcessList::ListOSProcess()
{
	SIZE_T SystemTotalSize;
	WCHAR szBuffer[MAX_FN_LEN];
	HANDLE hProcess;
	HANDLE hSystemItem,hUserItem,hParentItem,hItem;
	PROCESS_MEMORY_COUNTERS mc;
	PROCESSENTRY32W pe32;

	LockUpdate();
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
		return false;
	int UserCount,SystemCount;

	UserCount=SystemCount=0;
	hSystemItem = GetItem(0,m_hSystemItem);
	hUserItem = GetNextItem(m_hSystemItem);
	SystemTotalSize = 0;
	pe32.dwSize = sizeof(PROCESSENTRY32W);
	if(Process32FirstW(hProcessSnap,&pe32))
	{
		do
		{
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,pe32.th32ProcessID);
			CProcess::GetProcessUser(hProcess,szBuffer,MAX_FN_LEN);
			if(*szBuffer==0)
				TStrCpy(szBuffer,WSTR("SYSTEM"));
			if(TStrCmp(szBuffer,WSTR("SYSTEM")))
			{
				hParentItem = NULL;
				hItem = hUserItem;
				UserCount++;
			}
			else
			{
				hParentItem = m_hSystemItem;
				hItem = hSystemItem;
				SystemCount++;
			}
			if(hItem)
				SetItemText(hItem,0,TGetFileName(pe32.szExeFile));
			else
			{
				hItem = InsertItem(TGetFileName(pe32.szExeFile),hParentItem);
				InsertItem(WSTR("..."),hItem);
			}
			STZeroMemory(mc);
			GetProcessMemoryInfo(hProcess,&mc,sizeof(mc));
			SetItemData(hItem,0,pe32.th32ProcessID);
			SetItemText(hItem,1,szBuffer);
			SetItemNum(hItem,2,pe32.th32ProcessID,WSTR("0x%X"));
			SetItemNum(hItem,3,(UINT)((mc.WorkingSetSize+0x3FF)/0x400),WSTR("%10d K"));
			if(hParentItem)
			{
				hSystemItem = GetNextItem(hItem);
				SystemTotalSize+=mc.WorkingSetSize;
				if(GetItemCell(hItem)->FontColor!=SYS_COLOR[SC_LIGHT_BLUE])
				{
					for(int n=0;n<m_ColumnList.Count();n++)
						SetItemTextColor(hItem,n,SYS_COLOR[SC_LIGHT_BLUE]);
				}
			}
			else
				hUserItem = GetNextItem(hItem);
			CloseHandle(hProcess);
		}while(Process32NextW(hProcessSnap, &pe32));
	}
	CloseHandle(hProcessSnap);
	SetItemChildCount(NULL,UserCount+1);
	SetItemChildCount(m_hSystemItem,SystemCount);
	SetItemNum(m_hSystemItem,3,(UINT)((SystemTotalSize+0x3FF)/0x400),WSTR("%10d K"));
	m_pWispBase->LeaveCriticalSection();
	UnlockUpdate();
	Update();
	if(theApp.m_bMsgSleeping)
		theApp.WakeUpMsgThread();
	return true;
}
