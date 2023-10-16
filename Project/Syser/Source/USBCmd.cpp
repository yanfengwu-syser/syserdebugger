#include "StdAfx.h"
#include "Syser.h"
#include "USBCmd.h"
#include "UHCIDevice.h"

void DumpUHCILink(DWORD Link)
{
	if(UHCI_LinkIsTail(Link))
	{
		OUTPUT(WSTR(" ->| Link Tail\n"));
	}
	else
	{
		OUTPUT(WSTR(" --> %s [%08X]\n"),UHCI_GetLinkTypeName(Link),Link);
	}
}

void DumpUHCIQHList(DWORD Link)
{
	UHCI_QH*pQH;
	while(UHCI_LinkIsTail(Link)==false)
	{
		if(MapToVAddr(UHCI_GetLinkPhysAddr(Link),(DWORD*)&pQH)==false)
		{
			OUTPUT(WSTR("%<3>Invalid QH %08X\n"),Link);
			return;
		}
		OUTPUT(WSTR("%<B>QH"));
		DumpUHCILink(pQH->Link);
		if(UHCI_LinkIsTail(pQH->Link)==false)
		{
			OUTPUT(WSTR("|--Element"));
			DumpUHCILink(pQH->Element);
		}
		Link = pQH->Link;
		if(UHCI_LinkIsQH(Link)==false)
			return;
		if(IS_CTRL_BREAK)
			return;
	}
}

void DumpUHCITD(UHCI_TD*pTD)
{
	OUTPUT(WSTR("|- TDToken PID[%<F>%02X%<1>] MaxLen[%<F>%04X%<1>]\n"),(BYTE)pTD->TDToken,(pTD->TDToken>>21)+1);
	OUTPUT(WSTR("|- Status [%<F>%08X%<1>]\n"),pTD->Status);
	OUTPUT(WSTR("|- TDBuffer [%<F>%08X%<1>]\n"),pTD->TDBuffer);
}

void DumpUHCITDList(DWORD Link)
{
	UHCI_TD*pTD;
	int n=0;
	pTD = NULL;
	while(UHCI_LinkIsTail(Link)==false && n<20)
	{
		if(pTD)
			DumpUHCITD(pTD);
		if(MapToVAddr(UHCI_GetLinkPhysAddr(Link),(DWORD*)&pTD)==false)
		{
			OUTPUT(WSTR("%<3>Invalid TD %08X\n"),Link);
			return;
		}
		OUTPUT(WSTR("%<B>TD"));
		DumpUHCILink(pTD->Link);
		Link = pTD->Link;
		if(UHCI_LinkIsQH(Link))
			return;
		if(IS_CTRL_BREAK)
			return;
		n++;
	}
	if(n==20)
		OUTPUT(WSTR("................\n"));
}

void DumpUHCILinkList(DWORD Link)
{
	if(UHCI_LinkIsQH(Link))
	{
		DumpUHCIQHList(Link);
	}
	else
	{
		DumpUHCITDList(Link);
	}
}

bool IsTDExistFrame(DWORD Link)
{
	if(UHCI_LinkIsTail(Link))
		return false;
	if(UHCI_LinkIsQH(Link)==false)
		return true;
	UHCI_QH*pQH = NULL;
	while(UHCI_LinkIsTail(Link)==false && UHCI_LinkIsQH(Link))
	{
		if(pQH && UHCI_LinkIsTail(pQH->Element)==false && UHCI_LinkIsQH(pQH->Element)==false)
			return true;
		if(MapToVAddr(UHCI_GetLinkPhysAddr(Link),(DWORD*)&pQH)==false)
			return false;
		Link = pQH->Link;
	}
	return false;
}

void DumpUHCIFrame(UHCI_CTRL_INFO*pUHCIInfo)
{
	int Index;
	DWORD PhysAddr;
	DWORD FP;
	OUTPUT(WSTR("UHCI Bus %02X Device %02X Function %02X USBBase %X FrameBase %08X\n"),pUHCIInfo->Bus,pUHCIInfo->DevFN>>3,pUHCIInfo->DevFN&7,pUHCIInfo->USBBase,pUHCIInfo->FrameBase);
	PhysAddr = pUHCIInfo->FrameBase;
	Index=0;
	while(ReadPhysicalAddress(PhysAddr,FP) && UHCI_LinkIsTail(FP)==false)
	{
		if(IsTDExistFrame(FP))
			OUTPUT(WSTR("Frame[%04X] FP[%08X] --> %s\n"),Index,FP,UHCI_GetLinkTypeName(FP));
		PhysAddr+=4;
		Index++;
	}
}

