#ifndef _WISP_HEX_WND_H_
#define _WISP_HEX_WND_H_

#include "WispWnd.h"
#define MAX_POS_LIST_COUNT 100
enum ENUM_ADDR_SHOW_MOD
{
	ADDRESS_MODE_HEX,
	OFFSET_MODE_HEX,
	ADDRESS_MODE_MAX,
};

#define	MAX_LINES				0x100


#define WISP_HEX_WS_RELATIVE_SCROLL		0x00010000

enum
{
	HEX_START_INDEX = 0,
	HEX_POS_INDEX,		//文件位置空格
	HEX_HEX_INDEX,		//HEX字节空格
	HEX_ASCII_INDEX,	//ASCII空格
	HEX_ITEM_COUNT
};

enum
{
	HEX_BYTE_NORMAL = 0,
	HEX_BYTE_SEL,
	HEX_BYTE_MASK
};

class CWispHexWnd : public CWispWnd
{
	typedef struct _HISTORY_ADDRESS
	{
		DWORD dwAddress;
		WORD	wOffset;
		WORD	wFlags;
	}HISTORY_ADDRESS;
	typedef TList<HISTORY_ADDRESS> ADDR_LIST;
public:
	CWispHexWnd();
	~CWispHexWnd();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnChar)
	DECLARE_WISP_MSG(OnCreate)
	DECLARE_WISP_MSG(OnKeyEvent)
	DECLARE_WISP_MSG(OnMouseMove)
	DECLARE_WISP_MSG(OnUpdateClient)
	DECLARE_WISP_MSG(OnRecalcLayout)
	DECLARE_WISP_MSG(OnScrollEvent)
	DECLARE_WISP_MSG(OnSize)
	DECLARE_WISP_MSG(OnMouseDBClick);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG(OnCmdVSlide)
	DECLARE_WISP_MSG (OnPrevPos)
	DECLARE_WISP_MSG(OnNextPos)
	DECLARE_WISP_MSG(OnSavePos)
public:
	virtual ULSIZE	WriteData(ULPOS Address,BYTE*Buffer,ULSIZE Size);
	virtual ULSIZE	ReadData(ULPOS Address,BYTE*Buffer,ULSIZE Size);
	virtual	UINT	GetHexByteAttribute(IN DWORD Address);
	virtual ULPOS	GetFloatAddress(CStrW& CmdStr){return m_CurAddr;};
	virtual	void	OnAddrChange(){};
	virtual	void	OnDataChange(){};
	virtual	int	GetStartLine(){return m_bShowOffset?1:0;};
	UINT		CorrectHitPoint(IN WISP_POINT*pPoint);
	bool		CalcPonitPos(IN WISP_POINT*pPoint,IN ULPOS*pPos,INOUT ULPOS* pOffset=NULL);
	bool		ViewAddress(IN ULPOS Address,bool bSave=true);
	bool		ViewAddressMsg(IN ULPOS Address,bool bSave=false);
	bool		SetDataWidth(int width);
	int			GetDataWidth()const;
	void		SetAddressMode(int Mod,ULPOS BaseAddr=0);
	int			GetAddressMode();
	void		ToggleShowOffset();
	void		SetFloatCmdString(WCHAR* pCmdString);
	bool		ToggleFloatMode();
	bool		IsFloatMode();
	void		SaveContext();//用来保存当前显示的数据内容，用做下次高亮显示改变
public:
	int			m_OffsetMode;//0: +offset; 1:   //如果显示第一行的偏移信息,偏移模式 0 模式 +1 +2 +3  偏移模式 1 模式  1 2 3
	bool		m_bShowOffset;					//是否显示第一行的偏移
	ULPOS		m_ImageBase;
	ULSIZE		m_ImageSize;
	ULPOS		m_ImageHighBase;
	ULPOS		m_CurAddr;						//当前地址
	COLORREF	m_BSelColor;					//选择时背景颜色
	COLORREF	m_TextColor;					//文字颜色
	COLORREF	m_TSelColor;					//选择时文字颜色
	COLORREF	m_BBPXColor;					//Debug时BPX背景颜色 
	//屏幕信息
	int			m_ScrollSpace;
	int			m_ShowLength;					//数据显示宽度
	int			m_nLinePerPage;					//当前每页行数
	int			m_nChars_Line;					//每行字数
	int			m_LineHeight;					//行高
	int			m_CharWidth;					//字宽
	int			m_nByte_Line;					//一行字节数
	int			m_CharXPos;						//字符列位置
	int			m_CharMax;						//一行最大字符数
	int			m_CaretIndex;					//当前光标所在列字符串的索引
	int			m_CaretnLine;					//当前光标所在行
	WISP_POINT	m_CaretPos;						//光标的位置
	//用于剪切
	DWORD		m_SelStart;						//剪切开始
	DWORD		m_SelEnd;						//剪切结束
	bool		m_bSelect;						//是否处于剪切模式
	bool		m_bSelText;						//是否剪切文本
	DWORD		m_CurArea;						//当前区域
	//用于Search Next
	DWORD		m_SrhAddr;
	BYTE		m_SrhData[256];
	DWORD		m_SrhSize;
	DWORD		m_SrhLeftSize;
	bool		m_SrhbCase;
	int			m_LenArray[HEX_ITEM_COUNT][MAX_LINES];//长度数组，用于修正光标位置
	COLORREF	m_ItemColor[HEX_ITEM_COUNT];	//颜色数组
	int			m_ItemSpace[HEX_ITEM_COUNT];	//空格数组
	static WISP_CHAR*	m_UnReadable;
	static WISP_CHAR*	m_UnReadableASCII;
	static WISP_CHAR*	m_Spaces;
	ENUM_ADDR_SHOW_MOD	m_AddrShowMode;
	ULPOS	m_BaseActiveAddress;
	CStrW	m_FloatString;
	bool	m_FloatMode;
	//用来显示改变高亮使用
	BYTE	m_PrevData[0x1000];
	DWORD	m_PrevDataAddress;
	DWORD	m_CurrentDataAddress;
	DWORD	m_PrevDataLen;
	BYTE	m_CurrentData[0x1000];
	DWORD	m_CurrentDataLen;
	bool IsModifyValue(ULPOS Address,BYTE* ValueBuffer);//判断数据是否改边过
	ADDR_LIST m_AddrList;
	ADDR_LIST::IT	m_AddrIter;
	void EmptyPosList();
	void	RecordCurAddr(ULPOS Address,ULPOS uPrevAddress);

};

#endif
