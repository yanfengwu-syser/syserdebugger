#include "StdAfx.h"
#include "SyserSymAnalyzer.h"
#include "SourceCodeWnd.h"
#include "Syser.h"
#include "Lex2.h"

WISP_MENU_RES_ITEM SourceCodeWndMenu[]=
{
	{WSTR("Insert/Remove  Breakpoint         F9"),		EVENT_ID_TOGGLE_BP,			15*16+3},
	{WSTR("Enable/Disable Breakpoint"),					EVENT_ID_TOGGLE_BP_STATE,	15*16+4},
	{WSTR("Toggle BookMark                   Ctrl+K"),	EVENT_ID_BOOKMARK_TOGGLE,	13*16},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Go To Line                        Ctrl+G"),	EVENT_ID_GOTOLINE,	16*16+11},
	{WSTR("Go To Here                        F7"),		EVENT_ID_GOTO,		16*16+13},
	//{WSTR("Set EIP To Here"),							EVENT_ID_SET_EIP,	16*16+15},//内核调试中可能弄垮机器，不推荐加入
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Add Watch"),									EVENT_ID_ADDWATCH,	16*16+12},
	WISP_MENU_RES_SEPARATOR,
	{WSTR("Expansion All"),								EVENT_ID_EXPANSION,	16*16+9},
	{WSTR("Collapse  All"),								EVENT_ID_COLLAPSE,	16*16+10},
	WISP_MENU_RES_END
};

bool CSrcTXTFile::Open(PCSTR FileName,HANDLE*pHandleOpen,UINT Style)
{
	ULPOS nBegin,nEnd,nOffset;
	char*FileBuffer,*szLine;
	if(CImageFile::Open(FileName,pHandleOpen)==false)
		return false;
	FileBuffer=new char[m_FileSize+1];
	FileBuffer[m_FileSize]=0;
	ReadFile(0,FileBuffer,m_FileSize);
	nBegin=nOffset=0;
	m_TxtStyle=Style;
	while(nOffset<m_FileSize)
	{
		if(FileBuffer[nOffset]=='\r' || FileBuffer[nOffset]=='\n')
		{
			nEnd = nOffset;
			if(FileBuffer[nOffset]=='\r' && FileBuffer[nOffset+1]=='\n')
				nOffset=nEnd+2;
			else
				nOffset++;
			if(m_TxtStyle&TXTFILE_OPEN_CONTAIN_NEWLINE)
				nEnd=nOffset;
			szLine=new char[nEnd-nBegin+1];
			TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
			szLine[nEnd-nBegin]=0;
			m_StrList.Append(szLine);
			if(m_TxtStyle&TXTFILE_OPEN_CONTAIN_LINEOFFSET)
				m_LineOffsetLine.Append(nBegin);
			nBegin=nOffset;
		}
		else
		{
			nOffset++;
		}
	}
	if(nOffset!=nBegin)
	{
		nEnd = nOffset;
		szLine=new char[nEnd-nBegin+1];
		TStrNCpy(szLine,&FileBuffer[nBegin],nEnd-nBegin);
		szLine[nEnd-nBegin]=0;
		m_StrList.Append(szLine);
		if(m_TxtStyle&TXTFILE_OPEN_CONTAIN_LINEOFFSET)
			m_LineOffsetLine.Append(nBegin);
	}
	delete FileBuffer;
	return true;
}

WISP_MSG_MAP_BEGIN(CSourceCodeWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList)

WISP_MSG_EVENT_MAP_BEGIN(CSourceCodeWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_EXPANSION,OnEventExpansion)
	WISP_MSG_EVENT_MAP(EVENT_ID_COLLAPSE,OnEventCollapse)
	WISP_MSG_EVENT_MAP(EVENT_ID_ADDWATCH,OnEventAddWatch)
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_BP,OnEventToggleBreakPoint)
	WISP_MSG_EVENT_MAP(EVENT_ID_TOGGLE_BP_STATE,OnEventToggleBreakPointState)
	WISP_MSG_EVENT_MAP(EVENT_ID_BOOKMARK_TOGGLE,OnEventToggleBookMarks)
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTOLINE,OnEventGoToLine)
	WISP_MSG_EVENT_MAP(EVENT_ID_GOTO,OnEventGotoHere)
	WISP_MSG_EVENT_MAP(EVENT_ID_SET_EIP,OnEventSetEIP)	
WISP_MSG_EVENT_MAP_END

CSourceCodeWnd::CSourceCodeWnd()
{
	m_FileOpen=false;
	m_TxtFileLineNumber=0;
	m_CurrentFileID=-1;
	m_CommentState=false;
	m_CurModuleBase = 0;//最后一次从内存装入汇编时的基地址，如果相等，不用每次清除汇编行。
}

CSourceCodeWnd::~CSourceCodeWnd()
{
}

