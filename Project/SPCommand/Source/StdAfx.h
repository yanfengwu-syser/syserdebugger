#ifndef _STDAFX_H_
#define _STDAFX_H_

#ifdef __cplusplus
extern "C"{
#endif
#include <NTDDK.h>
	NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath);
#ifdef __cplusplus
}
#endif
#include "define.h"
#include "SyserDebugger.h"

#endif//_STDAFX_H_
