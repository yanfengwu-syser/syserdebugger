#include "StdAfx.h"
#include "SysDep.h"

NAME_SPACE_BEGIN

#ifdef CODE_OS_WIN

DWORD PASCAL WinThread(THREAD_PROC pFunc)
{
	pFunc();
	return 0;
}

DWORD CreateThread(THREAD_PROC pFunc)
{
	DWORD ThreadID;
	ThreadID=0;
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)WinThread,pFunc,THREAD_SUSPEND_RESUME | THREAD_TERMINATE,&ThreadID);
	return ThreadID;
}

void UpdateTickCount(ULONGLONG*pTickCount)
{
	static DWORD PrevTickCount=0;
	DWORD TickCount;
	TickCount=GetTickCount();
	if(TickCount>PrevTickCount)
		*pTickCount+=TickCount-PrevTickCount;
	else
		*pTickCount+=TickCount+(~PrevTickCount+1);
	PrevTickCount=TickCount;
}

int GetModulePath(PSTR szPathName,bool bSeparator)
{
	DWORD Size;
	*szPathName=0;
	Size = GetModuleFileName(NULL,szPathName,MAX_FN_LEN);
	if(szPathName[1]==':'&&szPathName[0]>='a'&&szPathName[0]<='z')
		szPathName[0]+='A'-'a';
	char*pStr=TStrRChr(szPathName,PATH_SEPARATOR_CHAR);
	if(pStr)
	{
		if(bSeparator)
			pStr++;
		*pStr=0;
	}
	return TStrLen(szPathName);
}

int GetModulePath(PWSTR szPathName,bool bSeparator)
{
	DWORD Size;
	*szPathName=0;
	Size = GetModuleFileNameW(NULL,szPathName,MAX_FN_LEN);
	if(szPathName[1]==':'&&szPathName[0]>='a'&&szPathName[0]<='z')
		szPathName[0]+='A'-'a';
	WCHAR*pStr=TStrRChr(szPathName,(WCHAR)PATH_SEPARATOR_CHAR);
	if(pStr)
	{
		if(bSeparator)
			pStr++;
		*pStr=0;
	}
	return TStrLen(szPathName);
}

int	CodeDebugPrintf(PCSTR Format,...)
{
	int Length;
	char Buffer[0x400];
	va_list Next;
	va_start(Next,Format);
	Length = TVSPrintf(Buffer,Format,Next);
	va_end(Next);
	OutputDebugString(Buffer);
	return Length;
}

#endif

#ifdef CODE_OS_NT_DRV
/// 获取当前系统时间 
/// 转化成本地时间后取用时，分 
/// 合并成时间串  
/// 如17:35 分，转化成1735 
/// 
short    GetCurTime() 
{ 
/*
__int64 Date=864000000000,Year,mDate,Minute,Hour=0,Second;
LARGE_INTEGER Large;	
SYSTEM_TIME_OF_DAY_INFORMATION TimeDay;
ULONG len;
status = ZwQuerySystemInformation(3,&TimeDay,sizeof(SYSTEM_TIME_OF_DAY_INFORMATION),&len);
Hour = TimeDay.CurrentTime.QuadPart % Date;
Date = TimeDay.CurrentTime.QuadPart/Date;
Minute = Hour % 36000000000;
Second = Minute % 600000000;
Second = Second / 10000000;
Minute = Minute / 600000000;
Hour = Hour / 36000000000;
DbgPrint("ZwQuerySystemInformation %I64d:%I64d:%I64d\n",(Hour+8)%24,Minute,Second);
*/

	LARGE_INTEGER ulTimeStamp,ulLocalTime; 
	TIME_FIELDS   tfTime; 
	KeQuerySystemTime(& ulTimeStamp); 

	ExSystemTimeToLocalTime(&ulTimeStamp,&ulLocalTime); 
	RtlTimeToTimeFields(&ulTimeStamp,&tfTime); 

	return (short)(tfTime.Hour*100+tfTime.Minute); 


} 

