#ifndef _WISP_DEFINE_H_
#define _WISP_DEFINE_H_

//#define WISP_TIMER_SIM_KEY_REPEAT

#ifndef WISP_ANSI_CHAR
#define WISP_STR(s)		L##s
typedef WCHAR			WISP_CHAR;
#else
#define WISP_STR(s)		s
typedef CHAR			WISP_CHAR;
#endif

typedef WISP_CHAR*					WISP_PSTR;
typedef const WISP_CHAR*			WISP_PCSTR;

typedef DWORD						WISP_COLOR_CHAR;
typedef TString<WISP_CHAR>			CWispString;
typedef TString<WISP_COLOR_CHAR>	CWispColorString;
/////////////////////////////////////////////////////////////////////////////////
//颜色宏<Start>
/////////////////////////////////////////////////////////////////////////////////
#undef	WISP_RGB
#define WISP_RGB(r,g,b)						((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))
#define WISP_RGB_B(c)						((BYTE)(c))
#define WISP_RGB_G(c)						((BYTE)((c)>>8 ))
#define WISP_RGB_R(c)						((BYTE)((c)>>16))
#define WIN_RGB_TO_WISP(c)					WISP_RGB(WISP_RGB_B(c),WISP_RGB_G(c),WISP_RGB_R(c))

//渐变
#define GRAY_CHG_RGB(r,g,b,s,n)				WISP_RGB((r)+3*(s)*(n),(g)+5*(s)*(n),(b)+(s)*(n))
#define GRAY_CHG(c,s,n)						GRAY_CHG_RGB(WISP_RGB_R(c),WISP_RGB_G(c),WISP_RGB_B(c),s,n)
#define GRAY_DEEP(c)						(WISP_RGB_B(c)*3+WISP_RGB_G(c)*5+WISP_RGB_B(c))
//透明
#define ALPHA_CHG_RGB(sr,sg,sb,dr,dg,db,a)	WISP_RGB((sr*a+(255-a)*dr)/255,(sg*a+(255-a)*dg)/255,(sb*a+(255-a)*db)/255)
#define ALPHA_CHG(sc,dc,a)					ALPHA_CHG_RGB(WISP_RGB_R(sc),WISP_RGB_G(sc),WISP_RGB_B(sc),WISP_RGB_R(dc),WISP_RGB_G(dc),WISP_RGB_B(dc),(a))
//////////////////////////////////////////////////
//颜色宏<End>
//////////////////////////////////////////////////

///////////////////////////////////////////////////
//Lock键
///////////////////////////////////////////////////
#define WISP_VK_LOCK_COUNT		3
#define WISP_VK_CAPS_LOCK		0
#define WISP_VK_NUM_LOCK		1
#define WISP_VK_SCROLL_LOCK		2
///////////////////////////////////////////////////
//按键
///////////////////////////////////////////////////
#define	WISP_VK_COUNT			0x100

#define WISP_VK_NULL			0x00
#define WISP_VK_LBUTTON			0x01
#define WISP_VK_RBUTTON			0x02
#define WISP_VK_CANCEL			0x03
#define WISP_VK_MBUTTON			0x04
#define WISP_VK_XBUTTON1		0x05
#define WISP_VK_XBUTTON2		0x06
#define WISP_VK_KEYBOARD_START	0x07
#define WISP_VK_BACK			0x08
#define WISP_VK_TAB				0x09
#define WISP_VK_0X0A			0x0A
#define WISP_VK_0X0B			0x0B
#define WISP_VK_CLEAR			0x0C
#define WISP_VK_RETURN			0x0D
#define WISP_VK_0X0E			0x0E
#define WISP_VK_0X0F			0x0F

#define WISP_VK_SHIFT			0x10
#define WISP_VK_CONTROL			0x11
#define WISP_VK_ALT				0x12
#define WISP_VK_PAUSE			0x13
#define WISP_VK_CAPITAL			0x14
#define WISP_VK_0X15			0x15
#define WISP_VK_0X16			0x16
#define WISP_VK_0X17			0x17
#define WISP_VK_0X18			0x18
#define WISP_VK_0X19			0x19
#define WISP_VK_0X1A			0x1A
#define WISP_VK_ESCAPE			0x1B
#define WISP_VK_CONVERT			0x1C
#define WISP_VK_NONCONVERT		0x1D
#define WISP_VK_ACCEPT			0x1E
#define WISP_VK_MODECHANGE		0x1F

