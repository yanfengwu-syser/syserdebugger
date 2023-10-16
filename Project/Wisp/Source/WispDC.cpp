#include "StdAfx.h"
#include "WispDC.h"
#include "WispWnd.h"


CWispDC::CWispDC()
{
	m_pWispWnd = NULL;
	m_pRect = NULL;
	m_pClipRect = NULL;
	m_TabAlign = 4;
	m_ColorTable = NULL;
}

CWispDC::CWispDC(CWispDIB*pDIB)
{
	AttachDIB(pDIB);
	m_pClipRect = NULL;
}

CWispDC::CWispDC(WISP_FRAME_BUFFER*pFrameBuffer,WISP_RECT*pRect)
{
	AttachFrameBuffer(pFrameBuffer,pRect);
	m_pClipRect = NULL;
}

void CWispDC::InitParam()
{
	m_pWispBase = gpCurWisp;
	m_TextStyle=WISP_TEXT_TRANS;
	m_TextColor=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BLACK];
	m_TextShadowColor = m_pWispBase->m_pCurDrawObj->m_crSystem[SC_SHADOW_LIGHT];
	m_TextBKColor=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_WHITE];
	m_pFont=&m_pWispBase->m_FontList[m_pWispBase->m_DefaultFontType];
	if(m_pWispWnd && m_pWispWnd->m_ParentWnd && m_pWispWnd->m_ParentWnd->m_CtrlType == WISP_CTRL_FORM)
		m_pFont=&m_pWispBase->m_FontList[WISP_FONT_6X12];
}

bool CWispDC::AttachDIB(CWispDIB*pDIB)
{
	m_pWispWnd = NULL;
	m_pWispBase = gpCurWisp;
	m_pFrameBuffer = &pDIB->m_FrameBuffer;
	m_pRect = &pDIB->m_Rect;
	InitParam();
	return true;
}

bool CWispDC::AttachFrameBuffer(WISP_FRAME_BUFFER*pFrameBuffer,WISP_RECT*pRect)
{
	m_pWispWnd = NULL;
	m_pWispBase = gpCurWisp;
	m_pFrameBuffer = pFrameBuffer;
	m_pRect = pRect;
	InitParam();
	return true;
}

void CWispDC::SetTextType(UINT Type)
{
	m_pFont=&m_pWispBase->m_FontList[Type];
}

bool CWispDC::AttachWnd(IN CWispBaseWnd*pWispWnd,IN WISP_RECT*pRect)
{
	m_pWispBase = pWispWnd->m_pWispBase;
	m_pWispWnd=pWispWnd;
	m_pRect=pRect;
	m_pFrameBuffer = &m_pWispBase->m_FrameBuffer;
	InitParam();
	return true;
}

void CWispDC::Detach()
{
}

int CWispDC::DrawString(IN int x,IN int y,IN const WISP_CHAR*string,IN int Len,int Index,int Flags)
{
	WISP_RECT rc;
	COLORREF*pBKColor;
	rc.x=x+m_pRect->x;
	rc.y=y+m_pRect->y;
	rc.cx= GetTextExtent(string,Len);
	rc.cy = m_pFont->m_Height;
	if(ClipDCRect(&rc)==false)
		return 0;
	if(m_TextStyle & WISP_TEXT_OPAQUE)
		pBKColor=&m_TextBKColor;
	else
		pBKColor=NULL;
	return DrawString(m_pFont,x+m_pRect->x,y+m_pRect->y,string,m_TextColor,&rc,pBKColor,Len,Index,Flags);
}

int CWispDC::DrawRightString(IN int x,IN int y,IN const WISP_CHAR*string,IN int Len,int Index)
{
	WISP_RECT rc;
	COLORREF*pBKColor;
	if(Len == -1)
		Len = TStrLen(string);
	rc.x=x+m_pRect->x;
	rc.y=y+m_pRect->y;
	rc.cx= m_pRect->cx;
	rc.cy = m_pFont->m_Height;
	if(ClipDCRect(&rc)==false)
		return 0;
	if(m_TextStyle & WISP_TEXT_OPAQUE)
		pBKColor=&m_TextBKColor;
	else
		pBKColor=NULL;
	return 0;
}

int CWispDC::DrawShadowString(IN int x,IN int y,IN const WISP_CHAR*string,IN int Deep,IN int Len,int Index)
{
	COLORREF TextColor;
	TextColor=m_TextColor;
	m_TextColor=m_TextShadowColor;
	DrawString(x+Deep,y+Deep,string,Len);
	m_TextColor=TextColor;
	return DrawString(x,y,string,Len,Index);
}

int CWispDC::DrawShadowString(IN WISP_RECT*pRect,IN const WISP_CHAR*string,IN int Deep,IN int Len,int Index)
{
	int x,y;
	COLORREF TextColor;
	WISP_RECT ClipRect;
	ClipRect.x=pRect->x+m_pRect->x;
	ClipRect.y=pRect->y+m_pRect->y;
	ClipRect.cx = pRect->cx;
	ClipRect.cy = pRect->cy;
	if(ClipDCRect(&ClipRect)==false)
		return 0;
	TextColor=m_TextColor;
	m_TextColor=m_TextShadowColor;
	y = CENTER_ALGN(m_pFont->m_Height,pRect->cy)+pRect->y+m_pRect->y;
	x = m_pRect->x + pRect->x;
	DrawString(m_pFont,x+Deep,y+Deep,string,m_TextColor,&ClipRect,NULL,Len,Index);
	m_TextColor=TextColor;
	return DrawString(m_pFont,x,y,string,m_TextColor,&ClipRect,NULL,Len,Index);
}

int CWispDC::DrawString(IN WISP_RECT*pRect,IN const WISP_CHAR*string,IN int Len,int Index)
{
	int x,y;
	WISP_RECT ClipRect;
	ClipRect.x=pRect->x+m_pRect->x;
	ClipRect.y=pRect->y+m_pRect->y;
	ClipRect.cx = pRect->cx;
	ClipRect.cy = pRect->cy;
	if(ClipDCRect(&ClipRect)==false)
		return 0;
	y = CENTER_ALGN(m_pFont->m_Height,pRect->cy)+pRect->y+m_pRect->y;
	x = m_pRect->x + pRect->x;;
	return DrawString(m_pFont,x,y,string,m_TextColor,&ClipRect,NULL,Len,Index);
}

int CWispDC::DrawColorString(IN int x,IN int y,IN const WISP_COLOR_CHAR*string,IN int Len,int Index)
{
	WISP_RECT rc;
	rc.x=x+m_pRect->x;
	rc.y=y+m_pRect->y;
	rc.cx= m_pRect->cx+(m_pRect->x-x);
	rc.cy = m_pFont->m_Height;
	if(ClipDCRect(&rc)==false)
		return 0;
	return DrawColorString(m_pFont,x+m_pRect->x,y+m_pRect->y,string,&rc,Len,Index);
}

int CWispDC::DrawColorString(IN WISP_RECT*pRect,IN const WISP_COLOR_CHAR*string,IN int Len,int Index)
{
	int x,y;
	WISP_RECT ClipRect;
	ClipRect.x=pRect->x+m_pRect->x;
	ClipRect.y=pRect->y+m_pRect->y;
	ClipRect.cx = pRect->cx;
	ClipRect.cy = pRect->cy;
	if(ClipDCRect(&ClipRect)==false)
		return 0;
	y = CENTER_ALGN(m_pFont->m_Height,pRect->cy)+pRect->y+m_pRect->y;
	x = m_pRect->x + pRect->x;;
	return DrawColorString(m_pFont,x,y,string,&ClipRect,Len,Index);
}

int CWispDC::DrawColorString(IN CWispFont*pLogFont,IN int x,IN int y,IN const WISP_COLOR_CHAR*pStr,IN WISP_RECT*pClipRect,IN int Length,IN int Index)
{
	BYTE*pFont;
	int Width,n,i,j,BitOffset,OrgX;
	WISP_CHAR szText[MAX_TAB_ALIGN];
	COLORREF TXTClr,BKClr;
	if(m_ColorTable == NULL)
		m_ColorTable = m_pWispBase->m_pCurDrawObj->m_crSystem;
	OrgX = x;
	while(Length && *pStr)
	{
		switch((WISP_CHAR)*pStr)
		{
		case WISP_STR('\n'):
			return x - OrgX;
		case WISP_STR('\t'):
			n = m_TabAlign - Index % m_TabAlign;
			szText[n]=0;
			do
			{
				n--;
				szText[n]=WISP_STR(' ');
			}while(n>0);
			break;
		default:
			szText[0]=(WISP_CHAR)*pStr;
			szText[1]=0;
			break;
		}
		TXTClr = LOW_BYTE(HIGH_WORD(*pStr));
		BKClr = HIGH_BYTE(HIGH_WORD(*pStr));
		for(n=0;szText[n];n++)
		{
			pFont=pLogFont->GetCharPixelBuffer(szText[n]);
			Width=pLogFont->GetCharWidth(szText[n]);
			BitOffset=0;
			if(x+Width>=pClipRect->x && x<pClipRect->x+pClipRect->cx)
			{
				for(j=0;j<pLogFont->m_Height;j++)
				{
					for(i=0;i<Width;i++)
					{
						if((pFont[BitOffset/8]>>(BitOffset%8)) & 1)
						{
							if(PtInRect(pClipRect,x+i,y+j))
								m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x+i,y+j,m_ColorTable[TXTClr]);
						}
						else if(BKClr)
						{
							if(PtInRect(pClipRect,x+i,y+j))
								m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x+i,y+j,m_ColorTable[BKClr]);
						}
						BitOffset++;
					}
				}
			}
			x+=Width;
			Index++;
		}
		pStr++;
		Length--;
	}
	return x - OrgX;
}

