#include "StdAfx.h"
#include "SysInfo.h"
#include "Syser.h"
#include "X86Optr.h"
#include "NTUtility.h"
extern DWORD 	dwgErrorCode;
#define FREE_DAY_COUNT				7

PCSTR CSysInfo::m_gNtoskrnlName[]={"ntoskrnl.exe","ntkrnlpa.exe","ntkrnlmp.exe","ntkrpamp.exe",NULL};

bool ConvertFileNameByMacro(CHAR*szFileName,const CHAR*szMacro,const CHAR*szMacroStr)
{
	int Len;
	CHAR szBuffer[MAX_FN_LEN];
	Len = TStrLen(szMacro);
	if(TStrNICmp(szFileName,szMacro,Len)==0)
	{
		TStrCpy(szBuffer,&szFileName[Len]);
		TStrCpy(szFileName,szMacroStr);
		TStrCat(szFileName,szBuffer);
		return true;
	}
	return false;
}

MODULE_ID GetModuleID(ULPOS ImageBase,ULSIZE ImageSize)
{
	PE_HEAD*pHead;
	ULPOS Offset;
	__try
	{
		if(_GET_WORD(ImageBase)!=0x4D5A && _GET_WORD(ImageBase)!=0x5A4D)
			return 0;
		Offset = GET_DWORD(ImageBase,0x3C);
		if(ImageSize && Offset>=ImageSize-sizeof(PE_HEAD))
			return 0;
		pHead = (PE_HEAD*)(ImageBase+Offset);
		if(pHead->Signature!=0x4550)
			return 0;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		::DbgPrint("Syser : GetModuleID fail. base=%08x size=%08x\n",ImageBase,ImageSize);
		return 0;
	}
	return MAKE_MODULE_ID(pHead->CheckSum ,pHead->TimeDateStamp);
}

MODULE_ID GetModuleIDAndImageSize(ULPOS ImageBase,ULSIZE& ImageSize)
{
	PE_HEAD*pHead;
	ULPOS Offset;
	__try
	{
		if(_GET_WORD(ImageBase)!=0x4D5A && _GET_WORD(ImageBase)!=0x5A4D)
			return 0;
		Offset = GET_DWORD(ImageBase,0x3C);
		if(ImageSize && Offset>=ImageSize-sizeof(PE_HEAD))
			return 0;
		pHead = (PE_HEAD*)(ImageBase+Offset);
		if(pHead->Signature!=0x4550)
			return 0;
		ImageSize = pHead->SizeOfImage;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		::DbgPrint("Syser : GetModuleID fail. base=%08x size=%08x\n",ImageBase,ImageSize);
		return 0;
	}
	return MAKE_MODULE_ID(pHead->CheckSum ,pHead->TimeDateStamp);
}

CSysInfo::CSysInfo()
{
	DWORD CR3;
	PEPROCESS curproc;
	m_pZwQueryVirtualMemory=NULL;
	m_SyserBase = m_SyserHighBase = 0;
	m_win32kImageBase = 0;
	m_win32kImageSize = 0;
	m_OSKernlBase = 0;
	m_W32ServiceTableAddress=0;
	m_W32ServiceTable=NULL;
	m_W32ServiceArgv=NULL;
	m_W32ServiceNumbers=0;
	m_OSMajorVersion=0;
	m_OSMinorVersion=0;
	m_OSBuildNumber=0;
	m_OSCheckBuild=FALSE;
	m_HidP_TranslateUsageAndPagesToI8042ScanCodes=0;
	m_OrgWindowsServiceTable=NULL;
	m_OrgWindowsServiceArgTable=NULL;
	m_LoCount=0;
	m_HiCount=0;
	m_OSKernelName[0]=0;
	m_SystemStartAddr = (DWORD)MM_SYSTEM_RANGE_START;
	m_OrgWindowIDT=NULL;
    curproc = PsGetCurrentProcess();
	m_ProcNameOff = 0;
    for(int i=0;i<0x400;i++)
	{
        if(TStrICmp("System",(char*)curproc+i)==0)
		{
			m_ProcNameOff = i;
			break;
		}
    }
	CR3 = SyserGetCR3Reg();
	m_ProcCR3dwOff=0;
    for(int i=0;i<0x100;i++)
	{
		if(((DWORD*)curproc)[i] ==CR3)
		{
			m_ProcCR3dwOff = i;
			break;
		}
	}
	m_PEBOffsetOfEPROCESS=0;
	GetPEBOffset(&m_PEBOffsetOfEPROCESS);
	GetSystemRoot();
	GetPathSymbolLinker();
	TStrCpy(m_szSystem32,m_szSystemRoot);
	TStrCat(m_szSystem32,WSTR("system32\\"));
	TStrCpy(m_szSystem32Drivers,m_szSystem32);
	TStrCat(m_szSystem32Drivers,WSTR("drivers\\"));
	UNICODE_STRING UnicodeName;
	RtlInitUnicodeString(&UnicodeName,WSTR("MmUnmapViewOfSection"));
	m_MmUnmapViewOfSection=(DWORD)MmGetSystemRoutineAddress(&UnicodeName);
	PsGetVersion(&m_OSMajorVersion,&m_OSMinorVersion,&m_OSBuildNumber,NULL);
	UnicodeToAnsi(m_szSystemRoot,m_szSystemRootA,sizeof(m_szSystemRootA));
	UnicodeToAnsi(m_szSystem32,m_szSystem32A,sizeof(m_szSystem32A));
	UnicodeToAnsi(m_szSystem32Drivers,m_szSystem32DriversA,sizeof(m_szSystem32DriversA));
	m_bEvlVer = m_bSNPass = false;
	//m_SNType = SN_ERROR;

}

CSysInfo::~CSysInfo()
{
	
}

bool CSysInfo::GetSystemRoot()
{
	NTSTATUS Status;
	UNICODE_STRING UniSystemRootDir;
	RTL_QUERY_REGISTRY_TABLE RegTable[2];
	int Len;
	ZeroMemory(RegTable,sizeof(RegTable));
	ZeroMemory(m_szSystemRoot,sizeof(m_szSystemRoot));
	TStrCpy(m_szSystemRoot,WSTR("\\??\\"));
	UniSystemRootDir.Length=0;
	UniSystemRootDir.MaximumLength=sizeof(m_szSystemRoot);
	UniSystemRootDir.Buffer=&m_szSystemRoot[TStrLen(m_szSystemRoot)];
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("SystemRoot");
	RegTable[0].EntryContext = &UniSystemRootDir;
	Status = RtlQueryRegistryValues(RTL_REGISTRY_WINDOWS_NT,WSTR(""),RegTable,NULL,NULL);
	if(NT_SUCCESS(Status))
	{
		Len = TStrLen(m_szSystemRoot);
		if(m_szSystemRoot[Len-1]!='\\')
		{
			m_szSystemRoot[Len]='\\';
			m_szSystemRoot[Len+1]=0;
		}
		TStrCpy(m_szSystemRootMarco,&m_szSystemRoot[6]);
		return true;
	}
	ZeroMemory(RegTable,sizeof(RegTable));
	ZeroMemory(m_szSystemRoot,sizeof(m_szSystemRoot));
	TStrCpy(m_szSystemRoot,WSTR("\\??\\"));
	UniSystemRootDir.Length=0;
	UniSystemRootDir.MaximumLength=sizeof(m_szSystemRoot);
	UniSystemRootDir.Buffer=&m_szSystemRoot[TStrLen(m_szSystemRoot)];
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("SystemRoot");
	RegTable[0].EntryContext = &UniSystemRootDir;
	Status = RtlQueryRegistryValues(RTL_REGISTRY_SERVICES,WSTR("Syser"),RegTable,NULL,NULL);
	if(NT_SUCCESS(Status))
	{
		Len = TStrLen(m_szSystemRoot);
		if(m_szSystemRoot[Len-1]!='\\')
		{
			m_szSystemRoot[Len]='\\';
			m_szSystemRoot[Len+1]=0;
		}
	}
	else
		TStrCpy(m_szSystemRoot,WSTR("\\??\\C:\\WINDOWS\\"));
	TStrCpy(m_szSystemRootMarco,&m_szSystemRoot[6]);
	return true;
}