#define WISP_VK_SPACE			0x20
#define WISP_VK_PAGE_UP			0x21
#define WISP_VK_PAGE_DOWN		0x22
#define WISP_VK_END				0x23
#define WISP_VK_HOME			0x24
#define WISP_VK_LEFT			0x25
#define WISP_VK_UP				0x26
#define WISP_VK_RIGHT			0x27
#define WISP_VK_DOWN			0x28
#define WISP_VK_SELECT			0x29
#define WISP_VK_PRINT			0x2A
#define WISP_VK_EXECUTE			0x2B
#define WISP_VK_SNAPSHOT		0x2C
#define WISP_VK_INSERT			0x2D
#define WISP_VK_DELETE			0x2E
#define WISP_VK_HELP			0x2F

#define WISP_VK_0				0x30
#define WISP_VK_1				0x31
#define WISP_VK_2				0x32
#define WISP_VK_3				0x33
#define WISP_VK_4				0x34
#define WISP_VK_5				0x35
#define WISP_VK_6				0x36
#define WISP_VK_7				0x37
#define WISP_VK_8				0x38
#define WISP_VK_9				0x39
#define WISP_VK_0X3A			0x3A
#define WISP_VK_0X3B			0x3B
#define WISP_VK_0X3C			0x3C
#define WISP_VK_0X3D			0x3D
#define WISP_VK_0X3E			0x3E
#define WISP_VK_0X3F			0x3F

#define WISP_VK_0X40			0x40
#define WISP_VK_A				0x41
#define WISP_VK_B				0x42
#define WISP_VK_C				0x43
#define WISP_VK_D				0x44
#define WISP_VK_E				0x45
#define WISP_VK_F				0x46
#define WISP_VK_G				0x47
#define WISP_VK_H				0x48
#define WISP_VK_I				0x49
#define WISP_VK_J				0x4A
#define WISP_VK_K				0x4B
#define WISP_VK_L				0x4C
#define WISP_VK_M				0x4D
#define WISP_VK_N				0x4E
#define WISP_VK_O				0x4F

#define WISP_VK_P				0x50
#define WISP_VK_Q				0x51
#define WISP_VK_R				0x52
#define WISP_VK_S				0x53
#define WISP_VK_T				0x54
#define WISP_VK_U				0x55
#define WISP_VK_V				0x56
#define WISP_VK_W				0x57
#define WISP_VK_X				0x58
#define WISP_VK_Y				0x59
#define WISP_VK_Z				0x5A
#define WISP_VK_LWIN			0x5B
#define WISP_VK_RWIN			0x5C
#define WISP_VK_APPS			0x5D
#define WISP_VK_0X5E			0x5E
#define WISP_VK_SLEEP			0x5F

#define WISP_VK_NUMPAD0			0x60
#define WISP_VK_NUMPAD1			0x61
#define WISP_VK_NUMPAD2			0x62
#define WISP_VK_NUMPAD3			0x63
#define WISP_VK_NUMPAD4			0x64
#define WISP_VK_NUMPAD5			0x65
#define WISP_VK_NUMPAD6			0x66
#define WISP_VK_NUMPAD7			0x67
#define WISP_VK_NUMPAD8			0x68
#define WISP_VK_NUMPAD9			0x69
#define WISP_VK_MULTIPLY		0x6A
#define WISP_VK_ADD				0x6B
#define WISP_VK_SEPARATOR		0x6C
#define WISP_VK_SUBTRACT		0x6D
#define WISP_VK_DECIMAL			0x6E
#define WISP_VK_DIVIDE			0x6F

#define WISP_VK_F1				0x70
#define WISP_VK_F2				0x71
#define WISP_VK_F3				0x72
#define WISP_VK_F4				0x73
#define WISP_VK_F5				0x74
#define WISP_VK_F6				0x75
#define WISP_VK_F7				0x76
#define WISP_VK_F8				0x77
#define WISP_VK_F9				0x78
#define WISP_VK_F10				0x79
#define WISP_VK_F11				0x7A
#define WISP_VK_F12				0x7B
#define WISP_VK_F13				0x7C
#define WISP_VK_F14				0x7D
#define WISP_VK_F15				0x7E
#define WISP_VK_F16				0x7F

