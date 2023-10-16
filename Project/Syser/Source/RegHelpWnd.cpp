#include "StdAfx.h"
#include "RegHelpWnd.h" 
REGISTERBITNAME PageDirEntry4K[]={
	{WSTR("Page-Table Base Address"),31,20,NULL},	
	{WSTR("Avail"),11,3,WSTR("Available for system programmer's use")},
	{WSTR("G"),8,1,WSTR("Global page (Ignored)")},
	{WSTR("P\nS"),7,1,WSTR("Page size(0 indicates 4 KBytes)")},
	{WSTR("0"),6,1,WSTR("Reserved (set to 0)")},
	{WSTR("A"),5,1,WSTR("Accessed")},
	{WSTR("P\nC\nD"),4,1,WSTR("Cache disabled")},
	{WSTR("P\nW\nT"),3,1,WSTR("Write-through")},
	{WSTR("U\n/\nS"),2,1,WSTR("User/Supervisor")},
	{WSTR("R\n/\nW"),1,1,WSTR("Read/Write")},
	{WSTR("P"),0,1,WSTR("Present")},
	{NULL,0,0,NULL},
};

REGISTERBITNAME PageTabEntry4K[]={
	{WSTR("Page Base Address"),31,20,NULL},	
	{WSTR("Avail"),11,3,WSTR("Available for system programmer's use")},
	{WSTR("G"),8,1,WSTR("Global Page")},
	{WSTR("P\nA\nT"),7,1,WSTR("Page Table Attribute Index")},
	{WSTR("D"),6,1,WSTR("Dirty")},
	{WSTR("A"),5,1,WSTR("Accessed")},
	{WSTR("P\nC\nD"),4,1,WSTR("Cache disabled")},
	{WSTR("P\nW\nT"),3,1,WSTR("Write-through")},
	{WSTR("U\n/\nS"),2,1,WSTR("User/Supervisor")},
	{WSTR("R\n/\nW"),1,1,WSTR("Read/Write")},
	{WSTR("P"),0,1,WSTR("Present")},
	{NULL,0,0,NULL},
};


REGISTERBITNAME PageDirEntry4M[]={
	{WSTR("Page Base Address"),31,10,NULL},
	{WSTR("Reserved"),21,9,NULL},
	{WSTR("P\nA\nT"),12,1,WSTR("Page Table Attribute Index")},
	{WSTR("Avail."),11,3,WSTR("Available for system programmer's use")},
	{WSTR("G"),8,1,WSTR("Global page")},
	{WSTR("P\nS"),7,1,WSTR("Page size(1 indicates 4 MBytes)")},
	{WSTR("D"),6,1,WSTR("Dirty")},
	{WSTR("A"),5,1,WSTR("Accessed")},
	{WSTR("P\nC\nD"),4,1,WSTR("Cache disabled")},
	{WSTR("P\nW\nT"),3,1,WSTR("Write-through")},
	{WSTR("U\n/\nS"),2,1,WSTR("User/Supervisor")},
	{WSTR("R\n/\nW"),1,1,WSTR("Read/Write")},
	{WSTR("P"),0,1,WSTR("Present")},
	{NULL,0,0,NULL},
};
REGISTERBITNAME DataSegmentDesc0[]={
	{WSTR("Base 31:24"),31,8,NULL},
	{WSTR("G"),23,1,NULL},
	{WSTR("B"),22,1,NULL},
	{WSTR("0"),21,1,NULL},
	{WSTR("A\nV\nL"),20,1,NULL},
	{WSTR("Limit\n19:16"),19,4,NULL},
	{WSTR("P"),15,1,NULL},
	{WSTR("D\nP\nL"),14,2,NULL},
	{WSTR("1"),12,1,NULL},
	{WSTR("Type"),11,4,NULL},
	{WSTR("Base 23:16"),7,8,NULL},
	{NULL,0,0,NULL},
};
REGISTERBITNAME DataSegmentDesc1[]={
	{WSTR("Base Address 15:00"),31,16,NULL},
	{WSTR("Segment Limit 15:00"),15,16,NULL},
	{NULL,0,0,NULL},
};
REGISTERBITNAME CodeSegmentDesc0[]={
	{WSTR("Base 31:24"),31,8,NULL},
	{WSTR("G"),23,1,NULL},
	{WSTR("D"),22,1,NULL},
	{WSTR("0"),21,1,NULL},
	{WSTR("A\nV\nL"),20,1,NULL},
	{WSTR("Limit\n19:16"),19,4,NULL},
	{WSTR("P"),15,1,NULL},
	{WSTR("D\nP\nL"),14,2,NULL},
	{WSTR("1"),12,1,NULL},
	{WSTR("Type"),11,4,NULL},
	{WSTR("Base 23:16"),7,8,NULL},
	{NULL,0,0,NULL},
};
REGISTERBITNAME CodeSegmentDesc1[]={
	{WSTR("Base Address 15:00"),31,16,NULL},
	{WSTR("Segment Limit 15:00"),15,16,NULL},
	{NULL,0,0,NULL},
};
REGISTERBITNAME SystemSegmentDesc0[]={
	{WSTR("Base 31:24"),31,8,NULL},
	{WSTR("G"),23,1,NULL},	
	{WSTR("0"),21,1,NULL},	
	{WSTR("Limit\n19:16"),19,4,NULL},
	{WSTR("P"),15,1,NULL},
	{WSTR("D\nP\nL"),14,2,NULL},
	{WSTR("0"),12,1,NULL},
	{WSTR("Type"),11,4,NULL},
	{WSTR("Base 23:16"),7,8,NULL},
	{NULL,0,0,NULL},
};
REGISTERBITNAME SystemSegmentDesc1[]={
	{WSTR("Base Address 15:00"),31,16,NULL},
	{WSTR("Segment Limit 15:00"),15,16,NULL},
	{NULL,0,0,NULL},
};

