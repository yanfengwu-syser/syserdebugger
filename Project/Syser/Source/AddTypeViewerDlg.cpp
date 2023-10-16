#include "stdafx.h"
#include "AddTypeViewerDlg.h"
#include "Syser.h"
#include "TypeViewerWnd.h"
enum CAddTypeViewerDlg::WISP_FORM_ID
{
	CMD_ID_BUTTON_OK=WISP_ID_USER_START,
	CMD_ID_BUTTON_CANCEL,
	CMD_ID_LIST_TYPE,
	CMD_ID_RADIOBOX_FLOATTYPE,
	CMD_ID_RADIOBOX_LOCKTYPE,
	CMD_ID_RADIOBOX_DWORD,
	CMD_ID_RADIOBOX_QWORD,
	CMD_ID_STATICSTR_DESCRIPTION,
	CMD_ID_RADIOBOX_HEX,
	CMD_ID_RADIOBOX_DECIMAL,
	CMD_ID_STATICSTR_VALUE,
	CMD_ID_STATICSTR_BEGINADDRESS,
	CMD_ID_EDIT_END_POSITION,
	CMD_ID_EDIT_VALUE,
	CMD_ID_CHECKBOX_COUNT,
};
WISP_FORM_RES_ITEM CAddTypeViewerDlg::m_FormRes[] = 
{
	{
		WISP_CTRL_FORM,
		{0,0,386,268},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("Attach Type"),
		"\\SyserIcon\\Plugin.ico",
		NULL,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{166,10,204,56},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Description")
	},
		{
			WISP_CTRL_STATIC_STRING,
			{174,30,204,56},
			CMD_ID_STATICSTR_DESCRIPTION,
			WISP_WS_NULL,
			WSTR(""),
			NULL,
		},
	{
		WISP_CTRL_STATIC_GROUP,
		{166,75,204,106},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Options")
	},
	{
		WISP_CTRL_LIST,
		{5,5,155,230},
		CMD_ID_LIST_TYPE,
		WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER,
		NULL,
	},
	
	{
		WISP_CTRL_RADIO_BOX,
		{176,90,100,16},
		CMD_ID_RADIOBOX_FLOATTYPE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Floating Type"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{176,110,90,16},
		CMD_ID_RADIOBOX_LOCKTYPE,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Lock Type"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_STATIC_STRING,
		{194,135,45,16},
		CMD_ID_STATICSTR_BEGINADDRESS,
		WISP_WS_NULL,
		WSTR("Address:"),
		NULL,
	},
	{
		WISP_CTRL_EDIT,
		{245,135,93,16},
		CMD_ID_EDIT_END_POSITION,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_RADIO_BOX,
		{245,155,45,16},
		CMD_ID_RADIOBOX_DECIMAL,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Dec"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_RADIO_BOX,
		{301,155,45,16},
		CMD_ID_RADIOBOX_HEX,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		WSTR("Hex"),
		NULL,
		NULL
	},
	
	{
		WISP_CTRL_BUTTON,
		{185,197,68,25},
		CMD_ID_BUTTON_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
	},
	{
		WISP_CTRL_BUTTON,
		{280,197,68,25},
		CMD_ID_BUTTON_CANCEL,
		WISP_BS_NORMAL,
		WSTR("Cancel"),
	},
	{WISP_CTRL_NULL}
};
WISP_MSG_MAP_BEGIN(CAddTypeViewerDlg)
WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CAddTypeViewerDlg)
WISP_MSG_CMD_MAP(CMD_ID_LIST_TYPE,OnTypeListCmd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CAddTypeViewerDlg)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_OK,OnOKButtonEvent)
WISP_MSG_EVENT_MAP(CMD_ID_BUTTON_CANCEL,OnCancelButtonEvent)
WISP_MSG_EVENT_MAP(CMD_ID_RADIOBOX_LOCKTYPE,OnLockRadioBoxEvent)
WISP_MSG_EVENT_MAP(CMD_ID_RADIOBOX_FLOATTYPE,OnFloatRadioBoxEvent)

