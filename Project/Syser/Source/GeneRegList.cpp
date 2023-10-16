#include "StdAfx.h"
#include "Syser.h"
#include "GeneRegList.h" 

WISP_MENU_RES_ITEM GeneRegMenu[]=
{
	{WSTR("Show Code "),EVENT_ID_SHOW_CODE,14*16},
	{WSTR("Show Data "),EVENT_ID_SHOW_DATA,13*16+15},
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CGeneRegList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CGeneRegList)
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_CODE,OnEventShowCode);
	WISP_MSG_EVENT_MAP(EVENT_ID_SHOW_DATA,OnEventShowData);

	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_EAX,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_EBX,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_ECX,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_EDX,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_ESP,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_EBP,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_ESI,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_EDI,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_DATAVIEW_EIP,OnShowData)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_EAX,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_EBX,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_ECX,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_EDX,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_ESP,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_EBP,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_ESI,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_EDI,OnShowCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_CODEVIEW_EIP,OnShowCode)

WISP_MSG_EVENT_MAP_END


CGeneRegList::CGeneRegList()
{
	STZeroMemory(m_PrevCPUReg);	
}

CGeneRegList::~CGeneRegList()
{
}

bool CGeneRegList::OnCreate(IN WISP_MSG*pMsg)
{
	m_ChgColor = ColorOption.clrChgText;
	m_NormalColor = ColorOption.clrText;
	m_SelectBKColor = ColorOption.clrSelectedFrame;
	m_X86RegPtr=X86_REG_PTR;

	
	if(m_Style & WISP_WS_CAPTION)
		AttachTitleDIB(WispTKDIBListDIB("\\Toolbar.bmp",16,16,52));

	SetDefaultTextColor(m_NormalColor);
	SetBGColor(ColorOption.clrBackground);

	m_PopupMenu.CreatePopupMenu(GeneRegMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_hMenuShowCode = m_PopupMenu.GetItem(EVENT_ID_SHOW_CODE);
	m_hMenuShowData = m_PopupMenu.GetItem(EVENT_ID_SHOW_DATA);

	int FontWidth = m_ClientDC.GetTextExtent(WSTR("X"));
	InsertColumn(WISP_STR("Register"),FontWidth*9);
	InsertColumn(WISP_STR("Value[F2]"),FontWidth*10,WISP_WLCS_EDITABLE);
	InsertColumn(WISP_STR("Context"),100);

	m_hLastItem = 
	m_hGeneRegItem[REG_GENE_EAX] = InsertItem(WISP_STR("EAX"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_EBX] = InsertItem(WISP_STR("EBX"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_ECX] = InsertItem(WISP_STR("ECX"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_EDX] = InsertItem(WISP_STR("EDX"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_ESI] = InsertItem(WISP_STR("ESI"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_EDI] = InsertItem(WISP_STR("EDI"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_EBP] = InsertItem(WISP_STR("EBP"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_ESP] = InsertItem(WISP_STR("ESP"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_EIP] = InsertItem(WISP_STR("EIP"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_EFL] = InsertItem(WISP_STR("EFLAG"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_AF] = InsertItem(WISP_STR("AF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_CF] = InsertItem(WISP_STR("CF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_DF] = InsertItem(WISP_STR("DF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_IF] = InsertItem(WISP_STR("IF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_OF] = InsertItem(WISP_STR("OF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_PF] = InsertItem(WISP_STR("PF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_SF] = InsertItem(WISP_STR("SF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_ZF] = InsertItem(WISP_STR("ZF"),m_hGeneRegItem[REG_GENE_EFL],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_CS] = InsertItem(WISP_STR("CS"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_DS] = InsertItem(WISP_STR("DS"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_ES] = InsertItem(WISP_STR("ES"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_FS] = InsertItem(WISP_STR("FS"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_GS] = InsertItem(WISP_STR("GS"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_SS] = InsertItem(WISP_STR("SS"),NULL,WISP_WLIS_NORMAL);

	m_hGeneRegItem[REG_GENE_CS_BASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_CS],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_DS_BASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_DS],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_ES_BASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_ES],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_FS_BASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_FS],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_GS_BASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_GS],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_SS_BASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_SS],WISP_WLIS_NORMAL);
#ifdef CODE_OS_NT_DRV	
	m_hGeneRegItem[REG_GENE_GDTR] = InsertItem(WISP_STR("GDTR"),NULL,WISP_WLIS_NORMAL);	
	m_hGeneRegItem[REG_GENE_IDTR] = InsertItem(WISP_STR("IDTR"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_LDTR] = InsertItem(WISP_STR("LDTR"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_TR] = InsertItem(WISP_STR("TR"),NULL,WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_GDTRBASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_GDTR],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_GDTRLIMIT] = InsertItem(WISP_STR("Limit"),m_hGeneRegItem[REG_GENE_GDTR],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_IDTRBASE] = InsertItem(WISP_STR("Base"),m_hGeneRegItem[REG_GENE_IDTR],WISP_WLIS_NORMAL);
	m_hGeneRegItem[REG_GENE_IDTRLIMIT] = InsertItem(WISP_STR("Limit"),m_hGeneRegItem[REG_GENE_IDTR],WISP_WLIS_NORMAL);
#endif
	for(int n=0;n<REG_GENE_REGCOUNT;n++)
	{
		SetItemData(m_hGeneRegItem[n],0,n);
	}
	ResetContext();

	AttachShortcutKey();

	return true;
}
void	CGeneRegList::AttachShortcutKey()
{
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_EAX,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_1,EVENT_ID_SET_DATAVIEW_EAX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_EBX,m_HotKeyMap)==0)	
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_2,EVENT_ID_SET_DATAVIEW_EBX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_ECX,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_3,EVENT_ID_SET_DATAVIEW_ECX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_EDX,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_4,EVENT_ID_SET_DATAVIEW_EDX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_ESP,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_5,EVENT_ID_SET_DATAVIEW_ESP);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_EBP,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_6,EVENT_ID_SET_DATAVIEW_EBP);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_ESI,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_7,EVENT_ID_SET_DATAVIEW_ESI);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_EDI,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_8,EVENT_ID_SET_DATAVIEW_EDI);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_DATAVIEW_EIP,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_SHIFT | WISP_VK_9,EVENT_ID_SET_DATAVIEW_EIP);

	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_EAX,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_1,EVENT_ID_SET_CODEVIEW_EAX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_EBX,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_2,EVENT_ID_SET_CODEVIEW_EBX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_ECX,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_3,EVENT_ID_SET_CODEVIEW_ECX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_EDX,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_4,EVENT_ID_SET_CODEVIEW_EDX);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_ESP,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_5,EVENT_ID_SET_CODEVIEW_ESP);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_EBP,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_6,EVENT_ID_SET_CODEVIEW_EBP);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_ESI,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_7,EVENT_ID_SET_CODEVIEW_ESI);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_EDI,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_8,EVENT_ID_SET_CODEVIEW_EDI);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SET_CODEVIEW_EIP,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_9,EVENT_ID_SET_CODEVIEW_EIP);
}
bool CGeneRegList::OnClose(IN WISP_MSG* pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

bool CGeneRegList::OnEventShowCode(IN WISP_MSG*pMsg)
{	
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	DWORD Address;
	if(USHexStrToNum((WISP_PCSTR)GetItemText(hItem,1),&Address)==false)
		return true;
	VIEW_CODE(Address,true);
	return true;
}



bool CGeneRegList::OnEventShowData(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	DWORD Address;
	if(USHexStrToNum((WISP_PCSTR)GetItemText(hItem,1),&Address)==false)
		return true;
	VIEW_DATA(Address);
	return true;
}

bool CGeneRegList::OnDestroy(IN WISP_MSG*pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}
bool CGeneRegList::OnShowData(IN WISP_MSG*pMsg)
{
	UINT RegIndex=pMsg->Command.CmdID-EVENT_ID_SET_DATAVIEW_EAX+1;
	DWORD Address;
	switch(RegIndex)
	{
	case 1:Address = *CPU_REG_PTR_X86.pEAX;break;
	case 2:Address = *CPU_REG_PTR_X86.pEBX;break;
	case 3:Address = *CPU_REG_PTR_X86.pECX;break;
	case 4:Address = *CPU_REG_PTR_X86.pEDX;break;
	case 7:Address = *CPU_REG_PTR_X86.pESI;break;
	case 8:Address = *CPU_REG_PTR_X86.pEDI;break;
	case 6:Address = *CPU_REG_PTR_X86.pEBP;break;
	case 5:Address = *CPU_REG_PTR_X86.pESP;break;
	case 9:Address = *CPU_REG_PTR_X86.pEIP;break;
	}
	VIEW_DATA(Address);
	return true;
}
bool CGeneRegList::OnShowCode(IN WISP_MSG*pMsg)
{
	UINT RegIndex=pMsg->Command.CmdID-EVENT_ID_SET_CODEVIEW_EAX+1;
	
	DWORD Address;
	switch(RegIndex)
	{
	case 1:Address = *CPU_REG_PTR_X86.pEAX;break;
	case 2:Address = *CPU_REG_PTR_X86.pEBX;break;
	case 3:Address = *CPU_REG_PTR_X86.pECX;break;
	case 4:Address = *CPU_REG_PTR_X86.pEDX;break;
	case 7:Address = *CPU_REG_PTR_X86.pESI;break;
	case 8:Address = *CPU_REG_PTR_X86.pEDI;break;
	case 6:Address = *CPU_REG_PTR_X86.pEBP;break;
	case 5:Address = *CPU_REG_PTR_X86.pESP;break;
	case 9:Address = *CPU_REG_PTR_X86.pEIP;break;
	}

	VIEW_CODE(Address,true);
	return true;
}


bool CGeneRegList::OnKeyEvent(IN WISP_MSG*pMsg)
{
	WCHAR szBuffer[128];
	HANDLE hItem;
	ULPOS Address;
	bool bAddressVailed=false;
	REGHOTKEYMAP::IT FindIT;
	int SizeXorY;
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return true;
	if(pMsg->KeyEvent.bKeyDown==false)
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
			hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);

			if(hItem)
			{
				Address = (ULPOS)GetItemData(hItem,1);
				if(gpSyser->m_pDebugger->ReadMemory(Address,szBuffer,1)==1)
					bAddressVailed=true;
				WISP_PCSTR pszText = (WISP_PCSTR)GetItemText(hItem,1);
				TStrCpy(szBuffer,WSTR("Show Code "));
				TStrCat(szBuffer,pszText);
				m_PopupMenu.SetItemText(m_hMenuShowCode,szBuffer);
				TStrCpy(szBuffer,WSTR("Show Data "));
				TStrCat(szBuffer,pszText);
				m_PopupMenu.SetItemText(m_hMenuShowData,szBuffer);
			}			
			m_PopupMenu.EnableItem(m_hMenuShowCode,hItem!=NULL && bAddressVailed);
			m_PopupMenu.EnableItem(m_hMenuShowData,hItem!=NULL && bAddressVailed);
			m_PopupMenu.Popup();
			break;
		case WISP_VK_F2:
			hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
			if(hItem)
			{
				EnableVisible(hItem);
				BeginEditItem(hItem,1);
			}
			return false;
			
		case WISP_VK_A:
			{
				
				gpSyser->m_MainFrame.m_SystemExplorer.m_MainSplitWnd.GetWndSpace(0,SizeXorY);
				if(SizeXorY>10)
					gpSyser->m_MainFrame.m_SystemExplorer.m_MainSplitWnd.ResizeWndSpace(0,SizeXorY-10);
				else
					gpSyser->m_MainFrame.m_SystemExplorer.m_MainSplitWnd.ResizeWndSpace(0,0);
				gpSyser->m_MainFrame.m_SystemExplorer.m_MainSplitWnd.AdjustWndPos();
				return false;
			}
			break;
		case WISP_VK_D:
			{
				
				gpSyser->m_MainFrame.m_SystemExplorer.m_MainSplitWnd.GetWndSpace(0,SizeXorY);				
				gpSyser->m_MainFrame.m_SystemExplorer.m_MainSplitWnd.ResizeWndSpace(0,SizeXorY+10);
				gpSyser->m_MainFrame.m_SystemExplorer.m_MainSplitWnd.AdjustWndPos();
				return false;
			}
			break;
		case WISP_VK_W:
			{

				gpSyser->m_MainFrame.m_SystemExplorer.m_MonitorSplitWnd.GetWndSpace(0,SizeXorY);
				if(SizeXorY>10)
					gpSyser->m_MainFrame.m_SystemExplorer.m_MonitorSplitWnd.ResizeWndSpace(0,SizeXorY-10);
				else
					gpSyser->m_MainFrame.m_SystemExplorer.m_MonitorSplitWnd.ResizeWndSpace(0,0);
				gpSyser->m_MainFrame.m_SystemExplorer.m_MonitorSplitWnd.AdjustWndPos();
				return false;
			}

		case WISP_VK_S:
			{

				gpSyser->m_MainFrame.m_SystemExplorer.m_MonitorSplitWnd.GetWndSpace(0,SizeXorY);				
				gpSyser->m_MainFrame.m_SystemExplorer.m_MonitorSplitWnd.ResizeWndSpace(0,SizeXorY+10);
				gpSyser->m_MainFrame.m_SystemExplorer.m_MonitorSplitWnd.AdjustWndPos();
				return false;
			}
			break;
			

		}		
	}
	return true;
}

