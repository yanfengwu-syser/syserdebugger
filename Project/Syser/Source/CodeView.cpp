#include "StdAfx.h"
#include "CodeView.h"
#include "StringReference.h"
#ifdef _SYSER_
#include "Syser.h"
#endif



WISP_MENU_RES_ITEM CodeViewModeMenu[]=
{
	{WSTR("Symbol Switch        Tab"),			EVENT_ID_TOGGLE_SYMBOL,		0,WISP_MIS_CHECKBOX},
	{WSTR("Full Symbol          Ctrl+Tab"),		EVENT_ID_TOGGLE_FULL_SYMBOL,0,WISP_MIS_CHECKBOX},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Address Mode"),						EVENT_ID_ADDRESS_MODE_HEX,	0,WISP_MIS_CHECKBOX},
	{WSTR("Offset  Mode"),						EVENT_ID_OFFSET_MODE_HEX,	0,WISP_MIS_CHECKBOX},
	{WSTR("Relative to EIP"),					EVENT_ID_RELATIVE_TO_EIP,	0,WISP_MIS_CHECKBOX},
	WISP_MENU_RES_END
};

WISP_MENU_RES_ITEM EIPFollowModeMenu[]=
{
	{WSTR("Automatic"),							EVENT_ID_FM_AUTOMATIC,				0,WISP_MIS_CHECKBOX},
	{WSTR("System Explorer"),					EVENT_ID_FM_SYSTEM_EXPLORER,		0,WISP_MIS_CHECKBOX},
	{WSTR("Source Code Explorer"),				EVENT_ID_FM_SOURCE_CODE_EXPLORER,	0,WISP_MIS_CHECKBOX},
	WISP_MENU_RES_END
};


WISP_MENU_RES_ITEM CodeViewOperationMenu[]=
{
	{WSTR("Insert/Remove  Breakpoint      F9"),			EVENT_ID_TOGGLE_BP,				15*16+3},
	{WSTR("Enable/Disable Breakpoint"),					EVENT_ID_TOGGLE_BP_STATE,		15*16+4},
	{WSTR("Toggle BookMark                Ctrl+K"),		EVENT_ID_BOOKMARK_TOGGLE,		13*16},
	{WSTR("Save Position                  Shift+Enter"),EVENT_ID_SAVE_POS,				16*1+8},
	//{WSTR("Identify standard C(++) Library Function"),	EVENT_ID_ANALYZE_FROM_ADDRESS,	15*16+6},
	{WSTR("Go To Here                     F7"),			EVENT_ID_GOTO,					16*16+13},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Search Transfer Reference"),					EVENT_ID_TRANSFER_REFERENCE,	17*16+8},
	{WSTR("Search Operand Reference"),					EVENT_ID_OPERAND_REFERENCE,		17*16+9},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Code View Mode"),0,61,WISP_MIS_POPUP,		CodeViewModeMenu},
	{WSTR("EIP Follow Mode"),0,16,WISP_MIS_POPUP,		EIPFollowModeMenu},
	{WSTR("Copy"),										WISP_ID_COPY,					35},
	{WSTR("Edit Code"),									EVENT_ID_CODEVIEW_EDIT_CODE,	126},
	{WSTR("Edit Comment"),								EVENT_ID_CODEVIEW_EDIT_COMMENT,	9*16+3},
	{WSTR("String Reference"),							EVENT_ID_STRING_REFERENCE,	9*16+3},
	WISP_MENU_RES_END
};

WISP_MSG_MAP_BEGIN(CCodeView)
	WISP_MSG_MAP(WISP_WM_PRECREATE,OnPrecreate)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_SCROLL_EVENT,OnScrollEvent)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_CHAR,OnChar)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_GET_FOCUS,OnGetFocus)
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_CMD_MAP_BEGIN(CCodeView)
	WISP_MSG_CMD_MAP(WISP_ID_VSLIDE,OnCmdVSlide);
	WISP_MSG_CMD_MAP(EVENT_ID_STRING_REFERENCE_WISPLIST,OnCmdStringGoto);
	
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CCodeView)
	WISP_MSG_EVENT_MAP(WISP_ID_COPY,OnEventCopy)
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_BP,OnEventToggleBreakPoint)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_FM_AUTOMATIC,			OnEventFMAutomiatic)
	WISP_MSG_EVENT_MAP(EVENT_ID_FM_SYSTEM_EXPLORER,		OnEventFMSystemExplorer)
	WISP_MSG_EVENT_MAP(EVENT_ID_FM_SOURCE_CODE_EXPLORER,OnEventFMSourceCodeExplorer)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_SYMBOL,			OnEventToggleSymbol)
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_FULL_SYMBOL,		OnEventToggleFullSymbol)
	WISP_MSG_EVENT_MAP(EVENT_ID_ADDRESS_MODE_HEX,	OnEventAddressModeHex)
	WISP_MSG_EVENT_MAP(EVENT_ID_OFFSET_MODE_HEX,	OnEventOffsetModeHex)
	WISP_MSG_EVENT_MAP(EVENT_ID_RELATIVE_TO_EIP,	OnEventRelativeToEIP)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_TRANSFER_REFERENCE,	OnEventCrossReference)
	WISP_MSG_EVENT_MAP(EVENT_ID_OPERAND_REFERENCE,		OnEventXrefOperand)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_BP_STATE,	OnEventToggleBreakPointState)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_TOGGLE,	OnEventToggleBookMarks)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTO,				OnEventGotoHere)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_NEXT_POS,			OnEventNextPos)
	WISP_MSG_EVENT_MAP(EVENT_ID_PREV_POS,			OnEventPrevPos)
	WISP_MSG_EVENT_MAP(EVENT_ID_SAVE_POS,			OnEventSavePos)
	WISP_MSG_EVENT_MAP(EVENT_ID_EMPTY_POS_LIST,		OnEventEmptyPosList)
	//-----------------------------------------------------------------------
	//WISP_MSG_EVENT_MAP(EVENT_ID_ANALYZE_FROM_ADDRESS,	OnEventAnalyzeFromAddress)
	//-----------------------------------------------------------------------
	WISP_MSG_EVENT_MAP(EVENT_ID_CODEVIEW_EDIT_CODE,		OnEventEditCode)
	WISP_MSG_EVENT_MAP(EVENT_ID_CODEVIEW_EDIT_COMMENT,	OnEventEnterComment)
	WISP_MSG_EVENT_MAP(EVENT_ID_STRING_REFERENCE,	OnEventStringReference)

	WISP_MSG_EVENT_MAP(EVENT_ID_STARTADDRESS_DEC,	OnStartAddressDec)
	WISP_MSG_EVENT_MAP(EVENT_ID_STARTADDRESS_INC,	OnStartAddressInc)

	WISP_MSG_EVENT_MAP(EVENT_ID_GETNEXTTRACE,		OnGetNextTrace)
	WISP_MSG_EVENT_MAP(EVENT_ID_GETPREVTRACE,		OnGetPrevTrace)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_0,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_1,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_2,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_3,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_4,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_5,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_6,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_7,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_ACTIVE_CODEVIEW_8,	OnActiveCodeView)
	WISP_MSG_EVENT_MAP(EVENT_ID_FOLLOW_TO_DESTINATION,OnEnterAddr)
	
WISP_MSG_EVENT_MAP_END


void CCodeView::GetAddressString(ULPOS Address,WISP_PSTR szBuffer)
{
	WISP_CHAR szRelStr[32];
	int BaseAddress,Offset;
	switch(m_AddrShowMode)
	{
	case CODE_VIEW_ADDRESS_MOD:
		TSPrintf(szBuffer,WSTR("%08X"),Address);
		return;
	case CODE_VIEW_OFFSET_MOD:
		BaseAddress=(int)m_BaseActiveAddress;
		Offset = (int)Address-BaseAddress;
		TStrCpy(szRelStr,"$");
		break;
	case CODE_VIEW_REL_TO_EIP_MOD:
		BaseAddress=(int)*X86_REG_PTR.pEIP;
		Offset = (int)Address-BaseAddress;
		TStrCpy(szRelStr,"EIP");
		break;
	}
	if(Offset>0)
	{
		TSPrintf(szBuffer,WSTR("%s+%X"),szRelStr,Offset);
	}
	else if(Offset==0)
	{
		TStrCpy(szBuffer,szRelStr);
		TStrCat(szBuffer,"==>");
	}
	else
	{
		TSPrintf(szBuffer,WSTR("%s-%X"),szRelStr,-Offset);
	}
}

void CCodeView::ItemRClickNotify(HANDLE hItem,int Col)
{
	switch(Col)
	{
	case ITEM_STATE:
		OnEventToggleBookMarks(NULL);
		break;
	}
}

void CCodeView::ItemClickNotify(HANDLE hItem,int Col)
{
	switch(Col)
	{
	case ITEM_STATE:
		OnEventToggleBreakPoint(NULL);
		break;
	case ITEM_ADDRESS:
		switch(m_AddrShowMode)
		{
		case CODE_VIEW_ADDRESS_MOD:
			OnEventOffsetModeHex(NULL);
			break;
		case CODE_VIEW_OFFSET_MOD:
			OnEventRelativeToEIP(NULL);
			break;
		case CODE_VIEW_REL_TO_EIP_MOD:
			OnEventAddressModeHex(NULL);
			break;
		}
		UpdateView();
		break;
	}
}

