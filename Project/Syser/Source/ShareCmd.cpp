#include "StdAfx.h"
#include "Syser.h"
#include "ShareCmd.h"
#include "OSData.h"
#include "ErrorCodeTable.h"
#include "NtstatStr.h"
#include "SystemIoctl.h"
#include "BugCheckCode.h"
#include "StringReference.h"
//#include <winioctl.h>
SYSER_CMD_ENTRY	ShareCmdTable[]=
{
	{WSTR("resize"),		WSTR("resize syser windows"),										window_resize_command},
	{WSTR("lines"),			WSTR("Change the number of lines for the syser display."),			lines_command},
	{WSTR("width"),			WSTR("Set the number of display columns in the syser window."),		width_command},
	{WSTR("ioctl"),			WSTR("Decodes the IOCTL and FSCTL codes into readable English."),	ioctl_command},
	{WSTR("ntstatus"),		WSTR("Display header-defined mnemonics for NTSTATUS error codes."),	ntstatus_command},
	{WSTR("winerror"),		WSTR("Display header-defined mnemonics for Win32 error codes."),	errorcode_command},
	{WSTR("bugcheckcode"),	WSTR("Display Bug Check Code mnemonics for windows."),				bugcheckcode_command},
	{WSTR("wmsg"),			WSTR("Display the names and message numbers of Windows messages."),	wmsg_command},
	{WSTR("zap"),			WSTR("Replace an embedded INT 1 or INT 3 with a NOP instruction."),	zap_command},	
	{WSTR("file"),			WSTR("List source code file"),										file_command},
	{WSTR("watch"),			WSTR("Add source code variable watch"),								watch_source_command},
	{WSTR("table"),			WSTR("List source code module"),									table_source_command},
	{WSTR("crc16"),			WSTR("Calculate crc16 value with memory region."),					crc_command},
	{WSTR("crc32"),			WSTR("Calculate crc32 value with memory region."),					crc_command},
	{WSTR("crc16-ccitt"),	WSTR("Calculate crc-ccitt value with memory region."),				crc_command},
	{NULL,NULL,NULL}
};
typedef struct _IOCTL_STR
{
	unsigned int TransferType:2;
	unsigned int FunctionCode:11;
	unsigned int Custom:1;
	unsigned int RequiredAccess:2;
	unsigned int DeviceType:15;
	unsigned int Common:1;
}IOCTL_STR,*PIOCTL_STR;

int table_source_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	WCHAR wFileName[512];
	CSDSModuleMap::IT BeginIT,EndIT;
	int Count;
	BeginIT=gpSyser->m_SyserUI.m_SDSModuleMap.Begin();
	EndIT=gpSyser->m_SyserUI.m_SDSModuleMap.End();
	Count = gpSyser->m_SyserUI.m_SDSModuleMap.Count();
	if(Count==0 || argc >2)
	{
		OUTPUT(WSTR("Error : not found symbol module.\n"));
		return 1;
	}
	if(argc==1)
	{
		for(;BeginIT!=EndIT;BeginIT++)
		{
			TStrCpy(wFileName,(*BeginIT).GetSymbolModuleName());
			OUTPUT(WSTR("%s\n"),wFileName);
		}
		return 0;
	}
	for(;BeginIT!=EndIT;BeginIT++)
	{
		TStrCpy(wFileName,(*BeginIT).GetSymbolModuleName());
		if(TStrICmp(wFileName,argv[1])==0)
		{
			gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.SetActiveModule(&(*BeginIT));
			gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
			break;
		}		
	}	
	return 0;
}