bool CSysInfo::ValidateSN()
{
	return true;
// 	WCHAR szBuffer[256],szLicName[128];
// #ifndef __DEMO__VERSION__
// 	m_SNType = ValidateSerialNumber(m_LicNameStr,m_SNStr);
// 	if(m_SNType!=SN_ERROR && m_SNType!=SN_CHARGEBACK)
// 	{
// 		TStrCpy(szLicName,(PCSTR)m_LicNameStr);
// 		if(m_SNType == SN_STUDENT)
// 			TStrCpy(szBuffer,WSTR("Tztfs!Efcvhhfs!Tuvefou!Wfstjpo!;!Mjdfotf!up!&t"));//Syser Debugger Student Version : License to %s
// 		else if(m_SNType == SN_PERSONAL)
// 			TStrCpy(szBuffer,WSTR("Tztfs!Efcvhhfs!Qfstpobm!Wfstjpo!;!Mjdfotf!up!&t"));//Syser Debugger Personal Version : License to %s
// 		else if(m_SNType == SN_ENTERPRISE)
// 			TStrCpy(szBuffer,WSTR("Tztfs!Efcvhhfs!Foufsqsjtf!Wfstjpo!;!Mjdfotf!up!&t"));//Syser Debugger Enterprise Version : License to %s
// 		else
// 			*szBuffer=0;
// 		for(int n=0;szBuffer[n];n++)
// 			szBuffer[n]--;
// 		m_LicTip.Format(szBuffer,szLicName);
// 		m_bEvlVer = false;
// 		return true;
// 	}
// #endif
// 	if(IsValidInstTime(m_InstallTime.QuadPart)==false || m_CurrentTime.QuadPart==0 || m_SNType==SN_CHARGEBACK)
// 		goto InvalidLic;
// 	LONGLONG dTime = m_CurrentTime.QuadPart - m_InstallTime.QuadPart;
// 	dTime/=10000000;
// 	dTime/=3600*24;
// 	if(dTime>=0 && dTime<FREE_DAY_COUNT)
// 	{
// 		TStrCpy(szBuffer,WSTR("Fwbmvbujpo!wfstjpo!&e!ebzt!mfgu"));//WSTR("Evaluation version %d days left")
// 		for(int n=0;szBuffer[n];n++)
// 			szBuffer[n]--;
// 		m_LicTip.Format(szBuffer,FREE_DAY_COUNT-(int)dTime);
// 		m_bEvlVer = true;
// 		return false;
// 	}
// InvalidLic:
// 	TStrCpy(szBuffer,WSTR("Jowbmje!Mjdfotf"));//WSTR("Invalid License")
// 	for(int n=0;szBuffer[n];n++)
// 		szBuffer[n]--;
// 	m_LicTip = szBuffer;
// 	m_bEvlVer = false;
// 	return false;
}

void CSysInfo::UpdateHostSN()
{
	DWORD VerType;
	CHAR szBufferA[128];
	WCHAR szBuffer[128],StrBuffer[128];

	//读SN///////////////////////////////////////////////
	TStrCpy(StrBuffer,WSTR("TO"));//SN
	for(int n=0;StrBuffer[n];n++)
		StrBuffer[n]--;

	*szBuffer=0;
	gpSyserCfg->ReadStringValue(StrBuffer,szBuffer);
	TStrCpy(szBufferA,szBuffer);
	m_SNStr = szBufferA;

	//读LicName/////////////////////////////////////////
	TStrCpy(StrBuffer,WSTR("MjdObnf"));//LicName
	for(int n=0;StrBuffer[n];n++)
		StrBuffer[n]--;

	*szBuffer=0;
	gpSyserCfg->ReadStringValue(StrBuffer,szBuffer);
	TStrCpy(szBufferA,szBuffer);
	m_LicNameStr = szBufferA;

	//读InstTime////////////////////////////////////////
	TStrCpy(StrBuffer,WSTR("JotuUjnf"));//InstTime
	for(int n=0;StrBuffer[n];n++)
		StrBuffer[n]--;

	m_InstallTime.QuadPart = m_CurrentTime.QuadPart = 0;
	gpSyserCfg->ReadQwordValue(StrBuffer,(QWORD*)&m_InstallTime.QuadPart);
	KeQuerySystemTime(&m_CurrentTime);

	m_bSNPass = ValidateSN();
#ifndef __DEMO__VERSION__
	//::DbgPrint("Syser : CheckSN ok.............\n"); 
	if(m_bSNPass==false)
	{
		WCHAR szBuffer[256],szLicName[128];
		//SYSER_SN_TYPE type;
		m_bSNPass=gpSyser->CheckSN(m_SNStr,m_LicNameStr);
		if(m_bSNPass)
		{
			//m_SNType=type;
			TStrCpy(szLicName,(PCSTR)m_LicNameStr);
// 			if(m_SNType == SN_STUDENT)
// 				TStrCpy(szBuffer,WSTR("Tztfs!Efcvhhfs!Tuvefou!Wfstjpo!;!Mjdfotf!up!&t"));//Syser Debugger Student Version : License to %s
// 			else if(m_SNType == SN_PERSONAL)
// 				TStrCpy(szBuffer,WSTR("Tztfs!Efcvhhfs!Qfstpobm!Wfstjpo!;!Mjdfotf!up!&t"));//Syser Debugger Personal Version : License to %s
// 			else if(m_SNType == SN_ENTERPRISE)
				TStrCpy(szBuffer,WSTR("Tztfs!Efcvhhfs!Foufsqsjtf!Wfstjpo!;!Mjdfotf!up!&t"));//Syser Debugger Enterprise Version : License to %s
// 			else
// 				*szBuffer=0;
			for(int n=0;szBuffer[n];n++)
				szBuffer[n]--;
			m_LicTip.Format(szBuffer,szLicName);
			m_bEvlVer = false;
			//::DbgPrint("Syser : CheckSN ok\n");
		}
	}
#endif
	TStrCpy(StrBuffer,WSTR("WfsUzqf"));//VerType
	for(int n=0;StrBuffer[n];n++)
		StrBuffer[n]--;
	//VerType = SN_ERROR;
	gpSyserCfg->ReadDwordValue(StrBuffer,&VerType);
	if(VerType!=0)
	{
		if(m_bSNPass==false)
		{
			VerType = 0;
			gpSyserCfg->WriteDwordValue(StrBuffer,VerType);
		}
		else if(VerType!=(DWORD)0)
		{
			VerType = (DWORD)1;
			gpSyserCfg->WriteDwordValue(StrBuffer,VerType);
		}
	}
	else
	{
		if(m_bSNPass)
		{
			VerType = (DWORD)1;
			gpSyserCfg->WriteDwordValue(StrBuffer,VerType);
		}
	}
}

void CSysInfo::GetSystemInformation()
{
	CDbgModule*pModule;
	char szFileName[MAX_FN_LEN];
	m_win32kImageBase = 0;
	m_win32kImageSize = 0;
	pModule = gpSyser->m_pSysDebugger->GetModule("win32k.sys");
	if(pModule)
	{
		m_win32kImageBase = pModule->m_ModuleBase;
		m_win32kImageSize = pModule->m_ModuleSize;
	}
	pModule = gpSyser->m_pSysDebugger->GetModule("hidparse.sys");
	if(pModule)
	{
		CMemPEFile MemPEFile;
		if(MemPEFile.Open(pModule->m_ModuleBase,PE_OPEN_NO_IMPORT,CImageFile::StaticReadRealMemory,NULL))
		{
			m_HidP_TranslateUsageAndPagesToI8042ScanCodes = MemPEFile.GetExportFunc("HidP_TranslateUsageAndPagesToI8042ScanCodes");
			::DbgPrint("Syser : Found HidP_TranslateUsageAndPagesToI8042ScanCodes %08X!\n",m_HidP_TranslateUsageAndPagesToI8042ScanCodes);	
			MemPEFile.Close();
		}
	}
}

bool CSysInfo::FindWin32KServiceSymName()
{
	CPEFile PEFile;
	CHAR szFileName[MAX_FN_LEN];
	int n;
	ULSIZE ReadLen;
	BYTE CodeBuffer[MAX_INSTR_LEN];
	DWORD ServiceNum;
	TNtcallNameIDMap::IT Iter;
	TStrCpy(szFileName,m_szSystem32A);
	TStrCat(szFileName,"user32.dll");
	PEFile.m_OpenMode|=PE_OPEN_NO_IMPORT;
	if(PEFile.Open(szFileName)==false)
		return false;
	for(n=0;n<PEFile.m_ExportFuncCount;n++)
	{		
		ReadLen = PEFile.ReadImageMemory(PEFile.m_ExportFunc[n].Address,CodeBuffer,sizeof(CodeBuffer));
		if(ReadLen!=sizeof(CodeBuffer))continue;
		if((CodeBuffer[0]==0xb8&&CodeBuffer[5]==0xba && CodeBuffer[0xa]==0xff && CodeBuffer[0xb]==0x12)//xp			
			)
		{
			ServiceNum = *(DWORD*)&CodeBuffer[1];
			Iter = m_Win32kNtcallMap.InsertUnique(ServiceNum,PEFile.m_ExportFunc[n].FuncName);
			if(Iter==m_Win32kNtcallMap.End())continue;
		}		
	}
	PEFile.Close();

	TStrCpy(szFileName,m_szSystem32A);
	TStrCat(szFileName,"gdi32.dll");
	PEFile.m_OpenMode|=PE_OPEN_NO_IMPORT;
	if(PEFile.Open(szFileName)==false)
		return false;
	for(n=0;n<PEFile.m_ExportFuncCount;n++)
	{		
		ReadLen = PEFile.ReadImageMemory(PEFile.m_ExportFunc[n].Address,CodeBuffer,sizeof(CodeBuffer));
		if(ReadLen!=sizeof(CodeBuffer))continue;
		if((CodeBuffer[0]==0xb8&&CodeBuffer[5]==0xba && CodeBuffer[0xa]==0xff && CodeBuffer[0xb]==0x12)//xp			
			)
		{
			ServiceNum = *(DWORD*)&CodeBuffer[1];
			Iter = m_Win32kNtcallMap.InsertUnique(ServiceNum,PEFile.m_ExportFunc[n].FuncName);
			if(Iter==m_Win32kNtcallMap.End())continue;
		}		
	}
	PEFile.Close();
	return true;
}

