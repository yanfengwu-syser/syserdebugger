#include "StdAfx.h"
#include "CodeDoc.h"

CCodeDoc::CCodeDoc()
{
	m_DocRangeStart = 0;
	m_DocRangeEnd = 0xFFFFFFFF;
	m_bIsOpened = false;
}

CCodeDoc::~CCodeDoc()
{

}

bool CCodeDoc::Open(PCSTR Name)
{
	m_bIsOpened = true;
	return true;
}

void CCodeDoc::Close()
{
	m_bIsOpened = false;
}

bool CCodeDoc::GetSymbol(ULPOS Address,WCHAR*szSymbol,int BufSize)
{
	return false;
}

bool CCodeDoc::GetComment(ULPOS Address,WCHAR*szComment,int BufSize)
{
	return false;
}

bool CCodeDoc::SetComment(ULPOS Address,WCHAR*szComment)
{
	return false;
}

bool CCodeDoc::GetLabel(ULPOS Address,WCHAR*szLabel,int BufSize)
{
	return GetSymbol(Address,szLabel,BufSize);
}

UINT CCodeDoc::GetLineMark(ULPOS Address)
{
	return CV_MARK_NULL;
}

