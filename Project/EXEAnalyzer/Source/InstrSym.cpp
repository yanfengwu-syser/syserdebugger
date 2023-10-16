// InstrSym.cpp: implementation of the CInstrSym class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "InstrSym.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define MAX_PREV_INSTR_LEN		MAX_INSTR_LEN*2

PCWSTR CInstrSym::m_RegStr[3][16]=
{
	WSTR("AX"),WSTR("CX"),WSTR("DX"),WSTR("BX"),WSTR("SP"),WSTR("BP"),WSTR("SI"),WSTR("DI"),
	WSTR("R8W"),WSTR("R9W"),WSTR("R10W"),WSTR("R11W"),WSTR("R12W"),WSTR("R13W"),WSTR("R14W"),WSTR("R15W"),
	WSTR("EAX"),WSTR("ECX"),WSTR("EDX"),WSTR("EBX"),WSTR("ESP"),WSTR("EBP"),WSTR("ESI"),WSTR("EDI"),
	WSTR("R8D"),WSTR("R9D"),WSTR("R10D"),WSTR("R11D"),WSTR("R12D"),WSTR("R13D"),WSTR("R14D"),WSTR("R15D"),
	WSTR("RAX"),WSTR("RCX"),WSTR("RDX"),WSTR("RBX"),WSTR("RSP"),WSTR("RBP"),WSTR("RSI"),WSTR("RDI"),
	WSTR("R8"),WSTR("R9"),WSTR("R10"),WSTR("R11"),WSTR("R12"),WSTR("R13"),WSTR("R14"),WSTR("R15")
};
PCWSTR CInstrSym::m_ScaleStr[4]=
{
	WSTR("1"),WSTR("2"),WSTR("4"),WSTR("8")
};
PCWSTR CInstrSym::m_SizePtr[9]=
{
	WSTR("Err"),WSTR("%02X"),WSTR("%04X"),WSTR("Err"),WSTR("%08X"),WSTR("Err"),WSTR("Err"),WSTR("Err"),WSTR("%16I64X")
};
PCWSTR CInstrSym::m_SizeSym[11]=
{
	WSTR(""),WSTR("BYTE"),WSTR("WORD"),WSTR(""),WSTR("DWORD"),WSTR(""),WSTR("FWORD"),WSTR(""),WSTR("QWORD"),WSTR(""),WSTR("TWORD")
};
PCWSTR CInstrSym::m_SegStr[6]=
{
	WSTR("ES"),WSTR("CS"),WSTR("SS"),WSTR("DS"),WSTR("FS"),WSTR("GS")
};
PCWSTR CInstrSym::m_LengthStr[5]=
{
	WSTR("DB"),WSTR("DB"),WSTR("DW"),WSTR("Err"),WSTR("DD")
};
PCWSTR CInstrSym::m_DefaultOPSize[2]=
{
	WSTR("%04X"),WSTR("%08X")
};

PCSTR CInstrSym::m_TransDesInst[]=
{
	"CALL",
	"JMP",
	NULL
};

PCWSTR CInstrSym::m_UnReaded=WSTR("????????");


#define UxAlign		6