bool CCodeView::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	if(m_pCodeDoc==NULL || m_pCodeDoc->IsOpened()==false)
		return false;
	switch(Col)
	{
	case 3:
		m_EditCtrl.SetWindowText(L" ");
		break;
	case 4:
		if(IsColorString(String))
			return false;
		break;
	}
	return true;
}
bool CCodeView::OnCmdStringGoto(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	NUM_PTR ItemData;
	CCodeView* pCodeView;
	CDataView* pDataView;
	if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_LDBCLICK)
	{		
		hItem=(HANDLE)pMsg->Command.Param2;
		ItemData = gpSyser->m_MainFrame.m_StringReferenceWnd.GetItemData(hItem,0);
		if(ItemData & 0x8000000000000000i64)
		{
			ItemData = gpSyser->m_MainFrame.m_StringReferenceWnd.GetItemData(hItem,1);
			pDataView=(CDataView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();	
			if(pDataView)
				pDataView->ViewAddress((DWORD)ItemData);
		}
		else
		{
			pCodeView=(CCodeView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();			
			if(pCodeView)
				pCodeView->SetStartAddress((DWORD)ItemData,true);
		}
	}
	else if(pMsg->Command.CmdMsg == WISP_CMD_ITEM_RDBCLICK)
	{
		hItem=(HANDLE)pMsg->Command.Param2;
		ItemData = gpSyser->m_MainFrame.m_StringReferenceWnd.GetItemData(hItem,1);
		pDataView=(CDataView*)gpSyser->m_MainFrame.m_SystemExplorer.m_MultiDataView.GetActiveWnd();	
		if(pDataView)
			pDataView->ViewAddress((DWORD)ItemData);
	}
	return true;
}
bool CCodeView::BuildASM(HANDLE hItem,CWispString& String)
{
	char Buf[256];
	BYTE OutBuf[128];
	DWORD Len;
	ULPOS Address = (ULPOS)GetItemData(hItem,1);
	TStrCpyLimit(Buf,(PCWSTR)String,sizeof(Buf));
	Len = Assembler(Buf,OutBuf,Address,BIT32);
	if(Len)
	{
		gpSyser->m_pDebugger->WriteMemory(Address,OutBuf,Len);
		UpdateView();
		return false;
	}
	return false;
}

bool CCodeView::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	ULPOS Address;
	switch(Col)
	{
	case 1:
		if(GetItemText(hItem,Col)==String)
			return false;
		if(CALCEXP((WISP_PCSTR)String,&Address)==false)
			return false;
		SetStartAddress(Address,true);
		return false;
	case 3:
		return BuildASM(hItem,String);
	case 4:
		Address = (ULPOS)GetItemData(hItem,1);
		m_pCodeDoc->SetComment(Address,String);
		UpdateView();
		return true;
		break;
	}
	return true;
}

bool CCodeView::OnCmdVSlide(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		SetScrollBarCurPos(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,false);
	}
	return true;
}

bool CCodeView::OnEventToggleSymbol(IN WISP_MSG*pMsg)
{
	if(m_pCodeDoc->m_Style&DS_USE_SYM)
		m_pCodeDoc->m_Style&=~DS_USE_SYM;
	else
		m_pCodeDoc->m_Style|=DS_USE_SYM;
	UpdateView();
	return true;
}

bool CCodeView::OnEventToggleFullSymbol(IN WISP_MSG*pMsg)
{
	if(SyserOption.iShowFullSym)
		SyserOption.iShowFullSym=0;
	else
		SyserOption.iShowFullSym=1;
	UpdateView();
	return true;
}

bool CCodeView::OnEventEnterComment(IN WISP_MSG*pMsg)
{
	HANDLE hItem=GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem)
		BeginEditItem(hItem,4);
	return true;
}
bool CCodeView::OnEventStringReference(IN WISP_MSG*pMsg)
{
	gpSyser->m_MainFrame.m_FindListWnd.Create(WSTR("String Reference"),0,0,564,344,NULL,EVENT_ID_STRING_REFERENCE_WISPLIST,WISP_WLS_COLUMN_TITLE|WISP_WS_NORMAL|WISP_WLS_TREE);
	return true;
}

bool CCodeView::OnEventEditCode(IN WISP_MSG*pMsg)
{
	HANDLE hItem=GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem)
		BeginEditItem(hItem,3);
	return true;
}

bool CCodeView::OnEventCopy(IN WISP_MSG*pMsg)
{
	CWispString*pStrObj;
	HANDLE hItem;
	hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(m_hPopupMenuItem!=hItem || hItem==NULL)
		return true;
	if(m_PopupMenuCol<1 || m_PopupMenuCol>4)
		return true;
	pStrObj = &GetItemText(m_hPopupMenuItem,m_PopupMenuCol);
	if(IsColorString(pStrObj->m_pData))
	{
		WISP_CHAR szBuffer[256];
		TStrCpyLimit(szBuffer,GetColorString(pStrObj->m_pData),256);
		m_pWispBase->SetClipboardString(szBuffer);
	}
	else
	{
		if(pStrObj->Length())
			m_pWispBase->SetClipboardString(pStrObj->m_pData);
	}
	return true;
}

