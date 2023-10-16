#include "stdafx.h"
#include "NotCompatible.h"
/*
NTSTATUS GetProcessByThread(PETHREAD Thread,PEPROCESS* Process)
{
	NTSTATUS Status=STATUS_SUCCESS;
	DWORD Offset=0;
	unsigned char* pstr;
	*Process=NULL;
	if(gOSMajorVersion==4)
	{
		Offset = 0x22c;
	}else if(gOSMajorVersion==5)
	{
		switch(gOSMinorVersion)
		{
		case 0:
			Offset = 0x22c;
			break;
		case 1:
			Offset = 0x220;
			break;
		case 2:
			Offset = 0x228;
			break;
		}
	}
	if(Offset)
	{
		pstr = (unsigned char*)Thread;
		*Process = *(PEPROCESS*)&pstr[Offset];
		if(*Process==NULL)
			*Process=gSystemProcess;
	}
	else
	{
		return STATUS_NOT_IMPLEMENTED;
	}
	return Status;
}
NTSTATUS GetThreadImpersonation(PETHREAD Thread,bool* Impersonation)
{
	NTSTATUS Status=STATUS_SUCCESS;
	DWORD Offset=0;
	unsigned char* pstr;
	unsigned char Value;
	pstr = (unsigned char*)Thread;
	if(gOSMajorVersion==4)
	{
		Value = pstr[0x23b];
	}else if(gOSMajorVersion==5)
	{
		switch(gOSMinorVersion)
		{
		case 0:
			Value = pstr[0x23b];
			break;
		case 1:
			Value = pstr[0x248];
			Value >>= 3;
			Value &=1;
			break;
		case 2:
			Value = pstr[0x250];
			Value >>= 3;
			Value &=1;
			break;
		default :
			Status=STATUS_INVALID_PARAMETER;
		}
	}else
		Status=STATUS_INVALID_PARAMETER;
	*Impersonation=(Value&1)==1;
	return Status;
}
*/

//GetSegmentBaseAddress()
void UpdateSystemKernelDRX()
{
	DWORD BaseAddress;
	BaseAddress = GetSegmentBaseAddress((WORD)gSystemFSRegisterSelector);
	
}