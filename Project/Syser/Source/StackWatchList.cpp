#include "StdAfx.h"
#include "Syser.h"
#include "StackWatchList.h"
#include "StringReference.h"

WISP_MENU_RES_ITEM StackWatchMenu[]=
{
	{WSTR("Show Data "),		EVENT_ID_SHOW_DATA,127},
	{WSTR("Show Code "),		EVENT_ID_SHOW_CODE,126},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Show ESP Address"),	EVENT_ID_SHOW_ESP_ADDR,119},
	{WSTR("Show EBP Address"),	EVENT_ID_SHOW_EBP_ADDR,119},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Address Mode"),		EVENT_ID_ADDRESS_MODE_HEX,	0,WISP_MIS_CHECKBOX},
	{WSTR("Offset  Mode"),		EVENT_ID_OFFSET_MODE_HEX,	0,WISP_MIS_CHECKBOX},
	{WSTR("Relative to ESP"),	EVENT_ID_RELATIVE_TO_ESP,	0,WISP_MIS_CHECKBOX},
	{WSTR("Relative to EBP"),	EVENT_ID_RELATIVE_TO_EBP,	0,WISP_MIS_CHECKBOX},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Low->High Address"),	EVENT_ID_ADDRESS_ORFER,	0},
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CStackWatchList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_SCROLL_EVENT,OnScrollEvent)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_CMD_MAP_BEGIN(CStackWatchList)
	WISP_MSG_CMD_MAP(WISP_ID_VSLIDE,OnCmdVSlide);
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CStackWatchList)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_EBP_ADDR,		OnEventShowEBP)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_ESP_ADDR,		OnEventShowESP)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_CODE,			OnEventShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_DATA,			OnEventShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_CODE_BY_ADDRESS,			OnShowCodeByAddress)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_DATA_BY_ADDRESS,			OnShowDataByAddress)
	
	WISP_MSG_EVENT_MAP(EVENT_ID_ADDRESS_MODE_HEX,	OnEventAddressModeHex)
	WISP_MSG_EVENT_MAP(EVENT_ID_OFFSET_MODE_HEX,	OnEventOffsetModeHex)
	WISP_MSG_EVENT_MAP(EVENT_ID_RELATIVE_TO_ESP,	OnEventRelativeToESP)
	WISP_MSG_EVENT_MAP(EVENT_ID_RELATIVE_TO_EBP,	OnEventRelativeToEBP)
	WISP_MSG_EVENT_MAP(EVENT_ID_ADDRESS_ORFER,		OnEventToggleAddressOrder)

WISP_MSG_EVENT_MAP_END


CStackWatchList::CStackWatchList()
{
	m_ScrollSpace = 2;
	m_AddrLowToHigh=true;
}

bool CStackWatchList::OnCmdVSlide(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		SetScrollBarCurPos(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,false);
	}
	return true;
}

bool CStackWatchList::OnEventShowEBP(IN WISP_MSG*pMsg)
{
	UpdateContext(*X86_REG_PTR.pEBP);
	return true;
}

bool CStackWatchList::OnEventShowESP(IN WISP_MSG*pMsg)
{
	UpdateContext(*X86_REG_PTR.pESP);
	return true;
}

bool CStackWatchList::OnEventShowCode(IN WISP_MSG*pMsg)
{	
	DWORD Value;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ULPOS Address=(ULPOS)GetItemData(hItem,1);
	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
	VIEW_CODE((ULPOS)GetItemData(hItem,1),true);
	return true;
}

bool CStackWatchList::OnShowCodeByAddress(IN WISP_MSG*pMsg)
{	
	DWORD Value;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ULPOS Address=(ULPOS)GetItemData(hItem,0);

	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		VIEW_CODE((ULPOS)GetItemData(hItem,0),true);
	return true;
}



bool CStackWatchList::OnEventShowData(IN WISP_MSG*pMsg)
{
	DWORD Value;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ULPOS Address=(ULPOS)GetItemData(hItem,1);
	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		VIEW_DATA((ULPOS)GetItemData(hItem,1));
	return true;
}

bool CStackWatchList::OnShowDataByAddress(IN WISP_MSG*pMsg)
{
	DWORD Value;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	ULPOS Address=(ULPOS)GetItemData(hItem,0);
	if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		VIEW_DATA((ULPOS)GetItemData(hItem,0));
	return true;
}

