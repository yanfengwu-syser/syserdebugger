#ifndef _SYSER_C_ABI_
#define _SYSER_C_ABI_

#ifdef __cplusplus
extern "C" {
#endif

//
//	CSyser
//

VOID SyserAttachPopupProcess(DWORD dwCR3);

//
//	CSyser -> CDbgProcess -> HandleInt1
//

bool SyserDbgProcessHandleInt1(ULPOS Address);

//
//	CSyser -> CDbgProcess -> HandleInt3
//

bool SyserDbgProcessHandleInt3(ULPOS Address);

//
//	CSyser
//

bool SyserIsgpSyserValid(VOID);

//
//	CSyser -> m_bDbgRegAccessMon
//

bool SyserGetIsDbgRegAccessMon(VOID);
VOID SyserSetIsDbgRegAccessMon(bool newValue);

//
//	CSyser -> m_bUpdateReg
//

bool SyserGetbUpdateReg(VOID);
VOID SyserSetbUpdateReg(bool newValue);

//
//	CSyser -> InstallDebug()
//
bool SyserGetInstallDebug(VOID);

//
//	CSyser -> DbgPrint()
//

VOID SyserDbgPrint(int x,int y,IN WCHAR*Format,...);

//
//	CSyser -> m_bInitSuccess
//

bool SyserGetbInitSuccess(VOID);

//
//	gpSyser != NULL
//

bool SyserbIsgpSyserValid(VOID);

//
//	CSyser -> m_SysInfo -> m_SyserBase
//

ULONG_PTR	SyserGetSysInfoSyserBase(VOID);

//
//	CSyser -> m_SysInfo -> m_SyserHighBase
//

ULONG_PTR	SyserGetSysInfoSyserHighBase(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif