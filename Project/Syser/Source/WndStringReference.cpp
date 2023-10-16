#include "StdAfx.h"
#include "Syser.h"
#include "StringReference.h"
#include "WndStringReference.h"

enum{
	CMD_SEARCH_CHANGE,
};


enum CFindStringForm::WISP_FORM_ID
{
	CMD_ID_BUTTON_FIND = WISP_ID_USER_START,
	CMD_ID_BUTTON_CLOSE,
	CMD_ID_EDIT_FINDTEXT,
};
WISP_FORM_RES_ITEM CFindStringForm::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,320,120},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Find"),
		"\\SyserIcon\\Plugin.ico",
		WSTR("Find"),
	},
	{
		WISP_CTRL_STATIC_STRING,
		{10,18,70,20},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Find what:  "),
		NULL,
		NULL
		},
		{
			WISP_CTRL_EDIT,
			{80,15,220,20},
			CMD_ID_EDIT_FINDTEXT,
			WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
			NULL,
			NULL,
			NULL
		},
		{
			WISP_CTRL_BUTTON,
			{54,50,78,21},
			CMD_ID_BUTTON_FIND,
			WISP_BS_NORMAL|WISP_WS_DISABLED,
			WSTR("Find Next"),

			},
			{
				WISP_CTRL_BUTTON,
				{186,50,78,21},
				WISP_ID_CANCEL,
				WISP_BS_NORMAL,
				WSTR("Close"),
			},
		{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CFindStringForm)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)

WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CFindStringForm)
WISP_MSG_CMD_MAP(CMD_ID_EDIT_FINDTEXT,OnFindTextCmd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CFindStringForm)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_FIND,OnFindButtonEvent)
WISP_MSG_EVENT_MAP_END

CFindStringForm::CFindStringForm()
{
	m_pFormRes = m_FormRes;
}

CFindStringForm::~CFindStringForm()
{

}
bool CFindStringForm::OnFormCreate(IN WISP_MSG* pMsg)
{
	m_FindButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_FIND);
	m_CloseButton = (CWispButton*)GetFormItem(CMD_ID_BUTTON_CLOSE);
	m_FindEdit = (CWispEdit*)GetFormItem(CMD_ID_EDIT_FINDTEXT);
	return true;
}
bool CFindStringForm::OnFindTextCmd(IN WISP_MSG* pMsg)
{
	CWispString* FindText;
	switch(pMsg->Command.CmdMsg) {
	case WISP_CMD_EN_INPUT_KEY_DOWN:
		if(pMsg->Command.Param1==WISP_VK_RETURN)
		{
			m_FindButton->Focus();
			return OnFindButtonEvent(NULL);
		}
		break;
	case WISP_CMD_EN_INPUT_KEY_UP:
		if(pMsg->Command.Param1==WISP_VK_RETURN)
			return false;
		break;
	case WISP_CMD_EN_CHANGED:
		FindText = &m_FindEdit->GetWindowText();
		m_FindButton->EnableWindow(FindText->IsEmpty()==false);
		m_FindButton->Update();
		break;
	}
	return true;
}
bool CFindStringForm::OnFindButtonEvent(IN WISP_MSG* pMsg)
{
	CWispString& pFindText = m_FindEdit->GetWindowText();
	if(m_pContextList)
	{
		if(m_pContextList->m_SearchString == pFindText)
			m_pContextList->OnEventSearchAgain(NULL);
		else
			m_pContextList->FindString(pFindText);
	}
	return true;
}
void CFindStringForm::SetContextList(CStringReferenceList* pContextList)
{
	m_pContextList = pContextList;
	return;
}


WISP_MENU_RES_ITEM SRMenu[]=
{
	{WSTR("Search          Ctrl+N"),	EVENT_ID_SR_SEARCH,		7*16+7},
	{WSTR("Search again    Alt+N"),		EVENT_ID_SR_SEARCH_AGAIN,7*16+7},
		WISP_MENU_RES_END
};
WISP_MSG_MAP_BEGIN(CStringReferenceList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
	WISP_MSG_MAP(WISP_WM_CHAR,OnChar)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_CMD_MAP_BEGIN(CStringReferenceList)

WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CStringReferenceList)
	WISP_MSG_EVENT_MAP(EVENT_ID_SR_SEARCH_AGAIN,		OnEventSearchAgain)
	WISP_MSG_EVENT_MAP(EVENT_ID_SR_SEARCH,		OnEventSearch)
WISP_MSG_EVENT_MAP_END


