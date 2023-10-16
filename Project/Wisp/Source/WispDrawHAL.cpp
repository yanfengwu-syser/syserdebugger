#include "StdAfx.h"
#include "WispDefine.h"
#include "WispDrawHAL.h"

void CWispDraw4Bit::DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	BYTE Value=(BYTE)color,Value1;
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	Value1 = GET_BYTE(pFB->Buffer,y*pFB->LineDistance+x/2);
	if(x%2) Value1 |= (Value&0xf);
	else Value1 |= (Value<<4);
	PUT_BYTE(pFB->Buffer,y*pFB->LineDistance+x/2,Value1);
}

void CWispDraw4Bit::DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	BYTE Value1;
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	void*pPixelBuf=RT_PVOID(pFB->Buffer,y*pFB->LineDistance+x/2);
	BYTE Value = _GET_BYTE(pPixelBuf);
	Value1 = (BYTE)color;
	if(x%2)
	{
		Value1&=0xf;
		Value^=Value1;
	}
	else
	{
		Value1<<=4;
		Value^=Value1;
	}
	_PUT_BYTE(pPixelBuf,Value);
}

void CWispDraw4Bit::SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x + Count<= pFB->Width && y < pFB->Height);
	BYTE*StartBuffer = RT_PBYTE(pFB->Buffer,y*pFB->LineDistance+x/2);
	BYTE Value;
	if(x%2)
	{
		Value=_GET_BYTE(StartBuffer);
		Value |= (BYTE)color & 0xf;
		_PUT_BYTE(StartBuffer,Value);
		Count--;
		StartBuffer++;
	}
	Value = (BYTE)color;
	Value = (Value << 4) | (Value&0xf);
	while(Count)
	{

		_PUT_BYTE(StartBuffer,Value);
		StartBuffer++;
		Count--;
		if(!Count)break;
		Count--;
	}
}

COLORREF CWispDraw4Bit::GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y)
{
	CODE_ASSERT(x < pFB->Width && y < pFB->Height);
	BYTE Value=GET_BYTE(pFB->Buffer,y*pFB->LineDistance+x/2);
	Value = x%2?(Value&0xf):(Value>>4);
	return (COLORREF)Value;
}

void CWispDraw4Bit::Copy32BitPixelTo(void* pDes,void* pSrc,int Count)
{
	BYTE Value;
	for(int n = 0,j=0; n < Count;n++,j++)
	{
		Value = (BYTE)GET_DWORD(pSrc,n*4);
		Value <<= 4;
		n++;
		if(n<Count)
		{
			Value |= (BYTE)GET_DWORD(pSrc,n*4)&0xf;
		}
		PUT_BYTE(pDes,j,Value);
	}
}

void CWispDraw4Bit::CopyTo32BitPixel(void* pDes,void* pSrc,int Count)
{
	BYTE Value;
	for(int n =0,j=0;n<Count;n++,j++)
	{
		Value=GET_BYTE(pSrc,j);
		PUT_DWORD(pDes,n*4,Value>>4);
		n++;
		if(n<Count)
			PUT_DWORD(pDes,n*4,Value&0xf);
	}
}

void CWispDraw8Bit::DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	PUT_BYTE(pFB->Buffer,y*pFB->LineDistance+x,(BYTE)color);
}

void CWispDraw8Bit::DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	void*pPixelBuf=RT_PVOID(pFB->Buffer,y*pFB->LineDistance+x);
	_PUT_BYTE(pPixelBuf,_GET_BYTE(pPixelBuf)^(BYTE)color);
}

void CWispDraw8Bit::SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x + Count<= pFB->Width && y < pFB->Height);
	BYTE*StartBuffer = RT_PBYTE(pFB->Buffer,y*pFB->LineDistance+x);
	while(Count)
	{
		_PUT_BYTE(StartBuffer,(BYTE)color);
		StartBuffer++;
		Count--;
	}
}

COLORREF CWispDraw8Bit::GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y)
{
	CODE_ASSERT(x < pFB->Width && y < pFB->Height);
	return GET_BYTE(pFB->Buffer,y*pFB->LineDistance+x);
}

void CWispDraw8Bit::Copy32BitPixelTo(void* pDes,void* pSrc,int Count)
{
	for(int n = 0; n < Count;n++)
		PUT_BYTE(pDes,n,(BYTE)GET_DWORD(pSrc,n*4));
}

void CWispDraw8Bit::CopyTo32BitPixel(void* pDes,void* pSrc,int Count)
{
	for(int n =0;n<Count;n++)
		PUT_DWORD(pDes,n*4,GET_BYTE(pSrc,n));
}

void CWispDraw16Bit::DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	WORD WordColor;
	WordColor = (WORD)((color & 0xFF)>>3);
	WordColor|= ((color & 0xFF00)>>10)<<5;
	WordColor|= ((color & 0xFF0000)>>19)<<11;
	PUT_WORD(pFB->Buffer,y*pFB->LineDistance+x*2,WordColor);
}

void CWispDraw16Bit::DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	void*pPixelBuf=RT_PVOID(pFB->Buffer,y*pFB->LineDistance+x*2);
	_PUT_WORD(pPixelBuf,_GET_WORD(pPixelBuf) ^ (WORD)color);
}

void CWispDraw16Bit::SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x + Count<= pFB->Width && y < pFB->Height);
	WORD WordColor,*StartBuffer;
	WordColor = (WORD)((color & 0xFF)>>3);
	WordColor|= ((color & 0xFF00)>>10)<<5;
	WordColor|= ((color & 0xFF0000)>>19)<<11;
	StartBuffer = RT_PWORD(pFB->Buffer,y*pFB->LineDistance+(x<<1));
	while(Count)
	{
		_PUT_WORD(StartBuffer,WordColor);
		StartBuffer++;
		Count--;
	}
}