WCHAR*OptItemToStr(OPERAND_ITEM*OpArray,int nOp,WCHAR*pString,INSTRUCTION_INFORMATION*pDasmInstr)
{
	DIS_ADDRESS*pAddr;
	OPERAND_ITEM*pOp;
	WCHAR szBuffer[32];
	for(int n=0;n<nOp;n++)
	{
		pOp=&OpArray[n];
		if(pOp->mode==mode_invalid)
			break;
		if(n>0)
		{//画操作数间隔符
			pString+=TStrCpy(pString,",");
		}
		if(pOp->mode==mode_address)
		{//分析地址结构
			pAddr=(DIS_ADDRESS*)&pOp->addr;
			//if(pDasmInstr->xxxxptr!=-1)
			{
				pString+=TStrCpy(pString,",");
				if(pOp->opersize!=-1)
				{
						pString+=TStrCpy(pString,CInstrSym::m_SizeSym[pOp->opersize]);
						pString+=TStrCpy(pString," PTR ");
				}

			}
			if(pDasmInstr->SegmentPrefix!=-1)
			{
				pString+=TStrCpy(pString,CInstrSym::m_SegStr[pDasmInstr->SegmentPrefix]);
				pString+=TStrCpy(pString,":");
			}
			pString+=TStrCpy(pString,"[");
			if(pAddr->base!=-1)//画Base寄存器
			{
				pString+=TStrCpy(pString,CInstrSym::m_RegStr[pAddr->address_size][pAddr->base]);
			}
			if(pAddr->index!=-1)//画Index寄存器
			{
				if(pAddr->base!=-1)
				{
					pString+=TStrCpy(pString,"+");
				}
				pString+=TStrCpy(pString,CInstrSym::m_RegStr[pAddr->address_size][pAddr->index]);
				if(pAddr->scale>1)
				{
					pString+=TStrCpy(pString,"*");
					pString+=TStrCpy(pString,CInstrSym::m_ScaleStr[pAddr->scale]);
				}
			}
			if(pAddr->displacement || (pAddr->base==-1 && pAddr->index==-1))
			{//画displacement
				if(pAddr->index!=-1 || pAddr->base!=-1)
				{
					pString+=TStrCpy(pString,"+");
				}
				TSPrintf(szBuffer,CInstrSym::m_SizePtr[pAddr->displacement_size],pAddr->displacement);
				pString+=TStrCpy(pString,szBuffer);
			}
			pString+=TStrCpy(pString,"]");
		}
		else
			switch(pOp->mode)
		{
			case mode_register:
				pString+=TStrCpy(pString,pOp->string);
				break;
			case mode_segment:
				pString+=TStrCpy(pString,pOp->string);
				break;
			case mode_far:
				TSPrintf(szBuffer,WSTR("%04X"),pOp->farptr.segment);
				pString+=TStrCpy(pString,szBuffer);
				pString+=TStrCpy(pString,WSTR(":"));
				TSPrintf(szBuffer,CInstrSym::m_SizePtr[pOp->opersize-2],pOp->farptr.offset);
				pString+=TStrCpy(pString,szBuffer);
				break;
			case mode_near:
			case mode_immed:
				pString+=TStrCpy(pString,pOp->string);
				break;
			case mode_datadup:
				if(n>0)
					break;
				for(n=0;n<pOp->datadup.count;n++)
				{
					if(n>0)
					{
						pString+=TStrCpy(pString,WSTR(","));
					}
					TSPrintf(szBuffer,WSTR("%02X"),pOp->datadup.buffer[n]);
					pString+=TStrCpy(pString,szBuffer);
				}
				break;
			case mode_symbol:
				if(pOp->symbol.offset)
				{
					pString+=TStrCpy(pString,WSTR("OFFSET "));
				}
				pString+=TStrCpy(pString,pOp->symbol.string);
				break;
			case mode_align:
				if(n>0)
					break;
				TSPrintf(szBuffer,WSTR("%X"),pOp->align.nBytes);
				pString+=TStrCpy(pString,szBuffer);
				break;
		}
	}
	return pString;
}

WCHAR* InstrToStr(INSTRUCTION_INFORMATION*pDasmInstr,WCHAR*pString)
{
	bool bFirstStr = TRUE;
	///////////////////////////////////////////////////
	//画LOCK前缀
	///////////////////////////////////////////////////
	if(pDasmInstr->Lock!=-1)
	{
		TStrCpy(pString,pDasmInstr->LockName);
		TStrCat(pString," ");
		if(bFirstStr)//如果存在此项且未使用对齐
		{			
			pString+=TStrFillTail(pString,UxAlign,WSTR(' '));
			bFirstStr = FALSE;
		}
		else
			pString+=TStrLen(pString);
	}
	///////////////////////////////////////////////////
	//画REP前缀
	///////////////////////////////////////////////////
	if(pDasmInstr->Repeat!=-1)
	{
		TStrCpy(pString,pDasmInstr->RepeatName);
		TStrCat(pString," ");
		if(bFirstStr)
		{
			pString+=TStrFillTail(pString,UxAlign,WSTR(' '));
			bFirstStr = FALSE;
		}
		else
			pString+=TStrLen(pString);
		pString+=TStrLen(pString);
	}
	///////////////////////////////////////////////////
	//画OPCODE
	///////////////////////////////////////////////////
	TStrCpy(pString,pDasmInstr->Name);
	TStrCat(pString," ");
	if(*pDasmInstr->Name && bFirstStr)//如果存在此项且未使用对齐
	{
		pString+=TStrFillTail(pString,UxAlign,WSTR(' '));
		bFirstStr = FALSE;
	}
	else
		pString+=TStrLen(pString);
	///////////////////////////////////////////////////
	//画操作元素
	///////////////////////////////////////////////////
	return OptItemToStr(pDasmInstr->op,3,pString,pDasmInstr);
}


