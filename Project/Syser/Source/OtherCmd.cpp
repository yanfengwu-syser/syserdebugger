#include "StdAfx.h"
#include "Syser.h"
#include "OtherCmd.h"


const WCHAR cmd_dx_usage[]=
{
	L"d,db,dw,dd: Show memory data\n"
	L"Format: d[b,w,d] address\n"
	L"Example1: d[b,w,d] 401000\n"
	L"Example2: d[b,w,d] ESI+8\n"
	L"Example3: d[b,w,d] +\n"
	L"Example4: d[b,w,d] -\n"
	L"Example5: d[b,w,d] + offset\n"
	L"Example6: d[b,w,d] - offset\n"

};

const WCHAR cmd_wcd_usage[]=
{
	L"wc,wd: Code,Data Window command\n"
	L"Format: wc[d] [+][-] [address][index_of_windows]\n"
	L"Example1: wc[d] eip+5\n"
	L"Example2: wc[d] 1                   (focus code[data] window 1)\n"
	L"Example3: wc[d] +                   (add new code[data] window)\n"
	L"Example4: wc[d] -                   (remove current code[data] window)\n"
};
const WCHAR cmd_data_usage[]=
{
	L"data: Data Window command\n"
	L"Format: data [+][-] [address][index_of_windows]\n"
	L"Example1: data eip+5\n"
	L"Example2: data 1                   (focus data window 1)\n"
	L"Example3: data +                   (add new data window)\n"
	L"Example4: data -                   (remove current data window)\n"
};
const WCHAR cmd_code_usage[]=
{
	L"code: Code Window command\n"
	L"Format: code [+][-] [address][index_of_windows]\n"
	L"Example1: code eip+5\n"
	L"Example2: code 1                   (focus code window 1)\n"
	L"Example3: code +                   (add new code window)\n"
	L"Example4: code -                   (remove current code window)\n"
};
/*
const WCHAR cmd_isf_usage[]=
{
	L"isf: Identify standard C(++) library function\n"
	L"Format: isf address    (if address is a standard C(++) library function and symbols will be inserted automaticly)\n"
	L"Example1: isf 401000\n"
};
*/
const WCHAR cmd_cv_usage[]=
{
	L"cv: Dump CodeView context to console (then you can save console histroy by loader)\n"
	L"Format: cv\n"
	L"Example1: cv\n"
};

const WCHAR cmd_dv_usage[]=
{
	L"dv: Dump DataView context to console (then you can save console histroy by loader)\n"
	L"Format: dv\n"
	L"Example1: dv\n"
};

SYSER_CMD_ENTRY	OtherCmdTable[]=
{
	////////////////////////////////////////////////////////////////////////////////////////////
	//Info
	////////////////////////////////////////////////////////////////////////////////////////////
	{WSTR("?"),			WSTR("Calculate expression"),						exp_command},
	////////////////////////////////////////////////////////////////////////////////////////////
	//View
	////////////////////////////////////////////////////////////////////////////////////////////

	{WSTR("cv"),		WSTR("Print Code View string to console"),			cv_command,			cmd_cv_usage},
	{WSTR("dv"),		WSTR("Print Data View string to console"),			dv_command,			cmd_dv_usage},
	{WSTR("sw"),		WSTR("Show data at stack watch"),					sw_command},
	{WSTR("d"),			WSTR("Show memory data"),							db_command,			cmd_dx_usage},
	{WSTR("db"),		WSTR("Show memory data (BYTE)"),					db_command,			cmd_dx_usage},
	{WSTR("dw"),		WSTR("Show memory data (WORD)"),					db_command,			cmd_dx_usage},
	{WSTR("dd"),		WSTR("Show memory data (DWORD)"),					db_command,			cmd_dx_usage},
	{WSTR("wc"),		WSTR("focus code view (wc + to add new view)"),		wc_command,			cmd_wcd_usage},
	{WSTR("code"),		WSTR("focus code view (code + to add new view)"),	wc_command,			cmd_code_usage},
	{WSTR("wd"),		WSTR("focus data view (wd + to add new view)"),		wd_command,			cmd_wcd_usage},
	{WSTR("data"),		WSTR("focus data view (data + to add new view)"),	wd_command,			cmd_data_usage},
	{WSTR("ws"),		WSTR("focus stack watch list (HotKey ALT+S)"),		ws_command},
	{WSTR("ww"),		WSTR("focus watch list (HotKey ALT+S)"),			ww_command},
	{WSTR("wr"),		WSTR("focus register list (HotKey ALT+R)"),			wr_command},
	{WSTR("wf"),		WSTR("focus FPU register list (HotKey ALT+F)"),		wf_command},
	{WSTR("wx"),		WSTR("focus XMM register list (HotKey ALT+X)"),		wx_command},
	{WSTR("dex"),		WSTR("switch data view float address mode"),		dex_command},
	////////////////////////////////////////////////////////////////////////////////////////////
	//Memory
	////////////////////////////////////////////////////////////////////////////////////////////
	//{WSTR("isf"),		WSTR("Identify standard C(++) library function"),	isf_command,		cmd_isf_usage},
	{NULL,NULL,NULL}
};