void CGeneRegList::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WSTR("Register View"),CWispRect(0,0,320,210),NULL,0,WISP_WS_NORMAL_NO_MAX|WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE|WISP_WLS_EMPTY_SEL_RECT);
		Center();
		UpdateContext();
	}	
}

void CGeneRegList::ResetContext()
{
	if(IsWindow()==false)
		return;
	for(int n=0;n<REG_GENE_REGCOUNT;n++)
	{
		if(n>=REG_GENE_EAX && n<=REG_GENE_EFL)
			SetItemText(m_hGeneRegItem[n],1,WSTR("????????"));
		else if(n>=REG_GENE_CS && n<=REG_GENE_SS)
			SetItemText(m_hGeneRegItem[n],1,WSTR("????"));
		else if(n>=REG_GENE_AF && n<=REG_GENE_ZF)
			SetItemText(m_hGeneRegItem[n],1,WSTR("?"));
		else if(n>=REG_GENE_CS_BASE && n<=REG_GENE_SS_BASE)
			SetItemText(m_hGeneRegItem[n],1,WSTR("????????"));
		SetItemText(m_hGeneRegItem[n],2,NULL);
		SetItemTextColor(m_hGeneRegItem[n],1,m_NormalColor);
	}
	SelectItem(m_hGeneRegItem[REG_GENE_EAX]);
	STZeroMemory(m_PrevCPUReg);
}

