#include "StdAfx.h"
#include "SyserOption.h"
#include "../../Syser/Source/SyserResource.h"
HOTKEY_INFO gDefaultHotkeyInfo[]=
{
	{"ActiveHotKey",WISP_MOD_CTRL,WISP_VK_F12,0},
	{"Debug:Continue",WISP_VK_F5,0,EVENT_ID_CONTINUE},
	{"Debug:Return",WISP_VK_F6,0,EVENT_ID_RETURN},
	{"Debug:Step",WISP_VK_F8,0,EVENT_ID_STEP},
	{"Debug:Proceed",WISP_VK_F10,0,EVENT_ID_PROCEED},
	{"Debug:Step Branch",WISP_VK_F11,0,EVENT_ID_STEP_BRANCH},
	{"Debug:Break Point",WISP_MOD_CTRL,WISP_VK_F9,EVENT_ID_BREAK_POINT},
	{"Monitor:Register View",WISP_MOD_ALT,WISP_VK_G,EVENT_ID_REG_VIEW},
	{"Monitor:Data View",WISP_MOD_ALT,WISP_VK_D,EVENT_ID_DATA_VIEW_FORM},
	{"Monitor:Call Stack",WISP_MOD_ALT,WISP_VK_C,EVENT_ID_CALL_STACK},
	{"View:Toggle BookMark",WISP_MOD_CTRL,WISP_VK_K,EVENT_ID_BOOKMARK_TOGGLE},
	{"View:Previous BookMark",WISP_MOD_CTRL,WISP_VK_P,EVENT_ID_BOOKMARK_PREV},
	{"View:Next BookMark",WISP_MOD_CTRL,WISP_VK_N,EVENT_ID_BOOKMARK_NEXT},
	{"View:Clear BookMark",WISP_MOD_CTRL,WISP_VK_L,EVENT_ID_BOOKMARK_CLEAR},
	
	{NULL,0,0},
};

HOTKEY_INFO gCodeViewShortcatKeys[]=
{
	{"Toggle symbols display",0,WISP_VK_TAB,									EVENT_ID_TOGGLE_SYMBOL},
	{"Toggle full symbols display",WISP_MOD_CTRL,WISP_VK_TAB,				EVENT_ID_TOGGLE_FULL_SYMBOL},
	{"Set register value to next trace",0,WISP_VK_OEM_PLUS,					EVENT_ID_GETNEXTTRACE},
	{"Set register value to previous trace",0,WISP_VK_OEM_MINUS,				EVENT_ID_GETPREVTRACE},
	{"Set start address to previous position",0,WISP_VK_BACK,					EVENT_ID_PREV_POS},
	{"Set start address to next position",WISP_MOD_CTRL,WISP_VK_RETURN,	EVENT_ID_NEXT_POS},
	{"Follow to the destination of be selected instruction",0,WISP_VK_RETURN,	EVENT_ID_FOLLOW_TO_DESTINATION},
	{"Save the address of be selected instruction",WISP_MOD_SHIFT,WISP_VK_RETURN, EVENT_ID_SAVE_POS},
	{"Backwards disassemble code 1 byte",WISP_MOD_CTRL,WISP_VK_UP,			EVENT_ID_STARTADDRESS_DEC},
	{"Forwards disassemble code 1 byte",WISP_MOD_CTRL,WISP_VK_DOWN,		EVENT_ID_STARTADDRESS_INC},
	{"Insert/Remove Breakpoint",WISP_VK_F9,	0,								EVENT_ID_TOGGLE_BP},
	{"Run to here",WISP_VK_F7,0,												EVENT_ID_GOTO},
	{"Display code window #0",WISP_MOD_ALT,WISP_VK_1,						EVENT_ID_ACTIVE_CODEVIEW_0},
	{"Display code window #1",WISP_MOD_ALT,WISP_VK_2,						EVENT_ID_ACTIVE_CODEVIEW_1},
	{"Display code window #2",WISP_MOD_ALT,WISP_VK_3,						EVENT_ID_ACTIVE_CODEVIEW_2},
	{"Display code window #3",WISP_MOD_ALT,WISP_VK_4,						EVENT_ID_ACTIVE_CODEVIEW_3},
	{"Display code window #4",WISP_MOD_ALT,WISP_VK_5,						EVENT_ID_ACTIVE_CODEVIEW_4},
	{"Display code window #5",WISP_MOD_ALT,WISP_VK_6,						EVENT_ID_ACTIVE_CODEVIEW_5},
	{"Display code window #6",WISP_MOD_ALT,WISP_VK_7,						EVENT_ID_ACTIVE_CODEVIEW_6},
	{"Display code window #7",WISP_MOD_ALT,WISP_VK_8,						EVENT_ID_ACTIVE_CODEVIEW_7},
	{"Display code window #8",WISP_MOD_ALT,WISP_VK_9,						EVENT_ID_ACTIVE_CODEVIEW_8},
	{NULL,0,0},
};

