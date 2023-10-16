%{
#include "Lex2.h"
#ifdef CODE_OS_NT_DRV
#define malloc mymalloc
#define free myfree
#define realloc myrealloc
void myfree(void *);
void* mymalloc(size_t size);
void* myrealloc(void* path, size_t size);
//#define FILE MYFILE
//typedef void MYFILE;
#endif
#define YY_FATAL_ERROR
/* Included code before lex code */
/*************** Includes and Defines *****************************/
/*
__abstract  |
__alignof |
__asm |
__assume |
__based |
__box  |
__cdecl |
__declspec |
__delegate  |
__event |
__except |
__fastcall |
__forceinline |
__gc  |
__hook | 
__identifier |
__if_exists |
__if_not_exists |
__inline |
__int8 |
__int16 |
__int32 |
__int64 |
__interface |
__leave |
__m64 |
__m128 |
__m128d |
__m128i |
__multiple_inheritance |
__nogc  |
__noop |
__pin  |
__property  |
__raise |
__sealed |
__single_inheritance |
__stdcall |
__super |
__try_cast | 
__try |
__except | 
__finally |
__unhook  |
__uuidof |
__value  |
__virtual_inheritance |
__w64 |
bool |
break |
case |
catch |
char |
class |
const |
const_cast |
continue |
default |
delete |
deprecated  |
dllexport  |
dllimport  |
do |
double |
dynamic_cast |
else |
enum |
explicit |
extern |
false |
float |
for |
friend |
goto |
if |
inline |
int |
long |
mutable |
naked  |
namespace |
new |
noinline  |
noreturn |
nothrow  |
novtable  |
operator |
private |
property | 
protected |
public |
register |
reinterpret_cast |
return |
selectany  |
short |
signed |
sizeof |
static |
static_cast |
struct |
switch |
template |
this |
thread  |
throw |
true |
try |
typedef |
typeid |
typename |
union |
unsigned | 
using |  
uuid | 
virtual | 
void |
volatile |
__wchar_t |
wchar_t |
while   |
*/


typedef char * YYSTYPE; /* interface with lexer: should be  in  header
                        file*/

char  *  yylval;  /*  We  will always point at the text of the lexeme.
          This makes it easy to print out nice trees when  YYDEBUG  is
          enabled.   (see  C++  grammar  file  and  its  definition of
          YYDEBUG_LEXER_TEXT to be "yylval" */



#define WHITE_RETURN(x) /* do nothing */

#define NEW_LINE_RETURN() WHITE_RETURN('\n')

#define PA_KEYWORD_RETURN(x)   RETURN_VAL(x)  /* standard C PArser Keyword */
#define CPP_KEYWORD_RETURN(x)  PA_KEYWORD_RETURN(x)  /* C++ keyword */
#define PPPA_KEYWORD_RETURN(x) RETURN_VAL(x)  /* both PreProcessor and PArser keyword */
#define PP_KEYWORD_RETURN(x)   IDENTIFIER_RETURN()
#define COMMENT_RETURN()	RETURN_VAL(x)



#define NUMERICAL_RETURN(x) RETURN_VAL(x)            /* some sort of constant */
#define LITERAL_RETURN(x)   RETURN_VAL(x)            /* a string literal */

#define RETURN_VAL(x) yylval = yytext; return(x);

#define isatty(a) (1)
#define fileno(a) (1)
#define YY_SKIP_YYWRAP
int main1(int argc, char*argv[]);
int yywrap(){return 1;}
#undef YY_INPUT
#define YY_INPUT(b,r,ms) (r = my_yyinput(b,ms))
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
int my_yyinput(char* buf,int max_size);
#define ECHO
%}

identifier [a-zA-Z_][0-9a-zA-Z_]*

exponent_part [eE][-+]?[0-9]+
fractional_constant ([0-9]*"."[0-9]+)|([0-9]+".")
floating_constant (({fractional_constant}{exponent_part}?)|([0-9]+{exponent_part}))[FfLl]?

integer_suffix_opt ([uU]?[lL]?)|([lL][uU])
decimal_constant [1-9][0-9]*{integer_suffix_opt}
octal_constant "0"[0-7]*{integer_suffix_opt}
hex_constant "0"[xX][0-9a-fA-F]+{integer_suffix_opt}

