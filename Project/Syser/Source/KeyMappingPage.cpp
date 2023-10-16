#include "StdAfx.h"
#ifdef CODE_OS_NT_DRV
#include "Syser.h"
#endif
//#include "SyserOptionApp.h"
#include "KeyMappingPage.h"
#include "SyserResource.h"
//using namespace std;
BYTE gExternTable[]=
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
BYTE gNormalTable[]=
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
};

typedef struct _KSC_NAME
{
	char* KeyName;
	BYTE VKCode;
}KSC_NAME;
KSC_NAME gKeyNameMap[]=
{
	{"",		0xff},						//scancode 00 0x00 空的没有对应的键
	{"Esc",		WISP_VK_ESCAPE},				//scancode 01 0x01 'Esc'
	{"1",		WISP_VK_1},					//scancode 02 0x02	'1'
	{"2",		WISP_VK_2},					//scancode 03 0x03	'2'
	{"3",		WISP_VK_3},					//scancode 04 0x04	'3'
	{"4",		WISP_VK_4},					//scancode 05 0x05	'4'
	{"5",		WISP_VK_5},					//scancode 06 0x06	'5'
	{"6",		WISP_VK_6},					//scancode 07 0x07	'6'
	{"7",		WISP_VK_7},					//scancode 08 0x08	'7'
	{"8",		WISP_VK_8},					//scancode 09 0x09	'8'
	{"9",		WISP_VK_9},					//scancode 10 0x0a	'9'
	{"0",		WISP_VK_0},					//scancode 11 0x0b  '0'
	{"-",		WISP_VK_OEM_MINUS},			//scancode 12 0x0c  '-_'
	{"+",		WISP_VK_OEM_PLUS},			//scancode 13 0x0d  '=+'	
	{"Backspace",WISP_VK_BACK},				//scancode 14 0x0e  'Back Space'
	{"Tab",		WISP_VK_TAB},				//scancode 15 0x0f  'Tab'
	{"Q",		WISP_VK_Q},					//scancode 16 0x10	'Q'
	{"W",		WISP_VK_W},					//scancode 17 0x11	'W'
	{"E",		WISP_VK_E},					//scancode 18 0x12	'E'
	{"R",		WISP_VK_R},					//scancode 19 0x13	'R'
	{"T",		WISP_VK_T},					//scancode 20 0x14	'T'
	{"Y",		WISP_VK_Y},					//scancode 21 0x15	'Y'
	{"U",		WISP_VK_U},					//scancode 22 0x16	'U'
	{"I",		WISP_VK_I},					//scancode 23 0x17	'I'
	{"O",		WISP_VK_O},					//scancode 24 0x18	'O'
	{"P",		WISP_VK_P},					//scancode 25 0x19	'P'
	{"[",		WISP_VK_LSQUARE_BRACKET},	//scancode 26 0x1a	'[{'
	{"]",		WISP_VK_RSQUARE_BRACKET},	//scancode 27 0x1b	'P'
	{"Enter",	WISP_VK_RETURN},				//scancode 28 0x1c	'Enter'
	{"Ctrl",	WISP_VK_CONTROL},			//scancode 29 0x1d	'Left Ctrl'
	{"A",		WISP_VK_A},					//scancode 30 0x1E	'A'
	{"S",		WISP_VK_S},					//scancode 31 0x1F	'S'
	{"D",		WISP_VK_D},					//scancode 32 0x20	'D'
	{"F",		WISP_VK_F},					//scancode 33 0x21	'F'
	{"G",		WISP_VK_G},					//scancode 34 0x22	'G'
	{"H",		WISP_VK_H},					//scancode 35 0x23	'H'
	{"J",		WISP_VK_J},					//scancode 36 0x24	'J'
	{"K",		WISP_VK_K},					//scancode 37 0x25	'K'
	{"L",		WISP_VK_L},					//scancode 38 0x26	'L'
	{";",		WISP_VK_SEMI},				//scancode 39 0x27	';:'
	{"'",		WISP_VK_QUOT},				//scancode 40 0x28	''"'
	{"",		0xff},						//scancode 41 0x29  ''
	{"Shift",	WISP_VK_SHIFT},				//scancode 42 0x2a  'Left Shift'
	{"\\",		WISP_VK_OEM_5},				//scancode 43 0x2b  '\|'
	{"Z",		WISP_VK_Z},					//scancode 44 0x2c	'Z'
	{"X",		WISP_VK_X},					//scancode 45 0x2d	'X'
	{"C",		WISP_VK_C},					//scancode 46 0x2E	'C'
	{"V",		WISP_VK_V},					//scancode 47 0x2F	'V'
	{"B",		WISP_VK_B},					//scancode 48 0x30	'B'
	{"N",		WISP_VK_N},					//scancode 49 0x31	'N'
	{"M",		WISP_VK_M},					//scancode 50 0x32	'M'
	{",",		WISP_VK_OEM_COMMA},			//scancode 51 0x33  ',<'
	{".",		WISP_VK_OEM_PERIOD},			//scancode 52 0x34  ',>'
	{"/",		WISP_VK_OEM_2},				//scancode 53 0x35  '/?'
	{"Shift",	WISP_VK_SHIFT},				//scancode 54 0x36  'Right Shift'
	{"*",		WISP_VK_MULTIPLY},			//scancode 55 0x37  '*'在小键盘上 . 'Print Screen* Sys Rq' 0xE0 0x2A 0xE0 0x37 0xE0 0xB7 0xE0 0xAA
	{"Alt",		WISP_VK_ALT},				//scancode 56 0x38  'Left Alt'
	{"Space",	WISP_VK_SPACE},				//scancode 57 0x39  'Blank Space' 
	{"Caps Lock",WISP_VK_CAPITAL},			//scancode 58 0x3a	'Caps Lock'
	{"F1",		WISP_VK_F1},					//scancode 59 0x3b  'F1' 
	{"F2",		WISP_VK_F2},					//scancode 60 0x3c  'F2'
	{"F3",		WISP_VK_F3},					//scancode 61 0x3d  'F3'
	{"F4",		WISP_VK_F4},					//scancode 62 0x3e  'F4'
	{"F5",		WISP_VK_F5},					//scancode 63 0x3f  'F5'
	{"F6",		WISP_VK_F6},					//scancode 64 0x40  'F6'
	{"F7",		WISP_VK_F7},					//scancode 65 0x41  'F7'
	{"F8",		WISP_VK_F8},					//scancode 66 0x42  'F8'
	{"F9",		WISP_VK_F9},					//scancode 67 0x43  'F9'
	{"F10",		WISP_VK_F10},				//scancode 68 0x44  'F10'
	{"Num Lock",		WISP_VK_NUMLOCK},			//scancode 69 0x45  'Num Lock'   Pause Break  0xE1 0x1D 0x45 0xE1 0x9D 0xC5
	{"",		WISP_VK_SCROLL},				//scancode 70 0x46  'Scroll Lock'
	{"Numeric pad 7",		WISP_VK_NUMPAD7},			//scancode 71 0x47  'Home'
	{"Numeric pad 8",		WISP_VK_NUMPAD8},			//scancode 72 0x48  'Up Arrow Key'在小键盘上 .
	{"Numeric pad 9",		WISP_VK_NUMPAD9},			//scancode 73 0x49  'Page Up'在小键盘上
	{"",		WISP_VK_SUBTRACT},			//scancode 74 0x4a  '-'在小键盘上
	{"Numeric pad 4",		WISP_VK_NUMPAD4},			//scancode 75 0x4b  'Left Arrow Key'在小键盘上 .						
	{"Numeric pad 5",		WISP_VK_NUMPAD5},			//scancode 76 0x4c  '5' 在小键盘上
	{"Numeric pad 6",		WISP_VK_NUMPAD6},			//scancode 77 0x4d  'Right Arrow Key' 在小键盘上
	{"",		WISP_VK_ADD},				//scancode 78 0x4e  '+' 
	{"Numeric pad 1",		WISP_VK_NUMPAD1},			//scancode 79 0x4f  'End' 在小键盘上
	{"Numeric pad 2",		WISP_VK_NUMPAD2},			//scancode 80 0x50  'Down Arrow Key'在小键盘上
	{"Numeric pad 3",		WISP_VK_NUMPAD3},			//scancode 81 0x51  'Page Dn'在小键盘上
	{"Numeric pad 0",		WISP_VK_NUMPAD0},			//scancode 82 0x52  'Ins'在小键盘上
	{"Decimal",		WISP_VK_DECIMAL},			//scancode 83 0x53  'Del'在小键盘上
	{"",		0xff},						//scancode 84 0x54
	{"",		0xff},						//scancode 85 0x55
	{"",		0xff},						//scancode 86 0x56
	{"F11",		WISP_VK_F11},				//scancode 87 0x57  'F11'
	{"F12",		WISP_VK_F12},				//scancode 88 0x58  'F12'
	{"",		0xff},						//scancode 89 0x59  ''
	{"",		0xff},						//scancode 90 0x5a  ''
	{"",		0xff},						//scancode 91 0x5b  'Left Windows'
	{"",		0xff},						//scancode 92 0x5c  'Right Windows'
	{"",		0xff},						//scancode 93 0x5d  'Window Apps'
	{"",		0xff},						//scancode 94 0x5e  'Power'
	{"",		0xff},						//scancode 95 0x5f  'Sleep'
	{"",		0xff},						//scancode 96 0x60	
	{"",		WISP_VK_PAUSE},				//scancode 97 0x61  
	{"",		0xff},						//scancode 98 0x62
	{"",		0xff},						//scancode 99 0x63  'Wake Up'
	{"Up",		WISP_VK_UP},						//scancode 98 0x62
	{"Down",		WISP_VK_DOWN},						//scancode 99 0x63  'Wake Up'

};



