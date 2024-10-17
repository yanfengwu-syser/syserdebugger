#ifndef _NTSTATSTR_H_
#define _NTSTATSTR_H_
typedef struct _NTSTATUS_STR
{
	char* Description;
	char* Name;
	unsigned long Code;
}NTSTATUS_STR,*P_NTSTATUS_STR;
extern NTSTATUS_STR gNtstatusTable[];
#endif //_NTSTATSTR_H_