#define REGISTRY_VALUE_NAME_LEN_MAX 32
typedef struct _KEY__VALUE_FULL_INFORMATION_STRUCT
{
	KEY_VALUE_FULL_INFORMATION KeyValueInformation;
	WCHAR ValueName[32];
	DWORD Value[1];
}KEY__VALUE_FULL_INFORMATION_STRUCT,*PKEY__VALUE_FULL_INFORMATION_STRUCT;
bool ReadDwordValueRegistry(WCHAR *pValue,DWORD *pdwRetValue,WCHAR *pKey)
{
	ULONG ResultLength;
	NTSTATUS ntStatus;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;
	KEY__VALUE_FULL_INFORMATION_STRUCT KeyValueInformation;
	PKEY__VALUE_FULL_INFORMATION_STRUCT pKeyValueInformation;
	ULONG BufLen;
	BufLen = sizeof(KeyValueInformation);
	pKeyValueInformation=&KeyValueInformation;
	if(pKey==NULL)	
		return false;
	RtlInitUnicodeString(&RegKey,pKey);
	DesiredAccess=KEY_QUERY_VALUE;
	ObjectAttributes.Length=sizeof(OBJECT_ATTRIBUTES);
	ObjectAttributes.RootDirectory=0;
	ObjectAttributes.ObjectName=&RegKey;
	ObjectAttributes.Attributes=OBJ_CASE_INSENSITIVE;			
	ObjectAttributes.SecurityDescriptor=0;
	ObjectAttributes.SecurityQualityOfService=0;
	ntStatus = ZwOpenKey(&hKeyHandle,DesiredAccess,&ObjectAttributes);
	if(ntStatus != STATUS_SUCCESS)
		return false;
	RtlInitUnicodeString(&ValueName,pValue);
	ResultLength = TStrLen(pValue);
	if(ResultLength>REGISTRY_VALUE_NAME_LEN_MAX)
	{
		BufLen =ResultLength + BufLen-REGISTRY_VALUE_NAME_LEN_MAX*sizeof(WCHAR);
		pKeyValueInformation =(PKEY__VALUE_FULL_INFORMATION_STRUCT) new BYTE[BufLen];
		if(pKeyValueInformation==NULL)
		{
			ZwClose(hKeyHandle);
			return false;
		}
	}
	ntStatus = ZwQueryValueKey(hKeyHandle,	&ValueName,KeyValueFullInformation,pKeyValueInformation,BufLen,&ResultLength);
	if(ntStatus!=STATUS_SUCCESS)
	{
		if(pKeyValueInformation!=&KeyValueInformation)
			delete []pKeyValueInformation;
		ZwClose(hKeyHandle);
		return false;
	}
	*pdwRetValue = *(DWORD*)(pKeyValueInformation->KeyValueInformation.DataOffset+(DWORD)pKeyValueInformation);
	if(pKeyValueInformation!=&KeyValueInformation)
		delete []pKeyValueInformation;
	ZwClose(hKeyHandle);
	return true;
}
bool WriteDwordValueRegistry(WCHAR *pValue,DWORD dwValue,WCHAR *pKey)
{
	ULONG ResultLength;
	NTSTATUS ntStatus;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;	
	if(pKey==NULL||pValue==NULL)	
		return false;
	RtlInitUnicodeString(&RegKey,pKey);
	DesiredAccess=KEY_SET_VALUE;
	ObjectAttributes.Length=sizeof(OBJECT_ATTRIBUTES);
	ObjectAttributes.RootDirectory=0;
	ObjectAttributes.ObjectName=&RegKey;
	ObjectAttributes.Attributes=OBJ_CASE_INSENSITIVE;			
	ObjectAttributes.SecurityDescriptor=0;
	ObjectAttributes.SecurityQualityOfService=0;
	ntStatus = ZwOpenKey(&hKeyHandle,DesiredAccess,&ObjectAttributes);
	if(ntStatus != STATUS_SUCCESS)
		return false;
	RtlInitUnicodeString(&ValueName,pValue);
	ntStatus = ZwSetValueKey(hKeyHandle,&ValueName,0,REG_DWORD,&dwValue,sizeof(DWORD));
	ZwClose(hKeyHandle);
	return ntStatus==STATUS_SUCCESS;
}
bool WriteStringValueRegistry(WCHAR *pValue,WCHAR* szValue,WCHAR *pKey)
{
	ULONG ResultLength;
	NTSTATUS ntStatus;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;	
	if(pKey==NULL||pValue==NULL)	
		return false;
	RtlInitUnicodeString(&RegKey,pKey);
	DesiredAccess=KEY_SET_VALUE;
	ObjectAttributes.Length=sizeof(OBJECT_ATTRIBUTES);
	ObjectAttributes.RootDirectory=0;
	ObjectAttributes.ObjectName=&RegKey;
	ObjectAttributes.Attributes=OBJ_CASE_INSENSITIVE;
	ObjectAttributes.SecurityDescriptor=0;
	ObjectAttributes.SecurityQualityOfService=0;
	ntStatus = ZwOpenKey(&hKeyHandle,DesiredAccess,&ObjectAttributes);
	if(ntStatus != STATUS_SUCCESS)
		return false;
	RtlInitUnicodeString(&ValueName,pValue);
	ntStatus = ZwSetValueKey(hKeyHandle,&ValueName,0,REG_SZ,szValue,TStrLen(szValue)*2+2);
	ZwClose(hKeyHandle);
	return ntStatus==STATUS_SUCCESS;
}
void WinDrvThread(IN THREAD_PROC pFunc)
{
	pFunc();
}

