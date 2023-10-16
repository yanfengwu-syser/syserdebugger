#include "StdAfx.h"
#include "Syser.h"
#include "StringReference.h"

ULSIZE ReadDbgProcMemory(ULPOS Address,void*Buffer,ULSIZE Size,void*Param)
{
#ifdef	CODE_OS_NT_DRV
	ULSIZE Len=0;
	bool bSuccess;
	while(Size)
	{
		PUT_BYTE(Buffer,Len,ReadByte(RT_PVOID(Address,Len),&bSuccess));
		if(bSuccess==false)
			break;
		Len++;
		Size--;
	}
	return Len;
#else
	return ((CDebugger*)Param)->ReadMemory(Address,Buffer,Size);
#endif
}

void CSyserDI::OnLoadModule(CDebugger*pDbgProc,PCSTR szFileName,ULPOS ModuleBase,ULSIZE ModuleSize,MODULE_ID ModuleID)
{
	CCommentModule*pCommentModule;
	CSymbolModule*pSymbolModule;
	CDbgModule*pDbgModule = pDbgProc->m_ModuleList.InsertModule(szFileName,ModuleBase,ModuleSize,ModuleID);
	if(pDbgModule==NULL)
		return;
	if(pCommentModule = m_pCommentContainer->GetCommentModule(ModuleID))
		pDbgModule->AttachCommentModule(pCommentModule);
	if(pSymbolModule = m_pSymbolContainer->GetSymbolModule(ModuleID))
	{
		pDbgModule->AttachSymbolModule(pSymbolModule);
		return;
	}
/////////////////////////////////////////////////////////////////////////////////////
#ifdef CODE_OS_WIN
	gpSyser->m_SyserUI.LoadTranslateSDS(szFileName,ModuleBase,ModuleSize);
	gpSyser->m_SyserUI.LoadPESym(szFileName,pDbgModule);
#else
	CSDSModuleMap::IT Iter = gpSyser->m_SyserUI.m_SDSModuleMap.Find(ModuleID);
	if(Iter.IsExist())
	{
		pSymbolModule = m_pSymbolContainer->InsertSymbolModule(ModuleID);
		pDbgModule->AttachSymbolModule(pSymbolModule);
		gpSyser->m_SyserUI.LoadSDSSymbol(&(*Iter));
	}
#endif
}

void CSyserDI::OnUnloadModule(CDebugger*pDbgProc,ULPOS ModuleBase)
{
	CDbgModule*pDbgModule=pDbgProc->m_ModuleList.GetModule(ModuleBase);
	if(pDbgModule==NULL)
		return;
#ifdef CODE_OS_NT_DRV
	//////////////////////////////////////////////////////////////////////////
	//Unload SDS Module
	CSDSModule*pSDSModule = gpSyser->m_SyserUI.GetSDSModule(pDbgModule->m_ModuleBase);
	if(pSDSModule && pSDSModule->m_ParentPID == gpSyser->m_pDebugger->m_PID)
	{
		gpSyser->m_SyserUI.UnloadSDSModule(pSDSModule);
	}
#endif
	//////////////////////////////////////////////////////////////////////////
	//删除在此模块上的代码断点
	CCodeBPMap::IT Iter = pDbgProc->m_pCodeBPMap->Begin();
	while(Iter.IsExist())
	{
		if(pDbgProc->m_PID == Iter->PID && Iter->Address>=pDbgModule->m_ModuleBase && Iter->Address<pDbgModule->m_ModuleBase+pDbgModule->m_ModuleSize)
		{//因为内存已释放，只需要删除断点数据
			CCodeBPMap::IT RemoveIter=Iter;
			//DbgPrint("Syser : Clear Module BP [%s] %08X %s\n",(PCSTR)pDbgProc->m_ProcName,RemoveIter->Address,(PCSTR)RemoveIter->Name);
			Iter++;
			RemoveIter->State = BP_STATE_DISABLE;
			pDbgProc->RemoveCodeBP(&(*RemoveIter));
		}
		else
			Iter++;
	}
	//////////////////////////////////////////////////////////////////////////
	//删除系统进程中模块
	pDbgProc->m_ModuleList.RemoveModule(pDbgModule->m_ModuleBase);
	return;
}

bool CSyserDI::OnDebugTerminate(bool bCloseDoc)
{
	if(bCloseDoc)
	{
		RUNCMD(WSTR("close"));
	}
	else
	{
		gpSyser->m_MainFrame.m_SystemExplorer.LocalEIP(*X86_REG_PTR.pEIP);
		gpSyser->m_MainFrame.m_SystemExplorer.UpdateContext();
	}
	return true;
}

bool CSyserDI::OnDebugPlunge(UINT PlungeType)
{
	if(SyserOption.iFollowMode!=SYSER_FM_AUTOMATIC)
		gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SyserOption.iFollowMode==SYSTEM_EXPLORER_VIEW?SYSTEM_EXPLORER_VIEW:SOURCE_EXPLORER_VIEW);
	else
		gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SYSTEM_EXPLORER_VIEW);

	gpSyser->m_MainFrame.m_SystemExplorer.LocalEIP(*X86_REG_PTR.pEIP);
	gpSyser->m_MainFrame.m_SystemExplorer.InsertRunTrace();
	UpdateContext();
	for(CPluginMap::IT Iter = gpSyser->m_PluginMap.Begin();Iter!=gpSyser->m_PluginMap.End();Iter++)
	{
		if(Iter->fpOnDebuggerPlunge)
			Iter->fpOnDebuggerPlunge();
	}
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

bool CSyserDI::OnDebugTerminateMultiThread(bool bCloseDoc)
{
	WISP_MSG Msg;
	Msg.hWnd = &gpSyser->m_MainFrame;
	Msg.Msg = EVENT_ID_DEBUG_TERMINATE;
	Msg.Command.Param1 = bCloseDoc;
	gpSyser->PostMessage(&Msg);
	return true;
}

bool CSyserDI::OnDebugPlungeMultiThread(UINT PlungeType)
{
	WISP_MSG Msg;
	Msg.hWnd = &gpSyser->m_MainFrame;
	Msg.Msg = EVENT_ID_DEBUG_PLUNGE;
	Msg.Command.Param1 = PlungeType;
	gpSyser->PostMessage(&Msg);
	return true;
}

void CSyserDI::UpdateTraceConditionVal()
{
	gpSyser->m_SyserUI.m_CodeDoc.UpdateEIPOpcode();
}

void CSyserDI::UpdateContext()
{
	UPDATE_CONTEXT();
	UPDATE_SOURCE_CODE_VIEW(true);//Ensure Show EIP
	gpSyser->m_SyserUI.m_CallStack.UpdateContext();
	gpSyser->m_MainFrame.m_CallStackWnd.UpdateContext();
}

void CSyserDI::DisplayMsg(PCSTR szMessage)
{
	WISP_CHAR szBuffer[512];
	AnsiToUnicode(szMessage,szBuffer,512);
#ifdef CODE_OS_NT_DRV
	if(gbActive)
		gpSyser->m_MainFrame.m_SystemExplorer.m_TerminalWnd.Output(szBuffer);
	else
		SCR_DBG_PRINT(gpSyser->m_RootPos.x+(gpSyser->m_FrameBuffer.Width-TStrLen(szMessage)*8)/2,gpSyser->m_RealFrameBuffer.Height/2,WSTR("%s"),szBuffer);
#else
	gpSyser->m_MainFrame.m_SystemExplorer.m_TerminalWnd.Output(szBuffer);
#endif
}

bool CSyserDI::TestCondition(PCSTR szCondition,PBREAK_POINT pBP)
{
	DWORD Result;
	if(*szCondition==0)
		return true;
	if(pBP)
		gpSyser->m_SyserUI.m_CodeDoc.m_BPCount=pBP->BPCount;
	return CALCEXP(szCondition,&Result) && Result!=0;
}

bool CSyserDI::RunCmd(PCSTR szCmd)
{
	WCHAR szBuffer[256];
	AnsiToUnicode(szCmd,szBuffer,256);
	RUNCMD(szBuffer);
	return true;
}

void CSyserDI::RunCmdList(PCSTR szCmd)
{
	WCHAR szBuffer[1024];
	if(*szCmd==0)
		return;
	AnsiToUnicode(szCmd,szBuffer,1024);
	gpSyser->m_MainFrame.m_ConsoleWnd.RunCmdList(szBuffer);	
}


bool CSyserDI::CalcPageRangeCondition()
{
	return true;
}
CDebugger* CSyserDI::GetCurrentDebugger()
{
	return gpSyser->m_pDebugger;
}

CExpCalc::STExpItem* ColonOptrFunc(CExpCalc::STExpItemListIT&OptIter,CExpCalc::STExpItemList&ExpItemList,CSyserCodeDoc*pThis)
{
	if(pThis->CheckCalcItem(0,OptIter,1,ExpItemList)==false)
		return NULL;
	CExpCalc::STExpItemListIT PrevIter,NextIter;
	PrevIter = OptIter-1;
	NextIter = OptIter+1;
	if(PrevIter==ExpItemList.End())
		return NULL;
	int n = I_ES;
	while(n<=I_GS)
	{
		if(TStrNICmp(CInstrSym::m_SegStr[n],PrevIter->ItemStr,2)==0)
			break;
		n++;
	}
	if(n>I_GS)
		return NULL;
	PrevIter->Value.Value = 0;
	gpSyser->m_pDebugger->GetSegRegBase(n,(DWORD*)&PrevIter->Value.Value);
	PrevIter->Value.Value=PrevIter->Value.Value + NextIter->Value.Value;
	pThis->RemoveCalcItem(OptIter,2,ExpItemList);
	return &(*PrevIter);
}

CSyserCodeDoc::CSyserCodeDoc()
{
	InsertOptFunc(":",3,(PFOptFunc)ColonOptrFunc,this);
}

CSyserCodeDoc::~CSyserCodeDoc()
{
}

bool CSyserCodeDoc::AddrToSym(DWORD Address,PSTR szSym,int MaxLength)
{
	return gpSyser->m_SyserUI.GetSym(Address,szSym,MaxLength);
}

bool CSyserCodeDoc::GetInstrRefPoint(ULPOS*pAddress)
{
	if(gpSyser->m_pDebugger->m_ModuleList.GetNearbySymbolAddrress(pAddress))
		return true;
#ifdef CODE_OS_NT_DRV
	if(gpSyser->m_pDebugger == gpSyser->m_pSysDebugger)
		return false;
	return gpSyser->m_pSysDebugger->m_ModuleList.GetNearbySymbolAddrress(pAddress);
#else
	return false;
#endif
}

