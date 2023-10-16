#include "StdAfx.h"
#include "Syser.h"

#ifdef __cplusplus
extern "C" {
#endif

bool SyserVMWareTest(VOID);
VOID SyserIsDisableVmMouse(BYTE  *PortValue1,BYTE *PortValue2);
#ifdef __cplusplus
}; // extern "C"
#endif

bool gInVMWARE=false;
bool gIsSupportVMMouse=false;
bool VMWareTest()
{
	BYTE PortValue1,PortValue2;
	__try
	{
// 		__asm
// 		{
// 			pushad 
// 			pushfd
// 			xor ebx,ebx
// 			mov ecx,0xa 
// 			mov eax, 'VMXh'			; EAX=magic
// 			mov dx, 'VX'			; DX=magic
// 			in  eax, dx				; specially processed io cmd
// 			cmp ebx, 'VMXh'			; also eax/ecx modified (maybe vmw/os ver?)
// 			jne local_001
// 			mov gInVMWARE,1
// local_001:
// 			popfd
// 			popad
// 		}

		gInVMWARE = SyserVMWareTest();
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		gInVMWARE=false;
	}

	if(gInVMWARE)
	{
		//gIsSupportVMMouse = IsSupportVMMouse();
		DbgPrint("Syser : Host machine is VMWare!\n");		
// 		__asm
// 		{
// 			push eax 
// 			push edx 
// 			xor eax,eax 
// 			in al,0x64 
// 			mov PortValue1,al 
// 			xor eax,eax 
// 			in eax,0x64 
// 			mov PortValue2,al 
// 			pop edx
// 			pop eax
// 		}

		SyserIsDisableVmMouse(&PortValue1,&PortValue2);

		if(PortValue1!=PortValue2)
		{
			DbgPrint("Syser : VMWare version < 5,need modify the virtual machine config file.(.vmx)\n");			
			DbgPrint("Syser : Add the following one line:\n");
			DbgPrint("Syser :     vmmouse.present = FALSE\n");
		}
	}
	return gInVMWARE;
}
// 
// 
// void FlushMouseBuffer(WORD CommandPort,WORD DataPort)
// {
// 	__asm
// 	{
// 		ret
// 		push edx 
// 		push eax
// 		mov dx,CommandPort 
// 		mov eax,0x18
// 		out dx,eax 
// 		mov dx,DataPort 
// 		mov eax,0 
// 		out dx,eax 
// 		mov dx,CommandPort 
// 		mov eax,0x18
// 		out dx,eax 
// 		mov dx,DataPort 
// 		mov eax,2 
// 		out dx,eax 
// 		pop eax 
// 		pop edx
// 	}
// }

	/*
	out(pci第一个端口，SET_CURSOR_POINT_FLAG）；
	out(pci第二个端口，0x1）；
	out(pci第一个端口，SET_CURSOR_POINT_X）；
	out(pci第二个端口，x坐标）；
	out(pci第一个端口，SET_CURSOR_POINT_Y）；
	out(pci第二个端口，y坐标）；
	out(pci第一个端口，SET_ACCESS_FLAG）；
	out(pci第二个端口，0x1）；
*/
void GetVMWareMousePos(DWORD* mousex,DWORD* mousey)
{
	DWORD x,y,CommandPort,DataPort;
	CommandPort = gpSyser->m_PCSystem.m_VmwareVideoCommandPort;
	DataPort=gpSyser->m_PCSystem.m_VmwareVideoDatePort;
// 	__asm
// 	{
// 		push eax
// 		push edx
// 		mov edx,CommandPort 
// 		mov eax,0x19 
// 		out dx,eax 
// 		mov edx,DataPort
// 		in eax,dx 
// 		mov x,eax 
// 		mov edx,CommandPort 
// 		mov eax,0x1a 
// 		out dx,eax 
// 		mov edx,DataPort
// 		in eax,dx 
// 		mov y,eax 
// 		pop edx 
// 		pop eax
// 	}

	SyserWritePortDword(CommandPort,0x19);
	x = SyserReadPortDword(DataPort);
	SyserWritePortDword(CommandPort,0x1a);
	y = SyserReadPortDword(DataPort);

	*mousex=x;
	*mousey=y;
}
void SetVMWareMousePos(DWORD CommandPort,DWORD DataPort,DWORD mousex,DWORD mousey)
{
	SyserWritePortDword(CommandPort,VMWARESET_CURSOR_POINT_FLAG);
	SyserWritePortDword(DataPort,1);

	SyserWritePortDword(CommandPort,VMWARESET_CURSOR_POINT_X);
	SyserWritePortDword(DataPort,mousex);

	SyserWritePortDword(CommandPort,VMWARESET_CURSOR_POINT_Y);
	SyserWritePortDword(DataPort,mousey);

	SyserWritePortDword(CommandPort,VMWARESET_ACCESS_FLAG);
	SyserWritePortDword(DataPort,0);
// 	__asm
// 	{
// 		push eax 
// 		push edx
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_FLAG
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,1
// 		out dx,eax
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_X
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousex 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_Y
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousey 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_ACCESS_FLAG 
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,0 
// 		out dx,eax
// 		/*
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_FLAG
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,0
// 		out dx,eax
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_X
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousex 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_Y
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousey 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_ACCESS_FLAG 
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,0 
// 		out dx,eax
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_FLAG
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,1
// 		out dx,eax
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_X
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousex 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_Y
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousey 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_ACCESS_FLAG 
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,0 
// 		out dx,eax
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_FLAG
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,0
// 		out dx,eax
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_X
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousex 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_CURSOR_POINT_Y
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,mousey 
// 		out dx,eax 
// 		mov edx,CommandPort 
// 		mov eax,VMWARESET_ACCESS_FLAG 
// 		out dx,eax 
// 		mov edx,DataPort
// 		mov eax,1 
// 		out dx,eax
// 		*/
// 		pop edx 
// 		pop eax
// 	}
}
void FlushVmwareScreenBuffer(WORD CommandPort,WORD DataPort)
{
// 	__asm{
// 		push eax 
// 		push edx
// 		mov dx,CommandPort
// 		mov eax,0x1b
// 		out dx,eax 
// 		mov dx,DataPort 
// 		mov eax,0 
// 		out dx,eax
// 		mov dx,CommandPort
// 		mov eax,0x1b
// 		out dx,eax 
// 		mov dx,DataPort 
// 		mov eax,2 
// 		out dx,eax
// 		pop edx 
// 		pop eax
// 	}

	SyserWritePortDword(CommandPort,0x1b);
	SyserWritePortDword(DataPort,0);

	SyserWritePortDword(CommandPort,0x1b);
	SyserWritePortDword(DataPort,2);
}