int dex_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{		
	CDataView*pDataView;
	ULONG Index=0;
	if(argc==1)
	{
		CTabWndList::IT WndIt=gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.m_WndList.Begin();
		while(WndIt!=gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.m_WndList.End())
		{
			pDataView = (CDataView*)WndIt->pWnd;
			OUTPUT(WSTR("DataView[%d] Float Address %<f>%s\n"),Index,pDataView->IsFloatMode()?WSTR("On "):WSTR("Off"));		
			WndIt++;
			Index++;
		}
		return 0;
	}
	if(CALCEXP(argv[1],&Index)==false)
		Index = 0;
	pDataView = (CDataView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetWnd(Index);
	if(pDataView==NULL)
	{		
		pDataView = ADD_DATA_VIEW();
	}
	if(pDataView==NULL)
		return 0;
	OUTPUT(WSTR("DataView[%d] Float Address %<f>%s\n"),Index,pDataView->IsFloatMode()?WSTR("Off"):WSTR("On"));	
	pDataView->ToggleFloatMode();
	return 0;
}

int cv_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	WCHAR szBuffer[MAX_LINE_CHAR];
	CCodeView*pCodeView=ACTIVE_CODE_VIEW;
	if(pCodeView==NULL)
		return -1;
	HANDLE hItem = pCodeView->GetScrStartItem();
	while(hItem)
	{
		pCodeView->GetItemText(hItem,ITEM_ADDRESS,szBuffer,MAX_LINE_CHAR);
		OUTPUT(WSTR("%s "),szBuffer);
		pCodeView->GetItemText(hItem,ITEM_BIN_DATA,szBuffer,MAX_LINE_CHAR);
		OUTPUT(WSTR("%-20s "),szBuffer);
		pCodeView->GetItemText(hItem,ITEM_ASM_CODE,szBuffer,MAX_LINE_CHAR);
		OUTPUT(WSTR("%-30s "),szBuffer);
		pCodeView->GetItemText(hItem,ITEM_COMMENT,szBuffer,MAX_LINE_CHAR);
		OUTPUT(WSTR("%s\n"),szBuffer);
		hItem = pCodeView->GetNextItem(hItem);
	}
	return 0;
}

