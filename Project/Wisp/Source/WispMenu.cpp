#include "StdAfx.h"
#include "WispMenu.h"

WISP_MSG_MAP_BEGIN(CWispMenu)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_MOUSE_LEAVE,OnMouseLeave)
	WISP_MSG_MAP(WISP_WM_PARENT_RESIZE,OnParentResize)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_UPDATE_BORDER,OnUpdateBorder)
	WISP_MSG_MAP(WISP_WM_LOST_FOCUS,OnLostFocus)
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispWnd)

CWispMenu::CWispMenu()
{
	m_CtrlType = WISP_CTRL_MENU;
	m_PopupItemHeight = 18;
	m_WndItemHeight = 20;
	m_MenuStartSpace = 20;
	m_MenuIconSpace = 20;
	m_MenuEndSpace = 20;
	m_MenuMarge = 5;
	m_WndMenuHeight = 22;
	m_PopupMenuTopSpace = 5;
	m_PopupMenuBottomSpace = 5;
}

CWispMenu::~CWispMenu()
{
}

bool CWispMenu::InitWnd()
{
	if(CWispWnd::InitWnd()==false)
		return false;
	m_BorderSize = 1;
	m_pParentMenu = NULL;
	m_HoverIter = m_ItemList.End();
	m_pParentMenu = NULL;
	m_bExpandMenu = false;
	m_WndMenuItemWidth = 0;
	return true;
}

bool CWispMenu::OnParentResize(WISP_MSG*pMsg)
{
	if((m_Style&WISP_WMS_POPUP)==0)
		Resize(((CWispWnd*)m_ParentWnd)->m_ClientRect.cx,m_WindowRect.cy);
	return true;
}

bool CWispMenu::OnRecalcLayout(WISP_MSG*pMsg)
{
	int x,y;
	if(m_Style & WISP_WMS_POPUP)
	{
		y = m_MenuMarge;
		for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
		{
			if(Iter->Style&WISP_MIS_SEPARATOR)
			{
				Iter->ItemRC.x = 0;
				Iter->ItemRC.y = y;
				Iter->ItemRC.cx = m_ClientRect.cx;
				Iter->ItemRC.cy = 1;
			}
			else
			{
				Iter->ItemRC.x = 0;
				Iter->ItemRC.y = y;
				Iter->ItemRC.cx = m_ClientRect.cx;
				Iter->ItemRC.cy = m_PopupItemHeight;
			}
			y+=Iter->ItemRC.cy;
		}
	}
	else
	{
		x = 0;
		for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
		{
			if(Iter->Style&WISP_MIS_SEPARATOR)
			{
				Iter->ItemRC.x = x;
				Iter->ItemRC.y = (m_WndMenuHeight-m_WndItemHeight)/2;
				Iter->ItemRC.cy = m_WndItemHeight;
				Iter->ItemRC.cx = 1+m_MenuMarge*2;
			}
			else
			{
				Iter->ItemRC.x = x;
				Iter->ItemRC.y = (m_WndMenuHeight-m_WndItemHeight)/2;
				Iter->ItemRC.cy = m_WndItemHeight;
				Iter->ItemRC.cx = m_ClientDC.GetTextExtent(Iter->szText)+m_MenuMarge*2;
				if(Iter->Style&WISP_MIS_CHECKBOX)
					Iter->ItemRC.cx+=WISP_SSI_CHECKBOX_SIZE+m_MenuMarge;
				else if(Iter->pIcon)
					Iter->ItemRC.cx+=Iter->pIcon->Width()+m_MenuMarge;
			}
			x+=Iter->ItemRC.cx;
		}
		m_WndMenuItemWidth = x;
	}
	return true;
}

bool CWispMenu::OnDestroy(WISP_MSG*pMsg)
{
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(Iter->Style&WISP_MIS_POPUP)
			Iter->pSubMenu->Destroy();
	}
	m_ItemList.Clear();
	return true;
}

bool CWispMenu::OnUpdateClient(WISP_MSG*pMsg)
{
	if(m_Style&WISP_WMS_POPUP)
	{
		DrawPopupMenu();
	}
	else
	{
		DrawWndMenu();
	}
	return false;
}