CInstrSym::CInstrSym()
{
	m_bUseSym=TRUE;
	m_UxAlign=6;
	m_Mode = BIT32;
	m_Style=DS_USE_SYM|DS_JMP_API;
}

CInstrSym::~CInstrSym()
{
}

bool CInstrSym::AddrToSym(ULPOS Address,PSTR szSym,int BufSize)
{
	return false;
}

ULSIZE CInstrSym::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size)
{
	for(ULPOS n=0;n<Size;n++)
	{
		PUT_BYTE(Buffer,n,(BYTE)(Address+n));
	}
	return Size;
}


ULSIZE CInstrSym::Asm(LPSTR InstString,PBYTE OutPutCode,ULPOS EIP)
{
	return Assembler(InstString,OutPutCode,EIP,m_Mode);
}

void CInstrSym::HandleAddressOp(OPERAND_ITEM*pOp,WCHAR* szInfo,INSTRUCTION_INFORMATION*pInstrInfo)
{
	int Size;
	CHAR szSym[MAX_LONG_NAME_LEN];
	DWORD Data;
	szInfo=OptItemToStr(pOp,1,szInfo,pInstrInfo);
	szInfo+=TStrCpy(szInfo," = ");
	if(pOp->addr.base!=-1 || pOp->addr.index!=-1 || pInstrInfo->SegmentPrefix!=-1)
	{
		szInfo+=TStrCpy(szInfo,"[");
		szInfo+=TSPrintf(szInfo,CInstrSym::m_DefaultOPSize[pInstrInfo->CodeMode],pOp->addr.line_address);
		szInfo+=TStrCpy(szInfo,"] = ");
	}
	Size = pOp->opersize;
	if(Size<=0 || Size>4)
		Size = 4;
	Data = 0;
	if(ReadMemory((ULPOS)pOp->addr.line_address,&Data,Size)!=Size)
	{
		szInfo+=TStrCpy(szInfo,"????");
		return;
	}
	szInfo+=TSPrintf(szInfo,CInstrSym::m_SizePtr[Size],Data);
	if(AddrToSym(Data,szSym,sizeof(szSym)/sizeof(WCHAR)))
	{
		szInfo+=TStrCpy(szInfo," = ");
		TStrCpy(szInfo,szSym);
	}
}