bool CSourceCodeWnd::OnCreate(IN WISP_MSG* pMsg)
{
	m_Style|=WISP_WLS_VERT_LINE;
	InsertColumn(WSTR("Mark"),40);
	InsertColumn(WSTR("Source Code"),512);
	m_ListBTIndex = 1;
	ShowColumnTitle(false);
	m_PopupMenu.CreatePopupMenu(SourceCodeWndMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_Color[COLOR_BK]=ColorOption.clrCVBK;
	m_Color[COLOR_ADDRESS ]=ColorOption.clrCVAddr;
	m_Color[COLOR_PREFIX  ]=ColorOption.clrCVPrefix;
	m_Color[COLOR_OPCODE  ]=ColorOption.clrCVOpCode;
	m_Color[COLOR_REGISTER]=ColorOption.clrCVReg;
	m_Color[COLOR_SEG_REG ]=ColorOption.clrCVSegReg;
	m_Color[COLOR_IMMED   ]=ColorOption.clrCVImmed;
	m_Color[COLOR_OPTR    ]=ColorOption.clrCVOptr;
	m_Color[COLOR_SYMBOL  ]=ColorOption.clrCVSymbol;
	m_Color[COLOR_COMMENT ]=ColorOption.clrCVComment;
	m_Color[COLOR_KEYWORD ]=ColorOption.clrCVKeyword;
	m_Color[COLOR_STR     ]=ColorOption.clrCVStr;
	m_Color[COLOR_BPX_STRIP]=ColorOption.clrCVBPXStrip;
	m_Color[COLOR_EIP_STRIP]=ColorOption.clrCVEIPStrip;
	m_Color[COLOR_BPXEIP_STRIP]=ColorOption.clrCVBPXEIPStrip;

	m_Color[CPLUSPLUS_KEYWORD]=ColorOption.clrSDKeyword;
	m_Color[CPLUSPLUS_IDENTIFIER]=ColorOption.clrSDId;
	m_Color[CPRE_KEYWORD]=ColorOption.clrSDPrekeyWord;
	m_Color[CPLUSPLUS_COMMENT_BLOCK]=ColorOption.clrSDCmtBlock;
	m_Color[CPLUSPLUS_COMMENT_LINE]=ColorOption.clrSDCmtLine;
	m_Color[CPLUSPLUS_STRING]=ColorOption.clrSDString;
	m_Color[CPLUSPLUS_NUMERICAL]=ColorOption.clrSDNum;
	m_Color[CPLUSPLUS_OPERATION]=ColorOption.clrSDOperation;
	m_Color[CPLUSPLUS_CLASS_NAME]=ColorOption.clrSDClassName;
	m_Color[CPLUSPLUS_STRUCT_NAME]=ColorOption.clrSDStructName;
	m_Color[CPLUSPLUS_UNION_NAME]=ColorOption.clrSDUnionName;
	m_Color[CPLUSPLUS_TYPEDEF_NAME]=ColorOption.clrSDTypedefName;
	m_Color[CPLUSPLUS_FUNCTION_NAME]=ColorOption.clrSDFunctionName;
	m_Color[CPLUSPLUS_UNKNOW]=ColorOption.clrSDUnknown;

	m_ClientDC.SetColorTable(m_Color);
	m_SelectBKColor = ColorOption.clrSDSelectedFrame;
	m_LostFocusSelBKColor = ColorOption.clrSDLostFocusSelFrame;
	SetBGColor(ColorOption.clrSDBK);
	SetDefaultTextColor(ColorOption.clrSDNum);

	m_StateDIBList=WispTKDIBList("\\SyserApp\\LineMark.bmp",16,16);
	m_StateDIBList->SetColorKey(0);
	return true;
}

bool CSourceCodeWnd::OnDestroy(IN WISP_MSG* pMsg)
{
	if(m_FileOpen)
		ClearChildItem();
	m_PopupMenu.Destroy();
	return true;
}

void CSourceCodeWnd::PopupMenu(IN WISP_MSG*pMsg)
{
	if(GetContextString()==false)
		m_PopupMenu.DisableItem(EVENT_ID_ADDWATCH);
	else 
		m_PopupMenu.EnableItem(EVENT_ID_ADDWATCH);
	m_PopupMenu.Popup();	
}

void CSourceCodeWnd::ItemRClickNotify(HANDLE hItem,int Col)
{
	switch(Col)
	{
	case 0:
		OnEventToggleBookMarks(NULL);
		break;
	}
}

void CSourceCodeWnd::ItemClickNotify(HANDLE hItem,int Col)
{
	switch(Col)
	{
	case 0:
		OnEventToggleBreakPoint(NULL);
		break;
	}
}

bool CSourceCodeWnd::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	WCHAR szBuffer[512];
	if(IsColorString(String))
	{
		TStrCpyLimit(szBuffer,GetColorString(String),512);
		GetItemEditString()=szBuffer;
	}
	return true;
}

bool CSourceCodeWnd::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	return false;
}

bool CSourceCodeWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	UINT Mark;
	WISP_RECT rc;
	CWispList::OnUpdateClient(pMsg);
	rc.x=0;
	if(m_ColumnList.Count())
		rc.x+=m_ColumnList.Begin()->Width-20;
	rc.cx=16,rc.cy=16;
	rc.y=m_TitleHeight;
	CItemList::IT ItemIter = m_CurItemIter;
	if(ItemIter!=m_RootItem.ChildItemList.End())
	{
		for(int iLine=0; iLine<m_nLinePerPage;iLine++)
		{
			Mark = (UINT)GetItemData(&(*ItemIter),0);
			if(Mark&CV_MARK_BOOK_MARK)
				m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(1));
			if(Mark&CV_MARK_EIP)
				m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(0));
			if(Mark&CV_MARK_BPX)
				m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(2));
			else if(Mark&CV_MARK_DISABLED_BPX)
				m_ClientDC.DrawDIB(&rc,m_StateDIBList->GetDIB(3));
			rc.y+=m_ButtonSize.cy;
			if(GetNextLineItem(ItemIter)==false)
				break;
		}
	}
	return false;
}

bool CSourceCodeWnd::OnEventCollapse(IN WISP_MSG* pMsg)
{
	HANDLE hItem,hSubItem,hFirstItem,hParentItem,hRootItem;
	hItem = GetItem(0);
	hRootItem=GetParentItem(hItem);
	hFirstItem=GetScrStartItem();
	hParentItem = GetParentItem(hFirstItem);
	if(hRootItem != hParentItem)
		EnableVisible(hParentItem,0);
#if 1
	while(hItem)
	{
		hSubItem = GetItem(0,hItem);
		if(hSubItem)
			UnexpandItem(hItem);
		hItem=GetNextItem(hItem);
	}
#endif
	Update();
	return true;
}

bool CSourceCodeWnd::OnEventExpansion(IN WISP_MSG* pMsg)
{
	HANDLE hItem,hSubItem;
	hItem = GetItem(0);
	while(hItem)
	{
		hSubItem = GetItem(0,hItem);
		if(hSubItem)
			ExpandItem(hItem);
		hItem=GetNextItem(hItem);
	}
	Update();
	return true;
}

bool CSourceCodeWnd::OnEventAddWatch(IN WISP_MSG* pMsg)
{
	SOURCE_WATCH_WND.AddWatchByName(m_ContextString);
	return true;
}

