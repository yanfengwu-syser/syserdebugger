#ifndef _NOTCOMPATIBLE_H_
#define _NOTCOMPATIBLE_H_
NTSTATUS GetProcessByThread(PETHREAD Thread,PEPROCESS* Process);
NTSTATUS GetThreadImpersonation(PETHREAD Thread,bool* Impersonation);
#endif //_NOTCOMPATIBLE_H_