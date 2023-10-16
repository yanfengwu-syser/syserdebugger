#ifndef _CODE_DEPENDENT_INCLUDE_H_
#define _CODE_DEPENDENT_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

////////////////////////////////////////////////
//Windows Application<Start>
////////////////////////////////////////////////
#ifdef	CODE_OS_WIN

#include <windows.h>
#define CODE_OS_DEFINED

#endif//CODE_OS_WIN
////////////////////////////////////////////////
//Windows Application<End>
////////////////////////////////////////////////

////////////////////////////////////////////////
//Windows NT Driver<Start>
////////////////////////////////////////////////
#ifdef	CODE_OS_NT_DRV
#ifdef __cplusplus
extern "C"{
#endif
#include <NTDDK.h>
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath);
#ifdef __cplusplus
}
#endif
#define CODE_OS_DEFINED
#endif//CODE_OS_NT_DRV
////////////////////////////////////////////////
//Windows Driver<End>
////////////////////////////////////////////////

////////////////////////////////////////////////
//UNIX Application<Start>
////////////////////////////////////////////////
#ifdef	CODE_OS_UNIX
#include <dirent.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <pthread.h>
#include <wchar.h>
#include <unistd.h>
#define CODE_OS_DEFINED
#endif//CODE_OS_UNIX
////////////////////////////////////////////////
//UNIX Application<End>
////////////////////////////////////////////////
#ifdef  CODE_OS_CATOS
#define CODE_OS_DEFINED
#endif

#endif

