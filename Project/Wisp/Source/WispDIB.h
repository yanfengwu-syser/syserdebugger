#ifndef _WISP_DIB_H_
#define _WISP_DIB_H_

#include "Utility.h"

#define WISP_DIB_BITMAP			0x00000001
#define WISP_DIB_TK				0x00000002
#define WISP_DIB_TK_XOR			0x00000003

struct BITMAP_FILE_HEADER
{
	WORD	bfType;
	WORD	bfSizeLow;
	WORD	bfSizeHigh;
	WORD	bfReserved1;
	WORD	bfReserved2;
	WORD	bfOffBitsLow;
	WORD	bfOffBitsHigh;
};

struct BITMAP_INFO_HEADER
{
	DWORD	biSize;
	LONG	biWidth;
	LONG	biHeight;
	WORD	biPlanes;
	WORD	biBitCount;
	DWORD	biCompression;
	DWORD	biSizeImage;
	LONG	biXPelsPerMeter;
	LONG	biYPelsPerMeter;
	DWORD	biClrUsed;
	DWORD	biClrImportant;
};

struct ICON_DIR
{
	WORD	idReserved;   // Reserved
	WORD	idType;       // resource type (1 for icons)
	WORD	idCount;      // how many images?
};

struct ICON_DIR_ENTRY
{
	BYTE	bWidth;               // Width of the image
	BYTE	bHeight;              // Height of the image (times 2)
	BYTE	bColorCount;          // Number of colors in image (0 if >=8bpp)
	BYTE	bReserved;            // Reserved
	WORD	wPlanes;              // Color Planes
	WORD	wBitCount;            // Bits per pixel
	DWORD	dwBytesInRes;         // how many bytes in this resource?
	DWORD	dwImageOffset;        // where in the file is this image
};


class CWispFont;
class CWispDIB
{
public:
	CWispDIB();
	~CWispDIB();
public:
	WISP_FRAME_BUFFER	m_FrameBuffer;
	WISP_RECT	m_Rect;
	UINT		m_Type;
	COLORREF	m_ColorKey;
	WISP_POINT	m_HotPT;
	COLORREF*	m_Pal;
	bool		m_bAutoDelete;
	int			m_RefCount;
public:
	void	InitParam();
	bool	Load(PCSTR FileName,int Index = -1);
	bool	Save(PCSTR FileName);
	bool	LoadIcon(PCSTR FileName,int Index = -1);
	bool	Create(int Width,int Height,UINT Type=WISP_DIB_TK,WISP_POINT*pHotPT=NULL,COLORREF ColorKey=0);
	bool	Resize(int Width,int Height);
	void	Destroy();
	void	Blt(const WISP_RECT&SrcRect,CWispDIB*pDesBIB,int x,int y);
	void	BltTiled(CWispDIB*pDesBIB);
	void	SetType(UINT Type);
	void	SetColorKey(COLORREF ColorKey);
	void	SetHotPoint(int x,int y);
	void	SetHotPoint(WISP_POINT*pHotPT);
	bool	GetPixel(int x,int y,COLORREF*pClr);
	void	Clear(COLORREF Color = 0);
	inline	int	Width()const { return m_Rect.cx;}
	inline	int	Height()const { return m_Rect.cy;}
};

class CWispDIBList
{
public:
	CWispDIBList();
	~CWispDIBList();
public:
	CWispDIB*m_DIBList;
	int		m_RefCount;
	int		m_Count;
public:
	bool	Load(PCSTR FileName,int TileWidth,int TileHeight,int Count);
	bool	LoadIcon(PCSTR FileName);
	void	Destroy();
	void	SetType(UINT Type);
	void	SetColorKey(COLORREF ColorKey);
public:
	inline	CWispDIB*GetDIB(int ID)const{return &m_DIBList[ID];}
	inline	CWispDIB*operator[](int ID)const{return &m_DIBList[ID];}
};

#endif
