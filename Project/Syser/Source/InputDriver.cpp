#include "StdAfx.h"
#include "Syser.h"
#include "InputDriver.h"
#include "X86Optr.h"
#include "Interrupt2D.h"
#include "SerialPort.h"
#include "Services.h"
#include "ObjectDirectory.h"
#include "pci.h"
#include "IOAPIC.h"
#include "PIC_8259.h"
#include "TimerInterrupt.h"
#include "NMIInterruptHandle.h"
#include "HardWareInterruptCtrl.h"
#include "Mouse.h"
#include "PS2Mouse.h"
#include "UHCIDevice.h"
#include "Int0xe.h"
#include "Int0xd.h"
#include "Int3.h"
#include "VirtualPCSupport.h"
#include "VMWareSupport.h"

#ifdef __cplusplus
extern "C" {
#endif

bool gbInterruptInstalled=false;
bool gHasPS2Keyboard=false;
bool gHasPS2Mouse=false;
extern bool*pbSyserDisabled;
bool bKeytoSoftice = false;
DWORD gHardInt1Vector=0xffffffff;
DWORD gHardIntCVector=0xffffffff;
DWORD gHardInt8Vector=0xffffffff;
ULONG gSystemTimerFrequency = 0;
ULONGLONG gSystemTickCount = 0;
DWORD dwMouseErrorWait = 0;
DWORD dwWaitMouseCounter = 0;
DWORD dwTmpVar2 = 0;
UINT nKeyBufferLength = KEYBUFFERMAXLENGTH;
DWORD dwInterruptF8Address = 0;
DWORD dwInterruptFaAddress = 0;
DWORD dwInterruptF9Address = 0;
DWORD dwBakFlags = 0;
DWORD dwSofticeDriverBase = 0;
LONGLONG TscPerSec = 0;
bool gbChangeDrmState = FALSE;
bool bKeyLedCmd = FALSE;
bool bKeyNumLockStat = FALSE;
bool bKeyCapsLockStat = FALSE;
bool bKeyScrollLockStat = FALSE;
bool bKeyScrollLockStatInitOK = FALSE;
bool bKeyNumLockStatInitOK = FALSE;
bool bKeyCapsLockStatInitOK = FALSE;
BYTE byteOrgWRITE_PORT_UCHARInstruction[5];
bool bREAD_PORT_UCHAR_PatchOK = FALSE;
BYTE byteOrgREAD_PORT_UCHARInstruction[5];
bool bWRITE_PORT_UCHAR_PatchOK = FALSE;
void (*pSofticeActivePointer)(void) = NULL;
bool bActiveSoftice = FALSE;
DWORD dwTimeCounter = 0;
DWORD dwMyCounter1 = 0;								//调整鼠标中断对齐时鼠标中断产生的次数。例如在用功能键激活驱动时鼠标中断包的开始偏移是 0，从驱动中返回 Windows 时
													//鼠标中断包的偏移是 1 则要等待随后的两个鼠标中断的产生（在两键鼠标中），或是等待随后的三个鼠标中断的产生（在 3键的鼠标中）
													//这样在返回到 Windows 时鼠标才不会乱掉。
DWORD dwMyOperationMouseCounter = 0;				//本驱动在被激活时处理的鼠标中断的个数。dwMouseInterruptCounter - dwMyOperationMouseCounter 的差就是被驱动程序被加载后 Windows 处理的鼠标中断的个数
DWORD dwActivateCounter = 0;						//本驱动被加载后被激活的次数。
DWORD dwMouseUnAlignCounter = 0;					//在用热键激活本驱动时 鼠标包没有对齐的的次数。
DWORD dwMouseAlignCounter = 0;						//在用热键激活本驱动时 鼠标包对齐的的次数。 dwMouseUnAlignCounter + dwMouseAlignCounter == dwActivateCounter
DWORD dwMouseUnAlignMofifyCounter = 0;				//在用热键激活本驱动时 鼠标包没有对齐的的次数。但是在返回 Windows 时被正确修正的次数
DWORD dwMouseUnAlignErrorCounter = 0;				//在用热键激活本驱动时 鼠标包没有对齐的的次数。在返回 Windows 时鼠标对齐仍然没有被修正的次数。 dwMouseAlignMofifyCounter + dwMouseAlignErrorCounter + dwMouseUnalignNotModifyCounter== dwMouseUnAlignCounter
DWORD dwMouseInterruptCounter = 0;					//鼠标中断的总次数（驱动程序被安装时开始计算，包括 Windows 处理的中断，和本驱动被处理的中断的总和）
DWORD dwWindowsMouseCounter = 0;					//Windows 操作的鼠标中断的次数，dwWindowsMouseCounter + dwMyOperationMouseCounter == dwMouseInterruptCounter
DWORD dwMouseUnalignNotModifyCounter = 0;			//在用热键激活本驱动时 鼠标包没有对齐的的次数。但是在返回 Windows 时不用被修正。
DWORD dwWaitMouseInterrupt = FALSE;
DWORD dwKeyLedFlags = 0;
DWORD dwPhysical_0_LinesAddress=0xffffffff;					//物理地址 0 被映射的线形地址。
DWORD OwnerPageDirItemAddress = 0;
DWORD OwnerPageTabItemAddress = 0;


DWORD dwOldInterruptFA = 0;
DWORD dwOldInterruptF8 = 0;
DWORD dwOldInterruptF9 = 0;

bool bInt1HereStat = 0;
bool bInt3HereStat = 0;

KeyInterruptVariable stKeyGlobalVariable = {
	FALSE,									//bool IsActive = FALSE;						//0  代表没有进入操作模式 //1  进入了操作模式	
	FALSE,									//bool IsInsideActive = FALSE;					//用来控制键盘中断的死循环结束
	FUNCKEYRELEASE,							//DWORD dwFuncKeyState = FUNCKEYRELEASE;		//功能键的状态，0代表功能键没有被按下，1代表功能键被按下
	0,
	0,
	NULL,
	0,
	NULL,									//键盘的描述符的指针
	NULL,									//鼠标的描述符的指针
	0x10,
	0,
	0x1d,
	0x58,
	0,
	0,
	0,
	0,
	0x38,//chAltKeyScanCode
	0,//chCurrentScanCode
	0,//dwIOAPICLineAddress
	0,//dwIOAPICPhysAddress
	0,//dwLocalAPICPhysAddress
	0,//dwLocalAPICLineAddress
	FALSE,//bIsUseAPIC
	0,//DWORD dwOldMouseInterrupt	
	0,//	bMouseResponseState
	0,//dwMouseDataIndex该中断是一个鼠标数据包中的第几个数据。数据包中可能包含四个数据或则三个数据。
	0,
	0,//dwLocalAPICTaskPriority
	0,//chPrveScanCode
};
BYTE chWindowsKeyArray[0x10];   //该缓冲区是用来模拟  READ_PORT_UCHAR 函数用的，
								//该缓冲区中的数据要在i8042prt.sys 驱动读端口60时来模拟真的 60端口
bool bRightCtrlKey = FALSE;
DWORD dwCurrentReadIndex = 0;
DWORD dwCurrentWriteIndex = 0;
DWORD dwCurrentWindowsKeyLen = 0;
#define MAX_WINDOWSKEYBUFFER_LENGTH 0x10
DWORD dwEflag;
DWORD dwInSofticeDebug = 0;						//是否被 Softice 调式
BYTE *SoftIceActive = NULL;						//该变量主要用来判断是否被 我的键盘中断是否被 Softice 调试。

INT nTempVar = 0;									//临时变量随时会被删掉
DWORD dwRPUC = 0;
DWORD dwRPUCLookup = 0;
DWORD dwWPUC = 0;
DWORD dwWPUCLookup = 0;
bool gbActiveMethod = FALSE;						//激活方式，如果是真则代表是键盘激活。
/*
BYTE ShiftKeyTable[]=
{
	0xff,0x1b,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x2d,0x3d,0x08,0x09,
	0x71,0x77,0x65,0x72,0x74,0x79,0x75,0x69,0x6f,0x70,0x5b,0x5d,0x0d,0xff,0x41,0x73,
	0x44,0x46,0x47,0x48,0x4a,0x4b,0x4c,0x3b,0x27,0x60,0xff,0x5c,0x7a,0x78,0x43,0x76,
	0x42,0x6e,0x6d,0x2c,0x2e,0x2f,0xff,0x2a,0xff,0x20,0xff,0x97,0x98,0x99,0x9a,0x9b,
	0x9c,0x9d,0x9e,0x9f,0xa0,0xff,0xff,0x87,0x83,0x85,0x2d,0x81,0x35,0x82,0x2b,0x88,
	0x84,0x86,0x89,0x8a,0xff,0xff,0xff,0xa1,0xa2,
};

BYTE ShiftKeyTable1[]=
{
	0x00,0x1b,0x21,0x40,0x23,0x24,0x25,0x5e,0x26,0x2a,0x28,0x29,0x5f,0x2b,0x08,0x8f,
	0x51,0x57,0x45,0x52,0x54,0x59,0x55,0x49,0x4f,0x50,0x7b,0x7d,0x0d,0x00,0x41,0x53,
	0x44,0x46,0x47,0x48,0x4a,0x4b,0x4c,0x3a,0x22,0x7e,0x00,0x7c,0x5a,0x58,0x43,0x56,
	0x42,0x4e,0x4d,0x3c,0x3e,0x3f,0x00,0x2a,0x00,0x20,0x00,0xa3,0xa4,0xa5,0xa6,0xa7,
	0xa8,0xa9,0xaa,0xab,0xac,0x00,0x00,0x87,0xe2,0x85,0x2d,0xe0,0x35,0xe1,0x2b,0x88,
	0xe3,0x86,0x89,0x8a,0x00,0x00,0x00,0xad,0xae,
};



BYTE NormalTable1[]=
{
	0x00,0x1b,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x2d,0x3d,0x08,0x09,
	0x71,0x77,0x65,0x72,0x74,0x79,0x75,0x69,0x6f,0x70,0x5b,0x5d,0x0d,0x00,0x61,0x73,
	0x64,0x66,0x67,0x68,0x6a,0x6b,0x6c,0x3b,0x27,0x60,0x00,0x5c,0x7a,0x78,0x63,0x76,
	0x62,0x6e,0x6d,0x2c,0x2e,0x2f,0x00,0x2a,0x00,0x20,0x00,0x97,0x98,0x99,0x9a,0x9b,
	0x9c,0x9d,0x9e,0x9f,0xa0,0x00,0x00,0x87,0x83,0x85,0x2d,0x81,0x35,0x82,0x2b,0x88,
	0x84,0x86,0x89,0x8a,0x00,0x00,0x00,0xa1,0xa2,
};
*/
BYTE ExternTable[]=
{
	0xff,					//scancode 00 0x00 空的没有对应的键
	0xff,					//scancode 01 0x01 'Esc'
	0xff,					//scancode 02 0x02	'1'
	0xff,					//scancode 03 0x03	'2'
	0xff,					//scancode 04 0x04	'3'
	0xff,					//scancode 05 0x05	'4'
	0xff,					//scancode 06 0x06	'5'
	0xff,					//scancode 07 0x07	'6'
	0xff,					//scancode 08 0x08	'7'
	0xff,					//scancode 09 0x09	'8'
	0xff,					//scancode 10 0x0a	'9'
	0xff,					//scancode 11 0x0b  '0'
	0xff,					//scancode 12 0x0c  '-_'
	0xff,					//scancode 13 0x0d  '=+'	
	0xff,					//scancode 14 0x0e  'Back Space'
	0xff,					//scancode 15 0x0f  'Tab'
	0xff,					//scancode 16 0x10	'Q'
	0xff,					//scancode 17 0x11	'W'
	0xff,					//scancode 18 0x12	'E'
	0xff,					//scancode 19 0x13	'R'
	0xff,					//scancode 20 0x14	'T'
	0xff,					//scancode 21 0x15	'Y'
	0xff,					//scancode 22 0x16	'U'
	0xff,					//scancode 23 0x17	'I'
	0xff,					//scancode 24 0x18	'O'
	0xff,					//scancode 25 0x19	'P'
	0xff,					//scancode 26 0x1a	'[{'
	0xff,					//scancode 27 0x1b	'P'
	WISP_VK_RETURN,			//scancode 28 0x1c	'}]'
	WISP_VK_RCONTROL,		//scancode 29 0x1d	'Left Ctrl'
	0xff,					//scancode 30 0x1E	'A'
	0xff,					//scancode 31 0x1F	'S'
	0xff,					//scancode 32 0x20	'D'
	0xff,					//scancode 33 0x21	'F'
	0xff,					//scancode 34 0x22	'G'
	0xff,					//scancode 35 0x23	'H'
	0xff,					//scancode 36 0x24	'J'
	0xff,					//scancode 37 0x25	'K'
	0xff,					//scancode 38 0x26	'L'
	0xff,						//scancode 39 0x27	';:'
	0xff,						//scancode 40 0x28	''"'
	0xff,						//scancode 41 0x29  ''
	0xff,						//scancode 42 0x2a  'Left Shift'
	0xff,						//scancode 43 0x2b  '\|'
	0xff,						//scancode 44 0x2c	'Z'
	0xff,						//scancode 45 0x2d	'X'
	0xff,						//scancode 46 0x2E	'C'
	0xff,						//scancode 47 0x2F	'V'
	0xff,						//scancode 48 0x30	'B'
	0xff,						//scancode 49 0x31	'N'
	0xff,						//scancode 50 0x32	'M'
	0xff,						//scancode 51 0x33  ',<'
	0xff,						//scancode 52 0x34  ',>'
	WISP_VK_OEM_2,				//scancode 53 0x35  '/?'
	0xff,						//scancode 54 0x36  'Right Shift'
	WISP_VK_PRINT,				//scancode 55 0x37  '*'在小键盘上 . 'Print Screen* Sys Rq' 0xE0 0x2A 0xE0 0x37 0xE0 0xB7 0xE0 0xAA
	WISP_VK_RALT,				//scancode 56 0x38  'Left Alt'
	0xff,						//scancode 57 0x39  'Blank Space' 
	0xff,						//scancode 58 0x3a	'Caps Lock'
	0xff,						//scancode 59 0x3b  'F1' 
	0xff,						//scancode 60 0x3c  'F2'
	0xff,						//scancode 61 0x3d  'F3'
	0xff,						//scancode 62 0x3e  'F4'
	0xff,						//scancode 63 0x3f  'F5'
	0xff,						//scancode 64 0x40  'F6'
	0xff,						//scancode 65 0x41  'F7'
	0xff,						//scancode 66 0x42  'F8'
	0xff,						//scancode 67 0x43  'F9'
	0xff,						//scancode 68 0x44  'F10'
	0xff,						//scancode 69 0x45  'Num Lock'   
	0xff,						//scancode 70 0x46  'Scroll Lock'
	WISP_VK_HOME,				//scancode 71 0x47  'Home'
	WISP_VK_UP,					//scancode 72 0x48  'Up Arrow Key'在小键盘上 .
	WISP_VK_PAGE_UP,			//scancode 73 0x49  'Page Up'在小键盘上
	0xff,						//scancode 74 0x4a  '-'在小键盘上
	WISP_VK_LEFT,				//scancode 75 0x4b  'Left Arrow Key'在小键盘上 .						
	0xff,						//scancode 76 0x4c  '5' 在小键盘上
	WISP_VK_RIGHT,				//scancode 77 0x4d  'Right Arrow Key' 在小键盘上
	0xff,						//scancode 78 0x4e  '+' 
	WISP_VK_END,				//scancode 79 0x4f  'End' 在小键盘上
	WISP_VK_DOWN,				//scancode 80 0x50  'Down Arrow Key'在小键盘上
	WISP_VK_PAGE_DOWN,			//scancode 81 0x51  'Page Dn'在小键盘上
	WISP_VK_INSERT,				//scancode 82 0x52  'Ins'在小键盘上
	WISP_VK_DELETE,				//scancode 83 0x53  'Del'在小键盘上
	0xff,						//scancode 84 0x54
	0xff,						//scancode 85 0x55
	0xff,						//scancode 86 0x56
	0xff,						//scancode 87 0x57  'F11'
	0xff,						//scancode 88 0x58  'F12'
	0xff,						//scancode 89 0x59  ''
	0xff,						//scancode 90 0x5a  ''
	WISP_VK_LWIN,				//scancode 91 0x5b  'Left Windows'
	WISP_VK_RWIN,				//scancode 92 0x5c  'Right Windows'
	WISP_VK_APPS,				//scancode 93 0x5d  'Apps'
	WISP_VK_0X5E,				//scancode 94 0x5e  'Power'
	WISP_VK_SLEEP,				//scancode 95 0x5f  'Sleep'
	0xff,						//scancode 96 0x60	
	0xff,						//scancode 97 0x61  
	0xff,						//scancode 98 0x62
	0xff,						//scancode 99 0x63  'Wake Up'
};
//E0 2A E0 37 'Print Screen' 键被按下 //E0 B7 E0 AA 'Print Screen' 键被抬起
//E1 1D 45 E1 9D C5'Pause Break' 键被按下 抬起时没有扫描码
BYTE NormalTable[2][0x80]=
{
	{
	0xff,						//scancode 00 0x00 空的没有对应的键
	WISP_VK_ESCAPE,				//scancode 01 0x01 'Esc'
	WISP_VK_1,					//scancode 02 0x02	'1'
	WISP_VK_2,					//scancode 03 0x03	'2'
	WISP_VK_3,					//scancode 04 0x04	'3'
	WISP_VK_4,					//scancode 05 0x05	'4'
	WISP_VK_5,					//scancode 06 0x06	'5'
	WISP_VK_6,					//scancode 07 0x07	'6'
	WISP_VK_7,					//scancode 08 0x08	'7'
	WISP_VK_8,					//scancode 09 0x09	'8'
	WISP_VK_9,					//scancode 10 0x0a	'9'
	WISP_VK_0,					//scancode 11 0x0b  '0'
	WISP_VK_OEM_MINUS,			//scancode 12 0x0c  '-_'
	WISP_VK_OEM_PLUS,			//scancode 13 0x0d  '=+'	
	WISP_VK_BACK,				//scancode 14 0x0e  'Back Space'
	WISP_VK_TAB,				//scancode 15 0x0f  'Tab'
	WISP_VK_Q,					//scancode 16 0x10	'Q'
	WISP_VK_W,					//scancode 17 0x11	'W'
	WISP_VK_E,					//scancode 18 0x12	'E'
	WISP_VK_R,					//scancode 19 0x13	'R'
	WISP_VK_T,					//scancode 20 0x14	'T'
	WISP_VK_Y,					//scancode 21 0x15	'Y'
	WISP_VK_U,					//scancode 22 0x16	'U'
	WISP_VK_I,					//scancode 23 0x17	'I'
	WISP_VK_O,					//scancode 24 0x18	'O'
	WISP_VK_P,					//scancode 25 0x19	'P'
	WISP_VK_LSQUARE_BRACKET,	//scancode 26 0x1a	'[{'
	WISP_VK_RSQUARE_BRACKET,	//scancode 27 0x1b	'P'
	WISP_VK_RETURN,				//scancode 28 0x1c	'Enter'
	WISP_VK_CONTROL,			//scancode 29 0x1d	'Left Ctrl'
	WISP_VK_A,					//scancode 30 0x1E	'A'
	WISP_VK_S,					//scancode 31 0x1F	'S'
	WISP_VK_D,					//scancode 32 0x20	'D'
	WISP_VK_F,					//scancode 33 0x21	'F'
	WISP_VK_G,					//scancode 34 0x22	'G'
	WISP_VK_H,					//scancode 35 0x23	'H'
	WISP_VK_J,					//scancode 36 0x24	'J'
	WISP_VK_K,					//scancode 37 0x25	'K'
	WISP_VK_L,					//scancode 38 0x26	'L'
	WISP_VK_SEMI,				//scancode 39 0x27	';:'
	WISP_VK_QUOT,				//scancode 40 0x28	''"'
	0xff,						//scancode 41 0x29  ''
	WISP_VK_SHIFT,				//scancode 42 0x2a  'Left Shift'
	WISP_VK_OEM_5,				//scancode 43 0x2b  '\|'
	WISP_VK_Z,					//scancode 44 0x2c	'Z'
	WISP_VK_X,					//scancode 45 0x2d	'X'
	WISP_VK_C,					//scancode 46 0x2E	'C'
	WISP_VK_V,					//scancode 47 0x2F	'V'
	WISP_VK_B,					//scancode 48 0x30	'B'
	WISP_VK_N,					//scancode 49 0x31	'N'
	WISP_VK_M,					//scancode 50 0x32	'M'
	WISP_VK_OEM_COMMA,			//scancode 51 0x33  ',<'
	WISP_VK_OEM_PERIOD,			//scancode 52 0x34  ',>'
	WISP_VK_OEM_2,				//scancode 53 0x35  '/?'
	WISP_VK_SHIFT,				//scancode 54 0x36  'Right Shift'
	WISP_VK_MULTIPLY,			//scancode 55 0x37  '*'在小键盘上 . 'Print Screen* Sys Rq' 0xE0 0x2A 0xE0 0x37 0xE0 0xB7 0xE0 0xAA
	WISP_VK_ALT,				//scancode 56 0x38  'Left Alt'
	WISP_VK_SPACE,				//scancode 57 0x39  'Blank Space' 
	WISP_VK_CAPITAL,			//scancode 58 0x3a	'Caps Lock'
	WISP_VK_F1,					//scancode 59 0x3b  'F1' 
	WISP_VK_F2,					//scancode 60 0x3c  'F2'
	WISP_VK_F3,					//scancode 61 0x3d  'F3'
	WISP_VK_F4,					//scancode 62 0x3e  'F4'
	WISP_VK_F5,					//scancode 63 0x3f  'F5'
	WISP_VK_F6,					//scancode 64 0x40  'F6'
	WISP_VK_F7,					//scancode 65 0x41  'F7'
	WISP_VK_F8,					//scancode 66 0x42  'F8'
	WISP_VK_F9,					//scancode 67 0x43  'F9'
	WISP_VK_F10,				//scancode 68 0x44  'F10'
	WISP_VK_NUMLOCK,			//scancode 69 0x45  'Num Lock'   Pause Break  0xE1 0x1D 0x45 0xE1 0x9D 0xC5
	WISP_VK_SCROLL,				//scancode 70 0x46  'Scroll Lock'
	WISP_VK_NUMPAD7,			//scancode 71 0x47  'Home'
	WISP_VK_NUMPAD8,			//scancode 72 0x48  'Up Arrow Key'在小键盘上 .
	WISP_VK_NUMPAD9,			//scancode 73 0x49  'Page Up'在小键盘上
	WISP_VK_SUBTRACT,			//scancode 74 0x4a  '-'在小键盘上
	WISP_VK_NUMPAD4,			//scancode 75 0x4b  'Left Arrow Key'在小键盘上 .						
	WISP_VK_NUMPAD5,			//scancode 76 0x4c  '5' 在小键盘上
	WISP_VK_NUMPAD6,			//scancode 77 0x4d  'Right Arrow Key' 在小键盘上
	WISP_VK_ADD,				//scancode 78 0x4e  '+' 
	WISP_VK_NUMPAD1,			//scancode 79 0x4f  'End' 在小键盘上
	WISP_VK_NUMPAD2,			//scancode 80 0x50  'Down Arrow Key'在小键盘上
	WISP_VK_NUMPAD3,			//scancode 81 0x51  'Page Dn'在小键盘上
	WISP_VK_NUMPAD0,			//scancode 82 0x52  'Ins'在小键盘上
    WISP_VK_DECIMAL,			//scancode 83 0x53  'Del'在小键盘上
	0xff,						//scancode 84 0x54
	0xff,						//scancode 85 0x55
	0xff,						//scancode 86 0x56
	WISP_VK_F11,				//scancode 87 0x57  'F11'
	WISP_VK_F12,				//scancode 88 0x58  'F12'
	0xff,						//scancode 89 0x59  ''
	0xff,						//scancode 90 0x5a  ''
	0xff,						//scancode 91 0x5b  'Left Windows'
	0xff,						//scancode 92 0x5c  'Right Windows'
	0xff,						//scancode 93 0x5d  'Window Apps'
	0xff,						//scancode 94 0x5e  'Power'
	0xff,						//scancode 95 0x5f  'Sleep'
	0xff,						//scancode 96 0x60	
	WISP_VK_PAUSE,				//scancode 97 0x61  
	0xff,						//scancode 98 0x62
	0xff,						//scancode 99 0x63  'Wake Up'
},
{
	0xff,						//scancode 00 0x00 空的没有对应的键
	WISP_VK_ESCAPE,				//scancode 01 0x01 'Esc'
	WISP_VK_1,					//scancode 02 0x02	'1'
	WISP_VK_2,					//scancode 03 0x03	'2'
	WISP_VK_3,					//scancode 04 0x04	'3'
	WISP_VK_4,					//scancode 05 0x05	'4'
	WISP_VK_5,					//scancode 06 0x06	'5'
	WISP_VK_6,					//scancode 07 0x07	'6'
	WISP_VK_7,					//scancode 08 0x08	'7'
	WISP_VK_8,					//scancode 09 0x09	'8'
	WISP_VK_9,					//scancode 10 0x0a	'9'
	WISP_VK_0,					//scancode 11 0x0b  '0'
	WISP_VK_OEM_MINUS,			//scancode 12 0x0c  '-_'
	WISP_VK_OEM_PLUS,			//scancode 13 0x0d  '=+'	
	WISP_VK_BACK,				//scancode 14 0x0e  'Back Space'
	WISP_VK_TAB,				//scancode 15 0x0f  'Tab'
	WISP_VK_A,					//scancode 16 0x10	'Q'
	WISP_VK_Z,					//scancode 17 0x11	'W'
	WISP_VK_E,					//scancode 18 0x12	'E'
	WISP_VK_R,					//scancode 19 0x13	'R'
	WISP_VK_T,					//scancode 20 0x14	'T'
	WISP_VK_Y,					//scancode 21 0x15	'Y'
	WISP_VK_U,					//scancode 22 0x16	'U'
	WISP_VK_I,					//scancode 23 0x17	'I'
	WISP_VK_O,					//scancode 24 0x18	'O'
	WISP_VK_P,					//scancode 25 0x19	'P'
	WISP_VK_LSQUARE_BRACKET,	//scancode 26 0x1a	'[{'
	WISP_VK_RSQUARE_BRACKET,	//scancode 27 0x1b	'P'
	WISP_VK_RETURN,				//scancode 28 0x1c	'Enter'
	WISP_VK_CONTROL,			//scancode 29 0x1d	'Left Ctrl'
	WISP_VK_Q,					//scancode 30 0x1E	'A'
	WISP_VK_S,					//scancode 31 0x1F	'S'
	WISP_VK_D,					//scancode 32 0x20	'D'
	WISP_VK_F,					//scancode 33 0x21	'F'
	WISP_VK_G,					//scancode 34 0x22	'G'
	WISP_VK_H,					//scancode 35 0x23	'H'
	WISP_VK_J,					//scancode 36 0x24	'J'
	WISP_VK_K,					//scancode 37 0x25	'K'
	WISP_VK_L,					//scancode 38 0x26	'L'
	WISP_VK_M,//WISP_VK_SEMI,				//scancode 39 0x27	';:'
	WISP_VK_QUOT,				//scancode 40 0x28	''"'
	0xff,						//scancode 41 0x29  ''
	WISP_VK_SHIFT,				//scancode 42 0x2a  'Left Shift'
	WISP_VK_OEM_5,				//scancode 43 0x2b  '\|'
	WISP_VK_W,					//scancode 44 0x2c	'Z'
	WISP_VK_X,					//scancode 45 0x2d	'X'
	WISP_VK_C,					//scancode 46 0x2E	'C'
	WISP_VK_V,					//scancode 47 0x2F	'V'
	WISP_VK_B,					//scancode 48 0x30	'B'
	WISP_VK_N,					//scancode 49 0x31	'N'
	WISP_VK_SEMI,//WISP_VK_M,					//scancode 50 0x32	'M'
	WISP_VK_OEM_COMMA,			//scancode 51 0x33  ',<'
	WISP_VK_OEM_PERIOD,			//scancode 52 0x34  ',>'
	WISP_VK_OEM_2,				//scancode 53 0x35  '/?'
	WISP_VK_SHIFT,				//scancode 54 0x36  'Right Shift'
	WISP_VK_MULTIPLY,			//scancode 55 0x37  '*'在小键盘上 . 'Print Screen* Sys Rq' 0xE0 0x2A 0xE0 0x37 0xE0 0xB7 0xE0 0xAA
	WISP_VK_ALT,				//scancode 56 0x38  'Left Alt'
	WISP_VK_SPACE,				//scancode 57 0x39  'Blank Space' 
	WISP_VK_CAPITAL,			//scancode 58 0x3a	'Caps Lock'
	WISP_VK_F1,					//scancode 59 0x3b  'F1' 
	WISP_VK_F2,					//scancode 60 0x3c  'F2'
	WISP_VK_F3,					//scancode 61 0x3d  'F3'
	WISP_VK_F4,					//scancode 62 0x3e  'F4'
	WISP_VK_F5,					//scancode 63 0x3f  'F5'
	WISP_VK_F6,					//scancode 64 0x40  'F6'
	WISP_VK_F7,					//scancode 65 0x41  'F7'
	WISP_VK_F8,					//scancode 66 0x42  'F8'
	WISP_VK_F9,					//scancode 67 0x43  'F9'
	WISP_VK_F10,				//scancode 68 0x44  'F10'
	WISP_VK_NUMLOCK,			//scancode 69 0x45  'Num Lock'   Pause Break  0xE1 0x1D 0x45 0xE1 0x9D 0xC5
	WISP_VK_SCROLL,				//scancode 70 0x46  'Scroll Lock'
	WISP_VK_NUMPAD7,			//scancode 71 0x47  'Home'
	WISP_VK_NUMPAD8,			//scancode 72 0x48  'Up Arrow Key'在小键盘上 .
	WISP_VK_NUMPAD9,			//scancode 73 0x49  'Page Up'在小键盘上
	WISP_VK_SUBTRACT,			//scancode 74 0x4a  '-'在小键盘上
	WISP_VK_NUMPAD4,			//scancode 75 0x4b  'Left Arrow Key'在小键盘上 .						
	WISP_VK_NUMPAD5,			//scancode 76 0x4c  '5' 在小键盘上
	WISP_VK_NUMPAD6,			//scancode 77 0x4d  'Right Arrow Key' 在小键盘上
	WISP_VK_ADD,				//scancode 78 0x4e  '+' 
	WISP_VK_NUMPAD1,			//scancode 79 0x4f  'End' 在小键盘上
	WISP_VK_NUMPAD2,			//scancode 80 0x50  'Down Arrow Key'在小键盘上
	WISP_VK_NUMPAD3,			//scancode 81 0x51  'Page Dn'在小键盘上
	WISP_VK_NUMPAD0,			//scancode 82 0x52  'Ins'在小键盘上
	WISP_VK_DECIMAL,			//scancode 83 0x53  'Del'在小键盘上
	0xff,						//scancode 84 0x54
	0xff,						//scancode 85 0x55
	WISP_VK_OEM_102,						//scancode 86 0x56
	WISP_VK_F11,				//scancode 87 0x57  'F11'
	WISP_VK_F12,				//scancode 88 0x58  'F12'
	0xff,						//scancode 89 0x59  ''
	0xff,						//scancode 90 0x5a  ''
	0xff,						//scancode 91 0x5b  'Left Windows'
	0xff,						//scancode 92 0x5c  'Right Windows'
	0xff,						//scancode 93 0x5d  'Window Apps'
	0xff,						//scancode 94 0x5e  'Power'
	0xff,						//scancode 95 0x5f  'Sleep'
	0xff,						//scancode 96 0x60	
	WISP_VK_PAUSE,				//scancode 97 0x61  
	0xff,						//scancode 98 0x62
	0xff,						//scancode 99 0x63  'Wake Up'
},
};

#ifdef __cplusplus
}; // extern "C"
#endif