bool CSourceCodeWnd::GetContextString()
{
	char NameBuffer[512];
	WISP_CHAR szTip[512];
	HANDLE hItem;
	WISP_RECT CellRect;
	WISP_PCSTR pStr;
	bool bRet=true,bPreId=false;
	int RetValue,LineLen,Col=1,PreState,CurrentIndex,BeginIdOffset=0,FirstIdPos,x,offset;
	CStrA OutBuffer;
	WISP_COLOR_CHAR*pCStr;
	char* IdString;
	char Buf[512];
	CItemList::IT ListIT;
	int NameBufferLen=sizeof(NameBuffer);
	PSDUDTDATAITEM pDataItem;
	DWORD ThisOffset=0,CurrentLineNum;

	m_ContextString.Empty();
	m_FullContextString.Empty();
	bool bIsFunc=false;

	PointToItem(m_RightButtonPoint,ListIT);
	hItem = &*ListIT;
	if(hItem==NULL)
		return true;
	GetItemCellRect(hItem,Col,&CellRect);
	if(m_RightButtonPoint.x < CellRect.x || m_RightButtonPoint.x > CellRect.x + CellRect.cx)
		return false;
	TStrCpy(szTip,"");
	CurrentLineNum = (DWORD)GetItemData(hItem,1);
	
	x = m_RightButtonPoint.x-CellRect.x - m_TextMargin;
	pStr=GetItemText(hItem,Col);
	offset = m_ClientDC.PixelOffToTextOff(pStr,x);
	if(offset==-1)
		return false;
	pCStr = (WISP_COLOR_CHAR*)GetColorString(pStr);
	TStrCpy(Buf,pCStr);
	
	myinputptr=Buf;
	LineLen=TStrLen(Buf);
	myinputlim=myinputptr+LineLen;
	CurrentIndex=0;
	RetValue=0;
	yyrestart(0);
	PreState=0;
	FirstIdPos = 0;
	while(RetValue=yylex())
	{
		switch(RetValue)
		{
		case LEX_DOT:
			PreState=RetValue;
			break;
		case LEX_ARROW:
			PreState=RetValue;
			break;
		case LEX_IDENTIFIER:
			if(FirstIdPos==0)
			{
				FirstIdPos=CurrentIndex;
			}
			bPreId=true;
			PreState=RetValue;
			break;
		default:
			bPreId=false;
			FirstIdPos=0;
			PreState=RetValue;
		}
		if(offset>=CurrentIndex&&offset<CurrentIndex+yyleng)
		{
			if(PreState!=LEX_IDENTIFIER)
			{
				bRet=false;
				goto quit_001;
			}
			
			if(FirstIdPos!=CurrentIndex)
			{
				IdString=&Buf[FirstIdPos];
				Buf[CurrentIndex+yyleng]=0;
				pDataItem = m_pSDSModule->GetDataSymbolByString(IdString,m_CurrentFileID,CurrentLineNum,&bIsFunc,&ThisOffset);
				if(pDataItem==NULL)
					return false;
				m_FullContextString=IdString;
				OutBuffer.Empty();
				if(!bIsFunc)
				{
					OutBuffer = m_pSDSModule->GetSDSymbolName(pDataItem->TypeId,NameBuffer,&NameBufferLen);
					OutBuffer+=" ";
					if(pDataItem->TypeIdParentUDT)
					{
						PSDTYPE_INFILE pType = m_pSDSModule->GetTypeSymbol(pDataItem->TypeIdParentUDT);
						if(pType)
						{
							if(pType->Type==SD_STRUCT||pType->Type==SD_CLASS||pType->Type==SD_UNION)
							{
								OutBuffer+= m_pSDSModule->GetSDSymbolName(pDataItem->TypeIdParentUDT,NameBuffer,&NameBufferLen);
								OutBuffer+="::";
							}
						}
					}
					OutBuffer+=pDataItem->uName.Name;
				}
				else
				{
					bRet=false;
					goto quit_001;
				}
				TStrCpy(szTip,(char*)OutBuffer);
				bRet=true;
				goto quit_001;
			}
			PSDTYPE_INFILE pType;
			pType=m_pSDSModule->GetSymbolByName(yytext);
			if(pType==NULL)
			{
				if(GetVariable(yytext,hItem,OutBuffer)==true)
				{
					TStrCpy(szTip,(char*)OutBuffer);
					bRet=true;
				}else
					bRet=false;
			}
			goto quit_001;
		}
		CurrentIndex+=yyleng;
	}
	return false;
quit_001:	
	if(bRet)
		m_ContextString=yytext;
	return bRet;
}

bool CSourceCodeWnd::OnEventGoToLine(IN WISP_MSG* pMsg)
{
	int nLine;
	HANDLE hItem;
	CWispString szLine;
	WCHAR szStatic[64];
	TSPrintf(szStatic,WSTR("Line number (1 - %d):  "),m_TxtFileLineNumber-1);
	hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		szLine=WSTR("1");
	else
		szLine.Format(WSTR("%d"),(int)GetItemData(hItem,1));
	if(GetInputText(szLine,szStatic))
	{
		if(USDecStrToNum((PCWSTR)szLine,&nLine) && nLine>=1)
		{
			hItem = GetItem(nLine-1);
			if(hItem)
			{
				EnableVisible(hItem);
				SelectItem(hItem);
				Focus();
			}
		}
	}
	return true;
}

ULPOS CSourceCodeWnd::GetItemAddress(HANDLE hItem)
{
	ULPOS Address;
	Address = (ULPOS)GetItemData(hItem,1);
	if(GetItemLevel(hItem)==0)
	{	//选择的行是在源代码上，Address为行号
		LINENUMBERMAP::IT FindIT=m_LineMap.Find(Address);
		if(FindIT==m_LineMap.End())
		{
			PSDLINE pLine = m_pSDSModule->GetContiguityLineBySourceFileID(m_CurrentFileID,Address);
			if(pLine)
				Address=pLine->Rva;
			else
				Address=0;
		}
		else
			Address = (*FindIT).pLine->Rva;
	}
	return	Address;	
}

bool CSourceCodeWnd::OnKeyEvent(IN WISP_MSG* pMsg)
{
	int Pos;
	if(pMsg->KeyEvent.bKeyDown)
	{
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_VK_RBUTTON:
			m_RightButtonPoint = pMsg->MsgMouseWndPT;
			m_RightButtonPoint = pMsg->MsgMouseCltPT;
			PointToItem(pMsg->MsgMouseCltPT,&Pos);
			if(Pos>LI_POS_CELL_AREA_START && Pos<LI_POS_CELL_AREA_END)
				PopupMenu(pMsg);//不在第一列弹菜单
			break;
		case WISP_VK_F7:
			OnEventGotoHere(NULL);
			break;

		case WISP_VK_F9:
			OnEventToggleBreakPoint(NULL);
			break;
		}
	}
	return true;
}

void CSourceCodeWnd::SyntaxColor(char* SourceCodeLine,WISP_COLOR_CHAR *szColorBuffer)
{
	int RetValue;
	PSDTYPE_INFILE pType;
	PSDFUNCTIONITEM pFunc;
	int Count=0;
	myinputptr=SourceCodeLine;
	myinputlim=myinputptr+TStrLen(SourceCodeLine);
	ColorStrCpy(szColorBuffer,"",CPLUSPLUS_UNKNOW,0);
	if(m_CommentState==false)
		yyrestart(0);
	while(RetValue=yylex())
	{
		(*(int*)&Count)++;
		switch(RetValue)
		{
		case LEX_COMMENT_LINE:
			ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_COMMENT_LINE,0);
			break;
		case LEX_COMMENT_BLOCK_BEGIN:
			ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_COMMENT_BLOCK,0);
			m_CommentState=true;
			//Count=0;
			break;
		case LEX_COMMENT_BLOCK_END:
			ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_COMMENT_BLOCK,0);
			m_CommentState=false;
			break;
		case LEX_IDENTIFIER:
			{
				pType = m_pSDSModule->GetSymbolByName(yytext);
				if(pType)
				{
					switch(pType->Type)
					{
					case SD_CLASS:
						ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_CLASS_NAME,0);
						break;
					case SD_STRUCT:
						ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_STRUCT_NAME,0);
						break;
					case SD_UNION:
						ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_UNION_NAME,0);
						break;
					case SD_TYPEDEF:
						ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_TYPEDEF_NAME,0);
						break;
					default:
						ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_IDENTIFIER,0);
						break;
					}
				}
				else
				{
					pFunc = m_pSDSModule->GetFunctionSymbolByName(yytext);
					if(pFunc)
						ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_FUNCTION_NAME,0);	
					else
						ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_IDENTIFIER,0);
				}
			}
			break;
		case LEX_ELLIPSIS:
		case LEX_STRINGliteral:
			ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_STRING,0);
			break;
		case LEX_INTEGERconstant:
		case LEX_OCTALconstant:
		case LEX_HEXconstant:
		case LEX_FLOATINGconstant:
		case LEX_CHARACTERconstant:
			ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_NUMERICAL,0);
			break;
		
		default:
			if(RetValue>=LEX___ABSTRACT && RetValue<=LEX_WHILE)
				ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_KEYWORD,0);
			else if(RetValue>=LEX_PRE_DEFINE && RetValue<=LEX_PRE_GRAMA)
				ColorStrCat(szColorBuffer,yytext,CPRE_KEYWORD,0);
			else if(RetValue>=LEX_LP && RetValue<=LEX_ELLIPSIS)
				ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_OPERATION,0);
			else
				ColorStrCat(szColorBuffer,yytext,CPLUSPLUS_UNKNOW,0);
			
		}
	}
	if(m_CommentState)
	{
		if(Count==0)
		{
			ColorStrCpy(szColorBuffer,SourceCodeLine,CPLUSPLUS_COMMENT_BLOCK,0);
		}
	}
}