bool CSysInfo::GetWin32KServiceTable()
{
	CPEFile PEFile;
	CHAR szFileName[MAX_FN_LEN];
	DWORD CodeSectionVirtualAddress,CodeSectionVirtualSize;
	DWORD DataSectionInx=0,i,FilePos,ReadWriteLen,j;
	DWORD* pWin32ServiceTable=NULL;
	DWORD dwServiceNumbers=0;
	if(m_win32kImageBase==0)
		return false;
	bool bFindServiceTable=false,bFindText=false,bFindData=false,bOK,bFindINIT=false;
	TStrCpy(szFileName,m_szSystem32A);
	TStrCat(szFileName,"win32k.sys");
	PEFile.m_OpenMode|=PE_OPEN_NO_IMPORT;
	if(PEFile.Open(szFileName)==false)
		return false;
	for(i = 1;i<=(DWORD)PEFile.m_SectCount;i++)
	{
		if(TStrNICmp(PEFile.m_Section[i].Name,".data",5)==0)
		{
			DataSectionInx=i;
			bFindData=true;
		}
		else
		{
			if(TStrNICmp(PEFile.m_Section[i].Name,".text",5)==0)
			{
				CodeSectionVirtualAddress=PEFile.m_Section[i].VirtualAddress+PEFile.m_PEHead.ImageBase;
				CodeSectionVirtualSize=PEFile.m_Section[i].VirtualSize;
				bFindText=true;
			}
			else
			{
				if(TStrNICmp(PEFile.m_Section[i].Name,"INIT",4)==0)
				{
					bFindINIT=true;
				}
			}
		}
	}
	if(bFindData==true&&bFindText==true)
	{
		pWin32ServiceTable = new DWORD[0x1400];
		if(pWin32ServiceTable!=NULL)
		{
			FilePos=MIN(PEFile.m_Section[DataSectionInx].VirtualSize,PEFile.m_Section[DataSectionInx].SizeOfRawData);
			ReadWriteLen = FilePos > sizeof(DWORD)*0x1400 ? sizeof(DWORD)*0x1400 : FilePos;
			if(PEFile.MapToFile(PEFile.m_Section[DataSectionInx].VirtualAddress,&FilePos,false))
			{
				if(PEFile.ReadFile(FilePos,pWin32ServiceTable,ReadWriteLen))
				{
					for(i = 0; i < ReadWriteLen/sizeof(DWORD);i++)
					{
						if(pWin32ServiceTable[i]<CodeSectionVirtualAddress || pWin32ServiceTable[i]>=CodeSectionVirtualAddress+CodeSectionVirtualSize)
							break;
					}
					if(i<0x100 || i >=0x1000)
					{
						bFindServiceTable=false;
					}
					else
					{
						bFindServiceTable=true;
						dwServiceNumbers=i;
					}
				}
			}
			if(bFindServiceTable)
			{
				m_W32ServiceTable=new DWORD[dwServiceNumbers+1];
				if(m_W32ServiceTable)
				{
					memset(m_W32ServiceTable,0,sizeof(DWORD)*(dwServiceNumbers+1));
					memcpy(m_W32ServiceTable,pWin32ServiceTable,sizeof(DWORD)*dwServiceNumbers);
				}
				m_W32ServiceArgv = new BYTE[dwServiceNumbers+1];
				if(m_W32ServiceArgv)
				{
					memset(m_W32ServiceArgv,0,sizeof(BYTE)*(dwServiceNumbers+1));
					memcpy(m_W32ServiceArgv,&pWin32ServiceTable[dwServiceNumbers],sizeof(BYTE)*dwServiceNumbers);
				}
				if(m_W32ServiceTable&&m_W32ServiceArgv)
				{
					m_W32ServiceNumbers=dwServiceNumbers;
					m_W32ServiceTableAddress = PEFile.m_Section[DataSectionInx].VirtualAddress;
				}
			}
			delete []pWin32ServiceTable;
		}	
	}
	if(bFindServiceTable)
	{
		if(m_win32kImageBase&&m_W32ServiceTableAddress)
		{
			m_W32ServiceTableAddress+=m_win32kImageBase;
			if(m_W32ServiceTable)
			{
				if(m_win32kImageBase!=PEFile.m_ImageBase)
				{
					DWORD Delta=m_win32kImageBase-PEFile.m_ImageBase;
					for(DWORD i=0;i<m_W32ServiceNumbers;i++)
					{
						m_W32ServiceTable[i]+=Delta;
					}
				}
			}
		}		
	}
	PEFile.Close();
	return bFindServiceTable;
}

void CSysInfo::OutputEnv()
{
	OUTPUT(WSTR("Syser : SystemRoot = %s\n"),m_szSystemRoot);
	OUTPUT(WSTR("Syser : Win32 Service Table = 0x%08X\n"),m_W32ServiceTable);
	if(gpSysBootDevEx)
		OUTPUT(WSTR("Syser : SyserBoot Device Found ! DDraw hook is availabe !\n"));
	if(gpSysLangDevEx)
		OUTPUT(WSTR("Syser : SyserLanguage Device Found ! Safe Unicode Function is availabe !\n"));
}

bool CSysInfo::Init()
{
	CDbgProcess*pProcess;
	DWORD Size,PID;
	PSYSTEM_MODULE pModule;
	NTSTATUS ntstatus=0x12345678;
	void*Buffer=NULL;
	Size=sizeof(SYSTEM_MODULE)*0x100;
	ULONG ReturnLength=0;
	GetOSKernelName();
	NtcallInit();
	Size=sizeof(SYSTEM_PROCESS_INFORMATION)*0x100;
	Buffer = new BYTE[Size];
		dwgErrorCode=114;
	while(Buffer)
	{
		if(NT_SUCCESS(ZwQuerySystemInformation(SystemProcessInformation,Buffer,Size,NULL)))
			break;
		delete Buffer;
		Buffer=NULL;
		Size*=2;
		Buffer=new BYTE[Size];
		if(Buffer==NULL || Size>sizeof(SYSTEM_PROCESS_INFORMATION)*0x1000)
		{
			if(Buffer)
				delete Buffer;
			return false;
		}
	}
dwgErrorCode=115;
	ULONG Offset = 0;
	SYSTEM_PROCESS_INFORMATION*P=(SYSTEM_PROCESS_INFORMATION*)Buffer;
    do
    {
		P=(SYSTEM_PROCESS_INFORMATION*)((BYTE*)P+Offset);
		Offset = P->NextEntryOffset;
		PID = PTR_TO_NUM(P->UniqueProcessId);
		pProcess = InsertProcess(PID);
		if(pProcess==NULL)
		{
			::DbgPrint("Syser : Fail to InitProcessList !\n");
			delete Buffer;
			return false;
		}
    }while(Offset);
	dwgErrorCode=117;
    delete Buffer;
	gpSyser->m_pDebugger = GetProcess(WSTR("System"));
	gpSyser->m_pCsrssProcess = GetProcess(WSTR("csrss"));
	if(gpSyser->m_pDebugger)
	{
		gpSyser->m_pSysDebugger = gpSyser->m_pDebugger;
		gpSyser->MapToProcess(gpSyser->m_pDebugger);
		gpSyser->m_SyserUI.m_CodeDoc.Open(gpSyser->m_pDebugger->m_ProcName);
	}
	dwgErrorCode=118;
	if(gpSyser->m_pDebugger==NULL)
	{
		::DbgPrint("Syser : Cann't find SYSTEM Process!\n");
		return false;
	}
	LoadExpModList();
	dwgErrorCode=119;
	for(CProcMap::IT Iter = m_ProcMap.Begin();Iter!=m_ProcMap.End();Iter++)
	{
		if(GetDllList(&(*Iter))==false)
		{
			if(GetDllListNew(&(*Iter))==false)
			{
				::DbgPrint("Syser : %s ExGetDllList except...\n",(char*)Iter->m_ProcName);
			}
		}
	}
	dwgErrorCode=120;
	GetDriverList();
	dwgErrorCode=121;
	gpSyser->m_SyserUI.SetPublicSymbolModuleBase();
	dwgErrorCode=122;
	GetSystemInformation();	
	dwgErrorCode=123;
	GetServiceTable();
	dwgErrorCode=124;
	GetIDTTable();
	dwgErrorCode=125;
	OutputEnv();
	dwgErrorCode=126;	
	return true;
}

