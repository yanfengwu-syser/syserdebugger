#include "StdAfx.h"
#include "StrMem.h"

NAME_SPACE_BEGIN

#ifndef	CODE_OS_NT_DRV
int __cdecl sprintfcat_s(char*buffer,int buffer_size,const char*format,...)
{
	int length;
	length=(int)strlen(buffer);
	if(length>=buffer_size)
		return 0;
	va_list Next;
	va_start(Next,format);
	length += vsprintf_s(&buffer[length],buffer_size-length,format,Next);
	va_end(Next);
	return length;
}
#endif

int CSToStr(COLOR_STRING*pCS,PSTR pStr)
{	
	int Len;
	*pStr=0;
	Len=0;
	while(pCS->StrLen)
	{
		TStrCpy(&pStr[Len],pCS->String);
		Len+=pCS->StrLen;
		pCS=CSBuf(&pCS->String[pCS->StrLen+1]);
	}
	return Len;
}

UINT SplitCmdString(PSTR CmdString,PSTR*Param,UINT MaxParam)
{
	UINT Start,End,nParam,Length;
	PSTR pStr;
	nParam=End=Start=0;
	Length=(UINT)TStrLen(CmdString);
	pStr=TStrChr(CmdString,' ');
	if(pStr==NULL)
	{
		Param[0]=CmdString;
		nParam=1;
	}
	else
	{
		End=(UINT)(pStr-CmdString);
		memcpy(Param[0],CmdString,End);
		Param[0][End]=0;
		TStrUpr(Param[0]);
		nParam=1;
		Start=End;
		while(Start<Length)
		{
			while(Start<Length && CmdString[Start]==' ')
				Start++;
			pStr=TStrChr(&CmdString[Start],' ');
			if(pStr==NULL)End=Length;
			else		  End=(UINT)(pStr-CmdString);
			if(End<=Start)break;
			memcpy(Param[nParam],&CmdString[Start],End-Start);
			Param[nParam][End]=0;
			TStrUpr(Param[nParam]);
			Start=End;
			if(nParam>=MaxParam)break;
			nParam++;
		}
	}
	return nParam;
}

PSTR Tab2SpaceString(PCSTR TabBuffer,PSTR SpaceBuffer)
{
	DWORD toff=0,soff=0;
	
	while(TabBuffer[toff])
	{
		if(TabBuffer[toff]=='\t')
		{
			*(DWORD*)&SpaceBuffer[soff]=0x20202020;
			soff+=4;
		}
		else
		{
			SpaceBuffer[soff]=TabBuffer[toff];
			soff++;
		}
		toff++;
	}
	SpaceBuffer[soff]=0;
	return  SpaceBuffer;
}

CHAR InvalidVarStr[]=" \\|-={}[]/?*,:.&^%$#@!~`();\"<>^";
int Str2VarName(PSTR Str,int MaxLen)
{
	int size = 0;
	while(*Str && MaxLen)
	{
		if(TStrChr(InvalidVarStr,*Str))
			*Str='_';
		Str++;
		MaxLen--;
		size++;
	}
	*Str=0;
	return size;
}

bool IsASCString(PCSTR Str,int Length)
{
	while(*Str && Length)
	{
		if(*Str<=(char)0x20 && *Str>(char)0x80)
			return false;
		Str++;
		Length--;
	}
	return true;
}


DWORD GetCRCCode(BYTE*Buffer,int Len)
{
	WORD WordSum=0;
	WORD ByteSum=0;
	for(int n=0;n<Len;n++)
	{
		ByteSum+=Buffer[n];
		if(n+2<=Len)
			WordSum+=GET_WORD(Buffer,n);
	}
	return MAKE_DWORD(WordSum,ByteSum);
}

void*MemSearch(IN void*Buffer,IN int BufSize,IN void*SchBuf,IN int Len)
{
	for(int n = 0; n <=BufSize - Len; n++)
	{
		if(GET_BYTE(Buffer,n)==_GET_BYTE(SchBuf) && !memcmp((BYTE*)Buffer+n,SchBuf,Len))
			return (BYTE*)Buffer+n;
	}
	return NULL;
}