HOTKEY_INFO gDataViewShortcatKeys[]=
{

	{"Follow to value of current caret position in data view",0,WISP_VK_RETURN,									EVENT_ID_FOLLOW_VALUE_TO_DATAVIEW},
	{"Follow to value of current caret position in code view",WISP_MOD_SHIFT,WISP_VK_RETURN,				EVENT_ID_FOLLOW_VALUE_TO_CODEVIEW},
	{"Copy the value of current caret position to clipboard",WISP_MOD_CTRL,WISP_VK_RETURN,					EVENT_ID_COPY_VALUE_TO_CLIPBOARD},
	{"Copy the address of current caret position to clipboard",WISP_MOD_ALT,WISP_VK_RETURN,				EVENT_ID_COPY_CARETPOSITION_TO_CLIPBOARD},
	{"Copy the date of be selected area with separator",WISP_MOD_CTRL,WISP_VK_X,					EVENT_ID_COPY_SEL_VALUE},
	{"Copy the date of be selected area without separator",WISP_MOD_SHIFT,WISP_VK_X,		EVENT_ID_COPY_SEL_VALUE_NO_SEPARATOR},
	{"Toggle the display mode of the address column",WISP_MOD_CTRL,WISP_VK_O,		EVENT_ID_TOGGLE_ADDRESS_MODE},
	{"Toggle dynamic and static address mode",WISP_MOD_CTRL,WISP_VK_M,		EVENT_ID_TOGGLE_FLOAT_MODE},
	{"Set start address to next position",0,WISP_VK_OEM_PLUS,		EVENT_ID_GOTO_NEXT_POS},
	{"Set start address to prev position",0,WISP_VK_OEM_MINUS,		EVENT_ID_GOTO_PREV_POS},
	{"Enable/Disable display offset ",WISP_MOD_CTRL,WISP_VK_S,		EVENT_ID_DATA_SHOW_OFFICE},
	{"Enable/Disable display toolbar ",WISP_MOD_CTRL,WISP_VK_T,		EVENT_ID_DATAVIEW_TOOLBAR},
	{"Copy the date of be selected area as C source code",WISP_MOD_CTRL,WISP_VK_Z,		EVENT_ID_COPY_SEL_VALUE_AS_C_SOURCE_CODE},	
	{"Display data window #0",WISP_MOD_ALT,WISP_VK_1,						EVENT_ID_ACTIVE_DATAVIEW_0},	
	{"Display data window #1",WISP_MOD_ALT,WISP_VK_2,						EVENT_ID_ACTIVE_DATAVIEW_1},	
	{"Display data window #2",WISP_MOD_ALT,WISP_VK_3,						EVENT_ID_ACTIVE_DATAVIEW_2},	
	{"Display data window #3",WISP_MOD_ALT,WISP_VK_4,						EVENT_ID_ACTIVE_DATAVIEW_3},	
	{"Display data window #4",WISP_MOD_ALT,WISP_VK_5,						EVENT_ID_ACTIVE_DATAVIEW_4},	
	{"Display data window #5",WISP_MOD_ALT,WISP_VK_6,						EVENT_ID_ACTIVE_DATAVIEW_5},	
	{"Display data window #6",WISP_MOD_ALT,WISP_VK_7,						EVENT_ID_ACTIVE_DATAVIEW_6},	
	{"Display data window #7",WISP_MOD_ALT,WISP_VK_8,						EVENT_ID_ACTIVE_DATAVIEW_7},	
	{"Display data window #8",WISP_MOD_ALT,WISP_VK_9,						EVENT_ID_ACTIVE_DATAVIEW_8},	
	{NULL,0,0},
};

