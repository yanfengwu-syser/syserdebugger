#ifndef _TSTRMEM_H_
#define _TSTRMEM_H_

NAME_SPACE_BEGIN

template<class CHAR_TYPE,class MODULE_CHAR_TYPE>
bool TCmpModuleName(IN const CHAR_TYPE*FileName,IN const MODULE_CHAR_TYPE*ModuleName)
{
	CHAR_TYPE FileCmpName[MAX_FN_LEN],*pStr;
	MODULE_CHAR_TYPE ModuleCmpName[MAX_FN_LEN];
	pStr = TStrRChr(ModuleName,(MODULE_CHAR_TYPE)PATH_SEPARATOR_CHAR);
	if(pStr)
		return TStrICmp(FileName,ModuleName)==0;
	pStr = TStrRChr(ModuleName,(MODULE_CHAR_TYPE)'.');
	if(pStr && TStrRChr(FileName,(MODULE_CHAR_TYPE)'.')==NULL)
		pStr = NULL;
	if(pStr)
	{
		TStrCpy(FileCmpName,TGetFileName(FileName));
		TStrCpy(ModuleCmpName,TGetFileName(ModuleName));
	}
	else
	{
		TGetFileTitle(FileName,FileCmpName);
		TGetFileTitle(ModuleName,ModuleCmpName);
	}
	return TStrICmp(FileCmpName,ModuleCmpName)==0;
}

#define HEX_CHAR(h)		(h<=9?'0'+h:'A'+h-10)

template<class CHAR_TYPE>
CHAR_TYPE*THexBytesToStr(IN BYTE* Hex,OUT CHAR_TYPE*String,IN int nHex,IN int Length,IN const CHAR_TYPE*szSpc=NULL)
{
    BYTE tmp,Data;
	CHAR_TYPE*pStr;
    int LeftLen,Turn=2*Length,StrLen=0,n;

	if(szSpc)
	{
		StrLen=TStrLen(szSpc);
		Turn+=StrLen;
	}
	
	for(n=0;n<nHex/Length;n++)
	{
		pStr=&String[n*Turn+2*Length];
		if(szSpc)
			TStrCpy(pStr,szSpc);
		for(int m=0;m<Length;m++)
		{
			Data=Hex[n*Length+m];
			tmp=Data%0x10;
			pStr--;
			*pStr=HEX_CHAR(tmp);
			tmp=Data>>4;
			pStr--;
			*pStr=HEX_CHAR(tmp);
		}
	}
	LeftLen=nHex%Length;
	if(LeftLen)
	{
		pStr=&String[n*Turn+2*LeftLen];
		for(int m=0;m<LeftLen;m++)
		{
			Data=Hex[n*Length+m];
			tmp=Data%0x10;
			pStr--;
			*pStr=HEX_CHAR(tmp);
			tmp=Data>>4;
			pStr--;
			*pStr=HEX_CHAR(tmp);
		}
		StrLen=0;
	}
	pStr=&String[n*Turn-StrLen+LeftLen*2];
	*pStr=0;
	return pStr;
}

template<class CHAR_TYPE>
void THexBytesToASCII(IN BYTE*Hex,OUT CHAR_TYPE*String,IN int nHex)
{
	int n;
	for(n=0;n<nHex;n++)
	{
		String[n]=Hex[n];
		if(String[n]<' ')
				String[n]='.';
	}
	String[n]=0;
}

template<class CHAR_TYPE>
int THexStrToBytes(IN const CHAR_TYPE*HexString,OUT BYTE*Mem,int MaxLength=32)
{
	CHAR_TYPE Char;
	BYTE Hex;
	int n=0;
	while(*HexString && n<MaxLength)
	{
		Char = HexString[1];
		if(Char>='0'&&Char<='9')
			Hex=Char-'0';
		else if(Char>='A'&&Char<='F')
			Hex=Char-'A'+10;
		else if(Char>='a'&&Char<='f')
			Hex=Char-'a'+10;
		else return 0;
		Char = *HexString;
		if(Char>='0'&&Char<='9')
			Hex+=(Char-'0')*16;
		else if(Char>='A'&&Char<='F')
			Hex+=(Char-'A'+10)*16;
		else if(Char>='a'&&Char<='f')
			Hex+=(Char-'a'+10)*16;
		else return 0;
		HexString+=2;
		Char = *HexString;
		if(Char==' ' || Char==',')
			HexString++;
		Mem[n++]=Hex;
	}
	return n;
}

template<class CHAR_TYPE>
DWORD TGetNameCode(CHAR_TYPE*Name)
{
	int Len;
	WORD Word=0;
	BYTE Byte=0;
	Len=TStrLen(Name);
	for(int n=0;n<Len;n++)
	{
		Byte+=(BYTE)Name[n];
		Word+=(WORD)Name[n];
	}
	return MAKE_DWORD(Word,MAKE_WORD(Byte,Len));
}

template<class CHAR_TYPE>
void TCorrectFileName(CHAR_TYPE*Name)
{
	while(*Name)
	{
		if(TStrChr("\\/:*?\"<>|",*Name))
			*Name='_';
		Name++;
	}
}
template<class TYPE>
TYPE*TStrTrimBefore(TYPE*buf,DWORD *Pos)
{
	int i;
	for(i=0;buf[i];i++)
		if(buf[i]==' '||buf[i]=='\t')
			continue;
		else
			break;
	if(!buf[i])
		i=0;
	if(Pos)
		*Pos=i;
	return buf+i;
}

template<class TYPE>
TYPE*TStrTrimAfter(TYPE*buf,DWORD* Pos)
{
	int i;
	for(i = 0;buf[i];)i++;
	i--;
	for(;i;i--)
		if(buf[i]==' '||buf[i]=='\t')
			continue;
		else
			break;
	if(Pos)
		*Pos=i;
	if(i)
		(*Pos)++;
	else
	{
		if(buf[i]==' '||buf[i]=='\t')
		{
			return buf;
		}
		return NULL;	
	}
	return buf+i;
}
template<class TYPE>
TYPE TStrTrim(TYPE buf,DWORD* Len)
{
	int m,j;
	int i;
	for(i = 0;buf[i];i++)
		if(buf[i]==' '||buf[i]=='\t')
			continue;
		else
			break;

	for(j=i;buf[j];j++);
	m=j-1;
	for(;m>=i;m--)
		if(buf[m]!=' '&&buf[m]!='\t')
			break;
	if(Len)
		*Len=m+1-i;
	return buf[i]?buf+i:buf;
}
NAME_SPACE_END

#endif