enum CKeyMappingPage::WISP_FORM_ID
{
	CMD_ID_KEYMAP_LIST_COMMANDS = WISP_ID_USER_START,
	CMD_ID_KEYMAP_STRING_COMMANDS,
	CMD_ID_KEYMAP_STRING_EXISTING,
	CMD_ID_KEYMAP_LIST_EXISTING ,
	CMD_ID_KEYMAP_STRING_NEW_KEY,
	CMD_ID_KEYMAP_GROUP_DESCRIPTION,
	CMD_ID_KEYMAP_EDIT_NEW_KEY,
	CMD_ID_STATIC_GROUP,
	CMD_ID_KEYMAP_ADD,
	CMD_ID_KEYMAP_REMOVE,
	CMD_ID_KEYMAP_APPLY,
	CMD_ID_KEYMAP_RELOAD,
	CMD_ID_KEYMAP_DEFAULT_BT,
	CMD_ID_KEYMAP_DEFAULT,
};

WISP_FORM_RES_ITEM CKeyMappingPage::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,560,410},
		WISP_ID_NULL,
#ifdef _SYSER_ 
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("SyserDebugger HotKey configure"),
		"\\SyserIcon\\Plugin.ico",
		WSTR("Syser HotKey configure !"),
#else
		WISP_WS_NULL,
