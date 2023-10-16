#ifndef _ERROR_CODE_TABLE_H_
#define _ERROR_CODE_TABLE_H_
typedef struct _ERRORCODES
{
	int Code;
	char* Description;
	char* Name;
}ERRORCODES,*PERRORCODES;
ERRORCODES ErrorCodes[];
#endif //_ERROR_CODE_TABLE_H_