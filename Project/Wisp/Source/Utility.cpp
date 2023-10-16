#include "StdAfx.h"
#include "Utility.h"

//	点是否在矩形区域内
bool PtInRect(IN const WISP_RECT *pRect, IN int x, int y)
{
	return	pRect->cx >0 && pRect->cy >0 && x >= pRect->x && y >= pRect->y && x <  pRect->x + pRect->cx && y <  pRect->y + pRect->cy;
}

bool PtInRect(IN  WISP_RECT *pRect,const IN WISP_POINT*pPoint)
{
	return	pRect->cx >0 && pRect->cy >0 && 
			pPoint->x >= pRect->x && pPoint->y >= pRect->y &&
			pPoint->x <  pRect->x + pRect->cx && pPoint->y <  pRect->y + pRect->cy;
}

bool PtInRect(IN  WISP_RECT *pRect,const IN WISP_POINT &Point)
{
	return	pRect->cx >0 && pRect->cy >0 && 
			Point.x >= pRect->x && Point.y >= pRect->y &&
			Point.x <  pRect->x + pRect->cx && Point.y <  pRect->y + pRect->cy;
}

void PointToRect(INOUT WISP_POINT*pPoint,IN WISP_RECT*pRect)
{
	pPoint->x-=pRect->x;
	pPoint->y-=pRect->y;
}

void RectToRect(INOUT WISP_RECT*pRect,IN WISP_RECT*pToRect)
{
	pRect->x-=pToRect->x;
	pRect->y-=pToRect->y;
}

void PointSpliceRect(INOUT WISP_POINT*pPoint,IN WISP_RECT*pRect)
{
	pPoint->x+=pRect->x;
	pPoint->y+=pRect->y;
}

bool IsInvalidRect(IN WISP_RECT*pRect)
{
	return pRect->cx<=0 || pRect->cy<=0;
}

bool ClipLine(INOUT int*pX1,INOUT int*pY1,INOUT int*pX2,INOUT int*pY2,IN WISP_RECT*pRect)
{
	if(*pX1==*pX2)
		return ClipVLine(pX1,pY1,pY2,pRect);
	if(*pY1==*pY2)
		return ClipHLine(pX1,pX2,pY1,pRect);

	if(*pX1<pRect->x && *pX2<pRect->x)
		return false;
	if(*pX1>=pRect->x+pRect->cx && *pX2>=pRect->x+pRect->cx)
		return false;
	if(*pY1<pRect->y && *pY2<pRect->y)
		return false;
	if(*pY1>=pRect->y+pRect->cy && *pY2>=pRect->y+pRect->cy)
		return false;

	int dx,dy,l;
	dx = *pX2 - *pX1;
	dy = *pY2 - *pY1;

	if(*pX1<pRect->x)
	{
		l=pRect->x-*pX1;
		*pX1=pRect->x;
		*pY1+=((dy<<16)/dx*l)>>16;
	}
	else if(*pX1>=pRect->x+pRect->cx)
	{
		l=pRect->x+pRect->cx-1-*pX1;
		*pX1=pRect->x+pRect->cx-1;
		*pY1+=((dy<<16)/dx*l)>>16;
	}
	if(*pX2<pRect->x)
	{
		l=pRect->x-*pX2;
		*pX2=pRect->x;
		*pY2+=((dy<<16)/dx*l)>>16;
	}
	else if(*pX2>=pRect->x+pRect->cx)
	{
		l=pRect->x+pRect->cx-1-*pX2;
		*pX2=pRect->x+pRect->cx-1;
		*pY2+=((dy<<16)/dx*l)>>16;
	}
	if(*pY1<pRect->y)
	{
		l=pRect->y-*pY1;
		*pY1=pRect->y;
		*pX1+=((dx<<16)/dy*l)>>16;
	}
	else if(*pY1>=pRect->y+pRect->cy)
	{
		l=pRect->y+pRect->cy-1-*pY1;
		*pY1=pRect->y+pRect->cy-1;
		*pX1+=((dx<<16)/dy*l)>>16;
	}
	if(*pY2<pRect->y)
	{
		l=pRect->y-*pY2;
		*pY2=pRect->y;
		*pX2+=((dx<<16)/dy*l)>>16;
	}
	else if(*pY2>=pRect->y+pRect->cy)
	{
		l=pRect->y+pRect->cy-1-*pY2;
		*pY2=pRect->y+pRect->cy-1;
		*pX2+=((dx<<16)/dy*l)>>16;
	}
	return *pX1!=*pX2 || *pY1!=*pY2;
}