bool CStackWatchList::OnCreate(IN WISP_MSG*pMsg)
{
	m_Style|=WISP_WLS_VERT_LINE;
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	HANDLE hItem;
	int FontWidth = m_ClientDC.GetTextExtent(WSTR("X"));
	InsertColumn(WISP_STR("Address"),FontWidth*9);
	InsertColumn(WISP_STR("Value[F2]"),FontWidth*10,WISP_WLCS_EDITABLE);
	InsertColumn(WISP_STR("Context"),100);
	m_CurAddr = 0;
	for(int n=0;n<m_nLinePerPage;n++)
	{
		hItem = InsertItem(WISP_STR("????????"));
		SetItemText(hItem,1,WISP_STR("????????"));
	}
	m_ScrollBar[WISP_SB_VERT]->Style = WISP_SS_NORMAL;
	m_ScrollBar[WISP_SB_VERT]->bHide = false;
	m_PopupMenu.CreatePopupMenu(StackWatchMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_hMenuShowCode = m_PopupMenu.GetItem(EVENT_ID_SHOW_CODE);
	m_hMenuShowData = m_PopupMenu.GetItem(EVENT_ID_SHOW_DATA);
	m_hAddrLowToHigh = m_PopupMenu.GetItem(EVENT_ID_ADDRESS_ORFER);

	AttachShortcutKey();
	return true;
}

void	CStackWatchList::AttachShortcutKey()
{
	if(gpSyser->AttachShortcutKey(EVENT_ID_SHOW_CODE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_RETURN,EVENT_ID_SHOW_CODE);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SHOW_DATA_BY_ADDRESS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL | WISP_VK_RETURN,EVENT_ID_SHOW_DATA_BY_ADDRESS);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SHOW_DATA,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_RETURN,EVENT_ID_SHOW_DATA);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SHOW_CODE_BY_ADDRESS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_RETURN,EVENT_ID_SHOW_CODE_BY_ADDRESS);

}

