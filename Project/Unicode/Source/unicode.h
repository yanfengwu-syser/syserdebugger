/*
 * Wine internal Unicode definitions
 *
 * Copyright 2000 Alexandre Julliard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __WINE_UNICODE_H
#define __WINE_UNICODE_H

#define _UNICODE_VALID_

extern const struct  sbcs_table cptable_037;
extern const struct  sbcs_table cptable_042;
extern const struct  sbcs_table cptable_424;
extern const struct  sbcs_table cptable_437;
extern const struct  sbcs_table cptable_500;
extern const struct  sbcs_table cptable_737;
extern const struct  sbcs_table cptable_775;
extern const struct  sbcs_table cptable_850;
extern const struct  sbcs_table cptable_852;
extern const struct  sbcs_table cptable_855;
extern const struct  sbcs_table cptable_856;
extern const struct  sbcs_table cptable_857;
extern const struct  sbcs_table cptable_860;
extern const struct  sbcs_table cptable_861;
extern const struct  sbcs_table cptable_862;
extern const struct  sbcs_table cptable_863;
extern const struct  sbcs_table cptable_864;
extern const struct  sbcs_table cptable_865;
extern const struct  sbcs_table cptable_866;
extern const struct  sbcs_table cptable_869;
extern const struct  sbcs_table cptable_874;
extern const struct  sbcs_table cptable_875;
extern const struct  sbcs_table cptable_878;
extern const struct  dbcs_table cptable_932;
extern const struct  dbcs_table cptable_936;
extern const struct  dbcs_table cptable_949;
extern const struct  dbcs_table cptable_950;
extern const struct  sbcs_table cptable_1006;
extern const struct  sbcs_table cptable_1026;
extern const struct  sbcs_table cptable_1250;
extern const struct  sbcs_table cptable_1251;
extern const struct  sbcs_table cptable_1252;
extern const struct  sbcs_table cptable_1253;
extern const struct  sbcs_table cptable_1254;
extern const struct  sbcs_table cptable_1255;
extern const struct  sbcs_table cptable_1256;
extern const struct  sbcs_table cptable_1257;
extern const struct  sbcs_table cptable_1258;
extern const struct  sbcs_table cptable_10000;
extern const struct  sbcs_table cptable_10006;
extern const struct  sbcs_table cptable_10007;
extern const struct  sbcs_table cptable_10029;
extern const struct  sbcs_table cptable_10079;
extern const struct  sbcs_table cptable_10081;
extern const struct  sbcs_table cptable_20866;
extern const struct  dbcs_table cptable_20932;
extern const struct  sbcs_table cptable_28591;
extern const struct  sbcs_table cptable_28592;
extern const struct  sbcs_table cptable_28593;
extern const struct  sbcs_table cptable_28594;
extern const struct  sbcs_table cptable_28595;
extern const struct  sbcs_table cptable_28596;
extern const struct  sbcs_table cptable_28597;
extern const struct  sbcs_table cptable_28598;
extern const struct  sbcs_table cptable_28599;
extern const struct  sbcs_table cptable_28600;
extern const struct  sbcs_table cptable_28603;
extern const struct  sbcs_table cptable_28604;
extern const struct  sbcs_table cptable_28605;
extern const struct  sbcs_table cptable_28606;









#undef NULL
#ifdef __cplusplus
#define NULL  0
#else
#define NULL  ((void*)0)
#endif



#define MB_PRECOMPOSED              0x00000001
#define MB_COMPOSITE                0x00000002
#define MB_USEGLYPHCHARS            0x00000004
#define MB_ERR_INVALID_CHARS        0x00000008

#define LCID_INSTALLED              0x00000001

/* flags to GetLocaleInfo */
#define	LOCALE_NOUSEROVERRIDE	    0x80000000
#define	LOCALE_USE_CP_ACP	    0x40000000
#define	LOCALE_RETURN_NUMBER	    0x20000000

/* When adding new defines, don't forget to add an entry to the
 * locale_name2id map in ole/ole2nls.c
 */
