#include "StdAfx.h"
#include "Syser.h"

WISP_TOOLBAR_RES_ITEM DataViewToolbar[]=
{
	{DATAOPERATOR_ID_BYTEFLIP,			0,WISP_TBIS_BUTTON,WSTR("ByteFlip")},
	{DATAOPERATOR_ID_INVERSEBITS,		1,WISP_TBIS_BUTTON,WSTR("Inverse Bits")},
	{DATAOPERATOR_ID_SHIFTLEFT,			2,WISP_TBIS_BUTTON,WSTR("Shift Left")},
	{DATAOPERATOR_ID_SHIFTRIGHT,		3,WISP_TBIS_BUTTON,WSTR("Shift Right")},
	{DATAOPERATOR_ID_ROTATELEFT,		4,WISP_TBIS_BUTTON,WSTR("Rotate Left")},
	{DATAOPERATOR_ID_ROTATERIGHT,		5,WISP_TBIS_BUTTON,WSTR("Rotate Right")},
	{DATAOPERATOR_ID_BLOCKSHIFTLEFT,	6,WISP_TBIS_BUTTON,WSTR("Block Shift Left")},
	{DATAOPERATOR_ID_BLOCKSHIFTRIGHT,	7,WISP_TBIS_BUTTON,WSTR("Block Shift Right")},
	{DATAOPERATOR_ID_XOR,				8,WISP_TBIS_BUTTON,WSTR("XOR")},
	{DATAOPERATOR_ID_OR,				9,WISP_TBIS_BUTTON,WSTR("OR")},
	{DATAOPERATOR_ID_AND,				10,WISP_TBIS_BUTTON,WSTR("AND")},
	//	WISP_TOOLBAR_RES_SEPARATOR,
	{DATAOPERATOR_ID_CHANGESIGN,		11,WISP_TBIS_BUTTON,WSTR("Change Sign")},
	{DATAOPERATOR_ID_ADD,				12,WISP_TBIS_BUTTON,WSTR("Add")},
	{DATAOPERATOR_ID_SUBTRACT,			13,WISP_TBIS_BUTTON,WSTR("Subtract")},
	{DATAOPERATOR_ID_MULTIPLY,			14,WISP_TBIS_BUTTON,WSTR("Multiply")},
	{DATAOPERATOR_ID_DIVIDE,			15,WISP_TBIS_BUTTON,WSTR("Divide")},
	{DATAOPERATOR_ID_MOD,				16,WISP_TBIS_BUTTON,WSTR("Mod")},
	{DATAOPERATOR_ID_UPPERCASE,			17,WISP_TBIS_BUTTON,WSTR("Upper Case")},
	{DATAOPERATOR_ID_LOWERCASE,			18,WISP_TBIS_BUTTON,WSTR("Lower Case")},
	{DATAOPERATOR_ID_INVERSECASE,		19,WISP_TBIS_BUTTON,WSTR("Inverse Case")},
	WISP_TOOLBAR_RES_END
};


WISP_MENU_RES_ITEM OperatorMenu[]=
{
	{WSTR("Open new data view at "),EVENT_ID_SHOW_DATA_NEWWND,14*16},
	{WSTR("Show Data                  Enter"),EVENT_ID_SHOW_DATA,14*16},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Open new code view at "),EVENT_ID_DASM_ADDRESS_NEWWND,13*16+15},
	{WSTR("Disassemble code at %08X   Shift+Enter"),EVENT_ID_DASM_ADDRESS,13*16+15},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Data Operator Toolbar          Ctrl+T"),EVENT_ID_DATAVIEW_TOOLBAR,7*16+6},
	{WSTR("Show offset                    Ctrl+S"),EVENT_ID_DATA_SHOW_OFFICE,14*16+2},
	WISP_MENU_RES_SEPARATOR,	
	{WSTR("Address Mode                   Ctrl+O"),EVENT_ID_TOGGLE_ADDRESS_MODE,14*16+2},
	WISP_MENU_RES_SEPARATOR,	
	{WSTR("Float mode                     Ctrl+M"),EVENT_ID_TOGGLE_FLOAT_MODE,14*16+2},
	WISP_MENU_RES_SEPARATOR,	
	{WSTR("Copy selected data             Shift+X"),EVENT_ID_COPY_SEL_VALUE,2*16+3},
	{WSTR("Copy selected data             Ctrl+X"),EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR,8*16+2},
	{WSTR("Copy data as C source          Ctrl+Z"),EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE,8*16+2},	
	{WSTR("Copy value                     Ctrl+Enter"),EVENT_ID_COPY_VALUE_TO_CLIPBOARD,16*16+0},
	
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CDataView)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispHexWnd)

