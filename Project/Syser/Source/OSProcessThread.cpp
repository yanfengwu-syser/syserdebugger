#include "StdAfx.h"
#include "OSProcessThread.h"
#include "Syser.h"
#define OS_INFO_FLAG_BUILDNUMBER 0x1
DWORD gPsActiveProcessHead=0;
DWORD gPsIdleProcess=0;

#ifdef __cplusplus
extern "C" {
#endif
extern DWORD gSystemFSRegisterSelector;

#ifdef __cplusplus
}; // extern "C"
#endif

OS_OFFSET_INFO OSOffsetInfo[]=
{
	{
0,0,5,0,2195,
0x18,                //KPROCESS_DirectoryTableBase_OFFSET;
0x20,				 //KPROCESS_LdtDescriptor_OFFSET;
0x50,				 //KPROCESS_ThreadListHead_Flink_OFFSET;
0x54,				 //KPROCESS_ThreadListHead_Blink_OFFSET;
0xa0,				 //EPROCESS_ActiveProcessLinks_Flink_OFFSET;
0xa4,				 //EPROCESS_ActiveProcessLinks_Blink_OFFSET;
0x194,				 //EPROCESS_VadRoot_OFFSET;
0x128,				 //EPROCESS_ObjectTable_OFFSET;
0x1b0,				 //EPROCESS_Peb_OFFSET;
0x9c,				 //EPROCESS_UniqueProcessId_OFFSET;
0x1fc,				 //EPROCESS_ImageFileName_OFFSET;
0x44,				 //KTHREAD_ApcState_Process_OFFSET;
0x1a4,				 //KTHREAD_ThreadListEntry_Flink_OFFSET;
0x1a8,				 //KTHREAD_ThreadListEntry_Blink_OFFSET;
0x1e4,				 //ETHREAD_Cid_UniqueThread_OFFSET;
0x18,				 //KTHREAD_InitialStack_OFFSET;
0x1c,				 //KTHREAD_StackLimit_OFFSET;
0x28,				 //KTHREAD_KernelStack_OFFSET;
0x20,				 //KTHREAD_Teb_OFFSET;
0xdc,				 //KTHREAD_ServiceTable_OFFSET;
0xffffffff,			 //KTHREAD_TrapFrame_OFFSET;
0xffffffff,			 //KTHREAD_State_OFFSET;
0x230,				 //ETHREAD_StartAddress_OFFSET;
0x6cc,				 //TEB_Win32ClientInfo_OFFSET;
0x8,				 //WIN32CLIENT_hwnd_OFFSET;
	},
	{
		0,0,5,1,2600,
0x18,                //KPROCESS_DirectoryTableBase_OFFSET;
0x20,				 //KPROCESS_LdtDescriptor_OFFSET;
0x50,				 //KPROCESS_ThreadListHead_Flink_OFFSET;
0x54,				 //KPROCESS_ThreadListHead_Blink_OFFSET;
0x88,				 //EPROCESS_ActiveProcessLinks_Flink_OFFSET;
0x8c,				 //EPROCESS_ActiveProcessLinks_Blink_OFFSET;
0x11C,				 //EPROCESS_VadRoot_OFFSET;
0xc4,				 //EPROCESS_ObjectTable_OFFSET;
0x1b0,				 //EPROCESS_Peb_OFFSET;
0x84,				 //EPROCESS_UniqueProcessId_OFFSET;
0x174,				 //EPROCESS_ImageFileName_OFFSET;
0x44,				 //KTHREAD_ApcState_Process_OFFSET;
0x1b0,				 //KTHREAD_ThreadListEntry_Flink_OFFSET;
0x1b4,				 //KTHREAD_ThreadListEntry_Blink_OFFSET;
0x1f0,				 //ETHREAD_Cid_UniqueThread_OFFSET;
0x18,				 //KTHREAD_InitialStack_OFFSET;
0x1c,				 //KTHREAD_StackLimit_OFFSET;
0x28,				 //KTHREAD_KernelStack_OFFSET;
0x20,				 //KTHREAD_Teb_OFFSET;
0xe0,				 //KTHREAD_ServiceTable_OFFSET;
0x134,				 //KTHREAD_TrapFrame_OFFSET;
0x2d,				 //KTHREAD_State_OFFSET;
0x224,				 //ETHREAD_StartAddress_OFFSET;
0x6cc,				 //TEB_Win32ClientInfo_OFFSET;
0x8,				 //WIN32CLIENT_hwnd_OFFSET;
},
{
	0,0,6,0,6000,
0x18,                //KPROCESS_DirectoryTableBase_OFFSET;
0x20,				 //KPROCESS_LdtDescriptor_OFFSET;
0x50,				 //KPROCESS_ThreadListHead_Flink_OFFSET;
0x54,				 //KPROCESS_ThreadListHead_Blink_OFFSET;
0xa0,				 //EPROCESS_ActiveProcessLinks_Flink_OFFSET;
0xa4,				 //EPROCESS_ActiveProcessLinks_Blink_OFFSET;
0xf8,				 //EPROCESS_VadRoot_OFFSET;
0xdc,				 //EPROCESS_ObjectTable_OFFSET;
0x188,				 //EPROCESS_Peb_OFFSET;
0x9c,				 //EPROCESS_UniqueProcessId_OFFSET;
0x14c,				 //EPROCESS_ImageFileName_OFFSET;
0x48,				 //KTHREAD_ApcState_Process_OFFSET;
0x1c4,				 //KTHREAD_ThreadListEntry_Flink_OFFSET;
0x1c8,				 //KTHREAD_ThreadListEntry_Blink_OFFSET;
0x210,				 //ETHREAD_Cid_UniqueThread_OFFSET;
0x28,				 //KTHREAD_InitialStack_OFFSET;
0x2c,				 //KTHREAD_StackLimit_OFFSET;
0x30,				 //KTHREAD_KernelStack_OFFSET;
0x84,				 //KTHREAD_Teb_OFFSET;
0x12C,				 //KTHREAD_ServiceTable_OFFSET;
0x120,				 //KTHREAD_TrapFrame_OFFSET;
0x5c,				 //KTHREAD_State_OFFSET;
0x1f4,				 //ETHREAD_StartAddress_OFFSET;
0x6cc,				 //TEB_Win32ClientInfo_OFFSET;
0x8,				 //WIN32CLIENT_hwnd_OFFSET;
},
{
0,1,6,1,7000,
0x18,                //KPROCESS_DirectoryTableBase_OFFSET;
0x20,				 //KPROCESS_LdtDescriptor_OFFSET;
0x50,				 //KPROCESS_ThreadListHead_Flink_OFFSET;
0x54,				 //KPROCESS_ThreadListHead_Blink_OFFSET;
0xB8,				 //EPROCESS_ActiveProcessLinks_Flink_OFFSET;
0xBc,				 //EPROCESS_ActiveProcessLinks_Blink_OFFSET;
0x270,				 //EPROCESS_VadRoot_OFFSET;
0xf4,				 //EPROCESS_ObjectTable_OFFSET;
0x1a0,				 //EPROCESS_Peb_OFFSET;
0xb4,				 //EPROCESS_UniqueProcessId_OFFSET;
0x164,				 //EPROCESS_ImageFileName_OFFSET;
0x50,				 //KTHREAD_ApcState_Process_OFFSET;
0x1e4,				 //KTHREAD_ThreadListEntry_Flink_OFFSET;
0x1e8,				 //KTHREAD_ThreadListEntry_Blink_OFFSET;
0x230,				 //ETHREAD_Cid_UniqueThread_OFFSET;
0x28,				 //KTHREAD_InitialStack_OFFSET;
0x2c,				 //KTHREAD_StackLimit_OFFSET;
0x30,				 //KTHREAD_KernelStack_OFFSET;
0x88,				 //KTHREAD_Teb_OFFSET;
0x134,				 //KTHREAD_ServiceTable_OFFSET;
0x128,				 //KTHREAD_TrapFrame_OFFSET;
0x68,				 //KTHREAD_State_OFFSET;
0x218,				 //ETHREAD_StartAddress_OFFSET;
0x6cc,				 //TEB_Win32ClientInfo_OFFSET;
0x8,				 //WIN32CLIENT_hwnd_OFFSET;
},

{
	0,1,6,1,7100,
0x18,                //KPROCESS_DirectoryTableBase_OFFSET;
0x20,				 //KPROCESS_LdtDescriptor_OFFSET;
0x2c,				 //KPROCESS_ThreadListHead_Flink_OFFSET;
0x30,				 //KPROCESS_ThreadListHead_Blink_OFFSET;
0xB8,				 //EPROCESS_ActiveProcessLinks_Flink_OFFSET;
0xBc,				 //EPROCESS_ActiveProcessLinks_Blink_OFFSET;
0x274,				 //EPROCESS_VadRoot_OFFSET;
0xf4,				 //EPROCESS_ObjectTable_OFFSET;
0x1a8,				 //EPROCESS_Peb_OFFSET;
0xb4,				 //EPROCESS_UniqueProcessId_OFFSET;
0x16c,				 //EPROCESS_ImageFileName_OFFSET;
0x50,				 //KTHREAD_ApcState_Process_OFFSET;
0x1e0,				 //KTHREAD_ThreadListEntry_Flink_OFFSET;
0x1e4,				 //KTHREAD_ThreadListEntry_Blink_OFFSET;
0x230,				 //ETHREAD_Cid_UniqueThread_OFFSET;
0x28,				 //KTHREAD_InitialStack_OFFSET;
0x2c,				 //KTHREAD_StackLimit_OFFSET;
0x30,				 //KTHREAD_KernelStack_OFFSET;
0x88,				 //KTHREAD_Teb_OFFSET;
0xbc,				 //KTHREAD_ServiceTable_OFFSET;
0x128,				 //KTHREAD_TrapFrame_OFFSET;
0x68,				 //KTHREAD_State_OFFSET;
0x218,				 //ETHREAD_StartAddress_OFFSET;
0x6cc,				 //TEB_Win32ClientInfo_OFFSET;
0x8,				 //WIN32CLIENT_hwnd_OFFSET;
},

{
	0,1,6,1,7600,
		0x18,                //KPROCESS_DirectoryTableBase_OFFSET;
		0x20,				 //KPROCESS_LdtDescriptor_OFFSET;
		0x2c,				 //KPROCESS_ThreadListHead_Flink_OFFSET;
		0x30,				 //KPROCESS_ThreadListHead_Blink_OFFSET;
		0xB8,				 //EPROCESS_ActiveProcessLinks_Flink_OFFSET;
		0xBc,				 //EPROCESS_ActiveProcessLinks_Blink_OFFSET;
		0x274,				 //EPROCESS_VadRoot_OFFSET;
		0xf4,				 //EPROCESS_ObjectTable_OFFSET;
		0x1a8,				 //EPROCESS_Peb_OFFSET;
		0xb4,				 //EPROCESS_UniqueProcessId_OFFSET;
		0x16c,				 //EPROCESS_ImageFileName_OFFSET;
		0x50,				 //KTHREAD_ApcState_Process_OFFSET;
		0x1e0,				 //KTHREAD_ThreadListEntry_Flink_OFFSET;
		0x1e4,				 //KTHREAD_ThreadListEntry_Blink_OFFSET;
		0x230,				 //ETHREAD_Cid_UniqueThread_OFFSET;
		0x28,				 //KTHREAD_InitialStack_OFFSET;
		0x2c,				 //KTHREAD_StackLimit_OFFSET;
		0x30,				 //KTHREAD_KernelStack_OFFSET;
		0x88,				 //KTHREAD_Teb_OFFSET;
		0xbc,				 //KTHREAD_ServiceTable_OFFSET;
		0x128,				 //KTHREAD_TrapFrame_OFFSET;
		0x68,				 //KTHREAD_State_OFFSET;
		0x218,				 //ETHREAD_StartAddress_OFFSET;
		0x6cc,				 //TEB_Win32ClientInfo_OFFSET;
		0x8,				 //WIN32CLIENT_hwnd_OFFSET;
	},
		{
	0,1,6,1,7601,
		0x18,                //KPROCESS_DirectoryTableBase_OFFSET;
		0x1c,				 //KPROCESS_LdtDescriptor_OFFSET;
		0x2c,				 //KPROCESS_ThreadListHead_Flink_OFFSET;
		0x30,				 //KPROCESS_ThreadListHead_Blink_OFFSET;
		0xB8,				 //EPROCESS_ActiveProcessLinks_Flink_OFFSET;
		0xBc,				 //EPROCESS_ActiveProcessLinks_Blink_OFFSET;
		0x278,				 //EPROCESS_VadRoot_OFFSET;
		0xf4,				 //EPROCESS_ObjectTable_OFFSET;
		0x1a8,				 //EPROCESS_Peb_OFFSET;
		0xb4,				 //EPROCESS_UniqueProcessId_OFFSET;
		0x16c,				 //EPROCESS_ImageFileName_OFFSET;
		0x50,				 //KTHREAD_ApcState_Process_OFFSET;
		0x1e0,				 //KTHREAD_ThreadListEntry_Flink_OFFSET;
		0x1e4,				 //KTHREAD_ThreadListEntry_Blink_OFFSET;
		0x230,				 //ETHREAD_Cid_UniqueThread_OFFSET;
		0x28,				 //KTHREAD_InitialStack_OFFSET;
		0x2c,				 //KTHREAD_StackLimit_OFFSET;
		0x30,				 //KTHREAD_KernelStack_OFFSET;
		0x88,				 //KTHREAD_Teb_OFFSET;
		0xbc,				 //KTHREAD_ServiceTable_OFFSET;
		0x128,				 //KTHREAD_TrapFrame_OFFSET;
		0x68,				 //KTHREAD_State_OFFSET;
		0x218,				 //ETHREAD_StartAddress_OFFSET;
		0x6cc,				 //TEB_Win32ClientInfo_OFFSET;
		0x8,				 //WIN32CLIENT_hwnd_OFFSET;
	},
};

