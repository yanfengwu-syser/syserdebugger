#include "StdAfx.h"
#include "Syser.h"

WISP_MSG_MAP_BEGIN(CGDTWnd) 
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
WISP_MSG_MAP_END(CWispList)

CGDTWnd::CGDTWnd()
{
#ifdef CODE_OS_WIN
	m_pGDTAddress = gdtdata;
	m_dwGDTSize = 0x7FF;
#else
	m_pGDTAddress = (void *)SyserGetGDTBase(&m_dwGDTSize);
#endif
	m_dwBeginIndex = 0;
}

CGDTWnd::~CGDTWnd()
{
}


void CGDTWnd::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WSTR("GDT"),CWispRect(0,0,540,350),NULL,0,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL);
		Center();
	}
}

bool CGDTWnd::OnCreate(IN WISP_MSG*pMsg)
{
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);
	InsertColumn(WISP_STR("Selector"),40);
	InsertColumn(WISP_STR("Type"),80);
	InsertColumn(WISP_STR("Base"),90);
	InsertColumn(WISP_STR("Limit"),100);
	InsertColumn(WISP_STR("DPL"),90);
	InsertColumn(WISP_STR("Attributes"),90);
	SetWindowText(WISP_STR("GDT TABLE"));
	UpdateContext();
	return true;
}

bool CGDTWnd::OnClose(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}

void CGDTWnd::UpdateContext()
{
	ClearChildItem();
	InsertGDT();
}