HOTKEY_INFO gStackViewShortcatKeys[]=
{

	{"Follow to value of current caret position in data view",0,WISP_VK_RETURN,									EVENT_ID_SHOW_CODE},
	{"Follow to value of current caret position in code view",WISP_MOD_SHIFT,WISP_VK_RETURN,				EVENT_ID_SHOW_DATA},
	{"Copy the value of current caret position to clipboard",WISP_MOD_CTRL,WISP_VK_RETURN,					EVENT_ID_SHOW_DATA_BY_ADDRESS},
	{"Copy the address of current caret position to clipboard",WISP_MOD_ALT,WISP_VK_RETURN,				EVENT_ID_SHOW_CODE_BY_ADDRESS},

	{NULL,0,0},
};

HOTKEY_INFO gCpuViewShortcatKeys[]=
{

	{"Set start address of data window to which value eax register",WISP_MOD_ALT,WISP_VK_1,						EVENT_ID_SET_DATAVIEW_EAX},	
	{"Set start address of data window to which value ebx register",WISP_MOD_ALT,WISP_VK_2,						EVENT_ID_SET_DATAVIEW_EBX},	
	{"Set start address of data window to which value ecx register",WISP_MOD_ALT,WISP_VK_3,						EVENT_ID_SET_DATAVIEW_ECX},	
	{"Set start address of data window to which value edx register",WISP_MOD_ALT,WISP_VK_4,						EVENT_ID_SET_DATAVIEW_EDX},	
	{"Set start address of data window to which value esp register",WISP_MOD_ALT,WISP_VK_5,						EVENT_ID_SET_DATAVIEW_ESP},	
	{"Set start address of data window to which value ebp register",WISP_MOD_ALT,WISP_VK_6,						EVENT_ID_SET_DATAVIEW_EBP},	
	{"Set start address of data window to which value esi register",WISP_MOD_ALT,WISP_VK_7,						EVENT_ID_SET_DATAVIEW_ESI},	
	{"Set start address of data window to which value edi register",WISP_MOD_ALT,WISP_VK_8,						EVENT_ID_SET_DATAVIEW_EDI},	
	{"Set start address of data window to which value eip register",WISP_MOD_ALT,WISP_VK_9,						EVENT_ID_SET_DATAVIEW_EIP},	

	{"Set start address of code window to which value eax register",WISP_MOD_SHIFT,WISP_VK_1,						EVENT_ID_SET_CODEVIEW_EAX},	
	{"Set start address of code window to which value ebx register",WISP_MOD_SHIFT,WISP_VK_2,						EVENT_ID_SET_CODEVIEW_EBX},	
	{"Set start address of code window to which value ecx register",WISP_MOD_SHIFT,WISP_VK_3,						EVENT_ID_SET_CODEVIEW_ECX},	
	{"Set start address of code window to which value edx register",WISP_MOD_SHIFT,WISP_VK_4,						EVENT_ID_SET_CODEVIEW_EDX},	
	{"Set start address of code window to which value esp register",WISP_MOD_SHIFT,WISP_VK_5,						EVENT_ID_SET_CODEVIEW_ESP},	
	{"Set start address of code window to which value ebp register",WISP_MOD_SHIFT,WISP_VK_6,						EVENT_ID_SET_CODEVIEW_EBP},	
	{"Set start address of code window to which value esi register",WISP_MOD_SHIFT,WISP_VK_7,						EVENT_ID_SET_CODEVIEW_ESI},	
	{"Set start address of code window to which value edi register",WISP_MOD_SHIFT,WISP_VK_8,						EVENT_ID_SET_CODEVIEW_EDI},	
	{"Set start address of code window to which value eip register",WISP_MOD_SHIFT,WISP_VK_9,						EVENT_ID_SET_CODEVIEW_EIP},	
	{NULL,0,0},
};