#define LOCALE_ILANGUAGE            0x00000001
#define LOCALE_SLANGUAGE            0x00000002
#define LOCALE_SENGLANGUAGE         0x00001001
#define LOCALE_SABBREVLANGNAME      0x00000003
#define LOCALE_SNATIVELANGNAME      0x00000004
#define LOCALE_ICOUNTRY             0x00000005
#define LOCALE_SCOUNTRY             0x00000006
#define LOCALE_SENGCOUNTRY          0x00001002
#define LOCALE_SABBREVCTRYNAME      0x00000007
#define LOCALE_SNATIVECTRYNAME      0x00000008
#define LOCALE_IDEFAULTLANGUAGE     0x00000009
#define LOCALE_IDEFAULTCOUNTRY      0x0000000A
#define LOCALE_IDEFAULTCODEPAGE     0x0000000B
#define LOCALE_IDEFAULTANSICODEPAGE 0x00001004
#define LOCALE_IDEFAULTMACCODEPAGE  0x00001011
#define LOCALE_SLIST                0x0000000C
#define LOCALE_IMEASURE             0x0000000D
#define LOCALE_SDECIMAL             0x0000000E
#define LOCALE_STHOUSAND            0x0000000F
#define LOCALE_SGROUPING            0x00000010
#define LOCALE_IDIGITS              0x00000011
#define LOCALE_ILZERO               0x00000012
#define LOCALE_INEGNUMBER           0x00001010
#define LOCALE_SNATIVEDIGITS        0x00000013
#define LOCALE_SCURRENCY            0x00000014
#define LOCALE_SINTLSYMBOL          0x00000015
#define LOCALE_SMONDECIMALSEP       0x00000016
#define LOCALE_SMONTHOUSANDSEP      0x00000017
#define LOCALE_SMONGROUPING         0x00000018
#define LOCALE_ICURRDIGITS          0x00000019
#define LOCALE_IINTLCURRDIGITS      0x0000001A
#define LOCALE_ICURRENCY            0x0000001B
#define LOCALE_INEGCURR             0x0000001C
#define LOCALE_SDATE                0x0000001D
#define LOCALE_STIME                0x0000001E
#define LOCALE_SSHORTDATE           0x0000001F
#define LOCALE_SLONGDATE            0x00000020
#define LOCALE_STIMEFORMAT          0x00001003
#define LOCALE_IDATE                0x00000021
#define LOCALE_ILDATE               0x00000022
#define LOCALE_ITIME                0x00000023
#define LOCALE_ITIMEMARKPOSN        0x00001005
#define LOCALE_ICENTURY             0x00000024
#define LOCALE_ITLZERO              0x00000025
#define LOCALE_IDAYLZERO            0x00000026
#define LOCALE_IMONLZERO            0x00000027
#define LOCALE_S1159                0x00000028
#define LOCALE_S2359                0x00000029
#define LOCALE_ICALENDARTYPE        0x00001009
#define LOCALE_IOPTIONALCALENDAR    0x0000100B
#define LOCALE_IFIRSTDAYOFWEEK      0x0000100C
#define LOCALE_IFIRSTWEEKOFYEAR     0x0000100D
#define LOCALE_SDAYNAME1            0x0000002A
#define LOCALE_SDAYNAME2            0x0000002B
#define LOCALE_SDAYNAME3            0x0000002C
#define LOCALE_SDAYNAME4            0x0000002D
#define LOCALE_SDAYNAME5            0x0000002E
#define LOCALE_SDAYNAME6            0x0000002F
#define LOCALE_SDAYNAME7            0x00000030
#define LOCALE_SABBREVDAYNAME1      0x00000031
#define LOCALE_SABBREVDAYNAME2      0x00000032
#define LOCALE_SABBREVDAYNAME3      0x00000033
#define LOCALE_SABBREVDAYNAME4      0x00000034
#define LOCALE_SABBREVDAYNAME5      0x00000035
#define LOCALE_SABBREVDAYNAME6      0x00000036
#define LOCALE_SABBREVDAYNAME7      0x00000037
#define LOCALE_SMONTHNAME1          0x00000038
#define LOCALE_SMONTHNAME2          0x00000039
#define LOCALE_SMONTHNAME3          0x0000003A
#define LOCALE_SMONTHNAME4          0x0000003B
#define LOCALE_SMONTHNAME5          0x0000003C
#define LOCALE_SMONTHNAME6          0x0000003D
#define LOCALE_SMONTHNAME7          0x0000003E
#define LOCALE_SMONTHNAME8          0x0000003F
#define LOCALE_SMONTHNAME9          0x00000040
#define LOCALE_SMONTHNAME10         0x00000041
#define LOCALE_SMONTHNAME11         0x00000042
#define LOCALE_SMONTHNAME12         0x00000043
#define LOCALE_SMONTHNAME13         0x0000100E
#define LOCALE_SABBREVMONTHNAME1    0x00000044
#define LOCALE_SABBREVMONTHNAME2    0x00000045
#define LOCALE_SABBREVMONTHNAME3    0x00000046
#define LOCALE_SABBREVMONTHNAME4    0x00000047
#define LOCALE_SABBREVMONTHNAME5    0x00000048
#define LOCALE_SABBREVMONTHNAME6    0x00000049
#define LOCALE_SABBREVMONTHNAME7    0x0000004A
#define LOCALE_SABBREVMONTHNAME8    0x0000004B
#define LOCALE_SABBREVMONTHNAME9    0x0000004C
#define LOCALE_SABBREVMONTHNAME10   0x0000004D
#define LOCALE_SABBREVMONTHNAME11   0x0000004E
#define LOCALE_SABBREVMONTHNAME12   0x0000004F
#define LOCALE_SABBREVMONTHNAME13   0x0000100F
#define LOCALE_SPOSITIVESIGN        0x00000050
#define LOCALE_SNEGATIVESIGN        0x00000051
#define LOCALE_IPOSSIGNPOSN         0x00000052
#define LOCALE_INEGSIGNPOSN         0x00000053
#define LOCALE_IPOSSYMPRECEDES      0x00000054
#define LOCALE_IPOSSEPBYSPACE       0x00000055
#define LOCALE_INEGSYMPRECEDES      0x00000056
#define LOCALE_INEGSEPBYSPACE       0x00000057
#define	LOCALE_FONTSIGNATURE        0x00000058
#define LOCALE_SISO639LANGNAME      0x00000059
#define LOCALE_SISO3166CTRYNAME     0x0000005A

