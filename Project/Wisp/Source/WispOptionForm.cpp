#include "StdAfx.h"
#include "WispOptionForm.h"

//////////////////////////////////////////////////////////////////////////////
//Form Resource
WISP_FORM_RES_ITEM CWispOptionForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,540,330},
		WISP_ID_NULL,
		WISP_WS_NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,300,100,20},
		CMD_ID_OPTION_APPLY,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Apply"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{10,300,100,20},
		CMD_ID_OPTION_RESTORE,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Restore"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{120,300,100,20},
		CMD_ID_OPTION_DEFAULT,
		WISP_BS_NORMAL,
		WSTR("Default"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};
//Form Resource
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//Option List
WISP_PCSTR CWispOptionForm::m_NoYesList[]=
{
	WISP_STR("No"),
	WISP_STR("Yes"),
	NULL
};

void CWispOptionList::DrawCellText(int Col,CWispListItemCell*pCell,WISP_RECT*pRect)
{
	COLORREF Color;
	WISP_OPTION_ITEM*pItem;
	if(Col!=1)
		goto DrawListCellText;
	pItem = (WISP_OPTION_ITEM*)NUM_TO_PTR(pCell->Data);
	if(pItem->Type == OPTION_RGB_COLORREF)
	{
		Color = *(COLORREF*)pItem->pNewValue;
		m_ClientDC.DrawFullRect(pRect->x, pRect->y + 2,20,pRect->cy - 4,Color);
		m_ClientDC.DrawRect(pRect->x, pRect->y + 2,20,pRect->cy - 4,SYS_COLOR[SC_BLACK]);
	}
DrawListCellText:
	CWispList::DrawCellText(Col,pCell,pRect);
}

WISP_MSG_MAP_BEGIN(CWispOptionForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnResize)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CWispOptionForm)
	WISP_MSG_CMD_MAP(CMD_ID_OPTION_LIST,OnListCommand)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CWispOptionForm)
	WISP_MSG_EVENT_MAP(CMD_ID_OPTION_APPLY,OnEventApply)
	WISP_MSG_EVENT_MAP(CMD_ID_OPTION_RESTORE,OnEventRestore)
	WISP_MSG_EVENT_MAP(CMD_ID_OPTION_DEFAULT,OnEventDefault)
WISP_MSG_EVENT_MAP_END

CWispOptionForm::CWispOptionForm()
{
	m_pFormRes = m_FormRes;
}

CWispOptionForm::~CWispOptionForm()
{

}

bool CWispOptionForm::OnDestroy(IN WISP_MSG*pMsg)
{
	RemoveOptionTree(NULL);
	return true;
}

bool CWispOptionForm::OnResize(IN WISP_MSG*pMsg)
{
	m_OptionList.Resize(m_ClientRect.cx-20,m_ClientRect.cy-50);
	m_pRestoreBT->MoveToWindow(m_OptionList.m_ScrWindowRect.x-m_ScrWindowRect.x,m_OptionList.m_ScrWindowRect.y-m_ScrWindowRect.y+m_OptionList.m_WindowRect.cy+10);
	if(m_pDefaultBT->IsVisible())
		m_pDefaultBT->MoveToWindow(m_pRestoreBT->m_ScrWindowRect.x + m_pRestoreBT->m_WindowRect.cx + 10 -m_ScrWindowRect.x,m_pRestoreBT->m_ScrWindowRect.y-m_ScrWindowRect.y);
	m_pApplyBT->MoveToWindow(m_OptionList.m_ScrWindowRect.x + m_OptionList.m_ScrWindowRect.cx - m_pApplyBT->m_WindowRect.cx - m_ScrWindowRect.x,
							m_pRestoreBT->m_ScrWindowRect.y-m_ScrWindowRect.y);
	return true;
}