#define WISP_VK_F17				0x80
#define WISP_VK_F18				0x81
#define WISP_VK_F19				0x82
#define WISP_VK_F20				0x83
#define WISP_VK_F21				0x84
#define WISP_VK_F22				0x85
#define WISP_VK_F23				0x86
#define WISP_VK_F24				0x87
#define WISP_VK_0X88			0x88
#define WISP_VK_0X89			0x89
#define WISP_VK_0X8A			0x8A
#define WISP_VK_0X8B			0x8B
#define WISP_VK_0X8C			0x8C
#define WISP_VK_0X8D			0x8D
#define WISP_VK_0X8E			0x8E
#define WISP_VK_0X8F			0x8F

#define WISP_VK_NUMLOCK 		0x90
#define WISP_VK_SCROLL 			0x91
#define WISP_VK_0X92			0x92
#define WISP_VK_0X93			0x93
#define WISP_VK_0X94			0x94
#define WISP_VK_0X95			0x95
#define WISP_VK_0X96			0x96
#define WISP_VK_0X97			0x97
#define WISP_VK_0X98			0x98
#define WISP_VK_0X99			0x99
#define WISP_VK_0X9A			0x9A
#define WISP_VK_0X9B			0x9B
#define WISP_VK_0X9C			0x9C
#define WISP_VK_0X9D			0x9D
#define WISP_VK_0X9E			0x9E
#define WISP_VK_0X9F			0x9F

#define WISP_VK_LSHIFT			0xA0
#define WISP_VK_RSHIFT			0xA1
#define WISP_VK_LCONTROL		0xA2
#define WISP_VK_RCONTROL		0xA3
#define WISP_VK_LALT			0xA4
#define WISP_VK_RALT			0xA5
#define WISP_VK_BROWSER_BACK			0xA6
#define WISP_VK_BROWSER_FORWARD			0xA7
#define WISP_VK_BROWSER_REFRESH			0xA8
#define WISP_VK_BROWSER_STOP			0xA9
#define WISP_VK_BROWSER_SEARCH			0xAA
#define WISP_VK_BROWSER_FAVORITES		0xAB
#define WISP_VK_BROWSER_HOME			0xAC
#define WISP_VK_VOLUME_MUTE				0xAD
#define WISP_VK_VOLUME_DOWN				0xAE
#define WISP_VK_VOLUME_UP				0xAF

#define WISP_VK_MEDIA_NEXT_TRACK		0xB0
#define WISP_VK_MEDIA_PREV_TRACK		0xB1
#define WISP_VK_MEDIA_STOP				0xB2
#define WISP_VK_MEDIA_PLAY_PAUSE		0xB3
#define WISP_VK_LAUNCH_MAIL				0xB4
#define WISP_VK_LAUNCH_MEDIA_SELECT		0xB5
#define WISP_VK_LAUNCH_APP1				0xB6
#define WISP_VK_LAUNCH_APP2				0xB7
#define WISP_VK_0XB8					0xB8
#define WISP_VK_0XB9					0xB9
#define WISP_VK_SEMI			0xBA   // ';:' for US
#define WISP_VK_OEM_PLUS		0xBB   // '+' any country
#define WISP_VK_OEM_COMMA		0xBC   // ',' any country
#define WISP_VK_OEM_MINUS		0xBD   // '-' any country
#define WISP_VK_OEM_PERIOD		0xBE   // '.' any country
#define WISP_VK_OEM_2			0xBF   // '/?' for US

#define WISP_VK_OEM_3			0xC0   // '`~' for US
#define WISP_VK_0XC1			0xC1
#define WISP_VK_0XC2			0xC2
#define WISP_VK_0XC3			0xC3
#define WISP_VK_0XC4			0xC4
#define WISP_VK_0XC5			0xC5
#define WISP_VK_0XC6			0xC6
#define WISP_VK_0XC7			0xC7
#define WISP_VK_0XC8			0xC8
#define WISP_VK_0XC9			0xC9
#define WISP_VK_0XCA			0xCA
#define WISP_VK_0XCB			0xCB
#define WISP_VK_0XCC			0xCC
#define WISP_VK_0XCD			0xCD
#define WISP_VK_0XCE			0xCE
#define WISP_VK_0XCF			0xCF

