#ifndef _PC_SYSTEM_H_
#define _PC_SYSTEM_H_

#include "UHCIDevice.h"
#include "OHCIDevice.h"

class CPCSystem
{
public:
	CPCSystem();
	~CPCSystem();
	bool	Init();
	void	Release();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PCI
private:
	pci_ops*	m_pPCIOps;
public:
	bool		InitPCI();
	void		ReleasePCI();
	void		SearchPCIDevice();
	void		RecognizePCIDevice(int Bus,int DevFN);
	void		ReadPCICFGByte(int Bus,int DevFN,int Offset,BYTE*Val);
	void		ReadPCICFGWord(int Bus,int DevFN,int Offset,WORD*Val);
	void		ReadPCICFGDWord(int Bus,int DevFN,int Offset,DWORD*Val);
	void		WritePCICFGByte(int Bus,int DevFN,int Offset,BYTE Val);
	void		WritePCICFGWord(int Bus,int DevFN,int Offset,WORD Val);
	void		WritePCICFGDWord(int Bus,int DevFN,int Offset,DWORD Val);
//PCI
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//USB
public:
	CUHCIDevice	m_UHCIDevice;
	COHCIDevice	m_OHCIDevice;
	bool		InitUSB();
	void		ReleaseUSB();
	void		AttachUSBDevice();
	void		DetachUSBDevice();
	void		USBDeviceService();
	void		InitVmwareVideo();
	WORD		m_VmwareVideoCommandPort;
	WORD		m_VmwareVideoDatePort;
	DWORD*		m_VmwareSecondFrameBuffer;
//USB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
};


#endif