ULSIZE CSyserCodeDoc::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return ReadImage(Address,Buffer,Size);
}

ULONG CSyserCodeDoc::GetPtrValue(ULONG Address)
{
	ULONG Data=0;
	ReadImage(Address,&Data,sizeof(Data));
	return Data;
}

bool CSyserCodeDoc::GetValue(PCSTR szItem,ULONG*pValue)
{
	CIStrW* ModuleName=NULL;
	if(gpSyser->m_pDebugger==NULL)
		return false;
	if(CExpCalc::GetValue(szItem,pValue))
		return true;
	if(gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
	{
		for(CDbgModuleMap::IT Iter=gpSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.Begin();Iter!=gpSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.End();Iter++)
		{
			if(Iter->GetAddress(szItem,(ULPOS*)pValue))
				return true;
		}
	}
	for(CDbgModuleMap::IT Iter=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();Iter!=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.End();Iter++)
	{
#ifdef CODE_OS_NT_DRV
		if(Iter->m_pSymbolModule==NULL || Iter->m_pSymbolModule->m_ModuleBase)
			continue;
#endif
		if(Iter->GetAddress(szItem,(ULPOS*)pValue))
			return true;
	}
#ifdef CODE_OS_NT_DRV
	for(CSymbolContainer::IT Iter = gpSyser->m_SyserUI.m_SymbolContainer.Begin();Iter.IsExist();Iter++)
	{
		if(Iter->m_ModuleBase==0)
			continue;
		if(Iter->GetAddress(szItem,(ULPOS*)pValue))
			return true;
	}
#endif
	return false;
}

bool CSyserCodeDoc::GetValue(PCWSTR szItem,ULONG*pValue)
{
	CHAR szBuffer[256];
	UnicodeToAnsi(szItem,szBuffer,256);
	return GetValue(szBuffer,pValue);
}

bool CSyserCodeDoc::Open(PCSTR Name)
{
	if(gpSyser->m_pDebugger==NULL || IsOpened())
		return false;
	gpSyser->m_pDebugger->GetX86RegPtr(&m_X86RegPtr);
#ifdef CODE_OS_WIN
	if(gpSyser->m_pDebugger->Open(Name)==false)
		return false;
	gpSyser->m_pSysDebugger = gpSyser->m_pDebugger;
#endif
	CCodeDoc::Open(Name);
	gpSyser->m_SyserUI.m_SyserDI.ResetTrace();
	m_MainModuleName = Name;
	InsertX86RegSym(&m_X86RegPtr);
	InsertPtrSym("OPCODE" ,&m_EIPOpcode,1);
	InsertPtrSym("OPCODE2",&m_EIPOpcode,2);
	InsertPtrSym("OPCODE3",&m_EIPOpcode,3);
	InsertPtrSym("OPCODE4",&m_EIPOpcode,4);
	InsertPtrSym("PID",&m_PopPID,4);
	InsertPtrSym("TID",&m_PopTID,4);
	InsertPtrSym("BPCOUNT",&m_BPCount,4);
	
	for(CPluginMap::IT Iter = gpSyser->m_PluginMap.Begin();Iter!=gpSyser->m_PluginMap.End();Iter++)
	{
		if(Iter->fpOnDebuggerOpen)
			Iter->fpOnDebuggerOpen();
	}
#ifdef CODE_OS_WIN
	gpSyser->m_MainFrame.m_SystemExplorer.UpdateItemState();
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
	UPDATE_CONTEXT();
	UPDATE_SOURCE_CODE_VIEW();
	gpSyser->InsertHistroy(Name,0);
#endif
	return true;
}

void CSyserCodeDoc::Close()
{
	if(IsOpened()==false)
		return;
	for(CPluginMap::IT Iter = gpSyser->m_PluginMap.Begin();Iter!=gpSyser->m_PluginMap.End();Iter++)
	{
		if(Iter->fpOnDebuggerClose)
			Iter->fpOnDebuggerClose();
	}
#ifdef CODE_OS_WIN
	if(gpSyser->m_pDebugger)
		gpSyser->m_pDebugger->Close();
	CSDSModuleMap::IT SDSIter,RemoveIter;
	SDSIter = gpSyser->m_SyserUI.m_SDSModuleMap.Begin();
	while(SDSIter!=gpSyser->m_SyserUI.m_SDSModuleMap.End())
	{
		RemoveIter = SDSIter;
		SDSIter++;
		gpSyser->m_SyserUI.UnloadSDSModule(&(*RemoveIter));
	}
#endif
	ClearAllSym();
	CCodeDoc::Close();
#ifdef CODE_OS_WIN
	if(gpSyser->m_bActive && gpSyser->m_MainFrame.IsWindow())
	{
		gpSyser->m_MainFrame.m_SystemExplorer.ResetContext();
		gpSyser->m_MainFrame.m_SystemExplorer.UpdateItemState();
		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
		gpSyser->m_MainFrame.UpdateClient();
	}
#endif
	STZeroMemory(m_X86RegPtr);
	m_MainModuleName.Empty();
}

void CSyserCodeDoc::UpdateEIPOpcode()
{
	if(gpSyser->m_pDebugger->ReadMemory(*X86_REG_PTR.pEIP,&m_EIPOpcode,sizeof(m_EIPOpcode))!=sizeof(m_EIPOpcode))
		m_EIPOpcode = 0xFFFFFFFF;
}
void CSyserCodeDoc::UpdatePID_TID(DWORD PID,DWORD TID)
{
	m_PopPID=PID;
	m_PopTID=TID;
}
void CSyserCodeDoc::GetCurInstrInfo(WCHAR*szInfo)
{
	int n;
	BYTE Buffer[0x100];
	INSTRUCTION_INFORMATION InstrInfo;
	X86_CPU_REG_PTR CPURegPtr;
	DIS_CPU DisCPU;
	if(IsOpened()==false)
		return;
	gpSyser->m_pDebugger->UpdateRegister();
	gpSyser->m_pDebugger->GetX86RegPtr(&CPURegPtr);
	DisCPU.gen_reg[I_EAX].erx = *CPURegPtr.pEAX;
	DisCPU.gen_reg[I_EBX].erx = *CPURegPtr.pEBX;
	DisCPU.gen_reg[I_ECX].erx = *CPURegPtr.pECX;
	DisCPU.gen_reg[I_EDX].erx = *CPURegPtr.pEDX;
	DisCPU.gen_reg[I_ESI].erx = *CPURegPtr.pESI;
	DisCPU.gen_reg[I_EDI].erx = *CPURegPtr.pEDI;
	DisCPU.gen_reg[I_EBP].erx = *CPURegPtr.pEBP;
	DisCPU.gen_reg[I_ESP].erx = *CPURegPtr.pESP;
	DisCPU.Eflags=*(DWORD*)CPURegPtr.pEFL;
	DisCPU.SEG_BASE[I_CS] = 0;
	DisCPU.SEG_BASE[I_DS] = 0;
	DisCPU.SEG_BASE[I_ES] = 0;
	DisCPU.SEG_BASE[I_FS] = 0;;
	DisCPU.SEG_BASE[I_GS] = 0;
	DisCPU.SEG_BASE[I_SS] = 0;
	
	gpSyser->m_pDebugger->GetSegRegBase(*CPURegPtr.pCS,&DisCPU.SEG_BASE[I_CS]);
	gpSyser->m_pDebugger->GetSegRegBase(*CPURegPtr.pDS,&DisCPU.SEG_BASE[I_DS]);
	gpSyser->m_pDebugger->GetSegRegBase(*CPURegPtr.pES,&DisCPU.SEG_BASE[I_ES]);
	gpSyser->m_pDebugger->GetSegRegBase(*CPURegPtr.pFS,&DisCPU.SEG_BASE[I_FS]);
	gpSyser->m_pDebugger->GetSegRegBase(*CPURegPtr.pGS,&DisCPU.SEG_BASE[I_GS]);
	gpSyser->m_pDebugger->GetSegRegBase(*CPURegPtr.pSS,&DisCPU.SEG_BASE[I_SS]);
	
	InstrInfo.CodeBuff = Buffer;
	InstrInfo.CodeMode = gpSyser->m_pDebugger->m_CodeMode;
	InstrInfo.pasm = NULL;
	InstrInfo.eip = *X86_REG_PTR.pEIP ;
	Dasm(&InstrInfo,&DisCPU);
	*szInfo=0;
	for(n=0;n<3;n++)
	{
		if(InstrInfo.op[n].mode == mode_address)
		{			
			HandleAddressOp(&InstrInfo.op[n],szInfo,&InstrInfo);						
			break;
		}
	}
	if(n>=3)
		return;
}

void CSyserCodeDoc::HandleAddressOpForCodeView(ULPOS Address,WISP_COLOR_CHAR* szInfo,int ccLen)
{
	CHAR szSym[MAX_LONG_NAME_LEN];
	WCHAR szBuffer[256];
	DWORD dwAddress;
	int StrType;
	//if(ReadMemory(Address,&dwAddress,sizeof(dwAddress))==sizeof(dwAddress))
	//{
	//	if(AddrToSym(Address,szSym,sizeof(szSym)/sizeof(WCHAR)))
	//	{
	//		ColorStrCat(szInfo,szSym,SC_WHITE,0);
	//	}
	//	else
	//	{
	//		if(GET_STRING_SYM(dwAddress,szBuffer,sizeof(szBuffer)/sizeof(szBuffer[0]),StrType))
	//		{
	//			if(StrType == CT_ASCII)
	//				ColorStrCat(szInfo,szBuffer,SC_BLUE,0);
	//			else if(StrType == CT_UINCODE)
	//				ColorStrCat(szInfo,szBuffer,SC_LIGHT_BROWN,0);
	//			return ;
	//		}
	//	}		
	//}
	if(GET_STRING_SYM(Address,szBuffer,sizeof(szBuffer)/sizeof(szBuffer[0]),StrType))
	{
		if(StrType == CT_ASCII)
			ColorStrCat(szInfo,szBuffer,SC_BLUE,0);
		else if(StrType == CT_UINCODE)
			ColorStrCat(szInfo,szBuffer,SC_LIGHT_BROWN,0);
		return ;
	}
	else
	{
		if(AddrToSym(Address,szSym,sizeof(szSym)/sizeof(WCHAR)))
		{
			ColorStrCat(szInfo,szSym,SC_WHITE,0);
		}
	}	
}

void CSyserCodeDoc::GetCurInstrInfoEx(WISP_COLOR_CHAR*szInfo,int ccLen)
{
	int n;
	BYTE Buffer[0x100];
	INSTRUCTION_INFORMATION InstrInfo;
	X86_CPU_REG_PTR CPURegPtr;
	DIS_CPU DisCPU;
	ULONG uPos;
	if(IsOpened()==false)
		return;
	gpSyser->m_pDebugger->UpdateRegister();
	gpSyser->m_pDebugger->GetX86RegPtr(&CPURegPtr);
	DisCPU.gen_reg[I_EAX].erx = *CPURegPtr.pEAX;
	DisCPU.gen_reg[I_EBX].erx = *CPURegPtr.pEBX;
	DisCPU.gen_reg[I_ECX].erx = *CPURegPtr.pECX;
	DisCPU.gen_reg[I_EDX].erx = *CPURegPtr.pEDX;
	DisCPU.gen_reg[I_ESI].erx = *CPURegPtr.pESI;
	DisCPU.gen_reg[I_EDI].erx = *CPURegPtr.pEDI;
	DisCPU.gen_reg[I_EBP].erx = *CPURegPtr.pEBP;
	DisCPU.gen_reg[I_ESP].erx = *CPURegPtr.pESP;
	DisCPU.Eflags=*(DWORD*)CPURegPtr.pEFL;
	DisCPU.SEG_BASE[I_CS] = 0;
	DisCPU.SEG_BASE[I_DS] = 0;
	DisCPU.SEG_BASE[I_ES] = 0;
	DisCPU.SEG_BASE[I_FS] = 0;
	DisCPU.SEG_BASE[I_GS] = 0;
	DisCPU.SEG_BASE[I_SS] = 0;

	InstrInfo.CodeBuff = Buffer;
	InstrInfo.CodeMode = gpSyser->m_pDebugger->m_CodeMode;
	InstrInfo.pasm = NULL;
	InstrInfo.eip = *X86_REG_PTR.pEIP ;
	Dasm(&InstrInfo,&DisCPU);
	*szInfo=0;
	for(n=0;n<3;n++)
	{
		switch(InstrInfo.op[n].mode)
		{
		case mode_address:
			uPos = (ULONG)InstrInfo.op[n].addr.line_address;
			HandleAddressOpForCodeView(uPos,szInfo,ccLen);
			break;
		case mode_register:
			{
				switch(InstrInfo.op[n].reg.reg_index)
				{
				case 0:
					uPos=*X86_REG_PTR.pEAX;
					break;
				case 1:
					uPos=*X86_REG_PTR.pECX;
					break;
				case 2:
					uPos=*X86_REG_PTR.pEDX;
					break;
				case 3:
					uPos=*X86_REG_PTR.pEBX;
					break;
				case 4:
					uPos=*X86_REG_PTR.pESP;
					break;
				case 5:
					uPos=*X86_REG_PTR.pEBP;
					break;
				case 6:
					uPos=*X86_REG_PTR.pESI;
					break;				
				case 7:
					uPos=*X86_REG_PTR.pEDI;
					break;
				}
				HandleAddressOpForCodeView(uPos,szInfo,ccLen);
			}
			break;
		}
		
	}
	if(n>=3)
		return;
}

ULSIZE CSyserCodeDoc::ReadImage(ULPOS Address,void*Buffer,ULSIZE Size)
{
	ULSIZE RDSize;
	if(!IsOpened())
		return 0;
	RDSize=gpSyser->m_pDebugger->ReadMemory(Address,Buffer,Size);
	if(RDSize==0)
		return 0;
	if(SyserOption.iShowCCByte==0)
	{
		for(ULSIZE n=0;n<Size;n++)
		{
			if(GET_BYTE(Buffer,n)==0xCC)
			{
				BREAK_POINT*pBP=gpSyser->m_pDebugger->GetCodeBP(Address+n);
				if(pBP && pBP->State == BP_STATE_ENABLE)
				{
					PUT_BYTE(Buffer,n,pBP->CodeBackup);
				}
			}
		}
	}
	return RDSize;
}

ULPOS CSyserCodeDoc::GetNextAddress(ULPOS Address,int Count)
{
	int CodeLen;
	if(Count >= 0)
	{
		while(Count>0)
		{
			CodeLen = InstrLen(Address);
			if(CodeLen<=0)
				CodeLen=1;
			Address += CodeLen;
			Count--;
		}
	}
	else
	{
		while(Count<0)
		{
			CodeLen = PrevInstrLen(Address);
			if(CodeLen<=0)
				CodeLen=1;
			Address -= CodeLen;
			Count++;
		}
	}
	return Address;
}

bool CSyserCodeDoc::GetSymbol(ULPOS Address,WCHAR*szSymbol,int BufSize)
{	
	CHAR szBuffer[256];
	if(GETSYM(Address,szBuffer,256)==false)
		return false;
	AnsiToUnicode(szBuffer,szSymbol,BufSize);
	return true;
}

bool CSyserCodeDoc::GetComment(ULPOS Address,WCHAR*szComment,int BufSize)
{
	PCSTR pszCmt;
	if(!IsOpened())
		return false;
	if(pszCmt = gpSyser->m_pDebugger->m_ModuleList.GetComment(Address))
	{
		TStrCpyLimit(szComment,pszCmt,BufSize);
		return true;
	}
	if(gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
	{
		if(pszCmt = gpSyser->m_pSysDebugger->m_ModuleList.GetComment(Address))
		{
			TStrCpyLimit(szComment,pszCmt,BufSize);
			return true;
		}
	}
	return false;
}

bool CSyserCodeDoc::SetComment(ULPOS Address,WCHAR*szComment)
{
	if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE))
	{
		DbgPrint("Syser : Not enough memory to in symbol heap , please enlarge it in option!\n");
		return false;
	}
	if(!IsOpened())
		return false;
	char szBuffer[MAX_CMT_LEN];
	CCommentModule*pCmtMod;
	CDbgModule*pDbgModule = gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
	if(pDbgModule==NULL)
		return false;
	if(pDbgModule->m_pCommentModule==NULL)
	{
		pCmtMod = gpSyser->m_SyserUI.m_CommentContainer.GetCommentModule(pDbgModule->m_ModuleID);
		if(pCmtMod==NULL)
		{
			pCmtMod = gpSyser->m_SyserUI.m_CommentContainer.InsertCommentModule(pDbgModule->m_ModuleID);
			if(pCmtMod==NULL)
				return false;
			pCmtMod->m_ModuleName = pDbgModule->m_ModuleFullName;
			gpSyser->m_SyserUI.AttachCommentModuleToProcess(pCmtMod);
		}
	}
	UnicodeToAnsi(szComment,szBuffer,MAX_CMT_LEN);
	if(pDbgModule->m_pCommentModule)
		return pDbgModule->m_pCommentModule->SetComment(Address-pDbgModule->m_ModuleBase,szBuffer);
	else
		return NULL;
}