void CSourceCodeWnd::LoadSourceFile(char* Buffer,DWORD size,PSDSOURCEFILEID pSDSourceFileId)
{
	HANDLE hItem;
	ULPOS ModuleBase,Address,TmpRva;
	ULSIZE ModuleSize,Count;
	BYTE CodeBuffer[50];
	char szBuffer[256],*Name;
	WISP_COLOR_CHAR szColorBuffer[256];
	WCHAR LineNumberStr[20],*wNameBuf;
	int i,NameLen,CurrentLineLen,InstrLength;
	PSDLINE pLine;
	LINENUMBERMAP::IT FindIT;
	int CurLen=1000;
	m_pCodeDoc=&gpSyser->m_SyserUI.m_CodeDoc;
	if(m_FileOpen)
		return;
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule==NULL && gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
		pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule)
	{
		ModuleBase = pDbgModule->m_ModuleBase;
		ModuleSize = pDbgModule->m_ModuleSize;
	}
	else
	{
		ModuleBase = 0;
		ModuleSize = 0;
	}
	m_CurrentFileID=pSDSourceFileId->FileID;
	m_FileOpen=true;
	m_TxtFile.Create((ULSIZE)size,(BYTE*)Buffer,false);
	m_TxtFile.Open(NULL,NULL,TXTFILE_OPEN_CONTAIN_NEWLINE|TXTFILE_OPEN_CONTAIN_LINEOFFSET);
	m_TxtFileLineNumber = m_TxtFile.m_StrList.Count();
	TTXTStrList::IT BeginIT,EndIT;
	BeginIT=m_TxtFile.m_StrList.Begin();
	EndIT=m_TxtFile.m_StrList.End();
	wNameBuf=new WCHAR[CurLen];
	Count = m_pSDSModule->GetLineBySourceFileID(m_CurrentFileID,&m_LineMap);
	for(i=1;BeginIT!=EndIT;BeginIT++,i++)
	{
		Name = *BeginIT;
		SyntaxColor(Name,szColorBuffer);
		NameLen=TStrLen(Name)+1;
		if(NameLen>CurLen)
		{
			delete []wNameBuf;
			CurLen = NameLen;
			wNameBuf=new WCHAR[CurLen];
		}
		NameLen = AnsiToUnicode(Name,wNameBuf,NameLen);
		for(int p=0;p<NameLen;p++)
		{
			szColorBuffer[p] = (szColorBuffer[p]&0xffff0000)|wNameBuf[p];
			if(wNameBuf[p]==0)
				szColorBuffer[p]=0;
		}
		uNumToStr(i,LineNumberStr,10);
		hItem = InsertItem(LineNumberStr);
		SetItemData(hItem,0,CV_MARK_NULL);
		SetItemColorText(hItem,1,szColorBuffer);
		SetItemData(hItem,1,i);
		if(ModuleBase==0)
			continue;
		FindIT = m_LineMap.Find(i);
		if(FindIT==m_LineMap.End())
			continue;				
		pLine = (*FindIT).pLine;
		if(pLine->Statement)
		{
			CurrentLineLen = pLine->Len;
			Address = pLine->Rva+ModuleBase;
			TmpRva = pLine->Rva;
			while(CurrentLineLen>0)
			{
				TSPrintf(szBuffer,"%08x      ",Address);
				InstrLength = m_pCodeDoc->InstrLen(Address);
				if(InstrLength==0)
					InstrLength=1;
				m_pCodeDoc->ReadImage(Address,CodeBuffer,InstrLength);
				ColorStrCpy(szColorBuffer,szBuffer,COLOR_ADDRESS,COLOR_BK);
				ColorDasm(ModuleBase,Address,MAX_INSTR_LEN,&szColorBuffer[14]);
				HANDLE hSubItem = InsertItem(WSTR(""),hItem);
				SetItemData(hSubItem,0,CV_MARK_NULL);
				SetItemColorText(hSubItem,1,szColorBuffer);
				SetItemData(hSubItem,1,TmpRva);
				CurrentLineLen-=InstrLength;
				Address+=InstrLength;
				TmpRva+=InstrLength;
			}
		}
	}
	if(ModuleBase)
		m_CurModuleBase = ModuleBase;
	m_TxtFile.Close();
	delete []wNameBuf;
}

int CSourceCodeWnd::GetSourceFileID()const
{
	return m_CurrentFileID;
}

CSDSModule*CSourceCodeWnd::GetSourceFileSymAnalyzer()const
{
	return m_pSDSModule;
}

WISP_COLOR_CHAR* CSourceCodeWnd::ColorDasm(DWORD ModuleBase,DWORD EIP,DWORD MaxSize,WISP_COLOR_CHAR*pColorString,DWORD nCodeAlgn)
{
	DWORD	Len;
	BYTE	Buffer[64];
	WCHAR	szBuffer[64];
	INSTRUCTION_INFORMATION DasmInstr;
	DasmInstr.CodeBuff = Buffer;
	DasmInstr.eip = EIP;
	DasmInstr.pasm = NULL;
	if(EIP<m_CurrentFunction.m_BeginAddress || EIP>=m_CurrentFunction.m_EndAddress)
	{
		PSDFUNCTIONITEM pFuncItem = m_pSDSModule->GetFunctionFromRav(EIP-ModuleBase);
		m_CurrentFunction.Init(m_pSDSModule,pFuncItem);
	}
	Len=m_pCodeDoc->Dasm(&DasmInstr,NULL,MaxSize);
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
	return pColorString;
}

WISP_COLOR_CHAR*CSourceCodeWnd::InstrToCS(INSTRUCTION_INFORMATION*pDasmInstr,WISP_COLOR_CHAR*pColorString)
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
	return OptItemToCS(pDasmInstr->op,3,pColorString,pDasmInstr,NULL);
}


