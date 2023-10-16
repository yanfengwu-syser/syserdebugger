#ifndef _VIDEO_HOOK_H_
#define _VIDEO_HOOK_H_

typedef DWORD		(*FPN_ZwSetSystemInformation)(DWORD FunctionNo,void*Informat,DWORD Size);
typedef NTSTATUS	(*PFN_ZwLoadDriver)(IN PUNICODE_STRING DriverServiceName);

struct SERVICETABLE
{
	void**	ServiceTable;
	DWORD	LowCall;
	DWORD	HiCall;
	PVOID*	ArgTable;
};

DWORD	NewZwSetSystemInformation(DWORD FunctionNo,void*Informat,DWORD Size);

bool	HookZwSetSystemInformation();
void	UnhookZwSetSystemInformation();

bool	HookZwLoadDriver();
void	UnhookZwLoadDriver();


#endif