void*CodeSearch(IN void*Buffer,IN int BufSize,IN void*SchBuf,IN int Len,BYTE IgnoreByte)
{
	BYTE ScrByte;
	int n,m;
	if(BufSize==0)
		return NULL;
	for(n=0;n<=BufSize-Len;n++)
	{
		for(m=0;m<Len;m++)
		{
			ScrByte=GET_BYTE(SchBuf,m);
			if(ScrByte!=IgnoreByte&&ScrByte!=GET_BYTE(Buffer,n+m))
				break;
		}
		if(m>=Len)
			return RT_PBYTE(Buffer,n);
	}
	return NULL;
}

void PutByteAtBit(INOUT BYTE*Ptr,IN int BitOff,IN BYTE nBit,IN BYTE Data)
{
	BYTE Shift,Mask=0xFF;
	Shift=8-nBit;
	Mask=0xFF;
	Data<<=Shift;
	Data>>=Shift;
	Mask<<=Shift;
	Mask>>=Shift;
	if(nBit+BitOff%8<=8)//在一个字节中
	{
		Shift=(BYTE)BitOff%8;
		Data<<=Shift;
		Mask<<=Shift;
		Mask=~Mask;
		Ptr[BitOff/8]&=Mask;
		Ptr[BitOff/8]|=Data;
	}
	else
	{
		PutByteAtBit(Ptr,BitOff,(BYTE)(8-BitOff%8),Data);
		PutByteAtBit(Ptr,BitOff+8-BitOff%8,nBit-(BYTE)(8-BitOff%8),Data>>(8-BitOff%8));
	}
	return ;
}

#ifdef	CODE_OS_NT_DRV

int	UnicodeToAnsi(const WCHAR*WszBuf,char*szBuf,int MaxLen)
{
	ANSI_STRING	AnsiName;
	UNICODE_STRING UniName;
	UniName.Buffer =(PWSTR) WszBuf;
	UniName.Length = TStrLen(WszBuf)*2;
	UniName.MaximumLength = UniName.Length + 2;
	AnsiName.Buffer = (PCHAR)szBuf;
	AnsiName.Length = 0;
	AnsiName.MaximumLength = (USHORT)MaxLen;
	RtlUnicodeStringToAnsiString(&AnsiName,&UniName,false);
	return UniName.Length/2;
}

int	AnsiToUnicode(const char*szBuf,WCHAR*WszBuf,int MaxLen)
{
	ANSI_STRING	AnsiName;
	UNICODE_STRING UniName;
	AnsiName.Buffer = (PCHAR)szBuf;
	AnsiName.Length = (USHORT)TStrLen(szBuf);
	AnsiName.MaximumLength = AnsiName.Length + 1;
	UniName.Buffer = WszBuf;
	UniName.Length = 0;
	UniName.MaximumLength = MaxLen*2;
	RtlAnsiStringToUnicodeString(&UniName,&AnsiName,false);
	return AnsiName.Length;
}

#endif

#ifdef	CODE_OS_WIN

int	UnicodeToAnsi(const WCHAR*WszBuf,char*szBuf,int MaxLen)
{
	int Length;
	if(Length = WideCharToMultiByte(CP_ACP,0,WszBuf,-1,szBuf,MaxLen,NULL,NULL))
		return Length-1;
	return 0;
}

int	AnsiToUnicode(const char*szBuf,WCHAR*WszBuf,int MaxLen)
{
	int Length;
	if(Length = MultiByteToWideChar(CP_ACP,0,szBuf,-1,WszBuf,MaxLen))
		return Length-1;
	return 0;
}

#endif

#ifdef	CODE_OS_UNIX

int	UnicodeToAnsi(const WCHAR*WszBuf,char*szBuf,int MaxLen)
{
	return 0;
}

int	AnsiToUnicode(const char*szBuf,WCHAR*WszBuf,int MaxLen)
{
	return 0;
}

#endif

NAME_SPACE_END
