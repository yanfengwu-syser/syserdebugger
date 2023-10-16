///////////////////////////////////////////////////////
//base define
//coded by Finaldoom
///////////////////////////////////////////////////////
#ifndef _DEFINE_H_
#define _DEFINE_H_

#ifndef	CODE_OS_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#ifdef	WIN32
#ifndef CODE_OS_NT_DRV
#define CODE_OS_WIN
#include <windows.h>
#endif
#else	//WIN32
#ifndef CODE_OS_CATOS
#define CODE_OS_UNIX
#endif
#endif

#endif

#ifndef CODE_INT_BYTES
#define CODE_INT_BYTES	4
#endif

///////////////////////////////////////////////////////
//Debug相关宏<Start>
///////////////////////////////////////////////////////
#ifdef	CODE_OS_WIN

#define	CODE_WARNING(__str)			MessageBox(NULL,__str,"代码异常",MB_OK|MB_ICONWARNING)
#if		_MSC_VER >=1400 
#define	CODE_ASSERT(_b)				{if(!(_b)){char Str[256];sprintf_s(Str,sizeof(Str),"源文件：%s\n代码行：%d",__FILE__,__LINE__);MessageBox(NULL,Str,"代码异常",MB_OK|MB_ICONWARNING);KdBreakPoint();}}
#else
#define	CODE_ASSERT(_b)				{if(!(_b)){char Str[256];sprintf(Str,"源文件：%s\n代码行：%d",__FILE__,__LINE__);MessageBox(NULL,Str,"代码异常",MB_OK|MB_ICONWARNING);KdBreakPoint();}}
#endif
#define CODE_DEBUG_OUTPUT			CodeDebugPrintf

#endif	//CODE_OS

#ifdef	CODE_OS_NT_DRV

#define	CODE_WARNING(__str)			{DbgPrint(__str);KdBreakPoint();}
#define	CODE_ASSERT(_b)				{if(!(_b)){::DbgPrint("代码异常\n源文件：%s\n代码行：%d\n",__FILE__,__LINE__);KdBreakPoint();}}
#define CODE_DEBUG_OUTPUT			::DbgPrint

#endif	//CODE_OS_NT_DRV

#ifdef	CODE_OS_UNIX

#define	CODE_WARNING(__str)			{printf(__str);getch();}
#define	CODE_ASSERT(_b)				{if(!(_b))printf("代码异常\n源文件：%s\n代码行：%d\n",__FILE__,__LINE__);}
#define CODE_DEBUG_OUTPUT			printf

#endif	//CODE_OS_UNIX


#ifdef _DEBUG

#define NOP_OPTR			do{}while(0)

#else

#undef	CODE_WARNING
#define	CODE_WARNING(_str)	do{}while(0)

#undef	CODE_ASSERT
#define	CODE_ASSERT(_b)

#endif
/////////////////////////////////////////////////////////////////////////////
//Debug相关宏<End>
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//常用常量<Start>
/////////////////////////////////////////////////////////////////////////////
#ifndef NULL
#define NULL				0
#endif

#ifndef TRUE
#define TRUE				1
#endif

#ifndef FALSE
#define FALSE				0
#endif

#define ERROR_USCODE		-1
#define PI					3.141592653549
#define MAX_FN_LEN			260
#define MAX_SHORT_NAME_LEN	32
#define MAX_NAME_LEN		64
#define MAX_LONG_NAME_LEN	128

#ifndef MAX_PATH
#define MAX_PATH            260
#endif

#define MAX_BYTE			0xFF
#define MAX_WORD			0xFFFF
#define MAX_DWORD			0xFFFFFFFF

#define IN
#define OUT
#define INOUT
#define OPTIONAL

#ifdef	CODE_OS_UNIX
#define PATH_SEPARATOR_CHAR     '/'
#define PATH_SEPARATOR_STR      "/"
#define PATH_SEPARATOR_WCHAR    L'/'
#define PATH_SEPARATOR_WSTR     L"/"
#else
#define PATH_SEPARATOR_CHAR     '\\'
#define PATH_SEPARATOR_STR      "\\"
#define PATH_SEPARATOR_WCHAR    L'\\'
#define PATH_SEPARATOR_WSTR     L"\\"
#endif

