#ifndef _LOADHLPMODULE_H_
#define _LOADHLPMODULE_H_
#include "NTDLLDefine.h" 
extern PZWCLOSE pZwClose;
extern PZWOPENFILE pZwOpenFile;
extern PZWQUERYOBJECT pZwQueryObject;
extern PZWOPENSECTION pZwOpenSection;
extern PRTLINITUNICODESTRING pRtlInitUnicodeString;
extern PZWOPENDIRECTORYOBJECT pZwOpenDirectoryObject;
extern PZWQUERYDIRECTORYOBJECT pZwQueryDirectoryObject;
extern PZWQUERYSYSTEMINFORMATION pZwQuerySystemInformation;
extern PZWOPENSYMBOLICLINKOBJECT pZwOpenSymbolicLinkObject;
extern PZWQUERYSYMBOLICLINKOBJECT pZwQuerySymbolicLinkObject;
bool UnloadAPI();
bool LoadAPI();
bool GetSymbolicLink(WCHAR* LinkName,OUT UNICODE_STRING *LinkTargetName,OUT PULONG ReturnLength);
void CloseFindObject(PFIND_OBJECT_DATA pFindData);
bool FindNextObject(INOUT PFIND_OBJECT_DATA pFindData);
bool FindFirstObject(WCHAR* DirectoryName,INOUT PFIND_OBJECT_DATA pFindData);

#endif //_LOADHLPMODULE_H_