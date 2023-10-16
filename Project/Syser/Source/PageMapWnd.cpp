#include "StdAfx.h"
#include "Syser.h"
#include "PageMapWnd.h"
#include "X86Define.h"
#include "X86Optr.h"

#define PAE_PAGE

WISP_MSG_MAP_BEGIN(CPageMapWnd)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_CLOSE,OnClose)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
WISP_MSG_MAP_END(CWispSplitWnd)

bool CPageMapWnd::OnCommand(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CtrlType==WISP_CTRL_LIST)
	{
		if(pMsg->Command.CmdID==WND_ID_PAGEDIRECTLIST)
		{
			HANDLE hItem = pMsg->Command.Param2;
			if(pMsg->Command.CmdMsg==WISP_CMD_ITEM_EXPANDED)
			{
				//gpCurWisp->DbgPrint(0,WISP_STR("WND_ID_PAGEDIRECTLIST  WISP_CMD_PL_EXPANDED"));
			}
			if(pMsg->Command.CmdMsg==WISP_CMD_ITEM_UNEXPANDED)
			{
				//gpCurWisp->DbgPrint(1,WISP_STR("WND_ID_PAGEDIRECTLIST  WISP_CMD_PL_COLLAPSED"));
			}
			if(pMsg->Command.CmdMsg==WISP_CMD_ITEM_SELECTED)
			{
				//m_PageDirectList.GetItemData(pItem,3)
				m_PageTableList.ClearChildItem();
				if(m_PageTableBaseAddress!=0)
					InsertPageTableList(pMsg);
				//gpCurWisp->DbgPrint(2,WISP_STR("%08x"),m_PageDirectList.GetItemData(pItem,3));
			}
			//gpCurWisp->DbgPrint(3,WISP_STR("WND_ID_PAGEDIRECTLIST"));
		}
		if(pMsg->Command.CmdID==WND_ID_PAGETABLELIST)
		{
			//gpCurWisp->DbgPrint(1,WISP_STR("WND_ID_PAGETABLELIST"));
		}		
	}
	return true;
}

CPageMapWnd::CPageMapWnd()
{
	m_PAE = false;
#ifdef CODE_OS_WIN
	m_PageTableBaseAddress=NULL;
	m_PageDirectBaseAddress=NULL;	
#else
	if(GetX86CR4() & CR4_PAE_BIT_MASK)
	{
		m_PageTableBaseAddress = (DWORD *)0xc0000000;
		m_PageDirectBaseAddress = (DWORD *)0xc0600000;
	}
	else
	{
		m_PageTableBaseAddress = (DWORD *)0xc0000000;
		m_PageDirectBaseAddress = (DWORD *)0xc0300000;
	}
#endif
}

CPageMapWnd::~CPageMapWnd()
{
}

void CPageMapWnd::Popup()
{
	if(IsWindow())
	{
		Destroy();
	}
	else
	{
		Create(WSTR("Page Map"),CWispRect(0,0,400,300),NULL,0,WISP_SWS_HORZ|WISP_WS_NORMAL);
		Center();
	}
}

