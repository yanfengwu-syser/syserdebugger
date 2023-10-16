#include "StdAfx.h"
#include "RunTrace.h"
#include "Syser.h"

CRunTrace::CRunTrace()
{
	m_MaxCount = 300;
	m_pRunTrace = new STRUNTRACE[m_MaxCount];
	memset(m_pRunTrace,0,sizeof(STRUNTRACE)*m_MaxCount);
	m_CurIndex=0;
	m_RegisterModifyMap=new DWORD[m_MaxCount];
	memset(m_RegisterModifyMap,0,sizeof(DWORD)*m_MaxCount);
	m_ModifyRegister=new DWORD[m_MaxCount*2];
	memset(m_ModifyRegister,0,sizeof(DWORD)*m_MaxCount*2);
	m_bFirstInsert=true;
	m_CurrentModifyIndex=0;
	m_MoveModifyIndex=0;
	m_FirstRegIndex=0;
	m_FirstRegModifyRegister=0;
}

CRunTrace::~CRunTrace()
{
	delete []m_pRunTrace;
	delete []m_RegisterModifyMap;
	delete []m_ModifyRegister;
	m_RegisterModifyMap=NULL;
	m_ModifyRegister=NULL;
	m_pRunTrace=NULL;
	m_MaxCount=0;
	
}
UINT CRunTrace::GetRunTraceCount()
{
	if(m_Count>m_MaxCount)
		return m_MaxCount;
	return m_Count;
}
UINT CRunTrace::Insert(ULPOS StartAddress,ULPOS EIP,ULPOS CodeViewIndex)
{
	ULPOS Index;
	X86_REG_CONTEXT TempReg;
	DWORD RegModifyMap=0;
	DWORD ModifyIndex=0,MaxIndex=m_MaxCount*2;
	
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return 0;
	if(m_CurIndex>=m_MaxCount)
	{
		HeadNext();
	}
	Index = m_CurIndex % m_MaxCount;
	m_pRunTrace[Index].CodeViewStartAddress=StartAddress;
	m_pRunTrace[Index].EIPOffset = (WORD)(EIP-StartAddress);
	m_pRunTrace[Index].CodeViewIndex =(WORD) CodeViewIndex;
	//OUTPUT(WSTR("insert %08x %08x\n"),StartAddress,EIP);
	if(m_bFirstInsert)
	{
		m_bFirstInsert=false;
#ifdef CODE_OS_WIN
		m_FirstReg.GeneReg[EAX_IDX]=*X86_REG_PTR.pEAX;
		m_FirstReg.GeneReg[ECX_IDX]=*X86_REG_PTR.pECX;
		m_FirstReg.GeneReg[EDX_IDX]=*X86_REG_PTR.pEDX;
		m_FirstReg.GeneReg[EBX_IDX]=*X86_REG_PTR.pEBX;
		m_FirstReg.GeneReg[ESP_IDX]=*X86_REG_PTR.pESP;
		m_FirstReg.GeneReg[EBP_IDX]=*X86_REG_PTR.pEBP;
		m_FirstReg.GeneReg[ESI_IDX]=*X86_REG_PTR.pESI;
		m_FirstReg.GeneReg[EDI_IDX]=*X86_REG_PTR.pEDI;
		m_FirstReg.EIP=*X86_REG_PTR.pEIP;
		m_FirstReg.EFlags=*(DWORD*)X86_REG_PTR.pEFL;
#else
		m_FirstReg=Reg;
#endif
		m_CurrentReg=m_FirstReg;
	}
	else
	{
#ifdef CODE_OS_WIN
		TempReg.GeneReg[EAX_IDX]=*X86_REG_PTR.pEAX;
		TempReg.GeneReg[ECX_IDX]=*X86_REG_PTR.pECX;
		TempReg.GeneReg[EDX_IDX]=*X86_REG_PTR.pEDX;
		TempReg.GeneReg[EBX_IDX]=*X86_REG_PTR.pEBX;
		TempReg.GeneReg[ESP_IDX]=*X86_REG_PTR.pESP;
		TempReg.GeneReg[EBP_IDX]=*X86_REG_PTR.pEBP;
		TempReg.GeneReg[ESI_IDX]=*X86_REG_PTR.pESI;
		TempReg.GeneReg[EDI_IDX]=*X86_REG_PTR.pEDI;
		TempReg.EIP=*X86_REG_PTR.pEIP;
		TempReg.EFlags=*(DWORD*)X86_REG_PTR.pEFL;
#else
		TempReg=Reg;
#endif
		if(TempReg.GeneReg[EAX_IDX]!=m_CurrentReg.GeneReg[EAX_IDX])
		{
			RegModifyMap = RegModifyMap|EAX_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[EAX_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.GeneReg[EBX_IDX]!=m_CurrentReg.GeneReg[EBX_IDX])
		{
			RegModifyMap = RegModifyMap|EBX_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[EBX_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.GeneReg[ECX_IDX]!=m_CurrentReg.GeneReg[ECX_IDX])
		{
			RegModifyMap = RegModifyMap|ECX_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[ECX_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.GeneReg[EDX_IDX]!=m_CurrentReg.GeneReg[EDX_IDX])
		{
			RegModifyMap = RegModifyMap|EDX_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[EDX_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.GeneReg[ESP_IDX]!=m_CurrentReg.GeneReg[ESP_IDX])
		{
			RegModifyMap = RegModifyMap|ESP_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[ESP_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.GeneReg[EBP_IDX]!=m_CurrentReg.GeneReg[EBP_IDX])
		{
			RegModifyMap = RegModifyMap|EBP_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[EBP_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.GeneReg[ESI_IDX]!=m_CurrentReg.GeneReg[ESI_IDX])
		{
			RegModifyMap = RegModifyMap|ESI_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[ESI_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.GeneReg[EDI_IDX]!=m_CurrentReg.GeneReg[EDI_IDX])
		{
			RegModifyMap = RegModifyMap|EDI_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.GeneReg[EDI_IDX];
			m_CurrentModifyIndex++;
		}
		if(TempReg.EIP!=m_CurrentReg.EIP)
		{
			RegModifyMap = RegModifyMap|EIP_MODIFY_BIT_MASK;			
		}
		if(TempReg.EFlags!=m_CurrentReg.EFlags)
		{
			RegModifyMap = RegModifyMap|EFL_MODIFY_BIT_MASK;
			m_ModifyRegister[m_CurrentModifyIndex%MaxIndex]=TempReg.EFlags;
			m_CurrentModifyIndex++;
		}
		m_CurrentReg = TempReg;
		m_RegisterModifyMap[Index]=RegModifyMap;
	}
	m_CurIndex++;
	m_MoveIndex=m_CurIndex%m_MaxCount;
	m_Count++;
	if(m_Count>m_MaxCount)
		return m_MaxCount;
	return m_Count;
}
int CRunTrace::GetModifyRegisterCount(DWORD RegModifyMask)
{
	int i,Count=0;
	for(i = 0;i<32;i++)
	{
		if(RegModifyMask&1)
			Count++;
		RegModifyMask>>=1;
	}
	return Count;
}
void CRunTrace::GetRegisterContext(DWORD Offset,X86_REG_CONTEXT* pRegContext,DWORD *RegModifyMask)
{
	DWORD RegModifyMap=0;
	DWORD MapIndex,MaxIndex=m_MaxCount*2;
	MapIndex=m_FirstRegModifyRegister;
	DWORD i =0;
	*pRegContext=m_FirstReg;
	if(Offset==0)
	{
		if(RegModifyMask)
			*RegModifyMask = m_RegisterModifyMap[(m_FirstRegModifyRegister+i)%m_MaxCount];
		return;
	}
	for(i = 1; i <= Offset;i++)
	{
		RegModifyMap = m_RegisterModifyMap[(m_FirstRegModifyRegister+i)%m_MaxCount];
		if(RegModifyMap==0)
			continue;
		if(RegModifyMap&EAX_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[EAX_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&EBX_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[EBX_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&ECX_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[ECX_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&EDX_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[EDX_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&ESP_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[ESP_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&EBP_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[EBP_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&ESI_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[ESI_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&EDI_MODIFY_BIT_MASK)
		{
			pRegContext->GeneReg[EDI_IDX]=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
		if(RegModifyMap&EFL_MODIFY_BIT_MASK)
		{
			pRegContext->EFlags=m_ModifyRegister[MapIndex%MaxIndex];
			MapIndex++;
		}
	}
	if(RegModifyMask)
		*RegModifyMask=RegModifyMap;
}
void CRunTrace::HeadNext()
{
	DWORD RegModifyMask;
	X86_REG_CONTEXT	 NewFirstReg;
	GetRegisterContext(1,&NewFirstReg,&RegModifyMask); 
	m_FirstRegIndex++;
	m_FirstRegIndex=m_FirstRegIndex%m_MaxCount;
	m_FirstRegModifyRegister+=GetModifyRegisterCount(m_RegisterModifyMap[m_FirstRegIndex]);
	m_FirstReg=NewFirstReg;
	
}
void CRunTrace::Clear()
{
	m_CurIndex=0;
	m_Count;
}
PSTRUNTRACE CRunTrace::GetNextTrace()
{
	m_MoveIndex++;
	m_MoveIndex%=m_MaxCount;
	if(m_MoveIndex>=m_CurIndex)
	{
		m_MoveIndex=m_CurIndex;
		return NULL;
	}
	return &m_pRunTrace[m_MoveIndex];
}
PSTRUNTRACE CRunTrace::GetPrevTrace()
{
	if(m_MoveIndex==0)
	{
		return m_pRunTrace;
	}
	m_MoveIndex--;
	return &m_pRunTrace[m_MoveIndex];
}

PSTRUNTRACE CRunTrace::GetTraceByIndex(DWORD Index)
{
	if(Index>=m_MaxCount||Index>=m_CurIndex)
		return NULL;
	return &m_pRunTrace[(m_FirstRegIndex+Index)%m_MaxCount];
}