DWORD GetScanCode(DWORD WispVKCode)
{
	DWORD ScanCode=0;
	for(int i=0;i<sizeof(NormalTable[0])/sizeof(NormalTable[0][0]);i++)
	{
		if(NormalTable[SyserOption.iKeyboardLayer][i]==WispVKCode)
			ScanCode=i;
	}
	return ScanCode;
}
/*
unsigned char rawData[212] =
{
		0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x30, 0x00, 0x2E, 0x00, 0x20, 0x00, 0x12, 0x00, 0x21, 0x00, 
		0x22, 0x00, 0x23, 0x00, 0x17, 0x00, 0x24, 0x00, 0x25, 0x00, 0x26, 0x00, 0x32, 0x00, 0x31, 0x00, 
		0x18, 0x00, 0x19, 0x00, 0x10, 0x00, 0x13, 0x00, 0x1F, 0x00, 0x14, 0x00, 0x16, 0x00, 0x2F, 0x00, 
		0x11, 0x00, 0x2D, 0x00, 0x15, 0x00, 0x2C, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 
		0x06, 0x00, 0x07, 0x00, 0x08, 0x00, 0x09, 0x00, 0x0A, 0x00, 0x0B, 0x00, 0x1C, 0x00, 0x01, 0x00, 
		0x0E, 0x00, 0x0F, 0x00, 0x39, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x1A, 0x00, 0x1B, 0x00, 0x2B, 0x00, 
		0x2B, 0x00, 0x27, 0x00, 0x28, 0x00, 0x29, 0x00, 0x33, 0x00, 0x34, 0x00, 0x35, 0x00, 0x3A, 0x00, 
		0x3B, 0x00, 0x3C, 0x00, 0x3D, 0x00, 0x3E, 0x00, 0x3F, 0x00, 0x40, 0x00, 0x41, 0x00, 0x42, 0x00, 
		0x43, 0x00, 0x44, 0x00, 0x57, 0x00, 0x58, 0x00, 0xE0, 0x37, 0x46, 0x00, 0xE0, 0x46, 0xE0, 0x52, 
		0xE0, 0x47, 0xE0, 0x49, 0xE0, 0x53, 0xE0, 0x4F, 0xE0, 0x51, 0xE0, 0x4D, 0xE0, 0x4B, 0xE0, 0x50, 
		0xE0, 0x48, 0x45, 0x00, 0xE0, 0x35, 0x37, 0x00, 0x4A, 0x00, 0x4E, 0x00, 0xE0, 0x1C, 0x4F, 0x00, 
		0x50, 0x00, 0x51, 0x00, 0x4B, 0x00, 0x4C, 0x00, 0x4D, 0x00, 0x47, 0x00, 0x48, 0x00, 0x49, 0x00, 
		0x52, 0x00, 0x53, 0x00, 0x56, 0x00, 0xE0, 0x5D, 0x00, 0x00, 0x59, 0x00, 0x5D, 0x00, 0x5E, 0x00, 
		0x5F, 0x00, 0x00, 0x00, 
} ;

BYTE OldNormalTable[]=
{
	0xff,0x1b,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x5f,0x2b,0x08,0x8f,
	0x51,0x57,0x45,0x52,0x54,0x59,0x55,0x49,0x4f,0x50,0x7b,0x7d,0x0d,0xff,0x41,0x53,
	0x44,0x46,0x47,0x48,0x4a,0x4b,0x4c,0x3a,0x22,0x7e,0xff,0x7c,0x5a,0x58,0x43,0x56,
	0x42,0x4e,0x4d,0x3c,0x3e,0x3f,0xff,0x2a,0xff,0x20,0xff,0xa3,0xa4,0xa5,0xa6,0xa7,
	0xa8,0xa9,0xaa,0xab,0xac,0x00,0xff,0x87,0xe2,0x85,0x2d,0xe0,0x35,0xe1,0x2b,0x88,
	0xe3,0x86,0x89,0x8a,0xff,0xff,0xff,0xad,0xae,
};
BYTE AltKeyTable[]=
{
	0x00,0x1b,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x2d,0x3d,0x08,0x09,
	0x71,0xd9,0x65,0xd8,0x8d,0x79,0x75,0x69,0x6f,0x70,0x5b,0x5d,0x0d,0x00,0x61,0xc7,
	0xd5,0x66,0x67,0x68,0x6a,0x6b,0xd7,0x3b,0x27,0x60,0x00,0x5c,0x7a,0x78,0xd4,0x76,
	0x62,0x6e,0x6d,0x2c,0x2e,0x2f,0x00,0x2a,0x00,0x20,0x00,0xbb,0xbc,0xbd,0xbe,0xbf,
	0xc0,0xc1,0xc2,0xc3,0xc4,0x00,0x00,0x87,0xca,0xcc,0x2d,0x81,0x35,0x82,0x2b,0x88,
	0xcb,0xcd,0x89,0x8a,0x00,0x00,0x00,0xc5,0xc6,
};
BYTE CtrlKeyTable[]=
{
	0x00,0x1b,0x21,0x40,0x23,0x24,0x25,0x5e,0x26,0x2a,0x28,0x29,0x5f,0x2b,0x08,0x8f,
	0x51,0x57,0x45,0x52,0x54,0x59,0x55,0x49,0x4f,0x50,0x7b,0x7d,0x0d,0x00,0x41,0x53,
	0x44,0x46,0x47,0x48,0x4a,0x4b,0xdd,0x3a,0x22,0x7e,0x00,0x7c,0x5a,0x58,0xda,0xdb,
	0x42,0x4e,0xdc,0x3c,0x3e,0x3f,0x00,0x2a,0x00,0x20,0x00,0xaf,0xb0,0xb1,0xb2,0xb3,
	0xb4,0xb5,0xb6,0xb7,0xb8,0x00,0x00,0xf6,0xf2,0xf4,0x2d,0xf0,0x35,0xf1,0x2b,0xf7,
	0xf3,0xf5,0x30,0x2e,0x00,0x00,0x00,0xb9,0xba,
};
BYTE CtrlAltKeyTable[]=
{
	0x00,0x1b,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x2d,0x3d,0x08,0x09,
	0x71,0x77,0x65,0x72,0x74,0x79,0x75,0x69,0x6f,0x70,0x5b,0x5d,0x0d,0x00,0x61,0x73,
	0x64,0x66,0x67,0x68,0x6a,0x6b,0x6c,0x3b,0x27,0x60,0x00,0x5c,0x7a,0x78,0xdf,0x76,
	0x62,0x6e,0x6d,0x2c,0x2e,0x2f,0x00,0x2a,0x00,0x20,0x00,0x97,0x98,0x99,0x9a,0x9b,
	0x9c,0x9d,0x9e,0x9f,0xa0,0x00,0x00,0x8e,0xfe,0x90,0x2d,0xfc,0x92,0xfd,0x2b,0x8f,
	0xff,0x91,0x89,0x8a,0x00,0x00,0x00,0xa1,0xa2,
};
*/
//WORD ExitMouseBuffer[0x1024];
// __declspec (naked) void WaitKeyboardOutPutBufferFull()
// {
// 	__asm {
// 		push ecx
// 		push eax
// 		mov ecx, 0x2000
// local_2:		
// 		in al, 0x64
// 		push ecx
// 		mov ecx,0x14
// local_1:		
// 		loop local_1
// 		pop ecx
// 		test al,1
// 		loope local_2
// 		pop eax
// 		pop ecx
// 		ret
// 	}
// }