bool CSyserCodeDoc::SetSymbol(ULPOS Address,WCHAR*szSymbol)
{
	if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE))
	{
		DbgPrint("Syser : Not enough memory to in symbol heap , please enlarge it in option!\n");
		return false;
	}
	if(!IsOpened())
		return false;
	char szBuffer[MAX_SYMBOL_LEN];
	CSymbolModule*pSymbolModule;
	CDbgModule*pDbgModule = gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
	if(pDbgModule==NULL)
		return false;
	if(pDbgModule->m_pSymbolModule==NULL)
	{
		pSymbolModule = gpSyser->m_SyserUI.m_SymbolContainer.GetSymbolModule(pDbgModule->m_ModuleID);
		if(pSymbolModule==NULL)
		{
			pSymbolModule = gpSyser->m_SyserUI.m_SymbolContainer.InsertSymbolModule(pDbgModule->m_ModuleID);
			if(pSymbolModule==NULL)
				return false;
			pSymbolModule->m_ModuleName = pDbgModule->m_ModuleFullName;
			gpSyser->m_SyserUI.AttachSymbolModuleToProcess(pSymbolModule);
		}
	}
	UnicodeToAnsi(szSymbol,szBuffer,MAX_SYMBOL_LEN);
	if(pDbgModule->m_pSymbolModule)
		return pDbgModule->m_pSymbolModule->SetSymbol(Address-pDbgModule->m_ModuleBase,szBuffer);
	else
		return NULL;
}

void CSyserCodeDoc::InsertX86RegSym(X86_CPU_REG_PTR*pRegPtr)
{
	InsertPtrSym("CR2",pRegPtr->pCR2,4);
	InsertPtrSym("EAX",pRegPtr->pEAX,4);
	InsertPtrSym("EBX",pRegPtr->pEBX,4);
	InsertPtrSym("ECX",pRegPtr->pECX,4);
	InsertPtrSym("EDX",pRegPtr->pEDX,4);
	InsertPtrSym("EBP",pRegPtr->pEBP,4);
	InsertPtrSym("ESP",pRegPtr->pESP,4);
	InsertPtrSym("ESI",pRegPtr->pESI,4);
	InsertPtrSym("EDI",pRegPtr->pEDI,4);
	InsertPtrSym("EIP",pRegPtr->pEIP,4);
	InsertPtrSym("EFLAG",pRegPtr->pEFL,4);
	InsertPtrSym("EFL",pRegPtr->pEFL,4);

	InsertPtrSym("AX",pRegPtr->pEAX,2);
	InsertPtrSym("BX",pRegPtr->pEBX,2);
	InsertPtrSym("CX",pRegPtr->pECX,2);
	InsertPtrSym("DX",pRegPtr->pEDX,2);
	InsertPtrSym("BP",pRegPtr->pEBP,2);
	InsertPtrSym("SP",pRegPtr->pESP,2);
	InsertPtrSym("SI",pRegPtr->pESI,2);
	InsertPtrSym("DI",pRegPtr->pEDI,2);
	InsertPtrSym("IP",pRegPtr->pEIP,2);

	InsertPtrSym("AH",RT_PVOID(pRegPtr->pEAX,1),1);
	InsertPtrSym("BH",RT_PVOID(pRegPtr->pEBX,1),1);
	InsertPtrSym("CH",RT_PVOID(pRegPtr->pECX,1),1);
	InsertPtrSym("DH",RT_PVOID(pRegPtr->pEDX,1),1);

	InsertPtrSym("AL",pRegPtr->pEAX,1);
	InsertPtrSym("BL",pRegPtr->pEBX,1);
	InsertPtrSym("CL",pRegPtr->pECX,1);
	InsertPtrSym("DL",pRegPtr->pEDX,1);
}