WISP_MSG_EVENT_MAP_BEGIN(CDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_DATA,				OnEventShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_DASM_ADDRESS,			OnEventDasmAddr)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_PHYS_ADDR,			OnEventShowPhysAddr)
	WISP_MSG_EVENT_MAP(EVENT_ID_DISASSEMBLE_PHYS_ADDR,	OnEventDasmPhysAddr)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_DATA_NEWWND,		OnEventShowDataNewWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_DASM_ADDRESS_NEWWND,	OnEventDasmAddrNewWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_DATAVIEW_TOOLBAR,		OnEventShowToolbar)
	WISP_MSG_EVENT_MAP(EVENT_ID_DATA_SHOW_OFFICE,		OnEventShowOffset)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_BYTEFLIP,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_INVERSEBITS,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_SHIFTLEFT,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_SHIFTRIGHT,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_ROTATELEFT,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_ROTATERIGHT,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_BLOCKSHIFTLEFT,	OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_BLOCKSHIFTRIGHT,	OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_XOR,				OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_OR,				OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_AND,				OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_CHANGESIGN,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_ADD,				OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_SUBTRACT,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_MULTIPLY,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_DIVIDE,			OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_MOD,				OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_UPPERCASE,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_LOWERCASE,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(DATAOPERATOR_ID_INVERSECASE,		OnEventDataOperation)
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_ADDRESS_MODE,	OnEventToggleAddressMode)
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_FLOAT_MODE,		OnEventToggleFloatMode)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_0,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_1,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_2,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_3,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_4,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_5,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_6,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_7,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_DATAVIEW_8,		OnActiveDataView)
	WISP_MSG_EVENT_MAP(EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW,OnGotoDataViewByValue)
	WISP_MSG_EVENT_MAP(EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW_WITH_OFFSET,OnGotoDataViewByValue)
	
	WISP_MSG_EVENT_MAP(EVENT_ID_FOLLOW_VALUE_TO_CODEVIEW,OnGotoCodeViewByValue)
	WISP_MSG_EVENT_MAP(EVENT_ID_COPY_VALUE_TO_CLIPBOARD,OnCopyValueToClipboard)
	WISP_MSG_EVENT_MAP(EVENT_ID_COPY_CARETPOSITION_TO_CLIPBOARD,OnCopyAddressToClipboard)
	WISP_MSG_EVENT_MAP(EVENT_ID_COPY_SEL_VALUE,OnCopySelectValue);
	WISP_MSG_EVENT_MAP(EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR,OnCopySelectValue)
	WISP_MSG_EVENT_MAP(EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE,OnCopySelectValue)
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTO_NEXT_POS,OnNextPos)
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTO_PREV_POS,OnPrevPos)
	//WISP_MSG_EVENT_MAP(EVENT_ID_ADDRESS_MODE_HEX,		OnEventAddressModeHex)
	//WISP_MSG_EVENT_MAP(EVENT_ID_OFFSET_MODE_HEX,		OnEventOffsetModeHex)
WISP_MSG_EVENT_MAP_END

bool CDataView::OnCreate(IN WISP_MSG*pMsg)
{	
	m_MenuShowPos=-1;
	m_DataOperatorAddr=-1;
	m_PopupMenu.CreatePopupMenu(OperatorMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));	
	m_Style|=WISP_HEX_WS_RELATIVE_SCROLL;
	m_Toolbar.CreateEx(this,0,-1,EVENT_ID_DATAVIEW_TOOLBAR,WISP_WS_NULL);
	m_Toolbar.LoadToolbar(WispTKDIBList("\\SyserApp\\Operation.bmp",16,16),DataViewToolbar);
	m_Toolbar.Show(WISP_SH_HIDDEN);	
	AttachShortcutKey();
	return true;
}


