#include "StdAfx.h"
#include "Syser.h"
#include "Dump.h"

bool MakePE(CDbgModule*pDbgModule,BYTE*DumpBuffer,int Size)
{
	int n;
	DWORD MaxSize;
	BYTE* SectionBuffer;
	CMemPEFile MemPEFile;
	CImageFile NewPEFile;
	
	NewPEFile.Create(Size,DumpBuffer);

	if(MemPEFile.Open(pDbgModule->m_ModuleBase,0,CDebugger::ReadMemory,gpSyser->m_pDebugger)==false)
		return false;

	MemPEFile.m_ImageBase = pDbgModule->m_ModuleBase;
	MaxSize = 0;
	for(n=0;n<=MemPEFile.m_SectCount;n++)
	{
		if(MemPEFile.m_Section[n].VirtualSize>MemPEFile.m_ImageSize || MemPEFile.m_Section[n].VirtualAddress>MemPEFile.m_ImageSize)
			return false;
		if(MemPEFile.m_Section[n].VirtualSize > MaxSize)
			MaxSize = MemPEFile.m_Section[n].VirtualSize;
	}
	SectionBuffer = new BYTE[MaxSize];
	__try
	{
		for(n=0;n<=MemPEFile.m_SectCount;n++)
		{
			gpSyser->m_pDebugger->ReadMemory(MemPEFile.m_Section[n].VirtualAddress + MemPEFile.m_ImageBase,SectionBuffer,MemPEFile.m_Section[n].VirtualSize);
			NewPEFile.WriteFile(MemPEFile.m_Section[n].VirtualAddress,SectionBuffer,MemPEFile.m_Section[n].VirtualSize);
			MemPEFile.m_Section[n].PointerToRawData	= MemPEFile.m_Section[n].VirtualAddress;
			MemPEFile.m_Section[n].SizeOfRawData = MemPEFile.m_Section[n].VirtualSize;
		}
		n = MemPEFile.GetLastMemAddrSection();
		MemPEFile.m_PEHead.SizeOfImage = ALIGN_SIZE(MemPEFile.m_Section[n].VirtualAddress + MemPEFile.m_Section[n].VirtualSize,MP_SIZE);
		/////////////////////////////////////////////////////////////////////
		//»ØÐ´PEÍ·
		/////////////////////////////////////////////////////////////////////
		int SectionOff=MemPEFile.m_PEHead.SizeOfOptionalHeader+MemPEFile.m_PEOff+0x18;

		NewPEFile.WriteFile(MemPEFile.m_PEOff,&MemPEFile.m_PEHead,sizeof(PE_HEAD));
		NewPEFile.WriteFile(SectionOff,&MemPEFile.m_Section[1],sizeof(PE_SECTION)*MemPEFile.m_SectCount);
	}
	__except(1)
	{
		OUTPUT(WSTR("Error : Fail to dump !\n"));
	};
	NewPEFile.Close();
	delete SectionBuffer;
	return true;
}

int dump_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	char szBuffer[MAX_FN_LEN];
	WCHAR wszBuffer[MAX_FN_LEN];
	ULPOS Address,RDAddr;
	int Size,RDSize;