void CWispMenu::DrawWndMenu()
{
	UINT Status,SysIcon;
	int Index,IconSpace;
	WISP_RECT ItemRC,*pRC,rc;
	CWispMenu*pPopupMenu;
	if((m_Style&WISP_WS_BACK_TRANS)==0)
		m_pWispBase->m_pCurDrawObj->DrawMenuBK(&m_ClientDC,&m_ClientRect,STATUS_NORMAL);
	Index=0;
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(Iter->Style&WISP_MIS_SEPARATOR)
		{
			m_ClientDC.DrawVLine(Iter->ItemRC.x+m_MenuMarge,Iter->ItemRC.y,Iter->ItemRC.y+Iter->ItemRC.cy-1,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
			Index++;
			continue;
		}
		ItemRC.x = Iter->ItemRC.x+m_pWispBase->m_Metrics[WISP_SM_THIN_BORDER_SIZE];
		ItemRC.cx = Iter->ItemRC.cx-m_MenuMarge*2;
		ItemRC.y = Iter->ItemRC.y;
		ItemRC.cy = Iter->ItemRC.cy;
		if(Iter==m_HoverIter)
		{
			if(m_bExpandMenu && (Iter->Style&WISP_MIS_POPUP))
			{
				pRC = &Iter->ItemRC;
				pPopupMenu = (CWispMenu*)Iter->Data;
				m_ClientDC.DrawHLine(pRC->x,pRC->x+pRC->cx-1,pRC->y,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
				m_ClientDC.DrawVLine(pRC->x,pRC->y,pRC->y+pRC->cy-1,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
				m_ClientDC.DrawVLine(pRC->x+pRC->cx-1,pRC->y,pRC->y+pRC->cy-1,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
				if(pPopupMenu->m_WindowRect.cx<pRC->cx)
					m_ClientDC.DrawHLine(pRC->x+pRC->cx-1,pRC->x+pPopupMenu->m_WindowRect.cx-1,pRC->y+pRC->cy-1,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
			}
			else
			{
				if((Iter->Style&WISP_MIS_DISABLED)==0)
				{
					m_ClientDC.DrawFullRect(&Iter->ItemRC,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_HOVER_LIGHT_BG]);
					m_ClientDC.DrawRect(&Iter->ItemRC,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CTRL_HOVER_FOCUS]);
				}
			}
			Status = STATUS_HOVER;
		}
		else
		{
			Status = STATUS_NORMAL;
		}
		if(Iter->Style&WISP_MIS_CHECKBOX)
		{
			rc.x = ItemRC.x;
			rc.cx = WISP_SSI_CHECKBOX_SIZE;
			rc.y = ItemRC.y;
			rc.cy = ItemRC.cy;
			SysIcon = (Iter->Style&WISP_MIS_CHECKED)?WISP_SSI_CHECKBOX_CHECKED:WISP_SSI_CHECKBOX_UNCHECKED;
			m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_ClientDC,&rc,SysIcon,STATUS_NORMAL);
			IconSpace = WISP_SSI_CHECKBOX_SIZE+m_MenuMarge;
			ItemRC.x+=IconSpace;
			ItemRC.cx-=IconSpace;
		}
		else if(Iter->pIcon)
		{
			rc.x = ItemRC.x;
			rc.cx = Iter->pIcon->Width();
			rc.y = ItemRC.y;
			rc.cy = ItemRC.cy;
			if(Iter->Style&WISP_MIS_DISABLED)
				m_ClientDC.DrawGrayDIB(&rc,Iter->pIcon);
			else
				m_ClientDC.DrawDIB(&rc,Iter->pIcon);
			IconSpace = Iter->pIcon->Width()+m_MenuMarge;
			ItemRC.x+=IconSpace;
			ItemRC.cx-=IconSpace;
		}
		else
		{
			ItemRC.x+=m_MenuMarge/2;
		}
		if(Iter->Style&WISP_MIS_DISABLED)
			Status = STATE_DISABLED;
		if(Iter->TextClr)
		{
			m_ClientDC.SetTextColor(Iter->TextClr);
			m_pWispBase->m_pCurDrawObj->DrawMenuString(&m_ClientDC,&ItemRC,Iter->szText,Status);
			m_ClientDC.RestoreTextColor();
		}
		else
		{
			m_pWispBase->m_pCurDrawObj->DrawMenuString(&m_ClientDC,&ItemRC,Iter->szText,Status);
		}
		Index++;
	}
	m_ClientDC.DrawHLine(0,m_ClientRect.cx-1,m_ClientRect.cy-1,SYS_COLOR[SC_BORDER_BG]);
}

void CWispMenu::DrawPopupMenu()
{
	UINT Status,SysIcon;
	int Index,StrWidth;
	WISP_RECT rc,ItemRc;

	rc.x=rc.y=0;
	rc.cx = m_MenuIconSpace;
	rc.cy = m_ClientRect.cy;
	m_pWispBase->m_pCurDrawObj->DrawMenuIconSpaceBK(&m_ClientDC,&rc);

	ItemRc.x = m_MenuStartSpace;
	ItemRc.y = m_PopupMenuTopSpace;
	ItemRc.cx = m_ClientRect.cx - m_MenuStartSpace;
	ItemRc.cy = m_PopupItemHeight;
	Index=0;
	StrWidth = m_ClientRect.cx-m_MenuMarge*2-m_MenuStartSpace-m_MenuEndSpace;
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		ItemRc.cy = Iter->ItemRC.cy;
		if(Iter->Style&WISP_MIS_SEPARATOR)
		{			
			m_ClientDC.DrawHLine(m_MenuIconSpace,m_ClientRect.cx-1,ItemRc.y,
								m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
			ItemRc.y+=Iter->ItemRC.cy;
			Index++;
			continue;
		}
		rc.y = ItemRc.y;
		rc.cy = ItemRc.cy;
		Status = Iter==m_HoverIter?STATUS_HOVER:STATUS_NORMAL;
		m_pWispBase->m_pCurDrawObj->DrawMenuBK(&m_ClientDC,&ItemRc,Status);
		rc.x = m_MenuStartSpace+m_MenuMarge;
		rc.cx = StrWidth;
		if(Iter->Style&WISP_MIS_DISABLED)
			Status = STATE_DISABLED;
		if(Iter->TextClr)
		{
			m_ClientDC.SetTextColor(Iter->TextClr);
			m_pWispBase->m_pCurDrawObj->DrawMenuString(&m_ClientDC,&rc,Iter->szText,Status);
			m_ClientDC.RestoreTextColor();
		}
		else
		{
			m_pWispBase->m_pCurDrawObj->DrawMenuString(&m_ClientDC,&rc,Iter->szText,Status);
		}
		if(Iter->Style&WISP_MIS_CHECKBOX)
		{
			rc.x = 0;
			rc.cx = m_MenuStartSpace;
			SysIcon = (Iter->Style&WISP_MIS_CHECKED)?WISP_SSI_CHECKBOX_CHECKED:WISP_SSI_CHECKBOX_UNCHECKED;
			m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(&m_ClientDC,&rc,SysIcon,Status);
		}
		else if(Iter->pIcon)
		{
			rc.x = 0;
			rc.cx = m_MenuStartSpace;
			if(Iter->Style&WISP_MIS_DISABLED)
				m_ClientDC.DrawGrayDIB(&rc,Iter->pIcon);
			else
				m_ClientDC.DrawDIB(&rc,Iter->pIcon);
		}
		if(Iter->Style&WISP_MIS_POPUP)
		{
			rc.x = m_ClientRect.cx - m_MenuEndSpace;
			rc.cx = m_MenuEndSpace;
			m_pWispBase->m_pCurDrawObj->DrawMenuString(&m_ClientDC,&rc,WISP_STR(">>"),STATUS_NORMAL);
		}
		ItemRc.y+=Iter->ItemRC.cy;
		Index++;
	}
	rc.x=rc.y=0;
	rc.cx=m_ClientRect.cx;
	rc.cy=m_PopupMenuTopSpace;
	m_pWispBase->m_pCurDrawObj->DrawMenuTopFrame(&m_ClientDC,&rc);
	rc.x=0;
	rc.cx=m_ClientRect.cx;
	rc.y=ItemRc.y;
	rc.cy=m_PopupMenuBottomSpace;
	m_pWispBase->m_pCurDrawObj->DrawMenuBottomFrame(&m_ClientDC,&rc);

}

bool CWispMenu::OnUpdateBorder(WISP_MSG*pMsg)
{
	WISP_MENU_ITEM*pMenuItem;
	if(m_pParentMenu && (m_pParentMenu->m_Style&WISP_WMS_POPUP)==0)
	{
		pMenuItem = &(*m_pParentMenu->m_HoverIter);
		m_WindowDC.DrawHLine(pMenuItem->ItemRC.cx-1,m_WindowRect.cx-1,0,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
		m_WindowDC.DrawHLine(1,pMenuItem->ItemRC.cx-2,0,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BG]);
		m_WindowDC.DrawHLine(0,m_WindowRect.cx-1,m_WindowRect.cy-1,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
		m_WindowDC.DrawVLine(0,0,m_WindowRect.cy-1,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
		m_WindowDC.DrawVLine(m_WindowRect.cx-1,0,m_WindowRect.cy-1,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
	}
	else
		m_WindowDC.DrawRect(&m_WindowRect,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_MENU_BORDER]);
	return false;
}

void CWispMenu::MenuNextSelect()
{
	CMenuItemList::IT Iter = m_HoverIter;
	if(Iter==m_ItemList.End())
		Iter = m_ItemList.Begin();
	else
	{
		Iter++;
		if(Iter==m_ItemList.End())
			Iter = m_ItemList.Begin();
	}
	while(Iter!=m_ItemList.End() && (Iter->Style&WISP_MIS_SEPARATOR))
		Iter++;
	m_HoverIter=Iter;
	Update();
}

bool CWispMenu::SetHoverItem(HANDLE hItem)
{
	CMenuItemList::IT Iter = *(WISP_MENU_ITEM*)hItem;
	if(m_HoverIter != Iter)
		HoverItemChanged(Iter);
	return true;
}


void CWispMenu::MenuPrevSelect()
{
	CMenuItemList::IT Iter = m_HoverIter;
	if(Iter==m_ItemList.End())
		Iter = m_ItemList.Last();
	else
	{
		Iter--;
		if(Iter==m_ItemList.End())
			Iter = m_ItemList.Last();
	}
	while(Iter!=m_ItemList.End() && (Iter->Style&WISP_MIS_SEPARATOR))
		Iter--;
	m_HoverIter=Iter;
	Update();
}

void CWispMenu::ClickItem(WISP_MENU_ITEM*pMenuItem)
{
	WISP_MSG Msg;
	if(ClickItemNotify(pMenuItem,pMenuItem->CmdID)==false)
		return;
	if((pMenuItem->Style&WISP_MIS_CHECKBOX))
		ToggleCheckItem((HANDLE)pMenuItem);
	Msg.hWnd=m_OwnerWnd;
	Msg.Msg=WISP_WM_COMMAND;
	Msg.Command.CmdMsg	= WISP_CMD_CTRL_CLICK;
	Msg.Command.CmdID	= pMenuItem->CmdID;
	Msg.Command.CtrlType= WISP_CTRL_MENU;
	Msg.Command.Param1	= 0;
	Msg.Command.Param2	= pMenuItem;
	if(SEND_MSG(&Msg))
	{
		Msg.hWnd=m_OwnerWnd;
		Msg.Msg=WISP_WM_EVENT;
		POST_MSG(&Msg);
		if(m_OwnerWnd==this)
			GetTopMenu()->HideMenuTree();
		else
			m_OwnerWnd->Focus();
	}
}

bool CWispMenu::OnKeyEvent(WISP_MSG*pMsg)
{
	WISP_MENU_ITEM*pMenuItem;
	if(m_ItemList.Count()==0)
		return true;
	if(pMsg->KeyEvent.bKeyDown)
	{
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_VK_LBUTTON:
			{
				if(PtInRect(&m_WindowRect,pMsg->MsgMouseCltPT)==false)
				{
					m_bExpandMenu = false;
					HideMenuTree();
					break;
				}
				if(m_bExpandMenu && m_HoverIter==m_ItemList.End())
				{
					m_bExpandMenu = false;
					HideMenuTree();
				}
				if(m_HoverIter!=m_ItemList.End())
				{
					pMenuItem = &(*m_HoverIter);
					if(	(pMenuItem->Style&WISP_MIS_DISABLED)==0 && 
						(pMenuItem->Style&WISP_MIS_SEPARATOR)==0)
					{
						if(pMenuItem->Style&WISP_MIS_POPUP)
						{
							if(m_bExpandMenu==false)
							{
								m_bExpandMenu = true;
								PopupItemMenu(pMenuItem,false);
								Update(&pMenuItem->ItemRC);
							}
							else
							{
								m_bExpandMenu = false;
								CMenuItemList::IT OldIter = m_HoverIter;
								HideMenuTree();
								m_HoverIter = OldIter;
								Update();
							}
						}
						else
						{
							ClickItem(pMenuItem);
						}
					}
				}
			}//End WISP_VK_LBUTTON
			break;
		case WISP_VK_UP:
			if(IsPopupMenu())
			{
				MenuPrevSelect();
			}
			else
			{
				if(m_pParentMenu)
				{
					HideMenuTree();
					m_pParentMenu->Focus();
				}
			}
			break;
		case WISP_VK_DOWN:
			if(IsPopupMenu())
			{
				MenuNextSelect();
			}
			else
			{
				if(m_HoverIter!=m_ItemList.End() && (m_HoverIter->Style&WISP_MIS_POPUP))
				{
					PopupItemMenu(&(*m_HoverIter));
				}
			}
			break;
		case WISP_VK_LEFT:
			if(IsPopupMenu())
			{
				if(m_pParentMenu)
				{
					HideMenuTree();
					m_pParentMenu->Focus();
				}
			}
			else
			{
				MenuPrevSelect();				
			}
			break;
		case WISP_VK_RIGHT:
			if(IsPopupMenu())
			{
				if(m_HoverIter!=m_ItemList.End() && (m_HoverIter->Style&WISP_MIS_POPUP))
				{
					PopupItemMenu(&(*m_HoverIter));
				}
			}
			else
			{
				MenuNextSelect();
			}
			break;
		case WISP_VK_RETURN:
			if(m_HoverIter!=m_ItemList.End())
			{
				if(m_HoverIter->Style&WISP_MIS_POPUP)
					PopupItemMenu(&(*m_HoverIter));
				else
				{
					ClickItem(&(*m_HoverIter));
				}
			}
			break;
		case WISP_VK_ESCAPE:
			if(m_pParentMenu)
			{
				HideMenuTree();
				m_pParentMenu->Focus();
			}
			else
			{
				if(m_OwnerWnd!=this)
					m_OwnerWnd->Focus();
				else
					HideMenuTree();
			}
			break;
		}
	}
	return true;
}

void CWispMenu::HoverItemChanged(const CMenuItemList::IT&Iter)
{
	WISP_MENU_ITEM*pMenuItem;
	if(m_HoverIter!=m_ItemList.End())
	{
		pMenuItem = &(*m_HoverIter);
		if(pMenuItem->Style&WISP_MIS_POPUP)
			((CWispMenu*)pMenuItem->Data)->HideMenuTree();
	}
	m_HoverIter = Iter;
	pMenuItem = &(*m_HoverIter);
	if(m_HoverIter!= m_ItemList.End() && ((m_Style&WISP_WMS_POPUP) || m_bExpandMenu))
	{
		if(pMenuItem->Style&WISP_MIS_POPUP)
			PopupItemMenu(pMenuItem,false);
	}
	Update();
}

bool CWispMenu::IsChildMenu(CWispBaseWnd*pMenu)
{
	if(pMenu->m_CtrlType != WISP_CTRL_MENU)
		return false;
	CWispMenu*pParentMenu = ((CWispMenu*)pMenu)->m_pParentMenu;
	while(pParentMenu)
	{
		if(pParentMenu==this)
			return true;
		pParentMenu = pParentMenu->m_pParentMenu;
	}
	return false;
}

CWispMenu* CWispMenu::GetTopMenu()
{
	CWispMenu*pParentMenu = this;
	while(pParentMenu)
	{
		if(pParentMenu->m_pParentMenu==NULL)
			return pParentMenu;
		pParentMenu = pParentMenu->m_pParentMenu;
	}
	return NULL;
}

bool CWispMenu::OnMouseMove(WISP_MSG*pMsg)
{
	CMenuItemList::IT Iter;
	for(Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(PtInRect(&Iter->ItemRC,&pMsg->MsgMouseCltPT))
		{
			if(m_HoverIter != Iter)
				HoverItemChanged(Iter);
			break;
		}
	}
	if(Iter == m_ItemList.End() && (m_Style&WISP_WMS_POPUP)==0)
	{
		if(m_HoverIter != Iter)
			HoverItemChanged(Iter);
	}
	return true;
}

bool CWispMenu::OnMouseLeave(WISP_MSG*pMsg)
{
	if((m_Style&WISP_WMS_POPUP)==0 && m_HoverIter!=m_ItemList.End() && m_bExpandMenu == false)
	{
		HoverItemChanged(m_ItemList.End());
	}
	return true;
}

bool CWispMenu::OnLostFocus(WISP_MSG*pMsg)
{
	CWispMenu*pTopMenu;
	pTopMenu = GetTopMenu();
	if(pTopMenu->IsChildMenu(pMsg->hOtherWnd)==false)
	{
		if(pTopMenu != pMsg->hOtherWnd)
			pTopMenu->HideMenuTree();
		m_HoverIter = m_ItemList.End();
	}
	return true;
}

bool CWispMenu::CreateWndMenu(CWispWnd*pParentWnd,UINT CmdID,WISP_MENU_RES_ITEM*pResItem,CWispDIBList*pDIBList)
{
	CWispDIB*pIcon;
	CWispMenu*pMenu;
	if(Create(NULL,0,0,pParentWnd->m_ClientRect.cx,m_WndMenuHeight,pParentWnd,CmdID,WISP_WS_NULL)==false)
		return false;
	if(pResItem==NULL)
		return true;
	while(pResItem->szText || pResItem->CmdID || pResItem->Style)
	{
		if((pResItem->Style&WISP_MIS_POPUP) && pResItem->pMenuItem)
		{
			pMenu = new CWispMenu;
			pMenu->CreatePopupMenu((WISP_MENU_RES_ITEM*)pResItem->pMenuItem,m_OwnerWnd,pDIBList);
			pMenu->m_pParentMenu = this;
			pMenu->m_OwnerWnd = m_OwnerWnd;
			pMenu->AddAdvStyle(WISP_WAS_AUTO_DELETE);
		}
		else
			pMenu = NULL;
		if(pDIBList && pResItem->DIBIndex>=0)
			pIcon = pDIBList->GetDIB(pResItem->DIBIndex);
		else
			pIcon = NULL;
		InsertItem(-1,pResItem->szText,pResItem->Style,pResItem->CmdID,pIcon,(NUM_PTR)pMenu);
		pResItem++;
	}
	RecalcLayout();
	return true;
}

bool CWispMenu::CreatePopupMenu(WISP_MENU_RES_ITEM*pResItem,CWispBaseWnd*pOwnerWnd,CWispDIBList*pDIBList)
{
	CWispDIB*pIcon;
	CWispMenu*pMenu;
	int Width,Height,ItemWidth;
	if(Create(NULL,0,0,0,0,NULL,0,WISP_WS_THIN_BORDER|WISP_WMS_POPUP,WISP_SH_HIDDEN)==false)
		return false;
	if(pResItem==NULL)
		return true;
	CWispBaseWnd::SetOwner(pOwnerWnd);
	Height = Width = 0;
	while(pResItem->szText || pResItem->CmdID || pResItem->Style)
	{
		if((pResItem->Style&WISP_MIS_POPUP) && pResItem->pMenuItem)
		{
			pMenu = new CWispMenu;
			pMenu->CreatePopupMenu((WISP_MENU_RES_ITEM*)pResItem->pMenuItem,pOwnerWnd,pDIBList);
			pMenu->m_pParentMenu = this;
			pMenu->CWispBaseWnd::SetOwner(pOwnerWnd);
			pMenu->AddAdvStyle(WISP_WAS_AUTO_DELETE);
		}
		else
			pMenu=NULL;
		if(pDIBList && pResItem->DIBIndex>=0)
			pIcon = pDIBList->GetDIB(pResItem->DIBIndex);
		else
			pIcon = NULL;
		InsertItem(-1,pResItem->szText,pResItem->Style,pResItem->CmdID,pIcon,(NUM_PTR)pMenu);
		ItemWidth = m_ClientDC.GetTextExtent(pResItem->szText);
		if(ItemWidth > Width)
			Width = ItemWidth;
		if(pResItem->Style&WISP_MIS_SEPARATOR)
			Height+=1;
		else
			Height+=m_PopupItemHeight;
		pResItem++;
	}
	Width += m_MenuStartSpace+m_MenuEndSpace+m_BorderSize*2+m_MenuMarge*2;
	Height += m_BorderSize*2+m_MenuMarge*2;
	Resize(Width,Height);
	return true;
}

void CWispMenu::AdjustPopupMenuSize()
{
	int Width,Height,ItemWidth;
	Width = 0;
	Height = 0;
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		ItemWidth = m_ClientDC.GetTextExtent(Iter->szText);
		if(ItemWidth > Width)
			Width = ItemWidth;
		if(Iter->Style&WISP_MIS_SEPARATOR)
			Height+=1;
		else
			Height+=m_PopupItemHeight;		
	}
	Width += m_MenuStartSpace+m_MenuEndSpace+m_BorderSize*2+m_MenuMarge*2;
	Height += m_BorderSize*2+m_MenuMarge*2;
	Resize(Width,Height);
	RecalcLayout();
}


void CWispMenu::SetOwner(CWispBaseWnd*pOwnerWnd)
{
	CWispWnd::SetOwner(pOwnerWnd);
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(Iter->Style&WISP_MIS_POPUP)
			Iter->pSubMenu->SetOwner(pOwnerWnd);
	}
}