////////////////////////////////////////////////////////////
//OHCI
void DumpOHCIED(const OHCI_ED&ED)
{
	if(OHCI_IsSkipED(ED.hwINFO))
	{
		OUTPUT(WSTR("%<C>Skip ED %<1>-> %08X\n"),ED.hwNextED);
	}
	else
	{
		OUTPUT(WSTR("%<B>ED %<1>-> %08X\n"),ED.hwNextED);
		OUTPUT(WSTR("|- FA [%02X] EN [%02X] D [%X] S [%X] K [%X] F [%X] MPS [%04X]\n"),ED.hwINFO&0x7F,(ED.hwINFO>>7)&0xF,(ED.hwINFO>>11)&0x3,(ED.hwINFO>>13)&0x1,(ED.hwINFO>>14)&0x1,(ED.hwINFO>>15)&0x1,(ED.hwINFO>>16)&0x7FF);
		OUTPUT(WSTR("|-TailP [%08X]\n"),ED.hwTailP&0xFFFFFFF0);
		OUTPUT(WSTR("|-HeadP [%08X] H [%X] C [%X]\n"),ED.hwHeadP&0xFFFFFFF0,ED.hwHeadP&0x1,(ED.hwHeadP>>1)&0x1);
	}
}


void DumpOHCIFrame(OHCI_CTRL_INFO*pOHCIInfo)
{
	int Index;
	DWORD*pAddr;
	OHCI_ED*pED;
	OUTPUT(WSTR("OHCI BarOHCI %08X HCCA %08X\n"),pOHCIInfo->pOHCIRegs,pOHCIInfo->pOHCIRegs->HCCA);
	if(MapToVAddr(pOHCIInfo->pOHCIRegs->HCCA,(ULPOS*)&pAddr)==false)
	{
		OUTPUT(WSTR("%<3>Bad HCCA Address %08X\n"),pOHCIInfo->pOHCIRegs->HCCA);
		return;
	}
	OUTPUT(WSTR("Frame Interrput Table\n"));
	for(int n=0;n<32;n++)
	{
		if(MapToVAddr(pAddr[n],(ULPOS*)&pED)==false)
		{
			OUTPUT(WSTR("%<3>Error ED\n"));
			continue;
		}
		DumpOHCIED(*pED);
	}
	OUTPUT(WSTR("TDDoneHead %08X\n"),pAddr[0x21]);
}

//OHCI
////////////////////////////////////////////////////////////

int ohci_ed_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD Link;
	OHCI_ED*pED;
	if(argc==2 && CALCEXP(argv[1],(ULONG*)&Link))
	{
		if((Link&0xF)||MapToVAddr(Link,(ULPOS*)&pED)==false)
		{
			OUTPUT(WSTR("%<3>Error : Bad ED Physical Address!\n"));
			return 1;
		}
		DumpOHCIED(*pED);
	}
	return 0;
}


int uhci_link_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	DWORD Link;
	if(argc==2 && CALCEXP(argv[1],(ULONG*)&Link))
	{
		DumpUHCILinkList(Link);
	}
	return 0;
}

int usb_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	int Index;
	if(argc==1)
	{
		Index = 0;
		for(TList<UHCI_CTRL_INFO>::IT Iter = gpSyser->m_PCSystem.m_UHCIDevice.m_UHCICtrlList.Begin();Iter!=gpSyser->m_PCSystem.m_UHCIDevice.m_UHCICtrlList.End();Iter++)
		{
			OUTPUT(WSTR("%d. UHCI USBBase %X FrameBase %08X\n"),Index,Iter->USBBase,Iter->FrameBase);
			Index++;
		}
		for(TList<OHCI_CTRL_INFO>::IT Iter = gpSyser->m_PCSystem.m_OHCIDevice.m_OHCICtrlList.Begin();Iter!=gpSyser->m_PCSystem.m_OHCIDevice.m_OHCICtrlList.End();Iter++)
		{
			OUTPUT(WSTR("%d. OHCI BarOHCI %08X HCCA %08X\n"),Index,Iter->pOHCIRegs,Iter->pOHCIRegs->HCCA);
			Index++;
		}
		return 0;
	}
	if(argc==2 && CALCEXP(argv[1],(ULONG*)&Index))
	{
		for(TList<UHCI_CTRL_INFO>::IT Iter = gpSyser->m_PCSystem.m_UHCIDevice.m_UHCICtrlList.Begin();Iter!=gpSyser->m_PCSystem.m_UHCIDevice.m_UHCICtrlList.End();Iter++)
		{
			if(Index==0)
			{
				DumpUHCIFrame(&(*Iter));
				return 0;
			}
			Index--;
		}
		for(TList<OHCI_CTRL_INFO>::IT Iter = gpSyser->m_PCSystem.m_OHCIDevice.m_OHCICtrlList.Begin();Iter!=gpSyser->m_PCSystem.m_OHCIDevice.m_OHCICtrlList.End();Iter++)
		{
			if(Index==0)
			{
				DumpOHCIFrame(&(*Iter));
				return 0;
			}
			Index--;
		}
	}
	OUTPUT(WSTR("Usage : usb [Index]\n"));
	return 0;
}
