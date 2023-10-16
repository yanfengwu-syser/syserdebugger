#include "StdAfx.h"
#include "WinReg.h"
 
HKEY OpenReg(HKEY h,PCSTR son)
{
	HKEY res;
	if(RegOpenKeyEx(h,son,0,KEY_ALL_ACCESS,&res)==ERROR_SUCCESS)
    return res;
    else return 0;
}

HKEY OpenCreateReg(HKEY h,PCSTR son)
{
	HKEY res;
	if(RegCreateKeyEx(h,son,0,NULL,REG_OPTION_NON_VOLATILE,
		              KEY_ALL_ACCESS,NULL,&res,NULL)==ERROR_SUCCESS)
    return res;
    else return 0;
}

void CloseReg(HKEY h) 
{
     RegCloseKey(h);
}

bool GetRegValue(HKEY h,PCSTR name,void* value)
{
	DWORD size=1024;
	return RegQueryValueEx(h,name,0,NULL,(PBYTE)value,&size)==ERROR_SUCCESS;
}

bool SetRegValue(HKEY h,PCSTR name,void* value,int type)
{
    DWORD size;
	switch(type)
	{
	 case REG_DWORD:size=4;
		            break;
	 case REG_SZ   :size=(DWORD)strlen((char*)value);
	                break;
	 default:       size=0;
		            break;
	} 	
	return RegSetValueEx(h,name,0,type,(PBYTE)value,size)==ERROR_SUCCESS;
}

bool GetRegValueEx(PCSTR KeyValue,void* value,int Size)
{
	DWORD Type;
    HKEY hRoot,hKey;
    char KeyValueBuf[256];
	char *p,*p1,*p2;

	strcpy_s(KeyValueBuf,sizeof(KeyValueBuf),KeyValue);
    p=KeyValueBuf;
	p1=strchr (KeyValueBuf,'\\');
    p2=strrchr(KeyValueBuf,'\\');

	*p2=*p1='\0';
	p1++;
	p2++;
	
	     if(strcmp(p,"HKCR")==0)hRoot=HKEY_CLASSES_ROOT;
	else if(strcmp(p,"HKCU")==0)hRoot=HKEY_CURRENT_USER;
	else if(strcmp(p,"HKLM")==0)hRoot=HKEY_LOCAL_MACHINE;
	else if(strcmp(p,"HKU" )==0)hRoot=HKEY_USERS;
	else if(strcmp(p,"HKCC")==0)hRoot=HKEY_CURRENT_CONFIG;
	else if(strcmp(p,"HKDD")==0)hRoot=HKEY_DYN_DATA;
    else return false;
	
	if(RegOpenKeyEx(hRoot,p1,0,KEY_QUERY_VALUE,&hKey)!=ERROR_SUCCESS)
		return false;

    if(RegQueryValueEx(hKey,p2,0,&Type,(PBYTE)value,(DWORD*)&Size)!=ERROR_SUCCESS)
	{
        RegCloseKey(hKey);
        return false;
    }

	RegCloseKey(hKey);
    return true;
}

bool SetRegValueEx(PCSTR KeyValue,void* value,int type,int Size)
{
    HKEY hRoot,hKey;
    DWORD size;
    char KeyValueBuf[256];
	char *p,*p1,*p2;

	strcpy_s(KeyValueBuf,sizeof(KeyValueBuf),KeyValue);
    p=KeyValueBuf;
	p1=strchr (KeyValueBuf,'\\');
    p2=strrchr(KeyValueBuf,'\\');

	*p2=*p1='\0';
	p1++;
	p2++;
	
	     if(strcmp(p,"HKCR")==0)hRoot=HKEY_CLASSES_ROOT;
	else if(strcmp(p,"HKCU")==0)hRoot=HKEY_CURRENT_USER;
	else if(strcmp(p,"HKLM")==0)hRoot=HKEY_LOCAL_MACHINE;
	else if(strcmp(p,"HKU" )==0)hRoot=HKEY_USERS;
	else if(strcmp(p,"HKCC")==0)hRoot=HKEY_CURRENT_CONFIG;
	else if(strcmp(p,"HKDD")==0)hRoot=HKEY_DYN_DATA;
    else return false;

	
	if(RegCreateKeyEx(hRoot,p1,0,NULL,REG_OPTION_NON_VOLATILE,
		              KEY_SET_VALUE,NULL,&hKey,NULL)!=ERROR_SUCCESS)
    return false;

	if(Size==0)
	{
		switch(type)
		{
		case REG_DWORD:size=4;
			break;
		case REG_SZ   :size=(DWORD)strlen((PCHAR)value);
			break;
		case REG_QWORD:size=8;
			break;
		default:       size=0;
			break;
		}
	}
	else
		size = Size;

	if(RegSetValueEx(hKey,p2,0,type,(PBYTE)value,size)!=ERROR_SUCCESS)
	{
        RegCloseKey(hKey);
        return false;
    }

	RegCloseKey(hKey);
    return true;
}