POS_OFFSET_INFO gOSOffsetInfo=OSOffsetInfo;
bool InitOSOffsetInfo(DWORD OSMajorVersion,DWORD OSMinorVersion,DWORD OSBuildNumber)
{
	
	for(int i=0;i<sizeof(OSOffsetInfo)/sizeof(OSOffsetInfo[0]);i++)
	{
		if(OSMajorVersion==OSOffsetInfo[i].dwMajorVersion && OSMinorVersion==OSOffsetInfo[i].dwMinorVersion)
		{
			if(OSOffsetInfo[i].dwFlags& OS_INFO_FLAG_BUILDNUMBER)
			{
				if(OSOffsetInfo[i].dwBuildNumber==OSBuildNumber)
				{
					gOSOffsetInfo=OSOffsetInfo+i;
					return true;
				}
			}
			else
			{
				gOSOffsetInfo=OSOffsetInfo+i;
				return true;
			}
		}
	}
	return false;
}

bool GetCurrentProcessAndThread(DWORD* Process,DWORD* Thread)
{
	DWORD dwLimit,dwFSBase=0;
#ifdef CODE_OS_NT_DRV
	dwFSBase=GetSegmentBaseAddress((WORD)gSystemFSRegisterSelector,&dwLimit);
	if(dwFSBase==0)
		return false;
#endif
	dwFSBase+=0x124;
	if(ReadDword((void*)dwFSBase,&dwLimit)==false)
		return false;
	if(Thread)
		*Thread=dwLimit;
	dwFSBase = dwLimit+gOSOffsetInfo->KTHREAD_ApcState_Process_OFFSET;
	if(ReadDword((void*)dwFSBase,&dwLimit)==false)
		return false;
	if(Process)
		*Process=dwLimit;
	return true;
}

