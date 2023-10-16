#include "StdAfx.h"
#include "Syser.h"
#include "Keyboard.h"
bool gUsbRightControl=false;
bool gbUsbKeyboardActive=false;
DWORD USBCOUNTPP=0;

void TranslateUSBKey(BYTE*pPrevData,BYTE*pNewData)
{
	bool bPrevMod,bMod;
	UINT VKey;
	//OUTPUT(WSTR("%02X %02X %02X %02X %02X %02X %02X %02X\n"),pNewData[0],pNewData[1],pNewData[2],pNewData[3],pNewData[4],pNewData[5],pNewData[6],pNewData[7]);
	if(pNewData[2] == 1 && pNewData[3] == 1 && pNewData[4] == 1 && pNewData[5] == 1 && pNewData[6] == 1 && pNewData[7] == 1)
		return;
	if(*(WORD*)pNewData || *(WORD*)pPrevData)
	{
		for(int n=0;USBModKeyTransTable[n].KeyType;n++)
		{
			bMod = (*(WORD*)pNewData & USBModKeyTransTable[n].Mask)!=0;
			bPrevMod = (*(WORD*)pPrevData & USBModKeyTransTable[n].Mask)!=0;
			if(bPrevMod^bMod)
				gpSyser->OnKeyEvent(USBModKeyTransTable[n].KeyType,bMod);
		}
	}
	for(int n=2;pNewData[n]&&n<8;n++)
	{
		VKey = USBKeyTransTable[pNewData[n]];
		if(VKey!=WISP_VK_NULL && TStrNChr(&pPrevData[2],pNewData[n],6)==NULL)
		{
			gpSyser->OnKeyEvent(VKey,true);
		}
	}
	for(int n=2;pPrevData[n]&&n<8;n++)
	{
		VKey = USBKeyTransTable[pPrevData[n]];
		if(VKey!=WISP_VK_NULL && TStrNChr(&pNewData[2],pPrevData[n],6)==NULL)
		{
			gpSyser->OnKeyEvent(VKey,false);
		}
	}
	memcpy(pPrevData,pNewData,8);
}

USB_MOD_TRANS USBModKeyTransTable[]=
{
	{WISP_VK_LCONTROL,		0x0001},
	{WISP_VK_LSHIFT,		0x0002},
	{WISP_VK_LALT,			0x0004},
	{WISP_VK_LWIN,			0x0008},
	{WISP_VK_RCONTROL,		0x0010},
	{WISP_VK_RSHIFT,		0x0020},
	{WISP_VK_RALT,			0x0040},
	{WISP_VK_RWIN,			0x0080},
	{WISP_VK_NULL,			0}
};

