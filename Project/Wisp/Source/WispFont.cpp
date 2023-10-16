#include "StdAfx.h"
#include "WispBase.h"
#include "WispFont.h"

CWispFont::CWispFont()
{
	m_BufSize=
	m_Width=
	m_Height=
	
	m_WideBufSize=
	m_WideWidth=
	m_WideHeight=0;

	m_Buffer=
	m_WideBuffer=NULL;
}

bool CWispFont::LoadChar(WISP_PHYS_FONT_INFO*pFontInfo)
{
	CImageFile ImageFile;
	ImageFile.ChangeFileIO(&gpCurWisp->m_PFSFileIO);
	m_Buffer = NULL;
	m_BufSize = 0;
	m_Width = 0;
	m_Height = 0;
	if(ImageFile.Open(pFontInfo->FontFN)==false)
		return false;
	m_BufSize=(int)ImageFile.GetFileLength();
	if(m_BufSize==0)
	{
		ImageFile.Close();
		return false;
	}
	m_Buffer=new BYTE[m_BufSize];
	if(m_Buffer==NULL)
	{
		m_BufSize=0;
		ImageFile.Close();
		return false;
	}
	if(ImageFile.ReadFile(0,m_Buffer,m_BufSize)==false)
	{
		m_BufSize=0;
		SafeDelete(m_Buffer);
		ImageFile.Close();
		return false;
	}
	m_Width = pFontInfo->Width;
	m_Height = pFontInfo->Height;
	ImageFile.Close();

	for(int i=0;i<0x100;i++)
		m_CharLenAry[i]=8;
	m_CharLenAry[0x00]=
	m_CharLenAry[0x0D]=
	m_CharLenAry[0x0A]=0;
	m_BytesPerChar = (m_Width * m_Height + 7)/8;
	return true;
}

bool CWispFont::LoadWideChar(WISP_PHYS_FONT_INFO*pFontInfo)
{
	CImageFile ImageFile;
	ImageFile.ChangeFileIO(&gpCurWisp->m_PFSFileIO);
	m_WideBuffer = NULL;
	m_WideBufSize = 0;
	m_WideWidth = 0;
	m_WideHeight = 0;
	if(ImageFile.Open(pFontInfo->WideFontFN)==false)
		return false;
	m_WideBufSize=(int)ImageFile.GetFileLength();
	if(m_WideBufSize==0)
	{
		ImageFile.Close();
		return false;
	}
	m_WideBuffer=new BYTE[m_WideBufSize];
	if(m_WideBuffer==NULL)
	{
		m_WideBufSize=0;
		ImageFile.Close();
		return false;
	}
	if(ImageFile.ReadFile(0,m_WideBuffer,m_WideBufSize)==false)
	{
		m_WideBufSize=0;
		SafeDelete(m_WideBuffer);
		ImageFile.Close();
		return false;
	}
	m_WideWidth = pFontInfo->Width*2;
	m_WideHeight = pFontInfo->Height;
	ImageFile.Close();
	return true;

}

void CWispFont::Destroy()
{
	SafeDelete(m_Buffer);
	SafeDelete(m_WideBuffer);
}

BYTE*CWispFont::GetCharPixelBuffer(WISP_CHAR Char)
{
	if(Char<0x100)
	{
		return &m_Buffer[Char*m_BytesPerChar];
	}
	else
	{
		int Offset=Char*m_BytesPerChar*2;
		if(m_WideBuffer && Offset<m_WideBufSize)
			return &m_WideBuffer[Offset];
		else
			return &m_Buffer['?'*m_BytesPerChar];
	}
}

int	CWispFont::GetCharWidth(WISP_CHAR Char)
{
	if(Char < 0x100)
	{
		return m_Width;
	}
	else
	{
		if(m_WideBuffer)
			return m_WideWidth;
		return m_Width;
	}
}

int	CWispFont::GetCharHeight(WISP_CHAR Char)
{
	if(Char < 0x100)
	{
		return m_Height;
	}
	else
	{
		if(m_WideBuffer)
			return m_WideHeight;
		return m_Height;
	}
}