bool CCodeView::OnEventGotoHere(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	if(gpSyser->m_pDebugger==NULL||gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return true;
	hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = (DWORD)GetItemData(hItem,1);
	gpSyser->m_pDebugger->InsertCodeBP(Address,BP_TYPE_DEBUG,BP_STATE_ENABLE);
	RUNCMD(WSTR("x"));
	return true;
}

bool CCodeView::OnEventAddressModeHex(IN WISP_MSG*pMsg)
{
	m_AddrShowMode=CODE_VIEW_ADDRESS_MOD;
	UpdateView();
	return true;
}

bool CCodeView::OnEventRelativeToEIP(IN WISP_MSG*pMsg)
{
	m_AddrShowMode=CODE_VIEW_REL_TO_EIP_MOD;
	UpdateView();
	return true;
}

bool CCodeView::OnEventOffsetModeHex(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	m_BaseActiveAddress = (ULPOS)GetItemData(hItem,1);
	m_AddrShowMode=CODE_VIEW_OFFSET_MOD;
	UpdateView();
	return true;
}

bool CCodeView::OnEventFMAutomiatic(IN WISP_MSG*pMsg)
{
	SyserOption.iFollowMode = SYSER_FM_AUTOMATIC;
	return true;
}

bool CCodeView::OnEventFMSystemExplorer(IN WISP_MSG*pMsg)
{
	SyserOption.iFollowMode = SYSER_FM_SYSTEM_EXPLORER;
	return true;
}

bool CCodeView::OnEventFMSourceCodeExplorer(IN WISP_MSG*pMsg)
{
	SyserOption.iFollowMode = SYSER_FM_SOURCE_EXPLORER;
	return true;
}

int CCodeView::GetCrossReferenceList(DWORD Address,CROSSREFERENCELIST* pCrossReferenceList)
{
	int TotalCount=0;
	BYTE* Buffer;
	HANDLE hItem=NULL;
	int ReadLen,RetLen,j,CurrentCount=0,i,Len,TmpLen,k;
	ULPOS Addr,DestAddress,HighAddr,LowAddr;
	int Offset;
	CDbgModule* pModule;
	pModule = gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
	if(pModule==NULL && gpSyser->m_pSysDebugger!=gpSyser->m_pDebugger)
	{
		pModule = gpSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
		if(pModule==NULL)
			return false;
	}
	Buffer = new BYTE[0x1010];
	if(Buffer==NULL)
	{
		return false;
	}
	Addr = pModule->m_ModuleBase;
	Len = pModule->m_ModuleSize;
	ReadLen = 0x1000;
	LowAddr=Address-128;
	HighAddr=Address+127;
	for(i = 0; i < Len;)
	{
		if(Len - i < ReadLen)
			ReadLen=Len-i;
		RetLen = gpSyser->m_pDebugger->ReadMemory(Addr,Buffer,ReadLen);
		if(RetLen == ReadLen)
		{
			for(j = 0; j < RetLen-5;j++)
			{
				if(Buffer[j]==0xe9 || Buffer[j]==0xe8)
				{
					TotalCount++;
					Offset=*(int*)&Buffer[j+1];
					DestAddress = Addr+Offset+j+5;
					if(Address==DestAddress)
					{
						CurrentCount++;
						pCrossReferenceList->Append(Addr+j);
					}
				}
				else
				{
					if(Buffer[j]==0x0f)
					{
						if(Buffer[j+1]>=0x80&&Buffer[j+1]<=0x8f)
						{
							TotalCount++;
							Offset=*(int*)&Buffer[j+2];
							DestAddress = Addr+Offset+j+6;
							if(Address==DestAddress)
							{
								CurrentCount++;
								pCrossReferenceList->Append(Addr+j);
							}
						}
					}
				}
			}
			for(k=j; k < RetLen;k++)
			{
				if(Buffer[k]==0xe9||Buffer[k]==0x0f)
					break;
			}
			if(k!=RetLen)
			{
				*(int*)&Buffer[ReadLen]=0;
				TmpLen = Len - (i+ReadLen);
				if(TmpLen>=5)
					TmpLen=5;
				k = gpSyser->m_pDebugger->ReadMemory(Addr+ReadLen,&Buffer[ReadLen],TmpLen);
				if(k == TmpLen)
				{
					for(;j<RetLen;j++)
					{
						if(Buffer[j]==0xe9||Buffer[j]==0xe8)
						{
							TotalCount++;
							Offset=*(int*)&Buffer[j+1];
							DestAddress = Addr+Offset+j+5;
							if(Address==DestAddress)
							{
								CurrentCount++;
								pCrossReferenceList->Append(Addr+j);
							}
						}
						else
						{
							if(Buffer[j]==0x0f)
							{
								if(Buffer[j+1]>=0x80&&Buffer[j+1]<=0x8f)
								{
									TotalCount++;
									Offset=*(int*)&Buffer[j+2];
									DestAddress = Addr+Offset+j+6;
									if(Address==DestAddress)
									{
										CurrentCount++;
										pCrossReferenceList->Append(Addr+j);
									}
								}
							}
						}
					}
				}
			} 
			
		}
		i+=ReadLen;
		Addr+=ReadLen;
	}
	Addr=LowAddr;
	RetLen = gpSyser->m_pDebugger->ReadMemory(LowAddr,Buffer,256);
	if(RetLen==256)
	{
		for(j = 0;j < RetLen-1;j++)
		{
			if(Buffer[j]==0xeb)
			{
				TotalCount++;
				Offset=(int)(char)Buffer[j+1];
				DestAddress = Addr+Offset+j+2;
				if(Address==DestAddress)
				{
					CurrentCount++;
					pCrossReferenceList->Append(Addr+j);
				}
			}else if(Buffer[j]>=0x70&&Buffer[j]<=0x7f)
			{
				TotalCount++;
				Offset=(int)(char)Buffer[j+1];
				DestAddress = Addr+Offset+j+2;
				if(Address==DestAddress)
				{
					CurrentCount++;
					pCrossReferenceList->Append(Addr+j);
				}
			}

		}
	}
	delete Buffer;
	TotalCount = pCrossReferenceList->Count();
	return TotalCount;
}

int CCodeView::GetDataReferenceList(DWORD Address,CROSSREFERENCELIST* pList,DWORD* VarAddr)
{
	int TotualCount=0;
	int ReadLen,RetLen=0,j=0,CurrentCount=0,i,Len,TmpLen=0,k=0;
	ULPOS Addr=0,DestAddress,TmpVar;
	int Offset=0;
	CDbgModule* pModule;
	
	bool bOk;
	ULPOS DesAddr=0;
	if(m_pCodeDoc==NULL||m_pCodeDoc->IsOpened()==false)
		return 0;
	bOk = m_pCodeDoc->GetVariableDesAddress(Address,&DestAddress);
	if(bOk==false)
		return 0;
	*VarAddr=DestAddress;
	pModule = gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
	if(pModule==NULL)
	{
#ifdef CODE_OS_NT_DRV
		pModule = gpSyser->m_pSysDebugger->GetModule(Address);
#endif
		if(pModule==NULL)
			return 0;
	}
	if(DestAddress<pModule->m_ModuleBase || DestAddress >= pModule->m_ModuleBase+pModule->m_ModuleSize)
		return 0;
	Addr = pModule->m_ModuleBase;
	Len = pModule->m_ModuleSize;
	ReadLen = 0x1000;
	for(i = 0; i < Len-3;i++)
	{
		if(m_pCodeDoc->ReadImage(Addr+i,&TmpVar,sizeof(TmpVar))==sizeof(TmpVar))
			if(TmpVar==DestAddress)
				pList->Append(Addr+i);
	}
	TotualCount=pList->Count();
	return TotualCount;
}

bool CCodeView::OnEventCrossReference(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	CROSSREFERENCELIST CrossReferenceList;
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return true;
	hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address=(ULPOS)GetItemData(hItem,1);
	CrossReferenceByAddr(Address);
	return true;
}


bool CCodeView::OnEventXrefOperand(IN WISP_MSG*pMsg)
{
	CROSSREFERENCELIST CrossReferenceList;
	CROSSREFERENCELIST::IT BeginIt,EndIt;
	HANDLE hItem;
	ULPOS Address;	
	if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return true;
	hItem=GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address=(ULPOS)GetItemData(hItem,1);
	XrefOperandByAddr(Address);
	return true;
}

bool CCodeView::CrossReferenceByAddr(ULPOS Address)
{
	CROSSREFERENCELIST CrossReferenceList;
	int Count;
	Count = GetCrossReferenceList(Address,&CrossReferenceList);
	if(Count==0)
	{
		SYSEXPLR_OUTPUT(WSTR("Can't find Transfer Reference\n"));
		return true;
	}
	if(gpSyser->m_MainFrame.m_CrossReferenceForm.IsWindow())
		gpSyser->m_MainFrame.m_CrossReferenceForm.Show();
	else
		gpSyser->m_MainFrame.m_CrossReferenceForm.CreateForm();
	gpSyser->m_MainFrame.m_CrossReferenceForm.InitReferenceList(&CrossReferenceList,Address);
	return true;
}

bool CCodeView::XrefOperandByAddr(ULPOS Address)
{
	CROSSREFERENCELIST CrossReferenceList;
	int Count;
	ULPOS RetAddr;	
	Count =  GetDataReferenceList(Address,&CrossReferenceList,&RetAddr);
	if(Count==0)
	{
		SYSEXPLR_OUTPUT(WSTR("Can't find Operand Reference\n"));
		return true;
	}
	if(gpSyser->m_MainFrame.m_CrossReferenceForm.IsWindow())
		gpSyser->m_MainFrame.m_CrossReferenceForm.Show();
	else
		gpSyser->m_MainFrame.m_CrossReferenceForm.CreateForm();
	gpSyser->m_MainFrame.m_CrossReferenceForm.InitDataReferenceList(&CrossReferenceList,RetAddr);
	return true;
}

bool CCodeView::OnEventNextPos(IN WISP_MSG*pMsg)
{
	OnNextPos(pMsg);
	return true;
}

bool CCodeView::OnEventPrevPos(IN WISP_MSG*pMsg)
{
	OnPrevPos(pMsg);
	return true;
}

bool CCodeView::OnEventSavePos(IN WISP_MSG*pMsg)
{
	OnSavePos(pMsg);
	return true;
}

bool CCodeView::OnEventEmptyPosList(IN WISP_MSG*pMsg)
{
	EmptyPosList();
	return true;
}

bool CCodeView::OnNextPos(IN WISP_MSG*pMsg)
{
	if(m_AddrIter!=m_AddrList.End() && *m_AddrIter!= m_CurAddr)
	{//如果当前地址不在当前存储点，先跳到这点上，再NextPos或PrevPos
		SetStartAddress(*m_AddrIter,false);
	}
	else if(m_AddrIter!=m_AddrList.Last())
	{
		m_AddrIter++;
		SetStartAddress(*m_AddrIter,false);
	}
	SYSTEM_EXPLORER.UpdateItemState();
	return true;
}

bool CCodeView::OnPrevPos(IN WISP_MSG*pMsg)
{
	if(m_pCodeDoc==NULL||m_pCodeDoc->IsOpened()==false)
		return true;
	if(m_AddrIter!=m_AddrList.End() && *m_AddrIter!= m_CurAddr)
	{//如果当前地址不在当前存储点，先跳到这点上，再NextPos或PrevPos
		SetStartAddress(*m_AddrIter,false);
	}
	else if(m_AddrIter!=m_AddrList.Begin())
	{
		m_AddrIter--;
		SetStartAddress(*m_AddrIter,false);
	}
	SYSTEM_EXPLORER.UpdateItemState();
	return true;
}

bool CCodeView::OnSavePos(IN WISP_MSG*pMsg)
{
	if(m_AddrIter!=m_AddrList.Last())
	{//如果不是最后一个就
		m_AddrIter++;
		m_AddrList.Remove(m_AddrIter,m_AddrList.End());
		m_AddrIter=m_AddrList.End();
	}	
	if(m_AddrList.Count()>MAX_POS_LIST_COUNT)
	{
		if(m_AddrIter==m_AddrList.Begin())
			m_AddrIter++;
		m_AddrList.Remove(m_AddrList.Begin());
	}
	int nCount=m_AddrList.Count();
	if(m_AddrList.Count()==0 || m_CurAddr!= *m_AddrList.Last())
		m_AddrIter = m_AddrList.Append(m_CurAddr);
	SYSTEM_EXPLORER.UpdateItemState();
	return true;
}

void CCodeView::EmptyPosList()
{
	m_AddrList.Clear();
	m_AddrIter = m_AddrList.Append(m_CurAddr);
	SYSTEM_EXPLORER.UpdateItemState();
}

bool CCodeView::OnEnterAddr(IN WISP_MSG*pMsg)
{
	ULPOS DesAddr,Address,Immed;
	HANDLE hItem;
	int nCount;
	BYTE Buffer[4];
	bool TransferAddress=true;
	
	if(m_pCodeDoc==NULL||m_pCodeDoc->IsOpened()==false)
		return true;
	hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = (ULPOS) GetItemData(hItem,1);
	if(m_pCodeDoc->GetTransferAddress(Address,&DesAddr)==false)
	{		
		nCount = m_pCodeDoc->GetInstrImmediateAndDesAddress(Address,&DesAddr,&Immed);
		if(nCount==0)
			return true;
		TransferAddress=false;
	}
	if(TransferAddress)
	{
		if(m_AddrIter!=m_AddrList.Last())
		{//如果不是最后一个就
			m_AddrIter++;
			m_AddrList.Remove(m_AddrIter,m_AddrList.End());
			m_AddrIter=m_AddrList.End();
		}
		SetStartAddress(DesAddr,true);
		return true;
	}
	if(Immed!=-1)
	{	
		ACTIVE_DATA_VIEW->ViewAddress(Immed);
		return true;	
	}
	if(DesAddr!=-1)
	{
		if(m_pCodeDoc->ReadMemory(DesAddr,Buffer,sizeof(Buffer))==sizeof(Buffer))
		{
			ACTIVE_DATA_VIEW->ViewAddress(DesAddr);
		}
	}
	return true;
}

bool CCodeView::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	WISP_RECT CellRC;
	HANDLE hItem=NULL;
	ULPOS Address=0;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{
		GetItemCellRect(GetItem(0),3,&CellRC);
		if(pMsg->MsgMouseWndPT.x >= CellRC.x && pMsg->MsgMouseWndPT.x<=CellRC.x+CellRC.cx)
			OnEnterAddr(pMsg);
	}	
	return true;
}

void CCodeView::SetSelectItemByAddress(ULPOS Address)
{
	HANDLE hItem = GetScrStartItem();
	NUM_PTR NumPtr;
	while(hItem)
	{
		NumPtr = GetItemData(hItem,1);
		if(Address == *(ULPOS*)&NumPtr)
		{
			SelectItem(hItem);
			break;
		}
		hItem = GetNextItem(hItem);
	}
}
bool CCodeView::OnGetNextTrace(IN WISP_MSG*pMsg)
{
	PSTRUNTRACE pRunTrace;
	pRunTrace = SYSTEM_EXPLORER.GetNextTrace();
	if(pRunTrace==NULL)
		return false;
	SetStartAddress(pRunTrace->CodeViewStartAddress);
	SetSelectItemByAddress(pRunTrace->CodeViewStartAddress+pRunTrace->EIPOffset);
	return true;
}

bool CCodeView::OnGetPrevTrace(IN WISP_MSG*pMsg)
{
	PSTRUNTRACE pRunTrace;
	pRunTrace = SYSTEM_EXPLORER.GetPrevTrace();
	if(pRunTrace==NULL)
		return true;
	SetStartAddress(pRunTrace->CodeViewStartAddress);
	SetSelectItemByAddress(pRunTrace->CodeViewStartAddress+pRunTrace->EIPOffset);
	return true;
}