#define WSTR(s)					(L##s)
/////////////////////////////////////////////////////////////////////////////
//常用常量<End>
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//常用函数类型<Start>
/////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER

#ifndef FASTCALL
#define FASTCALL			__fastcall
#endif

#endif

#ifndef FASTCALL
#define FASTCALL
#endif

#ifndef PASCAL
#define PASCAL				__stdcall
#endif

#ifndef INLINE
#define INLINE				inline
#endif

/////////////////////////////////////////////////////////////////////////////
//常用函数类型<End>
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//编译选项宏<Start>
/////////////////////////////////////////////////////////////////////////////
#ifdef	CODE_ST_PACK
#define ST_PACK_ONE_BYTE		__attribute__((packed))
#else
#define ST_PACK_ONE_BYTE
#endif

/////////////////////////////////////////////////////////////////////////////
//编译选项宏<End>
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//常用数据类型<Start>
/////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER

typedef __int64				LONGLONG;
typedef unsigned __int64	ULONGLONG;
typedef unsigned __int64	NUM_PTR;

#ifndef _WCHAR_T_DEFINED
typedef unsigned short		wchar_t;
#define _WCHAR_T_DEFINED
#endif

#else //_MSC_VER

typedef long long			LONGLONG;
typedef unsigned long long	ULONGLONG;
typedef unsigned long long	NUM_PTR;

#endif //_MSC_VER

typedef ULONGLONG			QWORD;
typedef unsigned long		DWORD;
typedef unsigned short		WORD;
typedef unsigned char		BYTE;

typedef long				LONG;
typedef int					INT;
typedef short				SHORT;
typedef char				CHAR;
typedef unsigned long		ULONG;
typedef unsigned int		UINT;
typedef unsigned short		USHORT;
typedef unsigned char		UCHAR;
typedef int					BOOL;

typedef wchar_t				WCHAR;
typedef DWORD				DCHAR;
typedef DWORD*				PDWORD;
typedef WORD*				PWORD;
typedef BYTE*				PBYTE;
typedef INT*				PINT;
typedef UINT*				PUINT;
typedef LONG*				PLONG;
typedef ULONG*				PULONG;
typedef DWORD*				LPDWORD;
typedef WORD*				LPWORD;
typedef BYTE*				LPBYTE;
typedef INT*				LPINT;
typedef UINT*				LPUINT;
typedef LONG*				LPLONG;
typedef ULONG*				LPULONG;

#define VOID				void

typedef void*				PVOID;
typedef void*				LPVOID;
typedef const void*			PCVOID;
typedef const void*			LPCVOID;

typedef void*				HANDLE;
typedef CHAR*				PCHAR;
typedef CHAR*				PSTR;
typedef const char*			PCSTR;
typedef CHAR*				LPSTR;
typedef const char*			LPCSTR;

typedef WCHAR*				PWSTR;
typedef const WCHAR*		PCWSTR;
typedef PWSTR				LPWSTR;
typedef PCWSTR				LPCWSTR;

typedef DCHAR*				PDSTR;
typedef const DCHAR*		PCDSTR;
typedef PDSTR				LPDSTR;
typedef PCDSTR				LPCDSTR;

typedef DWORD				COLORREF;

#if		CODE_INT_BYTES <=	4
typedef unsigned long		ULSIZE;
typedef unsigned long		ULPOS;
typedef long				LPOS;
#else
typedef ULONGLONG			ULSIZE;
typedef ULONGLONG			ULPOS;
typedef LONGLONG			LPOS;
#endif

typedef ULONGLONG			ULLSIZE;
typedef ULONGLONG			ULLPOS;
typedef LONGLONG			LLPOS;

/////////////////////////////////////////////////////////////////////////////
//常用数据类型<End>
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//常用函数原型类型<Start>
/////////////////////////////////////////////////////////////////////////////

typedef void (*PVFV)(void);
typedef void (*PVFI)(int);
typedef int (*PIFV)(void);
typedef int (*PIFI)(int);

