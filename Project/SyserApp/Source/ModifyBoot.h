#ifndef _MODIFYBOOT_H_
#define _MODIFYBOOT_H_
int GetBootIniKeyNameByDiskNum(DWORD PhysicalDiskNumber,WCHAR *RetName,DWORD BufRetLen);
bool GetBootINIKeyName(char* RetKeyName,DWORD RetKeyLen);
int DisableNOGUIBOOT(bool Switch);
#endif //_MODIFYBOOT_H_