int watch_source_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	if(argc<2)
	{
		OUTPUT(WSTR("Error : watch variablename [variablename2 ..].\n"));
		return 1;
	}
	if(CUR_SOURCE_SDSMODULE==NULL)
	{
		OUTPUT(WSTR("Error : not found symbol module.\n"));
		return 1;
	}
	for(int i = 1; i < argc;i++)
	{
#ifdef CODE_OS_NT_DRV
		if(gpSyser->m_SysInfo.m_bSNPass==false && SOURC_DEBUGE_FRAME_WND.m_SourceVariableWatchWnd.GetItemCount(NULL,false)>1)
		{
			SOURC_DEBUGE_FRAME_WND.m_SourceVariableWatchWnd.m_pWispBase->MsgBox(WSTR("Unregister version limited"),WSTR("Warning"),WISP_MB_OK);
			return 0;
		}
#endif
		SOURC_DEBUGE_FRAME_WND.m_SourceVariableWatchWnd.AddWatchByName(argv[i],NULL);
		gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
	}
	return 0;
}
int file_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	CSDSModule* pSDSModule;
	PSDSOURCEFILEID SourceID;
	char FileName[512];
	char* pModuleName;
	WCHAR wFileName[512];
	pSDSModule=CUR_SOURCE_SDSMODULE;
	if(pSDSModule==NULL)
	{
		OUTPUT(WSTR("Error : not found symbol module.\n"));
		return 1;
	}
	if(argc==1)
	{
		DWORD SourceFileNum;
		SourceID = pSDSModule->GetSourceFileList(&SourceFileNum);
		if(SourceID==NULL)
		{
			OUTPUT(WSTR("Error : not found source file.\n"));
			return 1;
		}
		for(DWORD i = 0; i < SourceFileNum;i++)
		{			
			if(SourceID[i].FileLen==0)
				continue;
			pModuleName=TStrRChr(SourceID[i].uName.Name,'\\');
			if(pModuleName)
			{
				pModuleName++;
				TStrCpy(wFileName,pModuleName);
				OUTPUT(WSTR("%s\n"),wFileName);
			}
		}
		return 0;
	}

	for(int i = 1; i < argc;i++)
	{
		TStrCpy(FileName,argv[i]);
		SourceID = pSDSModule->GetSourceFileByName(FileName);
		if(SourceID==NULL)
			continue;
		gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
		SOURC_DEBUGE_FRAME_WND.ShowSourceFile(pSDSModule,SourceID->FileID,0);
		gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SOURCE_EXPLORER_VIEW);
	}
	return 0;
}
int ioctl_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	char* DeviceTypeName[]={
		NULL,
		"BEEP",
		"CD_ROM",
		"CD_ROM_FILE_SYSTEM",
		"CONTROLLER",
		"DATALINK",
		"DFS",
		"DISK",
		"DISK_FILE_SYSTEM",
		"FILE_SYSTEM",
		"INPORT_PORT",
		"KEYBOARD",
		"MAILSLOT",
		"MIDI_IN",
		"MIDI_OUT",
		"MOUSE",
		"MULTI_UNC_PROVIDER",
		"NAMED_PIPE",
		"NETWORK",
		"NETWORK_BROWSER",
		"NETWORK_FILE_SYSTEM",
		"NULL",
		"PARALLEL_PORT",
		"PHYSICAL_NETCARD",
		"PRINTER",
		"SCANNER",
		"SERIAL_MOUSE_PORT",
		"SERIAL_PORT",
		"SCREEN",
		"SOUND",
		"STREAMS",
		"TAPE",
		"TAPE_FILE_SYSTEM",
		"TRANSPORT",
		"UNKNOWN",
		"VIDEO",
		"VIRTUAL_DISK",
		"WAVE_IN",
		"WAVE_OUT",
		"8042_PORT",
		"NETWORK_REDIRECTOR",
		"BATTERY",
		"BUS_EXTENDER",
		"MODEM",
		"VDM",
		"MASS_STORAGE",
		"SMB",
		"KS",
		"CHANGER",
		"SMARTCARD",
		"ACPI",
		"DVD",
		"FULLSCREEN_VIDEO",
		"DFS_FILE_SYSTEM",
		"DFS_VOLUME",
		"SERENUM",
		"TERMSRV",
		"KSEC",
		"FIPS",
		"INFINIBAND",
	};
	DWORD ControlCode;
	int i;
	bool bTitle=false;
	WCHAR DeviceTypeNameBuf[50];
	PIOCTL_STR pIoctl;
	int k;
	if(argc==1)
	{
		for( k =0; gSysIoctl[k].Name;k++)
		{
			
			OUTPUT(WSTR("%08X "),gSysIoctl[k].Code);
			TStrCpy(DeviceTypeNameBuf,gSysIoctl[k].Name);
			OUTPUT(WSTR("FILE_DEVICE_"));
			OUTPUT(DeviceTypeNameBuf);
			OUTPUT(WSTR("\n"));
			
		}
		//OUTPUT(WSTR("IOCTL ctl-code\n"));
		return 1;
	}
	pIoctl = (PIOCTL_STR)&ControlCode;
	for(i = 1; i < argc; i++)
	{
		if(CALCEXP(argv[i],&ControlCode)==false)
		{
			char tmpname[128]="FILE_DEVICE_";
			
			for(k = 0; gSysIoctl[k].Name;k++)
			{
				strcpy(tmpname+12,gSysIoctl[k].Name);
				if(TStrIStr(tmpname,argv[i]))
				{
					ControlCode=gSysIoctl[k].Code;
					goto local_001;
				}
			}
			continue;
		}
local_001:

		OUTPUT(WSTR("    Control Code:  %08x "),ControlCode);
		for(k =0; gSysIoctl[k].Name;k++)
		{
			if(gSysIoctl[k].Code==ControlCode)
			{
				TStrCpy(DeviceTypeNameBuf,gSysIoctl[k].Name);
				OUTPUT(DeviceTypeNameBuf);
				break;
			}
		}
		OUTPUT(WSTR("\n"));
		if(pIoctl->Common==0)
		{
			if(pIoctl->DeviceType>0 && pIoctl->DeviceType<=0x3b)
			{
				TStrCpy(DeviceTypeNameBuf,"FILE_DEVICE_");
				TStrCat(DeviceTypeNameBuf,DeviceTypeName[pIoctl->DeviceType]);
				OUTPUT(WSTR("    Device Type:   %s"),DeviceTypeNameBuf);
			}else
				OUTPUT(WSTR("    Device Type:   %x(Microsoft reserved)"),pIoctl->DeviceType);
			
		}else
		{
			OUTPUT(WSTR("    Device Type:   %x(vendor-assigned) "),pIoctl->DeviceType|0x8000);
		}
		OUTPUT(WSTR("\n    Function:      "));
		if(pIoctl->Custom==0)
		{
			OUTPUT(WSTR("0x%x (%d)(Microsoft Reserved) "),pIoctl->FunctionCode,pIoctl->FunctionCode);
		}else
		{
			OUTPUT(WSTR("0x%x (%d) "),pIoctl->FunctionCode|0x800,pIoctl->FunctionCode|0x800);
		}
		OUTPUT(WSTR("\n    Method:        "));
		switch(pIoctl->TransferType)
		{
		case METHOD_BUFFERED:  
			OUTPUT(WSTR("METHOD_BUFFERED "));
			break;
		case METHOD_IN_DIRECT:   
			OUTPUT(WSTR("METHOD_IN_DIRECT "));
			break;
		case METHOD_OUT_DIRECT:  
			OUTPUT(WSTR("METHOD_OUT_DIRECT "));
			break;
		case METHOD_NEITHER:     
			OUTPUT(WSTR("METHOD_NEITHER "));
			break;
		}
		OUTPUT(WSTR("\n    Access:        "));
		switch(pIoctl->RequiredAccess)
		{
		case FILE_ANY_ACCESS:  
			OUTPUT(WSTR("FILE_ANY_ACCESS "));
			break;
		case FILE_READ_ACCESS:   
			OUTPUT(WSTR("FILE_READ_ACCESS "));
			break;
		case FILE_WRITE_ACCESS:  
			OUTPUT(WSTR("FILE_WRITE_ACCESS "));
			break;
		case FILE_WRITE_ACCESS|FILE_READ_ACCESS:     
			OUTPUT(WSTR("FILE_READ_ACCESS|FILE_WRITE_ACCESS "));
			break;
		}
		OUTPUT(WSTR("\n"));
	}
	return 1;
}
int wmsg_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	int i,j;
	DWORD dwIndex,Count=0;

	WCHAR Buf[256];
	if(argc==1)
	{
		for(i = 0; stMsgList[i].MsgName; i++)
		{
			Count++;
			TStrCpy(Buf,stMsgList[i].MsgName);
			OUTPUT(WSTR("%04x  %s\n"),stMsgList[i].MsgNumber,Buf);	
		}
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);
		return 0;
	}
	for(i = 1; i < argc;i++)
	{
		if(CALCEXP(argv[i],&dwIndex))
		{
			for(j = 0; stMsgList[j].MsgName; j++)
			{
				if(stMsgList[j].MsgNumber==dwIndex)
				{
					TStrCpy(Buf,stMsgList[j].MsgName);
					OUTPUT(WSTR("%04x  %<b>%s\n"),stMsgList[j].MsgNumber,Buf);
					Count++;
					//break;
				}
			}
		}
		else
		{
			for(j = 0; stMsgList[j].MsgName; j++)
			{
				if(TStrNICmp(argv[i], stMsgList[j].MsgName,TStrLen(argv[i]))==0)
				{
					TStrCpy(Buf,stMsgList[j].MsgName);
					OUTPUT(WSTR("%<b>%04x  %<1>%s\n"),stMsgList[j].MsgNumber,Buf);
					Count++;
				}
			}
		}
	}	
	if(Count)
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);
	return 0;
}