void CPageMapWnd::UpdateContext()
{
#ifdef CODE_OS_NT_DRV
	DWORD dwTmpVar;
#endif
	HANDLE hItem;
	int i,j;
	X86_PDE *pCurrentPDEBegin;
	X86_PDE_4M *pCurrentPDE4M;
	DWORD *dwPDEValue;
	ULONGLONG DisplayValue;
	WISP_CHAR DisplayOut[100];
	WCHAR *Format=WSTR("%sP %s %s %s %s %s %s");

	pCurrentPDEBegin = (X86_PDE *)m_PageDirectBaseAddress;
#ifdef CODE_OS_WIN
#  ifdef PAE_PAGE
	if(1)
#  else
	if(0)
#  endif
#else
	if(GetX86CR4() & 0x20)
#endif
	{		
		X86_36_PDE* PDE_36 = (X86_36_PDE*)m_PageDirectBaseAddress;
		X86_36_PDE_2M *PDE_36_2M;
		for(j = 0,i = 0; i < 512 * 4; i++)	
		{		
			dwPDEValue = (DWORD *)&PDE_36[i];
#ifndef CODE_OS_WIN
			if(ReadDword(dwPDEValue,&dwTmpVar)==false)
				continue;
#endif
			if(!PDE_36[i].u.P)
				continue;	
			if(PDE_36[i].u.Page2M)
			{												
				PDE_36_2M = (X86_36_PDE_2M *)&PDE_36[i];
				DisplayValue=PDE_36_2M->PDE36Value2M;
				DisplayValue&= 0xffffffffffe00000i64;
				TSPrintf(DisplayOut,WISP_STR("%013I64X"),DisplayValue);
				hItem = m_PageDirectList.InsertItem(DisplayOut);
				TSPrintf(DisplayOut,WISP_STR("%08X - %08X"),i*0x200000,i*0x200000+0x1fffff);
				m_PageDirectList.SetItemText(hItem,1,DisplayOut);						

				TSPrintf(DisplayOut,Format,
					WSTR(" "),
					PDE_36_2M[i].u.G ? WSTR("G"):WSTR(" "),
					PDE_36_2M[i].u.D ? WSTR("D"):WSTR(" "),
					PDE_36_2M[i].u.A ? WSTR("A"):WSTR(" "),
					PDE_36_2M[i].u.US ? WSTR("U"):WSTR("S"),
					PDE_36_2M[i].u.RW ? WSTR("RW"):WSTR("R "),
					WSTR("2M")
					);			
				m_PageDirectList.SetItemText(hItem,2,DisplayOut);
				m_PageDirectList.SetItemNum(hItem,3,i);
			}else
			{
				DisplayValue=*(ULONGLONG*)&PDE_36[i];
				TSPrintf(DisplayOut,WISP_STR("%013I64X"),DisplayValue);
				hItem = m_PageDirectList.InsertItem(DisplayOut);

				TSPrintf(DisplayOut,WISP_STR("%08X - %08X"),i*0x200000,i*0x200000+0x1fffff);
				m_PageDirectList.SetItemText(hItem,1,DisplayOut);
				TSPrintf(DisplayOut,Format,			
					WSTR(" "),
					WSTR(" "),
					WSTR(" "),
					PDE_36[i].u.A ? WSTR("A"):WSTR(" "),
					PDE_36[i].u.US ? WSTR("U"):WSTR("S"),
					PDE_36[i].u.RW ? WSTR("RW"):WSTR("R "),
					WSTR("  ")
					);			
				m_PageDirectList.SetItemText(hItem,2,DisplayOut);			
				m_PageDirectList.SetItemNum(hItem,3,i);
			}
		}
		return;
	}	
	for(j = 0,i = 0; i < 1024; i++)
	{
		dwPDEValue = (DWORD *)&pCurrentPDEBegin[i];
#ifndef CODE_OS_WIN
		if(ReadDword(dwPDEValue,&dwTmpVar)==false)
			continue;
#endif
		if(!pCurrentPDEBegin[i].u.Present)
			continue;	
		if(pCurrentPDEBegin[i].u.Page4M)
		{
			pCurrentPDE4M = (X86_PDE_4M *)&pCurrentPDEBegin[i];
			TSPrintf(DisplayOut,WISP_STR("%08X"),*dwPDEValue&0xfff00000);			
			hItem = m_PageDirectList.InsertItem(DisplayOut);
			TSPrintf(DisplayOut,WISP_STR("%08X - %08X"),i*0x400000,i*0x400000+0x3fffff);
			m_PageDirectList.SetItemText(hItem,1,DisplayOut);						

			TSPrintf(DisplayOut,Format,
				WSTR(" "),
				pCurrentPDE4M->GlobePage ? WSTR("G"):WSTR(" "),
				pCurrentPDE4M->Dirty ? WSTR("D"):WSTR(" "),
				pCurrentPDE4M->Accessed ? WSTR("A"):WSTR(" "),
				pCurrentPDE4M->UserPage ? WSTR("U"):WSTR("S"),
				pCurrentPDE4M->ReadWrite ? WSTR("RW"):WSTR("R "),
				WSTR("4M")
				);			
			m_PageDirectList.SetItemText(hItem,2,DisplayOut);
			m_PageDirectList.SetItemNum(hItem,3,i);

		}
		else
		{
			TSPrintf(DisplayOut,WISP_STR("%08X"),*dwPDEValue&0xfffff000);
			hItem = m_PageDirectList.InsertItem(DisplayOut);

			TSPrintf(DisplayOut,WISP_STR("%08X - %08X"),i*0x400000,i*0x400000+0x3fffff);
			m_PageDirectList.SetItemText(hItem,1,DisplayOut);						
			TSPrintf(DisplayOut,Format,			
				WSTR(" "),
				WSTR(" "),
				WSTR(" "),
				pCurrentPDEBegin[i].u.Accessed ? WSTR("A"):WSTR(" "),
				pCurrentPDEBegin[i].u.UserPage ? WSTR("U"):WSTR("S"),
				pCurrentPDEBegin[i].u.ReadWrite ? WSTR("RW"):WSTR("R "),
				WSTR("  ")
				);			
			m_PageDirectList.SetItemText(hItem,2,DisplayOut);			
			m_PageDirectList.SetItemNum(hItem,3,i);
		}
	}

}

