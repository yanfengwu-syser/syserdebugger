#include "StdAfx.h"
#include "WispMenu.h"
#include "WispMisc.h"
#include "WispButton.h"
#include "WispRGBSelect.h"

class CWispSelectMenu : public CWispMenu
{
public:
	CWispSelectMenu();
	int		m_Result;
	static	WISP_PCSTR m_szYesNoList[];
	bool	Create(WISP_PCSTR*szTextList);
	bool	ClickItemNotify(HANDLE hMenuItem,UINT CmdID);
};

CWispSelectMenu::CWispSelectMenu()
{
	m_Result = -1;
}

bool CWispSelectMenu::ClickItemNotify(HANDLE hMenuItem,UINT CmdID)
{
	m_Result = (int)(CmdID - WISP_ID_USER_START);
	PostCloseMsg();
	return true;
}

bool CWispSelectMenu::Create(WISP_PCSTR*szTextList)
{
	UINT Style;
	int Width,Height,ItemWidth,Start;
	if(CWispMenu::Create(NULL,0,0,0,0,NULL,0,WISP_WS_THIN_BORDER|WISP_WMS_POPUP,WISP_SH_HIDDEN)==false)
		return false;
	CWispBaseWnd::SetOwner(this);
	Height = Width = 0;
	int n = 0;
	while(szTextList[n])
	{
		Style = 0;
		Start = 0;
		if(szTextList[n][0]=='%')
		{
			if(szTextList[n][1]=='d')
			{
				Style = WISP_MIS_DISABLED;
				Start = 2;
			}
		}
		InsertItem(-1,&szTextList[n][Start],Style,WISP_ID_USER_START+n);
		ItemWidth = m_ClientDC.GetTextExtent(szTextList[n]);
		if(ItemWidth > Width)
			Width = ItemWidth;
		Height+=m_PopupItemHeight;
		n++;
	}
	Width += m_MenuStartSpace+m_MenuEndSpace+m_BorderSize*2+m_MenuMarge*2;
	Height += m_BorderSize*2+m_MenuMarge*2;
	Resize(Width,Height);
	return true;
}

bool GetResultFromList(int x,int y,WISP_PCSTR*szTextList,int*pResult,int Default)
{
	HANDLE hItem;
	WISP_POINT pt;
	CWispBaseWnd*pOldFocusWnd;
	CWispSelectMenu Menu;
	Menu.Create(szTextList);
	pt.x = x;
	pt.y = y;
	pOldFocusWnd = Menu.m_pWispBase->m_pFocusWnd;
	Menu.Popup(&pt,false);
	if(Default>=0)
	{
		hItem = Menu.GetItemByPos(Default);
		if(hItem)
			Menu.SetHoverItem(hItem);
	}
	Menu.Show(WISP_SH_MODAL_BLOCK);
	Menu.Destroy();
	pOldFocusWnd->Focus();
	if(Menu.m_Result<0)
		return false;
	*pResult= Menu.m_Result;
	return true;
}

class CStrInputWnd : public CWispForm
{
public:
	CStrInputWnd();
	~CStrInputWnd();
	CWispString*	m_pStrText;
	WISP_PCSTR		m_pszTitle;
	WISP_PCSTR		m_pszStaticText;
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnOK)
};

enum CStrInputWnd::WISP_FORM_ID
{
	CMD_ID_EDIT_TEXT = WISP_ID_USER_START,
	CMD_ID_STATIC_TEXT
};

WISP_FORM_RES_ITEM CStrInputWnd::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,300,100},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("Please Input ...")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,270,50},
		CMD_ID_STATIC_TEXT,
		WISP_WS_NULL,
		WSTR("Text"),
	},
	{
		WISP_CTRL_EDIT,
		{20,30,200,16},
		CMD_ID_EDIT_TEXT,
		WISP_WS_THIN_BORDER|WISP_ES_AUTOHSCROLL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{230,30,40,16},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CStrInputWnd)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CStrInputWnd)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnOK)
WISP_MSG_CMD_MAP_END


CStrInputWnd::CStrInputWnd()
{
	m_pFormRes = m_FormRes;
	m_pszStaticText = m_pszTitle = 0;
}

CStrInputWnd::~CStrInputWnd()
{

}

bool CStrInputWnd::OnFormCreate(IN WISP_MSG*pMsg)
{
	if(m_pszStaticText)
		GetFormItem(CMD_ID_STATIC_TEXT)->SetWindowText(m_pszStaticText);
	if(m_pszTitle)
		SetWindowText(m_pszTitle);
	return true;
}

bool CStrInputWnd::OnOK(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
		*m_pStrText = GetFormItem(CMD_ID_EDIT_TEXT)->GetWindowText();
	return true;
}

bool GetInputText(CWispString&szText,WISP_PSTR szStaticText,WISP_PSTR szTitle)
{
	CStrInputWnd InputWnd;
	InputWnd.m_pStrText = &szText;
	InputWnd.m_pszStaticText = szStaticText;
	InputWnd.m_pszTitle = szTitle;
	InputWnd.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	return InputWnd.m_Result == WISP_ID_OK;
}

bool GetRGBColor(COLORREF*pResult,COLORREF *pDefault)
{
	CWispRGBSelect RGBSelect;
	if(pDefault)
		RGBSelect.m_RGBClr = *pDefault;
	RGBSelect.CreateForm(NULL,WISP_SH_MODAL_BLOCK);
	if(RGBSelect.m_Result != WISP_ID_OK)
		return false;
	*pResult = RGBSelect.m_RGBClr;
	return true;
}


enum CWispProgressForm::WISP_FORM_ID
{
	CMD_ID_PROGRESS = WISP_ID_USER_START,
	CMD_ID_TEXT
};

WISP_FORM_RES_ITEM CWispProgressForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,325,60},
		WISP_ID_NULL,
		WISP_WS_THIN_BORDER,
		NULL
	},
	{
		WISP_CTRL_STATIC_STRING,
		{10,10,300,16},
		CMD_ID_TEXT,
		WISP_WS_NULL,
		NULL,
		NULL,
		NULL
	},
	{
		WISP_CTRL_PROGRESS,
		{10,30,300,16},
		CMD_ID_PROGRESS,
		WISP_WS_NULL,
		NULL,
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};


WISP_MSG_MAP_BEGIN(CWispProgressForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)


CWispProgressForm::CWispProgressForm()
{
	m_pFormRes = m_FormRes;
	m_pProgessCtrl = NULL;
	m_pStaticStr = NULL;
}

CWispProgressForm::~CWispProgressForm()
{

}

bool CWispProgressForm::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pProgessCtrl = (CWispProgress*) GetFormItem(CMD_ID_PROGRESS);
	m_pProgessCtrl->SetRange(0,99);
	m_pProgessCtrl->SetPos(0);
	m_pStaticStr = (CWispStaticStr*) GetFormItem(CMD_ID_TEXT);
	return true;
}

void CWispProgressForm::SetProgressText(WISP_PCSTR szText)
{
	m_pStaticStr->SetWindowText(szText);
}
