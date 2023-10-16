#include "StdAfx.h"
#include "SyserOptionApp.h"
#include "GUIColorPage.h"

enum 
{
	INDEX_clrBackground = 0,
	INDEX_clrText,
	INDEX_clrSelectedFrame,
	INDEX_clrLostFocusSelFrame,
	INDEX_clrChgText,
	INDEX_clrMON_MAX
};

WISP_OPTION_ITEM MonitorWindowOption[]=
{
	{WSTR("Background"),					OPTION_RGB_COLORREF,&ColorOption.clrBackground ,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Item text"),						OPTION_RGB_COLORREF,&ColorOption.clrText ,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Selected frame"),				OPTION_RGB_COLORREF,&ColorOption.clrSelectedFrame ,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Selected frame when lost focus"),OPTION_RGB_COLORREF,&ColorOption.clrLostFocusSelFrame,	sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Changed item text"),				OPTION_RGB_COLORREF,&ColorOption.clrChgText ,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{NULL}
};

enum 
{
	INDEX_clrCVBK = 0,
	INDEX_clrCVSelectedFrame,
	INDEX_clrCVLostFocusSelFrame,
	INDEX_clrCVAddr,
	INDEX_clrCVPrefix,
	INDEX_clrCVOpCode,
	INDEX_clrCVReg,
	INDEX_clrCVSegReg,
	INDEX_clrCVImmed,
	INDEX_clrCVOptr,
	INDEX_clrCVSymbol,
	INDEX_clrCVComment,
	INDEX_clrCVKeyword,
	INDEX_clrCVStr,
	INDEX_clrCVBPXStrip,
	INDEX_clrCVEIPStrip,
	INDEX_clrCVBPXEIPStrip,
	INDEX_clrCVAPIName,
	INDEX_clrCVAPIParamType,
	INDEX_clrCVAPIParamName,
	INDEX_clrCVJmpLine,
	INDEX_clrCVActivedJmpLine,
	INDEX_clrCVPrefixByte,
	INDEX_clrCVOpcodeByte,
	INDEX_clrCVRegRMByte,
	INDEX_clrCVSIBByte,
	INDEX_clrCVOtherOpcodeType,
	INDEX_clrCV3DNowByte,
	INDEX_clrCV_MAX
};

WISP_OPTION_ITEM CodeViewOption[]=
{
	{WSTR("Background"),					OPTION_RGB_COLORREF,&ColorOption.clrCVBK,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Selected frame"),				OPTION_RGB_COLORREF,&ColorOption.clrCVSelectedFrame,	sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Selected frame when lost focus"),OPTION_RGB_COLORREF,&ColorOption.clrCVLostFocusSelFrame,sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Address"),						OPTION_RGB_COLORREF,&ColorOption.clrCVAddr ,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Prefix"),						OPTION_RGB_COLORREF,&ColorOption.clrCVPrefix,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Operate Code"),					OPTION_RGB_COLORREF,&ColorOption.clrCVOpCode,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Register"),						OPTION_RGB_COLORREF,&ColorOption.clrCVReg,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Segment Register"),				OPTION_RGB_COLORREF,&ColorOption.clrCVSegReg,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Immed"),							OPTION_RGB_COLORREF,&ColorOption.clrCVImmed,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Operater"),						OPTION_RGB_COLORREF,&ColorOption.clrCVOptr,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Symbol"),						OPTION_RGB_COLORREF,&ColorOption.clrCVSymbol,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Comment"),						OPTION_RGB_COLORREF,&ColorOption.clrCVComment,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Keyword"),						OPTION_RGB_COLORREF,&ColorOption.clrCVKeyword,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("String"),						OPTION_RGB_COLORREF,&ColorOption.clrCVStr,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("BPX Strip"),						OPTION_RGB_COLORREF,&ColorOption.clrCVBPXStrip,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("EIP Strip"),						OPTION_RGB_COLORREF,&ColorOption.clrCVEIPStrip,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("BPX EIP Strip"),					OPTION_RGB_COLORREF,&ColorOption.clrCVBPXEIPStrip,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("API Name"),						OPTION_RGB_COLORREF,&ColorOption.clrCVAPIName,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Param Type"),					OPTION_RGB_COLORREF,&ColorOption.clrCVAPIParamType,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Param Name"),					OPTION_RGB_COLORREF,&ColorOption.clrCVAPIParamName,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Jump Line"),						OPTION_RGB_COLORREF,&ColorOption.clrCVJmpLine,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Actived Jump Line"),				OPTION_RGB_COLORREF,&ColorOption.clrCVActivedJmpLine,	sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Prefix Byte"),					OPTION_RGB_COLORREF,&ColorOption.clrCVPrefixByte,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Opcode Byte"),					OPTION_RGB_COLORREF,&ColorOption.clrCVOpcodeByte,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("RegRM Byte"),					OPTION_RGB_COLORREF,&ColorOption.clrCVRegRMByte,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("SIB Byte"),						OPTION_RGB_COLORREF,&ColorOption.clrCVSIBByte,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Other Opcode Byte"),				OPTION_RGB_COLORREF,&ColorOption.clrCVOtherOpcodeByte,	sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("3dNow! Immediate Byte"),			OPTION_RGB_COLORREF,&ColorOption.clrCV3DNowByte,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{NULL}
};

