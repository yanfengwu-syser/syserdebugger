#ifndef _SYSER_DEFINE_H_
#define _SYSER_DEFINE_H_

#define SYSER_VERSION				"1.97"

#define	MAIN_WND_NAME				"Syser : Active Hotkey [Ctrl+F12]"

#ifdef CODE_OS_WIN
#define WM_SYSER_APP_RELOAD_CFG		(WM_USER+0x101)
#endif 

#define SDP_NULL					0x00000000
#define SDP_AUTO_UNLOAD_SDS			0x00000001//进程退出时卸载相关的SDS
///////////////////////////////////////////////
//上层使用
#define SDP_LOAD_SDS				0x00010000
#define SDP_LOAD_DEP_SDS			0x00020000
///////////////////////////////////////////////
typedef struct _SYSER_DEBUG_PROCESS
{
	DWORD Style;
	DWORD ProcessID;
	char ExeFullPathName[MAX_PATH];
	char SymbolFileName[MAX_PATH];
}SYSER_DEBUG_PROCESS,*PSYSER_DEBUG_PROCESS;

typedef struct _SYSER_DEBUG_DRIVER
{
	DWORD Style;
	char DriverPathName[MAX_PATH];
	char SymbolFileName[MAX_PATH];
}SYSER_DEBUG_DRIVER,*PSYSER_DEBUG_DRIVER;

typedef struct _SYSER_LOAD_IDA_MAPFILE
{
	char ModuleName[MAX_PATH];
	char IDAMapFile[MAX_PATH];
}SYSER_LOAD_IDA_MAPFILE,*PSYSER_LOAD_IDA_MAPFILE;

typedef struct _SYSER_PROCESS_MEMORY_READ_WRITE
{
	DWORD ProcessID;
	void* Address;
}SYSER_READ_PROCESS_MEMORY,*PSYSER_READ_PROCESS_MEMORY,SYSER_WRITE_PROCESS_MEMORY,*PSYSER_WRITE_PROCESS_MEMORY;

typedef struct _SYSER_CORRECT_VIDEO_PARAM
{
	void*	FrameBuffer;
	int		BufferSize;
	int		Pitch;
	int		Width;
	int		Height;
	int		Bpp;
	UINT	PID;
}SYSER_CORRECT_VIDEO_PARAM,*PSYSER_CORRECT_VIDEO_PARAM;

typedef struct _SYSER_FRAME_BUFFER
{
	int		Width;
	int		Height;
	int		Bpp;
	void*	BaseBuffer;
	void*	Buffer;
	int		LineDistance;
	int		PixelFormat;
}SYSER_FRAME_BUFFER,*PSYSER_FRAME_BUFFER;

typedef struct _SYSER_LOAD_SYMBOL_MODULE
{
	char SymbolModuleName[MAX_PATH];
}SYSER_LOAD_SYMBOL_MODULE,*PSYSER_LOAD_SYMBOL_MODULE;

typedef struct _SYSER_UNLOAD_SYMBOL_MODULE
{
	char SymbolModuleName[MAX_PATH];
}SYSER_UNLOAD_SYMBOL_MODULE,*PSYSER_UNLOAD_SYMBOL_MODULE;
typedef struct _SYSER_QUER_SDS
{
	DWORD PECheckSum;
	DWORD TimeDateStamp;
	char FileName[MAX_PATH];
}SYSER_QUER_SDS,*PSYSER_QUER_SDS;


class CSDSModule;

typedef struct stSourceDebugCallStack
{
	DWORD ESP;
	DWORD EIP;
	DWORD EBP;
	DWORD ReturnAddress;
}SOURCEDEBUGCALLSTACK;

typedef TList<SOURCEDEBUGCALLSTACK> SOUCEDEBUGCALLSTACKLIST;

struct SYSER_COMMENT_MODULE_HEAD
{
	DWORD	Signature;//"CMT"
	DWORD	DateStamp;
	int		Count;
	CHAR	szDesFileName[4];
};