bool CreateThread(THREAD_PROC pFunc,void*Param)
{
	HANDLE hThread;
	return NT_SUCCESS(PsCreateSystemThread(&hThread,THREAD_ALL_ACCESS,NULL,NULL,NULL,(PKSTART_ROUTINE)WinDrvThread,pFunc));
}
DWORD dwCPUMHz=0;
ULONGLONG TmpDrvCurTickCount;
ULONGLONG TmpDrvPrevTickCount;
ULONGLONG GetRDTSC()
{
// 	DWORD dwHighValue=0;
// 	DWORD dwLowValue=0;
// 	ULONGLONG Value;
// 	__asm
// 	{
// 		push eax
// 		push edx
// 		rdtsc
// 		mov dwHighValue,edx 
// 		mov dwLowValue,eax
// 		pop edx
// 		pop eax
// 	}
// 	Value=dwHighValue;
// 	Value<<=32;
// 	Value|=dwLowValue;
// 	
// 	return Value;

	return SyserGetRdTsc();
}
void InitTickCount()
{
	DWORD dwHighValue=0;
	DWORD dwLowValue=0;
	if(ReadDwordValueRegistry(L"~MHz",&dwCPUMHz,L"\\REGISTRY\\MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0")==false)
	{
		dwCPUMHz=500;
	}
	TmpDrvPrevTickCount = GetRDTSC();
}

void UpdateTickCount(ULONGLONG*pTickCount)
{
// 	__asm push ecx 
// 	__asm push eax 
// 	__asm push edx
	TmpDrvCurTickCount = GetRDTSC();
	*pTickCount+=(TmpDrvCurTickCount-TmpDrvPrevTickCount);
	TmpDrvPrevTickCount=TmpDrvCurTickCount;
// 	__asm pop edx 
// 	__asm pop eax
// 	__asm pop ecx 
}

int GetModulePath(PSTR szPathName,bool bSeparator)
{
	*szPathName=0;
	return 0;
}

