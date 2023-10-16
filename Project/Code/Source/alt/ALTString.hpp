#ifndef _ALT_STRING_HPP_
#define _ALT_STRING_HPP_

ALT_NAME_SPACE_BEGIN
//TMemCpy		memcpy的模板
//TMemCCpy		memccpy的模板
//TMemChr		memchr的模板
//TMemCmp		memcmp的模板
//TMemICmp		memicmp的模板
//TMemSet		memset的模板
//TStrCpy		strcpy的模板
//TStrLen		strlen的模板
//TStrCat		strcat的模板
//TStrChr		strchr的模板
//TStrCmp		strcmp的模板
//TStrICmp		stricmp的模板
//TStrNCat		strncat的模板
//TStrNCmp		strncmp的模板
//TStrNCpy		strncpy的模板
//TStrNICmp		strnicmp的模板
//TStrNSet		strnset的模板
//TStrRChr		strrchr的模板
//TStrSet		strset的模板
//TStrStr		strstr的模板
//TStrIStr		strstr的大小写忽略版本模板
//TStrUpr		strupr的模板
//TStrOmit		将长字符串短成省略形式
//TStrFillTail	用某一字符添充字符串尾部
//TStrCpyLimit	复制有最大长度限制的字符串

template<class TYPE>
TYPE*TMemCpy(TYPE*dst,const TYPE*src,int count)
{
	TYPE*ret = dst;
	while(count--)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return ret;
}

template<class TYPE>
TYPE*TMemCCpy(TYPE*dest,const TYPE*src,unsigned char c,int count)
{
	while ( count && (*((unsigned char *)(dest = (unsigned char *)dest + 1) - 1) =
		*((unsigned char *)(src = (unsigned char *)src + 1) - 1)) != c )
		count--;
	return(count ? dest : NULL);
}

template<class TYPE>
TYPE*TMemChr(const TYPE*buf,TYPE chr,int cnt)
{
	while( cnt && *buf != chr)
	{
		buf++;
		cnt--;
	}
	return cnt ? buf : NULL;
}

template<class TYPE>
TYPE TMemCmp(const TYPE*buf1,const TYPE*buf2,int count)
{
	if(count==0)
		return 0;
	while(--count && *buf1 == *buf2)
	{
		buf1++;
		buf2++;
	}
	return	*buf1-*buf2;
}

template<class TYPE>
TYPE TMemICmp(const TYPE*first,const TYPE*last,int count)
{
	TYPE f = 0;
	TYPE l = 0;
	while(count--)
	{
		f=*first;
		l=*last;
		if(f>='A' && f<='Z')
			f-='A'-'a';
		if(l>='A' && l<='Z')
			l-='A'-'a';		
		if(f==l)
		{
			first++;
			last++;
		}
		else
			break;
	}
	return f - l;
}