#endif	
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{10,10,530,330},
		CMD_ID_STATIC_GROUP,
		WISP_WS_NULL,
		WSTR("Key Mapping"),
	},
	{
		WISP_CTRL_STATIC_STRING,
		{20,30,80,16},
		CMD_ID_KEYMAP_STRING_COMMANDS,
		WISP_WS_NULL,
		WSTR("Commands"),
	},	
	{
		WISP_CTRL_LIST,
		{20,50,300,280},
		CMD_ID_KEYMAP_LIST_COMMANDS,
		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_TREE,
		
	},
	{
		WISP_CTRL_STATIC_STRING,
		{340,30,80,16},
		CMD_ID_KEYMAP_STRING_EXISTING,
		WISP_WS_NULL,
		WSTR("Existing"),
	},
	{
		WISP_CTRL_LIST,
		{340,50,80,170},
		CMD_ID_KEYMAP_LIST_EXISTING,
		WISP_WS_THIN_BORDER,
	},
	{
		WISP_CTRL_EDIT,
		{340,310,80,20},
		CMD_ID_KEYMAP_EDIT_NEW_KEY,
		WISP_WS_THIN_BORDER,
	},
	{
		WISP_CTRL_STATIC_GROUP,
		{340,225,190,70},
		CMD_ID_KEYMAP_GROUP_DESCRIPTION,
		WISP_WS_NULL,
		WSTR("Description"),
	},
	{
		WISP_CTRL_STATIC_STRING,
		{340,295,100,16},
		CMD_ID_KEYMAP_STRING_NEW_KEY,
		WISP_WS_NULL,
		WSTR("Press New Key:"),
	},
		{
			WISP_CTRL_BUTTON,
			{430,310,100,20},
			CMD_ID_KEYMAP_DEFAULT_BT,
			WISP_BS_NORMAL|WISP_WS_DISABLED,
			WSTR("Default"),
			NULL,
			NULL
		},
	{
		WISP_CTRL_BUTTON,
		{430,50,100,20},
		CMD_ID_KEYMAP_ADD,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Assign"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,80,100,20},
		CMD_ID_KEYMAP_REMOVE,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Remove"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{430,350,100,20},
		CMD_ID_KEYMAP_APPLY,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Save"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{10,350,100,20},
		CMD_ID_KEYMAP_RELOAD,
		WISP_BS_NORMAL|WISP_WS_DISABLED,
		WSTR("Reload"),
		NULL,
		NULL
	},
	{
		WISP_CTRL_BUTTON,
		{120,350,100,20},
		CMD_ID_KEYMAP_DEFAULT,
		WISP_BS_NORMAL,
		WSTR("Default"),
		NULL,
		NULL
	},
	{WISP_CTRL_NULL}
};

WISP_MSG_MAP_BEGIN(CKeyMappingPage)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnResize)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CKeyMappingPage)
	WISP_MSG_CMD_MAP(CMD_ID_KEYMAP_LIST_COMMANDS,OnFileListCommand)
	WISP_MSG_CMD_MAP(CMD_ID_KEYMAP_EDIT_NEW_KEY,OnNewKeyEdit)
	WISP_MSG_CMD_MAP(CMD_ID_KEYMAP_LIST_EXISTING,OnExistKeyList)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CKeyMappingPage)
	WISP_MSG_EVENT_MAP(CMD_ID_KEYMAP_ADD,OnButtonAdd)
	WISP_MSG_EVENT_MAP(CMD_ID_KEYMAP_REMOVE,OnButtonRemove)
	WISP_MSG_EVENT_MAP(CMD_ID_KEYMAP_APPLY,OnButtonSave)
	WISP_MSG_EVENT_MAP(CMD_ID_KEYMAP_RELOAD,OnButtonReload)
	WISP_MSG_EVENT_MAP(CMD_ID_KEYMAP_DEFAULT,OnButtonDefault)
WISP_MSG_EVENT_MAP_END

CKeyMappingPage::CKeyMappingPage()
{
	m_pFormRes = m_FormRes;
#ifndef CODE_OS_NT_DRV
	GetSystemDirectory(m_HotKeyFile,MAX_FN_LEN);
	TStrCat(m_HotKeyFile,"\\drivers\\SyserHotKey.cfg");
	GetWindowsDirectoryW(m_szSystemRootDir,MAX_FN_LEN);
	m_PreviousKeyType=0;
#endif

}

