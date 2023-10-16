#ifndef _SYSER_OPTION_H_
#define _SYSER_OPTION_H_

enum SYSER_CONNECT_TYPE
{
	SYSER_NO_CONNECT = 0,
	SYSER_SERIAL_PORT_CONNECT,
	SYSER_NET_CARD_CONNECT
};

enum SYSER_FOLLOW_MODE
{
	SYSER_FM_AUTOMATIC = 0,
	SYSER_FM_SYSTEM_EXPLORER,
	SYSER_FM_SOURCE_EXPLORER
};

enum VIDEO_DETECT_MODE 
{
	SYSER_VDM_AUTO = 0,
	SYSER_VDM_USER,
	SYSER_VDM_KERNEL,
};

#define MIN_MAIN_HEAP			15
#define MAX_MAIN_HEAP			40

#define MIN_SYMBOL_HEAP			4
#define MAX_SYMBOL_HEAP			40

#define MIN_SOURCE_CODE_HEAP	6
#define MAX_SOURCE_CODE_HEAP	60

#define HEAP_MIN_FREE_SIZE			0x10000
#define MAIN_HEAP_MIN_FREE_SIZE		0x100000


typedef struct _KEY_PAIR
{
	DWORD FuncKeyCode;
	DWORD SecondKeyCode;
	bool operator == (const struct _KEY_PAIR& dest) const
	{
		if(FuncKeyCode==dest.FuncKeyCode && SecondKeyCode == dest.SecondKeyCode)
			return true;
		return false;
	}
}KEY_PAIR,*PKEY_PAIR;

typedef struct _HOTKEY_INFO
{
	char* KeyName;
	DWORD FuncKeyCode;
	DWORD SecondKeyCode;
	DWORD CommandID;
	DWORD TypeIndex;//是代表全局的 hotkey(针对于所有窗口的快捷键) 或者是 shortcat key （ 这个是针对每个窗口的快捷键盘 只有输入焦点在本窗口时才起作用的快捷键）
	char* Description;
}HOTKEY_INFO,*PHOTKEY_INFO;



typedef  struct _HOTKEY_CONF
{
	int Count;
	HOTKEY_INFO* pHotKeyInfo;
}HOTKEY_CONF;


extern HOTKEY_CONF gKeyConfig[5];
struct SYSER_OPTION
{
	DWORD	CRCCode;//效验和,当数据破坏或非法修改时,装入缺省
	int		iBigFont;
	int		iFollowMode;
	int		iShowStartSplash;
	int		iShowFullSym;
	int		iShowCCByte;
	int		iMouseSensitivity;
	int		iHistroyLines;
	//Source Debug
	int		iSourceCodeShowTips;
	int		iSourceCodeSyntaxColors;
	int		iSourceCodeShowLineNumbers;
	//Conect
	int		iConnectType;
	int		iComPort;
	//Advance
	int		iVideoDetectMode;
	int		iStackSizeK;
	int		iHardTimerEnable;
	WCHAR	szDebuggerFileName[MAX_FN_LEN];
	int		iStartWndWidth;
	int		iStartWndHeight;
	int		iMaxWndWidth;
	int		iMaxWndHeight;
	int		iHeapSizeM;
	int		iSourceCodeHeapSizeM;
	int		iKeyboardLayer;
	int		i3here;
	int		i1here;
	int		ifaults;
};

extern SYSER_OPTION OrgSyserOption;
extern SYSER_OPTION SyserOption;

extern STRegOptVal SyserOptVal[];
extern CHAR DefaultPEExportList[];
extern HOTKEY_INFO gDefaultHotkeyInfo[];
extern BYTE* gSyserHotKeyDriverBuffer;
extern int gSyserHotKeyDriverLen;

bool LoadSyserOption(PCSTR FileName,void*pOption,int Length);
bool SaveSyserOption(PCSTR FileName,void*pOption,int Length);
bool LoadSyserHotKeyOption(PCSTR FileName,void*pOption,ULSIZE BufLen,int* Length);
bool SaveSyserHotKeyOption(PCSTR FileName,void*pOption,int Length);
bool LoadSyserOptionDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int Length);
bool SaveSyserOptionDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int Length);
bool LoadSyserHotKeyDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int BufLen,int* Length);
bool SaveSyserHotKeyDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int Length);
bool SaveSyserHotKeyBufferDriver(void*pOption,int Length);
class CSyserOptionForm : public CWispOptionForm
{
public:
	CSyserOptionForm();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	bool InitWnd();
	void OptionApplyNotify();
};

#endif