enum CALL_TYPE
{
	TYPE_STDCALL,
	TYPE_CDECL,
	TYPE_FASTCALL,
	TYPE_INLINE,
};

struct API_FUNC_DEF
{
	CStrA Return;
	TList<CStrA> ParamList;	
	CALL_TYPE CallType;
	int Load(ALTFileStream&Stream)
	{
		int TotalLength,Length;
		TotalLength = 0;

		Length=Return.Load(Stream);
		if(Length==0)
			return 0;
		TotalLength+=Length;

		Length=ParamList.Load(Stream);
		if(Length==0)
			return 0;
		TotalLength+=Length;

		Length=Stream.Gets(&CallType,sizeof(CallType));
		if(Length!=sizeof(CallType))
			return 0;
		TotalLength+=Length;

		return TotalLength;
	}
	int Save(ALTFileStream&Stream)
	{
		int Length=Return.Save(Stream);
		Length+=ParamList.Save(Stream);
		Length+=Stream.Puts(&CallType,sizeof(CallType)); 
		return Length;
	}
};

typedef TMap<CIStrA,API_FUNC_DEF>	CAPIMap;

#define DBG_MSG_WBUF_LEN					0x1000
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IOCTL_SYSER_DEBUG_PROCESS			CTL_CODE(FILE_DEVICE_UNKNOWN,0x0001,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_DEBUG_DRIVER			CTL_CODE(FILE_DEVICE_UNKNOWN,0x0002,METHOD_BUFFERED,FILE_ANY_ACCESS)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IOCTL_SYSER_RELOAD_CONFIG			CTL_CODE(FILE_DEVICE_UNKNOWN,0x0010,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_RELOAD_COLOR_CONFIG		CTL_CODE(FILE_DEVICE_UNKNOWN,0x0011,METHOD_BUFFERED,FILE_ANY_ACCESS)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IOCTL_SYSER_SET_CLIP_BOARD			CTL_CODE(FILE_DEVICE_UNKNOWN,0x0021,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_GET_CLIP_BOARD			CTL_CODE(FILE_DEVICE_UNKNOWN,0x0022,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_SCREEN_SHOT				CTL_CODE(FILE_DEVICE_UNKNOWN,0x0023,METHOD_BUFFERED,FILE_ANY_ACCESS)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IOCTL_SYSER_CORRECT_VIDEO_PARAM		CTL_CODE(FILE_DEVICE_UNKNOWN,0x0030,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_LOAD_SDS				CTL_CODE(FILE_DEVICE_UNKNOWN,0x0031,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_UNLOAD_SDS				CTL_CODE(FILE_DEVICE_UNKNOWN,0x0032,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_LOAD_EXPORT_SYMBOL		CTL_CODE(FILE_DEVICE_UNKNOWN,0x0033,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_LOAD_IDA_MAPFILE		CTL_CODE(FILE_DEVICE_UNKNOWN,0x0034,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_QUERY_SDS				CTL_CODE(FILE_DEVICE_UNKNOWN,0x0035,METHOD_BUFFERED,FILE_ANY_ACCESS)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IOCTL_SYSER_SAVE_HISTROYS			CTL_CODE(FILE_DEVICE_UNKNOWN,0x0041,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYSER_SAVE_COMMENTS			CTL_CODE(FILE_DEVICE_UNKNOWN,0x0042,METHOD_BUFFERED,FILE_ANY_ACCESS)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IOCTL_SYSER_BOOT_GET_FRAME_BUFFER	CTL_CODE(FILE_DEVICE_UNKNOWN,0x0100,METHOD_BUFFERED,FILE_ANY_ACCESS)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum
{
	SYSER_MAIN_HEAP = 0,
	SYSER_SCREEN_HEAP,
	SYSER_SOURCE_DEBUG_HEAP
};

#define DERIVER_GROUP_NAME "Syser"
#define DRIVER_NAME "Syser"
#define DRIVER_RING3_NAME "\\\\.\\Syser"

#endif
