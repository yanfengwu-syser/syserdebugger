#include "StdAfx.h"
#include "WispHexWnd.h"

WISP_MSG_MAP_BEGIN(CWispHexWnd)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_MOVE,OnMouseMove)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_RECALCLAYOUT,OnRecalcLayout)
	WISP_MSG_MAP(WISP_WM_SCROLL_EVENT,OnScrollEvent)
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
	WISP_MSG_MAP(WISP_WM_CHAR,OnChar)
	WISP_MSG_MAP(WISP_WM_SIZE,OnSize)
	WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_CMD_MAP_BEGIN(CWispHexWnd)
	WISP_MSG_CMD_MAP(WISP_ID_VSLIDE,OnCmdVSlide);
WISP_MSG_CMD_MAP_END

bool CWispHexWnd::OnCmdVSlide(IN WISP_MSG*pMsg)
{
	if((m_Style & WISP_HEX_WS_RELATIVE_SCROLL) && pMsg->Command.CmdMsg == WISP_CMD_BT_UP)
	{
		SetScrollBarCurPos(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,false);
	}
	return true;
}

bool CWispHexWnd::OnSize(IN WISP_MSG*pMsg)
{
	if(m_Style & WISP_HEX_WS_RELATIVE_SCROLL)
	{
		if(m_bShowOffset)
			SetScrollBarInfo(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,m_nLinePerPage*(m_ScrollSpace+m_ScrollSpace+1),m_nLinePerPage-1,0,false);
		else
			SetScrollBarInfo(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,m_nLinePerPage*(m_ScrollSpace+m_ScrollSpace+1),m_nLinePerPage,0,false);
	}
	else
	{
		SetScrollBarRange(WISP_SB_VERT,m_ImageHighBase/m_nByte_Line,m_ImageBase/m_nByte_Line);
	}
	SetScrollBarInfo(WISP_SB_HORZ,m_CharXPos,m_CharMax,m_nChars_Line,0);
	return true;
}

bool CWispHexWnd::OnCreate(IN WISP_MSG*pMsg)
{
	m_ItemColor[HEX_START_INDEX]=SYS_COLOR[SC_BLACK];
	m_ItemColor[HEX_POS_INDEX]=SYS_COLOR[SC_LIGHT_CYAN];
	m_ItemColor[HEX_HEX_INDEX]=SYS_COLOR[SC_LIGHT_GREEN] ;
	m_ItemColor[HEX_ASCII_INDEX]=SYS_COLOR[SC_UNNAMED_10];
	m_BSelColor=SYS_COLOR[SC_UNNAMED_11];
	m_TSelColor=SYS_COLOR[SC_WHITE];
	m_BBPXColor=SYS_COLOR[SC_UNNAMED_12];

	EnableScrollBar(WISP_SB_VERT);
	EnableScrollBar(WISP_SB_HORZ);
	CreateCaret(WISP_DI_CARET);
	ShowCaret(true);
	SetCaretPos(0,0);
	m_SelStart=m_SelEnd=-1;
	m_bSelect=m_bSelText=false;
	m_CurAddr=0;
	m_CharXPos=0;
	m_bBGColor	= true;
	m_crBGColor = SYS_COLOR[SC_BLACK];
	m_CaretPos.x = m_CaretPos.y = 0;
	m_AddrShowMode=ADDRESS_MODE_HEX;
	m_BaseActiveAddress=0;
	memset(m_PrevData,0,sizeof(m_PrevData));
	m_PrevDataAddress=0;
	m_PrevDataLen=0;
	m_CurrentDataLen=0;
	return true;
}