void Lru_trans_svga_command(ULONG i_ulong)
{
	ULONG*                  p_ulong;
	BOOL					tBool;
	ULONG					t_ulong;

	if(gpSyser->m_PCSystem.m_VmwareSecondFrameBuffer==NULL)
		return;
	p_ulong =gpSyser->m_PCSystem.m_VmwareSecondFrameBuffer;
	tBool = FALSE;

	if ((p_ulong[2]+4)==p_ulong[3])
		tBool = TRUE;
	if ((!tBool)&&((p_ulong[1]-4)==p_ulong[2]))
	{
		if (p_ulong[0]==p_ulong[3])
			tBool = TRUE;
	}
	p_ulong =gpSyser->m_PCSystem.m_VmwareSecondFrameBuffer;
	t_ulong = p_ulong[2]>>2;
	p_ulong[t_ulong] = i_ulong;

	if ((p_ulong[2]+4) == p_ulong[1])
	{
		p_ulong[2] = p_ulong[0];
	}
	else
	{
		p_ulong[2] = p_ulong[2]+4;
	}
} 

void FlushVedioBuffer(int x,int y,int width,int heigh,int command)
{
	Lru_trans_svga_command(1);
	Lru_trans_svga_command(x);
	Lru_trans_svga_command(y);
	Lru_trans_svga_command(width);
	Lru_trans_svga_command(heigh);
	//if(command==0)
	FlushVmwareScreenBuffer(gpSyser->m_PCSystem.m_VmwareVideoCommandPort,gpSyser->m_PCSystem.m_VmwareVideoDatePort);
	//else
	//	FlushMouseBuffer(gpSyser->m_PCSystem.m_VmwareVideoCommandPort,gpSyser->m_PCSystem.m_VmwareVideoDatePort);
}

