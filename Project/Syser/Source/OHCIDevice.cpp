#include "StdAfx.h"
#include "Syser.h"
#include "OHCIDevice.h"
#include "Keyboard.h"
#include "Mouse.h"


COHCIDevice::COHCIDevice()
{
	for(int n=0;n<MAX_OHCI_MOUSE_DEVICE;n++)
	{
		STZeroMemory(m_OHCIMouse[n]);
	}
	for(int n=0;n<MAX_OHCI_KEYBOARD_DEVICE;n++)
	{
		STZeroMemory(m_OHCIKeyboard[n]);
	}
	m_OHCIKeyboardCount = m_OHCIMouseCount = 0;
}

COHCIDevice::~COHCIDevice()
{
}

bool COHCIDevice::Init()
{
	for(int n=0;n<MAX_OHCI_MOUSE_DEVICE;n++)
	{
		InitOHCIInputDevice(&m_OHCIMouse[n].DevInfo);
	}
	for(int n=0;n<MAX_OHCI_KEYBOARD_DEVICE;n++)
	{
		InitOHCIInputDevice(&m_OHCIKeyboard[n].DevInfo);
	}
	m_OHCIKeyboardCount = m_OHCIMouseCount = 0;
	return true;
}

void COHCIDevice::Release()
{
	for(int n=0;n<MAX_OHCI_MOUSE_DEVICE;n++)
	{
		ReleaseOHCIInputDevice(&m_OHCIMouse[n].DevInfo);
	}
	for(int n=0;n<MAX_OHCI_KEYBOARD_DEVICE;n++)
	{
		ReleaseOHCIInputDevice(&m_OHCIKeyboard[n].DevInfo);
	}
	m_OHCICtrlList.Clear();
	m_PhyscialMemoryCacheMap.Clear();
}

bool COHCIDevice::CacheMapToVAddr(ULPOS PhysicalAddress,ULPOS* VirtualAddress)
{
	TMap<ULPOS,ULPOS>::IT FindIT;
	ULPOS SwapVal;
	ULPOS AlignPhysicalAddress,PhysicalAddressMod;

	AlignPhysicalAddress=(PhysicalAddress&0xFFFFF000);
	PhysicalAddressMod = PhysicalAddress - AlignPhysicalAddress;
	FindIT = m_PhyscialMemoryCacheMap.Find(AlignPhysicalAddress);
	if(FindIT==m_PhyscialMemoryCacheMap.End())
	{
		if(MapToVAddr(AlignPhysicalAddress,&SwapVal)==0)
			return false;
		FindIT = m_PhyscialMemoryCacheMap.InsertUnique(AlignPhysicalAddress,SwapVal);
	}
	*VirtualAddress = *FindIT;
	*VirtualAddress |= PhysicalAddressMod;
	return true;
}

void COHCIDevice::Attach()
{
	int Level;
	DWORD EDAddr;
	OHCI_ED*pED;
	OHCI_HCCA*pHCCA;
	for(TList<OHCI_CTRL_INFO>::IT Iter=m_OHCICtrlList.Begin();Iter!=m_OHCICtrlList.End();Iter++)
	{
		//OUTPUT(WSTR("Search OHCI %08X\n"),Iter->pOHCIRegs->HCCA);
		if(CacheMapToVAddr(Iter->pOHCIRegs->HCCA,(ULPOS*)&pHCCA)==false)
			continue;
		for(int n=0;n<MAX_OHCI_DEVICE_FRAME_PERIOD;n++)
		{
			//OUTPUT(WSTR("Search Frame %d\n"),n);
			Level = 10;
			EDAddr = pHCCA->IntTab[n];
			while(Level>0 && EDAddr && CacheMapToVAddr(EDAddr,(ULPOS*)&pED))
			{
				//OUTPUT(WSTR("ED %08X\n"),EDAddr);
				if(OHCI_IsSkipED(pED->hwINFO)==false)
					RecognizeOHCIDevice(pHCCA,pED);
				if(pED->hwNextED == EDAddr)
					break;
				EDAddr = pED->hwNextED;
				Level--;
			}
		}
	}
	/*
	for(int n=0;n<m_OHCIMouseCount;n++)
	{
		OUTPUT(WSTR("%d Found USB Mouse %X\n"),n,m_OHCIMouse[n].DevInfo.pDeviceED);
	}*/
}