bool CStringReferenceList::OnEventSearch(IN WISP_MSG*pMsg)
{
	m_FindDlg.CreateForm(NULL);
	m_FindDlg.SetContextList(this);
	return true;
}
bool CStringReferenceList::OnEventSearchAgain(IN WISP_MSG*pMsg)
{
	WCHAR Buffer[256];
	PWCHAR pBuffer;
	int n,nCol;
	HANDLE hItem;
	hItem= GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(m_SearchString.Length()==0)
		return true;
	if(hItem==NULL)
		hItem = GetNextListItem();
			
	n=m_SearchString.Length()+5;
	if(n>sizeof(Buffer)/sizeof(Buffer[0])-1)
		n=sizeof(Buffer)/sizeof(Buffer[0])-1;
	if(m_TypeWnd==0)
		nCol=1;
	else
		nCol=3;
	if(hItem)
		hItem=GetNextListItem(hItem);
	while(hItem)
	{
		GetItemText(hItem,nCol,Buffer,n);
		if(Buffer[0]=='L' && Buffer[1]=='"')
			pBuffer=Buffer+2;
		else
			pBuffer=Buffer+1;
		if(TStrNICmp(pBuffer,(WISP_CHAR*)m_SearchString,m_SearchString.Length())==0)
			break;
		hItem = GetNextListItem(hItem);
	}
	if(hItem)
	{
		SelectItem(hItem);
		EnableVisible(hItem);					
	}
	return true;
}

void CStringReferenceList::AttachShortcutKey()
{
	if(gpSyser->AttachShortcutKey(EVENT_ID_SR_SEARCH_AGAIN,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_N,EVENT_ID_SR_SEARCH_AGAIN);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SR_SEARCH,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL | WISP_VK_N,EVENT_ID_SR_SEARCH);
}
bool CStringReferenceList::OnKeyEvent(IN WISP_MSG*pMsg)
{
	SRHOTKEYMAP::IT FindIT;
	WISP_MSG Msg;
	if(pMsg->KeyEvent.bKeyDown)
	{
		FindIT = m_HotKeyMap.Find(pMsg->KeyEvent.KeyType);
		if(FindIT != m_HotKeyMap.End())
		{
			memset(&Msg,0,sizeof(Msg));
			Msg.Command.CmdID=*FindIT;			
			return OnEvent(&Msg);						
		}
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_VK_RBUTTON:
			PopupMenu();
			break;
		}
	}
	return true;
}


CStringReferenceList::CStringReferenceList()
{
	m_MaxMatchLen=0;
}



bool CStringReferenceList::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	WISP_RECT CellRC;
	int nCol=1;
	HANDLE hItem= GetNextItem(NULL,WISP_WLIS_SELECTED);;
	ULPOS Address=0;
	if(m_TypeWnd==0)
		nCol=1;
	else
		nCol=3;
	memset(&CellRC,0,sizeof(CellRC));
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON && hItem)
	{
		GetItemCellRect(hItem,nCol,&CellRC);
		if(pMsg->MsgMouseWndPT.x >= CellRC.x && pMsg->MsgMouseWndPT.x<=CellRC.x+CellRC.cx)
		{
			VIEW_DATA((ULPOS)GetItemData(hItem,1));
		}
		else
		{						
			VIEW_CODE((ULPOS)GetItemData(hItem,0),true);			
		}

	}	
	return true;
}

bool CStringReferenceList::FindString(WISP_CHAR* pSearch)
{
	int n,nCol;
	WCHAR Buffer[256];
	PWCHAR pBuffer;
	if(m_TypeWnd==0)
		nCol=1;
	else
		nCol=3;
	if(pSearch)
		m_SearchString=pSearch;
	n=m_SearchString.Length()+5;
	if(n>sizeof(Buffer)/sizeof(Buffer[0])-1)
		n=sizeof(Buffer)/sizeof(Buffer[0])-1;
	HANDLE hItem = GetNextItem(NULL);
	while(hItem)
	{
		Buffer[255]=0;
		GetItemText(hItem,nCol,Buffer,sizeof(Buffer)-1);
		if(Buffer[0]=='L' && Buffer[1]=='"')
			pBuffer=Buffer+2;
		else
			pBuffer=Buffer+1;
		pBuffer = TStrIStr(pBuffer,(WISP_CHAR*)m_SearchString);
		if(pBuffer)
			break;
		hItem = GetNextItem(hItem);
	}
	if(hItem)
	{
		m_MaxMatchLen=m_SearchString.Length();

		SelectItem(hItem);
		EnableVisible(hItem);
	
		SendCmdMsg(CMD_SEARCH_CHANGE,1,0);
	}
	else
	{		
		SendCmdMsg(CMD_SEARCH_CHANGE,0,0);
	}
	return true;
}