bool CGeneRegList::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	int n;
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return false;
	DWORD dwCurrentCpuID=0;
#ifdef CODE_OS_NT_DRV	
	dwCurrentCpuID = GetCurrentCPULocalAPICID();
	if(dwCurrentCpuID!= GetCPUIndex())
		return false;
#endif
	n = (int)GetItemData(hItem,0);
	if(n>=REG_GENE_AF && n<=REG_GENE_ZF)
	{
		bool bChg;
		int Value;
		EFL_REG*pEFL = (EFL_REG*)&m_PrevCPUReg.EFL;
		switch(n)
		{
		case REG_GENE_AF:
			Value = CPU_REG_PTR_X86.pEFL->AF = !CPU_REG_PTR_X86.pEFL->AF;
			bChg = CPU_REG_PTR_X86.pEFL->AF != pEFL->AF;
			break;
		case REG_GENE_CF:
			Value = CPU_REG_PTR_X86.pEFL->CF = !CPU_REG_PTR_X86.pEFL->CF;
			bChg = CPU_REG_PTR_X86.pEFL->CF != pEFL->CF;
			break;
		case REG_GENE_DF:
			Value = CPU_REG_PTR_X86.pEFL->DF = !CPU_REG_PTR_X86.pEFL->DF;
			bChg = CPU_REG_PTR_X86.pEFL->DF != pEFL->DF;
			break;
		case REG_GENE_IF:
			Value = CPU_REG_PTR_X86.pEFL->IF = !CPU_REG_PTR_X86.pEFL->IF;
			bChg = CPU_REG_PTR_X86.pEFL->IF != pEFL->IF;
			break;
		case REG_GENE_OF:
			Value = CPU_REG_PTR_X86.pEFL->OF = !CPU_REG_PTR_X86.pEFL->OF;
			bChg = CPU_REG_PTR_X86.pEFL->OF != pEFL->OF;
			break;
		case REG_GENE_PF:
			Value = CPU_REG_PTR_X86.pEFL->PF = !CPU_REG_PTR_X86.pEFL->PF;
			bChg = CPU_REG_PTR_X86.pEFL->PF != pEFL->PF;
			break;
		case REG_GENE_SF:
			Value = CPU_REG_PTR_X86.pEFL->SF = !CPU_REG_PTR_X86.pEFL->SF;
			bChg = CPU_REG_PTR_X86.pEFL->SF != pEFL->SF;
			break;
		case REG_GENE_ZF:
			Value = CPU_REG_PTR_X86.pEFL->ZF = !CPU_REG_PTR_X86.pEFL->ZF;
			bChg = CPU_REG_PTR_X86.pEFL->ZF != pEFL->ZF;
			break;
		default:
			return false;
		}
		SetItemNum(m_hGeneRegItem[REG_GENE_EFL],1,*(DWORD*)CPU_REG_PTR_X86.pEFL,WSTR("%08X"));
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EFL],1,*(DWORD*)CPU_REG_PTR_X86.pEFL==m_PrevCPUReg.EFL?m_NormalColor:m_ChgColor);
		SetItemText(m_hGeneRegItem[n],1,Value?WSTR("1"):WSTR("0"));
		SetItemTextColor(m_hGeneRegItem[n],1,bChg?m_ChgColor:m_NormalColor);
		UpdateClient();
		UPDATE_CONTEXT();
		return false;
	}
	return true;
}