void CWispDC::DrawPixel(IN int x, IN int y, IN COLORREF color)
{
	WISP_POINT pt;
	pt.x=x+m_pRect->x;
	pt.y=y+m_pRect->y;
	if(ClipDCPoint(&pt)==false)
		return;
	m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x,y,color);
}

void CWispDC::DrawCircle(IN int x,IN int y,IN int radius,IN COLORREF color)
{
	WISP_RECT rc;
	int dx,dy,p;
	rc = *m_pRect;
	dx = 0;
	dy = radius;
	p = 1 - radius;
	x += m_pRect->x;
	y += m_pRect->y;
	ClipDCRect(&rc);
	CirclePlotPoints(x,y,dx,dy,color,&rc);
	while(dx<dy)
	{
		dx++;
		if(p<0)
		{
			p+=2*dx+1;
		}
		else
		{
			dy--;
			p+=2*(dx-dy)+1;
		}
		CirclePlotPoints(x,y,dx,dy,color,&rc);
	}
}

void CWispDC::DrawCircleRightTop(IN int x,IN int y,IN int radius,IN COLORREF color)
{
	WISP_RECT rc;
	int dx,dy,p;
	rc = *m_pRect;
	dx = 0;
	dy = radius;
	p = 1 - radius;
	x += m_pRect->x;
	y += m_pRect->y;
	ClipDCRect(&rc);
	while(dx<dy)
	{
		dx++;
		if(p<0)
		{
			p+=2*dx+1;
		}
		else
		{
			dy--;
			p+=2*(dx-dy)+1;
		}
		CirclePlotPointsRightTop(x,y,dx,dy,color,&rc);
	}
}

void CWispDC::DrawCircleRightBottom(IN int x,IN int y,IN int radius,IN COLORREF color)
{
	WISP_RECT rc;
	int dx,dy,p;
	rc = *m_pRect;
	dx = 0;
	dy = radius;
	p = 1 - radius;
	x += m_pRect->x;
	y += m_pRect->y;
	ClipDCRect(&rc);
	while(dx<dy)
	{
		dx++;
		if(p<0)
		{
			p+=2*dx+1;
		}
		else
		{
			dy--;
			p+=2*(dx-dy)+1;
		}
		CirclePlotPointsRightBottom(x,y,dx,dy,color,&rc);
	}
}

void CWispDC::DrawCircleLeftTop(IN int x,IN int y,IN int radius,IN COLORREF color)
{
	WISP_RECT rc;
	int dx,dy,p;
	rc = *m_pRect;
	dx = 0;
	dy = radius;
	p = 1 - radius;
	x += m_pRect->x;
	y += m_pRect->y;
	ClipDCRect(&rc);
	while(dx<dy)
	{
		dx++;
		if(p<0)
		{
			p+=2*dx+1;
		}
		else
		{
			dy--;
			p+=2*(dx-dy)+1;
		}
		CirclePlotPointsLeftTop(x,y,dx,dy,color,&rc);
	}
}

void CWispDC::DrawCircleLeftBottom(IN int x,IN int y,IN int radius,IN COLORREF color)
{
	WISP_RECT rc;
	int dx,dy,p;
	rc = *m_pRect;
	dx = 0;
	dy = radius;
	p = 1 - radius;
	x += m_pRect->x;
	y += m_pRect->y;
	ClipDCRect(&rc);
	while(dx<dy)
	{
		dx++;
		if(p<0)
		{
			p+=2*dx+1;
		}
		else
		{
			dy--;
			p+=2*(dx-dy)+1;
		}
		CirclePlotPointsLeftBottom(x,y,dx,dy,color,&rc);
	}
}

void CWispDC::DrawLine(IN int x1,IN int y1,IN int x2,IN int y2,IN COLORREF color)
{
	int x,y,xDelta,yDelta,Delta,Count=0;
	x1+=m_pRect->x;
	x2+=m_pRect->x;
	y1+=m_pRect->y;
	y2+=m_pRect->y;
	if(ClipDCLine(&x1,&y1,&x2,&y2)==false)
		return;

	xDelta=ABS(x2-x1);
	yDelta=ABS(y2-y1);
	if(xDelta<yDelta)
	{
		if(y1>y2)
		{
			SWAP(y1,y2);
			SWAP(x1,x2);
		}
		x=x1;
		if(x1<x2)	Delta=1;
		else		Delta=-1;
		for(y=y1;y<=y2;y++)
		{
			if(Count>=yDelta)
			{
				Count-=yDelta;
				x+=Delta;
			}
			Count+=xDelta;
			m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x,y,color);
		}
	}
	else
	{
		if(x1>x2)
		{
			SWAP(x1,x2);
			SWAP(y1,y2);
		}
		y=y1;
		if(y1<y2)	Delta=1;
		else		Delta=-1;
		for(x=x1;x<=x2;x++)
		{
			if(Count>=xDelta)
			{
				Count-=xDelta;
				y+=Delta;
			}
			Count+=yDelta;
			m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x,y,color);
		}
	}
}

void CWispDC::DrawVLine(IN int x,IN int y1,IN int y2,IN COLORREF color)
{
	x+=m_pRect->x;
	y1+=m_pRect->y;
	y2+=m_pRect->y;
	if(ClipDCLine(&x,&y1,&x,&y2)==false)
		return;
	if(y2<y1)
		SWAP(y1,y2);
	for(int y=y1;y<=y2;y++)
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x,y,color);
}

void CWispDC::DrawHLine(IN int x1,IN int x2,IN int y,IN COLORREF color)
{
	x1+=m_pRect->x;
	x2+=m_pRect->x;
	y+=m_pRect->y;
	if(ClipDCLine(&x1,&y,&x2,&y)==false)
		return;
	if(x2<x1)
		SWAP(x1,x2);
	m_pFrameBuffer->pDrawHAL->SetHLinePixel(m_pFrameBuffer,x1,y,x2-x1+1,color);
}

void CWispDC::DrawVDashLine(IN int x,IN int y1,IN int y2,IN COLORREF color)
{
	x+=m_pRect->x;
	y1+=m_pRect->y;
	y2+=m_pRect->y;
	if(ClipDCLine(&x,&y1,&x,&y2)==false)
		return;
	int n = y1;
	while(n<=y2)
	{
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x, n, color);
		n+=2;
	}
}

void CWispDC::DrawHDashLine(IN int x1,IN int x2,IN int  y,IN COLORREF color)
{
	x1+=m_pRect->x;
	x2+=m_pRect->x;
	y+=m_pRect->y;
	if(ClipDCLine(&x1,&y,&x2,&y)==false)
		return;
	int n = x1;
	while(n<=x2)
	{
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,n, y, color);
		n+=2;
	}
}

void CWispDC::DrawRect(IN WISP_RECT*pRc,IN COLORREF color)
{
	DrawVLine(pRc->x,			pRc->y,				pRc->y+pRc->cy-1,	color);
	DrawVLine(pRc->x+pRc->cx-1,	pRc->y,				pRc->y+pRc->cy-1,	color);
	DrawHLine(pRc->x,			pRc->x+pRc->cx-1,	pRc->y,				color);
	DrawHLine(pRc->x,			pRc->x+pRc->cx-1,	pRc->y+pRc->cy-1,	color);
}

void CWispDC::DrawRect(IN int x,IN int y,IN int cx,IN int cy,IN COLORREF color)
{
	DrawVLine(x,		y,		y+cy-1,	color);
	DrawVLine(x+cx-1,	y,		y+cy-1,	color);
	DrawHLine(x,		x+cx-1,	y,		color);
	DrawHLine(x,		x+cx-1,	y+cy-1,	color);
}

void CWispDC::DrawRoundRect(IN WISP_RECT*pRc,IN COLORREF color)
{
	DrawVLine(pRc->x,			pRc->y+1,			pRc->y+pRc->cy-2,	color);
	DrawVLine(pRc->x+pRc->cx-1,	pRc->y+1,			pRc->y+pRc->cy-2,	color);
	DrawHLine(pRc->x+1,			pRc->x+pRc->cx-2,	pRc->y,				color);
	DrawHLine(pRc->x+1,			pRc->x+pRc->cx-2,	pRc->y+pRc->cy-1,	color);
}

void CWispDC::Draw3DRect(IN WISP_RECT *pRc,IN COLORREF crTopLeft, COLORREF crBottomRight)
{
	DrawVLine(pRc->x,			pRc->y,				pRc->y+pRc->cy-1,	crTopLeft);
	DrawVLine(pRc->x+pRc->cx-1,	pRc->y,				pRc->y+pRc->cy-1,	crBottomRight);
	DrawHLine(pRc->x,			pRc->x+pRc->cx-1,	pRc->y,				crTopLeft);
	DrawHLine(pRc->x,			pRc->x+pRc->cx-1,	pRc->y+pRc->cy-1,	crBottomRight);
}

