#include "StdAfx.h"
#include "WispRGBSelect.h"


enum CWispRGBSelect::WISP_FORM_ID
{
	CMD_ID_VERSION_EDIT = WISP_ID_USER_START,
	CMD_ID_RGB_SELECT_GROUP,
	CMD_ID_RGB_R,
	CMD_ID_RGB_G,
	CMD_ID_RGB_B,
};

WISP_FORM_RES_ITEM CWispRGBSelect::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,350,210},
		WISP_ID_NULL,
		WISP_WFS_DIALOG,
		WSTR("RGB")
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{5,5,250,170},
		CMD_ID_RGB_SELECT_GROUP,
		WISP_WS_NULL,
		WSTR("RGB"),
	},
	{
		WISP_CTRL_BUTTON,
		{270,130,60,18},
		WISP_ID_CANCEL,
		WISP_BS_NORMAL,
		WSTR("Cancel"),
	},
	{
		WISP_CTRL_BUTTON,
		{270,155,60,18},
		WISP_ID_OK,
		WISP_BS_NORMAL,
		WSTR("OK"),
	},
	{
		WISP_CTRL_STATIC_STRING,
		{270,56,30,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Red")
	},
	{
		WISP_CTRL_EDIT,
		{305,55,25,16},
		CMD_ID_RGB_R,
		WISP_ES_EDIT_NORMAL,
		NULL
	},
	{
		WISP_CTRL_STATIC_STRING,
		{270,76,30,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Green")
	},
	{
		WISP_CTRL_EDIT,
		{305,75,25,16},
		CMD_ID_RGB_G,
		WISP_ES_EDIT_NORMAL,
		NULL
	},
	{
		WISP_CTRL_STATIC_STRING,
		{270,96,30,16},
		WISP_ID_NULL,
		WISP_WS_NULL,
		WSTR("Blue")
	},
	{
		WISP_CTRL_EDIT,
		{305,95,25,16},
		CMD_ID_RGB_B,
		WISP_ES_EDIT_NORMAL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CWispRGBSelect)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispForm)


WISP_MSG_CMD_MAP_BEGIN(CWispRGBSelect)
WISP_MSG_CMD_MAP_DEFAULT_END(OnCmdGetCmd)

bool CWispRGBSelect::OnCmdGetCmd(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg==WISP_CMD_EN_INPUT_KEY_UP)
	{
		UpdateColorValue();
	}
	return true;
}


CWispRGBSelect::CWispRGBSelect()
{
	m_pFormRes = m_FormRes;
	m_RGBClr = 0;
}

bool CWispRGBSelect::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pRGBGroupCtrl = GetFormItem(CMD_ID_RGB_SELECT_GROUP);
	m_pRedEdit = (CWispEdit*)GetFormItem(CMD_ID_RGB_R);
	m_pGreenEdit = (CWispEdit*)GetFormItem(CMD_ID_RGB_G);
	m_pBlueEdit = (CWispEdit*)GetFormItem(CMD_ID_RGB_B);

	m_RGBDIB.Create(m_pRGBGroupCtrl->m_WindowRect.cx - 55,m_pRGBGroupCtrl->m_WindowRect.cy - 25,WISP_DIB_BITMAP);
	m_LumDIB.Create(20,m_RGBDIB.m_Rect.cy,WISP_DIB_BITMAP);
	FillRGBRect(&m_RGBDIB);

	m_RGBRect.x = m_pRGBGroupCtrl->m_WindowRect.x + 15;
	m_RGBRect.y = m_pRGBGroupCtrl->m_WindowRect.y + 20;
	m_RGBRect.cx = m_RGBDIB.m_Rect.cx;
	m_RGBRect.cy = m_RGBDIB.m_Rect.cy;

	m_RGBFrameRect.x = m_RGBRect.x - 1;
	m_RGBFrameRect.y = m_RGBRect.y - 1;
	m_RGBFrameRect.cx = m_RGBRect.cx + 2;
	m_RGBFrameRect.cy = m_RGBRect.cy + 2;

	m_LumRect.x = m_RGBRect.x + m_RGBRect.cx + 10;
	m_LumRect.y = m_RGBRect.y;
	m_LumRect.cx = m_LumDIB.m_Rect.cx;
	m_LumRect.cy = m_LumDIB.m_Rect.cy;

	m_LumDragRect = m_LumRect;
	m_LumDragRect.cx += 5;
	m_LumDragRect.cy += 10;
	m_LumDragRect.y -= 5;

	m_LumFrameRect.x = m_LumRect.x - 1;
	m_LumFrameRect.y = m_LumRect.y - 1;
	m_LumFrameRect.cx = m_LumRect.cx + 2;
	m_LumFrameRect.cy = m_LumRect.cy + 2;

	m_CurRGBRect.x = 270;
	m_CurRGBRect.y = 10;
	m_CurRGBRect.cx = 60;
	m_CurRGBRect.cy = 40;

	m_PTSelected.x = m_RGBRect.x + m_RGBRect.cx/2;
	m_PTSelected.y = m_RGBRect.y + m_RGBRect.cy/2;

	m_LumYPos = m_LumRect.y + m_LumRect.cy/2;
	UpdateLumColor(false);
	ShowColorValue();
	return true;
}