void CCodeView::PopupMenu(IN WISP_MSG*pMsg)
{
	bool bState;
	ULPOS Address;
	if(PointToItem(pMsg->MsgMouseCltPT,&m_PopupMenuCol)==NULL)
		return;
	if(m_PopupMenuCol<1 || m_PopupMenuCol>LI_POS_CELL_AREA_END)
		return;
	m_hPopupMenuItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(m_hPopupMenuItem==NULL)
		return;
	Address = (ULPOS)GetItemData(m_hPopupMenuItem,1);
	bState = GetItemText(m_hPopupMenuItem,2).Length()!=0;
	m_PopupMenu.EnableItem(EVENT_ID_CODEVIEW_EDIT_CODE,bState);
	m_PopupMenu.EnableItem(EVENT_ID_CODEVIEW_EDIT_COMMENT,bState);
	m_PopupMenu.EnableItem(EVENT_ID_PREV_POS,m_AddrIter!=m_AddrList.Begin());
	m_PopupMenu.EnableItem(EVENT_ID_NEXT_POS,m_AddrIter!=m_AddrList.Last());
	m_PopupMenu.EnableItem(EVENT_ID_EMPTY_POS_LIST,m_AddrList.Count()>1);
	m_PopupMenu.CheckItem(EVENT_ID_TOGGLE_SYMBOL,(m_pCodeDoc->m_Style&DS_USE_SYM)!=0);
	m_PopupMenu.CheckItem(EVENT_ID_TOGGLE_FULL_SYMBOL,SyserOption.iShowFullSym!=0);

	m_PopupMenu.CheckItem(EVENT_ID_ADDRESS_MODE_HEX,m_AddrShowMode == CODE_VIEW_ADDRESS_MOD);
	m_PopupMenu.CheckItem(EVENT_ID_OFFSET_MODE_HEX,m_AddrShowMode == CODE_VIEW_OFFSET_MOD);
	m_PopupMenu.CheckItem(EVENT_ID_RELATIVE_TO_EIP,m_AddrShowMode == CODE_VIEW_REL_TO_EIP_MOD);

	m_PopupMenu.CheckItem(EVENT_ID_FM_AUTOMATIC,			SyserOption.iFollowMode == SYSER_FM_AUTOMATIC);
	m_PopupMenu.CheckItem(EVENT_ID_FM_SYSTEM_EXPLORER,		SyserOption.iFollowMode == SYSER_FM_SYSTEM_EXPLORER);
	m_PopupMenu.CheckItem(EVENT_ID_FM_SOURCE_CODE_EXPLORER,	SyserOption.iFollowMode == SYSER_FM_SOURCE_EXPLORER);

	m_PopupMenu.Popup();
}
void CCodeView::ToggleHighlight(IN WISP_MSG* pMsg)
{
	int Col;
	HANDLE hItem;
	WISP_RECT CellRect;
	int x,offset;	
	WCHAR szBuffer[512];	
	WISP_PCSTR pStr;
	int n,OldLen;
	CItemList::IT ItemIter;
	OldLen=TStrLen(m_HighlightString);
	Col = PointToItem(pMsg->MsgMouseCltPT,ItemIter);
	if(Col<1 || Col>LI_POS_CELL_AREA_END)
	{
		goto quit;
	}
	hItem= &(*ItemIter);
	if(hItem==NULL)
	{
		goto quit;
	}
	pStr=GetItemText(hItem,Col);
	if(pStr==NULL)
	{
		goto quit;
	}
	if(IsColorString(pStr))
	{
		TStrCpyLimit(szBuffer,GetColorString(pStr),512);
		pStr=szBuffer;
	}
	n = TStrLen(pStr);
	GetItemCellRect(hItem,Col,&CellRect);
	x = m_pWispBase->m_MousePT.x - m_ScrClientRect.x-CellRect.x ;//- m_TextMargin;
	offset = m_ClientDC.PixelOffToTextOff(pStr,x);
	if(offset==-1)
	{
		goto quit;
	}
	int nLastSpilte=0;
	if((pStr[offset]>='0'&&pStr[offset]<='9')||(pStr[offset]>='a'&&pStr[offset]<='z')||(pStr[offset]>='A'&&pStr[offset]<='Z')||pStr[offset]=='_')
	{
		for(int i=0;i<n;i++)
		{
			if((pStr[i]>='0'&&pStr[i]<='9')||(pStr[i]>='a'&&pStr[i]<='z')||(pStr[i]>='A'&&pStr[i]<='Z')||pStr[i]=='_')
				continue;
			if(i>offset)
			{
				TStrNCpy(m_HighlightString,pStr+nLastSpilte,i-nLastSpilte);
				m_HighlightString[i-nLastSpilte]=0;
				UpdateView();
				return;
			}
			nLastSpilte=i+1;
		}	
		TStrNCpy(m_HighlightString,pStr+nLastSpilte,n-nLastSpilte);
		m_HighlightString[n-nLastSpilte]=0;
		UpdateView();
		return;
	}
quit:
	if(OldLen)
	{
		m_HighlightString[0]=0;
		UpdateView();
	}	
}

bool CCodeView::OnStartAddressInc(IN WISP_MSG*pMsg)
{
	SetStartAddress(m_CurAddr+1);
	return false;
}
bool CCodeView::OnStartAddressDec(IN WISP_MSG*pMsg)
{
	SetStartAddress(m_CurAddr-1);
	return false;
}
bool CCodeView::OnKeyEvent(IN WISP_MSG*pMsg)
{
	CODEHOTKEYMAP::IT FindIT;
	WISP_MSG Msg;
	if(pMsg->KeyEvent.bKeyDown)
	{
		FindIT = m_HotKeyMap.Find(pMsg->KeyEvent.KeyType);
		if(FindIT != m_HotKeyMap.End())
		{
			memset(&Msg,0,sizeof(Msg));
			Msg.Command.CmdID=*FindIT;				
			return OnEvent(&Msg);						
		}

		switch(pMsg->KeyEvent.KeyType)
		{ 
		case WISP_VK_RBUTTON:
			PopupMenu(pMsg);
			break;
		case WISP_VK_LBUTTON:
			ToggleHighlight(pMsg);
			break;
		case WISP_VK_W:
			{
				int SizeXorY;
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.GetWndSpace(1,SizeXorY);
				if(SizeXorY>10)
					gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.ResizeWndSpace(1,SizeXorY-10);
				else
					gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.ResizeWndSpace(1,0);
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.AdjustWndPos();
				return false;
			}
			
			break;
		case WISP_VK_S:
			{
				int SizeXorY;
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.GetWndSpace(1,SizeXorY);				
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.ResizeWndSpace(1,SizeXorY+10);
				gpSyser->m_MainFrame.m_SystemExplorer.m_ViewSplitWnd.AdjustWndPos();
				return false;
				
			}
			break;

		}

	}
	return true;
}

bool CCodeView::OnChar(IN WISP_MSG*pMsg)
{
	if(pMsg->Char.Char>='a' && pMsg->Char.Char<='z')
	{
		gpSyser->m_MainFrame.m_SystemExplorer.m_TerminalWnd.Focus();
		WISP_MSG Msg = *pMsg;
		Msg.hWnd = &gpSyser->m_MainFrame.m_SystemExplorer.m_TerminalWnd;
		m_pWispBase->SendMessage(&Msg);
		return false;
	}
	return true;
}

bool CCodeView::OnSize(IN WISP_MSG*pMsg)
{
	SetScrollBarInfo(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,m_nLinePerPage*(m_ScrollSpace+m_ScrollSpace+1),m_nLinePerPage,0,false);
	UpdateView();
	return true;
}

bool CCodeView::OnGetFocus(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
	{
		hItem = GetFirstItem();
		if(hItem)
			SelectItem(hItem);
	}
	return true;
}

