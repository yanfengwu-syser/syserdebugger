#ifndef __HWNDCMD__H__

#define __HWNDCMD__H__

#ifdef CODE_OS_NT_DRV

#define WS_POPUPWINDOW			0x80880000L
#define WS_OVERLAPPEDWINDOW		0x00cf0000L
#define WS_CHILDWINDOW			0x40000000L
#define WS_CAPTION				0x00c00000L
#define WS_CHILD				0x40000000L
#define WS_OVERLAPPED			0x00000000L
#define WS_EX_OVERLAPPEDWINDOW	0x00000300L
#define WS_EX_PALETTEWINDOW		0x00000188L
#define WS_EX_RIGHT             0x00001000L
#define WS_EX_RTLREADING        0x00002000L
#define WS_EX_LEFTSCROLLBAR     0x00004000L

#endif

typedef struct _WND_STYLE_INFO
{
	DWORD Value;
	WCHAR *Name;
}WND_STYLE_INFO,*PWND_STYLE_INFO;
extern WND_STYLE_INFO gWndStyleExInfo[18];
extern WND_STYLE_INFO gWndStyleInfo[17];
extern WND_STYLE_INFO gOSPredefineColor[30];
extern WND_STYLE_INFO gOSClassStyle[13];
extern WND_STYLE_INFO gOSPredefineCursor[14];
struct _SYSER_HWND_INFO;
typedef struct _SYSER_HWND_INFO
{
	DWORD hWnd;							//0
	DWORD Unknow1;						//4
	DWORD Thread;						//8
	DWORD Unknow2[4];					//c
	DWORD Style;						//1c
	DWORD StyleEx;						//20
	DWORD InstanceHandle	;			//24
	DWORD Unknow3;						//28
	_SYSER_HWND_INFO* NextHwnd;			//2c
	_SYSER_HWND_INFO* PreviousHwnd;		//30
	_SYSER_HWND_INFO* ParentHwnd;		//34
	_SYSER_HWND_INFO* ChildHwnd;		//38
	_SYSER_HWND_INFO* OwnerHwnd;		//3c
	int	WndLeft;						//40
	int WndTop;							//44
	int WndRight;						//48
	int WndBottom;						//4c
	int CliLeft;						//50
	int CliTop;							//54
	int CliRight;						//58
	int CliBottom;						//5c
	DWORD WndProc;						//60
	DWORD ClassInfo;					//64
	DWORD Unknow4[4];					//68
	union{
		DWORD Menu;						//78
		DWORD ControlID;				//78 
	};	
	DWORD Unknow5;						//7c
	DWORD WindowCaptionLen;				//80
	DWORD Unknow9;						//84
	DWORD WindowCaptionBuffer;			//88
	DWORD Unknow21[3];					//8c
	DWORD UserData;						//98
	DWORD Unknow11;						//9c
}SYSER_HWND_INFO,*PSYSER_HWND_INFO;

struct _SYSER_HWND_CLASS_INFO;
typedef struct _SYSER_HWND_CLASS_INFO
{
DWORD Next;							//0
DWORD Flags;						//4
DWORD Unknow1;						//8
DWORD Unknow2[0x24/sizeof(DWORD)];	//c
DWORD style;						//0x30
DWORD lpfnWndProc;					//0x34
DWORD cbClsExtra;					//0x38
DWORD cbWndExtra;					//0x3c
DWORD hInstance;					//0x40
DWORD IconHandle;					//0x44
DWORD hCursor;						//0x48
DWORD hbrBackground;				//0x4c
DWORD lpszMenuName;					//0x50
DWORD lpszClassName;				//0x54
DWORD hIconSm;						//0x58
}SYSER_HWND_CLASS_INFO,*PSYSER_HWND_CLASS_INFO;

bool GetHwndInfoByWndStruct(void* OsWindowPtr,PSYSER_HWND_INFO SyserHwndInfo);
bool GetClassInfoByHwndInfo(PSYSER_HWND_INFO SyserHwndInfo,PSYSER_HWND_CLASS_INFO SyserHwndClassInfo);
DWORD GetHwndInfoByHwnd(DWORD HwndID,PSYSER_HWND_INFO HwndInfo);
class CWndHwnd
{
public:
	CWndHwnd(void* WindowHwndPtr=NULL);
	~CWndHwnd();
	DWORD GetNextWindowCaption(WCHAR* Caption,DWORD CaptionLen);
	DWORD GetPrevWindowCaption(WCHAR* Caption,DWORD CaptionLen);
	DWORD GetParentWindowCaption(WCHAR* Caption,DWORD CaptionLen);
	DWORD GetFirstChildWindowCaption(WCHAR* Caption,DWORD CaptionLen);
	DWORD GetOwnerWindowCaption(WCHAR* Caption,DWORD CaptionLen);
	DWORD GetClassName(WCHAR* ClassName,DWORD ClassNameLen);
	SYSER_HWND_CLASS_INFO m_HwndInfo;
};

class CSyser;
DECLARE_SYSER_CMD(hwnd_command);
DECLARE_SYSER_CMD(bmsg_command);
extern const WCHAR cmd_bmsg_usage[];
extern const WCHAR cmd_hwnd_usage[];
#endif //__HWNDCMD__H__