HOTKEY_CONF gKeyConfig[5]=
{
	{sizeof(gDefaultHotkeyInfo)/sizeof(gDefaultHotkeyInfo[0]),gDefaultHotkeyInfo},
	{sizeof(gCodeViewShortcatKeys)/sizeof(gCodeViewShortcatKeys[0]),gCodeViewShortcatKeys},
	{sizeof(gDataViewShortcatKeys)/sizeof(gDataViewShortcatKeys[0]),gDataViewShortcatKeys},
	{sizeof(gStackViewShortcatKeys)/sizeof(gStackViewShortcatKeys[0]),gStackViewShortcatKeys},
	{sizeof(gCpuViewShortcatKeys)/sizeof(gCpuViewShortcatKeys[0]),gCpuViewShortcatKeys},
};

CHAR DefaultPEExportList[]=
{
	"\\SystemRoot\\system32\\Kernel32.dll\r\n"
	"\\SystemRoot\\system32\\GDI32.dll\r\n"
	"\\SystemRoot\\system32\\User32.dll\r\n"
	"\\SystemRoot\\system32\\AdvApi32.dll\r\n"
	"\\SystemRoot\\system32\\ws2_32.dll\r\n"
	"\\SystemRoot\\system32\\msvcrt.dll\r\n"
	"\\SystemRoot\\system32\\comdlg32.dll\r\n"
	"\\SystemRoot\\system32\\comctl32.dll\r\n"
	"\\SystemRoot\\system32\\ImageHlp.dll\r\n"
	"\\SystemRoot\\system32\\win32k.sys\r\n"
	"\\SystemRoot\\system32\\ntoskrnl.exe\r\n"
	"\\SystemRoot\\system32\\ntkrnlpa.exe\r\n"
	"\\SystemRoot\\system32\\ntkrnlmp.exe\r\n"
	"\\SystemRoot\\system32\\ntkrpamp.exe\r\n"
	"\\SystemRoot\\system32\\ntdll.dll\r\n"
	"\\SystemRoot\\system32\\hal.dll\r\n"
};

int	SyserOptionRef = 0;
/*
SDRemote
UnExe
SDWin32
*/
SYSER_OPTION OrgSyserOption=
{
	0,//CRCCode
	0,//iBigFont
	SYSER_FM_AUTOMATIC,//iFollowMode
	1,//iShowStartSplash
	0,//iShowFullSym
	0,//iShowCCByte
	10,//iMouseSensitivity
	500,//iHistroyLines
	//Source Debug
	1,//iSourceCodeShowTips;
	1,//iSourceCodeSyntaxColors;
	1,//iSourceCodeShowLineNumbers;
	//Conect
	SYSER_SERIAL_PORT_CONNECT,//iConnectType
	1,//iComPort
	//Advance
	SYSER_VDM_AUTO,		//iVideoDetectMode
	512,				//iStackSizeK
	1,					//iTimerIntEnable
	WSTR("SDWin32.dll"),//szDebuggerFileName
	1024,
	768,
	1024,
	768,
	12, //iHeapSizeM
	15,	//iSourceCodeHeapSizeM;
	0,  //默认值 0 是标准键盘, 1 是 Azerty 键盘，就是法文键盘
	2,//i3here;
	0,//i1here;
	1,//ifaults;
};

SYSER_OPTION SyserOption;