template<class TYPE>
TYPE*TMemSet(TYPE *dst,TYPE val,int count)
{
	TYPE*start = dst;
	if(dst)
	{
		while(count--)
		{
			*dst = val;
			dst++;
		}
	}
	return start;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int TStrCpy(DES_CHAR_TYPE*dst,const SRC_CHAR_TYPE*src)
{
	if(NULL == dst)
		return NULL;

	int len=0;
	DES_CHAR_TYPE*cp = dst;
	if(src)
	{
		while( *cp++ = (DES_CHAR_TYPE)*src++ )
			len++;
	}
	return len;
}

template<class CHAR_TYPE>
int TStrLen(const CHAR_TYPE*str)
{
	if(NULL == str)
		return 0;
	
	const CHAR_TYPE*eos = str;
	while( *eos++ );
	return( (int)(eos - str - 1) );
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
DES_CHAR_TYPE*TStrCat(DES_CHAR_TYPE*dst,const SRC_CHAR_TYPE*src)
{
	if(dst && src)
	{
		DES_CHAR_TYPE*cp=dst;
		while( *cp )
			cp++;
		while( *cp++ = (DES_CHAR_TYPE)*src++ ) ;
	}
	return( dst );
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
SRC_CHAR_TYPE*TStrChr(const SRC_CHAR_TYPE*string,DES_CHAR_TYPE ch)
{
	if(string)
	{
		while(*string && *string != ch)
			string++;
		if(*string==ch)
			return (SRC_CHAR_TYPE*)string;
	}
	return NULL;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
SRC_CHAR_TYPE*TStrNChr(const SRC_CHAR_TYPE*string,DES_CHAR_TYPE ch,int count)
{
	if(string)
	{
		while(*string && *string != ch && count--)
			string++;
		if(*string==ch)
			return (SRC_CHAR_TYPE*)string;
	}
	return NULL;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
SRC_CHAR_TYPE*TStrIChr(const SRC_CHAR_TYPE*string,DES_CHAR_TYPE ch)
{
	if(string)
	{
		DES_CHAR_TYPE och;
		if((ch<'A'&&ch>'Z')&&(ch<'a'&&ch>'z'))
			return TStrChr(string,ch);
		och=(ch>='A' && ch<='Z')?(ch+'a'-'A'):(ch+'A' -'a');
		while(*string)
		{
			if(ch == *string || och == *string)
				return (SRC_CHAR_TYPE*)string;
			string++;
		}
	}
	return NULL;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
SRC_CHAR_TYPE*TStrNIChr(const SRC_CHAR_TYPE*string,DES_CHAR_TYPE ch,int count)
{
	if(string && (count>=0))
	{
		DES_CHAR_TYPE och;
		if((ch<'A'&&ch>'Z')&&(ch<'a'&&ch>'z'))
			return TStrChr(string,ch);
		och=(ch>='A' && ch<='Z')?(ch+'a'-'A'):(ch+'A' -'a');
		while(*string)
		{
			if(ch == *string || och == *string)
				return (SRC_CHAR_TYPE*)string;
			count--;
			if(count<0)
				break;
			string++;
		}
	}
	return NULL;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int TStrCmp(const DES_CHAR_TYPE* dst,const SRC_CHAR_TYPE* src)
{
	SRC_CHAR_TYPE ret;
	if(dst==NULL || src==NULL)
	{
		if(dst==NULL && src)
			return -(*src);
		if(dst && src==NULL)
			return (SRC_CHAR_TYPE)(*dst);
		return 0;
	}
	ret = 0 ;
	while( ! (ret = ( ((SRC_CHAR_TYPE)*dst) - *src)) && *dst)
		++src, ++dst;
	if( ret < 0 )
		ret = -1;
	else if ( ret > 0 )
		ret = 1;
	return (int)ret;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int TStrICmp(const DES_CHAR_TYPE* dst,const SRC_CHAR_TYPE* src)
{
	SRC_CHAR_TYPE f, l;
	if(dst==NULL || src==NULL)
	{
		if(dst==NULL && src)
			return -(*src);
		if(dst && src==NULL)
			return (SRC_CHAR_TYPE)(*dst);
		return 0;
	}
	do
	{
		if ( ((f = (SRC_CHAR_TYPE)(*(dst++))) >= 'A') && (f <= 'Z') )
			f -= 'A' - 'a';
		if ( ((l = (SRC_CHAR_TYPE)(*(src++))) >= 'A') && (l <= 'Z') )
			l -= 'A' - 'a';
	} while ( f && (f == l) );
	return(f - l);
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int	TStrNICmp(const DES_CHAR_TYPE*dst,const SRC_CHAR_TYPE*src,int count)
{
	SRC_CHAR_TYPE f, l;
	if(dst==NULL || src==NULL)
	{
		if(dst==NULL && src)
			return -(*src);
		if(dst && src==NULL)
			return (SRC_CHAR_TYPE)(*dst);
		return 0;
	}
	do
	{
		if ( ((f = (SRC_CHAR_TYPE)(*(dst++))) >= 'A') && (f <= 'Z') )
			f -= 'A' - 'a';
		if ( ((l = (SRC_CHAR_TYPE)(*(src++))) >= 'A') && (l <= 'Z') )
			l -= 'A' - 'a';
	} while ( --count && f && (f == l) );
	return (int)(f - l);
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
DES_CHAR_TYPE*TStrNCat(DES_CHAR_TYPE*front,const SRC_CHAR_TYPE*back,int count)
{
	DES_CHAR_TYPE*start = front;
	if(front && back && (count>0) )
	{
		while(*front++);
		front--;
		while(count--)
			if (!(*front++ = (DES_CHAR_TYPE)*back++))
				return start;
		*front = '\0';
	}
	return start;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int	TStrNCmp(const DES_CHAR_TYPE* dst,const SRC_CHAR_TYPE* src,int count)
{
	if(!count)
		return 0;
	if(dst==NULL || src==NULL)
	{
		if(dst==NULL && src)
			return -(int)(*src);
		if(dst && src==NULL)
			return (int)(*dst);
		return 0;
	}
	while(--count && *dst && *dst == *src)
	{
		dst++;
		src++;
	}
	return (int)*(SRC_CHAR_TYPE*)dst-(int)*(DES_CHAR_TYPE*)src;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
DES_CHAR_TYPE*TStrNCpy(DES_CHAR_TYPE* dest,const SRC_CHAR_TYPE*source,int count)
{
	DES_CHAR_TYPE*start = dest;
	if(dest && source && (count>0) )
	{
		while(count && (*dest++ = (DES_CHAR_TYPE)*source++))
			count--;
		if(count)
		{
			while(--count)
				*dest++ = '\0';
		}
	}
	return start;
}

template<class CHAR_TYPE>
int TCountOfChar(const CHAR_TYPE*string,CHAR_TYPE val)
{
	int count=0;
	if(string)
	{
		while(*string)
		{
			if(*string==val)
				count++;
			string++;
		}
	}
	return count;
}

template<class CHAR_TYPE>
CHAR_TYPE*TStrNSet(CHAR_TYPE*string,CHAR_TYPE val,int count)
{
	CHAR_TYPE*start = string;
	if(string && (count>0))
	{
		while(count-- && *string)
			*string++ = val;
	}
	return start;
}

template<class CHAR_TYPE>
CHAR_TYPE*TStrRChr(const CHAR_TYPE* string,CHAR_TYPE ch)
{
	CHAR_TYPE*start = (CHAR_TYPE*)string;
	while(*string++);
	while(--string != start && *string != (CHAR_TYPE)ch);
	if (*string == (CHAR_TYPE)ch)
		return( (CHAR_TYPE*)string );
	return NULL;
}

template<class CHAR_TYPE>
CHAR_TYPE*TStrRChr(const CHAR_TYPE* string,const CHAR_TYPE* start_string,CHAR_TYPE ch)
{
	CHAR_TYPE*start = (CHAR_TYPE*)string;
	string=start_string;
	while(--string != start && *string != (CHAR_TYPE)ch);
	if (*string == (CHAR_TYPE)ch)
		return( (CHAR_TYPE*)string );
	return NULL;
}

template<class CHAR_TYPE>
CHAR_TYPE*TStrSet(CHAR_TYPE*string,CHAR_TYPE val)
{
	CHAR_TYPE*start = string;
	if(string)
	{
		while(*string)
			*string++ = (CHAR_TYPE)val;
	}
	return start;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
DES_CHAR_TYPE*TStrIStr(const DES_CHAR_TYPE* str1,const SRC_CHAR_TYPE* str2)
{
	DES_CHAR_TYPE c1;
	SRC_CHAR_TYPE c2;
	const DES_CHAR_TYPE*s1;
	const SRC_CHAR_TYPE*s2;
	const DES_CHAR_TYPE*cp = str1;
	if( (NULL == str1) || (NULL == str2) )
		return NULL;
	if(!*str2)
		return (DES_CHAR_TYPE*)str1;
	while(*cp)
	{
		s1 = cp;
		s2 = str2;
		while ( *s1 && *s2 )
		{
			c1 =  *s1;
			c2 =  *s2;
			if(c1>='A' && c1<='Z')
				c1-='A'-'a';
			if(c2>='A' && c2<='Z')
				c2-='A'-'a';
			if(c1!=c2)
				break;
			s1++, s2++;
		}
		if(!*s2)
			return (DES_CHAR_TYPE*)cp;
		cp++;
	}
	return NULL;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
DES_CHAR_TYPE*TStrStr(const DES_CHAR_TYPE* str1,const SRC_CHAR_TYPE* str2)
{
	const DES_CHAR_TYPE*cp = str1;
	const DES_CHAR_TYPE*s1;
	const SRC_CHAR_TYPE*s2;
	if( (NULL == str1) || (NULL == str2) )
		return NULL;
	if ( !*str2 )
		return((DES_CHAR_TYPE*)str1);
	while (*cp)
	{
		s1 = cp;
		s2 = str2;
		while ( *s1 && *s2 && !(*s1-*s2) )
			s1++, s2++;
		if (!*s2)
			return (DES_CHAR_TYPE*)cp;
		cp++;
	}
	return NULL;
}

template<class CHAR_TYPE>
CHAR_TYPE* TStrUpr(CHAR_TYPE* string)
{
	CHAR_TYPE*cp;
	if(NULL != string)
	{
		for ( cp = string ; *cp ; ++cp )
			if ( ('a' <= *cp) && (*cp <= 'z') )
				*cp -= 'a' - 'A';
	}
	return string;
}

template<class CHAR_TYPE>
CHAR_TYPE* TStrLwr(CHAR_TYPE* string)
{
	CHAR_TYPE*cp;
	if(NULL != string)
	{
		for ( cp = string ; *cp ; ++cp )
			if ( ('A' <= *cp) && (*cp <= 'Z') )
				*cp += 'a' - 'A';
	}
	return string;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int TStrToStr(const SRC_CHAR_TYPE*Src,DES_CHAR_TYPE*Des)
{
	int Count=0;
	if( (NULL != Src) && (NULL != Des) )
	{
		while(Src[Count])
		{
			Des[Count]=(DES_CHAR_TYPE)Src[Count];
			Count++;
		}
		Des[Count]=0;
	}
	return Count;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int	TStrOmit(const SRC_CHAR_TYPE*Src,DES_CHAR_TYPE*Des,int MaxLen)
{
	int StrLen;
	MaxLen--;
	if( (MaxLen<=0) || (NULL == Src) || (NULL == Des) )
		return 0;
	StrLen=TStrLen(Src);
	if(StrLen<=MaxLen)
	{
		TStrCpy(Des,Src);
		return StrLen;
	}
	TStrCpyLimit(Des,Src,MaxLen+1);
	for(int i=1;i<=3;i++)
		Des[MaxLen-i]='.';
	return MaxLen;
}

template<class CHAR_TYPE>
int TStrFillTail(CHAR_TYPE*Str,int MaxLen,CHAR_TYPE FillChar)
{
	int StrLen=TStrLen(Str);
	if(StrLen >= MaxLen)
		return StrLen;
	else
		TMemSet(&Str[StrLen],FillChar,MaxLen-StrLen);
	Str[MaxLen]=0;
	return MaxLen;
}

template<class SRC_CHAR_TYPE,class DES_CHAR_TYPE>
int TStrCpyLimit(DES_CHAR_TYPE*Des,const SRC_CHAR_TYPE*Src,int Limit)
{
	int Len=0;
	Limit--;
	while(*Src && Len < Limit)
	{
		*Des=(DES_CHAR_TYPE)*Src;
		Des++;
		Src++;
		Len++;
	}
	*Des=0;
	return Len;
}


////////////////////////////////////////////////////////////////////////
//文件名处理
/////////////////////////////////////////////////////////////////////////
template<class CHAR_TYPE>
CHAR_TYPE*TGetPathItem(const CHAR_TYPE*PathName,CHAR_TYPE*ItemName)
{
	CHAR_TYPE*pStart,*pEnd;
	pStart=(CHAR_TYPE*)PathName;
	if(*pStart==PATH_SEPARATOR_CHAR)
		pStart++;
	pEnd=TStrChr(PathName,PATH_SEPARATOR_CHAR);
	if(pEnd==NULL)
		pEnd=&pStart[TStrLen(pStart)];
	TStrNCpy(ItemName,pStart,(int)(pEnd-pStart));
	if(pEnd)
		pEnd++;
	return pEnd;
}


template<class CHAR_TYPE>
CHAR_TYPE*TGetFileName(const CHAR_TYPE*szFullName)
{
	CHAR_TYPE*pStr;
	if(*szFullName==0)
		return NULL;
	pStr = TStrRChr(szFullName,(CHAR_TYPE)PATH_SEPARATOR_CHAR);
	if(pStr==NULL)
		return (CHAR_TYPE*)szFullName;
	return &pStr[1];
}


template<class CHAR_TYPE>
CHAR_TYPE*TGetFileExt(const CHAR_TYPE*szFullName)
{
	CHAR_TYPE*pStr;
	pStr = TGetFileName(szFullName);
	if(pStr==NULL)
		return NULL;
	pStr = TStrRChr(pStr,(CHAR_TYPE)'.');
	if(pStr==NULL || pStr[1]==0)
		return NULL;
	return &pStr[1];
}

template<class CHAR_TYPE>
int TGetFileTitle(const CHAR_TYPE*szFullName,CHAR_TYPE*szTitle)
{
	CHAR_TYPE*pStr,*pDot;
	if(NULL == szTitle)
		return 0;
	pStr = TGetFileName(szFullName);
	if(pStr==NULL)
	{
		*szTitle=0;
		return 0;
	}
	pDot = TStrRChr(pStr,(CHAR_TYPE)'.');
	if(pDot==NULL)
	{
		return TStrCpy(szTitle,pStr);
	}
	else
	{
		int Length = (int)(pDot-pStr);
		TMemCpy(szTitle,pStr,Length);
		szTitle[Length]=0;
		return Length;
	}
}

template<class CHAR_TYPE>
int TGetFilePath(const CHAR_TYPE*szFullName,CHAR_TYPE*szPath)
{
	CHAR_TYPE*pStr;
	pStr = TGetFileName(szFullName);
	if(pStr)
	{
		int Length;
		Length = (int)(pStr-szFullName);
		if(Length>0)
			Length--;
		TMemCpy(szPath,szFullName,Length);
		szPath[Length]=0;
		return Length;
	}
	else
	{
		return TStrCpy(szPath,szFullName);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
//通配符
////////////////////////////////////////////////////////////////////////////////////////////////
template<class CHAR_TYPE>
bool TMatchWithPattern(const CHAR_TYPE*Pattern,const CHAR_TYPE*Name)
{
	if(*Pattern=='\0')
		return true;
	if( *Pattern == '*' )
	{
		Pattern++;
		if(*Pattern=='\0')
			return true;
		while( *Name )
		{
			if( *Pattern == *Name || *Pattern == '?')
				if( TMatchWithPattern( Pattern+1, Name+1 ))
					return true;
			Name++;
		}
		return !(*Pattern && *Pattern != '*');
	}
	while( *Name && *Pattern != '*' )
	{
		if( *Pattern == *Name || *Pattern=='?')
		{
			Pattern++;
			Name++;
		}
		else
			return false;
	}
	if( *Name )
		return TMatchWithPattern( Pattern, Name );
	return !(*Pattern && *Pattern != '*');
}

template<class CHAR_TYPE>
bool TMultiMatchWithPattern(const CHAR_TYPE*Pattern,const CHAR_TYPE*Name)
{
	CHAR_TYPE  buf[256];
	CHAR_TYPE* pBegin,*pEnd;
	bool  Result;
	if(*Pattern=='\0')
		return true;
	TStrCpy(buf,Pattern);
	pBegin=buf+TStrLen(buf)-1;
	if(*pBegin==';')*pBegin='\0';
	pBegin=buf;
	while(pEnd=TStrChr(pBegin,(CHAR_TYPE)';'))
	{
		*pEnd='\0';
		Result=TMatchWithPattern(pBegin,Name);
		if(Result)
			return true;
		pBegin=pEnd+1;
	}
	Result=TMatchWithPattern(pBegin,Name);
	return Result;	
}

template<class CHAR_TYPE>
bool TIMatchWithPattern(const CHAR_TYPE*Pattern,const CHAR_TYPE*Name)
{
	if(*Pattern=='\0')
		return true;
	if( *Pattern == '*' )
	{
		Pattern++;
		if(*Pattern=='\0')
			return true;
		while( *Name )
		{
			if( LOWER_CHAR(*Pattern) == LOWER_CHAR(*Name) || *Pattern == '?')
				if( TIMatchWithPattern( Pattern+1, Name+1 ))
					return true;
			Name++;
		}
		return !(*Pattern && *Pattern != '*');
	}
	while( *Name && *Pattern != '*' )
	{
		if( LOWER_CHAR(*Pattern) == LOWER_CHAR(*Name) || *Pattern=='?')
		{
			Pattern++;
			Name++;
		}
		else
			return false;
	}
	if( *Name )
		return TIMatchWithPattern( Pattern, Name );
	return !(*Pattern && *Pattern != '*');
}

template<class CHAR_TYPE>
bool TIMultiMatchWithPattern(const CHAR_TYPE*Pattern,const CHAR_TYPE*Name)
{
	CHAR_TYPE  buf[256];
	CHAR_TYPE* pBegin,*pEnd;
	bool  Result;
	if(*Pattern=='\0')
		return true;
	TStrCpy(buf,Pattern);
	pBegin=buf+TStrLen(buf)-1;
	if(*pBegin==';')*pBegin='\0';
	pBegin=buf;
	while(pEnd=TStrChr(pBegin,';'))
	{
		*pEnd='\0';
		Result=TIMatchWithPattern(pBegin,Name);
		if(Result)
			return true;
		pBegin=pEnd+1;
	}
	Result=TIMatchWithPattern(pBegin,Name);
	return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//串数转换
////////////////////////////////////////////////////////////////////////////////////////////////
template<class TYPE,class CHAR_TYPE>
CHAR_TYPE* uNumToStr(TYPE Num,CHAR_TYPE* String,int Radix = 16)
{
	TYPE Pow,PrevPow,Digit;
	CHAR_TYPE* pStr;
	if(Num == 0)
	{
		String[0]='0';
		String[1]=0;
		return String;
	}
	if(Radix< 2||Radix>36)
	{
		*String = 0;
		return String;
	}
	pStr = String;
	for(PrevPow=0,Pow=1;(Num>=Pow)&&( (((Pow%Radix) == 0) || (Pow==1)) && (Pow > PrevPow));Pow*=(TYPE)Radix)
		PrevPow=Pow;
	Pow = PrevPow;
	while(Pow!= 0)
	{
		Digit = Num/Pow;
		*pStr = (CHAR) ((Digit <= 9) ? ('0'+Digit) : ('A'-10+Digit));
		pStr++;
		Num -= Digit*Pow;
		Pow /= (TYPE)Radix;
	}
	*pStr = 0;
	return String;
}

template<class TYPE,class CHAR_TYPE>
CHAR_TYPE* NumToStr(TYPE Num,CHAR_TYPE* String,int Radix = 16)
{
	TYPE Pow,PrevPow,Digit;
	CHAR_TYPE* pStr;
	if(Num==0)
	{
		String[0]='0';
		String[1]=0;
		return String;
	}
	if(Radix< 2||Radix>36)
	{
		*String = 0;
		return String;
	}
	pStr = String;
	if(Num<0)
	{
		*String='-';
		Num = -Num;
		pStr++;
	}
	for(PrevPow=0,Pow=1;(Num>=Pow)&&( (((Pow%Radix) == 0) || (Pow==1)) && (Pow > PrevPow));Pow*=Radix)
		PrevPow=Pow;
	Pow = PrevPow;
	while(Pow)
	{
		Digit = Num/Pow;
		*pStr = (CHAR_TYPE) ((Digit <= 9) ? ('0'+Digit) : ('a'-10+Digit));
		pStr++;
		Num -= Digit*Pow;
		Pow /= Radix;
	}
	*pStr = 0;
	return String;
}

template<class TYPE,class CHAR_TYPE>//十六进制字符串转有符号32位整数
bool SHexStrToNum(const CHAR_TYPE* String,TYPE* SHex)
{
	CHAR_TYPE Char;
	TYPE Sign,tmp,Len,Result;
	if(*String=='-')
	{
		Sign=-1;
		String++;
	}
	else
	{
		if(*String=='+')
			String++;
		Sign=1;
	}
		Len=Result=0;
	while(String[Len])
		Len++;

	if(Len>sizeof(TYPE)*2)
		return false;
	for(TYPE n=0;n<Len;n++)
	{
		Char=String[Len-1-n];
		if(Char>='0'&&Char<='9')
			tmp=(TYPE)(Char-'0');
		else if(Char>='A'&&Char<='F')
			tmp=(TYPE)(Char-'A'+10);
		else if(Char>='a'&&Char<='f')
			tmp=(TYPE)(Char-'a'+10);
		else return false;
		tmp<<=4*n;
		Result|=tmp;
	}
	Result*=Sign;
	if(SHex)
		*SHex=Result;
	return true;
}

template<class TYPE,class CHAR_TYPE>/*十六进制字符串转无符号32位整数 */
bool USHexStrToNum(const CHAR_TYPE* String,TYPE*USHex)
{
	CHAR_TYPE Char;
	TYPE tmp,Len,Result;
	Len=Result=0;
	while(String[Len])
		Len++;
	if(Len==0)
		return false;
	if(Len>sizeof(TYPE)*2)
		return false;
	for(TYPE n=0;n<Len;n++)
	{
		Char=String[Len-1-n];
		if(Char>='0'&&Char<='9')
			tmp=(TYPE)(Char-'0');
		else if(Char>='A'&&Char<='F')
			tmp=(TYPE)(Char-'A'+10);
		else if(Char>='a'&&Char<='f')
			tmp=(TYPE)(Char-'a'+10);
		else return false;
		tmp<<=4*n;
		Result|=tmp;
	}
	if(USHex)
		*USHex=Result;
	return true;
}

//十进制字符串转有符号32位整数
template<class TYPE,class CHAR_TYPE>
bool SDecStrToNum(const CHAR_TYPE* String,TYPE*SDec)
{
	CHAR_TYPE Char;
	TYPE Sign,tmp,Len,Result,X10Base;
	if(*String=='-')
	{
		Sign=-1;
		String++;
	}
	else
	{
		if(*String=='+')
			String++;
		Sign=1;	
	}
		Len=Result=0;
	while(String[Len])
		Len++;
	if(Len==0)
		return false;
	X10Base=1;
	for(TYPE n=0;n<Len;n++)
	{
		Char=String[Len-n-1];
		if(Char>='0'&&Char<='9')
			tmp=(TYPE)(Char-'0');
		else 
			return false;
		Result+=tmp*X10Base;
		X10Base*=10;
	}
	Result*=Sign;
	if(SDec)
		*SDec=Result;
	return true;
}
//十进制字符串转无符号32位整数
template<class TYPE,class CHAR_TYPE>
bool USDecStrToNum(const CHAR_TYPE* String,TYPE*USDec)
{
	CHAR_TYPE c;
	TYPE tmp,Len,Result,X10Base;
	Len=Result=0;
	while(String[Len])
		Len++;
	if(Len==0)
		return false;
	X10Base=1;
	for(TYPE n=0;n<Len;n++)
	{
		c=String[Len-n-1];
		if(c>='0'&&c<='9')
			tmp=(TYPE)c-'0';
		else 
			return false;
		Result+=tmp*X10Base;
		X10Base*=10;
	}
	if(USDec)
		*USDec=Result;
	return true;
}


#define MAX_SIG_DIGITS 20
#define EXP_DENORM_ADJUST MAX_SIG_DIGITS
#define MAX_ALLOWED_EXP (MAX_SIG_DIGITS  + EXP_DENORM_ADJUST - DBL_MIN_10_EXP)

#define DBL_DIG         15                      /* # of decimal digits of precision */
#if DBL_DIG > MAX_SIG_DIGITS
#error need to adjust MAX_SIG_DIGITS
#endif

#define INT_MAX       2147483647    /* maximum (signed) int value */
#if MAX_ALLOWED_EXP > INT_MAX
#error size assumption violated for MAX_ALLOWED_EXP
#endif

/* Note: For i386 the macro resulted in smaller code than the function call. */

#undef isdigit
#define isdigit(x) ( (x >= '0') && (x <= '9') )

template<class CHAR_TYPE>
double strtod(const CHAR_TYPE *str, CHAR_TYPE **endptr)
{
	double number;
	double p10;
	char *pos0;
	char *pos1;
	char *pos = (char *) str;
	int exponent_power;
	int exponent_temp;
	int negative;
	int num_digits;

	while (isspace(*pos)) {	/* skip leading whitespace */
		++pos;
	}

	negative = 0;
	switch(*pos) {		/* handle optional sign */
	case '-': negative = 1;	/* fall through to increment position */
	case '+': ++pos;
	}

	number = 0.;
	num_digits = -1;
	exponent_power = 0;
	pos0 = NULL;

LOOP:
	while (isdigit(*pos)) {	/* process string of digits */

		if (num_digits < 0) {	/* first time through? */
			++num_digits;	/* we've now seen a digit */
		}
		if (num_digits || (*pos != '0')) { /* had/have nonzero */
			++num_digits;
			if (num_digits <= MAX_SIG_DIGITS) { /* is digit significant */
				number = number * 10. + (*pos - '0');
			}
		}
		++pos;
	}

	if ((*pos == '.') && !pos0) { /* is this the first decimal point? */
		pos0 = ++pos;		/* save position of decimal point */
		goto LOOP;		/* and process rest of digits */
	}


	if (num_digits<0) {		/* must have at least one digit */
		pos = (char *) str;
		goto DONE;
	}



	if (num_digits > MAX_SIG_DIGITS) { /* adjust exponent for skipped digits */
		exponent_power += num_digits - MAX_SIG_DIGITS;
	}

	if (pos0) {
		exponent_power += pos0 - pos; /* adjust exponent for decimal point */
	}

	if (negative) {		/* correct for sign */
		number = -number;
		negative = 0;		/* reset for exponent processing below */
	}

	/* process an exponent string */
	if (*pos == 'e' || *pos == 'E') {

		pos1 = pos;

		switch(*++pos) {	/* handle optional sign */
	case '-': negative = 1;	/* fall through to increment pos */
	case '+': ++pos;
		}

		pos0 = pos;
		exponent_temp = 0;
		while (isdigit(*pos)) {	/* process string of digits */

			if (exponent_temp < MAX_ALLOWED_EXP) { /* overflow check */
				exponent_temp = exponent_temp * 10 + (*pos - '0');
			}
			++pos;
		}


		if (pos == pos0) {	/* were there no digits? */
			pos = pos1;		/* back up to e|E */
		} /* else */
		if (negative) {
			exponent_power -= exponent_temp;
		} else {
			exponent_power += exponent_temp;
		}
	}

	/* scale the result */

	exponent_temp = exponent_power;
	p10 = 10.;

	if (exponent_temp < 0) {
		exponent_temp = -exponent_temp;
	}

	while (exponent_temp) {
		if (exponent_temp & 1) {
			if (exponent_power < 0) {
				number /= p10;
			} else {
				number *= p10;
			}
		}
		exponent_temp >>= 1;
		p10 *= p10;
	}

DONE:

	if (endptr) {
		*endptr = pos;
	}

	return number;
}




#define PUTONE(c)		{if(buffer)*buffer++ = (c); Length++;}

#define CVTBUFSIZE  5000
typedef union
{
	double value;
	struct
	{
		unsigned int lsw;
		unsigned int msw;
	} parts;
} ieee_double_shape_type;


/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)				\
	do {								\
	ieee_double_shape_type ew_u;					\
	ew_u.value = (d);						\
	(ix0) = ew_u.parts.msw;					\
	(ix1) = ew_u.parts.lsw;					\
	} while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)					\
	do {								\
	ieee_double_shape_type gh_u;					\
	gh_u.value = (d);						\
	(i) = gh_u.parts.msw;						\
	} while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)					\
	do {								\
	ieee_double_shape_type gl_u;					\
	gl_u.value = (d);						\
	(i) = gl_u.parts.lsw;						\
	} while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)					\
	do {								\
	ieee_double_shape_type iw_u;					\
	iw_u.parts.msw = (ix0);					\
	iw_u.parts.lsw = (ix1);					\
	(d) = iw_u.value;						\
	} while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)					\
	do {								\
	ieee_double_shape_type sh_u;					\
	sh_u.value = (d);						\
	sh_u.parts.msw = (v);						\
	(d) = sh_u.value;						\
	} while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)					\
	do {								\
	ieee_double_shape_type sl_u;					\
	sl_u.value = (d);						\
	sl_u.parts.lsw = (v);						\
	(d) = sl_u.value;						\
	} while (0)




typedef union
{
	long double value;
	struct
	{
		unsigned int lsw;
		unsigned int msw;
		int sign_exponent:16;
		unsigned int empty:16;
	} parts;
} ieee_long_double_shape_type;


/* Get three 32 bit ints from a double.  */

#define GET_LDOUBLE_WORDS(exp,ix0,ix1,d)			\
	do {								\
	ieee_long_double_shape_type ew_u;				\
	ew_u.value = (d);						\
	(exp) = ew_u.parts.sign_exponent;				\
	(ix0) = ew_u.parts.msw;					\
	(ix1) = ew_u.parts.lsw;					\
	} while (0)

/* Set a double from two 32 bit ints.  */

#define SET_LDOUBLE_WORDS(d,exp,ix0,ix1)			\
	do {								\
	ieee_long_double_shape_type iw_u;				\
	iw_u.parts.sign_exponent = (exp);				\
	iw_u.parts.msw = (ix0);					\
	iw_u.parts.lsw = (ix1);					\
	(d) = iw_u.value;						\
	} while (0)

/* Get the more significant 32 bits of a long double mantissa.  */

#define GET_LDOUBLE_MSW(v,d)					\
	do {								\
	ieee_long_double_shape_type sh_u;				\
	sh_u.value = (d);						\
	(v) = sh_u.parts.msw;						\
	} while (0)

/* Set the more significant 32 bits of a long double mantissa from an int.  */

#define SET_LDOUBLE_MSW(d,v)					\
	do {								\
	ieee_long_double_shape_type sh_u;				\
	sh_u.value = (d);						\
	sh_u.parts.msw = (v);						\
	(d) = sh_u.value;						\
	} while (0)

/* Get int from the exponent of a long double.  */

#define GET_LDOUBLE_EXP(exp,d)					\
	do {								\
	ieee_long_double_shape_type ge_u;				\
	ge_u.value = (d);						\
	(exp) = ge_u.parts.sign_exponent;				\
	} while (0)

/* Set exponent of a long double from an int.  */

#define SET_LDOUBLE_EXP(d,exp)					\
	do {								\
	ieee_long_double_shape_type se_u;				\
	se_u.value = (d);						\
	se_u.parts.sign_exponent = (exp);				\
	(d) = se_u.value;						\
	} while (0)



const long double one = 1.0;

template<class FLOAT_TYPE>
FLOAT_TYPE modfl_for_ten_byte(FLOAT_TYPE x, FLOAT_TYPE *iptr)
{
	int i0,i1,j0;
	unsigned int i,se;
	GET_LDOUBLE_WORDS(se,i0,i1,x);
	j0 = (se&0x7fff)-0x3fff;	/* exponent of x */
	if(j0<32) {			/* integer part in high x */
		if(j0<0) {			/* |x|<1 */
			SET_LDOUBLE_WORDS(*iptr,se&0x8000,0,0);	/* *iptr = +-0 */
			return x;
		} else {
			i = (0x7fffffff)>>j0;
			if(((i0&i)|i1)==0) {		/* x is integral */
				*iptr = x;
				SET_LDOUBLE_WORDS(x,se&0x8000,0,0);	/* return +-0 */
				return x;
			} else {
				SET_LDOUBLE_WORDS(*iptr,se,i0&(~i),0);
				return x - *iptr;
			}
		}
	} else if (j0>63) {		/* no fraction part */
		*iptr = x*one;
		/* We must handle NaNs separately.  */
		if (j0 == 0x4000 && ((i0 & 0x7fffffff) | i1))
			return x*one;
		SET_LDOUBLE_WORDS(x,se&0x8000,0,0);	/* return +-0 */
		return x;
	} else {			/* fraction part in low x */
		i = ((u_int32_t)(0x7fffffff))>>(j0-32);
		if((i1&i)==0) { 		/* x is integral */
			*iptr = x;
			SET_LDOUBLE_WORDS(x,se&0x8000,0,0);	/* return +-0 */
			return x;
		} else {
			SET_LDOUBLE_WORDS(*iptr,se,i0,i1&(~i));
			return x - *iptr;
		}
	}
}




template<class FLOAT_TYPE>
FLOAT_TYPE mymodfl(FLOAT_TYPE x, FLOAT_TYPE *iptr)

{
	int i0,i1,j0;
	unsigned int i;
	EXTRACT_WORDS(i0,i1,x);
	j0 = ((i0>>20)&0x7ff)-0x3ff;	/* exponent of x */
	if(j0<20) {			/* integer part in high x */
		if(j0<0) {			/* |x|<1 */
			INSERT_WORDS(*iptr,i0&0x80000000,0);	/* *iptr = +-0 */
			return x;
		} else {
			i = (0x000fffff)>>j0;
			if(((i0&i)|i1)==0) {		/* x is integral */
				*iptr = x;
				INSERT_WORDS(x,i0&0x80000000,0);	/* return +-0 */
				return x;
			} else {
				INSERT_WORDS(*iptr,i0&(~i),0);
				return x - *iptr;
			}
		}
	} else if (j0>51) {		/* no fraction part */
		*iptr = x*one;
		/* We must handle NaNs separately.  */
		if (j0 == 0x400 && ((i0 & 0xfffff) | i1))
			return x*one;
		INSERT_WORDS(x,i0&0x80000000,0);	/* return +-0 */
		return x;
	} else {			/* fraction part in low x */
		i = ((unsigned int)(0xffffffff))>>(j0-20);
		if((i1&i)==0) { 		/* x is integral */
			*iptr = x;
			INSERT_WORDS(x,i0&0x80000000,0);	/* return +-0 */
			return x;
		} else {
			INSERT_WORDS(*iptr,i0,i1&(~i));
			return x - *iptr;
		}
	}
}

//#include "fcvt.h"
template<class CHAR_TYPE>
static CHAR_TYPE * mycvt( double arg, int ndigits, int * decpt, int * sign, CHAR_TYPE * buf, int eflag )
{
	int r2,r3=0;
	bool overflow=false;
	double fi, fj,fb,fa=0.0;
	CHAR_TYPE * p, * p1;

	if ( ndigits < 0 ) ndigits = 0;
	if ( ndigits >= CVTBUFSIZE - 1 ) ndigits = CVTBUFSIZE - 2;
	r2 = 0;
	* sign = 0;
	p = & buf[0];
	if ( arg < 0 )
	{
		* sign = 1;
		arg = - arg;
	}
	arg = mymodfl( arg, & fi );
	p1 = & buf[CVTBUFSIZE];

	if ( fi != 0 ) 
	{
		p1 = & buf[CVTBUFSIZE];
		fb = fi;
		while ( fi != 0 ) 
		{
			fj = mymodfl( fi / 10, & fi );
			if(p1 > p)
			{
				*-- p1 = ( int )(( fj + .03 ) * 10 ) + '0';
				fb=fi;
			}
			else
			{
				overflow=true;
				r3++;
			}
			r2 ++;
		}
		while ( p1 < & buf[CVTBUFSIZE] ) * p ++ = * p1 ++;
	} 
	else if ( arg > 0 )
	{
		while (( fj = arg * 10 ) < 1 ) 
		{
			arg = fj;
			r2 --;
		}
	}
	p1 = & buf[ndigits];
	if ( eflag == 0 ) p1 += r2;
	* decpt = r2;
	if ( p1 < & buf[0] ) 
	{
		buf[0] = '\0';
		return buf;
	}

	while ( p <= p1 && p < & buf[CVTBUFSIZE] )
	{
		arg *= 10;
		arg = mymodfl( arg, & fj );
		* p ++ = ( int ) fj + '0';
	}
	if ( p1 >= & buf[CVTBUFSIZE] ) 
	{
		buf[CVTBUFSIZE - 1] = '\0';
		return buf;
	}
	p = p1;
	* p1 += 5;
	while (* p1 > '9' ) 
	{
		* p1 = '0';
		if ( p1 > buf )
			++*-- p1;
		else 
		{
			* p1 = '1';
			(* decpt )++;
			if ( eflag == 0 ) 
			{
				if ( p > buf ) * p = '0';
				p ++;
			}
		}
	}
	* p = '\0';
	return buf;
}


template<class CHAR_TYPE>
CHAR_TYPE * ecvtbuf( double arg, int ndigits, int * decpt, int * sign, CHAR_TYPE * buf )
{
	return mycvt( arg, ndigits, decpt, sign, buf, 1 );
}


template<class CHAR_TYPE>
CHAR_TYPE * fcvtbuf( double arg, int ndigits, int * decpt, int * sign, CHAR_TYPE * buf )
{
	return mycvt( arg, ndigits, decpt, sign, buf, 0 );
}

template<class CHAR_TYPE>
void cfltcvt( double value, CHAR_TYPE * buffer, CHAR_TYPE fmt, int precision )
{
	int decpt, sign, exp, pos;
	CHAR_TYPE * digits = NULL;
	CHAR_TYPE cvtbuf[CVTBUFSIZE + 1];
	int capexp = 0;
	int magnitude;
	
	if ( fmt == 'G' || fmt == 'E' )
	{
		capexp = 1;
		fmt += 'a' - 'A';
	}

	if ( fmt == 'g' )
	{
		digits = ecvtbuf( value, precision, & decpt, & sign, cvtbuf );
		magnitude = decpt - 1;
		if ( magnitude < - 4  ||  magnitude > precision - 1 )
		{
			fmt = 'e';
			precision -= 1;
		}
		else
		{
			fmt = 'f';
			precision -= decpt;
		}
	}

	if ( fmt == 'e' )
	{
		digits = ecvtbuf( value, precision + 1, & decpt, & sign, cvtbuf );

		if ( sign ) * buffer ++ = '-';
		* buffer ++ = * digits;
		if ( precision > 0 ) * buffer ++ = '.';
		memcpy( buffer, digits + 1, precision*sizeof(CHAR_TYPE) );
		buffer += (precision);
		* buffer ++ = capexp ? 'E' : 'e';

		if ( decpt == 0 )
		{
			if ( value == 0.0 )
				exp = 0;
			else
				exp = - 1;
		}
		else
			exp = decpt - 1;

		if ( exp < 0 )
		{
			* buffer ++ = '-';
			exp = - exp;
		}
		else
			* buffer ++ = '+';

		buffer[2] = ( exp % 10 ) + '0';
		exp = exp / 10;
		buffer[1] = ( exp % 10 ) + '0';
		exp = exp / 10;
		buffer[0] = ( exp % 10 ) + '0';
		buffer += 3;
	}
	else if ( fmt == 'f' )
	{
		digits = fcvtbuf( value, precision, & decpt, & sign, cvtbuf );
		if ( sign ) * buffer ++ = '-';
		if (* digits )
		{
			if ( decpt <= 0 )
			{
				* buffer ++ = '0';
				* buffer ++ = '.';
				for ( pos = 0; pos < - decpt; pos ++) * buffer ++ = '0';
				while (* digits ) * buffer ++ = * digits ++;
			}
			else
			{
				pos = 0;
				while (* digits )
				{
					if ( pos ++ == decpt ) * buffer ++ = '.';
					* buffer ++ = * digits ++;
				}
			}
		}
		else
		{
			* buffer ++ = '0';
			if ( precision > 0 )
			{
				* buffer ++ = '.';
				for ( pos = 0; pos < precision; pos ++) * buffer ++ = '0';
			}
		}
	}

	* buffer = '\0';
}
template<class CHAR_TYPE>
void forcdecpt( CHAR_TYPE * buffer )
{
	while (* buffer )
	{
		if (* buffer == '.' ) return;
		if (* buffer == 'e' || * buffer == 'E' ) break;
		buffer ++;
	}

	if (* buffer )
	{
		int n = TStrLen( buffer );
		while ( n > 0 ) 
		{
			buffer[n + 1] = buffer[n];
			n --;
		}

		* buffer = '.';
	}
	else
	{
		* buffer ++ = '.';
		* buffer = '\0';
	}
}

template<class CHAR_TYPE>
void cropzeros( CHAR_TYPE * buffer )
{
	CHAR_TYPE * stop;

	while (* buffer && * buffer != '.' ) buffer ++;
	if (* buffer ++)
	{
		while (* buffer && * buffer != 'e' && * buffer != 'E' ) buffer ++;
		stop = buffer --;
		while (* buffer == '0' ) buffer --;
		if (* buffer == '.' ) buffer --;
		while (*++ buffer = * stop ++);
	}
}

#define TVSP_ZEROPAD 1               // Pad with zero
#define TVSP_SIGN    2               // Unsigned/signed long
#define TVSP_PLUS    4               // Show plus
#define TVSP_SPACE   8               // Space if plus
#define TVSP_LEFT    16              // Left justified
#define TVSP_SPECIAL 32              // 0x
#define TVSP_LARGE   64              // Use 'ABCDEF' instead of 'abcdef'

template<class CHAR_TYPE>
CHAR_TYPE * myflt( CHAR_TYPE * str, double num, int size, int precision, CHAR_TYPE fmt, int flags )
{
	CHAR_TYPE tmp[80];
	char c, sign;
	int n, i;

	// Left align means no zero padding
	if ( flags & TVSP_LEFT ) flags &= ~ TVSP_ZEROPAD;

	// Determine padding and sign char
	c = ( flags & TVSP_ZEROPAD ) ? '0' : ' ';
	sign = 0;
	if ( flags & TVSP_SIGN )
	{
		if ( num < 0.0 )
		{
			sign = '-';
			num = - num;
			size --;
		}
		else if ( flags & TVSP_PLUS )
		{
			sign = '+';
			size --;
		}
		else if ( flags & TVSP_SPACE )
		{
			sign = ' ';
			size --;
		}
	}

	// Compute the precision value
	if ( precision < 0 )
		precision = 6; // Default precision: 6
	else if ( precision == 0 && fmt == 'g' )
		precision = 1; // ANSI specified

	// Convert floating point number to text
	cfltcvt( num, tmp, fmt, precision );

	// '#' and precision == 0 means force a decimal point
	if (( flags & TVSP_SPECIAL ) && precision == 0 ) forcdecpt( tmp );

	// 'g' format means crop zero unless '#' given
	if ( fmt == 'g' && !( flags & TVSP_SPECIAL )) cropzeros( tmp );

	n = TStrLen( tmp );

	// Output number with alignment and padding
	size -= n;
	if (!( flags & ( TVSP_ZEROPAD | TVSP_LEFT ))) while ( size -- > 0 ) * str ++ = ' ';
	if ( sign ) * str ++ = sign;
	if (!( flags & TVSP_LEFT )) while ( size -- > 0 ) * str ++ = c;
	for ( i = 0; i < n; i ++) * str ++ = tmp[i];
	while ( size -- > 0 ) * str ++ = ' ';

	return str;
}



template<class CHAR_TYPE>
int TVSPrintf(CHAR_TYPE*buffer,const CHAR_TYPE*format,void*ParamList)
{
	int   nFlags;
	int   Length;				// Limit at entry point
	bool  bMore;				// Loop control
	int	  Width;				// Optional width
	int   Precision;			// Optional precision
	CHAR_TYPE  *str;			// String
	CHAR_TYPE  strbuf[128];		// Constructed string
	int	  len;					// Length of string
	int	  nLeadingZeros;		// Number of leading zeros required
	int	  nPad;					// Number of pad characters required
	CHAR_TYPE  *sPrefix;		// Prefix string
	ULONG val;					// Value of current number
	bool  bLeftJustify;			// Justification
	bool  bPlusSign;			// Show plus sign?
	bool  bBlankSign;			// Blank for positives?
	bool  bZeroPrefix;			// Want 0x for hex, 0 for octal?
	bool  bIsShort;				// true if short
	bool  bIsLong;				// true if long
	CHAR_TYPE  cPad;
	CHAR_TYPE* savestr;
	bool  bIsLonglong;			// true if LONGLONG
	LONGLONG val64;
	va_list Next;
	Next = (va_list)ParamList;
	Length=0;
	nFlags=0;
	static CHAR_TYPE strPlus[]={'+',0};
	static CHAR_TYPE strSub[]={'-',0};
	static CHAR_TYPE str0x[]={'0','x',0};
	static CHAR_TYPE str0X[]={'0','X',0};
	static CHAR_TYPE strNULL[]={0};
	static CHAR_TYPE strSpace[]={' ',0};
	static CHAR_TYPE strZero[]={'0',0};
	static CHAR_TYPE strError[]={'<','E','r','r','o','r','>',0};

	while(*format != '\0')
	{
		// Everything but '%' is copied to buffer
		if (*format != '%') 
		{
			if(buffer)
				*buffer++ = *format;
			Length++;
			format++;
		}
		else// '%' gets special handling here
		{
			// Set default flags, etc
			Width = 0;
			Precision = -1;
			bLeftJustify = false;
			bPlusSign = false;
			bBlankSign = false;
			bZeroPrefix = false;
			bIsShort = false;
			bIsLong = false;
			bIsLonglong = false;
			nFlags = 0;
			cPad = ' ';
			sPrefix = strNULL;
			format++;
			bMore = true;


			while (bMore) {
				// optional flags
				switch (*format) {
		case '-':  bLeftJustify = true; format++;nFlags|=TVSP_LEFT; break;
		case '+':  bPlusSign = true; format++; nFlags|=TVSP_PLUS;break;
		case '0':  cPad = '0'; format++; nFlags|=TVSP_ZEROPAD;break;
		case ' ':  bBlankSign = true; format++; nFlags|=TVSP_SPACE;break;
		case '#':  bZeroPrefix = true; format++; nFlags|=TVSP_SPECIAL;break;
		default:   bMore = false;
				}
			}
			// optional width		
			if (*format == '*') {
				Width = (int) va_arg(Next, int);
				format++;
				if ( Width < 0 )
				{
					Width = - Width;
					bLeftJustify = true;
					nFlags|=TVSP_LEFT;
				}
			}
			else if (IS_DIGIT(*format)) {
				while (IS_DIGIT(*format)) {
					Width *= 10;
					Width += (*format++) - '0';
				}
			}
			// optional precision		
			if (*format == '.') {
				format++;
				Precision = 0;
				if (*format == '*') {
					Precision = (int) va_arg(Next, int);
					format++;
				}
				else while (IS_DIGIT(*format)) {
					Precision *= 10;
					Precision += (*format++) - '0';
				}
				if ( Precision < 0 ) Precision = 0;
			}
			// optional size'o'



			switch (*format) 
			{
			case 'h':  bIsShort = true; format++; break;
			case 'l':  bIsLong = true;  format++; break;
			case 'I':
				if ( (format[1]=='6') && (format[2]=='4') )
				{
					format += 3;
					bIsLonglong = true;
				}
				break;
			}
			// All controls are completed, dispatch on the conversion character
			switch (*format++) {
		case 'd':
		case 'i':
			 nFlags |= TVSP_SIGN;
			if (bIsLonglong)
				NumToStr( (LONGLONG) va_arg (Next, LONGLONG), strbuf, 10);
			else
				if (bIsLong)		// Signed long int
					NumToStr( (long) va_arg(Next, long), strbuf, 10);
				else			// Signed int
					NumToStr( (int) va_arg(Next, int), strbuf, 10);
			if (strbuf[0] == '-') sPrefix = strSub;
			else {
				if (bPlusSign) sPrefix = strPlus;
				else if (bBlankSign) sPrefix = strSpace;
			}
			goto EmitNumber;
		case 'u':
			if (bIsLonglong)
				uNumToStr( (LONGLONG) va_arg(Next, ULONGLONG), strbuf, 10);
			else
				if (bIsLong)	// Unsigned long int
					uNumToStr( (ULONG) va_arg(Next, ULONG), strbuf, 10);
				else			// Unsigned int
					uNumToStr( (ULONG) (int) va_arg(Next, int), strbuf, 10);
			goto EmitNumber;
			// set sPrefix for these...
		case 'o':
			if (bIsLonglong)
				uNumToStr( (LONGLONG) va_arg(Next, LONGLONG), strbuf, 10);
			else
			{
				if (bZeroPrefix) sPrefix = strZero;
				if (bIsLong)
					val = (long) va_arg(Next, long);
				else
					val = (int) va_arg(Next, int);
				uNumToStr(val, strbuf, 8);
				if (val == 0) sPrefix = strNULL;
			}
			goto EmitNumber;
		case 'p':	// pointer 
		case 'x':
			if (bZeroPrefix) sPrefix = str0x;
			if (bIsLonglong)
			{
				val64 = (LONGLONG) va_arg(Next, LONGLONG);
				uNumToStr( val64, strbuf, 16);
				if (val64 == 0) sPrefix = strNULL;
			}
			else
			{
				if (bIsLong)
					val = (ULONG) va_arg(Next, long);
				else
					val = (unsigned int) va_arg(Next, int);			
				uNumToStr(val, strbuf, 16);
				if (val == 0) sPrefix = strNULL;
			}
			TStrLwr(strbuf);
			goto EmitNumber;
		case 'X':
			if (bZeroPrefix) sPrefix = str0X;
			if (bIsLonglong)
			{
				val64 = (LONGLONG) va_arg(Next, LONGLONG);
				uNumToStr( val64, strbuf, 16);
				if (val64 == 0) sPrefix = strNULL;
			}
			else
			{
				if (bIsLong)
					val = (ULONG) va_arg(Next, long);
				else
					val = (unsigned int) va_arg(Next, int);
				uNumToStr(val, strbuf, 16);
				if (val == 0) sPrefix = strNULL;
			}
			TStrUpr(strbuf);
			goto EmitNumber;
		case 'c':
			strbuf[0] = (CHAR_TYPE) va_arg(Next, int);
			str = strbuf;
			len = 1;
			goto EmitString;
		case 's':
			str = (CHAR_TYPE *) va_arg(Next, CHAR_TYPE*);
			len =  TStrLen(str);
			if (Precision != -1 &&
				Precision < len)
				len = Precision;
			goto EmitString;
		case 'n':
			break;
		case '%':
			strbuf[0] = '%';
			str = strbuf;
			len = 1;
			goto EmitString;
			break;
		case 'f':
		case 'e':
		case 'E':
		case 'g':
		case 'G':
//		case 'U':
			str = myflt( (CHAR_TYPE*)&strbuf[0], va_arg( Next, double ), Width, Precision, *(format-1), nFlags | TVSP_SIGN );
			*str='\0';
			str=strbuf;
			len =  TStrLen(str);
			goto EmitNumber;
		default:
			str = strError;//"<bad format character>";
			len =  TStrLen(str);
			goto EmitString;
			}
EmitNumber:
			if (Precision == -1) Precision = 1;
			str = strbuf;
			if (*str == '-') str++;		// if negative, already have prefix
			len =  TStrLen(str);
			nLeadingZeros = Precision - len;
			if (nLeadingZeros < 0) nLeadingZeros = 0;
			nPad = Width - (len + nLeadingZeros +  TStrLen(sPrefix));
			if (nPad < 0) nPad = 0;
			// If 0-padding, emit prefix first.
			// if ' ' padding, emit padding first
			if (cPad == '0') {
				while (*sPrefix != '\0') PUTONE(*sPrefix++);
			}
			if (nPad && !bLeftJustify) {
				// Left padding required
				while (nPad--) {
					PUTONE(cPad);
				}
				nPad = 0;		// Indicate padding completed
			}
			// Put prefix now if not used up earlier (i.e. if blank padding)
			while (*sPrefix != '\0') PUTONE(*sPrefix++);
			while (nLeadingZeros-- > 0) PUTONE('0');
			while (len-- > 0) {
				PUTONE(*str++);
			}
			if (nPad) {
				// Right padding required
				while (nPad--) PUTONE(' ');
			}
			goto Done;
EmitString:
			// Here we have the string ready to emit.  Handle padding, etc.
			if (Width > len) nPad = Width - len;
			else nPad = 0;
			if (nPad && !bLeftJustify) {
				// Left padding required
				while (nPad--) PUTONE(cPad);
			}
			savestr = str;
			while (len-- > 0) PUTONE(*str++);
			if (nPad && bLeftJustify) {
				// Right padding required
				while (nPad--) PUTONE(' ');
			}
Done:	;
		}
	}
	if(buffer)
		*buffer = '\0';
	return Length;		// Don't count terminating NULL
}

template<class CHAR_TYPE>
int TSPrintf(CHAR_TYPE*buffer,const CHAR_TYPE*format,...)
{
	int Result;
	va_list Next;
	va_start(Next,format);
	Result = TVSPrintf(buffer,format,Next);
	va_end(Next);
	return Result;
}

template<class CHAR_TYPE,bool bIgnoreCase = false,int Align = 8>
class TString
{
public://当m_pData!=NULL && m_MaxLength==0时TString是个常量字符串
	CHAR_TYPE*m_pData;
	int m_Length;
	int m_MaxLength;
public:
	void Init()
	{
		m_pData	= NULL;
		m_MaxLength	= m_Length = 0;
	}
	TString()
	{
		Init();
	}
	TString(const CHAR_TYPE* pString)
	{
		Init();
		m_pData = (CHAR_TYPE*)pString;
		m_Length = TStrLen(m_pData);
	}
	TString(const TString&String)
	{
		Init();
		if(String.m_Length)
			Preallocate(String.m_Length+1,String.m_pData);
	}
	virtual ~TString()
	{
		if(m_pData)
		{
			if(m_MaxLength)
				delete m_pData;
			m_pData = NULL;
		}
		m_MaxLength = m_Length = 0;
	}
	// Length包含结束符，是真实空间大小。
	virtual void Preallocate(int Length, const CHAR_TYPE* pNewString = NULL)
	{
		CHAR_TYPE* pNewData = m_pData;
		int OldMaxLength = m_MaxLength;
		if(Length>m_MaxLength)
		{
			m_MaxLength = Length+(Align-Length%Align);
			pNewData = new CHAR_TYPE[m_MaxLength];
			*pNewData = 0;
		}
		if(pNewString && pNewString!=pNewData)
		{
			m_Length = TStrLen(pNewString);
			TStrCpyLimit(pNewData, pNewString, m_MaxLength);
		}
		if(m_pData && pNewData!=m_pData)
		{
			if(OldMaxLength)
				delete m_pData;
			m_pData = NULL;
		}
		m_pData = pNewData;
	}
	int GetLength()	const { return m_Length; }
	int Length() const { return m_Length; }
	virtual void Empty()
	{
		if(m_pData)
		{
			if(m_MaxLength)
				delete m_pData;
			m_pData = NULL;
		}
		m_MaxLength = m_Length = 0;
	}
	bool IsEmpty() const
	{
		return (m_pData==NULL)||(m_Length==0)||(m_pData[0]==0);
	}
	int Compare(const TString String) const
	{
		if(m_pData == NULL || String.m_pData)
			return -1;
		return TStrCmp(m_pData, String.m_pData);
	}
	int CompareNoCase(const TString String) const
	{
		if(m_pData == NULL || String.m_pData)
			return -1;
		return TStrICmp(m_pData, String.m_pData);
	}
	CHAR_TYPE GetAt(int nIndex) const
	{
		if(nIndex<m_MaxLength)
			return m_pData[nIndex];
		else
			return 0;
	}
	CHAR_TYPE SetAt(int nIndex, CHAR_TYPE ch)
	{
		if(m_pData==NULL)
			Preallocate(nIndex+1);
		m_pData[nIndex] = ch;
		if(ch==0)
			m_Length = TStrLen(m_pData);
		return ch;
	}
	void Truncate(int nIndex)
	{
		SetAt(nIndex, '\0');
	}
	void ReverseCpy(CHAR_TYPE*dst,const CHAR_TYPE*src,int count)
	{
		dst += count;
		src += count;
		while(count--)
		{
			dst--;
			src--;
			*dst = *src;
		}
	}
	int Insert(int nIndex, CHAR_TYPE* pszString)
	{
		if(m_pData==NULL)
			Preallocate(nIndex+1);
		int nNewLen = TStrLen(pszString);
		if( nNewLen+m_Length >= m_MaxLength )
		{
			Preallocate(nNewLen+m_Length+1,m_pData);
		}
		ReverseCpy(m_pData+nIndex+nNewLen, m_pData+nIndex, m_Length-nIndex);
		ReverseCpy(m_pData+nIndex, pszString, nNewLen);
		m_Length+=nNewLen;
		*(m_pData+m_Length) = 0;
		return m_Length;
	}
	int Insert(int nIndex, CHAR_TYPE ch)
	{
		if(m_pData==NULL)
			Preallocate(nIndex+1);
		if( m_Length+1 >= m_MaxLength )
		{
			Preallocate(m_Length+1+1,m_pData);
		}
		ReverseCpy(m_pData+nIndex+1, m_pData+nIndex, m_Length-nIndex);
		*(m_pData+nIndex) = ch;
		m_Length++;
		*(m_pData+m_Length) = 0;
		return m_Length;
	}
	int Delete(	int nIndex,	int nCount = 1)
	{
		if(nIndex<0 || nIndex>=m_Length)
			return m_Length;
		if(nIndex+nCount>m_Length)
			nCount = m_Length-nIndex;
		TMemCpy(m_pData+nIndex, m_pData+nIndex+nCount, m_Length-(nIndex+nCount));
		m_Length -= nCount;
		m_pData[m_Length] = 0;
		return m_Length;
	}
	TString& operator=(const CHAR_TYPE* pString)
	{
		if(pString)
			Preallocate(TStrLen(pString)+1, pString);
		else
			Empty();
		return *this;
	}

	TString& operator=(const TString& String)
	{
		if(String.m_Length)
			Preallocate(String.m_Length+1, String.m_pData);
		else
			Empty();
		return *this;
	}

	TString& operator+=(const CHAR_TYPE* pString)
	{
		int nNewLen = TStrLen(pString);
		Preallocate(nNewLen+m_Length+1,m_pData);
		TStrCat(m_pData, pString);
		m_Length += nNewLen;
		return *this;
	}
	TString& operator+=(const TString& String)
	{
		Preallocate(String.m_Length+m_Length+1,m_pData);
		TStrCat(m_pData, String.m_pData);
		m_Length += String.m_Length;
		return *this;
	}
	TString&operator+=(CHAR_TYPE Char)
	{
		Preallocate(m_Length+2,m_pData);
		m_pData[m_Length]=Char;
		m_Length++;
		m_pData[m_Length]=0;
		return *this;
	}
	TString& Fill(CHAR_TYPE Char,int Count)
	{
		Preallocate(Count+1);
		for(int i =0; i < Count; i++)
		{	
			m_pData[i]=Char;
			m_Length++;	
		}
		m_pData[m_Length]=0;
		return *this;
	}
	TString& Append(CHAR_TYPE Char,int Count)
	{
		Preallocate(m_Length+Count+1,m_pData);
		for(int i =0; i < Count; i++)
		{
			m_pData[m_Length]=Char;
			m_Length++;	
		}
		m_pData[m_Length]=0;
		return *this;
	}
	operator CHAR_TYPE*()
	{
		static CHAR_TYPE NullChar;
		NullChar = 0;
		if(m_pData==NULL)
			return &NullChar;
		return m_pData;
	}
	TString operator+(const TString& String)
	{
		TString NewString;
		NewString = *this;
		NewString += String;
		return NewString;
	}
	TString operator+(const CHAR_TYPE* pString)
	{
		TString NewString;
		NewString = *this;
		NewString += pString;
		return NewString;
	}
	CHAR_TYPE& operator[](int n)
	{
		return m_pData[n];
	}
	bool operator==(const TString&StrObj) const	{	return (bIgnoreCase?!TStrICmp(m_pData,StrObj.m_pData):!TStrCmp(m_pData,StrObj.m_pData));}
	bool operator!=(const TString&StrObj) const	{	return (bIgnoreCase?TStrICmp(m_pData,StrObj.m_pData):TStrCmp(m_pData,StrObj.m_pData))!=0;}
	bool operator<(const TString&StrObj) const	{	return (bIgnoreCase?TStrICmp(m_pData,StrObj.m_pData):TStrCmp(m_pData,StrObj.m_pData))<0;}
	bool operator>(const TString&StrObj) const	{	return (bIgnoreCase?TStrICmp(m_pData,StrObj.m_pData):TStrCmp(m_pData,StrObj.m_pData))>0;}
	bool operator<=(const TString&StrObj) const	{	return (bIgnoreCase?TStrICmp(m_pData,StrObj.m_pData):TStrCmp(m_pData,StrObj.m_pData))<=0;}
	bool operator>=(const TString&StrObj) const	{	return (bIgnoreCase?TStrICmp(m_pData,StrObj.m_pData):TStrCmp(m_pData,StrObj.m_pData))>=0;}
	bool operator==(const CHAR_TYPE*pStr) const	{	return (bIgnoreCase?!TStrICmp(m_pData,pStr):!TStrCmp(m_pData,pStr));}
	bool operator!=(const CHAR_TYPE*pStr) const	{	return (bIgnoreCase?TStrICmp(m_pData,pStr):TStrCmp(m_pData,pStr))!=0;}
	bool operator<(const CHAR_TYPE*pStr) const	{	return (bIgnoreCase?TStrICmp(m_pData,pStr):TStrCmp(m_pData,pStr))<0;}
	bool operator>(const CHAR_TYPE*pStr) const	{	return (bIgnoreCase?TStrICmp(m_pData,pStr):TStrCmp(m_pData,pStr))>0;}
	bool operator<=(const CHAR_TYPE*pStr) const	{	return (bIgnoreCase?TStrICmp(m_pData,pStr):TStrCmp(m_pData,pStr))<=0;}
	bool operator>=(const CHAR_TYPE*pStr) const	{	return (bIgnoreCase?TStrICmp(m_pData,pStr):TStrCmp(m_pData,pStr))>=0;}
	void FormatV(const CHAR_TYPE* pFormat, va_list va)
	{
		int nLen = TVSPrintf((CHAR_TYPE*)NULL, pFormat, va);
		Preallocate(nLen+1);
		TVSPrintf(m_pData, pFormat, va);
		m_Length = nLen;
	}
	void Format(const CHAR_TYPE* pFormat,	...)
	{
		va_list va;
		va_start(va, pFormat);
		FormatV(pFormat, va);
		va_end(va);
	}
	TString& MakeUpper()
	{
		if(m_pData)
			TStrUpr(m_pData);
		return *this;
	}

	TString& MakeLower()
	{
		if(m_pData)
			TStrLwr(m_pData);
		return *this;
	}
	///////////////////////////////////////
	//路径操作
	//////////////////////////////////////
	//取文件名
	//"C:\Windows\Notepad.exe"
	//"Notepad.exe"
	CHAR_TYPE*GetFileName()
	{
		return TGetFileName(m_pData);
	}
	//取文件扩展名
	//"C:\Windows\Notepad.exe"
	//"exe"
	CHAR_TYPE*GetFileExt()
	{
		return TGetFileExt(m_pData);
	}
	//取主文件名
	//"C:\Windows\Notepad.exe"
	//"Notepad"
	int GetFileTitle(CHAR_TYPE*szTitle)
	{
		return TGetFileTitle(m_pData,szTitle);
	}
	//取文件路径名
	//"C:\Windows\Notepad.exe"
	//C:\Windows
	int GetFilePath(CHAR_TYPE*szPath)
	{
		return TGetFilePath(m_pData,szPath);
	}
	int	Save(ALTFileStream&Stream)
	{
		int Length = Stream.Puts(&m_Length,sizeof(m_Length));
		if(m_Length>0)
			Length += Stream.Puts(m_pData,m_Length*sizeof(CHAR_TYPE));
		return Length;
	}
	int	Load(ALTFileStream&Stream)
	{
		int TotalLength,Length;
		TotalLength = 0;
		Length = Stream.Gets(&m_Length,sizeof(m_Length));
		if(Length!=sizeof(m_Length))
			return 0;
		TotalLength+=Length;
		if(m_Length==0)
			return TotalLength;
		Preallocate(m_Length+1);
		Length = Stream.Gets(m_pData,m_Length*sizeof(CHAR_TYPE));
		if(Length!=m_Length*sizeof(CHAR_TYPE))
			return 0;
		TotalLength+=Length;
		m_pData[m_Length]=0;
		return TotalLength;
	}
};

typedef TString<char>	CStrA;
typedef TString<WCHAR>	CStrW;

typedef TString<char,true>	CIStrA;
typedef TString<WCHAR,true>	CIStrW;

ALT_NAME_SPACE_END

#endif