UINT CSyserCodeDoc::GetLineMark(ULPOS Address)
{
	BREAK_POINT*pBP;
	UINT Mark = CV_MARK_NULL;
	if(!IsOpened())
		return CV_MARK_NULL;
	pBP = gpSyser->m_pDebugger->GetCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
	if(pBP)
	{
		if(pBP->State == BP_STATE_ENABLE || pBP->State == BP_STATE_RECOV)
			Mark|=CV_MARK_BPX;
		else if(pBP->State == BP_STATE_DISABLE)
			Mark|=CV_MARK_DISABLED_BPX;
	}
	else 
	{
		CModuleBPMap::IT Iter = gpSyser->m_SyserUI.m_ModuleBPMap.Find(Address);
		if(Iter.IsExist())
		{
			if(Iter->State == BP_STATE_ENABLE)
				Mark|=CV_MARK_BPX;
			else
				Mark|=CV_MARK_DISABLED_BPX;
		}
	}
	if(Address == *X86_REG_PTR.pEIP)
		Mark|=CV_MARK_EIP;
	if(gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.IsBookMark(Address))
		Mark|=CV_MARK_BOOK_MARK;
	return Mark;
}

bool CSyserCodeDoc::IsExecutePointVisible(ULPOS Address,ULSIZE Size)
{
	int Len;
	ULPOS Off=0;
	while(Off<Size)
	{
		if(Address+Off == *X86_REG_PTR.pEIP)
			return true;
		Len=InstrLen(Address+Off);
		if(Len==0)
			Len=1;
		Off+=Len;
	}
	return false;
}

PCSTR szPublicModuleName[]=
{
	"kernel32.dll",
	"user32.dll",
	"gdi32.dll",
	"advapi32.dll",
	"ws2_32.dll",
	NULL
};

CSyserUI::CSyserUI()
{
	m_SyserDI.m_pCodeDoc = &m_CodeDoc;
	m_SyserDI.m_pCommentContainer = &m_CommentContainer;
	m_SyserDI.m_pSymbolContainer = &m_SymbolContainer;
}

CSyserUI::~CSyserUI()
{

}

#ifdef CODE_OS_WIN

bool CSyserUI::ToggleCodeBP(ULPOS Address)
{
	bool Result;
	BREAK_POINT*pBP = gpSyser->m_pDebugger->GetCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_PATCH|BP_TYPE_DEBUG);
	if(pBP)
		Result = gpSyser->m_pDebugger->RemoveCodeBP(pBP);
	else
		Result = gpSyser->m_pDebugger->InsertCodeBP(Address,0,BP_STATE_ENABLE)!=0;
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	UPDATE_BP_FORM();
	return Result;
}


bool CSyserUI::ToggleCodeBPState(ULPOS Address)
{
	bool Result;
	BREAK_POINT*pBP;
	Result = false;
	pBP = gpSyser->m_pDebugger->GetCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_PATCH|BP_TYPE_DEBUG);
	if(pBP)
	{
		if(pBP->State==BP_STATE_ENABLE)
			Result = gpSyser->m_pDebugger->DisableCodeBP(pBP);
		else 
			Result = gpSyser->m_pDebugger->EnableCodeBP(pBP);
	}
	return Result;
}

bool CSyserUI::InsertCodeBP(ULPOS Address,PCSTR Name,PCSTR Contidion,PCSTR DoCmd)
{
	BREAK_POINT*pBP;
	pBP = gpSyser->m_pDebugger->InsertCodeBP(Address,0,BP_STATE_ENABLE);
	if(pBP==NULL)
		return false;
	if(Contidion && *Contidion)
		pBP->Condition = Contidion;
	if(Name && *Name)
		pBP->Name = Name;
	if(DoCmd && *DoCmd)
		pBP->DoCmd = DoCmd;
	return true;
}

bool CSyserUI::RemoveCodeBP(ULPOS Address)
{
	return gpSyser->m_pDebugger->RemoveCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
}

void CSyserUI::EnableAllModuleBP(bool bEnable)
{
}

bool CSyserUI::EnableModuleBP(ULPOS Address,bool bEnable)
{
	return false;
}

#endif


#ifdef CODE_OS_NT_DRV

bool CSyserUI::ToggleCodeBP(ULPOS Address)
{
	bool Result;
	if(IsPublicBP(Address)==false)
	{
		BREAK_POINT*pBP = gpSyser->m_pDebugger->GetCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_PATCH|BP_TYPE_DEBUG);
		if(pBP)
			Result = gpSyser->m_pDebugger->RemoveCodeBP(pBP);
		else
			Result = gpSyser->m_pDebugger->InsertCodeBP(Address,0,BP_STATE_ENABLE)!=0;
	}
	else
	{
		CModuleBPMap::IT ModBPIter=gpSyser->m_SyserUI.m_ModuleBPMap.Find(Address);
		if(ModBPIter.IsExist())
		{
			Result = RemoveCodeBP(Address);
		}
		else
		{
			Result = InsertCodeBP(Address);
		}
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	UPDATE_BP_FORM();
	return Result;
}

bool CSyserUI::ToggleCodeBPState(ULPOS Address)
{
	bool Result;
	BREAK_POINT*pBP;
	Result = false;
	if(IsPublicBP(Address)==false)
	{
		pBP = gpSyser->m_pDebugger->GetCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_PATCH|BP_TYPE_DEBUG);
		if(pBP)
		{
			if(pBP->State==BP_STATE_ENABLE)
				Result = gpSyser->m_pDebugger->DisableCodeBP(pBP);
			else 
				Result = gpSyser->m_pDebugger->EnableCodeBP(pBP);
		}
	}
	else
	{
		CModuleBPMap::IT ModBPIter=gpSyser->m_SyserUI.m_ModuleBPMap.Find(Address);
		if(ModBPIter.IsExist())
		{
			for(CProcMap::IT ProcIter=gpSyser->m_SysInfo.m_ProcMap.Begin();ProcIter.IsExist();ProcIter++)
			{
				if(ModBPIter->State==BP_STATE_ENABLE)
					ProcIter->DisableCodeBP(Address);
				else
					ProcIter->EnableCodeBP(Address);
			}
			Result = true;
			ModBPIter->State = ModBPIter->State == BP_STATE_ENABLE?BP_STATE_DISABLE:BP_STATE_ENABLE;
		}
	}
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	UPDATE_BP_FORM();
	return Result;
}

bool CSyserUI::InsertCodeBP(ULPOS Address,PCSTR Name,PCSTR Contidion,PCSTR DoCmd)
{
	BREAK_POINT*pBP;
	CHAR szModuleName[MAX_FN_LEN];
	if(IsPublicBP(Address,szModuleName)==false)
	{
		if(Address >= gpSyser->m_SysInfo.m_SyserBase && Address < gpSyser->m_SysInfo.m_SyserHighBase)
			return false;
		pBP = gpSyser->m_pDebugger->InsertCodeBP(Address,0,BP_STATE_ENABLE);
		if(pBP==NULL)
			return false;
		if(Contidion && *Contidion)
			pBP->Condition = Contidion;
		if(Name && *Name)
			pBP->Name = Name;
		if(DoCmd && *DoCmd)
			pBP->DoCmd = DoCmd;
	}
	else
	{
		CModuleBPMap::IT ModBPIter=gpSyser->m_SyserUI.m_ModuleBPMap.InsertUnique(Address);
		if(ModBPIter.IsExist()==false)
			return false;
		ModBPIter->ModuleFileName = szModuleName;
		ModBPIter->State = BP_STATE_ENABLE;
		if(Contidion && *Contidion)
			ModBPIter->Condition = Contidion;
		if(Name && *Name)
		{
			ModBPIter->Name = Name;
		}
		else
		{
			char szSymbol[256];
			if(GetAlmostSym(Address,szSymbol))
				ModBPIter->Name = szSymbol;
		}
		if(DoCmd && *DoCmd)
			ModBPIter->DoCmd = DoCmd;
		for(CProcMap::IT ProcIter=gpSyser->m_SysInfo.m_ProcMap.Begin();ProcIter.IsExist();ProcIter++)
		{
			pBP = ProcIter->InsertCodeBP(Address,0,BP_STATE_ENABLE);
			if(pBP)
			{
				pBP->Name = ModBPIter->Name;
				pBP->Condition = ModBPIter->Condition;
				pBP->DoCmd = ModBPIter->DoCmd;
				pBP->pModuleBP = &(*ModBPIter);
			}
		}
	}
	return true;
}