enum
{
	INDEX_clrSDBK = 0,
	INDEX_clrSDSelectedFrame,
	INDEX_clrSDLostFocusSelFrame,
	INDEX_clrSDKeyword,
	INDEX_clrSDId,
	INDEX_clrSDPrekeyWord,
	INDEX_clrSDCmtBlock,
	INDEX_clrSDCmtLine,
	INDEX_clrSDString,
	INDEX_clrSDNum,
	INDEX_clrSDOperation,
	INDEX_clrSDClassName,
	INDEX_clrSDStructName,
	INDEX_clrSDUnionName,
	INDEX_clrSDTypedefName,
	INDEX_clrSDFunctionName,
	INDEX_clrSDUnknown,
	INDEX_clrSD_MAX
};


WISP_OPTION_ITEM SourceCodeViewOption[]=
{
	{WSTR("Background"),					OPTION_RGB_COLORREF,&ColorOption.clrSDBK,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Selected frame"),				OPTION_RGB_COLORREF,&ColorOption.clrSDSelectedFrame,	sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Selected frame when lost focus"),OPTION_RGB_COLORREF,&ColorOption.clrSDLostFocusSelFrame,sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Keyword"),						OPTION_RGB_COLORREF,&ColorOption.clrSDKeyword,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Identifier"),					OPTION_RGB_COLORREF,&ColorOption.clrSDId,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Preprocessor Keyword"),			OPTION_RGB_COLORREF,&ColorOption.clrSDPrekeyWord,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Comment block"),					OPTION_RGB_COLORREF,&ColorOption.clrSDCmtBlock,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Comment line"),					OPTION_RGB_COLORREF,&ColorOption.clrSDCmtLine,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("String"),						OPTION_RGB_COLORREF,&ColorOption.clrSDString,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Numerical"),						OPTION_RGB_COLORREF,&ColorOption.clrSDNum,				sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Operation"),						OPTION_RGB_COLORREF,&ColorOption.clrSDOperation,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Class name"),					OPTION_RGB_COLORREF,&ColorOption.clrSDClassName,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Struct name"),					OPTION_RGB_COLORREF,&ColorOption.clrSDStructName,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Union name"),					OPTION_RGB_COLORREF,&ColorOption.clrSDUnionName,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Typedef name"),					OPTION_RGB_COLORREF,&ColorOption.clrSDTypedefName,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Function name"),					OPTION_RGB_COLORREF,&ColorOption.clrSDFunctionName,		sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{WSTR("Unknown"),						OPTION_RGB_COLORREF,&ColorOption.clrSDUnknown,			sizeof(COLORREF),NULL,NULL,&ColorOptionRef},
	{NULL}
};

WISP_OPTION_ITEM ColorOptionTitle[]=
{
	{WSTR("Monitor window"),OPTION_TITLE,MonitorWindowOption},
	{WSTR("Code View"),OPTION_TITLE,CodeViewOption},
	{WSTR("Source Code View"),OPTION_TITLE,SourceCodeViewOption},
	{NULL}
};