// __declspec (naked) void WaitKeyboardInputBufferEmpte()
// {
// 	__asm{
// 		push ecx
// 		push eax
// 		mov ecx, 0x2000
// local_2:
// 		in al, 0x64
// 		push ecx
// 		mov ecx, 0x14
// local_1:		
// 		loop local_1
// 		pop ecx
// 		test al,2
// 		loopne local_2
// 		pop eax
// 		pop ecx
// 		ret
// 	}
// }

//  void SimulateKeyboardInput(BYTE scancode,bool isDisableInterrupt)
// {
// 	DWORD dwIsInterrupt = 0;
// 	if(isDisableInterrupt)
// 		dwIsInterrupt = 1;
// 	__asm{
// 		pushad
// 		mov ah,scancode
// 		mov edx, dwIsInterrupt
// 		cmp edx,0
// 		jz local_b
// 		mov al, 0x20						//读键盘命令字 的命令
// 		out 0x64,al
// 		push ecx
// 		mov ecx, 0x14
// local_1:
// 		loop local_1
// 		pop ecx
// 		
// 		call WaitKeyboardOutPutBufferFull
// 		in al, 0x60							//读书键盘命令字
// 		push ecx
// 		mov ecx, 0x14
// local_2:
// 		loop local_2
// 		pop ecx
// 		call WaitKeyboardInputBufferEmpte
// 		mov al,0x60							//写键盘命令字 的命令
// 		out 0x64,al
// 		push ecx
// 		mov ecx, 0x14
// local_3:
// 		loop local_3
// 		pop ecx
// 		call WaitKeyboardInputBufferEmpte
// 		mov al,cl
// 		and al,0xfe							//禁止键盘产生中断  
// 		out 0x60,al
// 		push ecx
// 		mov ecx, 0x14
// local_4:
// 		loop local_4
// 		pop ecx
// local_b:		
// 		call WaitKeyboardInputBufferEmpte
// 		mov al, 0xd2						//写键盘输出缓冲区 命令
// 		out 0x64,al
// 		push ecx
// 		mov ecx, 0x14
// local_5:
// 		loop local_5
// 		pop ecx
// 		call WaitKeyboardInputBufferEmpte
// 		mov al,ah
// 		out 0x60,al							//写入扫描码
// 		push ecx
// 		mov ecx, 0x14
// local_6:
// 		loop local_6
// 		pop ecx
// 		call WaitKeyboardOutPutBufferFull
// 		or dl,dl
// 		jz local_a
// 		call WaitKeyboardInputBufferEmpte
// 		mov al,0x60
// 		out 0x64,al
// 		push ecx
// 		mov ecx, 0x14
// local_7:
// 		loop local_7
// 		pop ecx
// 		call WaitKeyboardInputBufferEmpte
// 		mov al,cl
// 		or al,1
// 		out 0x60,al
// 		push ecx
// 		mov ecx, 0x14
// local_8:
// 		loop local_8
// 		pop ecx
// 		call WaitKeyboardInputBufferEmpte
// local_a:		
// 		popad		
// 	}
// }

