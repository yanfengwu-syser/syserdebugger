#include "StdAfx.h"
#include "Debugger.h"

#define MAX_CONDITION_INSTR_COUNT	0x100000


bool IsTypeMatched(UINT TypeInc,UINT TypeExc,BREAK_POINT&BP)
{
	if(TypeInc & BP_TYPE_FULL_CMP)
	{
		TypeInc&=~BP_TYPE_FULL_CMP;
		if((BP.Type&TypeInc)!=TypeInc)
			return false;
	}
	else
	{
		if(TypeInc && (BP.Type&TypeInc)==0)
			return false;
	}
	if(TypeExc & BP_TYPE_FULL_CMP)
	{
		TypeExc&=~BP_TYPE_FULL_CMP;
		if((BP.Type&TypeExc)==TypeExc)
			return false;
	}
	else
	{
		if(BP.Type & TypeExc)
			return false;
	}
	return true;
}


CDebugger::CDebugger()
{
	m_pCodeBPMap = &m_CodeBPMap;
	m_pDataBPList = &m_DataBPList;
}

CDebugger::~CDebugger()
{
}

BREAK_POINT*CDebugger::GetCodeBP(ULPOS Address,UINT TypeInc,UINT TypeExc)
{
	ULONGLONG PhysAddr;
	if(MapToPhysAddr(Address,PhysAddr)==false)
		return NULL;
	CCodeBPMap::IT Iter = m_pCodeBPMap->Find(PhysAddr);
	if(!Iter.IsExist())
		return NULL;
	if(IsTypeMatched(TypeInc,TypeExc,*Iter)==false)
		return NULL;
	return &(*Iter);
}

BREAK_POINT*CDebugger::InsertCodeBP(ULPOS Address,UINT Type,BP_STATE State)
{
	ULONGLONG PhysAddr;
	if(SwitchProcessSpace(m_PID)==false)
	{
		m_LastError = BP_ERROR_SWITCH_PROCESS;
		return NULL;
	}
	if(MapToPhysAddr(Address,PhysAddr)==false)
	{
		RestoreProcessSpace();
		m_LastError = BP_ERROR_MAP_TO_PHYS;
		return NULL;
	}
	CCodeBPMap::IT Iter = m_pCodeBPMap->Find(PhysAddr);
	if(Iter.IsExist())
	{
		RestoreProcessSpace();
		m_LastError = BP_ERROR_BP_EXIST;
		return NULL;
	}
	Iter = m_pCodeBPMap->InsertUnique(PhysAddr);
	Iter->Address = Address;
	Iter->Type = Type;
	Iter->State = BP_STATE_DISABLE;
	Iter->Length = 0;
	Iter->UserData = 0;
	Iter->PID = m_PID;
	Iter->OwnerName = m_ProcName;
	Iter->pModuleBP = NULL;
	Iter->BPCount=0;
	if(State == BP_STATE_ENABLE && SetCodeBreakPoint(*Iter)==false)
	{
		m_pCodeBPMap->Remove(Iter);
		RestoreProcessSpace();
		m_LastError = BP_ERROR_FAIL_TO_SET;
		return NULL;
	}
	Iter->State = State;
	RestoreProcessSpace();
	m_LastError = BP_ERROR_SUCCESS;
	return &(*Iter);
}

bool CDebugger::RemoveCodeBP(ULPOS Address,UINT TypeInc,UINT TypeExc)
{
	ULONGLONG PhysAddr;
	if(SwitchProcessSpace(m_PID)==false)
	{
		RestoreProcessSpace();
		m_LastError = BP_ERROR_SWITCH_PROCESS;
		return false;
	}
	if(MapToPhysAddr(Address,PhysAddr)==false)
	{
		RestoreProcessSpace();
		m_LastError = BP_ERROR_MAP_TO_PHYS;
		return false;
	}
	CCodeBPMap::IT Iter = m_pCodeBPMap->Find(PhysAddr);
	if(!Iter.IsExist())
	{
		RestoreProcessSpace();
		m_LastError = BP_ERROR_BP_NOT_EXIST;
		return false;
	}
	if(!IsTypeMatched(TypeInc,TypeExc,*Iter))
	{
		RestoreProcessSpace();
		return false;
	}
	if(Iter->State == BP_STATE_ENABLE && ClearCodeBreakPoint(*Iter)==false)
	{
		RestoreProcessSpace();
		m_LastError = BP_ERROR_FAIL_TO_CLEAR;
		return false;
	}
	m_pCodeBPMap->Remove(Iter);
	RestoreProcessSpace();
	m_LastError = BP_ERROR_SUCCESS;
	return true;
}