bool CCodeView::OnCreate(IN WISP_MSG*pMsg)
{
	m_ColorTable[COLOR_BK	   ]=ColorOption.clrCVBK;
	m_ColorTable[COLOR_ADDRESS ]=ColorOption.clrCVAddr;
	m_ColorTable[COLOR_PREFIX  ]=ColorOption.clrCVPrefix;
	m_ColorTable[COLOR_OPCODE  ]=ColorOption.clrCVOpCode;
	m_ColorTable[COLOR_REGISTER]=ColorOption.clrCVReg;
	m_ColorTable[COLOR_SEG_REG ]=ColorOption.clrCVSegReg;
	m_ColorTable[COLOR_IMMED   ]=ColorOption.clrCVImmed;
	m_ColorTable[COLOR_OPTR    ]=ColorOption.clrCVOptr;
	m_ColorTable[COLOR_SYMBOL  ]=ColorOption.clrCVSymbol;
	m_ColorTable[COLOR_COMMENT ]=ColorOption.clrCVComment;
	m_ColorTable[COLOR_KEYWORD ]=ColorOption.clrCVKeyword;
	m_ColorTable[COLOR_STR     ]=ColorOption.clrCVStr;
	m_ColorTable[COLOR_BPX_STRIP]=ColorOption.clrCVBPXStrip;
	m_ColorTable[COLOR_EIP_STRIP]=ColorOption.clrCVEIPStrip;
	m_ColorTable[COLOR_BPXEIP_STRIP]=ColorOption.clrCVBPXEIPStrip;
	m_ColorTable[COLOR_API_NAME]=ColorOption.clrCVAPIName;
	m_ColorTable[COLOR_API_PARAM_TYPE]=ColorOption.clrCVAPIParamType;
	m_ColorTable[COLOR_API_PARAM_NAME]=ColorOption.clrCVAPIParamName;
	m_ColorTable[COLOR_JMP_LINE]=ColorOption.clrCVJmpLine ;
	m_ColorTable[COLOR_ACTIVED_JMP_LINE]=ColorOption.clrCVActivedJmpLine;
	m_ColorTable[COLOR_PREFIX_BYTE]=ColorOption.clrCVPrefixByte;
	m_ColorTable[COLOR_OPCODE_BYTE]=ColorOption.clrCVOpcodeByte;
	m_ColorTable[COLOR_REGRM_BYTE]=ColorOption.clrCVRegRMByte;		//opcode 中 RegRM 字节的颜色
	m_ColorTable[COLOR_SIB_BYPE]=ColorOption.clrCVSIBByte;			//opcode 中 SIB 字节的颜色
	m_ColorTable[COLOR_OTHER_OPCODE_BYTE]=ColorOption.clrCVOtherOpcodeByte;		//opcode 中 其他字节的颜色
	m_ColorTable[COLOR_3DNOW_BYTE]=ColorOption.clrCV3DNowByte;//如果是3dNow 指令这个是immediate byte


	m_SelectBKColor = ColorOption.clrCVSelectedFrame;
	m_LostFocusSelBKColor = ColorOption.clrCVLostFocusSelFrame;
	m_ClientDC.SetColorTable(m_ColorTable);
	m_PopupMenu.CreatePopupMenu(CodeViewOperationMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_ColIconList.Load("\\SyserIcon\\CodeView.bmp",16,16,4);
	m_ColIconList.SetType(WISP_DIB_TK);
	m_ColIconList.SetColorKey(WISP_RGB(0,255,255));

	int FontWidth = m_ClientDC.GetTextExtent(WSTR("X"));
	InsertColumn(WSTR("Pic"),20,WISP_WLCS_FIXED);
	InsertColumn(WSTR("Address"),FontWidth*9+3,0);
	InsertColumn(WSTR("Bin"),FontWidth*15,0);
	InsertColumn(WSTR("Code"),FontWidth*35,0);
	InsertColumn(WSTR("Comment"),200,WISP_WLCS_EDITABLE);
	ShowColumnTitle(false);
	SetBGColor(m_ColorTable[COLOR_BK]);
	m_Style|=WISP_WLS_EMPTY_SEL_RECT|WISP_WLS_VERT_LINE;
	m_ScrollBar[WISP_SB_VERT]->Style=WISP_SS_NORMAL;
	m_ScrollBar[WISP_SB_VERT]->bHide = false;
	m_AddrShowMode = CODE_VIEW_ADDRESS_MOD;
	m_JmpLineSpace = 13;
	m_StateDIBList=WispTKDIBList("\\SyserApp\\LineMark.bmp",16,16);
	m_StateDIBList->SetColorKey(0);
	AttachShortcutKey();
	return true;
}



bool CCodeView::OnActiveCodeView(IN WISP_MSG*pMsg)
{
	DWORD NewAddr;
	DWORD Index;
	Index = pMsg->Command.CmdID;
	Index -= EVENT_ID_ACTIVE_CODEVIEW_0;
	CCodeView*pCodeView = (CCodeView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetWnd(Index);
	if(pCodeView==NULL)
	{
		pCodeView =(CCodeView*) gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.GetActiveWnd();
		NewAddr = ACTIVE_CODE_VIEW->m_CurAddr;
		pCodeView = ADD_CODE_VIEW(pCodeView);
		if(pCodeView==NULL)
			return false;
	}
	else
	{
		gpSyser->m_MainFrame.m_SystemExplorer.m_MultiCodeView.ChangeActiveWnd(pCodeView);
	}
	return true;
}

void CCodeView::AttachShortcutKey()
{
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_0,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_1,EVENT_ID_ACTIVE_CODEVIEW_0);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_1,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_2,EVENT_ID_ACTIVE_CODEVIEW_1);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_2,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_3,EVENT_ID_ACTIVE_CODEVIEW_2);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_3,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_4,EVENT_ID_ACTIVE_CODEVIEW_3);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_4,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_5,EVENT_ID_ACTIVE_CODEVIEW_4);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_5,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_6,EVENT_ID_ACTIVE_CODEVIEW_5);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_6,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_7,EVENT_ID_ACTIVE_CODEVIEW_6);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_7,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_8,EVENT_ID_ACTIVE_CODEVIEW_7);
	if(gpSyser->AttachShortcutKey(EVENT_ID_ACTIVE_CODEVIEW_8,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_ALT | WISP_VK_9,EVENT_ID_ACTIVE_CODEVIEW_8);
	if(gpSyser->AttachShortcutKey(EVENT_ID_TOGGLE_SYMBOL,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_TAB,					EVENT_ID_TOGGLE_SYMBOL);
	if(gpSyser->AttachShortcutKey(EVENT_ID_TOGGLE_FULL_SYMBOL,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_TAB|WISP_MOD_CTRL,		EVENT_ID_TOGGLE_FULL_SYMBOL);
	if(gpSyser->AttachShortcutKey(EVENT_ID_GETNEXTTRACE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_OEM_PLUS,				EVENT_ID_GETNEXTTRACE);
	if(gpSyser->AttachShortcutKey(EVENT_ID_GETPREVTRACE,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_OEM_MINUS,				EVENT_ID_GETPREVTRACE);
	if(gpSyser->AttachShortcutKey(EVENT_ID_PREV_POS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_BACK,					EVENT_ID_PREV_POS);
	if(gpSyser->AttachShortcutKey(EVENT_ID_NEXT_POS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_RETURN|WISP_MOD_CTRL,	EVENT_ID_NEXT_POS);
	if(gpSyser->AttachShortcutKey(EVENT_ID_FOLLOW_TO_DESTINATION,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_RETURN,				EVENT_ID_FOLLOW_TO_DESTINATION);
	if(gpSyser->AttachShortcutKey(EVENT_ID_SAVE_POS,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_RETURN|WISP_MOD_SHIFT, EVENT_ID_SAVE_POS);
	if(gpSyser->AttachShortcutKey(EVENT_ID_STARTADDRESS_DEC,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL|	WISP_VK_UP,		EVENT_ID_STARTADDRESS_DEC);
	if(gpSyser->AttachShortcutKey(EVENT_ID_STARTADDRESS_INC,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_MOD_CTRL|	WISP_VK_DOWN,	EVENT_ID_STARTADDRESS_INC);
	if(gpSyser->AttachShortcutKey(EVENT_ID_TOGGLE_BP,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_F9,					EVENT_ID_TOGGLE_BP);
	if(gpSyser->AttachShortcutKey(EVENT_ID_GOTO,m_HotKeyMap)==0)
		m_HotKeyMap.InsertUnique(WISP_VK_F7,					EVENT_ID_GOTO);


}

bool CCodeView::OnDestroy(IN WISP_MSG*pMsg)
{
	m_ColIconList.Destroy();
	m_PopupMenu.Destroy();
	return true;
}

bool CCodeView::OnScrollEvent(IN WISP_MSG*pMsg)
{
	int	CodeLen;	
	ULPOS StartAddr,EndAddr;
	if(pMsg->ScrollEvent.SBType==WISP_SB_VERT)
	{
		switch(pMsg->ScrollEvent.Event)
		{
		case WISP_SB_DEC:
			StartAddr = m_CurAddr;
			CodeLen=m_CurAddr - m_pCodeDoc->GetNextAddress(m_CurAddr,-1);
			if((LONGLONG)m_CurAddr-(LONGLONG)CodeLen>=(LONGLONG)m_pCodeDoc->m_DocRangeStart)
				StartAddr-=CodeLen;
			else
				StartAddr=(DWORD)m_pCodeDoc->m_DocRangeStart;
			SetStartAddress(StartAddr,false);
			break;
		case WISP_SB_INC:
			StartAddr = m_CurAddr;
			CodeLen=m_pCodeDoc->GetNextAddress(m_CurAddr,1) - m_CurAddr;
			if(StartAddr+CodeLen<m_pCodeDoc->m_DocRangeEnd)
			{
				StartAddr+=CodeLen;
				SetStartAddress(StartAddr,false);
			}
			break;
		case WISP_SB_PAGE_UP:
			StartAddr=m_pCodeDoc->GetNextAddress(m_CurAddr,-(m_nLinePerPage-1));
			if(StartAddr<m_pCodeDoc->m_DocRangeStart)
				StartAddr=m_pCodeDoc->m_DocRangeStart;
			SetStartAddress(StartAddr);
			break;
		case WISP_SB_PAGE_DOWN:
			GetCodeRange(&StartAddr,&EndAddr);
			SetStartAddress(EndAddr,false);
			break;
		case WISP_SB_POS_CHANGE:
			if(pMsg->ScrollEvent.Delta<0)
			{
				StartAddr=m_pCodeDoc->GetNextAddress(m_CurAddr,pMsg->ScrollEvent.Delta);
			}
			else
			{
				StartAddr=m_pCodeDoc->GetNextAddress(m_CurAddr,pMsg->ScrollEvent.Delta);
			}
			SetStartAddress(StartAddr,false);
			return false;
			break;
		}
		SetScrollBarCurPos(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace);
	}
	return false;
}

CCodeView::CCodeView()
{
	m_CurAddr = 0;
	m_ScrollSpace = 2;
	m_AddrIter = m_AddrList.End();
	m_HighlightString[0]=0;
}

CCodeView::~CCodeView()
{
	m_AddrList.Clear();
}

void CCodeView::UpdateCodeViewAddrSym()
{
	ULPOS Address;
	int Length;
	CHAR szSymbol[256];
	WCHAR szBuffer[512];
#ifdef CODE_OS_NT_DRV
	Length = TStrCpy(szBuffer,(PCWSTR)gpSyser->m_pDebugger->m_ProcNameW);
#else
	Length = AnsiToUnicode(TGetFileName((PCSTR)gpSyser->m_SyserUI.m_CodeDoc.m_MainModuleName),szBuffer,512);
#endif
	Address = m_CurAddr;
	//Address = *X86_REG_PTR.pEIP;
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
	if(pDbgModule==NULL&&gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
		pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
	if(pDbgModule)
	{
		Length+=TStrCpy(&szBuffer[Length],WSTR(" : "));
		Length+=AnsiToUnicode(pDbgModule->m_ModuleTitle,&szBuffer[Length],512-Length);
		if(gpSyser->m_SyserUI.GetAlmostSym(Address,szSymbol))
		{
			Length+=TStrCpy(&szBuffer[Length],WSTR("!"));
			Length+=TStrCpy(&szBuffer[Length],szSymbol);			
		}
		else
		{
			Length+=TSPrintf(&szBuffer[Length],WSTR("+%X"),Address-pDbgModule->m_ModuleBase);
		}
	}
	gpSyser->m_MainFrame.m_TipStr.SetWindowText(szBuffer);
}


void CCodeView::SetStartAddress(ULPOS Address,bool bRecordAddr)
{
	WISP_CHAR szBuffer[64];
	ULPOS uPrevPos;
	int Index;
	uPrevPos=m_CurAddr;
	if(Address == m_CurAddr)
		return;
	Index = 0;
	m_CurAddr = Address;
	for(CTabWndList::IT Iter=SYSTEM_EXPLORER.m_MultiCodeView.m_WndList.Begin();
		Iter!=SYSTEM_EXPLORER.m_MultiCodeView.m_WndList.End();Iter++)
	{
		if(Iter->pWnd==this)
		{
			TSPrintf(szBuffer,WSTR("%08X"),m_CurAddr);
			SYSTEM_EXPLORER.m_MultiCodeView.SetTabText(Index,szBuffer);
		}
		Index++;
	}
	if(this == gpSyser->m_MainFrame.m_SystemExplorer.m_pCurCodeView)
	{
		UpdateCodeViewAddrSym();
	}
	if(bRecordAddr && m_CurAddr!=0)
	{
		RecordCurAddr(m_CurAddr,uPrevPos);
	}
	UpdateView();
	Update();
}

void  CCodeView::RecordCurAddr(ULPOS Address,ULPOS PrevAddress)
{
	if(m_AddrList.Count()>MAX_POS_LIST_COUNT)
	{
		if(m_AddrIter==m_AddrList.Begin())
			m_AddrIter++;
		m_AddrList.Remove(m_AddrList.Begin());
	}
	if(m_AddrList.Count()==0 && Address!=PrevAddress)
		m_AddrIter = m_AddrList.Append(PrevAddress);
	if( Address!= *m_AddrList.Last())
		m_AddrIter = m_AddrList.Append(Address);
	SYSTEM_EXPLORER.UpdateItemState();	
}

void  CCodeView::CenterVisibleAddress(ULPOS Address)
{
	HANDLE hItem;
	ULPOS NewAddress,ItemAddr;
	NewAddress = m_pCodeDoc->GetNextAddress(Address,-m_nLinePerPage/2);
	SetStartAddress(NewAddress);
	hItem = GetScrStartItem();
	while(hItem)
	{
		ItemAddr = (ULPOS) GetItemData(hItem,ITEM_ADDRESS);
		if(ItemAddr==Address)
		{
			SelectItem(hItem);
			break;
		}
		hItem = GetNextItem(hItem);
	}
}

void CCodeView::GetCodeRange(DWORD*pStart,DWORD*pEnd)
{
	*pStart = m_CurAddr;
	*pEnd=m_pCodeDoc->GetNextAddress(*pStart,m_nLinePerPage-1);
}

void CCodeView::UpdateViewAPICall(ULPOS Address,PCSTR szAPIName,HANDLE hItem,int nLine)
{
	CWispString*pColorString;
	WISP_COLOR_CHAR*pColorStr;
	int Length,Count;
	DWORD CodeBuffer;
	WISP_COLOR_CHAR szBuffer[1024];
	WCHAR wszBuffer[256];
	PCSTR pParamStr,pParamStrEnd;
	CAPIMap::IT APIIter = gpSyser->m_SyserUI.m_APIMap.Find(szAPIName);
	if(APIIter.IsExist()==false)
		return;
	Length =ColorStrCpy(szBuffer,(PCSTR)APIIter->Return,COLOR_API_PARAM_TYPE,COLOR_BK);
	Length+=ColorStrCpy(&szBuffer[Length]," ",COLOR_BK,COLOR_BK);
	Length+=ColorStrCpy(&szBuffer[Length],(PCSTR)APIIter.Key(),COLOR_API_NAME,COLOR_BK);
	Length+=ColorStrCpy(&szBuffer[Length],"(",COLOR_OPTR,COLOR_BK);
	for(TList<CStrA>::IT ParamIter=APIIter->ParamList.Begin();ParamIter!=APIIter->ParamList.End();ParamIter++)
	{
		pParamStrEnd=NULL;
		pParamStr = TStrRChr((PCSTR)*ParamIter,' ');
		if(pParamStr)
		{
			if(TStrCmp(&pParamStr[1],"OPTIONAL")==0)
			{
				pParamStrEnd = pParamStr;
				pParamStr = TStrRChr((PCSTR)*ParamIter,pParamStr-1,' ');
				if(pParamStr==NULL)
					pParamStr = (PCSTR)*ParamIter;
			}
			Count = TCountOfChar((PCSTR)*ParamIter,' ');
			if(Count==1)
			{
				if(TStrNCmp((PCSTR)*ParamIter,"IN ",3)==0 || TStrNCmp((PCSTR)*ParamIter,"OUT ",4)==0)
					pParamStr=NULL;
			}
			else if(Count==2)
			{
				if(TStrNCmp((PCSTR)*ParamIter,"IN OUT ",7)==0)
					pParamStr=NULL;
			}
		}
		if(pParamStr)
		{
			TStrCpyLimit(wszBuffer,(PCSTR)*ParamIter,(int)(pParamStr-(PCSTR)*ParamIter)+1);
			Length+=/*@@*/ColorStrCpy(&szBuffer[Length],wszBuffer,COLOR_API_PARAM_TYPE,COLOR_BK);
			if(pParamStrEnd)
				TStrCpyLimit(wszBuffer,pParamStr,(int)(pParamStrEnd-pParamStr)+1);
			else
				TStrCpy(wszBuffer,pParamStr);
			Length+=ColorStrCpy(&szBuffer[Length],wszBuffer,COLOR_API_PARAM_NAME,COLOR_BK);
			if(pParamStrEnd)
			{
				TStrCpy(wszBuffer,pParamStrEnd);
				Length+=ColorStrCpy(&szBuffer[Length],wszBuffer,COLOR_API_PARAM_TYPE,COLOR_BK);
			}
		}
		else
		{
			Length+=ColorStrCpy(&szBuffer[Length],(PCSTR)*ParamIter,COLOR_API_PARAM_TYPE,COLOR_BK);
		}
		if(ParamIter!=APIIter->ParamList.Last())
			Length+=ColorStrCpy(&szBuffer[Length],",",COLOR_OPTR,COLOR_BK);
	}
	Length+=ColorStrCpy(&szBuffer[Length],")",COLOR_OPTR,COLOR_BK);
	SetItemColorText(hItem,4,szBuffer);
	if(APIIter->CallType==TYPE_STDCALL)
	{
		TList<CStrA>::IT ParamIter = APIIter->ParamList.Begin();
		while(nLine>0 && ParamIter!=APIIter->ParamList.End())
		{
			nLine--;
			hItem = GetPrevItem(hItem);
			if(hItem==NULL)
				break;
			pColorString=&GetItemText(hItem,ITEM_COMMENT);
			if(IsColorString(pColorString->m_pData))
			{//次行已经是彩色注解行，表示是上个函数的参数
				continue;
			}
			pColorString=&GetItemText(hItem,ITEM_ASM_CODE);
			if(pColorString->Length()>0)
			{
				CodeBuffer=(DWORD)GetItemData(hItem,ITEM_BIN_DATA);
				if(CInstrSym::GetNearJmpDes((BYTE*)&CodeBuffer))
					break;
				pColorStr = (WISP_COLOR_CHAR*)&pColorString->m_pData[2];
				if(TStrNICmp(pColorStr,"PUSH",4)==0)
				{					
					Address = (ULPOS)GetItemData(hItem,ITEM_ADDRESS);
					pParamStrEnd=NULL;
					pParamStr = TStrRChr((PCSTR)*ParamIter,' ');
					if(pParamStr)
					{
						if(TStrCmp(&pParamStr[1],"OPTIONAL")==0)
						{
							pParamStrEnd = pParamStr;
							pParamStr = TStrRChr((PCSTR)*ParamIter,pParamStr-1,' ');
							if(pParamStr==NULL)
								pParamStr = (PCSTR)*ParamIter;
						}
						Count = TCountOfChar((PCSTR)*ParamIter,' ');
						if(Count==1)
						{
							if(TStrNCmp((PCSTR)*ParamIter,"IN ",3)==0 || TStrNCmp((PCSTR)*ParamIter,"OUT ",4)==0)
								pParamStr=NULL;
						}
						else if(Count==2)
						{
							if(TStrNCmp((PCSTR)*ParamIter,"IN OUT ",7)==0)
								pParamStr=NULL;
						}
					}
					if(pParamStr)
					{
						TStrCpyLimit(wszBuffer,(PCSTR)*ParamIter,(int)(pParamStr-(PCSTR)*ParamIter)+1);
						Length=/*@@*/ColorStrCpy(szBuffer,wszBuffer,COLOR_API_PARAM_TYPE,COLOR_BK);
						if(pParamStrEnd)
							TStrCpyLimit(wszBuffer,pParamStr,(int)(pParamStrEnd-pParamStr)+1);
						else
							TStrCpy(wszBuffer,pParamStr);
						Length+=ColorStrCpy(&szBuffer[Length],wszBuffer,COLOR_API_PARAM_NAME,COLOR_BK);
						if(pParamStrEnd)
						{
							TStrCpy(wszBuffer,pParamStrEnd);
							Length+=ColorStrCpy(&szBuffer[Length],wszBuffer,COLOR_API_PARAM_TYPE,COLOR_BK);
						}
					}
					else
					{
						ColorStrCpy(szBuffer,(PCSTR)*ParamIter,COLOR_API_PARAM_TYPE,COLOR_BK);
					}
					SetItemColorText(hItem,ITEM_COMMENT,szBuffer);
					ParamIter++;
				}
			}
		}
	}
}

//Col 0 Data   ->   每行对应的地址的Mark
//Col 1 Data   ->   每行对应的地址
//Col 2 Data   ->   代码数据的DWORD
//Col 3 Data   ->   NearJmp 目的地址

bool CCodeView::UpdateView()
{
	HANDLE hItem;
	BYTE CodeBuffer[MAX_INSTR_LEN];
	WISP_COLOR_CHAR szOpcodeColorBuffer[120];
	WISP_COLOR_CHAR szColorBuffer[256];
	WISP_CHAR szBuffer[256];
	WISP_CHAR* pszBuf;
	ULPOS Address,NearJmpDes;
	int nHighlightLen=0;
	ULSIZE CodeLen;
	INSTRUCTION_INFORMATION DasmInstr;
	bool bLabel = false;
	int StrType;
	SetItemChildCount(NULL,m_nLinePerPage);
	Address = m_CurAddr;
	hItem = GetNextItem();
	STZeroMemory(DasmInstr);
	memset(CodeBuffer,0xff,sizeof(CodeBuffer));
	nHighlightLen = TStrLen(m_HighlightString);
	for(int n=0;n<m_nLinePerPage && hItem;n++)
	{
		szColorBuffer[0]=0;
		DasmInstr.CodeBuff=CodeBuffer;

		CodeLen = ColorDasm(Address,MAX_INSTR_LEN,szColorBuffer,0,&DasmInstr,CodeBuffer);
		NearJmpDes = 0;
		if(CodeLen>=2)
			CInstrSym::GetNearJmpDes(CodeBuffer,Address,&NearJmpDes);
		TStrCpy(szBuffer,szColorBuffer);
		pszBuf=szBuffer;
		if(nHighlightLen)
		{
			while(pszBuf=TStrIStr(pszBuf,m_HighlightString))
			{
				for(int iii=0;iii<nHighlightLen;iii++)
				{
					szColorBuffer[pszBuf-szBuffer+iii]=(szColorBuffer[pszBuf-szBuffer+iii]&0xffffff)+(10<<24);
				}
				pszBuf+=nHighlightLen;
			}
		}
		
		
		SetItemData(hItem,ITEM_ADDRESS,Address);
		if(bLabel==false && m_pCodeDoc->GetLabel(Address,szBuffer,sizeof(szBuffer)/sizeof(WCHAR)))
		{
			SetItemData(hItem,ITEM_STATE,COLOR_NULL);
			SetItemData(hItem,ITEM_ASM_CODE,0);
			SetItemText(hItem,ITEM_STATE,WSTR(""));
			SetItemText(hItem,ITEM_ADDRESS,WSTR(""));
			SetItemText(hItem,ITEM_BIN_DATA,WSTR(""));
			SetItemTextColor(hItem,ITEM_ASM_CODE,m_ColorTable[COLOR_SYMBOL]);
			SetItemText(hItem,ITEM_ASM_CODE,szBuffer);
			SetItemText(hItem,ITEM_COMMENT,WSTR(""));
			bLabel = true;
			hItem = GetNextItem(hItem);
			continue;
		}
		SetItemData(hItem,ITEM_STATE,m_pCodeDoc->GetLineMark(Address));
		SetItemTextColor(hItem,ITEM_ADDRESS,m_ColorTable[COLOR_ADDRESS]);
		GetAddressString(Address,szBuffer);
		SetItemText(hItem,ITEM_ADDRESS,szBuffer);
		int nlen=0;
		if(CodeLen>=1 && DasmInstr.OpCode!=-1)
		{
			int bskip=false;
			for(int qq=0;(ULSIZE)qq<CodeLen;qq++)
			{
				THexBytesToStr(CodeBuffer+qq,szBuffer,1,1);
				if(qq<DasmInstr.PrefixLen)
				{
					nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],szBuffer,COLOR_PREFIX_BYTE,COLOR_BK);
				}
				else if(qq >=DasmInstr.PrefixLen && qq <DasmInstr.PrefixLen+DasmInstr.OpcodeLen)
				{
					if(qq==DasmInstr.PrefixLen && qq)
					{
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],":",COLOR_OPCODE_BYTE,COLOR_BK);
					}
					nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],szBuffer,COLOR_OPCODE_BYTE,COLOR_BK);
				}
				else
				{
					if(DasmInstr.Have_RegRM!=-1 && (DasmInstr.PrefixLen+DasmInstr.OpcodeLen)==qq)
					{
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen]," ",COLOR_REGRM_BYTE,COLOR_BK);
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],szBuffer,COLOR_REGRM_BYTE,COLOR_BK);
					}
					else if(DasmInstr.Have_SIB!=-1 && (DasmInstr.PrefixLen+DasmInstr.OpcodeLen+1)==qq)
					{
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen]," ",COLOR_SIB_BYPE,COLOR_BK);
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],szBuffer,COLOR_SIB_BYPE,COLOR_BK);
					}
					else if(DasmInstr.Is3DNow!=-1 && qq == (CodeLen-1))
					{
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen]," ",COLOR_3DNOW_BYTE,COLOR_BK);
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],szBuffer,COLOR_3DNOW_BYTE,COLOR_BK);
					}
					else
					{ 
						if(bskip==false)
						{
							nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen]," ",COLOR_OTHER_OPCODE_BYTE,COLOR_BK);
							bskip=true;
						}
						nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],szBuffer,COLOR_OTHER_OPCODE_BYTE,COLOR_BK);
					}
				}
			}
			//THexBytesToStr(CodeBuffer,szBuffer,CodeLen,1);
		}
		else
		{
			THexBytesToStr(CodeBuffer,szBuffer,1,1);
			nlen+=ColorStrCpy(&szOpcodeColorBuffer[nlen],szBuffer,COLOR_API_PARAM_TYPE,COLOR_BK);
		}
		//SetItemTextColor(hItem,ITEM_BIN_DATA,m_ColorTable[COLOR_IMMED]);
		//SetItemText(hItem,ITEM_BIN_DATA,szBuffer);
		SetItemColorText(hItem,ITEM_BIN_DATA,szOpcodeColorBuffer);
		SetItemData(hItem,ITEM_BIN_DATA,_GET_DWORD(CodeBuffer));
		SetItemColorText(hItem,ITEM_ASM_CODE,szColorBuffer);
		
		SetItemData(hItem,ITEM_ASM_CODE,NearJmpDes);
		*szBuffer=0;
		SetItemTextColor(hItem,ITEM_COMMENT,m_ColorTable[COLOR_COMMENT]);
		SetItemText(hItem,ITEM_COMMENT,szBuffer);
		
		if(m_pCodeDoc->GetComment(Address,szBuffer,sizeof(szBuffer)/sizeof(WCHAR)))
		{			
			SetItemText(hItem,ITEM_COMMENT,szBuffer);
		}
		else
		{
			ULPOS DestAddr,Immed,Count;
			bool bImmed=false;
			Count = m_pCodeDoc->GetInstrImmediateAndDesAddress(Address,&DestAddr,&Immed);
			if(Count)
			{
				if(Immed!=0-1)
				{
					if(GET_STRING_SYM(Immed,szBuffer,sizeof(szBuffer)/sizeof(szBuffer[0]),StrType))
					{
						SetItemText(hItem,ITEM_COMMENT,szBuffer);
						bImmed=true;
					}					
				}
				if(!bImmed && DestAddr!=0-1)
				{
					if(GET_STRING_SYM(DestAddr,szBuffer,sizeof(szBuffer)/sizeof(szBuffer[0]),StrType))
					{
						SetItemText(hItem,ITEM_COMMENT,szBuffer);						
					}
				}
			}
			else
			{
				szColorBuffer[0]=0;
				if(gpSyser->m_SyserUI.m_CodeDoc.IsOpened()  && Address==*X86_REG_PTR.pEIP)
				{
					m_pCodeDoc->GetCurInstrInfoEx(szColorBuffer,sizeof(szColorBuffer)/sizeof(szColorBuffer[0]));
					SetItemColorText(hItem,ITEM_COMMENT,szColorBuffer);			
				}
			}
		}
		
		bLabel = false;
		if(TStrNICmp(szColorBuffer,"CALL",4)==0 && DasmInstr.op->mode == mode_symbol)
		{//API参数分析
			UpdateViewAPICall(Address,DasmInstr.op->symbol.string,hItem,n);
		}
		m_LastAddr = Address;
		Address = m_pCodeDoc->GetNextAddress(Address,1);
		hItem = GetNextItem(hItem);
	}
	UpdateNearJmpState();
	Update();
	return true;
}