ULSIZE CInstrSym::Dasm(INSTRUCTION_INFORMATION*pDasmInstr,DIS_CPU*pDisCPU,ULSIZE MaxSize)
{
	ULPOS Address;
	ULSIZE CodeLen,RDSize;
	RDSize = ReadMemory(pDasmInstr->eip,pDasmInstr->CodeBuff,MAX_INSTR_LEN);
	if(RDSize==0)
	{
		pDasmInstr->OpCode=-1;
		strcpy(pDasmInstr->Name,"???");
		pDasmInstr->Lock =-1;
		pDasmInstr->Repeat=-1;
		pDasmInstr->SegmentPrefix=-1;
		pDasmInstr->op[0].mode=mode_invalid;
		pDasmInstr->op[1].mode=mode_invalid;
		pDasmInstr->op[2].mode=mode_invalid;
		return 0;
	}
	if(RDSize > MaxSize)
		RDSize = MaxSize;
	CodeLen=Disassembler(pDasmInstr,pDisCPU);
	if(CodeLen==0 || CodeLen>RDSize)
	{
		if(CodeLen>RDSize)
			CodeLen=RDSize;
		pDasmInstr->OpCode=-1;
		strcpy(pDasmInstr->Name,"DB");
		pDasmInstr->Lock=-1;
		pDasmInstr->Repeat=-1;
		pDasmInstr->SegmentPrefix=-1;
		pDasmInstr->op[1].mode=mode_invalid;
		pDasmInstr->op[2].mode=mode_invalid;
		pDasmInstr->op[0].mode=mode_datadup;
		pDasmInstr->op[0].datadup.count=1;
		if(1 && pDasmInstr->CodeBuff)
			memcpy(pDasmInstr->op[0].datadup.buffer,pDasmInstr->CodeBuff,1);
		return 0;
	}
	if((m_Style & DS_USE_SYM) ==0)
		return CodeLen;
	if((_GET_WORD(pDasmInstr->CodeBuff)==0x15FF)||(_GET_WORD(pDasmInstr->CodeBuff)==0x25FF))
	{
		RDSize = ReadMemory(_GET_DWORD(&pDasmInstr->CodeBuff[2]),&Address,sizeof(Address));
		if(RDSize==sizeof(Address))
		{
			if(AddrToSym(Address,pDasmInstr->op[0].symbol.string,MAX_SYMBOL_LEN))
			{
				pDasmInstr->op->symbol.mode = pDasmInstr->op[0].mode;
				pDasmInstr->op->mode=mode_symbol;
				pDasmInstr->op->symbol.offset = FALSE;
				pDasmInstr->op->symbol.addr = Address;
				return CodeLen;
			}
		}
	}
	if((m_Style & DS_JMP_API) && TStrCmp(pDasmInstr->Name,"CALL")==0)
	{//间接Call API
		if(pDasmInstr->op->mode == mode_near)
		{
			UINT OldStyle;
			BYTE Buffer[MAX_INSTR_LEN];
			INSTRUCTION_INFORMATION DasmInstr;
			DasmInstr.pasm = NULL;
			DasmInstr.CodeMode = pDasmInstr->CodeMode;
			DasmInstr.eip = (DWORD)pDasmInstr->op->nearptr.label ;
			DasmInstr.CodeBuff = Buffer;
			OldStyle = m_Style;
			m_Style &= ~DS_JMP_API;
			Dasm(&DasmInstr);
			m_Style = OldStyle;
			if((_GET_WORD(DasmInstr.CodeBuff)==0x15FF)||(_GET_WORD(DasmInstr.CodeBuff)==0x25FF)||(_GET_BYTE(DasmInstr.CodeBuff)==0xE9)
				&& DasmInstr.op->mode ==mode_symbol)
			{
				TStrCpy(pDasmInstr->op->symbol.string,DasmInstr.op->symbol.string);
				pDasmInstr->op->symbol.mode = pDasmInstr->op->mode;
				pDasmInstr->op->mode=mode_symbol;
				pDasmInstr->op->symbol.offset=FALSE;
				pDasmInstr->op->symbol.addr = DasmInstr.op->symbol.addr;
				return CodeLen;
			}
		}		
	}
	for(int n=0;n<3;n++)
	{
		if(pDasmInstr->op[n].mode == mode_immed)
		{
			Address = (ULPOS)pDasmInstr->op[n].immed.immed_value;
			if(AddrToSym(Address,pDasmInstr->op[n].symbol.string,MAX_SYMBOL_LEN))
			{
				pDasmInstr->op[n].symbol.mode = pDasmInstr->op[n].mode;
				pDasmInstr->op[n].mode=mode_symbol;
				pDasmInstr->op[n].symbol.offset = TRUE;
				pDasmInstr->op[n].symbol.addr = Address;
			}
		}
		else if(pDasmInstr->op[n].mode == mode_near)
		{
			Address = pDasmInstr->eip + (ULPOS)pDasmInstr->op[n].nearptr.offset + CodeLen;
			if(AddrToSym(Address,pDasmInstr->op[n].symbol.string,MAX_SYMBOL_LEN))
			{
				pDasmInstr->op[n].symbol.mode = pDasmInstr->op[n].mode;
				pDasmInstr->op[n].mode=mode_symbol;
				pDasmInstr->op[n].symbol.offset = FALSE;
				pDasmInstr->op[n].symbol.addr = Address;
			}
		}
		else if(pDasmInstr->op[n].mode==mode_address)
		{
			if(pDasmInstr->SegmentPrefix==-1&&pDasmInstr->op[n].addr.base==-1&&pDasmInstr->op[n].addr.index==-1)
			{
				Address = (ULPOS)pDasmInstr->op[n].addr.effect_address;
				if(AddrToSym(Address,pDasmInstr->op[n].symbol.string,MAX_SYMBOL_LEN))
				{
					pDasmInstr->op[n].symbol.mode = pDasmInstr->op[n].mode;
					pDasmInstr->op[n].mode=mode_symbol;
					pDasmInstr->op[n].symbol.offset = FALSE;
					pDasmInstr->op[n].symbol.addr = Address;
				}
				else if(pDasmInstr->op[n].opersize == 4)
				{
					RDSize=ReadMemory((ULPOS)pDasmInstr->op[n].addr.effect_address,&Address,sizeof(Address));
					if(RDSize==sizeof(Address))
					{
						if(AddrToSym(Address,pDasmInstr->op[n].symbol.string,MAX_SYMBOL_LEN))
						{
							pDasmInstr->op[n].symbol.mode = pDasmInstr->op[n].mode;
							pDasmInstr->op[n].mode=mode_symbol;
							pDasmInstr->op[n].symbol.offset = FALSE;
							pDasmInstr->op[n].symbol.addr = Address;
						}
					}
				}
			}
		}
	}
	return CodeLen;
}

