#include "StdAfx.h"
#include "TXTFile.h"

NAME_SPACE_BEGIN

CTXTFile::CTXTFile()
{
}

CTXTFile::~CTXTFile()
{
	for(TTXTStrList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
		delete *Iter;
	m_StrList.Clear();
}

bool CTXTFile::Open(PCSTR FileName,HANDLE*pHandleOpen)
{
	char*FileBuffer;
	if(CImageFile::Open(FileName,pHandleOpen)==false)
		return false;
	FileBuffer=new CHAR[m_FileSize+1];
	FileBuffer[m_FileSize]=0;
	ReadFile(0,FileBuffer,m_FileSize);
	if(_GET_WORD(FileBuffer)==0xFEFF)
	{
		delete FileBuffer;
		Close();
		return false;
	}
	SplitLine(FileBuffer,m_FileSize);
	delete FileBuffer;
	return true;
}

int CTXTFile::SplitLine(PCSTR FileBuffer,ULLSIZE BufferSize)
{
	ULPOS nBegin,nEnd,nOffset;
	char*szLine;

	nBegin=nOffset=0;
	while(nOffset<BufferSize)
	{
		if(FileBuffer[nOffset]=='\r' || FileBuffer[nOffset]=='\n')
		{
			nEnd = nOffset;
			if(FileBuffer[nOffset]=='\r' && FileBuffer[nOffset+1]=='\n')
				nOffset=nEnd+2;
			else
				nOffset++;
			szLine=new char[nEnd-nBegin+1];
			TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
			szLine[nEnd-nBegin]=0;
			m_StrList.Append(szLine);
			nBegin=nOffset;
		}
		else
		{
			nOffset++;
		}
	}
	if(nOffset!=nBegin)
	{
		nEnd = nOffset;
		szLine=new char[nEnd-nBegin+1];
		TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
		szLine[nEnd-nBegin]=0;
		m_StrList.Append(szLine);
	}
	return m_StrList.Count();
}

bool CTXTFile::Open(PCSTR szTXTBuffer,ULLSIZE BufSize)
{
	SplitLine(szTXTBuffer,BufSize);
	return true;
}

bool CTXTFile::Save(PCSTR FileName)
{
	ULSIZE	Length;
	char*FileBuffer,*pStr;
	bool bClose=false;
	if(TStrCmp(FileName,(PCSTR)m_ImageName)==0)
	{
		CImageFile::Close();
		bClose=true;
	}

	Length=0;
	for(TTXTStrList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
		Length=Length+TStrLen(*Iter)+sizeof("\r\n")-1;

	FileBuffer=new char[Length+1];
	FileBuffer[Length]=0;
	pStr=FileBuffer;
	for(TTXTStrList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
	{
		TStrCpy(pStr,*Iter);
		TStrCat(pStr,"\r\n");
		pStr+=TStrLen(pStr);
	}
	m_pFileIO->WriteToFile(FileName,FileBuffer,Length);
	if(bClose)
		return CImageFile::Open(FileName);
	return true;
}

void CTXTFile::Close()
{
	CImageFile::Close();
	for(TTXTStrList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
		delete *Iter;
	m_StrList.Clear();
}

bool CTXTFile::Insert(ULPOS nLine,ULPOS nCol,char*szBuffer)
{
	ULPOS nBegin,nEnd,nOffset;
	ULSIZE Length;
	char*FileBuffer,*pStr,*szLine;
	TTXTStrList::IT Iter=m_StrList.Begin();
	while(nLine)
	{
		if(Iter==m_StrList.End())
			return false;
		nLine--;		
		Iter++;
	}
	Length=TStrLen(*Iter);
	if(Length<=nCol)
		return false;
	Length+=TStrLen(szBuffer);
	FileBuffer = new char[Length+1];
	pStr=FileBuffer;
	TStrNCpy(pStr,*Iter,nCol);
	pStr[nCol]=0;
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,szBuffer);
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,&(*Iter)[nCol]);
	delete *Iter;
	TTXTStrList::IT DelIter;
	DelIter=Iter;
	Iter++;
	m_StrList.Remove(DelIter);

	nOffset=0;
	nBegin=0;
	while(nOffset<Length)
	{
		if(FileBuffer[nOffset]=='\r' || FileBuffer[nOffset]=='\n')
		{
			nEnd = nOffset;
			if(FileBuffer[nOffset]=='\r' && FileBuffer[nOffset+1]=='\n')
				nOffset=nEnd+2;
			else
				nOffset++;
			szLine=new char[nEnd-nBegin+1];
			TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
			szLine[nEnd-nBegin]=0;
			m_StrList.InsertAfter(Iter,szLine);
			nBegin=nOffset;
		}
		else
		{
			nOffset++;
		}
	}
	delete FileBuffer;
	return true;
}

bool CTXTFile::Replace(ULPOS nLine,ULPOS nCol,char*szBuffer,ULSIZE Replen)
{
	ULPOS nBegin,nEnd,nOffset;
	ULSIZE Length;
	char*FileBuffer,*pStr,*szLine;

	TTXTStrList::IT Iter=m_StrList.Begin();
	while(nLine)
	{
		if(Iter==m_StrList.End())
			return false;
		nLine--;
		Iter++;
	}
	Length=TStrLen(*Iter);
	if(Length<=nCol+Replen)
		return false;
	Length+=TStrLen(szBuffer);
	FileBuffer = new char[Length+1];
	pStr=FileBuffer;
	TStrNCpy(pStr,*Iter,nCol);
	pStr[nCol]=0;
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,szBuffer);
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,&(*Iter)[nCol+Replen]);
	delete *Iter;
	TTXTStrList::IT DelIter;
	DelIter=Iter;
	Iter++;
	m_StrList.Remove(DelIter);

	nOffset=0;
	nBegin=0;
	while(nOffset<Length)
	{
		if(FileBuffer[nOffset]=='\r' || FileBuffer[nOffset]=='\n')
		{
			nEnd = nOffset;
			if(FileBuffer[nOffset]=='\r' && FileBuffer[nOffset+1]=='\n')
				nOffset=nEnd+2;
			else
				nOffset++;
			szLine=new char[nEnd-nBegin+1];
			TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
			szLine[nEnd-nBegin]=0;
			m_StrList.InsertAfter(Iter,szLine);
			nBegin=nOffset;
		}
		else
		{
			nOffset++;
		}
	}
	delete FileBuffer;
	return true;
}

