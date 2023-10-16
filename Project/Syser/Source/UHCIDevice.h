#ifndef _UHCI_DEVICE_H_
#define _UHCI_DEVICE_H_

#define UHCI_LinkIsTail(x)		(((x)&1)!=0)
#define UHCI_LinkIsQH(x)		(((x)&2)!=0)
#define UHCI_GetLinkPhysAddr(x)	((x)&0xFFFFFFF0)
#define UHCI_GetLinkTypeName(x)	(UHCI_LinkIsQH(x)?WSTR("QH"):WSTR("TD"))

struct UHCI_CTRL_INFO
{
	int		Bus;
	int		DevFN;
	DWORD	FrameBase;
	WORD	USBBase;
};

struct UHCI_QH
{
	DWORD Link; 
	DWORD Element;
};

struct UHCI_TD
{
	DWORD	Link;
	DWORD	Status;
	DWORD	TDToken;
	DWORD	TDBuffer;
};

#define MAX_UHCI_DEVICE_FRAME_PERIOD	0x10
#define MAX_UHCI_MOUSE_DEVICE			8
#define MAX_UHCI_KEYBOARD_DEVICE		8

#define UHCI_DEVICE_TD_COUNT			10
#define UHCI_DATA_BUFF_LENGTH			0x20
#define UHCI_TD_LENGTH					(UHCI_DATA_BUFF_LENGTH+sizeof(UHCI_TD))

struct UHCI_DEVICE_INFO
{
	DWORD*	pTDHead;
	DWORD	OldTDListPhysAddr;
	DWORD	TDListBufferPA;
	BYTE*	pTDListBuffer;
	int		CurTDIndex;
};

struct UHCI_KEYBOARD_DEVICE
{
	UHCI_DEVICE_INFO DevInfo;
	BYTE PrevData[8];
};

struct UHCI_MOUSE_DEVICE
{
	UHCI_DEVICE_INFO DevInfo;
	char BtStatus;
};

class CUHCIDevice
{
public:
	CUHCIDevice();
	~CUHCIDevice();
public:
	TMap<ULPOS,ULPOS>		m_PhyscialMemoryCacheMap;
	TList<UHCI_CTRL_INFO>	m_UHCICtrlList;		//UHCI ¿ØÖÆÆ÷ÐÅÏ¢
	UHCI_KEYBOARD_DEVICE	m_UHCIKeyboard[MAX_UHCI_KEYBOARD_DEVICE];
	int						m_UHCIKeyboardCount;
	UHCI_MOUSE_DEVICE		m_UHCIMouse[MAX_UHCI_MOUSE_DEVICE];
	int						m_UHCIMouseCount;
	bool	Init();
	void	Release();
	void	Attach();
	void	Detach();
	void	RecognizeUHCIDevice(UHCI_TD*pTD,UHCI_QH*pQH);
	void	InitUHCIInputDevice(UHCI_DEVICE_INFO*pDeviceInfo);
	void	ResetUHCIInputDevice(UHCI_DEVICE_INFO*pDeviceInfo,UHCI_TD*pTD,UHCI_QH*pQH);
	void	ReleaseUHCIInputDevice(UHCI_DEVICE_INFO*pDeviceInfo);
	void	UHCIMouseService();
	void	UHCIKeyboardService();
	void	UHCIPacketDone(UHCI_DEVICE_INFO*pDevInfo);
	bool	CacheMapToVAddr(ULPOS PhysicalAddress,ULPOS* VirtualAddress);
};


#endif
