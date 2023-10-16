#include "StdAfx.h"
#include "Syser.h"
#include "SyserConnect.h"


CSyserConnect::CSyserConnect()
{

}

CSyserConnect::~CSyserConnect()
{

}

int CSyserConnect::RecvDataBuffer()
{
	int Size;
	if(m_BufSize>=m_MaxBufSize)
		m_BufSize = 0;
	Size = RecvData(&m_Buffer[m_BufSize],m_MaxBufSize-m_BufSize);
	m_BufSize+=Size;
	return Size;
}
