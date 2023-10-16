#include "StdAfx.h"
#include "RunTraceWnd.h"
#include "Syser.h"

WISP_MSG_MAP_BEGIN(CRunTraceWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose) 
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CRunTraceWnd)
	WISP_MSG_EVENT_MAP(WISP_ID_COPY,OnEventCopy)
WISP_MSG_EVENT_MAP_END

CRunTraceWnd::CRunTraceWnd()
{

}

CRunTraceWnd::~CRunTraceWnd()
{

}

void CRunTraceWnd::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WSTR("Run Trace List"),0,0,500,280,NULL,CMD_ID_RUN_TRACE,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL|WISP_WLS_EMPTY_SEL_RECT);
		Center();
	}	
}

bool CRunTraceWnd::OnClose(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();	
	return true;
}

bool CRunTraceWnd::OnEventCopy(IN WISP_MSG* pMsg)
{
	return true;
}

void CRunTraceWnd::UpdateContext()
{
	int i = 0,Count;
	HANDLE hItem;
	DWORD Address;
	WCHAR buf[200];
	WCHAR buf1[20];
	PSTRUNTRACE pRunTrace;
	CCodeView*pCodeView;
	X86_REG_CONTEXT RegContext;
	WISP_COLOR_CHAR szColorBuffer[256];
	DWORD RegModifyMask;
	if(IsWindow()==false)
		return;
	ClearChildItem();
	pCodeView = (CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	Count = gpSyser->m_MainFrame.m_SystemExplorer.m_TraceCount-1;
	pRunTrace = gpSyser->m_MainFrame.m_SystemExplorer.m_RunTrace.GetTraceByIndex(i);
	while(pRunTrace)
	{
		
		szColorBuffer[0]=0;
		Address = pRunTrace->CodeViewStartAddress+pRunTrace->EIPOffset;
		TSPrintf(buf,WSTR("%d"),Count - i);
		
		hItem = InsertItem(buf);
		SetItemTextColor(hItem,0,ColorOption.clrText);
		SetItemData(hItem,0,i);

		SetItemNum(hItem,1,Address,WSTR("%08X"));
		SetItemTextColor(hItem,1,ColorOption.clrCVAddr);
		if(pCodeView)
			pCodeView->ColorDasm(Address,MAX_INSTR_LEN,szColorBuffer);
		SetItemColorText(hItem,2,szColorBuffer);
		buf[0]=0;
		gpSyser->m_MainFrame.m_SystemExplorer.m_RunTrace.GetRegisterContext(i,&RegContext,&RegModifyMask);
		if(RegModifyMask!=0)
		{
			if(RegModifyMask&EAX_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("EAX=%08X "),RegContext.GeneReg[EAX_IDX]);
				TStrCat(buf,buf1);
			}
			if(RegModifyMask&EBX_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("EBX=%08X "),RegContext.GeneReg[EBX_IDX]);
				TStrCat(buf,buf1);
			}
			if(RegModifyMask&ECX_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("ECX=%08X "),RegContext.GeneReg[ECX_IDX]);
				TStrCat(buf,buf1);
			}
			if(RegModifyMask&EDX_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("EDX=%08X "),RegContext.GeneReg[EDX_IDX]);
				TStrCat(buf,buf1);
			}
			if(RegModifyMask&ESI_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("ESI=%08X "),RegContext.GeneReg[ESI_IDX]);
				TStrCat(buf,buf1);
			}
			if(RegModifyMask&EDI_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("EDI=%08X "),RegContext.GeneReg[EDI_IDX]);
				TStrCat(buf,buf1);
			}
			if(RegModifyMask&ESP_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("ESP=%08X "),RegContext.GeneReg[ESP_IDX]);
				TStrCat(buf,buf1);
			}
			if(RegModifyMask&EBP_MODIFY_BIT_MASK)
			{
				TSPrintf(buf1,WSTR("EBP=%08X "),RegContext.GeneReg[EBP_IDX]);
				TStrCat(buf,buf1);
			}
		}
		SetItemText(hItem,3,buf);
		SetItemTextColor(hItem,3,ColorOption.clrChgText);
		i++;pRunTrace = gpSyser->m_MainFrame.m_SystemExplorer.m_RunTrace.GetTraceByIndex(i);
	}
	if(hItem)
	{
		if(IsItemVisible(hItem)==false)
		{
			EnableVisible(hItem);
		}
	}
}

bool CRunTraceWnd::OnCreate(IN WISP_MSG* pMsg)
{
	m_SelectBKColor = ColorOption.clrSelectedFrame;
	m_ColorTable[COLOR_BK	   ]=ColorOption.clrCVBK;
	m_ColorTable[COLOR_ADDRESS ]=ColorOption.clrCVAddr;
	m_ColorTable[COLOR_PREFIX  ]=ColorOption.clrCVPrefix;
	m_ColorTable[COLOR_OPCODE  ]=ColorOption.clrCVOpCode;
	m_ColorTable[COLOR_REGISTER]=ColorOption.clrCVReg;
	m_ColorTable[COLOR_SEG_REG ]=ColorOption.clrCVSegReg;
	m_ColorTable[COLOR_IMMED   ]=ColorOption.clrCVImmed;
	m_ColorTable[COLOR_OPTR    ]=ColorOption.clrCVOptr;
	m_ColorTable[COLOR_SYMBOL  ]=ColorOption.clrCVSymbol;
	m_ColorTable[COLOR_COMMENT ]=ColorOption.clrCVComment;
	m_ColorTable[COLOR_KEYWORD ]=ColorOption.clrCVKeyword;
	m_ColorTable[COLOR_STR     ]=ColorOption.clrCVStr;
	m_ColorTable[COLOR_BPX_STRIP]=ColorOption.clrCVBPXStrip;
	m_ColorTable[COLOR_EIP_STRIP]=ColorOption.clrCVEIPStrip;
	m_ColorTable[COLOR_BPXEIP_STRIP]=ColorOption.clrCVBPXEIPStrip;
	m_ClientDC.SetColorTable(m_ColorTable);
	AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,181));
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	InsertColumn(WSTR("Back"),40);
	InsertColumn(WSTR("Address"),60);
	InsertColumn(WSTR("Instruction"),180);
	InsertColumn(WSTR("Modified Registers"),120);
	SetBGColor(SC_BLACK);
	UpdateContext();
	return true;
}

bool CRunTraceWnd::OnKeyEvent(IN WISP_MSG* pMsg)
{
	if(pMsg->KeyEvent.bKeyDown && pMsg->KeyEvent.KeyType == WISP_VK_RETURN)
	{
		OnMouseDBClick(NULL);
	}
	return true;
}

bool CRunTraceWnd::OnMouseDBClick(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	NUM_PTR NumPtr;
	hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	NumPtr = GetItemData(hItem);
	gpSyser->m_MainFrame.m_SystemExplorer.SetRunTrace((UINT)NumPtr);
	return true;
}