STRegOptVal SyserOptVal[]=
{
	{WSTR("iFollowMode"),					STOptVal::INT_VAL,	&SyserOption.iFollowMode		},
	{WSTR("iShowStartSplash"),				STOptVal::INT_VAL,	&SyserOption.iShowStartSplash	},
	{WSTR("iShowFullSym"),					STOptVal::INT_VAL,	&SyserOption.iShowFullSym		},
	{WSTR("iShowCCByte"),					STOptVal::INT_VAL,	&SyserOption.iShowCCByte		},
	{WSTR("iMouseSensitivity"),				STOptVal::INT_VAL,	&SyserOption.iMouseSensitivity	},
	//Source Debug
	{WSTR("iSourceCodeShowTips"),			STOptVal::INT_VAL,	&SyserOption.iSourceCodeShowTips},
	{WSTR("iSourceCodeSyntaxColors"),		STOptVal::INT_VAL,	&SyserOption.iSourceCodeSyntaxColors},
	{WSTR("iSourceCodeShowLineNumbers"),	STOptVal::INT_VAL,	&SyserOption.iSourceCodeShowLineNumbers},
	//Connect
	{WSTR("iConnectType"),					STOptVal::INT_VAL,	&SyserOption.iConnectType},
	{WSTR("iComPort"),						STOptVal::INT_VAL,	&SyserOption.iComPort},
	//Advance
	{WSTR("iHardTimerEnable"),				STOptVal::INT_VAL,	&SyserOption.iHardTimerEnable},
	{WSTR("szDebuggerFileName"),			STOptVal::STR_VAL,	&SyserOption.szDebuggerFileName,MAX_FN_LEN},
	{NULL}
};

#ifdef CODE_OS_NT_DRV

bool LoadSyserHotKeyDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int BufLen,int* Length)
{
	WCHAR SystemDriverPath[MAX_FN_LEN]=L"";
	OBJECT_ATTRIBUTES	oa;
	IO_STATUS_BLOCK		IOStatus;
	DWORD OpenMode,ShareMode;
	NTSTATUS Status;
	UNICODE_STRING UniName;
	FILE_STANDARD_INFORMATION StdInfo;
	WCHAR *NameBuf;
	LARGE_INTEGER Offset64;
	DWORD CRCCode;
	HANDLE hFile;
	*Length=0;
	if(GetSystemRootPath(RegistryServiceName,SystemDriverPath,sizeof(SystemDriverPath))==false)
		return false;
	TStrCat(SystemDriverPath,L"System32\\drivers\\");
	TStrCat(SystemDriverPath,FileName);
	RtlInitUnicodeString(&UniName,SystemDriverPath);
	InitializeObjectAttributes(&oa,&UniName,OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE,NULL,NULL);
	Status = ZwOpenFile(&hFile,GENERIC_READ,&oa,&IOStatus,FILE_SHARE_READ,FILE_RANDOM_ACCESS|FILE_NON_DIRECTORY_FILE|FILE_SYNCHRONOUS_IO_NONALERT|FILE_COMPLETE_IF_OPLOCKED);
	if(!NT_SUCCESS(Status))
		return false;
	Status = ZwQueryInformationFile(hFile,&IOStatus,&StdInfo,sizeof(FILE_STANDARD_INFORMATION),FileStandardInformation);
	if(!NT_SUCCESS(Status))
	{
		ZwClose(hFile);
		return false;
	}
	*Length=(int)StdInfo.EndOfFile.QuadPart;
	if(StdInfo.EndOfFile.QuadPart>BufLen)
	{
		ZwClose(hFile);
		return false;
	}
	Offset64.QuadPart=0;
	Status = ZwReadFile(hFile,NULL,NULL,NULL,&IOStatus,pOption,*Length,&Offset64,NULL);
	ZwClose(hFile);
	if(!NT_SUCCESS(Status))
		return false;
	CRCCode = GetCRCCode(RT_PBYTE(pOption,sizeof(CRCCode)),*Length-sizeof(DWORD));
	if(CRCCode==0 || CRCCode!=_GET_DWORD(pOption))
		return false;
	return true;
}
BYTE* gSyserHotKeyDriverBuffer=NULL;
int gSyserHotKeyDriverLen=0;
bool SaveSyserHotKeyBufferDriver(void*pOption,int Length)
{
	if(Length==0)
	{
		if(gSyserHotKeyDriverBuffer)
		{
			delete gSyserHotKeyDriverBuffer;
			gSyserHotKeyDriverBuffer=NULL;
		}
		gSyserHotKeyDriverLen=0;
		return true;

	}
	if(Length<=gSyserHotKeyDriverLen)
	{
		memcpy(gSyserHotKeyDriverBuffer,pOption,Length);
		gSyserHotKeyDriverLen=Length;
		return true;
	}
	if(gSyserHotKeyDriverBuffer)
		delete gSyserHotKeyDriverBuffer;
	gSyserHotKeyDriverLen=0;
	gSyserHotKeyDriverBuffer = new BYTE[Length];
	if(gSyserHotKeyDriverBuffer==NULL)
		return false;
	gSyserHotKeyDriverLen=Length;
	memcpy(gSyserHotKeyDriverBuffer,pOption,Length);
	return true;
}
bool SaveSyserHotKeyDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int Length)
{
	WCHAR SystemDriverPath[MAX_FN_LEN]=L"";
	OBJECT_ATTRIBUTES	oa;
	IO_STATUS_BLOCK		IOStatus;
	DWORD OpenMode,ShareMode;
	NTSTATUS Status;
	UNICODE_STRING UniName;
	FILE_STANDARD_INFORMATION StdInfo;
	WCHAR *NameBuf;
	LARGE_INTEGER Offset64;
	DWORD CRCCode;
	HANDLE hFile;
	if(GetSystemRootPath(RegistryServiceName,SystemDriverPath,sizeof(SystemDriverPath))==false)
		return false;
	TStrCat(SystemDriverPath,L"System32\\drivers\\");
	TStrCat(SystemDriverPath,FileName);
	RtlInitUnicodeString(&UniName,SystemDriverPath);
	InitializeObjectAttributes(&oa,&UniName,OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE,NULL,NULL);
	Status = ZwCreateFile(&hFile,GENERIC_WRITE,&oa,&IOStatus,NULL,FILE_ATTRIBUTE_NORMAL,FILE_SHARE_READ,
		FILE_OVERWRITE_IF,FILE_RANDOM_ACCESS|FILE_NON_DIRECTORY_FILE|FILE_SYNCHRONOUS_IO_NONALERT|FILE_COMPLETE_IF_OPLOCKED,NULL,0);
	if(!NT_SUCCESS(Status))
		return false;
	Offset64.QuadPart=0;
	_PUT_DWORD(pOption,GetCRCCode(RT_PBYTE(pOption,sizeof(DWORD)),Length-sizeof(DWORD)));
	Status = ZwWriteFile(hFile,NULL,NULL,NULL,&IOStatus,pOption,Length,&Offset64,NULL);
	ZwClose(hFile);
	if(!NT_SUCCESS(Status))
		return false;
	return true;
}