bool CKeyMappingPage::OnFormCreate(IN WISP_MSG*pMsg)
{
	m_pGroup = (CWispStaticGroup*) GetFormItem(CMD_ID_STATIC_GROUP);
	m_pGroupDescription = (CWispStaticGroup*) GetFormItem(CMD_ID_KEYMAP_GROUP_DESCRIPTION);
	m_pCommandsList = (CWispList*) GetFormItem(CMD_ID_KEYMAP_LIST_COMMANDS);
	m_pExistList = (CWispList*) GetFormItem(CMD_ID_KEYMAP_LIST_EXISTING);
	m_ExistStr=(CWispStaticStr*)GetFormItem(CMD_ID_KEYMAP_STRING_EXISTING);
	m_CommandStr=(CWispStaticStr*)GetFormItem(CMD_ID_KEYMAP_STRING_COMMANDS);
	m_NewKeyStr=(CWispStaticStr*)GetFormItem(CMD_ID_KEYMAP_STRING_NEW_KEY);
	m_NewKeyEdit=(CWispEdit*)GetFormItem(CMD_ID_KEYMAP_EDIT_NEW_KEY);
	m_pSaveBT = (CWispButton*) GetFormItem(CMD_ID_KEYMAP_APPLY);
	m_pDefaultBT = (CWispButton*) GetFormItem(CMD_ID_KEYMAP_DEFAULT);
	m_pReloadBT = (CWispButton*) GetFormItem(CMD_ID_KEYMAP_RELOAD);
	m_pAddBT = (CWispButton*) GetFormItem(CMD_ID_KEYMAP_ADD);
	m_pRemoveBT = (CWispButton*) GetFormItem(CMD_ID_KEYMAP_REMOVE);
	
	m_pDefaultSignBT = (CWispButton*) GetFormItem(CMD_ID_KEYMAP_DEFAULT_BT);
	m_pExistList->InsertColumn(NULL,0,WISP_WLCS_NORMAL);
	
	m_pCommandsList->m_Style|=WISP_WLS_VERT_LINE;
	m_pCommandsList->InsertColumn(NULL,200,WISP_WLCS_NORMAL);
	m_pCommandsList->InsertColumn(NULL,90,WISP_WLCS_NORMAL);
	LoadHotKeyConfigFile();
	
	return true;
}

bool CKeyMappingPage::OnResize(IN WISP_MSG*pMsg)
{
#ifdef _SYSER_
	return true;
#endif
	m_pGroup->Resize(m_ClientRect.cx-20,m_ClientRect.cy-50);

	m_pCommandsList->Resize(m_pGroup->m_WindowRect.cx-230,m_pGroup->m_WindowRect.cy-50);
	m_pExistList->Resize(m_pExistList->m_WindowRect.cx ,m_pGroup->m_WindowRect.cy-160);
	//m_pExistList->MoveToWindow(m_pCommandsList->m_ScrWindowRect.x+ m_pCommandsList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+50);
	m_pExistList->MoveToWindow(m_pCommandsList->m_ScrWindowRect.x - m_ScrWindowRect.x + m_pCommandsList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+50);
	m_ExistStr->MoveToWindow(m_pCommandsList->m_ScrWindowRect.x+ m_pCommandsList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+30);
	m_NewKeyStr->MoveToWindow(m_pCommandsList->m_ScrWindowRect.x+ m_pCommandsList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+m_pGroup->m_WindowRect.cy - 36);
	m_NewKeyEdit->MoveToWindow(m_pCommandsList->m_ScrWindowRect.x+ m_pCommandsList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+m_pGroup->m_WindowRect.cy - 16);
	m_pGroupDescription->MoveToWindow(m_pCommandsList->m_ScrWindowRect.x+ m_pCommandsList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+m_pGroup->m_WindowRect.cy - 106);
	m_pRemoveBT->MoveToWindow(m_pExistList->m_ScrWindowRect.x + m_pExistList->m_WindowRect.cx+10,m_pRemoveBT->m_ScrWindowRect.y - m_ScrWindowRect.y);
	m_pDefaultSignBT->MoveToWindow(m_pExistList->m_ScrWindowRect.x + m_pExistList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+m_pGroup->m_WindowRect.cy - 16);
	m_pRemoveBT->MoveToWindow(m_pExistList->m_ScrWindowRect.x + m_pExistList->m_WindowRect.cx+10,m_pRemoveBT->m_ScrWindowRect.y - m_ScrWindowRect.y);
	m_pAddBT->MoveToWindow(m_pExistList->m_ScrWindowRect.x +m_pExistList->m_WindowRect.cx+10,m_pGroup->m_WindowRect.y+50);
	m_pReloadBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x-m_ScrWindowRect.x,m_pGroup->m_ScrWindowRect.y-m_ScrWindowRect.y+m_pGroup->m_WindowRect.cy+10);
	m_pDefaultBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x-m_ScrWindowRect.x+m_pReloadBT->m_WindowRect.cx+10,m_pGroup->m_ScrWindowRect.y-m_ScrWindowRect.y+m_pGroup->m_WindowRect.cy+10);
	m_pSaveBT->MoveToWindow(m_pGroup->m_ScrWindowRect.x + m_pGroup->m_ScrWindowRect.cx - m_pSaveBT->m_WindowRect.cx - m_ScrWindowRect.x,m_pReloadBT->m_ScrWindowRect.y-m_ScrWindowRect.y);
	
	return true;
}
bool CKeyMappingPage::OnExistKeyList(IN WISP_MSG*pMsg)
{
	switch(pMsg->Command.CmdMsg)
	{
		case WISP_CMD_ITEM_SELECTED:
			m_pRemoveBT->EnableWindow(true);
			break;
	}
	
	return true;
}