void CWispDC::Draw3DRect(IN WISP_RECT*pRc,IN bool bRaised,IN int Deep)
{
	COLORREF ColTop,ColBottom;
	int Sign,Inc;
	if(bRaised)
	{
		ColTop=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BRIGHT];
		ColBottom=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_SHADOW];
	}
	else
	{
		ColTop=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_SHADOW];
		ColBottom=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BRIGHT];
	}
	if(Deep<0)
	{
		Deep=-Deep;
		Sign=-1;
	}
	else
	{
		Sign=1;
	}
	for(int n=0;n<Deep;n++)
	{
		Inc=n*Sign;
		DrawHLine(pRc->x+Inc,pRc->x+pRc->cx-1-Inc,pRc->y+Inc,ColTop);
		DrawVLine(pRc->x+Inc,pRc->y+Inc,pRc->y+pRc->cy-1-Inc,ColTop);
		DrawHLine(pRc->x+Inc,pRc->x+pRc->cx-1-Inc,pRc->y+pRc->cy-1-Inc,ColBottom);
		DrawVLine(pRc->x+pRc->cx-1-Inc,pRc->y+Inc,pRc->y+pRc->cy-1-Inc,ColBottom);
	}
}


void CWispDC::DrawDashRect(IN WISP_RECT*pRc,IN COLORREF color)
{
	DrawVDashLine(pRc->x,			pRc->y,				pRc->y+pRc->cy-1,	color);
	DrawVDashLine(pRc->x+pRc->cx-1,	pRc->y,				pRc->y+pRc->cy-1,	color);
	DrawHDashLine(pRc->x,			pRc->x+pRc->cx-1,	pRc->y,				color);
	DrawHDashLine(pRc->x,			pRc->x+pRc->cx-1,	pRc->y+pRc->cy-1,	color);
}

void CWispDC::DrawFullRect(IN WISP_RECT*pRc,IN COLORREF color)
{
	WISP_RECT rc;
	rc=*pRc;
	rc.x+=m_pRect->x;
	rc.y+=m_pRect->y;
	if(ClipDCRect(&rc)==false)
		return;
	for(int y=rc.y;y<rc.y+rc.cy;y++)
	{
		m_pFrameBuffer->pDrawHAL->SetHLinePixel(m_pFrameBuffer,rc.x,y,rc.cx,color);
	}
}

void CWispDC::DrawFullRect(IN int x,IN int y,IN int cx,IN int cy,IN COLORREF color)
{
	WISP_RECT rc;
	rc.x = x + m_pRect->x;
	rc.y = y + m_pRect->y;
	rc.cx = cx;
	rc.cy = cy;
	if(ClipDCRect(&rc)==false)
		return;
	for(int y=rc.y;y<rc.y+rc.cy;y++)
	{
		m_pFrameBuffer->pDrawHAL->SetHLinePixel(m_pFrameBuffer,rc.x,y,rc.cx,color);
	}
}

void CWispDC::DrawMiddleXGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg)
{
	COLORREF Clr;
	WISP_RECT rc = *pRc;
	rc.cx /= 2;
	Clr = DrawXGrayChgFullRect(&rc,color,nChg);
	rc.x+=rc.cx;
	rc.cx = pRc->x + pRc->cx - rc.x;
	DrawXGrayChgFullRect(&rc,Clr,-nChg);	
}

void CWispDC::DrawMiddleXGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc)
{
	WISP_RECT rc = *pRc;
	rc.cx /= 2;
	DrawXGrayChgFullRect(ColorBegin,ColorEnd,&rc);
	rc.x+=rc.cx;
	rc.cx = pRc->x + pRc->cx - rc.x;
	DrawXGrayChgFullRect(ColorEnd,ColorBegin,&rc);
}

COLORREF CWispDC::DrawXGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg)
{
	COLORREF LastColor;
	WISP_RECT rc,frc;
	rc=*pRc;
	rc.x+=m_pRect->x;
	rc.y+=m_pRect->y;
	if(ClipDCRect(&rc)==false)
		return GRAY_CHG(color,nChg,pRc->cx);
	frc=*pRc;
	frc.x+=m_pRect->x;
	frc.y+=m_pRect->y;
	for(int x=frc.x;x<frc.x+frc.cx;x++)
	{
		LastColor = GRAY_CHG(color,nChg,x-frc.x);
		if(x>=rc.x && x<rc.x+rc.cx)
		{
			for(int y=rc.y;y<rc.y+rc.cy;y++)
			{
				m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x,y,LastColor);
			}
		}
	}
	return LastColor;
}

void CWispDC::DrawXGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc)
{
	COLORREF Color;
	WISP_RECT rc,frc;
	int r1,g1,b1,r,g,b,dr,dg,db;

	rc=*pRc;
	rc.x+=m_pRect->x;
	rc.y+=m_pRect->y;
	if(ClipDCRect(&rc)==false)
		return;

	r = WISP_RGB_R(ColorBegin);
	g = WISP_RGB_G(ColorBegin);
	b = WISP_RGB_B(ColorBegin);
	r1 = WISP_RGB_R(ColorEnd);
	g1 = WISP_RGB_G(ColorEnd);
	b1 = WISP_RGB_B(ColorEnd);
	dr = ((r1 - r)<<16)/pRc->cx;
	dg = ((g1 - g)<<16)/pRc->cx;
	db = ((b1 - b)<<16)/pRc->cx;
	r=r<<16;g=g<<16;b=b<<16;
	frc=*pRc;
	frc.x+=m_pRect->x;
	frc.y+=m_pRect->y;

	for(int x=frc.x;x<frc.x+frc.cx;x++)
	{
		r+=dr;g+=dg;b+=db;
		Color = WISP_RGB(r>>16,g>>16,b>>16);
		if(x>=rc.x && x<rc.x+rc.cx)
		{
			for(int y=rc.y;y<rc.y+rc.cy;y++)
			{
				m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x,y,Color);
			}
		}
	}
}

void CWispDC::DrawMiddleYGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg)
{
	COLORREF Clr;
	WISP_RECT rc = *pRc;
	rc.cy /= 2;
	Clr = DrawYGrayChgFullRect(&rc,color,nChg);
	rc.y+=rc.cy;
	rc.cy = pRc->y + pRc->cy - rc.y;
	DrawYGrayChgFullRect(&rc,Clr,-nChg);
}

void CWispDC::DrawMiddleYGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc)
{
	WISP_RECT rc = *pRc;
	rc.cy /= 2;
	DrawYGrayChgFullRect(ColorBegin,ColorEnd,&rc);
	rc.y+=rc.cy;
	rc.cy = pRc->y + pRc->cy - rc.y;
	DrawYGrayChgFullRect(ColorEnd,ColorBegin,&rc);
}


COLORREF CWispDC::DrawYGrayChgFullRect(IN WISP_RECT*pRc,IN COLORREF color,IN int nChg)
{
	COLORREF LastColor;
	WISP_RECT rc,frc;
	rc=*pRc;
	rc.x+=m_pRect->x;
	rc.y+=m_pRect->y;
	if(ClipDCRect(&rc)==false)
		return GRAY_CHG(color,nChg,pRc->cy);
	frc=*pRc;
	frc.x+=m_pRect->x;
	frc.y+=m_pRect->y;
	for(int y=frc.y;y<frc.y+frc.cy;y++)
	{
		LastColor = GRAY_CHG(color,nChg,y-frc.y);
		if(y>=rc.y && y<rc.y+rc.cy)
		{
			m_pFrameBuffer->pDrawHAL->SetHLinePixel(m_pFrameBuffer,rc.x,y,rc.cx,LastColor);
		}
	}
	return LastColor;
}

void CWispDC::DrawYGrayChgFullRect(IN COLORREF ColorBegin,IN COLORREF ColorEnd,IN WISP_RECT*pRc)
{
	WISP_RECT rc,frc;
	int r1,g1,b1,r,g,b,dr,dg,db;

	rc=*pRc;
	rc.x+=m_pRect->x;
	rc.y+=m_pRect->y;
	if(ClipDCRect(&rc)==false)
		return;

	r = WISP_RGB_R(ColorBegin);
	g = WISP_RGB_G(ColorBegin);
	b = WISP_RGB_B(ColorBegin);
	r1 = WISP_RGB_R(ColorEnd);
	g1 = WISP_RGB_G(ColorEnd);
	b1 = WISP_RGB_B(ColorEnd);
	dr = ((r1 - r)<<16)/pRc->cy;
	dg = ((g1 - g)<<16)/pRc->cy;
	db = ((b1 - b)<<16)/pRc->cy;
	r=r<<16;g=g<<16;b=b<<16;

	frc=*pRc;
	frc.x+=m_pRect->x;
	frc.y+=m_pRect->y;

	for(int y=frc.y;y<frc.y+frc.cy;y++)
	{
		r+=dr;g+=dg;b+=db;
		if(y>=rc.y && y<rc.y+rc.cy)
		{
			m_pFrameBuffer->pDrawHAL->SetHLinePixel(m_pFrameBuffer,rc.x,y,rc.cx,WISP_RGB(r>>16,g>>16,b>>16));
		}
	}
}

void CWispDC::DrawFrameRect(IN int x,IN int y,IN int cx,IN int cy,IN bool bRaised,IN int Deep)
{
	COLORREF ColTop,ColBottom;
	int Sign,Inc;
	if(bRaised)
	{
		ColTop=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BRIGHT];
		ColBottom=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_SHADOW];
	}
	else
	{
		ColTop=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_SHADOW];
		ColBottom=m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BRIGHT];
	}
	if(Deep<0)
	{
		Deep=-Deep;
		Sign=-1;
	}
	else
	{
		Sign=1;
	}
	for(int n=0;n<Deep;n++)
	{
		Inc=n*Sign;
		DrawHLine(x+Inc,x+cx-1-Inc,y+Inc,ColTop);
		DrawHLine(x+Inc,x+cx-1-Inc,y+cy-1-Inc,ColBottom);
		DrawVLine(x+Inc,y+Inc,y+cy-1-Inc,ColTop);
		DrawVLine(x+cx-1-Inc,y+Inc,y+cy-1-Inc,ColBottom);
	}
}

