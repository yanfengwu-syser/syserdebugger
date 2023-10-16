#include "StdAfx.h"
#include "PromptQuit.h"
int PromptQuit(char* DisplayString,LONG TimeOut)
{
	int LoopCount;
	LARGE_INTEGER  Interval;
	PHYSICAL_ADDRESS PhysicaAddressl;
	SIZE_T Size;
	BYTE *VideoBuffer=NULL;
	int RetValue=0;
	Interval.QuadPart =TimeOut;
	Size=0x8000;
	PhysicaAddressl.QuadPart=0xb8000;
	VideoBuffer = (BYTE*)MmMapIoSpace(PhysicaAddressl,Size,MmNonCached);
	LoopCount=0;
	
	DisplayTextString(DisplayString,0,24,VideoBuffer);
	VidDisplayStringXY("Press Esc to cancel loading SYSER",180,408,1);
	for(;LoopCount<250;LoopCount++)
	{
		__asm
		{
			push eax
			xor eax,eax
			in al,0x64
			test al,1 
			jz local_001
			in al,0x60 
			mov RetValue,eax
local_001:
			pop eax 
		}
		if(RetValue)
			break;
		KeDelayExecutionThread(KernelMode,FALSE,&Interval);
	}
	DisplayTextString( "                                                                              ",0,24,VideoBuffer);
	ULONG  MajorVersion;
	ULONG  MinorVersion;
	ULONG  BuildNumber;
	PsGetVersion(&MajorVersion,&MinorVersion,&BuildNumber,NULL);
	if(MajorVersion == 5 && MinorVersion == 0)
		VidSolidColorFill(180,408,180+280,408+13,15);
	else
		VidSolidColorFill(180,408,180+280,408+13,1);
	if(VideoBuffer)
		MmUnmapIoSpace(VideoBuffer,Size);
	return RetValue;
}
void DisplayTextString(char* DisplayString,int x,int y,BYTE* VideoBuffer)
{
	int i;
	int StartOffset = y*80*2+x*2;
	if(StartOffset>25*80*2||DisplayString==NULL||VideoBuffer==NULL)
		return ;
	for(i=0;DisplayString[i];i++)
	{
		VideoBuffer[StartOffset+i*2]=DisplayString[i];
		VideoBuffer[StartOffset+i*2+1]=0x7; 
	}
}