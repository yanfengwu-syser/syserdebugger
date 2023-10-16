#include "StdAfx.h"
#include "Syser.h"
#include "SyserMemoryReadWrite.h"
#include "Services.h"
#include "HardWareInterruptCtrl.h"
#include "MultiCPU.h"
#include "Keyboard.h"

#ifdef __cplusplus
extern "C" {
#endif

bool			gbSystemCrash = false;
bool			gbActive=false;
bool			gbBugCheckExExit=false;
bool			gbBugCheckExFlags=false;
DWORD			gPrevStepEIP=0;						//前一次单步执行的 EIP 地址。这里要处理一些特殊的情况，
													//例如前一次执行的单步命令是 pushfd 那么就要处理堆栈中的 tf 标志
													//如果上一次退出的时候不是单步退出的。这该变量为 0 
DWORD			gGenInterruptOffset;
X86_GATE_DECR	gOldInterruptDescropterTable[0x100];
DWORD			gOldInterruptProcAddress[0x100];
bool			bGoToSoftice;
DWORD			gSofticeDriverEntry = 0;			//在加载 Softice 时 ntice.sys 的 DriverEntry 入口地址;
													//在 ntice.sys 模块装载时我们要在这里下  patch 断点。
													//在中断被激活时，我们把自己安装的中断处理函数以及 给系统打的
													// patch 卸载。等 ntice.sys 安装完成后我们从新安装。

DWORD			SyserDR[8];
DWORD			gSofticeDriverEntryReturnAddress=0;
bool			gbTemplateTraceFlag = false;
DWORD			gGenInterruptNumber = 0xFFFFFFFF;

DWORD			OldESP;
BYTE*			gpStackBuffer;
BYTE*			gpStackBufferTop;
BYTE*			gpStackBufferBottom;
BYTE			FpuRegisterImage[2][FPU_REGISTER_IMAGE_SIZE];
BYTE			FxsaveBuffer[512+15];
DWORD			CurrentFpuImageIndex = 0;
bool			bSaveFpuFlags = false;
WORD			gSystemSSSegment;

DWORD	gpBugCheckExAddress=0;
bool	gbBugCheckExFirstByteIsCC=false;
DWORD	Int01ReEnter_DR6;
DWORD	Int01ReEnter_DR1;
DWORD	Int01ReEnter_EIP;
DWORD	Int01ReEnter_DR7;
DWORD	pRootWndCount=0;
DWORD	pRootWndCount11=0;
DWORD	pRootWndCount12=0;
DWORD	Int01ExecuteCount=0;

#ifdef __cplusplus
}; // extern "C"
#endif





/*
堆栈情况分析   
情况1 这个中断是有3环程序中产生
			R3_SS
			R3_ESP
			EFLAGS
			CS
			EIP

情况2 这个中断是有0环程序中产生
            EFLAGS
			CS
			EIP

情况3 这个中断是在v86模式中产生
			V86_GS
			V86_FS
			V86_DS
			V86_ES
			V86_SS
			V86_ESP
			EFALGS
			CS
			EIP
*/

