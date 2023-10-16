#ifndef __LASTBRANCH__H__
#define __LASTBRANCH__H__

#ifdef __cplusplus
extern "C" {
#endif

bool		SetLastBranchMointer();
bool		InitBranchMointer();
bool		GetLastBranchAddress(DWORD Index,DWORD* FromAddr,DWORD* ToAdd);

typedef bool (*GETLASTBRANCHINFO)(DWORD Index,DWORD* FromAddr,DWORD* ToAddr);
extern GETLASTBRANCHINFO gfnGetLastBranchInfo[7];
int SyserDetectLastBranchType(VOID);
int GetLastBranchType();

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //__LASTBRANCH__H__