bool CCodeView::GetItemLineByAddr(ULPOS Address,int *pLine)
{
	int Line;
	HANDLE hItem;
	if(Address<m_CurAddr || Address>m_LastAddr)
		return false;
	Line = 0;
	hItem = GetScrStartItem();
	while(hItem)
	{
		if(Address == (ULPOS)GetItemData(hItem,1))
		{
			if(pLine)
				*pLine = Line;
			return true;
		}
		hItem = GetNextItem(hItem);
		Line++;
	}
	return false;
}

void CCodeView::UpdateNearJmpState()
{
	int StartLine,EndLine;
	HANDLE hItem;
	ULPOS DesAddr;
	NUM_PTR CodeData;
	m_NearJmpCount = 0;
	m_iActivedNearJmp = -1;
	hItem = GetScrStartItem();
	StartLine = 0;
	while(hItem && m_NearJmpCount<MAX_JMP_LINE_COUNT)
	{
		DesAddr = (ULPOS)GetItemData(hItem,ITEM_ASM_CODE);
		if(DesAddr && GetItemLineByAddr(DesAddr,&EndLine))
		{
			m_NearJmpPos[m_NearJmpCount].StartAddr = (ULPOS) GetItemData(hItem,1);
			m_NearJmpPos[m_NearJmpCount].StartLine = StartLine;
			m_NearJmpPos[m_NearJmpCount].EndAddr = DesAddr;
			m_NearJmpPos[m_NearJmpCount].EndLine = EndLine;
			if(m_NearJmpPos[m_NearJmpCount].StartAddr == *X86_REG_PTR.pEIP)
			{
				CodeData = GetItemData(hItem,ITEM_BIN_DATA);
				if(CInstrSym::IsActiveNearJmp((PBYTE)&CodeData,*(DWORD*)X86_REG_PTR.pEFL))
				{
					m_iActivedNearJmp = m_NearJmpCount;
				}
			}
			m_NearJmpCount++;
		}
		hItem = GetNextItem(hItem);
		StartLine++;
	}
}

