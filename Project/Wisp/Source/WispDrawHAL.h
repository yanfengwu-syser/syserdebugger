#ifndef _WISP_DRAW_HAL_
#define _WISP_DRAW_HAL_


class CWispDrawHAL
{
public:
	virtual void		DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color){}
	virtual void		DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color){}
	virtual void		SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color){}
	virtual COLORREF	GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y){return 0;}
	virtual void		Copy32BitPixelTo(void* pDes,void* pSrc,int Count){}
	virtual void		CopyTo32BitPixel(void* pDes,void* pSrc,int Count){}
};

class CWispDraw4Bit : public CWispDrawHAL
{
public:
	virtual void		DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color);
	virtual COLORREF	GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y);
	virtual void		Copy32BitPixelTo(void* pDes,void* pSrc,int Count);
	virtual void		CopyTo32BitPixel(void* pDes,void* pSrc,int Count);
};

class CWispDraw8Bit : public CWispDrawHAL
{
public:
	virtual void		DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color);
	virtual COLORREF	GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y);
	virtual void		Copy32BitPixelTo(void* pDes,void* pSrc,int Count);
	virtual void		CopyTo32BitPixel(void* pDes,void* pSrc,int Count);
};

class CWispDraw16Bit : public CWispDrawHAL
{
public:
	virtual void		DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color);
	virtual COLORREF	GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y);
	virtual void		Copy32BitPixelTo(void* pDes,void* pSrc,int Count);
	virtual void		CopyTo32BitPixel(void* pDes,void* pSrc,int Count);
};

class CWispDraw24Bit : public CWispDrawHAL
{
public:
	virtual void		DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color);
	virtual COLORREF	GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y);
	virtual void		Copy32BitPixelTo(void* pDes,void* pSrc,int Count);
	virtual void		CopyTo32BitPixel(void* pDes,void* pSrc,int Count);
};

class CWispDraw32Bit : public CWispDrawHAL
{
public:
	virtual void		DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color);
	virtual void		SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color);
	virtual COLORREF	GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y);
	virtual void		Copy32BitPixelTo(void* pDes,void* pSrc,int Count);
	virtual void		CopyTo32BitPixel(void* pDes,void* pSrc,int Count);
};


#endif