#define WISP_VK_0XD0			0xD0
#define WISP_VK_0XD1			0xD1
#define WISP_VK_0XD2			0xD2
#define WISP_VK_0XD3			0xD3
#define WISP_VK_0XD4			0xD4
#define WISP_VK_0XD5			0xD5
#define WISP_VK_0XD6			0xD6
#define WISP_VK_0XD7			0xD7
#define WISP_VK_0XD8			0xD8
#define WISP_VK_0XD9			0xD9
#define WISP_VK_0XDA			0xDA
#define WISP_VK_LSQUARE_BRACKET	0xDB  //  '[{' for US
#define WISP_VK_OEM_5			0xDC  //  '\|' for US
#define WISP_VK_RSQUARE_BRACKET	0xDD  //  ']}' for US
#define WISP_VK_QUOT			0xDE  //  ''"' for US
#define WISP_VK_OEM_8			0xDF

#define WISP_VK_0XE0			0xE0
#define WISP_VK_OEM_AX			0xE1  //  'AX' key on Japanese AX kbd
#define WISP_VK_OEM_102			0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define WISP_VK_ICO_HELP		0xE3  //  Help key on ICO
#define WISP_VK_ICO_00			0xE4  //  00 key on ICO
#define WISP_VK_PROCESSKEY		0xE5
#define WISP_VK_ICO_CLEAR		0xE6
#define WISP_VK_PACKET			0xE7
#define WISP_VK_OEM_RESET		0xE9
#define WISP_VK_OEM_JUMP		0xEA
#define WISP_VK_OEM_PA1			0xEB
#define WISP_VK_OEM_PA2			0xEC
#define WISP_VK_OEM_PA3			0xED
#define WISP_VK_OEM_WSCTRL		0xEE
#define WISP_VK_OEM_CUSEL		0xEF

#define WISP_VK_OEM_ATTN		0xF0
#define WISP_VK_OEM_FINISH		0xF1
#define WISP_WISP_VK_OEM_COPY	0xF2
#define WISP_VK_OEM_AUTO		0xF3
#define WISP_VK_OEM_ENLW		0xF4
#define WISP_VK_OEM_BACKTAB		0xF5
#define WISP_VK_ATTN			0xF6
#define WISP_VK_CRSEL			0xF7
#define WISP_VK_EXSEL			0xF8
#define WISP_VK_EREOF			0xF9
#define WISP_VK_PLAY			0xFA
#define WISP_VK_ZOOM			0xFB
#define WISP_VK_NONAME			0xFC
#define WISP_VK_PA1				0xFD
#define WISP_VK_VK_OEM_CLEAR	0xFE
#define WISP_VK_OTHER			0xFF
#define WISP_VK_MAX_ID			0x100

enum WISP_SM
{//系统尺寸
	WISP_SM_CAPTION_CY=0,
	WISP_SM_BORDER_SIZE,
	WISP_SM_THIN_BORDER_SIZE,
	WISP_SM_SCREEN_CX,
	WISP_SM_SCREEN_CY,
	WISP_SM_CAPTION_BT_SIZE,
	WISP_SM_SCROLL_BAR_SIZE,
	WISP_SM_FONT_FRAME_HEIGHT,
	WISP_SM_RESIZE_SPACE,
	WISP_SM_COUNT
};

#define WISP_COLOR_WHITE		0x00FFFFFF
#define WISP_COLOR_BLACK		0x00000000

enum WISP_MOUSE_EVENT
{
	WISP_MOUSE_LEAVE=0,
	WISP_MOUSE_ENTER,
	WISP_MOUSE_MOVE,
	WISP_MOUSE_KEY,
	WISP_MOUSE_EVENT_COUNT
};

enum WISP_DIBLIST_ID
{
	WISP_DIBLIST_MIN = 0,
	WISP_DIBLIST_MAX,
	WISP_DIBLIST_NORMAL,
	WISP_DIBLIST_CLOSE,
	WISP_DIBLIST_HORZ_DEC,
	WISP_DIBLIST_HORZ_INC,
	WISP_DIBLIST_VERT_DEC,
	WISP_DIBLIST_VERT_INC,
	WISP_DIBLIST_COUNT
};

enum WISP_DIB_TYPE
{
	WISP_DI_CARET=0,
	WISP_DI_CURSOR,
	WISP_DI_RESIZE,
	WISP_DI_COUNT
};