bool CStackWatchList::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CStackWatchList::OnSize(IN WISP_MSG*pMsg)
{
	if(pMsg->Resize.NewSizeDelta.cy==0)
		return true;
	ResetContext();
	if(gpSyser->m_pDebugger==NULL || gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return true;
	UpdateContext(*X86_REG_PTR.pESP);
	return true;
}

bool CStackWatchList::OnScrollEvent(IN WISP_MSG*pMsg)
{
	if(gpSyser->m_pDebugger==NULL || gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return false;
	if(pMsg->ScrollEvent.SBType==WISP_SB_VERT)
	{
		switch(pMsg->ScrollEvent.Event)
		{
		case WISP_SB_PAGE_UP:
			if(m_AddrLowToHigh)
				UpdateContext(m_CurAddr-(sizeof(VALUE_TYPE)*m_ScrollBar[WISP_SB_VERT]->Page),true);
			else
				UpdateContext(m_CurAddr+(sizeof(VALUE_TYPE)*m_ScrollBar[WISP_SB_VERT]->Page),true);
			break;
		case WISP_SB_PAGE_DOWN:
			if(m_AddrLowToHigh)
				UpdateContext(m_CurAddr+(sizeof(VALUE_TYPE)*m_ScrollBar[WISP_SB_VERT]->Page),true);
			else
				UpdateContext(m_CurAddr-(sizeof(VALUE_TYPE)*m_ScrollBar[WISP_SB_VERT]->Page),true);
			break;
		case WISP_SB_DEC:
			if(m_AddrLowToHigh)
				UpdateContext(m_CurAddr-sizeof(VALUE_TYPE),true);
			else
				UpdateContext(m_CurAddr+sizeof(VALUE_TYPE),true);
			break;
		case WISP_SB_INC:
			if(m_AddrLowToHigh)
				UpdateContext(m_CurAddr+sizeof(VALUE_TYPE),true);
			else
				UpdateContext(m_CurAddr-sizeof(VALUE_TYPE),true);
			break;
		case WISP_SB_POS_CHANGE:
			if(m_AddrLowToHigh)
				UpdateContext(m_CurAddr+pMsg->ScrollEvent.Delta*sizeof(VALUE_TYPE),true);
			else
				UpdateContext(m_CurAddr-pMsg->ScrollEvent.Delta*sizeof(VALUE_TYPE),true);
			return false;
			break;
		}
		SetScrollBarCurPos(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace);
		return false;
	}
	return true;
}
DWORD	CStackWatchList::FindShortcutKey(DWORD CmdID)
{
	STACKHOTKEYMAP::IT BeginIT,EndIT;

	BeginIT = m_HotKeyMap.Begin();
	EndIT = m_HotKeyMap.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		if(*BeginIT == CmdID)
			return BeginIT.Key();
	}
	return 0;
}
void CStackWatchList::PopupMenu(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	CWispDIB*pIcon;
	ULPOS Address;
	bool bIsAddressVailed=false;
	BYTE Buffer;
	WCHAR szBuffer[128];
	WCHAR wHotKeyBuffer[50];
		
	if(pMsg)
	{
		WISP_RECT CellRC;
		GetItemCellRect(GetItem(0),0,&CellRC);
		if(pMsg->MsgMouseWndPT.x >= CellRC.x && pMsg->MsgMouseWndPT.x<=CellRC.x+CellRC.cx)
		{
		}
	}

	
	hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);	
	if(hItem)
	{		
		Address = (ULPOS)GetItemData(hItem,1);
		if(gpSyser->m_pDebugger->ReadMemory(Address,&Buffer,sizeof(Buffer))==sizeof(Buffer))
		{
			bIsAddressVailed=true;
		}
		WISP_PCSTR pszText = (WISP_PCSTR)GetItemText(hItem,1);
		gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_SHOW_CODE_BY_ADDRESS),wHotKeyBuffer);	
		TSPrintf(szBuffer,WSTR("Show code at:%s  %s"),pszText,wHotKeyBuffer);
		m_PopupMenu.SetItemText(m_hMenuShowCode,szBuffer);
		gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_SHOW_DATA_BY_ADDRESS),wHotKeyBuffer);	
		TSPrintf(szBuffer,WSTR("Show data at:%s  %s"),pszText,wHotKeyBuffer);
		m_PopupMenu.SetItemText(m_hMenuShowData,szBuffer);		
	}
	m_PopupMenu.EnableItem(m_hMenuShowCode,hItem!=NULL && bIsAddressVailed);
	m_PopupMenu.EnableItem(m_hMenuShowData,hItem!=NULL && bIsAddressVailed);
	m_PopupMenu.CheckItem(EVENT_ID_ADDRESS_MODE_HEX,m_AddrShowMode == STACK_WATCH_ADDRESS_MOD);
	m_PopupMenu.CheckItem(EVENT_ID_OFFSET_MODE_HEX,m_AddrShowMode == STACK_WATCH_OFFSET_MOD);
	m_PopupMenu.CheckItem(EVENT_ID_RELATIVE_TO_ESP,m_AddrShowMode == STACK_WATCH_REL_TO_ESP_MOD);
	m_PopupMenu.CheckItem(EVENT_ID_RELATIVE_TO_EBP,m_AddrShowMode == STACK_WATCH_REL_TO_EBP_MOD);
	if(m_AddrLowToHigh)
	{
		pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*10+15);
		TStrCpy(szBuffer,WSTR("High-->Low Address"));		
	}
	else
	{
		pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*10+14);
		TStrCpy(szBuffer,WSTR("Low-->High Address"));
	}
	m_PopupMenu.SetItemText(m_hAddrLowToHigh,szBuffer);
	m_PopupMenu.SetItemIcon(m_hAddrLowToHigh,pIcon);
	m_PopupMenu.Popup();
}


bool CStackWatchList::OnKeyEvent(IN WISP_MSG*pMsg)
{	
	HANDLE hItem;
	STACKHOTKEYMAP::IT FindIT;

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
			PopupMenu(pMsg);
			break;
		case WISP_VK_F2:
			hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
			if(hItem)
				BeginEditItem(hItem,1);
			break;
		case WISP_VK_W:
			OnEventToggleAddressOrder(NULL);
			break;
		case WISP_VK_S:
			OnEventToggleAddressOrder(NULL);
			break;

		}
	}
	return true;
}