bool CSyserUI::RemoveCodeBP(ULPOS Address)
{
	BREAK_POINT*pBP;
	CHAR szModuleName[MAX_FN_LEN];
	if(IsPublicBP(Address,szModuleName)==false)
	{
		return gpSyser->m_pDebugger->RemoveCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
	}
	else
	{
		CModuleBPMap::IT ModBPIter=gpSyser->m_SyserUI.m_ModuleBPMap.Find(Address);
		if(ModBPIter.IsExist()==false)
			return false;
		gpSyser->m_SyserUI.m_ModuleBPMap.Remove(ModBPIter);
		for(CProcMap::IT ProcIter=gpSyser->m_SysInfo.m_ProcMap.Begin();ProcIter.IsExist();ProcIter++)
		{
			ProcIter->RemoveCodeBP(Address,BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		}
	}
	return true;
}

void CSyserUI::EnableAllModuleBP(bool bEnable)
{
	for(CModuleBPMap::IT ModBPIter=m_ModuleBPMap.Begin();ModBPIter.IsExist();ModBPIter++)
	{
		for(CProcMap::IT ProcIter=gpSyser->m_SysInfo.m_ProcMap.Begin();ProcIter.IsExist();ProcIter++)
		{
			if(bEnable)
				ProcIter->EnableCodeBP(ModBPIter.Key(),BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
			else
				ProcIter->DisableCodeBP(ModBPIter.Key(),BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		}
		ModBPIter->State = bEnable?BP_STATE_ENABLE:BP_STATE_DISABLE;
	}
}

bool CSyserUI::EnableModuleBP(ULPOS Address,bool bEnable)
{
	CModuleBPMap::IT ModBPIter=m_ModuleBPMap.Find(Address);
	if(ModBPIter.IsExist()==false)
		return false;
	for(CProcMap::IT ProcIter=gpSyser->m_SysInfo.m_ProcMap.Begin();ProcIter.IsExist();ProcIter++)
	{
		if(bEnable)
			ProcIter->EnableCodeBP(ModBPIter.Key(),BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
		else
			ProcIter->DisableCodeBP(ModBPIter.Key(),BP_TYPE_INC_ALL,BP_TYPE_DEBUG|BP_TYPE_PATCH);
	}
	ModBPIter->State = bEnable?BP_STATE_ENABLE:BP_STATE_DISABLE;
	return true;
}

bool CSyserUI::IsPublicBP(ULPOS Address,PSTR ModuleName)
{
	if(gpSyser->m_pCsrssProcess==NULL)
		return false;
	CDbgModule*pDbgModule = gpSyser->m_pCsrssProcess->GetModule(Address);
	if(pDbgModule==NULL)
		return false;
	for(int n=0;szPublicModuleName[n];n++)
	{
		if(TStrICmp(pDbgModule->m_ModuleName,szPublicModuleName[n])==0)
		{
			if(ModuleName)
				TStrCpy(ModuleName,(PCSTR)pDbgModule->m_ModuleFullName);
			return true;
		}
	}
	return false;
}

void CSyserUI::SetPublicSymbolModuleBase()
{
	CDbgModule*pDbgModule;
	if(gpSyser->m_pCsrssProcess==NULL)
		return;
	for(int n=0;szPublicModuleName[n];n++)
	{
		pDbgModule = gpSyser->m_pCsrssProcess->GetModule(szPublicModuleName[n]);
		if(pDbgModule && pDbgModule->m_pSymbolModule)
		{
			pDbgModule->m_pSymbolModule->m_ModuleBase = pDbgModule->m_ModuleBase;
			pDbgModule->m_pSymbolModule->m_ModuleSize = pDbgModule->m_ModuleSize;
		}
	}
}
#endif


bool CSyserUI::InsertLoadBP(PCSTR ModuleName,UINT Type,BP_STATE State)
{
	CModuleLoadBPMap::IT Iter = m_ModuleLoadBPMap.InsertUnique(ModuleName);
	if(Iter.IsExist()==false)
		return false;
	Iter->Type = Type;
	Iter->State = State;
	return true;
}

bool CSyserUI::RemoveLoadBP(PCSTR ModuleName)
{
	return m_ModuleLoadBPMap.Remove(ModuleName)!=0;
}

void CSyserUI::EnableAllLoadBP(bool bEnable)
{
	for(CModuleLoadBPMap::IT Iter=m_ModuleLoadBPMap.Begin();Iter.IsExist();Iter++)
	{
		if((Iter->Type&(BP_TYPE_DEBUG|BP_TYPE_PATCH))==0)
		{
			Iter->State = bEnable?BP_STATE_ENABLE:BP_STATE_DISABLE;
		}
	}
}

bool CSyserUI::RegisterPluginModule(PCWSTR ModuleName,SYSER_PLUGIN_MODULE*pPluginModule)
{
	CPluginMap::IT Iter = gpSyser->m_PluginMap.InsertUnique(ModuleName,*pPluginModule);
	if(Iter==gpSyser->m_PluginMap.End())
		return false;
	OUTPUT(WSTR("Syser : Register Plugin Module %s (%s)\n"),ModuleName,pPluginModule->PluginInfo);
	return true;
}

bool CSyserUI::UnregisterPluginModule(PCWSTR ModuleName)
{
	CPluginMap::IT Iter = gpSyser->m_PluginMap.Find(ModuleName);
	if(Iter==gpSyser->m_PluginMap.End())
		return false;
	gpSyser->m_PluginMap.Remove(Iter);
	OUTPUT(WSTR("Syser : Unregister Plugin Module %s\n"),ModuleName);
	return true;
}

HANDLE CSyserUI::InsertMenu(void*hParentMenu,const WCHAR*szMenuName,FPMenuProc fpMenuProc)
{
	HANDLE hItem;
	hItem = gpSyser->m_MainFrame.m_SystemExplorer.m_WndMenu.InsertItem(-1,szMenuName,0,0);
	gpSyser->m_MainFrame.m_SystemExplorer.m_WndMenu.SetItemData(hItem,(NUM_PTR)fpMenuProc);
	return hItem;
}

bool CSyserUI::RemoveMenu(HANDLE hMenu)
{
	return true;
}

void CSyserUI::Outputf(PCWSTR szMsg,...)
{
	va_list Next;
	va_start(Next,szMsg);
	gpSyser->m_MainFrame.m_ConsoleWnd.VPrintf(szMsg,Next);
	va_end(Next);
}

void CSyserUI::Output(PCDSTR szMsg)
{
	gpSyser->m_MainFrame.m_ConsoleWnd.Output((WISP_COLOR_CHAR*)szMsg);
}

bool CSyserUI::EnableMenu(HANDLE hMenu,bool bEnable)
{
	return true;
}

void* CSyserUI::GetMainTabWnd()
{
	return &gpSyser->m_MainFrame.m_MainTabWnd;
}

void* CSyserUI::GetMainMenu()
{
	return &gpSyser->m_MainFrame.m_SystemExplorer.m_WndMenu;
}

void* CSyserUI::GetWisp()
{
	return gpCurWisp;
}

bool CSyserUI::InsertCmd(PCWSTR szCmd,FPCmd pCmdProc,void*pUserData,PCWSTR pComment,PCWSTR pUsage)
{
	return gpSyser->m_MainFrame.m_ConsoleWnd.InsertCmd(szCmd,(CMDPROC)pCmdProc,pUserData,pComment,pUsage);
}

void CSyserUI::RemoveCmd(PCWSTR szCmd)
{
	gpSyser->m_MainFrame.m_ConsoleWnd.RemoveCmd(szCmd);
}

int CSyserUI::RunCmd(PCWSTR szCmd)
{
	return RUNCMD(szCmd);
}

bool CSyserUI::CalcExp(const CHAR*szExp,ULONG*pResult)
{
	return m_CodeDoc.CalcExp(szExp,(ULONG*)pResult);
}

bool CSyserUI::CalcExp(const WCHAR*szExp,ULONG*pResult)
{
	CHAR szBuffer[256];
	if(szExp==NULL)
		return false;
	UnicodeToAnsi(szExp,szBuffer,256);
	return m_CodeDoc.CalcExp(szBuffer,(ULONG*)pResult);
}

bool CSyserUI::SegmentFilter(const WCHAR*szExp,DWORD*pResult)
{
	return CalcExp(szExp,pResult);
}

bool CSyserUI::GetSegmentBaseAddress(const WCHAR* pStr,OUT WCHAR* pOutStr,OUT DWORD* SegmentBaseAddres,OUT DWORD* SegmentLimit)
{
	int Len,i,j,k;
	int PrevEnd=0;
	char DigBuf[9];
	DWORD SegmentSelector;
	WCHAR *pSegment=NULL;
	Len=TStrLen(pStr);
	for(i = 1; i < Len;i++)
	{
		if(pStr[i]!=':')
			continue;
		if(i-PrevEnd>=2)
		{
			if(pStr[i-1]=='s'||pStr[i-1]=='S')
			{
				switch(pStr[i-2]) {
				case 'c':case 'C':case 'd':case 'D':case 'e':case 'E':
				case 'f':case 'F':case 'g':case 'G':case 's':case 'S':
					break;
				default:
					break;
				}
			}
			else
			{
				for(k = 0,j = i-1;j>=PrevEnd;j--,k++)
				{
					if((pStr[j]>='0'&& pStr[j]<='9')||(pStr[j]>='a'&&pStr[j]<='f')||(pStr[j]>='A'&&pStr[j]<='F'))
						continue;
					break;
				}
				if(k&&k<9)
				{
					TStrNCpy(DigBuf,&pStr[j+1],k+1);
					SegmentSelector=0;
					USHexStrToNum(DigBuf,&SegmentSelector);
				}
			}
		}
	}
	return true;
}

bool CSyserUI::GetSym(ULPOS Address,PSTR szSym,int MaxLength)
{
	PCSTR pszSym;
	if(gpSyser->m_pDebugger==NULL)
		return NULL;
	if(SyserOption.iShowFullSym)
	{
		if(gpSyser->m_pDebugger->m_ModuleList.GetFullSymbol(Address,szSym,MaxLength))
			return true;
		if(gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger && gpSyser->m_pSysDebugger->m_ModuleList.GetFullSymbol(Address,szSym,MaxLength))
			return true;
		//公用模块符号全局可见
		if(gpSyser->m_SyserUI.m_SymbolContainer.GetFullSymbol(Address,szSym,MaxLength))
			return true;
	}
	else
	{
		if(pszSym = gpSyser->m_pDebugger->m_ModuleList.GetSymbol(Address))
		{
			TStrCpyLimit(szSym,pszSym,MaxLength);
			return true;
		}
		if(gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger && gpSyser->m_pSysDebugger)
		{
			if(pszSym = gpSyser->m_pSysDebugger->m_ModuleList.GetSymbol(Address))
			{
				TStrCpyLimit(szSym,pszSym,MaxLength);
				return true;
			}
		}
		//公用模块符号全局可见
		if(pszSym = gpSyser->m_SyserUI.m_SymbolContainer.GetSymbol(Address))
		{
			TStrCpyLimit(szSym,pszSym,MaxLength);
			return true;
		}
	}
	return false;
}
bool CSyserUI::GetString(ULPOS Address, WCHAR* szBuffer,int ccLen,int& type)
{
	char Buffer[256];
	if(IsUNICODEString(Address,szBuffer,ccLen)==true)
	{
		type=1;
		return true;
	}
	if(IsASCIIString(Address,Buffer,sizeof(Buffer))==false)
		return false;		 
	TStrCpyLimit(szBuffer,Buffer,ccLen);
	AnsiToUnicode((const char*)Buffer,szBuffer,ccLen);
	type=0;
	return true;
}
bool CSyserUI::IsASCIIString(ULPOS Address,PSTR szBuffer,int ccLen)
{
	CFindString FindString;
	BYTE InBuffer[256];
	BYTE OutBuffer[256];
	ULSIZE Size;
	int OutLen;
	Size = m_CodeDoc.ReadMemory(Address,InBuffer,sizeof(InBuffer));
	if(Size<10)
		return false;
	if(FindString.GetString(InBuffer,Size,(BYTE*)OutBuffer,sizeof(OutBuffer),&OutLen))
	{		
		Size = TStrCpy(szBuffer,"ASCII \"");
		TStrCpyLimit(szBuffer+Size,OutBuffer,ccLen-Size-1);
		TStrCat(szBuffer,"\"");
		return true;
	}
	return false;
}

bool CSyserUI::IsUNICODEString(ULPOS Address,WCHAR* szBuffer,int ccLen)
{
	CFindString FindString;
	BYTE InBuffer[256];
	WCHAR OutBuffer[256];
	ULSIZE Size;
	int OutLen;
	Size = m_CodeDoc.ReadMemory(Address,InBuffer,sizeof(InBuffer));
	if(Size<10)
		return false;
	if(FindString.GetUnicodeString(InBuffer,Size,(BYTE*)OutBuffer,sizeof(OutBuffer),&OutLen))
	{		
		Size = TStrCpy(szBuffer,"UNICODE \"");
		TStrCpyLimit(szBuffer+Size,OutBuffer,ccLen-Size-1);
		TStrCat(szBuffer,"\"");
		return true;
	}
	return false;
}

bool CSyserUI::GetAlmostSym(ULPOS Address,PSTR szSym)
{
	CHAR szBuffer[256];
	ULPOS AlmostAddress = Address;
	*szSym=0;
	if(gpSyser->m_pDebugger->m_ModuleList.GetNearbySymbolAddrress(&AlmostAddress)==false)
	{
		if(gpSyser->m_pDebugger == gpSyser->m_pSysDebugger)
			return false;
		if(gpSyser->m_pSysDebugger->m_ModuleList.GetNearbySymbolAddrress(&AlmostAddress)==false)
			return false;
	}
	if(GetSym(AlmostAddress,szBuffer)==false)
		return false;
	if(AlmostAddress==Address)
	{
		TStrCpy(szSym,szBuffer);
	}
	else if(AlmostAddress>Address)
	{
		TSPrintf(szSym,"%s-0x%X",szBuffer,AlmostAddress - Address);
	}
	else
	{
		TSPrintf(szSym,"%s+0x%X",szBuffer,Address - AlmostAddress);
	}
	return true;
}

int CSyserUI::GetFullSymbol(PSTR szPart)
{
	int Length = TStrLen(szPart);

	for(CDbgModuleMap::IT ModeIter=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();ModeIter.IsExist();ModeIter++)
		if(ModeIter->m_pSymbolModule)
			for(CSymbolMap::IT Iter = ModeIter->m_pSymbolModule->m_SymbolMap.Begin();Iter.IsExist();Iter++)
				if(TStrNICmp(szPart,(PCSTR)*Iter,Length)==0)
					return TStrCpyLimit(szPart,(PCSTR)*Iter,MAX_SYMBOL_LEN);

	if(gpSyser->m_pDebugger != gpSyser->m_pSysDebugger)
	for(CDbgModuleMap::IT ModeIter=gpSyser->m_pSysDebugger->m_ModuleList.m_DbgModuleMap.Begin();ModeIter.IsExist();ModeIter++)
		if(ModeIter->m_pSymbolModule)
			for(CSymbolMap::IT Iter = ModeIter->m_pSymbolModule->m_SymbolMap.Begin();Iter.IsExist();Iter++)
				if(TStrNICmp(szPart,(PCSTR)*Iter,Length)==0)
					return TStrCpyLimit(szPart,(PCSTR)*Iter,MAX_SYMBOL_LEN);

	return Length;
}

int CSyserUI::GetInstrLen(DWORD Address)
{
	return m_CodeDoc.InstrLen(Address);
}

void CSyserUI::SetInstrMode(UINT Mode)
{
	return m_CodeDoc.SetMode(Mode);
}

bool CSyserUI::LoadComment()
{
	char szFileName[MAX_FN_LEN];
#ifdef CODE_OS_NT_DRV
	TStrCpy(szFileName,gpSyser->m_SysInfo.m_szSystem32DriversA);
	TStrCat(szFileName,"Syser.cmt");
#else
	GetSystemDirectory(szFileName,MAX_FN_LEN);
	TStrCat(szFileName,"\\drivers\\Syser.cmt");
#endif
	CImageFileStream File;
	if(File.Open(szFileName)==false)
		return false;
	CCommentContainer::IT DelIter,Iter;
	Iter = m_CommentContainer.Begin();
	while(Iter!=m_CommentContainer.End())
	{
		DelIter=Iter;
		Iter++;
		DetachCommentModuleToProcess(&(*DelIter));		
	}
	m_CommentContainer.Load(File);
	File.Close();
	for(CCommentContainer::IT Iter=m_CommentContainer.Begin();Iter!=m_CommentContainer.End();Iter++)
	{
		AttachCommentModuleToProcess(&(*Iter));
		Iter->m_ReferenceCount++;//引用加1保证驻留
	}
	UPDATE_CODE_VIEW();
	return true;
}

bool CSyserUI::SaveComment()
{
	char szFileName[MAX_FN_LEN];
#ifdef CODE_OS_NT_DRV
	TStrCpy(szFileName,gpSyser->m_SysInfo.m_szSystem32DriversA);
	TStrCat(szFileName,"Syser.cmt");
#else
	GetSystemDirectory(szFileName,MAX_FN_LEN);
	TStrCat(szFileName,"\\drivers\\Syser.cmt");
#endif
	if(m_CommentContainer.Count()==0)
	{
		gpFileIO->DeleteFile(szFileName);
		return true;
	}
	CImageFileStream File;
	if(File.Create(szFileName)==false)
		return false;
	m_CommentContainer.Save(File);
	File.Close();
	for(CCommentContainer::IT Iter=m_CommentContainer.Begin();Iter!=m_CommentContainer.End();Iter++)
	{
		Iter->m_ReferenceCount++;//引用加1保证驻留
	}
	return true;
}

int CSyserUI::AttachSymbolModuleToProcess(CSymbolModule*pSymbolModule)
{
	CDbgModule*pDbgModule;
	int Count=0;
#ifdef CODE_OS_NT_DRV
	for(CProcMap::IT Iter=gpSyser->m_SysInfo.m_ProcMap.Begin();Iter!=gpSyser->m_SysInfo.m_ProcMap.End();Iter++)	
	{
		pDbgModule = Iter->m_ModuleList.GetModuleByID(pSymbolModule->m_ModuleID);
		if(pDbgModule && pDbgModule->m_pSymbolModule==NULL)
		{
			pDbgModule->AttachSymbolModule(pSymbolModule);
			Count++;
		}
	}
#else
	pDbgModule = gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(pSymbolModule->m_ModuleID);
	if(pDbgModule && pDbgModule->m_pSymbolModule==NULL)
		pDbgModule->AttachSymbolModule(pSymbolModule);
#endif
	return Count;
}

int CSyserUI::DetachSymbolModuleToProcess(CSymbolModule*pSymbolModule)
{
	int Count=0;
#ifdef CODE_OS_NT_DRV
	for(CProcMap::IT Iter=gpSyser->m_SysInfo.m_ProcMap.Begin();Iter!=gpSyser->m_SysInfo.m_ProcMap.End();Iter++)	
	{
		for(CDbgModuleMap::IT ModIter=Iter->m_ModuleList.m_DbgModuleMap.Begin();ModIter!=Iter->m_ModuleList.m_DbgModuleMap.End();ModIter++)
		{
			if(ModIter->m_pSymbolModule==pSymbolModule)
			{
				ModIter->DetachSymbolModule(&gpSyser->m_SyserUI.m_SymbolContainer);
				Count++;
			}
		}
	}
#else
	for(CDbgModuleMap::IT Iter=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();Iter!=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.End();Iter++)
	{
		if(Iter->m_pSymbolModule==pSymbolModule)
		{
			Iter->DetachSymbolModule(&m_SymbolContainer);
			Count++;
		}
	}
#endif
	return Count;
}


DWORD CSyserUI::WriteMemory(DWORD Address,void*Buffer,DWORD Size)
{
	if(gpSyser == NULL || gpSyser->m_pDebugger == NULL || Size == 0 || Buffer == NULL)
		return 0;
	return gpSyser->m_pDebugger->WriteMemory(Address,Buffer,Size);
}
DWORD CSyserUI::ReadMemory(DWORD Address,void*Buffer,DWORD Size)
{
	if(gpSyser == NULL || gpSyser->m_pDebugger == NULL || Size == 0 || Buffer == NULL)
		return 0;
	return gpSyser->m_pDebugger->ReadMemory(Address,Buffer,Size);
}
int CSyserUI::AttachCommentModuleToProcess(CCommentModule*pCmtMod)
{
	CDbgModule*pDbgModule;
	int Count=0;
#ifdef CODE_OS_NT_DRV
	for(CProcMap::IT Iter=gpSyser->m_SysInfo.m_ProcMap.Begin();Iter!=gpSyser->m_SysInfo.m_ProcMap.End();Iter++)	
	{
		pDbgModule = Iter->m_ModuleList.GetModuleByID(pCmtMod->m_ModuleID);
		if(pDbgModule && pDbgModule->m_pCommentModule==NULL)
		{
			pDbgModule->AttachCommentModule(pCmtMod);
			Count++;
		}
	}
#else
	pDbgModule = gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(pCmtMod->m_ModuleID);
	if(pDbgModule && pDbgModule->m_pCommentModule==NULL)
		pDbgModule->AttachCommentModule(pCmtMod);
#endif
	return Count;
}

int CSyserUI::DetachCommentModuleToProcess(CCommentModule*pCmtMod)
{
	int Count=0;
#ifdef CODE_OS_NT_DRV
	for(CProcMap::IT Iter=gpSyser->m_SysInfo.m_ProcMap.Begin();Iter!=gpSyser->m_SysInfo.m_ProcMap.End();Iter++)	
	{
		for(CDbgModuleMap::IT ModIter=Iter->m_ModuleList.m_DbgModuleMap.Begin();ModIter!=Iter->m_ModuleList.m_DbgModuleMap.End();ModIter++)
		{
			if(ModIter->m_pCommentModule==pCmtMod)
			{
				ModIter->DetachCommentModule(&gpSyser->m_SyserUI.m_CommentContainer);
				Count++;
			}
		}
	}
#else
	for(CDbgModuleMap::IT Iter=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();Iter!=gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.End();Iter++)
	{
		if(Iter->m_pCommentModule==pCmtMod)
		{
			Iter->DetachCommentModule(&m_CommentContainer);
			Count++;
		}
	}
#endif
	return Count;
}
CSymbolModule*CSyserUI::LoadIDAMapFile(PCSTR szIDAMapFile,PCSTR szFileName,CDbgModule*pDbgModule)
{
	MODULE_ID ModuleID;
	CHAR szSym[MAX_FN_LEN];
	CSymbolModule*pSymbolModule;
	if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE))
	{
		DbgPrint("Syser : Not enough memory to in symbol heap , please enlarge it in option!\n");
		return NULL;
	}
	CPEFile PEFile;
	if(PEFile.Open(szFileName)==false)
		return NULL;
	ModuleID = MAKE_MODULE_ID(PEFile.m_PEHead.CheckSum,PEFile.m_PEHead.TimeDateStamp);
	pSymbolModule = m_SymbolContainer.GetSymbolModule(ModuleID);
	if(pSymbolModule==NULL)
	{
		pSymbolModule = m_SymbolContainer.InsertSymbolModule(ModuleID);
		if(pSymbolModule)
			pSymbolModule->m_ModuleName = szFileName;
		if(pDbgModule)
			pDbgModule->AttachSymbolModule(pSymbolModule);
		else
			AttachSymbolModuleToProcess(pSymbolModule);
	}
	CTXTFile TxtFile;
	if(TxtFile.Open(szIDAMapFile)==false)
	{
		PEFile.Close();
		return NULL;
	}
	TTXTStrList::IT BeginIT,EndIT;
	DWORD SectionID;
	DWORD RVA;
	char* c1;
	DWORD SectCount=(DWORD)PEFile.m_SectCount;
	for(BeginIT=TxtFile.m_StrList.Begin(),EndIT=TxtFile.m_StrList.End();BeginIT!=EndIT;BeginIT++)
	{
		c1=*BeginIT;
		while(*c1==' ' || *c1=='\t')c1++;
		if(c1[4]!=':')
			continue;
		c1[4]=0;
		if(SHexStrToNum(c1,&SectionID)==false)
			continue;
		if(SectCount<SectionID)
			continue;
		if(c1[13]=='H' || c1[13]=='h')
			continue;
		c1[13]=0;
		if(SHexStrToNum(&c1[5],&RVA)==false)
			continue;
		if(RVA>PEFile.m_Section[SectionID].VirtualSize)
			continue;
		c1+=14;
		while(*c1==' ' || *c1=='\t')
			c1++;
		RVA+=PEFile.m_Section[SectionID].VirtualAddress;

		//::DbgPrint("Section[%d]=%08x\n",SectionID,PEFile.m_Section[SectionID].VirtualAddress);
		if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE))
		{
			DbgPrint("Syser : Not enough memory to in symbol heap , please enlarge it in option!\n");
			TxtFile.Close();
			PEFile.Close();
			return NULL;
		}
		pSymbolModule->InsertSymbol(RVA,c1);
	}
	TGetFileTitle(szFileName,szSym);
	pSymbolModule->InsertSymbol(0,szSym);
	PEFile.Close();
	TxtFile.Close();
	return pSymbolModule;
}

