#include "StdAfx.h"
#include "WispMsgBox.h"
#include "WispBase.h"

WISP_MSG_MAP_BEGIN(CWispMsgBox)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
WISP_MSG_MAP_END(CWispWnd)

CWispMsgBox::CWispMsgBox(void)
{
	m_nBtnWidth	= 50;
	m_nReturnStatus = WISP_ID_NULL;
	m_CtrlType = WISP_CTRL_MSG_BOX;
}

CWispMsgBox::~CWispMsgBox(void)
{
}

bool CWispMsgBox::Create(IN CWispBaseWnd*pParentWnd)
{
	return  CWispWnd::Create(NULL, 0,0,0,0, pParentWnd,0,WISP_WS_CAPTION | WISP_WS_BORDER | WISP_WS_BT_CLOSE);
}

int CWispMsgBox::StaticShowMsgBox(WISP_CHAR* pText, WISP_CHAR* pCaption, UINT uType,CWispBaseWnd*pParentWnd)
{
	CWispMsgBox MsgBox;
	if(MsgBox.Create(NULL)==false)
		return WISP_ID_NULL;
	return MsgBox.ShowMsgBox(pText, pCaption, uType);
}

int CWispMsgBox::ShowMsgBox(WISP_CHAR* pText, WISP_CHAR* pCaption, UINT uType)
{
		// caption and infomation
		m_strText	= pText;
		m_WndText	= pCaption;
		// button style
		if( !(uType&WISP_MB_CUSTOMIZE) )
		{
			UINT uBtnType = uType&WISP_MB_BTNMASK;
			if(uBtnType==0)	uBtnType = WISP_MB_OK;
			AddDefaultButton(uBtnType);
		}
		// icon
		if( uType&WISP_MB_ICONMASK)
			AddDefaultIcon(uType);

		// calc window width
		WISP_RECT	rcText={0,0,0,0};
		m_ClientDC.DrawString(pText,&rcText, WISP_DT_CALCRECT);
		int cx1 = rcText.cx+(m_dibIcon.m_FrameBuffer.Buffer?20:0);
		int cx2 = m_ClientDC.GetTextExtent(pCaption);
		int cx3 = (int)m_vButtons.Count()*(m_nBtnWidth+MSGBOX_BTN_SPACE*2);
		int nWndWidth = MAX(MAX(cx1,cx2),cx3) + 60;
		if(nWndWidth<150)	nWndWidth = 150;
		int nWndHeight = MAX(rcText.cy+50, 120);
		Resize(nWndWidth,  nWndHeight);
		Center();
		// create buttons
		int nBeginPos = (nWndWidth - m_vButtons.Count()*(m_nBtnWidth+MSGBOX_BTN_SPACE*2))/2;
		for(TList<BTNPAIR>::IT It=m_vButtons.Begin(); It!=m_vButtons.End(); It++)
		{
			nBeginPos += MSGBOX_BTN_SPACE;
			CWispButton* pButton = new CWispButton();
			pButton->Create(It->pBtnText, nBeginPos, nWndHeight-50, m_nBtnWidth, m_ClientDC.m_pFont->m_Height+6, this, It->nID, WISP_BS_NORMAL, WISP_SH_NORMAL);
			if(It->nID==WISP_ID_OK || It->nID==WISP_ID_YES)
				pButton->Focus();
			pButton->m_AdvStyle |= WISP_WAS_AUTO_DELETE;
			nBeginPos += (m_nBtnWidth+MSGBOX_BTN_SPACE);
		}
		// do modal
		Show(WISP_SH_MODAL_BLOCK);
		Destroy();
		RemoveAllButtons();
		return m_nReturnStatus;
}

bool CWispMsgBox::OnUpdateClient(IN WISP_MSG* pMsg)
{
	CWispWnd::OnUpdateClient(pMsg);
	WISP_RECT rect;
	m_dibIcon.m_FrameBuffer.Buffer? rect.x = 50 : rect.x = 20;
	rect.cx = m_ClientRect.cx - rect.x;
	rect.y = 10;
	rect.cy = m_ClientRect.cy;
	m_ClientDC.DrawString(m_strText, &rect, WISP_DT_LEFT);


	if(m_dibIcon.m_FrameBuffer.Buffer)
		m_ClientDC.DrawDIB(10, 10, &m_dibIcon);
	return false;
}

bool CWispMsgBox::OnCommand(IN WISP_MSG* pMsg)
{
	if(pMsg->Command.CtrlType==WISP_CTRL_BUTTON)
	{
		if(pMsg->Command.CmdMsg != WISP_CMD_BT_UP)
			return true;
		m_nReturnStatus = pMsg->Command.CmdID;
		Show(WISP_SH_HIDDEN);
		return true;
	}
	return true;
}

void CWispMsgBox::AddDefaultButton(UINT uType)
{
	if(uType & WISP_MB_OK)
		AddButton(WISP_STR("OK"),WISP_ID_OK);
	if(uType & WISP_MB_YES)
		AddButton(WISP_STR("YES"),WISP_ID_YES);
	if(uType & WISP_MB_NO)
		AddButton(WISP_STR("NO"),WISP_ID_NO);
	if(uType & WISP_MB_CANCEL)
		AddButton(WISP_STR("CANCEL"),WISP_ID_CANCEL);
	if(uType & WISP_MB_TRY)
		AddButton(WISP_STR("TRY"),WISP_ID_TRY);
	if(uType & WISP_MB_CONTINUE)
		AddButton(WISP_STR("CONTINUE"),WISP_ID_CONTINUE);
	if(uType & WISP_MB_ABORT)
		AddButton(WISP_STR("ABORT"),WISP_ID_ABORT);
	if(uType & WISP_MB_RETRY)
		AddButton(WISP_STR("RETRY"),WISP_ID_RETRY);
	if(uType & WISP_MB_IGNORE)
		AddButton(WISP_STR("IGNORE"),WISP_ID_IGNORE);
}

void CWispMsgBox::AddDefaultIcon(UINT uType)
{
	if(uType&WISP_MB_ICONINFOMATION)
		m_dibIcon.Load("\\WispApp\\MsgBox\\Information.bmp");
	else if(uType&WISP_MB_ICONQUESTION)
		m_dibIcon.Load("\\WispApp\\MsgBox\\Question.bmp");
	else if(uType&WISP_MB_ICONALERT)
		m_dibIcon.Load("\\WispApp\\MsgBox\\Alert.bmp");
	else if(uType&WISP_MB_ICONERROR)
		m_dibIcon.Load("\\WispApp\\MsgBox\\Error.bmp");

	m_dibIcon.m_Type = WISP_DIB_TK;
	m_dibIcon.m_ColorKey = SYS_COLOR[SC_UNNAMED_15];
}

void CWispMsgBox::AddButton(WISP_CHAR* pText, int nID)
{
	BTNPAIR stPair;
	stPair.pBtnText	= pText;
	stPair.nID		= nID;

	int nLength = m_ClientDC.GetTextExtent(pText)+4;
	if(nLength>m_nBtnWidth)
		m_nBtnWidth = nLength;

	m_vButtons.Append(stPair);
}

void CWispMsgBox::RemoveAllButtons()
{
	m_vButtons.Clear();
}
