extern "C"
{
#include <wdm.h>
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath);
}

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#endif

NTSTATUS DllInitialize( IN PUNICODE_STRING pus )
{
    DbgPrint("SAMPLE: DllInitialize(%S)\n", pus->Buffer );
    return STATUS_SUCCESS;
}

NTSTATUS DllUnload( )
{
    DbgPrint("SAMPLE: DllUnload\n");
    return STATUS_SUCCESS;
}

extern "C" __declspec(dllexport) int VidResetDisplay(int)
{
	return 0;
}
extern "C" __declspec(dllexport) int VidSetScrollRegion(int,int,int,int)
{
	return 0;
}
extern "C" __declspec(dllexport) int VidDisplayString(char* pStr)
{
	return 0;
}
extern "C" __declspec(dllexport) int VidInitialize(int mode)
{
	return 0;
}
extern "C" __declspec(dllexport) int VidCleanUp()
{
	return 0;
}
extern "C" __declspec(dllexport) int VidSetTextColor(int NewTextColor)
{
	return 0;
}
extern "C" __declspec(dllexport) void VidSolidColorFill(int x,int y,int x1,int y1,int TextColor)
{    
	return ;
}
extern "C" __declspec(dllexport) void  VidDisplayStringXY(char* pStr,int x,int y,int TextColor)
{    
    return ;
}

extern "C" __declspec(dllexport) void  VidBitBlt(char* colorbuf,int x,int y)
{    
	return ;
}

extern "C" __declspec(dllexport) int  VidBufferToScreenBlt(char* buffer,int x,int y,int width,int height,int copymode)
{    
	return 0;
}

extern "C" __declspec(dllexport) int  VidScreenToBufferBlt(char* buffer,int x,int y,int width,int heigh,int bitcount)
{
	return 0;
}
// The DLL must have an entry point, but it is never called.
//
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
    return STATUS_SUCCESS;
}
