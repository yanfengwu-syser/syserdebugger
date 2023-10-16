#include "StdAfx.h"
#include "Syser.h"
#include "HwndWnd.h"
#include "HwndCmd.h"
#include "OSProcessThread.h"

WISP_MSG_MAP_BEGIN(CHwndProcessAndThread)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnClientUpdate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CHwndProcessAndThread)

WISP_MSG_EVENT_MAP_END
bool CHwndProcessAndThread::OnCreate(WISP_MSG*pMsg)
{
	return true;
}
void CHwndProcessAndThread::UpdateContext()
{
	
}

bool CHwndProcessAndThread::OnClientUpdate(WISP_MSG*pMsg)
{
	CWispWnd::OnUpdateClient(pMsg);
	WISP_RECT rc;
	WCHAR Name[10];
	DWORD dwAddress;
	SYSER_THREAD Thread;
	SYSER_PROCESS Process;
	rc.x=12;
	rc.y=12;
	rc.cx=80;
	rc.cy=16;
	m_ClientDC.DrawString(WSTR("Process ID:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	m_ClientDC.DrawString(WSTR("Thread ID:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	PSYSER_HWND_INFO pHwndInfo=pForm->GetHwndInfo();
	rc.y-=20;
	rc.x+=200;
	TSPrintf(Name,WSTR("%08x"),pHwndInfo->Thread);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	if(ReadDword(*(void**)&pHwndInfo->Thread,&dwAddress)==false)
		return false;
	if(GetThreadInfoByETHREAD((DWORD)dwAddress,&Thread)==false)
		return false;
	if(GetProcessInfoByEPROCESS((DWORD)Thread.Process,&Process)==false)
		return false;
	rc.x-=100;
	TSPrintf(Name,WSTR("%08x"),Process.UniqueProcessId);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	TSPrintf(Name,WSTR("%08x"),Thread.ThreadID);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	return false;
}

enum _CHILD_WND_ID
{
CMD_ID_NEXTHWND=WISP_ID_USER_START,
CMD_ID_PREVIOUSHWND,
CMD_ID_PARENTHWND,
CMD_ID_CHILDHWND,
CMD_ID_OWNERHWND,
};


WISP_MSG_MAP_BEGIN(CHwndClassWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnClientUpdate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CHwndClassWnd)

WISP_MSG_EVENT_MAP_END

bool CHwndClassWnd::OnCreate(WISP_MSG*pMsg)
{

	return true;
}
void CHwndClassWnd::UpdateContext()
{

}

bool CHwndClassWnd::OnClientUpdate(WISP_MSG*pMsg)
{
	WISP_RECT rc;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	PSYSER_HWND_CLASS_INFO pHwndClassInfo=pForm->GetHwndClassInfo();
	DWORD dwLen;
	WCHAR Name[256];
	CWispWnd::OnUpdateClient(pMsg);
	int m;
	rc.x=12;
	rc.y=12;
	rc.cx=80;
	rc.cy=16;
	m_ClientDC.DrawString(WSTR("Class Name:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Class Style:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Class Bytes:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Class Atom:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Window Bytes:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Menu Name:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Icon Handle:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Cursor:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;	
	m_ClientDC.DrawString(WSTR("Bkgnd Brush:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.x=175;
	rc.y=80;
	rc.cx=180;
	rc.cy=16;
	m_ClientDC.DrawString(WSTR("Instance Handle:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=20;
	m_ClientDC.DrawString(WSTR("Window Proc:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.x=95;
	rc.y=12;
	rc.cx=80;
	rc.cy=16;
	rc.y+=19;
	TSPrintf(Name,WSTR("%08x"),pHwndClassInfo->style);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=19;
	TSPrintf(Name,WSTR("%d"),pHwndClassInfo->cbClsExtra);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;
	rc.y+=19;
	TSPrintf(Name,WSTR("%d"),pHwndClassInfo->cbWndExtra);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;
	TSPrintf(Name,WSTR("(None)"));
	if(pHwndClassInfo->IconHandle)
	{
		if(ReadDword(*(void**)&pHwndClassInfo->IconHandle,&dwLen))
			TSPrintf(Name,WSTR("%08x"),dwLen);
	}
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;
	TSPrintf(Name,WSTR("(None)"));
	if(pHwndClassInfo->hCursor)
	{
		if(ReadDword(*(void**)&pHwndClassInfo->hCursor,&dwLen))
		{
			TSPrintf(Name,WSTR("%08x"),dwLen);
			for(m =0;m<sizeof(gOSPredefineCursor)/sizeof(gOSPredefineCursor[0]);m++)
			{
				if(gOSPredefineCursor[m].Value==dwLen)
				{
					TSPrintf(Name,WSTR("%s"),gOSPredefineCursor[m].Name);
					break;
				}
			}			
		}
	}
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=19;
	TSPrintf(Name,WSTR("(None)"));
	if(pHwndClassInfo->hbrBackground)
	{
		if(ReadDword(*(void**)&pHwndClassInfo->hbrBackground,&dwLen))
		{
			TSPrintf(Name,WSTR("%08x"),dwLen);
			for(m =0;m<sizeof(gOSPredefineColor)/sizeof(gOSPredefineColor[0]);m++)
			{
				if(gOSPredefineColor[m].Value==dwLen)
				{
					TSPrintf(Name,WSTR("%s"),gOSPredefineColor[m].Name);
					break;
				}
			}			
		}
	}
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	return false;
}

CHwndStyleWnd::CHwndStyleWnd()
{

}
CHwndStyleWnd::~CHwndStyleWnd()
{

}

WISP_MSG_MAP_BEGIN(CHwndStyleWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)

WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CHwndStyleWnd)

WISP_MSG_EVENT_MAP_END
bool CHwndStyleWnd::OnCreate(WISP_MSG*pMsg)
{
	m_StyleList.Create(WSTR(""),12,25,345,65,this,CMD_ID_MODULE_LIST_WND,WISP_WLS_SELECTED_ALWAYS|WISP_WS_THIN_BORDER);
	m_StyleList.InsertColumn(NULL,340);
	m_StyleExList.Create(WSTR(""),12,110,345,65,this,CMD_ID_MODULE_LIST_WND,WISP_WLS_SELECTED_ALWAYS|WISP_WS_THIN_BORDER);
	m_StyleList.InsertColumn(NULL,340);
	m_StyleStr.Create(WSTR(""),12,8,170,16,this);
	m_StyleExStr.Create(WSTR(""),12,93,170,16,this);
	UpdateContext();
	return true;
}

void CHwndStyleWnd::UpdateContext()
{
	WCHAR Buffer[128];
	int i;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	PSYSER_HWND_INFO pHwndInfo=pForm->GetHwndInfo();
	m_StyleExList.ClearChildItem();
	DWORD Value=pHwndInfo->StyleEx;
	OUTPUT(WSTR("offset %d %d %08x [%08x] [%08x]\n"),(BYTE*)&pHwndInfo->StyleEx-(BYTE*)pHwndInfo, (BYTE*)&pHwndInfo->Style-(BYTE*)pHwndInfo,pHwndInfo,pHwndInfo->Style,pHwndInfo->StyleEx);
	OUTPUT(WSTR("sizeof(gWndStyleExInfo)/sizeof(gWndStyleExInfo[0])=%d %08x %08x\n"),sizeof(gWndStyleExInfo)/sizeof(gWndStyleExInfo[0]),pHwndInfo->StyleEx,pHwndInfo->Style);
	for(i =0;i<sizeof(gWndStyleExInfo)/sizeof(gWndStyleExInfo[0]);i++)
	{
		if(Value & gWndStyleExInfo[i].Value)
		{
			m_StyleExList.InsertItem(gWndStyleExInfo[i].Name);
			Value&=~(gWndStyleExInfo[i].Value);
		}
		else
		{
			OUTPUT(WSTR("%08x & %08x\n"),Value,gWndStyleExInfo[i].Value);
		}
	}
	TStrCat(Buffer,Value&WS_EX_LEFTSCROLLBAR?"WS_EX_LEFTSCROLLBAR":"WS_EX_RIGHTSCROLLBAR");
	m_StyleExList.InsertItem(Buffer);
	TStrCat(Buffer,Value&WS_EX_RTLREADING?"WS_EX_RTLREADING":"WS_EX_LTRREADING");	
	m_StyleExList.InsertItem(Buffer);
	TStrCat(Buffer,Value&WS_EX_RIGHT?"WS_EX_RIGHT":"WS_EX_LEFT");
	m_StyleExList.InsertItem(Buffer);
	if(Value)
	{
		TSPrintf(Buffer,WSTR("0x%08x"),Value);
		m_StyleExList.InsertItem(Buffer);
	}
	OUTPUT(WSTR("sizeof(gWndStyleInfo)/sizeof(gWndStyleInfo[0])=%d\n"),sizeof(gWndStyleInfo)/sizeof(gWndStyleInfo[0]));
	m_StyleList.ClearChildItem();
	Value=pHwndInfo->Style;
	for(i =0;i<sizeof(gWndStyleInfo)/sizeof(gWndStyleInfo[0]);i++)
	{
		if(Value & gWndStyleInfo[i].Value)
		{
			m_StyleList.InsertItem(gWndStyleInfo[i].Name);			
			Value&=~(gWndStyleInfo[i].Value);
		}
	}
	if(Value)
	{
		TSPrintf(Buffer,WSTR("0x%08x"),Value);
		m_StyleList.InsertItem(Buffer);
	}
	TSPrintf(Buffer,WSTR("Window Styles:      %08x"),pHwndInfo->Style);
	m_StyleStr.SetWindowText(Buffer);
	TSPrintf(Buffer,WSTR("Extended Styles:    %08x"),pHwndInfo->StyleEx);
	m_StyleExStr.SetWindowText(Buffer);
}
CHwndOtherWnd::CHwndOtherWnd()
{

}
CHwndOtherWnd::~CHwndOtherWnd()
{

}

WISP_MSG_MAP_BEGIN(CHwndOtherWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnClientUpdate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CHwndOtherWnd)

WISP_MSG_EVENT_MAP_END

WISP_MSG_CMD_MAP_BEGIN(CHwndOtherWnd)
WISP_MSG_CMD_MAP(CMD_ID_NEXTHWND,OnGotoNextHwnd)
WISP_MSG_CMD_MAP(CMD_ID_PREVIOUSHWND,OnGotoPreviousHwnd)
WISP_MSG_CMD_MAP(CMD_ID_PARENTHWND,OnGotoParentHwnd)
WISP_MSG_CMD_MAP(CMD_ID_CHILDHWND,OnGotoChildHwnd)
WISP_MSG_CMD_MAP(CMD_ID_OWNERHWND,OnGotoOwnerHwnd)
WISP_MSG_CMD_MAP_END

bool CHwndOtherWnd::OnGotoNextHwnd(IN WISP_MSG*pMsg)
{
	OUTPUT(WSTR("Clicked Next Hwnd %08x\n"),m_NextHwnd);
	if(m_NextHwnd==0)
		return true;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	pForm->UpdateContext(m_NextHwnd);	
	return false;
}
bool CHwndOtherWnd::OnGotoPreviousHwnd(IN WISP_MSG*pMsg)
{
	if(m_PreviousHwnd==0)
		return true;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	pForm->UpdateContext(m_PreviousHwnd);	
	return true;
}
bool CHwndOtherWnd::OnGotoParentHwnd(IN WISP_MSG*pMsg)
{
	if(m_ParentHwnd==0)
		return true;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	pForm->UpdateContext(m_ParentHwnd);	
	return true;
}
bool CHwndOtherWnd::OnGotoChildHwnd(IN WISP_MSG*pMsg)
{
	if(m_FirstChildHwnd==0)
		return true;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	pForm->UpdateContext(m_FirstChildHwnd);	
	return true;
}
bool CHwndOtherWnd::OnGotoOwnerHwnd(IN WISP_MSG*pMsg)
{
	if(m_OwnerWnd==0)
		return true;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	pForm->UpdateContext(m_OwnerHwnd);	
	return true;
}
bool CHwndOtherWnd::OnCreate(WISP_MSG*pMsg)
{
	WISP_RECT rc={12,12,344,30},rc2={56,25,74,12};
	m_NextGroup.Create(WSTR("Next Window"),&rc,this);
	rc.y+=32;
	m_PreviousGroup.Create(WSTR("Previous Window"),&rc,this);
	rc.y+=32;
	m_ParentGroup.Create(WSTR("Parent Window"),&rc,this);
	rc.y+=32;
	m_FirstChildGroup.Create(WSTR("First Child Window"),&rc,this);
	rc.y+=32;
	m_OnwerGroup.Create(WSTR("Owner Window"),&rc,this);	
	
	m_NextURL.Create(NULL,&rc2,this,CMD_ID_NEXTHWND);
	rc2.y+=32;
	m_PreviousURL.Create(NULL,&rc2,this,CMD_ID_PREVIOUSHWND);	
	rc2.y+=32;
	m_ParentURL.Create(NULL,&rc2,this,CMD_ID_PARENTHWND);
	rc2.y+=32;
	m_FirstChildURL.Create(NULL,&rc2,this,CMD_ID_CHILDHWND);
	rc2.y+=32;
	m_OwnerURL.Create(NULL,&rc2,this,CMD_ID_OWNERHWND);

	return true;
}
bool CHwndOtherWnd::OnClientUpdate(WISP_MSG*pMsg)
{
	CWispWnd::OnUpdateClient(pMsg);
	WCHAR Name[10]=WSTR("Handle:"),Catpion[10]=WSTR("Caption ");
	WISP_RECT rc={15,25,40,12},rc2={138,25,214,12};	
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	m_ClientDC.DrawString(Catpion,&rc2,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=32;rc2.y+=32;
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	m_ClientDC.DrawString(Catpion,&rc2,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=32;rc2.y+=32;
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	m_ClientDC.DrawString(Catpion,&rc2,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=32;rc2.y+=32;
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	m_ClientDC.DrawString(Catpion,&rc2,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=32;rc2.y+=32;
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	m_ClientDC.DrawString(Catpion,&rc2,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	return false;
}

void CHwndOtherWnd::UpdateContext()
{
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	PSYSER_HWND_INFO pHwndInfo=pForm->GetHwndInfo();
	WCHAR Name[20],NullName[]=WSTR("NULL");
	DWORD dwAddress;
	m_NextHwnd=0;
	m_PreviousHwnd=0;
	m_ParentHwnd=0;
	m_FirstChildHwnd=0;
	m_OwnerHwnd=0;
	if(pHwndInfo->NextHwnd && ReadDword(pHwndInfo->NextHwnd,&dwAddress))
	{
		TSPrintf(Name,WSTR("%08X"),dwAddress);
		m_NextURL.SetWindowText(Name);
		m_NextHwnd=*(DWORD*)&pHwndInfo->NextHwnd;
	}
	else
		m_NextURL.SetWindowText(NullName);
	if(pHwndInfo->PreviousHwnd && ReadDword(pHwndInfo->PreviousHwnd,&dwAddress))
	{
		TSPrintf(Name,WSTR("%08X"),dwAddress);
		m_PreviousURL.SetWindowText(Name);
		m_PreviousHwnd=*(DWORD*)&pHwndInfo->PreviousHwnd;		
	}
	else
		m_PreviousURL.SetWindowText(NullName);
	if(pHwndInfo->ChildHwnd && ReadDword(pHwndInfo->ChildHwnd,&dwAddress))
	{
		TSPrintf(Name,WSTR("%08X"),dwAddress);
		m_FirstChildURL.SetWindowText(Name);
		m_FirstChildHwnd=*(DWORD*)&pHwndInfo->ChildHwnd;
	}
	else
		m_FirstChildURL.SetWindowText(NullName);
	if(pHwndInfo->ParentHwnd && ReadDword(pHwndInfo->ParentHwnd,&dwAddress))
	{
		TSPrintf(Name,WSTR("%08X"),dwAddress);
		m_ParentURL.SetWindowText(Name);
		m_ParentHwnd=*(DWORD*)&pHwndInfo->ParentHwnd;
	}
	else
		m_ParentURL.SetWindowText(NullName);
	if(pHwndInfo->OwnerHwnd && ReadDword(pHwndInfo->OwnerHwnd,&dwAddress))
	{
		TSPrintf(Name,WSTR("%08X"),dwAddress);
		m_OwnerURL.SetWindowText(Name);
		m_OwnerHwnd=*(DWORD*)&pHwndInfo->OwnerHwnd;
	}
	else
		m_OwnerURL.SetWindowText(NullName);
}

CHwndGeneralWnd::CHwndGeneralWnd()
{

}
CHwndGeneralWnd::~CHwndGeneralWnd()
{

}

WISP_MSG_MAP_BEGIN(CHwndGeneralWnd)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnClientUpdate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CHwndGeneralWnd)

WISP_MSG_EVENT_MAP_END
bool CHwndGeneralWnd::OnCreate(WISP_MSG*pMsg)
{
	
	return true;
}
void CHwndGeneralWnd::UpdateContext()
{

}
bool CHwndGeneralWnd::OnClientUpdate(WISP_MSG*pMsg)
{
	WISP_RECT rc;
	CHwndPropertyForm* pForm=(CHwndPropertyForm*)m_OwnerWnd;
	PSYSER_HWND_INFO pHwndInfo=pForm->GetHwndInfo();
	DWORD dwLen;
	WCHAR Name[256];
	CWispWnd::OnUpdateClient(pMsg);
	rc.x=12;
	rc.y=6;
	rc.cx=180;
	rc.cy=16;
	m_ClientDC.DrawString(WSTR("Window Caption:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;	
	m_ClientDC.DrawString(WSTR("Window Handle:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=20;	
	m_ClientDC.DrawString(WSTR("Window Proc:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=20;	
	m_ClientDC.DrawString(WSTR("Window Rectangle:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=20;	
	m_ClientDC.DrawString(WSTR("Client Rectangle:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=20;	
	m_ClientDC.DrawString(WSTR("Instance Handle:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=20;	
	m_ClientDC.DrawString(WSTR("Menu Handle:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.y+=20;	
	m_ClientDC.DrawString(WSTR("User Data:"),&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);
	rc.x=140;
	rc.y=6;
	rc.cx=180;
	rc.cy=16;
	if(pHwndInfo->WindowCaptionLen && pHwndInfo->WindowCaptionBuffer)
	{		
		dwLen=pHwndInfo->WindowCaptionLen;
		if(pHwndInfo->WindowCaptionLen>sizeof(Name))
			dwLen=sizeof(Name)-2;
		SafeMemCopy((BYTE*)Name,*(BYTE**)&pHwndInfo->WindowCaptionBuffer,dwLen);	
		Name[dwLen/sizeof(WCHAR)]=0;
		m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);			
	}
	rc.y+=20;
	TSPrintf(Name,WSTR("%08x"),pHwndInfo->hWnd);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	TSPrintf(Name,WSTR("%08x"),pHwndInfo->WndProc);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	TSPrintf(Name,WSTR("(%d, %d)-(%d, %d), %dx%d"),
		pHwndInfo->WndLeft,
		pHwndInfo->WndTop,
		pHwndInfo->WndRight,
		pHwndInfo->WndBottom,
		pHwndInfo->WndRight-pHwndInfo->WndLeft,
		pHwndInfo->WndBottom-pHwndInfo->WndTop);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	TSPrintf(Name,WSTR("(%d, %d)-(%d, %d), %dx%d"),
		pHwndInfo->CliLeft-pHwndInfo->WndLeft,
		pHwndInfo->CliTop-pHwndInfo->WndTop,
		pHwndInfo->CliRight-pHwndInfo->WndRight,
		pHwndInfo->CliBottom-pHwndInfo->WndBottom,
		pHwndInfo->CliRight-pHwndInfo->CliLeft,
		pHwndInfo->CliBottom-pHwndInfo->CliTop);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	TSPrintf(Name,WSTR("%08x"),pHwndInfo->InstanceHandle);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	Name[0]=0;
	if(pHwndInfo->Style&WS_CHILD) 
		TSPrintf(Name,WSTR("%08x"),pHwndInfo->ControlID);
	else
	{
		dwLen=pHwndInfo->Menu;
		if(pHwndInfo->Menu)
		{
			ReadDword(*(void**)&pHwndInfo->Menu,&dwLen);							
		}		
		TSPrintf(Name,WSTR("%08x"),dwLen);
	}
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	rc.y+=20;
	TSPrintf(Name,WSTR("%08x"),pHwndInfo->UserData);
	m_ClientDC.DrawString(Name,&rc,WISP_DT_VCENTER|WISP_DT_SINGLELINE);	
	return false;
}



enum CHwndPropertyForm::WISP_FORM_ID
{	
	CMD_ID_BT_EDIT = WISP_ID_USER_START,
	CMD_ID_MAIN_TAB,
	CMD_ID_COMBOBOX_MODULE,
	CMD_ID_WND_PE_HEADER,	
	CMD_ID_WND_RELOCATIONS,
	CMD_ID_WND_IMPORT,
	CMD_ID_WND_EXPORT,
	CMD_ID_BP_DATA_LIST,
};

WISP_FORM_RES_ITEM CHwndPropertyForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,386,268},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("PE Explorer"),
		"\\SyserIcon\\Syser.ico",
	},
	
	{
		WISP_CTRL_TAB,
		{6,6,368,206},
		CMD_ID_MAIN_TAB,
		WISP_WS_THIN_BORDER,
		NULL,
	},		
	{WISP_CTRL_NULL}
};


WISP_MSG_MAP_BEGIN(CHwndPropertyForm)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CHwndPropertyForm)
WISP_MSG_CMD_MAP(CMD_ID_COMBOBOX_MODULE,OnModuleSelectComboxCmd)
WISP_MSG_CMD_MAP(CMD_ID_MAIN_TAB,OnTabActiveChange)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CHwndPropertyForm)


WISP_MSG_EVENT_MAP_END

CHwndPropertyForm::CHwndPropertyForm()
{
	m_pFormRes = m_FormRes;	
	m_pMainTab=NULL;
	memset(&m_HwndInfo,0,sizeof(m_HwndInfo));
}
bool CHwndPropertyForm::OnTabActiveChange(IN WISP_MSG* pMsg)
{
	if(pMsg->Command.CmdMsg==WISP_CMD_TAB_ACTIVE_CHG)
	{
		if(pMsg->Command.Param1==1)
			m_pStyleWnd->UpdateContext();
	}
	
	return  true;

}

CHwndPropertyForm::~CHwndPropertyForm()
{

}
void CHwndPropertyForm::UpdateContext(DWORD ModuleBase)
{
	m_HwndInfoAddress=ModuleBase;
	memset(&m_HwndInfo,0,sizeof(m_HwndInfo));
	if(!IsWindow())
		return;
	GetHwndInfoByWndStruct(*(void**)&ModuleBase,&m_HwndInfo);
	m_pGeneralWnd->UpdateContext();
	m_pStyleWnd->UpdateContext();	
	m_pOtherWnd->UpdateContext();
	m_pClassWnd->UpdateContext();
}



void CHwndPropertyForm::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
	{
		CreateForm(NULL);
	}
}
bool CHwndPropertyForm::OnModuleSelectComboxCmd(IN WISP_MSG* pMsg)
{

	return true;
}

bool CHwndPropertyForm::OnFormCreate(WISP_MSG*pMsg)
{
	m_pMainTab = (CWispTabWnd*) GetFormItem(CMD_ID_MAIN_TAB);
	m_pGeneralWnd=new CHwndGeneralWnd;	
	m_pGeneralWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_PE_HEADER,WISP_WS_NULL);
	m_pGeneralWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("General"),m_pGeneralWnd);
	m_pGeneralWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	m_pStyleWnd=new CHwndStyleWnd;
	m_pStyleWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_PE_HEADER,WISP_WS_NULL);
	m_pStyleWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Style"),m_pStyleWnd);
	m_pStyleWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	m_pOtherWnd = new CHwndOtherWnd;
	m_pOtherWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_PE_HEADER,WISP_WS_NULL);
	m_pOtherWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Windows"),m_pOtherWnd);
	m_pOtherWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	m_pClassWnd = new CHwndClassWnd;
	m_pClassWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_PE_HEADER,WISP_WS_NULL);
	m_pClassWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Class"),m_pClassWnd);
	m_pClassWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	
	m_pProcessAndThread = new CHwndProcessAndThread;
	m_pProcessAndThread->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_PE_HEADER,WISP_WS_NULL);
	m_pProcessAndThread->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Process"),m_pProcessAndThread);
	m_pProcessAndThread->AddAdvStyle(WISP_WAS_AUTO_DELETE);

	return true;
}


WISP_MSG_MAP_BEGIN(CHwndListWnd) 
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CHwndListWnd)
WISP_MSG_EVENT_MAP(EVENT_ID_GOTO,OnEventGoto)
WISP_MSG_EVENT_MAP(EVENT_ID_PE_EXPLORER,OnEventPEExplorer)
WISP_MSG_EVENT_MAP_END

WISP_MENU_RES_ITEM HwndListMenu[]=
{
	{WSTR("Goto"),EVENT_ID_GOTO,8,WISP_MIS_NORMAL},
	{WSTR("Properties"),EVENT_ID_PE_EXPLORER,14,WISP_MIS_NORMAL},
	WISP_MENU_RES_END
};

CHwndListWnd::CHwndListWnd()
{
	
}

CHwndListWnd::~CHwndListWnd()
{

}

void CHwndListWnd::ItemClickNotify(HANDLE hItem,int Col)
{
	
}

bool CHwndListWnd::OnCreate(IN WISP_MSG* pMsg)
{
	AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,13*16+12));
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	m_Style|=WISP_WLS_EMPTY_SEL_RECT;
	m_PopupMenu.CreatePopupMenu(HwndListMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	InsertColumn(WSTR("HWND"),60);
	InsertColumn(WSTR("Name"),200);
	InsertColumn(WSTR("Class Name"),200);
	
	UpdateContext(NULL,GetWindowHwndHead());
	return true;
}

bool CHwndListWnd::OnClose(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

bool CHwndListWnd::OnDestroy(IN WISP_MSG* pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CHwndListWnd::OnKeyEvent(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	if(pMsg->KeyEvent.bKeyDown && pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
	{
		hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
		if(hItem)
			m_PopupMenu.Popup();
	}
	return true;
}

void CHwndListWnd::Popup()
{	
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WSTR("HWND"),0,0,500,350,NULL,CMD_ID_MODULE_LIST_WND,WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WS_NORMAL|WISP_WLS_TREE);
		SetOwner(&gpSyser->m_MainFrame.m_SystemExplorer);
		Center();
	}	
}
DWORD CHwndListWnd::GetWindowHwndHead()
{
#ifdef CODE_OS_NT_DRV
	gpSyser->InitOSHwndRoot();
	return gpSyser->m_OSHwndRoot;
#endif
	return 0;
}
void CHwndListWnd::UpdateContext(HANDLE hItem,DWORD dwAddress)
{
	CDbgProcess*pDbgProcess=NULL;
	DWORD dwLen,dwHeader;
	HANDLE hSubItem;
	WCHAR Name[256];
	SYSER_HWND_CLASS_INFO ClassInfo;
	ClearChildItem(hItem);
	dwHeader=dwAddress;		
	if(dwAddress==0)
		return;
	SYSER_HWND_INFO HwndInfo;
	while(dwAddress && GetHwndInfoByWndStruct(*(void**)&dwAddress,&HwndInfo))
	{
		hSubItem = InsertItem(HwndInfo.hWnd,hItem);
		SetItemData(hSubItem,0,dwAddress);		
		if(GetClassInfoByHwndInfo(&HwndInfo,&ClassInfo))
		{			
			if(ClassInfo.lpszClassName)			
			{				
				if(SyserPrivateFindByte(*(BYTE**)&ClassInfo.lpszClassName,0,256)!=NULL)
				{					
					SetItemTextA(hSubItem,2,*(const CHAR**)&ClassInfo.lpszClassName);
				}
			}						
		}
		if(HwndInfo.WindowCaptionLen && HwndInfo.WindowCaptionBuffer)
		{
			dwLen=HwndInfo.WindowCaptionLen;
			if(HwndInfo.WindowCaptionLen>sizeof(Name))
				dwLen=sizeof(Name)-2;
			SafeMemCopy((BYTE*)Name,*(BYTE**)&HwndInfo.WindowCaptionBuffer,dwLen);
			Name[dwLen/sizeof(WCHAR)]=0;
			SetItemText(hSubItem,1,Name);
		}
		UpdateContext(hSubItem,*(DWORD*)&HwndInfo.ChildHwnd);
		dwAddress=*(DWORD*)&HwndInfo.NextHwnd;
	}
	
}
bool CHwndListWnd::OnEventPEExplorer(IN WISP_MSG*pMsg)
{
	ULPOS ModuleBase;
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ModuleBase = (ULPOS)GetItemData(hItem,0);

	gpSyser->m_MainFrame.m_HwndPropertyForm.Popup();
	gpSyser->m_MainFrame.m_HwndPropertyForm.UpdateContext(ModuleBase);
	
	return true;
}
bool CHwndListWnd::OnEventGoto(IN WISP_MSG*pMsg)
{
	ULPOS ModuleBase;
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ModuleBase = (ULPOS)GetItemData(hItem,0);
	gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveAddress(ModuleBase);
	return true;
}