bool CWispOptionForm::OnListCommand(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	WISP_RECT rc;
	WISP_OPTION_ITEM*pItem;
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_ITEM_BEGIN_EDIT:
		hItem = pMsg->Command.Param2;
		pItem = (WISP_OPTION_ITEM*)m_OptionList.GetItemData(hItem);
		if(pItem==NULL)
			return false;
		if(m_OptionList.GetItemCellRect(hItem,pMsg->Command.Param1,&rc)==false)
			return false;
		return ProcessOptionBeginModify(rc.x+m_OptionList.m_ScrClientRect.x,rc.y+rc.cy+m_OptionList.m_ScrClientRect.y,hItem,pItem);
	case WISP_CMD_ITEM_END_EDIT:
		hItem = pMsg->Command.Param2;
		pItem = (WISP_OPTION_ITEM*)m_OptionList.GetItemData(hItem);
		if(pItem==NULL)
			return false;
		return ProcessOptionEndModify(hItem,pItem);
	case WISP_CMD_ITEM_KEY_DOWN:
		if(pMsg->Command.Param1 == WISP_VK_F2)
		{
			hItem = m_OptionList.GetNextListItem(NULL,WISP_WLIS_SELECTED);
			if(hItem)
			{
				pItem = (WISP_OPTION_ITEM*)m_OptionList.GetItemData(hItem);
				if(pItem)
					m_OptionList.BeginEditItem(hItem,1);
			}
		}
		break;
	}
	return true;
}

bool CWispOptionForm::OnKeyEvent(IN WISP_MSG*pMsg)
{
	return true;
}

bool CWispOptionForm::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_OptionList.Create(NULL,10,10,520,280,this,CMD_ID_OPTION_LIST,WISP_WS_THIN_BORDER|WISP_WLS_OPTION_TREE|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	m_pApplyBT = (CWispButton*) GetFormItem(CMD_ID_OPTION_APPLY);
	m_pRestoreBT = (CWispButton*) GetFormItem(CMD_ID_OPTION_RESTORE);
	m_pDefaultBT = (CWispButton*) GetFormItem(CMD_ID_OPTION_DEFAULT);
	m_OptionList.InsertColumn(WSTR("Option Item"),m_OptionList.m_ClientRect.cx/2,WISP_WLCS_NORMAL,WispTKDIBListDIB("\\Toolbar.bmp",16,16,15));
	m_OptionList.InsertColumn(WSTR("Value"),m_OptionList.m_ClientRect.cx/2,WISP_WLCS_EDITABLE,WispTKDIBListDIB("\\Toolbar.bmp",16,16,26));
	InsertOptionTree(m_pOptionItem,NULL);
	m_nModifyItem = 0;
	if(m_Style & WISP_OFS_HIDE_DEFAULT_BT)
		m_pDefaultBT->Show(WISP_SH_HIDDEN);
	return true;
}

bool CWispOptionForm::OnEventApply(IN WISP_MSG*pMsg)
{
	if(OptionBeforeApplyNotify()==false)
		return true;
	ApplyOptionTree(NULL);
	m_pApplyBT->EnableWindow(false);
	m_pRestoreBT->EnableWindow(false);
	m_nModifyItem = 0;
	SendCmdMsg(WISP_CMD_OPTION_APPLY);
	OptionApplyNotify();
	UpdateClient();
	return true;
}

bool CWispOptionForm::OnEventRestore(IN WISP_MSG*pMsg)
{
	if(OptionBeforeRestoreNotify()==false)
		return true;
	RestoreOptionTree(NULL);
	m_pApplyBT->EnableWindow(false);
	m_pRestoreBT->EnableWindow(false);
	m_nModifyItem = 0;
	OptionRestoreNotify();
	UpdateClient();
	return true;
}

bool CWispOptionForm::OnEventDefault(IN WISP_MSG*pMsg)
{
	if(OptionBeforeDefaultNotify()==false)
		return true;
	ReloadOptionTree(NULL);
	m_pApplyBT->EnableWindow(false);
	m_pRestoreBT->EnableWindow(false);
	m_pDefaultBT->EnableWindow(false);
	m_nModifyItem = 0;
	OptionDefaultNotify();
	UpdateClient();
	return true;
}

