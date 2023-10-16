#ifndef _HARDWAREINTERRUPTCTRL_H_
#define _HARDWAREINTERRUPTCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

void SetInteruptEOI(DWORD dwInterruptNum);
VOID SyserEnableAllHardInterrupt(VOID);
void EnableHardWareInterrupt(INT arg);
VOID SyserDisableAllHardInterrupt(VOID);
extern bool gbIsSaveInterruptShieldRegister;

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //_HARDWAREINTERRUPTCTRL_H_