bool CStackWatchList::GetValueSym(ULPOS Address,VALUE_TYPE Value,WISP_COLOR_CHAR* szColorBuffer,int ccLen,COMMENT_TYPE* CommentType)
{
	CHAR szBufferA[256];
	CHAR szRetBuf[256];
	WCHAR szBuffer[256];
	CHAR* pStr;
	bool bSuccess;
	int nLen=0;
	int StrType;
	ULPOS DestAddress;
	szColorBuffer[0]=0;
	szBuffer[0] = 0;
	if(Address == *X86_REG_PTR.pESP)
		nLen = ColorStrCpy(szColorBuffer,"<-ESP ",SC_WHITE,SC_LIGHT_RED);
	if(Address == *X86_REG_PTR.pEBP)
		nLen += ColorStrCat(szColorBuffer,"<-EBP ",SC_WHITE,SC_LIGHT_GREEN);
	
		GetSEHSym(Address,Value,szColorBuffer,ccLen);

	if(GET_STRING_SYM(Value,szBuffer,ccLen-nLen-1,StrType))
	{
		if(StrType == CT_ASCII)
			ColorStrCat(szColorBuffer,szBuffer,SC_BLUE,0);
		else if(StrType == CT_UINCODE)
			ColorStrCat(szColorBuffer,szBuffer,SC_LIGHT_BROWN,0);
		if(CommentType)
			*CommentType=(COMMENT_TYPE)StrType;
		return true;
	}
	bSuccess = GET_ALMOST_SYM(Value,szBufferA);
	szRetBuf[0]=0;
	if(bSuccess)
	{
		*CommentType=CT_SYMBOLS;
		pStr = TStrChr(szBufferA,'+');
		if(pStr)
		{						
			nLen = gpSyser->m_SyserUI.m_CodeDoc.IsPrevCodeCallInstr(Value,szRetBuf,NULL);
			if(nLen)
			{
				if(gpSyser->m_SyserUI.m_CodeDoc.GetInstrDesAddress(Value-nLen,&DestAddress))
				{
					TSPrintf(szRetBuf,"Return to %08X from %08X ",Value,DestAddress);
				}
				else
				{
					TSPrintf(szRetBuf,"Return to %08X ",Value);
				}								
			}	
			else
				szRetBuf[0]=0;
		}
		ColorStrCat(szColorBuffer,szRetBuf,SC_RED,0);		
		ColorStrCat(szColorBuffer,szBufferA,SC_WHITE,0);		
	}
	else
	{
		
		szBufferA[0]=0;
		nLen = gpSyser->m_SyserUI.m_CodeDoc.IsPrevCodeCallInstr(Value,szRetBuf,NULL);			
		if(nLen==0)
			return false;
		if(gpSyser->m_SyserUI.m_CodeDoc.GetInstrDesAddress(Value-nLen,&DestAddress))
		{
			TSPrintf(szRetBuf,"Return to %08X from %08X",Value,DestAddress);
		}
		else
			TSPrintf(szRetBuf,"(return to %08X)",Value);		
		ColorStrCat(szColorBuffer,szRetBuf,SC_RED,0);		
		*CommentType=CT_RETURN_ADDRESS;
	}

		

	return true;
}

void CStackWatchList::ItemClickNotify(HANDLE hItem,int Col)
{
	switch(Col)
	{
	case 0:
		switch(m_AddrShowMode)
		{
		case STACK_WATCH_ADDRESS_MOD:
			OnEventOffsetModeHex(NULL);
			break;
		case STACK_WATCH_OFFSET_MOD:
			OnEventRelativeToESP(NULL);
			break;
		case STACK_WATCH_REL_TO_ESP_MOD:
			OnEventRelativeToEBP(NULL);
			break;
		case STACK_WATCH_REL_TO_EBP_MOD:
			OnEventAddressModeHex(NULL);
			break;
		}
		break;
	}
}