void CDataView::AttachShortcutKey()
{
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_0,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_1,					EVENT_ID_ACTIVE_DATAVIEW_0);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_1,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_2,					EVENT_ID_ACTIVE_DATAVIEW_1);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_2,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_3,					EVENT_ID_ACTIVE_DATAVIEW_2);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_3,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_4,					EVENT_ID_ACTIVE_DATAVIEW_3);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_4,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_5,					EVENT_ID_ACTIVE_DATAVIEW_4);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_5,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_6,					EVENT_ID_ACTIVE_DATAVIEW_5);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_6,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_7,					EVENT_ID_ACTIVE_DATAVIEW_6);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_7,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_8,					EVENT_ID_ACTIVE_DATAVIEW_7);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_DATAVIEW_8,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_0,					EVENT_ID_ACTIVE_DATAVIEW_8);
	if(gpSyser->AttachShortcutKey(EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_RETURN,							EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW);
	if(gpSyser->AttachShortcutKey(EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW_WITH_OFFSET,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_RETURN|WISP_MOD_ALT|WISP_MOD_CTRL,	EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW_WITH_OFFSET);

	if(gpSyser->AttachShortcutKey(EVENT_ID_FOLLOW_VALUE_TO_CODEVIEW,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_RETURN,			EVENT_ID_FOLLOW_VALUE_TO_CODEVIEW);
	if(gpSyser->AttachShortcutKey(EVENT_ID_COPY_VALUE_TO_CLIPBOARD,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL | WISP_VK_RETURN,			EVENT_ID_COPY_VALUE_TO_CLIPBOARD);
	if(gpSyser->AttachShortcutKey(EVENT_ID_COPY_CARETPOSITION_TO_CLIPBOARD,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT| WISP_VK_RETURN,				EVENT_ID_COPY_CARETPOSITION_TO_CLIPBOARD);
	if(gpSyser->AttachShortcutKey(EVENT_ID_COPY_SEL_VALUE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL| WISP_VK_X,					EVENT_ID_COPY_SEL_VALUE);
	if(gpSyser->AttachShortcutKey(EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT| WISP_VK_X,					EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR);
	if(gpSyser->AttachShortcutKey(EVENT_ID_TOGGLE_ADDRESS_MODE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL| WISP_VK_O,					EVENT_ID_TOGGLE_ADDRESS_MODE );

	if(gpSyser->AttachShortcutKey(EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL| WISP_VK_Z,					EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE );

	if(gpSyser->AttachShortcutKey(EVENT_ID_GOTO_NEXT_POS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_OEM_PLUS,					EVENT_ID_GOTO_NEXT_POS);
	if(gpSyser->AttachShortcutKey(EVENT_ID_GOTO_PREV_POS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_OEM_MINUS,					EVENT_ID_GOTO_PREV_POS );

	if(gpSyser->AttachShortcutKey(EVENT_ID_TOGGLE_FLOAT_MODE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL| WISP_VK_M,					EVENT_ID_TOGGLE_FLOAT_MODE );
	if(gpSyser->AttachShortcutKey(EVENT_ID_DATA_SHOW_OFFICE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL| WISP_VK_S,					EVENT_ID_DATA_SHOW_OFFICE );
	if(gpSyser->AttachShortcutKey(EVENT_ID_DATAVIEW_TOOLBAR,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL| WISP_VK_T,					EVENT_ID_DATAVIEW_TOOLBAR );

}

bool CDataView::OnGotoDataViewByValue(IN WISP_MSG* pMsg)
{
	DWORD Address,Value;
	DWORD Offset=0;
	ULPOS Pos;
	if(CalcPonitPos(&m_CaretPos,&Pos)==false)
		return true;
	if(pMsg && pMsg->Command.CmdID==EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW_WITH_OFFSET)
	{
		Offset= Pos-m_CurAddr;
	}
			
	Pos = Pos+ (m_ShowLength- 1 - (m_CaretIndex % (m_ShowLength*3))/2);
	if(ReadData(Pos,(BYTE*)&Address,4)==0)
		return true;
	if(Address!=-1)
	{		
		Address-=Offset;
		if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		{
			ViewAddress(Address);	
		}
	}
	return true;
}

bool CDataView::OnGotoDataViewByValueWithOffset(IN WISP_MSG* pMsg)
{


	DWORD Address,Value;
	ULPOS Pos;
	if(CalcPonitPos(&m_CaretPos,&Pos)==false)
		return true;
	Pos = Pos+ (m_ShowLength- 1 - (m_CaretIndex % (m_ShowLength*3))/2);
	if(ReadData(Pos,(BYTE*)&Address,4)==0)
		return true;
	if(Address!=-1)
	{
		if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		{
			ViewAddress(Address);	
		}
	}
	return true;
}


bool CDataView::OnGotoCodeViewByValue(IN WISP_MSG* pMsg)
{
	DWORD Address;
	ULPOS Pos,Value;
	CCodeView*pCodeWnd;
	if(CalcPonitPos(&m_CaretPos,&Pos)==false)
		return true;
	Pos = Pos+ (m_ShowLength- 1 - (m_CaretIndex % (m_ShowLength*3))/2);
	if(ReadData(Pos,(BYTE*)&Address,4)==0)
		return true;
	if(Address!=-1)
	{
		if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
		{
			pCodeWnd=ACTIVE_CODE_VIEW;
			if(pCodeWnd)
				pCodeWnd->SetStartAddress(Address,true);
		}

	}

	return true;
}

bool CDataView::OnCopyValueToClipboard(IN WISP_MSG* pMsg)
{
	DWORD Address;
	ULPOS Pos;
	WISP_CHAR AddressString[10];
	CWispString ClipboardString;
	bool bSeparator=true;
	ClipboardString.Empty();
	if(CalcPonitPos(&m_CaretPos,&Pos)==false)
		return true;
	Pos = Pos+ (m_ShowLength- 1 - (m_CaretIndex % (m_ShowLength*3))/2);
	if(ReadData(Pos,(BYTE*)&Address,4)==0)
		return true;
	if(Address==-1)
		return true;
	TSPrintf(AddressString,WSTR("%08x"),Address);			
	ClipboardString+=AddressString;
	m_pWispBase->SetClipboardString(ClipboardString);
	return true;
}

bool CDataView::OnCopyAddressToClipboard(IN WISP_MSG* pMsg)
{
	ULPOS Pos;
	WISP_CHAR AddressString[10];
	CWispString ClipboardString;
	bool bSeparator=true;
	if(CalcPonitPos(&m_CaretPos,&Pos)==false)
		return true;
	TSPrintf(AddressString,WSTR("%08x"),Pos);			
	ClipboardString+=AddressString;
	m_pWispBase->SetClipboardString(ClipboardString);
	return true;
}


bool CDataView::OnCopySelectValue(IN WISP_MSG* pMsg)
{
	WISP_CHAR AddressString[256];
	BYTE Vaule[16];
	CWispString ClipboardString;
	bool bSeparator=true;
	ClipboardString.Empty();
	
	if(!m_bSelect)
		return true;

	if(pMsg->Command.CmdID==EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR)
		bSeparator=false;

	if(pMsg->Command.CmdID==EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE)
	{
		DWORD dwCount;		
		dwCount = m_SelEnd - m_SelStart + 1;
		ClipboardString += WSTR("// Generated by Syser software's Syser Debugger v");
		TStrCpy(AddressString,VER_PRODUCTVERSION_STR );
		ClipboardString += AddressString;
		ClipboardString += WSTR("\r\n//   http://www.sysersoft.com\r\n");	
		TSPrintf(AddressString,WSTR("unsigned char rawData[%d] =\r\n{"),dwCount);
		ClipboardString+=AddressString;
		for(DWORD i = 0; i < dwCount; i++)
		{
			if((i%16)==0)
				ClipboardString+=WSTR("\r\n\t");
			if(gpSyser->m_pDebugger->ReadMemory(m_SelStart+i,Vaule,1)!=1)
				break;			
			if( i != (dwCount-1))
				TSPrintf(AddressString,WSTR("0x%02X, "),Vaule[0]);			
			else
				TSPrintf(AddressString,WSTR("0x%02X"),Vaule[0]);			
			ClipboardString+=AddressString;			
		}
		ClipboardString+=WSTR("\r\n}\n");
		m_pWispBase->SetClipboardString(ClipboardString);		
		return true;
	}
	DWORD dwCount;
	dwCount = m_SelEnd - m_SelStart + 1;
	for(DWORD i = 0; i < dwCount/m_ShowLength; i++)
	{
		if(gpSyser->m_pDebugger->ReadMemory(m_SelStart+i*m_ShowLength,Vaule,m_ShowLength)!=m_ShowLength)
			break;
		switch(m_ShowLength)
		{
		case 1:
			TSPrintf(AddressString,WSTR("%02x"),Vaule[0]);
			break;
		case 2:
			TSPrintf(AddressString,WSTR("%04x"),*(WORD*)&Vaule[0]);
			break;
		case 4:
			TSPrintf(AddressString,WSTR("%08x"),*(DWORD*)&Vaule[0]);
			break;
		}
		ClipboardString+=AddressString;
		if(bSeparator && i != dwCount - 1)
			ClipboardString+=L" ";
	}
	m_pWispBase->SetClipboardString(ClipboardString);				
	return true;
}
bool CDataView::OnActiveDataView(IN WISP_MSG*pMsg)
{
	DWORD Index;
	Index = pMsg->Command.CmdID;
	Index -= EVENT_ID_ACTIVE_DATAVIEW_0;
	DWORD NewAddr;
	CDataView* pDataView =(CDataView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetWnd(Index);
	if(pDataView==NULL)
	{
		pDataView =(CDataView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();
		NewAddr = ACTIVE_DATA_VIEW->m_CurAddr;
		pDataView = ADD_DATA_VIEW(pDataView);
		if(pDataView==NULL)
			return false;
	}
	else
	{
		gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.ChangeActiveWnd(pDataView);
	}
	return true;
}


bool CDataView::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

bool CDataView::OnKeyEvent(IN WISP_MSG*pMsg)
{	
	DATAHOTKEYMAP::IT FindIT;
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
			PopupMenu(pMsg);
			return false;			
		case WISP_VK_LBUTTON:
			if(CalcPonitPos(&pMsg->MsgMouseWndPT,&m_DataOperatorAddr)==false)
				m_DataOperatorAddr=m_CurAddr;
			return true;			
		case WISP_VK_W:
			{
				int SizeXorY;
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.GetWndSpace(0,SizeXorY);
				if(SizeXorY>10)
					gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.ResizeWndSpace(0,SizeXorY-10);
				else
					gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.ResizeWndSpace(0,0);
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.AdjustWndPos();
				return false;
			}

			break;
		case WISP_VK_S:
			{
				int SizeXorY;
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.GetWndSpace(0,SizeXorY);				
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.ResizeWndSpace(0,SizeXorY+10);
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.AdjustWndPos();
				return false;

			}
			break;
		}
		
	}
	return true;	
}

DWORD	CDataView::FindShortcutKey(DWORD CmdID)
{
	DATAHOTKEYMAP::IT BeginIT,EndIT;

	BeginIT = m_HotKeyMap.Begin();
	EndIT = m_HotKeyMap.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		if(*BeginIT == CmdID)
			return BeginIT.Key();
	}
	return 0;
}

void CDataView::PopupMenu(IN WISP_MSG*pMsg)
{
	bool bValidAddress=false;
	bool bValidAddress1=false;
	HANDLE hItem;
	DWORD TmpValue;
	DWORD dwAddress=0;
	WCHAR wHotKeyBuffer[50];
	WCHAR szBuffer[256];
	m_MenuShowPos = -1;
	bValidAddress = false;
	DATAHOTKEYMAP::IT FindIT;
	if(CalcPonitPos(&pMsg->MsgMouseWndPT,&m_MenuShowPos))
	{
		dwAddress=m_MenuShowPos;
		if(gpSyser->m_KeyMap[WISP_VK_SHIFT])// 当右键菜单弹出时， 判断 shift 键盘是否被按下。 主要用来浏览一个链表的结构
			dwAddress -= m_CurAddr ;
		else
			dwAddress=0;
		bValidAddress1=(ReadData(m_MenuShowPos,(BYTE*)&m_MenuShowPos,4)==4); //bValidAddress1 判断当前鼠标位置内存是否可读
		if(bValidAddress1)
		{
			bValidAddress=(ReadData(m_MenuShowPos,(BYTE*)&TmpValue,4)==4);//bValidAddress 判断当前鼠标位置的 dword 做为一个新的地址是否可读
		}
	}
	if(bValidAddress)
	{				
		m_MenuShowPos-=dwAddress;
		hItem = m_PopupMenu.GetItem(EVENT_ID_SHOW_DATA_NEWWND);
		TSPrintf(szBuffer,WSTR("Open new data view at %08X"),m_MenuShowPos);
		m_PopupMenu.SetItemText(hItem,szBuffer);
		
		hItem = m_PopupMenu.GetItem(EVENT_ID_SHOW_DATA);
		gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW),wHotKeyBuffer);	
		TSPrintf(szBuffer,WSTR("Display data at %08X           %s"),m_MenuShowPos,wHotKeyBuffer);
		m_PopupMenu.SetItemText(hItem,szBuffer);
		
		hItem = m_PopupMenu.GetItem(EVENT_ID_DASM_ADDRESS_NEWWND);
		TSPrintf(szBuffer,WSTR("Open new code view at %08X"),m_MenuShowPos);
		m_PopupMenu.SetItemText(hItem,szBuffer);

		hItem = m_PopupMenu.GetItem(EVENT_ID_DASM_ADDRESS);	
		gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_FOLLOW_VALUE_TO_CODEVIEW),wHotKeyBuffer);	
		TSPrintf(szBuffer,WSTR("Disassemble code at %08X       %s"),m_MenuShowPos,wHotKeyBuffer);
		m_PopupMenu.SetItemText(hItem,szBuffer);
	}


	hItem = m_PopupMenu.GetItem(EVENT_ID_TOGGLE_ADDRESS_MODE);
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_TOGGLE_ADDRESS_MODE),wHotKeyBuffer);		
	if(GetAddressMode()==ADDRESS_MODE_HEX)
	{
		TSPrintf(szBuffer,WSTR("Offset Mode                    %s"),wHotKeyBuffer);
	}
	else
	{
		TSPrintf(szBuffer,WSTR("Address Mode                   %s"),wHotKeyBuffer);		
	}
	m_PopupMenu.SetItemText(hItem,szBuffer);
	
	hItem = m_PopupMenu.GetItem(EVENT_ID_COPY_SEL_VALUE);
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_COPY_SEL_VALUE),wHotKeyBuffer);		
	TSPrintf(szBuffer,WSTR("Copy selected data             %s"),wHotKeyBuffer);
	m_PopupMenu.SetItemText(hItem,szBuffer);

	hItem = m_PopupMenu.GetItem(EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR);
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR),wHotKeyBuffer);	
	TSPrintf(szBuffer,WSTR("Copy selected data             %s"),wHotKeyBuffer);
	m_PopupMenu.SetItemText(hItem,szBuffer);

	hItem = m_PopupMenu.GetItem(EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE);
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE),wHotKeyBuffer);	
	TSPrintf(szBuffer,WSTR("Copy data as C source          %s"),wHotKeyBuffer);
	m_PopupMenu.SetItemText(hItem,szBuffer);

	hItem = m_PopupMenu.GetItem(EVENT_ID_COPY_VALUE_TO_CLIPBOARD);
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_COPY_VALUE_TO_CLIPBOARD),wHotKeyBuffer);	
	TSPrintf(szBuffer,WSTR("Copy value                     %s"),wHotKeyBuffer);
	m_PopupMenu.SetItemText(hItem,szBuffer);


	hItem = m_PopupMenu.GetItem(EVENT_ID_DATAVIEW_TOOLBAR);
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_DATAVIEW_TOOLBAR),wHotKeyBuffer);	
	TSPrintf(szBuffer,WSTR("Data Operator Toolbar          %s"),wHotKeyBuffer);
	m_PopupMenu.SetItemText(hItem,szBuffer);

	hItem = m_PopupMenu.GetItem(EVENT_ID_DATA_SHOW_OFFICE);
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_DATA_SHOW_OFFICE),wHotKeyBuffer);	
	TSPrintf(szBuffer,WSTR("Show offset                    %s"),wHotKeyBuffer);
	m_PopupMenu.SetItemText(hItem,szBuffer);


	hItem = m_PopupMenu.GetItem(EVENT_ID_TOGGLE_FLOAT_MODE);		
	gpSyser->m_MainFrame.m_KeyMapForm.GetHotKeyName(FindShortcutKey(EVENT_ID_TOGGLE_FLOAT_MODE),wHotKeyBuffer);	
	if(IsFloatMode())
		TSPrintf(szBuffer,WSTR("Fixed mode                     %s"),wHotKeyBuffer);		
	else
		TSPrintf(szBuffer,WSTR("Float mode                     %s"),wHotKeyBuffer);
	m_PopupMenu.SetItemText(hItem,szBuffer);

	m_PopupMenu.EnableItem(EVENT_ID_TOGGLE_FLOAT_MODE,!m_FloatString.IsEmpty());
	m_PopupMenu.EnableItem(EVENT_ID_SHOW_DATA_NEWWND,bValidAddress);
	m_PopupMenu.EnableItem(EVENT_ID_SHOW_DATA,bValidAddress);
	m_PopupMenu.EnableItem(EVENT_ID_DASM_ADDRESS_NEWWND,bValidAddress);
	m_PopupMenu.EnableItem(EVENT_ID_DASM_ADDRESS,bValidAddress);
	m_PopupMenu.EnableItem(EVENT_ID_COPY_SEL_VALUE,m_bSelect);
	m_PopupMenu.EnableItem(EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR,m_bSelect);
	m_PopupMenu.EnableItem(EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE,m_bSelect);
	m_PopupMenu.EnableItem(EVENT_ID_COPY_VALUE_TO_CLIPBOARD,bValidAddress1);
	m_PopupMenu.Popup();
}