WISP_MSG_MAP_BEGIN(CGUIColorPage)
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispOptionForm)


WISP_MSG_CMD_MAP_BEGIN(CGUIColorPage)
	WISP_MSG_CMD_MAP(CMD_ID_OPTION_LIST,OnListCmd);
WISP_MSG_CMD_MAP_END

CGUIColorPage::FPGUIColorSimMothed	CGUIColorPage::m_Mothed[MAX_COLOR_DEMO]=
{
	&CGUIColorPage::DrawMonitorDemo,
	&CGUIColorPage::DrawCodeViewDemo,
	&CGUIColorPage::DrawSourceCodeViewDemo,
};

CGUIColorPage::CGUIColorPage()
{
	m_DemoHeight = 120;
	m_pOptionItem = ColorOptionTitle;
}

bool CGUIColorPage::OnFormCreate(IN WISP_MSG*pMsg)
{
	CWispOptionForm::OnFormCreate(pMsg);
	m_DemoGroup.Create(WISP_STR("Preview"),10,5,m_ClientRect.cx-20,m_DemoHeight-10,this);
	m_DemoDIB.Create(520,m_DemoGroup.m_WindowRect.cy - 25,WISP_DIB_BITMAP);
	m_DemoDIB.Clear();
	m_OptionList.Move(0,m_DemoHeight);
	m_OptionList.SetOwner(this);
	FillOptionTreeValue();
	if(ColorOption.CRCCode == OrgColorOption.CRCCode)
		m_pDefaultBT->EnableWindow(false);
	m_CurMothed = MAX_COLOR_DEMO;
	return false;
}

bool CGUIColorPage::OnSize(IN WISP_MSG*pMsg)
{
	m_DemoGroup.Resize(m_ClientRect.cx-20,m_DemoHeight-10);
	m_OptionList.Resize(m_ClientRect.cx-20,m_ClientRect.cy-50-m_DemoHeight);
	m_pRestoreBT->MoveToWindow(m_OptionList.m_ScrWindowRect.x-m_ScrWindowRect.x,m_OptionList.m_ScrWindowRect.y-m_ScrWindowRect.y+m_OptionList.m_WindowRect.cy+10);
	if(m_pDefaultBT->IsVisible())
		m_pDefaultBT->MoveToWindow(m_pRestoreBT->m_ScrWindowRect.x + m_pRestoreBT->m_WindowRect.cx + 10 -m_ScrWindowRect.x,m_pRestoreBT->m_ScrWindowRect.y-m_ScrWindowRect.y);
	m_pApplyBT->MoveToWindow(m_OptionList.m_ScrWindowRect.x + m_OptionList.m_ScrWindowRect.cx - m_pApplyBT->m_WindowRect.cx - m_ScrWindowRect.x,
		m_pRestoreBT->m_ScrWindowRect.y-m_ScrWindowRect.y);
	return false;
}

bool CGUIColorPage::OnDestroy(IN WISP_MSG*pMsg)
{
	m_DemoDIB.Destroy();
	return true;
}

bool CGUIColorPage::OnUpdateClient(IN WISP_MSG*pMsg)
{
	int x,y;
	CWispOptionForm::OnUpdateClient(pMsg);
	x = (m_ClientRect.cx-m_DemoDIB.Width())/2;
	y = 20;
	m_ClientDC.DrawDIB(x,y,&m_DemoDIB);
	m_ClientDC.DrawFrameRect(x-1,y-1,m_DemoDIB.Width()+2,m_DemoDIB.Height()+2,false);
	return false;
}

void CGUIColorPage::OptionApplyNotify()
{
	if(ColorOptionRef)//SyserColor.cfg被修改
	{
		ColorOptionRef = 0;
		SaveSyserOption(theApp.m_szColorCfgFN,&ColorOption,sizeof(ColorOption));
	}
	//比较配置文件是否和默认的一样,不一样则把Default按钮激活
	if(	ColorOption.CRCCode == OrgColorOption.CRCCode)
		m_pDefaultBT->EnableWindow(false);
	theApp.SendSyserMsg(IOCTL_SYSER_RELOAD_COLOR_CONFIG);
}