bool CWispHexWnd::OnChar(IN WISP_MSG*pMsg)
{
	CHAR	NumBuffer[10];
	DWORD	Addr;
	int		nLine;
	BYTE    DataBuf[4];
	BYTE	ValueB;
	ULPOS Pos,OldPos;
	WISP_MSG Msg;
	int Index;
	int BeginLine=GetStartLine();
	WISP_CHAR nChar = pMsg->Char.Char;
	Index = CorrectHitPoint(&m_CaretPos);
	if(Index==HEX_ASCII_INDEX)
	{
		if(CalcPonitPos(&m_CaretPos,&Pos)==false)
			return true;
		if(m_CaretIndex>=m_nByte_Line)
			return true;
		if(ReadData(Pos,DataBuf,1)==0)
			return true;
		DataBuf[0]=(char)nChar;
		if(WriteData(Pos,DataBuf,1)==0)
			return true;
		Msg.KeyEvent.bKeyDown=true;
		Msg.KeyEvent.KeyType=WISP_VK_RIGHT;
		OnKeyEvent(&Msg);
		return true;
	}
	if((nChar >='0' && nChar <='9') || (nChar <='F' && nChar >='A') || (nChar <='f' && nChar >='a'))
	{
		//if(CorrectHitPoint(&m_CaretPos)!=HEX_POS_INDEX)
		//	return true;
		switch(Index)
		{
			case HEX_POS_INDEX:
			{
				if(m_CaretIndex<8)
				{
					OldPos=m_CurAddr+(m_CaretnLine-BeginLine)*m_nByte_Line;
					TSPrintf(NumBuffer,"%08X",OldPos);
					NumBuffer[m_CaretIndex]=(CHAR)nChar;
					if(USHexStrToNum(NumBuffer,&Addr)==false)
						return true;
					nLine=(ULPOS)(Addr-m_ImageBase)/m_nByte_Line;
					if(nLine<m_CaretnLine)
					{
						m_CaretPos.y=nLine*m_LineHeight;
						ViewAddressMsg(m_ImageBase);
						m_CaretPos.x+=m_CharWidth;
						SetCaretPos(m_CaretPos.x,m_CaretPos.y);
						Update();
						return true;
					}
					nLine-=m_CaretnLine;
					if((DWORD)nLine<=m_ImageHighBase/m_nByte_Line-m_nLinePerPage)
					{
						
						ViewAddressMsg(Addr-OldPos+m_CurAddr);
						m_CaretPos.x+=m_CharWidth;
						SetCaretPos(m_CaretPos.x,m_CaretPos.y);
						Update();
						return true;
					}
					if((DWORD)nLine<m_ImageHighBase/m_nByte_Line)
					{
						m_CaretPos.y=(ULPOS)(Addr-m_CurAddr)/m_nByte_Line*m_LineHeight;
						m_CaretPos.x+=m_CharWidth;
						SetCaretPos(m_CaretPos.x,m_CaretPos.y);
						Update();
						return true;
					}
					return true;
				}
				//if(m_CaretIndex == 7)
				//{
				//	OldPos=m_CurAddr+(m_CaretnLine-BeginLine)*m_nByte_Line;
				//	sprintf(NumBuffer,"%08X",OldPos);
				//	NumBuffer[m_CaretIndex]=(CHAR)nChar;
				//	USHexStrToNum(NumBuffer,&Addr);
				//	if(Addr>=m_ImageBase+m_ImageSize)
				//		return true;
				//	ShowCaret(false);
				//	m_SelStart=Addr;
				//	m_SelEnd=m_SelStart;
				//	m_bSelect=TRUE;
				//	Update();
				//	return true;
				//}
				break;
			}
			case HEX_HEX_INDEX:
			{
				if((m_CaretIndex % (m_ShowLength*3))<(m_ShowLength*2))
				{
					if(CalcPonitPos(&m_CaretPos,&Pos)==false)
						break;
					Pos = Pos+ (m_ShowLength- 1 - (m_CaretIndex % (m_ShowLength*3))/2);
					if(ReadData(Pos,DataBuf,1)==0)
						break;
					ValueB=(char)nChar;
					if(ValueB>='0'&&ValueB<='9')
					{
						ValueB-='0';
					}
					else
					{
						ValueB|=0x20;
						ValueB = ValueB - 'a'+10;
					}
					if(((m_CaretIndex%(m_ShowLength*3))%2)==0)
					{
						ValueB<<=4;
						DataBuf[0] = ValueB | (DataBuf[0]&0xf);
					}
					else
					{
						DataBuf[0] = ValueB | (DataBuf[0]&0xf0);
					}
					if(WriteData(Pos,DataBuf,1)==0)
						break;
					Msg.KeyEvent.bKeyDown=true;
					Msg.KeyEvent.KeyType=WISP_VK_RIGHT;
					OnKeyEvent(&Msg);
					OnDataChange();
					break;
				}
				break;
			}
		}
	}
	return true;
}

