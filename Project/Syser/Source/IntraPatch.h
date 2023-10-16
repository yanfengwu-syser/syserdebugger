#ifndef _INTRAPATCH_H_
#define _INTRAPATCH_H_
typedef struct _SYSERINTRAPATCHBREAKPOINT
{
	DWORD BPAddress;
	void* BeginPatchRoutine;
	void* EndPatchRoutine;
	BYTE  OrgIntruction[16];
}SYSERINTRABREAKPOINT,*PSYSERINTRABREAKPOINT;
#endif //_INTRAPATCH_H_