bool CDebugger::RemoveCodeBP(BREAK_POINT*pBP)
{
	CCodeBPMap::IT Iter=*pBP;
	ULONGLONG PhysAddr;
	if(SwitchProcessSpace(pBP->PID)==false)
		return false;
	if(MapToPhysAddr(Iter->Address,PhysAddr)==false || PhysAddr!=Iter.Key())
	{
		RestoreProcessSpace();
		return false;
	}
	if(Iter->State == BP_STATE_ENABLE && ClearCodeBreakPoint(*Iter)==false)
	{
		RestoreProcessSpace();
		return false;
	}
	m_pCodeBPMap->Remove(Iter);
	RestoreProcessSpace();
	return true;
}

int CDebugger::RemoveAllCodeBP(UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CCodeBPMap::IT RemoveIter,Iter;
	Iter=m_pCodeBPMap->Begin();
	while(Iter.IsExist())
	{
		if(IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			RemoveIter = Iter;
			Iter++;
			if(RemoveCodeBP(&(*RemoveIter)))
				Count++;
		}
		else
			Iter++;
	}
	return Count;
}

int CDebugger::EnableAllCodeBP(UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CCodeBPMap::IT Iter;
	Iter=m_pCodeBPMap->Begin();
	while(Iter!=m_pCodeBPMap->End())
	{
		if(IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			if(EnableCodeBP(&(*Iter)))
				Count++;
		}
		Iter++;
	}
	return Count;
}

int CDebugger::DisableAllCodeBP(UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CCodeBPMap::IT Iter;
	Iter=m_pCodeBPMap->Begin();
	while(Iter!=m_pCodeBPMap->End())
	{
		if(IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			if(DisableCodeBP(&(*Iter)))
				Count++;
		}
		Iter++;
	}
	return Count;
}

bool CDebugger::EnableCodeBP(BREAK_POINT*pBP)
{
	if(pBP->State == BP_STATE_ENABLE || pBP->State == BP_STATE_RECOV)
		return true;
	if(SwitchProcessSpace(pBP->PID)==false)
		return false;
	if(SetCodeBreakPoint(*pBP)==false)
	{
		RestoreProcessSpace();
		return false;
	}
	pBP->State = BP_STATE_ENABLE;
	RestoreProcessSpace();
	return true;
}

bool CDebugger::EnableCodeBP(ULPOS Address,UINT TypeInc,UINT TypeExc)
{
	BREAK_POINT*pBP = GetCodeBP(Address,TypeInc,TypeExc);
	if(pBP)
		return EnableCodeBP(pBP);
	return NULL;
}

bool CDebugger::DisableCodeBP(BREAK_POINT*pBP)
{
	if(pBP->State == BP_STATE_DISABLE)
		return true;
	if(pBP->State==BP_STATE_ENABLE)
	{
		if(SwitchProcessSpace(pBP->PID)==false)
			return false;
		if(ClearCodeBreakPoint(*pBP)==false)
		{
			RestoreProcessSpace();
			return false;
		}
		RestoreProcessSpace();
	}
	pBP->State = BP_STATE_DISABLE;
	return true;
}

bool CDebugger::DisableCodeBP(ULPOS Address,UINT TypeInc,UINT TypeExc)
{
	BREAK_POINT*pBP=GetCodeBP(Address,TypeInc,TypeExc);
	if(pBP)
		return DisableCodeBP(pBP);
	return NULL;
}

