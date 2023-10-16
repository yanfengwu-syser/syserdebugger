#include "StdAfx.h"
#include "DebuggerSelectForm.h"
#include "Syser.h"

enum CCrossReferenceForm::WISP_FORM_ID
{
	CMD_ID_REFERENCE_LIST = WISP_ID_USER_START,
	CMD_ID_BT_OK,

};

WISP_FORM_RES_ITEM CCrossReferenceForm::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,400,240},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("xrefs to ..."),
		"\\SyserIcon\\Syser.ico",
		NULL
	},
	{
		WISP_CTRL_LIST,
		{5,5,380,160},
		CMD_ID_REFERENCE_LIST,
		WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER|WISP_WLS_SELECTED_ALWAYS,
		NULL,
	},
	{
		WISP_CTRL_BUTTON,
		{80,180,70,20},
		CMD_ID_BT_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{250,180,70,20},
		WISP_ID_CANCEL,
		WISP_BS_NORMAL,
		WSTR("Cancel"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CCrossReferenceForm)
	WISP_MSG_MAP_ON_COMMAND	
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CCrossReferenceForm)
WISP_MSG_CMD_MAP(CMD_ID_REFERENCE_LIST,OnListCmd);
WISP_MSG_CMD_MAP_END
WISP_MSG_EVENT_MAP_BEGIN(CCrossReferenceForm)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_OK,OnOkButton)
	//WISP_MSG_EVENT_MAP(CMD_ID_BT_REFRESH,OnRefresh)
WISP_MSG_EVENT_MAP_END


CCrossReferenceForm::CCrossReferenceForm()
{
	m_pFormRes = m_FormRes;
}

CCrossReferenceForm::~CCrossReferenceForm()
{
}

bool CCrossReferenceForm::OnListCmd(WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_LDBCLICK)
	{
		OnOkButton(NULL);
	}
	return true;
}

bool CCrossReferenceForm::OnOkButton(WISP_MSG*pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	CCodeView*pCodeView;
	hItem = m_AddressReferenceList->GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem)
	{
		Address=(ULPOS)m_AddressReferenceList->GetItemData(hItem,0);
		pCodeView=(CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
		if(pCodeView)
			pCodeView->SetStartAddress(Address,true);
	}
	if(pMsg)
		Destroy();
	return true;
}

bool CCrossReferenceForm::OnFormCreate(WISP_MSG*pMsg)
{
	m_AddressReferenceList = (CWispList*)GetFormItem(CMD_ID_REFERENCE_LIST);
	m_AddressReferenceList->InsertColumn(WSTR("Direction"),40);
	m_AddressReferenceList->InsertColumn(WSTR("Type"),35);
	m_AddressReferenceList->InsertColumn(WSTR("Address"),100);
	m_AddressReferenceList->InsertColumn(WSTR("Instruction"),200);
	m_AddressReferenceList->SetDefaultTextColor(ColorOption.clrText);
	m_AddressReferenceList->SetBGColor(ColorOption.clrBackground);
	return true;
}

bool CCrossReferenceForm::InitReferenceList(CROSSREFERENCELIST* pList,DWORD Address)
{
	CROSSREFERENCELIST::IT BeginIt,EndIt;
	DWORD DestAddr;
	HANDLE hItem;
	CCodeView*pCodeView;
	WISP_COLOR_CHAR szColorBuffer[256];
	bool bFirst=true;
	m_AddressReferenceList->ClearChildItem();
	pCodeView=(CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	if(pCodeView==NULL)
		return false;
	BeginIt = pList->Begin();
	EndIt = pList->End();
	for(;BeginIt!=EndIt;BeginIt++)
	{
		DestAddr = *BeginIt;
		if(DestAddr<Address)
			hItem = m_AddressReferenceList->InsertItemW(WSTR("UP"));
		else
			hItem = m_AddressReferenceList->InsertItemW(WSTR("DOWN"));
		m_AddressReferenceList->SetItemData(hItem,0,DestAddr);
		m_AddressReferenceList->SetItemTextColor(hItem,0,WispColor(SC_WHITE));
		m_AddressReferenceList->SetItemTextColor(hItem,1,WispColor(SC_WHITE));
		m_AddressReferenceList->SetItemTextColor(hItem,2,WispColor(SC_WHITE));
		m_AddressReferenceList->SetItemNum(hItem,2,DestAddr);
		pCodeView->ColorDasm(DestAddr,MAX_INSTR_LEN,szColorBuffer);
		m_AddressReferenceList->SetItemColorText(hItem,3,szColorBuffer);
		if(bFirst)
			m_AddressReferenceList->SelectItem(hItem);
		bFirst=false;
	}
	return true;
}

bool CCrossReferenceForm::InitDataReferenceList(CROSSREFERENCELIST* pList,DWORD Address)
{
	CROSSREFERENCELIST::IT BeginIt,EndIt;
	DWORD DestAddr,TmpAddr;
	HANDLE hItem;
	bool bFirst=true,bOK;
	CCodeView*pCodeView;
	WISP_COLOR_CHAR szColorBuffer[256];
	m_AddressReferenceList->ClearChildItem();
	pCodeView=(CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	if(pCodeView==NULL)
		return false;
	BeginIt = pList->Begin();
	EndIt = pList->End();
	for(;BeginIt!=EndIt;BeginIt++)
	{
		DestAddr = *BeginIt;
		
		bOK = pCodeView->m_pCodeDoc->GetInstrDesAddress(--DestAddr,&TmpAddr);
		if(bOK==false||TmpAddr!=Address)
		{
			bOK = pCodeView->m_pCodeDoc->GetInstrDesAddress(--DestAddr,&TmpAddr);
			if(bOK==false||TmpAddr!=Address)
			{
				continue;
			}
		}
		if(DestAddr<Address)
			hItem = m_AddressReferenceList->InsertItemW(WSTR("UP"));
		else
			hItem = m_AddressReferenceList->InsertItemW(WSTR("DOWN"));
		m_AddressReferenceList->SetItemData(hItem,0,DestAddr);
		m_AddressReferenceList->SetItemTextColor(hItem,0,WispColor(SC_WHITE));
		m_AddressReferenceList->SetItemTextColor(hItem,1,WispColor(SC_WHITE));
		m_AddressReferenceList->SetItemTextColor(hItem,2,WispColor(SC_WHITE));
		m_AddressReferenceList->SetItemNum(hItem,2,DestAddr);
		pCodeView->ColorDasm(DestAddr,MAX_INSTR_LEN,szColorBuffer);
		m_AddressReferenceList->SetItemColorText(hItem,3,szColorBuffer);
		if(bFirst)
			m_AddressReferenceList->SelectItem(hItem);
		bFirst=false;
	}
	return true;
}