#define LOCALE_IDEFAULTEBCDICCODEPAGE 0x00001012
#define LOCALE_IPAPERSIZE             0x0000100A
#define LOCALE_SENGCURRNAME           0x00001007
#define LOCALE_SNATIVECURRNAME        0x00001008
#define LOCALE_SYEARMONTH             0x00001006
#define LOCALE_SSORTNAME              0x00001013
#define LOCALE_IDIGITSUBSTITUTION     0x00001014

#define NORM_IGNORECASE				1
#define NORM_IGNORENONSPACE			2
#define NORM_IGNORESYMBOLS			4
#define NORM_STRINGSORT				0x1000
#define NORM_IGNOREKANATYPE                     0x00010000
#define NORM_IGNOREWIDTH                        0x00020000

#define CP_ACP					0
#define CP_OEMCP				1
#define CP_MACCP				2
#define CP_THREAD_ACP				3
#define CP_SYMBOL				42
#define CP_UTF7					65000
#define CP_UTF8					65001

#define WC_DISCARDNS                0x00000010
#define WC_SEPCHARS                 0x00000020
#define WC_DEFAULTCHAR              0x00000040
#define WC_COMPOSITECHECK           0x00000200
#define WC_NO_BEST_FIT_CHARS        0x00000400


/* Locale Dependent Mapping Flags */
#define LCMAP_LOWERCASE	0x00000100	/* lower case letters */
#define LCMAP_UPPERCASE	0x00000200	/* upper case letters */
#define LCMAP_SORTKEY	0x00000400	/* WC sort key (normalize) */
#define LCMAP_BYTEREV	0x00000800	/* byte reversal */

#define SORT_STRINGSORT 0x00001000      /* take punctuation into account */