BREAK_POINT*CDebugger::InsertDataBP(ULPOS Address,UINT Type,BP_STATE State,UINT Length)
{
	CDataBPList::IT Iter = m_pDataBPList->Append();
	Iter->Address = Address;
	Iter->Type = Type;
	Iter->State = BP_STATE_DISABLE;
	Iter->Length = Length;
	Iter->UserData = 0;
	Iter->PID = m_PID;
	Iter->BPCount=0;
	Iter->OwnerName = m_ProcName;
	if(State == BP_STATE_ENABLE && SetDataBreakPoint(*Iter)==false)
	{
		m_pDataBPList->Remove(Iter);
		return NULL;
	}
	Iter->State = State;
	return &(*Iter);
}

int CDebugger::RemoveDataBP(ULPOS Address,UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	for(CDataBPList::IT Iter=m_pDataBPList->Begin();Iter!=m_pDataBPList->End();Iter++)
	{
		if(Iter->Address == Address &&  IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			RemoveDataBP(&(*Iter));
			Count++;
		}
	}
	return Count;
}

bool CDebugger::RemoveDataBP(BREAK_POINT*pBP)
{
	if(pBP->State == BP_STATE_ENABLE)
	{
		if(ClearDataBreakPoint(*pBP)==false)
			return false;
	}
	CDataBPList::IT Iter = *pBP;
	m_pDataBPList->Remove(Iter);
	return true;
}

int CDebugger::RemoveAllDataBP(UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CDataBPList::IT RemoveIter,Iter=m_pDataBPList->Begin();
	while(Iter!=m_pDataBPList->End())
	{
		if(IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			RemoveIter = Iter;
			Iter++;
			if(RemoveDataBP(&(*RemoveIter)))
				Count++;
		}
		else
			Iter++;
	}
	return Count;
}

int CDebugger::EnableAllDataBP(UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CDataBPList::IT Iter=m_pDataBPList->Begin();
	while(Iter!=m_pDataBPList->End())
	{
		if(IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			if(EnableDataBP(&(*Iter)))
				Count++;
		}
		Iter++;
	}
	return Count;
}

int CDebugger::DisableAllDataBP(UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CDataBPList::IT Iter=m_pDataBPList->Begin();
	while(Iter!=m_pDataBPList->End())
	{
		if(IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			if(DisableDataBP(&(*Iter)))
				Count++;
		}
		Iter++;
	}
	return Count;
}

bool CDebugger::EnableDataBP(BREAK_POINT*pBP)
{
	if(pBP->State == BP_STATE_ENABLE || pBP->State == BP_STATE_RECOV)
		return true;
	if(SetDataBreakPoint(*pBP)==false)
		return false;
	pBP->State = BP_STATE_ENABLE;
	return true;
}

int CDebugger::EnableDataBP(ULPOS Address,UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CDataBPList::IT Iter=m_pDataBPList->Begin();
	while(Iter!=m_pDataBPList->End())
	{
		if(Address == Iter->Address && IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			if(EnableDataBP(&(*Iter)))
				Count++;
		}
		Iter++;
	}
	return Count;
}

bool CDebugger::DisableDataBP(BREAK_POINT*pBP)
{
	if(pBP->State == BP_STATE_DISABLE)
		return true;
	if(pBP->State == BP_STATE_ENABLE)
	{
		if(ClearDataBreakPoint(*pBP)==false)
			return false;
	}
	pBP->State = BP_STATE_DISABLE;
	return true;
}

int CDebugger::DisableDataBP(ULPOS Address,UINT TypeInc,UINT TypeExc)
{
	int Count=0;
	CDataBPList::IT Iter=m_pDataBPList->Begin();
	while(Iter!=m_pDataBPList->End())
	{
		if(Address == Iter->Address && IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			if(DisableDataBP(&(*Iter)))
				Count++;
		}
		Iter++;
	}
	return Count;
}