WISP_COLOR_CHAR*CSourceCodeWnd::OptItemToCS(OPERAND_ITEM*OpArray,int nOp,WISP_COLOR_CHAR*pColorString,INSTRUCTION_INFORMATION*pDasmInstr,DIS_CPU*pCurrent_CPU)
{
	DIS_ADDRESS*pAddr;
	OPERAND_ITEM*pOp;
	WCHAR szBuffer[32];
	bool bHasSymbols;
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
			//if(pDasmInstr->xxxxptr!=-1)
			{
				//pColorString+=ColorStrCpy(pColorString,",",COLOR_OPTR,0);
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
			if(pAddr->displacement || (pAddr->base==-1 && pAddr->index==-1))
			{//画displacement
				bHasSymbols=false;
				if(pAddr->index!=-1 || pAddr->base!=-1)
				{
					pColorString+=ColorStrCpy(pColorString,"+",COLOR_OPTR,0);
				}
				if(pAddr->index==-1&&pAddr->address_size==1&&pAddr->base==5)
				{
					char* TempSymbol;
					TempSymbol = m_CurrentFunction.FindNameByRegisterOffset((DWORD)pAddr->displacement,pAddr->base,NULL);
					if(TempSymbol)
					{
						bHasSymbols=true;
						pColorString+=ColorStrCpy(pColorString,TempSymbol,COLOR_SYMBOL,0);
					}
				}
				if(bHasSymbols==false)
				{
					TSPrintf(szBuffer,CInstrSym::m_SizePtr[pAddr->displacement_size],pAddr->displacement);
					pColorString+=ColorStrCpy(pColorString,szBuffer,COLOR_IMMED,0);
				}
			}
			pColorString+=ColorStrCpy(pColorString,"]",COLOR_OPTR,0);
		}
		else
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
	return pColorString;
}

void CSourceCodeWnd::LoadModuleImage()
{
	ULPOS ModuleBase;
	BYTE CodeBuffer[MAX_INSTR_LEN];
	char szBuffer[256];
	WISP_COLOR_CHAR szColorBuffer[256];
	DWORD i = 1;
	SDLINELIST LineList;
	int CurrentLineLen,InstrLength;
	ULPOS TmpRva,Address;
	SDLINELIST::IT LineBeginIT;
	PSDLINE pLine;
	if(m_FileOpen==false||m_pSDSModule==NULL)
		return;
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule==NULL && gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
		pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	ModuleBase=pDbgModule?pDbgModule->m_ModuleBase:0;
	HANDLE hItem,hSubItem;
	LINENUMBERMAP::IT FindIT;
	hItem = GetFirstItem();
	while(hItem)
	{
		hSubItem = GetFirstItem(hItem);
		if(hSubItem)
		{
			if(ModuleBase && m_CurModuleBase == ModuleBase)
				break;
			ClearChildItem(hItem);
		}
		if(ModuleBase)
		{
			FindIT = m_LineMap.Find(i);
			if(FindIT!=m_LineMap.End())
			{
				pLine = FindIT->pLine;
				CurrentLineLen = pLine->Len;
				Address = pLine->Rva+ModuleBase;
				TmpRva=pLine->Rva;
				while(CurrentLineLen>0)
				{
					TSPrintf(szBuffer,"%08x      ",Address);
					InstrLength = m_pCodeDoc->InstrLen(Address);
					if(InstrLength==0)
						InstrLength=1;
					m_pCodeDoc->ReadImage(Address,CodeBuffer,InstrLength);
					ColorStrCpy(szColorBuffer,szBuffer,COLOR_ADDRESS,COLOR_BK);
					ColorDasm(ModuleBase,Address,MAX_INSTR_LEN,&szColorBuffer[14]);
					HANDLE hSubItem = InsertItem(WSTR(""),hItem);
					SetItemColorText(hSubItem,1,szColorBuffer);
					SetItemData(hSubItem,1,TmpRva);
					SetItemData(hSubItem,0,CV_MARK_NULL);
					CurrentLineLen-=InstrLength;
					Address+=InstrLength;
					TmpRva+=InstrLength;
				}
			}
		}
		SetItemData(hItem,0,CV_MARK_NULL);
		hItem = GetNextItem(hItem);
		i++;
	}
	if(ModuleBase && m_CurModuleBase!=ModuleBase)
		m_CurModuleBase = ModuleBase;
}

bool CSourceCodeWnd::UpdateView()
{//如果包含EIP返回true
	if(m_FileOpen==false||m_pSDSModule==NULL)
		return false;
	bool bContainEIP,bViewContainEIP;
	UINT Mark;
	DWORD LineNumber,LineCount=0;
	ULPOS Rva,ModuleBase;
	PSDLINE pLine;
	LINENUMBERMAP::IT FindIT;
	HANDLE hSubItem,hItem;
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule==NULL && gpSyser->m_pDebugger!=gpSyser->m_pSysDebugger)
		pDbgModule=gpSyser->m_pSysDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());

	ModuleBase = pDbgModule ? pDbgModule->m_ModuleBase : 0;
	bViewContainEIP = false;
	LineNumber = 1;
	hItem = GetFirstItem();
	while(hItem)
	{
		FindIT = m_LineMap.Find(LineNumber);
		if(!FindIT.IsExist())
		{//没有对应代码的行
			Mark = CV_MARK_NULL;
			if(IsBookMark(LineNumber))
				Mark|=CV_MARK_BOOK_MARK;
			SetItemData(hItem,0,Mark);
			hItem=GetNextItem(hItem);
			LineNumber++;
			continue;
		}
		//有对应代码的行
		pLine = (*FindIT).pLine;
		if(ModuleBase)
		{//模块可用
			bContainEIP=false;
			hSubItem = GetItem(0,hItem);
			while(hSubItem)
			{
				Rva=(DWORD)GetItemData(hSubItem,1);
				Mark = m_pCodeDoc->GetLineMark(Rva+ModuleBase);
				if(Mark&CV_MARK_EIP)
					bContainEIP = true;
				SetItemData(hSubItem,0,Mark);
				hSubItem=GetNextItem(hSubItem);
			}
			Mark = m_pCodeDoc->GetLineMark(pLine->Rva+ModuleBase);
			if(bContainEIP)
				bViewContainEIP=true;
			if(bContainEIP)
				Mark|=CV_MARK_EIP;
			if(IsBookMark(LineNumber))
				Mark|=CV_MARK_BOOK_MARK;
		}
		else
		{//模块不可用
			Mark = CV_MARK_NULL;
			if(m_pSDSModule->m_BreakPointList.Count())
			{
				TList<ULPOS>::IT Iter = m_pSDSModule->m_BreakPointList.Find(pLine->Rva);
				if(Iter != m_pSDSModule->m_BreakPointList.End())
					Mark|=CV_MARK_BPX;
			}
			if(IsBookMark(LineNumber))
				Mark|=CV_MARK_BOOK_MARK;
		}
		SetItemData(hItem,0,Mark);
		hItem=GetNextItem(hItem);
		LineNumber++;
	}
	Update();
	return bViewContainEIP;
}