REGISTERBITNAME stCR0Name[]={
	{WSTR("P\nG"),31,1,NULL},
	{WSTR("C\nD"),30,1,NULL},
	{WSTR("N\nW"),29,1,NULL},
	{WSTR("A\nM"),18,1,NULL},
	{WSTR("W\nP"),16,1,NULL},
	{WSTR("N\nE"),5,1,NULL},
	{WSTR("E\nT"),4,1,NULL},
	{WSTR("T\nS"),3,1,NULL},
	{WSTR("E\nM"),2,1,NULL},
	{WSTR("M\nP"),1,1,NULL},
	{WSTR("P\nE"),0,1,NULL},
	{NULL,0,0,NULL},
};

REGISTERBITNAME stCR2Name[]={
	{WSTR("Page-Fault Linear Address"),31,32,NULL},
	{NULL,0,0,NULL},
};

REGISTERBITNAME stCR3Name[]={
	{WSTR("Page-Directory Base"),31,20,NULL},
	{WSTR("P\nC\nD"),4,1,NULL},
	{WSTR("P\nW\nT"),3,1,NULL},
	{NULL,0,0,NULL},
};

REGISTERBITNAME stCR4Name[]={
	{WSTR("Reserved (Set to 0)"),31,21,NULL},
	{WSTR(""),10,1,WSTR("OSXMMEX")},
	{WSTR(""),9,1,WSTR("OSFXSR")},
	{WSTR("P\nC\nE"),8,1,NULL},
	{WSTR("P\nG\nE"),7,1,NULL},
	{WSTR("M\nC\nE"),6,1,NULL},
	{WSTR("P\nA\nE"),5,1,NULL},
	{WSTR("P\nS\nE"),4,1,NULL},
	{WSTR("D\nE"),3,1,NULL},
	{WSTR("T\nS\nD"),2,1,NULL},
	{WSTR("P\nV\nI"),1,1,NULL},
	{WSTR("V\nM\nE"),0,1,NULL},
	{NULL,0,0,NULL},
};
REGISTERBITNAME stEFlagsName[]={
	{WSTR("Reserved(set to 0)"),31,10,NULL},
	{WSTR("I\nD"),21,1,WSTR("ID   -- Identification Flag")},
	{WSTR("V\nI\nP"),20,1,WSTR("VIP  -- Virtual Interrupt Pending")},
	{WSTR("V\nI\nF"),19,1,WSTR("VIF  -- Virtual Interrupt Flag")},
	{WSTR("A\nC"),18,1,WSTR("AC   -- Alignment Check")},
	{WSTR("V\nM"),17,1,WSTR("VM   -- Virtual-8086 Mode")},
	{WSTR("R\nF"),16,1,WSTR("RF   -- Resume Flag")},
	{WSTR("0"),15,1,NULL},
	{WSTR("N\nT"),14,1,WSTR("NT   -- Nested Task Flag")},
	{WSTR("IOPL"),13,2,WSTR("IOPL -- I/O Privilege Level")},	
	{WSTR("O\nF"),11,1,NULL},
	{WSTR("D\nF"),10,1,NULL},
	{WSTR("I\nF"),9,1,WSTR("IF   -- Interrupt Enable Flag")},
	{WSTR("T\nF"),8,1,WSTR("TF   -- Trap Flag")},
	{WSTR("S\nF"),7,1,WSTR("SF   -- Sign Flag")},
	{WSTR("Z\nF"),6,1,WSTR("ZF   -- Zero Flag")},
	{WSTR("0"),5,1,NULL},
	{WSTR("A\nF"),4,1,WSTR("AF   -- Auxiliary Carry Flag")},
	{WSTR("0"),3,1,NULL},
	{WSTR("P\nF"),2,1,WSTR("PF   -- Parity Flag")},
	{WSTR("1"),1,1,NULL},
	{WSTR("C\nF"),0,1,WSTR("CF   -- Carry Flag")},
	{NULL,0,0,NULL},
};

