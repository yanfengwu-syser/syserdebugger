#include "StdAfx.h"
#include "Syser.h"
#include "PCSystem.h"


CPCSystem::CPCSystem()
{
	m_pPCIOps = NULL;
	m_VmwareVideoCommandPort=0;
	m_VmwareVideoDatePort=0;
	m_VmwareSecondFrameBuffer=NULL;
}

CPCSystem::~CPCSystem()
{

}

bool CPCSystem::Init()
{
	if(InitPCI())
	{
		SearchPCIDevice();
		InitVmwareVideo();
	}
	InitUSB();
	return true;
}


void CPCSystem::InitVmwareVideo()
{
	if(gInVMWARE==false)
		return;

	PCI_CONFIG_COMMON PCIConfigREG;
	DWORD dwOldValue,dwPhysicalAddr;
	DWORD dwSize=0;
	//pci_dev dev;
	bool bFound=false;
	int j;

	for(j =0;j<0x100;j++)
	{
		//dev.bus = j;
		for(int i = 0; i < 0x100; i++)
		{
			//dev.devfn = i;
			gpSyser->m_PCSystem.ReadPCICFGWord(j,i,PCI_VENDOR_ID,&PCIConfigREG.VendorID);
			if(PCIConfigREG.VendorID != 0xffff && PCIConfigREG.VendorID != 0)
			{
				gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_REVISION_ID,(DWORD *)&PCIConfigREG.RevisionID);
				if(PCIConfigREG.BaseClass==3&&PCIConfigREG.SubClass==0&&PCIConfigREG.ProgIf==0)
				{
					
					for(int k =0; k <6;k++)
					{
						gpSyser->m_PCSystem.ReadPCICFGDWord(j,i,PCI_BASE_ADDRESS_0+k*4,&dwOldValue);
						if(dwOldValue!=0)
						{
							if(dwOldValue&1)
							{
								m_VmwareVideoCommandPort=*(WORD*)&dwOldValue;
								m_VmwareVideoCommandPort&=0xfffe;
								m_VmwareVideoDatePort=m_VmwareVideoCommandPort+1;
							}else
							{
								//m_VmwareSecondFrameBuffer = (DWORD*)dwOldValue;
								DWORD Addr1;
								dwPhysicalAddr=dwOldValue;
								MapToVAddr(dwOldValue,&Addr1);
								m_VmwareSecondFrameBuffer =(DWORD*) Addr1;
							}
						}	
						bFound=true;
					}	
				}
			}
			if(bFound)
				break;
		}
		if(bFound)
			break;
	}
	::DbgPrint("Syser : m_VmwareVideoCommandPort=%04x %04x %08x[%08x]\n",m_VmwareVideoCommandPort,m_VmwareVideoDatePort,m_VmwareSecondFrameBuffer,dwPhysicalAddr);
}

void CPCSystem::Release()
{
	ReleasePCI();
	ReleaseUSB();
}

bool CPCSystem::InitPCI()
{
	m_pPCIOps = pci_init();
	return m_pPCIOps!=NULL;
}

void CPCSystem::ReleasePCI()
{
	m_pPCIOps = NULL;
}

bool CPCSystem::InitUSB()
{
	m_UHCIDevice.Init();
	m_OHCIDevice.Init();
	return true;
}

void CPCSystem::ReleaseUSB()
{
	m_OHCIDevice.Release();
	m_UHCIDevice.Release();
}

void CPCSystem::SearchPCIDevice()
{
	WORD  VendorID,DeviceID;
	for(int bus =0;bus<0x100;bus++)
	{
		for(int fn = 0; fn < 0x100; fn++)
		{
			gpSyser->m_PCSystem.ReadPCICFGWord(bus,fn,PCI_VENDOR_ID,&VendorID);
			gpSyser->m_PCSystem.ReadPCICFGWord(bus,fn,PCI_DEVICE_ID,&DeviceID);
			if(VendorID!=0xFFFF && VendorID && DeviceID!=0xFFFF && DeviceID)
				RecognizePCIDevice(bus,fn);
		}
	}	
}