bool CPageMapWnd::OnDestroy(IN WISP_MSG*pMsg)
{
#ifdef CODE_OS_WIN
	BYTE *pByte;
	pByte = (BYTE *)m_PageTableBaseAddress;
	delete []m_PageTableBaseAddress;
#else
#endif
	return true;
}

bool CPageMapWnd::InsertPageTableList(IN WISP_MSG *pMsg)
{
	int i;//,j;
	WCHAR *Format1=WSTR("%sP %s %s %s %s %s %s");
	X86_PDE *pCurrentPDEBegin;
	X86_PTE *pPageTableBegin;	
	DWORD dwPageDirectEntryIndex,dwTmpVar;
	DWORD dwPTEValue,dwPDEValue;
	WISP_CHAR DisplayOut[100];
	HANDLE hItem = (HANDLE*)pMsg->Command.Param2;
	dwPageDirectEntryIndex =(DWORD) m_PageTableList.GetItemData(hItem,3);
#ifdef CODE_OS_WIN
#  ifdef PAE_PAGE
	if(1)
#  else
	if(0)
#  endif
#else
	if(GetX86CR4() & 0x20)
#endif	
	{
		X86_36_PDE *PDE_36;
		X86_36_PTE *PTE_36;
		PDE_36 = (X86_36_PDE *)m_PageDirectBaseAddress;
#ifndef CODE_OS_WIN
		if(ReadDword(&PDE_36[dwPageDirectEntryIndex],&dwTmpVar)==false)
			return true;
#endif
		if(!PDE_36[dwPageDirectEntryIndex].u.P)
			return true;
		if(PDE_36[dwPageDirectEntryIndex].u.Page2M)
			return true;
		PTE_36 = (X86_36_PTE*)RT_PBYTE(m_PageTableBaseAddress,dwPageDirectEntryIndex << 12);
		dwPDEValue = dwPageDirectEntryIndex * 0x200000;
		for(i = 0; i < 512; i++)
		{
			if(ReadDword(&PTE_36[i],&dwTmpVar)==false)
				return true;
			if(!PTE_36[i].u.P)
				continue;
			dwPTEValue = *(DWORD *)(&PTE_36[i]);		
			TSPrintf(DisplayOut,WISP_STR("%08X"),dwPDEValue + (i<<12));
			hItem =	m_PageTableList.InsertItem(DisplayOut);
			TSPrintf(DisplayOut,WISP_STR("%01X%08X"),PTE_36[i].u.BaseAddressHigh,dwPTEValue & 0xfffff000);
			m_PageTableList.SetItemText(hItem,1,DisplayOut);


			TSPrintf(DisplayOut,Format1,
				WSTR(" "),
				PTE_36[i].u.G ? WSTR("G"):WSTR(" "),
				PTE_36[i].u.D ? WSTR("D"):WSTR(" "),
				PTE_36[i].u.A ? WSTR("A"):WSTR(" "),
				PTE_36[i].u.US ? WSTR("U"):WSTR("S"),
				PTE_36[i].u.RW ? WSTR("RW"):WSTR("R "),
				WSTR("  "));		
			m_PageTableList.SetItemText(hItem,2,DisplayOut);

		}
		return true;
	}
	pCurrentPDEBegin = (X86_PDE *)m_PageDirectBaseAddress;
#ifndef CODE_OS_WIN
	if(ReadDword(&pCurrentPDEBegin[dwPageDirectEntryIndex],&dwTmpVar)==false)
		return true;
#endif
	if(pCurrentPDEBegin[dwPageDirectEntryIndex].u.Page4M)
		return true;
	if(!pCurrentPDEBegin[dwPageDirectEntryIndex].u.Present)
		return true;
	dwPDEValue = dwPageDirectEntryIndex * 0x400000;
	pPageTableBegin = (X86_PTE *)RT_PBYTE(m_PageTableBaseAddress,dwPageDirectEntryIndex << 12);
	for(i = 0; i < 1024;i++)
	{
		if(ReadDword(&pPageTableBegin[i],&dwTmpVar)==false)
			return true;
		if(!pPageTableBegin[i].Present)
			continue;
		dwPTEValue = *(DWORD *)(&pPageTableBegin[i]);		
		TSPrintf(DisplayOut,WISP_STR("%08X"),dwPDEValue + (i<<12));
		hItem =	m_PageTableList.InsertItem(DisplayOut);
		TSPrintf(DisplayOut,WISP_STR("%08X"),dwPTEValue & 0xfffff000);
		m_PageTableList.SetItemText(hItem,1,DisplayOut);

		
		TSPrintf(DisplayOut,Format1,								
				WSTR(" "),
				pPageTableBegin[i].GlobePage ? WSTR("G"):WSTR(" "),
				pPageTableBegin[i].Dirty ? WSTR("D"):WSTR(" "),
				pPageTableBegin[i].Accessed ? WSTR("A"):WSTR(" "),
				pPageTableBegin[i].UserPage ? WSTR("U"):WSTR("S"),
				pPageTableBegin[i].ReadWrite ? WSTR("RW"):WSTR("R "),
				WSTR("  "));		
		m_PageTableList.SetItemText(hItem,2,DisplayOut);
	}
	return true;
}