REGISTERBITNAME stDR7Name[]={
	{WSTR("L\n0"),0,1,NULL},
	{WSTR("G\n0"),1,1,NULL},
	{WSTR("L\n1"),2,1,NULL},
	{WSTR("G\n1"),3,1,NULL},
	{WSTR("L\n2"),4,1,NULL},
	{WSTR("G\n2"),5,1,NULL},
	{WSTR("L\n3"),6,1,NULL},
	{WSTR("G\n3"),7,1,NULL},
	{WSTR("L\nE"),8,1,NULL},
	{WSTR("G\nE"),9,1,NULL},
	{WSTR("1"),10,1,NULL},
	{WSTR("0"),11,1,NULL},
	{WSTR("0"),12,1,NULL},
	{WSTR("G\nD"),13,1,NULL},
	{WSTR("0"),14,1,NULL},
	{WSTR("0"),15,1,NULL},
	{WSTR("R/W\n0"),17,2,NULL},
	{WSTR("LEN\n0"),19,2,NULL},
	{WSTR("R/W\n1"),21,2,NULL},
	{WSTR("LEN\n1"),23,2,NULL},
	{WSTR("R/W\n2"),25,2,NULL},
	{WSTR("LEN\n2"),27,2,NULL},
	{WSTR("R/W\n3"),29,2,NULL},
	{WSTR("LEN\n4"),31,2,NULL},
	{NULL,0,0,NULL},
};
REGISTERBITNAME stDR6Name[]={
	{WSTR("B\n0"),0,1,NULL},
	{WSTR("B\n1"),1,1,NULL},
	{WSTR("B\n2"),2,1,NULL},
	{WSTR("B\n3"),3,1,NULL},
	{WSTR("1"),4,1,NULL},
	{WSTR("1"),5,1,NULL},
	{WSTR("1"),6,1,NULL},
	{WSTR("1"),7,1,NULL},
	{WSTR("1"),8,1,NULL},
	{WSTR("1"),9,1,NULL},
	{WSTR("1"),10,1,NULL},
	{WSTR("1"),11,1,NULL},
	{WSTR("0"),12,1,NULL},
	{WSTR("B\nD"),13,1,NULL},
	{WSTR("B\nS"),14,1,NULL},
	{WSTR("B\nT"),15,1,NULL},
	{WSTR("Reserved(set to 1)"),31,16,NULL},	
	{NULL,0,0,NULL},
};
REGISTERBITNAME stDR5Name[]={	
	{WSTR("Reserved"),31,32,NULL},	
	{NULL,0,0,NULL},
};
REGISTERBITNAME stDR4Name[]={	
	{WSTR("Reserved"),31,32,NULL},	
	{NULL,0,0,NULL},
};
REGISTERBITNAME stDR3Name[]={
	{WSTR("Breakpoint Linear Address"),31,32,NULL},	
	{NULL,0,0,NULL},
};
REGISTERBITNAME stDR2Name[]={
	{WSTR("Breakpoint 2 Linear Address"),31,32,NULL},	
	{NULL,0,0,NULL},
};
REGISTERBITNAME stDR1Name[]={
	{WSTR("Breakpoint 1 Linear Address"),31,32,NULL},	
	{NULL,0,0,NULL},
};
REGISTERBITNAME stDR0Name[]={
	{WSTR("Breakpoint 0 Linear Address"),31,32,NULL},	
	{NULL,0,0,NULL},
};

WISP_MSG_MAP_BEGIN(CRegHelpWnd)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
WISP_MSG_MAP_END(CWispWnd)

CRegHelpWnd::CRegHelpWnd()
{
	m_RegisterGroup=-1;
}

CRegHelpWnd::~CRegHelpWnd()
{
}


#define BEGIN_X_POS 60
#define BEGIN_Y_POS 30
#define FIELDWIDTH  15
#define FIELDHEIGH	45
#define DATA_LEN	32
#define WIDTH_LEN	(FIELDWIDTH*DATA_LEN+1)