bool GetIdleProcessAndThread(DWORD* Process,DWORD* Thread)
{
	DWORD dwLimit,dwFSBase=0;
#ifdef CODE_OS_NT_DRV
	dwFSBase=GetSegmentBaseAddress((WORD)gSystemFSRegisterSelector,&dwLimit);
	if(dwFSBase==0)
		return false;
#endif
	dwFSBase+=0x12c;
	if(ReadDword((void*)dwFSBase,&dwLimit)==false)
		return false;
	if(Thread)
		*Thread=dwLimit;
	dwFSBase = dwLimit+gOSOffsetInfo->KTHREAD_ApcState_Process_OFFSET;
	if(ReadDword((void*)dwFSBase,&dwLimit)==false)
		return false;
	if(Process)
		*Process=dwLimit;
	return true;
}
bool InitPsActiveProcessHead()
{
	DWORD Process,Thread,dwTemp;
	DWORD MajorVersion=0;
	DWORD MinorVersion=0;
	DWORD BuildNumber=0;
#ifdef CODE_OS_NT_DRV
	PsGetVersion(&MajorVersion,&MinorVersion,&BuildNumber,NULL);
	if(InitOSOffsetInfo(MajorVersion,MinorVersion,BuildNumber)==false)
		return false;
#endif
	if(GetCurrentProcessAndThread(&Process,&Thread)==false)
		return false;
	Process+=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Blink_OFFSET;
	if(ReadDword((void*)Process,&dwTemp)==false)
		return false;
	gPsActiveProcessHead=dwTemp;
	if(GetIdleProcessAndThread(&Process,&Thread)==false)
		return false;
	gPsIdleProcess=Process;
	DbgPrint("Syser : PsActiveProcessHead=0x%08x PsIdleProcess=%08x\n",gPsActiveProcessHead,gPsIdleProcess);
	return true;
}
bool GetThreadInfoByETHREAD(DWORD pOSThread,PSYSER_THREAD pThread)
{
	DWORD dwTemp,dwValue,dwProcess;
	if(pOSThread==0)
		return false;
	pThread->OSThread=(void*)pOSThread;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->ETHREAD_Cid_UniqueThread_OFFSET),&dwTemp)==false)
		return false;
	pThread->ThreadID=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_TrapFrame_OFFSET),&dwTemp)==false)
		return false;
	pThread->TrapFrame=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_State_OFFSET),&dwTemp)==false)
		return false;
	pThread->State=(dwTemp & 0xff);
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_InitialStack_OFFSET),&dwTemp)==false)
		return false;
	pThread->InitialStack=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_StackLimit_OFFSET),&dwTemp)==false)
		return false;
	pThread->StackLimit=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_KernelStack_OFFSET),&dwTemp)==false)
		return false;
	pThread->KernelStack=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_Teb_OFFSET),&dwTemp)==false)
		return false;
	pThread->Teb=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_ApcState_Process_OFFSET),&dwTemp)==false)
		return false;
	pThread->Process=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_ServiceTable_OFFSET),&dwTemp)==false)
		return false;
	pThread->ServiceTable=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->ETHREAD_StartAddress_OFFSET),&dwTemp)==false)
		return false;
	pThread->StartAddress=dwTemp;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_ApcState_Process_OFFSET),&dwTemp)==false)
		return false;
	dwProcess=dwTemp;
	dwValue = dwTemp+gOSOffsetInfo->KPROCESS_ThreadListHead_Flink_OFFSET;
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_ThreadListEntry_Flink_OFFSET),&dwTemp)==false)
		return false;
	
	if(dwProcess==0 || dwTemp==dwValue)
		pThread->NextThread=0;
	else
		pThread->NextThread=dwTemp-gOSOffsetInfo->KTHREAD_ThreadListEntry_Flink_OFFSET;
	
	if(ReadDword((void*)(pOSThread+gOSOffsetInfo->KTHREAD_ThreadListEntry_Blink_OFFSET),&dwTemp)==false)
		return false;
	if(dwProcess==0|| dwTemp==dwValue)
		pThread->PrevThread=0;
	else
		pThread->PrevThread=dwTemp-gOSOffsetInfo->KTHREAD_ThreadListEntry_Flink_OFFSET;

	return true;
}
bool GetNextThread(PSYSER_THREAD pThread)
{
	if(pThread->NextThread==0)
		return false;
	return GetThreadInfoByETHREAD(pThread->NextThread,pThread);
}

