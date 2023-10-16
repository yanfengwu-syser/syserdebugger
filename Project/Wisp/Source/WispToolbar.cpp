#include "StdAfx.h"
#include "WispToolbar.h"
#include "WispButton.h"
#include "WispEdit.h"
#include "WispStatic.h"

WISP_MSG_MAP_BEGIN(CWispToolbar)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
	WISP_MSG_MAP(WISP_WM_PARENT_RESIZE,OnParentResize)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispWnd)


CWispToolbar::CWispToolbar()
{
	m_CtrlType = WISP_CTRL_TOOL_BAR;
	m_pDIBList = NULL;
	m_Margin = 3;
	m_SeparatorWitdh = 2;
}

CWispToolbar::~CWispToolbar()
{
}

bool CWispToolbar::OnDestroy(IN WISP_MSG*pMsg)
{
	m_BTList.Clear();
	return true;
}

bool CWispToolbar::OnParentResize(IN WISP_MSG*pMsg)
{
	if((m_Style&WISP_TBS_WINDOW)==0)
		Resize(((CWispWnd*)m_ParentWnd)->m_ClientRect.cx,m_WindowRect.cy);
	return true;
}

bool CWispToolbar::OnUpdateClient(IN WISP_MSG*pMsg)
{
	int x;
	if((m_Style&WISP_WS_BACK_TRANS)==0)
		m_pWispBase->m_pCurDrawObj->DrawToolbarBK(&m_ClientDC,&m_ClientRect);
	x=m_Margin;
	for(CBTList::IT Iter=m_BTList.Begin();Iter!=m_BTList.End();Iter++)
	{
		if(Iter->pItemWnd)
		{
			x+=Iter->pItemWnd->m_WindowRect.cx+m_Margin;
		}
		else
		{
			WISP_RECT rc;
			rc.x = x+m_SeparatorWitdh/2;
			rc.y = m_Margin;
			rc.cx = m_SeparatorWitdh;
			rc.cy = m_ClientRect.cy-m_Margin*2;
			m_ClientDC.DrawFrameRect(&rc,false);
			x+=m_SeparatorWitdh+m_Margin;
		}
	}
	m_ClientDC.DrawHLine(0,m_ClientRect.cx-1,m_ClientRect.cy-1,SYS_COLOR[SC_BORDER_BG]);
	return false;
}

bool CWispToolbar::OnRecalcLayout(IN WISP_MSG*pMsg)
{
	int x,y,rx;
	x=m_Margin;
	rx = m_ClientRect.cx - m_Margin;
	for(CBTList::IT Iter=m_BTList.Begin();Iter!=m_BTList.End();Iter++)
	{
		if(Iter->pItemWnd)
		{
			y = CENTER_ALGN(Iter->pItemWnd->m_WindowRect.cy,m_WindowRect.cy);
			if(Iter->ItemStyle&WISP_TBIS_RIGHT_ALIGN)
			{
				rx -= Iter->pItemWnd->m_WindowRect.cx;
				Iter->pItemWnd->MoveToClient(rx,y,false);
				Iter->pItemWnd->Show(rx<x?WISP_SH_HIDDEN:WISP_SH_NORMAL);
				rx-=m_Margin;
			}
			else
			{
				Iter->pItemWnd->MoveToClient(x,y);
				x+=Iter->pItemWnd->m_WindowRect.cx+m_Margin;
			}
		}
		else
		{
			x+=m_SeparatorWitdh+m_Margin;
		}
		if(rx<x)
			rx=x;
	}
	return true;
}

bool CWispToolbar::CreateEx(CWispWnd*pParentWnd,int y,int Height,UINT CmdID,UINT Style)
{
	m_pDIBList = NULL;
	if(Height==-1)
		Height = gpCurWisp->m_Metrics[WISP_SM_FONT_FRAME_HEIGHT]+m_Margin*2;
	return CWispWnd::Create(NULL,0,y,pParentWnd->m_ClientRect.cx,Height,pParentWnd,CmdID,Style);
}