bool CSysInfo::NtcallInit()
{
	CPEFile PEFile;
	char FileName[MAX_FN_LEN];
	CHAR*Name=NULL;
	CSymbolModule* pSymbolModule;	
	BYTE CodeBuffer[MAX_INSTR_LEN];
	int n;
	ULONGLONG zwFunc[4]={0,0,0,0};
	ULSIZE ReadLen;
	DWORD ServiceNum;
	ULONGLONG llData;
	TNtcallMap::IT Iter;
	CDbgModule* pDbgModule;

	TStrCpy(FileName,m_szSystem32A);
	TStrCat(FileName,"ntdll.dll");
	PEFile.m_OpenMode|=PE_OPEN_NO_IMPORT;
	if(PEFile.Open(FileName)==false)
	{
		::DbgPrint("Syser : Ntcall initialize failed to load PE file symbol %s\n",FileName);
		return false;
	}
	for(n=0;n<PEFile.m_ExportFuncCount;n++)
	{
		if(_GET_WORD(PEFile.m_ExportFunc[n].FuncName)=='tN')
		{
			ReadLen = PEFile.ReadImageMemory(PEFile.m_ExportFunc[n].Address,CodeBuffer,sizeof(CodeBuffer));
			if(ReadLen!=sizeof(CodeBuffer))continue;
			if((CodeBuffer[0]==0xb8&&CodeBuffer[5]==0x8d&&CodeBuffer[0x9]==0xcd)||//2k
				(CodeBuffer[0]==0xb8&&CodeBuffer[5]==0xba&&CodeBuffer[0xa]==0xff&&CodeBuffer[0xb]==0x12)||//xp
				(CodeBuffer[0]==0xb8&&CodeBuffer[5]==0xba&&CodeBuffer[0xa]==0xff&&CodeBuffer[0xb]==0xd2)//2003
				)
			{
				ServiceNum = *(DWORD*)&CodeBuffer[1];
				llData = PEFile.m_ExportFunc[n].Address-PEFile.m_ImageBase;
				llData <<= 32;
				llData |= ServiceNum;
				Iter = m_NtcallMap.InsertUnique(PEFile.m_ExportFunc[n].FuncName,llData);
				if(Iter==m_NtcallMap.End())continue;
			}
		}
	}
	Iter = m_NtcallMap.Find("NtQueryVirtualMemory");
	if(Iter!=m_NtcallMap.End())
		zwFunc[3]=*Iter;
	PEFile.Close();
	if(m_OSKernelName[0])
		Name = m_OSKernelName;
	if(Name==NULL)
	{
		if(gpSyser->m_pSysDebugger==NULL)
			return true;		
		pDbgModule = gpSyser->m_pSysDebugger->GetModule((ULPOS)KeSetEvent);
		if(pDbgModule==NULL)
			return true;
		Name = (char*)pDbgModule->m_ModuleFullName;
	}
	PEFile.m_OpenMode|=PE_OPEN_NO_IMPORT;	
	if(PEFile.Open(Name)==false)
	{
		::DbgPrint("Syser : Ntcall initialize failed to load PE file symbol %s\n",(char*)Name);
		return true;
	}
	for(n=0;n<PEFile.m_ExportFuncCount;n++)
	{
		if(_GET_WORD(PEFile.m_ExportFunc[n].FuncName)=='wZ')
		{
			ReadLen = PEFile.ReadImageMemory(PEFile.m_ExportFunc[n].Address,CodeBuffer,sizeof(CodeBuffer));
			if(ReadLen==sizeof(CodeBuffer))
			{
				if(CodeBuffer[0]==0xb8||CodeBuffer[5]==0x8d||CodeBuffer[0x9]==0x9c||CodeBuffer[0xa]==0x6a)
				{
					ServiceNum = *(DWORD*)&CodeBuffer[1];
					llData = PEFile.m_ExportFunc[n].Address-PEFile.m_ImageBase;
					llData <<= 32;
					llData |= ServiceNum;
					Iter = m_NtcallMap.InsertUnique(PEFile.m_ExportFunc[n].FuncName,llData);
					if(zwFunc[0]==0)
						zwFunc[0]=llData;
					else if(zwFunc[1]==0)
						zwFunc[1]=llData;
					else if(zwFunc[2]==0)
						zwFunc[2]=llData;
				}
			}
		}
	}
	if(zwFunc[0] && zwFunc[1]&&zwFunc[2]&&zwFunc[3])
	{
		ULONGLONG first,second,addr1,addr2,len1,len2,len3;
		if((zwFunc[0] & 0xffffffff)>(zwFunc[1] & 0xffffffff))
		{
			first = zwFunc[0] & 0xffffffff;
			addr1 = (zwFunc[0]>>32) & 0xffffffff;
			second = zwFunc[1] & 0xffffffff;
			addr2 = (zwFunc[1]>>32) & 0xffffffff;
		}
		else
		{
			first=zwFunc[1] & 0xffffffff;
			addr1 = (zwFunc[1]>>32) & 0xffffffff;
			second=zwFunc[0] & 0xffffffff;
			addr2 = (zwFunc[0]>>32) & 0xffffffff;
		}
		len1= (addr1-addr2) / (first-second);
		if((zwFunc[1] & 0xffffffff)>(zwFunc[2] & 0xffffffff))
		{
			first = zwFunc[1] & 0xffffffff;
			addr1 = (zwFunc[1]>>32) & 0xffffffff;
			second = zwFunc[2] & 0xffffffff;
			addr2 = (zwFunc[2]>>32) & 0xffffffff;
		}
		else
		{
			first=zwFunc[2] & 0xffffffff;
			addr1 = (zwFunc[2]>>32) & 0xffffffff;
			second=zwFunc[1] & 0xffffffff;
			addr2 = (zwFunc[1]>>32) & 0xffffffff;
		}
		len2= (addr1-addr2) / (first-second);
		if((zwFunc[0] & 0xffffffff)>(zwFunc[2] & 0xffffffff))
		{
			first = zwFunc[0] & 0xffffffff;
			addr1 = (zwFunc[0]>>32) & 0xffffffff;
			second = zwFunc[2] & 0xffffffff;
			addr2 = (zwFunc[2]>>32) & 0xffffffff;
		}
		else
		{
			first=zwFunc[2] & 0xffffffff;
			addr1 = (zwFunc[2]>>32) & 0xffffffff;
			second=zwFunc[0] & 0xffffffff;
			addr2 = (zwFunc[0]>>32) & 0xffffffff;
		}
		len3= (addr1-addr2) / (first-second);
		addr2=0;
		if(len2 == len1 || len2 == len3)
		{
			if((zwFunc[0] & 0xffffffff)>(zwFunc[3] & 0xffffffff))
			{
				first = zwFunc[0] & 0xffffffff;			
				second = zwFunc[3] & 0xffffffff;
				addr1 = (zwFunc[0] >> 32) & 0xffffffff;
				addr2 = addr1 -(first - second)*len1;
			}
			else
			{
				first = zwFunc[3] & 0xffffffff;			
				second = zwFunc[0] & 0xffffffff;
				addr1 = (zwFunc[0] >> 32) & 0xffffffff;
				addr2 = addr1 + (first - second)*len1;
			}
		}
		if(m_OSKernlBase)
		{
			addr2+=m_OSKernlBase;
			m_pZwQueryVirtualMemory = *(ZWQUERYVIRTUALMEMORY*)&addr2;
			DbgPrint("Syser : Find ZwQueryVirtualMemory address %08x\n",m_pZwQueryVirtualMemory);
		}

	}
	PEFile.Close();
	return true;
}

void CSysInfo::Release()
{
	gpSyser->m_SyserUI.m_CodeDoc.Close();
	for(CProcMap::IT Iter=m_ProcMap.Begin();Iter!=m_ProcMap.End();Iter++)
		Iter->Release();
	m_ProcMap.Clear();
	gpSyser->m_pSysDebugger=gpSyser->m_pDebugger=NULL;
	SafeDelete(m_OrgWindowsServiceTable);
	SafeDelete(m_OrgWindowsServiceArgTable);
	SafeDelete(m_OrgWindowIDT);
	SafeDelete(m_W32ServiceTable);
	SafeDelete(m_W32ServiceArgv);
}

