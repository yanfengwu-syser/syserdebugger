#include "StdAfx.h"
#include "InterruptPatch.h"

INTERRUPT_STUB gInterruptStub[MAX_INTERRUPT_STUB];

void InitInterruptStub()
{
	ZeroMemory(gInterruptStub,sizeof(gInterruptStub));
	for(int i = 0; i < MAX_INTERRUPT_STUB; i++)
	{
		gInterruptStub[i].RetPCode=0xc3;
		gInterruptStub[i].PushPCode=0x68;
		gInterruptStub[i].PushPCode2=0x68;
	}
}

PINTERRUPT_STUB GetInterruptStub()
{
	for(int i = 0; i < MAX_INTERRUPT_STUB; i++)
	{
		if(gInterruptStub[i].OldInterruptAddress==0 &&gInterruptStub[i].InterruptVector==0&&gInterruptStub[i].IDTBaseAddress==0)
		{
			return &gInterruptStub[i];
		}
	}
	return NULL;
}
DWORD GetOrgInterruptAddress(PINTERRUPT_STUB pStub)
{
	for(int i=0;i<MAX_INTERRUPT_STUB;i++)
	{
		if(pStub==gInterruptStub+i)
		{
			if(gInterruptStub[i].OldInterruptAddress && gInterruptStub[i].IDTBaseAddress)
				return gInterruptStub[i].OldInterruptAddress;
		}
	}
	return 0;
}

void ReleaseInterruptStub(PINTERRUPT_STUB IStub)
{
	ZeroMemory(IStub,sizeof(INTERRUPT_STUB));
	IStub->RetPCode=0xc3;
	IStub->PushPCode=0x68;
	IStub->PushPCode2=0x68;
}