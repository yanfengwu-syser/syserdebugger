#ifndef _PIC_8259_H_
#define _PIC_8259_H_

#ifdef __cplusplus
extern "C" {
#endif


VOID SyserEnablePIC8259HardWareInterrupt(DWORD arg);
VOID SyserSet8259EOI(DWORD dwInterruptNum);
extern BYTE gdwPIC8259Shield_1;
extern BYTE gdwPIC8259Shield_2;

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //_PIC_8259_H_