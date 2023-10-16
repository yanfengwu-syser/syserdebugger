#include "StdAfx.h"
#include "M3DView.h"

WISP_WIN win;
WISP_VIEW view;
VS_3D v0,v1,v2,v3,v4;
OBJ obj;
OBJ obj1;
double rl=0;

WISP_MSG_MAP_BEGIN(CM3DView)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
WISP_MSG_MAP_END(CWispWnd)

CM3DView::CM3DView(void)
{
}

CM3DView::~CM3DView(void)
{
}

bool CM3DView::OnCreate(IN WISP_MSG*pMsg)
{

	win.min_x=-m_ClientRect.cx/2;
	win.min_y=-m_ClientRect.cy/2;
	win.max_x= m_ClientRect.cx/2-1;
	win.max_y= m_ClientRect.cy/2-1;

	view.dp=200;
	view.ox=150;
	view.oy=0;
	view.oz=100;

	view.u1=1;
	view.u2=0;
	view.u3=0,

	view.v1=0;
	view.v2=0;
	view.v3=-1;

	view.w1=0;
	view.w2=1;
	view.w3=0;

	v0.x=0;  v0.y=0;  v0.z=0;
	v1.x=100;v1.y=0;  v1.z=0;
	v2.x=100;v2.y=100;v2.z=0;
	v3.x=0;  v3.y=100;v3.z=0;
	v4.x=50; v4.y=50; v4.z=100;


	obj.ep=new ES_3D[10];
	obj.en=5;


	obj1.ep=new ES_3D[10];
	obj1.en=5;


	obj.ep[0].vp[0]=v0; obj.ep[0].vp[1]=v1; obj.ep[0].vp[2]=v4; 
	obj.ep[0].vn=3;

	obj.ep[1].vp[0]=v1; obj.ep[1].vp[1]=v2; obj.ep[1].vp[2]=v4; 
	obj.ep[1].vn=3;

	obj.ep[2].vp[0]=v2; obj.ep[2].vp[1]=v3; obj.ep[2].vp[2]=v4; 
	obj.ep[2].vn=3;

	obj.ep[3].vp[0]=v3; obj.ep[3].vp[1]=v0; obj.ep[3].vp[2]=v4; 
	obj.ep[3].vn=3;

	obj.ep[4].vp[0]=v0; obj.ep[4].vp[1]=v1; obj.ep[4].vp[2]=v2;obj.ep[4].vp[3]=v3; 
	obj.ep[4].vn=4;

	v0.x+=300;
	v1.x+=300;
	v2.x+=300;
	v3.x+=300;
	v4.x+=300;

	obj1.ep[0].vp[0]=v0; obj1.ep[0].vp[1]=v1; obj1.ep[0].vp[2]=v4; 
	obj1.ep[0].vn=3;

	obj1.ep[1].vp[0]=v1; obj1.ep[1].vp[1]=v2; obj1.ep[1].vp[2]=v4; 
	obj1.ep[1].vn=3;

	obj1.ep[2].vp[0]=v2; obj1.ep[2].vp[1]=v3; obj1.ep[2].vp[2]=v4; 
	obj1.ep[2].vn=3;

	obj1.ep[3].vp[0]=v3; obj1.ep[3].vp[1]=v0; obj1.ep[3].vp[2]=v4; 
	obj1.ep[3].vn=3;

	obj1.ep[4].vp[0]=v0; obj1.ep[4].vp[1]=v1; obj1.ep[4].vp[2]=v2;obj1.ep[4].vp[3]=v3; 
	obj1.ep[4].vn=4;

	rl=0;
	return true;
}

bool CM3DView::OnDestroy(IN WISP_MSG*pMsg)
{
	delete obj.ep;
	delete obj1.ep;
	return true;
}

bool CM3DView::OnUpdateClient(IN WISP_MSG*pMsg)
{
	WISP_RECT rc;
	rc = m_ClientRect;
	rc.x = rc.y = 0;
	rc.cy/=2;
	m_ClientDC.DrawFullRect(&rc,RGB(180,180,255));
	rc.y+=rc.cy;
	rc.cy = m_ClientRect.cy - rc.cy;
	m_ClientDC.DrawFullRect(&rc,RGB(50,50,50));
	draw_obj(&win,&view,&obj,4,&m_ClientDC);
	draw_obj(&win,&view,&obj1,8,&m_ClientDC);
	return false;
}

bool CM3DView::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.bKeyDown==false)
		return true;
	
	rl=0;
	switch(pMsg->KeyEvent.KeyType)
	{
	case WISP_VK_LEFT:
		rl= 0.03;
		break;
	case WISP_VK_RIGHT:
		rl=-0.03;
		break;
	case WISP_VK_UP:
		view.oy+=10;
		break;
	case WISP_VK_DOWN:
		view.oy-=10;
		break;
	case WISP_VK_W:
		view.oz++;
		break;
	case WISP_VK_S:
		view.oz--;
		break;
	case WISP_VK_A:
		view.dp++;
		break;
	case WISP_VK_D:
		view.dp--;
		break;
	default:
		return true;
	}
	change_view(&view,(float)rl,0);
	Update();
	return true;
}

bool CM3DView::OnMouseMove(IN WISP_MSG*pMsg)
{
	return true;
}