simple_escape [abfnrtv'"?\\]
octal_escape  [0-7]{1,3}
hex_escape "x"[0-9a-fA-F]+

escape_sequence [\\]({simple_escape}|{octal_escape}|{hex_escape})
c_char [^'\\\n]|{escape_sequence}
s_char [^"\\\n]|{escape_sequence}


h_tab [\011]
form_feed [\014]
v_tab [\013]
c_return [\015]

horizontal_white [ ]|{h_tab}

%x COMMENT

%%


{horizontal_white}+     {
			RETURN_VAL(LEX_WHITE_SPACE);
			}

({v_tab}|{c_return}|{form_feed})+   {
			RETURN_VAL(LEX_WHITE_SPACE);
			}


({horizontal_white}|{v_tab}|{c_return}|{form_feed})*"\n"   {
			RETURN_VAL(LEX_WHITE_SPACE);
			}

__abstract                   {RETURN_VAL(LEX___ABSTRACT);}
__alignof                    {RETURN_VAL(LEX___ALIGNOF);}
__asm                        {RETURN_VAL(LEX___ASM);}
__assume                     {RETURN_VAL(LEX___ASSUME);}
__based                      {RETURN_VAL(LEX___BASED);}
__box                        {RETURN_VAL(LEX___BOX);}
__cdecl                      {RETURN_VAL(LEX___CDECL);}
__declspec                   {RETURN_VAL(LEX___DECLSPEC);}
__delegate                   {RETURN_VAL(LEX___DELEGATE);}
__event                      {RETURN_VAL(LEX___EVENT);}
__except                     {RETURN_VAL(LEX___EXCEPT);}
__fastcall                   {RETURN_VAL(LEX___FASTCALL);}
__forceinline                {RETURN_VAL(LEX___FORCEINLINE);}
__gc                         {RETURN_VAL(LEX___GC);}
__hook                       {RETURN_VAL(LEX___HOOK);}
__identifier                 {RETURN_VAL(LEX___IDENTIFIER);}
__if_exists                  {RETURN_VAL(LEX___IF_EXISTS);}
__if_not_exists              {RETURN_VAL(LEX___IF_NOT_EXISTS);}
__inline                     {RETURN_VAL(LEX___INLINE);}
__int8                       {RETURN_VAL(LEX___INT8);}
__int16                      {RETURN_VAL(LEX___INT16);}
__int32                      {RETURN_VAL(LEX___INT32);}
__int64                      {RETURN_VAL(LEX___INT64);}
__interface                  {RETURN_VAL(LEX___INTERFACE);}
__leave                      {RETURN_VAL(LEX___LEAVE);}
__m64                        {RETURN_VAL(LEX___M64);}
__m128                       {RETURN_VAL(LEX___M128);}
__m128d                      {RETURN_VAL(LEX___M128D);}
__m128i                      {RETURN_VAL(LEX___M128I);}
__multiple_inheritance       {RETURN_VAL(LEX___MULTIPLE_INHERITANCE);}
__nogc                       {RETURN_VAL(LEX___NOGC);}
__noop                       {RETURN_VAL(LEX___NOOP);}
__pin                        {RETURN_VAL(LEX___PIN);}
__property                   {RETURN_VAL(LEX___PROPERTY);}
__raise                      {RETURN_VAL(LEX___RAISE);}
__sealed                     {RETURN_VAL(LEX___SEALED);}
__single_inheritance         {RETURN_VAL(LEX___SINGLE_INHERITANCE);}
__stdcall                    {RETURN_VAL(LEX___STDCALL);}
__super                      {RETURN_VAL(LEX___SUPER);}
__try_cast                   {RETURN_VAL(LEX___TRY_CAST);}
__try                        {RETURN_VAL(LEX___TRY);}
__finally                    {RETURN_VAL(LEX___FINALLY);}
__unhook                     {RETURN_VAL(LEX___UNHOOK);}
__uuidof                     {RETURN_VAL(LEX___UUIDOF);}
__value                      {RETURN_VAL(LEX___VALUE);}
__virtual_inheritance        {RETURN_VAL(LEX___VIRTUAL_INHERITANCE);}
__w64                        {RETURN_VAL(LEX___W64);}
bool                         {RETURN_VAL(LEX_BOOL);}
break                        {RETURN_VAL(LEX_BREAK);}
case                         {RETURN_VAL(LEX_CASE);}
catch                        {RETURN_VAL(LEX_CATCH);}
char                         {RETURN_VAL(LEX_CHAR);}
class                        {RETURN_VAL(LEX_CLASS);}
const                        {RETURN_VAL(LEX_CONST);}
const_cast                   {RETURN_VAL(LEX_CONST_CAST);}
continue                     {RETURN_VAL(LEX_CONTINUE);}
default                      {RETURN_VAL(LEX_DEFAULT);}
delete                       {RETURN_VAL(LEX_DELETE);}
deprecated                   {RETURN_VAL(LEX_DEPRECATED);}
dllexport                    {RETURN_VAL(LEX_DLLEXPORT);}
dllimport                    {RETURN_VAL(LEX_DLLIMPORT);}
do                           {RETURN_VAL(LEX_DO);}
double                       {RETURN_VAL(LEX_DOUBLE);}
dynamic_cast                 {RETURN_VAL(LEX_DYNAMIC_CAST);}
else                         {RETURN_VAL(LEX_ELSE);}
enum                         {RETURN_VAL(LEX_ENUM);}
explicit                     {RETURN_VAL(LEX_EXPLICIT);}
extern                       {RETURN_VAL(LEX_EXTERN);}
false                        {RETURN_VAL(LEX_FALSE);}
float                        {RETURN_VAL(LEX_FLOAT);}
for                          {RETURN_VAL(LEX_FOR);}
friend                       {RETURN_VAL(LEX_FRIEND);}
goto                         {RETURN_VAL(LEX_GOTO);}
if                           {RETURN_VAL(LEX_IF);}
inline                       {RETURN_VAL(LEX_INLINE);}
int                          {RETURN_VAL(LEX_INT);}
long                         {RETURN_VAL(LEX_LONG);}
mutable                      {RETURN_VAL(LEX_MUTABLE);}
naked                        {RETURN_VAL(LEX_NAKED);}
namespace                    {RETURN_VAL(LEX_NAMESPACE);}
new                          {RETURN_VAL(LEX_NEW);}
noinline                     {RETURN_VAL(LEX_NOINLINE);}
noreturn                     {RETURN_VAL(LEX_NORETURN);}
nothrow                      {RETURN_VAL(LEX_NOTHROW);}
novtable                     {RETURN_VAL(LEX_NOVTABLE);}
operator                     {RETURN_VAL(LEX_OPERATOR);}
private                      {RETURN_VAL(LEX_PRIVATE);}
property                     {RETURN_VAL(LEX_PROPERTY);}
protected                    {RETURN_VAL(LEX_PROTECTED);}
public                       {RETURN_VAL(LEX_PUBLIC);}
register                     {RETURN_VAL(LEX_REGISTER);}
reinterpret_cast             {RETURN_VAL(LEX_REINTERPRET_CAST);}
return                       {RETURN_VAL(LEX_RETURN);}
selectany                    {RETURN_VAL(LEX_SELECTANY);}
short                        {RETURN_VAL(LEX_SHORT);}
signed                       {RETURN_VAL(LEX_SIGNED);}
sizeof                       {RETURN_VAL(LEX_SIZEOF);}
static                       {RETURN_VAL(LEX_STATIC);}
static_cast                  {RETURN_VAL(LEX_STATIC_CAST);}
struct                       {RETURN_VAL(LEX_STRUCT);}
switch                       {RETURN_VAL(LEX_SWITCH);}
template                     {RETURN_VAL(LEX_TEMPLATE);}
this                         {RETURN_VAL(LEX_THIS);}
thread                       {RETURN_VAL(LEX_THREAD);}
throw                        {RETURN_VAL(LEX_THROW);}
true                         {RETURN_VAL(LEX_TRUE);}
try                          {RETURN_VAL(LEX_TRY);}
typedef                      {RETURN_VAL(LEX_TYPEDEF);}
typeid                       {RETURN_VAL(LEX_TYPEID);}
typename                     {RETURN_VAL(LEX_TYPENAME);}
union                        {RETURN_VAL(LEX_UNION);}
unsigned                     {RETURN_VAL(LEX_UNSIGNED);}
using                        {RETURN_VAL(LEX_USING);}
uuid                         {RETURN_VAL(LEX_UUID);}
virtual                      {RETURN_VAL(LEX_VIRTUAL);}
void                         {RETURN_VAL(LEX_VOID);}
volatile                     {RETURN_VAL(LEX_VOLATILE);}
__wchar_t                    {RETURN_VAL(LEX___WCHAR_T);}
wchar_t                      {RETURN_VAL(LEX_WCHAR_T);}
while                        {RETURN_VAL(LEX_WHILE);}

#define						   {RETURN_VAL(LEX_PRE_DEFINE);}
#error                         {RETURN_VAL(LEX_PRE_ERROR);}
#import                        {RETURN_VAL(LEX_PRE_IMPORT);}
#undef                         {RETURN_VAL(LEX_PRE_UNDEF);}
#elif                          {RETURN_VAL(LEX_PRE_ELIF);}
#if                            {RETURN_VAL(LEX_PRE_IF);}
#include                       {RETURN_VAL(LEX_INCLUDE);}
#using                         {RETURN_VAL(LEX_PRE_USING);}
#else                          {RETURN_VAL(LEX_PRE_ELSE);}
#ifdef                         {RETURN_VAL(LEX_PRE_IFDEF);}
#line                          {RETURN_VAL(LEX_PRE_LINE);}
#endif                         {RETURN_VAL(LEX_PRE_ENDIF);}
#ifndef                        {RETURN_VAL(LEX_PRE_IFNDEF);}
#pragma                        {RETURN_VAL(LEX_PRE_GRAMA);}

{identifier}                   {RETURN_VAL(LEX_IDENTIFIER);}
{decimal_constant}  		   {RETURN_VAL(LEX_INTEGERconstant);}
{octal_constant}    		   {RETURN_VAL(LEX_OCTALconstant);}
{hex_constant}      		   {RETURN_VAL(LEX_HEXconstant);}
{floating_constant} 		   {RETURN_VAL(LEX_FLOATINGconstant);}
"L"?[']{c_char}+['] 		   {RETURN_VAL(LEX_CHARACTERconstant);}
"L"?["]{s_char}*["]            {RETURN_VAL(LEX_STRINGliteral);}

"("               			   {RETURN_VAL(LEX_LP);}
")"               			   {RETURN_VAL(LEX_RP);}
","               			   {RETURN_VAL(LEX_COMMA);}
"#"               			   {RETURN_VAL('#') ;}
"##"              			   {RETURN_VAL(LEX_POUNDPOUND);}
"{"               			   {RETURN_VAL(LEX_LC);}
"}"               			   {RETURN_VAL(LEX_RC);}
"["               			   {RETURN_VAL(LEX_LB);}
"]"               			   {RETURN_VAL(LEX_RB);}
"."               			   {RETURN_VAL(LEX_DOT);}
"&"               			   {RETURN_VAL(LEX_AND);}
"*"               			   {RETURN_VAL(LEX_STAR);}
"+"               			   {RETURN_VAL(LEX_PLUS);}
"-"               			   {RETURN_VAL(LEX_MINUS);}
"~"               			   {RETURN_VAL(LEX_NEGATE);}
"!"               			   {RETURN_VAL(LEX_NOT);}
"/"               			   {RETURN_VAL(LEX_DIV);}
"%"               			   {RETURN_VAL(LEX_MOD);}
"<"               			   {RETURN_VAL(LEX_LT);}
">"               			   {RETURN_VAL(LEX_GT);}
"^"               			   {RETURN_VAL(LEX_XOR);}
"|"               			   {RETURN_VAL(LEX_PIPE);}
"?"               			   {RETURN_VAL(LEX_QUESTION);}
":"               			   {RETURN_VAL(LEX_COLON);}
";"               			   {RETURN_VAL(LEX_SEMICOLON);}
"="               			   {RETURN_VAL(LEX_ASSIGN);}
".*"              			   {RETURN_VAL(LEX_DOTstar);}
"::"              			   {RETURN_VAL(LEX_CLCL);}
"->"              			   {RETURN_VAL(LEX_ARROW);}
"->*"             			   {RETURN_VAL(LEX_ARROWstar);}
"++"              			   {RETURN_VAL(LEX_ICR);}
"--"              			   {RETURN_VAL(LEX_DECR);}
"<<"              			   {RETURN_VAL(LEX_LS);}
">>"              			   {RETURN_VAL(LEX_RS);}
"<="              			   {RETURN_VAL(LEX_LE);}
">="              			   {RETURN_VAL(LEX_GE);}
"=="              			   {RETURN_VAL(LEX_EQ);}
"!="              			   {RETURN_VAL(LEX_NE);}
"&&"              			   {RETURN_VAL(LEX_ANDAND);}
"||"              			   {RETURN_VAL(LEX_OROR);}
"*="              			   {RETURN_VAL(LEX_MULTassign);}
"/="              			   {RETURN_VAL(LEX_DIVassign);}
"%="              			   {RETURN_VAL(LEX_MODassign);}
"+="              			   {RETURN_VAL(LEX_PLUSassign);}
"-="              			   {RETURN_VAL(LEX_MINUSassign);}
"<<="             			   {RETURN_VAL(LEX_LSassign);}
">>="             			   {RETURN_VAL(LEX_RSassign);}
"&="              			   {RETURN_VAL(LEX_ANDassign);}
"^="              			   {RETURN_VAL(LEX_ERassign);}
"|="              			   {RETURN_VAL(LEX_ORassign);}
"..."             			   {RETURN_VAL(LEX_ELLIPSIS);}
"/*"						   {BEGIN COMMENT;RETURN_VAL(LEX_COMMENT_BLOCK_BEGIN);}
<COMMENT>"*/"				   {BEGIN 0;RETURN_VAL(LEX_COMMENT_BLOCK_END);}
"//".*\n					   {RETURN_VAL(LEX_COMMENT_LINE);}
.							   {RETURN_VAL(LEX_UNKNOW);}
%%

/* I won't bother to provide any error recovery. I won't  even  handle
unknown characters */

/*******************************************************************/
int isaTYPE(char* string)
{  
    return ('A' <= string[0] && 'Z' >= string[0]);
}
char* myinputptr="int main(int argc, char* argv[]);";
char* myinputlim;
int my_yyinput(char* buf,int max_size)
{
	int n = min(max_size,*(int*)&myinputlim - *(int*)&myinputptr);
	if(n > 0)
	{
		memcpy(buf,myinputptr,n);
		myinputptr += n;
	}
	return n;
}
#ifndef CODE_OS_NT_DRV
#ifdef CODE_OS_WIN
int main1(int argc, char* argv[])
#else
int main(int argc, char* argv[])
#endif
{
FILE* fp;
	size_t filelen=strlen(myinputptr);

	if(argc==2)
	{
		fp = fopen(argv[1],"r");
		if(fp)
		{
			filelen = fseek(fp,0,SEEK_END);
			filelen = ftell(fp);
			if(filelen<=0x1000000)
			{
				fseek(fp,0,SEEK_SET);
				myinputptr = (char*)malloc(filelen);
				memset(myinputptr,0,filelen);
				filelen = fread(myinputptr,1,filelen,fp);
				//printf("read file %d\n",filelen,myinputptr);
			}
			else
				filelen = strlen(myinputptr);
			fclose(fp);
		}
	}
	myinputlim=myinputptr+filelen;
	int retvalue=-1;	
	while(retvalue=yylex())
{
	//printf("retvalue=%d %s\n",retvalue,yylval);
}
	//printf("exit retvalue=%d %s\n",retvalue,yylval);
return 0;
}
#endif


#ifdef CODE_OS_NT_DRV 
typedef TMap<void*,unsigned int > CALLOCMAP;
CALLOCMAP* gpLexAllocList=NULL; 
void myfree(void *ptr)
{
	CALLOCMAP::IT FindIT ;
	FindIT = gpLexAllocList->Find(ptr);
	if(FindIT!=gpLexAllocList->End())
	{
		gpLexAllocList->Remove(FindIT);
		delete ptr;
		if(gpLexAllocList->Count()==0)
		{
			delete gpLexAllocList;
			gpLexAllocList=NULL;
		}
	}
}
void* mymalloc(size_t size)
{
	void* ptr=NULL;
	ptr = (void*)new char[size];
	if(ptr)
	{
		if(gpLexAllocList==NULL)
		{
			gpLexAllocList=new CALLOCMAP;
			if(gpLexAllocList==NULL)
				return NULL;
		}
		gpLexAllocList->InsertUnique(ptr,size);
	}
	return ptr;
}
void* myrealloc(void* ptr, size_t size)
{
	char *TmpPtr=NULL;	
	CALLOCMAP::IT FindIT ;
	FindIT = gpLexAllocList->Find(ptr);
	if(FindIT!=gpLexAllocList->End())
	{
		if(*FindIT>=size)
			return ptr;
		TmpPtr = (char*)mymalloc(size);
		memcpy(TmpPtr,ptr,*FindIT);
		myfree(ptr);
	}
	return TmpPtr;
}
#endif