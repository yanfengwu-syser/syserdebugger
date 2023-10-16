#include "StdAfx.h"
#include "WispDIB.h"
#include "WispBase.h"

CWispDIB::CWispDIB()
{
	m_FrameBuffer.Buffer=NULL;
	m_Pal = NULL;
	m_bAutoDelete = false;
	m_RefCount = 0;
	m_FrameBuffer.Width = m_FrameBuffer.Height = 0;
}

CWispDIB::~CWispDIB()
{
	if(m_bAutoDelete==false)
		Destroy();
}

void CWispDIB::InitParam()
{
	m_FrameBuffer.LineDistance=sizeof(COLORREF)*m_FrameBuffer.Width;
	m_FrameBuffer.BufferSize = sizeof(COLORREF)*m_FrameBuffer.Width*m_FrameBuffer.Height;
	m_FrameBuffer.Buffer = new BYTE[m_FrameBuffer.BufferSize];
	m_FrameBuffer.Bpp=32;
	m_Rect.x = m_Rect.y = 0;
	m_Rect.cx = m_FrameBuffer.Width;
	m_Rect.cy = m_FrameBuffer.Height;
	switch(m_FrameBuffer.Bpp)
	{
	case 4:
		m_FrameBuffer.pDrawHAL = &gpCurWisp->m_DrawHAL4Bit;
	case 8:
		m_FrameBuffer.pDrawHAL = &gpCurWisp->m_DrawHAL8Bit;
		break;
	case 16:
		m_FrameBuffer.pDrawHAL = &gpCurWisp->m_DrawHAL16Bit;
		break;
	case 24:
		m_FrameBuffer.pDrawHAL = &gpCurWisp->m_DrawHAL24Bit;
		break;
	case 32:
		m_FrameBuffer.pDrawHAL = &gpCurWisp->m_DrawHAL32Bit;
		break;
	default:
		m_FrameBuffer.pDrawHAL = &gpCurWisp->m_NotSupportDrawHAL;
		break;
	}
}

void CWispDIB::Clear(COLORREF Color)
{
	for(int n=m_FrameBuffer.BufferSize/(m_FrameBuffer.Bpp>>3)-1;n>=0;n--)
		((COLORREF*)m_FrameBuffer.Buffer)[n] = Color;
}

bool CWispDIB::Create(int Width,int Height,UINT Type,WISP_POINT*pHotPT,COLORREF ColorKey)
{
	m_FrameBuffer.Width=Width;
	m_FrameBuffer.Height=Height;
	m_ColorKey=ColorKey;
	m_Type=Type;
	if(pHotPT)
		m_HotPT=*pHotPT;
	else
		m_HotPT.x=m_HotPT.y=0;
	InitParam();
	return true;
}

bool CWispDIB::Resize(int Width,int Height)
{
	int AlignSize,NewBufferSize;
	if(Width == -1)
		Width = m_FrameBuffer.Width;
	if(Height == -1)
		Height = m_FrameBuffer.Height;
	NewBufferSize = Width*Height*sizeof(COLORREF);
	if(NewBufferSize==m_FrameBuffer.BufferSize)
		return true;
	AlignSize = MAX(Width,Height)*sizeof(COLORREF)*8;
	if(NewBufferSize>m_FrameBuffer.BufferSize)
	{
		m_FrameBuffer.BufferSize = ALIGN_SIZE(NewBufferSize,AlignSize);
		delete m_FrameBuffer.Buffer;
		m_FrameBuffer.Buffer = new BYTE[m_FrameBuffer.BufferSize];
	}
	else if(m_FrameBuffer.BufferSize - NewBufferSize > AlignSize)
	{
		m_FrameBuffer.BufferSize = Width*Height*sizeof(COLORREF);
		delete m_FrameBuffer.Buffer;
		m_FrameBuffer.Buffer = new BYTE[m_FrameBuffer.BufferSize];
	}
	m_FrameBuffer.Width = Width;
	m_FrameBuffer.Height = Height;
	m_FrameBuffer.LineDistance=sizeof(COLORREF)*m_FrameBuffer.Width;
	m_Rect.x = m_Rect.y = 0;
	m_Rect.cx = m_FrameBuffer.Width;
	m_Rect.cy = m_FrameBuffer.Height;
	return true;
}