char* gMFCDllName[][2]=
{
	{"mfc42.dll","mfc42.def"},
	{"mfc70.dll","mfc70.def"},
	{"mfc71.dll","mfc71.def"},
	{"mfc80.dll","mfc80.def"},
	{"mfc90.dll","mfc90.def"},
	{"mfc42d.dll","mfc42d.def"},
	{"mfc70d.dll","mfc70d.def"},
	{"mfc71d.dll","mfc71d.def"},
	{"mfc80d.dll","mfc80d.def"},
	{"mfc90d.dll","mfc90d.def"},
	{"mfc42u.dll","mfc42u.def"},
	{"mfc70u.dll","mfc70u.def"},
	{"mfc71u.dll","mfc71u.def"},
	{"mfc80u.dll","mfc80u.def"},
	{"mfc90u.dll","mfc90u.def"},
	{"mfc42ud.dll","mfc42ud.def"},
	{"mfc70ud.dll","mfc70ud.def"},
	{"mfc71ud.dll","mfc71ud.def"},
	{"mfc80ud.dll","mfc80ud.def"},
	{"mfc90ud.dll","mfc90ud.def"},
};

char* IsMFCDll(PCSTR szFileName)
{
	int i=0,n;
	n=TStrLen(szFileName);
	if(n>10)
	{
		for(;i<sizeof(gMFCDllName)/sizeof(gMFCDllName[0]);i++)
		{
			if(TStrIStr(szFileName+n-10,gMFCDllName[i][0]))
				return gMFCDllName[i][1];
		}
	}

	return NULL;
}