bool LoadSyserOptionDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int Length)
{
	WCHAR SystemDriverPath[MAX_FN_LEN]=L"";
	OBJECT_ATTRIBUTES	oa;
	IO_STATUS_BLOCK		IOStatus;
	DWORD OpenMode,ShareMode;
	NTSTATUS Status;
	UNICODE_STRING UniName;
	FILE_STANDARD_INFORMATION StdInfo;
	WCHAR *NameBuf;
	LARGE_INTEGER Offset64;
	DWORD CRCCode;
	HANDLE hFile;

	if(GetSystemRootPath(RegistryServiceName,SystemDriverPath,sizeof(SystemDriverPath))==false)
		return false;
	TStrCat(SystemDriverPath,L"System32\\drivers\\");
	TStrCat(SystemDriverPath,FileName);
	RtlInitUnicodeString(&UniName,SystemDriverPath);
	InitializeObjectAttributes(&oa,&UniName,OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE,NULL,NULL);
	Status = ZwOpenFile(&hFile,GENERIC_READ,&oa,&IOStatus,FILE_SHARE_READ,FILE_RANDOM_ACCESS|FILE_NON_DIRECTORY_FILE|FILE_SYNCHRONOUS_IO_NONALERT|FILE_COMPLETE_IF_OPLOCKED);
	if(!NT_SUCCESS(Status))
		return false;
	Status = ZwQueryInformationFile(hFile,&IOStatus,&StdInfo,sizeof(FILE_STANDARD_INFORMATION),FileStandardInformation);
	if(!NT_SUCCESS(Status))
	{
		ZwClose(hFile);
		return false;
	}
	Offset64.QuadPart = (ULONGLONG)Length;
	if(StdInfo.EndOfFile.QuadPart!=Offset64.QuadPart)
	{
		ZwClose(hFile);
		return false;
	}
	Offset64.QuadPart=0;
	Status = ZwReadFile(hFile,NULL,NULL,NULL,&IOStatus,pOption,Length,&Offset64,NULL);
	ZwClose(hFile);
	if(!NT_SUCCESS(Status))
		return false;
	CRCCode = GetCRCCode(RT_PBYTE(pOption,sizeof(CRCCode)),Length-sizeof(DWORD));
	if(CRCCode==0 || CRCCode!=_GET_DWORD(pOption))
		return false;
	return true;
}

