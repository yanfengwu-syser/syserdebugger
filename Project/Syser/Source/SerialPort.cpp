#include "StdAfx.h"
#include "Syser.h"
#include "SerialPort.h"
#include "Services.h"
#include "HardWareInterruptCtrl.h"

#ifdef __cplusplus
extern "C" {
#endif

VOID SyserIODelay(VOID);
VOID SyserSerialDLAB(WORD BasePort,bool bSet);
int SyserSerialSendData(WORD BasePort,void* Buffer,int BufSize);
int SyserSerialRecvData(WORD BasePort,void*Buffer,int BufSize);

#ifdef __cplusplus
}; // extern "C"
#endif


// void __declspec(naked) IODelay()
// {
// 	__asm
// 	{
// 		jmp Next
// Next:
// 		ret
// 	}
// }
// 
// void __declspec(naked) SerialDLAB(WORD BasePort,bool bSet)
// {
// 	__asm
// 	{
// 		////////////////////////////////
// 		//proc
// 		push	ebp
// 		mov		ebp,esp
// 		push    edx
// 		push	eax
// 		////////////////////////////////
// 		mov     dx,BasePort
// 		add     dx, 3              // point to Line Control Reg
// 		in      al, dx             // get current state
// 		call	IODelay
// 		mov		ah,bSet
// 		xor		ah,ah
// 		jz		Disable
// 		or      al, 80h            // set DLAB to 1
// 		jmp		Next
// Disable:
// 		and		al, 7fh
// Next:
// 		out     dx, al
// 		////////////////////////////////
// 		//endp
// 		pop		eax
// 		pop		edx
// 		mov		esp, ebp
// 		pop		ebp
// 		ret		8
// 		////////////////////////////////
// 	}
// }
// 
// 
// int __declspec(naked) SerialSendData(WORD BasePort,void*Buffer,int BufSize)
// {
// 	__asm
// 	{
// 		////////////////////////////////
// 		//proc
// 		push	ebp
// 		mov		ebp,esp
// 		push	esi
// 		push    edx
// 		push	ecx
// 		////////////////////////////////
// 		mov     dx, BasePort
// 		mov		esi,Buffer
// 		mov		ecx,BufSize
// 		cld
// send_next:
// 		add     dx, 6				// modem status register
// 		in      al, dx
// 		call	IODelay
// 		test    al, 80h				// remote problem ?, DCD=0
// 		jz      send_exit			// jump if so 
// 		dec     dx					// line status register
// 		in      al, dx
// 		call	IODelay
// 		test    al, 20h				// xmit holding reg ready? 
// 		jz      send_exit			// jump if not
// 		mov     dx, BasePort		// transmit holding register
// 		lodsb						// get byte into al from [esi]
// 		out     dx, al				// send byte
// 		call	IODelay
// 		loop    send_next
// send_exit:
// 		////////////////////////////////
// 		//endp
// 		mov		eax,BufSize
// 		sub		eax,ecx
// 		pop		ecx
// 		pop		edx
// 		pop		esi
// 		mov		esp, ebp
// 		pop		ebp
// 		ret		0ch
// 		////////////////////////////////
// 	}
// }
// 
// int __declspec(naked) SerialRecvData(WORD BasePort,void*Buffer,int BufSize)
// {
// 	__asm
// 	{
// 		////////////////////////////////
// 		//proc
// 		push	ebp
// 		mov		ebp,esp
// 		push	edi
// 		push    edx
// 		push	ecx
// 		////////////////////////////////
// 		mov     dx, BasePort
// 		mov		ecx,BufSize
// 		mov		edi,Buffer
// 		add     dx, 4				//modem control register
// 		mov     al, 3				//set Data Terminal Ready
// 		out     dx, al				//and Request to Send
// 		cld
// 		mov     dx, BasePort		//base I/O address
// get_next:
// 		add     dx, 5				//line status register
// 		in      al, dx				//get error & data ready bits
// 		test    al, 0eh             //any received byte (bl=1) ?
// 		jnz     get_exit			//loop if not
// 		test    al, 1				//any received byte (bl=1) ?
// 		jz		get_exit			//loop if not
// 		mov     dx, BasePort		//receive register
// 		in      al, dx				//get byte
// 		stosb
// 		loop    get_next
// get_exit:
// 		////////////////////////////////
// 		//endp
// 		mov		eax,BufSize
// 		sub		eax,ecx
// 		pop		ecx
// 		pop		edx
// 		pop		edi
// 		mov		esp, ebp
// 		pop		ebp
// 		ret		0ch
// 		////////////////////////////////
// 	}
// }

CSerialPortConnect::CSerialPortConnect()
{
	m_hSerialPortDevice = NULL;
	m_Buffer = NULL;
	m_ComPort = 0;
}

CSerialPortConnect::~CSerialPortConnect()
{

}