// 
// 
// __declspec(naked) DWORD __stdcall VMWareCall(PVMVWARE_CALL pVMCParam)
// {
// 	__asm
// 	{
// 		push ebp 
// 		mov ebp,esp 
// 		push ecx
// 		pushad
// 		mov eax,[ebp+8]
// 		mov word ptr[eax+0xc],'VX'
// 		mov dword ptr[eax],'VMXh'
// 		mov edi,[eax+14h]
// 		mov esi,[eax+10h]
// 		mov edx,[eax+0Ch]
// 		mov ecx,[eax+8]
// 		mov ebx,[eax+4]
// 		mov eax,[eax]
// 		in  eax,dx
// 		mov [ebp-4],eax 
// 		mov eax,[ebp+8]		
// 		mov [eax+4],ebx		
// 		mov [eax+8],ecx	
// 		mov [eax+0Ch],edx
// 		mov [eax+10h],esi
// 		mov [eax+14h],edi								
// 		mov ebx,[ebp+8]
// 		mov eax,[ebp-4]
// 		mov [ebx],eax
// 		popad
// 		pop eax
// 		pop ebp
// 		ret 4
// 	}
// }
// 

bool IsSupportVMMouse()
{
	DWORD bret=0;
	
	//DbgPrint("Syser : IsSupportVMMouse\n");
// 	__asm
// 	{
// 		pushad 
// 		mov eax,'VMXh'
// 		mov ebx,0xa9b2a797
// 		mov ecx,0xa 
// 		mov edx,'VX'
// 		mov esi,0
// 		mov edi,0 
// 		in eax,dx 
// 		cmp ebx,'VMXh'
// 		jnz local_001
// 		mov bret,1
// local_001:
// 		popad
// 	}
// 	return bret==1;

	VMVWARE_CALL  VMCParam;

	VMCParam.Exist_flag=0xA9B2A797;
	VMCParam.Func_num=0xa;
	SyserVMWareCall(&VMCParam);
/*
	DbgPrint("eax=%08x ebx=%08x ecx=%08x edx=%08x esi=%08x edi=%08x\n",VMCParam.Return_Status,VMCParam.Exist_flag,
		VMCParam.Func_num,VMCParam.Port,VMCParam.Trans_Src,VMCParam.Trans_Dest);
*/
	if ((VMCParam.Exist_flag!=0x564D5868)||(VMCParam.Return_Status==0xffffffff))
		return false;
	VMCParam.Exist_flag=0;
	VMCParam.Func_num=0xa;
	SyserVMWareCall(&VMCParam);
/*
	DbgPrint("eax=%08x ebx=%08x ecx=%08x edx=%08x esi=%08x edi=%08x\n",VMCParam.Return_Status,VMCParam.Exist_flag,
		VMCParam.Func_num,VMCParam.Port,VMCParam.Trans_Src,VMCParam.Trans_Dest);
*/
	if ((VMCParam.Exist_flag!=0x564D5868)||(VMCParam.Return_Status==0xffffffff))
		return false;
	return true;

}

bool GetVMMouseData(PTRANS_MOUSEDATA pTranMouseData)
{		
	DWORD dwData,dwExit;

	dwData=SyserReadPortDword(0x64);

	if ((dwData&0xffff0000)==0xffff0000)
		return false;
	dwData=dwData&0xffff;
	//if (dwData==0)
	//	return false;
	//if ((dwData%4)!=0)
	//	return false;

	dwExit=dwData;	
	dwData=SyserReadPortDword(0x60);
	pTranMouseData->Priority_flag=(USHORT)((dwData>>0x10)&0xffff);
	pTranMouseData->ButtonStatus=(USHORT)((dwData)&0xffff);
	dwData=SyserReadPortDword(0x60);
	pTranMouseData->DeltaX=dwData;
	dwData=SyserReadPortDword(0x60);
	pTranMouseData->DeltaY=dwData;
	dwData=SyserReadPortDword(0x60);
	pTranMouseData->DeltaWheel=dwData;
	dwExit=dwExit>>2;
	if (dwExit)
		return true;
	return false;
}