bool CRegHelpWnd::OnUpdateClient(IN WISP_MSG *pMsg)
{
//	WISP_CHAR DisplayOut[4];
	
//	WISP_RECT rc;
	int			FontHeight,x,y;
	FontHeight = m_ClientDC.GetTextHeight(WISP_CHAR("M"));

	m_ClientDC.DrawFullRect(&m_ClientRect,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_WHITE]);

	x = 10;y = 10;
	if(m_RegisterGroup == CONTROL_REGISTER)
	{
		DrawRegister(x,y,0x80000fff,0xfffff800,0x7ff,0,m_ClientDC,stCR4Name,WSTR("CR4"));
		y = y + FontHeight+FIELDHEIGH+45;
		DrawRegister(x,y,0x8000183d,0x00000fe7,0x81c,0,m_ClientDC,stCR3Name,WSTR("CR3"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0x0,0x0,0,m_ClientDC,stCR2Name,WSTR("CR2"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0xffffffff,0x0,0,m_ClientDC,NULL,WSTR("CR1"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0xf00f807f,0x1ffaffc0,0x7007803f,0,m_ClientDC,stCR0Name,WSTR("CR0"));	
	}
	if(m_RegisterGroup==DEBUG_REGISTER)
	{			
		DrawRegister(x,y,0xffffffff,0x0000dc00,0xaaaab3ff,0,m_ClientDC,stDR7Name,WSTR("DR7"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x8001ffff,0xffff1ff0,0xf00f,0,m_ClientDC,stDR6Name,WSTR("DR6"));	
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0xffffffff,0x0,0,m_ClientDC,stDR5Name,WSTR("DR5"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0xffffffff,0x0,0,m_ClientDC,stDR4Name,WSTR("DR4"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0x0,0x0,0,m_ClientDC,stDR3Name,WSTR("DR0 - DR3"));
		/*
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0x0,0x0,0,m_ClientDC,stDR2Name,WSTR("DR2"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0x0,0x0,0,m_ClientDC,stDR1Name,WSTR("DR1"));
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80000001,0x0,0x0,0,m_ClientDC,stDR0Name,WSTR("DR0"));	
		*/
	}
	if(m_RegisterGroup==SEGMENT_DESCRIPTOR_REGISTER)
	{
		DrawRegister(x,y,0x81f9f981,0x00200000,0x80f8d880,0,m_ClientDC,DataSegmentDesc0);
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80018001,0x00000000,0x8000,0,m_ClientDC,DataSegmentDesc1);
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x81f9f981,0x00200000,0x80f8d880,0,m_ClientDC,CodeSegmentDesc0);
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80018001,0x00000000,0x8000,0,m_ClientDC,CodeSegmentDesc1);
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x81f9f981,0x00700000,0x80f8d880,0,m_ClientDC,SystemSegmentDesc0);
		y = y + FontHeight+FIELDHEIGH;
		DrawRegister(x,y,0x80018001,0x0,0x8000,0,m_ClientDC,SystemSegmentDesc1);
	}
	if(m_RegisterGroup==FLAGS_REGISTER)
	{
		DrawRegister(40,y,0x807fffff,0xffc0802a,0x003fefff,1,m_ClientDC,stEFlagsName);
	}
	if(m_RegisterGroup==PAGEDIRENTRY4M_REGISTER)
	{
		DrawRegister(x,y,0x80603bff,0x003fe000,0x002019ff,0,m_ClientDC,PageDirEntry4M);
	}
	if(m_RegisterGroup==PAGEDIRENTRY4K_REGISTER)
	{
		DrawRegister(x,y,0x80003bff,0,0x000009ff,0,m_ClientDC,PageDirEntry4K);
		y=225;
		DrawRegister(x,y,0x80003bff,0,0x000009ff,0,m_ClientDC,PageTabEntry4K);
	}
	return false;
}