WCHAR* CKeyMappingPage::GetHotKeyName(DWORD dwFuncKey,DWORD dwSecondKey,WCHAR* Buffer)
{
	int i;
	Buffer[0]=0;
	if(dwSecondKey==0)
	{
		for(i=0;i<sizeof(gKeyNameMap)/sizeof(gKeyNameMap[0]);i++)
		{
			if(dwFuncKey==gKeyNameMap[i].VKCode)
			{
				TStrCpy(Buffer,gKeyNameMap[i].KeyName);
				break;
			}
		}
	}
	else
	{
		if(dwFuncKey&WISP_MOD_CTRL)
			TStrCpy(Buffer,"Ctrl+");
		if(dwFuncKey&WISP_MOD_ALT)
			TStrCat(Buffer,"Alt+");
		if(dwFuncKey&WISP_MOD_SHIFT)
			TStrCat(Buffer,"Shift+");
		for(i=0;i<sizeof(gKeyNameMap)/sizeof(gKeyNameMap[0]);i++)
		{
			if(dwSecondKey==gKeyNameMap[i].VKCode)
			{
				TStrCat(Buffer,gKeyNameMap[i].KeyName);
				break;
			}
		}			
	}	
	return Buffer;
}

WCHAR* CKeyMappingPage::GetHotKeyName(DWORD KeyValue,WCHAR* Buffer)
{
	int i;
	DWORD dwSecondKey,dwFuncKey;
	if(Buffer==NULL)
		return NULL;
	Buffer[0]=0;
	dwSecondKey = KeyValue & 0xffffff;
	dwFuncKey = KeyValue & 0xff000000;
	if(dwSecondKey==0)
	{
		for(i=0;i<sizeof(gKeyNameMap)/sizeof(gKeyNameMap[0]);i++)
		{
			if(dwFuncKey==gKeyNameMap[i].VKCode)
			{
				TStrCpy(Buffer,gKeyNameMap[i].KeyName);
				break;
			}
		}
	}
	else
	{
		if(dwFuncKey&WISP_MOD_CTRL)
			TStrCpy(Buffer,"Ctrl+");
		if(dwFuncKey&WISP_MOD_ALT)
			TStrCat(Buffer,"Alt+");
		if(dwFuncKey&WISP_MOD_SHIFT)
			TStrCat(Buffer,"Shift+");
		for(i=0;i<sizeof(gKeyNameMap)/sizeof(gKeyNameMap[0]);i++)
		{
			if(dwSecondKey==gKeyNameMap[i].VKCode)
			{
				TStrCat(Buffer,gKeyNameMap[i].KeyName);
				break;
			}
		}			
	}	
	return Buffer;
}

bool CKeyMappingPage::OnFileListCommand(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	NUM_PTR Num;
	DWORD dwFuncKey;
	DWORD dwSecondCode;
	WCHAR Buf[50]={0};
	DWORD dwHotKeyCmdID;
	CMDHOTKEYMAP::IT FindIT;
	CWispList p1;
	HOTKEYLIST* pList;
	HOTKEYLIST::IT BeginIT,EndIT;

	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_ITEM_SELECTED:		
		hItem = m_pCommandsList->GetNextListItem(NULL,WISP_WLIS_SELECTED);
		if(hItem)
		{
			m_pAddBT->EnableWindow(false);
			m_NewKeyEdit->SetWindowText(WSTR(""));
			dwHotKeyCmdID=(DWORD)m_pCommandsList->GetItemData(hItem,1);
			m_pExistList->ClearChildItem();
			FindIT = m_CmdHotKeyMap.Find(dwHotKeyCmdID);
			if(FindIT!=m_CmdHotKeyMap.End())
			{
				pList = &*FindIT;
				BeginIT=pList->Begin();
				EndIT=pList->End();
				for(;BeginIT!=EndIT;BeginIT++)
				{
					dwFuncKey=BeginIT->FuncKeyCode;
					dwSecondCode=BeginIT->SecondKeyCode;
					GetHotKeyName(dwFuncKey,dwSecondCode,Buf);
					Num=dwSecondCode;
					Num<<=32;
					Num|=dwFuncKey;
					hItem = m_pExistList->InsertItem(Buf);
					m_pExistList->SetItemData(hItem,0,Num);
				}				
			}				
		}
		m_pRemoveBT->EnableWindow(false);
		break;
	case WISP_CMD_ITEM_UNSELECTED:
		m_pRemoveBT->EnableWindow(false);
		break;
	case WISP_CMD_ITEM_CHANGED:
		m_pSaveBT->EnableWindow(TRUE);
		m_pReloadBT->EnableWindow(TRUE);
		break;
	}
	return true;
}

bool CKeyMappingPage::OnNewKeyEdit(IN WISP_MSG*pMsg)
{
	int i;
	WCHAR Name[50]={0};
	bool bFind=false;
	bool bCtrl=false;
	bool bAtl=false;
	bool bShift=false;
	DWORD nKey,nPrevKey;
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_EN_INPUT_KEY_DOWN:
		{
			nKey=pMsg->Command.Param1;
			m_PreviousKeyType=nKey;
			bCtrl=(nKey & WISP_MOD_CTRL)?true:false;
			bAtl=(nKey & WISP_MOD_ALT)?true:false;
			bShift=(nKey & WISP_MOD_SHIFT)?true:false;
			nKey=nKey & (~(WISP_MOD_CTRL|WISP_MOD_ALT|WISP_MOD_SHIFT));			
			for(i=0;i<sizeof(gKeyNameMap)/sizeof(gKeyNameMap[0]);i++)
			{

				if(gKeyNameMap[i].VKCode==nKey)
				{
					if(bCtrl)
						TStrCpy(Name,"Ctrl+");
					if(bAtl)
						TStrCat(Name,"Alt+");
					if(bShift)
						TStrCat(Name,"Shift+");
					if(nKey!=WISP_VK_SHIFT && nKey!=WISP_VK_CONTROL && nKey!=WISP_VK_ALT)
						TStrCat(Name,gKeyNameMap[i].KeyName);
					m_NewKeyEdit->SetWindowText(Name);
					bFind=true;
					break;
				}				
			}
			if(!bFind)
				m_NewKeyEdit->SetWindowText(Name);
		}
		return false;
	case WISP_CMD_EN_INPUT_KEY_UP:
		nKey=pMsg->Command.Param1;
		nKey=nKey & (~(WISP_MOD_CTRL|WISP_MOD_ALT|WISP_MOD_SHIFT));
		nPrevKey=m_PreviousKeyType;
		nPrevKey=nPrevKey & (~(WISP_MOD_CTRL|WISP_MOD_ALT|WISP_MOD_SHIFT));
		if((nKey==WISP_VK_SHIFT || nKey==WISP_VK_CONTROL || nKey==WISP_VK_ALT) && (nPrevKey==WISP_VK_SHIFT || nPrevKey==WISP_VK_CONTROL || nPrevKey==WISP_VK_ALT))
		{
			m_NewKeyEdit->SetWindowText(Name);
			return false;
		}
		m_pAddBT->EnableWindow(true);
		m_pDefaultSignBT->EnableWindow(true);
		return false;
	}
	return true;
}