bool CWispHexWnd::OnKeyEvent(IN WISP_MSG*pMsg)
{
	int Index;
	int Height=m_bShowOffset?m_LineHeight:0;
	if(pMsg->KeyEvent.bKeyDown)
	{
		switch(pMsg->KeyEvent.KeyType)
		{
		case WISP_VK_LBUTTON:
			WISP_POINT Point;
			Point=pMsg->MsgMouseWndPT;
			Point.y-=m_ClientRect.y;
			ShowCaret(true);
			m_CurArea =  CorrectHitPoint(&Point);
			m_CaretPos.x=Point.x-Point.x%m_CharWidth;
			m_CaretPos.y=Point.y-Point.y%m_LineHeight;
			if(m_bSelect)
			{
				m_bSelect=false;
				m_SelStart=m_SelEnd=-1;
			}
			SetCaretPos(m_CaretPos.x,m_CaretPos.y);
			UpdateClient();
			break;
		case WISP_VK_UP:
			if(m_CaretPos.y>=m_LineHeight+Height)
			{
				m_CaretPos.y-=m_LineHeight;
				CorrectHitPoint(&m_CaretPos);
				SetCaretPos(m_CaretPos.x,m_CaretPos.y);
				UpdateClient();
			}
			else if(m_CaretPos.y==(0+Height) && m_CurAddr>m_ImageBase)
			{
				m_CurAddr-=m_nByte_Line;
				if(m_CurAddr<m_ImageBase)
				{
					m_CurAddr=m_ImageBase;
					ViewAddressMsg(m_CurAddr);
				}
				CorrectHitPoint(&m_CaretPos);
				UpdateClient();
			}
			break;
		case WISP_VK_DOWN:
			if(m_CaretPos.y<(m_nLinePerPage-1)*m_LineHeight)
			{
				m_CaretPos.y+=m_LineHeight;
				CorrectHitPoint(&m_CaretPos);
				SetCaretPos(m_CaretPos.x,m_CaretPos.y);
				UpdateClient();
			}
			else if(m_CaretPos.y==(m_nLinePerPage-1)*m_LineHeight && 
					m_CurAddr<m_ImageHighBase-m_nLinePerPage*m_nByte_Line)
			{
				m_CurAddr+=m_nByte_Line;
				ViewAddressMsg(m_CurAddr);
				CorrectHitPoint(&m_CaretPos);
				UpdateClient();
			}
			break;
		case WISP_VK_LEFT:
			if(m_CaretPos.x>=m_CharWidth)
			{
				m_CaretPos.x-=m_CharWidth;
				Index = CorrectHitPoint(&m_CaretPos);
				if(Index==HEX_HEX_INDEX)
				{
					if((m_CaretIndex%(m_ShowLength*3)) >= m_ShowLength*2)
					{
						if(m_CaretPos.x >= m_CharWidth)
						{
							m_CaretPos.x-=m_CharWidth*m_ShowLength;
							m_CaretIndex-=m_ShowLength;
						}
					}
				}
				SetCaretPos(m_CaretPos.x,m_CaretPos.y);
				UpdateClient();
			}
			else if(m_CaretPos.x==0&&m_CharXPos>0)
			{
				m_CharXPos--;
				CorrectHitPoint(&m_CaretPos);
				UpdateClient();
			}
			break;
		case WISP_VK_RIGHT:
			if(m_CaretPos.x<m_nChars_Line*m_CharWidth)
			{
				m_CaretPos.x+=m_CharWidth;
				Index = CorrectHitPoint(&m_CaretPos);
				if(Index==HEX_HEX_INDEX)
				{
					if((m_CaretIndex%(m_ShowLength*3)) >= m_ShowLength*2)
					{
						if(m_CaretPos.x<m_nChars_Line*m_CharWidth)
						{
							m_CaretPos.x+=m_CharWidth*m_ShowLength;
							m_CaretIndex+=m_ShowLength;
						}
					}
				}
				SetCaretPos(m_CaretPos.x,m_CaretPos.y);
				UpdateClient();
			}
			else if(m_CaretPos.x==m_nChars_Line*m_CharWidth && m_CharXPos<m_CharMax)
			{
				m_CharXPos++;
				CorrectHitPoint(&m_CaretPos);
				UpdateClient();
			}
			break;
		case WISP_VK_HOME:
			m_CurAddr=m_ImageBase;
			ViewAddressMsg(m_CurAddr);
			UpdateClient();
			break;
		case WISP_VK_END:
			m_CurAddr=m_ImageHighBase-m_nLinePerPage*m_nByte_Line;
			ViewAddressMsg(m_CurAddr);
			UpdateClient();
			break;
		case WISP_VK_PAGE_UP:
			m_CurAddr-=m_nLinePerPage*m_nByte_Line;
			if(m_CurAddr<m_ImageBase)
				m_CurAddr=m_ImageBase;
			UpdateClient();
			break;
		case WISP_VK_PAGE_DOWN:
			m_CurAddr+=m_nLinePerPage*m_nByte_Line;
			if(m_CurAddr>m_ImageHighBase-m_nLinePerPage*m_nByte_Line)
				m_CurAddr=m_ImageHighBase-m_nLinePerPage*m_nByte_Line;
			ViewAddressMsg(m_CurAddr);
			UpdateClient();
			break;
		case WISP_VK_TAB:
			m_ShowLength*=2;
			if(m_ShowLength>=8)
				m_ShowLength=1;
			UpdateClient();
			break;
		case WISP_MOD_SHIFT|WISP_VK_TAB:
			{
				int MinX,MaxX;
				if(m_CurArea>=HEX_ASCII_INDEX)
					m_CurArea=HEX_POS_INDEX;
				else
					m_CurArea++;
				m_CharXPos=0;
				MinX=MaxX=0;
				for(int SpaceIndex=0;(DWORD)SpaceIndex<=m_CurArea;SpaceIndex++)
				{
					MinX=MaxX;
					MaxX+=m_ItemSpace[SpaceIndex]*m_CharWidth;
				}
						
				m_CaretPos.x=MinX;
				SetCaretPos(m_CaretPos.x,m_CaretPos.y);
				UpdateClient();
			}

			break;
		}
	}
	return true;
}
int CWispHexWnd::GetDataWidth()const
{
	return m_ShowLength;
}
bool CWispHexWnd::SetDataWidth(int width)
{
	if(16 % width)
		return false;
	m_ShowLength = width;
	Update();
	return true;
}