bool CPageMapWnd::OnCreate(IN WISP_MSG *pMsg)
{	
#ifdef CODE_OS_WIN
	CLocalFileIO PageTableFile;
	BYTE *pByte;
	int nLen;
	HANDLE hFile;
	if(PageTableFile.OpenFile("PageTable.bin",&hFile))
	{	
		nLen = (int)PageTableFile.GetFileLength(hFile);
		pByte= new BYTE[nLen];
		m_PageTableBaseAddress = (DWORD *)pByte;
		PageTableFile.ReadFile(hFile,(void*)m_PageTableBaseAddress,nLen);
		m_PageDirectBaseAddress =(DWORD *) (pByte+0x300000);
		PageTableFile.CloseHandle(hFile);
	}else
	{
		m_PageTableBaseAddress=NULL;
		m_PageDirectBaseAddress=NULL;
		return true;
	}
#endif
	m_PageDirectList.Create(NULL,CWispRect(0,0,m_ClientRect.cx / 2,m_ClientRect.cy),this,WND_ID_PAGEDIRECTLIST,WISP_WLS_COLUMN_TITLE);
	m_PageDirectList.InsertColumn(WISP_STR("Page Table Physical Address"),68);
	m_PageDirectList.InsertColumn(WISP_STR("Lines Address"),120);
	m_PageDirectList.InsertColumn(WISP_STR("Attribute"),120);
	m_PageDirectList.InsertColumn(WISP_STR(""),80);

	m_PageTableList.Create(NULL,CWispRect(m_ClientRect.cx / 2,0,m_ClientRect.cx / 2,m_ClientRect.cy),this,WND_ID_PAGETABLELIST,WISP_WLS_COLUMN_TITLE);
	m_PageTableList.InsertColumn(WISP_STR("Lines Address"),120);
	m_PageTableList.InsertColumn(WISP_STR("Physical"),80);
	m_PageTableList.InsertColumn(WISP_STR("Attribute"),120);
	m_PageTableList.InsertColumn(WISP_STR(""),80);
	InsertWnd(&m_PageDirectList,0,100);
	InsertWnd(&m_PageTableList,0,100);
	AdjustWndPos();
	UpdateContext();
	return true;
}

bool CPageMapWnd::OnClose(IN WISP_MSG *pMsg)
{
	gpSyser->m_MainFrame.SetDefaultFocus();
	return true;
}


