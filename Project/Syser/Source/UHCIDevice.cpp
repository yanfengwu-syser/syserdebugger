#include "StdAfx.h"
#include "UHCIDevice.h"
#include "InputDriver.h"
#include "Syser.h"
#include "Keyboard.h"
#include "Mouse.h"


void CUHCIDevice::UHCIMouseService()
{
	UHCI_DEVICE_INFO*pDevInfo;
	UHCI_MOUSE_DEVICE*pMouseDev;
	UHCI_TD*pTD;
	for(int n=0;n<m_UHCIMouseCount;n++)
	{
		pMouseDev = &m_UHCIMouse[n];
		pDevInfo = &m_UHCIMouse[n].DevInfo;
		pTD = (UHCI_TD*)(&pDevInfo->pTDListBuffer[pDevInfo->CurTDIndex*UHCI_TD_LENGTH]);
		if((pTD->Status&0x00800000) == 0)
		{
			TranslateUSBMouse((char*) &pTD[1],&pMouseDev->BtStatus);
			UHCIPacketDone(pDevInfo);
		}
	}
}

void CUHCIDevice::UHCIKeyboardService()
{
	BYTE*pData;
	UHCI_DEVICE_INFO*pDevInfo;
	UHCI_KEYBOARD_DEVICE*pKeyboardDev;
	UHCI_TD*pTD;
	for(int n=0;n<m_UHCIKeyboardCount;n++)
	{
		pKeyboardDev = &m_UHCIKeyboard[n];
		pDevInfo = &m_UHCIKeyboard[n].DevInfo;
		pTD = (UHCI_TD*)(&pDevInfo->pTDListBuffer[pDevInfo->CurTDIndex*UHCI_TD_LENGTH]);
		if((pTD->Status&0x00800000) == 0)
		{
			pData = (BYTE*) &pTD[1];
			TranslateUSBKey(pKeyboardDev->PrevData,pData);
			UHCIPacketDone(pDevInfo);
		}
	}
}

void CUHCIDevice::UHCIPacketDone(UHCI_DEVICE_INFO*pDevInfo)
{
	UHCI_TD*pTD;
	pDevInfo->CurTDIndex++;
	if(pDevInfo->CurTDIndex>=UHCI_DEVICE_TD_COUNT)
		pDevInfo->CurTDIndex=0;
	pTD = (UHCI_TD*)(&pDevInfo->pTDListBuffer[pDevInfo->CurTDIndex*UHCI_TD_LENGTH]);
	pTD->Status |= 0x00800000;
}

CUHCIDevice::CUHCIDevice()
{
	for(int n=0;n<MAX_UHCI_MOUSE_DEVICE;n++)
	{
		STZeroMemory(m_UHCIMouse[n]);
	}
	for(int n=0;n<MAX_UHCI_KEYBOARD_DEVICE;n++)
	{
		STZeroMemory(m_UHCIKeyboard[n]);
	}
	m_UHCIKeyboardCount = m_UHCIMouseCount = 0;
}

CUHCIDevice::~CUHCIDevice()
{
}

bool CUHCIDevice::Init()
{
	for(int n=0;n<MAX_UHCI_MOUSE_DEVICE;n++)
	{
		InitUHCIInputDevice(&m_UHCIMouse[n].DevInfo);
	}
	for(int n=0;n<MAX_UHCI_KEYBOARD_DEVICE;n++)
	{
		InitUHCIInputDevice(&m_UHCIKeyboard[n].DevInfo);
	}
	m_UHCIKeyboardCount = m_UHCIMouseCount = 0;
	return true;
}

void CUHCIDevice::Release()
{
	for(int n=0;n<MAX_UHCI_MOUSE_DEVICE;n++)
	{
		ReleaseUHCIInputDevice(&m_UHCIMouse[n].DevInfo);
	}
	for(int n=0;n<MAX_UHCI_KEYBOARD_DEVICE;n++)
	{
		ReleaseUHCIInputDevice(&m_UHCIKeyboard[n].DevInfo);
	}
	m_UHCICtrlList.Clear();
	m_PhyscialMemoryCacheMap.Clear();
}