// 
// DWORD dwLoadRegTmpCpuID;
// DWORD dwValue;
// 
// __declspec(naked) void LoadReg()
// {
// 	__asm
// 	{
// 		push ebx
// 		mov eax,dr0
// 		mov Reg.DR[0*4],eax
// 		mov eax,dr1
// 		mov Reg.DR[1*4],eax
// 		mov eax,dr2
// 		mov Reg.DR[2*4],eax
// 		mov eax,dr3
// 		mov Reg.DR[3*4],eax
// 		mov eax,dr6
// 		mov Reg.DR[6*4],eax
// 		mov eax,dr7
// 		mov Reg.DR[7*4],eax
// 		mov eax,cr0
// 		mov Reg.CR[0*4],eax		
// 		mov eax,cr2
// 		mov Reg.CR[2*4],eax
// 		mov eax,cr3
// 		mov Reg.CR[3*4],eax
// 		_emit(0x0f)//mov eax,cr4
// 		_emit(0x20)
// 		_emit(0xe0)
// 		mov Reg.CR[4*4],eax
// 
// 		mov eax,[ebp+12]
// 		mov Reg.GeneReg[EDI_IDX*4],eax
// 		mov eax,[ebp+12+4]
// 		mov Reg.GeneReg[ESI_IDX*4],eax
// 
// 		mov eax,[ebp+12+8]
// 		mov Reg.GeneReg[EBP_IDX*4],eax
// 
// 		mov ebx,OldESP
// 		mov Reg.GeneReg[ESP_IDX*4],ebx
// 
// 		mov eax,[ebx+8]
// 		mov Reg.EFlags,eax
// 		mov ReturnContext.rEflags,eax
// 		mov eax,[ebp+12+16]
// 		mov Reg.GeneReg[EBX_IDX*4],eax
// 		mov eax,[ebp+12+20]
// 		mov Reg.GeneReg[EDX_IDX*4],eax
// 		mov eax,[ebp+12+24]
// 		mov Reg.GeneReg[ECX_IDX*4],eax
// 		mov eax,[ebp+12+28]
// 		mov Reg.GeneReg[EAX_IDX*4],eax
// 
// 		mov eax,[ebx]
// 		mov Reg.EIP,eax
// 		mov ReturnContext.rEIP,eax
// 		movzx eax,word ptr [ebx+4]
// 		mov word ptr Reg.SegReg[CS_IDX*2],ax
// 		mov ReturnContext.rCS,eax
// 		mov eax,Reg.EFlags
// 		test eax,0x20000			//Virtual Mode
// 		jz local_1
// 
// 		mov eax,[ebx+0x0C]                //这里是 v86模式
// 		mov Reg.GeneReg[ESP_IDX*4],eax
// 		mov ReturnContext.r3ESP,eax
// 		mov eax,[ebx+0x10]
// 		mov Reg.SegReg[SS_IDX*2],ax
// 		mov ReturnContext.r3SS,eax
// 
// 		mov eax,[ebx+0x14]
// 		mov Reg.SegReg[ES_IDX*2],ax
// 		mov ReturnContext.rV86ES,eax
// 
// 		mov eax,[ebx+0x18]
// 		mov Reg.SegReg[DS_IDX*2],ax
// 		mov ReturnContext.rV86DS,eax
// 
// 		mov eax,[ebx+0x1C]
// 		mov Reg.SegReg[FS_IDX*2],ax
// 		mov ReturnContext.rV86FS,eax
// 		mov eax,[ebx+0x20]
// 		mov Reg.SegReg[GS_IDX*2],ax
// 		mov ReturnContext.rV86GS,eax
// 
// 		jmp local_3
// local_1:
// 		mov ax,Reg.SegReg[CS_IDX*2]
// 		test ax,0x3
// 		jz local_2
// 
// 		mov eax,[ebx+0x0C]              //这里是 ring3 触发的情况 这里要更新被调试程序的 esp,ss 积存器
// 		mov Reg.GeneReg[ESP_IDX*4],eax
// 		mov ReturnContext.r3ESP,eax
// 		movzx eax,[ebx+0x10]
// 		mov Reg.SegReg[SS_IDX*2],ax
// 		mov ReturnContext.r3SS,eax
// 		jmp local_4
// local_2:                     
// 		xor eax,eax                     //这里是 ring0 触发的情况
// 		mov ax,ss
// 		mov Reg.SegReg[SS_IDX*2],ax
// 		add Reg.GeneReg[ESP_IDX*4],12   //这里的加12 就是跳过中断的返回现场的  
// 		                                // push eflags
// 		                                // push cs
// 										// push eip
//        // 这里我们要保存 返回现场中的 数据到安全的位置
// 
// local_4:
// 		xor eax,eax
// 		mov ax,[ebp]
// 		mov Reg.SegReg[ES_IDX*2],ax
// 		mov ax,[ebp+4]
// 		mov Reg.SegReg[DS_IDX*2],ax
// 		mov ax,[ebp+8]
// 		mov Reg.SegReg[FS_IDX*2],ax
// 		mov ax,gs
// 		mov Reg.SegReg[GS_IDX*2],ax
// local_3:
// 		pop ebx
// 		
// 	}
// 	SaveFpuRegister();
// 	Reg.IDTBase = SyserGetIDTBase(&dwValue);
// 	Reg.IDTLimit = (WORD)dwValue;
// 
// 	Reg.GDTBase = SyserGetGDTBase(&dwValue);
// 	Reg.GDTLimit = (WORD)dwValue;
// 
// 	if(gCPUNumbers>1)
// 	{
// 		dwLoadRegTmpCpuID=GetCurrentCPULocalAPICID();
// 		gpMCPUReg[dwLoadRegTmpCpuID]=Reg;		
// 		SaveLocalApic(&gpMCPULocalApic[dwLoadRegTmpCpuID]);		
// 		gpMCPUReg[dwLoadRegTmpCpuID].LocalAPIC=&gpMCPULocalApic[dwLoadRegTmpCpuID];
// 	}
// 	ReadOnlyActiveReg=Reg;
// 	__asm ret
// }