int	CDebugger::GetDataBPList(UINT TypeInc,UINT TypeExc,TList<BREAK_POINT*>*pList)
{
	int Count=0;
	for(CDataBPList::IT Iter=m_pDataBPList->Begin();Iter!=m_pDataBPList->End();Iter++)
	{
		if(IsTypeMatched(TypeInc,TypeExc,*Iter))
		{
			if(pList)
				pList->Append(&(*Iter));
			Count++;
		}
	}
	return Count;
}

ULSIZE CDebugger::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size,void*Param)
{
	return ((CDebugger*)Param)->ReadMemory(Address,Buffer,Size);
}

bool CDebugger::Init(CDebugInterface*pDebugInterface)
{
	m_pDebugInterface=pDebugInterface;
	return true;
}

void CDebugger::Release()
{
	m_pDebugInterface=NULL;
}

bool CDebugger::Open(PCSTR ModuleName)
{
	return true;
}

bool CDebugger::Close()
{
	for(CDbgModuleMap::IT ModIter = m_ModuleList.m_DbgModuleMap.Begin();ModIter!=m_ModuleList.m_DbgModuleMap.End();ModIter++)
	{
		if(ModIter->m_pSymbolModule)
			ModIter->m_pSymbolModule->m_ReferenceCount--;
		if(ModIter->m_pCommentModule)
			ModIter->m_pCommentModule->m_ReferenceCount--;
	}
	if(m_pDebugInterface)
	{
		if(m_pDebugInterface->m_pSymbolContainer)
			m_pDebugInterface->m_pSymbolContainer->RemoveUnusedSymbolModule();
		if(m_pDebugInterface->m_pCommentContainer)
			m_pDebugInterface->m_pCommentContainer->RemoveUnusedCommentModule();
	}
	m_ModuleList.m_DbgModuleMap.Clear();
	m_ProcName.Empty();
	return true;
}

ULSIZE CDebugger::WriteMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return 0;
}

ULSIZE CDebugger::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	return 0;
}

ULSIZE CDebugger::MoveMem(ULPOS DesAddr,ULPOS SrcAddr,ULSIZE Size)
{
	BYTE Buffer[256];
	ULSIZE Length,RDSize = 0;
	while(Size>0)
	{
		Length = Size > sizeof(Buffer) ? sizeof(Buffer) : Size;
		if(ReadMemory(SrcAddr+RDSize,Buffer,Length)!=Length)
			return RDSize;
		if(WriteMemory(DesAddr+RDSize,Buffer,Length)!=Length)
			return RDSize;	
		RDSize+=Length;
		if(Size<Length)
			break;
		Size-=Length;
	}
	return RDSize;
}

ULSIZE CDebugger::CmpMem(ULPOS DesAddr,ULPOS SrcAddr,ULSIZE Size)
{
	ULSIZE n;
	BYTE*SrcBuf,*DesBuf;
	if(Size==0)
		return 0;
	SrcBuf = new BYTE[Size];
	DesBuf = new BYTE[Size];
	n = ReadMemory(SrcAddr,SrcBuf,Size);
	if(n<Size)
		Size=n;
	n = ReadMemory(DesAddr,DesBuf,Size);
	if(n<Size)
		Size=n;
	n = 0;
	while(n<Size && SrcBuf[n] == DesBuf[n])
		n++;
	delete SrcBuf;
	delete DesBuf;
	return n;
}

ULPOS CDebugger::SearchMem(ULPOS Address,ULSIZE Length,BYTE*ByteCode,ULSIZE Size,bool bCase)
{
	BYTE Buffer[0x1000];
	ULPOS RDAddr;
	ULSIZE RDSize,LSize,SectMaxPos=0,SectPos=0;
	if(Size>sizeof(Buffer))
		return -1;
	for(ULPOS Pos=0;Pos<Length-Size;Pos++)
	{
		if(Pos+Size>SectMaxPos)
		{
			LSize=Length-Pos;
			if(LSize>sizeof(Buffer))
				LSize=sizeof(Buffer);
			RDAddr=Address+Pos;
			RDSize=LSize;
			SectPos=Pos;
			RDSize = ReadMemory(RDAddr,Buffer,RDSize);
			if(RDSize==0)
			{
				Pos = (RDAddr&0xFFFFF000)+0x1000;
				Pos -= Address;
				Pos -= 1;
				SectMaxPos=Pos+RDSize;
				continue;
			}
			SectMaxPos=Pos+RDSize;
		}
		if(bCase)
		{
			if(memcmp(&Buffer[Pos-SectPos],ByteCode,Size)==0)
				return Pos+Address;
		}
		else
		{
			if(TMemICmp(&Buffer[Pos-SectPos],ByteCode,Size)==0)
				return Pos+Address;
		}
	}
	return -1;
}

