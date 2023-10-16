#include "StdAfx.h"
#include "SyserConfig.h"
#include "Syser.h"

typedef struct _KEY_VALUE_FULL_INFORMATION_STRUCT
{
	KEY_VALUE_FULL_INFORMATION KeyValueInformation;
	BYTE Value[512];
}KEY_VALUE_FULL_INFORMATION_STRUCT,*PKEY_VALUE_FULL_INFORMATION_STRUCT;

void CSyserConfig::SetDriverRegistryPath(PUNICODE_STRING RegistryPath)
{
	if(RegistryPath==NULL)
		m_DriverRegistryPath[0]=0;
	else
		UnicodeStrCpy(m_DriverRegistryPath,RegistryPath,sizeof(m_DriverRegistryPath)/sizeof(WCHAR));
}

CSyserConfig::CSyserConfig()
{
	m_RegStart=UNINITIALIZATION_VALUE;
	m_SupportSofticeCheck=UNINITIALIZATION_VALUE;
	m_SupportDebugRegisterMontior=UNINITIALIZATION_VALUE;
	m_SupportTimerInterrupt=UNINITIALIZATION_VALUE;
	m_SupportKeyboardLedProgram=UNINITIALIZATION_VALUE;
	m_DisableDisplay=UNINITIALIZATION_VALUE;
	m_DebugKeyboardInterrupt=UNINITIALIZATION_VALUE;
	m_ExceptionDebugInfo=UNINITIALIZATION_VALUE;

	m_PS2NULLKeyboard=UNINITIALIZATION_VALUE;
	m_CheckPS2Mouse=0;
	m_PS2MouseType=0;
	m_DisableCopyOnWrite = 0;
	m_MouseDoubleClickTimeInterval=UNINITIALIZATION_VALUE;
	m_PatchKeBugCheckEx=1;
	m_DisableUSBInput=UNINITIALIZATION_VALUE;
	m_DisableRWPortHook=0;
	m_DisableHookException=0;
	m_SupportVMWareMouse=0;
}

bool CSyserConfig::WriteDwordValue(WCHAR *pValue,DWORD dwValue,WCHAR *pKey)
{
	ULONG ResultLength;
	NTSTATUS ntStatus;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;
	KEY_VALUE_FULL_INFORMATION_STRUCT KeyValueInformation;
	PKEY_VALUE_FULL_INFORMATION_STRUCT pKeyValueInformation;
	ULONG BufLen;
	BufLen = sizeof(KeyValueInformation);
	pKeyValueInformation=&KeyValueInformation;
	if(pKey==NULL)	
		if(m_DriverRegistryPath[0]==0)
			return false;
		else
			pKey = &m_DriverRegistryPath[0];
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
	ntStatus = ZwSetValueKey(hKeyHandle,&ValueName,0,REG_DWORD,&dwValue,sizeof(DWORD));
	ZwClose(hKeyHandle);
	return ntStatus==STATUS_SUCCESS;
}

bool CSyserConfig::ReadDwordValue(WCHAR *pValue,DWORD *pdwRetValue,WCHAR *pKey)
{
	ULONG ResultLength;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;
	KEY_VALUE_FULL_INFORMATION_STRUCT KeyValueInformation;
	if(pKey==NULL)	
		if(m_DriverRegistryPath[0]==0)
			return false;
		else
			pKey = &m_DriverRegistryPath[0];
	RtlInitUnicodeString(&RegKey,pKey);
	DesiredAccess=KEY_QUERY_VALUE;
	ObjectAttributes.Length=sizeof(OBJECT_ATTRIBUTES);
	ObjectAttributes.RootDirectory=0;
	ObjectAttributes.ObjectName=&RegKey;
	ObjectAttributes.Attributes=OBJ_CASE_INSENSITIVE;
	ObjectAttributes.SecurityDescriptor=0;
	ObjectAttributes.SecurityQualityOfService=0;
	if(ZwOpenKey(&hKeyHandle,DesiredAccess,&ObjectAttributes)!=STATUS_SUCCESS)
		return false;
	RtlInitUnicodeString(&ValueName,pValue);
	if(ZwQueryValueKey(hKeyHandle,&ValueName,KeyValueFullInformation,&KeyValueInformation,sizeof(KeyValueInformation),&ResultLength)!=STATUS_SUCCESS)
	{
		ZwClose(hKeyHandle);
		return false;
	}
	*pdwRetValue = *(DWORD*)(RT_PBYTE(&KeyValueInformation,KeyValueInformation.KeyValueInformation.DataOffset));
	ZwClose(hKeyHandle);
	return true;
}

bool CSyserConfig::WriteQwordValue(WCHAR *pValue,QWORD qwValue,WCHAR *pKey)
{
	ULONG ResultLength;
	NTSTATUS ntStatus;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;

	if(pKey==NULL)	
		if(m_DriverRegistryPath[0]==0)
			return false;
		else
			pKey = &m_DriverRegistryPath[0];
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
	ntStatus = ZwSetValueKey(hKeyHandle,&ValueName,0,REG_QWORD,&qwValue,sizeof(QWORD));
	ZwClose(hKeyHandle);
	return ntStatus==STATUS_SUCCESS;
}