bool CGUIColorPage::OptionBeforeDefaultNotify()
{
	ColorOption = OrgColorOption;
	ColorOptionRef = 0;
	return true;
}

void CGUIColorPage::OptionDefaultNotify()
{
	SaveSyserOption(theApp.m_szColorCfgFN,&ColorOption,sizeof(ColorOption));
	if(m_CurMothed<MAX_COLOR_DEMO)
		(this->*m_Mothed[m_CurMothed])();
	theApp.SendSyserMsg(IOCTL_SYSER_RELOAD_COLOR_CONFIG);
}

bool CGUIColorPage::OnListCmd(IN WISP_MSG*pMsg)
{
	HANDLE hItem;
	if(pMsg->Command.CmdMsg != WISP_CMD_ITEM_SELECTED)
		return true;
	//切换Demo DIB;
	hItem = pMsg->Command.Param2;
	if(m_OptionList.GetItemLevel(hItem)==1)
		hItem = m_OptionList.GetParentItem(hItem);
	COLOR_DEMO_INDEX Mothed = (COLOR_DEMO_INDEX)m_OptionList.GetItemIndex(hItem);
	if(m_CurMothed!=Mothed)
	{
		m_CurMothed = Mothed;
		(this->*m_Mothed[m_CurMothed])();
	}
	return true;
}

void CGUIColorPage::DrawMonitorDemo()
{
	CWispDC dc;
	dc.AttachDIB(&m_DemoDIB);
	////////////////////////////
	COLORREF clrBackground = *(COLORREF*)MonitorWindowOption[INDEX_clrBackground].pNewValue;
	COLORREF clrText = *(COLORREF*)MonitorWindowOption[INDEX_clrText].pNewValue;
	COLORREF clrSelectedFrame = *(COLORREF*)MonitorWindowOption[INDEX_clrSelectedFrame].pNewValue;
	COLORREF clrChgText = *(COLORREF*)MonitorWindowOption[INDEX_clrChgText].pNewValue;
	
	
	dc.DrawFullRect(0,0,m_DemoDIB.Width(),m_DemoDIB.Height(),clrBackground);
	dc.SetTextColor(clrText);
	dc.DrawString(5,5,WSTR("EAX"));
	dc.DrawString(40,5,WSTR("00000001"));
	
	dc.DrawString(5,20,WSTR("EBX"));
	dc.SetTextColor(clrChgText);
	dc.DrawString(40,20,WSTR("7FFBC2A0"));
	dc.RestoreTextColor();

	dc.DrawString(5,35,WSTR("EIP"));
	dc.DrawString(40,35,WSTR("00401000"));
	
	dc.DrawRect(0,35,m_DemoDIB.Width()-1,12,clrSelectedFrame);

	////////////////////////////
	UpdateClient();
}