bool CSysInfo::LoadExpModList()
{
	CSymbolModule*pSymbolModule;
	CTXTFile File;
	WCHAR szBuffer[MAX_FN_LEN];
	CHAR szFileName[MAX_FN_LEN];
	CHAR* pFileName;
	TStrCpy(szFileName,m_szSystem32DriversA);
	TStrCat(szFileName,"ModExSym.lst");
	if(File.Open(szFileName)==false)
	{
		gpFileIO->WriteToFile(szFileName,DefaultPEExportList,TStrLen(DefaultPEExportList));
		if(File.Open(szFileName)==false)
			return false;
	}
	for(TTXTStrList::IT Iter=File.m_StrList.Begin();Iter!=File.m_StrList.End();Iter++)
	{		
		TStrCpyLimit(szFileName,*Iter,MAX_FN_LEN);
		pFileName = TGetFileName(szFileName);
		if(m_OSKernelName[0] && pFileName)
		{
			bool bFind=false;
			for(int i =0 ;m_gNtoskrnlName[i];i++)
			{
				if(TStrICmp(m_gNtoskrnlName[i],pFileName)==0)
				{
					bFind=true;
				}
			}
			if(bFind)
				continue;
		}
		if(ConvertFileName(szFileName)==false)
		{
			TStrCpy(szFileName,"\\??\\");
			TStrCat(szFileName,*Iter);
		}
		if(pSymbolModule=gpSyser->m_SyserUI.LoadPESym(szFileName))
		{
			pSymbolModule->m_ReferenceCount++;//引用计数+1,保证不被释放
			AnsiToUnicode(szFileName,szBuffer,MAX_FN_LEN);
			OUTPUT(WSTR("Syser : Load module %4d export symbols %s\n"),pSymbolModule->m_SymbolMap.Count(),szBuffer);
		}
	}
	File.Close();
	if(m_OSKernelName[0])//这里是确保我们只增加一次 kernel 的符号表。
	{
		if(pSymbolModule=gpSyser->m_SyserUI.LoadPESym(m_OSKernelName))
		{
			pSymbolModule->m_ReferenceCount++;//引用计数+1,保证不被释放
			AnsiToUnicode(m_OSKernelName,szBuffer,MAX_FN_LEN);
			OUTPUT(WSTR("Syser : Load module %4d export symbols %s\n"),pSymbolModule->m_SymbolMap.Count(),szBuffer);
		}
	}
	return true;
}

bool CSysInfo::LoadSDSList()
{
	CTXTFile File;
	CHAR szFileName[MAX_FN_LEN];
	TStrCpy(szFileName,m_szSystem32DriversA);
	TStrCat(szFileName,"SDSInit.lst");
	if(File.Open(szFileName)==false)
		false;
	TStrCpy(szFileName,"\\??\\");
	for(TTXTStrList::IT Iter=File.m_StrList.Begin();Iter!=File.m_StrList.End();Iter++)
	{
		TStrCpyLimit(&szFileName[4],*Iter,MAX_FN_LEN-4);
		gpSyser->m_SyserUI.LoadSDSModule(szFileName);
	}
	File.Close();
	return true;
}

CDbgProcess*CSysInfo::InsertProcess(DWORD PID)
{
	if(GetProcess(PID)!=NULL)
		return NULL;
	CProcMap::IT Iter = m_ProcMap.InsertUnique(PID);
	Iter->InitProcess(PID);
	return &(*Iter);
}

bool CSysInfo::RemoveProcess(DWORD PID)
{
	CProcMap::IT ProcIter=m_ProcMap.Find(PID);
	if(ProcIter==m_ProcMap.End())
		return false;
	CSDSModuleMap::IT Iter=gpSyser->m_SyserUI.m_SDSModuleMap.Begin();
	while(Iter.IsExist())
	{
		if(Iter->m_ParentPID == PID)
		{
			CSDSModuleMap::IT RemoveIter = Iter;
			Iter++;
			gpSyser->m_SyserUI.UnloadSDSModule(&(*RemoveIter));
		}
		else
			Iter++;
	}
	ProcIter->Release();
	m_ProcMap.Remove(ProcIter);
	return true;
}

CDbgProcess*CSysInfo::GetProcessByEPROCESS(DWORD EProcess)
{
	for(CProcMap::IT Iter=m_ProcMap.Begin();Iter!=m_ProcMap.End();Iter++)
	{
		if(Iter->m_PEProcess == *(PEPROCESS*)&EProcess)		
			return &(*Iter);
	}	
	return NULL;
}

CDbgProcess*CSysInfo::GetProcess(DWORD PID)
{
	CProcMap::IT Iter=m_ProcMap.Find(PID);
	if(Iter==m_ProcMap.End())
		return NULL;
	if(Iter->m_PID==0)
		return gpSyser->m_pSysDebugger;
	return &(*Iter);
}

CDbgProcess*CSysInfo::GetProcessByCR3(DWORD CR3)
{
	for(CProcMap::IT Iter=m_ProcMap.Begin();Iter!=m_ProcMap.End();Iter++)
	{
		if(Iter->m_CR3 == CR3 && Iter->m_PID)
		{
			if(Iter->m_PID==0)
				return gpSyser->m_pSysDebugger;
			return &(*Iter);
		}
	}
	return NULL;
}

CDbgProcess*CSysInfo::GetProcess(WCHAR*szProcName)
{
	for(CProcMap::IT Iter=m_ProcMap.Begin();Iter!=m_ProcMap.End();Iter++)
	{
		if(TStrICmp(szProcName,(PCWSTR)Iter->m_ProcNameW)==0)
			return &(*Iter);
	}	
	return NULL;
}

bool CSysInfo::GetProcessName(PEPROCESS curproc,WCHAR*ProcessName,int BufCount)
{
	PWSTR pwStr;
	char*NamePtr;
	if(m_ProcNameOff==0)
	{
		TStrCpy(ProcessName,"<unknown>");
		return false;
	}
    NamePtr=(char*)curproc+m_ProcNameOff;
	AnsiToUnicode(NamePtr,ProcessName,BufCount);
	pwStr = TStrRChr(ProcessName,(WCHAR)'.');
	if(pwStr)
		*pwStr=0;
    return true;
}

DWORD CSysInfo::SearchMemory(DWORD BaseAddr,DWORD BaseSize,BYTE* Feature,DWORD Size)
{
	BYTE Buffer[200];
	DWORD LSize,SectMaxPos=0;
	if(Size>sizeof(Buffer))
		return 0;
	for(DWORD Pos=0;Pos<BaseSize-Size;Pos++)
	{
		if(Pos+Size>SectMaxPos)
		{
			LSize=BaseSize-Pos;
			if(LSize > sizeof(Buffer))
				LSize = sizeof(Buffer);
			SectMaxPos = Pos + LSize;
			if(gpSyser->ReadMemory(BaseAddr+Pos,Buffer,LSize,gpSyser)==0)
			{
				Pos+=sizeof(Buffer);
				continue;
			}
		}
		if(memcmp(&Buffer[Pos+sizeof(Buffer)-SectMaxPos],Feature,Size)==NULL)
			return Pos+BaseAddr;
	}
	return 0;
}

bool CSysInfo::ConvertFileName(CHAR*szFileName)
{
	CHAR szBuffer[MAX_FN_LEN];
	if(TStrNCmp(szFileName,"\\??\\",4)==0)
		return true;
	if(*szFileName!='\\' && szFileName[1]!=':')
	{
		TStrCpy(szBuffer,szFileName);
		TStrCpy(szFileName,m_szSystemRoot);
		TStrCat(szFileName,"system32\\drivers\\");
		TStrCat(szFileName,szBuffer);
		return true;
	}
	if(ConvertFileNameByMacro(szFileName,"\\SystemRoot\\",m_szSystemRootA))
		return true;
	if(ConvertFileNameByMacro(szFileName,m_szSystemRootMarco,m_szSystemRootA))
		return true;
	if(ConvertFileNameByMacro(szFileName,"system32\\",m_szSystem32A))
		return true;
	if(ConvertFileNameByMacro(szFileName,"system32\\drivers\\",m_szSystem32DriversA))
		return true;
	if(ConvertFileNameByMacro(szFileName,"\\device\\lanmanredirector\\","\\\\"))
		return true;
	if(ConvertFileNameByMacro(szFileName,"\\device\\mup\\","\\\\"))
		return true;
	TList<CStrA>::IT Iter = m_SymbolPathList.Begin();
	for(CHAR cPath='C';cPath<='Z' && Iter!=m_SymbolPathList.End();cPath++)
	{
		TStrCpy(szBuffer,"\\??\\C:");
		szBuffer[4]=cPath;
		if(ConvertFileNameByMacro(szFileName,*Iter,szBuffer))
			return true;
		Iter++;
	}
	return false;
}

