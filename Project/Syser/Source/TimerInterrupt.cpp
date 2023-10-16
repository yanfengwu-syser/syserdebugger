#include "StdAfx.h"
#include "TimerInterrupt.h"
#include "IOAPIC.h"
#include "X86Optr.h"
#include "Syser.h"
#include "HardWareInterruptCtrl.h"
#include "UHCIDevice.h"


#ifdef __cplusplus
extern "C" {
#endif
DWORD dwTimerCounter = 0;
BYTE byteOldRTC_Register_A=0;
BYTE byteOldRTC_Register_B=0;
BYTE byteOldRTC_Register_C=0;
BYTE byteOldRTC_Register_D=0;
BYTE TimeSecond=0xff;
BYTE TimeHour=0;
BYTE TimeMinute=0;
bool bIsExecuteTimerInterrupt = false;
BYTE dwTmpRTC;
DWORD gdwOldTimerInterrupt=0;
DWORD gdwTimerInterruptNum=0;
ULONGLONG gTSCTickCount=300000;

#ifdef __cplusplus
}; // extern "C"
#endif

__declspec (naked) void Interrupt_0xFA_Timer_Service()
{
	__asm{
		pushfd
		cmp cs:bIsExecuteTimerInterrupt,1
		jz local_2
		popfd
		ret
local_2:
		pushad
		push ds 
		push es 
		mov eax,0x23 
		mov ds,ax 
		mov es,ax 

	}	
	dwTimerCounter++;
	if((dwTimerCounter%20)==0)
		gpSyser->OnTimer(20);
	gpSyser->m_PCSystem.USBDeviceService();
	SetInteruptEOI(IOAPIC_TIMER_INTERRUPT_NUM);
	__asm{
		pop es
		pop ds
		popad
		popfd
		lea esp,[esp+4]
		iretd
	}
}
bool InstallTimeInterrupt()
{	
	if(bIsExecuteTimerInterrupt)
	{
		return true;
	}
	bIsExecuteTimerInterrupt=true;
	if(gbIsUseAPIC)
	{
		__asm{
			push eax 
			push edx 
			mov edx,0x43 
			mov al ,0x36 
			out dx,al 
			jmp local_1 
local_1:
			jmp local_2 
local_2:
			mov eax, 1193
			sub edx,3 
			out dx,al 
			mov al,ah 
			jmp local_3 
local_3: 
			jmp local_4 
local_4: 
			out dx,al 
			pop edx 
			pop eax 
		}
		return true;
	}
	/*
	*	Bits[3:0] Periodic Rate Bits[3:0] Periodic Rate
	0000 none			1000 3.90625 ms
	0001 3.90625 ms		1001 7.8125 ms
	0010 7.8125 ms		1010 15.625 ms
	0011 122.070 ms		1011 31.25 ms
	0100 244.141 ms		1100 62.5 ms
	0101 488.281 ms		1101 125 ms
	0110 976.5625 ms	1110 250 ms
	0111 1.953125 ms	1111 500 ms
	*/

	__asm{
		push eax
		push edx
		push ecx
		mov edx,71h
		mov ecx,0x8000
local_001:
		dec edx
		mov al,0ah
		out dx,al
		inc edx
		in al,dx
		test al,0x80
		loopnz local_001		
		mov byteOldRTC_Register_A,al
		dec edx
		mov al,0bh
		out dx,al
		inc edx			
		in al,dx
		mov byteOldRTC_Register_B,al
		mov ecx,0x8000
local_007:
		mov al,0ah
		dec edx
		out dx,al
		inc edx
		in al,dx
		test al,0x80
		loopnz local_007		
		mov al,2bh  //7.8125 毫秒一次中断
		out dx,al		
		mov al,0bh
		dec edx
		out dx,al
		inc edx
		mov al,byteOldRTC_Register_B
		or al,052h
		and al,0dfh
		out dx,al
		mov al,0ch
		dec edx		
		out dx,al 
		inc edx
		in al,dx
		pop ecx
		pop edx
		pop eax
	}	
	TimeSecond=0xff;	
	return true;
}

bool UninstallTimeInterrupt()
{		
	if(bIsExecuteTimerInterrupt==false)
		return true;
	if(gbIsUseAPIC)
	{
		bIsExecuteTimerInterrupt=false;
		return true;
	}
	__asm
	{
		push eax
		push edx
		push ecx
		mov dx,070h
		mov ecx,0x8000
local_001:		
		mov al,0ah
		out dx,al 		
		inc edx
		in al,dx
		test al,80h		
		loopnz local_001
		mov al,0ah
		dec edx
		out dx,al 
		inc edx
		mov al,byteOldRTC_Register_A
		out dx,al 		
		dec edx
		mov al,0bh
		out dx,al 
		inc edx
		mov al,byteOldRTC_Register_B
		out dx,al
		mov al,0ch
		dec edx
		out dx,al 
		inc dx
		in al,dx
		pop ecx
		pop edx
		pop eax
	}
	bIsExecuteTimerInterrupt=false;
	return true;
}
__declspec (naked) void TimeInterrupeService()
{	
	__asm{
		pushfd
		cmp cs:bIsExecuteTimerInterrupt,1
		jz local_2
		popfd
		ret	
local_2:
		pushad	
		push ds
		mov eax,0x10
		mov ds,ax				
	}
	gSystemTickCount++;
	gpSyser->OnTimer(30);
	SyserWritePortByte(0x70,0xc);
	dwTmpRTC = SyserReadPortByte(0x71);
	gpSyser->m_PCSystem.USBDeviceService();
	if(dwTmpRTC & 0x10)
	{
		if(TimeSecond==0xff)
		{
			__asm{
				push edx
				push eax
				mov dx,071h
local_1:				
				dec edx
				mov al,0ah
				out dx,al 
				inc dx
				in al,dx 
				test al,0x80
				jnz local_1
				dec edx
				mov al,0 
				out dx,al 
				inc dx
				in al,dx
				mov TimeSecond,al 
				dec edx
				mov al,2
				out dx,al
				inc edx
				in al,dx 
				mov TimeMinute,al 
				dec edx 
				mov al,4
				out dx,al
				inc edx
				in al,dx
				mov TimeHour,al
				pop eax
				pop edx
			}
			TimeSecond = (TimeSecond >> 4) * 10 + (TimeSecond & 0xf);
			TimeMinute = (TimeMinute >> 4) * 10 + (TimeMinute & 0xf);
			TimeHour = (TimeHour >> 4) * 10 + (TimeHour & 0xf);
		}else
		{
			TimeSecond++;
			if(TimeSecond==60)
			{
				TimeSecond = 0;
				TimeMinute++;
			}
			if(TimeMinute == 60)
			{
				TimeMinute = 0;
				TimeHour++;
			}
			TimeHour %= 24;
			//gpSyser->m_MainFrame.Update();
		}

	}
	SetInteruptEOI(8);
	__asm{	
		pop ds		
		popad
		popfd
		lea esp,[esp+4]
		iretd
	}
}