void CCodeView::DrawJmpLine(NEAR_JMP_ENRTY*pEntry,int Index,COLORREF Color)
{
	int x1,y1,x2,y2;
	x1 = Index*(m_JmpLineSpace/m_NearJmpCount)+2;
	x2 = m_JmpLineSpace;
	y1 = pEntry->StartLine*m_ButtonSize.cy+m_ButtonSize.cy/2;
	y2 = pEntry->EndLine*m_ButtonSize.cy+m_ButtonSize.cy/2;
	m_ClientDC.DrawHLine(x1,x2,y1,Color);//Start
	m_ClientDC.DrawVLine(x2,y1-3,y1+3,Color);//End
	m_ClientDC.DrawHLine(x1,x2,y2,Color);//End
	m_ClientDC.DrawLine(x2-2,y2-2,x2,y2,Color);//End
	m_ClientDC.DrawLine(x2-2,y2+2,x2,y2,Color);//End
	m_ClientDC.DrawVLine(x1,y1,y2,Color);//Midway
}

bool CCodeView::OnUpdateClient(IN WISP_MSG*pMsg)
{
	UINT Mark;
	int SelJmpLineIndex;
	HANDLE hItem;
	ULPOS SelJmpSrcAddr;
	CWispList::OnUpdateClient(pMsg);
	WISP_RECT rc;
	rc.cx=16,rc.cy=16,rc.x=2;
	rc.y=m_TitleHeight;
	hItem = GetScrStartItem();
	while(hItem)
	{
		Mark = (UINT)GetItemData(hItem,ITEM_STATE);
		if(Mark&CV_MARK_BOOK_MARK)
			m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(1));
		if(Mark&CV_MARK_EIP)
			m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(0));
		if(Mark&CV_MARK_BPX)
			m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(2));
		else if(Mark&CV_MARK_DISABLED_BPX)
			m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(3));
		rc.y+=m_ButtonSize.cy;
		hItem = GetNextItem(hItem);
	}
	hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	SelJmpSrcAddr = hItem ? (ULPOS)GetItemData(hItem,ITEM_ADDRESS) : 0;
	SelJmpLineIndex = -1;
	for(int n=0;n<m_NearJmpCount;n++)
	{
		if(n!=m_iActivedNearJmp)
		{
			if(SelJmpSrcAddr==0 || SelJmpSrcAddr != m_NearJmpPos[n].StartAddr)
				DrawJmpLine(&m_NearJmpPos[n],n,m_ColorTable[COLOR_JMP_LINE]);
			else
				SelJmpLineIndex = n;
		}
	}
	if(SelJmpLineIndex>=0)
	{//选择中的最后画，保证不被覆盖
		DrawJmpLine(&m_NearJmpPos[SelJmpLineIndex],SelJmpLineIndex,ColorOption.clrCVSelectedFrame);
	}
	if(m_iActivedNearJmp>=0 && m_iActivedNearJmp<m_NearJmpCount)
	{
		DrawJmpLine(&m_NearJmpPos[m_iActivedNearJmp],m_iActivedNearJmp,m_ColorTable[COLOR_ACTIVED_JMP_LINE]);
	}
	return false;
}