char* ReadMFCDefFile(char* FileName,int& Length)
{
	CLocalFileIO File;
	HANDLE hFile;
	ULLSIZE Size;
	char* Buf=NULL;
	Length=0;
	if(File.OpenFile(FileName,&hFile))
	{
		Size = File.GetFileLength(hFile);
		if(Size<=0x100000)
		{
			Buf=new char[1+(ULONG)Size];
			if(Buf)
			{
				Length = File.ReadFile(hFile,Buf,(ULSIZE)Size,0);
				if(Length!=Size)
				{
					Length=0;
					delete []Buf;
					Buf=NULL;
				}
			}
		}
		File.CloseHandle(hFile);
	}
	return Buf;
	/*
	WCHAR SystemDriverPath[MAX_FN_LEN]=L"";
	OBJECT_ATTRIBUTES	oa;
	IO_STATUS_BLOCK		IOStatus;
	DWORD OpenMode,ShareMode;
	NTSTATUS Status;
	UNICODE_STRING UniName;
	FILE_STANDARD_INFORMATION StdInfo;
	WCHAR *NameBuf;
	LARGE_INTEGER Offset64;
	DWORD CRCCode;
	HANDLE hFile;
	char* Buf;
	RtlInitUnicodeString(&UniName,FileName);
	InitializeObjectAttributes(&oa,&UniName,OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE,NULL,NULL);
	Status = ZwOpenFile(&hFile,GENERIC_READ,&oa,&IOStatus,FILE_SHARE_READ,FILE_RANDOM_ACCESS|FILE_NON_DIRECTORY_FILE|FILE_SYNCHRONOUS_IO_NONALERT|FILE_COMPLETE_IF_OPLOCKED);
	if(!NT_SUCCESS(Status))
		return NULL;
	Status = ZwQueryInformationFile(hFile,&IOStatus,&StdInfo,sizeof(FILE_STANDARD_INFORMATION),FileStandardInformation);
	if(!NT_SUCCESS(Status))
	{
		ZwClose(hFile);
		return NULL;
	}
	if(StdInfo.EndOfFile.QuadPart>=0x100000)
	{
		ZwClose(hFile);
		return NULL;
	}
	Buf=new char[1+(int)StdInfo.EndOfFile.QuadPart];
	if(Buf==NULL)
	{
		ZwClose(hFile);
		return NULL;
	}
	
	Buf[StdInfo.EndOfFile.QuadPart]=0;		
	Offset64.QuadPart=0;
	Status = ZwReadFile(hFile,NULL,NULL,NULL,&IOStatus,Buf,(int)StdInfo.EndOfFile.QuadPart,&Offset64,NULL);
	ZwClose(hFile);
	if(!NT_SUCCESS(Status))
	{
		delete []Buf;
		return NULL;
	}
	Length=(int)StdInfo.EndOfFile.QuadPart;
	return Buf;
	*/
}
DWORD* InitMFCSym(char* Buf,int BufLen)
{
	DWORD* NameArray=new DWORD[10000];
	DWORD Ord;
	if(NameArray==NULL)
		return NULL;
	memset(NameArray,0,sizeof(DWORD)*10000);
	int i=0,j=0,l;
	for(;i<BufLen;i++)
	{
		if(Buf[i]=='\n')
		{
			Buf[i]=0;
			for(l=j;Buf[l]>='0' && Buf[l]<='9';l++);
			Buf[l]=0;
			l++;
			if(SDecStrToNum(Buf+j,&Ord))
			{				
				for(;Buf[l] && (Buf[l]==' ' || Buf[l]=='\t');l++);
				if(Ord<10000)
				{
					NameArray[Ord]=(DWORD)&Buf[l];
				}
			}
			j=i+1;
		}
	}
	return NameArray;
}
CSymbolModule*CSyserUI::LoadPESym(PCSTR szFileName,CDbgModule*pDbgModule)
{
	MODULE_ID ModuleID;
	CHAR szSym[MAX_FN_LEN];
	CSymbolModule*pSymbolModule;
	if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE))
	{
		DbgPrint("Syser : Not enough memory to in symbol heap , please enlarge it in option!\n");
		return NULL;
	}
	CPEFile PEFile;
	if(PEFile.Open(szFileName)==false)
		return NULL;
	ModuleID = MAKE_MODULE_ID(PEFile.m_PEHead.CheckSum,PEFile.m_PEHead.TimeDateStamp);
	pSymbolModule = m_SymbolContainer.GetSymbolModule(ModuleID);
	if(pSymbolModule==NULL)
	{
		pSymbolModule = m_SymbolContainer.InsertSymbolModule(ModuleID);
		if(pSymbolModule)
			pSymbolModule->m_ModuleName = szFileName;
		if(pDbgModule)
			pDbgModule->AttachSymbolModule(pSymbolModule);
		else
			AttachSymbolModuleToProcess(pSymbolModule);
	}
	char* defname =IsMFCDll(szFileName);
	DWORD* pMFCSym=NULL;
	char* TextBuf=NULL;
	if(defname)
	{
		int BufLen;
		char* DefFileName;
		int nLen=0;
#ifdef CODE_OS_WIN
		char FileName[MAX_PATH];
		GetWindowsDirectory(FileName,sizeof(FileName));
		TStrCat(FileName,"\\system32\\drivers\\plugin\\");
		TStrCat(FileName,defname);
		DefFileName=FileName;
#else
		nLen = TStrLen(gpSyser->m_SysInfo.m_szSystem32DriversA);
		TStrCat(gpSyser->m_SysInfo.m_szSystem32DriversA,"plugin\\");
		TStrCat(gpSyser->m_SysInfo.m_szSystem32DriversA,defname);		
		DefFileName=gpSyser->m_SysInfo.m_szSystem32DriversA;
#endif				
		TextBuf=ReadMFCDefFile(DefFileName,BufLen);		
		if(TextBuf)
		{
			pMFCSym = InitMFCSym(TextBuf,BufLen);
			if(pMFCSym==NULL)
			{
				delete []TextBuf;
				TextBuf=NULL;
			}
		}	
		DefFileName[nLen]=0;
	}
	char* szSymName;
	for(int n=0;n<PEFile.m_ExportFuncCount;n++)
	{
		if(IsHeapFreeBelow(SYSER_MAIN_HEAP,MAIN_HEAP_MIN_FREE_SIZE))
		{
			DbgPrint("Syser : Not enough memory to in symbol heap , please enlarge it in option!\n");
			PEFile.Close();
			return NULL;
		}
		szSymName=PEFile.m_ExportFunc[n].FuncName;
		if(pMFCSym&&PEFile.m_ExportFunc[n].FuncOrd<10000)
		{
			if(pMFCSym[PEFile.m_ExportFunc[n].FuncOrd])
			{
				szSymName=(char*)pMFCSym[PEFile.m_ExportFunc[n].FuncOrd];
			}
		}
		
		pSymbolModule->InsertSymbol(PEFile.m_ExportFunc[n].Address-PEFile.m_ImageBase,szSymName);
	}
	if(pMFCSym)
	{
		delete []pMFCSym;
		delete []TextBuf;
	}
	TGetFileTitle(szFileName,szSym);
	pSymbolModule->InsertSymbol(0,szSym);
	PEFile.Close();
	return pSymbolModule;
}