bool CWispHexWnd::OnMouseMove(IN WISP_MSG*pMsg)
{
	DWORD Pos;
	WISP_POINT	pt = pMsg->MsgMouseWndPT;
	PointToRect(&pt,&m_ClientRect);
	if(pMsg->bMsgLBTDown)
	{
		if(m_bSelect)
		{
			if(CalcPonitPos(&pt,&Pos)==false)
				return true;
			if(m_bSelText)
				m_SelEnd=Pos;
			else
				m_SelEnd=Pos+m_ShowLength-1;
		}
		else
		{
			if(CalcPonitPos(&pt,&Pos)==false)
				return true;
			ShowCaret(false);
			m_SelStart=Pos;
			m_bSelect=true;
			m_bSelText=m_CurArea==HEX_ASCII_INDEX;
		}
		Update();
	}
	return true;
}

bool CWispHexWnd::OnScrollEvent(IN WISP_MSG*pMsg)
{
	int LinePerPage=m_nLinePerPage;
	CWispWnd::OnScrollEvent(pMsg);
	if(m_bShowOffset)
		LinePerPage--;
	if(pMsg->ScrollEvent.SBType == WISP_SB_HORZ)
	{
		m_CharXPos = (int)m_ScrollBar[WISP_SB_HORZ]->CurPos;
	}
	else
	{
		if(m_Style&WISP_HEX_WS_RELATIVE_SCROLL)
		{
			switch(pMsg->ScrollEvent.Event)
			{
			case WISP_SB_PAGE_UP:
				
				ViewAddressMsg(m_CurAddr-LinePerPage*m_nByte_Line);
				break;
			case WISP_SB_PAGE_DOWN:
				ViewAddressMsg(m_CurAddr+LinePerPage*m_nByte_Line);
				break;
			case WISP_SB_DEC:
				ViewAddressMsg(m_CurAddr-m_nByte_Line);
				break;
			case WISP_SB_INC:
				ViewAddressMsg(m_CurAddr+m_nByte_Line);
				break;
			case WISP_SB_POS_CHANGE:
				ViewAddressMsg(m_CurAddr+m_nByte_Line*pMsg->ScrollEvent.Delta);
				return false;
				break;
			}
			SetScrollBarCurPos(WISP_SB_VERT,m_nLinePerPage*m_ScrollSpace,false);
			return false;
		}
		else
			ViewAddressMsg((ULPOS)(m_ScrollBar[WISP_SB_VERT]->CurPos*m_nByte_Line));
	}
	return false;
}
bool CWispHexWnd::IsModifyValue(ULPOS Address,BYTE* ValueBuffer)
{
	ULPOS Offset;
	if(Address>=m_PrevDataAddress && Address< m_PrevDataAddress+m_PrevDataLen)
	{
		Offset=Address-m_PrevDataAddress;
		for(int i=0;i<m_ShowLength;i++)
			if(m_PrevData[i+Offset]!=ValueBuffer[i])
				return true;
	}
	return false;
}
bool CWispHexWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
	BYTE DataBuffer[0x20];
	WISP_CHAR Buffer[512],szSpace[32];
	int nItem,Turn,AllLen,StrLen,BeginLine;
	DWORD Address,nByte,CurPos;
	bool bChangeColor;
	int ItemIndex,ij;
	CWispWnd::OnUpdateClient(pMsg);
	BeginLine=GetStartLine();
	m_CurrentDataLen=0;
	if(m_bShowOffset)
	{		
		AllLen=m_ItemSpace[HEX_START_INDEX];
		AllLen+=m_ItemSpace[HEX_POS_INDEX];
		nItem = m_nByte_Line/m_ShowLength;
		Turn=m_ShowLength*2+m_ShowLength;
		
		m_ClientDC.SetTextStyle(WISP_TEXT_TRANS);
		m_ClientDC.SetTextColor(m_ItemColor[HEX_POS_INDEX]);

		for(ItemIndex=0;ItemIndex<nItem;ItemIndex++)
		{
			if(m_OffsetMode==0)
			{
				for(ij = 0;ij < m_ShowLength;ij++)
					TSPrintf(&Buffer[ij*2],WSTR("%X "),(m_CurAddr+ItemIndex*m_ShowLength+(m_ShowLength-1-ij))%m_nByte_Line);
			}
			else
			{
				for(ij = 0;ij < m_ShowLength;ij++)
					TSPrintf(&Buffer[ij*2],WSTR("+%X"),ItemIndex*m_ShowLength+(m_ShowLength-1-ij));
			}
			
			m_ClientDC.DrawString((AllLen-m_CharXPos+ItemIndex*Turn)*m_CharWidth,0,Buffer,m_ShowLength*2);
		}
	}
	if(m_FloatMode)
	{
		Address =  GetFloatAddress(m_FloatString);
		if(Address!=m_CurAddr)
		{
			ViewAddressMsg(Address);
		}		
	}
	//长度队列填0
	ZeroMemory(m_LenArray,sizeof(m_LenArray));
	ZeroMemory(DataBuffer,sizeof(DataBuffer));
	for(int nLine=0;nLine<m_nLinePerPage;nLine++)
	{
		AllLen=m_ItemSpace[HEX_START_INDEX];
		Address=m_CurAddr+nLine*m_nByte_Line;
		switch(m_AddrShowMode)
		{
		case ADDRESS_MODE_HEX:
			TSPrintf(Buffer,WISP_STR("%08X:"),Address);
			break;
		case OFFSET_MODE_HEX:
			{
				int BaseAddress=(int)m_BaseActiveAddress;
				int Offset = (int)Address-BaseAddress;
				if(Offset>0)
				{
					TSPrintf(Buffer,WSTR("$+%X"),Offset);
				}else if(Offset==0)
				{
					TStrCpy(Buffer,"$ ==>");
				}else
				{
					TSPrintf(Buffer,WSTR("$-%X"),-Offset);
				}
			}
			break;
		}
		
		StrLen=(int)TStrLen(Buffer);
		m_LenArray[HEX_POS_INDEX][nLine]=StrLen;
		m_ClientDC.SetTextStyle(WISP_TEXT_TRANS);
		m_ClientDC.SetTextColor(m_ItemColor[HEX_POS_INDEX]);
		m_ClientDC.DrawString((AllLen-m_CharXPos)*m_CharWidth,(nLine+BeginLine)*m_LineHeight,Buffer,StrLen);
		AllLen+=m_ItemSpace[HEX_POS_INDEX];

		//调整最后一行的字节显示个数
		nByte=m_ImageSize+m_ImageBase-m_CurAddr-nLine*m_nByte_Line;
		if(nByte>(DWORD)m_nByte_Line)nByte=(DWORD)m_nByte_Line;
		//画字节
		TStrCpy(szSpace,m_Spaces);
		szSpace[m_ShowLength]=0;

		nItem=(int)nByte/m_ShowLength;
		if(nByte%m_ShowLength)
			nItem++;
		Turn=m_ShowLength*2+m_ShowLength;
		m_LenArray[HEX_HEX_INDEX][nLine]=Turn*nItem;
		for(ItemIndex=0;ItemIndex<nItem;ItemIndex++)
		{
			bChangeColor=false;
			if(ReadData(Address+ItemIndex*m_ShowLength,DataBuffer,m_ShowLength)==0)
				TStrCpy(Buffer,m_UnReadable);
			else
			{	
				THexBytesToStr(DataBuffer,Buffer,(int)nByte,m_ShowLength,szSpace);
				for(int mm=0;mm<m_ShowLength;mm++)
					m_CurrentData[m_CurrentDataLen+mm]=DataBuffer[mm];
				m_CurrentDataLen+=m_ShowLength;
				bChangeColor=IsModifyValue(Address+ItemIndex*m_ShowLength,DataBuffer);
			}
						
			CurPos=m_CurAddr+nLine*m_nByte_Line+ItemIndex*m_ShowLength;
			switch(GetHexByteAttribute(CurPos))//显示不同属性的字节
			{
			case HEX_BYTE_NORMAL:
				m_ClientDC.SetTextStyle(WISP_TEXT_TRANS);
				if(bChangeColor)
					m_ClientDC.SetTextColor(WISP_RGB(0xff,0xff,0));
				else
					m_ClientDC.SetTextColor(m_ItemColor[HEX_HEX_INDEX]);
				break;
			case HEX_BYTE_SEL:
				m_ClientDC.SetTextStyle(WISP_TEXT_OPAQUE);
				m_ClientDC.SetTextBKColor(m_BSelColor);
				if(bChangeColor)
					m_ClientDC.SetTextColor(WISP_RGB(0xff,0xff,0));
				else
					m_ClientDC.SetTextColor(m_TSelColor);
				break;
			case HEX_BYTE_MASK:
				m_ClientDC.SetTextStyle(WISP_TEXT_OPAQUE);
				m_ClientDC.SetTextBKColor(m_BBPXColor);
				m_ClientDC.SetTextColor(m_ItemColor[HEX_HEX_INDEX]);
				break;
			}
			m_ClientDC.DrawString((AllLen-m_CharXPos+ItemIndex*Turn)*m_CharWidth,(nLine+BeginLine)*m_LineHeight,Buffer,m_ShowLength*2);
		}
		AllLen+=m_ItemSpace[HEX_HEX_INDEX];
		//画ASCII
		m_LenArray[HEX_ASCII_INDEX][nLine]=m_nByte_Line;
		for(DWORD ByteIndex=0 ; ByteIndex < nByte; ByteIndex++)
		{
			if(ReadData((DWORD)(Address+ByteIndex),DataBuffer,1)==0)
				TStrCpy(Buffer,m_UnReadableASCII);
			else
				THexBytesToASCII(DataBuffer,Buffer,1);

			CurPos=m_CurAddr+nLine*m_nByte_Line+ByteIndex;
			switch(GetHexByteAttribute(CurPos))//显示不同属性的字节
			{
			case HEX_BYTE_NORMAL:
				m_ClientDC.SetTextStyle(WISP_TEXT_TRANS);
				m_ClientDC.SetTextBKColor(m_pWispBase->m_pCurDrawObj->m_crSystem[SC_CLIENT_BG]);
				m_ClientDC.SetTextColor(m_ItemColor[HEX_ASCII_INDEX]);
				break;
			case HEX_BYTE_SEL:
				m_ClientDC.SetTextStyle(WISP_TEXT_OPAQUE);
				m_ClientDC.SetTextBKColor(m_BSelColor);
				m_ClientDC.SetTextColor(m_TSelColor);
				break;
			}
			m_ClientDC.DrawString((AllLen-m_CharXPos+ByteIndex)*m_CharWidth,(nLine+BeginLine)*m_LineHeight,Buffer,1);
		}
		AllLen+=m_ItemSpace[HEX_ASCII_INDEX];
	}
	
	m_CurrentDataAddress=m_CurAddr;
	if(m_PrevDataLen==0)
		SaveContext();
	return false;
}