bool CStringReferenceList::OnChar(IN WISP_MSG*pMsg)
{

	int n;
	n = m_SearchString.Length();
	
	if(pMsg->Char.Char==0x8 || n>m_MaxMatchLen)
	{		
		if(n)
			m_SearchString.Delete(n-1);
		if(pMsg->Char.Char!=0x8)
			m_SearchString+= pMsg->Char.Char;	
	}
	else
		m_SearchString+= pMsg->Char.Char;	

	if(pMsg->Char.Char==0x08)
		SendCmdMsg(CMD_SEARCH_CHANGE,1,0);
	else
		FindString();
	return true;
}

bool CStringReferenceList::OnCreate(IN WISP_MSG*pMsg)
{
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);	
	m_SearchString.Empty();
	AttachShortcutKey();
	m_PopupMenu.CreatePopupMenu(SRMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_MenuSearchAgain = m_PopupMenu.GetItem(EVENT_ID_SR_SEARCH_AGAIN);
	return true;
}

bool CStringReferenceList::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}


void CStringReferenceList::PopupMenu()
{
	HANDLE hItem;		
	hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	m_PopupMenu.EnableItem(m_MenuSearchAgain,m_SearchString.IsEmpty()==false);
	m_PopupMenu.Popup();
}


void CStringReferenceList::ItemClickNotify(HANDLE hItem,int Col)
{
	
}


void CStringReferenceList::UpdateContext(ULPOS Address,bool bRelocal)
{
	CFindString FindString;
	TMap<DWORD,ULONGLONG>::IT BeginIT,EndIT;
	WISP_COLOR_CHAR szColorBuffer[256];
	WCHAR StringBuf[256];
	HANDLE hItem,hSubItem;
	bool bUnicode=false;
	char Str[256];
	TMap<DWORD,HANDLE> SortMap;
	TMap<DWORD,HANDLE>::IT SortIT;
	DWORD Len,ModuleAddress;
	CCodeView*pCodeView;
	NUM_PTR ItemData;
	pCodeView=(CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	if(pCodeView==NULL)
		return ;		
	gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.Clear();
	hItem=pCodeView->GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem)
	{
		ModuleAddress = (DWORD)GetItemData(hItem,1);
	}
	else
		ModuleAddress =*X86_REG_PTR.pEIP;
	if(m_TypeWnd)
	{
		FindString.SearchImageMemory(ModuleAddress);
		BeginIT = gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.Begin();
		EndIT = gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.End();

		for(;BeginIT!=EndIT;BeginIT++)
		{
			bUnicode=false;
			Address = (DWORD)(*BeginIT);
			ItemData=*BeginIT;
			pCodeView->ColorDasm(BeginIT.Key(),MAX_INSTR_LEN,szColorBuffer);
			hItem = InsertItem(BeginIT.Key(),NULL,WSTR("%08X"));					
			SetItemColorText(hItem,2,szColorBuffer);
			SetItemData(hItem,1,ItemData);
			ItemData=BeginIT.Key();
			SetItemData(hItem,0,ItemData);
			Len=(DWORD)((*BeginIT)>>32);
			if(Len&0x80000000)
			{
				bUnicode=true;	
				Len &= 0x7fffffff;
			}
			if(Len>256)
				Len=255;

			if(bUnicode)
			{
				StringBuf[0]='L';
				StringBuf[1]='"';
				gpSyser->m_pDebugger->ReadMemory(Address,StringBuf+2,Len*sizeof(WCHAR));
				StringBuf[1+Len]='"';
				StringBuf[2+Len]=0;
				StringBuf[255]=0;
				SetItemText(hItem,1,L"U");
			}
			else
			{
				Str[0]=0;
				gpSyser->m_pDebugger->ReadMemory(Address,Str,Len);
				Str[255]=0;			
				TStrCpyLimit(StringBuf+1,Str,Len);
				StringBuf[0]='"';
				TStrCat(StringBuf,"\"");
				SetItemText(hItem,1,L"C");
			}

			SetItemText(hItem,3,StringBuf);
		}
	}
	else
	{
		FindString.SearchImageMemory(*X86_REG_PTR.pEIP);
		BeginIT = gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.Begin();
		EndIT = gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.End();
		for(;BeginIT!=EndIT;BeginIT++)
		{
			bUnicode=false;
			Address = (DWORD)(*BeginIT);
			ItemData = *BeginIT;
			pCodeView->ColorDasm(BeginIT.Key(),MAX_INSTR_LEN,szColorBuffer);
			SortIT = SortMap.Find(Address);
			if(SortIT!=SortMap.End())
			{
				hItem=*SortIT;
			}
			else
			{
				hItem = InsertItem(Address,NULL,WSTR("%08X"));
				SortMap.InsertUnique(Address,hItem);

				SetItemData(hItem,1,ItemData);
				ItemData=BeginIT.Key();
				ItemData|=0x8000000000000000;
				SetItemData(hItem,0,ItemData);

				Len=(DWORD)((*BeginIT)>>32);
				if(Len&0x80000000)
				{
					bUnicode=true;	
					Len &= 0x7fffffff;
				}
				if(Len>256)
					Len=255;

				if(bUnicode)
				{
					StringBuf[0]='L';
					StringBuf[1]='"';
					gpSyser->m_pDebugger->ReadMemory(Address,StringBuf+2,Len*sizeof(WCHAR));
					StringBuf[1+Len]='"';
					StringBuf[2+Len]=0;
					StringBuf[255]=0;

				}
				else
				{
					Str[0]=0;
					gpSyser->m_pDebugger->ReadMemory(Address,Str,Len);
					Str[255]=0;			
					TStrCpyLimit(StringBuf+1,Str,Len);
					StringBuf[0]='"';
					TStrCat(StringBuf,"\"");
				}
				SetItemText(hItem,1,StringBuf);
			}
			hSubItem = InsertItem(BeginIT.Key(),hItem,WSTR("%08X"));
			SetItemColorText(hSubItem,1,szColorBuffer);		
			SetItemData(hSubItem,0,BeginIT.Key());
			ItemData = *BeginIT;
			SetItemData(hSubItem,1,ItemData);
		}
		SortMap.Clear();
	}
}

