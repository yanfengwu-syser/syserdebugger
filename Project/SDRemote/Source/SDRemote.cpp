#include "StdAfx.h"
#include "SDRemote.h"

CSyserPluginUI*gpSyserPluginUI;

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

bool WriteFileBlock(HANDLE hFile,void*Buffer,int Size,int BlockSize)
{
	DWORD cbRW;
	int nBlock,LeftSize,Offset;
	nBlock = PAGE_COUNT(Size,BlockSize);
	Offset = 0;
	LeftSize = Size%BlockSize;
	for(int n=1;n<nBlock;n++)
	{
		WriteFile(hFile,(BYTE*)Buffer+Offset,BlockSize,&cbRW,NULL);
		Offset+=BlockSize;
	}
	if(LeftSize)
		WriteFile(hFile,(BYTE*)Buffer+Offset,LeftSize,&cbRW,NULL);
	return true;
}


int sd_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSDRemote *pDebugger)
{
	DWORD cbRW;
	BYTE*Buffer;
	PCWSTR pszCmd;
	SD_PACKET*pPacket;
	if(argc==1)
	{
		OUTPUT(WSTR("Usage : sd cmd_string\n"));
		return 1;
	}
	pszCmd = &szCommandLine[argv[1]-argv[0]];
	Buffer = new BYTE[SD_MAX_LENGTH];
	pPacket = (SD_PACKET*)Buffer;
	pPacket->Length = ST_FIELD_OFF(SD_PACKET,Data.szCmd[0])+(TStrLen(pszCmd)+1)*sizeof(WCHAR);
	pPacket->Sign = SD_CMD_SIGN;
	pPacket->CRCCode=0;
	TStrCpy(pPacket->Data.szCmd,pszCmd);
	pPacket->CRCCode=GetCRCCode(Buffer,pPacket->Length);
	WriteFileBlock(pDebugger->m_hPipe,Buffer,pPacket->Length,0x10);

	int NeededSize = sizeof(SD_PACKET);
	int Size = 0;
	if(ReadFile(pDebugger->m_hPipe,Buffer,sizeof(SD_PACKET),&cbRW,NULL))
		Size+=(int)cbRW;
	while(Size < NeededSize)
	{
		if(ReadFile(pDebugger->m_hPipe,&Buffer[Size],NeededSize-Size,&cbRW,NULL))
			Size+=(int)cbRW;
		if(Size>=sizeof(SD_PACKET) && NeededSize == sizeof(SD_PACKET))
		{
			NeededSize = pPacket->Length;
		}
	}
	if(pPacket->Data.CSStream[0])
	{
		gpSyserPluginUI->Output(pPacket->Data.CSStream);
	}
	delete Buffer;
	return 0;
}


CDebugger*CreateDebugger(void*UIObj)
{
	CSDRemote*pDebugger = new CSDRemote;
	gpSyserPluginUI = (CSyserPluginUI*)UIObj;
	gpSyserPluginUI->InsertCmd(WSTR("sd"),(FPCmd)sd_command,pDebugger,WSTR("Remote command"),NULL);
	return pDebugger;
}

void GetFileFilter(WCHAR*szFilte)
{
	*szFilte=0;
}

void GetInfo(CHAR*szInfo)
{
	TStrCpy(szInfo,"Syser Remote Debugger");
#ifdef _DEBUG
	TStrCat(szInfo,"(DEBUG)");
#endif
}

bool CSDRemote::LoadPage(IN ULPOS Address,OUT void* Buffer)
{
	return ReadProcessMemory(Address,Buffer,MP_SIZE);
}

bool CSDRemote::SavePage(IN ULPOS Address,OUT void* Buffer)
{
	return WriteProcessMemory(Address,Buffer,MP_SIZE);
}

DWORD CSDRemote::GetPageAttribute(IN ULPOS Address)
{
	return true;
}

CSDRemote::CSDRemote()
{
	m_ImageBase = 0;
	m_ImageHighBase = 0xFFFFFFFF;
	m_ImageSize = 0xFFFFFFFF;
}