bool CInstrSym::GetNearJmpDes(BYTE*CodeBuffer,ULPOS EIP,ULPOS*pDes)
{
	if(CodeBuffer[0]>=0x70 && CodeBuffer[0] <=0x7f)
	{
		if(pDes)
			*pDes=EIP+2+(char)CodeBuffer[1];
		return true;
	}
	if(CodeBuffer[0]==0xf &&  CodeBuffer[1]>=0x80 && CodeBuffer[1] <=0x8f)
	{
		if(pDes)
			*pDes=EIP+6+*(int*)&CodeBuffer[2];
		return true;
	}
	return false;
}

bool CInstrSym::IsActiveNearJmp(BYTE*CodeBuffer,DWORD Eflags)
{
	switch(*CodeBuffer)
	{
	case 0x70:
		return (Eflags&EFLAGS_OF_MASK) != 0;
	case 0x71:
		return (Eflags&EFLAGS_OF_MASK) == 0;
	case 0x72:
		return (Eflags&EFLAGS_CF_MASK) != 0;
	case 0x73:
		return (Eflags&EFLAGS_CF_MASK) == 0;
	case 0x74:
		return (Eflags&EFLAGS_ZF_MASK) != 0;
	case 0x75:
		return (Eflags&EFLAGS_ZF_MASK) == 0;
	case 0x76:
		return ((Eflags&EFLAGS_ZF_MASK) != 0)&&((Eflags&EFLAGS_CF_MASK) != 0);
	case 0x77:
		return ((Eflags&EFLAGS_ZF_MASK) == 0)&&((Eflags&EFLAGS_CF_MASK) == 0);
	case 0x78:
		return (Eflags&EFLAGS_SF_MASK) != 0;
	case 0x79:
		return (Eflags&EFLAGS_SF_MASK) == 0;
	case 0x7a:
		return (Eflags&EFLAGS_PF_MASK) != 0;
	case 0x7b:
		return (Eflags&EFLAGS_PF_MASK) == 0;
	case 0x7c:
		return (Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT != (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT;
	case 0x7d:
		return (Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT == (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT;
	case 0x7e:
		return ((Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT != (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT) && (Eflags&EFLAGS_ZF_MASK) != 0;
	case 0x7f:
		return ((Eflags & EFLAGS_OF_MASK)>>EFLAGS_OF_SHIFT == (Eflags & EFLAGS_SF_MASK)>>EFLAGS_SF_SHIFT) && (Eflags&EFLAGS_ZF_MASK) == 0;
	}
	return false;
}


ULSIZE CInstrSym::PrevInstrLen(ULPOS Address)
{
	ULPOS	RefAddress;
	ULSIZE	MaxLen,Count,PrevLenCount,MaxRef,MaxRefIdx,PrevLen;
	BYTE	PrevLenAry[MAX_PREV_INSTR_LEN],CodeBuffer[MAX_PREV_INSTR_LEN],CodeLenArray[MAX_PREV_INSTR_LEN],RefLenAry[MAX_PREV_INSTR_LEN];
	MaxLen = Address >= m_ImageBase + MAX_PREV_INSTR_LEN ? MAX_PREV_INSTR_LEN : Address - m_ImageBase;
	if(MaxLen==0)
		return 1;
	Count = ReadMemory(Address - MaxLen,CodeBuffer,MaxLen);
	if(Count)
	{
		MaxLen = Count;
	}
	else
	{
		for(Count=MaxLen-1;Count>0;Count--)
		{
			if(ReadMemory(Address - Count,CodeBuffer,Count))
				break;
		}
		MaxLen = Count;
	}
	if(MaxLen==0)
		return 1;
	PrevLenCount = 0;
	for(ULSIZE PrevOff=1;PrevOff<=MaxLen;PrevOff++)
	{
		Count = InstrCount(&CodeBuffer[MaxLen-PrevOff],PrevOff,CodeLenArray);
		if(Count)
		{
			PrevLenAry[PrevLenCount] = CodeLenArray[Count-1];
			PrevLenCount++;
		}
	}
	if(PrevLenCount==0)
		return 1;
	ZeroMemory(RefLenAry,sizeof(RefLenAry));
	RefAddress = Address;
	if(GetInstrRefPoint(&RefAddress) && RefAddress < Address && (PrevLen = Address - RefAddress) < MAX_PREV_INSTR_LEN)
	{
		PrevLen = Address - RefAddress;
		for(Count=0;Count<PrevLenCount;Count++)
		{
			if(PrevLen == PrevLenAry[Count])
				RefLenAry[PrevLenAry[Count]]=MAX_PREV_INSTR_LEN+1;
			else
				RefLenAry[PrevLenAry[Count]]++;
		}
	}
	else
	{
		for(Count=0;Count<PrevLenCount;Count++)
			RefLenAry[PrevLenAry[Count]]++;
	}
	MaxRefIdx = MaxRef = 0;
	for(Count=0;Count<MAX_PREV_INSTR_LEN;Count++)
	{
		if(MaxRef<RefLenAry[Count])
		{
			MaxRefIdx = Count;
			MaxRef = RefLenAry[Count];
		}
	}
	return MaxRefIdx;
}

ULPOS CInstrSym::InstrCount(BYTE*CodeBuffer,ULSIZE CodeSize,BYTE*LenAry)
{
	ULPOS CodeLen,Off=0,Count=0;
	while(Off<CodeSize)
	{
		CodeLen=InstrLen(&CodeBuffer[Off]);
		if(CodeLen==0)
			return 0;
		Off+=CodeLen;
		if(LenAry)
			LenAry[Count]=(BYTE)CodeLen;
		Count++;
	}
	if(Off==CodeSize)
		return Count;
	return 0;
}

bool CInstrSym::IsProcessCode(ULPOS Address)
{
	BYTE Buffer[MAX_INSTR_LEN];
	ULPOS CodeLen;
	INSTRUCTION_INFORMATION DasmInstr;
	DasmInstr.eip=Address;
	DasmInstr.pasm = NULL;
	DasmInstr.CodeBuff=Buffer;
	CodeLen=Dasm(&DasmInstr);
	if(CodeLen<2)
		return false;
	if(TStrICmp(DasmInstr.Name,"CALL")==0)
		return true;
	else if(DasmInstr.Repeat!=-1)
		return true;
	return false;
}

//取转移类指令目的地址，用于CodeView的EnterAddr
bool CInstrSym::GetTransferAddress(ULPOS Address,ULPOS*pDesAddr)
{
	int n;
	BYTE Buffer[MAX_INSTR_LEN];
	INSTRUCTION_INFORMATION DasmInstr;
	DasmInstr.eip = Address;
	DasmInstr.pasm = NULL;
	DasmInstr.CodeBuff=Buffer;
	ULSIZE CodeLen,RDSize;
	RDSize = ReadMemory(Address,Buffer,MAX_INSTR_LEN);
	if(RDSize==0)
		return false;
	CodeLen=Disassembler(&DasmInstr,NULL);
	if(CodeLen==0 || CodeLen>RDSize || CodeLen<2)
		return false;
	if(DasmInstr.op[0].mode==mode_invalid||DasmInstr.op[1].mode!=mode_invalid)
		return false;
	if(GetNearJmpDes(Buffer)==false)
	{
		n=0;
		while(m_TransDesInst[n])
		{
			if(TStrICmp(DasmInstr.Name,m_TransDesInst[n])==0)
				break;
			n++;
		}
		if(m_TransDesInst[n]==NULL)
			return false;
	}
	switch(DasmInstr.op->mode)
	{
	case mode_near:
		*pDesAddr = (ULPOS)DasmInstr.op->nearptr.label;
		return true;
	case mode_immed:
		*pDesAddr=(ULPOS)DasmInstr.op->immed.immed_value;
		return true;
	case mode_address:
		if(DasmInstr.SegmentPrefix==-1&&DasmInstr.op->addr.base==-1&&DasmInstr.op->addr.index==-1&&DasmInstr.op->addr.displacement_size==4)
		{
			*pDesAddr=0;
			if(ReadMemory((ULPOS)DasmInstr.op->addr.effect_address,pDesAddr,sizeof(*pDesAddr))!=sizeof(*pDesAddr))
				return false;
			return true;
		}
		break;
	}
	return false;	
}

bool CInstrSym::GetInstrDesAddress(ULPOS Address,ULPOS*pDesAddr)
{
	BYTE Buffer[MAX_INSTR_LEN];
	INSTRUCTION_INFORMATION DasmInstr;
	DasmInstr.eip = Address;
	DasmInstr.pasm = NULL;
	DasmInstr.CodeBuff=Buffer;
	ULSIZE CodeLen,RDSize;
	RDSize = ReadMemory(Address,Buffer,MAX_INSTR_LEN);
	if(RDSize==0)
		return false;
	CodeLen=Disassembler(&DasmInstr,NULL);
	if(CodeLen==0 || CodeLen>RDSize || CodeLen<2)
		return false;
	for(int n=0;n<3;n++)
	{
		if(DasmInstr.op[n].mode == mode_near)
		{
			*pDesAddr = DasmInstr.eip + (ULPOS)DasmInstr.op[n].nearptr.offset + CodeLen;
			return true;
		}
		else if(DasmInstr.op[n].mode==mode_address)
		{
			if(DasmInstr.SegmentPrefix==-1&&DasmInstr.op[n].addr.base==-1&&DasmInstr.op[n].addr.index==-1&&DasmInstr.op[n].addr.displacement_size==4)
			{
				*pDesAddr=0;
				if(ReadMemory((ULPOS)DasmInstr.op[n].addr.effect_address,pDesAddr,sizeof(*pDesAddr))!=sizeof(*pDesAddr))
					return false;
				return true;
			}
		}else if(DasmInstr.op[n].mode == mode_immed)
		{
			*pDesAddr=(ULPOS)DasmInstr.op[n].immed.immed_value;
			return true;
		}
	}
	return false;
}
int CInstrSym::GetInstrImmediateAndDesAddress(ULPOS Address,ULPOS*pDesAddr,ULPOS* pImmediate)
{
	BYTE Buffer[MAX_INSTR_LEN];
	DWORD dwValue[3];
	int retvalue=0;
	INSTRUCTION_INFORMATION DasmInstr;
	DasmInstr.eip = Address;
	DasmInstr.pasm = NULL;
	DasmInstr.CodeBuff=Buffer;
	ULSIZE CodeLen,RDSize;
	RDSize = ReadMemory(Address,Buffer,MAX_INSTR_LEN);
	*pDesAddr=0-1;
	*pImmediate=0-1;
	if(RDSize==0)
		return retvalue;
	CodeLen=Disassembler(&DasmInstr,NULL);
	if(CodeLen==0 || CodeLen>RDSize || CodeLen<2)
		return retvalue;
	for(int n=0;n<3;n++)
	{
		//if(DasmInstr.op[n].mode == mode_near)
		//{			
		//	dwValue[retvalue]=DasmInstr.eip + DasmInstr.op[n].nearptr.offset + CodeLen;
		//	*pDesAddr=dwValue[retvalue];
		//	retvalue++;			
		//}
		//else
			if(DasmInstr.op[n].mode==mode_address)
		{
			if(DasmInstr.SegmentPrefix==-1&&DasmInstr.op[n].addr.base==-1&&DasmInstr.op[n].addr.index==-1&&DasmInstr.op[n].addr.displacement_size==4)
			{
				*pDesAddr=0-1;
				if(ReadMemory((ULPOS)DasmInstr.op[n].addr.effect_address,&RDSize,sizeof(RDSize))==sizeof(RDSize))					
				{
					dwValue[retvalue]=(DWORD)DasmInstr.op[n].addr.effect_address;
					retvalue++;
					*pDesAddr=(ULPOS)DasmInstr.op[n].addr.effect_address;
				}
			}
		}else if(DasmInstr.op[n].mode == mode_immed)
		{
			if(ReadMemory((ULPOS)DasmInstr.op[n].immed.immed_value,&RDSize,sizeof(RDSize))==sizeof(RDSize))	
			{
				dwValue[retvalue]=(DWORD)DasmInstr.op[n].immed.immed_value;	
				*pImmediate=(ULPOS)DasmInstr.op[n].immed.immed_value;	
				retvalue++;
			}			
		}
	}
	return retvalue;
}

bool CInstrSym::GetVariableDesAddress(ULPOS Address,ULPOS*pDesAddr)
{
	BYTE Buffer[MAX_INSTR_LEN];
	INSTRUCTION_INFORMATION DasmInstr;
	DasmInstr.eip=Address;
	DasmInstr.pasm = NULL;
	DasmInstr.CodeBuff=Buffer;
	ULSIZE CodeLen,RDSize;
	RDSize = ReadMemory(Address,Buffer,MAX_INSTR_LEN);
	if(RDSize==0)
		return false;
	CodeLen=Disassembler(&DasmInstr,NULL);
	if(CodeLen==0 || CodeLen>RDSize || CodeLen<2)
		return false;
	for(int n=0;n<3;n++)
	{
		if(DasmInstr.op[n].mode==mode_address)
		{
			if(DasmInstr.SegmentPrefix==-1&&DasmInstr.op[n].addr.base==-1&&DasmInstr.op[n].addr.index==-1)
			{
				*pDesAddr = (ULPOS)DasmInstr.op[n].addr.effect_address;
				return true;
			}
		}
	}
	if(DasmInstr.CodeBuff[0]==0x68)
	{
		*pDesAddr=(ULPOS)DasmInstr.op[0].immed.immed_value;
		return true;
	}
	return false;
}

int CInstrSym::IsPrevCodeCallInstr(ULPOS Address,PSTR szFunc,ULPOS*pDesAddr)
{
	static ULSIZE TestSize[]={6,5,4,3,2};
	ULSIZE CodeLen;
	INSTRUCTION_INFORMATION DasmInstr;
	BYTE Buffer[MAX_INSTR_LEN];
	for(int n=0;n<sizeof(TestSize)/sizeof(ULSIZE);n++)
	{
		DasmInstr.eip=Address-TestSize[n];
		DasmInstr.pasm = NULL;
		DasmInstr.CodeBuff=Buffer;
		CodeLen=Dasm(&DasmInstr);
		if(CodeLen!=TestSize[n])
			continue;
		if(TStrICmp(DasmInstr.Name,"CALL")==0)
		{
			switch(DasmInstr.op->mode)
			{
			case mode_symbol:
				if(szFunc)
					TStrCpy(szFunc,DasmInstr.op->symbol.string);
				if(pDesAddr)
					*pDesAddr=DasmInstr.op->symbol.addr;
				break;
			case mode_near:
				if(szFunc)
					*szFunc=0;
				if(pDesAddr)
					*pDesAddr = (ULPOS)DasmInstr.op->nearptr.label;
				break;
			case mode_address:
				if(szFunc)
					*szFunc=0;
				if(pDesAddr)
					*pDesAddr = 0;
				if(DasmInstr.SegmentPrefix==-1&&DasmInstr.op->addr.base==-1&&DasmInstr.op->addr.index==-1)
				{
					if(pDesAddr)
						ReadMemory((ULPOS)DasmInstr.op->addr.effect_address,pDesAddr,sizeof(*pDesAddr));
				}
				break;
			default:
				if(szFunc)
					*szFunc=0;
				if(pDesAddr)
					*pDesAddr=0;
				break;
			}
			return CodeLen;
		}
	}
	return 0;
}

bool CInstrSym::IsCallInstruction(ULPOS Address,PSTR szFunc)
{
	ULPOS CodeLen;
	BYTE Buffer[MAX_INSTR_LEN];
	INSTRUCTION_INFORMATION DasmInstr;
	DasmInstr.eip=Address;
	DasmInstr.pasm = NULL;
	DasmInstr.CodeBuff=Buffer;
	CodeLen=Dasm(&DasmInstr);
	if(CodeLen<2)
		return false;
	if(TStrICmp(DasmInstr.Name,"CALL")==0)
	{
		if(szFunc)
		{
			*szFunc=0;
			if(DasmInstr.op[0].mode==mode_symbol)
				TStrCpy(szFunc,DasmInstr.op[0].symbol.string);
		}
		return true;
	}
	return false;
}

ULSIZE CInstrSym::InstrLen(ULPOS Address,ULSIZE MaxSize)
{
	ULSIZE CodeLen,Size;
	BYTE Buffer[MAX_INSTR_LEN];
	Size = ReadMemory(Address,Buffer,MaxSize);
	if(Size==0)
		return 0;
	CodeLen=InstrLen(Buffer,Size);
	if(CodeLen>Size)
		CodeLen=Size;
	return CodeLen;
}

ULSIZE CInstrSym::InstrLen(BYTE*Buffer,ULSIZE BufSize)
{
	ULSIZE CodeLen=::Disassembler(NULL,Buffer,0,BIT32);
	if(CodeLen>BufSize)
		return 0;
	return CodeLen;
}

ULSIZE CInstrSym::InstrLen16(BYTE*Buffer,ULSIZE BufSize)
{
	ULSIZE CodeLen=::Disassembler(NULL,Buffer,0,BIT16);
	if(CodeLen>BufSize)
		return 0;
	return CodeLen;
}