bool SaveSyserOptionDriver(WCHAR* RegistryServiceName,WCHAR* FileName,void*pOption,int Length)
{
	WCHAR SystemDriverPath[MAX_FN_LEN]=L"";
	OBJECT_ATTRIBUTES	oa;
	IO_STATUS_BLOCK		IOStatus;
	DWORD OpenMode,ShareMode;
	NTSTATUS Status;
	UNICODE_STRING UniName;
	FILE_STANDARD_INFORMATION StdInfo;
	WCHAR *NameBuf;
	LARGE_INTEGER Offset64;
	DWORD CRCCode;
	HANDLE hFile;
	if(GetSystemRootPath(RegistryServiceName,SystemDriverPath,sizeof(SystemDriverPath))==false)
		return false;
	TStrCat(SystemDriverPath,L"System32\\drivers\\");
	TStrCat(SystemDriverPath,FileName);
	RtlInitUnicodeString(&UniName,SystemDriverPath);
	InitializeObjectAttributes(&oa,&UniName,OBJ_KERNEL_HANDLE|OBJ_CASE_INSENSITIVE,NULL,NULL);
	Status = ZwCreateFile(&hFile,GENERIC_WRITE,&oa,&IOStatus,NULL,FILE_ATTRIBUTE_NORMAL,FILE_SHARE_READ,
			FILE_OVERWRITE_IF,FILE_RANDOM_ACCESS|FILE_NON_DIRECTORY_FILE|FILE_SYNCHRONOUS_IO_NONALERT|FILE_COMPLETE_IF_OPLOCKED,NULL,0);
	if(!NT_SUCCESS(Status))
		return false;
	Offset64.QuadPart=0;
	_PUT_DWORD(pOption,GetCRCCode(RT_PBYTE(pOption,sizeof(DWORD)),Length-sizeof(DWORD)));
	Status = ZwWriteFile(hFile,NULL,NULL,NULL,&IOStatus,pOption,Length,&Offset64,NULL);
	ZwClose(hFile);
	if(!NT_SUCCESS(Status))
		return false;
	return true;
}
#endif //CODE_OS_NT_DRV

bool LoadSyserOption(PCSTR FileName,void*pOption,int Length)
{
	DWORD CRCCode;
	CImageFile CfgFile;
	if(CfgFile.Open(FileName)==false)
		return false;
	if(CfgFile.m_FileSize!=Length)
		goto ErrorExit;
	if(CfgFile.ReadFile(pOption,Length)==false)
		goto ErrorExit;
	CRCCode = GetCRCCode(RT_PBYTE(pOption,sizeof(CRCCode)),Length-sizeof(DWORD));
	if(CRCCode==0 || CRCCode !=_GET_DWORD(pOption))
		goto ErrorExit;
	CfgFile.Close();
	return true;
ErrorExit:
	CfgFile.Close();
	return false;
}

bool SaveSyserOption(PCSTR FileName,void*pOption,int Length)
{
	bool Result;
	CImageFile CfgFile;
	if(CfgFile.Create(FileName)==false)
		return false;
	Result = true;
	_PUT_DWORD(pOption,GetCRCCode(RT_PBYTE(pOption,sizeof(DWORD)),Length-sizeof(DWORD)));
	if(CfgFile.WriteFile(pOption,Length)==false)
		Result = false;
	CfgFile.Close();
	return Result;
}

