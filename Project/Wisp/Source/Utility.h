#ifndef _WISP_UTILITY_H_
#define _WISP_UTILITY_H_

#include "WispDefine.h"
#include "WispMsgDefine.h"

//	点是否在矩形区域内
bool PtInRect(IN const WISP_RECT *pRect, IN int x, int y);
bool PtInRect(IN  WISP_RECT *pRect,const IN WISP_POINT*pPoint);
bool PtInRect(IN  WISP_RECT *pRect,const  IN WISP_POINT &Point);
void PointToRect(INOUT WISP_POINT*pPoint,IN WISP_RECT*pRect);
void RectToRect(INOUT WISP_RECT*pRect,IN WISP_RECT*pToRect);
void PointSpliceRect(INOUT WISP_POINT*pPoint,IN WISP_RECT*pRect);
bool IsInvalidRect(IN WISP_RECT*pRect);
//裁减直线
bool ClipLine(INOUT int*pX1,INOUT int*pY1,INOUT int*pX2,INOUT int*pY2,IN WISP_RECT*pRect);
bool ClipHLine(INOUT int*pX1,INOUT int*pX2,INOUT int*pY,IN WISP_RECT*pRect);
bool ClipVLine(INOUT int*pX,INOUT int*pY1,INOUT int*pY2,IN WISP_RECT*pRect);
//裁减矩形
bool ClipRect(INOUT WISP_RECT*pRect,IN WISP_RECT*pClipRect);
bool IsRectVisible(IN WISP_RECT*pRect,IN WISP_RECT*pClipRect);
//融合矩形
void MergeRect(IN WISP_RECT*pRect1,IN WISP_RECT*pRect2,OUT WISP_RECT*pRect);
void MergeRect(IN WISP_RECT*pRect1,INOUT WISP_RECT*pRect2);
//矩形是否在矩形内
bool RectInRect(const IN WISP_RECT&Rect,const IN WISP_RECT&TestRect);
//计算两矩形重叠时的最小更新区域
//bool CalcUpdateRect(const IN WISP_RECT&Rect,INOUT WISP_RECT&UpdateRect);
COLORREF FindFitColor(COLORREF Color,COLORREF*Pal);
inline bool IsColorString(WISP_PCSTR pStr){return pStr && *pStr==0xFFFF;}
inline const WISP_COLOR_CHAR* GetColorString(WISP_PCSTR pStr){return (const WISP_COLOR_CHAR*)&pStr[2];}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//class WispRect
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class CWispRect : public WISP_RECT
{
public:
	CWispRect(){x=y=cx=cy=0;}
	CWispRect(LONG nx,LONG ny,LONG ncx,LONG ncy){ x=nx; y=ny; cx=ncx; cy=ncy; }
	CWispRect(const WISP_RECT&rc){ x=rc.x; y=rc.y; cx=rc.cx; cy=rc.cy; }
	CWispRect(const WISP_RECT*pRC){ x=pRC->x; y=pRC->y; cx=pRC->cx; cy=pRC->cy; }
	CWispRect(const WISP_POINT&pt,const WISP_SIZE &size){ x=pt.x; y=pt.y; cx=size.cx;cy=size.cy; }
	CWispRect(const WISP_POINT&LeftPT,const WISP_POINT&RightPT){x=LeftPT.x;y=LeftPT.y;cx=RightPT.x-x;cy=RightPT.y-y;}
	void DeflateRect(int nX, int nY) { x+=nX; y+=nY; cx-=2*nX; cy-=2*nY; }
	void OffsetRect(int nX, int nY) { x+=nX; y+=nY; }
	void operator=(const WISP_RECT& srcRect){ x = srcRect.x; y=srcRect.y; cx=srcRect.cx; cy=srcRect.cy; }
	bool operator==(const WISP_RECT&rc) { return x==rc.x && y==rc.y && cx==rc.cx && cy==rc.cy; }
	bool operator!=(const WISP_RECT&rc) { return x!=rc.x || y!=rc.y || cx!=rc.cx || cy!=rc.cy; }
	void operator+=(WISP_POINT pt){ x+=pt.x; y+=pt.y; }
	void operator+=(WISP_SIZE size){ x+=size.cx; y+=size.cy; }
	void operator+=(WISP_RECT&RC){ x+=RC.x; y+=RC.y; }
	void operator-=(WISP_POINT pt){ x-=pt.x; y-=pt.y; }
	void operator-=(WISP_SIZE size){ x-= size.cx; y-= size.cy; }
	void operator-=(WISP_RECT&RC){ x-=RC.x; y-=RC.y; }
	void operator&=(const WISP_RECT&rc)
	{
		
	}
	void operator|=(const WISP_RECT&rc)
	{
		LONG MinX,MinY,MaxX,MaxY;
		MinX=MIN(x,rc.x);
		MinY=MIN(y,rc.y);
		MaxX=MAX(x+cx,rc.x+rc.y);
		MaxY=MAX(y+cy,rc.y+rc.y);
		x=MinX;y=MinY;
		cx=MaxX-MinX;cy=MaxY-MinY;
	}

	CWispRect operator+(WISP_POINT pt)
	{
		CWispRect RC;
		RC.x=x+pt.x;
		RC.y=y+pt.y;
		RC.cx=cx;
		RC.cy=cy;
		return RC;
	}
	CWispRect operator+(WISP_RECT*pRC)
	{
		CWispRect RC;
		RC.x=x+pRC->x;
		RC.y=y+pRC->y;
		RC.cx=cx;
		RC.cy=cy;
		return RC;
	}
	CWispRect operator+(WISP_RECT rc)
	{
		CWispRect RC;
		RC.x=x+rc.x;
		RC.y=y+rc.y;
		RC.cx=cx;
		RC.cy=cy;
		return RC;
	}
	CWispRect operator+(WISP_SIZE size)
	{
		CWispRect RC;
		RC.x=x+size.cx;
		RC.y=y+size.cy;
		RC.cx=cx;
		RC.cy=cy;
		return RC;
	}
	CWispRect operator-(WISP_POINT pt)
	{
		CWispRect RC;
		RC.x=x-pt.x;
		RC.y=y-pt.y;
		RC.cx=cx;
		RC.cy=cy;
		return RC;
	}
	CWispRect operator-(WISP_RECT &RC)
	{
		CWispRect rRC;
		rRC.x=x-RC.x;
		rRC.y=y-RC.y;
		rRC.cx=cx;
		rRC.cy=cy;
		return rRC;
	}
	CWispRect operator-(WISP_SIZE size)
	{
		CWispRect RC;
		RC.x=x-size.cx;
		RC.y=y-size.cy;
		RC.cx=cx;
		RC.cy=cy;
		return RC;
	}
	CWispRect operator&(const WISP_RECT&rc)
	{
		
	}
	CWispRect operator|(const WISP_RECT&rc)
	{
		CWispRect RC;
		LONG MinX,MinY,MaxX,MaxY;
		MinX=MIN(x,rc.x);
		MinY=MIN(y,rc.y);
		MaxX=MAX(x+cx,rc.x+rc.y);
		MaxY=MAX(y+cy,rc.y+rc.y);
		RC.x=MinX;
		RC.y=MinY;
		RC.cx=MaxX-MinX;
		RC.cy=MaxY-MinY;
		return RC;
	}
	int y2() { return y+cy-1; }
	int x2() { return x+cx-1; }
	operator WISP_RECT*() const
	{
		return (WISP_RECT*)this;
	}
	void SetRect(int nx,int ny,int ncx,int ncy)
	{
		x = nx;
		y = ny;
		cx = ncx;
		cy = ncy;
	}
};

int ColorStrNCpy(WISP_COLOR_CHAR*Des,const WISP_CHAR*Src,int Count,BYTE TXTColor,BYTE BKColor);
int ColorStrCpy(WISP_COLOR_CHAR*Des,const WISP_CHAR*Src,BYTE TXTColor,BYTE BKColor);
int ColorStrCat(WISP_COLOR_CHAR*Des,const WISP_CHAR*Src,BYTE TXTColor,BYTE BKColor);
void ColorStrSet(WISP_COLOR_CHAR*Src,int Len,BYTE TXTColor,BYTE BKColor);
int ColorStrCpy(WISP_COLOR_CHAR*Des,const CHAR*Src,BYTE TXTColor,BYTE BKColor);
int ColorStrCat(WISP_COLOR_CHAR*Des,const CHAR*Src,BYTE TXTColor,BYTE BKColor);

#endif