int dv_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	BYTE DataBuffer[0x20];
	WISP_CHAR Buffer[512],szSpace[32];
	int nItem,Turn,BeginLine=0;
	DWORD nByte,CurPos;
	int ItemIndex;
	ULPOS Address;
	ULPOS OldAddress=0-1;;
	int nTotalLines=8;
	CDataView*pDataView=ACTIVE_DATA_VIEW;
	if(pDataView==NULL)
		return -1;
	nTotalLines=pDataView->m_nLinePerPage;
	if(argc>1)
	{
		if(CALCEXP(argv[1],&Address))
		{
			OldAddress=pDataView->m_CurAddr;
			pDataView->m_CurAddr=Address;
		}
		if(argc>2)
		{
			if(CALCEXP(argv[2],&Address))
				nTotalLines=Address;
		}
	}
	for(int nLine=0;nLine<nTotalLines;nLine++)
	{
		Address=pDataView->m_CurAddr+nLine*pDataView->m_nByte_Line;
		OUTPUT(WSTR("%08X   "),Address);
		nByte=pDataView->m_ImageSize+pDataView->m_ImageBase-pDataView->m_CurAddr-nLine*pDataView->m_nByte_Line;
		if(nByte>(DWORD)pDataView->m_nByte_Line)
			nByte=(DWORD)pDataView->m_nByte_Line;
		//画字节
		TStrCpy(szSpace,pDataView->m_Spaces);
		szSpace[pDataView->m_ShowLength]=0;

		nItem=(int)nByte/pDataView->m_ShowLength;
		if(nByte%pDataView->m_ShowLength)
			nItem++;
		Turn=pDataView->m_ShowLength*2+pDataView->m_ShowLength;
		pDataView->m_LenArray[HEX_HEX_INDEX][nLine]=Turn*nItem;
		for(ItemIndex=0;ItemIndex<nItem;ItemIndex++)
		{
			if(pDataView->ReadData(Address+ItemIndex*pDataView->m_ShowLength,DataBuffer,pDataView->m_ShowLength)==0)
				TStrCpy(Buffer,pDataView->m_UnReadable);
			else
				THexBytesToStr(DataBuffer,Buffer,(int)nByte,pDataView->m_ShowLength,szSpace);
			CurPos=pDataView->m_CurAddr+nLine*pDataView->m_nByte_Line+ItemIndex*pDataView->m_ShowLength;
			Buffer[pDataView->m_ShowLength*2]=0;
			OUTPUT(WSTR("%s "),Buffer);
		}
		for(DWORD ByteIndex=0 ; ByteIndex < nByte; ByteIndex++)
		{
			if(pDataView->ReadData((DWORD)(Address+ByteIndex),DataBuffer,1)==0)
				TStrCpy(Buffer,pDataView->m_UnReadableASCII);
			else
				THexBytesToASCII(DataBuffer,Buffer,1);
			CurPos=pDataView->m_CurAddr+nLine*pDataView->m_nByte_Line+ByteIndex;
			OUTPUT(WSTR("%c"),*Buffer);
		}
		OUTPUT(WSTR("\n"));
	}
	if(OldAddress!=0-1)
		pDataView->m_CurAddr=OldAddress;
	return 0;
}

int sw_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	if(!gpSyser->m_SyserUI.m_CodeDoc.IsOpened())
		return 0;
	if(argc==1)
	{
		if(X86_REG_PTR.pESP)
			gpSyser->m_MainFrame.m_SystemExplorer.m_StackWatchList.UpdateContext(*X86_REG_PTR.pESP);
	}
	else
	{
		ULPOS Address;
		if(CALCEXP(argv[1],&Address)==false)
		{
			OUTPUT_INPUT_ERROR;
			return -1;
		}
		gpSyser->m_MainFrame.m_SystemExplorer.m_StackWatchList.UpdateContext(Address);
	}
	return 0;
}