CSDRemote::~CSDRemote()
{

}

bool CSDRemote::Open(PCSTR ModuleName)
{
	STZeroMemory(m_Context);
	OUTPUT(WSTR("SDRemote : open \\\\.\\pipe\\com_1\n"));
	m_hPipe = CreateFile("\\\\.\\pipe\\com_1",GENERIC_WRITE|GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	if(m_hPipe == INVALID_HANDLE_VALUE)
		return false;
	if(CX86Debugger::Open(ModuleName)==false)
		return false;
	m_ProcessCache.Init(100,PMS_PAGE_OUT);
	if(m_ProcessCache.MapImage(this)==false)
		return false;
	return true;
}

bool CSDRemote::Close()
{
	if(m_hPipe!=INVALID_HANDLE_VALUE)
		CloseHandle(m_hPipe);
	m_ProcessCache.Release();
	return CX86Debugger::Close();
}

void CSDRemote::Release()
{
	CX86Debugger::Release();
	gpSyserPluginUI->RemoveCmd(WSTR("sd"));
	delete this;
}

bool CSDRemote::ReadProcessMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return 0;
}

bool CSDRemote::WriteProcessMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return 0;
}

ULSIZE CSDRemote::WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return 0;
}

ULSIZE CSDRemote::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return 0;
}


bool CSDRemote::SetSingleStep()
{
	return CX86Debugger::SetSingleStep();
}

bool CSDRemote::RemoveSingleStep()
{
	return CX86Debugger::RemoveSingleStep();
}

bool CSDRemote::UpdateRegister()
{
	return false;
}

bool CSDRemote::SaveRegister()
{
	return false;
}

bool CSDRemote::ContinueDebug()
{
	return false;
}

void CSDRemote::GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID)
{
	GetX86RegPtr(pCPURegPtr);
}
void CSDRemote::GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr)
{
	static DWORD Value;
	pCPURegPtr->pCS = (WORD*)&m_Context.CS;
	pCPURegPtr->pDS = (WORD*)&m_Context.DS;
	pCPURegPtr->pES = (WORD*)&m_Context.ES;
	pCPURegPtr->pFS = (WORD*)&m_Context.FS;
	pCPURegPtr->pGS = (WORD*)&m_Context.GS;
	pCPURegPtr->pSS = (WORD*)&m_Context.SS;
	pCPURegPtr->pEAX = (DWORD*)&m_Context.EAX;
	pCPURegPtr->pEBX = (DWORD*)&m_Context.EBX;
	pCPURegPtr->pECX = (DWORD*)&m_Context.ECX;
	pCPURegPtr->pEDX = (DWORD*)&m_Context.EDX;
	pCPURegPtr->pESI = (DWORD*)&m_Context.ESI;
	pCPURegPtr->pEDI = (DWORD*)&m_Context.EDI;
	pCPURegPtr->pEBP = (DWORD*)&m_Context.EBP;
	pCPURegPtr->pESP = (DWORD*)&m_Context.ESP;
	pCPURegPtr->pEFL = (EFL_REG*)&m_Context.EFL;
	pCPURegPtr->pEIP = (DWORD*)&m_Context.EIP;
	pCPURegPtr->pDR[0] = (DWORD*)&m_Context.DR[0];
	pCPURegPtr->pDR[1] = (DWORD*)&m_Context.DR[1];
	pCPURegPtr->pDR[2] = (DWORD*)&m_Context.DR[2];
	pCPURegPtr->pDR[3] = (DWORD*)&m_Context.DR[3];
	pCPURegPtr->pDR[4] = NULL;
	pCPURegPtr->pDR[5] = NULL;
	pCPURegPtr->pDR[6] = (DWORD*)&m_Context.DR[6];
	pCPURegPtr->pDR[7] = (DWORD*)&m_Context.DR[7];
}

bool CSDRemote::GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD *pSize)
{
	return false;
}

