#include "StdAfx.h"
#include "NTDriver.h"

bool CreateDriver(PCSTR DriverName,PCSTR FullDriver,UINT StartType)
{
	SC_HANDLE hDriver,hSCManager;
	bool Stopped = false;
	hSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if(hSCManager==NULL)
		return false;
	hDriver = OpenService(hSCManager,DriverName,SERVICE_ALL_ACCESS);
	if(hDriver)
		ChangeServiceConfig(hSCManager,SERVICE_KERNEL_DRIVER,StartType,SERVICE_ERROR_NORMAL,FullDriver,NULL,NULL,NULL,NULL,NULL,NULL);
	else
		hDriver = CreateService(hSCManager,DriverName,DriverName,SERVICE_ALL_ACCESS,SERVICE_KERNEL_DRIVER,StartType,SERVICE_ERROR_NORMAL,FullDriver,NULL,NULL,NULL,NULL,NULL);
	if(hDriver==NULL)
	{
		CloseServiceHandle(hSCManager);
		return false;
	}
	CloseServiceHandle(hDriver);
	CloseServiceHandle(hSCManager);
	return true;
}

bool RemoveDriver(PCSTR DriverName)
{
	SC_HANDLE hDriver,hSCManager;
	bool Result;
	hSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if(hSCManager==NULL)
		return false;
	hDriver = OpenService(hSCManager,DriverName,SERVICE_ALL_ACCESS);
	if(hDriver==NULL)
	{
		CloseServiceHandle(hSCManager);
		return true;
	}
	Result = DeleteService(hDriver)!=FALSE;
	CloseServiceHandle(hDriver);
	CloseServiceHandle(hSCManager);
	return Result;
}

bool StartDriver(PCSTR DriverName)
{
	bool Started;
	SERVICE_STATUS ss;
	SC_HANDLE hSCManager,hDriver;
	hSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_CONNECT);
	if(hSCManager==NULL)
		return false;
	hDriver=OpenService(hSCManager,DriverName,SERVICE_QUERY_STATUS|SERVICE_START);
	if(hDriver==NULL)
	{
		CloseServiceHandle(hSCManager);
		return false;
	}
	if(QueryServiceStatus(hDriver,&ss) && ss.dwCurrentState!=SERVICE_STOPPED)
		goto ErrorExit;
	if(StartService(hDriver,0,NULL)==false)
		goto ErrorExit;
	Started=false;
	for(int seconds=0;seconds<10;seconds++)
	{
		Sleep(1000);
		if(QueryServiceStatus(hDriver,&ss) && ss.dwCurrentState==SERVICE_RUNNING)
		{
			Started = true;
			break;
		}
	}
	if(Started==false)
		goto ErrorExit;
	CloseServiceHandle(hDriver);
	CloseServiceHandle(hSCManager);
	return true;
ErrorExit:
	CloseServiceHandle(hDriver);
	CloseServiceHandle(hSCManager);
	return false;
}


#ifndef INST_DRV_ONLY
bool StopDriver(PCSTR DriverName)
{
	SERVICE_STATUS ss;
	SC_HANDLE hDriver,hSCManager;
	bool Stopped = false;
	hSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if(hSCManager==NULL)
		return false;
	hDriver = OpenService(hSCManager,DriverName,SERVICE_ALL_ACCESS);
	if(hDriver==NULL)
	{
		CloseServiceHandle(hSCManager);
		return true;
	}
	if(QueryServiceStatus(hDriver,&ss)==false)
		goto SuccessExit;
	if(ss.dwCurrentState==SERVICE_STOPPED)
		goto SuccessExit;
	if(ControlService(hDriver,SERVICE_CONTROL_STOP,&ss)==false)
		goto ErrorExit;
	Stopped = false;
	for(int seconds=0;seconds<10;seconds++)
	{
		if(QueryServiceStatus(hDriver,&ss) == false || ss.dwCurrentState==SERVICE_STOPPED)
		{
			Stopped = true;
			break;
		}
		Sleep(1000);
	}
	if(Stopped == false)
		goto ErrorExit;
SuccessExit:
	CloseServiceHandle(hDriver);
	CloseServiceHandle(hSCManager);
	return true;
ErrorExit:
	CloseServiceHandle(hDriver);
	CloseServiceHandle(hSCManager);
	return false;
}

bool IsDriverActive(PCSTR DriverName)
{
	SERVICE_STATUS ss;
	SC_HANDLE hDriver,hSCManager;
	hSCManager = OpenSCManager(NULL,NULL,SC_MANAGER_CONNECT);
	if(hSCManager==NULL)
		return false;
	hDriver = OpenService(hSCManager,DriverName,SERVICE_QUERY_STATUS);
	if(hDriver==NULL)
	{
		CloseServiceHandle(hSCManager);
		return false;
	}
	if(QueryServiceStatus(hDriver,&ss)==false)
		goto ErrorExit;
	if(ss.dwCurrentState==SERVICE_RUNNING)
	{
		CloseServiceHandle(hDriver);
		CloseServiceHandle(hSCManager);
		return true;
	}
ErrorExit:
	CloseServiceHandle(hDriver);
	CloseServiceHandle(hSCManager);
	return false;
}