void CPCSystem::RecognizePCIDevice(int Bus,int DevFN)
{
	BYTE ProgIf;
	OHCI_REGS*pOHCIRegs;
	DWORD DevClass,Value;
	ReadPCICFGDWord(Bus,DevFN,PCI_REVISION_ID,&DevClass);
	switch(HIGH_WORD(DevClass))
	{
	case PCI_CLASS_SERIAL_USB:
		ProgIf = (BYTE)(DevClass>>8);
		switch(ProgIf)
		{
		case 0://UHCI
			ReadPCICFGDWord(Bus,DevFN,PCI_BASE_ADDRESS_4,&Value);
			if(Value&1)
			{
				TList<UHCI_CTRL_INFO>::IT  Iter = m_UHCIDevice.m_UHCICtrlList.Append();
				Iter->USBBase = (WORD)(Value&0xFFE0);
				Iter->FrameBase = SyserReadPortDword(Iter->USBBase+8) & 0xFFFFF000;
				Iter->Bus = Bus;
				Iter->DevFN = DevFN;
				OUTPUT(WSTR("Syser : Find UHCI Ctrl %d [Bus %02X Device %02X Function %02X USBBase %X FrameBase %08X]\n"),m_UHCIDevice.m_UHCICtrlList.Count()-1,Iter->Bus,Iter->DevFN>>3,Iter->DevFN&7,Iter->USBBase,Iter->FrameBase);
			}
			break;
		case 0x10://OHCI
			{
				ReadPCICFGDWord(Bus,DevFN,PCI_BASE_ADDRESS_0,&Value);
				if(MapToVAddr(Value,(ULPOS*)&pOHCIRegs)==0)
					break;
				TList<OHCI_CTRL_INFO>::IT  Iter = m_OHCIDevice.m_OHCICtrlList.Append();
				Iter->Bus = Bus;
				Iter->DevFN = DevFN;
				Iter->pOHCIRegs = pOHCIRegs;
				OUTPUT(WSTR("Syser : Find OHCI Ctrl %d [Bus %02X Device %02X Function %02X]\n"),m_OHCIDevice.m_OHCICtrlList.Count()-1,Iter->Bus,Iter->DevFN>>3,Iter->DevFN&7);
			}
			break;
		case 0x20://EHCI
			OUTPUT(WSTR("Syser : Find EHCI Ctrl\n"));
			break;
		}
		break;
	}
}

void CPCSystem::ReadPCICFGByte(int Bus,int DevFN,int Offset,BYTE*Val)
{
	pci_dev dev;
	if(m_pPCIOps==NULL)
		return;
	dev.bus = Bus;
	dev.devfn = DevFN;
	m_pPCIOps->read_byte(&dev,Offset,Val);
}

void CPCSystem::ReadPCICFGWord(int Bus,int DevFN,int Offset,WORD*Val)
{
	pci_dev dev;
	if(m_pPCIOps==NULL)
		return;
	dev.bus = Bus;
	dev.devfn = DevFN;
	m_pPCIOps->read_word(&dev,Offset,Val);
}

void CPCSystem::ReadPCICFGDWord(int Bus,int DevFN,int Offset,DWORD*Val)
{
	pci_dev dev;
	if(m_pPCIOps==NULL)
		return;
	dev.bus = Bus;
	dev.devfn = DevFN;
	m_pPCIOps->read_dword(&dev,Offset,Val);
}

void CPCSystem::WritePCICFGByte(int Bus,int DevFN,int Offset,BYTE Val)
{
	pci_dev dev;
	if(m_pPCIOps==NULL)
		return;
	dev.bus = Bus;
	dev.devfn = DevFN;
	m_pPCIOps->write_byte(&dev,Offset,Val);
}

void CPCSystem::WritePCICFGWord(int Bus,int DevFN,int Offset,WORD Val)
{
	pci_dev dev;
	if(m_pPCIOps==NULL)
		return;
	dev.bus = Bus;
	dev.devfn = DevFN;
	m_pPCIOps->write_word(&dev,Offset,Val);
}

void CPCSystem::WritePCICFGDWord(int Bus,int DevFN,int Offset,DWORD Val)
{
	pci_dev dev;
	if(m_pPCIOps==NULL)
		return;
	dev.bus = Bus;
	dev.devfn = DevFN;
	m_pPCIOps->write_dword(&dev,Offset,Val);
}

void CPCSystem::AttachUSBDevice()
{
	m_UHCIDevice.Attach();
	m_OHCIDevice.Attach();
}

void CPCSystem::DetachUSBDevice()
{
	m_OHCIDevice.Detach();
	m_UHCIDevice.Detach();
}

void CPCSystem::USBDeviceService()
{
	gpSyser->m_PCSystem.m_UHCIDevice.UHCIMouseService();
	gpSyser->m_PCSystem.m_UHCIDevice.UHCIKeyboardService();
	gpSyser->m_PCSystem.m_OHCIDevice.OHCIMouseService();
	gpSyser->m_PCSystem.m_OHCIDevice.OHCIKeyboardService();
}

