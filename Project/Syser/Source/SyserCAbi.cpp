#include "StdAfx.h"
#include "Syser.h"
#include "SyserCAbi.h"

//
//	CSyser
//

VOID SyserAttachPopupProcess(DWORD dwCR3)
{
	gpSyser->AttachPopupProcess(dwCR3);
}

//
//	CSyser -> CDbgProcess
//

bool SyserDbgProcessHandleInt1(ULPOS Address)
{
	return gpSyser->m_pDebugger->HandleInt1(Address);
}

bool SyserDbgProcessHandleInt3(ULPOS Address)
{
	return gpSyser->m_pDebugger->HandleInt3(Address);
}

bool SyserIsgpSyserValid()
{
	return (gpSyser != NULL);
}

bool SyserGetIsDbgRegAccessMon(VOID)
{
	return gpSyser->m_bDbgRegAccessMon;
}

VOID SyserSetIsDbgRegAccessMon(bool newValue)
{
	gpSyser->m_bDbgRegAccessMon = newValue;
}

bool SyserGetbUpdateReg(VOID)
{
	return gpSyser->m_bUpdateReg;
}

VOID SyserSetbUpdateReg(bool newValue)
{
	gpSyser->m_bUpdateReg = newValue;
}

bool SyserGetInstallDebug(VOID)
{
	return gpSyser->InstallDebug();
}

VOID SyserDbgPrint(int x,int y,IN WCHAR*Format,...)
{
	va_list Next;
	WCHAR szBuffer[0x200];

	va_start(Next,Format);
	TVSPrintf(szBuffer,Format,Next);
	va_end(Next);

	gpSyser->DbgPrint(x,y,szBuffer);
}

bool SyserGetbInitSuccess(VOID)
{
	return gpSyser->m_bInitSuccess;
}

bool SyserbIsgpSyserValid(VOID)
{
	return (bool)(gpSyser != NULL);
}

ULONG_PTR	SyserGetSysInfoSyserBase(VOID)
{
	return gpSyser->m_SysInfo.m_SyserBase;
}

ULONG_PTR	SyserGetSysInfoSyserHighBase(VOID)
{
	return gpSyser->m_SysInfo.m_SyserHighBase;
}