#define LCMAP_HIRAGANA	0x00100000	/* map katakana to hiragana */
#define LCMAP_KATAKANA	0x00200000	/* map hiragana to katakana */
#define LCMAP_HALFWIDTH	0x00400000	/* map double byte to single byte */
#define LCMAP_FULLWIDTH	0x00800000	/* map single byte to double byte */

/* Date Flags for GetDateFormat. */

#define DATE_SHORTDATE         0x00000001  /* use short date picture */
#define DATE_LONGDATE          0x00000002  /* use long date picture */
#define DATE_USE_ALT_CALENDAR  0x00000004  /* use alternate calendar */
                          /* alt. calendar support is broken anyway */

#define TIME_FORCE24HOURFORMAT 0x00000008  /* force 24 hour format*/
#define TIME_NOTIMEMARKER      0x00000004  /* show no AM/PM */
#define TIME_NOSECONDS         0x00000002  /* show no seconds */
#define TIME_NOMINUTESORSECONDS 0x0000001  /* show no minutes either */

/* internal flags for GetDateFormat system */
#define DATE_DATEVARSONLY      0x00000100  /* only date stuff: yMdg */
#define TIME_TIMEVARSONLY      0x00000200  /* only time stuff: hHmst */
/* use this in a Winelib program if you really want all types */
#define LOCALE_TIMEDATEBOTH    0x00000300  /* full set */

/* Tests that we currently implement */
#define ITU_IMPLEMENTED_TESTS \
	IS_TEXT_UNICODE_SIGNATURE| \
	IS_TEXT_UNICODE_ODD_LENGTH


/* Character Type Flags */
#define	CT_CTYPE1		0x00000001	/* usual ctype */
#define	CT_CTYPE2		0x00000002	/* bidirectional layout info */
#define	CT_CTYPE3		0x00000004	/* textprocessing info */

/* CType 1 Flag Bits */
#define C1_UPPER		0x0001
#define C1_LOWER		0x0002
#define C1_DIGIT		0x0004
#define C1_SPACE		0x0008
#define C1_PUNCT		0x0010
#define C1_CNTRL		0x0020
#define C1_BLANK		0x0040
#define C1_XDIGIT		0x0080
#define C1_ALPHA		0x0100

/* CType 2 Flag Bits */
#define	C2_LEFTTORIGHT		0x0001
#define	C2_RIGHTTOLEFT		0x0002
#define	C2_EUROPENUMBER		0x0003
#define	C2_EUROPESEPARATOR	0x0004
#define	C2_EUROPETERMINATOR	0x0005
#define	C2_ARABICNUMBER		0x0006
#define	C2_COMMONSEPARATOR	0x0007
#define	C2_BLOCKSEPARATOR	0x0008
#define	C2_SEGMENTSEPARATOR	0x0009
#define	C2_WHITESPACE		0x000A
#define	C2_OTHERNEUTRAL		0x000B
#define	C2_NOTAPPLICABLE	0x0000

/* CType 3 Flag Bits */
#define	C3_NONSPACING		0x0001
#define	C3_DIACRITIC		0x0002
#define	C3_VOWELMARK		0x0004
#define	C3_SYMBOL		0x0008
#define	C3_KATAKANA		0x0010
#define	C3_HIRAGANA		0x0020
#define	C3_HALFWIDTH		0x0040
#define	C3_FULLWIDTH		0x0080
#define	C3_IDEOGRAPH		0x0100
#define	C3_KASHIDA		0x0200
#define	C3_LEXICAL		0x0400
#define	C3_ALPHA		0x8000
#define	C3_NOTAPPLICABLE	0x0000

/* Code page information.
 */
#define MAX_LEADBYTES     12
#define MAX_DEFAULTCHAR   2