/////////////////////////////////////////////////////////////////////////////
//常用函数原型类型<End>
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//可变参数函数宏<Start>
/////////////////////////////////////////////////////////////////////////////
#ifdef  __cplusplus
#define ADDRESS_OF(v)			( &reinterpret_cast<const char &>(v) )
#else
#define ADDRESS_OF(v)			( &(v) )
#endif
#define INT_SIZE_OF(n)			( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#ifdef	CODE_VA_DEFINE

typedef char*					va_list;
#define va_start(ap,v)			( ap = (va_list)ADDRESS_OF(v) + INT_SIZE_OF(v) )
#define va_arg(ap,at)			( *(at*)((ap +=	INT_SIZE_OF(at)) - INT_SIZE_OF(at)) )
#define va_end(ap)				( ap = (va_list)0 )

#endif
/////////////////////////////////////////////////////////////////////////////
//可变参数函数宏<End>
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//常用取值宏<Start>
/////////////////////////////////////////////////////////////////////////////

#define MAKE_WORD(HB,LB)			((WORD)(  (WORD)(LB) | ((WORD)(HB)<<8)   )) 
#define MAKE_DWORD(HW,LW)			((DWORD)(  (DWORD)(LW) | ((DWORD)(HW)<<16)  ))
#define MAKE_QDWORD(HD,LD)			((ULONGLONG)( (ULONGLONG)(LD) | ((ULONGLONG)(HD)<<32) ))

#define GET_BIT(Ptr,BitOff)			((RT_BYTE(Ptr,((BitOff)>>3)) >>((BitOff)&7)) & 1)
#define SET_BIT(Ptr,BitOff)			RT_BYTE(Ptr,((BitOff)>>3))|=1<<((BitOff)&7)
#define CLR_BIT(Ptr,BitOff)			RT_BYTE(Ptr,((BitOff)>>3))&=~(1<<((BitOff)&7))

#define PTR_TO_NUM(Ptr)				((unsigned int)(NUM_PTR)(Ptr))
#define NUM_TO_PTR(Num)				((void*)(NUM_PTR)(Num))

#define PTR_DELTA(__Ptr1,__Ptr2)	((UINT)(__Ptr2-__Ptr1))

#define LOW_BYTE(w)					((BYTE)(w))
#define HIGH_BYTE(w)				((BYTE)((WORD)(w)>>8))

#define LOW_WORD(l)					((WORD)(l))
#define HIGH_WORD(l)				((WORD)((DWORD)(l)>>16))

#define LOW_DWORD(l)				((DWORD)(l))
#define HIGH_DWORD(l)				((DWORD)((QWORD)(l)>>32))

//返回指针指向的数据

#define RT_PVOID(ptr,off)			((void*)( (BYTE*)(ptr) + (off) ))
#define RT_LPVOID(ptr,off)			((void*)( (BYTE*)(ptr) + (off) ))
#define RT_PDWORD(ptr,off)			((DWORD*)( (BYTE*)(ptr) + (off) ))
#define RT_PWORD(ptr,off)			((WORD *)( (BYTE*)(ptr) + (off) ))
#define RT_PBYTE(ptr,off)			((BYTE *)( (BYTE*)(ptr) + (off) ))
#define RT_PCHAR(ptr,off)			((CHAR *)( (BYTE*)(ptr) + (off) ))

#define _RT_PDWORD(ptr)				((DWORD*)(ptr) )
#define _RT_PWORD(ptr)				((WORD *)(ptr) )
#define _RT_PBYTE(ptr)				((BYTE *)(ptr) )
#define _RT_PCHAR(ptr)				((CHAR *)(ptr) )
#define _RT_PVOID(ptr)				((void *)(ptr) )

#define GET_CHAR(ptr,off)			(*(CHAR *)( (BYTE*)(ptr) + (off) ) )
#define _GET_CHAR(ptr)				(*(CHAR *)(ptr) )
#define _GET_CCHAR(ptr)				(*(const CHAR *)(ptr) )

#define PUT_CHAR(ptr,off,val)		do{(*(CHAR *)( (BYTE*)(ptr) + (off) ) ) = val;}while(0)
#define _PUT_CHAR(ptr,val)			do{(*(CHAR *)(ptr) ) = val;}while(0)

