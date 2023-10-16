#include "StdAfx.h"
#include "SysLang.h"

const union cptable * current_cptable = NULL;

void SyserLanguageUnload(IN PDRIVER_OBJECT DriverObject)
{
	IoDeleteDevice(DriverObject->DeviceObject);
}

int	SyserAnsiToUnicode(const char*szBuf,WCHAR*WszBuf,int MaxLen)
{
	if(current_cptable==NULL)
		return 0;
	return cp_mbstowcs(current_cptable,0,szBuf,TStrLen(szBuf)+1,WszBuf,MaxLen);
}

int	SyserUnicodeToAnsi(const WCHAR*WszBuf,char*szBuf,int MaxLen)
{
	if(current_cptable==NULL)
		return 0;
	return cp_wcstombs(current_cptable,0,WszBuf,TStrLen(WszBuf)+1,szBuf,MaxLen,NULL,NULL);
}

NTSTATUS  MJFunction(IN PDEVICE_OBJECT DeviceObject,IN PIRP  Irp)
{
	Irp->IoStatus.Status=STATUS_SUCCESS;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

void GetOSCodePage()
{
	UINT CodePage;
	WCHAR szBuffer[32];
	UNICODE_STRING UnicodeString;
	RTL_QUERY_REGISTRY_TABLE RegTable[2];
	ZeroMemory(RegTable,sizeof(RegTable));
	UnicodeString.Length=0;
	UnicodeString.MaximumLength=sizeof(szBuffer);
	UnicodeString.Buffer=szBuffer;
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED | RTL_QUERY_REGISTRY_NOEXPAND;
	RegTable[0].Name = WSTR("ACP");
	RegTable[0].EntryContext = &UnicodeString;
	if(!NT_SUCCESS(RtlQueryRegistryValues(RTL_REGISTRY_CONTROL,WSTR("\\Nls\\CodePage"),RegTable,NULL,NULL)))
	{
		::DbgPrint("SyserLanguage : Fail to get OS CodePage!\n");
		return;
	}
	if(USDecStrToNum(szBuffer,&CodePage)==false)
	{
	::DbgPrint("SyserLanguage : Invalid CodePage String [%ws]\n",szBuffer);	
		return;
	}
	current_cptable = cp_get_table(CodePage);
	if(current_cptable)
		::DbgPrint("SyserLanguage : CodePage = %d\n",CodePage);
	else
		::DbgPrint("SyserLanguage : Unsupported CodePage = %d\n",CodePage);
}

/////////////////////////////////////////////////////////////////////////////////////////
//³ÌÐòÈë¿Ú
/////////////////////////////////////////////////////////////////////////////////////////
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
	UNICODE_STRING      DeviceName;
	NTSTATUS            status;
	PDEVICE_OBJECT      DeviceObject;
	SYSER_LANGUAGE_DEVICE_EXTENSION*   pDevExt;
	RtlInitUnicodeString(&DeviceName,WSTR("\\Device\\SyserLanguage"));
	status = IoCreateDevice(DriverObject,sizeof(SYSER_LANGUAGE_DEVICE_EXTENSION),&DeviceName,FILE_DEVICE_UNKNOWN,0,TRUE,&DeviceObject);
	if(!NT_SUCCESS(status))
		return status;
	pDevExt = (SYSER_LANGUAGE_DEVICE_EXTENSION*)DeviceObject->DeviceExtension;
	ZeroMemory(pDevExt,sizeof(SYSER_LANGUAGE_DEVICE_EXTENSION));
	GetOSCodePage();
	pDevExt->cbSize = sizeof(SYSER_LANGUAGE_DEVICE_EXTENSION);
	pDevExt->pfnAnsiToUnicode = SyserAnsiToUnicode;
	pDevExt->pfnUnicodeToAnsi = SyserUnicodeToAnsi;
	for(DWORD FunCount=0;FunCount<IRP_MJ_MAXIMUM_FUNCTION;FunCount++)
		DriverObject->MajorFunction[FunCount]=MJFunction;
	DriverObject->DriverUnload = SyserLanguageUnload;
	return STATUS_SUCCESS;
}