void CStackWatchList::GetAddressString(ULPOS Address,WISP_PSTR szBuffer)
{
	WISP_CHAR szRelStr[32];
	int BaseAddress,Offset;
	switch(m_AddrShowMode)
	{
	case STACK_WATCH_ADDRESS_MOD:
		TSPrintf(szBuffer,WSTR("%08X"),Address);
		return;
	case STACK_WATCH_OFFSET_MOD:
		BaseAddress=(int)m_BaseActiveAddress;
		Offset = (int)Address-BaseAddress;
		TStrCpy(szRelStr,"$");
		break;
	case STACK_WATCH_REL_TO_ESP_MOD:
		BaseAddress=(int)*X86_REG_PTR.pESP;
		Offset = (int)Address-BaseAddress;
		TStrCpy(szRelStr,"ESP");
		break;
	case STACK_WATCH_REL_TO_EBP_MOD:
		BaseAddress=(int)*X86_REG_PTR.pEBP;
		Offset = (int)Address-BaseAddress;
		TStrCpy(szRelStr,"EBP");
		break;
	}
	if(Offset>0)
	{
		TSPrintf(szBuffer,WSTR("%s+%X"),szRelStr,Offset);
	}
	else if(Offset==0)
	{
		TStrCpy(szBuffer,szRelStr);
		TStrCat(szBuffer,"==>");
	}
	else
	{
		TSPrintf(szBuffer,WSTR("%s-%X"),szRelStr,-Offset);
	}
}
void CStackWatchList::GetSEHSym(ULPOS Address,VALUE_TYPE Value,WISP_COLOR_CHAR* szColorBuffer,int ccLen)
{
	SEH_MAP::IT FindIT;
	FindIT = m_SehMap.Find(Address);
	if(FindIT!=m_SehMap.End())
	{
		if(FindIT==m_SehMap.Last())
			ColorStrCat(szColorBuffer,"End of SEH chain",SC_RED,0);			
		else
			ColorStrCat(szColorBuffer,"Pointer to next SEH record",SC_RED,0);			
	}
	else if(m_RSehMap.Find(Value)!=m_RSehMap.End())
	{	
		FindIT = m_SehMap.Find(Address-4);
		if(FindIT!=m_SehMap.End())
			ColorStrCat(szColorBuffer,"SEH Handler",SC_RED,0);		
	}
}
void CStackWatchList::InitSEHMap()
{
	m_SehMap.Clear();
	m_RSehMap.Clear();
	DWORD dwSEH,dwSize,dwFSBase;
	if(gpSyser->m_pDebugger->GetSegRegBase( *X86_REG_PTR.pFS ,&dwFSBase,&dwSize))
	{
		SEH_STR SehHeader;
		SehHeader.dwNext=dwFSBase;		
		int i = 0; 
		dwSEH=dwFSBase;
		if(gpSyser->m_SyserUI.m_CodeDoc.ReadMemory(dwFSBase ,&dwSEH,sizeof(dwSEH))!=sizeof(dwSEH))
			return;
		for(i = 0; i< 100;i++)
		{
			if(gpSyser->m_SyserUI.m_CodeDoc.ReadMemory(dwSEH ,&SehHeader,sizeof(SehHeader))!=sizeof(SehHeader))
				break;			
			m_SehMap.InsertUnique(dwSEH,SehHeader.SEHHandler);

			m_RSehMap.InsertUnique(SehHeader.SEHHandler,dwSEH);
			dwSEH = SehHeader.dwNext;
			if(SehHeader.dwNext==0xffffffff)
				break;
		}
	}
		
}
void CStackWatchList::UpdateContext(ULPOS Address,bool bRelocal)
{
	HANDLE hItem;
	VALUE_TYPE Data;
	WCHAR szBuffer[256];
	WISP_COLOR_CHAR szColorBuffer[256];
	InitSEHMap();
	if(bRelocal)
	{
		m_CurAddr = Address;
	}
	else
	{
		if(m_AddrLowToHigh)
		{
			if(Address<m_CurAddr+m_nLinePerPage*sizeof(DWORD)/4 || Address>=m_CurAddr+sizeof(VALUE_TYPE)*m_nLinePerPage*3/4)
				m_CurAddr = Address - sizeof(VALUE_TYPE)*(m_nLinePerPage/2);
		}
		else
		{			
			if(Address>m_CurAddr-m_nLinePerPage*sizeof(DWORD)/4 || Address<=m_CurAddr-sizeof(VALUE_TYPE)*m_nLinePerPage*3/4)
				m_CurAddr = Address + sizeof(VALUE_TYPE)*(m_nLinePerPage/2);			
		}
		Address = m_CurAddr;
	}
	hItem = GetNextItem(NULL,WISP_WLIS_NORMAL);
	while(hItem!=NULL)
	{
		GetAddressString(Address,szBuffer);
		if(Address == *X86_REG_PTR.pESP )
		{
			ColorStrCpy(szColorBuffer,szBuffer,SC_WHITE,SC_LIGHT_RED);
			SetItemColorText(hItem,0,szColorBuffer);
		} 
		else if(Address == *X86_REG_PTR.pEBP)
		{
			ColorStrCpy(szColorBuffer,szBuffer,SC_WHITE,SC_LIGHT_GREEN);
			SetItemColorText(hItem,0,szColorBuffer);
		}
		else
			SetItemText(hItem,0,szBuffer);
		Data = 0;
		if(gpSyser->m_pDebugger->ReadMemory(Address,&Data,sizeof(Data))==sizeof(Data))
			TSPrintf(szBuffer,WSTR("%08X"),Data);
		else
			TStrCpy(szBuffer,WSTR("????????"));
		SetItemData(hItem,0,Address);
		SetItemText(hItem,1,szBuffer);
		SetItemData(hItem,1,Data);
		COMMENT_TYPE CommentType;
		GetValueSym(Address,Data,szColorBuffer,sizeof(szColorBuffer)/sizeof(szColorBuffer[0]),&CommentType);
		
		SetItemColorText(hItem,2,szColorBuffer);		
		if(m_AddrLowToHigh)
			Address+=sizeof(VALUE_TYPE);
		else
			Address-=sizeof(VALUE_TYPE);
		hItem = GetNextItem(hItem,WISP_WLIS_NORMAL);
	}
	UpdateClient();
}