bool CWispToolbar::LoadToolbar(CWispDIBList*pDIBList,WISP_TOOLBAR_RES_ITEM*pResItem)
{
	m_pDIBList = pDIBList;
	for(int n=0;pResItem[n].CmdID || pResItem[n].ItemStyle;n++)
	{
		if(pResItem[n].ItemStyle&WISP_TBIS_SPEARATOR)
		{
			InsertSeparator(-1,pResItem[n].ItemStyle);
		}
		else if(pResItem[n].ItemStyle&WISP_TBIS_EDIT)
		{
			InsertEdit(-1,pResItem[n].ItemStyle,pResItem[n].Width,pResItem[n].CmdID,pResItem[n].CtrlStyle,pResItem[n].pTipString);
		}
		else if(pResItem[n].ItemStyle&WISP_TBIS_STATIC_DIB)
		{
			InsertStaticDIB(-1,pResItem[n].ItemStyle,pResItem[n].CmdID,pDIBList->GetDIB(pResItem[n].DIBIndex));
		}
		else if(pResItem[n].ItemStyle&WISP_TBIS_STATIC_STR)
		{
			InsertStaticStr(-1,pResItem[n].ItemStyle,pResItem[n].CmdID,pResItem[n].pTipString);
		}
		else
		{
			InsertButton(-1,pResItem[n].ItemStyle,pResItem[n].CmdID,pResItem[n].CtrlStyle,pDIBList->GetDIB(pResItem[n].DIBIndex),pResItem[n].pTipString);
		}
	}
	if(m_WindowRect.cy==0)
		Resize(m_WindowRect.cx,pDIBList->GetDIB(0)->Height());
	RecalcLayout();
	return true;
}

bool CWispToolbar::InsertButton(int Pos,UINT ItemStyle,UINT CmdID,UINT Style,CWispDIB*pWispDIB,WISP_CHAR*HelpString)
{
	CBTList::IT Iter;
	CWispButton*pWnd;
	pWnd = new CWispButton;
	pWnd->CreateEx(pWispDIB,0,0,this,CmdID,WISP_BS_TOOLBAR_BT|WISP_WS_BACK_TRANS|Style);
	pWnd->Resize(pWispDIB->m_FrameBuffer.Width+4,pWispDIB->m_FrameBuffer.Height+4);
	pWnd->SetOwner(m_OwnerWnd);
	pWnd->EnableHelpTip(HelpString);
	pWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	if(Pos>=0)
	{
		Iter = m_BTList[Pos];
		m_BTList.InsertBefore(Iter);
	}
	else
	{
		Iter = m_BTList.Append();
	}
	Iter->ItemStyle = ItemStyle;
	Iter->pItemWnd = pWnd;
	Iter->pDIB = pWispDIB;
	RecalcLayout();
	return true;
}

bool CWispToolbar::InsertEdit(int Pos,UINT ItemStyle,int Width,UINT CmdID,UINT Style,WISP_CHAR*HelpString)
{
	int Height;
	CBTList::IT Iter;
	CWispEdit*pWnd;
	pWnd = new CWispEdit;
	Height = m_ClientDC.m_pFont->m_Height+m_Margin*2;
	pWnd->Create(NULL,0,0,Width,Height,this,CmdID,Style);
	pWnd->SetOwner(m_OwnerWnd);
	pWnd->EnableHelpTip(HelpString);
	pWnd->m_AdvStyle |= WISP_WAS_AUTO_DELETE;
	if(Pos>=0)
	{
		Iter = m_BTList[Pos];
		m_BTList.InsertBefore(Iter);
	}
	else
	{
		Iter = m_BTList.Append();
	}
	Iter->ItemStyle = ItemStyle;
	Iter->pItemWnd = pWnd;
	Iter->pDIB = NULL;
	RecalcLayout();
	return true;
}