bool CSourceCodeWnd::GetStringValue(IN char* pString,IN int nLen,IN CStrA& OutBuffer)
{
	return true;
}
bool CSourceCodeWnd::ItemShowTipNotify(HANDLE hItem,int Col,int*pX,int*pY,WISP_PSTR szTip)
{
	DWORD CurrentLineNum;
	WISP_RECT CellRect;
	WISP_PCSTR pStr;
	bool bRet=true;
	bool bPreId=false;
	int CurrentIndex;
	int BeginIdOffset=0;
	int RetValue;
	int LineLen;
	int PreState=0;
	CStrA OutBuffer;
	WISP_COLOR_CHAR*pCStr;
	int FirstIdPos;
	char* IdString;
	char Buf[512];
	int x,offset;
	if(Col!=1)
		return false;
	TStrCpy(szTip,"");
	CurrentLineNum = (DWORD)GetItemData(hItem,1);
	GetItemCellRect(hItem,Col,&CellRect);
	x = m_pWispBase->m_MousePT.x - m_ScrClientRect.x-CellRect.x - m_TextMargin;
	pStr=GetItemText(hItem,Col);
	offset = m_ClientDC.PixelOffToTextOff(pStr,x);
	if(offset==-1)
		return false;
	pCStr = (WISP_COLOR_CHAR*)GetColorString(pStr);
	TStrCpy(Buf,pCStr);
	*pX+=(x+10);
	*pY+=16;
	myinputptr=Buf;
	LineLen=TStrLen(Buf);
	myinputlim=myinputptr+LineLen;
	CurrentIndex=0;
	RetValue=0;
	yyrestart(0);
	PreState=0;
	FirstIdPos = 0;
	while(RetValue=yylex())
	{
		switch(RetValue) {
		case LEX_DOT:
			PreState=RetValue;
			break;
		case LEX_ARROW:
			PreState=RetValue;
			break;
		case LEX_IDENTIFIER:
			if(FirstIdPos==0)
			{
				FirstIdPos=CurrentIndex;
			}
			bPreId=true;
			PreState=RetValue;
			break;
		default:
			bPreId=false;
			FirstIdPos=0;
			PreState=RetValue;
		}
		if(offset>=CurrentIndex&&offset<CurrentIndex+yyleng)
		{
			if(PreState!=LEX_IDENTIFIER)
			{
				bRet=false;
				goto quit_001;
			}
			if(FirstIdPos!=CurrentIndex)
			{
				char NameBuffer[512];
				int NameBufferLen=sizeof(NameBuffer);
				PSDUDTDATAITEM pDataItem;
				DWORD ThisOffset=0;
				PSDFUNCTIONITEM pFuncItem;
				bool bIsFunc=false;
				IdString=&Buf[FirstIdPos];
				Buf[CurrentIndex+yyleng]=0;
				pDataItem = m_pSDSModule->GetDataSymbolByString(IdString,m_CurrentFileID,CurrentLineNum,&bIsFunc,&ThisOffset);
				if(pDataItem==NULL)
					return false;
				OutBuffer.Empty();
				if(bIsFunc)
				{
					pFuncItem=(PSDFUNCTIONITEM)pDataItem;
					char FuncName[512]={0};
					int FuncNameLen=sizeof(FuncName);
					m_pSDSModule->GetFunctionName(pFuncItem,FuncName,&FuncNameLen);
					OutBuffer=FuncName;
				}
				else
				{
					OutBuffer = m_pSDSModule->GetSDSymbolName(pDataItem->TypeId,NameBuffer,&NameBufferLen);
					OutBuffer+=" ";
					if(pDataItem->TypeIdParentUDT)
					{
						PSDTYPE_INFILE pType = m_pSDSModule->GetTypeSymbol(pDataItem->TypeIdParentUDT);
						if(pType)
						{

							if(pType->Type==SD_STRUCT||pType->Type==SD_CLASS||pType->Type==SD_UNION)
							{
								OutBuffer+= m_pSDSModule->GetSDSymbolName(pDataItem->TypeIdParentUDT,NameBuffer,&NameBufferLen);
								OutBuffer+="::";
							}
						}
					}
					OutBuffer+=pDataItem->uName.Name;
				}
				TStrCpy(szTip,(char*)OutBuffer);
				bRet=true;
				goto quit_001;
			}
			PSDTYPE_INFILE pType;
			pType=m_pSDSModule->GetSymbolByName(yytext);
			if(pType!=NULL)
			{
				switch(pType->Type) {
				case SD_TYPEDEF:
					OutBuffer.Empty();
					m_pSDSModule->DumpSDTypedefTypeToHeaderFile(pType,OutBuffer);
					TStrCpy(szTip,(char*)OutBuffer);
					break;
				case SD_STRUCT:
					TStrCpy(szTip,"struct ");
					TStrCat(szTip,yytext);
					break;
				case SD_CLASS:
					TStrCpy(szTip,"class ");
					TStrCat(szTip,yytext);
					break;
				case SD_UNION:
					TStrCpy(szTip,"union ");
					TStrCat(szTip,yytext);
					break;
				case SD_ENUMERATION:
					OutBuffer.Empty();
					m_pSDSModule->DumpSDEnumTypeToHeaderFile(pType,OutBuffer);
					TStrCpy(szTip,(char*)OutBuffer);
					break;
				default:
					{
						if(GetVariable(yytext,hItem,OutBuffer)==true)
						{
							TStrCpy(szTip,(char*)OutBuffer);
							bRet=true;
							goto quit_001;
						}
						bRet=false;
						goto quit_001;
					}
				}
			}
			else
			{
				if(GetVariable(yytext,hItem,OutBuffer)==true)
				{
					TStrCpy(szTip,(char*)OutBuffer);
					bRet=true;
					goto quit_001;
				}else
					bRet=false;
			}
			goto quit_001;
		}
		CurrentIndex+=yyleng;
	}
	return true;
quit_001:
	return bRet;
}
bool CSourceCodeWnd::GetVariable(const char* Name,HANDLE hItem,CStrA& OutBuffer)
{
	PSDTYPE_INFILE pType;
	bool bRet=false;
	char NameBuffer[512];
	int NameBufferLen=sizeof(NameBuffer);
	SDLINELIST LineList;
	PSDFUNCTIONITEM pFuncItem;
	NUM_PTR LineNum = GetItemData(hItem,1);
	PSDLINE pLine=NULL;
	PSDUDTDATAITEM pDataItem;
	LINENUMBERMAP::IT FindIT;
	FindIT = m_LineMap.Find(*(DWORD*)&LineNum);
	if(FindIT==m_LineMap.End())
	{
		pLine = m_pSDSModule->GetContiguityLineBySourceFileID(m_CurrentFileID,*(DWORD*)&LineNum);
	}
	else
		pLine=(*FindIT).pLine;	
	if(pLine)
	{
		pFuncItem = m_pSDSModule->GetFunctionFromRav(pLine->Rva);
		if(pFuncItem==NULL)
			return bRet;
		if(pFuncItem!=m_CurrentFunction.m_pFunction)
			m_CurrentFunction.Init(m_pSDSModule,pFuncItem);
		pDataItem =m_CurrentFunction.GetDataSymbolByName((char*)Name);
		if(pDataItem)
		{
			OutBuffer = m_pSDSModule->GetSDSymbolName(pDataItem->TypeId,NameBuffer,&NameBufferLen);
			OutBuffer+=" ";
			if(pDataItem->TypeIdParentUDT)
			{
				pType = m_pSDSModule->GetTypeSymbol(pDataItem->TypeIdParentUDT);
				if(pType)
				{
					
					if(pType->Type==SD_STRUCT||pType->Type==SD_CLASS||pType->Type==SD_UNION)
					{
						OutBuffer+= m_pSDSModule->GetSDSymbolName(pDataItem->TypeIdParentUDT,NameBuffer,&NameBufferLen);
						OutBuffer+="::";
					}
				}
			}
			OutBuffer+=pDataItem->uName.Name;
			bRet=true;
		}
		else
		{
			pFuncItem = m_CurrentFunction.GetFunctionSymbolByName((char*)Name);
			if(pFuncItem)
			{
				char FuncName[512]={0};
				int FuncNameLen=sizeof(FuncName);
				m_pSDSModule->GetFunctionName(pFuncItem,FuncName,&FuncNameLen);
				OutBuffer=FuncName;
				bRet=true;
			}
		}
	}
	return bRet;
}