int wd_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	CDataView* pDataView;
	ULONG Address,Index,NewAddr;
	ASSERT_DEBUGGER_OPENED
	NewAddr = 0;
	gpSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SYSTEM_EXPLORER_VIEW);
	if(argc==1)
	{
		pDataView =(CDataView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();
	}
	else
	{
		if(argv[1][0]=='-')
		{//关闭当前DataView
			if(gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetWndCount()>1)
			{
				Index = gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWndIndex();
				gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.RemoveWnd(Index);
				gpSyser->m_MainFrame.SetDefaultFocus();
			}
			return 0;
		}
		else if(argv[1][0]=='+')
		{//添加DataView
			NewAddr = ACTIVE_DATA_VIEW->m_CurAddr;
			pDataView = ADD_DATA_VIEW();
			if(pDataView==NULL)
				return 1;
		}
		else
		{
			if(CALCEXP(argv[1],&Index)==false)
				Index = 0;
			pDataView =(CDataView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetWnd(Index);
			if(pDataView==NULL)
			{
				NewAddr = ACTIVE_DATA_VIEW->m_CurAddr;
				pDataView = ADD_DATA_VIEW();
				if(pDataView==NULL)
					return 1;
			}
			else
			{
				gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.ChangeActiveWnd(pDataView);
			}
		}
	}
	if(argc>2 && CALCEXP(argv[2],&Address))
		pDataView->ViewAddress(Address);
	else if(NewAddr)
		pDataView->ViewAddress(NewAddr);
	pDataView->Focus();
	OUTPUT(WSTR("Press ESC to return console\n"));
	return 0;
}

int wc_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	CCodeView*pCodeView;
	ULONG Address,Index,NewAddr;
	ASSERT_DEBUGGER_OPENED
	NewAddr = 0;
	pSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(SYSTEM_EXPLORER_VIEW);
	if(argc==1)
	{
		pCodeView =(CCodeView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
	}
	else
	{
		if(argv[1][0]=='-')
		{//关闭当前CodeView
			if(pSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetWndCount()>1)
			{
				Index = pSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWndIndex();
				gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.RemoveWnd(Index);
				gpSyser->m_MainFrame.SetDefaultFocus();
			}
			return 0;
		}
		else if(argv[1][0]=='+')
		{//添加CodeView
			NewAddr = ACTIVE_CODE_VIEW->m_CurAddr;
			pCodeView = ADD_CODE_VIEW();
			if(pCodeView==NULL)
				return 1;
		}
		else
		{
			if(CALCEXP(argv[1],&Index)==false)
				Index = 0;
			pCodeView = (CCodeView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetWnd(Index);
			if(pCodeView==NULL)
			{
				NewAddr = ACTIVE_CODE_VIEW->m_CurAddr;
				pCodeView = ADD_CODE_VIEW();
				if(pCodeView==NULL)
					return 1;
			}
			else
			{
				gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.ChangeActiveWnd(pCodeView);
			}
		}
	}
	if(argc>2 && CALCEXP(argv[2],&Address))
		pCodeView->SetStartAddress(Address,true);
	else if(NewAddr)
		pCodeView->SetStartAddress(NewAddr,true);
	pCodeView->Focus();
	OUTPUT(WSTR("Press ESC to return console\n"));
	return 0;
}

int ws_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	pSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(0);
	pSyser->m_MainFrame.m_SystemExplorer.m_ContextTabWnd.SetActiveWnd(0);
	OUTPUT(WSTR("Press ESC to return console\n"));
	return 0;
}

int ww_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	pSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(0);
	pSyser->m_MainFrame.m_SystemExplorer.m_ContextTabWnd.SetActiveWnd(1);
	OUTPUT(WSTR("Press ESC to return console\n"));
	return 0;
}

int wr_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	pSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(0);
	CWispTabWnd* pWndRegTab=(CWispTabWnd*)pSyser->m_MainFrame.m_SystemExplorer.m_MultiCPUTabWnd.GetActiveWnd();
	pWndRegTab->SetActiveWnd(0);
	OUTPUT(WSTR("Press ESC to return console\n"));
	return 0;
}

int wf_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	pSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(0);
	CWispTabWnd* pWndRegTab=(CWispTabWnd*)pSyser->m_MainFrame.m_SystemExplorer.m_MultiCPUTabWnd.GetActiveWnd();
	pWndRegTab->SetActiveWnd(1);
	OUTPUT(WSTR("Press ESC to return console\n"));
	return 0;
}

int wx_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	pSyser->m_MainFrame.m_MainTabWnd.SetActiveWnd(0);
	CWispTabWnd* pWndRegTab=(CWispTabWnd*)pSyser->m_MainFrame.m_SystemExplorer.m_MultiCPUTabWnd.GetActiveWnd();
	pWndRegTab->SetActiveWnd(2);
	//pSyser->m_MainFrame.m_SystemExplorer.m_RegTabWnd.SetActiveWnd(2);
	OUTPUT(WSTR("Press ESC to return console\n"));
	return 0;
}

int exp_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	CHAR szBuffer[256];
	WCHAR szSym[256];
	DWORD Value;
	if(argc < 2)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(USHexStrToNum(argv[1],&Value) && GETSYM(Value,szBuffer))
	{
		TStrCpy(szSym,szBuffer);
		OUTPUT(WSTR("%<F>%s\n"),szSym);
	}
	else if(CALCEXP(argv[1],&Value)==false)
	{
		OUTPUT(WSTR("Error : %s is Invalid !\n"),argv[1]);
		return -1;
	}
	else
		OUTPUT(WSTR("Hex : %X\n"),Value);
	OUTPUT(WSTR("Dec : %d\n"),Value);
/*	if(Value<0x100)
	{
		OUTPUT(WSTR("Bin : "));
		for(int i = 0; i < 8;i++)
		{
			if(i==2 || i==5)
				OUTPUT(WSTR(" "));
			OUTPUT(WSTR("%d"),(Value>>(7-i))&1);
			
		}
		OUTPUT(WSTR("\n"));
	}
*/
	return 0;
}