bool GetPrevThread(PSYSER_THREAD pThread)
{
	if(pThread->PrevThread==0)
		return false;
	return GetThreadInfoByETHREAD(pThread->PrevThread,pThread);
}

bool GetThreadByID(DWORD ThreadID,PSYSER_THREAD pThread)
{
	SYSER_PROCESS Process;
	SYSER_THREAD Thread;
	bool bOK,bOK1;
	bOK = GetFirstProcess(&Process);
	while(bOK)
	{						
		memset(&Thread,0,sizeof(Thread));
		bOK1 = GetThreadInfoByETHREAD((DWORD)Process.ThreadHead,&Thread);
		while(bOK1)
		{
			if(ThreadID==Thread.ThreadID)
			{
				memcpy(pThread,&Thread,sizeof(Thread));
				return true;
			}
			bOK1=GetNextThread(&Thread);
		}
		bOK = GetNextProcess(&Process);
	}
	return false;
}

bool GetProcessInfoByEPROCESS(DWORD pOSProcess,PSYSER_PROCESS pProcess)
{
	DWORD dwTemp,i,dwValue;
	BYTE Value;
	pProcess->OSProcess=(void*)pOSProcess;
	if(ReadDword((void*)(pOSProcess+gOSOffsetInfo->KPROCESS_DirectoryTableBase_OFFSET),&dwTemp)==false)
		return false;
	pProcess->PDT=dwTemp;
	if(ReadDword((void*)(pOSProcess+gOSOffsetInfo->EPROCESS_VadRoot_OFFSET),&dwTemp)==false)
		return false;
	pProcess->VadRoot=dwTemp;
	if(ReadDword((void*)(pOSProcess+gOSOffsetInfo->EPROCESS_ObjectTable_OFFSET),&dwTemp)==false)
		return false;
	pProcess->ObjectTable=dwTemp;
	if(ReadDword((void*)(pOSProcess+gOSOffsetInfo->EPROCESS_Peb_OFFSET),&dwTemp)==false)
		return false;
	pProcess->Peb=dwTemp;
	if(ReadDword((void*)(pOSProcess+gOSOffsetInfo->EPROCESS_UniqueProcessId_OFFSET),&dwTemp)==false)
		return false;
	pProcess->UniqueProcessId=dwTemp;
	if(ReadDword((void*)(pOSProcess+gOSOffsetInfo->KPROCESS_LdtDescriptor_OFFSET),&dwTemp)==false)
		return false;
	pProcess->LDTBaseAddress=dwTemp;
	if(ReadDword((void*)(pOSProcess+gOSOffsetInfo->KPROCESS_LdtDescriptor_OFFSET+4),&dwTemp)==false)
		return false;
	pProcess->LDTLimit=dwTemp;
	for(i=0;i<16;i++)
	{
		if(ReadByte((void*)(pOSProcess+gOSOffsetInfo->EPROCESS_ImageFileName_OFFSET+i),&Value)==false)
			return false;
		pProcess->ImageFileName[i]=Value;
		if(Value==0)
			break;
		if(Value=='.')
		{
			pProcess->ImageFileName[i]=0;
			break;
		}
	}
	pProcess->ImageFileName[15]=0;
	pProcess->ThreadHead=0;
	pProcess->ThreadTail=0;
	dwValue=pOSProcess+gOSOffsetInfo->KPROCESS_ThreadListHead_Flink_OFFSET;
	if(ReadDword((void*)(dwValue),&dwTemp)==false)
		return false;
	if(dwValue!=dwTemp && dwTemp)
	{
		dwTemp-=gOSOffsetInfo->KTHREAD_ThreadListEntry_Flink_OFFSET;
		pProcess->ThreadHead=(void*)dwTemp;
		dwValue=pOSProcess+gOSOffsetInfo->KPROCESS_ThreadListHead_Blink_OFFSET;
		if(ReadDword((void*)(dwValue),&dwTemp)==false)
			return false;
		dwTemp-=gOSOffsetInfo->KTHREAD_ThreadListEntry_Flink_OFFSET;
		pProcess->ThreadTail=(void*)dwTemp;
	}
	return true;
}
bool GetFirstProcess(PSYSER_PROCESS pProcess)
{
	DWORD dwTemp,dwNext;
	memset(pProcess,0,sizeof(*pProcess));
	if(ReadDword((void*)gPsActiveProcessHead,&dwTemp)==false)
		return false;
	dwTemp-=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Flink_OFFSET;
	if(GetProcessInfoByEPROCESS(dwTemp,pProcess)==false)
		return false;
	dwTemp+=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Flink_OFFSET;
	pProcess->Next=0;
	if(ReadDword((void*)dwTemp,&dwNext))
	{
		if(dwNext==gPsIdleProcess)
			return true;
		if(dwNext==gPsActiveProcessHead)
		{
			dwNext=gPsIdleProcess;
			dwNext+=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Flink_OFFSET;
		}
		pProcess->Next=dwNext;		
	}
	return true;
}
bool GetNextProcess(PSYSER_PROCESS pProcess)
{
	DWORD dwTemp,dwNext;
	if(pProcess->Next==0)
		return false;
	dwTemp=pProcess->Next;
	dwTemp-=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Flink_OFFSET;
	if(GetProcessInfoByEPROCESS(dwTemp,pProcess)==false)
		return false;
	dwTemp+=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Flink_OFFSET;
	pProcess->Next=0;
	if(ReadDword((void*)dwTemp,&dwNext))
	{
		if(dwNext==gPsIdleProcess)
			return true;
		if(*(DWORD*)&pProcess->OSProcess==gPsIdleProcess)
			return true;
		if(dwNext==gPsActiveProcessHead)
		{
			dwNext=gPsIdleProcess;
			dwNext+=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Flink_OFFSET;
			if(ReadDword((void*)gPsActiveProcessHead,&dwTemp))//这个逻辑是用来处理window7 上的 Idle Process 和 system Process 是相同的问题
			{
				if(dwTemp==dwNext)
					dwNext=0;
			}
			//if(gOSOffsetInfo->dwBuildNumber>=7000)
			//{
			//	dwNext=0; //in windows 7 ,The Idle Process's next link isn't 0
			//}
			//else
			//{
			//	dwNext=gPsIdleProcess;  //in windows xp and windows 2k and vista . The Idle Process's next link is 0
			//	dwNext+=gOSOffsetInfo->EPROCESS_ActiveProcessLinks_Flink_OFFSET;
			//}			
		}
		pProcess->Next=dwNext;		
	}
	return true;
}
bool GetProcessByID(DWORD ProcessID,PSYSER_PROCESS pProcess)
{
	SYSER_PROCESS Process;
	bool bOK;
	bOK = GetFirstProcess(&Process);
	while(bOK)
	{
		if(Process.UniqueProcessId==ProcessID)
		{
			memcpy(pProcess,&Process,sizeof(SYSER_PROCESS));
			return true;
		}
		bOK=GetNextProcess(&Process);
	}
	return false;
}
bool GetProcessByName(char* Name,PSYSER_PROCESS pProcess)
{
	SYSER_PROCESS Process;
	bool bOK;
	bOK = GetFirstProcess(&Process);
	while(bOK)
	{
		if(TStrICmp(Name,Process.ImageFileName)==0)		
		{
			memcpy(pProcess,&Process,sizeof(SYSER_PROCESS));
			return true;
		}
		bOK=GetNextProcess(&Process);
	}
	return false;
}