bool CDebugger::SetSingleStep()
{
	return true;
}

bool CDebugger::RemoveSingleStep()
{
	return true;
}

bool CDebugger::UpdateRegister()
{
	return true;
}

bool CDebugger::SaveRegister()
{
	return true;
}

bool CDebugger::SetCodeBreakPoint(BREAK_POINT&BP)
{
	return true;
}

bool CDebugger::ClearCodeBreakPoint(BREAK_POINT&BP)
{
	return true;
}

bool CDebugger::SetDataBreakPoint(BREAK_POINT&BP)
{
	return true;
}

bool CDebugger::ClearDataBreakPoint(BREAK_POINT&BP)
{
	return true;
}

bool CDebugger::MapToPhysAddr(ULPOS Address,ULONGLONG&PhysAddr)
{
	PhysAddr = Address;
	return true;
}

bool CDebugger::SwitchProcessSpace(UINT PID)
{
	return true;
}

void CDebugger::RestoreProcessSpace()
{
}

bool CDebugger::ContinueDebug(bool bRestoreScreen)
{
	return false;
}

CDebugInterface::CDebugInterface()
{
	m_TraceType = TRACE_NULL;
	m_TraceCount = 0;
	m_RangeStart = 0;
	m_RangeEnd = 0;
}

bool CDebugInterface::IsHandledTraceEvent()
{
	ULPOS EIP;
	//char szBuffer[256];
	switch(m_TraceType)
	{
	case TRACE_NULL:
		return true;
	case TRACE_STEP_RANGE_IN:
		EIP =*(GetCurrentDebugger()->m_pExecutePoint);
		if(EIP >= m_RangeStart && EIP < m_RangeEnd)
		{
			ResetTrace();
			return true;
		}
		else
		{
			RunCmd("T");
		}
		break;
	case TRACE_STEP_RANGE_OUT:
		EIP =*(GetCurrentDebugger()->m_pExecutePoint);
		if(EIP < m_RangeStart || EIP >= m_RangeEnd)
		{
			ResetTrace();
			return true;
		}
		else
		{
			RunCmd("T");
		}
		break;
	case TRACE_PROCEED_STEP_RANGE_IN:
		EIP =*(GetCurrentDebugger()->m_pExecutePoint);
		if(EIP >= m_RangeStart && EIP < m_RangeEnd)
		{
			ResetTrace();
			return true;
		}
		else
		{
			RunCmd("P");
		}
		break;
	case TRACE_PROCEED_STEP_RANGE_OUT:
		EIP =*(GetCurrentDebugger()->m_pExecutePoint);
		if(EIP < m_RangeStart || EIP >= m_RangeEnd)
		{
			ResetTrace();
			return true;
		}
		else
		{
			RunCmd("P");
		}
		break;
	case TRACE_STEP_COUNT:
		m_TraceCount--;
		if(m_TraceCount<=0)
		{
			ResetTrace();
			return true;
		}
		else
		{
			RunCmd("T");
		}
		break;
	case TRACE_PROCEED_STEP_COUNT:
		m_TraceCount--;
		if(m_TraceCount<=0)
		{
			ResetTrace();
			return true;
		}
		else
		{
			RunCmd("P");
		}
		break;
	case TRACE_CONDITION:
		UpdateTraceConditionVal();
		if(TestCondition(m_strTraceCondition))
		{
			ResetTrace();
			return true;
		}
		else
		{
			m_TraceCount++;
			if(m_TraceCount>=MAX_CONDITION_INSTR_COUNT)
			{
				ResetTrace();
				return false;
			}
			RunCmd("T");
		}
		break;
	case TRACE_PROCEED_CONDITION:
		UpdateTraceConditionVal();
		if(TestCondition(m_strTraceCondition))
		{
			ResetTrace();
			return true;
		}
		else
		{
			m_TraceCount++;
			if(m_TraceCount>=MAX_CONDITION_INSTR_COUNT)
			{
				ResetTrace();
				return false;
			}
			RunCmd("P");
		}
		break;
	case TRACE_PAGE_RANGE_BREAK:
		return CalcPageRangeCondition();		
	case TRACE_X86_RET_BREAK:
		{
			BYTE Opcode;
			ULPOS EIP =*(GetCurrentDebugger()->m_pExecutePoint);
			if(m_pCodeDoc->ReadImage(EIP,&Opcode,sizeof(Opcode)))
			{
				switch(Opcode)
				{
				case 0xC3://ret	
				case 0xC2://ret imm
				case 0xCB://retf
				case 0xCA://retf imm		
				case 0xCF://iret
					ResetTrace();
					return true;
				}
			}
			m_TraceCount++;
			if(m_TraceCount>=MAX_CONDITION_INSTR_COUNT)
			{
				ResetTrace();
				return false;
			}
			RunCmd("P");
		}
		break;
	case TRACE_RECOVER_BREAK_POINT:
		ResetTrace();
		break;
	}
	return false;
}