bool CWispDIB::Load(PCSTR FileName,int Index)
{
	int		Width,Height,BytesPixel,dwDibSize,dwSize,Delta,Off;
	BYTE*	pBits;
	BITMAP_FILE_HEADER	bmFileHead;
	BITMAP_INFO_HEADER*	pbmInfo;
	COLORREF*pColor;
	CImageFile DIBFile;

	DIBFile.ChangeFileIO(&gpCurWisp->m_PFSFileIO);
	if(gpCurWisp->m_PFSFileIO.GetFileAttr(FileName) & FIO_FA_COMPRESS)
	{
		int Size = (int)gpCurWisp->m_PFSFileIO.GetFileSize(FileName);
		if(Size<=0)
			return false;
		if(DIBFile.Create(Size)==false)
			return false;
		gpCurWisp->m_PFSFileIO.ReadFromFile(FileName,DIBFile.m_Buffer,Size);
	}
	else
	{
		if(DIBFile.Open(FileName)==false)
			return false;
	}

	m_Pal = NULL;
	DIBFile.ReadFile(0,&bmFileHead,sizeof(BITMAP_FILE_HEADER));
	if(bmFileHead.bfType != 0x4D42)//"BM"
	{
		DIBFile.Close();
		return LoadIcon(FileName,Index);
	}
	dwSize=MAKE_DWORD(bmFileHead.bfSizeHigh,bmFileHead.bfSizeLow);
	dwDibSize = dwSize - sizeof(BITMAP_FILE_HEADER);

	pbmInfo = (BITMAP_INFO_HEADER*)new BYTE[dwDibSize+4];
	if(DIBFile.ReadFile(pbmInfo,dwDibSize)==false)
	{
		DIBFile.Close();
		delete pbmInfo;
		return false;
	}

	if(pbmInfo->biCompression || pbmInfo->biBitCount==16)
	{
		DIBFile.Close();
		delete pbmInfo;
		return false;
	}

	BytesPixel=(pbmInfo->biBitCount+7)/8;
	if(pbmInfo->biSize == sizeof(BITMAP_INFO_HEADER))
	{
		Width	=pbmInfo->biWidth;
		Height	=ABS(pbmInfo->biHeight);
	}
	else
	{
		DIBFile.Close();
		delete pbmInfo;
		return false;
	}
	m_FrameBuffer.Width=Width;
	m_FrameBuffer.Height=Height;
	m_ColorKey=0;
	m_HotPT.x=m_HotPT.y=0;
	m_Type=WISP_DIB_BITMAP;
	Delta=ALIGN_SIZE(Width*BytesPixel,4);
	InitParam();
	if(pbmInfo->biBitCount == 8)
	{
		pColor = (COLORREF*)&pbmInfo[1];
		m_Pal = new COLORREF[256];
		for(int n=0;n<256;n++)
		{
			m_Pal[n]=pColor[n];
		}
		DWORD BitOffset = MAKE_DWORD(bmFileHead.bfOffBitsHigh,bmFileHead.bfOffBitsLow);
		pBits = (BYTE *)&pbmInfo[1] + BitOffset - sizeof(BITMAP_FILE_HEADER) - sizeof(BITMAP_INFO_HEADER) + Delta*Height;
		Off=0;
		if(gpCurWisp->m_FrameBuffer.Bpp==8)
		{
			for(int y=0;y<Height;y++)
			{
				pBits-=Delta;
				for(int x=0;x<Width;x++)
				{
					((COLORREF*)m_FrameBuffer.Buffer)[Off]=GET_BYTE(pBits,x);
					Off++;
				}
			}
		}
		else
		{
			for(int y=0;y<Height;y++)
			{
				pBits-=Delta;
				for(int x=0;x<Width;x++)
				{
					((COLORREF*)m_FrameBuffer.Buffer)[Off]=m_Pal[GET_BYTE(pBits,x)];
					Off++;
				}
			}
		}
	}
	else//24bit,32bit
	{
		pBits = (BYTE *)&pbmInfo[1] + Delta*Height;
		Off=0;
		for(int y=0;y<Height;y++)
		{
			pBits-=Delta;
			for(int x=0;x<Width;x++)
			{
				((COLORREF*)m_FrameBuffer.Buffer)[Off]=_GET_DWORD(pBits+x*BytesPixel) & 0x00FFFFFF;
				Off++;
			}
		}
	}
	DIBFile.Close();
	delete pbmInfo;
	return true;
}