HANDLE CWispMenu::InsertItem(int Pos,WISP_PCSTR szText,UINT Style,UINT CmdID,CWispDIB*pIcon,NUM_PTR MenuData)
{
	CMenuItemList::IT Iter;
	if(Pos<0)
	{
		Iter = m_ItemList.Append();
	}
	else
	{
		if(Pos>=m_ItemList.Count())
			return NULL;
		Iter = m_ItemList[Pos];
		Iter = m_ItemList.InsertBefore(Iter);
	}
	Iter->szText = szText;
	Iter->pIcon = pIcon;
	Iter->Style = Style;
	Iter->CmdID = CmdID;
	Iter->TextClr = 0;
	Iter->Data = MenuData;
	Iter->ItemRC.x = Iter->ItemRC.y = Iter->ItemRC.cx = Iter->ItemRC.cy;
	return Iter.pNode;
}

bool CWispMenu::InsertSubMenu(int Pos,WISP_PCSTR szText,CWispMenu*pMenu,CWispDIB*pIcon)
{
	CMenuItemList::IT Iter;
	if(Pos<0)
	{
		Iter = m_ItemList.Append();
	}
	else
	{
		if(Pos>=m_ItemList.Count())
			return NULL;
		Iter = m_ItemList[Pos];
		Iter = m_ItemList.InsertBefore(Iter);
	}
	Iter->szText = szText;
	Iter->pIcon = pIcon;
	Iter->Style = WISP_MIS_POPUP;
	Iter->CmdID = 0;
	Iter->TextClr = 0;
	Iter->pSubMenu = pMenu;
	Iter->ItemRC.x = Iter->ItemRC.y = Iter->ItemRC.cx = Iter->ItemRC.cy;
	return true;
}

