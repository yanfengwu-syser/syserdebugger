#include "StdAfx.h"
#include "Syser.h"
#include "CodeBPEdit.h"
#include "DataBPEdit.h"

enum CBreakPointForm::WISP_FORM_ID
{	
	CMD_ID_BT_EDIT = WISP_ID_USER_START,
	CMD_ID_BT_NEW,
	CMD_ID_BT_REMOVE,
	CMD_ID_BT_REMOVE_ALL,
	CMD_ID_BT_ENABLE_ALL,
	CMD_ID_BT_DISABLE_ALL,
	CMD_ID_BP_TAB,
	CMD_ID_BP_CODE_LIST,
	CMD_ID_BP_DATA_LIST,
};

WISP_FORM_RES_ITEM CBreakPointForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,450,300},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Breakpoint"),
		"\\SyserIcon\\Syser.ico",
	},
	{
		WISP_CTRL_TAB,
		{5,5,350,260},
		CMD_ID_BP_TAB,
		WISP_WS_THIN_BORDER,
		NULL,
	},
	{
		WISP_CTRL_STATIC_DIB,
		{380,30,70,20},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL,
		"\\SyserIcon\\Syser.ico:1"
	},
	{
		WISP_CTRL_BUTTON,
		{362,90,70,20},
		CMD_ID_BT_EDIT,
		WISP_BS_NORMAL,
		WSTR("Edit"),
		NULL,
		WSTR("Edit break point")
	},
	{
		WISP_CTRL_BUTTON,
		{362,120,70,20},
		CMD_ID_BT_NEW,
		WISP_BS_NORMAL,
		WSTR("New"),
		NULL,
		WSTR("Insert New break point")
	},
	{
		WISP_CTRL_BUTTON,
		{362,150,70,20},
		CMD_ID_BT_REMOVE,
		WISP_BS_NORMAL,
		WSTR("Remove"),
		NULL,
		WSTR("Remove break point")
	},
	{
		WISP_CTRL_BUTTON,
		{362,180,70,20},
		CMD_ID_BT_REMOVE_ALL,
		WISP_BS_NORMAL,
		WSTR("Remove All"),
		NULL,
		WSTR("Remove All break point")
	},
	{
		WISP_CTRL_BUTTON,
		{362,210,70,20},
		CMD_ID_BT_ENABLE_ALL,
		WISP_BS_NORMAL,
		WSTR("Enable All"),
		NULL,
		WSTR("Enable all break point")
	},
	{
		WISP_CTRL_BUTTON,
		{362,240,70,20},
		CMD_ID_BT_DISABLE_ALL,
		WISP_BS_NORMAL,
		WSTR("Disable All"),
		NULL,
		WSTR("Disable all break point")
	},
	{WISP_CTRL_NULL}
};


WISP_MSG_MAP_BEGIN(CBreakPointForm)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CBreakPointForm)
	WISP_MSG_CMD_MAP(CMD_ID_BP_TAB,OnBPListChange)
	WISP_MSG_CMD_MAP(CMD_ID_BP_CODE_LIST,OnBPListItemSelect)
	WISP_MSG_CMD_MAP(CMD_ID_BP_DATA_LIST,OnBPListItemSelect)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CBreakPointForm)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_EDIT,OnEdit)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_NEW,OnNew)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_REMOVE,OnRemove)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_REMOVE_ALL,OnRemoveAll)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_ENABLE_ALL,OnEnableAll)
	WISP_MSG_EVENT_MAP(CMD_ID_BT_DISABLE_ALL,OnDisableAll)
WISP_MSG_EVENT_MAP_END

CBreakPointForm::CBreakPointForm()
{
	m_pFormRes = m_FormRes;
}

CBreakPointForm::~CBreakPointForm()
{
}

void CBreakPointForm::Popup()
{
	if(IsWindow())
	{
		UpdateContext();
		Show();
	}
	else
	{
		CreateForm(NULL);
	}
}