bool GetSystemRootPath(WCHAR* RegistryServiceName,WCHAR* SystemPathBuffer ,ULONG SystemPathLen)
{
	NTSTATUS Status;
	UNICODE_STRING UniSystemRootDir;
	RTL_QUERY_REGISTRY_TABLE RegTable[2];
	WCHAR *ReturnBuffer=NULL;
	ULONG BufferByteSize =0x1000;
	RTL_OSVERSIONINFOEXW RtlOsVersion;
	int Len;

	if(SystemPathBuffer==NULL)
		return false;
	ReturnBuffer = (WCHAR*)ExAllocatePoolWithTag(NonPagedPool,BufferByteSize,'SDep');
	if(ReturnBuffer==NULL)
		return false;
	ZeroMemory(RegTable,sizeof(RegTable));
	ZeroMemory(ReturnBuffer,BufferByteSize);
	wcscpy(ReturnBuffer,WSTR("\\??\\"));
	UniSystemRootDir.Length=0;
	UniSystemRootDir.MaximumLength=(USHORT)(BufferByteSize-(wcslen(ReturnBuffer)+1)*sizeof(WCHAR));
	UniSystemRootDir.Buffer=&ReturnBuffer[wcslen(ReturnBuffer)];
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("SystemRoot");
	RegTable[0].EntryContext = &UniSystemRootDir;
	Status = RtlQueryRegistryValues(RTL_REGISTRY_WINDOWS_NT,WSTR(""),RegTable,NULL,NULL);
	if(NT_SUCCESS(Status))
	{
		Len = wcslen(ReturnBuffer);
		if(ReturnBuffer[Len-1]!='\\')
		{
			ReturnBuffer[Len]='\\';
			ReturnBuffer[Len+1]=0;
			Len++;
		}
		Len++;
		if(SystemPathLen<Len*sizeof(WCHAR))
		{
			ExFreePool(ReturnBuffer);
			return false;
		}
		wcscpy(SystemPathBuffer,ReturnBuffer);
		ExFreePool(ReturnBuffer);
		return true;
	}
	ZeroMemory(RegTable,sizeof(RegTable));
	ZeroMemory(ReturnBuffer,BufferByteSize);
	wcscpy(ReturnBuffer,WSTR("\\??\\"));
	UniSystemRootDir.Length=0;
	UniSystemRootDir.MaximumLength=(USHORT)(BufferByteSize-(wcslen(ReturnBuffer)+1)*sizeof(WCHAR));
	UniSystemRootDir.Buffer=&ReturnBuffer[wcslen(ReturnBuffer)];
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("SystemRoot");
	RegTable[0].EntryContext = &UniSystemRootDir;
	Status = RtlQueryRegistryValues(RTL_REGISTRY_SERVICES,RegistryServiceName,RegTable,NULL,NULL);
	if(NT_SUCCESS(Status))
	{
		Len = wcslen(ReturnBuffer);
		if(ReturnBuffer[Len-1]!='\\')
		{
			ReturnBuffer[Len]='\\';
			ReturnBuffer[Len+1]=0;
			Len++;
		}
		Len++;
		if(SystemPathLen<Len*sizeof(WCHAR))
		{
			ExFreePool(ReturnBuffer);
			return false;
		}
		wcscpy(SystemPathBuffer,ReturnBuffer);
		ExFreePool(ReturnBuffer);
		return true;
	}
	RtlOsVersion.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);	
	PsGetVersion(&RtlOsVersion.dwMajorVersion,&RtlOsVersion.dwMinorVersion,&RtlOsVersion.dwBuildNumber,NULL);
	if(RtlOsVersion.dwMajorVersion==5 && RtlOsVersion.dwMinorVersion>=1)
		wcscpy(ReturnBuffer,WSTR("\\??\\C:\\WINDOWS\\"));
	else
		wcscpy(ReturnBuffer,WSTR("\\??\\C:\\WINNT\\"));
	Len = wcslen(ReturnBuffer);
	Len++;
	if(SystemPathLen<Len*sizeof(WCHAR))
	{
		ExFreePool(ReturnBuffer);
		return false;
	}
	wcscpy(SystemPathBuffer,ReturnBuffer);
	ExFreePool(ReturnBuffer);
	return true;
}
#endif

#ifdef CODE_OS_UNIX
void UpdateTickCount(ULONGLONG*pTickCount)
{
	static LONGLONG PrevTickCount=0;
	LONGLONG TickCount;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	TickCount = tv.tv_sec;
	TickCount = 1000 * TickCount;
	TickCount += (tv.tv_usec / 1000);
	if(TickCount>PrevTickCount)
		*pTickCount+=TickCount-PrevTickCount;
	else
		*pTickCount+=TickCount+(~PrevTickCount+1);
	PrevTickCount=TickCount;
}