#define GET_BYTE(ptr,off)			(*(BYTE *)( (BYTE*)(ptr) + (off) ) )
#define _GET_BYTE(ptr)				(*(BYTE *)(ptr) )

#define PUT_BYTE(ptr,off,val)		do{(*(BYTE *)( (BYTE*)(ptr) + (off) ) ) = val;}while(0)
#define _PUT_BYTE(ptr,val)			do{(*(BYTE *)(ptr) ) = val;}while(0)

#ifdef CODE_BIG_ENDIAN

#define BIG_ENDIAN_DWORD(x)			(x = _GET_DWORD(&(x)))
#define BIG_ENDIAN_WORD(x)			(x = _GET_WORD(&(x)))

//大字节序
#define GET_WORD(ptr,off)			(*RT_PBYTE(ptr,off)+(*RT_PBYTE(ptr,(off)+1)<<8))
#define _GET_WORD(ptr)				(*_RT_PBYTE(ptr)+(*RT_PBYTE(ptr,1)<<8))

#define PUT_WORD(ptr,off,val)		do{PUT_BYTE(ptr,off,LOW_BYTE(val));PUT_BYTE(ptr,(off)+1,HIGH_BYTE(val));}while(0)
#define _PUT_WORD(ptr,val)			PUT_WORD(ptr,0,val)
#define GET_3BYTES(ptr,off)			(*RT_PBYTE(ptr,off)+(*RT_PBYTE(ptr,(off)+1)<<8)+(*RT_PBYTE(ptr,(off)+2)<<16))
#define _GET_3BYTES(ptr)			(*_RT_PBYTE(ptr)+(*RT_PBYTE(ptr,1)<<8)+(*RT_PBYTE(ptr,2)<<16))
#define PUT_3BYTES(ptr,off,val)		do{PUT_WORD(ptr,(off)+1,(WORD)((val)>>8));PUT_BYTE(ptr,off,LOW_BYTE(val));}while(0)
#define _PUT_3BYTES(ptr,val)		PUT_3BYTES(ptr,0,val)
#define GET_DWORD(ptr,off)			(*RT_PBYTE(ptr,off)+(*RT_PBYTE(ptr,(off)+1)<<8)+(*RT_PBYTE(ptr,(off)+2)<<16)+(*RT_PBYTE(ptr,(off)+3)<<24))
#define _GET_DWORD(ptr)				(*_RT_PBYTE(ptr)+(*RT_PBYTE(ptr,1)<<8)+(*RT_PBYTE(ptr,2)<<16)+(*RT_PBYTE(ptr,3)<<24))
#define PUT_DWORD(ptr,off,val)		do{PUT_WORD(ptr,off,LOW_WORD(val));PUT_WORD(ptr,(off)+2,HIGH_WORD(val));}while(0)
#define _PUT_DWORD(ptr,val)			PUT_DWORD(ptr,0,val)

#else//CODE_BIG_ENDIAN
//小字节序
#define GET_WORD(ptr,off)			(*(WORD*)( (BYTE*)(ptr) + (off) ) )
#define _GET_WORD(ptr)				(*(WORD*)( (BYTE*)(ptr)) )
#define PUT_WORD(ptr,off,val)		do{(*(WORD*)( (BYTE*)(ptr) + (off) ) )=val;}while(0)
#define _PUT_WORD(ptr,val)			do{(*(WORD*)( (BYTE*)(ptr)) )=val;}while(0)

#define GET_3BYTES(ptr,off)			MAKE_DWORD((BYTE)GET_WORD(ptr,(off)+2),GET_BYTE(ptr,off))
#define _GET_3BYTES(ptr)			MAKE_DWORD((BYTE)GET_WORD(ptr,2),_GET_BYTE(ptr))

#define PUT_3BYTES(ptr,off,val)		do{PUT_WORD(ptr,off,LOW_WORD(val));PUT_BYTE(ptr,(off)+2,(BYTE)HIGH_WORD(val));}while(0)
#define _PUT_3BYTES(ptr,val)		PUT_3BYTES(ptr,0,val)