void CBreakPointForm::UpdateContext()
{
	if(IsVisible())
	{
		RefreshCodeBreakPoint();
		RefreshDataBreakPoint();
	}
}

void CBreakPointForm::InitBPList(CWispList*pList)
{
	pList->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	pList->InsertColumn(WSTR("Name"),100);
	pList->InsertColumn(WSTR("Owner Process"),120);
	pList->InsertColumn(WSTR("Condition"),120);
}

bool CBreakPointForm::OnFormCreate(WISP_MSG*pMsg)
{
	m_pBPTab = (CWispTabWnd*) GetFormItem(CMD_ID_BP_TAB);
	m_pBTEdit = (CWispButton*) GetFormItem(CMD_ID_BT_EDIT);
	m_pBTRemove = (CWispButton*) GetFormItem(CMD_ID_BT_REMOVE);
	m_pBTRemoveAll = (CWispButton*) GetFormItem(CMD_ID_BT_REMOVE_ALL);
	m_pBTEnableAll = (CWispButton*) GetFormItem(CMD_ID_BT_ENABLE_ALL);
	m_pBTDisableAll = (CWispButton*) GetFormItem(CMD_ID_BT_DISABLE_ALL);

	m_pCodeBPList = new CWispList;
	m_pCodeBPList->Create(NULL,0,0,0,0,m_pBPTab,CMD_ID_BP_CODE_LIST,WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS);
	m_pCodeBPList->SetOwner(this);
	m_pBPTab->InsertWnd(WSTR("Code Breakpoint"),m_pCodeBPList);
	InitBPList(m_pCodeBPList);

	m_pActiveBPList = m_pCodeBPList;

	m_pDataBPList = new CWispList;
	m_pDataBPList->Create(NULL,0,0,0,0,m_pBPTab,CMD_ID_BP_DATA_LIST,WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS);
	m_pDataBPList->SetOwner(this);
	m_pBPTab->InsertWnd(WSTR("Data Breakpoint"),m_pDataBPList);
	InitBPList(m_pDataBPList);

	RefreshCodeBreakPoint();
	RefreshDataBreakPoint();
	return true;
}

int CBreakPointForm::RefreshCodeBreakPoint()
{
	int Count = 0;
	if(m_pCodeBPList)
		m_pCodeBPList->ClearChildItem();
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
	{
		Count=ListCodeBreakPoint();
	}
	UpdateBPListButton();
	UpdateClient();
	return Count;
}

int CBreakPointForm::RefreshDataBreakPoint()
{
	int Count = 0;
	if(m_pDataBPList)
		m_pDataBPList->ClearChildItem();
	if(gpSyser->m_pDebugger)
	{
		Count=ListDataBreakPoint();
	}
	UpdateBPListButton();
	UpdateClient();
	return Count;
}


void CBreakPointForm::UpdateBPListButton()
{
	bool bEnable = m_pActiveBPList->GetItemCount()>0;
	m_pBTRemoveAll->EnableWindow(bEnable);
	m_pBTEnableAll->EnableWindow(bEnable);
	m_pBTDisableAll->EnableWindow(bEnable);
	bEnable = m_pActiveBPList->GetNextItem(NULL,WISP_WLIS_SELECTED)!=NULL;
	m_pBTRemove->EnableWindow(bEnable);
	m_pBTEdit->EnableWindow(bEnable);
	Update();
}

bool CBreakPointForm::OnEdit(WISP_MSG*pMsg)
{
	HANDLE hItem = m_pActiveBPList->GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	if(m_pActiveBPList == m_pCodeBPList)
	{
		CCodeBPEdit	CodeBPEditDlg;
		if(m_pActiveBPList->GetItemData(hItem,1))
			CodeBPEditDlg.m_pModuleBP = (MODULE_BP*)m_pActiveBPList->GetItemData(hItem);
		else
			CodeBPEditDlg.m_pBP = (BREAK_POINT*)m_pActiveBPList->GetItemData(hItem);
		CodeBPEditDlg.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
		if(CodeBPEditDlg.GetFormResult() ==WISP_ID_OK)
			RefreshCodeBreakPoint();
	}
	else
	{
		CDataBPEdit	DataBPEditDlg;
		DataBPEditDlg.m_pBP = (BREAK_POINT*)m_pActiveBPList->GetItemData(hItem);
		DataBPEditDlg.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
		if(DataBPEditDlg.GetFormResult() ==WISP_ID_OK)
			RefreshDataBreakPoint();
	}
	return true;
}

