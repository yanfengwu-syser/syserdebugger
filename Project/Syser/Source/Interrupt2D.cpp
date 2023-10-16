#include "StdAfx.h"
#include "Syser.h"
#include "Interrupt2D.h"

LONG	bInt2DBusy = 0;

__declspec (naked) void Int2DService()
{
	DWORD dwEAX,dwEBX,dwECX,dwEDX,dwEBP;
	__asm
	{	
		pushad
		push fs
		push ds
		push es
		mov ax,0x30
		mov fs,ax
		mov ax,ss
		mov eax,0x10
		mov ds,ax
		mov es,ax
		mov ebp,esp
		lea esp,[esp-0x18]
		mov eax,[ebp+0x1c]
		mov dwEBX,eax
		mov eax,[ebp+0x20]
		mov dwEDX,eax
		mov eax,[ebp+0x24]
		mov dwECX,eax
		mov eax,[ebp+0x28]
		mov dwEAX,eax
		mov eax,[ebp+0x2c]
		mov dwEBP,eax
	}
	switch(dwEAX)
	{
	case 1:
		{
			if(gpSyser->m_OSVer==DRV_OS_XP)
			{
				if(dwEDX)
				{
					Int2D_OutputDebugString((char *)dwECX);
				}
			}
			else if(gpSyser->m_OSVer==DRV_OS_2K)
			{
				if(IsValidPage(dwECX))
				{
					Int2D_OutputDebugString(*(char **)(4+dwECX));
				}
			}
		}
		break;
	case 2:
		//gpSyser->m_MainFrame.m_ConsoleWnd.Printf(WSTR("%<e>(INT 2D )Debug Prompt EIP=%08x EAX=%08X EBX=%08X ECX=%08X EDX=%08X\n"),dwEBP,dwEAX,dwEBX,dwECX,dwEDX);
		break;
	case 3:
		LoadSystemModuleSymbols((PANSI_STRING)dwECX,dwEDX);
		break;
	case 4:
		//gpSyser->m_MainFrame.m_ConsoleWnd.Printf(WSTR("%<e>(INT 2D )Unload Symbol EIP=%08x EAX=%08X EBX=%08X ECX=%08X EDX=%08X\n"),dwEBP,dwEAX,dwEBX,dwECX,dwEDX);
		break;
	default:
		//gpSyser->m_MainFrame.m_ConsoleWnd.Printf(WSTR("%<e>(INT 2D )unkonw functions EIP=%08x EAX=%08X EBX=%08X ECX=%08X EDX=%08X\n"),dwEBP,dwEAX,dwEBX,dwECX,dwEDX);
		break;
	}
	__asm
	{
		mov		esp,ebp
		pop     es
		pop     ds
		pop     fs
		popad
		ret
	}
}

void Int2D_OutputDebugString(char *string)
{
	static LARGE_INTEGER PrevTime;
	KIRQL OldIRQL;
	WISP_CHAR buf[512];
	LARGE_INTEGER CurrentTime;
	if(gpSyserCfg->m_DisableDbgMsg || string == NULL || IsValidPage((VADDR32)string) == false)
		return;

	int Length=0;
	if(SyserOption.iShowDbgSrcProcName)
	{
		CDbgProcess*pProcess;
		pProcess = gpSyser->m_SysInfo.GetProcessByCR3(GetCR3Reg());
		if(pProcess)
		{
			if(pProcess->m_CR3==gpSyser->m_pSysDebugger->m_CR3)
				pProcess = gpSyser->m_pSysDebugger;
			TStrCpy(buf,(PCWSTR)pProcess->m_ProcessName);
			TStrCat(buf," : ");
			Length = TStrLen(buf);
		}
	}
	if(SyserOption.iDebugOutputSwitch)
		SyserAnsiToUnicode(string,&buf[Length],sizeof(buf)/sizeof(WISP_CHAR)-Length-1);

	if(KeGetCurrentIrql()<= DISPATCH_LEVEL)
	{
		if(SyserOption.iDebugOutputSwitch&SYSER_DBG_MSG_KERNEL)
			gpSyser->m_MainFrame.m_ConsoleWnd.Output(buf);

		if(SyserOption.iDebugOutputSwitch & SYSER_DBG_MSG_USER)
		{
			KeAcquireSpinLock(&gpSyser->m_SpinLock,&OldIRQL);
			gpSyser->InsertDbgMsg(buf);
			KeReleaseSpinLock(&gpSyser->m_SpinLock,OldIRQL);
			if(gpSyser->m_pMsgKEvent)
				KeSetEvent(gpSyser->m_pMsgKEvent,0,FALSE);
		}
	}
	else
	{
		if(SyserOption.iDebugOutputSwitch&SYSER_DBG_MSG_KERNEL)
			gpSyser->m_MainFrame.m_ConsoleWnd.Output(buf);
		gpSyser->InsertDbgMsg(buf);
	}
}


WCHAR LoadSystemModuleNameBuf[512];
void LoadSystemModuleSymbols(PANSI_STRING pModuleName,DWORD dwModuleBaseAddress)
{
	DWORD Len;
	if(dwModuleBaseAddress==0||pModuleName==NULL)
		return;
	if(IsValidPage((VADDR32)pModuleName,sizeof(ANSI_STRING))==false)
		return;
	if(pModuleName->Buffer==NULL)
		return;
	if(IsValidPage((VADDR32)pModuleName->Buffer)==false)
		return;
	if(pModuleName->Buffer[0]==0)
		return;
	Len = pModuleName->Length>512?511:pModuleName->Length+1;
	TStrCpyLimit(LoadSystemModuleNameBuf,pModuleName->Buffer,Len);
	//gpSyser->m_RootWnd.m_ConsoleWnd.Printf(WSTR("Load Symbol %s\n"),LoadSystemModuleNameBuf);
}

static DWORD SafeReadDwordValue(DWORD* Address,DWORD DefaultValue)
{	
	if(IsValidPage((VADDR32)Address))
		return *Address;
	else
		return DefaultValue;	
}