// __declspec (naked) void StoreDSRegister()
// {
// 	__asm{
// 		push eax
// 		mov ax,stKeyGlobalVariable.wDSRegister;
// 		mov ds, ax
// 		pop eax
// 		ret
// 	}
// }

BYTE byteCurrentPort64Value;
bool KeyboardHandler()
{	
	if(stKeyGlobalVariable.chCurrentScanCode & 0x80)        //键盘放开时
	{
		if((stKeyGlobalVariable.chCurrentScanCode  & 0x7f)== stKeyGlobalVariable.chFuncKeyScanCode)
			stKeyGlobalVariable.dwFuncKeyState = FUNCKEYRELEASE;		
		return false;
	}

	if(stKeyGlobalVariable.chCurrentScanCode == stKeyGlobalVariable.chFuncKeyScanCode)
	{
		bRightCtrlKey = (stKeyGlobalVariable.chPrveScanCode == 0xe0) ? TRUE:FALSE;
		stKeyGlobalVariable.dwFuncKeyState = FUNCKEYPRESS;
		return false;
	}
	if(stKeyGlobalVariable.dwFuncKeyState != FUNCKEYPRESS)
	{//ctrl down
		return false;
	}
	if(stKeyGlobalVariable.chCurrentScanCode == stKeyGlobalVariable.chSecondKeyScanCode)
	{//f12 down active
		return true;
	}
	return false;
}

// __declspec (naked) void Interrupt_0xF8_Keyboard_Service()
// {
// 	__asm{
// 		pushfd
// 		cmp cs:gbActive,0
// 		jnz local_2
// 		push eax
// 		in al,0x64
// 		test al,1 
// 		pop eax 
// 		jnz local_2
// 		popfd
// 		ret
// local_2:
// 		popfd
// 		push cs:KeyboardInterruptService
// 		ret
// 	}
// }

