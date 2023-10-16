#include "StdAfx.h"
#include "ProcessList.h"
#include "Syser.h"

WISP_MSG_MAP_BEGIN(CProcessList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispList)

CProcessList::CProcessList()
{
}

CProcessList::~CProcessList()
{
}

void CProcessList::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WISP_STR("Processes"),CWispRect(0,0,500,350),NULL,0,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WS_NORMAL);
		Center();
	}
}

bool CProcessList::OnCreate(IN WISP_MSG*pMsg)
{
	AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,15));
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	m_Style|=WISP_WLS_EMPTY_SEL_RECT;
	InsertColumn(WISP_STR("Name"),200);
	InsertColumn(WISP_STR("ID"),80);
#ifdef CODE_OS_NT_DRV
	InsertColumn(WISP_STR("CR3"),80);
	InsertColumn(WISP_STR("PEB"),80);
	InsertColumn(WISP_STR("EPROCESS"),80);
#else
	InsertColumn(WISP_STR("User Name"),80);
#endif
	UpdateContext();
	return true;
}

bool CProcessList::OnClose(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

void CProcessList::UpdateContext()
{
#ifdef CODE_OS_NT_DRV
	HANDLE hItem;
	WCHAR szBuffer[128];
	ClearChildItem();
	for(CProcMap::IT Iter=gpSyser->m_SysInfo.m_ProcMap.Begin();Iter!=gpSyser->m_SysInfo.m_ProcMap.End();Iter++)
	{
		
		hItem = InsertItem((PWSTR)Iter->m_ProcNameW);
		TSPrintf(szBuffer,WSTR("%04X"),Iter->m_PID);
		SetItemText(hItem,1,szBuffer);
		TSPrintf(szBuffer,WSTR("%08X"),Iter->m_CR3);
		SetItemText(hItem,2,szBuffer);
		SetItemData(hItem,0,(NUM_PTR)&(*Iter));
		TSPrintf(szBuffer,WSTR("%08X"),Iter->m_pCurrentPEB);
		SetItemText(hItem,3,szBuffer);
		TSPrintf(szBuffer,WSTR("%08X"),Iter->m_PEProcess);
		SetItemText(hItem,4,szBuffer);
	}
#else
	ClearChildItem();
	m_hSystemItem = InsertItem(WSTR("System Process List"));
	SetItemText(m_hSystemItem,1,WSTR("SYSTEM"));
	ListOSProcess();
#endif
}

#ifdef CODE_OS_WIN

bool GetProcessUser(HANDLE hProcess, WCHAR*szUserName,int MaxLen)
{
	SID_NAME_USE sn;
	WCHAR szDomainName[MAX_FN_LEN];
	DWORD Length,NameLen;
	bool Result;
	HANDLE hToken;
	TOKEN_USER*pTokenUser;
	*szUserName=0;
	if(OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)==FALSE)
	{
		return false;
	}
	Length=0;
	GetTokenInformation(hToken,TokenUser, NULL, 0, &Length);
	if(Length==0)
	{
		CloseHandle(hToken);
		return false;
	}
	pTokenUser = (TOKEN_USER*)new BYTE[Length];
	if(GetTokenInformation(hToken,TokenUser,pTokenUser,Length,&Length)==false)
	{
		delete pTokenUser;
		CloseHandle(hToken);
		return false;
	}
	Length = MAX_FN_LEN;
	NameLen = MaxLen;
	Result = LookupAccountSidW(NULL,pTokenUser->User.Sid,szUserName,&NameLen,szDomainName,&Length,&sn)!=FALSE;
	delete pTokenUser;
	CloseHandle(hToken);
	return Result;
}

bool CProcessList::ListOSProcess()
{
	WCHAR szBuffer[MAX_FN_LEN];
	HANDLE hProcess;
	HANDLE hSystemItem,hUserItem,hParentItem,hItem;
	PROCESS_MEMORY_COUNTERS mc;
	PROCESSENTRY32W pe32;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
		return false;
	int UserCount,SystemCount;

	UserCount=SystemCount=0;
	hSystemItem = GetItem(0,m_hSystemItem);
	hUserItem = GetNextItem(m_hSystemItem);
	pe32.dwSize = sizeof(PROCESSENTRY32W);
	if(Process32FirstW(hProcessSnap,&pe32))
	{
		do
		{
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,pe32.th32ProcessID);
			GetProcessUser(hProcess,szBuffer,MAX_FN_LEN);
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
			hItem = InsertItem(TGetFileName(pe32.szExeFile),hParentItem);
			STZeroMemory(mc);
			GetProcessMemoryInfo(hProcess,&mc,sizeof(mc));
			SetItemData(hItem,0,pe32.th32ProcessID);
			SetItemNum(hItem,1,pe32.th32ProcessID,WSTR("0x%X"));
			SetItemText(hItem,2,szBuffer);
			if(hParentItem)
				hSystemItem = GetNextItem(hItem);
			else
				hUserItem = GetNextItem(hItem);
			CloseHandle(hProcess);
		}while(Process32NextW(hProcessSnap, &pe32));
	}
	CloseHandle(hProcessSnap);
	SetItemChildCount(NULL,UserCount+1);
	SetItemChildCount(m_hSystemItem,SystemCount);
	return true;
}

#endif

bool CProcessList::OnKeyEvent(IN WISP_MSG*pMsg)
{

	return true;
}

#ifdef CODE_OS_WIN

void CProcessList::ItemClickNotify(HANDLE hItem,int Col)
{
	WCHAR szItem[256],szCmd[256];
	if(hItem == m_hSystemItem)
	{
		return;
	}
	GetItemText(hItem,1,szItem,256);
	if(szItem[0]!='0'||szItem[1]!='x')
	{
		return;
	}

	RUNCMD(WSTR("close"));
	TSPrintf(szCmd,WSTR("open \\PID:%s"),&szItem[2]);
	RUNCMD(szCmd);
	Destroy();
}

#endif