void CGUIColorPage::DrawCodeViewDemo()
{
	CWispDC dc;
	dc.AttachDIB(&m_DemoDIB);
	//////////////////////////////
	WISP_COLOR_CHAR szBuffer[256];
	COLORREF ColorTable[INDEX_clrCV_MAX];
	for(int n=0;n<INDEX_clrCV_MAX;n++)
	{
		ColorTable[n] = *(COLORREF*)CodeViewOption[n].pNewValue;
	}
	dc.SetColorTable(ColorTable);
	dc.DrawFullRect(0,0,m_DemoDIB.Width(),m_DemoDIB.Height(),ColorTable[INDEX_clrCVBK]);

	WISP_RECT rc;
	rc.x = 0;
	rc.y = 4;
	rc.cx = m_DemoDIB.Width();
	rc.cy = 15;
	dc.DrawFullRect(&rc,ColorTable[INDEX_clrCVEIPStrip]);
	rc.y+=30;
	dc.DrawRect(&rc,ColorTable[INDEX_clrCVSelectedFrame]);


	rc.y = 0;
	rc.cy = m_DemoDIB.Height();
	rc.cx = 2;

	rc.x = 55;
	dc.DrawFrameRect(&rc,false);
	rc.x = 110;
	dc.DrawFrameRect(&rc,false);
	rc.x = 270;
	dc.DrawFrameRect(&rc,false);

	dc.SetColorTable(ColorTable);
	int y = 5;
	int Off;
	Off = ColorStrCpy(szBuffer,		 "00401000 ",INDEX_clrCVAddr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"F3A4      ",INDEX_clrCVImmed,0);
	Off+= ColorStrCpy(&szBuffer[Off],"REPZ  ",INDEX_clrCVPrefix,0);
	Off+= ColorStrCpy(&szBuffer[Off],"MOVSB ",INDEX_clrCVOpCode,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;

	Off = ColorStrCpy(szBuffer,		 "00401002 ",INDEX_clrCVAddr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"E8003200  ",INDEX_clrCVImmed,0);
	Off+= ColorStrCpy(&szBuffer[Off],"CALL  ",INDEX_clrCVOpCode,0);
	Off+= ColorStrCpy(&szBuffer[Off],"Func_Symbol",INDEX_clrCVSymbol,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;

	Off = ColorStrCpy(szBuffer,		 "00401006 ",INDEX_clrCVAddr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"0FB701    ",INDEX_clrCVImmed,0);
	Off+= ColorStrCpy(&szBuffer[Off],"MOVZX ",INDEX_clrCVOpCode,0);
	Off+= ColorStrCpy(&szBuffer[Off],"EAX",INDEX_clrCVReg,0);
	Off+= ColorStrCpy(&szBuffer[Off],",",INDEX_clrCVOptr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"WORD PTR ",INDEX_clrCVKeyword,0);
	Off+= ColorStrCpy(&szBuffer[Off],"[",INDEX_clrCVOptr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"ECX",INDEX_clrCVReg,0);
	Off+= ColorStrCpy(&szBuffer[Off],"]",INDEX_clrCVOptr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"  Comment",INDEX_clrCVComment,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;

	Off = ColorStrCpy(szBuffer,		 "00401009 ",INDEX_clrCVAddr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"268B06    ",INDEX_clrCVImmed,0);
	Off+= ColorStrCpy(&szBuffer[Off],"MOV   ",INDEX_clrCVOpCode,0);
	Off+= ColorStrCpy(&szBuffer[Off],"EAX",INDEX_clrCVReg,0);
	Off+= ColorStrCpy(&szBuffer[Off],",",INDEX_clrCVOptr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"ES",INDEX_clrCVSegReg,0);
	Off+= ColorStrCpy(&szBuffer[Off],":[",INDEX_clrCVOptr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"ESI",INDEX_clrCVReg,0);
	Off+= ColorStrCpy(&szBuffer[Off],"]",INDEX_clrCVOptr,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;

	Off = ColorStrCpy(szBuffer,		 "0040100B ",INDEX_clrCVAddr,0);
	Off+= ColorStrCpy(&szBuffer[Off],"268B06    ",INDEX_clrCVImmed,0);
	Off+= ColorStrCpy(&szBuffer[Off],"CALL  ",INDEX_clrCVOpCode,0);
	Off+= ColorStrCpy(&szBuffer[Off],"SetLastError",INDEX_clrCVSymbol,0);
	Off+= ColorStrCpy(&szBuffer[Off],"        VOID ",INDEX_clrCVAPIParamType,0);
	Off+= ColorStrCpy(&szBuffer[Off],"SetLastError",INDEX_clrCVAPIName,0);
	Off+= ColorStrCpy(&szBuffer[Off],"(",INDEX_clrCVOpCode,0);
	Off+= ColorStrCpy(&szBuffer[Off],"IN DWORD ",INDEX_clrCVAPIParamType,0);
	Off+= ColorStrCpy(&szBuffer[Off],"dwErrCode",INDEX_clrCVAPIParamName,0);
	Off+= ColorStrCpy(&szBuffer[Off],")",INDEX_clrCVOpCode,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;

	////////////////////////////
	UpdateClient();
}

void CGUIColorPage::DrawSourceCodeViewDemo()
{
	CWispDC dc;
	dc.AttachDIB(&m_DemoDIB);
	//////////////////////////////
	WISP_COLOR_CHAR szBuffer[256];
	COLORREF ColorTable[INDEX_clrSD_MAX];
	for(int n=0;n<INDEX_clrSD_MAX;n++)
	{
		ColorTable[n] = *(COLORREF*)SourceCodeViewOption[n].pNewValue;
	}
	dc.SetColorTable(ColorTable);
	dc.DrawFullRect(0,0,m_DemoDIB.Width(),m_DemoDIB.Height(),ColorTable[INDEX_clrSDBK]);

	dc.SetColorTable(ColorTable);
	int y = 5;
	int Off;
	Off = ColorStrCpy(szBuffer,		 "#",INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"include ",INDEX_clrSDPrekeyWord,0);
	Off+= ColorStrCpy(&szBuffer[Off],"<",INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"stdio.h",INDEX_clrSDString,0);
	Off+= ColorStrCpy(&szBuffer[Off],">",INDEX_clrSDOperation,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;

	WISP_RECT rc;
	rc.x = 0;
	rc.y = 34;
	rc.cx = m_DemoDIB.Width();
	rc.cy = 15;
	dc.DrawRect(&rc,ColorTable[INDEX_clrSDSelectedFrame]);

	Off = ColorStrCpy(szBuffer,		 "int ",INDEX_clrSDKeyword,0);
	Off+= ColorStrCpy(&szBuffer[Off],"main",INDEX_clrSDFunctionName,0);
	Off+= ColorStrCpy(&szBuffer[Off],"(",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"int ",INDEX_clrSDKeyword,0);
	Off+= ColorStrCpy(&szBuffer[Off],"argc",INDEX_clrSDId,0);
	Off+= ColorStrCpy(&szBuffer[Off],",",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"char",INDEX_clrSDKeyword,0);
	Off+= ColorStrCpy(&szBuffer[Off],"*",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"argv",INDEX_clrSDId,0);
	Off+= ColorStrCpy(&szBuffer[Off],");",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"// Main Function",INDEX_clrSDCmtLine,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;
	Off = ColorStrCpy(szBuffer,		 "typedef int ",INDEX_clrSDKeyword,0);
	Off+= ColorStrCat(&szBuffer[Off],"INT",INDEX_clrSDTypedefName,0);
	Off+= ColorStrCpy(&szBuffer[Off],";",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"/* new typedef of int */",INDEX_clrSDCmtBlock,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;
	////////////////////////////
	Off = ColorStrCpy(szBuffer,		 "class ",INDEX_clrSDKeyword,0);
	Off+= ColorStrCat(&szBuffer[Off],"CFile",INDEX_clrSDClassName,0);
	Off+= ColorStrCpy(&szBuffer[Off],";",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"struct ",INDEX_clrSDKeyword,0);
	Off+= ColorStrCat(&szBuffer[Off],"ST_FILE",INDEX_clrSDStructName,0);
	Off+= ColorStrCpy(&szBuffer[Off],";",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"union ",INDEX_clrSDKeyword,0);
	Off+= ColorStrCat(&szBuffer[Off],"UN_FILE",INDEX_clrSDUnionName,0);
	Off+= ColorStrCpy(&szBuffer[Off],";",	INDEX_clrSDOperation,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;
	////////////////////////////
	Off = ColorStrCpy(szBuffer,		 "INT ",INDEX_clrSDTypedefName,0);
	Off+= ColorStrCat(&szBuffer[Off],"Value",INDEX_clrSDId,0);
	Off+= ColorStrCpy(&szBuffer[Off],"=",	INDEX_clrSDOperation,0);
	Off+= ColorStrCpy(&szBuffer[Off],"1000",INDEX_clrSDNum,0);
	Off+= ColorStrCpy(&szBuffer[Off],";",	INDEX_clrSDOperation,0);
	dc.DrawColorString(5,y,szBuffer);y+=15;
	UpdateClient();	
}

void CGUIColorPage::OnModify(HANDLE hItem)
{
	CWispOptionForm::OnModify(hItem);
	if(m_CurMothed<MAX_COLOR_DEMO)
		(this->*m_Mothed[m_CurMothed])();
}

void CGUIColorPage::OptionRestoreNotify()
{
	if(m_CurMothed<MAX_COLOR_DEMO)
		(this->*m_Mothed[m_CurMothed])();
}