void CDataView::OnAddrChange()
{
	WISP_CHAR szBuffer[64];
	int Index = 0;
	for(CTabWndList::IT Iter=gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.m_WndList.Begin();
		Iter!=gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.m_WndList.End();Iter++)
	{
		if(Iter->pWnd==this)
		{
			TSPrintf(szBuffer,WSTR("%08X"),m_CurAddr);
			gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetTabText(Index,szBuffer);
		}
		Index++;
	}
}

void CDataView::OnDataChange()
{
	UPDATE_CONTEXT();
}

bool CDataView::OnEventShowData(IN WISP_MSG*pMsg)
{
	DWORD Address=GetPopMenuDataPos();
	DWORD Value;
	if(Address!=-1)
	{
		if(gpSyser->m_pDebugger->ReadMemory(Address,&Value,sizeof(Value))==sizeof(Value))
			ViewAddress(Address);
	}
	return true;
}

bool CDataView::OnEventShowDataNewWnd(IN WISP_MSG*pMsg)
{
	DWORD Address=GetPopMenuDataPos();
	CMultiDataView* pMultiDataView;
	pMultiDataView = (CMultiDataView*)m_ParentWnd;
	pMultiDataView->InsertView(this);
	pMultiDataView->SetActiveAddress(Address);
	return true;
}