bool CRegHelpWnd::DrawRegister(int x, int y,unsigned int NumberMask,unsigned int  ReservedMask,unsigned int LineMask,unsigned int OtherMask, CWispDC DrawDC,REGISTERBITNAME *RegBitName,WISP_CHAR *RegisterName)
{
	
	WISP_CHAR DisplayOut[4];
	WISP_RECT rc;//,FillRect;
	int			FontHeight,i;
	
	FontHeight = DrawDC.GetTextHeight(WISP_CHAR("M"));
	//画背景色
	rc.x = x;rc.y = y;rc.cx = WIDTH_LEN; rc.cy=FIELDHEIGH+FontHeight;
	DrawDC.DrawFullRect(&rc,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_WHITE]);
	//画保留域的背景色	
	rc.x = x;rc.y = y+FontHeight;rc.cx = FIELDWIDTH;rc.cy = FIELDHEIGH;		
	for(i = 31; i >= 0; i--)
	{
		rc.x = x + (31 - i) * FIELDWIDTH;
		if((ReservedMask>>i)&1)
		{
			DrawDC.DrawFullRect(&rc,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_LIGHT_GRAY]);
		}
	}
	//画位的序号区域以及区域的分割线
	rc.x = x;rc.y = y;rc.cx = FIELDWIDTH;rc.cy = FontHeight;	
	for(i = 31; i >= 0; i--)
	{
		rc.x = x + (31 - i) * FIELDWIDTH;
		if((NumberMask >> i)&1)
		{
			TSPrintf(DisplayOut,WISP_STR("%d"),i);			
			DrawDC.DrawString(DisplayOut,&rc,WISP_DT_CENTER|WISP_DT_VCENTER|WISP_DT_SINGLELINE);
		}
		if((LineMask >> i) & 1 && i != 31)
		{
			DrawDC.DrawVLine(rc.x,rc.y+FontHeight,rc.y+FontHeight+FIELDHEIGH-1,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_BLACK]);
		}

	}
	//画区域的名字
	if(RegBitName)
	{
		rc.x = x;rc.y = y+FontHeight;rc.cy=FIELDHEIGH;
		i = 0;
		int DescriptorFieldMaxLen = 0,nTmp;
		bool bDescriptorExist = false;
		while(RegBitName[i].BitLen && i <= 31)
		{
			rc.x = x + (31 - RegBitName[i].BeginBitIndex) * FIELDWIDTH;
			rc.cx = FIELDWIDTH * RegBitName[i].BitLen;
			if(RegBitName[i].RegName)
				DrawDC.DrawString(RegBitName[i].RegName,&rc,WISP_DT_CENTER|WISP_DT_VCENTER);
			
			if(RegBitName[i].Descriptor)
			{
				bDescriptorExist=true;
				nTmp = DrawDC.GetTextExtent(RegBitName[i].Descriptor) - (31 - RegBitName[i].BeginBitIndex) * FIELDWIDTH;
				if(nTmp > DescriptorFieldMaxLen)
					DescriptorFieldMaxLen = nTmp;
			}
			i++;
		}
		
		//画区域的说明
		if(bDescriptorExist)
		{
			rc.x = x - DescriptorFieldMaxLen;rc.y = y + FIELDHEIGH+FontHeight;rc.cy = FontHeight;
			i = 0;
			int j = 0,tmpx,tmpy,tmpx2,tmpy2;
			tmpx = rc.x;
			tmpy2 = y + FIELDHEIGH+FontHeight+2;
			while(RegBitName[i].BitLen && i <= 31)
			{
				if(RegBitName[i].Descriptor)
				{
#define TEMP_HIGHT (FontHeight+2)					
					rc.y = y + FIELDHEIGH+FontHeight +20 + (TEMP_HIGHT * j);
					rc.cx = DrawDC.GetTextExtent(RegBitName[i].Descriptor);
					tmpx = rc.x+rc.cx;
					tmpy = rc.y+TEMP_HIGHT/2-2;
					tmpx2 = x + (31 - RegBitName[i].BeginBitIndex) * FIELDWIDTH + FIELDWIDTH/2;					
					DrawDC.DrawHLine(tmpx,tmpx2,tmpy,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_BLACK]);
					DrawDC.DrawVLine(tmpx2,tmpy2,tmpy,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_BLACK]);					
					DrawDC.DrawString(RegBitName[i].Descriptor,&rc,WISP_DT_LEFT|WISP_DT_SINGLELINE|WISP_DT_VCENTER);
					j++;
				}
				i++;
				
			}
		}
	}
	//画外边框
	rc.x = x;rc.y = y+FontHeight;rc.cx = WIDTH_LEN; rc.cy=FIELDHEIGH;
	DrawDC.DrawRect(&rc,gpCurWisp->m_pCurDrawObj->m_crSystem[SC_BLACK]);
	//画寄存器名
	if(RegisterName)
	{
		rc.x = x + WIDTH_LEN+1+8;
		rc.y = y + FontHeight;
		DrawDC.DrawString(RegisterName,&rc,WISP_DT_LEFT|WISP_DT_VCENTER|WISP_DT_NOCLIP);
	}
	return 0;
}

int CRegHelpWnd::SetRegisterGroup(int index)
{
	if(index >= 0 && m_RegisterGroup <MAX_REGISTER_GROUP_INDEX)
		m_RegisterGroup = index;
	return 0;
}
