#ifndef _INT0XE_H_
#define _INT0XE_H_


#ifdef __cplusplus
extern "C" {
#endif

//ȱҳ�쳣
VOID SyserInt0eProc(VOID);
extern DWORD gdwActiveInt0eProcAddress;
VOID SyserActive_Int0eProcStub(VOID);
void ActiveHookInt0e(bool bInstall);
bool Int0eHandle(DWORD *StackPointer);
extern DWORD gSyserInt0eAddress;

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //_INT0XE_H_