#ifdef CODE_OS_WIN

int LoadSourceFileCallBack(IN char* OrgFileName,OUT char* NewFileName);

bool CSyserUI::LoadTranslateSDS(PCSTR szFileName,ULPOS ModuleBase,ULSIZE ModuleSize)
{
	char szSymbolFileName[MAX_PATH];
	if(gpSyser->m_SourceDebug.IsTranslated(szFileName,szSymbolFileName)==false)
		if(gpSyser->m_SourceDebug.TranslateSymbolFile(szFileName,szSymbolFileName)==false)
			return false;
	if(gpSyser->m_SyserUI.LoadSDSModule(szSymbolFileName)==NULL)
		return false;
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_MultiSourceCodeView.UpdateAllView();
	return true;
}

#endif

CSDSModule*CSyserUI::GetSDSModule(ULPOS EIP)
{
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(EIP);
	if(pDbgModule==NULL)
	{
		if(gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
			pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModule(EIP);
		if(pDbgModule==NULL)
			return NULL;
	}
	CSDSModuleMap::IT Iter=m_SDSModuleMap.Find(pDbgModule->m_ModuleID);
	if(Iter.IsExist())
	{
		Iter->m_pCurDbgModule = pDbgModule;	
		return &(*Iter);
	}	
	return NULL;
}

bool CSyserUI::IsSDSModuleInProcess(CSDSModule*pSDSModule)
{
	MODULE_ID ModuleID = pSDSModule->GetModuleID();
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(ModuleID);
	if(pDbgModule==NULL)
	{
		if(gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
			pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModuleByID(ModuleID);
		if(pDbgModule==NULL)
		{
			pSDSModule->m_pCurDbgModule = NULL;
			return false;
		}
	}
	pSDSModule->m_pCurDbgModule = pDbgModule;
	return true;
}


CSDSModule*CSyserUI::LoadSDSModule(PCSTR szSymbolModuleFile)
{
	int SymCount,SrcCount;
	MODULE_ID ModuleID;
////////////////////////////////////////////////////////////////////////////////////////////////////////
//堆空间安全检测
#ifdef CODE_OS_NT_DRV
	if(gpUserHeap[SYSER_SOURCE_DEBUG_HEAP]->m_HeapBuffer==NULL)
		gpUserHeap[SYSER_SOURCE_DEBUG_HEAP]->Create(SyserOption.iSourceCodeHeapSizeM*0x100000);
	if(IsHeapFreeBelow(SYSER_SOURCE_DEBUG_HEAP,0x100000))
	{
		DbgPrint("Syser : Not enough memory to in source code heap , please enlarge it in option!\n");
		return NULL;
	}
#endif
//堆空间安全检测
////////////////////////////////////////////////////////////////////////////////////////////////////////
	ModuleID = CSDSModule::GetSDSMouleID(szSymbolModuleFile);
	if(ModuleID==0)
		return NULL;
	SwitchHeap(SYSER_SOURCE_DEBUG_HEAP);
	CSDSModuleMap::IT Iter = m_SDSModuleMap.InsertUnique(ModuleID);
	if(Iter.IsExist()==false)
	{
#ifdef CODE_OS_NT_DRV
		DbgPrint("Syser : Same SDS is already loaded!\n");
#endif
		SwitchHeap(SYSER_MAIN_HEAP);
		return NULL;
	}
#ifdef CODE_OS_NT_DRV
	Iter->m_MemoryUsed = gpUserHeap[SYSER_SOURCE_DEBUG_HEAP]->m_FreeChunkCount*CHUNK_SIZE;
#endif
	if(Iter->LoadSymFile(szSymbolModuleFile)==false)
	{
		DbgPrint("Syser : Fail to load SDS %s\n",szSymbolModuleFile);
		m_SDSModuleMap.Remove(Iter);
		SwitchHeap(SYSER_MAIN_HEAP);
		return NULL;
	}
	Iter->m_ModuleFileName=TGetFileName(Iter->GetPEFileFullName());
	CSymbolModule*pSymbolModule = gpSyser->m_SyserUI.m_SymbolContainer.GetSymbolModule(ModuleID);
	if(pSymbolModule==NULL)
	{
		pSymbolModule = gpSyser->m_SyserUI.m_SymbolContainer.InsertSymbolModule(ModuleID);
		if(pSymbolModule==NULL)
		{
			DbgPrint("Syser : Fail to insert %s Symbol Module\n",szSymbolModuleFile);			
			m_SDSModuleMap.Remove(Iter);
			SwitchHeap(SYSER_MAIN_HEAP);
			return NULL;
		}
		pSymbolModule->m_ModuleName = Iter->m_ModuleFileName;
		gpSyser->m_SyserUI.AttachSymbolModuleToProcess(pSymbolModule);
	}
	SymCount=gpSyser->m_SyserUI.LoadSDSSymbol(&(*Iter));
	SrcCount=Iter->GetSourceFileCountInPackages();
	if(SrcCount==0)
	{//没有源代码文件的SDS只插入符号
		m_SDSModuleMap.Remove(Iter);
		SwitchHeap(SYSER_MAIN_HEAP);
		DbgPrint("Syser : Load SDS %s < %d symbols >\n",TGetFileName(szSymbolModuleFile),SymCount);
		return NULL;
	}
	pSymbolModule->m_ReferenceCount++;//符号模块引用加1
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.InsertSymbolModule(&(*Iter));
#ifdef CODE_OS_NT_DRV
	Iter->m_MemoryUsed -= gpUserHeap[SYSER_SOURCE_DEBUG_HEAP]->m_FreeChunkCount*CHUNK_SIZE;
#endif
	SwitchHeap(SYSER_MAIN_HEAP);
	DbgPrint("Syser : Load SDS %s < %d symbols , %d source code files >\n",TGetFileName(szSymbolModuleFile),SymCount,SrcCount);
	return &(*Iter);
}

bool CSyserUI::UnloadSDSModule(CSDSModule*pSDSModule)
{
	MODULE_ID MID = pSDSModule->GetModuleID();
	CSDSModuleMap::IT Iter=m_SDSModuleMap.Find(MID);
	if(Iter.IsExist()==false)
		return false;
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.RemoveSymbolModule(&(*Iter));//卸载界面SDSModuleList里的数据
	CSymbolModule*pSymbolModule = m_SymbolContainer.GetSymbolModule(MID);
	if(pSymbolModule)//对应的符号模块引用减1
		pSymbolModule->m_ReferenceCount--;
	DbgPrint("Syser : Unload SDS %s\n",TGetFileName((PCSTR)pSDSModule->m_SymbolFileName));
	m_SDSModuleMap.Remove(Iter);
	return true;
}

int CSyserUI::LoadSDSSymbol(CSDSModule*pSDSModule)
{
	int SymCount;
	DWORD Count=0,i;
	PSDUDTDATAITEM pUdtDataItem=NULL;
	PSDFUNCTIONITEM *pFuncItemArray=NULL;
	PSDPUBLICSYMBOL pPublic;
	CSymbolModule*pSymbolModule;
	if(pSDSModule==NULL || pSDSModule->m_SDSymbolFile==NULL)
		return 0;
	pSymbolModule = m_SymbolContainer.GetSymbolModule(pSDSModule->GetModuleID());
	if(pSymbolModule==NULL)//查找对应的符号模块
		return 0;
	SymCount = 0;
	SwitchHeap(SYSER_SOURCE_DEBUG_HEAP);
	pUdtDataItem = pSDSModule->GetDataSymbolList(&Count);
	for(i = 0; i < Count; i++)
	{
		if(pUdtDataItem[i].Location==LocIsStatic)
		{
			if(IsHeapFreeBelow(SYSER_SOURCE_DEBUG_HEAP,HEAP_MIN_FREE_SIZE))
				goto LowMemory;
			pSymbolModule->InsertSymbol(pUdtDataItem[i].u.LOCISSTATIC.Rva,pUdtDataItem[i].uName.Name);
			SymCount++;
		}
	}
	pFuncItemArray = pSDSModule->GetFunctionSymbolList(&Count);	
	for(i = 1; i < Count; i++)
	{
		if(pFuncItemArray[i]->Rva)
		{
			if(IsHeapFreeBelow(SYSER_SOURCE_DEBUG_HEAP,HEAP_MIN_FREE_SIZE))
				goto LowMemory;
			pSymbolModule->InsertSymbol(pFuncItemArray[i]->Rva,pFuncItemArray[i]->uName.Name);
			SymCount++;
		}
	}
	pPublic = pSDSModule->GetPublicSymbolList(&Count);
	for(i = 1; i < Count; i++)
	{
		if(IsHeapFreeBelow(SYSER_SOURCE_DEBUG_HEAP,HEAP_MIN_FREE_SIZE))
			goto LowMemory;
		pSymbolModule->InsertSymbol(pPublic[i].Rva,pPublic[i].uName.Name);
		SymCount++;
	}
	SwitchHeap(SYSER_MAIN_HEAP);
	return SymCount;
LowMemory:
	DbgPrint("Syser : Not enough memory to in source code heap , please enlarge it in option!\n");
	SwitchHeap(SYSER_MAIN_HEAP);
	return SymCount;
}

bool CSyserUI::QuerySDS(PSYSER_QUER_SDS pSyserSDS)
{
	return false;
}

void CSyserUI::LoadAPIDefine()
{
	int LoadSize,FileSize;
	char szFileName[MAX_FN_LEN];
	GetModulePath(szFileName);
	TStrCat(szFileName,"APIDef.lib");
	CImageFileStream FileStream;
	if(FileStream.Open(szFileName))
	{
		LoadSize = m_APIMap.Load(FileStream);
		DbgPrint("Syser : Load API %d records\n",m_APIMap.Count());
		FileSize = FileStream.GetFileLength();
		if(LoadSize!=FileSize)
			DbgPrint("Syser : **********Invalid API Define Data , Load Size [%d] != File Size [%d]**********\n",LoadSize,FileSize);
		FileStream.Close();
	}
	else
	{
		DbgPrint("Syser : Fail to load APIDef %s\n",szFileName);
	}
}