bool CWispHexWnd::OnRecalcLayout(IN WISP_MSG*pMsg)
{
	m_nChars_Line = m_ClientRect.cx/m_ClientDC.m_pFont->m_Width;
	m_nLinePerPage = m_ClientRect.cy/m_ClientDC.m_pFont->m_Height;
	m_CharWidth   = m_ClientDC.m_pFont->m_Width;
	m_LineHeight  = m_ClientDC.m_pFont->m_Height;

	if(m_ClientRect.cy%m_LineHeight > m_LineHeight/2)
		m_nLinePerPage++;

	if(m_ClientRect.cx<0)
		m_nChars_Line = 0;
	if(m_ClientRect.cy<0)
		m_nLinePerPage = 0;

	if(m_CurAddr>m_ImageHighBase-m_nLinePerPage*m_nByte_Line)
		m_CurAddr=m_ImageHighBase-m_nLinePerPage*m_nByte_Line;
	if(m_CurAddr<m_ImageBase)
		m_CurAddr=m_ImageBase;

	if(m_nChars_Line <= 1+10+m_nByte_Line*4 )
	{
		m_ItemSpace[HEX_START_INDEX]=1;
		m_ItemSpace[HEX_POS_INDEX]=10;
		m_ItemSpace[HEX_HEX_INDEX]=m_nByte_Line*3;
		m_ItemSpace[HEX_ASCII_INDEX]=m_nByte_Line+1;
	}
	else
	{
		int Width;
		m_CharXPos=0;
		m_ItemSpace[HEX_START_INDEX]=1;
		m_ItemSpace[HEX_ASCII_INDEX]=m_nByte_Line+1;
		Width=m_nChars_Line-m_ItemSpace[HEX_ASCII_INDEX]-m_ItemSpace[HEX_START_INDEX];
		Width=(Width-10-m_nByte_Line*3 )/2;
		m_ItemSpace[HEX_POS_INDEX]=10+Width;
		m_ItemSpace[HEX_HEX_INDEX]=m_nByte_Line*3+Width;
	}
	if((DWORD)m_nLinePerPage>m_ImageSize/(DWORD)m_nByte_Line)
		m_nLinePerPage=(int)(m_ImageSize/m_nByte_Line);
	m_CharMax=m_ItemSpace[HEX_START_INDEX]+m_ItemSpace[HEX_POS_INDEX]+m_ItemSpace[HEX_HEX_INDEX]+m_ItemSpace[HEX_ASCII_INDEX];
	MIN_LIMIT(m_CharMax,m_nChars_Line-1);
	return true;
}