bool CWispDIB::Save(PCSTR FileName)
{
	DWORD Size,BitSize;
	BITMAP_FILE_HEADER BmpHeader;
	BITMAP_INFO_HEADER InfoHead;
	if(m_FrameBuffer.Buffer==NULL)
		return false;
	BitSize = m_FrameBuffer.Width*m_FrameBuffer.Height*(m_FrameBuffer.Bpp/8);
	Size = sizeof(BITMAP_FILE_HEADER)+sizeof(BITMAP_INFO_HEADER)+BitSize;
	BmpHeader.bfType = 0x4d42;   // 'BM' WINDOWS_BITMAP_SIGNATURE
	BmpHeader.bfSizeLow = LOW_WORD(Size);
	BmpHeader.bfSizeHigh = HIGH_WORD(Size);
	BmpHeader.bfReserved1 = BmpHeader.bfReserved2 = 0;
	Size = sizeof(BITMAP_FILE_HEADER)+sizeof(BITMAP_INFO_HEADER);
	BmpHeader.bfOffBitsLow = LOW_WORD(Size);
	BmpHeader.bfOffBitsHigh = HIGH_WORD(Size);

	InfoHead.biSize = sizeof(BITMAP_INFO_HEADER);
	InfoHead.biCompression = 0;
	InfoHead.biWidth = m_FrameBuffer.Width;
	InfoHead.biHeight = m_FrameBuffer.Height;
	InfoHead.biPlanes = 1;
	InfoHead.biBitCount = (WORD)m_FrameBuffer.Bpp;
	InfoHead.biSizeImage = BitSize;
	InfoHead.biXPelsPerMeter = 0;
	InfoHead.biYPelsPerMeter = 0;
	InfoHead.biClrUsed = 0;
	InfoHead.biClrImportant = 0;

	COLORREF*PixelBuffer = new COLORREF[m_FrameBuffer.Width*m_FrameBuffer.Height];
	if(PixelBuffer==NULL)
		return false;
	CImageFileStream FileObj;
	if(FileObj.Create(FileName)==false)
	{
		delete PixelBuffer;
		return false;
	}
	FileObj.Puts(&BmpHeader,sizeof(BmpHeader));
	FileObj.Puts(&InfoHead,sizeof(InfoHead));
	BitSize /= sizeof(COLORREF);
	int Off=0;
	COLORREF*pBits = &PixelBuffer[m_FrameBuffer.Width*m_FrameBuffer.Height];
	for(int y=0;y<m_FrameBuffer.Height;y++)
	{
		pBits-=m_FrameBuffer.Width;
		for(int x=0;x<m_FrameBuffer.Width;x++)
		{
			pBits[x]=((COLORREF*)m_FrameBuffer.Buffer)[Off];
			Off++;
		}
	}
	FileObj.Puts(PixelBuffer,BitSize*sizeof(COLORREF));
	FileObj.Close();
	delete PixelBuffer;
	return true;
}

void CWispDIB::SetType(UINT Type)
{	
	m_Type = Type;
}

void CWispDIB::SetColorKey(COLORREF ColorKey)
{
	if(m_Type!=WISP_DIB_TK)
		SetType(WISP_DIB_TK);
	m_ColorKey=ColorKey;
}

void CWispDIB::SetHotPoint(int x,int y)
{	
	m_HotPT.x = x;	m_HotPT.y = y;
}

void CWispDIB::SetHotPoint(WISP_POINT*pHotPT)
{
	m_HotPT = *pHotPT;
}

bool CWispDIB::GetPixel(int x,int y,COLORREF*pClr)
{
	if(x < 0 || y < 0 || x >= m_FrameBuffer.Width || y >= m_FrameBuffer.Height)
		return false;
	*pClr = *(COLORREF*)RT_PVOID(m_FrameBuffer.Buffer,m_FrameBuffer.LineDistance*y + sizeof(COLORREF) * x);
	return true;
}