bool CWispMenu::SetItemColor(UINT CmdID,COLORREF TextColor)
{
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(Iter->CmdID && Iter->CmdID==CmdID)
		{
			Iter->TextClr = TextColor;
			return true;
		}
	}
	return false;
}

bool CWispMenu::RemoveItemByPos(int Pos)
{
	CMenuItemList::IT Iter;
	if(Pos<0 || Pos>=m_ItemList.Count())
		return false;
	Iter = m_ItemList[Pos];
	m_ItemList.Remove(Iter);
	return true;
}

bool CWispMenu::RemoveItem(UINT CmdID)
{
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(Iter->Style!=WISP_MIS_POPUP && Iter->CmdID==CmdID)
		{
			m_ItemList.Remove(Iter);
			return true;
		}
	}
	return false;
}

bool CWispMenu::RemoveItem(HANDLE hItem)
{
	CMenuItemList::IT Iter = (CMenuItemList::NODE*)hItem;
	m_ItemList.Remove(Iter);
	return true;
}

int CWispMenu::RemoveAllItem()
{
	int Count = m_ItemList.Count();
	m_ItemList.Clear();
	return Count;
}

HANDLE CWispMenu::GetItemByName(WISP_PCSTR Name)
{
	HANDLE hItem;
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(Iter->szText && TStrCmp(Name,(WISP_PCSTR)Iter->szText)==0)
		{
			return (HANDLE)&(*Iter);;
		}
		else if(Iter->Style&WISP_MIS_POPUP)
		{
			hItem = Iter->pSubMenu->GetItemByName(Name);
			if(hItem)
				return hItem;
		}
	}
	return NULL;
}