void CWispDC::DrawFrameRect(IN WISP_RECT*pRc,IN bool bRaised,IN int Deep)
{
	DrawFrameRect(pRc->x,pRc->y,pRc->cx,pRc->cy,bRaised,Deep);
}

void CWispDC::Clear(IN COLORREF color)
{
	WISP_RECT rc;
	rc.x = rc.y = 0;
	rc.cx = m_pRect->cx;
	rc.cy = m_pRect->cy;
	DrawFullRect(&rc,color);
}

void CWispDC::DrawDIBTiled(IN CWispDIB*pDIB,IN WISP_RECT*pRect)
{
	WISP_RECT DefRect;
	if(pRect==NULL)
	{
		DefRect.x=DefRect.y=0;
		DefRect.cx=m_pRect->cx;
		DefRect.cy=m_pRect->cy;
		pRect=&DefRect;
	}
	for(int x=pRect->x;x<pRect->x+pRect->cx;x+=pDIB->m_FrameBuffer.Width)
	{
		for(int y=pRect->y;y<pRect->y+pRect->cy;y+=pDIB->m_FrameBuffer.Height)
		{
			DrawDIB(x,y,pDIB);
		}
	}
}

void CWispDC::DrawDIB(IN int x,IN int y,IN CWispDIB*pDIB)
{
	COLORREF*pPixel;
	WISP_RECT ClipRect;
	if(pDIB->m_FrameBuffer.Buffer==NULL)
		return;
	CODE_ASSERT(pDIB->m_FrameBuffer.Bpp==32);
	x-=pDIB->m_HotPT.x;
	y-=pDIB->m_HotPT.y;
	ClipRect.x=m_pRect->x+x;
	ClipRect.y=m_pRect->y+y;
	ClipRect.cx=pDIB->m_FrameBuffer.Width;
	ClipRect.cy=pDIB->m_FrameBuffer.Height;
	if(ClipDCRect(&ClipRect)==false)
		return;
	pPixel=(COLORREF*)RT_PBYTE(pDIB->m_FrameBuffer.Buffer,(ClipRect.y-m_pRect->y-y)*pDIB->m_FrameBuffer.LineDistance + (ClipRect.x-m_pRect->x-x)*sizeof(COLORREF) );
	for(int ny=0;ny<ClipRect.cy;ny++)
	{
		switch(pDIB->m_Type)
		{
		case WISP_DIB_BITMAP:
			m_pFrameBuffer->pDrawHAL->Copy32BitPixelTo(RT_PBYTE(m_pFrameBuffer->Buffer,(ClipRect.y+ny)*m_pFrameBuffer->LineDistance+ClipRect.x*(m_pFrameBuffer->Bpp/8)),pPixel,ClipRect.cx);
			pPixel+=(pDIB->m_FrameBuffer.LineDistance/sizeof(COLORREF));
			break;
		case WISP_DIB_TK:
			for(int nx=0;nx<ClipRect.cx;nx++)
			{
				if(*pPixel!=pDIB->m_ColorKey)
					m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,ClipRect.x+nx,ClipRect.y+ny,*pPixel);
				pPixel++;
			}
			pPixel+=(pDIB->m_FrameBuffer.LineDistance/sizeof(COLORREF))-ClipRect.cx;
			break;
		case WISP_DIB_TK_XOR:
			for(int nx=0;nx<ClipRect.cx;nx++)
			{
				if(*pPixel!=pDIB->m_ColorKey)
					m_pFrameBuffer->pDrawHAL->DrawXorPixel(m_pFrameBuffer,ClipRect.x+nx,ClipRect.y+ny,*pPixel);
				pPixel++;
			}
			pPixel+=(pDIB->m_FrameBuffer.LineDistance/sizeof(COLORREF))-ClipRect.cx;
			break;
		}
	}
}

void CWispDC::DrawDIB(IN WISP_RECT*pRC,IN CWispDIB*pDIB)
{
	int x,y;
	x = pRC->x+CENTER_ALGN(pDIB->Width(),pRC->cx);
	y = pRC->y+CENTER_ALGN(pDIB->Height(),pRC->cy);
	DrawDIB(x,y,pDIB);
}

void CWispDC::DrawGrayDIB(IN WISP_RECT*pRC,IN CWispDIB*pDIB)
{
	int x,y;
	x = pRC->x+CENTER_ALGN(pDIB->Width(),pRC->cx);
	y = pRC->y+CENTER_ALGN(pDIB->Height(),pRC->cy);
	DrawGrayDIB(x,y,pDIB);
}

void CWispDC::DrawGrayDIB(IN int x,IN int y,IN CWispDIB*pDIB)
{
	COLORREF*pPixel;
	WISP_RECT ClipRect;
	CODE_ASSERT(pDIB->m_FrameBuffer.Bpp==32);
	x-=pDIB->m_HotPT.x;
	y-=pDIB->m_HotPT.y;
	ClipRect.x=m_pRect->x+x;
	ClipRect.y=m_pRect->y+y;
	ClipRect.cx=pDIB->m_FrameBuffer.Width;
	ClipRect.cy=pDIB->m_FrameBuffer.Height;
	if(ClipDCRect(&ClipRect)==false)
		return;
	pPixel=(COLORREF*)RT_PBYTE(pDIB->m_FrameBuffer.Buffer,(ClipRect.y-m_pRect->y-y)*pDIB->m_FrameBuffer.LineDistance + (ClipRect.x-m_pRect->x-x)*sizeof(COLORREF) );
	for(int ny=0;ny<ClipRect.cy;ny++)
	{
		switch(pDIB->m_Type)
		{
		case WISP_DIB_BITMAP:
		case WISP_DIB_TK:
			for(int nx=0;nx<ClipRect.cx;nx++)
			{
				if(*pPixel!=pDIB->m_ColorKey)
					m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,ClipRect.x+nx,ClipRect.y+ny,GRAY_DEEP(*pPixel)>GRAY_DEEP(0x00808080) ? SYS_COLOR[SC_UNNAMED_21] : SYS_COLOR[SC_CLIENT_BG] );
				pPixel++;
			}
			pPixel+=(pDIB->m_FrameBuffer.LineDistance/sizeof(COLORREF))-ClipRect.cx;
			break;
		case WISP_DIB_TK_XOR:
			for(int nx=0;nx<ClipRect.cx;nx++)
			{
				if(*pPixel!=pDIB->m_ColorKey)
					m_pFrameBuffer->pDrawHAL->DrawXorPixel(m_pFrameBuffer,ClipRect.x+nx,ClipRect.y+ny,*pPixel);
				pPixel++;
			}
			pPixel+=(pDIB->m_FrameBuffer.LineDistance/sizeof(COLORREF))-ClipRect.cx;
			break;
		}
	}
}

bool CWispDC::ClipDCRect(INOUT WISP_RECT*pRect)
{
	CWispBaseWnd*pClipWnd,*pWnd;
	if(m_pClipRect && ClipRect(pRect,m_pClipRect)==false)
		return false;
	if(m_pWispWnd==NULL)//DIB DC
		return ClipRect(pRect,m_pRect);
	if(m_pWispWnd->m_pUpdateRect==NULL)
		return false;
	WISP_RECT UpdateRect = *m_pWispWnd->m_pUpdateRect;
	UpdateRect.x+=m_pWispWnd->m_ScrWindowRect.x;
	UpdateRect.y+=m_pWispWnd->m_ScrWindowRect.y;
	if(ClipRect(pRect,&UpdateRect)==false)
		return false;
	if(ClipRect(pRect,m_pRect)==false)
		return false;
	if(m_pWispWnd==(CWispBaseWnd*)m_pWispBase->m_pRootWnd)
		return true;
	pWnd=m_pWispWnd;
	pClipWnd=m_pWispWnd->m_ParentWnd;
	if(pClipWnd==NULL)
		pClipWnd = (CWispBaseWnd*)m_pWispBase->m_pRootWnd;
	while(pClipWnd)
	{
		if(pClipWnd->m_Style & WISP_WS_ADV_WND)
		{
			if(ClipRect(pRect,&((CWispWnd*)pClipWnd)->m_ScrClientRect)==false)
				return false;
		}
		else
		{//轻量级窗口
			if(ClipRect(pRect,&pClipWnd->m_ScrWindowRect)==false)
				return false;
		}
		pWnd=pWnd->m_ParentWnd;
		if(pWnd==NULL)
			break;
		pClipWnd=pWnd->m_ParentWnd;
	}
	return true;
}

bool CWispDC::ClipDCLine(INOUT int*pX1,INOUT int*pY1,INOUT int*pX2,INOUT int*pY2)
{
	CWispBaseWnd*pClipWnd,*pWnd;
	if(m_pClipRect && ClipLine(pX1,pY1,pX2,pY2,m_pClipRect)==false)
		return false;
	if(m_pWispWnd==NULL)//DIB DC
		return ClipLine(pX1,pY1,pX2,pY2,m_pRect);
	if(m_pWispWnd->m_pUpdateRect==NULL)
		return false;
	WISP_RECT UpdateRect = *m_pWispWnd->m_pUpdateRect;
	UpdateRect.x+=m_pWispWnd->m_ScrWindowRect.x;
	UpdateRect.y+=m_pWispWnd->m_ScrWindowRect.y;
	if(ClipLine(pX1,pY1,pX2,pY2,&UpdateRect)==false)
		return false;
	if(ClipLine(pX1,pY1,pX2,pY2,m_pRect)==false)
		return false;
	if(m_pWispWnd==(CWispBaseWnd*)m_pWispBase->m_pRootWnd)
		return true;
	pWnd=m_pWispWnd;
	pClipWnd=m_pWispWnd->m_ParentWnd;
	if(pClipWnd==NULL)
		pClipWnd = (CWispBaseWnd*)m_pWispBase->m_pRootWnd;
	while(pClipWnd)
	{
		if(pClipWnd->m_Style & WISP_WS_ADV_WND)
		{
			if(ClipLine(pX1,pY1,pX2,pY2,&((CWispWnd*)pClipWnd)->m_ScrClientRect)==false)
				return false;
		}
		else
		{//轻量级窗口
			if(ClipLine(pX1,pY1,pX2,pY2,&pClipWnd->m_ScrWindowRect)==false)
				return false;
		}
		pWnd=pWnd->m_ParentWnd;
		if(pWnd==NULL)
			break;
		pClipWnd=pWnd->m_ParentWnd;
	}
	return true;
}

