#ifndef _WISP_FONT_DATA_H_
#define _WISP_FONT_DATA_H_


enum WISP_FONT_ID
{
	WISP_FONT_8X16=0,
	WISP_FONT_6X12,
	WISP_FONT_ASCII_12X16,
	WISP_FONT_EBCDIC_12X16,
	WISP_FONT_ANSI_12X16,
	WISP_FONT_COUNT
};

struct WISP_PHYS_FONT_INFO
{
	int		Width;
	int		Height;
	PCSTR	FontFN;
	PCSTR	WideFontFN;
};

class CWispFont
{
public:
	CWispFont();
public:
	bool	LoadChar(WISP_PHYS_FONT_INFO*pFontInfo);
	bool	LoadWideChar(WISP_PHYS_FONT_INFO*pFontInfo);
	void	Destroy();
	int		m_CharLenAry[256];
	int		m_Height;										//字体的高度
	int		m_Width;										//字体的宽度
	BYTE*	m_Buffer;										//字模指针
	int		m_BufSize;										//字模缓存大小

	int		m_WideHeight;									//字体的高度
	int		m_WideWidth;									//字体的宽度
	BYTE*	m_WideBuffer;									//字模指针
	int		m_WideBufSize;									//字模缓存大小
	int		m_BytesPerChar;									//每个字符所占字节

	BYTE*	GetCharPixelBuffer(WISP_CHAR Char);
	int		GetCharWidth(WISP_CHAR Char);
	int		GetCharHeight(WISP_CHAR Char);
};

#endif
