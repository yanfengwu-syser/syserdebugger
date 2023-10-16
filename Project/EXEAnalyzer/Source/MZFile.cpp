#include "StdAfx.h"
#include "MZFile.h"

CMZFile::CMZFile()
{
	
}

void CMZFile::Close()
{
	CImageFile::Close();
}

bool CMZFile::Open(PCSTR FileName,HANDLE*pHandleOpen)
{
	if(CImageFile::Open(FileName,pHandleOpen)==FALSE)
		return FALSE;
	////是否是MZ文件//////////////////////
	if(!ReadFile(0,&m_MZHead,sizeof(m_MZHead)))
		return FALSE;
	if(m_MZHead.Signature!=0x4D5A && m_MZHead.Signature!=0x5A4D)
	{
		CImageFile::Close();
		return FALSE;
	}
	m_ImageBase=0x10000;
	m_ImageSize=m_MZHead.nPage*512+m_MZHead.cbLastPage-m_MZHead.cpHead*16;
	m_EntryPoint=m_MZHead.CS*16+m_MZHead.IP;
	return TRUE;
}

ULSIZE CMZFile::ReadImageMemory(IN ULPOS Address,OUT void* Buffer,IN ULSIZE Size)
{
	MZRELOC Reloc;
	ULPOS Pos=m_MZHead.cpHead*16;
	ULPOS ImageHighBase=m_ImageBase+m_ImageSize;
	if(Size>(int)(ImageHighBase-Address))
		Size=ImageHighBase-Address;
	if(!ReadFile(Pos+Address-m_ImageBase,Buffer,Size))
		return 0;
	if((DWORD)(m_MZHead.fpReloc+m_MZHead.nReloc*4)>m_FileSize)
		return 0;
	for(WORD n=0;n<m_MZHead.nReloc;n++)
	{
		if(!ReadFile(m_MZHead.fpReloc+n*sizeof(Reloc),&Reloc,sizeof(Reloc)))
		Pos=Reloc.Segment*16+Reloc.Offset;
		if(Pos>=Address && Pos<Address+Size)
			PUT_WORD(Buffer,Pos-Address,GET_WORD(Buffer,Pos-Address)+(WORD)(m_ImageBase/16));
	}
	return Size;
}