int GetModulePath(PSTR szPathName,bool bSeparator)
{
	int Size =1;
	TStrCpy(szPathName,".");
	if(bSeparator)
	{
		TStrCat(szPathName,PATH_SEPARATOR_STR);
		Size++;
	}
	return Size;
}

void* LinuxThread(void*pFunc)
{
	((THREAD_PROC)pFunc)();
	return NULL;
}


DWORD  CreateThread(THREAD_PROC pFunc)
{
#ifdef CODE_UNIX_THREAD
	pthread_t pid;
	DWORD dwRet;
	pthread_create(&pid,NULL,LinuxThread,(void*)pFunc);
	return pid;
#else
	return 0;
#endif
}

DWORD CreateThreadDetach(THREAD_PROC pFunc)
{
#ifdef CODE_UNIX_THREAD
	pthread_t pid;
	DWORD dwRet;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&pid,&attr,LinuxThread,(void*)pFunc);
	return pid;
#else
	return 0;
#endif
}

void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
#ifdef PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP
	pthread_mutex_t temp=PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
	lpCriticalSection->LockSemaphore=temp;
#else
	pthread_mutex_t temp=PTHREAD_MUTEX_INITIALIZER;
	lpCriticalSection->LockSemaphore=temp;
#endif
}

void DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
#ifdef CODE_UNIX_THREAD
	pthread_mutex_destroy(&lpCriticalSection->LockSemaphore);
#endif
}
void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
#ifdef CODE_UNIX_THREAD
	pthread_mutex_lock(&lpCriticalSection->LockSemaphore);
#endif
}
void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
#ifdef CODE_UNIX_THREAD
	pthread_mutex_unlock(&lpCriticalSection->LockSemaphore);
#endif
}
bool TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
#ifdef CODE_UNIX_THREAD
	pthread_mutex_trylock(&lpCriticalSection->LockSemaphore);
#else
	return false;
#endif
	return true;
}

#endif //CODE_OS_UNIX


DWORD gRandomMem[]=
{
	0x5a2b2e15, 0x15562e15, 0x9742a171, 0x8515582e, 0x0f510693,
	0x0708c533, 0x14c80e0b, 0xfe161780, 0x712a3dc2, 0xeb494746,
	0x08f9900a, 0xf7b908d0, 0x0384d5b6, 0x1b212c2b, 0x2022743f,
	0x3416e197, 0x06777bc9, 0xbab7c768, 0xe9837d6b, 0x2af10303,
	0xa6d7eb26, 0xe103eb3e, 0x90b7d0bd, 0x59cde23d, 0x25ebeb07,
	0x0a4a0690, 0x1207c337, 0x6920ee83, 0x690b739e, 0xedda9417,
	0x6010eb06, 0x55f2e920, 0xe959cbf4, 0x089df8fd, 0x525706f9,
	0x43c35351, 0xfe9bb757, 0x5be2809a, 0x4315191d, 0x34dbc2fb,
	0x0f740504, 0x74280b52, 0x0d820552, 0x4c5cdffc, 0x1e8dab6e,
	0x058a0e79, 0x0b72803c, 0xbadf5154, 0x776b6e07, 0x30d77509,
	0x36e68a24, 0x76b669a1, 0x3b03fdb3, 0x18721a44, 0x721e6708,
	0x650a1f0f, 0x6c0bff46, 0xeb2d721c, 0x58f99002, 0x5f5a595b,
	0xe23bb494, 0x1e0cecb7, 0x160ab907, 0x0dea75ae, 0x1b7fb26c,
	0xe0090666, 0x0000daeb, 0x76da06ff, 0x02f9db83, 0xfe012a40,
	0x6a0b0807, 0x0fec5a2e, 0xc9706854, 0x0b40c803, 0x6d555419,
	0x0addb179, 0x2073037d, 0x6968116f, 0x1f6e6407, 0xffde61a1,
	0x54204350, 0x59736c27, 0x2de40d43, 0x2ea36370, 0x9d5dc358,
	0x1e2f06d4, 0x8071b569, 0x2f701b11, 0x7f014b70, 0x1a7307c2,
	0x2a7550d9, 0xc52c2c52, 0xeac518b8, 0x16431995, 0x63226066,
	0xdc0c0bb7, 0x08ce0ee2, 0x0283c010, 0xdb40cce9, 0x5a0c940c,
	0xb78a50b8, 0x8781b15e, 0xd6821cb4, 0xbda35c16, 0xfe15eefd,
	0x0e8920c2, 0xf9810352, 0xb90373ce, 0xb6ec4f04, 0x320e7037,
	0x8a0354dd, 0x095c0507, 0x36230327, 0xef1c49dd, 0x085f7789,
	0x2daf4e97, 0x2c1ec524, 0xf8a67060, 0x28e09740, 0x032a9303,
	0xdb80ad79, 0x730470b6, 0xbb23a886, 0x0e6e344c, 0x4d1544de,
	0x6b754ea6, 0x1adb6e82, 0x6a39a52c, 0x0d176109, 0xda1b7313,
	0x570954b6, 0x745f0e13, 0x1d22e44f, 0xfe7f8ddd, 0x123c1975,
};