__declspec (naked) void KeyboardInterruptService()
{
	__asm
	{
		cmp		ss:gbActive,0
		jnz		SyserActived
		push	ds
		push	eax			//vc 编译器在调用函数时不会保存 eax,ecx,edx
		push	ecx
		push	edx
		mov		ax,ss
		mov		ds,ax
		in		al,0x64
		mov		byteCurrentPort64Value,al 
		in		al,0x60
		mov		stKeyGlobalVariable.chCurrentScanCode,al
	}
	//
	if(gpSyserCfg->m_DebugKeyboardInterrupt)
	{
		gpSyser->DbgPrint(0,0,WSTR("Keyboard P60=%02x P64=%02x"),stKeyGlobalVariable.chCurrentScanCode,byteCurrentPort64Value);
		if(stKeyGlobalVariable.chCurrentScanCode==0xe0)
			gpSyser->DbgPrint(0,16,WSTR("0xe0 Keyboard P60=%02x P64=%02x"),stKeyGlobalVariable.chCurrentScanCode,byteCurrentPort64Value);
		//else
		//	gpSyser->DbgPrint(0,16,WSTR("                                             "),stKeyGlobalVariable.chCurrentScanCode,byteCurrentPort64Value);
	}
	if(KeyboardHandler()==false || gpSyser->m_bInitSuccess==false || gbLoadImage)
	{
		stKeyGlobalVariable.chPrveScanCode = stKeyGlobalVariable.chCurrentScanCode;
		InsertKeyboardBuffer(stKeyGlobalVariable.chCurrentScanCode);
		__asm
		{
			pop edx
			pop ecx
			pop eax
			pop ds
			ret
		}
	}
	//DisableDebugRegisterMontior();
	__asm
	{
		pop edx
		pop ecx
		pop eax
		pop ds
		pop ss:stKeyGlobalVariable.dwOldKeyboardInterrupt
		call SyserStopOtherCPUs
		call SyserDisableDebugRegisterMontior
		mov ss:OldESP,esp
		mov ss:Reg.GeneReg[ESP_IDX*4],esp
		mov esp,ss:gpStackBufferTop
		pushad
		push fs
		push ds
		push es	
		mov ax,NT_FS
		mov fs,ax
		mov ax,ss
		mov ds,ax
		mov es,ax
		mov ebp,esp
		cld
	}
	////////////////////////
	//pbSyserDisabled用于延迟Active Syser,显存切换时，Active会导致显示不正常
	if(pbSyserDisabled==NULL || *pbSyserDisabled==false)
	{
		SyserLoadReg();
		gpSyser->AttachPopupProcess(Reg.CR[3]);		
		gpSyser->m_bSaveReg=false;
		gpSyser->Active();		
		SyserSaveReg();
	}
	else if(pbSyserDisabled && *pbSyserDisabled)
	{
		*pbSyserDisabled=false;//清掉此标志，等待SysBoot显示驱动回掉的Active
		SyserEnableDebugRegisterMontior();
	}
	else
	{
		SyserEnableDebugRegisterMontior();
	}
	if(bRightCtrlKey)
		SyserSimulateWindowsKeyboardInput(0xe0);
	SyserSimulateWindowsKeyboardInput(stKeyGlobalVariable.chFuncKeyScanCode | 0x80);
	////////////////////////															
	__asm
	{
		pop     es
		pop     ds
		pop     fs
		popad
		mov esp,ss:OldESP
		call SyserSyncMouseInterrupt		
		xchg eax,[esp+8]
		test eax,0x100
		jnz local_00099
		call SyserEnableAllHardInterrupt
		call SyserStartOtherCPUs
		jmp local_101
local_00099:
		call SyserDisableAllHardInterrupt
local_101:
		xchg eax,[esp+8]
		cmp cs:gGenInterruptNumber,0xffffffff
		jnz local_00100
		cmp cs:bGoToSoftice,0
		jz tmpgosoftice
		mov ss:bGoToSoftice,0
		call pSofticeActivePointer
tmpgosoftice:
		iretd
local_00100:
		mov ss:gGenInterruptNumber,0xffffffff;
		jmp cs:[gGenInterruptOffset]
	}
	__asm
	{
SyserActived:
		lea esp,[esp+4]
		pushad
		push ds
		mov ax,ss
		mov ds,ax
		in al,0x64
		mov byteCurrentPort64Value,al 
		in al,0x60
		mov stKeyGlobalVariable.chCurrentScanCode,al
	}
	if(gpSyserCfg->m_DebugKeyboardInterrupt)
	{
		gpSyser->DbgPrint(400,40,WSTR("Keyboard P60=%02x P64=%02x"),stKeyGlobalVariable.chCurrentScanCode,byteCurrentPort64Value);
		if(stKeyGlobalVariable.chCurrentScanCode==0x60||stKeyGlobalVariable.chCurrentScanCode==0xe0)
			gpSyser->DbgPrint(400,60,WSTR("Keyboard P60=%02x P64=%02x"),stKeyGlobalVariable.chCurrentScanCode,byteCurrentPort64Value);
	}
	if(stKeyGlobalVariable.chCurrentScanCode & 0x80)//如果是键盘抬起
	{	
		if((stKeyGlobalVariable.chCurrentScanCode  & 0x7f)== stKeyGlobalVariable.chFuncKeyScanCode)
			stKeyGlobalVariable.dwFuncKeyState = FUNCKEYRELEASE;		
		if((stKeyGlobalVariable.chCurrentScanCode & 0x7f) < 0x60)
		{
			if(stKeyGlobalVariable.chPrveScanCode==0xe0)
			{
				gpSyser->OnKeyEvent(ExternTable[(stKeyGlobalVariable.chCurrentScanCode & 0x7F)],false);
			}
			else
			{
				if(stKeyGlobalVariable.chPrveScanCode==0xe1)
				{
					if(stKeyGlobalVariable.chCurrentScanCode==0x9d)
						stKeyGlobalVariable.chPrveScanCode=0xe1;
					else if(stKeyGlobalVariable.chCurrentScanCode==0xc5)
						gpSyser->OnKeyEvent(WISP_VK_PAUSE,false);
				}
				else
					gpSyser->OnKeyEvent(NormalTable[SyserOption.iKeyboardLayer][(stKeyGlobalVariable.chCurrentScanCode & 0x7F)],false);
			}
		}
	}
	else
	{	
		if(stKeyGlobalVariable.chCurrentScanCode < 0x60)
		{
			if(stKeyGlobalVariable.chCurrentScanCode == stKeyGlobalVariable.chFuncKeyScanCode)
			{				
				stKeyGlobalVariable.dwFuncKeyState = FUNCKEYPRESS;			
			}
			if(stKeyGlobalVariable.chPrveScanCode==0xe0)
			{
				gpSyser->OnKeyEvent(ExternTable[(stKeyGlobalVariable.chCurrentScanCode)],true);
			}
			else
			{
				if(stKeyGlobalVariable.chPrveScanCode==0xe1)
				{
					if(stKeyGlobalVariable.chCurrentScanCode==0x1d)
						stKeyGlobalVariable.chPrveScanCode=0xe1;
					else if(stKeyGlobalVariable.chCurrentScanCode==0x45)
						gpSyser->OnKeyEvent(WISP_VK_PAUSE,true);
				}
				else
					gpSyser->OnKeyEvent(NormalTable[SyserOption.iKeyboardLayer][(stKeyGlobalVariable.chCurrentScanCode)],true);
			}
		}
	}
	//if(!(SoftIceActive && *SoftIceActive))//如果 softice 没有处理按键则要自己发送键盘硬件中断结束标志
	SetInteruptEOI(1);
	stKeyGlobalVariable.chPrveScanCode=stKeyGlobalVariable.chCurrentScanCode;
	__asm
	{
		pop ds
		popad
		iretd
	}
}

// __declspec (naked) void SaveDSRegister()
// {
// 	__asm{
// 		push eax
// 		push ebx
// 		mov bx, ds		
// 		mov eax,0x10
// 		mov ds,ax
// 		mov stKeyGlobalVariable.wDSRegister,bx
// 		pop ebx
// 		pop eax
// 		ret
// 	}
// }

BYTE gMouseID=0;

void InitPS2MouseDevice()
{
	BYTE Value;
	bool ReadMouseRet;
	if(gInVMWARE||gInVirtualPC)
	{
		dwMousePrePackageSize=4;
		gHasPS2Mouse=true;
		gpSyserCfg->m_CheckPS2Mouse=1;
		gpSyserCfg->m_PS2MouseType=4;		
	}	
	
	if(gpSyserCfg->m_CheckPS2Mouse==0)
	{
		//if(gHasPS2Keyboard==false)
		//	gHasPS2Keyboard=CheckPS2Keyboard();
		dwMousePrePackageSize=3;
		gHasPS2Mouse=true;
		if(gHasPS2Mouse==false)
		{
			dwMousePrePackageSize=0;
			if(SendMouseCommand(0xf2))
			{
				while(ReadMouseRet = SyserReadPort60(&Value,false))
				{
					if(Value==0xfa)
						continue;
					if(Value==0xfe)
						break;
					if(Value>=3)
					{
						dwMousePrePackageSize=4;
						gHasPS2Mouse=true;
					}
					if(Value==0)
					{
						dwMousePrePackageSize=3;
						gHasPS2Mouse=true;
					}
					break;
				}
				if(ReadMouseRet==false)
				{
					DbgPrint("Syser: ReadPort60 (%x) error!\n",Value);
				}
				/*
				SendMouseCommand(0xe5);
				TestTouchPad();
				SendMouseCommand(0xe4);
				*/
			}
			else
			{
				DbgPrint("Syser: Send Mouse Command (0xF2) error!\n");
			}
		}
		gpSyserCfg->WriteDwordValue(CHECK_PS2_MOUSE,1);
		gpSyserCfg->WriteDwordValue(PS2MOUSE_TYPE,dwMousePrePackageSize);
		gpSyserCfg->WriteDwordValue(NULL_PS2_KEYBOARD,gHasPS2Keyboard?0:1);
	}
	else 
	{
		gHasPS2Mouse=true;
		switch(gpSyserCfg->m_PS2MouseType)
		{
		case 3:
			dwMousePrePackageSize=3;
			break;
		case 4:
			dwMousePrePackageSize=4;
			break;
		case 6:
			dwMousePrePackageSize=6;
			break;
		default:
			gHasPS2Mouse=false;
			break;
		}
		gHasPS2Keyboard=gpSyserCfg->m_PS2NULLKeyboard?false:true;
	}
	//if(gHasPS2Mouse)
	//	DbgPrint("Syser : %s PS2 Mouse %d Button\n",gHasPS2Mouse?"Find":"Can't Find",dwMousePrePackageSize);
	//DbgPrint("Syser : %s PS2 Keyboard\n",gHasPS2Keyboard?"Find":"Can't Find");
}