bool CSerialPortConnect::Init()
{
	HANDLE hDir,hLink;
	WCHAR szBuffer[256];
	OBJECT_ATTRIBUTES	ObjAttr;
	UNICODE_STRING		UnicodeName;
	IO_STATUS_BLOCK		IOStatus;
	ULPOS BiosAddr;
	ULONG Length;
	if(MapToVAddr(0x0,&BiosAddr)==0)
	{
		OUTPUT(WSTR("Syser : Can't find com port!\n"));
		return false;
	}
	m_ComPort = GET_WORD(BiosAddr,0x400+((SyserOption.iComPort-1)%4)*2);
	RtlInitUnicodeString(&UnicodeName,WSTR("\\??"));
	InitializeObjectAttributes(&ObjAttr,&UnicodeName,OBJ_CASE_INSENSITIVE,NULL,NULL);
	if(!NT_SUCCESS(ZwOpenDirectoryObject(&hDir,DIRECTORY_QUERY,&ObjAttr)))
	{
		OUTPUT(WSTR("Syser : Can't open\\??!\n"));
		return false;
	}
	TSPrintf(szBuffer,WSTR("com%d"),SyserOption.iComPort);
	RtlInitUnicodeString(&UnicodeName,szBuffer);
	InitializeObjectAttributes(&ObjAttr,&UnicodeName,OBJ_CASE_INSENSITIVE,hDir,NULL);
	if(!NT_SUCCESS(ZwOpenSymbolicLinkObject(&hLink,GENERIC_READ,&ObjAttr)))
	{
		OUTPUT(WSTR("Syser : Can't open COM Device!\n"));
		return false;
	}
	UnicodeName.MaximumLength = sizeof(szBuffer)/sizeof(WCHAR);
	UnicodeName.Length = 0;
	UnicodeName.Buffer = szBuffer;
	if(!NT_SUCCESS(ZwQuerySymbolicLinkObject(hLink,&UnicodeName,&Length)))
	{
		OUTPUT(WSTR("Syser : Can't Query COM Device Symbol Link !\n"));
		return false;
	}
	ZwClose(hLink);
	m_hSerialPortDevice = NULL;
	InitializeObjectAttributes(&ObjAttr,&UnicodeName,OBJ_KERNEL_HANDLE,NULL,NULL);
	ZwCreateFile(&m_hSerialPortDevice,GENERIC_READ,&ObjAttr,&IOStatus,NULL,FILE_ATTRIBUTE_NORMAL,0,FILE_OPEN,0,NULL,0);
	OUTPUT(WSTR("Syser : COM%d port = 0x%X , Device Handle = 0x%08X\n"),SyserOption.iComPort,m_ComPort,m_hSerialPortDevice);
	m_MaxBufSize = SD_MAX_LENGTH;
	m_Buffer = new BYTE[m_MaxBufSize];
	m_BufSize = 0;
	return true;
}

void CSerialPortConnect::Release()
{
	if(m_hSerialPortDevice)
		ZwClose(m_hSerialPortDevice);
	SafeDelete(m_Buffer);
}

int CSerialPortConnect::RecvData(void*Buffer,int BufSize)
{
	return SyserSerialRecvData(m_ComPort,Buffer,BufSize);
}

int CSerialPortConnect::SendData(void*Buffer,int BufSize)
{
	return SyserSerialSendData(m_ComPort,Buffer,BufSize);
}


DWORD	gHardInt4Vector = 0;
DWORD	gHardInt3Vector = 0;
ST_DESC* Com1Com3Desc=NULL;
ST_DESC* Com2Com4Desc=NULL;
VADDR32 gOldCom1Com3Proc=0;
VADDR32 gOldCom2Com4Proc=0;
DWORD dwInterruptFbAddress=0;
DWORD dwInterruptFcAddress=0;
// 
// __declspec(naked) void  SerialCom1Com3Proc()
// {
// 	__asm
// 	{
// 		pushfd
// 		cmp cs:gbActive,1
// 		jz local_001
// 		popfd
// 		ret
// local_001:
// 		pushad
// 		push ds
// 		push es
// 		mov eax,0x10
// 		mov ds,ax
// 		mov es,ax
// 	}
// 	SetInteruptEOI(4);
// 	__asm
// 	{
// 		pop es
// 		pop ds
// 		popad
// 		popfd
// 		lea esp,[esp+4]
// 		iretd
// 	}
// }
// 
// __declspec(naked) void  SerialCom2Com4Proc()
// {
// 	__asm
// 	{
// 		pushfd	
// 		cmp cs:gbActive,1
// 		jz local_001
// 		popfd
// 		ret
// local_001:
// 		pushad
// 		push ds
// 		push es
// 		mov eax,0x10
// 		mov ds,ax
// 		mov es,ax
// 	}
// 	SetInteruptEOI(3);
// 	__asm
// 	{
// 		pop es
// 		pop ds		
// 		popad
// 		popfd
// 		lea esp,[esp+4]
// 		iretd
// 	}
// }

// 
// __declspec (naked) void Interrupt_0xFB_Com1_Com3_Service()
// {
// 	__asm
// 	{
// 		pushfd
// 		cmp cs:gbActive,0
// 		jnz local_2
// 		popfd
// 		ret
// 	}
// 	__asm
// 	{
// local_2:
// 		popfd
// 		push cs:SerialCom1Com3Proc
// 		ret
// 	}
// }
// 
// __declspec (naked) void Interrupt_0xFC_Com2_Com4_Service()
// {
// 	__asm
// 	{
// 		pushfd
// 		cmp cs:gbActive,0
// 		jnz local_2
// 		popfd
// 		ret
// 	}
// 	__asm
// 	{
// local_2:
// 		popfd
// 		push cs:SerialCom2Com4Proc
// 		ret
// 	}
// }