bool CWispDC::ClipDCPoint(IN WISP_POINT*pPT)
{
	CWispBaseWnd*pClipWnd,*pWnd;
	if(m_pClipRect && PtInRect(m_pClipRect,pPT)==false)
		return false;
	if(m_pWispWnd==NULL)//DIB DC
		return PtInRect(m_pRect,pPT);
	if(m_pWispWnd->m_pUpdateRect==NULL)
		return false;
	WISP_RECT UpdateRect = *m_pWispWnd->m_pUpdateRect;
	UpdateRect.x+=m_pWispWnd->m_ScrWindowRect.x;
	UpdateRect.y+=m_pWispWnd->m_ScrWindowRect.y;
	if(PtInRect(&UpdateRect,pPT)==false)
		return false;
	if(PtInRect(m_pRect,pPT)==false)
		return false;
	if(m_pWispWnd==(CWispBaseWnd*)m_pWispBase->m_pRootWnd)
		return true;
	pWnd=m_pWispWnd;
	pClipWnd=m_pWispWnd->m_ParentWnd;
	if(pClipWnd==NULL)
		pClipWnd = (CWispBaseWnd*)m_pWispBase->m_pRootWnd;
	while(pClipWnd)
	{
		if(pClipWnd->m_Style & WISP_WS_ADV_WND)
		{
			if(PtInRect(&((CWispWnd*)pClipWnd)->m_ScrClientRect,pPT)==false)
				return false;
		}
		else
		{//轻量级窗口
			if(PtInRect(&pClipWnd->m_ScrWindowRect,pPT)==false)
				return false;
		}
		pWnd=pWnd->m_ParentWnd;
		if(pWnd==NULL)
			break;
		pClipWnd=pWnd->m_ParentWnd;
	}
	return true;
}

int CWispDC::DrawSingleLineText(IN WISP_CHAR* lpString,IN int nCount,INOUT WISP_RECT* lpRect,IN UINT uFormat)
{
	bool isClip = true;
	WISP_POINT beginDraw;
	int nRightSkipCharNum = 0;
	int nLeftSkipCharNum = 0;
	int nTopSkipLineNum = 0;
	int nBottomSkipLineNum = 0;
	int nMaxCharOfLine = 0;//给定的矩形区域
	int nMaxLine = 0;
	int nRealLen;
	int nCenterPos = 0;
	int nStrBeginPos = 0;
	int LeftOffset = -1, RightOffset = -1;
	WISP_CHAR* lpTmpString = NULL;
	WISP_CHAR chTextOutbuf[1025];
	int nRet = 0;

	nRealLen = (int)TStrLen(lpString);	
	if(nCount == -1 || nCount > nRealLen)
		nCount = nRealLen;
	if(!nCount)
		return nCount;
	nCenterPos = lpRect->x + lpRect->cx / 2;
	if(uFormat & WISP_DT_NOCLIP)//为非裁剪的调整矩形
	{
		isClip = false;
		if(uFormat & WISP_DT_RIGHT)//如果是非裁减则右对齐的话则调整  x  到 DC 的最左边。
		{
				lpRect->cx += lpRect->x;
				lpRect->x =0;
		}
		else
		{
			if(uFormat & WISP_DT_CENTER)
			{				
				lpRect->x =0;
				lpRect->cx =m_pRect->cx;
			}
			else
			{
				if(lpRect->x + lpRect->cx  < m_pRect->cx)////如果是非裁减则左对齐的话则调整  cx  到 DC 的最右边。
				{
					lpRect->cx =m_pRect->cx - lpRect->x;
				}				 
			}
		}
	}
	if(uFormat & WISP_DT_SINGLELINE)
	{
		beginDraw.x = lpRect->x;
		beginDraw.y = lpRect->y;
		if(uFormat & WISP_DT_VCENTER)//处理垂直中间对齐。
		{
			beginDraw.y = lpRect->y + lpRect->cy / 2 - m_pFont->m_Height / 2;
		}
		else
		{
			if(uFormat & WISP_DT_BOTTOM)//处理底边对齐
			{
				beginDraw.y = lpRect->y + lpRect->cy - m_pFont->m_Height;			
			}
		}
		
		if(uFormat & WISP_DT_RIGHT)//横向对齐属性处理。
		{
			beginDraw.x = lpRect->x + lpRect->cx;
		}
		else
		{
			if(uFormat & WISP_DT_CENTER)//分成3种情况  第一种是给定的矩形区域的中心点的 x 轴坐标在  DC 的矩形的左边。
										//	           第一种是给定的矩形区域的中心点的 x 轴坐标在  DC 的矩形的右边。
										//	           第一种是给定的矩形区域的中心点的 x 轴坐标在  DC 的矩形的范围内。
			
			{					
				nStrBeginPos = (nRealLen - nCount) / 2;
				beginDraw.x = nCenterPos - nCount / 2 * m_pFont->m_Width;
				if(nCount % 2)
				{
					beginDraw.x = beginDraw.x - m_pFont->m_Width / 2;
				}
			}else
			{				
				nStrBeginPos = 0;
			}						
		}

		lpTmpString = chTextOutbuf;
		if(nRealLen - nStrBeginPos < nCount)
		{
			nCount = nRealLen - nStrBeginPos+1;
		}

		if(nCount >= 1025)
			nCount = 1023;
		TStrNCpy(lpTmpString, lpString+nStrBeginPos, nCount);
		lpTmpString[nCount] = 0;	
		if(uFormat & WISP_DT_RIGHT)
			DrawRightString(beginDraw.x, beginDraw.y, lpTmpString,nCount);
		else
		DrawString(beginDraw.x, beginDraw.y, lpTmpString,nCount);
	}	
	return nRet;
}

//画扩展系统按钮
void CWispDC::DrawSystemStandardIcon(const WISP_RECT&rcBoundary, UINT uStyle, COLORREF color)
{
	m_pWispBase->m_pCurDrawObj->DrawSystemStandardIcon(this, &rcBoundary, uStyle);
}


int	CWispDC::PixelOffToTextOff(const WISP_CHAR* pString,int PixelOff)
{
	int cx,Index,Count,Length,Width;
	if(pString == NULL)
		return -1;
	Index = 0;
	if(IsColorString(pString))
	{
		const WISP_COLOR_CHAR*pStr = GetColorString(pString);
		Length = TStrLen(pStr);
		cx=0;
		for(int i = 0; i < Length; i++)
		{
			switch((WISP_CHAR)pStr[i])
			{
			case WISP_STR('\n'):
				break;
			case WISP_STR('\t'):
				Count = m_TabAlign - Index % m_TabAlign;
				Width = m_pFont->GetCharWidth(WISP_STR(' '))*Count;
				cx += Width;
				Index += Count;
				break;
			default:
				Width = m_pFont->GetCharWidth((WISP_CHAR)pStr[i]);
				cx += Width;
				Index++;
				break;
			}
			if(PixelOff>=cx-Width && PixelOff<cx)
				return i;
		}
	}
	else
	{
		Length = TStrLen(pString);
		cx=0;
		for(int i = 0; i < Length; i++)
		{
			switch(pString[i])
			{
			case WISP_STR('\n'):
				break;
			case WISP_STR('\t'):
				Count = m_TabAlign - Index % m_TabAlign;
				Width = m_pFont->GetCharWidth(WISP_STR(' '))*Count;
				cx += Width;
				Index += Count;
				break;
			default:
				Width = m_pFont->GetCharWidth(pString[i]);
				cx += Width;
				Index++;
				break;
			}
			if(PixelOff>=cx-Width && PixelOff<cx)
				return i;
		}
	}
	return -1;
}

int	CWispDC::GetTextExtent(const WISP_CHAR* pString, int Length,int Index)
{
	int cx,Count;
	if(pString == NULL)
		return 0;
	if(IsColorString(pString))
	{
		const WISP_COLOR_CHAR*pStr = GetColorString(pString);
		if(Length == -1)
			Length = TStrLen(pStr);
		cx=0;
		for(int i = 0; i < Length; i++)
		{
			switch((WISP_CHAR)pStr[i])
			{
			case WISP_STR('\n'):
				break;
			case WISP_STR('\t'):
				Count = m_TabAlign - Index % m_TabAlign;
				cx+=m_pFont->GetCharWidth(WISP_STR(' '))*Count;
				Index+=Count;
				break;
			default:
				cx+=m_pFont->GetCharWidth((WISP_CHAR)pStr[i]);
				Index++;
				break;
			}
		}
	}
	else
	{
		if(Length == -1)
			Length = TStrLen(pString);
		cx=0;
		for(int i = 0; i < Length; i++)
		{
			switch(pString[i])
			{
			case WISP_STR('\n'):
				break;
			case WISP_STR('\t'):
				Count = m_TabAlign - Index % m_TabAlign;
				cx+=m_pFont->GetCharWidth(WISP_STR(' '))*Count;
				Index+=Count;
				break;
			default:
				cx+=m_pFont->GetCharWidth(pString[i]);
				Index++;
				break;
			}
		}
	}
	return cx;
}