int db_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	DWORD dwBaseAddress;
	DWORD dwAddress;
	CDataView*pActiveView;
	WCHAR* CmdString=NULL;
	bool bNext=false;
	if(argc>3)
		return 1;
	switch(argv[0][1])
	{
	case 'b':
	case 'B':
		if(pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveDataWidth()==1)
			bNext=true;
		else
			pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveDataWidth(1);
		break;
	case 'w':
	case 'W':
		if(pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveDataWidth()==2)
			bNext=true;
		else
			pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveDataWidth(2);
		break;
	case 'd':
	case 'D':
		if(pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveDataWidth()==4)
			bNext=true;
		else
			pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveDataWidth(4);
		break;
	}
	if(argc==1)
	{
		if(bNext==false)//是一个参数，并且是改变显示宽度
			return 0;
		//如果命令只有一个参数，并且显示宽度没有改变则继续显示下一屏幕的内容
		pActiveView=(CDataView*)pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();
		if(pActiveView==NULL)
			return 1;			
		dwAddress = pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveAddress();		
		dwAddress+=pActiveView->m_nLinePerPage*0x10;
		if(pActiveView->m_bShowOffset)
			dwAddress-=0x10;
		pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveAddress(dwAddress,CmdString);
		return 0;
	}
	if(argc==2)
	{
		pActiveView=(CDataView*)pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();
		if(pActiveView==NULL)
			return 1;	
		if(TStrICmp(argv[1],WSTR("-"))==0)
		{
			pActiveView->OnPrevPos(NULL);
			return 0;
		}
		else if(TStrICmp(argv[1],WSTR("+"))==0)
		{
			pActiveView->OnNextPos(NULL);
			return 0;
		}

		CmdString=argv[1];
		if(CALCEXP(argv[1],&dwAddress)==FALSE)
		{
		 	return 1;
		}
		pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveAddress(dwAddress,CmdString);
		return 0;
	}

	if(argc==3)
	{
		WCHAR *param1,*param2;
		param1=argv[1];
		param2=argv[2];
		do
		{
			argc--;
			if(TStrICmp(param1,WSTR("-"))==0)
			{
				if(CALCEXP(param2,&dwAddress)==FALSE)
				{
					OUTPUT(WSTR("Error : %<3>Input error !\n"));
					return -1;
				}
				pActiveView=(CDataView*)pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();
				if(pActiveView==NULL)
					return 1;			
				dwBaseAddress = pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveAddress();
				dwAddress=dwBaseAddress-dwAddress;
				break;

			}else if(TStrICmp(param1,WSTR("+"))==0)
			{
				if(CALCEXP(param2,&dwAddress)==FALSE)
				{
					OUTPUT(WSTR("Error : %<3>Input error !\n"));
					return -1;
				}
				pActiveView=(CDataView*)pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();
				if(pActiveView==NULL)
					return 1;			
				dwBaseAddress = pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveAddress();
				dwAddress=dwBaseAddress+dwAddress;
				break;
			}
#ifdef CODE_OS_NT_DRV
			else
			if(TStrICmp(param1,WSTR("-P"))==0)
			{
				if(CALCEXP(param2,&dwAddress)==FALSE)
				{
					OUTPUT(WSTR("Error : %<3>Input error !\n"));
					return -1;
				}
				if(MapToVAddr(dwAddress,&dwAddress)==false)
					return 1;
				break;
			}
#endif
			param1=argv[2];
			param2=argv[1];
		}while(argc!=1);
	}

	pSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.SetActiveAddress(dwAddress,CmdString);
	return 0;
}

/*
int isf_command(int argc, WCHAR *argv[ ],PCWSTR szCommandLine, CSyser*pSyser)
{
	ULPOS Address;
	if(argc<=1)
	{
		OUTPUT_COMMAND_USAGE;
		return -1;
	}
	if(CALCEXP(argv[1],&Address)==false)
	{
		OUTPUT_INVALID_ADDRESS;
		return -1;
	}
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
	if(pDbgModule==NULL)
		return true;
	gpSyser->m_SyserUI.InsertAnalyzerComment(pDbgModule,Address);
	UPDATE_CODE_VIEW();
	return 0;
}
*/