bool CGeneRegList::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	int n;
	DWORD Value,*pddValue;
	WORD *pdwValue;
	if(CALCEXP(String,&Value)==false)
		return false;
	n = (int)GetItemData(hItem,0);
	if(n<0 || n>=REG_GENE_REGCOUNT)
		return false;
	if(n>=REG_GENE_EAX && n<=REG_GENE_EFL)
	{
		switch(n)
		{
		case REG_GENE_EAX:pddValue = CPU_REG_PTR_X86.pEAX;break;
		case REG_GENE_EBX:pddValue = CPU_REG_PTR_X86.pEBX;break;
		case REG_GENE_ECX:pddValue = CPU_REG_PTR_X86.pECX;break;
		case REG_GENE_EDX:pddValue = CPU_REG_PTR_X86.pEDX;break;
		case REG_GENE_ESI:pddValue = CPU_REG_PTR_X86.pESI;break;
		case REG_GENE_EDI:pddValue = CPU_REG_PTR_X86.pEDI;break;
		case REG_GENE_EBP:pddValue = CPU_REG_PTR_X86.pEBP;break;
		case REG_GENE_ESP:pddValue = CPU_REG_PTR_X86.pESP;break;
		case REG_GENE_EIP:pddValue = CPU_REG_PTR_X86.pEIP;break;
		case REG_GENE_EFL:pddValue = (DWORD*)CPU_REG_PTR_X86.pEFL;break;
		default:return false;
		}
		if(*pddValue==Value)
			return false;
		*pddValue = Value;
		SetItemTextColor(m_hGeneRegItem[n],1,m_ChgColor);
		String.Format(WSTR("%08X"),*pddValue);
	}
	else if(n>=REG_GENE_CS && n<=REG_GENE_SS)
	{
		switch(n)
		{
		case REG_GENE_CS:pdwValue = CPU_REG_PTR_X86.pCS;break;
		case REG_GENE_DS:pdwValue = CPU_REG_PTR_X86.pDS;break;
		case REG_GENE_ES:pdwValue = CPU_REG_PTR_X86.pES;break;
		case REG_GENE_FS:pdwValue = CPU_REG_PTR_X86.pFS;break;
		case REG_GENE_GS:pdwValue = CPU_REG_PTR_X86.pGS;break;
		case REG_GENE_SS:pdwValue = CPU_REG_PTR_X86.pSS;break;
		default:return false;
		}
		if(*pdwValue==(WORD)Value)
			return false;
		*pdwValue=(WORD)Value;
		SetItemTextColor(m_hGeneRegItem[n],1,m_ChgColor);
		String.Format(WSTR("%04X"),*pdwValue);
	}
	else
		return false;
	gpSyser->m_pDebugger->SaveRegister();
	if(n==REG_GENE_EFL)
	{
		UpdateEFlagContext();
	}
	else if(n==REG_GENE_EIP)
	{
		gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.UpdateAllView();
	}
	m_hLastItem = m_hGeneRegItem[n];
	UPDATE_CONTEXT();
	return true;
}