int zap_command(int argc, WCHAR* argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	WORD wOrgInstr;
	if(argc != 1)
		return -1;
	X86_CPU_REG_PTR pReg;
	pSyser->m_pDebugger->GetX86RegPtr(&pReg);
	
	pSyser->m_pDebugger->ReadMemory(*pReg.pEIP-2,&wOrgInstr,2);
	if(wOrgInstr==0x1cd || wOrgInstr==0x3cd)
	{
		wOrgInstr=0x9090;
		pSyser->m_pDebugger->WriteMemory(*pReg.pEIP-2,&wOrgInstr,2);
	}
	else
	{
		if((wOrgInstr&0xff00)==0xcc00 ||(wOrgInstr&0xff00)==0xf100)
		{
			wOrgInstr=0x9090;
			pSyser->m_pDebugger->WriteMemory(*pReg.pEIP-1,&wOrgInstr,1);
		}else
		{
			OUTPUT(WSTR("NO embedded INT 1 or INT 3\n"));
		}
	}
	UPDATE_CONTEXT();
	return 0;
}
int errorcode_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	int i,j;
	DWORD dwIndex,Count=0;
	WCHAR Buf[400];
	if(argc==1)
	{
		for(i = 0; ErrorCodes[i].Name; i++)
		{
			Count++;
			TStrCpy(Buf,ErrorCodes[i].Name);
			OUTPUT(WSTR("0X%08x  %s\n"),ErrorCodes[i].Code,Buf);	
			//TStrCpy(Buf,ErrorCodes[i].Description);
			//OUTPUT(WSTR("%s\n"),Buf);
		}
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);
		return 0;
	}
	for(i = 1; i < argc;i++)
	{
		if(CALCEXP(argv[i],&dwIndex))
		{
			for(j = 0; ErrorCodes[j].Name; j++)
			{
				if(ErrorCodes[j].Code==dwIndex)
				{
					TStrCpy(Buf,ErrorCodes[j].Name);
					
					OUTPUT(WSTR("0X%08x  %<b>%s "),ErrorCodes[j].Code,Buf);
					TStrCpy(Buf,ErrorCodes[j].Description);
					OUTPUT(WSTR("\n"),Buf);
					Count++;
					//break;
				}
			}
		}
		else
		{
			for(j = 0; ErrorCodes[j].Name; j++)
			{
				if(TStrNICmp(argv[i], ErrorCodes[j].Name,TStrLen(argv[i]))==0)
				{
					TStrCpy(Buf,ErrorCodes[j].Name);
					OUTPUT(WSTR("%<b>0X%08x  %<1>%s "),ErrorCodes[j].Code,Buf);
					TStrCpy(Buf,ErrorCodes[j].Description);
					OUTPUT(WSTR("\n"),Buf);
					Count++;
				}
			}
		}
	}	
	if(Count)
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);

	return 0;
}