void SaveFpuRegister()
{
	DWORD pFpuRegister;
	CurrentFpuImageIndex ^=1;
	pFpuRegister = (DWORD)&FpuRegisterImage[CurrentFpuImageIndex];
	if((Reg.CR[0] & 4) || (Reg.CR[0] & 0x10) == 0)
	{
		bSaveFpuFlags = false;
		return;
	}
	bSaveFpuFlags = true;
	//__asm clts
	SyserCltr();
	memset((void*)pFpuRegister,0,108);

// 	__asm
// 	{
// 		mov eax,pFpuRegister
// 		fnsave BYTE PTR [eax]
// 		frstor BYTE PTR [eax]
// 	}

	SyserFnsave((PUCHAR)pFpuRegister);
	SyserFrstor((PUCHAR)pFpuRegister);
}
void RestorFpuRegister()
{
	DWORD pFpuRegister;	
	if(bSaveFpuFlags==false)
		return;
	pFpuRegister = (DWORD)&FpuRegisterImage[CurrentFpuImageIndex];
// 	__asm
// 	{
// 		mov eax,pFpuRegister
// 		frstor BYTE PTR [eax]
// 	}

	SyserFrstor((PUCHAR)pFpuRegister);
	
	bSaveFpuFlags=false;
}

// 
// __declspec(naked) void  SaveReg()
// {
// 	if(gpSyser->m_bDbgRegAccessMon)
// 	{
// 		EnableHardwaveBreakpoint();
// 		Reg.DR[7]|=0x2000;
// 		gpSyser->m_bUpdateReg=true;
// 	}
// 	if((Reg.EFlags&0x100)==0)
// 		gPrevStepEIP=0;
// 	RestorFpuRegister();
// 	if(gpSyser->m_bUpdateReg==false)
// 	{
// 		__asm
// 		{
// 			push eax
// 			push ebx
// 			mov eax,cr0 
// 			cmp eax,Reg.CR[0*4]
// 			jz local_ppp 
// 			mov eax,Reg.CR[0*4]
// 			mov cr0,eax
// local_ppp:
// 			mov eax,Reg.EFlags
// 			and eax,0xFFFFFEFF
// 			mov ebx,OldESP
// 			mov [ebx+8],eax
// 			mov eax,0xFFFF0FF0
// 			mov dr6,eax
// 			pop ebx
// 			pop eax
// 		}
// 		
// 		__asm ret;
// 	}
// 	gpSyser->m_bUpdateReg=false;
// 	__asm
// 	{
// 		sldt word ptr Reg.LDT
// 		str word ptr Reg.TR
// 		sgdt fword ptr Reg.GDTLimit
// 		sidt fword ptr Reg.IDTLimit
// 		mov eax,Reg.DR[0*4]
// 		mov dr0,eax
// 		mov eax,Reg.DR[1*4]
// 		mov dr1,eax
// 		mov eax,Reg.DR[2*4]
// 		mov dr2,eax
// 		mov eax,Reg.DR[3*4]
// 		mov dr3,eax
// 		mov eax,0xFFFF0FF0			//清DR6
// 		mov dr6,eax
// 		mov eax,Reg.DR[7*4]
// 		mov dr7,eax
// 		mov eax,cr0 
// 		cmp eax,Reg.CR[0*4]
// 		jz local_ppp1 
// 		mov eax,Reg.CR[0*4]
// 		mov cr0,eax
// local_ppp1:
// 		mov eax,Reg.CR[2*4]
// 		mov cr2,eax
// 		mov eax,Reg.CR[3*4]
// 		mov cr3,eax
// 		mov eax,Reg.EFlags
// 		test eax,0x20000			//如果是 v86 模式则跳转
// 		jnz local_0023
// 		mov ax,word ptr Reg.SegReg[ES_IDX*2]
// 		mov [ebp],ax
// 		mov ax,word ptr Reg.SegReg[DS_IDX*2]
// 		mov [ebp+4],ax
// 		mov ax,word ptr Reg.SegReg[FS_IDX*2]
// 		mov [ebp+8],ax
// 		mov ax,word ptr Reg.SegReg[GS_IDX*2]
// 		mov gs,ax
// 		jmp local_987
// local_0023:                   //这里是 v86 模式
// 		mov ebx,OldESP
// 		mov eax,Reg.GeneReg[ESP_IDX*4]
// 		mov [ebx+0x0C],eax
// 		movzx eax,word ptr Reg.SegReg[SS_IDX*2]
// 		mov [ebx+0x10],eax
// 		movzx eax,word ptr Reg.SegReg[ES_IDX*2]
// 		mov eax,0x1234
// 		mov [ebx+0x14],eax
// 		movzx eax,word ptr Reg.SegReg[DS_IDX*2]
// 		mov [ebx+0x18],eax
// 		movzx eax,word ptr Reg.SegReg[FS_IDX*2]
// 		mov [ebx+0x1C],eax
// 		movzx eax,word ptr Reg.SegReg[GS_IDX*2]
// 		mov [ebx+0x20],eax
// local_987:
// 		mov eax,Reg.GeneReg[EDI_IDX*4]
// 		mov [ebp+12],eax
// 		mov eax,Reg.GeneReg[ESI_IDX*4]
// 		mov [ebp+12+4],eax
// 		mov eax,Reg.GeneReg[EBP_IDX*4]
// 		mov [ebp+12+8],eax
// 		//mov [ebp+12+12],eax
// 		mov eax,Reg.GeneReg[EBX_IDX*4]
// 		mov [ebp+12+16],eax
// 		mov eax,Reg.GeneReg[EDX_IDX*4]
// 		mov [ebp+12+20],eax
// 		mov eax,Reg.GeneReg[ECX_IDX*4]
// 		mov [ebp+12+24],eax
// 		mov eax,Reg.GeneReg[EAX_IDX*4]
// 		mov [ebp+12+28],eax
// 		push ebx		
// 		mov ax,ReadOnlyActiveReg.SegReg[CS_IDX*2]
// 		test ax,0x3
// 		jnz local_2skip
// 		mov eax,Reg.GeneReg[ESP_IDX*4]   //在r0 的时候用户可能修改了 ESP 的值
// 		sub eax,12
// 		mov OldESP,eax
// local_2skip:
// 		mov ebx,OldESP
// 		mov eax,Reg.EIP
// 		mov [ebx],eax
// 		movzx eax,Reg.SegReg[CS_IDX*2]
// 		mov [ebx+4],eax
// 		mov eax,Reg.EFlags
// 		mov [ebx+8],eax
// 		mov ax,ReadOnlyActiveReg.SegReg[CS_IDX*2]
// 		test ax,0x3
// 		jz local_098skip
// 		mov eax,Reg.GeneReg[ESP_IDX*4]
// 		mov [ebx+0xc],eax
// 		movzx eax,word ptr Reg.SegReg[SS_IDX*2]
// 		mov [ebx+0x10],ax
// local_098skip:
// 		pop ebx		
// 	}
// 	
// 	__asm ret;
// }