void CSourceCodeWnd::SetBeginLine(DWORD Rva)
{
	DWORD LineRva;
	HANDLE hItem;
	hItem = GetItem(NULL);
	while(hItem)
	{
		LineRva = (DWORD)GetItemData(hItem,1);
		if(LineRva==Rva)
			break;
		hItem = GetNextItem(hItem);
	}
	if(hItem)
	{
		if(IsItemVisible(hItem))
			return;
		EnableVisible(hItem);
		SelectItem(hItem);
	}
}

bool CSourceCodeWnd::OnEventToggleBreakPoint(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	DWORD Address;
	hItem =GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = GetItemAddress(hItem);
	if(Address == 0)
		return true;
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule==NULL)
	{
		TList<ULPOS>::IT BPIter = m_pSDSModule->m_BreakPointList.Find(Address);
		if(BPIter==m_pSDSModule->m_BreakPointList.End())
			m_pSDSModule->m_BreakPointList.Append(Address);
		else
			m_pSDSModule->m_BreakPointList.Remove(BPIter);
		UpdateView();
		return true;
	}
	Address+=pDbgModule->m_ModuleBase;
	gpSyser->m_SyserUI.ToggleCodeBP(Address);
	return true;
}

bool CSourceCodeWnd::OnEventToggleBreakPointState(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = GetItemAddress(hItem);
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule==NULL)
		return true;
	Address+=pDbgModule->m_ModuleBase;
	gpSyser->m_SyserUI.ToggleCodeBPState(Address);
	return true;
}

bool CSourceCodeWnd::OnEventToggleBookMarks(IN WISP_MSG*pMsg)
{
	ToggleBookMark();
	return true;
}


bool CSourceCodeWnd::OnEventSetEIP(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = GetItemAddress(hItem);
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule==NULL)
		return true;
	Address+=pDbgModule->m_ModuleBase;
	*X86_REG_PTR.pEIP=Address;
	gpSyser->m_pDebugger->SaveRegister();
	UPDATE_CONTEXT();
	UPDATE_SOURCE_CODE_VIEW();
	return true;
}

bool CSourceCodeWnd::OnEventGotoHere(IN WISP_MSG* pMsg)
{
	HANDLE hItem;
	ULPOS Address;
	hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return true;
	Address = GetItemAddress(hItem);
	CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModuleByID(m_pSDSModule->GetModuleID());
	if(pDbgModule==NULL)
		return true;
	Address+=pDbgModule->m_ModuleBase;
	gpSyser->m_pDebugger->InsertCodeBP(Address,BP_TYPE_DEBUG,BP_STATE_ENABLE);
	RUNCMD(WSTR("x"));
	return true;
}

void CSourceCodeWnd::ToggleBookMark()
{
	HANDLE hItem;
	ULONG iLine;
	hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		return;
	if(GetItemLevel(hItem)==0)
	{
		iLine =(ULONG) GetItemData(hItem,1);
	}
	else
	{		
		hItem = GetParentItem(hItem);
		iLine= (ULONG) GetItemData(hItem,1);
	}
	TMap<ULONG,HANDLE>::IT Iter = m_BookMark.Find(iLine);
	if(Iter.IsExist())
	{
		m_BookMark.Remove(Iter);
	}
	else
	{
		m_BookMark.InsertUnique(iLine,hItem);
	}
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
	UpdateView();
}

bool CSourceCodeWnd::IsBookMark(ULONG iLine)
{
	return m_BookMark.Find(iLine)!=m_BookMark.End();
}

void CSourceCodeWnd::GotoNextBookMark()
{
	ULONG iLine;
	HANDLE hItem=GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		hItem = GetScrStartItem();
	if(hItem==NULL)
		return;
	if(GetItemLevel(hItem)!=0)
		hItem=GetParentItem(hItem);
	iLine = (ULONG)GetItemData(hItem,1);
	TMap<ULONG,HANDLE>::IT Iter=m_BookMark.FindAlmost(iLine);
	if(Iter.IsExist())
		Iter++;
	if(Iter.IsExist()==false)
		Iter = m_BookMark.Begin();
	if(Iter.IsExist())
	{
		EnableVisible(*Iter);
		SelectItem(*Iter);
	}
}

void CSourceCodeWnd::GotoPrevBookMark()
{
	ULONG iLine;
	HANDLE hItem=GetFirstItem(NULL,WISP_WLIS_SELECTED);
	if(hItem==NULL)
		hItem = GetScrStartItem();
	if(hItem==NULL)
		return;
	if(GetItemLevel(hItem)!=0)
		hItem=GetParentItem(hItem);
	iLine = (ULONG)GetItemData(hItem,1);
	TMap<ULONG,HANDLE>::IT Iter=m_BookMark.FindAlmost(iLine);
	if(Iter.IsExist() && GetFirstItem(NULL,WISP_WLIS_SELECTED) == *Iter)
		Iter--;
	if(Iter.IsExist()==false)
		Iter = m_BookMark.Last();
	if(Iter.IsExist())
	{
		EnableVisible(*Iter);	
		SelectItem(*Iter);
	}
}

void CSourceCodeWnd::ClearAllBookMark()
{
	m_BookMark.Clear();
	gpSyser->m_MainFrame.m_SourceDebugFrameWnd.UpdateItemState();
	UpdateView();
}

int CCurrentFunction::m_GeneralRegisterIndexMap[8]=
{
	CV_REG_EAX,
		CV_REG_ECX,
		CV_REG_EDX,
		CV_REG_EBX,
		CV_REG_ESP,
		CV_REG_EBP,
		CV_REG_ESI,
		CV_REG_EDI,
};

