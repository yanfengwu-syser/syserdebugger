#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unicode.h"
/*
extern int cp_mbstowcs( const union cptable *table, int flags,
                        const char *src, int srclen,
                        WCHAR *dst, int dstlen );

int utf8_mbstowcs( int flags, const char *src, int srclen, WCHAR *dst, int dstlen )
*/
void test2()
{
	WCHAR dst[0x100];
	int ret = 0,i;
	int dstlen = 0x100;
	char *src=NULL;
	int len = 0;
	FILE *fp;
#ifdef WIN32
	fp = fopen(".\\testfile\\demo.utf8.txt","r");
#else
	fp = fopen("./testfile/demo.utf8.txt","r");
#endif
	if(fp != NULL)
	{
		fseek(fp,0,SEEK_END);
		len = ftell(fp);
		fseek(fp,0,SEEK_SET);
		src =(char *) malloc(sizeof(char)*len);
		fread(src,1,len,fp);
		fclose(fp);
	}
	printf("src = ");
	for(i = 0; i < len; i++)
		printf("%x ",src[i]);
	printf("\n");
	printf("srclen = %d\n",len);

	ret = utf8_mbstowcs(0,src,len,dst,dstlen);
	fwrite(dst,1,sizeof(WCHAR)*ret,stderr);
	fwrite("\n",1,strlen("\n"),stderr);
	printf("dst = ");
	for(i = 0; i < ret; i++)
		printf("%x ",dst[i]);
	printf("\n");
	printf("dstlen = %d\n",ret);
	return ;
}
int main(int argc, char *argv[])
{
	const union cptable *table;
	WCHAR dst[0x100];
	int ret = 0,i;
	int dstlen = 0x100;
	char *src=NULL;
	int len = 0;
	FILE *fp;
	//test2();
	//return 0;
	table = cp_get_table(936);
#ifdef WIN32
	fp = fopen(".\\testfile\\demo.ansi.txt","r");
#else
	fp = fopen("./testfile/demo.ansi.txt","r");
#endif
	if(fp != NULL)
	{
		fseek(fp,0,SEEK_END);
		len = ftell(fp);
		fseek(fp,0,SEEK_SET);
		src = (char *)malloc(sizeof(char)*len);
		fread(src,1,len,fp);
		fclose(fp);
	}
	ret =	cp_mbstowcs(table,0,src,len,dst,dstlen);
	fwrite(dst,1,sizeof(WCHAR)*ret,stderr);
	for(i = 0; i < ret; i++)
		printf("%x ",dst[i]);
	printf("\n");
	printf("%d\n",ret);
	getchar();
	return 0;
}