bool GetProcessByThreadID(DWORD ThreadID,PSYSER_PROCESS pProcess)
{
	SYSER_PROCESS Process;
	SYSER_THREAD Thread;
	bool bOK,bOK1;
	bOK = GetFirstProcess(&Process);
	while(bOK)
	{						
		memset(&Thread,0,sizeof(Thread));
		bOK1 = GetThreadInfoByETHREAD((DWORD)Process.ThreadHead,&Thread);
		while(bOK1)
		{
			if(ThreadID==Thread.ThreadID)
			{
				memcpy(pProcess,&Process,sizeof(Process));
				return true;
			}
			bOK1=GetNextThread(&Thread);
		}
		bOK = GetNextProcess(&Process);
	}
	return false;
}

bool GetProcessByETHREAD(DWORD EThread,PSYSER_PROCESS pProcess)
{
	SYSER_PROCESS Process;
	SYSER_THREAD Thread;
	bool bOK,bOK1;
	bOK = GetFirstProcess(&Process);
	while(bOK)
	{						
		memset(&Thread,0,sizeof(Thread));
		bOK1 = GetThreadInfoByETHREAD((DWORD)Process.ThreadHead,&Thread);
		while(bOK1)
		{
			if(EThread==(DWORD)Thread.OSThread)
			{
				memcpy(pProcess,&Process,sizeof(Process));
				return true;
			}
			bOK1=GetNextThread(&Thread);
		}
		bOK = GetNextProcess(&Process);
	}
	return false;
}
bool GetCurrentProcessInfo(PSYSER_PROCESS pProcess)
{
	DWORD dwCurProc,dwCurThread;
	memset(pProcess,0,sizeof(*pProcess));
	if(GetCurrentProcessAndThread(&dwCurProc,&dwCurThread))
	{
		return GetProcessInfoByEPROCESS(dwCurProc,pProcess);
	}
	return false;	
}
bool GetCurrentThreadInfo(PSYSER_THREAD pThread)
{
	DWORD dwCurProc,dwCurThread;
	memset(pThread,0,sizeof(*pThread));
	if(GetCurrentProcessAndThread(&dwCurProc,&dwCurThread))
	{
		return GetThreadInfoByETHREAD(dwCurThread,pThread);
	}
	return false;	
}
bool GetProcessByEPROCESS(DWORD EProcess,PSYSER_PROCESS pProcess)
{
	SYSER_PROCESS Process;
	bool bOK;
	bOK = GetFirstProcess(&Process);
	while(bOK)
	{
		if((DWORD)Process.OSProcess == EProcess)
		{
			memcpy(pProcess,&Process,sizeof(SYSER_PROCESS));
			return true;
		}
		bOK=GetNextProcess(&Process);
	}
	return false;
}
#ifdef CODE_OS_NT_DRV
int thread_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	WCHAR Title[]=WSTR("TID   Krnl TEB  StackBtm  StkTop    StackPtr  User TEB  StartEIP State Process(Id)\n");
	SYSER_PROCESS pProcess;
	SYSER_THREAD pThread;
	WCHAR Name[17];
	bool bOK,bOK1;
	DWORD dwCount=0;
	DWORD dwCurThread,dwCurProcess;
	GetCurrentProcessAndThread(&dwCurProcess,&dwCurThread);
	if(argc==1)
	{
		OUTPUT(Title);
		bOK = GetFirstProcess(&pProcess);
		while(bOK)
		{				
			TStrCpyLimit(Name,pProcess.ImageFileName,16);			
			memset(&pThread,0,sizeof(pThread));
			bOK1 = GetThreadInfoByETHREAD((DWORD)pProcess.ThreadHead,&pThread);
			while(bOK1)
			{
				if(dwCurThread!=(DWORD)pThread.OSThread)
				{
					OUTPUT(WSTR("%04x  %08x  %08x  %08x  %08x  %08x  %08x %d     %s(%2x)\n"),pThread.ThreadID,
						pThread.OSThread,
						pThread.StackLimit,
						pThread.InitialStack,
						pThread.KernelStack,
						pThread.Teb,
						pThread.StartAddress,
						pThread.State,
						Name,pProcess.UniqueProcessId);
				}
				else
				{
					OUTPUT(WSTR("%<7>%04x  %08x  %08x  %08x  %08x  %08x  %08x %d     %s(%2x)\n"),pThread.ThreadID,
						pThread.OSThread,
						pThread.StackLimit,
						pThread.InitialStack,
						pThread.KernelStack,
						pThread.Teb,
						pThread.StartAddress,
						pThread.State,
						Name,pProcess.UniqueProcessId);
				}
				dwCount++;
				bOK1=GetNextThread(&pThread);
			}
			bOK = GetNextProcess(&pProcess);
		}
		if(dwCount)
			OUTPUT(WSTR("thread totals (%d)\n"),dwCount); 
		return 0;
	}
	
	argc--;
	int i;
	SYSER_VALUE_TYPE ValueType;
	DWORD dwValue;
	bool bTitle=false;
	CDbgProcess*pDbgProcess;
	WCHAR szBuffer[MAX_FN_LEN];