bool CWispDIB::LoadIcon(PCSTR FileName,int Index)
{
	COLORREF*pColor;
	BYTE*pBits,*pIcon;
	int HeadOffset,Delta,Off,BytesPixel;
	ICON_DIR_ENTRY IconDirEntry;
	ICON_DIR	IconDir;
	CImageFile	DIBFile;

	DIBFile.ChangeFileIO(&gpCurWisp->m_PFSFileIO);
	if(gpCurWisp->m_PFSFileIO.GetFileAttr(FileName) & FIO_FA_COMPRESS)
	{
		int Size = (int)gpCurWisp->m_PFSFileIO.GetFileSize(FileName);
		if(Size<=0)
			return false;
		if(DIBFile.Create(Size)==false)
			return false;
		gpCurWisp->m_PFSFileIO.ReadFromFile(FileName,DIBFile.m_Buffer,Size);
	}
	else
	{
		if(DIBFile.Open(FileName)==false)
			return false;
	}

	DIBFile.ReadFile(&IconDir,sizeof(IconDir));
	if(IconDir.idType!=1||IconDir.idReserved!=0)
	{
		DIBFile.Close();
		return false;
	}
	HeadOffset = sizeof(IconDir);
	if(Index < 0)
		Index = IconDir.idCount - 1;
	for(int n=0;n<IconDir.idCount;n++)
	{
		DIBFile.ReadFile(HeadOffset,&IconDirEntry,sizeof(IconDirEntry));
		if(Index==n)
		{
			m_FrameBuffer.Width = IconDirEntry.bWidth;
			m_FrameBuffer.Height = IconDirEntry.bHeight;
			m_HotPT.x=m_HotPT.y=0;
			m_Type=WISP_DIB_TK;
			m_ColorKey=0;
			BytesPixel = (IconDirEntry.wBitCount+7)/8;
			InitParam();
			pIcon = new BYTE[IconDirEntry.dwBytesInRes];
			DIBFile.ReadFile(IconDirEntry.dwImageOffset,pIcon,IconDirEntry.dwBytesInRes);
			if(BytesPixel==0)
				BytesPixel = ( ((BITMAP_INFO_HEADER*)pIcon)->biBitCount+7 ) / 8;
			Delta=ALIGN_SIZE(m_FrameBuffer.Width*BytesPixel,4);
			if(IconDirEntry.wBitCount==8)
			{//256 color
				pColor = (COLORREF*)(pIcon+sizeof(BITMAP_INFO_HEADER));
				pBits = pIcon+sizeof(BITMAP_INFO_HEADER)+sizeof(COLORREF)*256+Delta*m_FrameBuffer.Height;
				m_Pal = new COLORREF[256];
				for(int nClr=0;nClr<256;nClr++)
					m_Pal[nClr]=pColor[nClr];
				Off=0;
				if(gpCurWisp->m_FrameBuffer.Bpp==8)
				{//screen is 256 color
					for(int y=0;y<m_FrameBuffer.Height;y++)
					{
						pBits-=Delta;
						for(int x=0;x<m_FrameBuffer.Width;x++)
						{
							((COLORREF*)m_FrameBuffer.Buffer)[Off]=GET_BYTE(pBits,x);
							Off++;
						}
					}
				}
				else
				{//screen is tree color
					for(int y=0;y<m_FrameBuffer.Height;y++)
					{
						pBits-=Delta;
						for(int x=0;x<m_FrameBuffer.Width;x++)
						{
							((COLORREF*)m_FrameBuffer.Buffer)[Off]=m_Pal[GET_BYTE(pBits,x)];
							Off++;
						}
					}
				}
			}
			else
			{//16£¬24£¬32 bit tree color
				pBits = pIcon + sizeof(BITMAP_INFO_HEADER) + Delta*m_FrameBuffer.Height;
				Off=0;
				for(int y=0;y<m_FrameBuffer.Height;y++)
				{
					pBits-=Delta;
					for(int x=0;x<m_FrameBuffer.Width;x++)
					{
						((COLORREF*)m_FrameBuffer.Buffer)[Off]=_GET_DWORD(pBits+x*BytesPixel) & 0x00FFFFFF;
						Off++;
					}
				}
			}
			delete pIcon;
			DIBFile.Close();
			return true;
		}
		HeadOffset+=sizeof(IconDirEntry);
	}
	DIBFile.Close();
	return false;
}