/* Defines for calendar handling */
#define CAL_NOUSEROVERRIDE        LOCALE_NOUSEROVERRIDE
#define CAL_USE_CP_ACP            LOCALE_USE_CP_ACP
#define CAL_RETURN_NUMBER         LOCALE_RETURN_NUMBER
#define CAL_ICALINTVALUE          0x00000001
#define CAL_SCALNAME              0x00000002
#define CAL_IYEAROFFSETRANGE      0x00000003
#define CAL_SERASTRING            0x00000004
#define CAL_SSHORTDATE            0x00000005
#define CAL_SLONGDATE             0x00000006
#define CAL_SDAYNAME1             0x00000007
#define CAL_SDAYNAME2             0x00000008
#define CAL_SDAYNAME3             0x00000009
#define CAL_SDAYNAME4             0x0000000a
#define CAL_SDAYNAME5             0x0000000b
#define CAL_SDAYNAME6             0x0000000c
#define CAL_SDAYNAME7             0x0000000d
#define CAL_SABBREVDAYNAME1       0x0000000e
#define CAL_SABBREVDAYNAME2       0x0000000f
#define CAL_SABBREVDAYNAME3       0x00000010
#define CAL_SABBREVDAYNAME4       0x00000011
#define CAL_SABBREVDAYNAME5       0x00000012
#define CAL_SABBREVDAYNAME6       0x00000013
#define CAL_SABBREVDAYNAME7       0x00000014
#define CAL_SMONTHNAME1           0x00000015
#define CAL_SMONTHNAME2           0x00000016
#define CAL_SMONTHNAME3           0x00000017
#define CAL_SMONTHNAME4           0x00000018
#define CAL_SMONTHNAME5           0x00000019
#define CAL_SMONTHNAME6           0x0000001a
#define CAL_SMONTHNAME7           0x0000001b
#define CAL_SMONTHNAME8           0x0000001c
#define CAL_SMONTHNAME9           0x0000001d
#define CAL_SMONTHNAME10          0x0000001e
#define CAL_SMONTHNAME11          0x0000001f
#define CAL_SMONTHNAME12          0x00000020
#define CAL_SMONTHNAME13          0x00000021
#define CAL_SABBREVMONTHNAME1     0x00000022
#define CAL_SABBREVMONTHNAME2     0x00000023
#define CAL_SABBREVMONTHNAME3     0x00000024
#define CAL_SABBREVMONTHNAME4     0x00000025
#define CAL_SABBREVMONTHNAME5     0x00000026
#define CAL_SABBREVMONTHNAME6     0x00000027
#define CAL_SABBREVMONTHNAME7     0x00000028
#define CAL_SABBREVMONTHNAME8     0x00000029
#define CAL_SABBREVMONTHNAME9     0x0000002a
#define CAL_SABBREVMONTHNAME10    0x0000002b
#define CAL_SABBREVMONTHNAME11    0x0000002c
#define CAL_SABBREVMONTHNAME12    0x0000002d
#define CAL_SABBREVMONTHNAME13    0x0000002e
#define CAL_SYEARMONTH            0x0000002f
#define CAL_ITWODIGITYEARMAX      0x00000030
#define CAL_GREGORIAN                  1
#define CAL_GREGORIAN_US               2
#define CAL_JAPAN                      3
#define CAL_TAIWAN                     4
#define CAL_KOREA                      5
#define CAL_HIJRI                      6
#define CAL_THAI                       7
#define CAL_HEBREW                     8
#define CAL_GREGORIAN_ME_FRENCH        9
#define CAL_GREGORIAN_ARABIC           10
#define CAL_GREGORIAN_XLIT_ENGLISH     11
#define CAL_GREGORIAN_XLIT_FRENCH      12

/* CompareString defines */
#define CSTR_LESS_THAN			1
#define CSTR_EQUAL			2
#define CSTR_GREATER_THAN		3

#ifndef wchar_t
typedef unsigned short wchar_t;
#endif
#ifndef WCHAR
typedef wchar_t         WCHAR,      *PWCHAR;
#endif

#if 0
#ifndef WINE_WCHAR_DEFINED
#ifdef WINE_UNICODE_NATIVE
typedef wchar_t         WCHAR,      *PWCHAR;
#else
typedef unsigned short  WCHAR,      *PWCHAR;
#endif
#define WINE_WCHAR_DEFINED
#endif

#endif