ULSIZE CWispHexWnd::ReadData(ULPOS Address,BYTE*Buffer,ULSIZE Size)
{
	return 0;
}

ULSIZE CWispHexWnd::WriteData(ULPOS Address,BYTE*Buffer,ULSIZE Size)
{
	return 0;
}
UINT CWispHexWnd::GetHexByteAttribute(DWORD Address)
{
	DWORD Start,End;
	if(m_bSelect)
	{
		if(m_SelStart < m_SelEnd)
		{
			Start = m_SelStart;
			End  = m_SelEnd;
		}
		else
		{
			Start = m_SelEnd;
			End  = m_SelStart;
		}
		if(Start<m_ImageBase || End >=m_ImageBase+m_ImageSize)
			return HEX_BYTE_NORMAL;
		if(Address >= Start && Address <= End)
			return HEX_BYTE_SEL;
	}
	return HEX_BYTE_NORMAL;
}

WISP_CHAR* CWispHexWnd::m_UnReadable=WISP_STR("????????????????");
WISP_CHAR* CWispHexWnd::m_UnReadableASCII=WISP_STR("...................");
WISP_CHAR* CWispHexWnd::m_Spaces=WISP_STR("                ");

CWispHexWnd::CWispHexWnd()
{
	m_nByte_Line=0x10;
	m_ShowLength=1;
	m_CtrlType = WISP_CTRL_HEX_WND;
	m_ImageBase = 0;
	m_ImageSize =
	m_ImageHighBase = 0xFFFFFFFF;
	m_ScrollSpace = 4;
	m_bShowOffset=true;
	m_OffsetMode=0;
	m_FloatMode=false;	
	m_PrevDataAddress=0;
	m_PrevDataLen=0;
	m_CurrentDataLen=0;
	m_CurrentDataAddress=0;
	m_AddrIter=m_AddrList.Begin();
}