HANDLE CWispMenu::GetItemByPos(int Pos)
{
	if(Pos<0 || Pos>=m_ItemList.Count())
		return NULL;
	return (HANDLE)&(*m_ItemList[Pos]);
}

HANDLE CWispMenu::GetItem(UINT CmdID)
{
	HANDLE hItem;
	for(CMenuItemList::IT Iter=m_ItemList.Begin();Iter!=m_ItemList.End();Iter++)
	{
		if(Iter->Style&WISP_MIS_POPUP)
		{
			hItem = Iter->pSubMenu->GetItem(CmdID);
			if(hItem)
				return hItem;
		}
		else if(Iter->CmdID==CmdID)
			return (HANDLE)&(*Iter);
	}
	return NULL;
}

HANDLE CWispMenu::GetNextItem(HANDLE hItem,UINT Style)
{
	CMenuItemList::IT Iter;
	if(hItem)
	{
		Iter = *(WISP_MENU_ITEM*)hItem;
		Iter++;
	}
	else
	{
		Iter = m_ItemList.Begin();
	}
	while(Iter!=m_ItemList.End())
	{
		if((Iter->Style & Style)==Style)
			return &(*Iter);
		Iter++;
	}
	return NULL;
}

HANDLE CWispMenu::GetPrevItem(HANDLE hItem,UINT Style)
{
	CMenuItemList::IT Iter;
	if(hItem)
	{
		Iter = *(WISP_MENU_ITEM*)hItem;
		Iter--;
	}
	else
	{
		Iter = m_ItemList.Last();
	}
	while(Iter!=m_ItemList.End())
	{
		if((Iter->Style & Style)==Style)
			return &(*Iter);
		Iter--;
	}
	return &(*Iter);
}