bool CDataView::OnEventDasmAddrNewWnd(IN WISP_MSG*pMsg)
{
	CCodeView*pCodeWnd;
	DWORD Address=GetPopMenuDataPos();
	if(Address!=-1)
	{
		pCodeWnd = ADD_CODE_VIEW();
		if(pCodeWnd)
			pCodeWnd->SetStartAddress(Address,true);
	}
	return true;
}

bool CDataView::OnEventDasmAddr(IN WISP_MSG*pMsg)
{
	CCodeView*pCodeWnd;
	DWORD Address=GetPopMenuDataPos();
	if(Address!=-1)
	{
		pCodeWnd=ACTIVE_CODE_VIEW;
		if(pCodeWnd)
			pCodeWnd->SetStartAddress(Address,true);
	}
	return true;
}

bool CDataView::OnEventShowPhysAddr(IN WISP_MSG*pMsg)
{
#if CODE_OS_NT_DRV
	DWORD dwAddr=GetPopMenuDataPos();
	if(dwAddr!=-1)
	{
		if(MapToVAddr(dwAddr,&dwAddr))
			ViewAddress(dwAddr);
	}
#endif
	return true;
}
int	CDataView::GetStartLine()
{
	if(m_Toolbar.IsVisible()==false)
		return CWispHexWnd::GetStartLine();
	return 2;
};
bool CDataView::OnEventShowToolbar(IN WISP_MSG*pMsg)
{
	if(m_Toolbar.IsVisible()==false)
	{
		m_Toolbar.Show();
	}
	else
	{
		m_Toolbar.Show(WISP_SH_HIDDEN);
	}
	
	return true;
}