bool CWispRGBSelect::OnDestroy(IN WISP_MSG*pMsg)
{
	m_RGBDIB.Destroy();
	m_LumDIB.Destroy();
	return true;
}

bool CWispRGBSelect::OnUpdateClient(IN WISP_MSG*pMsg)
{
	if(CWispForm::OnUpdateClient(pMsg)==false)
		return false;
	m_ClientDC.DrawDIB(&m_RGBRect,&m_RGBDIB);
	m_ClientDC.DrawFrameRect(&m_RGBFrameRect,false);
	m_ClientDC.DrawDIB(&m_LumRect,&m_LumDIB);
	m_ClientDC.DrawFrameRect(&m_LumFrameRect,false);

	m_ClientDC.DrawHLine(m_PTSelected.x-5,m_PTSelected.x-2,m_PTSelected.y,0);
	m_ClientDC.DrawHLine(m_PTSelected.x+2,m_PTSelected.x+5,m_PTSelected.y,0);
	m_ClientDC.DrawVLine(m_PTSelected.x,m_PTSelected.y-5,m_PTSelected.y-2,0);
	m_ClientDC.DrawVLine(m_PTSelected.x,m_PTSelected.y+2,m_PTSelected.y+5,0);

	m_ClientDC.DrawHLine(m_LumRect.x+m_LumRect.cx,m_LumRect.x+m_LumRect.cx+5,m_LumYPos,0);
	m_ClientDC.DrawLine(m_LumRect.x+m_LumRect.cx,m_LumYPos,m_LumRect.x+m_LumRect.cx+3,m_LumYPos-3,0);
	m_ClientDC.DrawLine(m_LumRect.x+m_LumRect.cx,m_LumYPos,m_LumRect.x+m_LumRect.cx+3,m_LumYPos+3,0);

	m_ClientDC.DrawFullRect(&m_CurRGBRect,m_RGBClr);
	m_ClientDC.DrawFrameRect(&m_CurRGBRect);
	return false;
}

bool CWispRGBSelect::OnMouseMove(IN WISP_MSG*pMsg)
{
	if(pMsg->bMsgLBTDown)
	{
		if(PtInRect(&m_RGBRect,pMsg->MsgMouseCltPT))
		{
			m_PTSelected = pMsg->MsgMouseCltPT;
			UpdateLumColor();
			UpdateClient();
		}
		else if(PtInRect(&m_LumDragRect,pMsg->MsgMouseCltPT))
		{
			m_LumYPos = pMsg->MsgMouseCltPT.y;
			MIN_LIMIT(m_LumYPos,m_LumRect.y);
			MAX_LIMIT(m_LumYPos,m_LumRect.y+m_LumRect.cy-1);
			UpdateColor();
			UpdateClient();
		}
	}
	return true;
}

bool CWispRGBSelect::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.bKeyDown && pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{
		if(PtInRect(&m_RGBRect,pMsg->MsgMouseCltPT))
		{
			m_PTSelected = pMsg->MsgMouseCltPT;
			UpdateLumColor();
			UpdateClient();
		}
		else if(PtInRect(&m_LumDragRect,pMsg->MsgMouseCltPT))
		{
			m_LumYPos = pMsg->MsgMouseCltPT.y;
			UpdateColor();
			UpdateClient();
		}
	}
	return true;
}

void CWispRGBSelect::FillRGBRect(CWispDIB*pRGBDIB)
{
	COLORREF color;
	WISP_POINT pt;
	CWispDC dc;
	dc.AttachDIB(pRGBDIB);
	int nStep = 1;
	for (int i= 0;i<pRGBDIB->m_Rect.cy;i += nStep)
	{
		for(int j=0;j<pRGBDIB->m_Rect.cx;j += nStep)
		{
			pt.x = j;
			pt.y = pRGBDIB->m_Rect.cy - i - nStep;
			color = HLStoRGB_ONE((double)j/(double)pRGBDIB->m_Rect.cx, DEFAULT_LumINANCE, (double)i/(double)pRGBDIB->m_Rect.cy);
			dc.DrawPixel(pt.x,pt.y,color);
		}
	}
}