WISP_MSG_EVENT_MAP_END
CAddTypeViewerDlg::CAddTypeViewerDlg()
{
	m_pFormRes = m_FormRes;
	m_CurrentSymbol = NULL;
}
CAddTypeViewerDlg::~CAddTypeViewerDlg()
{
}
bool CAddTypeViewerDlg::OnFormCreate(IN WISP_MSG* pMsg)
{
	m_IconDIBList.Load("\\sysericon\\SourceCodeIcon.bmp",16,16,80);
	m_IconDIBList.SetColorKey(RGB(0,255,0));
	m_OKButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_OK);
	m_CancelButton=(CWispButton*)GetFormItem(CMD_ID_BUTTON_CANCEL);
	m_FloatRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_FLOATTYPE);
	m_LockRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_LOCKTYPE);
	m_DesciptionStr=(CWispStaticStr*)GetFormItem(CMD_ID_STATICSTR_DESCRIPTION);
	m_DecimalRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_DECIMAL);
	m_HexRadioBox=(CWispRadioBox*)GetFormItem(CMD_ID_RADIOBOX_HEX);
	m_BeginAddressEdit=(CWispEdit*)GetFormItem(CMD_ID_EDIT_END_POSITION);
	m_BeginAddressStr=(CWispStaticStr*)GetFormItem(CMD_ID_STATICSTR_BEGINADDRESS);
	m_TypeList=(CWispList*)GetFormItem(CMD_ID_LIST_TYPE);
	m_TypeList->InsertColumn(WSTR(""),500);
	m_HexRadioBox->Check();
	m_FloatRadioBox->Check();
	m_BeginAddressEdit->EnableWindow(false);
	m_HexRadioBox->EnableWindow(false);
	m_DecimalRadioBox->EnableWindow(false);
	m_BeginAddressStr->EnableWindow(false);
	m_OKButton->EnableWindow(false);
	m_DesciptionStr=(CWispStaticStr*)GetFormItem(CMD_ID_STATICSTR_DESCRIPTION);
	m_DesciptionStr->SetWindowText(WSTR("Attach type to address."));
	InitTypeList();
	return true;
}
bool CAddTypeViewerDlg::OnDestroy(IN WISP_MSG* pMsg)
{

	return true;
}
bool CAddTypeViewerDlg::OnFloatRadioBoxEvent(IN WISP_MSG* pMsg)
{
	WCHAR* pStr;
	DWORD BeginAddress;
	m_BeginAddressEdit->EnableWindow(false);
	m_HexRadioBox->EnableWindow(false);
	m_DecimalRadioBox->EnableWindow(false);
	m_BeginAddressStr->EnableWindow(false);
	pStr = m_BeginAddressEdit->GetWindowText();
	if(m_HexRadioBox->IsChecked())
	{
		if(SHexStrToNum(pStr,&BeginAddress))
			m_BeginAddress=BeginAddress;
	}
	else
	{
		if(SDecStrToNum(pStr,&BeginAddress))
			m_BeginAddress=BeginAddress;
	}
	m_BeginAddressEdit->SetWindowText(WSTR(""));
	return true;
}
bool CAddTypeViewerDlg::OnLockRadioBoxEvent(IN WISP_MSG* pMsg)
{
	WCHAR Buffer[30];
	m_BeginAddressEdit->EnableWindow(true);
	m_HexRadioBox->EnableWindow(true);
	m_DecimalRadioBox->EnableWindow(true);
	m_BeginAddressStr->EnableWindow(true);
	if(m_HexRadioBox->IsChecked())
	{
		TSPrintf(Buffer,WSTR("%X"),m_BeginAddress);
	}
	else
	{
		TSPrintf(Buffer,WSTR("%d"),m_BeginAddress);
	}
	m_BeginAddressEdit->SetWindowText(Buffer);
	return true;
}

bool CAddTypeViewerDlg::OnOKButtonEvent(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	NUM_PTR NumPtr;
	DWORD TypeInfo=0;
	hItem = m_TypeList->GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(m_FloatRadioBox->IsChecked())
	{
		TypeInfo=1;
	}
	if(hItem)
	{
		NumPtr = m_TypeList->GetItemData(hItem,0);		
	}
	PostCloseMsg();
	return true;
}
bool CAddTypeViewerDlg::OnCancelButtonEvent(IN WISP_MSG* pMsg)
{
	PostCloseMsg();
	return true;
}
bool CAddTypeViewerDlg::CreateForm(CWispBaseWnd* pParentWnd,UINT ShowMode,UINT BeginAddr)
{
	m_BeginAddress=BeginAddr;
	return CWispForm::CreateForm(pParentWnd,ShowMode);
}

void CAddTypeViewerDlg::InitTypeList()
{
	HANDLE hSubItem;
	DWORD SymbolCount;
	PSDTYPE_INFILE* pTypeList;
	CSDSModule* pSDSModule;
	PSDUDTTYPE pUdtItem;
	DWORD i,index,NameLen;
	if(m_CurrentSymbol==NULL)
		return;
	pSDSModule = m_CurrentSymbol;
	m_TypeList->ClearChildItem();
	pTypeList = pSDSModule->GetSymbolList(&SymbolCount);

	for(i = 1; i < SymbolCount; i++)
	{
		if(pTypeList[i]->Type!=SD_CLASS)
			continue;
		index=0;						
		pUdtItem = (PSDUDTTYPE)&pTypeList[i][1];
		NameLen = TStrLen(pTypeList[i]->uName.Name);
		hSubItem = m_TypeList->InsertItemA(pTypeList[i]->uName.Name,NULL,0,m_IconDIBList[index]);
		m_TypeList->SetItemData(hSubItem,0,i);
	}
	index = 54;							
	for(i = 1; i < SymbolCount; i++)
	{
		if(pTypeList[i]->Type!=SD_STRUCT)
			continue;
		pUdtItem = (PSDUDTTYPE)&pTypeList[i][1];
		hSubItem = m_TypeList->InsertItemA(pTypeList[i]->uName.Name,NULL,0,m_IconDIBList[index]);
		m_TypeList->SetItemData(hSubItem,0,i);
	}
	index = 72;		
	for(i = 1; i < SymbolCount; i++)
	{
		if(pTypeList[i]->Type!=SD_UNION)
			continue;	
		pUdtItem = (PSDUDTTYPE)&pTypeList[i][1];			
		hSubItem = m_TypeList->InsertItemA(pTypeList[i]->uName.Name,NULL,0,m_IconDIBList[index]);
		m_TypeList->SetItemData(hSubItem,0,i);
	}
}
bool CAddTypeViewerDlg::OnTypeListCmd(IN WISP_MSG* pMsg)
{
	switch(pMsg->Command.CmdMsg) {
	case WISP_CMD_ITEM_SELECTED:
		m_OKButton->EnableWindow(true);
		break;
	}
	return true;
}