#ifdef CODE_OS_NT_DRV
	for(i=0;i<argc;i++)
	{		
		if(CALCEXP(argv[i+1],&dwValue)==FALSE)
		{
			
			pDbgProcess=pSyser->m_SysInfo.GetProcess(argv[i+1]);
			if(pDbgProcess)
			{
				dwValue=(DWORD)pDbgProcess->GetEPROCESS();
			}
			else
			{
				TStrCpyLimit(szBuffer,argv[i+1],MAX_FN_LEN);
				TStrCat(szBuffer,".exe");
				pDbgProcess=pSyser->m_SysInfo.GetProcess(szBuffer);
				if(pDbgProcess)
				{
					dwValue=(DWORD)pDbgProcess->GetEPROCESS();
				}
				else
					continue;
			}
			ValueType=VALUE_TYPE_PROCESS_PTR;
		}
		else
		{
			ValueType = GetValueType(dwValue);
			if(ValueType==VALUE_TYPE_UNKNOW || ValueType==VALUE_TYPE_HWND_ID || ValueType == VALUE_TYPE_HWND_PTR)
				continue;
		}

#endif		
		bOK=false;
		switch(ValueType)
		{
		case VALUE_TYPE_THREAD_PTR:
			bOK=GetThreadInfoByETHREAD(dwValue,&pThread);	
			if(bOK)
				bOK=GetProcessByEPROCESS(pThread.Process,&pProcess);
			break;
		case VALUE_TYPE_THREAD_ID:			
			bOK = GetThreadByID(dwValue,&pThread);	
			if(bOK)
				bOK=GetProcessByEPROCESS(pThread.Process,&pProcess);
			break;		
		case VALUE_TYPE_PROCESS_ID:
			bOK=GetProcessByID(dwValue,&pProcess);
			break;
		case VALUE_TYPE_PROCESS_PTR:
			bOK=GetProcessInfoByEPROCESS(dwValue,&pProcess);
			break;

		}
	
		if(bOK==false)
			continue;					
		if(bTitle==false)
		{
			bTitle=true;
			OUTPUT(Title);
		}
		TStrCpyLimit(Name,pProcess.ImageFileName,16);

		if(ValueType==VALUE_TYPE_THREAD_PTR || VALUE_TYPE_THREAD_ID==ValueType)
		{
			OUTPUT(WSTR("%04x  %08x  %08x  %08x  %08x  %08x  %08x %d     %s(%2x)\n"),pThread.ThreadID,
				pThread.OSThread,
				pThread.StackLimit,
				pThread.InitialStack,
				pThread.KernelStack,
				pThread.Teb,
				pThread.StartAddress,
				pThread.State,
				Name,pProcess.UniqueProcessId);	
			dwCount++;
			
		}
		else
		{
			memset(&pThread,0,sizeof(pThread));
			bOK1 = GetThreadInfoByETHREAD((DWORD)pProcess.ThreadHead,&pThread);
			while(bOK1)
			{
				OUTPUT(WSTR("%04x  %08x  %08x  %08x  %08x  %08x  %08x %d     %s(%2x)\n"),pThread.ThreadID,
					pThread.OSThread,
					pThread.StackLimit,
					pThread.InitialStack,
					pThread.KernelStack,
					pThread.Teb,
					pThread.StartAddress,
					pThread.State,
					Name,pProcess.UniqueProcessId);
				bOK1=GetNextThread(&pThread);
				dwCount++; 
			}
		}
	}
	if(dwCount)
		OUTPUT(WSTR("thread totals (%d)\n"),dwCount); 
	return 0;
}

