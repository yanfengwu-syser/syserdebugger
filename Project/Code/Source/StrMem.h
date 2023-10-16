#ifndef	_STRMEM_H_
#define _STRMEM_H_

NAME_SPACE_BEGIN

struct COLOR_STRING 
{
	WORD StrLen;
	WORD Attribute;
	COLORREF Color;
	CHAR String[1];
};

#define CSBuf(__P)	((COLOR_STRING*)__P)

int __cdecl sprintfcat_s(char*buffer,int buffer_size,const char*format,...);
int		CSToStr(COLOR_STRING*pCS,PSTR pStr);
PSTR	Tab2SpaceString(PCSTR TabBuffer,PSTR SpaceBuffer);
UINT	SplitCmdString(PSTR CmdString,PSTR*Param,UINT MaxParam);
int		Str2VarName(PSTR Str,int MaxLen);//字符串转换成C语言变量名
bool	IsASCString(PCSTR Str,int Length);
/////////////////////////////////////////////////////////////////////////
//内存操作
/////////////////////////////////////////////////////////////////////////
void*	MemSearch(IN void*Buffer,IN int BufSize,IN void*SchBuf,IN int Len);
void*	CodeSearch(IN void*Buffer,IN int BufSize,IN void*SchBuf,IN int Len,BYTE IgnoreByte = 0xFF);

void	PutByteAtBit(INOUT BYTE*Ptr,IN int BitOff,IN BYTE nBit,IN BYTE Data);
int		UnicodeToAnsi(const WCHAR*WszBuf,char*szBuf,int MaxLen);
int		AnsiToUnicode(const char*szBuf,WCHAR*WszBuf,int MaxLen);

DWORD GetCRCCode(BYTE*Buffer,int Len);

#ifdef CODE_OS_CATOS
#define memcpy(d,s,c)		TMemCpy((BYTE*)(d),(BYTE*)(s),(int)(c))
#endif

NAME_SPACE_END

#endif