void CDebugInterface::SetTraceRange(ULPOS RangeStart,ULPOS RangeEnd,bool bRangeIn)
{
	m_TraceType = bRangeIn ? TRACE_STEP_RANGE_IN : TRACE_STEP_RANGE_OUT;
	m_RangeStart = RangeStart;
	m_RangeEnd = RangeEnd;
}


void CDebugInterface::SetProceedRange(ULPOS RangeStart,ULPOS RangeEnd,bool bRangeIn)
{
	m_TraceType = bRangeIn ? TRACE_PROCEED_STEP_RANGE_IN : TRACE_PROCEED_STEP_RANGE_OUT;
	m_RangeStart = RangeStart;
	m_RangeEnd = RangeEnd;
}

void CDebugInterface::SetTraceCondition(PCSTR szTraceCondition)
{
	m_TraceType = TRACE_CONDITION;
	m_strTraceCondition = szTraceCondition;
	m_TraceCount = 0;
}

void CDebugInterface::SetTraceProceedCondition(PCSTR szTraceCondition)
{
	m_TraceType = TRACE_PROCEED_CONDITION;
	m_strTraceCondition = szTraceCondition;
	m_TraceCount = 0;
}

void CDebugInterface::SetTraceCount(int StepCount)
{
	m_TraceType = TRACE_STEP_COUNT;
	m_TraceCount = StepCount;
}

void CDebugInterface::SetTracePageRangeCondition(DWORD dwPageCR2,DWORD dwPageEIP)
{
	m_TraceType = TRACE_PAGE_RANGE_BREAK;
	m_PageCR2=dwPageCR2;
	m_PageEIP=dwPageEIP;	
}

bool CDebugInterface::CalcPageRangeCondition()
{
	return true;
}

void CDebugInterface::SetProceedCount(int StepCount)
{
	m_TraceType = TRACE_PROCEED_STEP_COUNT;
	m_TraceCount = StepCount;
}

void CDebugInterface::SetX86RetBreak(CDebugger*pDbg)
{
	m_TraceType = TRACE_X86_RET_BREAK;
	m_TraceCount = 0;
	m_TraceDebugger = pDbg;
}

void CDebugInterface::ResetTrace()
{
	m_TraceType = TRACE_NULL;
	m_TraceCount = 0;
	m_RangeStart = m_RangeEnd = 0;
	m_strTraceCondition.Empty();
}