CWispHexWnd::~CWispHexWnd()
{
	m_AddrList.Clear();
}
void CWispHexWnd::SaveContext()
{
	DWORD dwStart,dwEnd;
	if(m_CurrentDataLen==0)
		return;
	dwStart=m_CurrentDataAddress;
	dwEnd=m_CurrentDataAddress+m_CurrentDataLen;
	for(DWORD i=0;i<m_PrevDataLen;i++)
	{
		if(m_PrevDataAddress+i >= dwStart && m_PrevDataAddress+i<dwEnd)
			m_CurrentData[m_PrevDataAddress+i-dwStart] =m_PrevData[i];
	}
	memcpy(m_PrevData,m_CurrentData,m_CurrentDataLen);
	m_PrevDataLen=m_CurrentDataLen;
	m_PrevDataAddress=m_CurrentDataAddress;
}
UINT CWispHexWnd::CorrectHitPoint(IN WISP_POINT*pPoint)
{
	int	nLine,MinX,MidX,MaxX,x;
	x=pPoint->x+m_CharXPos*m_CharWidth;
	nLine=pPoint->y/m_LineHeight;
	if(nLine>=m_nLinePerPage)
	{
		nLine=m_nLinePerPage-1;
		pPoint->y=m_LineHeight*nLine;
	}
	m_CaretnLine=pPoint->y/m_LineHeight;
	MinX=MaxX=0;
	//定位光标在哪个列上
	for(int SpaceIndex=0;SpaceIndex<=HEX_ASCII_INDEX;SpaceIndex++)
	{
		MinX=MaxX;
		MaxX+=m_ItemSpace[SpaceIndex]*m_CharWidth;
		if(x>=MinX&&x<MaxX)//如果在此列上
		{
			MidX=MinX+m_LenArray[SpaceIndex][nLine]*m_CharWidth;
			if(x>MidX)//如果超出此列显示长度
			{
				if(x-MidX<MaxX-x)//如果较靠近此列
				{
					pPoint->x=MidX-m_CharXPos*m_CharWidth;
					m_CaretIndex=(MidX-MinX)/m_CharWidth;
					return SpaceIndex;
				}
				else//如果较靠近下个列
				{
					pPoint->x=MaxX-m_CharXPos*m_CharWidth;
					m_CaretIndex=0;
					return SpaceIndex+1;
				}
			}
			else//如果在此列显示长度以内
			{
				m_CaretIndex=(pPoint->x-MinX)/m_CharWidth;
				return SpaceIndex;
			}
		}
	}
	pPoint->x=MaxX;
	m_CaretIndex=m_ItemSpace[HEX_ASCII_INDEX];
	return HEX_ASCII_INDEX;
}

bool CWispHexWnd::CalcPonitPos(IN WISP_POINT*pPoint,IN ULPOS*pPos,INOUT ULPOS* pOffset)
{
	int	nLine,MinX,nXCharLine,x;
	int BeginLine=GetStartLine();
	x=pPoint->x+m_CharXPos*m_CharWidth,
	nLine=pPoint->y/m_LineHeight;
	nXCharLine=3*m_nByte_Line-m_ShowLength;
	nXCharLine*=m_CharWidth;
	MinX=(m_ItemSpace[HEX_START_INDEX]+m_ItemSpace[HEX_POS_INDEX])*m_CharWidth;

	if(nLine<BeginLine)
		return false;
	nLine-=BeginLine;
	if(x>=MinX&&x<MinX+nXCharLine)
	{
		m_CurArea=HEX_HEX_INDEX;
		*pPos=m_CurAddr+nLine*m_nByte_Line+(x-MinX)/m_CharWidth/(m_ShowLength*3)*m_ShowLength;
		if(pOffset)
			*pOffset = (x-MinX)/m_CharWidth%(m_ShowLength*3);
		return true;
	}
	nXCharLine=m_nByte_Line*m_CharWidth;
	MinX+=m_ItemSpace[HEX_HEX_INDEX]*m_CharWidth;
	if(x>=MinX&&x<MinX+nXCharLine)
	{
		m_CurArea=HEX_ASCII_INDEX;
		*pPos=m_CurAddr+nLine*m_nByte_Line+(x-MinX)/m_CharWidth;
		return true;
	}
	return false;
}

bool CWispHexWnd::ViewAddress(IN ULPOS Address,bool bSave)
{
	ULPOS uPrevPos=m_CurAddr;
	if(Address<m_ImageBase || Address>=m_ImageHighBase)
		return false;
	if(m_Style&WISP_HEX_WS_RELATIVE_SCROLL)
	{		
		m_CurAddr = Address;
		if(m_CurAddr!=Address)
		{
			m_SelStart = Address;
			m_SelEnd = Address+m_ShowLength-1;
			m_bSelect = true;
			m_bSelText = false;
		}
	}
	else
	{
		if(m_nLinePerPage>0)
			SetScrollBarCurPos(WISP_SB_VERT,Address/m_nByte_Line,false);
	}
	if(bSave && m_CurAddr!=0)
	{
		RecordCurAddr(m_CurAddr,uPrevPos);
	}
	OnAddrChange();
	SaveContext();
	Update();
	return true;
}

