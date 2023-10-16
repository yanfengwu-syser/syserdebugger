#ifndef _OHCI_DEVICE_H_
#define _OHCI_DEVICE_H_

struct OHCI_REGS
{
	/* control and status registers */
	DWORD	Revision;
	DWORD	Control;
	DWORD	CmdStatus;
	DWORD	IntrStatus;
	DWORD	IntrEnable;
	DWORD	IntrDisable;
	/* memory pointers */
	DWORD	HCCA;
	DWORD	ed_periodcurrent;
	DWORD	ed_controlhead;
	DWORD	ed_controlcurrent;
	DWORD	ed_bulkhead;
	DWORD	ed_bulkcurrent;
	DWORD	DoneHead;
	/* frame counters */
	DWORD	FMInterVal;
	DWORD	FMRemaining;
	DWORD	FMNumber;
	DWORD	PerioDicstart;
	DWORD	lsthresh;
};

struct OHCI_CTRL_INFO
{
	int			Bus;
	int			DevFN;
	OHCI_REGS*	pOHCIRegs;
};

#define OHCI_IsSkipED(x)				(((x)&(1<<14))!=0)
#define OHCI_GetMPS(x)					(((x)>>16)&0x3FF)
#define OHCI_IsLowSpeed(x)				(((x)&(1<<13))!=0)


struct OHCI_ED
{
	DWORD	hwINFO;
	DWORD	hwTailP;
	DWORD	hwHeadP;
	DWORD	hwNextED;
};

struct OHCI_TD_INFO
{
	DWORD Reserved:18;
	DWORD R:1;
	DWORD DP:2;
	DWORD DI:3;
	DWORD T:2;
	DWORD EC:2;
	DWORD CC:4;
};

struct OHCI_TD
{
	OHCI_TD_INFO hwINFO;
	DWORD	hwCBP;
	DWORD	hwNextTD;
	DWORD	hwBE;
};

struct OHCI_HCCA
{
	DWORD	IntTab[32];
	WORD	FrameNum;
	WORD	Pad1;
	DWORD	DoneHead;
};

#define MAX_OHCI_DEVICE_FRAME_PERIOD	32
#define MAX_OHCI_MOUSE_DEVICE			8
#define MAX_OHCI_KEYBOARD_DEVICE		8

#define OHCI_DEVICE_TD_COUNT			2
#define OHCI_DATA_BUFF_LENGTH			0x20
#define OHCI_TD_LENGTH					(OHCI_DATA_BUFF_LENGTH+sizeof(OHCI_TD))
#define OHCI_TDLIST_LENGTH				((OHCI_DEVICE_TD_COUNT+1)*OHCI_TD_LENGTH)

struct OHCI_DEVICE_INFO
{
	OHCI_ED	OldED;
	OHCI_TD_INFO OrghwINFO;
	DWORD	Length;
	DWORD	TDListBufferPA;
	OHCI_HCCA*pHCCA;
	OHCI_ED*pDeviceED;
	BYTE*	pTDListBuffer;
};

struct OHCI_KEYBOARD_DEVICE
{
	OHCI_DEVICE_INFO DevInfo;
	BYTE PrevData[8];
};

struct OHCI_MOUSE_DEVICE
{
	OHCI_DEVICE_INFO DevInfo;
	char BtStatus;
};

#define OHCI_TD_NOERROR					0
#define OHCI_TD_NOTACCESS				0xE

///////////////////////////////////////////
//OHCI Buffer
///////////////////////////////////////////

class COHCIDevice
{
public:
	COHCIDevice();
	~COHCIDevice();
public:
	TMap<ULPOS,ULPOS>		m_PhyscialMemoryCacheMap;
	TList<OHCI_CTRL_INFO>	m_OHCICtrlList;		//OHCI ¿ØÖÆÆ÷ÐÅÏ¢
	OHCI_KEYBOARD_DEVICE	m_OHCIKeyboard[MAX_OHCI_KEYBOARD_DEVICE];
	int						m_OHCIKeyboardCount;
	OHCI_MOUSE_DEVICE		m_OHCIMouse[MAX_OHCI_MOUSE_DEVICE];
	int						m_OHCIMouseCount;
	bool	Init();
	void	Release();
	void	Attach();
	void	Detach();
	void	RecognizeOHCIDevice(OHCI_HCCA*pHCCA,OHCI_ED*pED);
	void	OHCIMouseService();
	void	OHCIKeyboardService();
	void	OHCIPacketDone(OHCI_DEVICE_INFO*pDevInfo);
	void	InitOHCIInputDevice(OHCI_DEVICE_INFO*pDevInfo);
	void	ReleaseOHCIInputDevice(OHCI_DEVICE_INFO*pDevInfo);
	void	AttachOHCIDevice(OHCI_DEVICE_INFO*pDevInfo,OHCI_ED*pED,OHCI_TD*pTD,OHCI_HCCA*pHCCA);
	void	DetachOHCIDevice(OHCI_DEVICE_INFO*pDevInfo);
	bool	CacheMapToVAddr(ULPOS PhysicalAddress,ULPOS* VirtualAddress);
};

#endif