void COHCIDevice::Detach()
{
	int n;
	for(n=0;n<m_OHCIMouseCount;n++)
	{
		DetachOHCIDevice(&m_OHCIMouse[m_OHCIMouseCount-n-1].DevInfo);
	}
	m_OHCIMouseCount = 0;
	for(n=0;n<m_OHCIKeyboardCount;n++)
	{
		DetachOHCIDevice(&m_OHCIKeyboard[m_OHCIKeyboardCount-n-1].DevInfo);
	}
	m_OHCIKeyboardCount = 0;
	//m_PhyscialMemoryCacheMap.Clear();
}

void COHCIDevice::RecognizeOHCIDevice(OHCI_HCCA*pHCCA,OHCI_ED*pED)
{
	DWORD Length;
	OHCI_TD*pTD;
	//OUTPUT(WSTR("pED->hwINFO %08X pED->hwHeadP %08X pED->hwTailP %08X\n"),pED->hwINFO,pED->hwHeadP,pED->hwTailP);
	if(pED->hwHeadP==pED->hwTailP || MapToVAddr(pED->hwHeadP&0xFFFFFFF0,(ULPOS*)&pTD)==0)
		return;
	Length = pTD->hwBE - pTD->hwCBP + 1;
	if(pTD->hwINFO.DP!=2)
		return;//不是IN
	//OUTPUT(WSTR("Length = %X ,pTD->hwINFO.DP = %X,pTD->hwINFO = %08X , pTD->hwCBP = %08X , pTD->hwNextTD = %08X , pTD->hwBE = %08X\n"),Length,pTD->hwINFO.DP,pTD->hwINFO,pTD->hwCBP,pTD->hwNextTD,pTD->hwBE);
	if(Length>=4 && Length<=16 && Length!=8)
	{
		if(m_OHCIMouseCount<MAX_OHCI_MOUSE_DEVICE)
		{
			for(int n=0;n<m_OHCIMouseCount;n++)
			{
				if(m_OHCIMouse[n].DevInfo.pDeviceED->hwINFO == pED->hwINFO)
					return;
			}
			AttachOHCIDevice(&m_OHCIMouse[m_OHCIMouseCount].DevInfo,pED,pTD,pHCCA);
			m_OHCIMouse[m_OHCIMouseCount].BtStatus = 0;
			m_OHCIMouseCount++;
		}
	}
	else if(Length==8)
	{
		if(m_OHCIKeyboardCount<MAX_OHCI_KEYBOARD_DEVICE)
		{
			for(int n=0;n<m_OHCIKeyboardCount;n++)
			{
				if(m_OHCIKeyboard[n].DevInfo.pDeviceED->hwINFO == pED->hwINFO)
					return;
			}
			AttachOHCIDevice(&m_OHCIKeyboard[m_OHCIKeyboardCount].DevInfo,pED,pTD,pHCCA);
			ZeroMemory(m_OHCIKeyboard[m_OHCIKeyboardCount].PrevData,8);
			m_OHCIKeyboardCount++;
		}
	}
}

void COHCIDevice::OHCIMouseService()
{
	OHCI_DEVICE_INFO*pDevInfo;
	OHCI_MOUSE_DEVICE*pMouseDev;
	OHCI_TD*pTD;
	for(int n=0;n<m_OHCIMouseCount;n++)
	{
		pDevInfo = &m_OHCIMouse[n].DevInfo;
		for(int i=0;i<OHCI_DEVICE_TD_COUNT;i++)
		{
			pTD = (OHCI_TD*)&pDevInfo->pTDListBuffer[i*OHCI_TD_LENGTH];
			if(pTD->hwINFO.CC==OHCI_TD_NOERROR)
			{
				pMouseDev = &m_OHCIMouse[n];
				TranslateUSBMouse((char*)&pTD[1],&pMouseDev->BtStatus);
				OHCIPacketDone(pDevInfo);//处理完恢复TD
				return;
			}
		}
		if(pDevInfo->pDeviceED->hwHeadP == pDevInfo->pDeviceED->hwTailP)
			OHCIPacketDone(pDevInfo);
	}
}

void COHCIDevice::OHCIKeyboardService()
{
	OHCI_DEVICE_INFO*pDevInfo;
	OHCI_TD*pTD;
	for(int n=0;n<m_OHCIKeyboardCount;n++)
	{
		pDevInfo = &m_OHCIKeyboard[n].DevInfo;
		for(int i=0;i<OHCI_DEVICE_TD_COUNT;i++)
		{
			pTD = (OHCI_TD*)&pDevInfo->pTDListBuffer[i*OHCI_TD_LENGTH];
			if(pTD->hwINFO.CC==OHCI_TD_NOERROR)
			{
				TranslateUSBKey(m_OHCIKeyboard[n].PrevData,(BYTE*)&pTD[1]);
				OHCIPacketDone(pDevInfo);//处理完恢复TD
				return;
			}
		}
		if(pDevInfo->pDeviceED->hwHeadP == pDevInfo->pDeviceED->hwTailP)
			OHCIPacketDone(pDevInfo);
	}
}