void CStringReferenceList::ResetContext()
{

}

bool CStringReferenceList::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{

	return true;
}

bool CStringReferenceList::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{

	return false;
}


WISP_MSG_MAP_BEGIN(CFindListWnd)
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_CMD_MAP_BEGIN(CFindListWnd)
WISP_MSG_CMD_MAP(EVENT_ID_STRING_REFERENCE_WISPLIST,OnListWndCmd);
WISP_MSG_CMD_MAP_END


bool CFindListWnd::OnListWndCmd(IN WISP_MSG* pMsg)
{
	switch(pMsg->Command.CmdMsg)
	{
	case CMD_SEARCH_CHANGE:
		m_StatusWnd.m_StatusString = m_ListWnd.m_SearchString;
		if(pMsg->Command.Param1 == 0 )
		{
			if(m_StatusWnd.m_StatusString.Length()!=0)
			m_StatusWnd.m_StatusString += WSTR(": not found");	
		}
		
		m_StatusWnd.Update();
		break;
	}
	return true;
}

bool CFindListWnd::OnCreate(IN WISP_MSG* pMsg)
{
	m_TypeWnd=1;
	m_ListWnd.Create(WSTR("String Reference"),0,0,556,300,this,EVENT_ID_STRING_REFERENCE_WISPLIST,WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_SELECTED_ALWAYS);
	m_ListWnd.SetWndType(1);
	gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.Clear();
	if(m_TypeWnd)
	{
		m_ListWnd.InsertColumn(WSTR("Address"),60);
		m_ListWnd.InsertColumn(WSTR("Type"),32);
		m_ListWnd.InsertColumn(WSTR("Disassembly"),200);
		m_ListWnd.InsertColumn(WSTR("Text String"),280);				
	}
	else
	{
		m_ListWnd.InsertColumn(WSTR("Address"),80);
		m_ListWnd.InsertColumn(WSTR("Text String/Disassembly"),200);	
	}		
	m_ListWnd.m_SelectBKColor = ColorOption.clrSelectedFrame;
	m_ListWnd.SetDefaultTextColor(ColorOption.clrText);
	m_ListWnd.SetBGColor(ColorOption.clrBackground);	
	m_StatusWnd.Create(NULL,0,300,564,20,this,0,WISP_WS_THIN_BORDER);
	
	m_StatusWnd.SetBGColor(ColorOption.clrBackground);
	m_StatusWnd.m_ClientDC.SetTextColor(ColorOption.clrText);	
	m_ListWnd.UpdateContext(0,0);
	return true;
}

bool CFindListWnd::OnSize(IN WISP_MSG* pMsg)
{
	m_ListWnd.Resize(m_ClientRect.cx,m_ClientRect.cy-20);
	m_StatusWnd.Resize(m_ClientRect.cx,20);
	m_ListWnd.MoveToWindow(m_ClientRect.x,m_ClientRect.y);
	m_StatusWnd.MoveToWindow(m_ClientRect.x,m_ClientRect.y+m_ClientRect.cy-20);
	return true;
}


WISP_MSG_MAP_BEGIN(CStatusWnd)
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
WISP_MSG_MAP_END(CWispWnd)

bool CStatusWnd::OnUpdateClient(IN WISP_MSG* pMsg)
{
	CWispWnd::OnUpdateClient(pMsg);
	m_ClientDC.DrawString(4,2,(WISP_CHAR*)m_StatusString);
	
	return false;
}


bool CStatusWnd::OnCreate(IN WISP_MSG* pMsg)
{
	m_BorderSize=2;
	m_StatusString.Empty();
	return true;
}