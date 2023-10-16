#ifndef _INTERRUPTPATCH_H_
#define _INTERRUPTPATCH_H_

#include "X86Define.h"
#define MAX_INTERRUPT_STUB 256

#include <pshpack1.h>
typedef struct _INTERRUPT_STUB
{
	BYTE PushPCode;
	DWORD OldInterruptAddress;
	BYTE PushPCode2;
	DWORD OwnerInterruptAddress;
	BYTE RetPCode;
	BYTE InterruptVector;
	DWORD IDTBaseAddress;
	X86_GATE_DECR GateDecr;
}INTERRUPT_STUB,*PINTERRUPT_STUB;
#include <poppack.h>

extern INTERRUPT_STUB gInterruptStub[MAX_INTERRUPT_STUB];
DWORD GetOrgInterruptAddress(PINTERRUPT_STUB pStub);
void InitInterruptStub();
void ReleaseInterruptStub(PINTERRUPT_STUB IStub);
PINTERRUPT_STUB GetInterruptStub();

#endif //_INTERRUPTPATCH_H_