void CWispDIB::Blt(const WISP_RECT&SrcRect,CWispDIB*pDesBIB,int x,int y)
{
	WISP_RECT ClipRC,DrawRC;
	if(m_FrameBuffer.Buffer==NULL)
		return;
	ClipRC.x = 0;
	ClipRC.y = 0;
	ClipRC.cx = pDesBIB->m_FrameBuffer.Width;
	ClipRC.cy = pDesBIB->m_FrameBuffer.Height;
	DrawRC.x = x;
	DrawRC.y = y;
	DrawRC.cx = SrcRect.cx;
	DrawRC.cy = SrcRect.cy;
	if(ClipRect(&DrawRC,&ClipRC)==false)
		return;
	for(int dy=0;dy<DrawRC.cy;dy++)
	{
		for(int dx=0;dx<DrawRC.cx;dx++)
		{
			((COLORREF*)pDesBIB->m_FrameBuffer.Buffer)[(y+dy)*pDesBIB->m_FrameBuffer.Width+x+dx] =
			((COLORREF*)m_FrameBuffer.Buffer)[(SrcRect.y+dy)*m_FrameBuffer.Width+SrcRect.x+dx];
		}
	}
}

void CWispDIB::BltTiled(CWispDIB*pDesBIB)
{
	WISP_RECT rc;
	if(m_FrameBuffer.Buffer==NULL)
		return;
	rc.x = rc.y = 0;	
	rc.cx = m_FrameBuffer.Width;
	rc.cy = m_FrameBuffer.Height;
	for(int x=0;x<pDesBIB->m_FrameBuffer.Width;x+=m_FrameBuffer.Width)
		for(int y=0;y<pDesBIB->m_FrameBuffer.Height;y+=m_FrameBuffer.Height)
			Blt(rc,pDesBIB,x,y);
}

void CWispDIB::Destroy()
{
	SafeDelete(m_FrameBuffer.Buffer);
	SafeDelete(m_Pal);
	if(m_bAutoDelete)
		delete this;
}

CWispDIBList::CWispDIBList()
{
	m_DIBList = NULL;
	m_RefCount = 0;
}

CWispDIBList::~CWispDIBList()
{
	Destroy();
}

bool CWispDIBList::Load(PCSTR FileName,int TileWidth,int TileHeight,int Count)
{
	int n;
	WISP_RECT Rect;
	CWispDIB WholeDIB;
	if(WholeDIB.Load(FileName)==false)
		return false;
	if(Count == 0)
		Count = (WholeDIB.m_FrameBuffer.Height*WholeDIB.m_FrameBuffer.Width) / (TileWidth * TileHeight);
	m_DIBList=new CWispDIB[Count];
	n=0;
	for(int y=0;y<WholeDIB.m_FrameBuffer.Height;y+=TileHeight)
	{
		for(int x=0;x<WholeDIB.m_FrameBuffer.Width&&n<Count;x+=TileWidth)
		{
			m_DIBList[n].Create(TileWidth,TileHeight,WISP_DIB_BITMAP);
			Rect.x=x;
			Rect.y=y;
			Rect.cx=TileWidth;
			Rect.cy=TileHeight;
			WholeDIB.Blt(Rect,&m_DIBList[n],0,0);
			n++;
		}
	}
	WholeDIB.Destroy();
	m_Count = Count;
	return true;
}

void CWispDIBList::Destroy()
{
	SafeDeleteAry(m_DIBList);
}

void CWispDIBList::SetType(UINT Type)
{
	for(int n=0;n<m_Count;n++)
		m_DIBList[n].SetType(Type);
}

void CWispDIBList::SetColorKey(COLORREF ColorKey)
{
	for(int n=0;n<m_Count;n++)
	{
		if(m_DIBList[n].m_Type!=WISP_DIB_TK)
			m_DIBList[n].SetType(WISP_DIB_TK);
		m_DIBList[n].SetColorKey(ColorKey);
	}
}

