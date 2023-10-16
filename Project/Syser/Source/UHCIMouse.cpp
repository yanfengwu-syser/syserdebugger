#include "stdafx.h"
#include "UHCIMouse.h"
#include "InputDriver.h"
#include "Syser.h"

char cPrevFirstData=0,cPrevXOffset=0,cPrevYOffset=0,cPrevZOffset=0;
void UsbMouseService()
{
	char cFirstData,cXOffset,cYOffset,cZOffset;
	char *pData;
	if((pUsbStructBuf[dwUSBMouseIndex*8+1] & 0x00800000) == 0)
	{
		pData = (char *) &pUsbStructBuf[dwUSBMouseIndex*8+0x4];
		cFirstData=pData[0];
		cXOffset=pData[1];
		cYOffset=pData[2];
		cZOffset=pData[3];
		if(cYOffset != 0 || cXOffset != 0)
			gpSyser->OnMouseMove(cXOffset,cYOffset);
		if(cZOffset)
		{
			gpSyser->OnMouseWheel(cZOffset);
		}
		if((cPrevFirstData & MOUSE_INTERRUPT_LEFT_PRESS) != (cFirstData & MOUSE_INTERRUPT_LEFT_PRESS))
			gpSyser->OnKeyEvent(WISP_VK_LBUTTON,cFirstData & MOUSE_INTERRUPT_LEFT_PRESS);
		if((cPrevFirstData & MOUSE_INTERRUPT_RIGHT_PRESS) != (cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS))
			gpSyser->OnKeyEvent(WISP_VK_RBUTTON,(cFirstData & MOUSE_INTERRUPT_RIGHT_PRESS)!=0);
		if((cPrevFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS) != (cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS))
			gpSyser->OnKeyEvent(WISP_VK_MBUTTON,(cFirstData & MOUSE_INTERRUPT_MIDDLE_PRESS)!=0);
		cPrevZOffset=cZOffset;
		cPrevYOffset=cYOffset;
		cPrevXOffset=cXOffset;
		cPrevFirstData=cFirstData;
		dwUSBMouseIndex++;
		if(dwUSBMouseIndex==10)
			dwUSBMouseIndex=0;
		pUsbStructBuf[dwUSBMouseIndex*8+1] |= 0x00800000;
	}
}

void InstallUsbMouseQueue()
{
	int i,m;
	bool bFound;
	for(i = 0; i < (int)UHCI_Number;i++)
	{
		DWORD dwPortAddr = UHCIFrameBaseRegister[i];
		DWORD dwPhysicalAddress,dwValue=0,dwCounter,dwValue2;
		dwCounter= 20;
		dwPhysicalAddress = ReadPortDword(dwPortAddr+8);
		dwPhysicalAddress &= 0xfffff000;
		bFound=false;
		while ((dwValue&1) == 0 && dwCounter!=0)
		{
			if(ReadPhysicalAddress(dwPhysicalAddress,dwValue))
			{
				if((dwValue & 0xff0) == 0)
				{
					bFound=true;
					break;
				}
				dwValue2 = dwValue;
				dwPhysicalAddress=dwValue&0xfffffff0;
			}
			dwCounter--;
		}
		if(bFound)
		{
			DWORD dwValueTemp = (dwValue&0xfffff000)+0x1c8;
			if(ReadPhysicalAddress(dwValueTemp,dwValue2))
			{
				if((dwValue2 & 0xff)==0x69)
				{
					if((dwValue2>>21) == 3 || (dwValue2>>21) == 2)
					{
						DWORD dwMouseQueueAddress=dwValue;
						//OUTPUT(WSTR("dwMouseQueueAddress= %08x %08x"),dwValue,pUsbStructBuf);
						for(m =0;m<10;m++)
						{
							pUsbStructBuf[m*8]=UsbStructBufPhysicalAddress+m*0x20+0x20;
							pUsbStructBuf[m*8+3]=UsbStructBufPhysicalAddress+m*0x20+0x10;
							pUsbStructBuf[m*8+2]=(m % 2)?(dwValue2 & 0xfff7ffff):(dwValue2 | 0x80000);
							pUsbStructBuf[m*8+1]=0x1c000000;
						}
						pUsbStructBuf[1]=0x1c800000;
						dwUSBMouseIndex = 0;
						pUsbStructBuf[(m-1)*8]=UsbStructBufPhysicalAddress;
						DWORD dwTmp;
						if(MapToVAddr((dwMouseQueueAddress&0xfffffff0)+4,&dwTmp))
							if(bUsbMouseInstallFlags==false)
							{
								USBQueueHeadPoint=(DWORD *) dwTmp;
								OLDUSBQueueHeadPoint=USBQueueHeadPoint[0];
								USBQueueHeadPoint[0]=(DWORD)UsbStructBufPhysicalAddress;
								bUsbMouseInstallFlags = true;
							}
							return;
					}
				}
			}
		}
	}
}

void UninstallUsbMouseQueue()
{
	if(bUsbMouseInstallFlags)
	{
		USBQueueHeadPoint[0]=OLDUSBQueueHeadPoint;
		bUsbMouseInstallFlags=false;
	}
}