//////////////////////////////////////////////////////////Unicode/////////////////////////////////////////////////////////////////////////

CUTXTFile::CUTXTFile()
{
}

CUTXTFile::~CUTXTFile()
{
	for(TTXTStrWList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
		delete *Iter;
	m_StrList.Clear();
}

bool CUTXTFile::Open(PCSTR FileName,HANDLE*pHandleOpen)
{
	BYTE*FileBuffer;
	if(CImageFile::Open(FileName,pHandleOpen)==false)
		return false;
	FileBuffer=new BYTE[m_FileSize+2];
	FileBuffer[m_FileSize]=0;
	FileBuffer[m_FileSize+1]=0;
	ReadFile(0,FileBuffer,m_FileSize);
	if(_GET_WORD(FileBuffer)!=0xFEFF)
	{
		delete FileBuffer;
		Close();
		return false;
	}
	SplitLine((PCWSTR)&FileBuffer[2],m_FileSize);
	delete FileBuffer;
	return true;
}

int CUTXTFile::SplitLine(PCWSTR FileBuffer,ULLSIZE BufferSize)
{
	ULPOS nBegin,nEnd,nOffset;
	WCHAR*szLine;

	nBegin=nOffset=0;
	while(nOffset<BufferSize/2)
	{
		if(FileBuffer[nOffset]=='\r' || FileBuffer[nOffset]=='\n')
		{
			nEnd = nOffset;
			if(FileBuffer[nOffset]=='\r' && FileBuffer[nOffset+1]=='\n')
				nOffset=nEnd+2;
			else
				nOffset++;
			szLine=new WCHAR[nEnd-nBegin+1];
			TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
			szLine[nEnd-nBegin]=0;
			m_StrList.Append(szLine);
			nBegin=nOffset;
		}
		else
		{
			nOffset++;
		}
	}
	if(nOffset!=nBegin)
	{
		nEnd = nOffset;
		szLine=new WCHAR[nEnd-nBegin+1];
		TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
		szLine[nEnd-nBegin]=0;
		m_StrList.Append(szLine);
	}
	return m_StrList.Count();
}

bool CUTXTFile::Open(PCWSTR szTXTBuffer,ULLSIZE BufSize)
{
	SplitLine(szTXTBuffer,BufSize);
	return true;
}

bool CUTXTFile::Save(PCSTR FileName)
{
	ULSIZE	Length;
	WCHAR*FileBuffer,*pStr;
	bool bClose=false;
	if(TStrCmp(FileName,(PCSTR)m_ImageName)==0)
	{
		CImageFile::Close();
		bClose=true;
	}

	Length=0;
	for(TTXTStrWList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
		Length=Length+TStrLen(*Iter)+sizeof("\r\n")-1;

	FileBuffer=new WCHAR[Length+1];
	FileBuffer[Length]=0;
	pStr=FileBuffer;
	for(TTXTStrWList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
	{
		TStrCpy(pStr,*Iter);
		TStrCat(pStr,"\r\n");
		pStr+=TStrLen(pStr);
	}
	m_pFileIO->WriteToFile(FileName,FileBuffer,Length*2);
	if(bClose)
		return CImageFile::Open(FileName);
	return true;
}

void CUTXTFile::Close()
{
	CImageFile::Close();
	for(TTXTStrWList::IT Iter=m_StrList.Begin();Iter!=m_StrList.End();Iter++)
		delete *Iter;
	m_StrList.Clear();
}

bool CUTXTFile::Insert(ULPOS nLine,ULPOS nCol,WCHAR*szBuffer)
{
	ULPOS nBegin,nEnd,nOffset;
	ULSIZE Length;
	WCHAR*FileBuffer,*pStr,*szLine;
	TTXTStrWList::IT Iter=m_StrList.Begin();
	while(nLine)
	{
		if(Iter==m_StrList.End())
			return false;
		nLine--;		
		Iter++;
	}
	Length=TStrLen(*Iter);
	if(Length<=nCol)
		return false;
	Length+=TStrLen(szBuffer);
	FileBuffer = new WCHAR[Length+1];
	pStr=FileBuffer;
	TStrNCpy(pStr,*Iter,nCol);
	pStr[nCol]=0;
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,szBuffer);
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,&(*Iter)[nCol]);
	delete *Iter;
	TTXTStrWList::IT DelIter;
	DelIter=Iter;
	Iter++;
	m_StrList.Remove(DelIter);

	nOffset=0;
	nBegin=0;
	while(nOffset<Length)
	{
		if(FileBuffer[nOffset]=='\r' || FileBuffer[nOffset]=='\n')
		{
			nEnd = nOffset;
			if(FileBuffer[nOffset]=='\r' && FileBuffer[nOffset+1]=='\n')
				nOffset=nEnd+2;
			else
				nOffset++;
			szLine=new WCHAR[nEnd-nBegin+1];
			TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
			szLine[nEnd-nBegin]=0;
			m_StrList.InsertAfter(Iter,szLine);
			nBegin=nOffset;
		}
		else
		{
			nOffset++;
		}
	}
	delete FileBuffer;
	return true;
}

bool CUTXTFile::Replace(ULPOS nLine,ULPOS nCol,WCHAR*szBuffer,ULSIZE Replen)
{
	ULPOS nBegin,nEnd,nOffset;
	ULSIZE Length;
	WCHAR*FileBuffer,*pStr,*szLine;

	TTXTStrWList::IT Iter=m_StrList.Begin();
	while(nLine)
	{
		if(Iter==m_StrList.End())
			return false;
		nLine--;
		Iter++;
	}
	Length=TStrLen(*Iter);
	if(Length<=nCol+Replen)
		return false;
	Length+=TStrLen(szBuffer);
	FileBuffer = new WCHAR[Length+1];
	pStr=FileBuffer;
	TStrNCpy(pStr,*Iter,nCol);
	pStr[nCol]=0;
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,szBuffer);
	pStr+=TStrLen(pStr);
	TStrCpy(pStr,&(*Iter)[nCol+Replen]);
	delete *Iter;
	TTXTStrWList::IT DelIter;
	DelIter=Iter;
	Iter++;
	m_StrList.Remove(DelIter);

	nOffset=0;
	nBegin=0;
	while(nOffset<Length)
	{
		if(FileBuffer[nOffset]=='\r' || FileBuffer[nOffset]=='\n')
		{
			nEnd = nOffset;
			if(FileBuffer[nOffset]=='\r' && FileBuffer[nOffset+1]=='\n')
				nOffset=nEnd+2;
			else
				nOffset++;
			szLine=new WCHAR[nEnd-nBegin+1];
			TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
			szLine[nEnd-nBegin]=0;
			m_StrList.InsertAfter(Iter,szLine);
			nBegin=nOffset;
		}
		else
		{
			nOffset++;
		}
	}
	delete FileBuffer;
	return true;
}

NAME_SPACE_END
