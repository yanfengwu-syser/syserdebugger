#ifndef _INTERRUPT2D_H_
#define _INTERRUPT2D_H_

void Int2DService();
void Int2D_OutputDebugString(char *string);
void LoadSystemModuleSymbols(PANSI_STRING pModuleName,DWORD dwModuleBaseAddress);
extern ST_DESC*	Int2DDesc; 
extern VADDR32	gOldInt2DProc;
extern LONG	bInt2DBusy;

DWORD SafeReadDwordValue(DWORD* Address,DWORD DefaultValue=0);
bool IsValidAddress(void* Address,DWORD size=4);
VOID BreakPrintDpcForIsr(PKDPC Dpc,PDEVICE_OBJECT DeviceObject,PIRP Irp,PCHAR string);
#endif