#endif

SYSER_VALUE_TYPE FindHwndType(DWORD dwHwnd,DWORD Value)
{
	SYSER_HWND_INFO HwndInfo;
	SYSER_VALUE_TYPE Type;
	while(dwHwnd && GetHwndInfoByWndStruct(*(void**)&dwHwnd,&HwndInfo))
	{
		if(Value==dwHwnd)
			return VALUE_TYPE_HWND_PTR;
		if(Value==HwndInfo.hWnd)
			return VALUE_TYPE_HWND_ID;
		Type = FindHwndType((DWORD)HwndInfo.ChildHwnd,Value);
		if(Type==VALUE_TYPE_HWND_PTR || Type==VALUE_TYPE_HWND_ID)
			return Type;			
		dwHwnd=(DWORD)HwndInfo.NextHwnd;
	}
	return VALUE_TYPE_UNKNOW;
}
SYSER_VALUE_TYPE IsHwndValueType(DWORD Value)
{
	BOOL bOK;
	gpSyser->InitOSHwndRoot();	
	SYSER_HWND_INFO HwndInfo;
#ifdef CODE_OS_NT_DRV 
	CDbgProcess*pDbgProcess;
	pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("csrss"));
	if(pDbgProcess==NULL)
	{
		pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("explorer"));
		if(pDbgProcess==NULL)
			return VALUE_TYPE_UNKNOW;
	}
	gpSyser->MapToProcess(pDbgProcess);
