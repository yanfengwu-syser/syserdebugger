#include "StdAfx.h"
#include "RippleWnd.h"


WISP_MSG_MAP_BEGIN(CRippleWnd)
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
WISP_MSG_MAP(WISP_WM_TIMER,OnTimer)
WISP_MSG_MAP_END(CWispWnd)

CRippleWnd::CRippleWnd(void)
{
}

CRippleWnd::~CRippleWnd(void)
{

}

bool CRippleWnd::OnCreate(IN WISP_MSG*pMsg)
{
	CWispDIB DIB;
	DIB.Load("\\Toolbar.bmp");
	DIB.SetType(WISP_DIB_BITMAP);
	m_OrgDIB.Create(DIB.m_Rect.cx,DIB.m_Rect.cy);
	m_RippleDIB.Create(DIB.m_Rect.cx,DIB.m_Rect.cy);
	DIB.BltTiled(&m_OrgDIB);
	DIB.BltTiled(&m_RippleDIB);
	m_Ripple.InitRipple(DIB.m_Rect.cx,DIB.m_Rect.cy,32);
	DIB.Destroy();
	Resize(DIB.m_Rect.cx,DIB.m_Rect.cy);
	return true;
}

bool CRippleWnd::OnDestroy(IN WISP_MSG*pMsg)
{
	m_OrgDIB.Destroy();
	m_RippleDIB.Destroy();
	m_Ripple.CleanRippleData();
	return true;
}

bool CRippleWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	m_Ripple.RenderRipple(m_OrgDIB.m_FrameBuffer.Buffer,m_RippleDIB.m_FrameBuffer.Buffer);
	m_ClientDC.DrawDIBTiled(&m_RippleDIB);
	return false;
}

bool CRippleWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON && pMsg->KeyEvent.bKeyDown==false)
	{
		m_Ripple.DropStone(pMsg->MsgMouseWndPT.x-m_ClientRect.x,pMsg->MsgMouseWndPT.y-m_ClientRect.y,3,128);
		InsertTimer(0,20,0,0);
	}
	return true;
}

bool CRippleWnd::OnMouseMove(IN WISP_MSG*pMsg)
{
	if(pMsg->bMsgLBTDown)
	{
		m_Ripple.DropStone(pMsg->MsgMouseWndPT.x-m_ClientRect.x,pMsg->MsgMouseWndPT.y-m_ClientRect.y,3,80);
	}
	return true;
}

bool CRippleWnd::OnTimer(IN WISP_MSG*pMsg)
{
	if(m_Ripple.RippleSpread())
		Update();
	else
		RemoveTimer((UINT)0);
	return true;
}