CWispString& CWispMenu::GetItemText(HANDLE hItem)
{
	return ((WISP_MENU_ITEM*)hItem)->szText;
}

CWispDIB* CWispMenu::GetItemIcon(HANDLE hItem)
{
	return ((WISP_MENU_ITEM*)hItem)->pIcon;
}

UINT CWispMenu::GetItemStyle(HANDLE hItem)
{
	return ((WISP_MENU_ITEM*)hItem)->Style;
}

NUM_PTR CWispMenu::GetItemData(HANDLE hItem)
{
	return ((WISP_MENU_ITEM*)hItem)->Data;
}

bool CWispMenu::SetItemInfo(HANDLE hItem,UINT Style,WISP_PCSTR szText,CWispDIB*pIcon,NUM_PTR Data)
{
	WISP_MENU_ITEM*pItem = (WISP_MENU_ITEM*)hItem;
	pItem->Style = Style;
	pItem->szText = szText;
	pItem->pIcon = pIcon;
	pItem->Data = Data;
	int Width = m_ClientDC.GetTextExtent(szText)+m_MenuStartSpace+m_MenuEndSpace+m_BorderSize*2+m_MenuMarge*2;
	if(Width>m_WindowRect.cx)
		Resize(Width,m_WindowRect.cy);
	return true;
}