extern int unicodelib_initflag;
/* code page info common to SBCS and DBCS */
struct cp_info
{
    unsigned int          codepage;          /* codepage id */
    unsigned int          char_size;         /* char size (1 or 2 bytes) */
    WCHAR                 def_char;          /* default char value (can be double-byte) */
    WCHAR                 def_unicode_char;  /* default Unicode char value */
    const char           *name;              /* code page name */
};

struct sbcs_table
{
    struct cp_info        info;
    const WCHAR          *cp2uni;            /* code page -> Unicode map */
    const unsigned char  *uni2cp_low;        /* Unicode -> code page map */
    const unsigned short *uni2cp_high;
};

struct dbcs_table
{
    struct cp_info        info;
    const WCHAR          *cp2uni;            /* code page -> Unicode map */
    const unsigned char  *cp2uni_leadbytes;
    const unsigned short *uni2cp_low;        /* Unicode -> code page map */
    const unsigned short *uni2cp_high;
    unsigned char         lead_bytes[12];    /* lead bytes ranges */
};

union cptable
{
    struct cp_info    info;
    struct sbcs_table sbcs;
    struct dbcs_table dbcs;
};

extern const union cptable *cp_get_table( unsigned int codepage );
extern const union cptable *cp_enum_table( unsigned int index );

extern int cp_mbstowcs( const union cptable *table, int flags,
                        const char *src, int srclen,
                        WCHAR *dst, int dstlen );
extern int cp_wcstombs( const union cptable *table, int flags,
                        const WCHAR *src, int srclen,
                        char *dst, int dstlen, const char *defchar, int *used );
extern int utf8_wcstombs( const WCHAR *src, int srclen, char *dst, int dstlen );
extern int utf8_mbstowcs( int flags, const char *src, int srclen, WCHAR *dst, int dstlen );

extern int strcmpiW( const WCHAR *str1, const WCHAR *str2 );
extern int strncmpiW( const WCHAR *str1, const WCHAR *str2, int n );
extern WCHAR *strstrW( const WCHAR *str, const WCHAR *sub );
extern long int strtolW( const WCHAR *nptr, WCHAR **endptr, int base );
extern unsigned long int strtoulW( const WCHAR *nptr, WCHAR **endptr, int base );

static inline int is_dbcs_leadbyte( const union cptable *table, unsigned char ch )
{
    return (table->info.char_size == 2) && (table->dbcs.cp2uni_leadbytes[ch]);
}

static inline WCHAR tolowerW( WCHAR ch )
{
    extern const WCHAR casemap_lower[];
    return ch + casemap_lower[casemap_lower[ch >> 8] + (ch & 0xff)];
}

static inline WCHAR toupperW( WCHAR ch )
{
    extern const WCHAR casemap_upper[];
    return ch + casemap_upper[casemap_upper[ch >> 8] + (ch & 0xff)];
}

/* the character type contains the C1_* flags in the low 12 bits */
/* and the C2_* type in the high 4 bits */
static inline unsigned short get_char_typeW( WCHAR ch )
{
    extern const unsigned short wctype_table[];
    return wctype_table[wctype_table[ch >> 8] + (ch & 0xff)];
}

inline static int iscntrlW( WCHAR wc )
{
    return get_char_typeW(wc) & C1_CNTRL;
}

inline static int ispunctW( WCHAR wc )
{
    return get_char_typeW(wc) & C1_PUNCT;
}

inline static int isspaceW( WCHAR wc )
{
    return get_char_typeW(wc) & C1_SPACE;
}

inline static int isdigitW( WCHAR wc )
{
    return get_char_typeW(wc) & C1_DIGIT;
}

inline static int isxdigitW( WCHAR wc )
{
    return get_char_typeW(wc) & C1_XDIGIT;
}

inline static int islowerW( WCHAR wc )
{
    return get_char_typeW(wc) & C1_LOWER;
}

inline static int isupperW( WCHAR wc )
{
    return get_char_typeW(wc) & C1_UPPER;
}

inline static int isalnumW( WCHAR wc )
{
    return get_char_typeW(wc) & (C1_ALPHA|C1_DIGIT|C1_LOWER|C1_UPPER);
}