int	CWispDC::GetTextHeight(const WISP_CHAR Char)
{
	return m_pFont->m_Height;
}

int CWispDC::DrawString(IN WISP_CHAR* lpString,INOUT WISP_RECT* lpRect,IN UINT uFormat,IN UINT nShowLen,IN int nPreLineMaxCharNum)
{
	struct stShowString
	{
		int coordinateX;
		WISP_CHAR *ShowString;
		int nShowLen;
		int nPixelWidth;
	}ShowString[4];
#define TABEXPENDLEN 9
	int nStringRealLen = 0, nTabCharLen = 8, nRet = 0, nTabCharCounter = 0;
	int nEllipsesBegineOffset;
	WISP_CHAR EllipsesArray[2]={0,0};
	int nLineNum = 0, i, j, nTmp, nMaxShowCharNum = 0;
	int nCurrentMaxLineCharNum = 0;
	int nTabExpandLen = 0,nCenterPos = 0;
	int nCharAverageWidth = 6;
	int nCharAverageHigh = GetTextHeight(WISP_CHAR("A"));
	int nTabPixelWidth = nCharAverageWidth;
	int nRightSkipCharNum = 0, nLeftSkipCharNum = 0;
	WISP_RECT rc;
	WISP_CHAR *ellipsis = WISP_STR("...");
	int EllipsisStringPixelWidth;
	//WISP_CHAR TabExpendString[TABEXPENDLEN];
	//int TabExpendStringPixelWidth;
	//	int nFileNameCorrdinateX;
	int nEllipsesCoordinateX;
	WISP_CHAR* PathName = NULL;
	int nPathStrLen;//目录名串的字符的个数
	int nPathShowStrLen;//目录名串要显示的字符的个数
	WISP_CHAR *FileName=NULL;
	int nFileNameStrLen;
	int nShowStringCounter = 1;//显示一个单行的串要分几次显示，最多是 四次  第一次是显示目录名部分，第二次是省略号，第三次是文件名，第四次是省略号
	bool isClip = true;
	int x,y;
	WISP_CHAR *pShowString = NULL;

	if(lpString != NULL)
		nStringRealLen = TStrLen(lpString);
	if(nStringRealLen == 0)
		return nRet;
	if(nShowLen != 0 && nShowLen < (UINT)nStringRealLen)
		nStringRealLen = nShowLen;
	rc = *lpRect;
	if(uFormat & WISP_DT_EXPANDTABS)//计算 TAB 字符的扩展象素宽度
	{
		if(uFormat & WISP_DT_TABSTOP)
		{
			nTabCharLen = (0xff00 & uFormat) >> 8;
			uFormat = uFormat & ~(WISP_DT_CALCRECT | WISP_DT_EXTERNALLEADING | WISP_DT_INTERNAL | WISP_DT_NOCLIP | WISP_DT_NOPREFIX);		
		}
		if(nTabCharLen == 0)
			nTabCharLen = 8;
		nTabPixelWidth = nTabCharLen * nCharAverageWidth;
		//uFormat = uFormat & ~(WISP_DT_END_ELLIPSIS | WISP_DT_PATH_ELLIPSIS | WISP_DT_EDITCONTROL | WISP_DT_WORD_ELLIPSIS);	
	}	
	nLineNum = CalcTextLineNum(lpString,nStringRealLen);
	if(uFormat & WISP_DT_CALCRECT)	
		return CalcDrawTextRect(lpString,lpRect,nStringRealLen, uFormat, nTabPixelWidth);
	nCenterPos = lpRect->x + lpRect->cx / 2;
	if(uFormat & (WISP_DT_END_ELLIPSIS | WISP_DT_WORD_ELLIPSIS | WISP_DT_PATH_ELLIPSIS))
		EllipsisStringPixelWidth = GetTextExtent(ellipsis);
	if(uFormat & WISP_DT_NOCLIP)//为非裁剪的调整矩形	
		AdjustNoClipRect(&rc,uFormat);			

	if(uFormat & WISP_DT_SINGLELINE)
	{
		if(rc.x + rc.cx < 0 || rc.x > m_pRect->cx) //不在显示区域中
			return nCharAverageHigh;
		x = rc.x;
		y =	rc.y;
		int nStringPixelWidth;

		if(uFormat & WISP_DT_EXPANDTABS)//计算要显示的字符串的象素长度
			nStringPixelWidth = GetTextExtentTabExpend(lpString,nTabPixelWidth,nStringRealLen);
		else
			nStringPixelWidth = GetTextExtent(lpString,nStringRealLen);

		if(uFormat & WISP_DT_RIGHT) // WISP_DT_RIGHT
			x = rc.x + rc.cx - nStringPixelWidth;
		else if(uFormat & WISP_DT_CENTER) // WISP_DT_CENTER
			x = nCenterPos - nStringPixelWidth / 2;	
		if(uFormat & WISP_DT_VCENTER)//处理垂直中间对齐。
			y = rc.y + rc.cy / 2 - nCharAverageHigh / 2;
		else if(uFormat & WISP_DT_BOTTOM)//处理底边对齐
			y = rc.y + rc.cy - nCharAverageHigh;	
		ShowString[0].coordinateX = x;
		ShowString[0].ShowString = lpString;
		ShowString[0].nShowLen = nStringRealLen;
		ShowString[0].nPixelWidth = nStringPixelWidth;
		if(nStringPixelWidth > rc.cx)
		{			
			if(uFormat & WISP_DT_PATH_ELLIPSIS)
			{
				int nFileNamePixelWidth;
				int nPathNamePixelWidth;

				for(j = 1,i = nStringRealLen - 2; i >= 0; i--,j++)//要跳过最后一个字符 
				{
					if(lpString[i] == PATH_SEPARATOR_CHAR)
					{
						FileName = &lpString[i];
						nPathStrLen = i;
						if(nPathStrLen < 3)
							goto local_2;
						if(i)
							PathName = lpString;
						else
							PathName = NULL;
						j++;
						break;
					}
				}
				nFileNameStrLen = j;
				if(FileName != NULL && nPathStrLen > 3)
				{
					if(uFormat & WISP_DT_EXPANDTABS)
						nFileNamePixelWidth = GetTextExtentTabExpend(FileName,nStringPixelWidth,j);
					else
						nFileNamePixelWidth = GetTextExtent(FileName,j);
					if(nFileNamePixelWidth + EllipsisStringPixelWidth < rc.cx)
					{
						nTmp = rc.cx - nFileNamePixelWidth - EllipsisStringPixelWidth;//计算显示路径名的最大宽度

						if(uFormat & WISP_DT_EXPANDTABS)
						{
							i = GetMaxShowCharNum(PathName,nTmp,nTabPixelWidth,nPathStrLen);
							nPathNamePixelWidth = GetTextExtentTabExpend(PathName,nStringPixelWidth,i);
							nTmp = nTmp - nPathNamePixelWidth;
						}
						else
						{
							i = GetMaxShowCharNum(PathName,nTmp,0,nPathStrLen);
							nPathNamePixelWidth = GetTextExtent(PathName,i);
							nTmp = nTmp - nPathNamePixelWidth;
						}
						nPathShowStrLen = i;
						if(nPathStrLen - nPathShowStrLen < 3)//判断显示不下的字符是否超过了 3 个
						{
							goto local_2;
						}

						if(uFormat & WISP_DT_RIGHT)
							x += nTmp;
						else if(uFormat & WISP_DT_CENTER)
							x += nTmp / 2;
						ShowString[0].coordinateX = x;
						ShowString[0].ShowString = PathName;
						ShowString[0].nShowLen = nPathShowStrLen;
						ShowString[0].nPixelWidth = nPathNamePixelWidth;

						ShowString[1].coordinateX = x + nPathNamePixelWidth;
						ShowString[1].ShowString = ellipsis;
						ShowString[1].nShowLen = 3;
						ShowString[1].nPixelWidth = EllipsisStringPixelWidth;

						ShowString[2].coordinateX = ShowString[1].coordinateX + EllipsisStringPixelWidth;
						ShowString[2].ShowString = FileName;
						ShowString[2].nShowLen = nFileNameStrLen;
						ShowString[2].nPixelWidth = nFileNamePixelWidth;
						nShowStringCounter = 3;

					}
					else
					{
						if(uFormat & WISP_DT_RIGHT)
						{
							x = rc.cx + rc.x - nFileNamePixelWidth;
						}else if(uFormat & WISP_DT_CENTER)
						{
							x = nCenterPos + nFileNamePixelWidth / 2;
						}	

						ShowString[0].coordinateX = x;
						ShowString[0].ShowString = ellipsis;
						ShowString[0].nShowLen = 3;
						ShowString[0].nPixelWidth = EllipsisStringPixelWidth;

						ShowString[1].coordinateX = x + EllipsisStringPixelWidth;
						ShowString[1].ShowString = FileName;
						ShowString[1].nShowLen = nFileNameStrLen;
						ShowString[1].nPixelWidth = nFileNamePixelWidth;
						nShowStringCounter = 2;
					}	
					if(uFormat & WISP_DT_MODIFYSTRING)
					{

						PathName[nPathShowStrLen] = 0x2e;
						PathName[nPathShowStrLen+1] = 0x2e;
						PathName[nPathShowStrLen+2] = 0x2e;
						for(i = 0; i < nFileNameStrLen;i++)
							PathName[nPathShowStrLen+3+i] = FileName[i];
						FileName[i] = 0;
					}
				}				
local_2:					
				;
			}else
				if(uFormat & WISP_DT_END_ELLIPSIS)
				{
					if(uFormat & (WISP_DT_RIGHT | WISP_DT_CENTER))			
						nTmp = rc.cx - EllipsisStringPixelWidth;
					else				
						nTmp = rc.cx - EllipsisStringPixelWidth / 2 + 1;
					if(uFormat & WISP_DT_EXPANDTABS)
					{
						i = GetMaxShowCharNum(lpString,nTmp,nStringRealLen,nTabPixelWidth);
						nEllipsesCoordinateX = GetTextExtentTabExpend(lpString,nStringPixelWidth,i);
						nTmp = nTmp - nEllipsesCoordinateX;
					}
					else
					{
						i = GetMaxShowCharNum(lpString,nTmp,nStringRealLen);
						nEllipsesCoordinateX = GetTextExtent(lpString,i);
						nTmp = nTmp - nEllipsesCoordinateX;
					}				
					if(uFormat & WISP_DT_RIGHT)
						x += nTmp;
					else if(uFormat & WISP_DT_CENTER)
						x = x + nTmp / 2;
					nEllipsesBegineOffset = i;
					ShowString[nShowStringCounter].coordinateX = ShowString[0].coordinateX;
					if(uFormat & WISP_DT_PATH_ELLIPSIS)
					{
						for(j = 0; j < nShowStringCounter;j++)
						{
							ShowString[nShowStringCounter].coordinateX += ShowString[j].nPixelWidth;
						}	
					}
					else
					{
						ShowString[0].coordinateX = x;
						ShowString[nShowStringCounter].coordinateX +=nEllipsesCoordinateX;
						ShowString[0].nShowLen = nEllipsesBegineOffset;
					}
					ShowString[nShowStringCounter].ShowString = ellipsis;
					ShowString[nShowStringCounter].nShowLen = 3;
					ShowString[nShowStringCounter].nPixelWidth = EllipsisStringPixelWidth;
					nShowStringCounter++;
					if(uFormat & WISP_DT_MODIFYSTRING)
					{									
						for(j = i; j < i + 3 && j < nStringRealLen; j++)
							lpString[j] = 0x2e;
					}
				}else if(uFormat & WISP_DT_WORD_ELLIPSIS)
				{
				}
		}
		if(uFormat & WISP_DT_EXPANDTABS)
		{	
			for(i = 0; i < nShowStringCounter;i++)
				DrawTabExpendString(ShowString[i].coordinateX,y,ShowString[i].ShowString, ShowString[i].nShowLen,rc,nTabPixelWidth);
		}
		else
		{
			for(i = 0; i < nShowStringCounter;i++)
				DrawString(ShowString[i].coordinateX,y,ShowString[i].ShowString, ShowString[i].nShowLen);
		}
		return nCharAverageHigh;
	}else  //if(uFormat & WISP_DT_SINGLELINE)如果是多行则
	{
		int nBeginOffset = 0;
		int nWriteByte = nStringRealLen;
		int n;
		int nShowLineNum = 0;
		bool bFlags = true;

		if(uFormat & WISP_DT_VCENTER)
		{
			if(rc.cy >(nLineNum * nCharAverageHigh))
			{
				rc.y = rc.y+(rc.cy - ((nLineNum)* nCharAverageHigh)) / 2;
			}			
			uFormat &= ~WISP_DT_VCENTER;	
		}
		uFormat &= ~WISP_DT_BOTTOM;
		uFormat |= WISP_DT_SINGLELINE;
		//nShowLen
		for(nTmp = 0,i = 0; i < nLineNum; i++,nShowLineNum++)
		{
			n = nTmp;
			for(j = 0;nTmp < nStringRealLen && lpString[nTmp] != '\r' && lpString[nTmp] != '\n';nTmp++,j++);
			if(j == 0)
			{
				if(nTmp < nStringRealLen)
					goto local_1;
				else
					break;
			}
			else
			{
				if(nWriteByte <= 0)
					break;
				if(j > nWriteByte)
					j = nWriteByte;
				nWriteByte -= j;

				if(uFormat & WISP_DT_EXPANDTABS)
					nBeginOffset = GetTextExtentLineTabExpend(&lpString[n],nTabPixelWidth,j);
				else
					nBeginOffset = GetTextExtent(&lpString[n],j);
				if(uFormat & WISP_DT_AUTONEWLINE)
				{
					if(nBeginOffset > lpRect->cx)
					{
						int l;
						for(; j > 0; )
						{
							if(uFormat & WISP_DT_EXPANDTABS)
								l = GetMaxShowCharNum(&lpString[n],lpRect->cx,nTabPixelWidth,j);
							else
								l = GetMaxShowCharNum(&lpString[n],lpRect->cx,0,j);
							DrawString((WISP_CHAR*)&lpString[n], &rc, uFormat, l);
							n+=l;	
							j -= l;

							nShowLineNum++;
							if(j !=0)
							{
								rc.y += nCharAverageHigh;
								rc.cy -= nCharAverageHigh;
							}
							if(rc.cy <= 0)
								break;
						}				
						nShowLineNum--;
					}
				}else if(uFormat & WISP_DT_MAXCHAR)
				{			

					for(;j >= nPreLineMaxCharNum;)
					{
						DrawString((WISP_CHAR*)&lpString[n], &rc, uFormat, nPreLineMaxCharNum);
						n+=nPreLineMaxCharNum;
						j -= nPreLineMaxCharNum;
						nShowLineNum++;
						if(j != 0)
						{
							rc.y += nCharAverageHigh;
							rc.cy -= nCharAverageHigh;
						}
						if(rc.cy <= 0)
							break;
					}
					if(j == 0)
						nShowLineNum--;
				}

				if(j)
					DrawString((WISP_CHAR*)&lpString[n], &rc, uFormat, j);
			}
local_1:
			nTmp++;	
			if(nTmp > nStringRealLen)
				break;
			nWriteByte--;
			if(lpString[nTmp] == '\n' || lpString[nTmp] == '\r')
				if(lpString[nTmp-1] != lpString[nTmp])
				{
					nTmp++;
					nWriteByte--;
				}

				rc.y += nCharAverageHigh;
				rc.cy -= nCharAverageHigh;
				if(rc.cy <= 0)
					break;
		}
		//local_3:
		return nShowLineNum * nCharAverageHigh;
	}
	return 0;
}