void CWispRGBSelect::UpdateLumColor(bool bGather)
{
	CWispDC dc;
	double	dblLum,dblSat,dblHue;
	if(bGather)
		m_RGBDIB.GetPixel(m_PTSelected.x - m_RGBRect.x,m_PTSelected.y - m_RGBRect.y,&m_RGBClr);
	RGBtoHSL(m_RGBClr,&dblHue,&dblSat,&dblLum);
	dc.AttachDIB(&m_LumDIB);
	dc.DrawHLine(0,m_LumRect.cx-1,0,WISP_RGB(255,255,255));
	for (int y =1; y < m_LumRect.cy-1; y++)
	{
		dc.DrawHLine(0,m_LumRect.cx-1,y,HLStoRGB_ONE (dblHue, ((double)(m_LumRect.cy-y))/(double)m_LumRect.cy, dblSat));
	}
	dc.DrawHLine(0,m_LumRect.cx-1,m_LumRect.cy-1,WISP_RGB(0,0,0));
	ShowColorValue();
}

void CWispRGBSelect::UpdateColor()
{
	m_LumDIB.GetPixel(0,m_LumYPos - m_LumRect.y,&m_RGBClr);
	ShowColorValue();
}

void CWispRGBSelect::UpdateColorValue()
{
	DWORD r,g,b;
	if(USDecStrToNum((WISP_PCSTR)m_pRedEdit->m_WndText,&r)==false || r>255)
		return;
	if(USDecStrToNum((WISP_PCSTR)m_pGreenEdit->m_WndText,&g)==false || g>255)
		return;
	if(USDecStrToNum((WISP_PCSTR)m_pBlueEdit->m_WndText,&b)==false || b>255)
		return;
	m_RGBClr = WISP_RGB(r,g,b);
	UpdateClient();
}

void CWispRGBSelect::ShowColorValue()
{
	CWispString String;
	String.Format(WSTR("%d"),WISP_RGB_R(m_RGBClr));
	m_pRedEdit->SetWindowText(String);
	String.Format(WSTR("%d"),WISP_RGB_G(m_RGBClr));
	m_pGreenEdit->SetWindowText(String);
	String.Format(WSTR("%d"),WISP_RGB_B(m_RGBClr));
	m_pBlueEdit->SetWindowText(String);

}

void RGBtoHSL( COLORREF rgb, double *H, double *S, double *L )
{   
	double delta;
	double r = (double)WISP_RGB_R(rgb)/255;
	double g = (double)WISP_RGB_G(rgb)/255;
	double b = (double)WISP_RGB_B(rgb)/255;   
	double cmax = max(r, max(g, b));
	double cmin = min(r, min(g, b));   
	*L=(cmax+cmin)/2.0;   

	if(cmax==cmin) 
	{
		*S = 0;      
		*H = 0; // it's really undefined   
	} 
	else 
	{
		if(*L < 0.5) 
			*S = (cmax-cmin)/(cmax+cmin);      
		else
			*S = (cmax-cmin)/(2.0-cmax-cmin);      

		delta = cmax - cmin;
		if(r==cmax) 
			*H = (g-b)/delta;      
		else if(g==cmax)
			*H = 2.0 +(b-r)/delta;
		else          
			*H=4.0+(r-g)/delta;
		*H /= 6.0; 
		if(*H < 0.0)
			*H += 1;  
	}
}

COLORREF HLStoRGB_ONE( double H, double L, double S )
{
	double r, g, b;
	double m1, m2;

	if(S==0) {
		r=g=b=L;
	} else {
		if(L <=0.5)
			m2 = L*(1.0+S);
		else
			m2 = L+S-L*S;
		m1 = 2.0*L-m2;
		r = HueToRGB(m1, m2, H+1.0/3.0);
		g = HueToRGB(m1, m2, H);
		b = HueToRGB(m1, m2, H-1.0/3.0);
	}
	return WISP_RGB((BYTE)(r*255), (BYTE)(g*255), (BYTE)(b*255));
}

double HueToRGB(double m1, double m2, double h )
{
	if( h < 0 ) h += 1.0;
	if( h > 1 ) h -= 1.0;
	if( 6.0*h < 1 )
		return (m1+(m2-m1)*h*6.0);
	if( 2.0*h < 1 )
		return m2;
	if( 3.0*h < 2.0 )
		return (m1+(m2-m1)*((2.0/3.0)-h)*6.0);
	return m1;
}