bool CDataView::OnEventDasmPhysAddr(IN WISP_MSG*pMsg)
{
#if CODE_OS_NT_DRV
	CCodeView*pCodeWnd;
	DWORD dwAddr=GetPopMenuDataPos();
	if(dwAddr!=-1)
	{
		pCodeWnd=(CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
		if(pCodeWnd)
		{
			if(MapToVAddr(dwAddr,&dwAddr))						
				pCodeWnd->SetStartAddress(dwAddr);
		}
	}
#endif
	return true;
}

ULSIZE CDataView::ReadData(ULPOS Address,BYTE*Buffer,ULSIZE Size)
{
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return 0;
	return gpSyser->m_pDebugger->ReadMemory(Address,Buffer,Size);
}

ULSIZE CDataView::WriteData(ULPOS Address,BYTE*Buffer,ULSIZE Size)
{
	ULSIZE dwSize;
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return 0;
	dwSize= gpSyser->m_pDebugger->WriteMemory(Address,Buffer,Size);
	return dwSize;
}

DWORD CDataView::GetPopMenuDataPos()
{
	return m_MenuShowPos;
}

DWORD CDataView::GetDataOperatorPos()
{
	return m_DataOperatorAddr;
}

bool CDataView::OnChar(IN WISP_MSG*pMsg)
{
	return true;
}

bool CDataView::GetDataOperatorParam(DWORD* BeginAddr,DWORD* EndAddr,DWORD* DataWidth)
{
	if(m_bSelect)
	{
		*BeginAddr=m_SelStart;
		*EndAddr=m_SelEnd;
		if(m_SelStart==m_SelEnd)
			*EndAddr+=1;
	}
	else
	{
		*BeginAddr=GetDataOperatorPos();
		if(*BeginAddr==-1)
			*BeginAddr = m_CurAddr;
		*EndAddr=*BeginAddr+m_ShowLength;
	}
	*DataWidth=m_ShowLength;
	return true;
}

bool CDataView::OnEventDataOperation(IN WISP_MSG*pMsg)
{
	DWORD BeginAddr,EndAddr,DataWidth;
	GetDataOperatorParam(&BeginAddr,&EndAddr,&DataWidth);
	m_DataOperatorDlg.CreateForm(NULL,WISP_SH_MODAL_BLOCK,BeginAddr,EndAddr,DataWidth,pMsg->Command.CmdID);
	return  true;
}
bool CDataView::OnEventToggleAddressMode(IN WISP_MSG*pMsg)
{
	SetAddressMode(1-GetAddressMode(),m_CurAddr);	
	Update();
	return true;
}
bool CDataView::OnEventToggleFloatMode(IN WISP_MSG*pMsg)
{
	ToggleFloatMode();
	return true;
}


bool CDataView::OnEventShowOffset(IN WISP_MSG*pMsg)
{
	ToggleShowOffset();
	return true;
}
ULPOS CDataView::GetFloatAddress(CStrW& CmdStr)
{
	ULPOS Address;
	if(CmdStr.IsEmpty())
		return m_CurAddr;
	if(CALCEXP(CmdStr.m_pData,&Address)==false)
		return m_CurAddr;
	return Address;
}