void CSysInfo::GetPathSymbolLinker()
{
	NTSTATUS            status;
	HANDLE              hLink;
	OBJECT_ATTRIBUTES   oa;
	UNICODE_STRING      Name;
	WCHAR               szBuffer[256];
	char				szBufferA[256];
	m_SymbolPathList.Clear();
	for(WCHAR cPath='C';cPath<='Z';cPath++)
	{
		TStrCpy(szBuffer,"\\??\\C:");
		szBuffer[4]=cPath;
		Name.Buffer=szBuffer;
		Name.Length=wcslen(szBuffer)*2;
		Name.MaximumLength=sizeof(szBuffer);
		InitializeObjectAttributes(&oa,&Name,OBJ_CASE_INSENSITIVE,NULL,NULL);
		if(!NT_SUCCESS(status=ZwOpenSymbolicLinkObject(&hLink,0x20001,&oa)))			
			return;
		Name.Buffer=szBuffer;
		Name.MaximumLength=Name.Length=sizeof(szBuffer);
		ZeroMemory(szBuffer,sizeof(szBuffer));
		if(!NT_SUCCESS(status=ZwQuerySymbolicLinkObject(hLink,&Name,NULL)))
			return;
		UnicodeToAnsi(szBuffer,szBufferA,256);
		m_SymbolPathList.Append(szBufferA);
		ZwClose(hLink);
	}
}

bool CSysInfo::GetDriverList()
{
	ULONG Size;
	PEPROCESS Pr;
	MODULE_ID ModuleID;
	CDbgModule*pDbgModule;
	CHAR szFileName[MAX_FN_LEN];
	CSymbolModule*pSymbolModule;
	PSYSTEM_MODULE_INFORMATION pModInfo,p;
	ZwQuerySystemInformation( SystemModuleInformation,&Size,0,&Size);
	if(Size==0)
		return false;
	p = (PSYSTEM_MODULE_INFORMATION) new BYTE[Size];
	ZwQuerySystemInformation( SystemModuleInformation,p,Size,0);
	pModInfo = p;
	Pr=NULL;
	if(gpSyser->m_pCsrssProcess)
	{
		PsLookupProcessByProcessId((HANDLE)gpSyser->m_pCsrssProcess->m_PID,&Pr);
		if(Pr==NULL)
		{
			delete p;
			return false;
		}
		KeAttachProcess((PRKPROCESS)Pr);
	}
	for(ULONG n=0; n<p->dCount; n++)
	{
		TStrCpyLimit(szFileName,(PCSTR)pModInfo->aSM[n].abName,MAX_FN_LEN);
		ConvertFileName(szFileName);
		if(MmIsAddressValid(pModInfo->aSM[n].pAddress))
			ModuleID = GetModuleID((ULPOS)pModInfo->aSM[n].pAddress,pModInfo->aSM[n].dSize);
		else
			ModuleID = 0;
		gpSyser->m_SyserUI.m_SyserDI.OnLoadModule(gpSyser->m_pSysDebugger,szFileName,(ULPOS)pModInfo->aSM[n].pAddress,pModInfo->aSM[n].dSize,ModuleID);
	}
	if(Pr)
		KeDetachProcess();
	delete p;
	pDbgModule = gpSyser->m_pSysDebugger->GetModule("Syser.sys");
	if(pDbgModule)
	{
		m_SyserBase =  pDbgModule->m_ModuleBase;
		m_SyserHighBase =  pDbgModule->m_ModuleBase+pDbgModule->m_ModuleSize;
	}
	return true;
}


extern "C" NTSTATUS NTSYSAPI ZwOpenProcess(
			  OUT PHANDLE ProcessHandle,
			  IN ACCESS_MASK DesiredAccess,
			  IN POBJECT_ATTRIBUTES ObjectAttributes,
			  IN PCLIENT_ID ClientId OPTIONAL
			  );
extern "C" NTSTATUS NTSYSAPI NtQueryVirtualMemory(
					 IN HANDLE ProcessHandle,
					 IN PVOID BaseAddress,
					 IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
					 OUT PVOID MemoryInformation,
					 IN ULONG MemoryInformationLength,
					 OUT PULONG ReturnLength OPTIONAL
					 );
extern "C" NTSTATUS NTSYSAPI __stdcall ZwQueryVirtualMemory(
					 IN HANDLE ProcessHandle,
					 IN PVOID BaseAddress,
					 IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
					 OUT PVOID MemoryInformation,
					 IN ULONG MemoryInformationLength,
					 OUT PULONG ReturnLength OPTIONAL
					 );



bool CSysInfo::GetDllListNew(CDbgProcess*pProcess)
{
	NTSTATUS ntstatus;
	MEMORY_BASIC_INFORMATION MemoryInfo;
	OBJECT_ATTRIBUTES   oa={sizeof(OBJECT_ATTRIBUTES), 0,NULL,NULL};
	HANDLE hProcess;
	PMEMORY_SECTION_NAME pName;
	WCHAR * PrevName;
	CLIENT_ID ClientID;
	CHAR szFileName[MAX_FN_LEN];
	bool bRetValue=true;
	DWORD nLength=0;
	
	if(pProcess==NULL || m_pZwQueryVirtualMemory==NULL)
		return false;
	pName = (PMEMORY_SECTION_NAME)new BYTE[520+520];
	if(pName==NULL)
		return false;	
	PrevName=(WCHAR*)pName;
	PrevName=PrevName+260;
	PrevName[0]=0;
	ClientID.UniqueProcess=(HANDLE)pProcess->m_PID;
	ClientID.UniqueThread=0;

	ntstatus = ZwOpenProcess(&hProcess,PROCESS_ALL_ACCESS,&oa,&ClientID);
	if(!NT_SUCCESS(ntstatus))
	{
		delete pName;
		return false;		
	}
	PEPROCESS Pr=NULL;
	DWORD PrevAddress=0;
	DWORD PrevLen=0;
	MODULE_ID ModuleID;
	PsLookupProcessByProcessId((HANDLE)pProcess->m_PID,&Pr);
	if(Pr==NULL)
		return false;	
	__try
	{
	if(pProcess!=gpSyser->m_pSysDebugger)
		KeAttachProcess((PRKPROCESS)Pr);
	DWORD ImageSize=PrevLen;
	for(DWORD i=0x0;i<0x7fffffff;i+=0x10000)
	{			
		ntstatus = m_pZwQueryVirtualMemory(hProcess,*(PVOID*)&i,MemorySectionName,pName,520,&nLength);
		nLength=i;			
		if(!NT_SUCCESS(ntstatus))
		{
			continue;
		}
		ntstatus = m_pZwQueryVirtualMemory(hProcess,*(PVOID*)&i,MemoryBasicInformation,&MemoryInfo,sizeof(MemoryInfo),&nLength);
		if(!NT_SUCCESS(ntstatus) || (MemoryInfo.Type & MEM_IMAGE)==0)
		{				
			continue;
		}
		if(TStrICmp(pName->SectionFileName.Buffer,PrevName))
		{
			if(PrevName[0]!=0 && PrevAddress && PrevLen)
			{
				ImageSize=PrevLen;
				ModuleID = GetModuleIDAndImageSize(PrevAddress,ImageSize);
				UnicodeToAnsi(PrevName,szFileName,MAX_FN_LEN);
				if(TStrNICmp(szFileName,WSTR("\\??\\"),4))
				{
					if(ConvertFileName(szFileName)==false)
					{
						TStrCpy(szFileName,"\\??\\");
						UnicodeToAnsi(PrevName,&szFileName[4],MAX_FN_LEN-4);
					}
				}
				gpSyser->m_SyserUI.m_SyserDI.OnLoadModule(pProcess,szFileName,PrevAddress,ImageSize,ModuleID);
			}
			PrevAddress=i;
			PrevLen=MemoryInfo.RegionSize;
			TStrCpy(PrevName,pName->SectionFileName.Buffer);
			
		}
		else
		{
			PrevLen+=MemoryInfo.RegionSize;
		}
		i=i+MemoryInfo.RegionSize;
		i=i&0xffff0000;
	}
	
	if(PrevName[0]!=0 && PrevAddress && PrevLen)
	{
		ImageSize=PrevLen;
		ModuleID = GetModuleIDAndImageSize(PrevAddress,ImageSize);
		UnicodeToAnsi(PrevName,szFileName,MAX_FN_LEN);
		if(TStrNICmp(szFileName,WSTR("\\??\\"),4))
		{
			if(ConvertFileName(szFileName)==false)
			{
				TStrCpy(szFileName,"\\??\\");
				UnicodeToAnsi(PrevName,&szFileName[4],MAX_FN_LEN-4);
			}
		}
		gpSyser->m_SyserUI.m_SyserDI.OnLoadModule(pProcess,szFileName,PrevAddress,ImageSize,ModuleID);
	}
		
	delete pName;
	if(pProcess!=gpSyser->m_pSysDebugger)
		KeDetachProcess();
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		bRetValue=false;		
	}
	ZwClose(hProcess);
	
	return bRetValue;
}
bool CSysInfo::GetDllList(CDbgProcess*pProcess)
{
	bool bRetValue=true;
	MODULE_ID ModuleID;
	CHAR szFileName[MAX_FN_LEN];
	WCHAR wszFileName[MAX_FN_LEN],*pUserModeName;
	PEB *Peb;
	PEPROCESS Pr;
	PEB_LDR_DATA *Ldr;
	LDR_DATA_TABLE_ENTRY *M,*T;
	if(pProcess == NULL || pProcess->m_pCurrentPEB==NULL)
		return false;
	Pr=NULL;
	PsLookupProcessByProcessId((HANDLE)pProcess->m_PID,&Pr);
	if(Pr==NULL)
		return false;	
	if(pProcess!=gpSyser->m_pSysDebugger)
		KeAttachProcess((PRKPROCESS)Pr);
	__try
	{
		Peb=(PEB*)pProcess->m_pCurrentPEB;
		
		Ldr=Peb->Ldr;
		
		M=(LDR_DATA_TABLE_ENTRY*)((BYTE*)Ldr->InMemoryOrderModuleList.Flink-8);
		T=M;
		
		do
		{
			TStrCpyLimit(wszFileName,T->FullDllName.Buffer,T->FullDllName.Length/2+1);
			UnicodeToAnsi(wszFileName,szFileName,MAX_FN_LEN);
			if(TStrNICmp(T->FullDllName.Buffer,WSTR("\\??\\"),4))
			{
				if(ConvertFileName(szFileName)==false)
				{
					TStrCpy(szFileName,"\\??\\");
					UnicodeToAnsi(wszFileName,&szFileName[4],MAX_FN_LEN-4);
				}
			}
			ModuleID = GetModuleID((ULPOS)T->DllBase,T->SizeOfImage);
			gpSyser->m_SyserUI.m_SyserDI.OnLoadModule(pProcess,szFileName,(ULPOS)T->DllBase,T->SizeOfImage,ModuleID);
			T=(LDR_DATA_TABLE_ENTRY*)T->InLoadOrderLinks.Flink;
			
		}while(T->InLoadOrderLinks.Flink!=(LIST_ENTRY*)M);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		bRetValue=false;
		//::DbgPrint("Syser : %s GetDllList except...\n",(PCSTR)pProcess->m_ProcName);
	}
	if(pProcess!=gpSyser->m_pSysDebugger)
		KeDetachProcess();
	return bRetValue;
}