void UnloadSystemModuleSymbols(PSTRING pModuleName,PKD_SYMBOLS_INFO pSymInfo)
{
	DWORD dwBaseAddress;
	if(ReadDword(&pSymInfo->BaseOfDll,&dwBaseAddress)==false)
		dwBaseAddress=0;
	//DbgPrint("UnloadSystemModuleSymbols %08X\n",pSymInfo->BaseOfDll);
	gpSyser->m_SyserUI.m_SyserDI.OnUnloadModule(gpSyser->m_pSysDebugger,(ULPOS)dwBaseAddress);
}

// 
// __declspec(naked) void Int2dProc()
// {
// 	DWORD SrvID,Arg1,Arg2;
// 	__asm
// 	{
// 		pushad
// 		push ds
// 		push es
// 		push fs
// 		mov bp,NT_DS
// 		mov ds,bp
// 		mov es,bp
// 		mov bp,NT_FS
// 		mov fs,bp
// 		mov ebp,esp
// 		sub esp,__LOCAL_SIZE
// 		mov SrvID,eax;
// 		mov Arg1,ecx;
// 		mov Arg2,edx;
// 	}
// 	switch(SrvID)
// 	{
// 	case 3:
// 		break;
// 	case 4:
// 		UnloadSystemModuleSymbols((PSTRING)Arg1,(PKD_SYMBOLS_INFO)Arg2);	
// 		break;
// 	}
// 	__asm
// 	{
// 		mov esp,ebp
// 		pop fs
// 		pop es
// 		pop ds
// 		popad
// 		ret
// 	}
// }

#define DEBUG_SOFTICE_DRIVERENTRY 0

LONG gbLoadImage=0;