bool CKeyMappingPage::IsListItem(PCWSTR szName)
{
	HANDLE hItem = m_pCommandsList->GetFirstItem();
	while(hItem)
	{
		if(m_pCommandsList->GetItemText(hItem)==szName)
			return true;
		hItem = m_pCommandsList->GetNextItem(hItem);
	}
	return false;
}
KEY_PAIR CKeyMappingPage::GetHotKey()
{
	KEY_PAIR Key;
	Key.SecondKeyCode=0;
	Key.FuncKeyCode=m_PreviousKeyType;
	if(m_PreviousKeyType & (WISP_MOD_CTRL|WISP_MOD_ALT|WISP_MOD_SHIFT))
	{
		Key.FuncKeyCode=m_PreviousKeyType & (WISP_MOD_CTRL|WISP_MOD_ALT|WISP_MOD_SHIFT);
		Key.SecondKeyCode = m_PreviousKeyType & (~(WISP_MOD_CTRL|WISP_MOD_ALT|WISP_MOD_SHIFT));
	}
	return Key;
}
bool CKeyMappingPage::OnButtonAdd(IN WISP_MSG*pMsg)
{
	//MsgBox(WSTR("Do you want to add this and delete the existing assignment?"),WSTR("Key assignment already exists"),WISP_MB_YESNO);
	HOTKEYLIST::IT FindIT;
	HOTKEYLIST* pList;
	HANDLE hItem;
	KEY_PAIR Key;;
	WCHAR Buf[50];
	
	pList=GetCurrentHotKeyList();
	if(pList==NULL)
		return true;
	hItem = m_pCommandsList->GetNextListItem(NULL,WISP_WLIS_SELECTED);
	DWORD Num=(DWORD)m_pCommandsList->GetItemData(hItem,1);	
	if(Num==0)//如果是激活热键则只支持一个
	{
		pList->Clear();
		m_pExistList->ClearChildItem();
	}
	Key = GetHotKey();
	FindIT = pList->Find(Key);
	
	if(FindIT==pList->End())
	{
		pList->Append(Key);
	}
	DWORD nKey=Key.FuncKeyCode;
	GetHotKeyName(nKey,Key.SecondKeyCode,Buf);
	hItem = m_pExistList->InsertItem(Buf);
	m_pExistList->SetItemData(hItem,0,*(NUM_PTR*)&Key);
	m_NewKeyEdit->SetWindowText(WSTR(""));
	m_pSaveBT->EnableWindow(TRUE);
	m_pReloadBT->EnableWindow(TRUE);
	m_pAddBT->EnableWindow(false);
	return true;
}
HOTKEYLIST* CKeyMappingPage::GetCurrentHotKeyList()
{
	HANDLE hItem = m_pCommandsList->GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return NULL;
	DWORD Num=(DWORD)m_pCommandsList->GetItemData(hItem,1);	
	CMDHOTKEYMAP::IT FindIT=m_CmdHotKeyMap.Find(Num);
	if(FindIT!=m_CmdHotKeyMap.End())
	{
		return &*FindIT;
	}
	return NULL;
}
bool CKeyMappingPage::OnButtonRemove(IN WISP_MSG*pMsg)
{
	HANDLE hItem = m_pExistList->GetNextListItem(NULL,WISP_WLIS_SELECTED);
	HOTKEYLIST* pList;
	HOTKEYLIST::IT FindIT;
	NUM_PTR Num;
	if(hItem)
	{
		pList=GetCurrentHotKeyList();
		if(pList==NULL)
			return true;
		Num = m_pExistList->GetItemData(hItem,0);
		FindIT = pList->Find( *(KEY_PAIR*)&Num);
		
		if(FindIT!=pList->End())
		{
			pList->Remove(FindIT);
		}
		m_pExistList->RemoveItem(hItem);
		m_pExistList->Update();
		m_pRemoveBT->EnableWindow(false);
		m_pReloadBT->EnableWindow(TRUE);
		m_pSaveBT->EnableWindow(TRUE);
	}
	return true;
}

bool CKeyMappingPage::OnButtonSave(IN WISP_MSG*pMsg)
{
	if(SaveHotKeyConfigFile()==false)
		return true;
	m_pReloadBT->EnableWindow(FALSE);
	m_pSaveBT->EnableWindow(FALSE);
	Update();
	return true;
}