void CGeneRegList::UpdateCommentContext(X86_CPU_REG_PTR& pPtr)
{
	CHAR szBuffer[256];
	WCHAR szBufferW[256];
	int StrType;
	szBufferW[0]=0;
	if(GETSYM(*pPtr.pEAX,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pEAX,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pEAX,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 		
	SetItemText(m_hGeneRegItem[REG_GENE_EAX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(*pPtr.pEBX,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pEBX,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pEBX,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_EBX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(*pPtr.pECX,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pECX,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pECX,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_ECX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(*pPtr.pEDX,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pEDX,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pEDX,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_EDX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(*pPtr.pESI,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pESI,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pESI,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_ESI],2,szBufferW);

	szBufferW[0]=0;
	if(GETSYM(*pPtr.pEDI,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pEDI,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pEDI,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 

	SetItemText(m_hGeneRegItem[REG_GENE_EDI],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(*pPtr.pEBP,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pEBP,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pEBP,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_EBP],2,szBufferW);
	szBufferW[0]=0;
	if(*CPU_REG_PTR_X86.pESP==0x7ffb8)
		szBufferW[0]=0;
	if(GETSYM(*pPtr.pESP,szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(*pPtr.pESP,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(*pPtr.pESP,szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_ESP],2,szBufferW);
	szBufferW[0]=0;
	//if(GETSYM(*CPU_REG_PTR_X86.pEIP,szBuffer,sizeof(szBuffer)))
	//{
	//	TStrCpy(szBufferW,szBuffer);
	//}
	//else if(!GET_STRING_SYM(*CPU_REG_PTR_X86.pEIP,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0])))
	//{
	if(GET_ALMOST_SYM(*pPtr.pEIP,szBuffer))
		TStrCpy(szBufferW,szBuffer);
	//} 
	SetItemText(m_hGeneRegItem[REG_GENE_EIP],2,szBufferW);

}

void CGeneRegList::UpdateContext()
{
	DWORD Address;
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false || IsWindow()==false)
		return;
	DWORD dwCurrentCpuID=0;
#ifdef CODE_OS_NT_DRV	
	dwCurrentCpuID = GetCurrentCPULocalAPICID();
#endif

	
	if(dwCurrentCpuID!=m_nCPUIndex)	
		gpSyser->m_pDebugger->GetCPUX86RegPtr(&m_X86RegPtr,m_nCPUIndex);
	else
		m_X86RegPtr=X86_REG_PTR;
	
	//////////////////////////////////////////////////////////////////
	//EAX
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_EAX],1,*CPU_REG_PTR_X86.pEAX,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EAX],1,*CPU_REG_PTR_X86.pEAX);
	if(*CPU_REG_PTR_X86.pEAX == m_PrevCPUReg.EAX)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EAX],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EAX],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//EBX
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_EBX],1,*CPU_REG_PTR_X86.pEBX,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EBX],1,*CPU_REG_PTR_X86.pEBX);
	if(*CPU_REG_PTR_X86.pEBX == m_PrevCPUReg.EBX)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBX],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBX],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//ECX
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_ECX],1,*CPU_REG_PTR_X86.pECX,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_ECX],1,*CPU_REG_PTR_X86.pECX);
	if(*CPU_REG_PTR_X86.pECX == m_PrevCPUReg.ECX)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ECX],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ECX],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//EDX
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_EDX],1,*CPU_REG_PTR_X86.pEDX,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EDX],1,*CPU_REG_PTR_X86.pEDX);
	if(*CPU_REG_PTR_X86.pEDX == m_PrevCPUReg.EDX)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDX],1,m_NormalColor);
	else
	{
		
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDX],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//ESI
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_ESI],1,*CPU_REG_PTR_X86.pESI,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_ESI],1,*CPU_REG_PTR_X86.pESI);
	if(*CPU_REG_PTR_X86.pESI == m_PrevCPUReg.ESI)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESI],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESI],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//EDI
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_EDI],1,*CPU_REG_PTR_X86.pEDI,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EDI],1,*CPU_REG_PTR_X86.pEDI);
	if(*CPU_REG_PTR_X86.pEDI == m_PrevCPUReg.EDI)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDI],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDI],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//EBP
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_EBP],1,*CPU_REG_PTR_X86.pEBP,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EBP],1,*CPU_REG_PTR_X86.pEBP);
	if(*CPU_REG_PTR_X86.pEBP == m_PrevCPUReg.EBP)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBP],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBP],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//ESP
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_ESP],1,*CPU_REG_PTR_X86.pESP,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_ESP],1,*CPU_REG_PTR_X86.pESP);
	if(*CPU_REG_PTR_X86.pESP == m_PrevCPUReg.ESP)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESP],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESP],1,m_ChgColor);
	}
	//////////////////////////////////////////////////////////////////
	//EIP
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_EIP],1,*CPU_REG_PTR_X86.pEIP,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EIP],1,*CPU_REG_PTR_X86.pEIP);
	if(*CPU_REG_PTR_X86.pEIP == m_PrevCPUReg.EIP)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EIP],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EIP],1,m_ChgColor);
	}
	UpdateCommentContext(m_X86RegPtr);
	//////////////////////////////////////////////////////////////////
	//EFlags
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_EFL],1,*(DWORD*)CPU_REG_PTR_X86.pEFL,WSTR("%08X"));
	if(*(DWORD*)CPU_REG_PTR_X86.pEFL == m_PrevCPUReg.EFL)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EFL],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EFL],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//CS
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_CS],1,*CPU_REG_PTR_X86.pCS,WSTR("%04X"));
	if(*CPU_REG_PTR_X86.pCS == m_PrevCPUReg.CS)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_CS],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_CS],1,m_ChgColor);
		if(gpSyser->m_pDebugger->GetSegRegBase(*CPU_REG_PTR_X86.pCS,&Address))
			SetItemNum(m_hGeneRegItem[REG_GENE_CS_BASE],1,Address,WSTR("%08X"));
		else
			SetItemText(m_hGeneRegItem[REG_GENE_CS_BASE],1,WSTR("????????"));
	}
	//////////////////////////////////////////////////////////////////
	//DS
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_DS],1,*CPU_REG_PTR_X86.pDS,WSTR("%04X"));
	if(*CPU_REG_PTR_X86.pDS == m_PrevCPUReg.DS)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_DS],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_DS],1,m_ChgColor);
		if(gpSyser->m_pDebugger->GetSegRegBase(*CPU_REG_PTR_X86.pDS,&Address))
			SetItemNum(m_hGeneRegItem[REG_GENE_DS_BASE],1,Address,WSTR("%08X"));
		else
			SetItemText(m_hGeneRegItem[REG_GENE_DS_BASE],1,WSTR("????????"));
	}
	//////////////////////////////////////////////////////////////////
	//ES
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_ES],1,*CPU_REG_PTR_X86.pES,WSTR("%04X"));
	if(*CPU_REG_PTR_X86.pES == m_PrevCPUReg.ES)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ES],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ES],1,m_ChgColor);
		if(gpSyser->m_pDebugger->GetSegRegBase(*CPU_REG_PTR_X86.pES,&Address))
		{
			SetItemNum(m_hGeneRegItem[REG_GENE_ES_BASE],1,Address,WSTR("%08X"));
			SetItemData(m_hGeneRegItem[REG_GENE_ES_BASE],1,Address);
		}
		else
			SetItemText(m_hGeneRegItem[REG_GENE_ES_BASE],1,WSTR("????????"));
	}
	//////////////////////////////////////////////////////////////////
	//FS
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_FS],1,*CPU_REG_PTR_X86.pFS,WSTR("%04X"));
	if(*CPU_REG_PTR_X86.pFS == m_PrevCPUReg.FS)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_FS],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_FS],1,m_ChgColor);
		if(gpSyser->m_pDebugger->GetSegRegBase(*CPU_REG_PTR_X86.pFS,&Address))
		{
			SetItemData(m_hGeneRegItem[REG_GENE_FS_BASE],1,Address);
			SetItemNum(m_hGeneRegItem[REG_GENE_FS_BASE],1,Address,WSTR("%08X"));
		}
		else
			SetItemText(m_hGeneRegItem[REG_GENE_FS_BASE],1,WSTR("????????"));
	}
	//////////////////////////////////////////////////////////////////
	//GS
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_GS],1,*CPU_REG_PTR_X86.pGS,WSTR("%04X"));
	if(*CPU_REG_PTR_X86.pGS == m_PrevCPUReg.GS)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_GS],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_GS],1,m_ChgColor);
		if(gpSyser->m_pDebugger->GetSegRegBase(*CPU_REG_PTR_X86.pGS,&Address))
		{
			SetItemNum(m_hGeneRegItem[REG_GENE_GS_BASE],1,Address,WSTR("%08X"));
			SetItemData(m_hGeneRegItem[REG_GENE_GS_BASE],1,Address);
		}
		else
			SetItemText(m_hGeneRegItem[REG_GENE_GS_BASE],1,WSTR("????????"));
	}
	//////////////////////////////////////////////////////////////////
	//SS
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_SS],1,*CPU_REG_PTR_X86.pSS,WSTR("%04X"));
	if(*CPU_REG_PTR_X86.pSS == m_PrevCPUReg.SS)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_SS],1,m_NormalColor);
	else
	{
		SetItemTextColor(m_hGeneRegItem[REG_GENE_SS],1,m_ChgColor);
		if(gpSyser->m_pDebugger->GetSegRegBase(*CPU_REG_PTR_X86.pSS,&Address))
		{
			SetItemNum(m_hGeneRegItem[REG_GENE_SS_BASE],1,Address,WSTR("%08X"));
			SetItemData(m_hGeneRegItem[REG_GENE_SS_BASE],1,Address);
		}
		else
			SetItemText(m_hGeneRegItem[REG_GENE_SS_BASE],1,WSTR("????????"));
	}