bool CWispToolbar::InsertSeparator(int Pos,UINT ItemStyle)
{
	CBTList::IT Iter;
	if(Pos>=0)
	{
		Iter = m_BTList[Pos];
		m_BTList.InsertBefore(Iter);
	}
	else
	{
		Iter = m_BTList.Append();
	}
	Iter->ItemStyle = ItemStyle;
	Iter->pItemWnd = NULL;
	Iter->pDIB = NULL;
	RecalcLayout();
	Update();
	return true;
}

bool CWispToolbar::InsertStaticDIB(int Pos,UINT ItemStyle,UINT CmdID,CWispDIB*pWispDIB)
{
	CBTList::IT Iter;
	CWispStaticDIB*pWnd;
	pWnd = new CWispStaticDIB;
	pWnd->Create(pWispDIB,0,0,this,CmdID);
	pWnd->m_AdvStyle |= WISP_WAS_AUTO_DELETE;
	if(Pos>=0)
	{
		Iter = m_BTList[Pos];
		m_BTList.InsertBefore(Iter);
	}
	else
	{
		Iter = m_BTList.Append();
	}
	Iter->ItemStyle = ItemStyle;
	Iter->pItemWnd = pWnd;
	Iter->pDIB = pWispDIB;
	RecalcLayout();
	return true;
}

bool CWispToolbar::InsertStaticStr(int Pos,UINT ItemStyle,UINT CmdID,WISP_PCSTR String)
{
	CBTList::IT Iter;
	CWispStaticStr*pWnd;
	pWnd = new CWispStaticStr;
	pWnd->Create(String,0,0,0,0,this,CmdID);
	pWnd->m_AdvStyle |= WISP_WAS_AUTO_DELETE;
	if(Pos>=0)
	{
		Iter = m_BTList[Pos];
		m_BTList.InsertBefore(Iter);
	}
	else
	{
		Iter = m_BTList.Append();
	}
	Iter->ItemStyle = ItemStyle;
	Iter->pItemWnd = pWnd;
	Iter->pDIB = NULL;
	pWnd->Resize(pWnd->m_WindowDC.GetTextExtent(String),pWnd->m_WindowDC.m_pFont->m_Height);
	RecalcLayout();
	return true;
}

bool CWispToolbar::RemoveItem(int Pos)
{
	CBTList::IT Iter = m_BTList[Pos];
	if(Iter==NULL)
		return false;
	Iter->pItemWnd->Destroy();
    m_BTList.Remove(Iter);
	RecalcLayout();
	Update();
	return true;
}

void CWispToolbar::SetOwner(CWispBaseWnd*pOwnerWnd)
{
	for(CBTList::IT Iter=m_BTList.Begin();Iter!=m_BTList.End();Iter++)
	{
		if(Iter->pItemWnd)
			Iter->pItemWnd->SetOwner(pOwnerWnd);
	}
	CWispWnd::SetOwner(pOwnerWnd);
}

bool CWispToolbar::EnableItemByPos(int Pos,bool State)
{
	CWispBaseWnd*pWnd=GetToolbarItemByPos(Pos);
	if(pWnd==NULL)
		return false;
	pWnd->EnableWindow(State);
	return true;
}

bool CWispToolbar::EnableItem(UINT CmdID,bool State)
{
	CWispBaseWnd*pWnd=GetToolbarItem(CmdID);
	if(pWnd==NULL)
		return false;
	pWnd->EnableWindow(State);
	return true;
}

CWispBaseWnd*CWispToolbar::GetToolbarItemByPos(int Pos)
{
	if(Pos<0 || Pos>=m_BTList.Count())
		return false;
	CBTList::IT Iter = m_BTList[Pos];
	if(Iter==NULL)
		return NULL;
	return Iter->pItemWnd;
}

CWispBaseWnd*CWispToolbar::GetToolbarItem(UINT CmdID)
{
	for(CBTList::IT Iter=m_BTList.Begin();Iter!=m_BTList.End();Iter++)
	{
		if(Iter->pItemWnd && Iter->pItemWnd->m_CmdID==CmdID)
			return Iter->pItemWnd;
	}
	return NULL;
}