int bugcheckcode_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	int i,j;
	DWORD dwIndex,Count=0;
	WCHAR Buf[400];
	if(argc==1)
	{
		for(i = 0; gBugCheckCode[i].Name; i++)
		{
			Count++;
			TStrCpy(Buf,gBugCheckCode[i].Name);
			OUTPUT(WSTR("0X%08x  %s\n"),gBugCheckCode[i].BucCheckCode,Buf);	
		}
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);
		return 0;
	}
	for(i = 1; i < argc;i++)
	{
		if(CALCEXP(argv[i],&dwIndex))
		{
			for(j = 0; gBugCheckCode[j].Name; j++)
			{
				if(gBugCheckCode[j].BucCheckCode==dwIndex)
				{
					TStrCpy(Buf,gBugCheckCode[j].Name);

					OUTPUT(WSTR("0X%08x  %<b>%s "),gBugCheckCode[j].BucCheckCode,Buf);
					TStrCpy(Buf,gBugCheckCode[j].Name);
					OUTPUT(WSTR("\n"),Buf);
					Count++;
					//break;
				}
			}
		}
		else
		{
			for(j = 0; gBugCheckCode[j].Name; j++)
			{
				if(TStrNICmp(argv[i], gBugCheckCode[j].Name,TStrLen(argv[i]))==0)
				{
					TStrCpy(Buf,gBugCheckCode[j].Name);
					OUTPUT(WSTR("%<b>0X%08x  %<1>%s "),gBugCheckCode[j].BucCheckCode,Buf);
					TStrCpy(Buf,gBugCheckCode[j].Name);
					OUTPUT(WSTR("\n"),Buf);
					Count++;
				}
			}
		}
	}	
	if(Count)
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);

	return 0;
}
int ntstatus_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	int i,j;
	DWORD dwIndex,Count=0;
	WCHAR Buf[400];
	if(argc==1)
	{
		for(i = 0; gNtstatusTable[i].Name; i++)
		{
			Count++;
			TStrCpy(Buf,gNtstatusTable[i].Name);
			OUTPUT(WSTR("0X%08x  %s\n"),gNtstatusTable[i].Code,Buf);	
			//TStrCpy(Buf,ErrorCodes[i].Description);
			//OUTPUT(WSTR("%s\n"),Buf);
		}
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);
		return 0;
	}
	for(i = 1; i < argc;i++)
	{
		if(CALCEXP(argv[i],&dwIndex))
		{
			for(j = 0; gNtstatusTable[j].Name; j++)
			{
				if(gNtstatusTable[j].Code==dwIndex)
				{
					TStrCpy(Buf,gNtstatusTable[j].Name);

					OUTPUT(WSTR("0X%08x  %<b>%s "),gNtstatusTable[j].Code,Buf);
					TStrCpy(Buf,gNtstatusTable[j].Description);
					OUTPUT(WSTR("\n"),Buf);
					Count++;
					//break;
				}
			}
		}
		else
		{
			for(j = 0; gNtstatusTable[j].Name; j++)
			{
				if(TStrNICmp(argv[i], gNtstatusTable[j].Name,TStrLen(argv[i]))==0)
				{
					TStrCpy(Buf,gNtstatusTable[j].Name);
					OUTPUT(WSTR("%<b>0X%08x  %<1>%s "),gNtstatusTable[j].Code,Buf);
					TStrCpy(Buf,gNtstatusTable[j].Description);
					OUTPUT(WSTR("\n"),Buf);
					Count++;
				}
			}
		}
	}	
	if(Count)
		OUTPUT(WSTR("totals (%<e>%d%<1>)\n"),Count);

	return 0;
}
int lines_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	int Height,Lines,Width;
	if(argc==1)
	{
		OUTPUT(WSTR("Usage : lines number\n"));
		return 0;
	}else if(argc!=2||USDecStrToNum(argv[1],&Lines)==false)
	{
		OUTPUT(WSTR("Usage : lines number\n"));
		return 0;
	}
	Width=gpSyser->m_MainFrame.m_WindowRect.cx;
	Height = gpSyser->m_FontList[WISP_FONT_6X12].m_Height * Lines;
	if(Height>=gpSyser->m_RealFrameBuffer.Height)
		Height=gpSyser->m_RealFrameBuffer.Height;
	gpSyser->m_MainFrame.Resize(Width,Height);
	return 0;
}
int width_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	int Height,Count,Width;
	if(argc==1)
	{
		OUTPUT(WSTR("Usage : width number\n"));
		return 0;
	}else if(argc!=2||USDecStrToNum(argv[1],&Count)==false)
	{
		OUTPUT(WSTR("Usage : width number\n"));
		return 0;
	}
	Height=gpSyser->m_MainFrame.m_WindowRect.cy;
	Width = gpSyser->m_FontList[WISP_FONT_6X12].m_Width * Count;
	if(Width>=gpSyser->m_RealFrameBuffer.Width)
		Width=gpSyser->m_RealFrameBuffer.Width;
	gpSyser->m_MainFrame.Resize(Width,Height);
	return 0;
}