bool DelReg(HKEY h,PCSTR sub)
{
    return RegDeleteKey(h,sub)==ERROR_SUCCESS;
}

bool DelRegValue(HKEY h,PCSTR name)
{	
	return RegDeleteValue(h,name)==ERROR_SUCCESS;
}

bool DelRegValueEx(PCSTR name)
{
	HKEY hRoot,hKey;
	char KeyValueBuf[256];
	char *p,*p1,*p2;

	strcpy_s(KeyValueBuf,sizeof(KeyValueBuf),name);
	p=KeyValueBuf;
	p1=strchr (KeyValueBuf,'\\');
	p2=strrchr(KeyValueBuf,'\\');

	*p2=*p1='\0';
	p1++;
	p2++;

	if(strcmp(p,"HKCR")==0)hRoot=HKEY_CLASSES_ROOT;
	else if(strcmp(p,"HKCU")==0)hRoot=HKEY_CURRENT_USER;
	else if(strcmp(p,"HKLM")==0)hRoot=HKEY_LOCAL_MACHINE;
	else if(strcmp(p,"HKU" )==0)hRoot=HKEY_USERS;
	else if(strcmp(p,"HKCC")==0)hRoot=HKEY_CURRENT_CONFIG;
	else if(strcmp(p,"HKDD")==0)hRoot=HKEY_DYN_DATA;
	else return false;

	if(RegOpenKeyEx(hRoot,p1,0,KEY_ALL_ACCESS,&hKey)!=ERROR_SUCCESS)
		return false;
	if(RegDeleteValue(hKey,p2)!=ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	RegCloseKey(hKey);
	return true;
}

void RegisterFileType(PCSTR FullPrgName,PCSTR OpenName)
{
	HKEY hOpenWith,hCommand;
	CHAR FileName[512],ValueBuf[512];
	bool bSuccess;
	
	strcpy_s(FileName,sizeof(FileName),FullPrgName);
	strcat_s(FileName,sizeof(FileName)," %1");
	
	hOpenWith=OpenCreateReg(HKEY_CLASSES_ROOT,OpenName);
	if(hOpenWith)
	{
		hCommand=OpenCreateReg(hOpenWith,"command");
		if(hCommand)
		{
			bSuccess=GetRegValue(hCommand,"",ValueBuf)==FALSE;
			if(bSuccess==FALSE || (bSuccess && TStrICmp(FileName,ValueBuf)))
				SetRegValue(hCommand,"",FileName,REG_SZ);
			CloseReg(hCommand);
		}
		CloseReg(hOpenWith);
	}
}

void UnregisterFileType(PCSTR OpenName)
{
	HKEY hKey;
	CHAR RegName[256],*pStr;
	
	hKey=OpenReg(HKEY_CLASSES_ROOT,OpenName);
	if(hKey)
	{
		DelReg(hKey,"command");
		CloseReg(hKey);
		strcpy_s(RegName,sizeof(RegName),OpenName);		
		pStr=strrchr(RegName,'\\');
		if(pStr)
		{
			*pStr=0;
			*pStr++;
			hKey=OpenReg(HKEY_CLASSES_ROOT,RegName);
			if(hKey)
			{
				DelReg(hKey,pStr);
				CloseReg(hKey);
			}				
		}
	}
}