DWORD GetRandom(DWORD MinNum,DWORD MaxNum)
{
	ULONGLONG TickCount;
	DWORD Random,Tmp,RMemDw,Delta;
	static DWORD RMemIndex=0;
	static DWORD Seek=0;

	UpdateTickCount(&TickCount);
	Random=(DWORD)TickCount;
	if(RMemIndex>=sizeof(gRandomMem)-4)
		RMemIndex=0;
	else
		RMemIndex++;

	Tmp=Random+GET_DWORD(gRandomMem,RMemIndex);
	RMemDw=gRandomMem[Tmp%(sizeof(gRandomMem)-4)];
	for(int n=0;n<32;n++)
	{
		Tmp^=gRandomMem[(Seek+n)%sizeof(gRandomMem)];
		RMemDw=Seek;
		Random-=Tmp;
		Random+=RMemDw;
		Random^=Seek;
	}
	Seek=Random;

	if(MaxNum<MinNum)
		return MinNum;
	if(MaxNum==MinNum)
		return MinNum;

	Delta=MaxNum-MinNum;
	if(Delta+1!=0)
		Random%=Delta+1;
	Random=Random+MinNum;
	return Random;
}

void SetRandomMem(void*Buffer,int Size)
{
	for(int n=0;n<Size;n++)
		((BYTE*)Buffer)[n]=(BYTE)GetRandom(0,0xff);
}

DWORD PrevRandom = 0;
void InitStaticRandom(DWORD Seed)
{
	PrevRandom = Seed;
}

DWORD GetStaticRandom(DWORD MinNum,DWORD MaxNum)
{
	DWORD Random,Tmp,RMemDw,Delta;
	static DWORD RMemIndex=0;
	static DWORD Seek=0;	
	Random=PrevRandom;
	if(RMemIndex>=sizeof(gRandomMem)-4)
		RMemIndex=0;
	else
		RMemIndex++;

	Tmp=Random+GET_DWORD(gRandomMem,RMemIndex);
	RMemDw=gRandomMem[Tmp%(sizeof(gRandomMem)-4)];
	for(int n=0;n<32;n++)
	{
		Tmp^=gRandomMem[(Seek+n)%sizeof(gRandomMem)];
		RMemDw=Seek;
		Random-=Tmp;
		Random+=RMemDw;
		Random^=Seek;
	}
	Seek=Random;

	if(MaxNum<MinNum)
		return MinNum;
	if(MaxNum==MinNum)
		return MinNum;

	Delta=MaxNum-MinNum;
	if(Delta+1!=0)
		Random%=Delta+1;
	Random=Random+MinNum;
	return Random;

}


NAME_SPACE_END

