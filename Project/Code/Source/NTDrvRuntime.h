#ifndef _NT_DRV_RUNTIME_H_
#define _NT_DRV_RUNTIME_H_

extern "C" void __cdecl _chkstk(void);
int UnicodeStrCpy(PWSTR szBuffer,PUNICODE_STRING pUnicodeString,int MaxLength);

#endif