bool CWispHexWnd::ViewAddressMsg(IN ULPOS Address,bool bSave)
{
	if(Address<m_ImageBase || Address>=m_ImageHighBase)
		return false;
	m_CurAddr=Address;
	SaveContext();
	OnAddrChange();
	return true;
}

void CWispHexWnd::ToggleShowOffset()
{
	m_bShowOffset=!m_bShowOffset;
	Update();
}
bool CWispHexWnd::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	int CurDataWidth;
	if(pMsg->KeyEvent.KeyType==WISP_VK_LBUTTON)
	{
		if(m_bShowOffset && pMsg->MsgMouseCltPT.y < m_LineHeight)
		{
			m_OffsetMode = 1 - m_OffsetMode;
			Update();
			return true;
		}
		CurDataWidth = GetDataWidth();
		CurDataWidth*=2;
		if(CurDataWidth>=8)
			CurDataWidth=1;
		if(m_CaretIndex>=0&&m_CaretIndex<=7&&m_CurArea==HEX_POS_INDEX)
			SetDataWidth(CurDataWidth);
	}
	return true;
}
void CWispHexWnd::SetAddressMode(int Mod,ULPOS BaseAddr)
{
	if(Mod <= 0 || Mod >=ADDRESS_MODE_MAX)
		Mod=ADDRESS_MODE_HEX;
	m_AddrShowMode=(ENUM_ADDR_SHOW_MOD)Mod;
	m_BaseActiveAddress = BaseAddr;
	OnUpdateClient(NULL);
	return ;
}
int CWispHexWnd::GetAddressMode()
{	
	return m_AddrShowMode;
}
void CWispHexWnd::SetFloatCmdString(WCHAR* pCmdString)
{
	m_FloatString=pCmdString;
}
bool CWispHexWnd::IsFloatMode()
{
	return m_FloatMode;
}
bool CWispHexWnd::ToggleFloatMode()
{
	m_FloatMode = !m_FloatMode;
	Update();
	return !m_FloatMode;
}

void CWispHexWnd::EmptyPosList()
{
	HISTORY_ADDRESS HistoryAddress;
	HistoryAddress.dwAddress=m_CurArea;
	m_AddrList.Clear();
	m_AddrIter = m_AddrList.Append(HistoryAddress);

}

bool CWispHexWnd::OnNextPos(IN WISP_MSG*pMsg)
{
	if(m_AddrIter!=m_AddrList.End() && m_AddrIter->dwAddress != m_CurAddr)
	{//如果当前地址不在当前存储点，先跳到这点上，再NextPos或PrevPos
		ViewAddress(m_AddrIter->dwAddress,false);
	}
	else if(m_AddrIter!=m_AddrList.Last())
	{
		m_AddrIter++;
		ViewAddress(m_AddrIter->dwAddress,false);
	}
	
	return true;
}

bool CWispHexWnd::OnPrevPos(IN WISP_MSG*pMsg)
{
	if(m_AddrIter!=m_AddrList.End() && m_AddrIter->dwAddress!= m_CurAddr)
	{//如果当前地址不在当前存储点，先跳到这点上，再NextPos或PrevPos
		ViewAddress(m_AddrIter->dwAddress,false);
	}
	else if(m_AddrIter!=m_AddrList.Begin())
	{
		m_AddrIter--;
		ViewAddress(m_AddrIter->dwAddress,false);
	}
	
	return true;
}

bool CWispHexWnd::OnSavePos(IN WISP_MSG*pMsg)
{
	HISTORY_ADDRESS HistoryAddress;
	HistoryAddress.dwAddress=m_CurArea;
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
	if(m_AddrList.Count()==0 || m_CurAddr!= m_AddrList.Last()->dwAddress)
		m_AddrIter = m_AddrList.Append(HistoryAddress);
	
	return true;
}

void  CWispHexWnd::RecordCurAddr(ULPOS Address,ULPOS PrevAddress)
{
	HISTORY_ADDRESS HistoryAddress;
	HistoryAddress.dwAddress=Address;
	if(m_AddrList.Count()>MAX_POS_LIST_COUNT)
	{
		if(m_AddrIter==m_AddrList.Begin())
			m_AddrIter++;
		m_AddrList.Remove(m_AddrList.Begin());
	}
	if(m_AddrList.Count()==0 && Address!=PrevAddress)
	{
		HistoryAddress.dwAddress=Address;
		m_AddrIter = m_AddrList.Append(HistoryAddress);
	}
	if( Address!= m_AddrList.Last()->dwAddress)
		m_AddrIter = m_AddrList.Append(HistoryAddress);
	
}