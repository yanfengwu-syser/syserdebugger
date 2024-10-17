#ifndef _SYSTEM_IOCTL_H_
#define _SYSTEM_IOCTL_H_
typedef struct _SYS_IOCTL 
{
	char* Name;
	unsigned int Code;
}SYS_IOCTL,*PSYS_IOCTL;
extern SYS_IOCTL gSysIoctl[];
#endif //_SYSTEM_IOCTL_H_