bool CKeyMappingPage::OnButtonReload(IN WISP_MSG*pMsg)
{
	if(LoadHotKeyConfigFile()==false)
		return true;
	m_pReloadBT->EnableWindow(FALSE);
	m_pSaveBT->EnableWindow(FALSE);
	Update();
	return true;
}

bool CKeyMappingPage::OnButtonDefault(IN WISP_MSG*pMsg)
{
	LoadDefaultAll();
	m_pReloadBT->EnableWindow(FALSE);
	m_pSaveBT->EnableWindow(FALSE);
	Update();
	return true;
}
void CKeyMappingPage::LoadDefaultAll()
{
	CLocalFileIO File;
	File.DeleteFile(m_HotKeyFile);
	CMDHOTKEYMAP::IT MapIT;
	for(MapIT=m_CmdHotKeyMap.Begin();MapIT!=m_CmdHotKeyMap.End();MapIT++)
	{
		MapIT->Clear();
	}
	m_CmdHotKeyMap.Clear();
	LoadHotKeyConfigFile();
	SaveHotKeyConfigFile();
	m_pExistList->ClearChildItem();
}
bool CKeyMappingPage::LoadHotKeyConfigFileByMap(CMDHOTKEYMAP *pCmdHotKeyMap)
{
	if(!pCmdHotKeyMap)
		return false;
	KEY_PAIR KeyPair;
	int nCount=0;
	HOTKEYLIST* pList;
	CMDHOTKEYMAP::IT MapIT;
	WCHAR HotKeyName[50];	
	HOTKEYLIST::IT FindIT;
	HANDLE hItem;	
	
	m_CmdHotKeyMap.Clear();
	for(MapIT=pCmdHotKeyMap->Begin();MapIT!=pCmdHotKeyMap->End();MapIT++)
	{
		m_CmdHotKeyMap.InsertUnique(MapIT.Key(),*MapIT);
	}
	m_pCommandsList->ClearChildItem();
	m_ItemHotkey[0] = m_pCommandsList->InsertItem(WSTR("Globals Hot key configuration"));
	m_pCommandsList->SetItemData(m_ItemHotkey[0],1,0-1);
	m_ItemHotkey[1] = m_pCommandsList->InsertItem(WSTR("Shortcut key for code windows"));;
	m_pCommandsList->SetItemData(m_ItemHotkey[1],1,0-1);
	m_ItemHotkey[2] = m_pCommandsList->InsertItem(WSTR("Shortcut key for data windows"));
	m_pCommandsList->SetItemData(m_ItemHotkey[2],1,0-1);
	m_ItemHotkey[3] =m_pCommandsList->InsertItem(WSTR("Shortcut key for stack windows"));
	m_pCommandsList->SetItemData(m_ItemHotkey[3],1,0-1);
	m_ItemHotkey[4]=m_pCommandsList->InsertItem(WSTR("Shortcut key for register windows"));;
	m_pCommandsList->SetItemData(m_ItemHotkey[4],1,0-1);

	for(int i = 0;i < 5;i++)
	{
		for(int j=0;j<gKeyConfig[i].Count-1;j++)
		{
			MapIT=m_CmdHotKeyMap.Find(gKeyConfig[i].pHotKeyInfo[j].CommandID);
			hItem = m_pCommandsList->InsertItemA(gKeyConfig[i].pHotKeyInfo[j].KeyName,m_ItemHotkey[i]);
			KeyPair.FuncKeyCode=gKeyConfig[i].pHotKeyInfo[j].FuncKeyCode;
			KeyPair.SecondKeyCode=gKeyConfig[i].pHotKeyInfo[j].SecondKeyCode;
			if(MapIT!=m_CmdHotKeyMap.End())
			{
				if(MapIT->Count())
				{
					KeyPair=*MapIT->Begin();
				}
			}
			else
			{
				MapIT = m_CmdHotKeyMap.InsertUnique(gKeyConfig[i].pHotKeyInfo[j].CommandID,HOTKEYLIST());
				pList=&*MapIT;
				pList->Append(KeyPair);
			}
			m_pCommandsList->SetItemData(hItem,1,gKeyConfig[i].pHotKeyInfo[j].CommandID);
			//if(KeyPair.FuncKeyCode)
			m_pCommandsList->SetItemText(hItem,1,GetHotKeyName(KeyPair.FuncKeyCode,KeyPair.SecondKeyCode,HotKeyName));
		}
	}

	return true;

}
bool CKeyMappingPage::LoadHotKeyConfigFile()
{	
	DWORD* Buffer,*pOrgBuffer;
	ULSIZE nBufLen=0x1000;
	int nRealLen;
	CLocalFileIO File;
	DWORD dwNum,i,j,m;
	DWORD dwKeyCmdID;
	KEY_PAIR KeyPair;
	int nCount=0;
	HOTKEYLIST* pList;
	CMDHOTKEYMAP::IT MapIT;
	m_CmdHotKeyMap.Clear();
#ifdef CODE_OS_NT_DRV
	if(gpSyser)
		return LoadHotKeyConfigFileByMap(&gpSyser->m_CmdHotKeyMap);
#endif
	Buffer=new DWORD[(nBufLen+3)/sizeof(sizeof(DWORD))];
	if(Buffer==NULL)
		return false;
	pOrgBuffer=Buffer;
	if(LoadSyserHotKeyOption(m_HotKeyFile,Buffer,nBufLen,&nRealLen))
	{
		Buffer++;
		dwNum=*Buffer++;
		for(i=0;i<dwNum;i++)
		{
			dwKeyCmdID=*Buffer++;
			m=*Buffer++;			
			MapIT = m_CmdHotKeyMap.InsertUnique(dwKeyCmdID,HOTKEYLIST());
			pList=&*MapIT;
			for(j=0;j<m;j++)
			{
				KeyPair.FuncKeyCode=*Buffer++;
				KeyPair.SecondKeyCode=*Buffer++;				
				pList->Append(KeyPair);
				nCount++;				
			}
		}
	}
	m_pCommandsList->ClearChildItem();

	WCHAR HotKeyName[50];	
	HOTKEYLIST::IT FindIT;
	HANDLE hItem;
	m_ItemHotkey[0] = m_pCommandsList->InsertItem(WSTR("Globals Hot key configuration"));
	m_pCommandsList->SetItemData(m_ItemHotkey[0],1,0-1);
	m_ItemHotkey[1] = m_pCommandsList->InsertItem(WSTR("Shortcut key for code windows"));;
	m_pCommandsList->SetItemData(m_ItemHotkey[1],1,0-1);
	m_ItemHotkey[2] = m_pCommandsList->InsertItem(WSTR("Shortcut key for data windows"));
	m_pCommandsList->SetItemData(m_ItemHotkey[2],1,0-1);
	m_ItemHotkey[3] =m_pCommandsList->InsertItem(WSTR("Shortcut key for stack windows"));
	m_pCommandsList->SetItemData(m_ItemHotkey[3],1,0-1);
	m_ItemHotkey[4]=m_pCommandsList->InsertItem(WSTR("Shortcut key for register windows"));;
	m_pCommandsList->SetItemData(m_ItemHotkey[4],1,0-1);
	//hItem = m_pCommandsList->InsertItem(WSTR(""));;
	//m_pCommandsList->SetItemData(hItem,1,0-1);
	for(int i = 0;i < 5;i++)
	{
		for(int j=0;j<gKeyConfig[i].Count-1;j++)
		{
			MapIT=m_CmdHotKeyMap.Find(gKeyConfig[i].pHotKeyInfo[j].CommandID);
			hItem = m_pCommandsList->InsertItemA(gKeyConfig[i].pHotKeyInfo[j].KeyName,m_ItemHotkey[i]);
			KeyPair.FuncKeyCode=gKeyConfig[i].pHotKeyInfo[j].FuncKeyCode;
			KeyPair.SecondKeyCode=gKeyConfig[i].pHotKeyInfo[j].SecondKeyCode;
			if(MapIT!=m_CmdHotKeyMap.End())
			{
				if(MapIT->Count())
				{
					KeyPair=*MapIT->Begin();
				}
			}
			else
			{
				MapIT = m_CmdHotKeyMap.InsertUnique(gKeyConfig[i].pHotKeyInfo[j].CommandID,HOTKEYLIST());
				pList=&*MapIT;
				pList->Append(KeyPair);
			}
			m_pCommandsList->SetItemData(hItem,1,gKeyConfig[i].pHotKeyInfo[j].CommandID);
			//if(KeyPair.FuncKeyCode)
			m_pCommandsList->SetItemText(hItem,1,GetHotKeyName(KeyPair.FuncKeyCode,KeyPair.SecondKeyCode,HotKeyName));
		}
	}

	delete []pOrgBuffer;
	return true;
}