#ifdef CODE_OS_NT_DRV	
	//////////////////////////////////////////////////////////////////
	//GDTR
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_GDTR],1,*CPU_REG_PTR_X86.pGDTRBase,WSTR("%08X"));
	//////////////////////////////////////////////////////////////////
	//GDTR Base
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_GDTRBASE],1,*CPU_REG_PTR_X86.pGDTRBase,WSTR("%08X"));
	//////////////////////////////////////////////////////////////////
	//GDTR Limit
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_GDTRLIMIT],1,*CPU_REG_PTR_X86.pGDTRLimit,WSTR("%04X"));
	//////////////////////////////////////////////////////////////////
	//IDTR
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_IDTR],1,*CPU_REG_PTR_X86.pIDTRBase,WSTR("%08X"));
	//////////////////////////////////////////////////////////////////
	//IDTR Base
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_IDTRBASE],1,*CPU_REG_PTR_X86.pIDTRBase,WSTR("%08X"));
	//////////////////////////////////////////////////////////////////
	//IDTR Limit
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_IDTRLIMIT],1,*CPU_REG_PTR_X86.pIDTRLimit,WSTR("%04X"));	
	//////////////////////////////////////////////////////////////////
	//LDTR
	//////////////////////////////////////////////////////////////////	
	SetItemNum(m_hGeneRegItem[REG_GENE_LDTR],1,*CPU_REG_PTR_X86.pLDTR,WSTR("%04X"));
	//////////////////////////////////////////////////////////////////
	//TR
	//////////////////////////////////////////////////////////////////
	SetItemNum(m_hGeneRegItem[REG_GENE_TR],1,*CPU_REG_PTR_X86.pTR,WSTR("%04X"));