COLORREF CWispDraw16Bit::GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	WORD WordColor;
	COLORREF color;
	WordColor=GET_WORD(pFB->Buffer,y*pFB->LineDistance+x*2);
	color = WordColor&0x1F;
	color|= (WordColor&0x7E)<<3;
	color|= (WordColor&0xF8)<<11;
	return color;
}

void CWispDraw16Bit::Copy32BitPixelTo(void* pDes,void* pSrc,int Count)
{
	COLORREF color;
	WORD WordColor;
	COLORREF*SrcBuf=(COLORREF*)pSrc;
	WORD*DesBuf=(WORD*)pDes;
	while(Count--)
	{
		color = *SrcBuf;
		WordColor = (WORD)((color & 0xFF)>>3);
		WordColor|= ((color & 0xFF00)>>10)<<5;
		WordColor|= ((color & 0xFF0000)>>19)<<11;
		*DesBuf=WordColor;
		SrcBuf++;
		DesBuf++;
	}
}

void CWispDraw16Bit::CopyTo32BitPixel(void* pDes,void* pSrc,int Count)
{
	WORD WordColor;
	WORD*SrcBuf=(WORD*)pSrc;
	COLORREF*DesBuf=(COLORREF*)pDes;
	while(Count--)
	{
		WordColor = *SrcBuf;
		*DesBuf=((WordColor&0x1F)<<3) | ((WordColor&0x3E0)<<6) | ((WordColor&0x7C00)<<9);
		SrcBuf++;
		DesBuf++;
	}
}

void CWispDraw24Bit::DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	CODE_ASSERT(x < pFB->Width && y < pFB->Height);
	PUT_3BYTES(pFB->Buffer,y*pFB->LineDistance+x*3,color);
}

void CWispDraw24Bit::DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	void*pPixelBuf=RT_PVOID(pFB->Buffer,y*pFB->LineDistance+x*3);
	_PUT_3BYTES(pPixelBuf,_GET_3BYTES(pPixelBuf) ^ color);
}

void CWispDraw24Bit::SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>= 0 && x + Count<= pFB->Width && y < pFB->Height);
	BYTE*StartBuffer = RT_PBYTE(pFB->Buffer,y*pFB->LineDistance+x*3);
	while(Count)
	{
		_PUT_3BYTES(StartBuffer,color);
		StartBuffer+=3;
		Count--;
	}
}

COLORREF CWispDraw24Bit::GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	return GET_3BYTES(pFB->Buffer,y*pFB->LineDistance+x*3);
}

void CWispDraw24Bit::Copy32BitPixelTo(void* pDes,void* pSrc,int Count)
{
	BYTE*SrcBuf=(BYTE*)pSrc;
	BYTE*DesBuf=(BYTE*)pDes;
	while(Count--)
	{
		*_RT_PWORD(DesBuf)=*_RT_PWORD(SrcBuf);
		DesBuf+=2;
		SrcBuf+=2;
		*_RT_PBYTE(DesBuf)=*_RT_PBYTE(SrcBuf);
		DesBuf++;
		SrcBuf+=2;
	}
}

void CWispDraw24Bit::CopyTo32BitPixel(void* pDes,void* pSrc,int Count)
{
	BYTE*SrcBuf=(BYTE*)pSrc;
	BYTE*DesBuf=(BYTE*)pDes;
	while(Count--)
	{
		*_RT_PWORD(DesBuf)=*_RT_PWORD(SrcBuf);
		DesBuf+=2;
		SrcBuf+=2;
		*_RT_PBYTE(DesBuf)=*_RT_PBYTE(SrcBuf);
		DesBuf+=2;
		SrcBuf++;
	}
}

void CWispDraw32Bit::DrawPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	CODE_ASSERT(x < pFB->Width && y < pFB->Height);
	PUT_DWORD(pFB->Buffer,y*pFB->LineDistance+x*4,color);
}

void CWispDraw32Bit::DrawXorPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	void*pPixelBuf=RT_PVOID(pFB->Buffer,y*pFB->LineDistance+x*4);
	_PUT_DWORD(pPixelBuf,_GET_DWORD(pPixelBuf)^color);
}

void CWispDraw32Bit::SetHLinePixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y,IN int Count,IN COLORREF color)
{
	CODE_ASSERT(x>=0 && y>=0 && x + Count<= pFB->Width && y < pFB->Height);
	DWORD*StartBuffer = RT_PDWORD(pFB->Buffer,y*pFB->LineDistance+x*4);
	while(Count)
	{
		*StartBuffer=color;
		StartBuffer++;
		Count--;
	}
}

COLORREF CWispDraw32Bit::GetPixel(IN WISP_FRAME_BUFFER*pFB,IN int x,IN int y)
{
	CODE_ASSERT(x>=0 && y>=0 && x<pFB->Width && y<pFB->Height);
	return GET_DWORD(pFB->Buffer,y*pFB->LineDistance+x*4);
}

void CWispDraw32Bit::Copy32BitPixelTo(void* pDes,void* pSrc,int Count)
{
	memcpy(pDes,pSrc,4*Count);
}

void CWispDraw32Bit::CopyTo32BitPixel(void* pDes,void* pSrc,int Count)
{
	memcpy(pDes,pSrc,4*Count);
}

