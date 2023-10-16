#ifndef _SYSER_CONNECT_H_
#define _SYSER_CONNECT_H_

class CSyserConnect
{
public:
	CSyserConnect();
	~CSyserConnect();
public:
	virtual bool	Init() = 0;
	virtual void	Release() = 0;
	virtual int		RecvData(void*Buffer,int BufSize) = 0;
	virtual int		SendData(void*Buffer,int BufSize) = 0;
	virtual	int		RecvDataBuffer();
	BYTE*	m_Buffer;
	int		m_MaxBufSize;
	int		m_BufSize;
};


#endif