inline static int isalphaW( WCHAR wc )
{
    return get_char_typeW(wc) & (C1_ALPHA|C1_LOWER|C1_UPPER);
}

inline static int isgraphW( WCHAR wc )
{
    return get_char_typeW(wc) & (C1_ALPHA|C1_PUNCT|C1_DIGIT|C1_LOWER|C1_UPPER);
}

inline static int isprintW( WCHAR wc )
{
    return get_char_typeW(wc) & (C1_ALPHA|C1_BLANK|C1_PUNCT|C1_DIGIT|C1_LOWER|C1_UPPER);
}

/* some useful string manipulation routines */

static inline unsigned int strlenW( const WCHAR *str )
{
#if defined(__i386__) && defined(__GNUC__)
    int dummy, res;
    __asm__ __volatile__( "cld\n\t"
                          "repnz\n\t"
                          "scasw\n\t"
                          "notl %0"
                          : "=c" (res), "=&D" (dummy)
                          : "0" (0xffffffff), "1" (str), "a" (0) );
    return res - 1;
#else
    const WCHAR *s = str;
    while (*s) s++;
    return (int)(s - str);
#endif
}

static inline WCHAR *strcpyW( WCHAR *dst, const WCHAR *src )
{
#if defined(__i386__) && defined(__GNUC__)
    int dummy1, dummy2, dummy3;
    __asm__ __volatile__( "cld\n"
                          "1:\tlodsw\n\t"
                          "stosw\n\t"
                          "testw %%ax,%%ax\n\t"
                          "jne 1b"
                          : "=&S" (dummy1), "=&D" (dummy2), "=&a" (dummy3)
                          : "0" (src), "1" (dst)
                          : "memory" );
#else
    WCHAR *p = dst;
    while ((*p++ = *src++));
#endif
    return dst;
}

static inline int strcmpW( const WCHAR *str1, const WCHAR *str2 )
{
    while (*str1 && (*str1 == *str2)) { str1++; str2++; }
    return *str1 - *str2;
}

static inline int strncmpW( const WCHAR *str1, const WCHAR *str2, int n )
{
    if (n <= 0) return 0;
    while ((--n > 0) && *str1 && (*str1 == *str2)) { str1++; str2++; }
    return *str1 - *str2;
}

static inline WCHAR *strncpyW( WCHAR *str1, const WCHAR *str2, int n )
{
    WCHAR *ret = str1;
    while (n-- > 0) if (!(*str1++ = *str2++)) break;
    while (n-- > 0) *str1++ = 0;
    return ret;
}

static inline WCHAR *strcatW( WCHAR *dst, const WCHAR *src )
{
    strcpyW( dst + strlenW(dst), src );
    return dst;
}

static inline WCHAR *strchrW( const WCHAR *str, WCHAR ch )
{
    for ( ; *str; str++) if (*str == ch) return (WCHAR *)str;
    return NULL;
}

static inline WCHAR *strrchrW( const WCHAR *str, WCHAR ch )
{
    WCHAR *ret = NULL;
    for ( ; *str; str++) if (*str == ch) ret = (WCHAR *)str;
    return ret;
}

static inline WCHAR *strlwrW( WCHAR *str )
{
    WCHAR *ret = str;
    while ((*str = tolowerW(*str))) str++;
    return ret;
}

static inline WCHAR *struprW( WCHAR *str )
{
    WCHAR *ret = str;
    while ((*str = toupperW(*str))) str++;
    return ret;
}

static inline long int atolW( const WCHAR *str )
{
    return strtolW( str, (WCHAR **)0, 10 );
}

static inline int atoiW( const WCHAR *str )
{
    return (int)atolW( str );
}


extern const WCHAR unicode_compose_table[0x846];
extern const unsigned int unicode_compose_table_size;
extern const WCHAR unicode_decompose_table[4560];
extern const unsigned short wctype_table[13568];
extern const WCHAR casemap_lower[3328];
extern const WCHAR casemap_upper[3328];

#endif  /* __WINE_UNICODE_H */