ULSIZE CCodeView::ColorDasm(ULPOS EIP,ULSIZE MaxSize,WISP_COLOR_CHAR*pColorString,ULSIZE nCodeAlgn,INSTRUCTION_INFORMATION* pDasmInstr,BYTE* CodeBuff)
{
	ULSIZE	Len;
	BYTE	Buffer[64];
	WCHAR	szBuffer[64];
	INSTRUCTION_INFORMATION DasmInstr;

	if(CodeBuff)
		DasmInstr.CodeBuff = CodeBuff;
	else
		DasmInstr.CodeBuff = Buffer;
	DasmInstr.eip = EIP;
	DasmInstr.pasm = NULL;
	Len = m_pCodeDoc->Dasm(&DasmInstr,NULL,MaxSize);
	if(nCodeAlgn)
	{
		if(DasmInstr.OpCode==-1)
		{
			ColorStrCpy(pColorString,WSTR("??"),COLOR_IMMED,0);
		}
		else
		{
			THexBytesToStr(DasmInstr.CodeBuff,szBuffer,Len,1);
			ColorStrCpy(pColorString,szBuffer,COLOR_IMMED,0);
		}
		pColorString+=TStrFillTail(pColorString,nCodeAlgn,(WISP_COLOR_CHAR)' ');
	}
	InstrToCS(&DasmInstr,pColorString);
	if(pDasmInstr)
	{
		*pDasmInstr=DasmInstr;
		if(CodeBuff==NULL)
			pDasmInstr->CodeBuff=NULL;
	}
	return Len;
}

WISP_COLOR_CHAR*CCodeView::InstrToCS(const INSTRUCTION_INFORMATION*pDasmInstr,WISP_COLOR_CHAR*pColorString)
{
	bool bFirstStr = TRUE;
	///////////////////////////////////////////////////
	//画LOCK前缀
	///////////////////////////////////////////////////
	if(pDasmInstr->Lock!=-1)
	{
		ColorStrCpy(pColorString,pDasmInstr->LockName,COLOR_PREFIX,0);
		ColorStrCat(pColorString," ",0,0);
		if(bFirstStr)//如果存在此项且未使用对齐
		{
			pColorString+=TStrFillTail(pColorString,m_pCodeDoc->m_UxAlign,(WISP_COLOR_CHAR)' ');
			bFirstStr = FALSE;
		}
		else
			pColorString+=TStrLen(pColorString);
	}
	///////////////////////////////////////////////////
	//画REP前缀
	///////////////////////////////////////////////////
	if(pDasmInstr->Repeat!=-1)
	{
		ColorStrCpy(pColorString,pDasmInstr->RepeatName,COLOR_PREFIX,0);
		ColorStrCat(pColorString," ",0,0);
		if(bFirstStr)//如果存在此项且未使用对齐
		{
			pColorString+=TStrFillTail(pColorString,m_pCodeDoc->m_UxAlign,(WISP_COLOR_CHAR)' ');
			bFirstStr = FALSE;
		}
		else
			pColorString+=TStrLen(pColorString);
		pColorString+=TStrLen(pColorString);
	}
	///////////////////////////////////////////////////
	//画OPCODE
	///////////////////////////////////////////////////
	ColorStrCpy(pColorString,pDasmInstr->Name,COLOR_OPCODE,0);
	ColorStrCat(pColorString," ",0,0);
	if(*pDasmInstr->Name && bFirstStr)//如果存在此项且未使用对齐
	{
		pColorString+=TStrFillTail(pColorString,m_pCodeDoc->m_UxAlign,(WISP_COLOR_CHAR)' ');
		bFirstStr = FALSE;
	}
	else
		pColorString+=TStrLen(pColorString);
	///////////////////////////////////////////////////
	//画操作元素
	///////////////////////////////////////////////////
	return OptItemToCS(pDasmInstr->op,3,pColorString,pDasmInstr);
}


WISP_COLOR_CHAR*CCodeView::OptItemToCS(const OPERAND_ITEM*OpArray,int nOp,WISP_COLOR_CHAR*pColorString,const INSTRUCTION_INFORMATION*pDasmInstr)
{
	DIS_ADDRESS*pAddr;
	const OPERAND_ITEM*pOp;
	WCHAR szBuffer[32];
	for(int n=0;n<nOp;n++)
	{
		pOp=&OpArray[n];
		if(pOp->mode==mode_invalid)
			break;
		if(n>0)
		{//画操作数间隔符
			pColorString+=ColorStrCpy(pColorString,",",COLOR_OPTR,0);
		}
		if(pOp->mode==mode_address)
		{//分析地址结构
			pAddr=(DIS_ADDRESS*)&pOp->addr;
			if(pOp->opersize!=-1)
			{
				pColorString+=ColorStrCpy(pColorString,CInstrSym::m_SizeSym[pOp->opersize],COLOR_KEYWORD,0);
				pColorString+=ColorStrCpy(pColorString," PTR ",COLOR_KEYWORD,0);
			}

			if(pDasmInstr->SegmentPrefix!=-1)
			{
				pColorString+=ColorStrCpy(pColorString,CInstrSym::m_SegStr[pDasmInstr->SegmentPrefix],COLOR_SEG_REG,0);
				pColorString+=ColorStrCpy(pColorString,":",COLOR_OPTR,0);
			}
			pColorString+=ColorStrCpy(pColorString,"[",COLOR_OPTR,0);
			if(pAddr->base!=-1)//画Base寄存器
			{
				pColorString+=ColorStrCpy(pColorString,CInstrSym::m_RegStr[pAddr->address_size][pAddr->base],COLOR_REGISTER,0);
			}
			if(pAddr->index!=-1)//画Index寄存器
			{
				if(pAddr->base!=-1)
				{
					pColorString+=ColorStrCpy(pColorString,"+",COLOR_OPTR,0);
				}
				pColorString+=ColorStrCpy(pColorString,CInstrSym::m_RegStr[pAddr->address_size][pAddr->index],COLOR_REGISTER,0);
				if(pAddr->scale>=1)
				{
					pColorString+=ColorStrCpy(pColorString,"*",COLOR_OPTR,0);
					pColorString+=ColorStrCpy(pColorString,CInstrSym::m_ScaleStr[pAddr->scale],COLOR_OPTR,0);
				}
			}
			if(pAddr->displacement_size || (pAddr->base==-1 && pAddr->index==-1))
			{//画displacement
				if(pAddr->index!=-1 || pAddr->base!=-1)
				{
					if(pAddr->displacement_size==1 && pAddr->displacement>=0xFFFFFF00)
					{
						pColorString+=ColorStrCpy(pColorString,"-",COLOR_OPTR,0);
						TSPrintf(szBuffer,CInstrSym::m_SizePtr[pAddr->displacement_size],-(int)pAddr->displacement);
					}
					else
					{
						pColorString+=ColorStrCpy(pColorString,"+",COLOR_OPTR,0);
						TSPrintf(szBuffer,CInstrSym::m_SizePtr[pAddr->displacement_size],pAddr->displacement);

					}
				}
				else
					TSPrintf(szBuffer,CInstrSym::m_SizePtr[pAddr->displacement_size],pAddr->displacement);
				pColorString+=ColorStrCpy(pColorString,szBuffer,COLOR_IMMED,0);
			}
			pColorString+=ColorStrCpy(pColorString,"]",COLOR_OPTR,0);
		}
		else
		{		
			switch(pOp->mode)
			{
				case mode_register:
					pColorString+=ColorStrCpy(pColorString,pOp->string,COLOR_REGISTER,0);
					break;
				case mode_segment:
					pColorString+=ColorStrCpy(pColorString,pOp->string,COLOR_SEG_REG,0);
					break;
				case mode_far:
					TSPrintf(szBuffer,WSTR("%04X"),pOp->farptr.segment);
					pColorString+=ColorStrCpy(pColorString,szBuffer,COLOR_IMMED,0);
					pColorString+=ColorStrCpy(pColorString,WSTR(":"),COLOR_OPTR,0);
					TSPrintf(szBuffer,CInstrSym::m_SizePtr[pOp->opersize-2],pOp->farptr.offset);
					pColorString+=ColorStrCpy(pColorString,szBuffer,COLOR_IMMED,0);
					break;
				case mode_near:
					pColorString+=ColorStrCpy(pColorString,pOp->string,COLOR_IMMED,0);
					break;
				case mode_immed:
					pColorString+=ColorStrCpy(pColorString,pOp->string,COLOR_IMMED,0);
					break;
				case mode_datadup:
					if(n>0)
						break;
					for(n=0;n<pOp->datadup.count;n++)
					{
						if(n>0)
						{
							pColorString+=ColorStrCpy(pColorString,",",COLOR_OPTR,0);
						}
						TSPrintf(szBuffer,WSTR("%02X"),pOp->datadup.buffer[n]);
						pColorString+=ColorStrCpy(pColorString,szBuffer,COLOR_IMMED,0);
					}
					break;
				case mode_symbol:
					if(pOp->symbol.offset)
					{
						pColorString+=ColorStrCpy(pColorString,"OFFSET ",COLOR_KEYWORD,0);
					}
					pColorString+=ColorStrCpy(pColorString,pOp->symbol.string,COLOR_SYMBOL,0);
					break;
				case mode_align:
					if(n>0)
						break;
					TSPrintf(szBuffer,WSTR("%X"),pOp->align.nBytes);
					pColorString+=ColorStrCpy(pColorString,szBuffer,COLOR_IMMED,0);
					break;
			}
		}
	}
	return pColorString;
}

bool CCodeView::OnEventToggleBreakPoint(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	if(gpSyser->m_pDebugger==NULL||gpSyser->m_SyserUI.m_CodeDoc.IsOpened()==false)
		return true;
	hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return false;
	Address = (ULPOS)GetItemData(hItem,1);
	gpSyser->m_SyserUI.ToggleCodeBP(Address);
	return false;
}

bool CCodeView::OnEventToggleBreakPointState(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	hItem = GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return false;
	Address = (ULPOS)GetItemData(hItem,ITEM_ADDRESS);
	gpSyser->m_SyserUI.ToggleCodeBPState(Address);
	return false;
}

bool CCodeView::OnEventToggleBookMarks(IN WISP_MSG*pMsg)
{
	SYSTEM_EXPLORER.m_MultiCodeView.ToggleBookMark();
	return false;
}