#endif
	UpdateEFlagContext();

	m_PrevCPUReg.EAX = *CPU_REG_PTR_X86.pEAX;
	m_PrevCPUReg.EBX = *CPU_REG_PTR_X86.pEBX;
	m_PrevCPUReg.ECX = *CPU_REG_PTR_X86.pECX;
	m_PrevCPUReg.EDX = *CPU_REG_PTR_X86.pEDX;
	m_PrevCPUReg.EDI = *CPU_REG_PTR_X86.pEDI;
	m_PrevCPUReg.ESI = *CPU_REG_PTR_X86.pESI;
	m_PrevCPUReg.EBP = *CPU_REG_PTR_X86.pEBP;
	m_PrevCPUReg.ESP = *CPU_REG_PTR_X86.pESP;
	m_PrevCPUReg.EIP = *CPU_REG_PTR_X86.pEIP;
	m_PrevCPUReg.EFL = *(DWORD*)CPU_REG_PTR_X86.pEFL;
	m_PrevCPUReg.CS = *CPU_REG_PTR_X86.pCS;
	m_PrevCPUReg.DS = *CPU_REG_PTR_X86.pDS;
	m_PrevCPUReg.ES = *CPU_REG_PTR_X86.pES;
	m_PrevCPUReg.FS = *CPU_REG_PTR_X86.pFS;
	m_PrevCPUReg.GS = *CPU_REG_PTR_X86.pGS;
	m_PrevCPUReg.SS = *CPU_REG_PTR_X86.pSS;
	
	UpdateClient();
}

void CGeneRegList::UpdateEFlagContext()
{
	EFL_REG*pPrevEFlag=(EFL_REG*)&m_PrevCPUReg.EFL;
	//////////////////////////////////////////////////////////////////
	//EFlag->AF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_AF],1,CPU_REG_PTR_X86.pEFL->AF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->AF==CPU_REG_PTR_X86.pEFL->AF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_AF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_AF],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//EFlag->CF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_CF],1,CPU_REG_PTR_X86.pEFL->CF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->CF==CPU_REG_PTR_X86.pEFL->CF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_CF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_CF],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//EFlag->DF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_DF],1,CPU_REG_PTR_X86.pEFL->DF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->DF==CPU_REG_PTR_X86.pEFL->DF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_DF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_DF],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//EFlag->IF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_IF],1,CPU_REG_PTR_X86.pEFL->IF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->IF==CPU_REG_PTR_X86.pEFL->IF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_IF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_IF],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//EFlag->OF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_OF],1,CPU_REG_PTR_X86.pEFL->OF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->OF==CPU_REG_PTR_X86.pEFL->OF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_OF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_OF],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//EFlag->PF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_PF],1,CPU_REG_PTR_X86.pEFL->PF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->PF==CPU_REG_PTR_X86.pEFL->PF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_PF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_PF],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//EFlag->SF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_SF],1,CPU_REG_PTR_X86.pEFL->SF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->SF==CPU_REG_PTR_X86.pEFL->SF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_SF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_SF],1,m_ChgColor);
	//////////////////////////////////////////////////////////////////
	//EFlag->ZF
	//////////////////////////////////////////////////////////////////
	SetItemText(m_hGeneRegItem[REG_GENE_ZF],1,CPU_REG_PTR_X86.pEFL->ZF?WSTR("1"):WSTR("0"));
	if(pPrevEFlag->ZF==CPU_REG_PTR_X86.pEFL->ZF)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ZF],1,m_NormalColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ZF],1,m_ChgColor);
}