bool InstallAllInterrupt()
{
	DWORD dwInterruptNumber = 0;
	WORD CurCS;
	//bool ReadMouseRet;
	//SaveDSRegister();//导致三环的多媒体程序异常 fuck M$
	//在页目录和页表里面占一个项在 poke peek 命令中使用。
	gPrevTSC=SyserGetTSC();
	gTSCTickCount = InitSTCTickCount();
	InitPS2MouseDevice();//
	SyserClrCR0WP();
	SyserCloseInterrupt();
	
	gpSyser->ResetInputState();
// 	__asm
// 	{
// 		push eax
// 		mov al,0xc0
// 		out 0x20,al
// 		pop eax
// 	}

	SyserWritePortByte(0x20,0xc0);
	if(gpSyserCfg->m_DisableRWPortHook==0)
	{
		PatchSystemREAD_PORT_UCHAR(TRUE);
		PatchSystemWRITE_PORT_UCHAR(TRUE);
	}
	GetIOAPICBase();
	if(gbIsUseAPIC)
		::DbgPrint("Syser : IOAPIC %08x[%08x] LocalAPIC %08x[%08x]\n",gdwIOAPICPhysAddress,gdwIOAPICLineAddress,gdwLocalAPICPhysAddress,gdwLocalAPICLineAddress);
	TscPerSec=0;
	TscPerSec=CalibrateByTimer();
	bIsExecuteTimerInterrupt = false;
	TimeSecond=0xff;
	TimeHour=0;
	TimeMinute=0;
	//安装键盘中断
	gHardInt1Vector = GetHardwareInterruptVectorNum(1);
	if(gbIsUseAPIC==false||gHardInt1Vector!=0xff)
		InstallInterruptHandle((BYTE)gHardInt1Vector,(VADDR32)KeyboardInterruptService);
#if SUPPORT_COM_INTERRUPT
	gHardInt4Vector = GetHardwareInterruptVectorNum(4);
	if(gbIsUseAPIC==false||gHardInt4Vector!=0xff)
		InstallInterruptHandle((BYTE)gHardInt4Vector,(VADDR32)SerialCom1Com3Proc);
	gHardInt3Vector = GetHardwareInterruptVectorNum(3);
	if(gbIsUseAPIC==false||gHardInt3Vector!=0xff)
		InstallInterruptHandle((BYTE)gHardInt3Vector,(VADDR32)SerialCom2Com4Proc);
#endif
// 	__asm
// 	{
// 		push eax
// 		xor eax,eax
// 		mov ax,cs
// 		mov CurCS,ax
// 		pop eax
// 	}

	CurCS = SyserGetCurCSeg();

	InstallInterruptHandle(0x1,(VADDR32)SyserInt01Proc,SYS_SEG_GATE_DECR_TYPE_32INT_GATE,3);
	InstallInterruptHandle(0x3,(VADDR32)SyserInt03Proc,SYS_SEG_GATE_DECR_TYPE_32INT_GATE,3);
	if(gCPUNumbers>1)
		InstallInterruptHandle(0x2,(VADDR32)SyserNMIInterruptService,SYS_SEG_GATE_DECR_TYPE_32INT_GATE,3,CurCS);
	if(gpSyserCfg->m_DisableHookException==0)
	{
		InstallInterruptHandle(0x6,(VADDR32)SyserInt06Proc);
		InstallInterruptHandle(0xb,(VADDR32)SyserInt0bProc);
		InstallInterruptHandle(0xc,(VADDR32)SyserInt0cProc);
		InstallInterruptHandle(0xd,(VADDR32)SyserInt0dProc);
	}
	if(gInt0xeHook==false)
	{
		gInt0xeHook = InstallInterruptHandle(0xe,(VADDR32)SyserInt0eProc);		
		gSyserInt0eAddress = GetCurrentCPUInterruptProcAddress(0xe);
	}
	InstallInterruptHandle(0x2d,(VADDR32)SyserInt2dProc);
	
	if(bWRITE_PORT_UCHAR_PatchOK)
	{	/*
		GetCurrentWindowLEDState(KEYBOARD_SCROLL_LOCK);
		GetCurrentWindowLEDState(KEYBOARD_SCROLL_LOCK);
		GetCurrentWindowLEDState(KEYBOARD_NUM_LOCK);
		GetCurrentWindowLEDState(KEYBOARD_NUM_LOCK);
		GetCurrentWindowLEDState(KEYBOARD_CAPS_LOCK);
		GetCurrentWindowLEDState(KEYBOARD_CAPS_LOCK);
		*/
	}	
	if(gbIsUseAPIC==false)
	{
		//安装时间中断
		//gdwTimerInterruptNum = GetHardwareInterruptVectorNum(8);
		//InstallInterruptHandle((BYTE)gdwTimerInterruptNum,(VADDR32)TimeInterrupeService);
		//安装鼠标中断
		if(gHasPS2Mouse)
		{
			gPS2MouseInterruptNum = GetHardwareInterruptVectorNum(0xC);
			InstallInterruptHandle((BYTE)gPS2MouseInterruptNum,(VADDR32)MouseInterruptService);
// 			__asm 
// 			{
// 				push eax
// 				in al,0x64
// 				test al,1 
// 				jz local_009
// 				in al,0x60
// local_009:
// 				pop eax 
// 			}

			SyserWaitMouseStatus();
		}
	}
	else
	{
		//安装 APIC 的时间中断
		//InstallInterruptHandle(SYSER_APIC_TIME_INTERRUPT_VECTOR,(VADDR32)Interrupt_0xFA_Timer_Service);
		//安装 APIC 的键盘中断
		InstallInterruptHandle(SYSER_APIC_KEYBOARD_INTERRUPT_VECTOR,(VADDR32)SyserInterrupt_0xF8_Keyboard_Service);
		//安装 APIC 的鼠标中断
		if(gHasPS2Mouse)
			InstallInterruptHandle(SYSER_APIC_MOUSE_INTERRUPT_VECTOR,(VADDR32)SyserInterrupt_0xF9_Mouse_Service);
#if SUPPORT_COM_INTERRUPT
		InstallInterruptHandle(SYSER_APIC_COM1_INTERRUPT_VECTOR,(VADDR32)Interrupt_0xFB_Com1_Com3_Service);
		InstallInterruptHandle(SYSER_APIC_COM2_INTERRUPT_VECTOR,(VADDR32)Interrupt_0xFC_Com2_Com4_Service);
#endif
	}
    InitBranchMointer();
	SyserOpenInterrupt();
	gbInterruptInstalled = true;
	SyserRestoreCR0();
	return true;
}

bool UninstallAllInterrupt()
{
	SyserClrCR0WP();
	SyserCloseInterrupt();
	UninstallInterruptHandle((BYTE)gHardInt1Vector);
#if SUPPORT_COM_INTERRUPT
	UninstallInterruptHandle((BYTE)gHardInt3Vector);
	UninstallInterruptHandle((BYTE)gHardInt4Vector);
#endif
	if(gHasPS2Mouse)
	{
		if(gbIsUseAPIC)
			UninstallInterruptHandle(SYSER_APIC_MOUSE_INTERRUPT_VECTOR);
		else
		{
			UninstallInterruptHandle((BYTE)gPS2MouseInterruptNum);
// 			__asm
// 			{
// 				push eax
// 				in al,0x64
// 				test al,1 
// 				jz local_009
// 				in al,0x60
// local_009:
// 				pop eax
// 			}

			SyserWaitMouseStatus();
		}
	}
	if(gbIsUseAPIC==false)
	{
		//UninstallInterruptHandle((BYTE)gdwTimerInterruptNum);
	}
	else
	{
		//UninstallInterruptHandle(SYSER_APIC_TIME_INTERRUPT_VECTOR);
		UninstallInterruptHandle(SYSER_APIC_KEYBOARD_INTERRUPT_VECTOR);
#if SUPPORT_COM_INTERRUPT
		UninstallInterruptHandle(SYSER_APIC_COM1_INTERRUPT_VECTOR);
		UninstallInterruptHandle(SYSER_APIC_COM2_INTERRUPT_VECTOR);
#endif
	}
	UninstallInterruptHandle(1);
	UninstallInterruptHandle(3);
	if(gCPUNumbers>1)
		UninstallInterruptHandle(0x2);
	if(gpSyserCfg->m_DisableHookException==0)
	{
		UninstallInterruptHandle(0x6);
		UninstallInterruptHandle(0xb);
		UninstallInterruptHandle(0xc);
		UninstallInterruptHandle(0xd);
	}	
	if(gInt0xeHook==true)
	{
		if(UninstallInterruptHandle(0xe))
		{
			gInt0xeHook=false;
			gSyserInt0eAddress=0;
		}
	}
	UninstallInterruptHandle(0x2d);
	if(gpSyserCfg->m_DisableRWPortHook==0)
	{
		PatchSystemWRITE_PORT_UCHAR(FALSE);
		PatchSystemREAD_PORT_UCHAR(FALSE);
	}
	
	SyserOpenInterrupt();
	gbInterruptInstalled = false;
	SyserRestoreCR0();
	return TRUE;
}


// void WaitMouseInputBufferEmpte()
// {
// 	__asm
// 	{		
// 		push eax
// 		push ecx
// 		mov ecx,2
// local_2:
// 		push ecx
// 		xor ecx,ecx
// local_1:
// 		in al, 0x64
// 		test al,2		
// 		loopne local_1		
// 		pop ecx
// 		jz local_3
// 		loop local_2
// local_3:
// 		pop ecx
// 		pop eax		
// 	}
// }

// void WaitMouseOutPutBufferFull()
// {
// 	__asm{
// 		push ecx
// 		push eax
// 		mov ecx,0x2000
// local_1:		
// 		in al,0x64
// 		and al,0x21
// 		cmp al,0x21
// 		loopne local_1		
// 		pop eax
// 		pop ecx
// 	}
// }
// void CleanMouseOutPutBuffer()
// {
// 	__asm{
// 		push eax
// 		push ecx
// 		mov ecx,0x1000
// 		in al, 0x64
// 		test al, 0x21
// 		jz local_1
// 		in al,0x60
// local_2:
// 		loop local_2
// local_1:
// 		pop ecx
// 		pop eax
// 	}
// }

void WriteMouseCommandPrefix(BYTE chCmd)
{
	ULONG_PTR	Flags;
	SyserSaveFlags(&Flags);
	SyserCloseInterrupt();
	SyserWaitMouseInputBufferEmpte();
	SendCommandTo64Port(chCmd);
	SyserRestoreFlags(Flags);
}
// bool MouseCommand(BYTE chCmd)
// {
// 	__asm
// 	{
// 		pushad
// 		pushfd
// 		cli
// 	}
// 	stKeyGlobalVariable.bMouseResponseState = FALSE;
// 	WriteMouseCommandPrefix(0xd4);
// 	WriteMouseCommandByte(chCmd);
// 	if(ReadMouseByte() == 0xfa)
// 		stKeyGlobalVariable.bMouseResponseState = TRUE;
// 	__asm
// 	{
// 		popfd
// 		popad
// 	}
// 	return stKeyGlobalVariable.bMouseResponseState;
// }
// bool IsMouseOutPutBufferFull()
// {
// 	bool bRet = 0;
// 	__asm{
// 		in al,0x64
// 		test al,0x21
// 		cmp al,0x21
// 		jnz local_1
// 		mov bRet,1		
// local_1:
// 	}	
// 	return bRet;
// }

// void WriteMouseCommandByte(BYTE chCmd)
// {
// 	if(IsMouseOutPutBufferFull())
// 		SyserCleanMouseOutPutBuffer();
// 	__asm{
// 		mov al,chCmd
// 		out 0x60,al
// 	}
// }
// void SaveEflag()
// {
// 	__asm{
// 		pushfd
// 		pop eax
// 		mov dwEflag,eax
// 	}
// }
// void StoreEflag()
// {
// 	__asm{
// 		push dwEflag
// 		popfd
// 	}
// }
// BYTE ReadMouseByte()
// {
// 	BYTE byteRet;
// 	SyserWaitMouseOutPutBufferFull();
// 	__asm{
// 		push eax
// 		in al,0x60
// 		mov byteRet ,al
// 		pop eax
// 	}
// 	return byteRet;
// }

//0x0e,0x24,0x08,0x1f,0x1b,0x08,0x24,0x10,0x08,0x28,0x07,0x28,0x2b,0xfc,0x28,0x28,0xf2,0x28,0x26,0xe9,0x28,0x1e,0xe2,0x28
DWORD CalcPackageBeginOffset()
{
	int i, k , j;

	for (i = 0; i < 4; i++)
	{
		if(MouseBeginBuffer[i] & 8)
		{
			
			k = 0;
			for(j = i + 3; j < MOUSE_BEGINDATA_MAX; j+=3)
			{
				if(MouseBeginBuffer[j] & 0x8)
					k++;
				else
					break;
			}
			
			if(k == 7)
			{
				dwMousePrePackageSize = 3;
				break;						
			}
			
			k = 0;
			for(j = i + 4; j < MOUSE_BEGINDATA_MAX; j+=4)
			{
				if(MouseBeginBuffer[j] & 0x8)
					k++;					
				else
					break;
			}
			if(k == 5)
			{
				dwMousePrePackageSize = 4;			
				break;
			}
			else
				dwMousePrePackageSize = 0xff;
		}
	}
	if(i)
	{
		dwMousePackageBeginOffset = dwMousePrePackageSize - i;
	}
	else
		dwMousePackageBeginOffset = i;

	return dwMousePackageBeginOffset;
}