bool InstallDriver(PCSTR DriverName,PCSTR DriverFileName,UINT StartType,PCSTR GroupName,DWORD Tag)
{
	UINT  OldStartType,OldTag;
	DWORD dwRegValue,Disposition,dwSize;
	HKEY hKey;
	bool bGroupChange=false;
	CHAR FullName[260],FullFileName[260],*pszName,OldGroupName[260];
	if(DriverFileName==NULL)
	{
		CHAR*pStr;
		GetModuleFileName(NULL,FullFileName,sizeof(FullFileName));
		pStr=strrchr(FullFileName,'\\');
		if(pStr==NULL)
			return false;
		pStr[1]=0;
		strcpy(&pStr[1],DriverName);
		strcat(pStr,".sys");
		DriverFileName = FullFileName;
	}
	else
	{
		strcpy(FullFileName,DriverFileName);
	}
	strcpy(FullName,"SYSTEM\\CurrentControlSet\\Services\\");
	strcat(FullName,DriverName);
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE,FullName,0,"",0,KEY_ALL_ACCESS,NULL,&hKey,&Disposition)!=ERROR_SUCCESS)
		return false;
	if(Disposition==REG_OPENED_EXISTING_KEY)
	{
		OldStartType = -1;
		dwSize = sizeof(OldStartType);
		RegQueryValueEx(hKey,"Start",NULL,NULL,(BYTE*)&OldStartType,&dwSize);
		dwSize = sizeof(OldTag);
		RegQueryValueEx(hKey,"Tag",NULL,NULL,(BYTE*)&OldTag,&dwSize);
		if(GroupName)
		{
			bGroupChange=true;
			dwSize=sizeof(OldGroupName);
			if(RegQueryValueEx(hKey,"Group",NULL,NULL,(BYTE*)OldGroupName,&dwSize) == ERROR_SUCCESS)
			{
					if(stricmp(OldGroupName,GroupName)==0)
						bGroupChange=false;
			}
		}
		dwSize=sizeof(FullName);
		
		if(bGroupChange ==false && OldTag == Tag && OldStartType == StartType && RegQueryValueEx(hKey,"ImagePath",NULL,NULL,(BYTE*)FullName,&dwSize) == ERROR_SUCCESS)
		{
			pszName = FullName;
			if(strnicmp(FullName,"\\??\\",4)==0)
				pszName+=4;
			if(stricmp(pszName,FullFileName)==0)
			{
				RegCloseKey(hKey);
				return true;
			}
		}
	}
	dwRegValue = SERVICE_ERROR_NORMAL;
	if(RegSetValueEx(hKey,"ErrorControl",0,REG_DWORD,(BYTE*)&dwRegValue,sizeof(DWORD)) != ERROR_SUCCESS)
		return false;
	dwRegValue = StartType;
	if(StartType>=0 && RegSetValueEx(hKey,"Start",0,REG_DWORD,(BYTE*)&dwRegValue,sizeof(DWORD)) != ERROR_SUCCESS)
		return false;
	dwRegValue = SERVICE_KERNEL_DRIVER;
	if(RegSetValueEx(hKey,"Type",0,REG_DWORD,(BYTE*)&dwRegValue,sizeof(DWORD)) != ERROR_SUCCESS)
		return false;
	dwSize = (DWORD)strlen(DriverName)+1;
	if(RegSetValueEx(hKey,"DisplayName",0,REG_SZ,(BYTE*)DriverName,dwSize) != ERROR_SUCCESS)
		return false;
	if(FullFileName[1]!=':')
	{
		strcpy(FullName,FullFileName);
	}
	else
	{
		strcpy(FullName,"\\??\\");
		strcat(FullName,FullFileName);
	}
	dwSize = (DWORD)strlen(FullName)+1;
	if(RegSetValueEx(hKey,"ImagePath",0,REG_SZ,(BYTE*)FullName,dwSize) != ERROR_SUCCESS)
		return false;
	
	if(GroupName)
	{
		dwSize = (DWORD)strlen(GroupName)+1;
		if(RegSetValueEx(hKey,"Group",0,REG_SZ,(BYTE*)GroupName,dwSize) != ERROR_SUCCESS)
			return false;
	}
	if(Tag!=-1)
	{
		if(RegSetValueEx(hKey,"Tag",0,REG_DWORD,(BYTE*)&Tag,sizeof(Tag)) != ERROR_SUCCESS)
			return false;
	}
	RegCloseKey(hKey);
	return CreateDriver(DriverName,DriverFileName,StartType);
}