bool CWispMenu::SetItemText(HANDLE hItem,WISP_PCSTR szText)
{
	int Width = m_ClientDC.GetTextExtent(szText)+m_MenuStartSpace+m_MenuEndSpace+m_BorderSize*2+m_MenuMarge*2;
	if(Width>m_WindowRect.cx)
		Resize(Width,m_WindowRect.cy);
	((WISP_MENU_ITEM*)hItem)->szText = szText;
	return true;
}

bool CWispMenu::SetItemIcon(HANDLE hItem,CWispDIB*pIcon)
{
	((WISP_MENU_ITEM*)hItem)->pIcon = pIcon;
	return true;
}

bool CWispMenu::SetItemStyle(HANDLE hItem,UINT Style)
{
	((WISP_MENU_ITEM*)hItem)->Style = Style;
	return true;
}

bool CWispMenu::SetItemData(HANDLE hItem,NUM_PTR Data)
{
	((WISP_MENU_ITEM*)hItem)->Data = Data;
	return true;
}

bool CWispMenu::ToggleCheckItem(HANDLE hItem)
{
	if(IsItemChecked(hItem))
	{
		UncheckItem(hItem);
		return true;
	}
	else
	{
		CheckItem(hItem);
		return false;
	}
}

bool CWispMenu::CheckItem(HANDLE hItem)
{	
	WISP_MENU_ITEM*pItem=(WISP_MENU_ITEM*)hItem;
	if(pItem->Style&WISP_MIS_CHECKED)
		return true;
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_CHECKING;
	Msg.Command.Param1 = false;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	pItem->Style|=WISP_MIS_CHECKED;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_CHECKED;
	Msg.Command.Param1 = true;
	SEND_MSG(&Msg);
	Update();
	return true;
}

bool CWispMenu::UncheckItem(HANDLE hItem)
{
	WISP_MENU_ITEM*pItem=(WISP_MENU_ITEM*)hItem;
	if((pItem->Style&WISP_MIS_CHECKED)==0)
		return true;
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_UNCHECKING;
	Msg.Command.Param1 = true;
	Msg.Command.Param2 = hItem;
	if(SEND_MSG(&Msg)==false)
		return false;
	pItem->Style&=~WISP_MIS_CHECKED;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_UNCHECKED;
	Msg.Command.Param1 = false;
	SEND_MSG(&Msg);
	Update();
	return true;
}

bool CWispMenu::IsItemChecked(HANDLE hItem)
{
	return (((WISP_MENU_ITEM*)hItem)->Style & WISP_MIS_CHECKED)!=0;
}

bool CWispMenu::ToggleDisableItem(HANDLE hItem)
{
	if(IsItemDisabled(hItem))
	{
		EnableItem(hItem);
		return false;
	}
	else
	{
		DisableItem(hItem);
		return true;
	}
}

bool CWispMenu::EnableItem(HANDLE hItem)
{
	WISP_MENU_ITEM*pItem=(WISP_MENU_ITEM*)hItem;
	if((pItem->Style&WISP_MIS_DISABLED)==0)
		return true;
	pItem->Style&=~WISP_MIS_DISABLED;
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_ENABLED;
	Msg.Command.Param1 = false;
	Msg.Command.Param2 = hItem;
	SEND_MSG(&Msg);
	Update();
	return true;
}

