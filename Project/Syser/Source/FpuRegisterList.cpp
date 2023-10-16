#include "StdAfx.h"
#include "Syser.h"

WISP_MSG_MAP_BEGIN(CFpuRegisterList)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
WISP_MSG_MAP_END(CWispList)

bool CFpuRegisterList::OnCreate(IN WISP_MSG*pMsg)
{
	m_ChgColor = ColorOption.clrChgText;
	m_NormalColor = ColorOption.clrText;
	m_SelectBKColor = ColorOption.clrSelectedFrame;

	SetDefaultTextColor(m_NormalColor);
	SetBGColor(ColorOption.clrBackground);

	InsertColumn(WISP_STR("Register"),90);
	InsertColumn(WISP_STR("Value"),180,WISP_WLCS_EDITABLE);
	m_hFpuRegItem[FPU_REG_ST_0] = InsertItem(WISP_STR("ST(0)"));
	m_hFpuRegItem[FPU_REG_ST_1] = InsertItem(WISP_STR("ST(1)"));
	m_hFpuRegItem[FPU_REG_ST_2] = InsertItem(WISP_STR("ST(2)"));
	m_hFpuRegItem[FPU_REG_ST_3] = InsertItem(WISP_STR("ST(3)"));
	m_hFpuRegItem[FPU_REG_ST_4] = InsertItem(WISP_STR("ST(4)"));
	m_hFpuRegItem[FPU_REG_ST_5] = InsertItem(WISP_STR("ST(5)"));
	m_hFpuRegItem[FPU_REG_ST_6] = InsertItem(WISP_STR("ST(6)"));
	m_hFpuRegItem[FPU_REG_ST_7] = InsertItem(WISP_STR("ST(7)"));
	m_hFpuRegItem[FPU_REG_STATE] = InsertItem(WISP_STR("FPU Status Word"));
	m_hFpuRegItem[FPU_REG_STATUS_B] = InsertItem(WISP_STR("FPU Busy"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_C3] = InsertItem(WISP_STR("Condition Code 3"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_TOP] = InsertItem(WISP_STR("Top of Stack Pointer"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_C2] = InsertItem(WISP_STR("Condition Code 2"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_C1] = InsertItem(WISP_STR("Condition Code 1"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_C0] = InsertItem(WISP_STR("Condition Code 0"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_ES] = InsertItem(WISP_STR("Error Summary Status"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_SF] = InsertItem(WISP_STR("Stack Fault"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_PE] = InsertItem(WISP_STR("Precision Exception"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_UE] = InsertItem(WISP_STR("Underflow Exception"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_OE] = InsertItem(WISP_STR("Overflow Exception"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_ZE] = InsertItem(WISP_STR("Zero Divide Exception"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_DE] = InsertItem(WISP_STR("Denormalized Exception"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_STATUS_IE] = InsertItem(WISP_STR("Invalid Operation Exception"),m_hFpuRegItem[FPU_REG_STATE]);
	m_hFpuRegItem[FPU_REG_CONTROL] = InsertItem(WISP_STR("FPU Control Word"));
	m_hFpuRegItem[FPU_REG_CONTROL_X] = InsertItem(WISP_STR("Infinity Control"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_RC] = InsertItem(WISP_STR("Rounding Control"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_PC] = InsertItem(WISP_STR("Precision Control"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_PM] = InsertItem(WISP_STR("Precision Mask"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_UM] = InsertItem(WISP_STR("Underflow Mask"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_OM] = InsertItem(WISP_STR("Overflow Mask"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_ZM] = InsertItem(WISP_STR("Zero Divide Mask"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_DM] = InsertItem(WISP_STR("Denormal Mask"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_CONTROL_IM] = InsertItem(WISP_STR("Invalid Mask"),m_hFpuRegItem[FPU_REG_CONTROL]);
	m_hFpuRegItem[FPU_REG_TAG_WORD] = InsertItem(WISP_STR("FPU Tag word"));
	m_hFpuRegItem[FPU_REG_TAG_0] = InsertItem(WISP_STR("TAG(0)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);
	m_hFpuRegItem[FPU_REG_TAG_1] = InsertItem(WISP_STR("TAG(1)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);
	m_hFpuRegItem[FPU_REG_TAG_2] = InsertItem(WISP_STR("TAG(2)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);
	m_hFpuRegItem[FPU_REG_TAG_3] = InsertItem(WISP_STR("TAG(3)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);
	m_hFpuRegItem[FPU_REG_TAG_4] = InsertItem(WISP_STR("TAG(4)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);
	m_hFpuRegItem[FPU_REG_TAG_5] = InsertItem(WISP_STR("TAG(5)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);
	m_hFpuRegItem[FPU_REG_TAG_6] = InsertItem(WISP_STR("TAG(6)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);
	m_hFpuRegItem[FPU_REG_TAG_7] = InsertItem(WISP_STR("TAG(7)"),m_hFpuRegItem[FPU_REG_TAG_WORD]);

	ResetContext();
	return true;
}

bool CFpuRegisterList::OnGetFocus(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetNextItem(NULL);
	if(hItem)
		SelectItem(hItem);
	return true;
}

void CFpuRegisterList::UpdateContext()
{
	WISP_CHAR ValueBuf[5000];
	WORD wValue;
	BYTE *Value;
	int i,j;
	FPU_STATUS_REG *pFPUStatus;
	FPU_CONTROL_REG* pFPUControl;
	FPU_TAG_WORD_REG* pFPUTagWord;
	FPU_STATUS_REG *pOldFPUStatus;
	FPU_CONTROL_REG* pOldFPUControl;
	FPU_TAG_WORD_REG* pOldFPUTagWord;
	double dValue=98.123;
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false || IsWindow()==false)
		return;
	DWORD dwCurrentCpuID=0;
#ifdef CODE_OS_NT_DRV	
	dwCurrentCpuID = GetCurrentCPULocalAPICID();
#endif


	if(dwCurrentCpuID!=m_nCPUIndex)	
		gpSyser->m_pDebugger->GetCPUX86RegPtr(&m_X86RegPtr,m_nCPUIndex);
	else
		m_X86RegPtr=X86_REG_PTR;


#ifdef CODE_OS_NT_DRV
	pFPUStatus =(FPU_STATUS_REG *) &FpuRegisterImage[CurrentFpuImageIndex][4];
	pFPUControl = (FPU_CONTROL_REG*)&FpuRegisterImage[CurrentFpuImageIndex][0];
	pFPUTagWord = (FPU_TAG_WORD_REG*)&FpuRegisterImage[CurrentFpuImageIndex][8];
	pOldFPUStatus =(FPU_STATUS_REG *) &FpuRegisterImage[CurrentFpuImageIndex ^ 1][4];
	pOldFPUControl = (FPU_CONTROL_REG*)&FpuRegisterImage[CurrentFpuImageIndex ^ 1][0];
	pOldFPUTagWord = (FPU_TAG_WORD_REG*)&FpuRegisterImage[CurrentFpuImageIndex ^ 1][8];
	Value=(BYTE *)&FpuRegisterImage[CurrentFpuImageIndex][28];
	memcpy(&m_PrevFPUStatus,FpuRegisterImage[CurrentFpuImageIndex ^ 1],sizeof(m_PrevFPUStatus));
#else 
	pFPUStatus =(FPU_STATUS_REG *) m_X86RegPtr.pFPUStatusWord;
	pFPUControl = (FPU_CONTROL_REG*)m_X86RegPtr.pFPUControlWord;
	pFPUTagWord = (FPU_TAG_WORD_REG*)m_X86RegPtr.pFPUTagWord;
	pOldFPUStatus =(FPU_STATUS_REG *) &m_PrevFPUStatus.ControlWord;
	pOldFPUControl = (FPU_CONTROL_REG*)&m_PrevFPUStatus.StatusWord;
	pOldFPUTagWord = (FPU_TAG_WORD_REG*)&m_PrevFPUStatus.TagWord;
	Value=(BYTE *)m_X86RegPtr.pFPURegisterArea;
#endif
	for(i = 0; i < 8;i++)
	{		
		
		TSPrintf(ValueBuf,WSTR("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x"),
			Value[0],
			Value[1],
			Value[2],
			Value[3],
			Value[4],
			Value[5],
			Value[6],
			Value[7],
			Value[8],
			Value[9]);
		SetItemText(m_hFpuRegItem[i],1,ValueBuf);
		
		for(j=0;j<10;j++)
		{
			if(Value[j]!=m_PrevFPUStatus.Reg[i][j])
			//if(FpuRegisterImage[0][28+j+10*i]!=FpuRegisterImage[1][28+j+10*i])
			{
				SetItemTextColor(m_hFpuRegItem[i],1,m_ChgColor);
				break;
			}
		}
		if(j==10)
			SetItemTextColor(m_hFpuRegItem[i],1,m_NormalColor);
		Value=Value+10;
	}	

	//show FPU status register
	wValue = *(WORD*)pFPUStatus;
	TSPrintf(ValueBuf,WSTR("%04x"),wValue);			
	SetItemText(m_hFpuRegItem[FPU_REG_STATE],1,ValueBuf);	
	if(*(WORD*)pFPUStatus != *(WORD*)pOldFPUStatus)	
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATE],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATE],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_IE],1,pFPUStatus->IE?WSTR("1"):WSTR("0"));
	if(pFPUStatus->IE !=pOldFPUStatus->IE)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_IE],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_IE],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_DE],1,pFPUStatus->DE?WSTR("1"):WSTR("0"));
	if(pFPUStatus->DE !=pOldFPUStatus->DE)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_DE],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_DE],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_ZE],1,pFPUStatus->ZE?WSTR("1"):WSTR("0"));
	if(pFPUStatus->ZE !=pOldFPUStatus->ZE)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_ZE],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_ZE],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_OE],1,pFPUStatus->OE?WSTR("1"):WSTR("0"));
	if(pFPUStatus->OE !=pOldFPUStatus->OE)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_OE],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_OE],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_UE],1,pFPUStatus->UE?WSTR("1"):WSTR("0"));
	if(pFPUStatus->UE !=pOldFPUStatus->UE)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_UE],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_UE],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_PE],1,pFPUStatus->PE?WSTR("1"):WSTR("0"));
	if(pFPUStatus->PE !=pOldFPUStatus->PE)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_PE],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_PE],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_SF],1,pFPUStatus->SF?WSTR("1"):WSTR("0"));
	if(pFPUStatus->SF !=pOldFPUStatus->SF)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_SF],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_SF],1,m_NormalColor);
	
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_ES],1,pFPUStatus->ES?WSTR("1"):WSTR("0"));
	if(pFPUStatus->ES !=pOldFPUStatus->ES)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_ES],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_ES],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C0],1,pFPUStatus->C0?WSTR("1"):WSTR("0"));
	if(pFPUStatus->C0 !=pOldFPUStatus->C0)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C0],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C0],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C1],1,pFPUStatus->C1?WSTR("1"):WSTR("0"));
	if(pFPUStatus->C1 !=pOldFPUStatus->C1)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C1],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C1],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C2],1,pFPUStatus->C2?WSTR("1"):WSTR("0"));
	if(pFPUStatus->C2 !=pOldFPUStatus->C2)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C2],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C2],1,m_NormalColor);

	TSPrintf(ValueBuf,WSTR("%x"),pFPUStatus->TOP);
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_TOP],1,ValueBuf);
	if(pFPUStatus->TOP !=pOldFPUStatus->TOP)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_TOP],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_TOP],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C3],1,pFPUStatus->C3?WSTR("1"):WSTR("0"));
	if(pFPUStatus->C3 !=pOldFPUStatus->C3)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C3],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_C3],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_B],1,pFPUStatus->B?WSTR("1"):WSTR("0"));
	if(pFPUStatus->B !=pOldFPUStatus->B)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_B],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_STATUS_B],1,m_NormalColor);

	//show FPU control register
	wValue = *(WORD*)pFPUControl;
	TSPrintf(ValueBuf,WSTR("%04x"),wValue);
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL],1,ValueBuf);
	if(*(WORD*)pFPUControl != *(WORD*)pOldFPUControl)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_X],1,pFPUControl->X?WSTR("1"):WSTR("0"));
	if(pFPUControl->X !=pFPUControl->X)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_X],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_X],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_CONTROL_RC],1,pFPUControl->RC);
	if(pFPUControl->RC !=pFPUControl->RC)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_RC],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_RC],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_CONTROL_PC],1,pFPUControl->PC);
	if(pFPUControl->PC !=pFPUControl->PC)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_PC],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_PC],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_PM],1,pFPUControl->PM?WSTR("1"):WSTR("0"));
	if(pFPUControl->PM !=pFPUControl->PM)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_PM],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_PM],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_UM],1,pFPUControl->UM?WSTR("1"):WSTR("0"));
	if(pFPUControl->UM !=pFPUControl->UM)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_UM],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_UM],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_OM],1,pFPUControl->OM?WSTR("1"):WSTR("0"));
	if(pFPUControl->OM !=pFPUControl->OM)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_OM],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_OM],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_ZM],1,pFPUControl->ZM?WSTR("1"):WSTR("0"));
	if(pFPUControl->ZM !=pFPUControl->ZM)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_ZM],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_ZM],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_DM],1,pFPUControl->DM?WSTR("1"):WSTR("0"));
	if(pFPUControl->DM !=pFPUControl->DM)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_DM],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_DM],1,m_NormalColor);

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_IM],1,pFPUControl->IM?WSTR("1"):WSTR("0"));
	if(pFPUControl->IM !=pFPUControl->IM)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_IM],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_CONTROL_IM],1,m_NormalColor);

	//show fpu tag word register
	wValue = *(WORD*)pFPUTagWord;
	TSPrintf(ValueBuf,WSTR("%04x"),wValue);	
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_WORD],1,ValueBuf);
	if(*(WORD*)pFPUTagWord != *(WORD*)pFPUTagWord)	
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_WORD],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_WORD],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_0],1,pFPUTagWord->TAG0);
	if(pFPUTagWord->TAG0 != pOldFPUTagWord->TAG0)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_0],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_0],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_1],1,pFPUTagWord->TAG1);
	if(pFPUTagWord->TAG1 != pOldFPUTagWord->TAG1)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_1],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_1],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_2],1,pFPUTagWord->TAG2);
	if(pFPUTagWord->TAG2 != pOldFPUTagWord->TAG2)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_2],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_2],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_3],1,pFPUTagWord->TAG3);
	if(pFPUTagWord->TAG3 != pOldFPUTagWord->TAG3)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_3],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_3],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_4],1,pFPUTagWord->TAG4);
	if(pFPUTagWord->TAG4 != pOldFPUTagWord->TAG4)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_4],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_4],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_5],1,pFPUTagWord->TAG5);
	if(pFPUTagWord->TAG5 != pOldFPUTagWord->TAG5)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_5],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_5],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_6],1,pFPUTagWord->TAG6);
	if(pFPUTagWord->TAG6 != pOldFPUTagWord->TAG6)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_6],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_6],1,m_NormalColor);

	SetItemNum(m_hFpuRegItem[FPU_REG_TAG_7],1,pFPUTagWord->TAG7);
	if(pFPUTagWord->TAG7 != pOldFPUTagWord->TAG7)
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_7],1,m_ChgColor);
	else
		SetItemTextColor(m_hFpuRegItem[FPU_REG_TAG_7],1,m_NormalColor);

}


void CFpuRegisterList::ResetContext()
{
	SelectItem(m_hFpuRegItem[FPU_REG_ST_0]);
	SetItemText(m_hFpuRegItem[FPU_REG_ST_0],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_ST_1],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_ST_2],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_ST_3],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_ST_4],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_ST_5],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_ST_6],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_ST_7],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATE],1,WSTR("????????"));

	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_B],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C3],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_TOP],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C2],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C1],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_C0],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_ES],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_SF],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_PE],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_UE],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_OE],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_ZE],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_DE],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_STATUS_IE],1,WSTR("????????"));

	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_X],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_RC],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_PC],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_PM],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_UM],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_OM],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_ZM],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_DM],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_CONTROL_IM],1,WSTR("????????"));

	SetItemText(m_hFpuRegItem[FPU_REG_TAG_WORD],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_0],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_1],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_2],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_3],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_4],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_5],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_6],1,WSTR("????????"));
	SetItemText(m_hFpuRegItem[FPU_REG_TAG_7],1,WSTR("????????"));
	memset(&m_PrevFPUStatus,0,sizeof(m_PrevFPUStatus));
	
}