bool CUHCIDevice::CacheMapToVAddr(ULPOS PhysicalAddress,ULPOS* VirtualAddress)
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

void CUHCIDevice::Attach()
{
	int nUHCI;
	DWORD Link,*FrameList,dwTmpVar;
	UHCI_TD*pTD;
	UHCI_QH*pQH;
	nUHCI = 0;
	for(TList<UHCI_CTRL_INFO>::IT Iter=m_UHCICtrlList.Begin();Iter!=m_UHCICtrlList.End();Iter++)
	{
		//OUTPUT(WSTR("Search UHCI Device %d\n"),nUHCI);
		if(CacheMapToVAddr(Iter->FrameBase,(DWORD*)&FrameList)==false)
		{
			//OUTPUT(WSTR("Syser : Fail to Map Iter->FrameBase [%08X]\n"),Iter->FrameBase);
			continue;
		}
		for(int nFP=0;nFP<MAX_UHCI_DEVICE_FRAME_PERIOD;nFP++)
		{
			Link = FrameList[nFP];
			if(UHCI_LinkIsTail(Link))
				break;
			if(UHCI_LinkIsQH(Link))
			{
				if(CacheMapToVAddr(UHCI_GetLinkPhysAddr(Link),(DWORD*)&pQH)==false)
					continue;
			}
			else
			{
				if(CacheMapToVAddr(UHCI_GetLinkPhysAddr(Link),(DWORD*)&pTD)==false)
					continue;
				if(UHCI_LinkIsTail(pTD->Link) || UHCI_LinkIsQH(pTD->Link)==false)
					continue;
				if(CacheMapToVAddr(UHCI_GetLinkPhysAddr(pTD->Link),(DWORD*)&pQH)==false)
					continue;
			}
			while(UHCI_LinkIsTail(pQH->Link)==false && UHCI_LinkIsQH(pQH->Link))
			{
				if(UHCI_LinkIsTail(pQH->Element)==false && UHCI_LinkIsQH(pQH->Element)==false)
				{
					if(CacheMapToVAddr(UHCI_GetLinkPhysAddr(pQH->Element),(DWORD*)&pTD)==false)
						break;
					RecognizeUHCIDevice(pTD,pQH);
					break;
				}
				if(CacheMapToVAddr(UHCI_GetLinkPhysAddr(pQH->Link),&dwTmpVar)==false)
					break;
				*(DWORD*)&pQH = dwTmpVar;
			}
		}
		nUHCI++;
	}
	/*
	for(int n=0;n<m_UHCIMouseCount;n++)
	{
		OUTPUT(WSTR("%d Found USB Mouse %X\n"),n,m_UHCIMouse[n].DevInfo.pTDHead);
	}*/
}

void CUHCIDevice::Detach()
{
	for(int n=0;n<m_UHCIMouseCount;n++)
	{
		*m_UHCIMouse[m_UHCIMouseCount-n-1].DevInfo.pTDHead = m_UHCIMouse[m_UHCIMouseCount-n-1].DevInfo.OldTDListPhysAddr;		
	}
	m_UHCIMouseCount = 0;
	for(int n=0;n<m_UHCIKeyboardCount;n++)
	{
		*m_UHCIKeyboard[m_UHCIKeyboardCount-n-1].DevInfo.pTDHead = m_UHCIKeyboard[m_UHCIKeyboardCount-n-1].DevInfo.OldTDListPhysAddr;
	}
	m_UHCIKeyboardCount = 0;
	//m_PhyscialMemoryCacheMap.Clear();
}