#ifdef AnsiToUnicode
#undef AnsiToUnicode
#endif

#ifdef UnicodeToAnsi
#undef UnicodeToAnsi
#endif

int SyserUnicodeToAnsi(const WCHAR*WszBuf,char*szBuf,int MaxLen)
{
	KIRQL Irq;
	int n,Result;
	for(n=0;WszBuf[n] && n<MaxLen;n++)
	{
		if(WszBuf[n]>0xFF)
			break;
	}
	if(WszBuf[n]==0 || n>=MaxLen)
		return TStrCpyLimit(szBuf,WszBuf,MaxLen);
	if(gpSysLangDevEx)
		return gpSysLangDevEx->pfnUnicodeToAnsi(WszBuf,szBuf,MaxLen);
	return TStrCpyLimit(szBuf,WszBuf,MaxLen);
}

int SyserAnsiToUnicode(const char*szBuf,WCHAR*WszBuf,int MaxLen)
{
	int n,Result;
	for(n=0;szBuf[n] && n<MaxLen;n++)
	{
		if(szBuf[n]&0x80)
			break;
	}
	if(szBuf[n]==0 || n>=MaxLen)
		return TStrCpyLimit(WszBuf,szBuf,MaxLen);
	if(gpSysLangDevEx)
		return gpSysLangDevEx->pfnAnsiToUnicode(szBuf,WszBuf,MaxLen);
	Result = 0;
	*WszBuf = 0;
	return Result;
}

bool CSysInfo::GetIDTTable()
{
	DWORD i;
	bool bOK;
	BYTE *PageBuffer;
	ULPOS Pos=0,ReadSize;
	
	CDbgModule*pDbgModule=NULL;
	
	if(gpSyser->m_pSysDebugger==NULL)
		return false;
	for(i = 0;m_gNtoskrnlName[i];i++)
	{
		pDbgModule = gpSyser->m_pSysDebugger->GetModule(m_gNtoskrnlName[i]);
		if(pDbgModule!=NULL)
			break;
	}
	if(pDbgModule==NULL||pDbgModule->m_ModuleBase==0||pDbgModule->m_ModuleSize==0)
		return false;
	PageBuffer = new BYTE[0x1040];
	if(PageBuffer==NULL)return false;
	memset(PageBuffer,0,0x1040);
	CPEFile PEFile;
	bOK = PEFile.Open(pDbgModule->m_ModuleFullName);
	if(bOK==false)
	{
		delete PageBuffer;
		return false;
	}
	for(;Pos<PEFile.m_FileSize;Pos+=0x1000)
	{
		ReadSize = (PEFile.m_FileSize-Pos) < 0x1020 ? (PEFile.m_FileSize-Pos) : 0x1020;
		if(PEFile.ReadFile(Pos,PageBuffer,ReadSize)==false)
			continue;
		for(i = 0; i < ReadSize;i++)
		{
			if(((*(DWORD*)&PageBuffer[i]) == 0x88e00) && ((*(DWORD*)&PageBuffer[i+0x8]) == 0x88e00) && ((*(DWORD*)&PageBuffer[i+0x10]) == 0x88e00))
			{
				Pos=Pos+i-4;
				if(PEFile.ReadFile(Pos,PageBuffer,0x800))
				{
					m_OrgWindowIDT = (PORGWINDOWSIDTENTRY)new BYTE[0x800];
					if(m_OrgWindowIDT)
					{
						memcpy(m_OrgWindowIDT,PageBuffer,0x800);
						for(int j  = 0 ; j < 0x100; j++)
						{
							if(m_OrgWindowIDT[j].EntryPoint)
							m_OrgWindowIDT[j].EntryPoint=m_OrgWindowIDT[j].EntryPoint - PEFile.m_ImageBase + pDbgModule->m_ModuleBase;
						}
						delete PageBuffer;
						PEFile.Close();
						//::DbgPrint("Syser : OrgWindowsIDT %08x\n",Pos);
						return true;
					}
				}
				delete PageBuffer;
				PEFile.Close();
				return false;
			}
		}
	}
	delete PageBuffer;
	PEFile.Close();
	return false;
}

bool CSysInfo::GetOSKernelName()
{
	ULONG Size;	
	CHAR szFileName[MAX_FN_LEN];
	NTSTATUS ntstatus;
	PSYSTEM_MODULE_INFORMATION pModInfo,p;
	ntstatus = ZwQuerySystemInformation( SystemModuleInformation,NULL,0,&Size);
	if(ntstatus != STATUS_INFO_LENGTH_MISMATCH || Size==0)	
		return false;
	p = (PSYSTEM_MODULE_INFORMATION) new BYTE[Size];
	if(p==NULL)
		return false;
	ntstatus = ZwQuerySystemInformation( SystemModuleInformation,p,Size,0);
	if(!NT_SUCCESS(ntstatus))
	{
		delete p;
		return false;
	}
	pModInfo = p;
	for(ULONG n=0; n<p->dCount; n++)
	{
		TStrCpyLimit(szFileName,(PCSTR)pModInfo->aSM[n].abName+pModInfo->aSM[n].wNameOffset,MAX_FN_LEN);
		for(int i =0 ;m_gNtoskrnlName[i];i++)
		{
			if(TStrICmp(szFileName,m_gNtoskrnlName[i])==0)
			{
				TStrCpyLimit(szFileName,(PCSTR)pModInfo->aSM[n].abName,MAX_FN_LEN);
				if(ConvertFileName(szFileName)==false)
				{
					TStrCpy(szFileName,"\\??\\");
					TStrCpyLimit(szFileName,(PCSTR)pModInfo->aSM[n].abName,MAX_FN_LEN-sizeof("\\??\\"));
				}
				m_OSKernlBase = *(DWORD*)&pModInfo->aSM[n].pAddress;
				
				TStrCpy(m_OSKernelName,szFileName);
				::DbgPrint("Syser : Windows kernel name '%s' base=%08x\n",(PCSTR)pModInfo->aSM[n].abName+pModInfo->aSM[n].wNameOffset,m_OSKernlBase);
				delete p;
				return true;
			}
		}				
	}	
	delete p;
	return false;	
}


