#ifndef	_SYSER_H_
#define	_SYSER_H_




//#define REG_LIST					gpSyser->m_MainFrame.m_SystemExplorer.m_GeneRegList
#define RUNCMD						gpSyser->m_MainFrame.m_ConsoleWnd.RunCmd
#define CALCEXP						gpSyser->m_SyserUI.CalcExp
#define GETSYM						gpSyser->m_SyserUI.GetSym
#define GET_ALMOST_SYM				gpSyser->m_SyserUI.GetAlmostSym
#define GET_STRING_SYM				gpSyser->m_SyserUI.GetString
#define SCR_DBG_PRINT				gpSyser->DbgPrint
//当前激活上下文的寄存器指针结构,这个是和多CPU无关的
#define X86_REG_PTR					gpSyser->m_SyserUI.m_CodeDoc.m_X86RegPtr
//当前CPU的寄存器指针结构是寄存器窗口类的成员变量
#define CPU_REG_PTR_X86				m_X86RegPtr

#define ACTIVE_CODE_VIEW			((CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd())
#define ACTIVE_DATA_VIEW			((CDataView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd())
#define SYSTEM_EXPLORER				gpSyser->m_MainFrame.m_SystemExplorer
#define SOURCE_WATCH_WND			gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SourceVariableWatchWnd

#define CENTER_VIEW_CODE			gpSyser->m_MainFrame.m_SystemExplorer.CenterViewCodeAddress
#define VIEW_CODE					gpSyser->m_MainFrame.m_SystemExplorer.ViewCodeAddress
#define VIEW_DATA					gpSyser->m_MainFrame.m_SystemExplorer.ViewDataAddress
#define ADD_CODE_VIEW				gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.InsertView
#define ADD_DATA_VIEW				gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.InsertView
#define STR_REF_WND					gpSyser->m_MainFrame.m_StringReferenceWnd

/////////////////////////////////////////////////////////////////////////////////////////////////////
//更新类
#define	UPDATE_CODE_VIEW			gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.UpdateAllView
#define	UPDATE_DATA_VIEW			gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.UpdateAllView
#define	UPDATE_MEMORY_VIEW			gpSyser->m_MainFrame.m_SystemExplorer.UpdateMemoryView
#define	SAVE_MEMORY_VIEW			gpSyser->m_MainFrame.m_SystemExplorer.SaveMemoryContext
#define UPDATE_CONTEXT				gpSyser->m_MainFrame.m_SystemExplorer.UpdateContext
#define UPDATE_SOURCE_CODE_VIEW		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UpdateAllView
#define UPDATE_BP_FORM				gpSyser->m_MainFrame.Update

//更新类
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//控制台输出
#define OUTPUT						gpSyser->m_MainFrame.m_ConsoleWnd.Printf
#define SYSEXPLR_OUTPUT				gpSyser->m_MainFrame.m_SystemExplorer.m_TerminalWnd.Printf
#define SRCEXPLR_OUTPUT				gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_TerminalWnd.Printf

#define OUTPUT_INPUT_ERROR			OUTPUT(WSTR("%<3>Error %<1>: Input error!\n"))
#define OUTPUT_INVALID_ADDRESS		OUTPUT(WSTR("%<3>Error %<1>: Invalid Address!\n"))
#define OUTPUT_INVALID_PARAM		OUTPUT(WSTR("%<3>Error %<1>: Invalid Parameter!\n"))
#define OUTPUT_FAIL_TO_READ_MEM		OUTPUT(WSTR("%<3>Error %<1>: Fail to read memory!\n"))
#define OUTPUT_FAIL_TO_WRITE_MEM	OUTPUT(WSTR("%<3>Error %<1>: Fail to write memory!\n"))
#define OUTPUT_COMMAND_USAGE		{WCHAR szCmdBuff[64];TSPrintf(szCmdBuff,WSTR("help %s"),argv[0]);RUNCMD(szCmdBuff);}
//控制台输出
/////////////////////////////////////////////////////////////////////////////////////////////////////


#define SOURC_DEBUGE_FRAME_WND		gpSyser->m_MainFrame.m_SourceDebugFrameWnd
#define DECLARE_SYSER_CMD(Name)		int Name(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
#define IS_CTRL_BREAK				(gpSyser->m_KeyMap[WISP_VK_CONTROL] && gpSyser->m_KeyMap[WISP_VK_C])
#define CUR_SOURCE_SDSMODULE		gpSyser->m_MainFrame.m_SourceDebugFrameWnd.m_SDSModuleList.m_pActiveSDSModule
#define ASSERT_DEBUGGER_OPENED		if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())return 1;
#define PATCH_SYSTEM(n,a,f)			gpSyser->m_pSysDebugger->PatchSystem(n,(ULPOS)(NUM_PTR)a,f)

enum
{
	SYSTEM_EXPLORER_VIEW = 0,
	CONSOLE_VIEW,
	SOURCE_EXPLORER_VIEW,
	MAX_VIEW
};
DWORD* LoadCFGHotKey();
///////////////////////////////////////////////////////////
//应用
#ifdef CODE_OS_WIN

#include "SyserApp.h"
#define SwitchHeap
#define IsHeapFreeBelow(iHeap,Size)		(false)
void	DbgPrint(PCSTR,...);
//应用
///////////////////////////////////////////////////////////
#else //CODE_OS_NT_DRV
///////////////////////////////////////////////////////////
//驱动
#include "SyserNTDrvApp.h"
#include "VMWareSupport.h"
#include "GlobalVariable.h"
#define IsHeapFreeBelow(iHeap,Size)		(gpUserHeap[iHeap]->m_FreeChunkCount<=((ULSIZE)(Size)/CHUNK_SIZE))

#define	SYSER_LINK_NAME				WSTR("\\??\\Syser")
#define SYSER_MSG_EVENT_NAME		WSTR("\\BaseNamedObjects\\SyserMsgEvent")
#define SYSER_DEVICE_NAME			WSTR("\\Device\\Syser")
#define SYSER_PLUGIN_DEVICE_NAME	WSTR("\\Device\\SyserPlugin")
#define SYSER_INIT					WSTR("SyserInit")

//bool WriteSyserEventLog(VOID* IoObject,ULONG ErrorMsgID,WCHAR *String,WCHAR *String2);
bool	SyserErrorLog(VOID* IoObject,ULONG ErrorMsgID,UCHAR MajorFunctionCode=0,UCHAR RetryCount=0,ULONG IoControlCode=0,ULONG FinalStatus=0,WCHAR *String=NULL,WCHAR *String2=NULL,ULONGLONG DumpData1=0,ULONGLONG DumpData2=0);
extern	PDRIVER_DISPATCH gDefaultPDriverDispatch;
void	SaveHeapInfo();
void	ReportHeapChangedInfo(PCSTR szMessage);
void	ReportHeapInfo(PCSTR szMessage);

//驱动
///////////////////////////////////////////////////////////
#endif//CODE_OS_WIN

#endif