void CWispOptionForm::InsertOptionTree(WISP_OPTION_ITEM*pItem,HANDLE hParent)
{
	HANDLE hItem;
	if(pItem==NULL)
		return;
	while(pItem->szText)
	{
		hItem = m_OptionList.InsertItem(pItem->szText,hParent);
		m_OptionList.SetItemData(hItem,0,(NUM_PTR)pItem);
		m_OptionList.SetItemData(hItem,1,(NUM_PTR)pItem);
		if(pItem->Type==OPTION_TITLE)
		{
			InsertOptionTree((WISP_OPTION_ITEM*)pItem->pValue,hItem);
		}
		else
		{
			pItem->pNewValue = (void*)new BYTE[pItem->Length];
			memcpy(pItem->pNewValue,pItem->pValue,pItem->Length);
		}
		pItem++;
	}
}

void CWispOptionForm::RemoveOptionTree(HANDLE hParent)
{
	WISP_OPTION_ITEM*pItem;
	HANDLE hItem = m_OptionList.GetItem(0,hParent);
	while(hItem)
	{
		pItem = (WISP_OPTION_ITEM*) m_OptionList.GetItemData(hItem);
		if(pItem->Type == OPTION_TITLE)
			RemoveOptionTree(hItem);
		else
			delete pItem->pNewValue;
		hItem = m_OptionList.GetNextItem(hItem);
	}
}

void CWispOptionForm::RestoreOptionTree(HANDLE hParent)
{
	WISP_OPTION_ITEM*pItem;
	HANDLE hItem = m_OptionList.GetItem(0,hParent);
	while(hItem)
	{
		pItem = (WISP_OPTION_ITEM*) m_OptionList.GetItemData(hItem);
		if(pItem->Type == OPTION_TITLE)
			RestoreOptionTree(hItem);
		else
		{
			if(memcmp(pItem->pValue,pItem->pNewValue,pItem->Length))
			{
				memcpy(pItem->pNewValue,pItem->pValue,pItem->Length);
				FillOptionValue(pItem,hItem);
				m_OptionList.SetItemTextColor(hItem,-1,m_OptionList.m_FontColor);
			}
		}
		hItem = m_OptionList.GetNextItem(hItem);
	}
}

void CWispOptionForm::ReloadOptionTree(HANDLE hParent)
{
	WISP_OPTION_ITEM*pItem;
	HANDLE hItem = m_OptionList.GetItem(0,hParent);
	while(hItem)
	{
		pItem = (WISP_OPTION_ITEM*) m_OptionList.GetItemData(hItem);
		if(pItem->Type == OPTION_TITLE)
			ReloadOptionTree(hItem);
		else
		{
			memcpy(pItem->pNewValue,pItem->pValue,pItem->Length);
			FillOptionValue(pItem,hItem);
			m_OptionList.SetItemTextColor(hItem,-1,m_OptionList.m_FontColor);
		}
		hItem = m_OptionList.GetNextItem(hItem);
	}
}

void CWispOptionForm::ApplyOptionTree(HANDLE hParent)
{
	WISP_OPTION_ITEM*pItem;
	HANDLE hItem = m_OptionList.GetItem(0,hParent);
	while(hItem)
	{
		pItem = (WISP_OPTION_ITEM*) m_OptionList.GetItemData(hItem);
		if(pItem->Type == OPTION_TITLE)
			ApplyOptionTree(hItem);
		else
		{
			if(memcmp(pItem->pValue,pItem->pNewValue,pItem->Length))
			{
				memcpy(pItem->pValue,pItem->pNewValue,pItem->Length);
				if(pItem->pRef)
					(*pItem->pRef)++;
				FillOptionValue(pItem,hItem);
				m_OptionList.SetItemTextColor(hItem,-1,m_OptionList.m_FontColor);
			}
		}
		hItem = m_OptionList.GetNextItem(hItem);
	}
}