void CUHCIDevice::RecognizeUHCIDevice(UHCI_TD*pTD,UHCI_QH*pQH)
{
	BYTE PID = (BYTE)pTD->TDToken;
	DWORD MaxLen = (pTD->TDToken>>21)+1;

	if(PID == 0x69)
	{//OUTPUT(WSTR("pQH %08X , pQH->Element %08X , MaxLen = %X , Link = %08X , Status = %08X , TDToken = %08X , TDBuffer = %08X\n"),pQH,pQH->Element,MaxLen,pTD->Link,pTD->Status,pTD->TDToken,pTD->TDBuffer);
		if(MaxLen>=4 && MaxLen<=16 && MaxLen!=8)
		{
			if(m_UHCIMouseCount<MAX_UHCI_MOUSE_DEVICE)
			{
				for(int n=0;n<m_UHCIMouseCount;n++)
				{
					if(m_UHCIMouse[n].DevInfo.pTDHead == &pQH->Element)
						return;
				}
				m_UHCIMouse[m_UHCIMouseCount].BtStatus=0;
				ResetUHCIInputDevice(&m_UHCIMouse[m_UHCIMouseCount].DevInfo,pTD,pQH);
				m_UHCIMouseCount++;
			}
		}
		else if(MaxLen == 8)
		{
			if(m_UHCIKeyboardCount<MAX_UHCI_KEYBOARD_DEVICE)
			{
				for(int n=0;n<m_UHCIKeyboardCount;n++)
				{
					if(m_UHCIKeyboard[n].DevInfo.pTDHead == &pQH->Element)
						return;
				}
				ZeroMemory(m_UHCIKeyboard[m_UHCIKeyboardCount].PrevData,8);
				ResetUHCIInputDevice(&m_UHCIKeyboard[m_UHCIKeyboardCount].DevInfo,pTD,pQH);
				m_UHCIKeyboardCount++;
			}
		}
	}
}

void CUHCIDevice::InitUHCIInputDevice(UHCI_DEVICE_INFO*pDeviceInfo)
{
	ULONGLONG PhysAddr;
	pDeviceInfo->pTDListBuffer = (BYTE*)gpUserHeap[SYSER_MAIN_HEAP]->AlignAllocate(UHCI_DEVICE_TD_COUNT*UHCI_TD_LENGTH+0x100,0x400);
	ZeroMemory(pDeviceInfo->pTDListBuffer,UHCI_DEVICE_TD_COUNT*UHCI_TD_LENGTH+0x100);
	PhysAddr = 0;
	MapToPAddr((ULPOS)pDeviceInfo->pTDListBuffer,&PhysAddr);
	pDeviceInfo->TDListBufferPA = (DWORD)PhysAddr;
	UHCI_TD* pTD;
	for(int i=0;i<UHCI_DEVICE_TD_COUNT;i++)
	{
		pTD = (UHCI_TD*)&pDeviceInfo->pTDListBuffer[i*UHCI_TD_LENGTH];
		pTD->Link = pDeviceInfo->TDListBufferPA+(i+1)*UHCI_TD_LENGTH;
		pTD->TDBuffer = pDeviceInfo->TDListBufferPA+i*UHCI_TD_LENGTH+sizeof(UHCI_TD);
		pTD->Status = 0;
	}
}


void CUHCIDevice::ResetUHCIInputDevice(UHCI_DEVICE_INFO*pDevInfo,UHCI_TD*pTD,UHCI_QH*pQH)
{
	UHCI_TD*pNewTD;
	for(int i=0;i<UHCI_DEVICE_TD_COUNT;i++)
	{
		pNewTD = (UHCI_TD*)&pDevInfo->pTDListBuffer[i*UHCI_TD_LENGTH];
		pNewTD->Status = pTD->Status;
		pNewTD->TDToken = (i % 2)?(pTD->TDToken & 0xFFF7FFFF):(pTD->TDToken | 0x80000);
	}
	pNewTD->Link = pDevInfo->TDListBufferPA;
	pDevInfo->CurTDIndex = 0;
	pNewTD = (UHCI_TD*)pDevInfo->pTDListBuffer;
	pNewTD->Status = pTD->Status|0x00800000;
	pDevInfo->pTDHead = &pQH->Element;
	pDevInfo->OldTDListPhysAddr = pQH->Element;
	*pDevInfo->pTDHead = pDevInfo->TDListBufferPA;
}

void CUHCIDevice::ReleaseUHCIInputDevice(UHCI_DEVICE_INFO*pDeviceInfo)
{
	gpUserHeap[0]->AlignFree(pDeviceInfo->pTDListBuffer);
}