bool UninstallDriver(PCSTR DriverName)
{
	CHAR szBuffer[256],FullName[260];
	HKEY hKey;
	FILETIME Time;
	DWORD dwSize;
	strcpy(FullName,"SYSTEM\\CurrentControlSet\\Services\\");
	strcat(FullName,DriverName);
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,FullName,0,KEY_ALL_ACCESS,&hKey)!=ERROR_SUCCESS)
		goto RemoveDriver;
	dwSize=sizeof(szBuffer);
	while(RegEnumKeyEx(hKey,0,szBuffer,&dwSize,NULL,NULL,NULL,&Time)==ERROR_SUCCESS)
	{
		RegDeleteKey(hKey,szBuffer);
		dwSize=sizeof(szBuffer);
	}
	RegCloseKey(hKey);
	RegDeleteKey(HKEY_LOCAL_MACHINE,FullName);
RemoveDriver:
	return RemoveDriver(DriverName);
}

bool EnableDriver(PCSTR DriverName,PCSTR DriverFileName)
{
	if(IsDriverActive(DriverName))
		return true;
	InstallDriver(DriverName,DriverFileName);
	return StartDriver(DriverName);
}

bool DisableDriver(PCSTR DriverName)
{
	return StopDriver(DriverName);
}

bool InstallServiceGroup(PCSTR szGroup,PCSTR szPosAfter)
{
	DWORD Size;
	HKEY hKey;
	TList<CStrA> NameList;
	TList<CStrA>::IT Iter;
	PSTR pStr;
	char*szList = NULL;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\ServiceGroupOrder",0,KEY_ALL_ACCESS,&hKey)!=ERROR_SUCCESS)
		return false;
	if(RegQueryValueEx(hKey,"List",0,NULL,NULL,&Size)!=ERROR_SUCCESS)
		goto ErrorExit;
	Size+=100;
	szList = new char[Size];
	if(RegQueryValueEx(hKey,"List",0,NULL,(PBYTE)szList,&Size)!=ERROR_SUCCESS)
		goto ErrorExit;
	for(pStr = szList;*pStr;pStr++)
	{
		Iter = NameList.Append(pStr);
		pStr+=Iter->Length();
	}
	Iter = NameList.Find(szGroup);
	while(Iter != NameList.End())
	{
		NameList.Remove(Iter);
		Iter = NameList.Find(szGroup);
	}
	if(szPosAfter==NULL)
		szPosAfter = "<last>";
	if(TStrICmp(szPosAfter,"<first>")==0)
		Iter = NameList.InsertBefore(NameList.Begin(),szGroup);
	else if(TStrICmp(szPosAfter,"<last>")==0)
		Iter = NameList.Append(szGroup);
	else
	{
		Iter = NameList.Find(szPosAfter);
		if(Iter == NameList.End())
			Iter = NameList.Last();
		NameList.InsertAfter(Iter,szGroup);
	}
	Iter = NameList.Begin();
	pStr = szList;
	while(Iter!=NameList.End())
	{
		TStrCpy(pStr,(PCSTR)*Iter);
		pStr+=Iter->Length()+1;
		Iter++;
	}
	*pStr=0;
	if(RegSetValueEx(hKey,"List",0,REG_MULTI_SZ,(PBYTE)szList,(DWORD)(pStr-szList)+1)!=ERROR_SUCCESS)
		goto ErrorExit;
	delete szList;
	RegCloseKey(hKey);
	return true;
ErrorExit:
	if(szList)
		delete szList;
	RegCloseKey(hKey);
	return false;
}

bool UninstallServiceGroup(PCSTR szGroup)
{
	DWORD Size;
	HKEY hKey;
	TList<CStrA> NameList;
	TList<CStrA>::IT Iter;
	PSTR pStr;
	char*szList = NULL;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\ServiceGroupOrder",0,KEY_ALL_ACCESS,&hKey)!=ERROR_SUCCESS)
		return false;
	if(RegQueryValueEx(hKey,"List",0,NULL,NULL,&Size)!=ERROR_SUCCESS)
		goto ErrorExit;
	Size+=100;
	szList = new char[Size];
	if(RegQueryValueEx(hKey,"List",0,NULL,(PBYTE)szList,&Size)!=ERROR_SUCCESS)
		goto ErrorExit;
	for(pStr = szList;*pStr;pStr++)
	{
		Iter = NameList.Append(pStr);
		pStr+=Iter->Length();
	}
	Iter = NameList.Find(szGroup);
	if(Iter==NameList.End())
		goto SuccessExit;
	while(Iter != NameList.End())
	{
		NameList.Remove(Iter);
		Iter = NameList.Find(szGroup);
	}
	Iter = NameList.Begin();
	pStr = szList;
	while(Iter!=NameList.End())
	{
		TStrCpy(pStr,(PCSTR)*Iter);
		pStr+=Iter->Length()+1;
		Iter++;
	}
	*pStr=0;
	if(RegSetValueEx(hKey,"List",0,REG_MULTI_SZ,(PBYTE)szList,(DWORD)(pStr-szList)+1)!=ERROR_SUCCESS)
		goto ErrorExit;
SuccessExit:
	delete szList;
	RegCloseKey(hKey);
	return true;
ErrorExit:
	if(szList)
		delete szList;
	RegCloseKey(hKey);
	return false;
}


#endif