bool CGDTWnd::InsertGDT()
{	
	WISP_CHAR display[64];
	HANDLE hItem;
	DWORD dwSelector=0,dwGDTSize,dwShowSelector;
	VADDR32 dwGDTBase = 0;
//	DWORD dwLow,dwHigh;
	DWORD dwSegmentBase,dwSegmentLimit;
	DWORD i = 0,j;	
	bool	bLDTCommand = false;
	X86_SEGMENT_DESCRIPTOR *pSegDesc;
	//int nOrgArgc;
	WCHAR *Format=WSTR("%04x  %s  %08x  %08x  %d    %s  %s %s");
//	X86_GATE_DECR *GateDecr;
	
	static WCHAR *DescType[16]={
		WSTR("Reserved"),
		WSTR("TSS16   "),
		WSTR("LDT     "),
		WSTR("TSS32   "),
		WSTR("CallG16 "),
		WSTR("TaskG   "),
		WSTR("IntG16  "),
		WSTR("TrapG16 "),
		WSTR("Reserved"),
		WSTR("TSS32   "),
		WSTR("Reserved"),
		WSTR("TSS32   "),
		WSTR("CallG32 "),
		WSTR("Reserved"),
		WSTR("IntG32  "),
		WSTR("TrapG32 "),
	};
	dwGDTBase = PTR_TO_NUM(m_pGDTAddress);
	dwGDTSize = m_dwGDTSize;
	j = (dwGDTSize + 1) / sizeof(X86_SEGMENT_DESCRIPTOR);
	pSegDesc = (X86_SEGMENT_DESCRIPTOR *)NUM_TO_PTR(dwGDTBase);
		
		for(i = 0; i < j; i++)
		{
			dwSegmentBase = (pSegDesc[i].base_H1<<24) |(pSegDesc[i].base_H0 << 16)|(pSegDesc[i].base_L1 << 8)|pSegDesc[i].base_L0;
			dwSegmentLimit = (pSegDesc[i].limit_H << 16) | (pSegDesc[i].limit_L1<<8)|pSegDesc[i].limit_L0;
			if(!pSegDesc[i].P)
			{
				TSPrintf(display,WISP_STR("%04X"),bLDTCommand ? (i * 8) | 4 |pSegDesc[i].DPL:(i*8)|pSegDesc[i].DPL);
				hItem = InsertItem(display);
				SetItemText(hItem,1,DescType[pSegDesc[i].TYPE]);
				TSPrintf(display,WISP_STR("%08X"),dwSegmentBase);
				SetItemText(hItem,2,display);
				TSPrintf(display,WISP_STR("%08X"),dwSegmentLimit);
				SetItemText(hItem,3,display);
				TSPrintf(display,WISP_STR("%d"),pSegDesc[i].DPL);
				SetItemText(hItem,4,display);
				SetItemText(hItem,5,WISP_STR("NP      "));				
				continue;
			}
			dwShowSelector = (i*8)|pSegDesc[i].DPL;
			if(bLDTCommand)
				dwShowSelector |= 4;
			if(pSegDesc[i].DT)//�洢��������
			{
				if(pSegDesc[i].G)
					dwSegmentLimit = (dwSegmentLimit << 12) | 0xfff;					
				TSPrintf(display,WISP_STR("%04X"),dwShowSelector);
				hItem = InsertItem(display);
				if(pSegDesc[i].TYPE & 8)//�����
					SetItemText(hItem,1,pSegDesc[i].D ? WSTR("Code32  "):WSTR("Code16  "));
				else
					SetItemText(hItem,1,pSegDesc[i].D ? WSTR("Data32  "):WSTR("Data16  "));
				TSPrintf(display,WISP_STR("%08X"),dwSegmentBase);
				SetItemText(hItem,2,display);
				TSPrintf(display,WISP_STR("%08X"),dwSegmentLimit);
				SetItemText(hItem,3,display);
				TSPrintf(display,WISP_STR("%d"),pSegDesc[i].DPL);				
				SetItemText(hItem,4,display);
				if(pSegDesc[i].TYPE & 8)//�����
				TSPrintf(display,WISP_STR("P  %s %s"),(pSegDesc[i].TYPE & 2) ? WSTR("RE") : WSTR("EO"),(pSegDesc[i].TYPE & 4) ?WSTR("C "):WSTR("  "));
				else
					TSPrintf(display,WISP_STR("P  %s %s"),(pSegDesc[i].TYPE & 2) ? WSTR("RW") : WSTR("RO"),(pSegDesc[i].TYPE & 4) ? WSTR("ED"):WSTR("  "));
				SetItemText(hItem,5,display);								
				continue;
			}
#if 0			
			//ϵͳ��������
			if(	pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_16TSS_AVAIL ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_LDT ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_16TSS_BUSY ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_32TSS_AVAIL ||
				pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_32TSS_BUSY)
			{
				if(pSegDesc[i].TYPE == SYS_SEG_GATE_DECR_TYPE_LDT)
				{										
					if((nOrgArgc == 2) && (TStrICmp(argv[0],WSTR("LDT")) == 0) && (dwSelector >> 3) == i)
					{	
						WCHAR NewCommandArgc[10];
						WCHAR NewCommandArgc1[10];
						TSPrintf(NewCommandArgc,WSTR("%08x"),dwSegmentBase);
						TSPrintf(NewCommandArgc1,WSTR("%08x"),dwSegmentLimit);
						WCHAR* newargv[]={WSTR("ldtlist"),NewCommandArgc,NewCommandArgc1,NULL};
						gdt_command(9999,newargv,gpSyser);						
						return;
					}	
					else
						OUTPUT(Format,dwShowSelector,DescType[pSegDesc[i].TYPE],dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "),WSTR("  "),WSTR("  "));
				}
				else				
					OUTPUT(Format,dwShowSelector,DescType[pSegDesc[i].TYPE],dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "),(pSegDesc[i].TYPE & 2) ? WSTR("B "):WSTR("  "),WSTR("  "));
				continue;
			}
			GateDecr = (X86_GATE_DECR* )(&pSegDesc[i]);
			dwSegmentLimit = GateDecr->OffsetLow | (GateDecr->OffsetHigh << 16);
			dwSegmentBase = GateDecr->Selector;
			if(GateDecr->Type == SYS_SEG_GATE_DECR_TYPE_TASK_GATE)
			{
				continue;
			}

			if((GateDecr->Type == SYS_SEG_GATE_DECR_TYPE_32CALL_GATE) && (GateDecr->Type == SYS_SEG_GATE_DECR_TYPE_16CALL_GATE))
				OUTPUT(WSTR("%04x  %s  %04x:%08x       %d    %s"),dwShowSelector,DescType[pSegDesc[i].TYPE],dwSegmentBase,dwSegmentLimit,pSegDesc[i].DPL,WSTR("P "));
#endif
		}
	return true;
}
void	SetGDTBaseAddress(void *IDTBase,DWORD dwIDTSize,DWORD dwIndex)
{

}
//DWORD GetIDTBase()
//dwIDTBase = GetIDTBase(&dwIDTSize);	

BYTE CGDTWnd::gdtdata[8*256]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x9B,0xCF,0x00,
0xFF,0xFF,0x00,0x00,0x00,0x93,0xCF,0x00,0xFF,0xFF,0x00,0x00,0x00,0xFB,0xCF,0x00,
0xFF,0xFF,0x00,0x00,0x00,0xF3,0xCF,0x00,0xAB,0x20,0x00,0x20,0x04,0x8B,0x00,0x80,
0x01,0x00,0x00,0xF0,0xDF,0x93,0xC0,0xFF,0xFF,0x0F,0x00,0x00,0x00,0xF3,0x40,0x00,
0xFF,0xFF,0x00,0x04,0x00,0xF2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x68,0x00,0x00,0x32,0x54,0x89,0x00,0x80,0x68,0x00,0x68,0x32,0x54,0x89,0x00,0x80,
0xFF,0xFF,0x20,0x2F,0x02,0x93,0x00,0x00,0xFF,0x3F,0x00,0x80,0x0B,0x92,0x00,0x00,
0xFF,0x03,0x00,0x70,0xFF,0x92,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x40,0x9A,0x00,0x80,
0xFF,0xFF,0x00,0x00,0x40,0x92,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x92,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x68,0x00,0xB8,0xEB,0xBD,0x89,0x00,0x81,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x20,0xA9,0x9F,0x00,0xF9,0xFF,0xFF,0x00,0x00,0x00,0x92,0x00,0x00,
0xCE,0x25,0xD0,0x31,0x50,0x98,0x0F,0x80,0xFF,0xFF,0x00,0x00,0x00,0x92,0x00,0x00,
0xFF,0xFF,0x00,0x20,0xAA,0x93,0x40,0xF9,0xFF,0xFF,0x00,0x20,0xAA,0x93,0x40,0xF9,
0xFF,0xFF,0x00,0x20,0xAA,0x93,0x40,0xF9,0x20,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x28,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x30,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x38,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x40,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x48,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x50,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x58,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x60,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x68,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x70,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x78,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x80,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x88,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x90,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0x98,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0xA0,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0xA8,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0xB0,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0xB8,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0xC0,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0xC8,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0xD0,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0xD8,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0xE0,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0xE8,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0xF0,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,
0xF8,0xF1,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x08,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x10,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x18,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x20,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x28,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x30,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x38,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x40,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x48,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x50,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x58,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x60,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x68,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x70,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x78,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x80,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x88,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x90,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0x98,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0xA0,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0xA8,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0xB0,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0xB8,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0xC0,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0xC8,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0xD0,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0xD8,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0xE0,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0xE8,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0xF0,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,
0xF8,0xF2,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x08,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x10,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x18,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x20,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x28,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x30,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x38,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x40,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x48,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x50,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x58,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x60,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x68,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x70,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x78,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x80,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x88,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x90,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0x98,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0xA0,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0xA8,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0xB0,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0xB8,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0xC0,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0xC8,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0xD0,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0xD8,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0xE0,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0xE8,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0xF0,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,
0xF8,0xF3,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x22,0xBC,0x08,0x00,0x00,0x8E,0x4D,0x80,0x69,0xAF,0x08,0x00,0x00,0xEE,0xF0,0xF1,
0x78,0xAF,0x08,0x00,0x00,0x8E,0xF0,0xF1,0x87,0xAF,0x08,0x00,0x00,0xEE,0xF0,0xF1,
0xE5,0xC1,0x08,0x00,0x00,0xEE,0x4D,0x80,0x26,0xC3,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x96,0xAF,0x08,0x00,0x00,0x8E,0xF0,0xF1,0x57,0xCA,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x78,0x11,0x50,0x00,0x00,0x85,0x00,0x00,0x71,0xCE,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x74,0xCF,0x08,0x00,0x00,0x8E,0x4D,0x80,0xA5,0xAF,0x08,0x00,0x00,0x8E,0xF0,0xF1,
0xB4,0xAF,0x08,0x00,0x00,0x8E,0xF0,0xF1,0xC3,0xAF,0x08,0x00,0x00,0x8E,0xF0,0xF1,
0xD2,0xAF,0x08,0x00,0x00,0x8E,0xF0,0xF1,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4F,0xE0,0x08,0x00,0x00,0x8E,0x4D,0x80,0x6A,0xE1,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xDF,0xA0,0x00,0x00,0x85,0x4D,0x80,0xB6,0xE2,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,
0xF6,0xB4,0x08,0x00,0x00,0xEE,0x4D,0x80,0xE1,0xB5,0x08,0x00,0x00,0xEE,0x4D,0x80,
0x44,0xB7,0x08,0x00,0x00,0xEE,0x4D,0x80,0xF0,0xAF,0x08,0x00,0x00,0xEE,0xF0,0xF1,
0xFF,0xAF,0x08,0x00,0x00,0xEE,0xF0,0xF1,0x4C,0xDF,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xC0,0xE4,0x08,0x00,0x00,0x8E,0x6C,0x80,0x0E,0xB0,0x08,0x00,0x00,0x8E,0xF0,0xF1,
0x84,0xA7,0x08,0x00,0x00,0x8E,0x4D,0x80,0x1D,0xB0,0x08,0x00,0x00,0x8E,0xF0,0xF1,
0x2C,0xB0,0x08,0x00,0x00,0x8E,0xF0,0xF1,0x9C,0x15,0x08,0x00,0x00,0x8E,0xA2,0x81,
0xAC,0xA7,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4A,0xB0,0x08,0x00,0x00,0x8E,0xF0,0xF1,
0x80,0x8E,0x08,0x00,0x00,0x8E,0x6C,0x80,0x6C,0x52,0x08,0x00,0x00,0x8E,0xBC,0x81,
0xD4,0xED,0x08,0x00,0x00,0x8E,0x90,0x81,0xF4,0xF2,0x08,0x00,0x00,0x8E,0x9E,0x81,
0x3B,0xB0,0x08,0x00,0x00,0x8E,0xF0,0xF1,0xF2,0xA7,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xE4,0x66,0x08,0x00,0x00,0x8E,0xBB,0x81,0x2C,0x1B,0x08,0x00,0x00,0x8E,0xB7,0x81,
0x10,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0xE1,0xAF,0x08,0x00,0x00,0xEE,0xF0,0xF1,
0x24,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0x2E,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x38,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0x42,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x4C,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0x56,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x60,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0x6A,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x74,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0x7E,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x88,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0x92,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x9C,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0xA6,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xB0,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0xBA,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xC4,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0xCE,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xD8,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0xE2,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xEC,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,0xF6,0xA8,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x00,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x0A,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x14,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x1E,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x28,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x32,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x3C,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x46,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x50,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x5A,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x64,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x6E,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x78,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x82,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x8C,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0x96,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xA0,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0xAA,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xB4,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0xBE,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xC8,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0xD2,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xDC,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0xE6,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0xF0,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,0xFA,0xA9,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x04,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,0x0E,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x18,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,0x22,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x2C,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,0x36,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x40,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,0x4A,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x54,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,0x5E,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x68,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,0x72,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,
0x7C,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,0x86,0xAA,0x08,0x00,0x00,0x8E,0x4D,0x80,
};

