#include "stdafx.h"
#include "SerialMouse.h"
#include "InputDriver.h"
#include "HardWareInterruptCtrl.h"
#include "Syser.h"
#include "Mouse.h"
stSerialMouse aSerialMouseData[]={
	{0x3f8,0x4,0x2},//Microsoft mode compatible      COM1
	{0x2f8,0x3,0x2},//Microsoft mode compatible      COM2
	{0x3f8,0x4,0x3},//Mouse system mode compatible   COM1
	{0x2f8,0x3,0x3},//Mouse system mode compatible   COM2
};

#ifdef __cplusplus
extern "C" {
#endif

WORD wSerialMousePort = 0x2f8;
BYTE byte3F8 = 0;
BYTE byte3FD = 0;
DWORD dwSerialMouseInterruptCounter = 0;
DWORD dwMouseMoveEventCounter = 0;
VOID SyserSerialMouseInterruptServiceInternal(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif


VOID SyserSerialMouseInterruptServiceInternal(VOID)
{
	do 
	{
		if(byte3FD & 0x2)//如果出现数据过载
		{
			stKeyGlobalVariable.dwMouseDataIndex = 0;
			dwMouseBeginBufferIndex = 0;
			dwMousePrePackageSize = 0;
			break;
		}
		if(dwMouseBeginBufferIndex < 3 && dwMousePrePackageSize == 0)
		{		
			MouseBeginBuffer[dwMouseBeginBufferIndex++] = stKeyGlobalVariable.chCurrentMouseData;		
			if(stKeyGlobalVariable.chCurrentMouseData & 0x40)
			{
				dwMousePackageBeginOffset = dwMouseBeginBufferIndex;
				stKeyGlobalVariable.dwMouseDataIndex = 1;
				dwMousePrePackageSize = 3;
				CurrentMouseData.D3.cFirstData = stKeyGlobalVariable.chCurrentMouseData;
			}		
		}
		else
		{
			stKeyGlobalVariable.dwMouseDataIndex ++;

			if(stKeyGlobalVariable.dwMouseDataIndex == 1)
				CurrentMouseData.D3.cFirstData = stKeyGlobalVariable.chCurrentMouseData;			
			if(stKeyGlobalVariable.dwMouseDataIndex == 2)		
				CurrentMouseData.D3.cXOffset = ((CurrentMouseData.D3.cFirstData & 0x3) << 6) | stKeyGlobalVariable.chCurrentMouseData;					
			if(stKeyGlobalVariable.dwMouseDataIndex == 3)		
				CurrentMouseData.D3.cYOffset = ((CurrentMouseData.D3.cFirstData & 0xc) << 4) | stKeyGlobalVariable.chCurrentMouseData;					

			if(stKeyGlobalVariable.dwMouseDataIndex == dwMousePrePackageSize)
			{
				dwMouseMoveEventCounter++;
				stKeyGlobalVariable.dwMouseDataIndex = 0;
				if((PrevMouseData.D3.cFirstData & 0x10) != (CurrentMouseData.D3.cFirstData & 0x10))			
					gpSyser->OnKeyEvent(WISP_VK_RBUTTON,(CurrentMouseData.D3.cFirstData & 0x10)!=0);
				if((PrevMouseData.D3.cFirstData & 0x20) != (CurrentMouseData.D3.cFirstData & 0x20))			
					gpSyser->OnKeyEvent(WISP_VK_LBUTTON,(CurrentMouseData.D3.cFirstData & 0x20)!=0);
				if(CurrentMouseData.D3.cYOffset != 0 || CurrentMouseData.D3.cXOffset != 0)			
					gpSyser->OnMouseMove(CurrentMouseData.D3.cXOffset,CurrentMouseData.D3.cYOffset);			

				PrevMouseData.D3.cFirstData = CurrentMouseData.D3.cFirstData;
				PrevMouseData.D3.cXOffset = CurrentMouseData.D3.cXOffset;
				PrevMouseData.D3.cYOffset = CurrentMouseData.D3.cYOffset;				
			}
		}
	} while (FALSE);
}
// 
// __declspec (naked) void SerialMouseInterruptService()
// {
// 	__asm{	
// 		cmp cs:dwOldInterruptF9,1
// 		jnz local_007
// 		mov ss:dwOldInterruptF9,0
// 		push cs:dwInterruptF9Address
// 		ret
// local_007:
// 		cmp cs:gbActive,TRUE
// 		jz local_1
// 		push dword ptr cs:stKeyGlobalVariable.dwOldMouseInterrupt
// 		ret		
// local_1:
// 		pushad
// 		pushfd			
// 		push ds
// 		movzx edx,wSerialMousePort
// 		lea edx,[edx+5]
// 		in al,dx
// 		mov byte3FD,al
// 		lea edx,[edx-5]
// 		in al,dx	
// 		mov stKeyGlobalVariable.chCurrentMouseData,al
// 	}
// 
// 	if(byte3FD & 0x2)//如果出现数据过载
// 	{
// 		stKeyGlobalVariable.dwMouseDataIndex = 0;
// 		dwMouseBeginBufferIndex = 0;
// 		dwMousePrePackageSize = 0;
// 		goto local_quit;
// 	}
// 	if(dwMouseBeginBufferIndex < 3 && dwMousePrePackageSize == 0)
// 	{		
// 		MouseBeginBuffer[dwMouseBeginBufferIndex++] = stKeyGlobalVariable.chCurrentMouseData;		
// 		if(stKeyGlobalVariable.chCurrentMouseData & 0x40)
// 		{
// 			dwMousePackageBeginOffset = dwMouseBeginBufferIndex;
// 			stKeyGlobalVariable.dwMouseDataIndex = 1;
// 			dwMousePrePackageSize = 3;
// 			CurrentMouseData.D3.cFirstData = stKeyGlobalVariable.chCurrentMouseData;
// 		}		
// 	}
// 	else
// 	{
// 		stKeyGlobalVariable.dwMouseDataIndex ++;
// 
// 		if(stKeyGlobalVariable.dwMouseDataIndex == 1)
// 			CurrentMouseData.D3.cFirstData = stKeyGlobalVariable.chCurrentMouseData;			
// 		if(stKeyGlobalVariable.dwMouseDataIndex == 2)		
// 			CurrentMouseData.D3.cXOffset = ((CurrentMouseData.D3.cFirstData & 0x3) << 6) | stKeyGlobalVariable.chCurrentMouseData;					
// 		if(stKeyGlobalVariable.dwMouseDataIndex == 3)		
// 			CurrentMouseData.D3.cYOffset = ((CurrentMouseData.D3.cFirstData & 0xc) << 4) | stKeyGlobalVariable.chCurrentMouseData;					
// 
// 		if(stKeyGlobalVariable.dwMouseDataIndex == dwMousePrePackageSize)
// 		{
// 			dwMouseMoveEventCounter++;
// 			stKeyGlobalVariable.dwMouseDataIndex = 0;
// 			if((PrevMouseData.D3.cFirstData & 0x10) != (CurrentMouseData.D3.cFirstData & 0x10))			
// 				gpSyser->OnKeyEvent(WISP_VK_RBUTTON,(CurrentMouseData.D3.cFirstData & 0x10)!=0);
// 			if((PrevMouseData.D3.cFirstData & 0x20) != (CurrentMouseData.D3.cFirstData & 0x20))			
// 				gpSyser->OnKeyEvent(WISP_VK_LBUTTON,(CurrentMouseData.D3.cFirstData & 0x20)!=0);
// 			if(CurrentMouseData.D3.cYOffset != 0 || CurrentMouseData.D3.cXOffset != 0)			
// 				gpSyser->OnMouseMove(CurrentMouseData.D3.cXOffset,CurrentMouseData.D3.cYOffset);			
// 
// 			PrevMouseData.D3.cFirstData = CurrentMouseData.D3.cFirstData;
// 			PrevMouseData.D3.cXOffset = CurrentMouseData.D3.cXOffset;
// 			PrevMouseData.D3.cYOffset = CurrentMouseData.D3.cYOffset;				
// 		}
// 	}
// local_quit:
// 	SetInteruptEOI(0x3);
// 	__asm{
// 		pop ds
// 		popfd
// 		popad
// 		iretd
// 	}	
// }

#ifdef __cplusplus
extern "C" {
#endif

bool SyserCheckSerialMouse(WORD	PortNum,BYTE	DataLen);

#ifdef __cplusplus
}; // extern "C"
#endif


bool CheckSerialMouse()
{
	int i;
	WORD wPortNum;
	BYTE byteDataLen;
	bool bRet;

	for(i = 0; i < sizeof(aSerialMouseData)/sizeof(stSerialMouse); i++)
	{
		bRet = FALSE;
		wPortNum = aSerialMouseData[i].wSerialPort;
		byteDataLen = aSerialMouseData[i].byteDataLen;
// 		__asm{
// 			push eax 
// 			push ebx 
// 			push ecx 
// 			push edx
// 			movzx edx,wPortNum
// 			add edx,3
// 			push edx
// 			mov eax,0x80
// 			out dx,al 
// 			dec edx
// 			dec edx
// 			mov eax,0
// 			out dx,al 
// 			dec edx
// 			mov eax,0x60      //设置串口的波特率
// 			out dx,al      
// 			pop edx
// 			movzx eax,byte ptr byteDataLen
// 			out dx,al        //设置数据长度
// 			dec edx
// 			dec edx 
// 			xor eax,eax
// 			out dx,al        //禁止发送中断
// 			add edx,4
// 			in al,dx 
// 			dec edx
// 			mov eax,1
// 			out dx,al //设置准备好线的状态
// 			sub edx,4
// 			mov ecx,0x8000
// local_1:
// 			in al,dx        //读出没有用的数据
// 			loop local_1
// 			add edx,5
// 			in al,dx 
// 			cmp byteDataLen,3
// 			jz local_2
// 			dec edx
// 			mov al,0xb
// 			out dx,al        //开放中断
// 			mov ebx,3
// local_6:
// 			movzx edx,word ptr wPortNum
// 			add edx,5
// 			mov ecx,0x8000
// local_3:
// 			in al,dx 
// 			test al,1
// 			loope local_3
// 			jecxz local_4
// 			sub edx,5
// 			in al,dx 
// 			cmp al,0x4d;'M'
// 			jz local_5
// 			dec ebx
// 			jnz local_6
// 			jmp local_4
// local_2:
// 			dec edx
// 			mov al,0xb
// 			out dx,al 
// 			jmp local_8
// local_8:
// 			in al,dx 
// 			cmp al,0xb
// 			jnz local_4
// local_5:
// 			movzx edx,word ptr wPortNum
// 			inc edx
// 			mov al,1
// 			out dx,al 
// 			mov bRet,TRUE
// local_4:
// 			pop edx 
// 			pop ecx 
// 			pop ebx 
// 			pop eax
// 		}

		bRet = SyserCheckSerialMouse(wPortNum,byteDataLen);
		if(bRet)
			break;
	}
	return TRUE;
}