CCurrentFunction::CCurrentFunction()
{
	m_BeginAddress=0;
	m_EndAddress=0;
	m_Size=0;
	m_pFunction=NULL;
	m_CurrentClass=NULL;
	m_pSDSModule=NULL;
}

CCurrentFunction::~CCurrentFunction()
{
	m_ContextDataList.Clear();
	m_ContextFuncList.Clear();
}

void CCurrentFunction::Init(CSDSModule* pSDSModule,PSDFUNCTIONITEM pFuncItem)
{
	if(pFuncItem==NULL)
	{
		m_BeginAddress=0;
		m_EndAddress=0;
		m_Size=0;
		m_pFunction=NULL;
		m_CurrentClass=NULL;
		m_ContextDataList.Clear();
		m_ContextFuncList.Clear();
		m_pSDSModule = pSDSModule;
	}
	else
	{
		m_pSDSModule = pSDSModule;
		CDbgModule*pDbgModule=gpSyser->m_pDebugger->m_ModuleList.GetModule(pSDSModule->m_ModuleFileName);
		if(pDbgModule)
			m_BeginAddress=pDbgModule->m_ModuleBase;
		else
			m_BeginAddress=0;
		m_EndAddress=m_BeginAddress+pFuncItem->Size;
		m_Size=pFuncItem->Size;
		m_pFunction=pFuncItem;
		InitVariableList();
	}
}
char* CCurrentFunction::FindNameByRegisterOffset(IN DWORD Offset,IN DWORD RegIndex,PSDUDTDATAITEM* pUdtData)
{
	CONTEXTDATALIST::IT BeginIT,EndIT;
	DWORD RegisterVal = m_GeneralRegisterIndexMap[RegIndex];
	PSDUDTDATAITEM pDataItem;
	if(pUdtData)
		*pUdtData=NULL;
	if(RegIndex>sizeof(m_GeneralRegisterIndexMap))
		return NULL;
	BeginIT=m_ContextDataList.Begin();
	EndIT=m_ContextDataList.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		pDataItem=*BeginIT;
		if(pDataItem->Location==LocIsRegRel&&pDataItem->u.LOCISREGREL.Register==RegisterVal&&Offset==pDataItem->u.LOCISREGREL.Offset)
		{
			if(pUdtData)
				*pUdtData=pDataItem;
			return pDataItem->uName.Name;
		}
	}
	return NULL;
}
PSDUDTDATAITEM CCurrentFunction::GetDataSymbolByName(char* Name,bool bCase)
{
	if(Name==NULL)
		return NULL;
	PSDUDTDATAITEM pDataItem;
	CONTEXTDATALIST::IT BeginIT,EndIT;
	BeginIT=m_ContextDataList.Begin();
	EndIT=m_ContextDataList.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		pDataItem = *BeginIT;
		if(bCase)
		{
			if(TStrCmp(Name,pDataItem->uName.Name)==0)
				return pDataItem;
		}
		else
		{
			if(TStrICmp(Name,pDataItem->uName.Name)==0)
				return pDataItem;
		}
	}
	pDataItem=NULL;
	if(m_pFunction->TypeIDParentUDT)
		pDataItem = m_pSDSModule->GetUdtClassDataMemberByName(Name,m_pSDSModule->GetTypeSymbol(m_pFunction->TypeIDParentUDT));
	if(pDataItem==NULL)
		pDataItem = m_pSDSModule->GetDataSymbolByNameAndKind(Name,DataIsGlobal);
	return pDataItem;
}
void CCurrentFunction::InitVariableList()
{
	PSDUDTDATAITEM pDataItem;
	PSDTYPE_INFILE  pType;
	m_ContextDataList.Clear();
	DWORD i,j;
	for(i = 0; i < m_pFunction->DataCounter; i++)
	{
		pDataItem = m_pSDSModule->GetDataSymbol(m_pFunction->pData.pDataMember[i]);
		if(pDataItem)
			m_ContextDataList.Append(pDataItem);
	}
	for(i = 0; i < m_pFunction->BlockCounter; i++)
	{
		pType = m_pSDSModule->GetTypeSymbol(m_pFunction->pBlock.pBlockTypeIdArray[i]);
		PSDBLOCK pBlock = (PSDBLOCK)&pType[1];
		for(j = 0; j < pBlock->DataCounter;j++)
		{
			pDataItem = m_pSDSModule->GetDataSymbol(pBlock->pDataMember[j]);
			if(pDataItem)
				m_ContextDataList.Append(pDataItem);
		}
	}

	pType = m_pSDSModule->GetTypeSymbol(m_pFunction->TypeIDParentUDT);
	if(pType!=m_CurrentClass&&pType)
	{
		m_ContextFuncList.Clear();
		AddUdtFuncMember(pType);
		m_CurrentClass=pType;
	}
	return ;
}
void CCurrentFunction::AddUdtFuncMember(PSDTYPE_INFILE pType)
{
	DWORD i;
	PSDFUNCTIONITEM pFuncItem;
	PSDUDTTYPE pUdtType;
	DWORD *pFuncIdArray;
	if(pType==NULL||(pType->Type!=SD_CLASS&&pType->Type!=SD_STRUCT&&pType->Type!=SD_UNION))
		return;
	pUdtType = (PSDUDTTYPE)&pType[1];
	if(pUdtType->FunctionCounter)
	{
		pFuncIdArray = pUdtType->pFunction.pFunctionMember;
		for(i = 0; i < pUdtType->FunctionCounter;i++)
		{
			pFuncItem = m_pSDSModule->GetFunctionSymbol(pFuncIdArray[i]);
			if(pFuncItem)
				m_ContextFuncList.Append(pFuncItem);
		}
	}
}

void CCurrentFunction::AddUdtDataMember(PSDTYPE_INFILE pType)
{
	DWORD i;
	PSDUDTDATAITEM pDataItem;
	PSDUDTTYPE pUdtType;
	DWORD *pDataIdArray;
	if(pType==NULL||(pType->Type!=SD_CLASS&&pType->Type!=SD_STRUCT&&pType->Type!=SD_UNION))
		return;
	pUdtType =(PSDUDTTYPE) &pType[1];
	if(pUdtType->DataCounter)
	{
		pDataIdArray = pUdtType->pData.pDataMember;
		for(i = 0; i < pUdtType->DataCounter;i++)
		{
			pDataItem = m_pSDSModule->GetDataSymbol(pDataIdArray[i]);
			if(pDataItem)
				m_ContextDataList.Append(pDataItem);
		}
	}
}

PSDFUNCTIONITEM CCurrentFunction::GetFunctionSymbolByName(char* Name,bool bCase)
{
	PSDFUNCTIONITEM pFuncItem=NULL;
	if(m_pFunction->TypeIDParentUDT)
		pFuncItem = m_pSDSModule->GetUdtClassFuncMemberByName(Name,m_CurrentClass);
	if(pFuncItem==NULL)
		pFuncItem = m_pSDSModule->GetFunctionSymbolByName(Name);
	return pFuncItem;
}