bool CWispDIBList::LoadIcon(PCSTR FileName)
{
	COLORREF*pColor;
	BYTE*pBits,*pIcon;
	int HeadOffset,Delta,Off,BytesPixel;
	ICON_DIR_ENTRY IconDirEntry;
	ICON_DIR	IconDir;
	CImageFile	DIBFile;

	DIBFile.ChangeFileIO(&gpCurWisp->m_PFSFileIO);
	if(gpCurWisp->m_PFSFileIO.GetFileAttr(FileName) & FIO_FA_COMPRESS)
	{
		int Size = (int)gpCurWisp->m_PFSFileIO.GetFileSize(FileName);
		if(Size<=0)
			return false;
		if(DIBFile.Create(Size)==false)
			return false;
		gpCurWisp->m_PFSFileIO.ReadFromFile(FileName,DIBFile.m_Buffer,Size);
	}
	else
	{
		if(DIBFile.Open(FileName)==false)
			return false;
	}
	DIBFile.ReadFile(&IconDir,sizeof(IconDir));
	if(IconDir.idType!=1||IconDir.idReserved!=0)
	{
		DIBFile.Close();
		return false;
	}
	m_Count = IconDir.idCount;
	m_DIBList = new CWispDIB[m_Count];
	HeadOffset = sizeof(IconDir);

	for(int n=0;n<m_Count;n++)
	{
		DIBFile.ReadFile(HeadOffset,&IconDirEntry,sizeof(IconDirEntry));
		m_DIBList[n].m_FrameBuffer.Width = IconDirEntry.bWidth;
		m_DIBList[n].m_FrameBuffer.Height = IconDirEntry.bHeight;
		m_DIBList[n].InitParam();
		m_DIBList[n].m_HotPT.x=m_DIBList[n].m_HotPT.y=0;
		m_DIBList[n].m_Type=WISP_DIB_TK;
		m_DIBList[n].m_ColorKey=0;
		BytesPixel = (IconDirEntry.wBitCount+7)/8;
		pIcon = new BYTE[IconDirEntry.dwBytesInRes];
		DIBFile.ReadFile(IconDirEntry.dwImageOffset,pIcon,IconDirEntry.dwBytesInRes);
		if(BytesPixel==0)
			BytesPixel = ( ((BITMAP_INFO_HEADER*)pIcon)->biBitCount+7 ) / 8;
		Delta=ALIGN_SIZE(m_DIBList[n].m_FrameBuffer.Width*BytesPixel,4);
		if(IconDirEntry.wBitCount==8)
		{//256 color
			pColor = (COLORREF*)(pIcon+sizeof(BITMAP_INFO_HEADER));
			pBits = pIcon+sizeof(BITMAP_INFO_HEADER)+sizeof(COLORREF)*256+Delta*m_DIBList[n].m_FrameBuffer.Height;
			m_DIBList[n].m_Pal = new COLORREF[256];
			for(int nClr=0;nClr<256;nClr++)
				m_DIBList[n].m_Pal[nClr]=pColor[nClr];
			Off=0;
			if(gpCurWisp->m_FrameBuffer.Bpp==8)
			{//screen is 256 color
				for(int y=0;y<m_DIBList[n].m_FrameBuffer.Height;y++)
				{
					pBits-=Delta;
					for(int x=0;x<m_DIBList[n].m_FrameBuffer.Width;x++)
					{
						((COLORREF*)m_DIBList[n].m_FrameBuffer.Buffer)[Off]=GET_BYTE(pBits,x);
						Off++;
					}
				}
			}
			else
			{//screen is tree color
				for(int y=0;y<m_DIBList[n].m_FrameBuffer.Height;y++)
				{
					pBits-=Delta;
					for(int x=0;x<m_DIBList[n].m_FrameBuffer.Width;x++)
					{
						((COLORREF*)m_DIBList[n].m_FrameBuffer.Buffer)[Off]=m_DIBList[n].m_Pal[GET_BYTE(pBits,x)];
						Off++;
					}
				}
			}
		}
		else
		{//16£¬24£¬32 bit tree color
			pBits = pIcon + sizeof(BITMAP_INFO_HEADER) + Delta*m_DIBList[n].m_FrameBuffer.Height;
			DIBFile.ReadFile(IconDirEntry.dwImageOffset,pIcon,IconDirEntry.dwBytesInRes);
			Off=0;
			for(int y=0;y<m_DIBList[n].m_FrameBuffer.Height;y++)
			{
				pBits-=Delta;
				for(int x=0;x<m_DIBList[n].m_FrameBuffer.Width;x++)
				{
					((COLORREF*)m_DIBList[n].m_FrameBuffer.Buffer)[Off]=_GET_DWORD(pBits+x*BytesPixel) & 0x00FFFFFF;
					Off++;
				}
			}
		}
		delete pIcon;
		HeadOffset+=sizeof(IconDirEntry);
	}
	DIBFile.Close();
	return true;
}