bool CSyserConfig::ReadQwordValue(WCHAR *pValue,QWORD *pRetQword,WCHAR *pKey)
{
	ULONG ResultLength;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;
	KEY_VALUE_FULL_INFORMATION_STRUCT KeyValueInformation;
	if(pKey==NULL)	
		if(m_DriverRegistryPath[0]==0)
			return false;
		else
			pKey = &m_DriverRegistryPath[0];
	RtlInitUnicodeString(&RegKey,pKey);
	DesiredAccess=KEY_QUERY_VALUE;
	ObjectAttributes.Length=sizeof(OBJECT_ATTRIBUTES);
	ObjectAttributes.RootDirectory=0;
	ObjectAttributes.ObjectName=&RegKey;
	ObjectAttributes.Attributes=OBJ_CASE_INSENSITIVE;
	ObjectAttributes.SecurityDescriptor=0;
	ObjectAttributes.SecurityQualityOfService=0;
	if(ZwOpenKey(&hKeyHandle,DesiredAccess,&ObjectAttributes) != STATUS_SUCCESS)
		return false;
	RtlInitUnicodeString(&ValueName,pValue);
	if(ZwQueryValueKey(hKeyHandle,&ValueName,KeyValueFullInformation,&KeyValueInformation,sizeof(KeyValueInformation),&ResultLength)!=STATUS_SUCCESS)
	{
		ZwClose(hKeyHandle);
		return false;
	}
	*pRetQword = *(QWORD*)(RT_PBYTE(&KeyValueInformation,KeyValueInformation.KeyValueInformation.DataOffset));
	ZwClose(hKeyHandle);
	return true;
}


bool CSyserConfig::WriteStringValue(WCHAR *pValue,WCHAR* szValue,WCHAR *pKey)
{
	ULONG ResultLength;
	NTSTATUS ntStatus;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;

	if(pKey==NULL)
		if(m_DriverRegistryPath[0]==0)
			return false;
		else
			pKey = &m_DriverRegistryPath[0];
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

bool CSyserConfig::ReadStringValue(WCHAR *pValue,WCHAR* szValue,WCHAR *pKey)
{
	ULONG ResultLength;
	UNICODE_STRING RegKey,ValueName;
	HANDLE hKeyHandle;
	ACCESS_MASK DesiredAccess;
	OBJECT_ATTRIBUTES ObjectAttributes;
	KEY_VALUE_FULL_INFORMATION_STRUCT KeyValueInformation;
	if(pKey==NULL)	
		if(m_DriverRegistryPath[0]==0)
			return false;
		else
			pKey = &m_DriverRegistryPath[0];
	RtlInitUnicodeString(&RegKey,pKey);
	DesiredAccess=KEY_QUERY_VALUE;
	ObjectAttributes.Length=sizeof(OBJECT_ATTRIBUTES);
	ObjectAttributes.RootDirectory=0;
	ObjectAttributes.ObjectName=&RegKey;
	ObjectAttributes.Attributes=OBJ_CASE_INSENSITIVE;
	ObjectAttributes.SecurityDescriptor=0;
	ObjectAttributes.SecurityQualityOfService=0;
	if(ZwOpenKey(&hKeyHandle,DesiredAccess,&ObjectAttributes) != STATUS_SUCCESS)
		return false;
	RtlInitUnicodeString(&ValueName,pValue);
	if(ZwQueryValueKey(hKeyHandle,&ValueName,KeyValueFullInformation,&KeyValueInformation,sizeof(KeyValueInformation),&ResultLength)!=STATUS_SUCCESS)
	{
		ZwClose(hKeyHandle);
		return false;
	}
	TStrCpy(szValue,(PCWSTR)RT_PBYTE(&KeyValueInformation,KeyValueInformation.KeyValueInformation.DataOffset));
	ZwClose(hKeyHandle);
	return true;
}

void CSyserConfig::LoadConfig()
{
	ReadDwordValue(SUPPORT_SOFTICE_CHECK,&m_SupportSofticeCheck);
	ReadDwordValue(SUPPORT_TIMER_INTERRUPT,&m_SupportTimerInterrupt);
	ReadDwordValue(SUPPORT_DEBUG_REGISTER_MONTIOR,&m_SupportDebugRegisterMontior);
	ReadDwordValue(SUPPORT_KEYBOARD_LED_PROGRAM,&m_SupportKeyboardLedProgram);
	ReadDwordValue(DISABLE_DISPLAY,&m_DisableDisplay);
	ReadDwordValue(DEBUG_KEBOARD_INTERRUPT,&m_DebugKeyboardInterrupt);
	ReadDwordValue(PATCH_KEBUGCHECKEX,&m_PatchKeBugCheckEx);
	ReadDwordValue(EXCEPTION_DEBUG_INFO,&m_ExceptionDebugInfo);
	ReadDwordValue(CHECK_PS2_MOUSE,&m_CheckPS2Mouse);
	ReadDwordValue(PS2MOUSE_TYPE,&m_PS2MouseType);
	ReadDwordValue(NULL_PS2_KEYBOARD,&m_PS2NULLKeyboard);
	ReadDwordValue(DBLCLK_TIME_INTERVAL,&m_MouseDoubleClickTimeInterval);
	ReadDwordValue(DISABLE_USBINPUT,&m_DisableUSBInput);	
	ReadDwordValue(DISABLE_RWPORTHOOK,&m_DisableRWPortHook);	
	ReadDwordValue(DISABLE_HOOKEXCEPTION,&m_DisableHookException);	
	ReadDwordValue(SUPPORT_VMWAREMOUSE,&m_SupportVMWareMouse);
	ReadDwordValue(DISABLE_COPYONWRITE,&m_DisableCopyOnWrite);	
}

