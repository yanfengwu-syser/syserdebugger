#include "StdAfx.h"
//#include "SPCommand.h"

extern __declspec(dllimport) CSyserPluginUI*gpSyserPluginUI;

void OnDebuggerOpen()
{
	//Syser Loaded Notify
	//::DbgPrint("SPCommand : OnDebuggerOpen\n");
}

void OnDebuggerClose()
{
	//Syser Unload Notify
	//::DbgPrint("SPCommand : OnDebuggerClose\n");
}

void OnDebuggerPlunge()
{
	//Syser 
	//::DbgPrint("SPCommand : OnDebuggerPlunge\n");
}

SYSER_PLUGIN_MODULE PluginModule=
{
	WSTR("Syser Command Plugin Module"),
	OnDebuggerOpen,
	OnDebuggerClose,
	OnDebuggerPlunge
};

void DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	gpSyserPluginUI->RemoveCmd(L"calc");
	gpSyserPluginUI->UnregisterPluginModule(WSTR("SPCommand"));
	::DbgPrint("SPCommand : DriverUnload\n");
}
int	syser_calc(int argc,PCWSTR argv[],PCWSTR szCommandLine,void*pUserData)
{
	DWORD dwValue;
	if(argc>=2)
	{
		if(gpSyserPluginUI->CalcExp(argv[1],&dwValue))
		{
			gpSyserPluginUI->Outputf(L"%s = %08x\n",argv[1],dwValue);
		}
	}		
	gpSyserPluginUI->Outputf(L"hello world!\n");
	return 0;
}
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
	if(gpSyserPluginUI->RegisterPluginModule(WSTR("SPCommand"),&PluginModule)==false)
		return STATUS_UNSUCCESSFUL;
	DriverObject->DriverUnload=DriverUnload;
	gpSyserPluginUI->InsertCmd(L"calc",syser_calc,NULL,L"calc expression value.",L"calc [parameter]");
	::DbgPrint("SPCommand : DriverEntry\n");
	return STATUS_SUCCESS;
}

NTSTATUS DllInitialize( IN PUNICODE_STRING pus )
{
	::DbgPrint("SPCommand : DllInitialize\n");
	return STATUS_SUCCESS;
}

NTSTATUS DllUnload( )
{
	::DbgPrint("SPCommand : DllUnload\n");
	return STATUS_SUCCESS;
}