void CWispOptionForm::OnModify(HANDLE hItem)
{
	m_OptionList.SetItemTextColor(hItem,-1,SYS_COLOR[SC_RED]);
	m_nModifyItem++;
	if(m_pApplyBT->IsDisabled())
		m_pApplyBT->EnableWindow(true);
	if(m_pRestoreBT->IsDisabled())
		m_pRestoreBT->EnableWindow(true);
	if(m_pDefaultBT->IsDisabled())
		m_pDefaultBT->EnableWindow(true);
}

void CWispOptionForm::OnModifyRestore(HANDLE hItem)
{
	m_OptionList.SetItemTextColor(hItem,-1,m_OptionList.m_FontColor);
	m_nModifyItem--;
	CODE_ASSERT(m_nModifyItem>=0)
	if(m_nModifyItem==0)
	{
		if(m_pApplyBT->IsDisabled()==false)
			m_pApplyBT->EnableWindow(false);
		if(m_pRestoreBT->IsDisabled()==false)
			m_pRestoreBT->EnableWindow(false);	
	}
}

bool CWispOptionForm::ProcessOptionBeginModify(int x,int y,HANDLE hItem,WISP_OPTION_ITEM*pItem)
{
	WCHAR szBuffer[MAX_FN_LEN];
	int Result;
	switch(pItem->Type)
	{
	case OPTION_TITLE:
		return false;
	case OPTION_RGB_COLORREF:
		if(GetRGBColor((COLORREF*)pItem->pNewValue,(COLORREF*)pItem->pValue)==false)
			return false;
		if(*(COLORREF*)pItem->pNewValue!=*(COLORREF*)pItem->pValue)
		{
			OnModify(hItem);
		}
		return false;
	case OPTION_SELECT_INT:
		if(GetResultFromList(x,y,pItem->SelectData,&Result,*(int*)pItem->pValue)==false)
			return false;
		if(*(int*)pItem->pValue!=Result)
		{
			if(pItem->pfnValueTest==NULL || pItem->pfnValueTest(&Result))
			{
				*(int*)pItem->pNewValue = Result;
				m_OptionList.SetItemText(hItem,1,pItem->SelectData[Result]);
				OnModify(hItem);
			}
		}
		else
		{
			if(*(int*)pItem->pNewValue!=Result)
			{
				*(int*)pItem->pNewValue = Result;
				m_OptionList.SetItemText(hItem,1,pItem->SelectData[Result]);
				OnModifyRestore(hItem);
			}
		}
		return false;
	case OPTION_DIR_NAME:
		if(GetResultFromList(x,y,pItem->SelectData,&Result)==false)
			return false;
		switch(Result)
		{
		case 0://Browse
			if(m_pWispBase->SelectDirForm(szBuffer,m_OptionList.GetItemText(hItem))==false)
				return false;
			if(TStrCmp(szBuffer,(WCHAR*)pItem->pValue))
			{
				ZeroMemory(pItem->pNewValue,pItem->Length);
				TStrCpyLimit((WCHAR*)pItem->pNewValue,szBuffer,pItem->Length);
				m_OptionList.SetItemText(hItem,1,szBuffer);
				OnModify(hItem);
			}
			else
			{
				if(TStrCmp(szBuffer,(WCHAR*)pItem->pNewValue))
				{
					ZeroMemory(pItem->pNewValue,pItem->Length);
					TStrCpyLimit((WCHAR*)pItem->pNewValue,szBuffer,pItem->Length);
					m_OptionList.SetItemText(hItem,1,szBuffer);
					OnModifyRestore(hItem);
				}
			}
			return false;
		case 2://Current Path & Edit
			{
				char szDir[MAX_FN_LEN];
				GetModulePath(szDir,false);
				AnsiToUnicode(szDir,szBuffer,MAX_FN_LEN);
				m_OptionList.GetItemEditString()=szBuffer;
			}
			return true;
		}
		break;
	}
	return true;
}