bool CBreakPointForm::OnNew(WISP_MSG*pMsg)
{
	if(m_pActiveBPList == m_pCodeBPList)
	{
		CCodeBPEdit	CodeBPEditDlg;
		CodeBPEditDlg.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
		if(CodeBPEditDlg.GetFormResult() ==WISP_ID_OK)
			RefreshCodeBreakPoint();
	}
	else
	{
		CDataBPEdit	DataBPEditDlg;
		DataBPEditDlg.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
		if(DataBPEditDlg.GetFormResult() ==WISP_ID_OK)
			RefreshDataBreakPoint();
	}
	return true;
}

bool CBreakPointForm::OnRemove(WISP_MSG*pMsg)
{
	HANDLE hItem = m_pActiveBPList->GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	if(m_pActiveBPList==m_pCodeBPList)
	{
		if(m_pActiveBPList->GetItemData(hItem,1))
		{
			CModuleBPMap::IT Iter = *(MODULE_BP*)m_pActiveBPList->GetItemData(hItem);
			gpSyser->m_SyserUI.RemoveCodeBP(Iter.Key());
		}
		else
		{
			gpSyser->m_pDebugger->RemoveCodeBP((BREAK_POINT*)m_pActiveBPList->GetItemData(hItem));
		}
		RefreshCodeBreakPoint();
	}
	else
	{
		gpSyser->m_pDebugger->RemoveDataBP((BREAK_POINT*)m_pActiveBPList->GetItemData(hItem));
		RefreshDataBreakPoint();
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	return true;
}

bool CBreakPointForm::OnRemoveAll(WISP_MSG*pMsg)
{
	if(m_pActiveBPList==m_pCodeBPList)
	{
		gpSyser->m_pDebugger->RemoveAllCodeBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		gpSyser->m_SyserUI.m_ModuleBPMap.Clear();
		RefreshCodeBreakPoint();
	}
	else
	{
		gpSyser->m_pDebugger->RemoveAllDataBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		RefreshDataBreakPoint();
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	return true;
}

bool CBreakPointForm::OnEnableAll(WISP_MSG*pMsg)
{
	if(m_pActiveBPList==m_pCodeBPList)
	{
		gpSyser->m_pDebugger->EnableAllCodeBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		gpSyser->m_SyserUI.EnableAllModuleBP();
		RefreshCodeBreakPoint();
	}
	else
	{
		gpSyser->m_pDebugger->EnableAllDataBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		RefreshDataBreakPoint();
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	return true;
}

bool CBreakPointForm::OnDisableAll(WISP_MSG*pMsg)
{
	if(m_pActiveBPList==m_pCodeBPList)
	{
		gpSyser->m_pDebugger->DisableAllCodeBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		gpSyser->m_SyserUI.EnableAllModuleBP(false);
		RefreshCodeBreakPoint();
	}
	else
	{
		gpSyser->m_pDebugger->DisableAllDataBP(BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		RefreshDataBreakPoint();
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	return true;
}

bool CBreakPointForm::OnBPListChange(WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_TAB_ACTIVE_CHG)
	{
		m_pActiveBPList = (CWispList*) pMsg->Command.Param2;
		UpdateBPListButton();
	}
	return true;
}

bool CBreakPointForm::OnBPListItemSelect(WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_SELECTED)
	{		
		if(m_pBTRemove->IsDisabled())
		{
			m_pBTEdit->EnableWindow(true);
			m_pBTRemove->EnableWindow(true);
		}
	}
	return true;
}

void CBreakPointForm::InitBPItem(CWispList*pList,HANDLE hItem,BREAK_POINT*pBP)
{
	WISP_CHAR szBuffer[256];
	pList->SetItemData(hItem,0,(NUM_PTR)pBP);
	pList->SetItemData(hItem,1,0);//BREAK_POINT
	AnsiToUnicode(pBP->OwnerName,szBuffer,256);
	pList->SetItemText(hItem,1,szBuffer);
	AnsiToUnicode(pBP->Condition,szBuffer,256);
	pList->SetItemText(hItem,2,szBuffer);
	if(pBP->State == BP_STATE_DISABLE)
	{
		pList->SetItemTextColor(hItem,0,SYS_COLOR[SC_GRAY]);
		pList->SetItemTextColor(hItem,1,SYS_COLOR[SC_GRAY]);
		pList->SetItemTextColor(hItem,2,SYS_COLOR[SC_GRAY]);
	}
}

void CBreakPointForm::InitModuleBPItem(CWispList*pList,HANDLE hItem,MODULE_BP*pBP)
{
	WISP_CHAR szBuffer[256];
	pList->SetItemData(hItem,0,(NUM_PTR)pBP);
	pList->SetItemData(hItem,1,1);//MODULE_BP
	pList->SetItemText(hItem,1,WSTR("<All Process>"));
	AnsiToUnicode(pBP->Condition,szBuffer,256);
	pList->SetItemText(hItem,2,szBuffer);
	if(pBP->State == BP_STATE_DISABLE)
	{
		pList->SetItemTextColor(hItem,0,SYS_COLOR[SC_GRAY]);
		pList->SetItemTextColor(hItem,1,SYS_COLOR[SC_GRAY]);
		pList->SetItemTextColor(hItem,2,SYS_COLOR[SC_GRAY]);
	}
}

int CBreakPointForm::ListCodeBreakPoint()
{
	WISP_CHAR szBuffer[256];
	HANDLE hItem;
	int Count = 0;
	for(CCodeBPMap::IT Iter=gpSyser->m_pDebugger->m_pCodeBPMap->Begin();Iter!=gpSyser->m_pDebugger->m_pCodeBPMap->End();Iter++)
	{
		if((Iter->Type&(BP_TYPE_PATCH|BP_TYPE_DEBUG)) || Iter->pModuleBP)
			continue;
		if(Iter->Name.Length())
		{
			AnsiToUnicode(Iter->Name,szBuffer,256);
		}
		else
		{
			uNumToStr(Iter->Address,szBuffer);
		}
		hItem = m_pCodeBPList->InsertItem(szBuffer);
		InitBPItem(m_pCodeBPList,hItem,&(*Iter));
		Count++;
	}
	for(CModuleBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleBPMap.Begin();Iter.IsExist();Iter++)
	{
		AnsiToUnicode(Iter->Name,szBuffer,256);
		hItem = m_pCodeBPList->InsertItem(szBuffer);
		InitModuleBPItem(m_pCodeBPList,hItem,&(*Iter));		
	}
	return Count;
}

int CBreakPointForm::ListDataBreakPoint()
{
	WISP_CHAR szBuffer[256];
	HANDLE hItem;
	int Count = 0;
	for(CDataBPList::IT Iter=gpSyser->m_pDebugger->m_pDataBPList->Begin();Iter!=gpSyser->m_pDebugger->m_pDataBPList->End();Iter++)
	{
		if((Iter->Type&(BP_TYPE_PATCH|BP_TYPE_DEBUG)))
			continue;
		if(Iter->Name.Length())
		{
			AnsiToUnicode(Iter->Name,szBuffer,256);
		}
		else
		{
			uNumToStr(Iter->Address,szBuffer);
		}
		hItem = m_pDataBPList->InsertItem(szBuffer);
		InitBPItem(m_pDataBPList,hItem,&(*Iter));
		Count++;
	}
	return Count;
}