void COHCIDevice::OHCIPacketDone(OHCI_DEVICE_INFO*pDevInfo)
{
	OHCI_TD*pNewTD;
	for(int i=0;i<OHCI_DEVICE_TD_COUNT;i++)
	{
		pNewTD = (OHCI_TD*)&pDevInfo->pTDListBuffer[i*OHCI_TD_LENGTH];
		pNewTD->hwINFO = pDevInfo->OrghwINFO;
		pNewTD->hwINFO.EC  = 0;
		pNewTD->hwINFO.CC  = OHCI_TD_NOTACCESS;

		pNewTD->hwCBP = pDevInfo->TDListBufferPA+i*OHCI_TD_LENGTH+sizeof(OHCI_TD);
		pNewTD->hwBE = pNewTD->hwCBP+pDevInfo->Length;
		pNewTD->hwNextTD = pDevInfo->TDListBufferPA+(i+1)*OHCI_TD_LENGTH;		
	}
	pDevInfo->pDeviceED->hwHeadP = pDevInfo->TDListBufferPA;
	pDevInfo->pDeviceED->hwTailP = pDevInfo->TDListBufferPA+OHCI_DEVICE_TD_COUNT*OHCI_TD_LENGTH;
}

void COHCIDevice::InitOHCIInputDevice(OHCI_DEVICE_INFO*pDevInfo)
{
	ULONGLONG PhysAddr;
	pDevInfo->pTDListBuffer = (BYTE*) gpUserHeap[0]->AlignAllocate(OHCI_TDLIST_LENGTH,0x400);
	ZeroMemory(pDevInfo->pTDListBuffer,OHCI_TDLIST_LENGTH);
	PhysAddr = 0;
	MapToPAddr((ULPOS)pDevInfo->pTDListBuffer,&PhysAddr);
	pDevInfo->TDListBufferPA = (DWORD)PhysAddr;
}

void COHCIDevice::ReleaseOHCIInputDevice(OHCI_DEVICE_INFO*pDevInfo)
{
	gpUserHeap[0]->AlignFree(pDevInfo->pTDListBuffer);
}

void COHCIDevice::AttachOHCIDevice(OHCI_DEVICE_INFO*pDevInfo,OHCI_ED*pED,OHCI_TD*pTD,OHCI_HCCA*pHCCA)
{
	ULONGLONG PhysAddr;
	pDevInfo->OldED = *pED;
	pDevInfo->OrghwINFO = pTD->hwINFO;
	pDevInfo->pDeviceED = pED;
	pDevInfo->pHCCA = pHCCA;
	pDevInfo->Length = pTD->hwBE-pTD->hwCBP;

	//OUTPUT(WSTR("OHCI Attach pDeviceED %08X , pNewTD %08X\n"),pDevInfo->pDeviceED,pDevInfo->pTDListBuffer);
	/*
	if(pTD->hwBE-pTD->hwCBP==7)
	OUTPUT(WSTR("Found Keyboard Device!\n"));
	else
	OUTPUT(WSTR("Found Mouse Device!\n"));
	*/
	ZeroMemory(pDevInfo->pTDListBuffer,OHCI_TDLIST_LENGTH);
	OHCI_TD*pNewTD;
	for(int i=0;i<OHCI_DEVICE_TD_COUNT;i++)
	{
		pNewTD = (OHCI_TD*)&pDevInfo->pTDListBuffer[i*OHCI_TD_LENGTH];
		pNewTD->hwINFO = pDevInfo->OrghwINFO;
		pNewTD->hwINFO.EC  = 0;
		pNewTD->hwINFO.CC  = OHCI_TD_NOTACCESS;

		pNewTD->hwCBP = pDevInfo->TDListBufferPA+i*OHCI_TD_LENGTH+sizeof(OHCI_TD);
		pNewTD->hwBE = pNewTD->hwCBP+pDevInfo->Length;
		pNewTD->hwNextTD = pDevInfo->TDListBufferPA+(i+1)*OHCI_TD_LENGTH;		
	}
	pED->hwHeadP = pDevInfo->TDListBufferPA;
	pED->hwTailP = pDevInfo->TDListBufferPA+OHCI_DEVICE_TD_COUNT*OHCI_TD_LENGTH;
}

void COHCIDevice::DetachOHCIDevice(OHCI_DEVICE_INFO*pDevInfo)
{
	//OUTPUT(WSTR("OHCI Detach\n"));
	*pDevInfo->pDeviceED = pDevInfo->OldED;
}