bool ClipHLine(INOUT int*pX1,INOUT int*pX2,INOUT int*pY,IN WISP_RECT*pRect)
{
	if(*pX1<pRect->x && *pX2<pRect->x)
		return false;
	if(*pX1>=pRect->x+pRect->cx && *pX2>=pRect->x+pRect->cx)
		return false;
	if(*pY<pRect->y || *pY>=pRect->y+pRect->cy)
		return false;
	if(*pX1<pRect->x)
		*pX1=pRect->x;
	else if(*pX1>=pRect->x+pRect->cx)
		*pX1=pRect->x+pRect->cx-1;
	if(*pX2<pRect->x)
		*pX2=pRect->x;
	else if(*pX2>=pRect->x+pRect->cx)
		*pX2=pRect->x+pRect->cx-1;
	return *pX1!=*pX2;
}


bool ClipVLine(INOUT int*pX,INOUT int*pY1,INOUT int*pY2,IN WISP_RECT*pRect)
{
	if(*pX<pRect->x || *pX>=pRect->x+pRect->cx)
		return false;
	if(*pY1<pRect->y && *pY2<pRect->y)
		return false;
	if(*pY1>=pRect->y+pRect->cy && *pY2>=pRect->y+pRect->cy)
		return false;
	if(*pY1<pRect->y)
		*pY1=pRect->y;
	else if(*pY1>=pRect->y+pRect->cy)
		*pY1=pRect->y+pRect->cy-1;
	if(*pY2<pRect->y)
		*pY2=pRect->y;
	else if(*pY2>=pRect->y+pRect->cy)
		*pY2=pRect->y+pRect->cy-1;
	return *pY1!=*pY2;
}


bool ClipRect(INOUT WISP_RECT*pRect,IN WISP_RECT*pClipRect)
{
	if(pRect->x < pClipRect->x)
	{
		pRect->cx-=pClipRect->x-pRect->x;
		pRect->x=pClipRect->x;
	}
	if(pRect->y < pClipRect->y)
	{
		pRect->cy-=pClipRect->y-pRect->y;
		pRect->y=pClipRect->y;
	}
	if(pRect->x+pRect->cx > pClipRect->x+pClipRect->cx)
		pRect->cx = pClipRect->x+pClipRect->cx - pRect->x;
	if(pRect->y+pRect->cy > pClipRect->y+pClipRect->cy)
		pRect->cy = pClipRect->y+pClipRect->cy - pRect->y;
	return pRect->cx>0 && pRect->cy>0;
}

bool IsRectVisible(IN WISP_RECT*pRect,IN WISP_RECT*pClipRect)
{
	WISP_RECT Rect=*pRect;
	if(Rect.x < pClipRect->x)
	{
		Rect.cx-=pClipRect->x-Rect.x;
		Rect.x=pClipRect->x;
	}
	if(Rect.y < pClipRect->y)
	{
		Rect.cy-=pClipRect->y-Rect.y;
		Rect.y=pClipRect->y;
	}
	if(Rect.x+Rect.cx > pClipRect->x+pClipRect->cx)
		Rect.cx = pClipRect->x+pClipRect->cx - Rect.x;
	if(Rect.y+Rect.cy > pClipRect->y+pClipRect->cy)
		Rect.cy = pClipRect->y+pClipRect->cy - Rect.y;
	return Rect.cx>0 && Rect.cy>0;
}

void MergeRect(IN WISP_RECT*pRect1,IN WISP_RECT*pRect2,OUT WISP_RECT*pRect)
{
	if(pRect1==NULL || pRect2==NULL)
		return;
	if(pRect1->cx <=0 || pRect1->cy <=0)
	{
		*pRect = *pRect2;
		return;
	}
	if(pRect2->cx <=0 || pRect2->cy <=0)
	{
		*pRect = *pRect1;
		return;
	}
	pRect->x = MIN(pRect1->x,pRect2->x);
	pRect->y = MIN(pRect1->y,pRect2->y);
	pRect->cx= MAX(pRect1->x+pRect1->cx,pRect2->x+pRect2->cx) - pRect->x;
	pRect->cy= MAX(pRect1->y+pRect1->cy,pRect2->y+pRect2->cy) - pRect->y;
}