#define GET_DWORD(ptr,off)			(*(DWORD*)( (BYTE*)(ptr) + (off) ) )
#define _GET_DWORD(ptr)				(*(DWORD*)( (BYTE*)(ptr) ) )

#define PUT_DWORD(ptr,off,val)		do{(*(DWORD*)( (BYTE*)(ptr) + (off) ) )=(DWORD)(val);}while(0)
#define _PUT_DWORD(ptr,val)			do{(*(DWORD*)( (BYTE*)(ptr) ) )=(DWORD)(val);}while(0)

#define BIG_ENDIAN_DWORD
#define BIG_ENDIAN_WORD

#endif//CODE_BIG_ENDIAN

/////////////////////////////////////////////////////////////////////////////
//常用指针宏<End>
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//其它宏<Start>
/////////////////////////////////////////////////////////////////////////////

#ifndef ABS
#define ABS(a)								((a)>=0?(a):-(a))
#endif

#ifndef MIN
#define MIN(a,b)							((a)>(b)?(b):(a))
#endif

#ifndef MAX
#define MAX(a,b)							((a)>(b)?(a):(b))
#endif

#ifndef IS_DIGIT
#define IS_DIGIT(c)							((c)>='0'&&(c)<='9')
#endif

#ifndef IS_HEX_LETTER
#define IS_HEX_LETTER						( ((c)>='a'&&(c)<='f') || ((c)>='A'&&(c)<='F') )
#endif

#ifndef IS_HEX_DIGIT
#define IS_HEX_DIGIT(c)						(IS_DIGIT(c) || IS_HEX_LETTER(c))
#endif

#ifndef SWAP
#define SWAP(a,b)							{a=a^b;b=a^b;a=a^b;}
#endif

#define PAGE_COUNT(__size,__page)			((__size)/(__page)+((__size)%(__page)?1:0))
#define ALIGN_SIZE(__size,__page)			(PAGE_COUNT((__size),(__page))*(__page))
#define CENTER_ALGN(__size,__total)			(((__total)-(__size))/2)

#ifndef ZeroMemory
#define ZeroMemory(__Buffer,__Size)			memset((__Buffer),0,(__Size))
#endif

#define STZeroMemory(__ST)					ZeroMemory(&__ST,sizeof(__ST))

#ifndef FillMemory
#define FillMemory(__Buffer,__Data,__Size)	memset(__Buffer,__Data,__Size)
#endif

#define SafeDelete(__Ptr)					if(__Ptr){delete __Ptr;__Ptr=NULL;}
#define SafeDeleteAry(__Ptr)				if(__Ptr){delete[] __Ptr;__Ptr=NULL;}
#define SafeRelease(__Ptr)					if(__Ptr){__Ptr->Release();__Ptr=NULL;}

#define ST_FIELD_OFF(__type,__field)		((int)(NUM_PTR)&(((__type*)NULL)->__field))////取结构中的偏移

#define BCDBYTE(__byte)						( (((__byte)/10)<<4) | ((__byte)%10) )

#define MAKE_CHAR_UPPER(__c)				if(__c>='a' && __c <='z')__c +='A'-'a'
#define MAKE_CHAR_LOWER(__c)				if(__c>='A' && __c <='Z')__c +='a'-'A'
#define UPPER_CHAR(__c)						((__c>='a' && __c<='z')?__c+'A'-'a':__c)
#define LOWER_CHAR(__c)						((__c>='A' && __c<='Z')?__c+'a'-'A':__c)

#define MAX_LIMIT(__L,__M)					if((__L)>(__M))__L=__M
#define MIN_LIMIT(__L,__M)					if((__L)<(__M))__L=__M

#define MEMBER_OFFSET(TypeName,MemberName) ((int)(&(((TypeName*)(0))->##MemberName)))
#define MEMBER_OFFSET2(TypeName,MemberName,ReturnTypeName) ((ReturnTypeName)(&(((TypeName*)(0))->##MemberName)))
/////////////////////////////////////////////////////////////////////////////
//其它宏<End>
/////////////////////////////////////////////////////////////////////////////
#endif//_CODE_DEFINE_H_