int window_resize_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	int Width,Height;
	if(argc == 1)
	{
		Width = gpSyser->m_RealFrameBuffer.Width;
		Height = gpSyser->m_RealFrameBuffer.Height;
	}
	else if(argc!=3 || USDecStrToNum(argv[1],&Width) == false ||
		USDecStrToNum(argv[2],&Height) == false)
	{
		OUTPUT(WSTR("Usage : ws width height\n"));
		return 1;
	}
	if(Width > 2048 || Height > 1536)
	{
		OUTPUT(WSTR("Error : window is too larger !\n"));
		return 1;
	}
	if(Width < 320 || Height < 200)
	{
		OUTPUT(WSTR("Error : window is too smaller !\n"));
		return 1;
	}
#ifdef CODE_OS_NT_DRV

	gpSyser->RestoreScreen();
	gpSyser->m_MainFrame.Resize(Width,Height);
	gpSyser->CenterScreen();
	gpSyser->BackupScreen();
#else
	gpSyser->m_MainFrame.Resize(Width,Height);
#endif
	return 0;
}

int crc_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	unsigned int crc=0;
	ULONG length;
	ULONG Address;
	BYTE value;
	if(argc != 3)
	{
		OUTPUT(WSTR("Usage : %s address size\n"),argv[0]);
		return 1;
	}
	if(!CALCEXP(argv[1],&Address))
	{
		OUTPUT(WSTR("Usage : %s address size\n"),argv[0]);
		return 1;
	}
	if(!CALCEXP(argv[2],&length))
	{
		OUTPUT(WSTR("Usage : %s address size\n"),argv[0]);
		return 1;
	}
	if(TStrICmp(argv[0],"crc16-ccitt")==0)
	{
		crc=0xffff;
		while( length-- ) {
			if(pSyser->m_pDebugger->ReadMemory(Address,&value,1)==0)
			{
				OUTPUT(WSTR("Syser : read memory failed, Address is %08x!\n"),Address);
				break;
			}
			crc = ( crc << 8 ) ^ crc16table_ccitt[ (( crc >> 8 ) ^ value)&0xff ];
			Address++;
		}	
		OUTPUT(WSTR("CRC16/ccitt %04X\n"),crc&0xffff);
	}
	else if(TStrICmp(argv[0],"crc16")==0)
	{		
		while (length--)
		{
			if(pSyser->m_pDebugger->ReadMemory(Address,&value,1)==0)
			{
				OUTPUT(WSTR("Syser : read memory failed, Address is %08x!\n"),Address);			
				break;
			}
			crc =(crc >> 8) ^ crc16_table[(crc ^ value) & 0xff] ;
			Address++;
		}		
		OUTPUT(WSTR("CRC16 %04X\n"),crc);
	} 
	else if(TStrICmp(argv[0],"crc32")==0)
	{
		crc=0xffffffff;	
		while(length--)
		{
			if(pSyser->m_pDebugger->ReadMemory(Address,&value,1)==0)
			{
				OUTPUT(WSTR("Syser : read memory failed, Address is %08x!\n"),Address);
				break;
			}
			crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ value];
			Address++;
		}
		crc^=0xffffffff;
		OUTPUT(WSTR("CRC32 %08X\n"),crc);
	}

	return 0;
}