//系统缺省子窗口ID
//0x80000000以上为系统定义窗口ID
//0x40000000为系统定义窗口ID
#define WISP_ID_SELF			0xFFFFFFFF
#define WISP_ID_NULL			0x00000000
#define WISP_ID_USER_START		0x00000001
#define WISP_ID_DEVELOP_START	0x40000000
#define WISP_ID_SYS_START		0x80000000

enum
{
	WISP_ID_TOP_MOST_ROOT = WISP_ID_SYS_START,
	WISP_ID_STATIC_STR,
	WISP_ID_STATIC_DIB,
	WISP_ID_STATIC_GROUP,
	WISP_ID_MAIN_FRAME,
	WISP_ID_MAIN_MENU,
	WISP_ID_MAIN_TAB,
	WISP_ID_MAIN_TOOLBAR,
	WISP_ID_SOFT_KB,
	WISP_ID_HELP_TIP,
	WISP_ID_SUB_MENU,
	WISP_ID_CARET_BLINK_TIMER,
	WISP_ID_CLOSE =	0x80001000,
	WISP_ID_MAX,
	WISP_ID_MIN,

	WISP_ID_VPAGE_UP,
	WISP_ID_VPAGE_DOWN,
	WISP_ID_VSLIDE,
	WISP_ID_VSPIN_DEC,
	WISP_ID_VSPIN_INC,

	WISP_ID_HPAGE_UP,
	WISP_ID_HPAGE_DOWN,
	WISP_ID_HSLIDE,
	WISP_ID_HSPIN_DEC,
	WISP_ID_HSPIN_INC,

	WISP_ID_FORM_CLOSE_ID_START = 0x80002000,
	WISP_ID_OK,
	WISP_ID_CANCEL,
	WISP_ID_YES,
	WISP_ID_NO,
	WISP_ID_RETRY,
	WISP_ID_CONTINUE,
	WISP_ID_IGNORE,
	WISP_ID_ABORT,
	WISP_ID_TRY,

	WISP_ID_FORM_CLOSE_ID_END,
	WISP_ID_COPY,
	WISP_ID_CUT,
	WISP_ID_PASTE,
};

///////////////////////////////////////////
//CtrlType
enum WISP_CTRL_TYPE
{
	WISP_CTRL_NULL = 0,
	WISP_CTRL_SYS_TYPE,
	WISP_CTRL_BASE_WND_BEGIN,
	//继存于CWispBaseWnd
	WISP_CTRL_STATIC_STRING,
	WISP_CTRL_STATIC_DIB,
	WISP_CTRL_STATIC_GROUP,
	WISP_CTRL_STATIC_URL,
	WISP_CTRL_BUTTON,
	WISP_CTRL_BASE_WND,
	WISP_CTRL_WND_BEGIN,
	//继存于CWispWnd
	WISP_CTRL_EDIT,
	WISP_CTRL_LIST,
	WISP_CTRL_CHECK_BOX,
	WISP_CTRL_TAB,
	WISP_CTRL_MENU,
	WISP_CTRL_RADIO_BOX,
	WISP_CTRL_MSG_BOX,
	WISP_CTRL_PROGRESS,
	WISP_CTRL_SPLIT_WND,
	WISP_CTRL_TOOL_BAR,
	WISP_CTRL_FORM,
	WISP_CTRL_HEX_WND,
	WISP_CTRL_COMBO_BOX,
	WISP_CTRL_TERMINAL_WND,
	WISP_CTRL_CONSOLE_WND,
	WISP_CTRL_TIP_WND,
	WISP_CTRL_DIB_DC_WND,
	WISP_CTRL_WND,
};

//窗口状态
#define		WISP_WST_INVAILD	0xFFFFFFFF
#define		WISP_WST_NORMAL		0x00000000
#define		WISP_WST_MOVING		0x00000001
#define		WISP_WST_SIZING		0x00000002
#define		WISP_WST_MAX		0x00000004
#define		WISP_WST_MIN		0x00000008

enum
{//指针类型
	WISP_CT_ARROW,
	WISP_CT_RESIZE_VERT,
	WISP_CT_RESIZE_HORZ,
	WISP_CT_DRAG_ARROW,
	WISP_CT_RESIZE_LEFT_LEAN,
	WISP_CT_RESIZE_RIGHT_LEAN,
	WISP_CT_USER_DIB_TYPE,
	WISP_CT_USER_DATA_TYPE
};

