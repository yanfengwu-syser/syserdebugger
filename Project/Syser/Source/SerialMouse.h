#ifndef _SERIALMOUSE_H_H
#define _SERIALMOUSE_H_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _stSerialMouse
{
	WORD wSerialPort;
	DWORD dwHardwareNum;
	BYTE byteDataLen;
}stSerialMouse;
VOID SyserSerialMouseInterruptService(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif


#endif //_SERIALMOUSE_H_H