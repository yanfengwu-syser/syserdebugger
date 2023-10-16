#ifndef _SD_SERVER_H_
#define _SD_SERVER_H_

#include "SDDefine.h"
#include "SyserConnect.h"

class CSDServer;
class CSDStream : public ALTFileStream
{
public:
	void*	m_Buffer;
	int		m_Length;
	int	Puts(void*Buffer,int Size)
	{
		if(m_Length>=SD_MAX_LENGTH)
			return 0;
		if(m_Length+Size>SD_MAX_LENGTH)
			Size=SD_MAX_LENGTH-m_Length;
		memcpy(RT_PVOID(m_Buffer,m_Length),Buffer,Size);
		m_Length+=Size;
		return Size;
	}
	int	Gets(void*Buffer,int Size){return 0;}
};

class CSDServer
{
public:
	CSDServer();
	~CSDServer();
public:
	bool	Init(CSyserConnect*pConnect);
	void	Release();
	void	StartServer();
	void	DoCommand();
	bool	WaitForCmd();
	bool	SendCmdResCSStream();
public:
	bool	m_bWorking;
	CSDStream m_Stream;
	SD_PACKET*m_pRes;
	SD_PACKET*m_pCmd;
	CSyserConnect*m_pConnect;
	CWispTerminalWnd m_RemoteTermWnd;
};


#endif
