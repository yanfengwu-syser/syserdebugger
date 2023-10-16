#ifndef _NMIINTERRUPTHANDLE_H_
#define _NMIINTERRUPTHANDLE_H_

#ifdef __cplusplus
extern "C" {
#endif

VOID SyserLoadContext(VOID);
VOID SyserEnterLoop(DWORD* dwPtr);
VOID	SyserNMIInterruptService(VOID);
VOID	SyserEnterLoop(DWORD* dwPtr);
void	UpdateOtherCPUDRX();
VOID	SyserSaveSyserDRX(VOID);
VOID	SyserSaveSyserDRXNew(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //_NMIINTERRUPTHANDLE_H_
