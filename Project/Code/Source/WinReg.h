#ifndef _WIN_REG_H_
#define _WIN_REG_H_

#define HKCR             HKEY_CLASSES_ROOT
#define HKCU             HKEY_CURRENT_USER
#define HKLM             HKEY_LOCAL_MACHINE
#define HKU		         HKEY_USERS
#define HKCC	         HKEY_CURRENT_CONFIG
#define HKDD	         HKEY_DYN_DATA

#define SUB_RUN          "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define SUB_RUNSERVICES  "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"
#define SUB_EXPLORER     "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"
#define VALUE_NODRV      "HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\NoDrives"

HKEY OpenCreateReg(HKEY h,PCSTR son);
HKEY OpenReg(HKEY h,PCSTR son);
void CloseReg(HKEY h);
bool SetRegValue(HKEY h,PCSTR name,void* value,int type);
bool SetRegValueEx(PCSTR KeyValue,void* value,int type,int Size = 0);
bool GetRegValue(HKEY h,PCSTR name,void* value);
bool GetRegValueEx(PCSTR KeyValue,void* value,int Size);
bool DelReg(HKEY h,PCSTR sub);
bool DelRegValue(HKEY h,PCSTR name);
bool DelRegValueEx(PCSTR name);
void RegisterFileType(PCSTR FullPrgName,PCSTR OpenName);
void UnregisterFileType(PCSTR OpenName);


#endif