#ifndef _CODE_DOC_H_
#define _CODE_DOC_H_

#include "DbgModule.h"

enum CV_COLOR//颜色定义
{
	COLOR_NULL	= 0,
	COLOR_BK,				//背景
	COLOR_ADDRESS,			//地址
	COLOR_PREFIX,			//前缀
	COLOR_OPCODE,			//操作码
	COLOR_REGISTER,			//寄存器
	COLOR_SEG_REG,			//段寄存器
	COLOR_IMMED,			//立即数
	COLOR_OPTR,				//操作数
	COLOR_SYMBOL,			//变量符号
	COLOR_COMMENT,			//注释
	COLOR_KEYWORD,			//关键字
	COLOR_STR,				//字符串
	COLOR_BPX_STRIP,		//断点
	COLOR_EIP_STRIP,		//EIP
	COLOR_BPXEIP_STRIP,		//断点的
	COLOR_API_NAME,			//API名字
	COLOR_API_PARAM_TYPE,	//API参数类型
	COLOR_API_PARAM_NAME,	//API参数名字
	COLOR_JMP_LINE,			//Jmp线
	COLOR_ACTIVED_JMP_LINE,	//就要跳转的Jmp线
	COLOR_PREFIX_BYTE,		//opcode 中的 prefix 字节的颜色
	COLOR_OPCODE_BYTE,		//主 opcode 字节的颜色
	COLOR_REGRM_BYTE,		//opcode 中 RegRM 字节的颜色
	COLOR_SIB_BYPE,			//opcode 中 SIB 字节的颜色
	COLOR_OTHER_OPCODE_BYTE,		//opcode 中 其他字节的颜色
	COLOR_3DNOW_BYTE,		//如果指令是 3dNow 指令，这个最后一个字节的颜色 //immediate byte
	MAX_COLOR
};

#define CV_MARK_NULL			0x00000000
#define CV_MARK_EIP				0x00000001
#define CV_MARK_BPX				0x00000002
#define CV_MARK_DISABLED_BPX	0x00000004
#define CV_MARK_BOOK_MARK		0x00000008


typedef TExpCalc<CHAR,ULONG> CExpCalc;

class CCodeDoc
{
	bool	m_bIsOpened;
public:
	CCodeDoc();
	virtual	~CCodeDoc();
public:
	ULPOS		m_DocRangeStart;
	ULPOS		m_DocRangeEnd;
	virtual	bool	Open(PCSTR Name);
	virtual	void	Close();
	virtual ULSIZE	ReadImage(ULPOS Address,void*Buffer,ULSIZE Size) = 0;
	virtual	ULPOS	GetNextAddress(ULPOS Address,int Count) = 0;
	virtual	bool	GetSymbol(ULPOS Address,WCHAR*szSymbol,int BufSize);
	virtual	bool	GetComment(ULPOS Address,WCHAR*szComment,int BufSize);
	virtual	bool	SetComment(ULPOS Address,WCHAR*szComment);
	virtual	bool	GetLabel(ULPOS Address,WCHAR*szLabel,int BufSize);
	virtual	UINT	GetLineMark(ULPOS Address);
public:
	bool	inline	IsOpened(){	return m_bIsOpened;	}
};


#endif