UINT USBKeyTransTable[256]=
{
	WISP_VK_NULL,				//0x00
	WISP_VK_NULL,				//0x01
	WISP_VK_NULL,				//0x02
	WISP_VK_NULL,				//0x03
	WISP_VK_A,					//0x04
	WISP_VK_B,					//0x05
	WISP_VK_C,					//0x06
	WISP_VK_D,					//0x07
	WISP_VK_E,					//0x08
	WISP_VK_F,					//0x09
	WISP_VK_G,					//0x0A
	WISP_VK_H,					//0x0B
	WISP_VK_I,					//0x0C
	WISP_VK_J,					//0x0D
	WISP_VK_K,					//0x0E
	WISP_VK_L,					//0x0F
	WISP_VK_M,					//0x10
	WISP_VK_N,					//0x11
	WISP_VK_O,					//0x12
	WISP_VK_P,					//0x13
	WISP_VK_Q,					//0x14
	WISP_VK_R,					//0x15
	WISP_VK_S,					//0x16
	WISP_VK_T,					//0x17
	WISP_VK_U,					//0x18
	WISP_VK_V,					//0x19
	WISP_VK_W,					//0x1A
	WISP_VK_X,					//0x1B
	WISP_VK_Y,					//0x1C
	WISP_VK_Z,					//0x1D
	WISP_VK_1,					//0x1E
	WISP_VK_2,					//0x1F
	WISP_VK_3,					//0x20
	WISP_VK_4,					//0x21
	WISP_VK_5,					//0x22
	WISP_VK_6,					//0x23
	WISP_VK_7,					//0x24
	WISP_VK_8,					//0x25
	WISP_VK_9,					//0x26
	WISP_VK_0,					//0x27
	WISP_VK_RETURN,				//0x28
	WISP_VK_ESCAPE,				//0x29	
	WISP_VK_BACK,				//0x2A
	WISP_VK_TAB,				//0x2B
	WISP_VK_SPACE,				//0x2C
	WISP_VK_OEM_MINUS,			//0x2D//WISP_VK_OEM_MINUS
	WISP_VK_OEM_PLUS,			//0x2E
	WISP_VK_LSQUARE_BRACKET,	//0x2F
	WISP_VK_RSQUARE_BRACKET,	//0x30
	WISP_VK_OEM_5,				//0x31
	WISP_VK_NULL,				//0x32//WISP_VK_OEM_5
	WISP_VK_SEMI,				//0x33
	WISP_VK_QUOT,				//0x34
	WISP_VK_OEM_3,				//0x35
	WISP_VK_OEM_COMMA,			//0x36
	WISP_VK_OEM_PERIOD,			//0x37
	WISP_VK_OEM_2,				//0x38
	WISP_VK_CAPS_LOCK,			//0x39
	WISP_VK_F1,					//0x3A
	WISP_VK_F2,					//0x3B
	WISP_VK_F3,					//0x3C
	WISP_VK_F4,					//0x3D
	WISP_VK_F5,					//0x3E
	WISP_VK_F6,					//0x3F
	WISP_VK_F7,					//0x40
	WISP_VK_F8,					//0x41
	WISP_VK_F9,					//0x42
	WISP_VK_F10,				//0x43
	WISP_VK_F11,				//0x44
	WISP_VK_F12,				//0x45
	WISP_VK_PRINT,				//0x46  //e0 37
	WISP_VK_SCROLL_LOCK,		//0x47
	WISP_VK_NULL,				//0xe0 0x46
	WISP_VK_INSERT,				//0xe0 0x52  'Ins'在小键盘上
	WISP_VK_HOME,				//scancode 71 0x47  'Home'
	WISP_VK_PAGE_UP,			//scancode 73 0x49  'Page Up'在小键盘上
	WISP_VK_DELETE,				//scancode 83 0x53  'Del'在小键盘上
	WISP_VK_END,				//scancode 79 0x4f  'End' 在小键盘上
	WISP_VK_PAGE_DOWN,			//scancode 81 0x51  'Page Dn'在小键盘上
	WISP_VK_RIGHT,				//scancode 77 0x4d  'Right Arrow Key' 在小键盘上
	WISP_VK_LEFT,				//scancode 75 0x4b  'Left Arrow Key'在小键盘上 .
	WISP_VK_DOWN,				//scancode 80 0x50  'Down Arrow Key'在小键盘上
	WISP_VK_UP,					//scancode 72 0x48  'Up Arrow Key'在小键盘上 .
	WISP_VK_NUMLOCK,			//scancode 69 0x45  'Num Lock'   Pause Break  0xE1 0x1D 0x45 0xE1 0x9D 0xC5
	WISP_VK_OEM_2,				//scancode 53 0x35  '/?'
	WISP_VK_MULTIPLY,			//scancode 55 0x37  '*'在小键盘上 . 'Print Screen* Sys Rq' 0xE0 0x2A 0xE0 0x37 0xE0 0xB7 0xE0 0xAA
	WISP_VK_SUBTRACT,			//scancode 74 0x4a  '-'在小键盘上
	WISP_VK_ADD,				//scancode 78 0x4e  '+' 
	WISP_VK_RETURN,				//scancode 28 0x1c	'}]'
	WISP_VK_NUMPAD1,			//scancode 79 0x4f  'End' 在小键盘上
	WISP_VK_NUMPAD2,			//scancode 80 0x50  'Down Arrow Key'在小键盘上
	WISP_VK_NUMPAD3,			//scancode 81 0x51  'Page Dn'在小键盘上
	WISP_VK_NUMPAD4,			//scancode 75 0x4b  'Left Arrow Key'在小键盘上 .
	WISP_VK_NUMPAD5,			//scancode 76 0x4c  '5' 在小键盘上
	WISP_VK_NUMPAD6,			//scancode 77 0x4d  'Right Arrow Key' 在小键盘上
	WISP_VK_NUMPAD7,			//scancode 71 0x47  'Home'
	WISP_VK_NUMPAD8,			//scancode 72 0x48  'Up Arrow Key'在小键盘上 .
	WISP_VK_NUMPAD9,			//scancode 73 0x49  'Page Up'在小键盘上
	WISP_VK_NUMPAD0,			//scancode 82 0x52  'Ins'在小键盘上
	WISP_VK_DECIMAL,			//scancode 83 0x53  'Del'在小键盘上
	WISP_VK_NULL,				//scancode 86 0x56
	WISP_VK_APPS,				//scancode 93 0x5d  'Apps'
	WISP_VK_NULL,				//
	WISP_VK_NULL,				//scancode 93 0x5d  'Window Apps'
	WISP_VK_NULL,				//scancode 94 0x5e  'Power'
	WISP_VK_NULL,				//scancode 95 0x5f  'Sleep'
};
