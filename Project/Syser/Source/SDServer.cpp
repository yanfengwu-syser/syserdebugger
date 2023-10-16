#include "StdAfx.h"
#include "Syser.h"
#include "SDServer.h"

CSDServer::CSDServer()
{
	m_bWorking = false;
	m_pRes = NULL;
}

CSDServer::~CSDServer()
{

}

bool CSDServer::Init(CSyserConnect*pConnect)
{
	m_pConnect = pConnect;
	m_RemoteTermWnd.Create(NULL,0,0,0,0,NULL,0,WISP_WS_VIRTUAL);
	m_RemoteTermWnd.AttachConsole(&gpSyser->m_MainFrame.m_ConsoleWnd);
	m_pRes = (SD_PACKET*)new BYTE[SD_MAX_LENGTH];
	m_pRes->Sign = SD_RES_SIGN;
	m_Stream.m_Length = 0;
	m_Stream.m_Buffer = (void*)m_pRes->Data.CSStream;;
	m_RemoteTermWnd.m_pStream = &m_Stream;
	return true;
}

void CSDServer::Release()
{
	SafeDelete(m_pRes);
	m_RemoteTermWnd.Destroy();
}

void CSDServer::StartServer()
{
	m_bWorking = true;
	while(m_bWorking && IS_CTRL_BREAK==false)
	{
		if(WaitForCmd())
			DoCommand();
	}
}

bool CSDServer::SendCmdResCSStream()
{
	int Size;
	BYTE*Buffer;
	m_pRes->Length = ST_FIELD_OFF(SD_PACKET,Data.CSStream[0])+m_Stream.m_Length+4;
	m_pRes->Data.CSStream[m_Stream.m_Length/4]=0;
	m_pRes->CRCCode = 0;
	m_pRes->CRCCode = GetCRCCode((BYTE*)m_pRes,m_pRes->Length);
	Buffer = (BYTE*) m_pRes;
	Size = 0;
	while(Size<m_pRes->Length)
	{
		Size+=m_pConnect->SendData(&Buffer[Size],m_pRes->Length-Size);
	}
	return true;
}

void CSDServer::DoCommand()
{
	OUTPUT(WSTR("SDServer : cmd %s\n"),m_pCmd->Data.szCmd);
	m_Stream.m_Length = 0;
	m_RemoteTermWnd.TermRunCmd(m_pCmd->Data.szCmd);
	SendCmdResCSStream();
	//m_bWorking = false;
}

bool CSDServer::WaitForCmd()
{
	int NeededSize;
	NeededSize = sizeof(SD_PACKET);
	m_pCmd = NULL;
	m_pConnect->m_BufSize = 0;
	while(m_bWorking && IS_CTRL_BREAK==false && m_pConnect->m_BufSize < NeededSize)
	{
		m_pConnect->RecvDataBuffer();
		if(m_pCmd == NULL && m_pConnect->m_BufSize>=sizeof(SD_PACKET))
		{
			m_pCmd = (SD_PACKET*)m_pConnect->m_Buffer;
			if(m_pCmd->Length > SD_MAX_LENGTH)
				return false;
			if(m_pCmd->Sign!=SD_CMD_SIGN)
				return false;
			NeededSize = m_pCmd->Length;
		}
	}
	return m_pConnect->m_BufSize >= NeededSize;
}