void CStackWatchList::ResetContext()
{
	HANDLE hItem;
	SetItemChildCount(NULL,m_nLinePerPage);
	EmptyChildItemContext();
	hItem = GetItem(0);
	if(hItem)
		SelectItem(hItem);
	SetScrollBarInfo(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,m_nLinePerPage*(m_ScrollSpace+m_ScrollSpace+1),m_nLinePerPage);
	m_SehMap.Clear();
	m_RSehMap.Clear();
}

bool CStackWatchList::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	if(gpSyser->m_pDebugger==NULL||gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return false;
	if(Col==1)
	{
		if(GetItemText(hItem,1)==WSTR("????????"))
			return false;
	}
	return true;
}

bool CStackWatchList::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	//WCHAR szBuffer[256];
	WISP_COLOR_CHAR szColorBuffer[256];
	VALUE_TYPE Value;
	if(CALCEXP(String,&Value)==false)
		return false;
	if(Col==0)
	{
		
	}
	else if(Col==1)
	{
		if(GetItemText(hItem,Col)==String)
			return false;
		ULPOS Address = (ULPOS)GetItemData(hItem,0);
		if(gpSyser->m_pDebugger->WriteMemory(Address,&Value,sizeof(Value))!=sizeof(Value))
			return false;
		GetItemEditString().Format(WSTR("%08X"),Value);
		COMMENT_TYPE CommentType;
		GetValueSym(Address,Value,szColorBuffer,sizeof(szColorBuffer)/sizeof(szColorBuffer[0]),&CommentType);
		SetItemColorText(hItem,2,szColorBuffer);
		return true;
	}
	return false;
}

bool CStackWatchList::OnEventAddressModeHex(IN WISP_MSG*pMsg)
{
	m_AddrShowMode=STACK_WATCH_ADDRESS_MOD;
	UpdateContext(m_CurAddr,true);
	return true;
}

bool CStackWatchList::OnEventOffsetModeHex(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	m_BaseActiveAddress=(ULPOS)GetItemData(hItem);
	m_AddrShowMode=STACK_WATCH_OFFSET_MOD;
	UpdateContext(m_CurAddr,true);
	return true;
}

bool CStackWatchList::OnEventRelativeToESP(IN WISP_MSG*pMsg)
{
	m_AddrShowMode=STACK_WATCH_REL_TO_ESP_MOD;
	UpdateContext(m_CurAddr,true);
	return true;
}

bool CStackWatchList::OnEventRelativeToEBP(IN WISP_MSG*pMsg)
{
	m_AddrShowMode=STACK_WATCH_REL_TO_EBP_MOD;
	UpdateContext(m_CurAddr,true);
	return true;
}

bool CStackWatchList::OnEventToggleAddressOrder(IN WISP_MSG*pMsg)
{
	ULPOS Address;
	
	if(m_AddrLowToHigh)	
		Address=m_CurAddr+m_nLinePerPage*sizeof(DWORD);	
	else	
		Address=m_CurAddr-m_nLinePerPage*sizeof(DWORD);	
	m_AddrLowToHigh=!m_AddrLowToHigh;
	UpdateContext(Address,true);
	return true;
}
