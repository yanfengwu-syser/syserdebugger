#include "StdAfx.h"
#include "Syser.h"
#include "CallStack.h"

CCallStack::CCallStack()
{
	m_pCurCallFrame = NULL;
	m_PrevEBP = 0;
}

void CCallStack::UpdateContext(ULPOS EBP)
{
	ULSIZE CodeLen;
	ULPOS Address,FrameAddress;
	CHAR szSymbol[MAX_SYMBOL_LEN];
	FRAME_ENTRY Frame;
	CDbgModule*pDbgModule;
	TList<CALL_FRAME>::IT Iter;

	m_pCurCallFrame = NULL;
	FrameAddress = EBP?EBP:*X86_REG_PTR.pEBP;
	if(m_PrevEBP == FrameAddress)
		return;
	m_PrevEBP = FrameAddress;
	m_CallFrameList.Clear();
	for(int n=0;n<MAX_CALL_STACK_COUNT;n++)
	{
		if(gpSyser->m_pDebugger->ReadMemory(FrameAddress,&Frame,sizeof(Frame))!=sizeof(Frame))
			break;
		if(Frame.PrevFrame<=FrameAddress)
			break;
		CodeLen=gpSyser->m_SyserUI.m_CodeDoc.IsPrevCodeCallInstr(Frame.CallReturn,szSymbol,&Address);
		if(CodeLen)
		{
			if(*szSymbol==0)//找不到符号就用模块名+偏移形式
			{
				pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
				if(pDbgModule==NULL && gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
					pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
				if(pDbgModule)
					TSPrintf(szSymbol,"%s+0x%X",(PCSTR)pDbgModule->m_ModuleTitle,Address-pDbgModule->m_ModuleBase);
				else
					TSPrintf(szSymbol,"unknown_function");
			}
			Iter=m_CallFrameList.Append();
			Iter->FrameAddress = FrameAddress;
			Iter->CallReturn = Frame.CallReturn;
			Iter->FuncAddr = Address;
			Iter->FuncName = szSymbol;
		}
		FrameAddress=Frame.PrevFrame;
	}
	if(m_CallFrameList.Count())
		m_pCurCallFrame = &(*m_CallFrameList.Begin());
}

void CCallStack::UpdateContext1(ULPOS EBP)
{
	ULSIZE CodeLen;
	ULPOS Address,FrameAddress;
	CHAR szSymbol[MAX_SYMBOL_LEN];
	FRAME_ENTRY Frame;
	CDbgModule*pDbgModule;
	TList<CALL_FRAME>::IT Iter;
	
	m_pCurCallFrame = NULL;
	FrameAddress = EBP?EBP:*X86_REG_PTR.pEBP;
	if(m_PrevEBP == FrameAddress)
		return;
	m_PrevEBP = FrameAddress;
	m_CallFrameList.Clear();
	for(int n=0;n<MAX_CALL_STACK_COUNT;n++)
	{
		if(gpSyser->m_pDebugger->ReadMemory(FrameAddress,&Frame,sizeof(Frame))!=sizeof(Frame))
			break;
		CodeLen=gpSyser->m_SyserUI.m_CodeDoc.IsPrevCodeCallInstr(Frame.CallReturn,szSymbol,&Address);
		if(CodeLen)
		{
			if(*szSymbol==0)//找不到符号就用模块名+偏移形式
			{
				pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
				if(pDbgModule==NULL && gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
					pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
				if(pDbgModule)
					TSPrintf(szSymbol,"%s+0x%X",(PCSTR)pDbgModule->m_ModuleTitle,Address-pDbgModule->m_ModuleBase);
				else
					TSPrintf(szSymbol,"unknown_function");
			}
			Iter=m_CallFrameList.Append();
			Iter->FrameAddress = FrameAddress;
			Iter->CallReturn = Frame.CallReturn;
			Iter->FuncAddr = Address;
			Iter->FuncName = szSymbol;
		}
	}
	if(m_CallFrameList.Count())
		m_pCurCallFrame = &(*m_CallFrameList.Begin());
}