bool LoadSyserHotKeyOption(PCSTR FileName,void*pOption,ULSIZE BufLen,int* Length)
{
	DWORD CRCCode;
	CImageFile CfgFile;
	if(CfgFile.Open(FileName)==false)
		return false;
	if(CfgFile.m_FileSize>BufLen)
		goto ErrorExit;
	*Length=CfgFile.m_FileSize;
	if(CfgFile.ReadFile(pOption,CfgFile.m_FileSize)==false)
		goto ErrorExit;
	CRCCode = GetCRCCode(RT_PBYTE(pOption,sizeof(CRCCode)),CfgFile.m_FileSize-sizeof(DWORD));
	if(CRCCode==0 || CRCCode !=_GET_DWORD(pOption))
		goto ErrorExit;
	CfgFile.Close();
	return true;
ErrorExit:
	CfgFile.Close();
	return false;
}

bool SaveSyserHotKeyOption(PCSTR FileName,void*pOption,int Length)
{
	bool Result;
	CImageFile CfgFile;
	if(CfgFile.Create(FileName)==false)
		return false;
	Result = true;
	_PUT_DWORD(pOption,GetCRCCode(RT_PBYTE(pOption,sizeof(DWORD)),Length-sizeof(DWORD)));
	if(CfgFile.WriteFile(pOption,Length)==false)
		Result = false;
	CfgFile.Close();
	return Result;
}

//////////////////////////////////////////////////////////////////////////////
//Option List用于Syser Win32 Debugger
WISP_OPTION_ITEM SyserWin32DebuggerOption[]=
{
	{WSTR("Show Full Symbol (Include Module Name)"),OPTION_SELECT_INT,&SyserOption.iShowFullSym,sizeof(int),CWispOptionForm::m_NoYesList,NULL,&SyserOptionRef},
	{WSTR("Mouse Sensitivity [1 - 30]"),OPTION_INT,&SyserOption.iMouseSensitivity,sizeof(int),NULL,TValueTest<int,1,30>,&SyserOptionRef},
	{WSTR("Default Debugger Module"),OPTION_STRING,&SyserOption.szDebuggerFileName,MAX_FN_LEN,NULL,NULL,&SyserOptionRef},
	{NULL}
};

WISP_OPTION_ITEM SyserSourceDebuggerOption[]=
{
	{WSTR("Syntax Color"),OPTION_SELECT_INT,&SyserOption.iSourceCodeSyntaxColors,sizeof(int),CWispOptionForm::m_NoYesList,NULL,&SyserOptionRef},
	{WSTR("Show Tips"),OPTION_SELECT_INT,&SyserOption.iSourceCodeShowTips ,sizeof(int),CWispOptionForm::m_NoYesList,NULL,&SyserOptionRef},
	{WSTR("Show Line Numbers"),OPTION_SELECT_INT,&SyserOption.iSourceCodeShowLineNumbers ,sizeof(int),CWispOptionForm::m_NoYesList,NULL,&SyserOptionRef},
	{NULL}
};

WISP_OPTION_ITEM SyserMainOption[]=
{
	{WSTR("Debugger"),OPTION_TITLE,SyserWin32DebuggerOption},
	{WSTR("Source Code Debugger"),OPTION_TITLE,SyserSourceDebuggerOption},
	{NULL}
};

WISP_MSG_MAP_BEGIN(CSyserOptionForm)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispOptionForm)


bool CSyserOptionForm::OnFormCreate(WISP_MSG*pMsg)
{
	CWispOptionForm::OnFormCreate(pMsg);
	FillOptionTreeValue();
	Resize(m_WindowRect.cx+m_BorderSize*2,m_WindowRect.cy+m_CaptionRect.cy+m_BorderSize*2);
	SetWindowText(WISP_STR("Option"));
	return false;
}

CSyserOptionForm::CSyserOptionForm()
{
	m_pOptionItem = SyserMainOption;
}

bool CSyserOptionForm::InitWnd()
{
	m_Style|=WISP_WS_FRAME;
	return CWispOptionForm::InitWnd();
}

void CSyserOptionForm::OptionApplyNotify()
{
	char szCfgFN[MAX_FN_LEN];
	if(SyserOptionRef)
	{
		SyserOptionRef = 0;
		GetModulePath(szCfgFN);
		TStrCat(szCfgFN,"Syser.cfg");
		SaveSyserOption(szCfgFN,&SyserOption,sizeof(SyserOption));
	}
}