void CGeneRegList::ItemClickNotify(HANDLE hItem,int Col)
{
	DWORD Address;
	if(Col!=0)
		return;
	if(USHexStrToNum((WISP_PCSTR)GetItemText(hItem,1),&Address)==false)
		return;
	VIEW_DATA(Address);
}
void CGeneRegList::RunTraceUpdateContext(DWORD ModifyBitMask,X86_REG_CONTEXT* pReg,DWORD EIP)
{
	SetItemNum(m_hGeneRegItem[REG_GENE_EIP],1,EIP,WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EIP],1,EIP);
	if(ModifyBitMask & EIP_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EIP],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EIP],1,m_NormalColor);

	SetItemNum(m_hGeneRegItem[REG_GENE_EAX],1,pReg->GeneReg[EAX_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EAX],1,pReg->GeneReg[EAX_IDX]);
	if(ModifyBitMask & EAX_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EAX],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EAX],1,m_NormalColor);
	
	SetItemNum(m_hGeneRegItem[REG_GENE_EBX],1,pReg->GeneReg[EBX_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EBX],1,pReg->GeneReg[EBX_IDX]);
	if(ModifyBitMask & EBX_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBX],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBX],1,m_NormalColor);

	SetItemNum(m_hGeneRegItem[REG_GENE_ECX],1,pReg->GeneReg[ECX_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_ECX],1,pReg->GeneReg[ECX_IDX]);
	if(ModifyBitMask & ECX_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ECX],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDX],1,m_NormalColor);
	SetItemNum(m_hGeneRegItem[REG_GENE_EDX],1,pReg->GeneReg[EDX_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EDX],1,pReg->GeneReg[EDX_IDX]);
	if(ModifyBitMask & EDX_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDX],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDX],1,m_NormalColor);

	SetItemNum(m_hGeneRegItem[REG_GENE_ESP],1,pReg->GeneReg[ESP_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_ESP],1,pReg->GeneReg[ESP_IDX]);
	if(ModifyBitMask & ESP_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESP],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESP],1,m_NormalColor);

	SetItemNum(m_hGeneRegItem[REG_GENE_EBP],1,pReg->GeneReg[EBP_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EBP],1,pReg->GeneReg[EBP_IDX]);
	if(ModifyBitMask & EBP_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBP],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EBP],1,m_NormalColor);
	SetItemNum(m_hGeneRegItem[REG_GENE_ESI],1,pReg->GeneReg[ESI_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_ESI],1,pReg->GeneReg[ESI_IDX]);
	if(ModifyBitMask & ESI_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESI],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_ESI],1,m_NormalColor);
	
	SetItemNum(m_hGeneRegItem[REG_GENE_EDI],1,pReg->GeneReg[EDI_IDX],WSTR("%08X"));
	SetItemData(m_hGeneRegItem[REG_GENE_EDI],1,pReg->GeneReg[EDI_IDX]);
	if(ModifyBitMask & EDI_MODIFY_BIT_MASK)
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDI],1,m_ChgColor);
	else
		SetItemTextColor(m_hGeneRegItem[REG_GENE_EDI],1,m_NormalColor);
	
	RunTraceUpdateCommentContext(pReg);
	return;
}
void CGeneRegList::RunTraceUpdateCommentContext(X86_REG_CONTEXT *pReg)
{
	CHAR szBuffer[256];
	WCHAR szBufferW[256];
	int StrType;
	szBufferW[0]=0;
	if(GETSYM(pReg->GeneReg[REG_GENE_EAX],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_EAX],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_EAX],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 		
	SetItemText(m_hGeneRegItem[REG_GENE_EAX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(pReg->GeneReg[REG_GENE_EBX],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_EBX],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_EBX],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_EBX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(pReg->GeneReg[REG_GENE_ECX],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_ECX],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_ECX],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_ECX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(pReg->GeneReg[REG_GENE_EDX],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_EDX],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_EDX],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_EDX],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(pReg->GeneReg[REG_GENE_ESI],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_ESI],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_ESI],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_ESI],2,szBufferW);

	szBufferW[0]=0;
	if(GETSYM(pReg->GeneReg[REG_GENE_EDI],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_EDI],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_EDI],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 

	SetItemText(m_hGeneRegItem[REG_GENE_EDI],2,szBufferW);
	szBufferW[0]=0;
	if(GETSYM(pReg->GeneReg[REG_GENE_EBP],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_EBP],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_EBP],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_EBP],2,szBufferW);
	szBufferW[0]=0;

	if(GETSYM(pReg->GeneReg[REG_GENE_ESP],szBuffer,sizeof(szBuffer)))
	{
		TStrCpy(szBufferW,szBuffer);
	}
	else if(!GET_STRING_SYM(pReg->GeneReg[REG_GENE_ESP],szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0]),StrType))
	{
		if(GET_ALMOST_SYM(pReg->GeneReg[REG_GENE_ESP],szBuffer))
			TStrCpy(szBufferW,szBuffer);
	} 
	SetItemText(m_hGeneRegItem[REG_GENE_ESP],2,szBufferW);
	szBufferW[0]=0;
	//if(GETSYM(*CPU_REG_PTR_X86.pEIP,szBuffer,sizeof(szBuffer)))
	//{
	//	TStrCpy(szBufferW,szBuffer);
	//}
	//else if(!GET_STRING_SYM(*CPU_REG_PTR_X86.pEIP,szBufferW,sizeof(szBufferW)/sizeof(szBufferW[0])))
	//{
	if(GET_ALMOST_SYM(pReg->EIP,szBuffer))
		TStrCpy(szBufferW,szBuffer);
	//} 
	SetItemText(m_hGeneRegItem[REG_GENE_EIP],2,szBufferW);
}