int	CWispDC::GetTextExtentTabExpend(const WISP_CHAR* lpString,int nTabPixelWidth,int nCount)
{
	int i,nRetLen = 0,nTmp;
	CODE_ASSERT(nTabPixelWidth);
	if(nCount == -1)
		nCount = TStrLen(lpString);
	for (i = 0; i < nCount; i++)
	{
		if(lpString[i] >= 0x100)
			nRetLen += 16;
		else
		{
			if(lpString[i] != '\t')
				nRetLen+=m_pFont->m_CharLenAry[lpString[i]];
			else
			{
				nTmp = nRetLen % nTabPixelWidth;
				nRetLen = nRetLen + nTabPixelWidth - nTmp;
			}
		}
	}

	return nRetLen;
}

int	CWispDC::GetTextExtentLineTabExpend(const WISP_CHAR* lpString,int nTabPixelWidth,int nCount)
{
	int i,nRetLen = 0,nTmp;
	CODE_ASSERT(nTabPixelWidth);
	if(nCount == -1)
		nCount = TStrLen(lpString);
	for (i = 0; i < nCount; i++)
	{
		if(lpString[i] == '\n' || lpString[i] == '\r')
			break;
		if(lpString[i] >= 0x100)
			nRetLen += 16;
		else
		{
			if(lpString[i] != '\t')
				nRetLen+=m_pFont->m_CharLenAry[lpString[i]];
			else
			{
				nTmp = nRetLen % nTabPixelWidth;
				nRetLen = nRetLen + nTabPixelWidth - nTmp;
			}
		}
	}
	return nRetLen;
}
int CWispDC::CalcTextLineNum(WISP_CHAR *lpString,int nCount)
{
	int i,j,nLineNum = 0,nTmp,nIsMutleLines=0;
/*
	for(i = 0; i < nCount; i++)
	{
		if(lpString[i] == '\r' || lpString[i] == '\n')
		{
			nIsMutleLines=1;
			break;
		}
	}
	if(nIsMutleLines == 0)
		return 1;
*/
	for(nTmp = 0,i = 0; i < nCount; i++)
	{
		for(j = 0;nTmp < nCount && lpString[nTmp] != '\r' && lpString[nTmp] != '\n';nTmp++,j++);		
		if(j == 0)
		{
			if(nTmp < nCount)
				nLineNum++;				
			else
				break;
		}
		else
		{
			nLineNum++;			
		}
		nTmp++;
		if(nTmp >= nCount)
			break;
		else
		{
			if(lpString[nTmp] == '\n' || lpString[nTmp] == '\r')
				if(lpString[nTmp - 1] != lpString[nTmp])
					nTmp++;
		}	
	}	
//	nLineNum++;	
	return nLineNum;
}


