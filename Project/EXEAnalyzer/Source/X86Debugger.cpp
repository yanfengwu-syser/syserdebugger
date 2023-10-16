#include "StdAfx.h"
#include "X86Debugger.h"

CX86Debugger::CX86Debugger()
{
	m_CodeMode = CODE_MODE_32;
}

CX86Debugger::~CX86Debugger()
{
}

void CX86Debugger::GetX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr)
{
}
void CX86Debugger::GetCPUX86RegPtr(X86_CPU_REG_PTR*pCPURegPtr,DWORD dwCPUID)
{
}

bool CX86Debugger::GetSegRegBase(int SegIndex,DWORD*pAddress,DWORD *pSize)
{
	return false;
}

bool CX86Debugger::SetCCBP(BREAK_POINT&BP)
{
	if(BP.State == BP_STATE_ENABLE)
		return true;
	if(ReadMemory(BP.Address,&BP.CodeBackup,1)==0)
		return false;
	if(BP.CodeBackup==0xCC)
		return false;
	if(WriteMemory(BP.Address,"\xCC",1)==0)
		return false;
	return true;
}

bool CX86Debugger::ClearCCBP(BREAK_POINT&BP)
{
	if(BP.State == BP_STATE_RECOV || BP.State == BP_STATE_DISABLE)
		return true;
	if(WriteMemory(BP.Address,&BP.CodeBackup,1)==0)
		return false;
	return true;
}

bool CX86Debugger::RecoverCCBP(BREAK_POINT&BP)
{
	BYTE Data;
	if(BP.State != BP_STATE_RECOV)
		return false;
	if(ReadMemory(BP.Address,&Data,1)==0)
		return false;
	if(Data!=BP.CodeBackup)
		return false;
	if(WriteMemory(BP.Address,"\xCC",1)==0)
		return false;
	return true;
}

bool CX86Debugger::SetX86HDBP(BREAK_POINT&BP,DWORD*pDR,DWORD*pDR7)
{
	int Index;
	DWORD GnLn,RWLen,Mask;
	////////////////////////////////////////////////////////
	//检查Dr7是否有空闲
	GnLn = 0x3;//11B
	Index=0;
	while(Index<4)
	{
		if((*pDR7&GnLn)==0)
			break;
		GnLn<<=2;
		Index++;
	}
	if(Index>=4)
		return false;
	//检查Dr7是否有空闲
	////////////////////////////////////////////////////////
	RWLen = 0;
	if(BP.Type&BP_TYPE_IO_READWRITE)
	{
		RWLen=0x2;
		BP.Description = "IO";
	}
	if(BP.Type&BP_TYPE_EXECUTE)
	{
		RWLen=0x0;
		BP.Description = "X";
	}
	if(BP.Type&BP_TYPE_WRITE&&(BP.Type&BP_TYPE_READ)==0)
	{
		BP.Description = "W";
		RWLen=0x1;
	}
	else if(BP.Type&BP_TYPE_READWRITE)
	{
		BP.Description = "RW";
		RWLen=0x3;
	}
	switch(BP.Length)
	{
	case 1:
		break;
	case 2:
		RWLen |= 0x04;
		break;
	case 4:
		RWLen |= 0x0C;
		break;
	default:
		if((BP.Type&BP_TYPE_EXECUTE)==0)
			RWLen |= 0x08;//Undefine or 8 byte
		break;
	}
	Mask = (0xF<<(Index*4+16))|GnLn|0xDF00;//0x2000 GD 清GD保护位
	Mask=~Mask;
	*pDR7&=Mask;//先清除和此索引上的数据
	*pDR7|=(RWLen<<(Index*4+16))|GnLn|0x700;//0x700 set GE and LE bit
	pDR[Index] = BP.Address;
	BP.CodeBackup = (BYTE)Index;
	SaveRegister();
	return true;
}

bool CX86Debugger::ClearX86HDBP(BREAK_POINT&BP,DWORD*pDR,DWORD*pDR7)
{
	DWORD Mask;
	int Index=0;
	while(Index<4)
	{
		if(pDR[Index]==BP.Address)
			break;
		Index++;
	}
	if(Index>=4)
		return true;
	Mask = (0xF<<(Index*4+16))|(0x3<<(Index*2))|0xDF00;//0x2000 GD 清GD保护位 
	Mask=~Mask;
	*pDR7&=Mask;
	if(*pDR7 & 0xFF)
		*pDR7 |= 0x700;
	pDR[Index] = 0;
	return true;
}


#define DR6_BD			0x2000
#define DR6_BS			0x4000
#define DR6_BT			0x8000

BREAK_POINT*CX86Debugger::IsHanldeHDBP(DWORD DR6)
{
	DWORD Bn;
	int Index;
	if(DR6&(DR6_BD|DR6_BS|DR6_BT))
		return NULL;
	Bn = 1;
	Index=0;
	while(Index<4)
	{
		Bn<<=1;
	}
	return NULL;
}

bool CX86Debugger::IsRecoverBPExist()
{
	CCodeBPMap::IT Iter = m_pCodeBPMap->Begin();
	while(Iter.IsExist())
	{
		if(Iter->State == BP_STATE_RECOV)
			return true;
		Iter++;
	}
	return false;
}

int CX86Debugger::RecoverBreakPoint()
{
	int Count=0;
	for(CCodeBPMap::IT Iter=m_pCodeBPMap->Begin();Iter.IsExist();Iter++)
	{
		if(Iter->State == BP_STATE_RECOV)
		{
			if(SwitchProcessSpace(Iter->PID))
			{
				if(RecoverCCBP(*Iter))
					Iter->State = BP_STATE_ENABLE;
				RestoreProcessSpace();
			}
			Count++;
		}
	}
	return Count;
}

