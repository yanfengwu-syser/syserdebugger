#ifndef _BUGCHECKCODE_H_
#define _BUGCHECKCODE_H_
typedef struct _BUGCHECKCODE
{
	int BucCheckCode;
	char* Name;
	char* Description;
}BUGCHECKCODE,*PBUGCHECKCODE;
BUGCHECKCODE gBugCheckCode[];

#endif //_BUGCHECKCODE_H_