DWORD dwWrite60Counter1 = 0;
UCHAR   NEW_READ_PORT_UCHAR( IN DWORD Port )
{
	UCHAR uRet;
// 	__asm
// 	{
// 		mov edx,Port
// 		in al,dx 
// 		mov uRet,al
// 	}

	uRet = SyserReadPortByte(Port);

	if(Port == 0x60) 
	{
		if(!bIsMouseData)//如果是读键盘的数据
		{
			if(dwCurrentWindowsKeyLen != 0)
			{
				uRet = chWindowsKeyArray[dwCurrentReadIndex];
				dwCurrentReadIndex++;
				dwCurrentReadIndex &= 0xf;
// 				__asm{
// 					lock dec dwCurrentWindowsKeyLen
// 				}

				InterlockedDecrement((PLONG)&dwCurrentWindowsKeyLen);
			}
		}
		else   //读鼠标数据
		{
			bIsMouseData = FALSE;//代表鼠标数据已经被读走	
			//OUTPUT(WSTR("%<b>%02x "),uRet);
			//dwWrite60Counter1++;
			//if((dwWrite60Counter1%30)==0)
			//	OUTPUT(WSTR("\n"));
		}
	}
	else
	{
		if( Port == 0x64)
		{
			if(!bIsMouseData)//是否为读键盘状态
			{
				
				if(dwCurrentWindowsKeyLen == 0 || (uRet & 0x31)==0x31)
					return (UCHAR)uRet;
				uRet &= 0x1e;
				uRet |= 1;
				return (UCHAR)uRet;
			}			
		}		
	}
	/*
	if(Port >= (PUCHAR)0x3f8 && Port <= (PUCHAR)0x3ff)
	{
		OUTPUT(WSTR("Read %04x %02x"),Port,uRet);
	}*/
	return (UCHAR)uRet;	
}


void InsertKeyboardBuffer(BYTE chScanCode)
{
	if(dwCurrentWindowsKeyLen < MAX_WINDOWSKEYBUFFER_LENGTH)
	{		
		chWindowsKeyArray[dwCurrentWriteIndex] = chScanCode;
		dwCurrentWriteIndex++;
		dwCurrentWriteIndex &= 0xf;

		//__asm lock inc dwCurrentWindowsKeyLen
		InterlockedIncrement((PLONG)&dwCurrentWindowsKeyLen);
	}
}






/*
typedef struct stSofticeIdFind
{
	DWORD dwIntNum1;
	DWORD dwIntNum1JmpOffset;					//softice 被加载时用	push OldWindowsHandleAddress
											//						jmp SofticeHandleAddress
											// 例如	jmp 的指令编码是 E98631f7ff 这里的 DWORD 就是 fff73186
	DWORD dwIntNum2;
	DWORD dwIntNum2JmpOffset;					//同上
	DWORD dwIntNum3;
	DWORD dwIntNum3JmpOffset;					//同上	
	DWORD dwIntNum1BaseOffset;					//该 dword 是 softice 的中断 1 的处理函数的地址相对于 softice 基地址的偏移
	DWORD dwActiveFunctionBaseOffset;		//softice 内部的激活函数相对于 softice 基地址的偏移
	DWORD dwActiveFlagsBaseOffset;			//softice 内部的激活的 byte 变量相对于 softice 基地址的偏移
}SOFTICEFINDDATA;
*/
SOFTICEFINDDATA stSofticeCode[]=
{
	{0xc,0xfff238ce,0xd,0xfff23923,0xe,0xfff23d12,0xdefb5,0x0421a,0xdd621},//3.2	
	{0xb,0xfff2f9b4,0xc,0xfff2fb13,0xd,0xfff2fb68,0xd2ef5,0x0440e,0xd161a},//3.1
	{1,0xfff3b5ef,2,0xfff3c1a9,3,0xfff3b981,0xc7f69,0x04fd3,0xc661a},//3.0
	{1,0xfff73186,2,0xfff73d1a,3,0xfff73518,0xaf729,0x2360f,0xadcc2},//2.7	
	{1,0xfff77159,2,0xfff77c81,3,0xfff774eb,0xa9b5d,0x2260b,0xa7182},//2.6
	{1,0xfff787e9,2,0xfff79311,3,0xfff78b7b,0xa84bd,0x225fb,0xa5e62},//2.5
	{1,0xfff819b7,2,0xfff824b6,3,0xfff81d20,0x9d58b,0x20804,0x9bf42},//2.0
	{1,0xfff8c54a,2,0xfff8cfd4,3,0xfff8c898,0x8d04b,0x1ae5e,0x8ba1d},//4.05 中断的偏移，ActiveSoftice,bActiveSoftice
};
/*
DWORD stSofticeCode[][6]={
	{0xfff8c54a,0xfff8cfd4,0xfff8c898,0x8d04b,0x1ae5e,0x8ba1d},//4.05 中断的偏移，ActiveSoftice,bActiveSoftice
	{0xfff819b7,0xfff824b6,0xfff81d20,0x9d58b,0x20804,0x9bf42},//2.0
	{0xfff787e9,0xfff79311,0xfff78b7b,0xa84bd,0x225fb,0xa5e62},//2.5
	{0xfff77159,0xfff77c81,0xfff774eb,0xa9b5d,0x2260b,0xa7182},//2.6
	{0xfff73186,0xfff73d1a,0xfff73518,0xaf729,0x242a9,0xadcc2},//2.7	
	{0xfff3b5ef,0xfff3c1a9,0xfff3b981,0xc7f69,0x04fd3,0xc661a},//3.0
};
*/

DWORD CheckSofticeExist()//得到 Softice 的加载的基地址
{
	DWORD dwIdtRegister;
	DWORD dwInterruptAddress;
	DWORD *dwTmpAddress;
	ST_DESC* stIDTBaseAddr;
	DWORD i,dwNumber;	

	dwSofticeDriverBase = 0;				
	pSofticeActivePointer = NULL;
	dwIdtRegister = SyserGetIDTBase();
	stIDTBaseAddr = (ST_DESC*)dwIdtRegister;		
	dwNumber = sizeof(stSofticeCode) / sizeof(stSofticeCode[0]);
	i = 0;
	__try
	{
		for (i = 0; i < dwNumber; i++)
		{					
			/*
			dwInterruptAddress = stIDTBaseAddr[stSofticeCode[i].dwIntNum2].wBaseAddrHigh;
			dwInterruptAddress <<=16;
			dwInterruptAddress |= stIDTBaseAddr[stSofticeCode[i].dwIntNum2].wBaseAddrLow;
			if(*(char *)dwInterruptAddress != 0x68)
			continue;
			if(*(unsigned char *)(dwInterruptAddress+5) != 0xe9)//如果 softice 没有安装则推出
			continue;
			dwTmpAddress = (DWORD *)(6+dwInterruptAddress);
			if(stSofticeCode[i].dwIntNum2JmpOffset!=*dwTmpAddress)
			continue;
			*/
			dwInterruptAddress = stIDTBaseAddr[stSofticeCode[i].dwIntNum3].wBaseAddrHigh;
			dwInterruptAddress <<=16;
			dwInterruptAddress |= stIDTBaseAddr[stSofticeCode[i].dwIntNum3].wBaseAddrLow;
			if(*(char *)dwInterruptAddress != 0x68)
				continue;
			if(*(unsigned char *)(dwInterruptAddress+5) != 0xe9)//如果 softice 没有安装则推出
				continue;
			dwTmpAddress = (DWORD *)(6+dwInterruptAddress);
			if(stSofticeCode[i].dwIntNum3JmpOffset!=*dwTmpAddress)
				continue;		
			dwInterruptAddress = stIDTBaseAddr[stSofticeCode[i].dwIntNum1].wBaseAddrHigh;
			dwInterruptAddress <<=16;
			dwInterruptAddress |= stIDTBaseAddr[stSofticeCode[i].dwIntNum1].wBaseAddrLow;
			if(*(char *)dwInterruptAddress != 0x68)
				continue;		
			if(*(unsigned char *)(dwInterruptAddress+5) != 0xe9)//如果 softice 没有安装则推出
				continue;		
			dwTmpAddress = (DWORD *)(6+ dwInterruptAddress);
			if(stSofticeCode[i].dwIntNum1JmpOffset!=*dwTmpAddress)
				continue;		
			dwSofticeDriverBase = dwInterruptAddress - stSofticeCode[i].dwIntNum1BaseOffset;
			pSofticeActivePointer = (void (*)(void))(dwSofticeDriverBase + stSofticeCode[i].dwActiveFunctionBaseOffset);
			SoftIceActive = (BYTE *)(stSofticeCode[i].dwActiveFlagsBaseOffset + dwSofticeDriverBase);		
			break;		
		}
	}
	__except(1)
	{

	}	
	return 1;
}
void SetKeyboardLEDState(DWORD bNumLock,DWORD bScrollLock,DWORD bCapsLock)
{
	ULONG_PTR	Flags;
	BYTE bLEDState = 0;
	BYTE bRet = 0;
	if(bNumLock)
		bLEDState |= 2;
	if(bScrollLock)
		bLEDState |= 1;
	if(bCapsLock)
		bLEDState |= 4;
	SyserSaveFlags(&Flags);
	SyserCloseInterrupt();
	SetKeyboardPortState(FALSE);
	SendCommandTo60Port(0xed);
	SyserWaitKeyboardOutPutBufferFull();	
	SyserGetPortState();
	SendCommandTo60Port(bLEDState);
	SyserGetPortState();
	SetKeyboardPortState(TRUE);
	SyserRestoreFlags(Flags);
}
void SetKeyboardPortState(bool bState)
{
	BYTE byteCmd;
	byteCmd = bState ? 0xae : 0xad;
	SendCommandTo64Port(byteCmd);
}

// void SendCommandTo64Port(BYTE byteCmd)//向端口 64 发送命令
// {	
// 	WaitKeyboardInputBufferEmpte();
// 	__asm{
// 		push eax
// 		mov al,byteCmd
// 		out 0x64,al 
// 		push ecx
// 		mov ecx,0x1000
// delay:
// 		jmp local_next
// local_next:		
// 		loop delay
// 		pop ecx
// 		pop eax
// 	}	
// }
// 
// 
// void SendCommandTo60Port(BYTE byteCmd)//向端口 60 发送命令
// {	
// 	WaitKeyboardInputBufferEmpte();
// 	__asm{
// 		push eax
// 		mov al,byteCmd
// 		out 0x60,al 
// 		push ecx
// delay:
// 		jmp local_next
// local_next:		
// 		loop delay
// 		pop ecx
// 		pop eax
// 	}		
// }