bool CWispOptionForm::ProcessOptionEndModify(HANDLE hItem,WISP_OPTION_ITEM*pItem)
{
	int Value;
	PCWSTR pStr;
	switch(pItem->Type)
	{
	case OPTION_INT:
		if(SDecStrToNum((PCWSTR)m_OptionList.GetItemEditString(),&Value)==false)
			return false;
		if(pItem->pfnValueTest && pItem->pfnValueTest(&Value)==false)
			return false;
		if(Value!=*(int*)pItem->pValue)
		{
			*(int*)pItem->pNewValue = Value;
			OnModify(hItem);
		}
		else
		{
			if(*(int*)pItem->pNewValue != Value)
			{
				*(int*)pItem->pNewValue = Value;
				OnModifyRestore(hItem);
			}
		}
		return true;
	case OPTION_STRING:
		pStr = (PCWSTR)m_OptionList.GetItemEditString();
		if(TStrCmp(pStr,(PCWSTR)pItem->pValue))
		{
			ZeroMemory(pItem->pNewValue,pItem->Length);
			TStrCpyLimit((PWSTR)pItem->pNewValue,pStr,pItem->Length);
			OnModify(hItem);
		}
		else
		{
			if(TStrCmp(pStr,(PCWSTR)pItem->pNewValue))
			{
				ZeroMemory(pItem->pNewValue,pItem->Length);
				TStrCpyLimit((PWSTR)pItem->pNewValue,pStr,pItem->Length);
				OnModifyRestore(hItem);
			}
		}
		return true;
	case OPTION_DIR_NAME:
		pStr = (PCWSTR)m_OptionList.GetItemEditString();
		if(TStrCmp(pStr,(PCWSTR)pItem->pValue))
		{
			char szDir[MAX_FN_LEN];
			UnicodeToAnsi(pStr,szDir,MAX_FN_LEN);
			if(gpFileIO->IsDir(szDir)==false)
				return false;
			ZeroMemory(pItem->pNewValue,pItem->Length);
			TStrCpyLimit((PWSTR)pItem->pNewValue,pStr,pItem->Length);
			OnModify(hItem);
		}
		else
		{
			if(TStrCmp(pStr,(PCWSTR)pItem->pNewValue))
			{
				ZeroMemory(pItem->pNewValue,pItem->Length);
				TStrCpyLimit((PWSTR)pItem->pNewValue,pStr,pItem->Length);
				OnModifyRestore(hItem);
			}
		}
		return true;
	}
	return true;
}

void CWispOptionForm::FillOptionValue(WISP_OPTION_ITEM*pItem,HANDLE hItem)
{
	switch(pItem->Type)
	{
	case OPTION_INT:
		m_OptionList.SetItemNum(hItem,1,*(int*)pItem->pValue,WSTR("%d"));
		break;
	case OPTION_SELECT_INT:
		{
			int Start = 0;
			WISP_PCSTR szText = pItem->SelectData[*(int*)pItem->pValue];
			if(szText[0]=='%')
			{
				if(szText[1]=='d')
					Start = 2;
			}
			m_OptionList.SetItemText(hItem,1,&szText[Start]);
		}
		break;
	case OPTION_STRING:
	case OPTION_DIR_NAME:
		m_OptionList.SetItemText(hItem,1, (WCHAR*)pItem->pValue);
		break;
	}
}

void CWispOptionForm::FillOptionTreeValue(HANDLE hParent)
{
	WISP_OPTION_ITEM*pItem;
	HANDLE hItem = m_OptionList.GetItem(0,hParent);
	while(hItem)
	{
		pItem = (WISP_OPTION_ITEM*) m_OptionList.GetItemData(hItem);
		if(pItem->Type == OPTION_TITLE)
		{
			FillOptionTreeValue(hItem);
		}
		else
		{
			FillOptionValue(pItem,hItem);
			memcpy(pItem->pNewValue,pItem->pValue,pItem->Length);
		}
		hItem = m_OptionList.GetNextItem(hItem);
	}
}