bool CKeyMappingPage::SaveHotKeyConfigFile()
{
	DWORD* Buffer;
	DWORD* pEndBuf;
	ULSIZE nBufLen=0x1000;
	int nRealLen;
	CLocalFileIO File;
	DWORD dwSize=0;
	DWORD dwNum=(DWORD)m_CmdHotKeyMap.Count();
	CMDHOTKEYMAP::IT BeginIT;
	HOTKEYLIST::IT ListIT;

	Buffer=new DWORD[(nBufLen+3)/sizeof(sizeof(DWORD))];
	if(Buffer==NULL)
		return false;
	pEndBuf=Buffer;
	pEndBuf++;	
	*pEndBuf++=dwNum;	
	for(BeginIT=m_CmdHotKeyMap.Begin();BeginIT!=m_CmdHotKeyMap.End();BeginIT++)
	{			
		dwNum=(DWORD)BeginIT->Count();
		if(dwNum==0)
			continue;			
		dwNum=BeginIT.Key();
		*pEndBuf++=dwNum;			
		dwNum=(DWORD)BeginIT->Count();
		*pEndBuf++=dwNum;			
		ListIT=BeginIT->Begin();
		for(;ListIT!=BeginIT->End();ListIT++)
		{
			*pEndBuf++=ListIT->FuncKeyCode;
			*pEndBuf++=ListIT->SecondKeyCode;				
		}
		dwSize++;
	}
	Buffer[1]=dwSize;
	nRealLen = *(int*)&pEndBuf-*(int*)&Buffer;
#ifndef CODE_OS_NT_DRV
	SaveSyserHotKeyOption(m_HotKeyFile,Buffer,nRealLen);
#else
	SaveSyserHotKeyBufferDriver(Buffer,nRealLen);	
#endif
	delete []Buffer;
	return true;
}

void CKeyMappingPage::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
	{
		CreateForm();
		//m_Style=WISP_WS_BORDER;
		//RecalcLayout();
		OnResize(NULL);
		//Create(540,400,NULL,WISP_SKBS_NORMAL,WISP_SH_NORMAL);
		Center();
	}
}