ULONG __declspec(naked) CalibrateByTimer()
{
#if 0
	_asm{
		pushfd
		pushad
		cli
local_12345:
		mov al,0ah
		out 70h,al		
		jmp short $+2
		in al,71h
		test al,80h
		jnz local_12345
		mov al,0
		out 70h,al
		jmp short $+2
		in al,71h
		mov bl,al 
local_212:		
		mov al,0ah
		out 70h,al
		jmp short $+2
		in al,71h
		test al,80h
		jnz local_212
		mov al,0
		out 70h,al 
		jmp short $+2
		in al,71h
		mov bh,al
		rdtsc
		mov esi,eax
		mov edi,edx
		cmp bl,bh
		jz local_212
local_213:
		mov al,0ah
		out 70h,al 
		jmp short $+2
		in al,71h
		test al,80h
		jnz local_213
		mov al,0
		out 70h,al 
		jmp short $+2
		in al,71h
		mov bl,al
		cmp bh,bl
		jz local_213		
		popad
		popfd
	}
#endif
	__asm {
		pushfd
		push esi
		push edi
		push ebx
		push ecx
		push edx
		xor esi, esi
		cli
		mov ecx, 4
loc_4456F:
		push ecx
		mov al, 0D2h
		out 43h, al
		jmp short $+2
		in al, 40h
		mov cl, al
		in al, 40h
		mov ch, al
		rdtsc
		mov edi, eax
		xor ah, ah
loc_44584:
		mov al, 0D2h
		out 43h, al
		in al, 40h
		mov bl, al
		in al, 40h
		mov bh, al
		or ah, ah
		jnz short loc_4459D
		cmp bx, cx
		jbe short loc_44584
		inc ah
		jmp short loc_44584

loc_4459D:
		cmp bx, cx
		ja short loc_44584
		rdtsc
		sub eax, edi
		add esi, eax
		pop ecx
		loop loc_4456F
		shr esi,2
		mov eax,esi
		pop edx
		pop ecx
		pop ebx
		pop edi
		pop esi
		popfd
		retn
	}
}

ULONGLONG gPrevTSC=0;

ULONGLONG InitSTCTickCount()
{	
	gPrevTSC=SyserGetTSC();
	__asm
	{
		pushfd
		push esi
		push edi
		push ecx 
		push edx 
		push ebx
		push eax
		push eax
		cli
		in al,0x61
		mov [esp],eax  //保存8253 的通道2的门脉冲的原始状态
		and al,0xfe
		out 0x61,al    //关闭8253的通道2的门脉冲,也就是禁止8253的通道2的计数
		mov al,0xb6    //写8253的命令字  先写低字节,再写高字节 通道2
		out 0x43,al
		
		mov ax,1193  //每秒种 1000Hz   计算1毫秒时间内 RDTSC 的计数 也就是8253 通道2的计数器的值每秒钟回绕 1000次
		out 0x42,al 
		
		mov al,ah
		out 0x42,al 
		xor ecx,ecx
		in al,0x61
		or al,1
		out 0x61,al	//打开 8253 的通道2 的门脉冲 允许 8253 的通道2开始计数
		xor edx,edx
		mov edi,300000
local_00a:
		mov al,0xd8  ////写8253的命令字  先读低字节,再读高字节 通道2
		out 0x43,al
		in al,0x42
		mov cl,al
		in al,0x42
		mov ch,al
		inc edx 
		cmp edx,0x20000000
		jg local_111   //这种情况只发生在 8253 通道2 不计数的情况下
		cmp cx,800
		jg local_00a
		rdtsc
		mov edi,eax
		mov esi,edx
		xor ah,ah
local_009:
		mov al,0xd8
		out 0x43,al
		in al,0x42
		mov bl,al
		in al,0x42
		mov bh,al
		or ah, ah
		jnz local_010
		cmp bx,cx
		jbe local_009
		inc ah
		jmp local_009
local_010:
		cmp bx, cx
		ja local_009
		rdtsc
		sub eax,edi
		sbb edx,esi
		mov edi,eax
local_111:
		pop eax 
		out 0x61,al
		pop eax
		mov eax,edi
		pop ebx 
		lea esp,[esp+4]
		//pop edx 
		pop ecx 
		pop edi
		pop esi
		popfd
	}
}