void CreateProcessHookProc(IN HANDLE ParentId,IN HANDLE ProcessId,IN BOOLEAN Create)
{
	KeWaitForSingleObject(&gpSyser->m_ImageLoadSyncEvent, Executive, KernelMode, TRUE, 0);
	if(Create)
	{
		CDbgProcess*pProcess = gpSyser->m_SysInfo.InsertProcess((DWORD)ProcessId);
		if(gpSyser->m_pCsrssProcess==NULL && pProcess && TStrICmp((PCSTR)pProcess->m_ProcName,"csrss")==0)
			gpSyser->m_pCsrssProcess = pProcess;
	}
	else
	{
		if((DWORD)ProcessId!=gpSyser->m_pSysDebugger->m_PID)
			gpSyser->m_SysInfo.RemoveProcess((DWORD)ProcessId);
		if(gpSyser->m_bActive==false && gpSyser->m_bUserScrBackuped)
			gpSyser->RestoreScreen();
	}
	KeSetEvent(&gpSyser->m_ImageLoadSyncEvent, 0, FALSE);
}
DWORD RtlGetCurrentDirectory()
{
	WORD FSSelector;
	DWORD SegLimit,SegBase,*Ptr;
	__try{
// 		__asm {
// 			Push eax
// 			mov ax,fs 
// 			mov FSSelector,ax
// 			pop eax
// 		}

		FSSelector = SyserGetCurFSeg();

		SegBase = GetSegmentBaseAddress(FSSelector,&SegLimit);
		Ptr= *(DWORD**)&SegBase;
		Ptr=*(DWORD**)&Ptr[6];
		if(Ptr==NULL)
			return 0;
		Ptr=*(DWORD**)&Ptr[12];
		Ptr=*(DWORD**)&Ptr[4];
		Ptr=*(DWORD**)&Ptr[10];
		return Ptr[0];
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		::DbgPrint("Syser : RtlGetCurrentDirectory fail.\n");
		return 0;
	}
	
}
void LoadImageHookProc(IN PUNICODE_STRING  FullImageName,IN HANDLE  ProcessId,IN PIMAGE_INFO  ImageInfo)
{
	MODULE_ID ModuleID;
	KIRQL kOldIrql;
	bool bModuleTouched;
	WCHAR wszBuffer[MAX_FN_LEN];
	CHAR szFileName[MAX_FN_LEN] = {0};
	ULPOS BaseAddress,HighBaseAddress;
	KeWaitForSingleObject(&gpSyser->m_ImageLoadSyncEvent, Executive, KernelMode, TRUE, 0);
	
	if(FullImageName==NULL)
	{
		::DbgPrint("Syser : ImageHook FullImageName is NULL\n");
		KeSetEvent(&gpSyser->m_ImageLoadSyncEvent, 0, FALSE);		
		return;
	}

	CDbgProcess*pProcess = gpSyser->m_SysInfo.GetProcess((DWORD)ProcessId);
	if(pProcess==NULL)
	{
		::DbgPrint("Syser : ImageHook GetProcess fail. ProcessID %x\n",(DWORD)ProcessId);
		KeSetEvent(&gpSyser->m_ImageLoadSyncEvent, 0, FALSE);		
		return;
	}
	gpSyser->m_pDebugger = pProcess;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//规范文件名,都转换成\??\X:\...的形式
	UnicodeStrCpy(wszBuffer,FullImageName,MAX_FN_LEN);
	UnicodeToAnsi(wszBuffer,szFileName,MAX_FN_LEN);
	BaseAddress = (ULPOS)ImageInfo->ImageBase;
	HighBaseAddress = BaseAddress+ImageInfo->ImageSize;

	if(gpSyser->m_SysInfo.ConvertFileName(szFileName)==false && !ImageInfo->SystemModeImage && pProcess->m_ModuleList.m_DbgModuleMap.Count())
	{//处理不带盘符得文件名,驱动模块不走这里
		if(gpSyser->m_OSMajorVersion==5 || gpSyser->m_OSMajorVersion==6)
		{
			DWORD wszCurDir = RtlGetCurrentDirectory();
			
			int Length;
			if((wszCurDir>>16)==':')
			{
				TStrCpy(szFileName,"\\??\\");
				szFileName[4] = (char)wszCurDir;//盘符
				szFileName[5] = ':';
				szFileName[6] = 0;
				Length = TStrLen(szFileName);
			}
			else
			{
				szFileName[0] = '\\';
				szFileName[1] = 0;
				Length=1;
			}
			UnicodeToAnsi(wszBuffer,&szFileName[Length],MAX_FN_LEN-Length);
		}		
	}
	bModuleTouched = false;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//设置当前Debugger为当前进程,不需要换CR3
	ModuleID = GetModuleID(BaseAddress,ImageInfo->ImageSize);
	gpSyser->m_SyserUI.m_SyserDI.OnLoadModule(pProcess,szFileName,BaseAddress,ImageInfo->ImageSize,ModuleID);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//System方式启动csrss没建立，在这里完成公用模块的处理
	if(gpSyser->m_SysInfo.m_win32kImageBase==0 && ImageInfo->SystemModeImage && TCmpModuleName(szFileName,"win32k.sys"))
	{
		//DbgPrint("Syser : win32k loaded\n");
		gpSyser->m_SysInfo.m_win32kImageBase = (ULPOS)ImageInfo->ImageBase;
		gpSyser->m_SysInfo.m_win32kImageSize = (ULSIZE)ImageInfo->ImageSize;
	}
	if(pProcess==gpSyser->m_pCsrssProcess && gpSyser->m_pCsrssProcess)
	{
		for(int n=0;szPublicModuleName[n];n++)
		{
			if(TCmpModuleName(szFileName,szPublicModuleName[n]))
			{
				CDbgModule*pDbgModule = gpSyser->m_pCsrssProcess->GetModule(szPublicModuleName[n]);
				if(pDbgModule && pDbgModule->m_pSymbolModule)
				{
					//DbgPrint("Syser : csrss %s loaded\n",szPublicModuleName[n]);
					pDbgModule->m_pSymbolModule->m_ModuleBase = pDbgModule->m_ModuleBase;
					pDbgModule->m_pSymbolModule->m_ModuleSize = pDbgModule->m_ModuleSize;
				}
				break;
			}
		}		
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(CSDSModuleMap::IT Iter=gpSyser->m_SyserUI.m_SDSModuleMap.Begin();Iter!=gpSyser->m_SyserUI.m_SDSModuleMap.End();Iter++)
	{//设置SDS模块中虚拟断点
		if(Iter->GetModuleID()==ModuleID)//模块匹配
		{
			for(TList<ULPOS>::IT BPIter = Iter->m_BreakPointList.Begin();BPIter!=Iter->m_BreakPointList.End();BPIter++)
			{
				if(bModuleTouched==false)
				{//Touch一边模块保证模块不缺页
					TouchModuleMemory(BaseAddress,ImageInfo->ImageSize);
					bModuleTouched = true;
				}
				pProcess->InsertCodeBP(BaseAddress+*BPIter,0,BP_STATE_ENABLE);
			}
		}
	}
	if(gpSyser->m_bPatchCopyOnWrite)
	{//Patch CopyOnWrite成功，才设置全局模块断点
		for(CModuleBPMap::IT ModBPIter=gpSyser->m_SyserUI.m_ModuleBPMap.Begin();ModBPIter.IsExist();ModBPIter++)
		{
			if(ModBPIter.Key()>=BaseAddress && ModBPIter.Key()<HighBaseAddress && (ModBPIter->ModuleFileName == (const char*)szFileName))
			{
				TouchModuleMemory(ModBPIter.Key(),1);
				BREAK_POINT*pBP=pProcess->InsertCodeBP(ModBPIter.Key(),0,ModBPIter->State);
				if(pBP)
				{
					pBP->Name = ModBPIter->Name;
					pBP->Condition = ModBPIter->Condition;
					pBP->pModuleBP = &(*ModBPIter);
				}
			}
		}
	}
	for(CModuleLoadBPMap::IT Iter=gpSyser->m_SyserUI.m_ModuleLoadBPMap.Begin();Iter!=gpSyser->m_SyserUI.m_ModuleLoadBPMap.End();Iter++)
	{//设置BPload断点
		if(Iter->State==BP_STATE_ENABLE && TCmpModuleName(szFileName,(PCSTR)Iter.Key()))
		{
			BYTE TouchData;
			BREAK_POINT*pBP;
			CMemPEFile MemPEFile;
			ULPOS Address;
			if(MemPEFile.Open(BaseAddress,PE_OPEN_NO_IMPORT|PE_OPEN_NO_EXPORT,CImageFile::StaticReadRealMemory,NULL))
			{
				if(bModuleTouched==false)
				{
					TouchModuleMemory(BaseAddress,ImageInfo->ImageSize);
					bModuleTouched = true;
				}
				Address = MemPEFile.m_PEHead.AddressOfEntryPoint+BaseAddress;

				pBP = pProcess->InsertCodeBP(Address,BP_TYPE_ONCE,BP_STATE_ENABLE);
				if(pBP)
					pBP->Name.Format("Module Entry point %s",szFileName);
				else
					::DbgPrint("Syser : BPLoad fail to set BP at [%s]%08X\n",(PCSTR)pProcess->m_ProcName,Address);
				MemPEFile.Close();
			}
			if(Iter->Type&BP_TYPE_ONCE)
				gpSyser->m_SyserUI.m_ModuleLoadBPMap.Remove(Iter);
			break;
		}
	}
	KeSetEvent(&gpSyser->m_ImageLoadSyncEvent, 0, FALSE);
}

// 
// 
// __declspec(naked) void SofticeDriverEntryExitCallBack()
// {
// 	__asm
// 	{
// 		PUSHAD
// 		PUSHFD
// 	}
// 	if(gpSyser->InstallDebug()==false)
// 	{
// 		gpSyser->DbgPrint(2,296,WSTR("SYSER : InstallDebug==false"));
// 	}
// 	gSofticeDriverEntry=0;
// 	__asm
// 	{
// 		POPFD
// 		POPAD
// 		PUSH SS:gSofticeDriverEntryReturnAddress
// 		RET
// 	}
// }

// 
// __declspec(naked) int  CloseDebugRegisterMontior()
// {
// 	__asm
// 	{
// 		nop
// 		mov eax,dr0
// 		ret
// 	}
// }
// 
// void DisableDebugRegisterMontior()
// {
// 	__asm
// 	{
// 		PUSHFD
// 		push eax
// 	}	
// 	CloseDebugRegisterMontior();	
// 	__asm
// 	{
// 		pop eax
// 		POPFD
// 	}
// }
// 
// 
// __declspec(naked)void OpenDebugRegisterMontior()
// {
// 	__asm
// 	{
// 		push eax		
// 		mov eax,dr7 
// 		or eax,0x2000
// 		mov dr7,eax
// 		pop eax 
// 		ret
// 	}
// }
// void EnableDebugRegisterMontior()
// {	
// 	__asm push eax
// 	if(gpSyser->m_bDbgRegAccessMon)
// 	{	
// 		__asm call OpenDebugRegisterMontior	
// 	}
// 	__asm pop eax
// }

void EnableHardwaveBreakpoint()
{
	Reg.DR[0] = SyserDR[0];
	Reg.DR[1] = SyserDR[1];
	Reg.DR[2] = SyserDR[2];
	Reg.DR[3] = SyserDR[3];
	Reg.DR[7] = SyserDR[7];
}

// void DisableHardwaveBreakpoint()
// {
// 	__asm
// 	{
// 		PUSH	EAX
// 		XOR		EAX,EAX
// 		MOV		DR7,EAX
// 		POP		EAX
// 	}
// }


void ClearExceptionRegister()
{
	DWORD CurrentCpuID;
	CurrentCpuID = GetCurrentCPULocalAPICID();
	memset(&ExceptionReg[CurrentCpuID],0,sizeof(X86_REG_CONTEXT));	
}
/*
 * [ebp+1c] push eflags
 * [ebp+18] push cs
 * [ebp+14] push eip
 * [ebp+10] push error_code
 * [ebp+c ] push window_address
 * [ebp+8 ] push interrupt index
 * [ebp+4 ] push call_ret
 * [ebp+0 ] push ebp
 */

DWORD GetLocalAPICIDNew()
{
	DWORD LocalApicID;
	DWORD *APICIDRegister = *(DWORD**)&gdwLocalAPICLineAddress;
	if(APICIDRegister==0)
	{
		//Beep(100,2000);
		return 0;
	}
	LocalApicID = APICIDRegister[0x20/sizeof(DWORD)];
	LocalApicID>>=18;
	return LocalApicID;
}

DWORD GetCurrentCPULocalAPICIDNew()
{
	DWORD LocalApicID,i;
	PKPCR FSBaseAddress;
	if(gCPUNumbers==1)
		return 0;
	LocalApicID = GetLocalAPICIDNew();
	if(gCPULocalAPIC_ID[LocalApicID]<=0xf)
		return gCPULocalAPIC_ID[LocalApicID];
	//FSBaseAddress =(PKPCR) GetSegmentBaseAddress((WORD)gSystemFSRegisterSelector);
	//for(i=0;i<gCPUNumbers;i++)
	//{
	//	if(gPCRArray[i]==FSBaseAddress)
	//	{
	//		gCPULocalAPIC_ID[LocalApicID]=(BYTE)i;
	//		return i;
	//	}
	//}
	return 0;
}

#ifdef __cplusplus
extern "C" {
#endif


//DWORD gExceptionSpinLock=0;
//static X86_REG_CONTEXT ExceptionTmpReg;
//static 	DWORD gExceptionCurrentCpuID;

#ifdef __cplusplus
}; // extern "C"
#endif


// 
// 
// void __declspec(naked) SaveExceptionRegister()
// {
// 	DWORD Count;
// 	__asm
// 	{
// 		push ebp 
// 		mov ebp,esp
// 		sub esp,__LOCAL_SIZE
// 		mov Count,0
// local_002:
// 		inc  Count 
// 		cmp Count,0x1000
// 		jg local_003
// 		lock bts dword ptr gExceptionSpinLock,0x1f
// 		jb local_002
// local_003:
// 		push eax 
// 		push ds 
// 		mov eax,0x10 
// 		mov ds,ax 
// 		mov eax,[esp+4]
// 		mov ExceptionTmpReg.GeneReg[EAX_IDX*4],eax 
// 		xor eax,eax
// 		mov eax,[esp]
// 		mov ExceptionTmpReg.SegReg[DS_IDX*2],ax 
// 		mov ExceptionTmpReg.GeneReg[ECX_IDX*4],ecx 
// 		mov ExceptionTmpReg.GeneReg[EDX_IDX*4],edx 
// 		mov ExceptionTmpReg.GeneReg[EBX_IDX*4],ebx 
// 		mov ExceptionTmpReg.GeneReg[ESI_IDX*4],esi 
// 		mov ExceptionTmpReg.GeneReg[EDI_IDX*4],edi 
// 		mov eax,[ebp+0]
// 		mov ExceptionTmpReg.GeneReg[EBP_IDX*4],eax		
// 		mov eax,[ebp+0x18]
// 		mov ExceptionTmpReg.SegReg[CS_IDX*2],ax 
// 		test ax,0x3
// 		jz local_2
// 		mov eax,[ebp+0x20] 
// 		mov ExceptionTmpReg.GeneReg[ESP_IDX*4],eax
// 		mov eax,[ebp+0x24]
// 		mov ExceptionTmpReg.SegReg[SS_IDX*2],ax 
// 		jmp local_3
// local_2:
// 		lea eax,[ebp+0x20]
// 		mov ExceptionTmpReg.GeneReg[ESP_IDX*4],eax
// 		mov ax,ss
// 		mov ExceptionTmpReg.SegReg[SS_IDX*2],ax 
// local_3:
// 		xor eax,eax 
// 		mov ax,fs
// 		mov ExceptionTmpReg.SegReg[FS_IDX*2],ax 
// 		mov ax,es
// 		mov ExceptionTmpReg.SegReg[ES_IDX*2],ax 
// 		mov ax,gs
// 		mov ExceptionTmpReg.SegReg[GS_IDX*2],ax
// 		mov eax,[ebp+0x10]
// 		mov ExceptionTmpReg.ExceptionInterruptErrorCode,eax 
// 		mov eax,[ebp+0x08]
// 		mov ExceptionTmpReg.ExceptionInterruptNumber,eax
// 		mov eax,[ebp+0x14]
// 		mov ExceptionTmpReg.EIP,eax 
// 		mov eax,[ebp+0x1c]
// 		mov ExceptionTmpReg.EFlags,eax 
// 		pop ds 
// 		pop eax
// 		pushad
// 		pushfd 
// 		cld
// 	} 
// 
// 	if(gpSyser && gpSyser->m_bInitSuccess)
// 	{
// 		gExceptionCurrentCpuID = GetCurrentCPULocalAPICID();
// 		if(ExceptionTmpReg.EIP < gpSyser->m_SysInfo.m_SyserBase || ExceptionTmpReg.EIP >=gpSyser->m_SysInfo.m_SyserHighBase)
// 			ExceptionReg[gExceptionCurrentCpuID]=ExceptionTmpReg;
// 	}
// 	__asm
// 	{
// 		lock btr dword ptr gExceptionSpinLock,0x1f
// 		popfd
// 		popad 
// 		mov esp,ebp
// 		pop ebp
// 		ret
// 	}
// }
// 


bool bgCtrlUpActive=false;
void OnPatchTranslateUsageAndPagesToI8042ScanCodes()
{
	USB_HOOK_PARAM*pFuncParam=(USB_HOOK_PARAM*)(Reg.GeneReg[I_ESP]+4);
	if(pFuncParam->ChangedUsageList->UsagePage != HID_USAGE_PAGE_KEYBOARD)
		return;
	if(pFuncParam->ChangedUsageList->Usage == 0xe0||pFuncParam->ChangedUsageList->Usage == 0xe4)
	{
		if(pFuncParam->KeyAction==HidP_Keyboard_Break)
		{
			if(bgCtrlUpActive)
			{
				bgCtrlUpActive=false;
				gpSyser->m_pDebugger->m_bPrevPatchBP = false;
				gpSyser->Active();
				return;
			}
		}
		else
		{
			bgCtrlUpActive=false;
		}
	}
	else
	{
		if(pFuncParam->ChangedUsageList->Usage == 0x45)
		{
			if(pFuncParam->ModifierState->LeftControl || pFuncParam->ModifierState->RightControl)
				bgCtrlUpActive=true;
			else
				bgCtrlUpActive=false;
		}
		else
		{
			bgCtrlUpActive=false;
		}
	}
}

void OnPatchMmUnmapViewOfSection()
{
	IN PEPROCESS PEProcess;
	IN PVOID BaseAddress;
	gpSyser->m_pDebugger->ReadMemory(Reg.GeneReg[ESP_IDX]+8,&BaseAddress,sizeof(BaseAddress));
	gpSyser->m_pDebugger->ReadMemory(Reg.GeneReg[ESP_IDX]+4,&PEProcess,sizeof(PEProcess));
	DbgPrint("PEProcess = %08X , BaseAddress = %08X\n",PEProcess,BaseAddress);
}

void OnDebugSoftice()
{
	DWORD *pTmpPointer;
	WISP_CHAR CommandName[64];
	gpSyser->m_pDebugger->RemoveSingleStep();
	TSPrintf(CommandName,WSTR("patch -d %08x"),gSofticeDriverEntry);
	RUNCMD(CommandName);
	if(gpSyser->UninstallDebug()==false)
		gpSyser->DbgPrint(0,364,WSTR("UninstallDebug == false"));
	pTmpPointer=(DWORD*)(Reg.GeneReg[ESP_IDX]);
	gSofticeDriverEntryReturnAddress=pTmpPointer[0];
	pTmpPointer[0]=(DWORD)SyserSofticeDriverEntryExitCallBack;
}