void MergeRect(IN WISP_RECT*pRect1,INOUT WISP_RECT*pRect2)
{
	int x,y,cx,cy;
	if(pRect1->cx <=0 ||pRect1->cy <=0)
		return;
	if(pRect2->cx <=0 ||pRect2->cy <=0)
	{
		*pRect2 = *pRect1;
		return;
	}
	x = MIN(pRect1->x,pRect2->x);
	y = MIN(pRect1->y,pRect2->y);
	cx= MAX(pRect1->x+pRect1->cx,pRect2->x+pRect2->cx) - x;
	cy= MAX(pRect1->y+pRect1->cy,pRect2->y+pRect2->cy) - y;
	pRect2->x = x;
	pRect2->y = y;
	pRect2->cx = cx;
	pRect2->cy = cy;
}

bool RectInRect(const IN WISP_RECT&Rect,const IN WISP_RECT&TestRect)
{
	return	TestRect.x >= Rect.x &&
			TestRect.x + TestRect.cx < Rect.x + Rect.cx &&
			TestRect.y >= Rect.y &&
			TestRect.y + TestRect.cy < Rect.y + Rect.cy;
}

COLORREF FindFitColor(COLORREF Color,COLORREF*Pal)
{
	long MinDelta,Delta,nDelta;
	MinDelta = 0x7FFFFFFF;
	nDelta = 0;
	for(int n=0;n<256;n++)
	{
		Delta = ABS((long)Color-(long)Pal[n]);
		if(Delta==0)
			return n;
		if(MinDelta>Delta)
		{
			MinDelta = Delta;
			nDelta = n;
		}
	}
	return nDelta;
}

void ColorStrSet(WISP_COLOR_CHAR*Src,int Len,BYTE TXTColor,BYTE BKColor)
{
	while(Len)
	{
		*Src += (TXTColor<<16) + (BKColor<<24);
		Src++;
		Len--;
	}
}

int ColorStrNCpy(WISP_COLOR_CHAR*Des,const WISP_CHAR*Src,int Count,BYTE TXTColor,BYTE BKColor)
{
	int len=0;
	while(*Src && Count--)
	{
		*Des = (WISP_COLOR_CHAR)*Src + (TXTColor<<16) + (BKColor<<24);
		Src++;
		Des++;
		len++;
	}
	*Des=0;
	return len;
}

int ColorStrCpy(WISP_COLOR_CHAR*Des,const WISP_CHAR*Src,BYTE TXTColor,BYTE BKColor)
{
	int len=0;
	while(*Src)
	{
		*Des = (WISP_COLOR_CHAR)*Src + (TXTColor<<16) + (BKColor<<24);
		Src++;
		Des++;
		len++;
	}
	*Des=0;
	return len;
}

int ColorStrCat(WISP_COLOR_CHAR*Des,const WISP_CHAR*Src,BYTE TXTColor,BYTE BKColor)
{
	int len=0;
	Des+=TStrLen(Des);
	while(*Src)
	{
		*Des = (WISP_COLOR_CHAR)*Src + (TXTColor<<16) + (BKColor<<24);
		Src++;
		Des++;
		len++;
	}
	*Des=0;
	return len;
}

int ColorStrCpy(WISP_COLOR_CHAR*Des,const CHAR*Src,BYTE TXTColor,BYTE BKColor)
{
	int len=0;
	while(*Src)
	{
		*Des = (WISP_COLOR_CHAR)*Src + (TXTColor<<16) + (BKColor<<24);
		Src++;
		Des++;
		len++;
	}
	*Des=0;
	return len;
}

int ColorStrCat(WISP_COLOR_CHAR*Des,const CHAR*Src,BYTE TXTColor,BYTE BKColor)
{
	int len=0;
	Des+=TStrLen(Des);
	while(*Src)
	{
		*Des = (WISP_COLOR_CHAR)*Src + (TXTColor<<16) + (BKColor<<24);
		Src++;
		Des++;
		len++;
	}
	*Des=0;
	return len;
}