int CWispDC::CalcDrawTextRect(WISP_CHAR *lpString,WISP_RECT *lpRect,int nStrLen,UINT uFormat, int nTabPixelWidth)
{
	int nCharAverageHigh = m_pFont->m_Height,nTmp,nCurrentMaxLineCharNum = 0;
	int i,j,nLineNum = 0,m;
	if(uFormat & WISP_DT_SINGLELINE)
	{			
		if(uFormat & WISP_DT_EXPANDTABS)
			lpRect->cx = GetTextExtentTabExpend(lpString,nTabPixelWidth,nStrLen);
		else
			lpRect->cx = GetTextExtent(lpString,nStrLen);
		lpRect->cy = nCharAverageHigh;
	}
	else
	{			
		for(i = 0; i < nStrLen;)
		{
			m = i;
			for(j = 0;i < nStrLen && lpString[i] != '\r' && lpString[i] != '\n';i++,j++);
			if(j == 0)
			{
				if(i < nStrLen)
					nLineNum++;				
				else
					break;
			}
			else
			{
				nLineNum++;	
			}

			if(uFormat & WISP_DT_EXPANDTABS)
				nTmp = GetTextExtentLineTabExpend(&lpString[m],nTabPixelWidth,j);
			else
				nTmp = GetTextExtent(&lpString[m],j);		
			if(uFormat & WISP_DT_AUTONEWLINE)
			{
				if(nTmp > lpRect->cx)
				{
					int l;
					
					for(; j > 0; j -= l)
					{
						l = GetMaxShowCharNum(&lpString[m],lpRect->cx,0,j);
						nLineNum++;
						m+=l;
					}
					nLineNum--;
				}
			}
			if(nCurrentMaxLineCharNum < nTmp)
				nCurrentMaxLineCharNum = nTmp;
			i++;
			if(i >= nStrLen)
				break;
			else
			{
				if(lpString[i] == '\n' || lpString[i] == '\r')
					if(lpString[i - 1] != lpString[i])
						i++;
			}
		}
		lpRect->cy = nLineNum * nCharAverageHigh;
		lpRect->cx = nCurrentMaxLineCharNum;
	}
	return lpRect->cy;
}

void CWispDC::AdjustNoClipRect(INOUT WISP_RECT *lpRect,UINT uFormat)
{
	if(uFormat & WISP_DT_RIGHT)//如果是非裁减则右对齐的话则调整  x  到 DC 的最左边。
	{
		if(lpRect->x > 0)
		{
			lpRect->cx += lpRect->x;
			lpRect->x =0;
		}
	}
	else
	{
		if(uFormat & WISP_DT_CENTER)
		{				
			if(lpRect->x > 0)
			{
				lpRect->cx += lpRect->x;
				lpRect->x =0;					
			}
			if(lpRect->x + lpRect->cx < m_pRect->cx)
				lpRect->cx =lpRect->cx + m_pRect->cx - (lpRect->x + lpRect->cx);					
		}
		else//WISP_DT_LEFT
			if(lpRect->x + lpRect->cx  < m_pRect->cx)////如果是非裁减则左对齐的话则调整  cx  到 DC 的最右边。
				lpRect->cx =m_pRect->cx - lpRect->x;
	}
}

int CWispDC::GetMaxShowCharNum(WISP_CHAR *lpString,int nMaxWidth,  int nTabPixelWidth,int nCount)
{
	int sum = 0,i,nTmp;
	CODE_ASSERT(lpString);
	if(nCount == -1)
		nCount = TStrLen(lpString);
	if(nTabPixelWidth)
	{
		for(i = 0; i < nCount; i++)
		{
			if(lpString[i] != '\t')
			{
				nTmp =  GetTextExtent(&lpString[i],1);
			}
			else
			{
				nTmp = nTabPixelWidth - sum % nTabPixelWidth;
			}
			if(sum + nTmp < nMaxWidth)
				sum += nTmp;
			else
			{
				if(lpString[i] == '\t')
					i++;
				break;
			}			
		}
	}
	else
	{
		for(i = 0; i < nCount; i++)
		{
			nTmp = GetTextExtent(&lpString[i],1);
			if(sum + nTmp < nMaxWidth)
				sum += nTmp;
			else
				break;
		}
	}
	return i;
}


#define		TABEXPENDLEN	9

int CWispDC::DrawTabExpendString(int x, int y, WISP_CHAR *lpString,int nStringRealLen,WISP_RECT rc,int nTabPixelWidth )
{
	WISP_CHAR TabExpendString[TABEXPENDLEN];
	int TabExpendStringPixelWidth;
	int k ,i ,j ,n = 0,nStartx, nTmp;
	for(i = 0; i < TABEXPENDLEN; i++)
		TabExpendString[i] = ' ';
	TabExpendString[TABEXPENDLEN-1] = 0;
	TabExpendStringPixelWidth = GetTextExtent(TabExpendString);
	nStartx = x;
	for(i = 0; i < nStringRealLen; i++)
	{
		nTmp = i;
		for(j = 0; i < nStringRealLen && lpString[i] != '\t'; i++,j++);		
		n = GetTextExtent(&lpString[nTmp],j);
		if(x + n >= 0 && x <= m_pRect->cx)
			DrawString(x,y,&lpString[nTmp],j);
		else
			break;
		x += n;
		k = nTabPixelWidth - (x - nStartx) % nTabPixelWidth;
		nTmp = (k + TabExpendStringPixelWidth - 1) / TabExpendStringPixelWidth;
		k = x + k;
		for(j = 0; j < nTmp; j++,x += TabExpendStringPixelWidth)
		{	
			if(x + TabExpendStringPixelWidth >= 0 && x <= m_pRect->cx)
				DrawString(x,y,TabExpendString,-1);
			else
				break;
		}
		x = k;				
	}
	return 0;
}

void CWispDC::CirclePlotPoints(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect)
{
	if(PtInRect(pClipRect,xCenter+x,yCenter-y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+x,yCenter-y,color);//TRT
	if(PtInRect(pClipRect,xCenter+y,yCenter-x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+y,yCenter-x,color);//TRB
	if(PtInRect(pClipRect,xCenter+y,yCenter+x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+y,yCenter+x,color);//BRT
	if(PtInRect(pClipRect,xCenter+x,yCenter+y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+x,yCenter+y,color);//BRB
	if(PtInRect(pClipRect,xCenter-x,yCenter+y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-x,yCenter+y,color);//BLB
	if(PtInRect(pClipRect,xCenter-y,yCenter+x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-y,yCenter+x,color);//BLT
	if(PtInRect(pClipRect,xCenter-y,yCenter-x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-y,yCenter-x,color);//TLB
	if(PtInRect(pClipRect,xCenter-x,yCenter-y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-x,yCenter-y,color);//TLT
}

void CWispDC::CirclePlotPointsRightTop(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect)
{
	if(PtInRect(pClipRect,xCenter+x,yCenter-y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+x,yCenter-y,color);//TRT
	if(PtInRect(pClipRect,xCenter+y,yCenter-x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+y,yCenter-x,color);//TRB
}

void CWispDC::CirclePlotPointsRightBottom(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect)
{
	if(PtInRect(pClipRect,xCenter+y,yCenter+x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+y,yCenter+x,color);//BRT
	if(PtInRect(pClipRect,xCenter+x,yCenter+y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter+x,yCenter+y,color);//BRB		
}

void CWispDC::CirclePlotPointsLeftTop(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect)
{
	if(PtInRect(pClipRect,xCenter-y,yCenter-x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-y,yCenter-x,color);//TLB
	if(PtInRect(pClipRect,xCenter-x,yCenter-y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-x,yCenter-y,color);//TLT
}

void CWispDC::CirclePlotPointsLeftBottom(int xCenter,int yCenter,int x,int y,COLORREF color,WISP_RECT*pClipRect)
{
	if(PtInRect(pClipRect,xCenter-x,yCenter+y))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-x,yCenter+y,color);//BLB
	if(PtInRect(pClipRect,xCenter-y,yCenter+x))
		m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,xCenter-y,yCenter+x,color);//BLT
}

int CWispDC::DrawString(IN CWispFont*pLogFont,IN int x,IN int y,IN const WISP_CHAR*pStr,IN COLORREF TextColor,IN WISP_RECT*pClipRect,IN COLORREF*pBKColor,IN int Length,IN int Index,int Flags)
{
	BYTE*pFont;
	int Width,n,i,j,BitOffset,OrgX;
	WISP_CHAR szText[MAX_TAB_ALIGN];
	OrgX = x;
	while(Length && *pStr)
	{
		if(Flags)
		{
			szText[0]=*pStr;
			szText[1]=0;
		}
		else
		{
			switch(*pStr)
			{
			case WISP_STR('\n'):
				return x - OrgX;
			case WISP_STR('\t'):
				n = m_TabAlign - Index % m_TabAlign;
				szText[n]=0;
				do
				{
					n--;
					szText[n]=WISP_STR(' ');
				}while(n>0);
				break;
			default:
				szText[0]=*pStr;
				szText[1]=0;
				break;
			}
		}

		for(n=0;szText[n];n++)
		{
			pFont=pLogFont->GetCharPixelBuffer(szText[n]);
			Width=pLogFont->GetCharWidth(szText[n]);
			BitOffset=0;
			for(j=0;j<pLogFont->m_Height;j++)
			{
				for(i=0;i<Width;i++)
				{
					if(PtInRect(pClipRect,x+i,y+j))
					{
						if((pFont[BitOffset/8]>>(BitOffset%8)) & 1)
							m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x+i,y+j,TextColor);
						else if(pBKColor)
							m_pFrameBuffer->pDrawHAL->DrawPixel(m_pFrameBuffer,x+i,y+j,*pBKColor);
					}
					BitOffset++;
				}
			}
			x+=Width;
			Index++;
		}
		pStr++;
		Length--;
	}
	return x - OrgX;
}