bool CSysInfo::GetServiceTable()
{
	DWORD i;
	CDbgModule*pDbgModule=NULL;
	DWORD KeServiceDescriptorTableRav,ServiceCount,dwSize;
	if(gpSyser->m_pSysDebugger==NULL)
		return false;

	if(GetWin32KServiceTable())
		FindWin32KServiceSymName();
	for(i = 0; m_gNtoskrnlName[i];i++)
	{
		pDbgModule = gpSyser->m_pSysDebugger->GetModule(m_gNtoskrnlName[i]);
		if(pDbgModule!=NULL) break;
	}
	if(pDbgModule==NULL||pDbgModule->m_ModuleBase==0||pDbgModule->m_ModuleSize==0)
		return false;
	CPEFile PEFile;
	if(PEFile.Open(pDbgModule->m_ModuleFullName)==false)
		return false;
	KeServiceDescriptorTableRav = PEFile.GetExportFunc("KeServiceDescriptorTable");
	if(KeServiceDescriptorTableRav<=PEFile.m_ImageBase||KeServiceDescriptorTableRav>=(PEFile.m_ImageBase+PEFile.m_ImageSize))
	{
error_quit:
		PEFile.Close();
		return false;
	}
	::DbgPrint("Syser : KeServiceDescriptorTable=%08x\n",KeServiceDescriptorTable);
	KeServiceDescriptorTableRav-=PEFile.m_ImageBase;
	KeServiceDescriptorTableRav+=pDbgModule->m_ModuleBase;
	DWORD ServiceTableBegin;
	PSERVICETABLE pServiceTable = *(PSERVICETABLE*)&KeServiceDescriptorTableRav;
	bool Success;
	if(ReadDword(&pServiceTable->LowCall,&m_LoCount)==false)
		goto error_quit;
	if(ReadDword(&pServiceTable->HiCall,&m_HiCount)==false)
		goto error_quit;		
	ServiceCount = m_HiCount - m_LoCount + 1;	
	ServiceTableBegin = *(DWORD*)&pServiceTable->ServiceTable;
	ServiceTableBegin -= pDbgModule->m_ModuleBase;
	if(ServiceTableBegin>=PEFile.m_ImageSize||ServiceCount>=0x1000)
	{
		goto error_quit;
	}
	m_OrgWindowsServiceTable = new DWORD[ServiceCount];
	if(m_OrgWindowsServiceTable==NULL)goto error_quit;
	m_OrgWindowsServiceArgTable = new DWORD[ServiceCount];
	if(m_OrgWindowsServiceArgTable == NULL)
	{
		delete m_OrgWindowsServiceTable;
		m_OrgWindowsServiceTable = NULL;
		goto error_quit;
	}
	memset(m_OrgWindowsServiceTable,0,sizeof(DWORD)*ServiceCount);
	dwSize = ServiceTableBegin % 0x1000 + sizeof(DWORD)*ServiceCount;
	dwSize += (0x1000-1);
	BYTE *PageBuffer=new BYTE[dwSize/0x1000*0x1000];
	if(PageBuffer==NULL)
	{
		delete m_OrgWindowsServiceArgTable;
		delete m_OrgWindowsServiceTable;
		m_OrgWindowsServiceTable = NULL;
		m_OrgWindowsServiceArgTable = NULL;
		goto error_quit;
	}
	PEFile.RelocLoad(pDbgModule->m_ModuleBase);
	for(i = 0 ; i < dwSize/0x1000;i++)
	{
		PEFile.LoadPage(ServiceTableBegin - ServiceTableBegin%0x1000 + pDbgModule->m_ModuleBase + i*0x1000,&PageBuffer[i*0x1000]);
	}
	memcpy(m_OrgWindowsServiceTable,&PageBuffer[ServiceTableBegin % 0x1000],sizeof(DWORD)*ServiceCount);
	delete PageBuffer;
	PEFile.Close();
	return true;
}

bool GetPEBOffset(ULONG* PEBOffset)
{
	ULONG Size,PID,Count=0,i=0;
	UCHAR* SearchBuffer;
	PEPROCESS Pr = NULL;
	void*Buffer;
	bool bOK;
	ULONG Array[3]={0,0,0};
	if(PEBOffset)
		*PEBOffset=0;
	
	Size=sizeof(SYSTEM_PROCESS_INFORMATION)*0x100;
	Buffer = new BYTE[Size];
	while(Buffer) 
	{
		if(NT_SUCCESS(ZwQuerySystemInformation(SystemProcessInformation,Buffer,Size,NULL)))
			break;
		delete Buffer;
		Size*=2;
		Buffer=new BYTE[Size];
		if(Buffer==NULL || Size>sizeof(SYSTEM_PROCESS_INFORMATION)*0x1000)
			return false;
	}
	ULONG Offset = 0;
	SYSTEM_PROCESS_INFORMATION*P=(SYSTEM_PROCESS_INFORMATION*)Buffer;
	do
	{
		P=(SYSTEM_PROCESS_INFORMATION*)((BYTE*)P+Offset);
		Offset = P->NextEntryOffset;
		PID = PTR_TO_NUM(P->UniqueProcessId);
		if(PID<8)continue;
		Pr = NULL;
		PsLookupProcessByProcessId(NUM_TO_PTR(PID),&Pr);
		if(Pr)
		{
			SearchBuffer=(UCHAR*)Pr;
			if(MmIsAddressValid((VOID*)&SearchBuffer[0x150])==false)
				continue;			
			if(MmIsAddressValid((VOID*)&SearchBuffer[0x304])==false)
				continue;
			for(int n = 0x150; n < 0x300;n++)
			{
				if((*(DWORD*)&SearchBuffer[n] & 0x7FFD0FFF)==0x7ffd0000)
				{
					Array[i]=n;
					i++;
					break;
				}
			}
			if(i>=3)
				break;
		}
	}while(Offset);
	delete Buffer;
	bOK=true;
	for(i = 0; i < 3;i++)
	{
		if(Array[i]!=Array[0])
		{
			bOK=false;
			break;
		}
	}	
	if(bOK)
	{
		if(PEBOffset)
			*PEBOffset=Array[0];		
	}
	return bOK;
}

bool CSysInfo::PatchI8042Driver()
{
	bool retvalue=false;
	CDbgModule*pModule;
	char szFileName[MAX_FN_LEN];
	int i,j;

	char* i8042[]={"i8042prt.sys","msi8042.sys","l8042prt.sys",NULL};

	for(i = 0; i8042[i];i++)
	{
		pModule = gpSyser->m_pSysDebugger->GetModule(i8042[i]);
		if(pModule)
			break;
	}	
	if(pModule==NULL)
	{
		DbgPrint("not found i8042\n");
		return retvalue;
	}
	
	CPEFile PEFile;
	TStrCpy(szFileName,m_szSystem32DriversA);
	TStrCat(szFileName,i8042[i]);
	//PEFile.m_OpenMode|=PE_OPEN_NO_EXPORT;
	if(PEFile.Open(szFileName)==false)
		return retvalue;
	DbgPrint("name = %s\n",szFileName);
	IMPORT_FUNC* pFuncREAD_PORT_UCHAR=NULL;
	IMPORT_FUNC* pFuncWRITE_PORT_UCHAR=NULL;	
	/*
	IMPORT_FUNC*FuncList;
	for(i = 0; i < PEFile.m_ImportModuleCount;i++)
	{
		DbgPrint(PEFile.m_ImportModule[i].ModuleName);
DbgPrint("\n");
		FuncList = PEFile.m_ImportModule[i].FuncList;
		if(FuncList)
		{
			for(j=0;j<PEFile.m_ImportModule[i].FuncCount;j++)
			{
				DbgPrint(FuncList[j].FuncName);
				DbgPrint("\n");
			}
		}				
	}
	*/
	pFuncREAD_PORT_UCHAR = PEFile.GetImportModuleFunc("hal.dll","READ_PORT_UCHAR");
	if(pFuncREAD_PORT_UCHAR==NULL)
		pFuncREAD_PORT_UCHAR = PEFile.GetImportModuleFunc("hal.dll","IMP_READ_PORT_UCHAR");
	pFuncWRITE_PORT_UCHAR = PEFile.GetImportModuleFunc("hal.dll","WRITE_PORT_UCHAR");
	if(pFuncWRITE_PORT_UCHAR ==NULL) 
		pFuncWRITE_PORT_UCHAR = PEFile.GetImportModuleFunc("hal.dll","IMP_WRITE_PORT_UCHAR");
	//DbgPrint("pFuncREAD_PORT_UCHAR=%08x pFuncWRITE_PORT_UCHAR=%08x\n",pFuncREAD_PORT_UCHAR,pFuncWRITE_PORT_UCHAR);
	if(pFuncREAD_PORT_UCHAR && pFuncWRITE_PORT_UCHAR)
	{
		retvalue=true;
		//::DbgPrint("%s BaseAddress =%08x\n",i8042[i],pModule->m_ModuleBase);
		//::DbgPrint("READ_PORT_UCHAR =%08x\n",pFuncREAD_PORT_UCHAR->ThunkAddr-PEFile.m_ImageBase+pModule->m_ModuleBase);
		//::DbgPrint("WRITE_PORT_UCHAR =%08x\n",pFuncWRITE_PORT_UCHAR->ThunkAddr-PEFile.m_ImageBase+pModule->m_ModuleBase);
		//::DbgPrint("pFuncWRITE_PORT_UCHAR->ThunkAddr=%08x\n",pFuncWRITE_PORT_UCHAR->ThunkAddr);
		//::DbgPrint("pFuncREAD_PORT_UCHAR->ThunkAddr=%08x\n",pFuncREAD_PORT_UCHAR->ThunkAddr);
		
	}	
	PEFile.Close();
	return true;
}