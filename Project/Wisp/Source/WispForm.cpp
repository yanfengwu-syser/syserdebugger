#include "StdAfx.h"
#include "Wisp.h"

WISP_MSG_MAP_BEGIN(CWispForm)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_CMD_MAP_BEGIN(CWispForm)
	WISP_MSG_CMD_MAP(WISP_ID_CLOSE,OnCmdClose)
	WISP_MSG_CMD_MAP(WISP_ID_CANCEL,OnCmdCancel)
	WISP_MSG_CMD_MAP(WISP_ID_OK,OnCmdOK)
WISP_MSG_CMD_MAP_DEFAULT_END(OnBTCmdDefault)

CWispForm::CWispForm(void)
{
	m_CtrlType = WISP_CTRL_FORM;
	m_Result = WISP_ID_NULL;
	m_pFormRes = NULL;
}

CWispForm::~CWispForm(void)
{
}

bool CWispForm::CreateForm(CWispBaseWnd*pParenWnd,UINT ShowMode)
{
	CODE_ASSERT(m_pFormRes);
	m_ParentWnd = pParenWnd;
	if(LoadForm(m_pFormRes)==false)
		return false;
	m_Result = WISP_ID_NULL;
	WISP_MSG Msg;
	Msg.hWnd = this;
	Msg.Msg = WISP_WM_FORM_CREATE;
	SEND_MSG(&Msg);
	Center(pParenWnd);
	Focus();
	Show(ShowMode);
	return true;
}

bool CWispForm::LoadForm(WISP_FORM_RES_ITEM*ItemAry)
{
	CWispBaseWnd*pWnd;
	for(int n=0;ItemAry[n].Type!=WISP_CTRL_NULL;n++)
	{
		switch(ItemAry[n].Type)
		{
		case WISP_CTRL_FORM:
			if(Create(ItemAry[n].pName,ItemAry[n].rc,m_ParentWnd,ItemAry[n].CmdID,ItemAry[n].Style)==false)
				return false;
			if(ItemAry[n].pData)
				LoadTitleDIB((PCSTR)ItemAry[n].pData);
			pWnd = this;
			break;
		case WISP_CTRL_BUTTON:
			pWnd = new CWispButton;
			((CWispButton*)pWnd)->Create(ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_EDIT:
			pWnd = new CWispEdit;
			((CWispEdit*)pWnd)->Create(ItemAry[n].rc,ItemAry[n].Style,this,ItemAry[n].CmdID);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_LIST:
			pWnd = new CWispList;
			((CWispList*)pWnd)->Create(ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_STATIC_STRING:
			pWnd = new CWispStaticStr;
			((CWispStaticStr*)pWnd)->Create((WISP_CHAR*)ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_STATIC_URL:
			pWnd = new CWispStaticURL;
			((CWispStaticURL*)pWnd)->Create((WISP_CHAR*)ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_STATIC_DIB:
			pWnd = new CWispStaticDIB;
			((CWispStaticDIB*)pWnd)->Create(WispDIB((PCSTR)ItemAry[n].pData,0),ItemAry[n].rc.x,ItemAry[n].rc.y,this,ItemAry[n].CmdID);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_STATIC_GROUP:
			pWnd = new CWispStaticGroup;
			((CWispStaticGroup*)pWnd)->Create(ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_COMBO_BOX:
			pWnd = new CWispComboBox;
			((CWispComboBox*)pWnd)->Create(ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_PROGRESS:
			pWnd = new CWispProgress;
			((CWispProgress*)pWnd)->Create(NULL,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_TAB:
			pWnd = new CWispTabWnd;
			((CWispTabWnd*)pWnd)->Create(ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_CHECK_BOX:
			pWnd = new CWispCheckBox;
			((CWispCheckBox*)pWnd)->Create(ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		case WISP_CTRL_RADIO_BOX:
			pWnd = new CWispRadioBox;
			((CWispRadioBox*)pWnd)->Create(ItemAry[n].pName,ItemAry[n].rc,this,ItemAry[n].CmdID,ItemAry[n].Style);
			pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
			if(ItemAry[n].CmdID)
				m_FormItemMap.InsertUnique(ItemAry[n].CmdID,pWnd);
			break;
		default:
			//CODE_WARNING("Wisp : Unsupport control type !");
			break;
		}
		if(ItemAry[n].pTipString)
			pWnd->EnableHelpTip(ItemAry[n].pTipString);
		if(pWnd->m_Style&WISP_WS_DEFAULT)
			pWnd->Focus();
	}
	return true;
}

CWispBaseWnd* CWispForm::GetFormItem(UINT CmdID)
{
	TMap<UINT,CWispBaseWnd*>::IT Iter = m_FormItemMap.Find(CmdID);
	if(Iter==m_FormItemMap.End())
		return NULL;
	return *Iter;
}

bool CWispForm::Destroy()
{
	m_FormItemMap.Clear();
	return CWispWnd::Destroy();
}

bool CWispForm::OnCmdClose(IN WISP_MSG*pMsg)
{
	m_Result = WISP_ID_CANCEL;
	return true;
}

bool CWispForm::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.KeyType == WISP_VK_ESCAPE && pMsg->KeyEvent.bKeyDown)
	{
		if(m_Style&WISP_WS_BT_CLOSE)
		{
			PostCloseMsg();
		}
		return true;
	}
	return true;
}

bool CWispForm::OnCmdCancel(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		m_Result = WISP_ID_CANCEL;
		PostCloseMsg();
	}
	return false;
}

bool CWispForm::OnCmdOK(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		m_Result = WISP_ID_OK;
		PostCloseMsg();
	}
	return false;
}

bool CWispForm::OnBTCmdDefault(IN WISP_MSG*pMsg)
{
	if(	pMsg->Command.CmdMsg == WISP_CMD_BT_UP	&&
		pMsg->Command.CmdID > WISP_ID_FORM_CLOSE_ID_START && 
		pMsg->Command.CmdID < WISP_ID_FORM_CLOSE_ID_END	)
	{
		m_Result = pMsg->Command.CmdID;
		PostCloseMsg();
	}
	return true;
}