// 	if(gpSyser->m_SysInfo.m_bSNPass && gpSyser->m_SysInfo.m_SNType==SN_STUDENT)
// 	{
// 		OUTPUT(WSTR("Student version limited\n"));
// 		return -1;
// 	}
	if(argc<3)
	{
		OUTPUT_COMMAND_USAGE;
		return 1;
	}
	if(CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return 1;
	}
	if(CALCEXP(argv[2],(ULPOS*)&Size)==false || Size==0)
	{
		OUTPUT_INVALID_PARAM;
		return 1;
	}
	if(argc<4)
	{
		OUTPUT(WSTR("Use default filename\n"));
		TStrCpy(szBuffer,"\\??\\C:\\SyserDump.bin");
	}
	else
	{
		TStrCpy(szBuffer,"\\??\\");
		UnicodeToAnsi(argv[3],&szBuffer[4],MAX_FN_LEN-4);
	}
	if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE+Size))
	{
		OUTPUT(WSTR("Error : Not enough memory to dump this module ! Please enlarge syser heap size !\n"),argv[1]);
		return 1;
	}
	CSyserDumpList::IT Iter = gpSyser->m_DumpList.Append();
	Iter->DumpSize = Size;
	Iter->DumpData = (BYTE*)gpUserHeap[SYSER_MAIN_HEAP]->Allocate(Iter->DumpSize);
	if(Iter->DumpData==NULL)
	{
		OUTPUT(WSTR("Error : Not enough memory to dump this module ! Please enlarge syser heap size !\n"),argv[1]);
		gpSyser->m_DumpList.Remove(Iter);
		return 1;
	}
	Iter->DumpFileName = szBuffer;
	ZeroMemory(Iter->DumpData,Iter->DumpSize);
	RDAddr = Address;
	if(RDAddr%MP_SIZE)
	{
		RDSize = MP_SIZE-(RDAddr%MP_SIZE);
		MAX_LIMIT(RDSize,Size);
		gpSyser->m_pDebugger->ReadMemory(RDAddr,Iter->DumpData,RDSize);
		Size-=RDSize;
		RDAddr+=RDSize;
	}
	while(Size>MP_SIZE)
	{
		gpSyser->m_pDebugger->ReadMemory(RDAddr,&Iter->DumpData[RDAddr-Address],MP_SIZE);
		RDAddr+=MP_SIZE;
		Size-=MP_SIZE;
	}
	if(Size)
	{
		gpSyser->m_pDebugger->ReadMemory(RDAddr,&Iter->DumpData[RDAddr-Address],Size);
		Size=0;
	}
	OUTPUT(WSTR("Address %<5>0x%08X %<1> ----- %<5>0x%08X\n"),Address,Address+Iter->DumpSize);
	AnsiToUnicode(Iter->DumpFileName,wszBuffer,MAX_FN_LEN);
	OUTPUT(WSTR("%<5>0x%X %<1>byte(s) prepare to dump to RAW file %<F>%s\n"),Iter->DumpSize,wszBuffer);
	OUTPUT(WSTR("This file will be written after exiting syser !\n"));
	KeSetEvent(&gpSyser->m_WaitEvent,0,FALSE);
	return 0;
}

int makepe_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	char szBuffer[MAX_FN_LEN];
	WCHAR wszBuffer[MAX_FN_LEN];
// 	if(gpSyser->m_SysInfo.m_bSNPass && gpSyser->m_SysInfo.m_SNType==SN_STUDENT)
// 	{
// 		OUTPUT(WSTR("Student version limited\n"));
// 		return -1;
// 	}
	if(argc<2)
	{
		OUTPUT_COMMAND_USAGE;
		return 1;
	}
	if(argc<3)
	{
		OUTPUT(WSTR("Use default filename\n"));
		TStrCpy(szBuffer,"\\??\\C:\\SyserDump.bin");
	}
	else
	{
		TStrCpy(szBuffer,"\\??\\");
		UnicodeToAnsi(argv[2],&szBuffer[4],MAX_FN_LEN-4);
	}
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->GetModule(argv[1]);
	if(pDbgModule==NULL)
	{
		OUTPUT(WSTR("Error : Couldn't find module %s\n"),argv[1]);
		return 1;
	}
	if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE+pDbgModule->m_ModuleSize))
	{
		OUTPUT(WSTR("Error : Not enough memory to dump this module ! Please enlarge syser heap size !\n"),argv[1]);
		return 1;
	}
	CSyserDumpList::IT Iter = gpSyser->m_DumpList.Append();
	Iter->DumpSize = pDbgModule->m_ModuleSize;
	Iter->DumpData = (BYTE*)gpUserHeap[SYSER_MAIN_HEAP]->Allocate(Iter->DumpSize);
	if(Iter->DumpData==NULL)
	{
		OUTPUT(WSTR("Error : Not enough memory to dump this module ! Please enlarge syser heap size !\n"),argv[1]);
		return 1;
	}
	Iter->DumpFileName = szBuffer;
	ZeroMemory(Iter->DumpData,Iter->DumpSize);
	MakePE(pDbgModule,Iter->DumpData,Iter->DumpSize);
	AnsiToUnicode(pDbgModule->m_ModuleName,wszBuffer,MAX_FN_LEN);
	OUTPUT(WSTR("Module Name %<F>%s %<1>Module Base %<5>0x%08X %<1>Module Size %<5>0x%08X\n"),wszBuffer,pDbgModule->m_ModuleBase,pDbgModule->m_ModuleSize);
	AnsiToUnicode(Iter->DumpFileName,wszBuffer,MAX_FN_LEN);
	OUTPUT(WSTR("%<5>0x%X %<1>byte(s) prepare to dump to RAW file %<F>%s\n"),Iter->DumpSize,wszBuffer);
	OUTPUT(WSTR("This file will be written after exiting syser !\n"));
	KeSetEvent(&gpSyser->m_WaitEvent,0,FALSE);
	return 0;
}