// void GetPortState()//在给键盘发送了命令以后该函数用来读取键盘的返回值
// {
// 	__asm{
// 		push eax
// 		push ecx
// 		mov ecx,1000		
// local_3:		
// 		in al,0x64
// 		push ecx
// 		mov ecx,8
// local_2:	
// 		jmp local_1
// local_1:
// 		loop local_2
// 		pop ecx
// 		test al,1
// 		loope local_3
// 		jz local_4
// 		in al,0x60
// 		cmp al,0xfa
// 		jnz local_3
// local_4:
// 		pop ecx
// 		pop eax
// 	}
// }
bool GetCurrentWindowLEDState(DWORD dwKeyIndex)
{	
	switch(dwKeyIndex) {
	case KEYBOARD_CAPS_LOCK:		
		SyserSimulateWindowsKeyboardInput(0x3a);//Caps Lock 3a
		dwKeyLedFlags = KEYBOARD_CAPS_LOCK | 0x80000000;
		SyserSimulateWindowsKeyboardInput(0x3a | 0x80);//Caps Lock 3a		
		return bKeyCapsLockStat;				
	case KEYBOARD_NUM_LOCK:		
		SyserSimulateWindowsKeyboardInput(0x45);//Caps Lock 45
		dwKeyLedFlags = KEYBOARD_NUM_LOCK | 0x80000000;
		SyserSimulateWindowsKeyboardInput(0x45 | 0x80);//Caps Lock 45		
		return bKeyNumLockStat;				
	case KEYBOARD_SCROLL_LOCK:		
		SyserSimulateWindowsKeyboardInput(0x46);//Caps Lock 46
		dwKeyLedFlags = KEYBOARD_SCROLL_LOCK | 0x80000000;
		SyserSimulateWindowsKeyboardInput(0x46 | 0x80);//Caps Lock 46		
		return bKeyScrollLockStat;		
	default:
		return FALSE;
	}	
}
// void SimulateWindowsKeyboardInput(BYTE byteScanCode)
// {
// 	ULONG_PTR	Flags;
// 	InsertKeyboardBuffer(byteScanCode);
// 	SyserSaveFlags(&Flags);
// 	__asm{
// 		cli
// 		pushfd		
// 		push cs
// 		push offset local_7
// 		jmp dword ptr cs:stKeyGlobalVariable.dwOldKeyboardInterrupt
// local_7:
// 	}
// 	SyserRestoreFlags(Flags);
// }
DWORD dwPortCounter = 0;
DWORD dwEDPortCounter = 0;
DWORD dwWrite60Counter = 0;
void NEW_WRITE_PORT_UCHAR(IN PUCHAR  Port, IN UCHAR  Value)
{
	DWORD dwPort;
	
	dwPort = (DWORD)Port;
	if(Port == (PUCHAR)0x60)
	{		
		if(Value == (UCHAR)0xed)//对端口 0x60 写入值 0xed 是操作键盘LED 灯的命令字。随后对 0x60的写操作是操作具体的 LED
		{
			dwEDPortCounter++;
			bKeyLedCmd = TRUE;
		}
		else
		{			
			if(bKeyLedCmd)
			{						
				dwPortCounter++;
				bKeyLedCmd = FALSE;
				switch(dwPortCounter)
				{
				case 1:
				case 2:
					{
						if(bKeyScrollLockStatInitOK == FALSE)
						{						
							bKeyScrollLockStat = (Value & 1)?FALSE:TRUE;
							bKeyScrollLockStatInitOK = TRUE;
						}
						break;
					}													
				case 3:
				case 4:
					{
						if(bKeyNumLockStatInitOK == FALSE)
						{						
							bKeyNumLockStat = (Value & 2)?FALSE:TRUE;
							bKeyNumLockStatInitOK = TRUE;
						}
						break;
					}				
				case 5:
				case 6:
					{
						if(bKeyCapsLockStatInitOK == FALSE)
						{						
							bKeyCapsLockStat = (Value & 4)?FALSE:TRUE;
							bKeyCapsLockStatInitOK = TRUE;
						}
						break;
					}				
				default:
					;
				}
			}		
			
		}				
// 		__asm{
// 			mov edx,dwPort
// 			mov al,Value
// 			out dx,al
// 		}

		SyserWritePortByte(dwPort,Value);
	}	
	else
	{
// 		__asm{
// 				mov edx,dwPort
// 				mov al,Value
// 				out dx,al
// 			}

		SyserWritePortByte(dwPort,Value);
	}
}

void PatchSystemWRITE_PORT_UCHAR(bool bIsPatch)
{
	BYTE* dwSystemWRITE_PORT_UCHAR;

	DWORD dwPatchNEW_WRITE_PORT_UCHAR,i;
	
	dwSystemWRITE_PORT_UCHAR = (BYTE*)WRITE_PORT_UCHAR;

	if(bIsPatch && bWRITE_PORT_UCHAR_PatchOK == FALSE)
	{
		dwPatchNEW_WRITE_PORT_UCHAR = (DWORD)NEW_WRITE_PORT_UCHAR;
		for(i = 0; i < 5; i++)
		{
			byteOrgWRITE_PORT_UCHARInstruction[i] = dwSystemWRITE_PORT_UCHAR[i];
		}
		dwSystemWRITE_PORT_UCHAR[0] = 0xe9;
		*(DWORD*)(&dwSystemWRITE_PORT_UCHAR[1]) = dwPatchNEW_WRITE_PORT_UCHAR -(5 + (DWORD)WRITE_PORT_UCHAR);
		bWRITE_PORT_UCHAR_PatchOK = TRUE;
	}
	else
	{
		if(bWRITE_PORT_UCHAR_PatchOK)
		{
			for(i = 0; i < 5; i++)
			{
				dwSystemWRITE_PORT_UCHAR[i] = byteOrgWRITE_PORT_UCHARInstruction[i];
			}
			bWRITE_PORT_UCHAR_PatchOK = FALSE;
		}
	}
}
void PatchSystemREAD_PORT_UCHAR(bool bIsPatch)
{
	BYTE* dwSystemREAD_PORT_UCHAR;

	DWORD dwPatchNEW_READ_PORT_UCHAR,i;
	ULONG_PTR	Flags;
	SyserSaveFlags(&Flags);
	SyserCloseInterrupt();
	dwSystemREAD_PORT_UCHAR = (BYTE*)READ_PORT_UCHAR;

	if(bIsPatch && bREAD_PORT_UCHAR_PatchOK == FALSE)
	{
		dwPatchNEW_READ_PORT_UCHAR = (DWORD)NEW_READ_PORT_UCHAR;
		for(i = 0; i < 5; i++)
		{
			byteOrgREAD_PORT_UCHARInstruction[i] = dwSystemREAD_PORT_UCHAR[i];
		}
		dwSystemREAD_PORT_UCHAR[0] = 0xe9;
		*(DWORD*)(&dwSystemREAD_PORT_UCHAR[1]) = dwPatchNEW_READ_PORT_UCHAR -(5 + (DWORD)READ_PORT_UCHAR);
		bREAD_PORT_UCHAR_PatchOK = TRUE;
	}
	else
	{
		if(bREAD_PORT_UCHAR_PatchOK)
		{
			for(i = 0; i < 5; i++)
			{
				dwSystemREAD_PORT_UCHAR[i] = byteOrgREAD_PORT_UCHARInstruction[i];
			}
			bREAD_PORT_UCHAR_PatchOK = FALSE;
		}
	}
	SyserRestoreFlags(Flags);
}

// __declspec (naked) void SyncMouseInterrupt()
// {
// 	__asm
// 	{		
// 		push eax
// 		push ecx
// 		push ds
// 		mov ax,0x10
// 		mov ds,ax
// 		mov ecx,0x88000			//有足够的时间来等待鼠标中断的发生，在最坏的情况下要等待 3 个鼠标中断
// 		mov eax,dwMousePackageBeginOffset
// 		cmp eax,stKeyGlobalVariable.dwMouseDataIndex
// 		
// 		jz local_ex
// 		mov dwWaitMouseInterrupt,1
// 		sti
// local_1:
// 		cmp eax, stKeyGlobalVariable.dwMouseDataIndex
// 		loopne local_1
// 		cli
// local_ex:
// 		mov gbActive,FALSE
// 		pop ds
// 		pop ecx
// 		pop eax
// 		ret
// 	}
// }


// bool CheckPS2Keyboard()
// {
// 	bool  ReadMouseRet;
// 	BYTE Value;
// 	int i=0;
// 	BYTE PS2KeyboardID[2];
// 	__asm
// 	{
// 		pushad
// 		pushfd
// 		cli
// 	}
// 	if(SendCommandTo60Port(0xF2)==false)
// 		goto local_quit;
// 	if(ReadPort60(&Value,false)==false)
// 		goto local_quit;
// 	if(Value!=0xfa)
// 		goto local_quit;
// 	i = 0;
// 	while(ReadMouseRet = ReadPort60(&Value,false))
// 	{
// 		if(i<2)
// 			PS2KeyboardID[i]=Value;
// 		i++;
// 	}
// local_quit:
// 	__asm
// 	{
// 		popfd 
// 		popad 
// 	}
// 	return i>=2;
// }

bool SendCommandTo60Port(BYTE byteCmd)//向端口 60 发送命令
{	
	bool bRet=false;
	if(SyserWaitI8042InputBufferEmpty())
	{
// 		__asm{
// 			push eax
// 			mov al,byteCmd
// 			out 0x60,al 
// 			pop eax
// 		}

		SyserWritePortByte(0x60,byteCmd);
		bRet = SyserWaitI8042InputBufferEmpty();
	}
	return bRet;
}

bool SendMouseCommand(BYTE CommandByte)
{
	bool bRet=false;
	BYTE Value;
	int i;
	X86SaveRegs	Regs;
	WORD	Flags;
	SyserSaveFlagsLow16(&Flags);
	SyserPushad(&Regs);
	SyserCli();
// 	__asm
// 	{
// 		pushf
// 		pushad
// 		cli
// 	}
	for(i = 0; i < 20;i++)
	{
		if(SendCommandTo64Port(0xd4))
		{
			if(SyserClearI8042OutputBuffer())
			{
				bRet = SendCommandTo60Port(CommandByte);
				break;
			}
		}
	}

	if(bRet)
	{
		if(SyserReadPort60(&Value,true))
		{
			if(Value==0xfa)
				bRet=true;
		}
	}

// 	__asm{
// 		popad
// 		popf
// 	}

	SyserPopad(&Regs);
	SyserRestoreFlagsLow16(Flags);
	return bRet;
}

// bool ReadPort60(BYTE* ReturnValue,bool IsMouse)
// {
// 	bool bRet=false;
// 	BYTE Value;
// 	__asm
// 	{
// 		push eax
// 		push ecx
// 		push ebx
// 		mov bl,1 
// 		cmp IsMouse,0
// 		jz local_005
// 		or bl,0x20
// local_005:
// 		mov ecx,0x800000
// local_001:		
// 		in al,0x64
// 		and al,bl
// 		cmp al,bl
// 		jz local_002
// 		loop local_001
// 		jmp local_quit
// local_002:
// 		mov bRet,1
// 		in al,0x60 
// 		mov Value,al
// local_quit:		
// 		pop ebx
// 		pop ecx
// 		pop eax
// 	}
// 	*ReturnValue=Value;
// 	return bRet;
// }

// bool WaitI8042InputBufferEmpty()
// {
// 	bool bRet=false;
// 	__asm
// 	{
// 		push ecx
// 		push eax
// 		mov ecx,0x800000
// local_000:		
// 		in al,0x64
// 		test al,2
// 		jz local_001
// 		loop local_000
// 		jmp local_quit
// local_001:
// 		push ecx 
// 		mov ecx,100
// local_005:
// 		jmp local_004
// local_004:
// 		loop local_005
// 		pop ecx
// local_003:
// 		in al,0x64
// 		test al,2 
// 		jz local_002
// 		loop local_003
// 		jmp local_quit
// local_002:
// 		mov bRet,1
// local_quit:
// 		pop eax
// 		pop ecx
// 	}
// 	return bRet;
// }

bool SendCommandTo64Port(BYTE byteCmd)//向端口 64 发送命令
{	
	bool bRet=false;
	if(SyserWaitI8042InputBufferEmpty())
	{
// 		__asm{
// 			push eax
// 			mov al,byteCmd
// 			out 0x64,al 
// 			pop eax
// 		}

		SyserWritePortByte(0x64,byteCmd);
		bRet = SyserWaitI8042InputBufferEmpty();
	}
	return bRet;
}

// bool ClearI8042OutputBuffer()
// {
// 	bool bRet=false;
// 	__asm
// 	{
// 		push ecx
// 		push eax
// 		xor ecx,ecx
// local_000:		
// 		in al,0x64
// 		test al,0x1
// 		jz local_007
// 		in al,0x60
// 		mov eax,0x20
// local_001:
// 		jmp local_002
// local_002:
// 		dec eax
// 		jnz local_001
// 		loop local_000
// 		jmp local_quit
// local_007:
// 		mov bRet,1
// local_quit:
// 		pop eax
// 		pop ecx
// 	}
// 	return bRet;
// }