#endif
	DWORD dwHwnd=gpSyser->m_OSHwndRoot;
	return FindHwndType(dwHwnd,Value);

}
SYSER_VALUE_TYPE GetValueType(DWORD Value)
{
	SYSER_PROCESS pProcess;
	SYSER_THREAD pThread;
	BOOL bOK,bOK1;
	bOK = GetFirstProcess(&pProcess);
	while(bOK)
	{						
		if(Value==(DWORD)pProcess.OSProcess)
			return VALUE_TYPE_PROCESS_PTR;
		if(Value==(DWORD)pProcess.UniqueProcessId)
			return VALUE_TYPE_PROCESS_ID;
		memset(&pThread,0,sizeof(pThread));
		bOK1 = GetThreadInfoByETHREAD((DWORD)pProcess.ThreadHead,&pThread);
		while(bOK1)
		{
			if(Value==(DWORD)pThread.ThreadID)
				return VALUE_TYPE_THREAD_ID;
			if(Value==(DWORD)pThread.OSThread)
				return VALUE_TYPE_THREAD_PTR;
			bOK1=GetNextThread(&pThread);
		}
		bOK = GetNextProcess(&pProcess);
	}
	return IsHwndValueType(Value);
}


DWORD  GetEProcessPointer(WCHAR* args)
{
#ifdef CODE_OS_NT_DRV
	SYSER_PROCESS pProcess;
	SYSER_THREAD pThread;
	SYSER_VALUE_TYPE ValueType;
	DWORD dwValue=0;
	bool bOK;
	CDbgProcess*pDbgProcess;
	WCHAR szBuffer[MAX_FN_LEN];

	if(args==NULL)
		return 0;

	if(CALCEXP(args,&dwValue)==FALSE)
	{
		pDbgProcess=gpSyser->m_SysInfo.GetProcess(args);
		if(pDbgProcess)
		{
			dwValue=(DWORD)pDbgProcess->GetEPROCESS();
		}
		else
		{
			TStrCpyLimit(szBuffer,args,MAX_FN_LEN);
			TStrCat(szBuffer,".exe");
			pDbgProcess=gpSyser->m_SysInfo.GetProcess(szBuffer);
			if(pDbgProcess)
			{
				dwValue=(DWORD)pDbgProcess->GetEPROCESS();
			}
		}
		return dwValue;
	}
	else
	{
		ValueType = GetValueType(dwValue);
		if(ValueType==VALUE_TYPE_UNKNOW || ValueType==VALUE_TYPE_HWND_ID || ValueType == VALUE_TYPE_HWND_PTR)
			return 0;
	}

	
	bOK=false;
	switch(ValueType)
	{
	case VALUE_TYPE_THREAD_PTR:
		bOK=GetThreadInfoByETHREAD(dwValue,&pThread);	
		if(bOK)
			bOK=GetProcessByEPROCESS(pThread.Process,&pProcess);
		break;
	case VALUE_TYPE_THREAD_ID:			
		bOK = GetThreadByID(dwValue,&pThread);	
		if(bOK)
			bOK=GetProcessByEPROCESS(pThread.Process,&pProcess);
		break;		
	case VALUE_TYPE_PROCESS_ID:
		bOK=GetProcessByID(dwValue,&pProcess);
		break;
	case VALUE_TYPE_PROCESS_PTR:
		bOK=GetProcessInfoByEPROCESS(dwValue,&pProcess);
		break;
	}
	return *(DWORD*)&pProcess.OSProcess;
#endif	
	return 0;
}