enum WISP_SB_TYPE
{
	WISP_SB_START=0,
	WISP_SB_VERT=0,
	WISP_SB_HORZ,
	WISP_SB_COUNT
};

#define WISP_FB_WINDOW					0x00000000
#define WISP_FB_FULL					0x00000001
#define WISP_FB_VIDEO_VIRTUAL_BUF		0x00000002


class CWispDrawHAL;

struct WISP_FRAME_BUFFER
{
	int		Width;
	int		Height;
	int		Bpp;
	int		PixelFormat;
	UINT	Flag;
	void*	Buffer;
	int		BufferSize;
	int		LineDistance;
	CWispDrawHAL*pDrawHAL;
};

enum PIXEL_FORMAT
{
	COLORREF_PF_DEFAULT=0,
	COLORREF_PF_PAL,
	COLORREF_PF_555,
	COLORREF_PF_565,
	COLORREF_PF_888,
	COLORREF_PF_COUNT
};

struct WISP_RECT
{
	int x;
	int y;
	int cx;
	int cy;
};

struct WISP_SIZE
{
	int cx;
	int cy;
};

struct WISP_POINT
{
	int x;
	int y;
};

class CWispDIB;
struct WISP_WND_CARET
{
	int			x;
	int			y;
	int			BlinkTime;
	CWispDIB*	pDIB;
	bool		bEnable;
};

#define WISP_SS_NORMAL			0x00000000
#define WISP_SS_AUTOHIDE		0x00000001
#define WISP_SS_DRAGED_CHANGING	0x00000002

#ifdef WISP_SCROLL_LONGLONG
typedef LONGLONG	WISP_SCROLL_LONG;
#else
typedef LONG	WISP_SCROLL_LONG;
#endif

struct WISP_SCROLL_BAR
{
	WISP_SCROLL_LONG	MinPos;
	WISP_SCROLL_LONG	MaxPos;
	WISP_SCROLL_LONG	CurPos;
	WISP_SCROLL_LONG	Page;
	WISP_SCROLL_LONG	AdjustPage;
	WISP_SCROLL_LONG	StartPos;
	UINT		State;
	UINT		Style;
	UINT		BTSpinIncState;
	UINT		BTSpinDecState;
	WISP_RECT	ScrollRect;
	WISP_RECT	SpaceRect;
	WISP_RECT	SlideRect;
	WISP_RECT	DecBTRect;
	WISP_RECT	IncBTRect;
	int			BarSize;
	int			HotPos;
	bool		bHide;
};

class CWispBaseWnd;
struct WISP_TIMER_KEY
{
	CWispBaseWnd*hWnd;
	UINT	ID;
	bool	operator<(const WISP_TIMER_KEY&Key)const
	{
		if(PTR_TO_NUM(hWnd)<PTR_TO_NUM(Key.hWnd))
			return true;
		if(PTR_TO_NUM(hWnd)>PTR_TO_NUM(Key.hWnd))
			return false;
		return ID<Key.ID;
	}
};

struct WISP_TIMER
{
	int		Elapse;
	int		Period;
	UINT	UserData;
	void*	UserPtr;
};

enum
{
	STATUS_NORMAL = 0,
	STATUS_HOVER,
	STATUS_DOWN,
	STATUS_DISABLED
};

#define	STATE_CHECKED		0x00000001
#define	STATE_SEMICHECKED	0x00000020
#define	STATE_SELECTED		0x00000020
#define	STATE_DISABLED		0x00000040

//Resource Define

struct WISP_FORM_RES_ITEM
{
	UINT		Type;
	WISP_RECT	rc;
	UINT		CmdID;
	UINT		Style;
	WISP_CHAR*	pName;
	void*		pData;
	WISP_CHAR*	pTipString;
};

#define WISP_MOD_SHIFT		0x10000000
#define WISP_MOD_ALT		0x20000000
#define WISP_MOD_CTRL		0x40000000
#define WISP_MOD_WIN		0x80000000

#define WISP_VK(x)			((x)&0xFFFF)

#define WISP_HKS_ALL_WND	0x00000000
#define WISP_HKS_CHILD_WND	0x00000001

struct WISP_HOTKEY_ITEM
{
	UINT	KeyType;
	UINT	Modifier;
	UINT	EventID;
	UINT	Style;
	CWispBaseWnd*hWnd;
};


#endif