bool CWispMenu::DisableItem(HANDLE hItem)
{
	WISP_MENU_ITEM*pItem=(WISP_MENU_ITEM*)hItem;
	if(pItem->Style&WISP_MIS_DISABLED)
		return true;
	pItem->Style|=WISP_MIS_DISABLED;
	WISP_MSG Msg;
	Msg.hWnd = m_OwnerWnd;
	Msg.Msg = WISP_WM_COMMAND;
	Msg.Command.CmdID = m_CmdID;
	Msg.Command.CmdMsg = WISP_CMD_ITEM_DISABLED;
	Msg.Command.Param1 = true;
	Msg.Command.Param2 = hItem;
	SEND_MSG(&Msg);
	Update();
	return true;
}

bool CWispMenu::IsItemDisabled(HANDLE hItem)
{
	return (((WISP_MENU_ITEM*)hItem)->Style & WISP_MIS_DISABLED)!=0;
}

bool CWispMenu::IsItemChecked(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;	
	return IsItemChecked(hItem);
}

bool CWispMenu::ToggleCheckItem(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;
	ToggleCheckItem(hItem);
	return true;
}

bool CWispMenu::CheckItem(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;
	CheckItem(hItem);
	return true;
}

bool CWispMenu::UncheckItem(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;
	UncheckItem(hItem);
	return true;
}

bool CWispMenu::IsItemDisabled(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;
	return IsItemDisabled(hItem);
}

bool CWispMenu::ToggleDisableItem(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;
	ToggleDisableItem(hItem);
	return true;
}

bool CWispMenu::EnableItem(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;
	EnableItem(hItem);
	return true;
}

bool CWispMenu::DisableItem(UINT CmdID)
{
	HANDLE hItem = GetItem(CmdID);
	if(hItem==NULL)
		return false;
	DisableItem(hItem);
	return true;
}

bool CWispMenu::Popup(WISP_POINT*pPT,bool bSelectItem)
{
	if(pPT==NULL)
		pPT = &m_pWispBase->m_MousePT;
	int X,Y;
	X = pPT->x;
	Y = pPT->y;
	if(X>m_ParentWnd->m_WindowRect.cx - m_WindowRect.cx)
		X = pPT->x - m_WindowRect.cx;
	if(Y>m_ParentWnd->m_WindowRect.cy - m_WindowRect.cy)
		Y = pPT->y - m_WindowRect.cy;
	if(bSelectItem)
		m_HoverIter = m_ItemList.Begin();
	MoveToScreen(X,Y);
	Show();
	Focus();
	Top();
	return true;
}

void CWispMenu::PopupItemMenu(WISP_MENU_ITEM*pMenuItem,bool bSelectItem)
{
	int Width;
	WISP_POINT pt;
	CWispMenu*pMenu = (CWispMenu*)pMenuItem->Data;
	pMenu->m_HoverIter = pMenu->m_ItemList.End();
	if(m_Style&WISP_WMS_POPUP)
	{
		pt.x = pMenuItem->ItemRC.x + pMenuItem->ItemRC.cx+ m_ScrClientRect.x;
		pt.y = pMenuItem->ItemRC.y + m_ScrClientRect.y;
	}
	else
	{
		pt.x = pMenuItem->ItemRC.x + m_ScrClientRect.x;
		pt.y = pMenuItem->ItemRC.y + pMenuItem->ItemRC.cy + m_ScrClientRect.y;
		Width = m_ClientDC.GetTextExtent(pMenuItem->szText)+m_MenuMarge*2;
		if(pMenuItem->pIcon)
			Width+=pMenuItem->pIcon->Width();
		if(Width>pMenu->m_WindowRect.cx)
			pMenu->Resize(Width,pMenu->m_WindowRect.cy);
	}
	if(pt.x>m_ParentWnd->m_WindowRect.cx - pMenu->m_WindowRect.cx)
		pt.x -= m_WindowRect.cx+pMenu->m_ClientRect.cx;
	if(pt.y>m_ParentWnd->m_WindowRect.cy - pMenu->m_WindowRect.cy)
	{
		pt.y -= pMenu->m_WindowRect.cy-pMenuItem->ItemRC.cy;
	}
	if(bSelectItem)
		pMenu->m_HoverIter = pMenu->m_ItemList.Begin();
	pMenu->MoveToScreen(pt.x,pt.y);
	pMenu->Show();
	pMenu->Focus();
}

void CWispMenu::HideMenuTree()
{
	WISP_MENU_ITEM*pMenuItem;
	CWispMenu*pMenu=this;
	if(m_Style&WISP_WMS_POPUP)
	{
		Show(WISP_SH_HIDDEN);
		while(pMenu)
		{
			if(pMenu->m_HoverIter == pMenu->m_ItemList.End())
				break;
			pMenuItem = &(*pMenu->m_HoverIter);
			if((pMenuItem->Style&WISP_MIS_POPUP) == 0)
				break;
			pMenu->m_HoverIter=pMenu->m_ItemList.End();
			pMenu = (CWispMenu*)pMenuItem->Data;
			pMenu->Show(WISP_SH_HIDDEN);
			m_pWispBase->m_pRootWnd->Update(&pMenu->m_ScrWindowRect);
		}
		Update();
	}
	else
	{
		m_bExpandMenu = false;
		if(m_HoverIter != m_ItemList.End())
		{
			pMenuItem = &(*m_HoverIter);
			m_HoverIter = m_ItemList.End();
			if(pMenuItem->Style&WISP_MIS_POPUP)
				((CWispMenu*)pMenuItem->Data)->HideMenuTree();
		}
	}
}

