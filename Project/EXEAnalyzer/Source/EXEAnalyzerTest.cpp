// EXEAnalyzerTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <Windows.h>

#define WIN_PE64 0
#define WIN_PE32 1

extern unsigned char grawData_pe32[512];
extern unsigned char grawData_pe64[512];
using namespace std; 
#define  StreamObject CMemoryStream
int create_pe_file(const char* dirname,int mode);
XSCAN_RES dump_hex(CFileIO*pFileIO,PCSTR filename,ULSIZE FileSize,void*CBParam);
class CStream;
int OutBinCodeWithOutPrefix_ib_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix);

typedef int (*OUTPUT_BIN_FP)(CStream* Stream,unsigned char *Buf,int Len,int Prefix);

int OutBinCodeWithPrefix_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int OutBinCodeWithPrefix_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int OutBinCodeWithPrefix_ib_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int opcode_creater_without_rm_id(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix);
int opcode_creater_without_rm_iw(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix);
int OutBinCodeWithPrefix_ib_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int OutBinCodeWithPrefix_ib_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int OutBinCodeWithPrefix_ib_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int OutBinCodeWithPrefix_iz_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int OutBinCodeWithPrefix_iv_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
int OutBinCodeWithPrefix_iz_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix);
#define OutBinCodeWithPrefix_iv_for_Normal OutBinCodeWithPrefix_iz_for_Normal
extern unsigned char rawdata[512];
int main1(int argc, char* argv[]);
XSCAN_RES dump_asm_and_hex(CFileIO*pFileIO,PCSTR filename,ULSIZE FileSize,void*CBParam);
enum{
	RM_0_4,
	RM_0_3,
	RM_4,
};
int opcode_creater(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix,int defaulttype=RM_0_4);
int opcode_creater_without_rm(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix);
int opcode_creater_2(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix,int defaulttype=RM_0_4,unsigned int mask=0XFFFFFFFF);

class CStream
{
public:
	CStream(){}
	virtual ~CStream(){}
	virtual int Write(void* Buffer,int Len)=0;
	virtual int Write(void* Buffer,int Len,int Pos)=0;

	virtual int GetSize()const =0;
	virtual void Flush()=0;
	virtual	int WriteString(char* Buffer)
	{
		int Len = strlen(Buffer);
		return Write(Buffer,Len);
	}
};

class CFileStream: public CStream
{
public:
	~CFileStream()
	{
		Flush();
		fclose(m_fp);
	}
	CFileStream(const char* name,const char* mode="wb")
	{
		m_fp=fopen(name,mode);
	}
	int Write(void* Buffer,int Len)
	{
		fwrite(Buffer,Len,1,m_fp);
		return Len;
	}
	int Write(void* Buffer,int Len,int Pos)
	{
		long oldpos=ftell(m_fp);
		fseek(m_fp,Pos,SEEK_SET);
		Write(Buffer,Len);
		fseek(m_fp,oldpos,SEEK_SET);
		return Len;
	}
	int GetSize()const{return 0;};
	void Flush()
	{
		fflush(m_fp);
	}
private:
	FILE* m_fp;
};
class CMemoryStream: public CFileStream
{
public:
	CMemoryStream(const char* name,const char* mode="wb"):CFileStream(name,mode)
	{
		m_CurPos=0;
		m_Length=0x100000*110;
		m_Buffer=new char[m_Length];
	}
	~CMemoryStream()
	{
		if(m_CurPos)
			CFileStream::Write(m_Buffer,m_CurPos);
		if(m_Buffer)
			delete m_Buffer;
	}

	int Write(void* Buffer,int Len)
	{
		if(Len+m_CurPos<m_Length-1)
		{
			memcpy(m_Buffer+m_CurPos,Buffer,Len);
			m_CurPos+=Len;
		}
		else
		{
			CFileStream::Write(m_Buffer,m_CurPos);
			m_CurPos=0;
			if(Len>m_Length)
				CFileStream::Write(Buffer,Len);
			else
			{
				memcpy(m_Buffer+m_CurPos,Buffer,Len);
				m_CurPos=Len;
			}
		}
		return Len;
	}
	int Write(void* Buffer,int Len,int Pos)
	{
		memcpy(m_Buffer+Pos,Buffer,Len);
		return Len;
	}
	int GetSize()const{return 0;};
	void Flush()
	{
		if(m_CurPos)
			CFileStream::Write(m_Buffer,m_CurPos);
		CFileStream::Flush();
	}
private:
	char* m_Buffer;
	int m_CurPos;
	int m_Length;
};
enum 
{
	IDA_OUTPUT,
	DUMPBIN_OUTPUT,
};
typedef struct _CB_PARAM
{
	int type;
	char* dirname;
	char* hexdirname;
	int mode;
}CB_PARAM;
int main(int argc, char*agv[])
{
#if 0
	main1(argc,agv);
#else

	DWORD dwBegin=GetTickCount();
	CB_PARAM cb={IDA_OUTPUT,"c:\\disasm_test\\syser_test","c:\\disasm_test\\syser_hex",WIN_PE32};
	char dirname[512]="c:\\disasm_test\\exe_sample\\*.exe";
	create_pe_file("c:\\disasm_test\\exe_sample",WIN_PE32);
	create_pe_file("c:\\disasm_test\\exe_sample",WIN_PE64);
	printf("%d\n",GetTickCount()-dwBegin);

	gpFileIO->XScan(dirname,dump_asm_and_hex,&cb);
	//gpFileIO->XScan(dirname,dump_hex,&cb);

#endif
	return 0;
}

int main1(int argc, char* argv[])
{
	char CodeBuffer[16]={0x0f, 0xae, 0x38, 0x04, 0x0d, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00 };
	int nLen2=0;
	INSTRUCTION_INFORMATION InstInfo;
	char buffer[1024];
	memset(&InstInfo,0,sizeof(InstInfo));
	InstInfo.pasm=buffer;
	unsigned long long dwEip=0x140008000ll;

	memset(&InstInfo,0,sizeof(InstInfo));
	nLen2=Disassembly(&InstInfo,(BYTE*)CodeBuffer,dwEip,BIT64,NULL);
	if(nLen2)
	{
		InstInfo.pasm=buffer;
		PrintPasmForIDA(&InstInfo,buffer,0,0);
		dwEip+=nLen2;
		printf("\t\t%-50s",InstInfo.pasm);
		for(int q=0;q<nLen2;q++)
			printf("%02x ",(unsigned char)CodeBuffer[q]);
		printf("\n");
	}
	return 0;
}

// testcase.cpp : Defines the entry point for the console application.
//

XSCAN_RES dump_hex(CFileIO*pFileIO,PCSTR filename,ULSIZE FileSize,void*CBParam)
{
	CB_PARAM *pCb=(CB_PARAM*)CBParam;
	
	char hexfilename[512];
	int mode=pCb->mode;
	char* dirname=(char*)pCb->dirname;
	HANDLE hFile;
	gpFileIO->OpenFile(filename,&hFile);
	unsigned long size=FileSize;
	unsigned char *CodeBuffer=new unsigned char[size];
	gpFileIO->ReadFile(hFile,CodeBuffer,size,0);
	gpFileIO->CloseHandle(hFile);
	int nLen2=0;
	INSTRUCTION_INFORMATION InstInfo;
	char buffer[1024];
	memset(&InstInfo,0,sizeof(InstInfo));
	InstInfo.U_x1=13;
	InstInfo.pasm=buffer;
	unsigned long long dwEip=0x140001000ll;
	int n=size;
	int i=0x2a00;
	char WriteBuffer[1024];
	char filetitle[512];
	TGetFileTitle(filename,filetitle);

	if(TStrStr(filename,"_win32_"))
		mode=WIN_PE32;
	else 
		mode=WIN_PE64;

	
	sprintf(hexfilename,"%s\\%s.hex",pCb->hexdirname,filetitle);

	
	StreamObject HexStream(hexfilename,"wt");
	printf("Create asm file for %s (%s)\n",filename,mode==WIN_PE32?"WIN32":"WIN64");
	for(i=0x200;i<n;)
	{
		memset(&InstInfo,0,sizeof(InstInfo));
		if(mode==WIN_PE64)
			nLen2=Disassembly(&InstInfo,(BYTE*)CodeBuffer+i,dwEip,BIT64,NULL);
		else
			nLen2=Disassembly(&InstInfo,(BYTE*)CodeBuffer+i,dwEip,BIT32,NULL);

		if(pCb->type!=IDA_OUTPUT)
		{
			InstInfo.pasm=buffer;
			PrintPasm(&InstInfo,buffer,0,12);
		}
		else
		{
			InstInfo.pasm=buffer;
			PrintPasmForIDA(&InstInfo,buffer,0,0);
		}

		if(nLen2)
		{
			dwEip+=nLen2;

			strcpy(WriteBuffer,InstInfo.pasm);
			
			int n=0;
			n=sprintf(WriteBuffer,"%llx ",dwEip);
			HexStream.Write(WriteBuffer,n);
			HexStream.WriteString(InstInfo.pasm);
			HexStream.WriteString(" (");

			n=0;
			for(int j=0;j<nLen2;j++)
				n+=sprintf(WriteBuffer+n,"%02x ",CodeBuffer[i+j]);
			HexStream.Write(WriteBuffer,n);
			HexStream.WriteString(")\n");
			i+=nLen2;;
		}
		else
		{
			int n=sprintf(WriteBuffer,"%16llx error![ ",dwEip);
			for(int j=0;j<15;j++)
				n+=sprintf(WriteBuffer+n,"%02x ",CodeBuffer[i+j]);
			n+=sprintf(WriteBuffer+n,"]\n");
			
			dwEip++;
			i++;
		}
	}

	delete []CodeBuffer;
	return XSCAN_RES_CONTINUE;
}


XSCAN_RES dump_asm_and_hex(CFileIO*pFileIO,PCSTR filename,ULSIZE FileSize,void*CBParam)
{

	CB_PARAM *pCb=(CB_PARAM*)CBParam;
	char asmfilename[512];
	char hexfilename[512];
	int mode=pCb->mode;
	char* dirname=(char*)pCb->dirname;
	HANDLE hFile;
	gpFileIO->OpenFile(filename,&hFile);
	unsigned long size=FileSize;
	unsigned char *CodeBuffer=new unsigned char[size];
	gpFileIO->ReadFile(hFile,CodeBuffer,size,0);
	gpFileIO->CloseHandle(hFile);
	int nLen2=0;
	INSTRUCTION_INFORMATION InstInfo;
	char buffer[1024];
	memset(&InstInfo,0,sizeof(InstInfo));
	InstInfo.U_x1=13;
	InstInfo.pasm=buffer;
	unsigned long long dwEip=0x140001000ll;
	int n=size;
	int i=0x2a00;
	char WriteBuffer[1024];
	char filetitle[512];
	TGetFileTitle(filename,filetitle);
	
	if(TStrStr(filename,"_win32_"))
		mode=WIN_PE32;
	else 
		mode=WIN_PE64;

	sprintf(asmfilename,"%s\\%s.txt",dirname,filetitle);
	sprintf(hexfilename,"%s\\%s.hex",pCb->hexdirname,filetitle);
	
	StreamObject TxtStream(asmfilename,"wt");
	StreamObject HexStream(hexfilename,"wt");
	printf("Create asm file for %s (%s)\n",filename,mode==WIN_PE32?"WIN32":"WIN64");
	
	for(i=0x200;i<n;)
	{
		memset(&InstInfo,0,sizeof(InstInfo));
		if(mode==WIN_PE64)
			nLen2=Disassembly(&InstInfo,(BYTE*)CodeBuffer+i,dwEip,BIT64,NULL);
		else
			nLen2=Disassembly(&InstInfo,(BYTE*)CodeBuffer+i,dwEip,BIT32,NULL);

		if(pCb->type!=IDA_OUTPUT)
		{
			InstInfo.pasm=buffer;
			PrintPasm(&InstInfo,buffer,0,12);
		}
		else
		{
			InstInfo.pasm=buffer;
			PrintPasmForIDA(&InstInfo,buffer,0,0);
		}

		if(nLen2)
		{
			strcpy(WriteBuffer,InstInfo.pasm);
			TxtStream.WriteString(WriteBuffer);
			TxtStream.Write("\n",1);
			int n=0;
			n=sprintf(WriteBuffer,"%llx ",dwEip);
			HexStream.Write(WriteBuffer,n);
			HexStream.WriteString(InstInfo.pasm);
			HexStream.WriteString(" (");

			n=0;
			for(int j=0;j<nLen2;j++)
				n+=sprintf(WriteBuffer+n,"%02x ",CodeBuffer[i+j]);
			HexStream.Write(WriteBuffer,n);
			HexStream.WriteString(")\n");
			i+=nLen2;;
			dwEip+=nLen2;
		}
		else
		{
			int n=sprintf(WriteBuffer,"%16llx error![ ",dwEip);
			for(int j=0;j<15;j++)
				n+=sprintf(WriteBuffer+n,"%02x ",CodeBuffer[i+j]);
			n+=sprintf(WriteBuffer+n,"]\n");
			TxtStream.Write(WriteBuffer,n);
			dwEip++;
			i++;
		}
	}
	
	delete []CodeBuffer;
	return XSCAN_RES_CONTINUE;
}


enum
{
	OUT_SOURCE_CODE,
	OUT_BIN_CODE,
	OUT_SOURCE_CODE_64,
	OUT_BIN_CODE_64,

};
typedef int (*FP_OUTPUT_INTERFACE)(CStream*,unsigned char*,int);




int create_pe_file(const char* dirname,int mode)
{
	unsigned long totalsize;
	unsigned long newvalue;
	unsigned long imagesizeoffset,sizecodeoffset;
	unsigned char *rawdata;
	char nameprefix[512];
	if(mode==WIN_PE64)
	{
		imagesizeoffset=0x108;
		sizecodeoffset=0xd4;
		rawdata= grawData_pe64;
		sprintf(nameprefix,"opcode_win64_");
	}
	else
	{
		imagesizeoffset=0x118;
		sizecodeoffset=0xe4;
		rawdata= grawData_pe32;
		sprintf(nameprefix,"opcode_win32_");
	}
	char filename[256];
#if 0

	int opcode_with_00_rm[]={


		0x00,0x01,0x02,0x03,
		0x10,0x11,0x12,0x13,
		0x20,0x21,0x22,0x23,
		0x30,0x31,0x32,0x33,
		0x84,0x85,0x86,0x87,
		0x63,
		0x08,0x09,0x0a,0x0b,
		0x18,0x19,0x1a,0x1b,
		0x28,0x29,0x2a,0x2b,
		0x38,0x39,0x3a,0x3b,
		0x88,0x89,0x8a,0x8b,0x8c,0x8e,
		0x0d0f,
		0x020f,0x030f,
		0x100f,0x110f,0x120f,0x140f,0x150f,0x160f,0x1f0f,
		0x400f,0x410f,0x420f,0x430f,0x440f,0x450f,0x460f,0x470f,
		0x480f,0x490f,0x4a0f,0x4b0f,0x4c0f,0x4d0f,0x4e0f,0x4f0f,
		0x510f,0x520f,0x530f,0x540f,0x550f,0x560f,0x570f,
		0x600f,0x610f,0x620f,0x630f,0x640f,0x650f,0x660f,0x670f,
		0x740f,0x750f,0x760f,
		0x280f,0x290f,0x2a0f,0x2c0f,0x2d0f,0x2e0f,0x2f0f,
		0x580f,0x590f,0x5a0f,0x5b0f,0x5c0f,0x5d0f,0x5e0f,0x5f0f,
		0x680f,0x690f,0x6a0f,0x6b0f,0x6e0f,0x6f0f,
		0x780f,0x790f,0x7e0f,0x7f0f,
		0xb00f,0xb10f,0xb30f,0xb60f,0xb70f,
		0xc00f,0xc10f,
		0xd10f,0xd20f,0xd30f,0xd40f,0xd50f,
		0xe00f,0xe10f,0xe20f,0xe30f,0xe40f,0xe50f,
		0xf10f,0xf20f,0xf30f,0xf40f,0xf50f,0xf60f,
		0xab0f,0xad0f,0xaf0f,
		0xbb0f,0xbc0f,0xbd0f,0xbe0f,0xbf0f,
		0xd80f,0xd90f,0xda0f,0xdb0f,0xdc0f,0xdd0f,0xde0f,0xdf0f,
		0xe80f,0xe90f,0xea0f,0xeb0f,0xec0f,0xed0f,0xee0f,0xef0f,
		0xf80f,0xf90f,0xfa0f,0xfb0f,0xfc0f,0xfd0f,0xfe0f,
		0x00380f,0x01380f,0x02380f,0x03380f,0x04380f,0x05380f,0x06380f,0x07380f,
		0x08380f,0x09380f,0x0a380f,0x0b380f,
		0x1c380f,0x1d380f,0x1e380f,
		0x0f3a0f,
		
	};
	for(int i = 0 ; i<sizeof(opcode_with_00_rm)/sizeof(opcode_with_00_rm[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_with_00_rm[i]&0xffff)==0x380f)||((opcode_with_00_rm[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_with_00_rm[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x.exe",dirname,nameprefix,opcode_with_00_rm[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_with_00_rm[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_with_00_rm[i],3,0x66);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_with_00_rm[i],3,0x66);
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_with_00_rm[i],opcodelen,0x66);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_with_00_rm[i],opcodelen,0x66);
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	int opcode_with_66_rm[]={
		
		0x00,0x01,0x02,0x03,
		0x10,0x11,0x12,0x13,
		0x20,0x21,0x22,0x23,
		0x30,0x31,0x32,0x33,
		0x84,0x85,0x86,0x87,
		0x63,
		0x08,0x09,0x0a,0x0b,
		0x18,0x19,0x1a,0x1b,
		0x28,0x29,0x2a,0x2b,
		0x38,0x39,0x3a,0x3b,
		0x88,0x89,0x8a,0x8b,0x8c,0x8e,
		0x0d0f,
		0x100f,0x110f,0x140f,0x150f,0x1f0f,
		0x020f,0x030f,
		0x400f,0x410f,0x420f,0x430f,0x440f,0x450f,0x460f,0x470f,0x480f,0x490f,0x4a0f,0x4b0f,0x4c0f,0x4d0f,0x4e0f,0x4f0f,
		0x510f,0x540f,0x550f,0x560f,0x570f,
		0x600f,0x610f,0x620f,0x630f,0x640f,0x650f,0x660f,0x670f,
		0x740f,0x750f,0x760f,
		0x280f,0x290f,0x2a0f,0x2c0f,0x2d0f,0x2e0f,0x2f0f,
		0x580f,0x590f,0x5a0f,0x5b0f,0x5c0f,0x5d0f,0x5e0f,0x5f0f,
		0x680f,0x690f,0x6a0f,0x6b0f,0x6c0f,0x6d0f,0x6e0f,0x6f0f,
		0x7c0f,0x7d0f,0x7e0f,0x7f0f,
		0xab0f,0xaf0f,0xa30f,0xa50f,
		0xb00f,0xb10f,0xb30f,0xb60f,0xb70f,
		0xbb0f,0xbc0f,0xbd0f,0xbe0f,0xbf0f,
		0xc00f,0xc10f,
		0xd00f,0xd10f,0xd20f,0xd30f,0xd40f,0xd50f,0xd60f,
		0xe00f,0xe10f,0xe20f,0xe30f,0xe40f,0xe50f,0xe60f,
		0xf10f,0xf20f,0xf30f,0xf40f,0xf50f,0xf60f,
		0xd80f,0xd90f,0xda0f,0xdb0f,0xdc0f,0xdd0f,0xde0f,0xdf0f,
		0xe80f,0xe90f,0xea0f,0xeb0f,0xec0f,0xed0f,0xee0f,0xef0f,
		0xf80f,0xf90f,0xfa0f,0xfb0f,0xfc0f,0xfd0f,0xfe0f,

		0x00380f,0x01380f,0x02380f,0x03380f,0x04380f,0x05380f,0x06380f,0x07380f,0x08380f,
		0x10380f,0x14380f,0x15380f,0x17380f,
		0x20380f,0x21380f,0x22380f,0x23380f,0x24380f,0x25380f,
		0x30380f,0x31380f,0x32380f,0x33380f,0x34380f,0x35380f,0x37380f,
		0x40380f,0x41380f,
		0x08380f,0x09380f,0x0a380f,0x0b380f,
		0x1c380f,0x1d380f,0x1e380f,
		0x28380f,0x29380f,0x2b380f,
		0x38380f,0x39380f,0x3a380f,0x3b380f,0x3c380f,0x3d380f,0x3e380f,0x3f380f,
		0xdb380f,0xdc380f,0xdd380f,0xde380f,0xdf380f,

		0x143a0f,0x153a0f,0x163a0f,0x173a0f,//ida ¥¶¿Ì 0x153a0f ”– bug  //0x143a0f,0x153a0f,0x163a0f 0x203a0f,0x223a0f 
		0x203a0f,0x213a0f,0x223a0f,
		
		0x403a0f,0x413a0f,0x423a0f,0x443a0f,
		0x603a0f,0x613a0f,0x623a0f,0x633a0f,
		0x083a0f,0x093a0f,0x0a3a0f,0x0b3a0f,0x0c3a0f,0x3d3a0f,0x0e3a0f,0x0f3a0f,
		0xdf3a0f,
		
	};
	
	for(int i = 0 ; i<sizeof(opcode_with_66_rm)/sizeof(opcode_with_66_rm[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_with_66_rm[i]&0xffff)==0x380f)||((opcode_with_66_rm[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_with_66_rm[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_66.exe",dirname,nameprefix,opcode_with_66_rm[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		if((opcode_with_66_rm[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_with_66_rm[i],3,0x66);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_with_66_rm[i],3,0x66);
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_with_66_rm[i],opcodelen,0x66);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_with_66_rm[i],opcodelen,0x66);
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	
	
	
	int opcode_with_f2_rm[]={
		0x100f,0x110f,0x120f,
		0x510f,
		0x2a0f,0x2c0f,0x2d0f,
		0x580f,0x590f,0x5a0f,0x5c0f,0x5d0f,0x5f0f,
		0x7c0f,0x7d0f,
		0xd00f,0xe60f,
		0xf0380f,0xf1380f,
	};
	for(int i = 0 ; i<sizeof(opcode_with_f2_rm)/sizeof(opcode_with_f2_rm[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_with_f2_rm[i]&0xffff)==0x380f)||((opcode_with_f2_rm[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_with_f2_rm[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_f2.exe",dirname,nameprefix,opcode_with_f2_rm[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_with_f2_rm[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_with_f2_rm[i],3,0xf2);
			if(mode==WIN_PE64)
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_with_f2_rm[i],3,0xf2);
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_with_f2_rm[i],opcodelen,0xf2);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_with_f2_rm[i],opcodelen,0xf2);
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	
	int opcode_with_f3_rm[]={
		
		0x160f,0x100f,0x110f,0x120f,
		0x510f,0x520f,0x530f,
		0x2a0f,0x2c0f,0x2d0f,
		0x580f,0x590f,0x5a0f,0x5b0f,0x5c0f,0x5d0f,0x5e0f,0x5f0f,
		0x6f0f,
		0x7e0f,0x7f0f,
		0xb80f,
		0xe60f,
		0x160f,0x520f,0x530f,0x5b0f,0x6f0f,0x7e0f,0x7f0f
	};
	for(int i = 0 ; i<sizeof(opcode_with_f3_rm)/sizeof(opcode_with_f3_rm[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_with_f3_rm[i]&0xffff)==0x380f)||((opcode_with_f3_rm[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_with_f3_rm[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_f3.exe",dirname,nameprefix,opcode_with_f3_rm[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_with_f3_rm[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_with_f3_rm[i],3,0xf3);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_with_f3_rm[i],3,0xf3);
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_with_f3_rm[i],opcodelen,0xf3);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_with_f3_rm[i],opcodelen,0xf3);
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	

	//only support memory address mode
	int opcode_memory_prefix_00_[]=
	{
		0xf0380f,0xf1380f,0xe70f,0xb20f,0xb40f,0xb50f,0x2b0f,0x170f,0x130f,0xc30f,
	};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_memory_prefix_00_)/sizeof(opcode_memory_prefix_00_[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_memory_prefix_00_[i]&0xffff)==0x380f)||((opcode_memory_prefix_00_[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_memory_prefix_00_[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_00.exe",dirname,nameprefix,opcode_memory_prefix_00_[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_memory_prefix_00_[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_memory_prefix_00_[i],opcodelen,0x00,RM_0_3);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_memory_prefix_00_[i],opcodelen,0x00,RM_0_3);
			}
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_memory_prefix_00_[i],opcodelen,0x00,RM_0_3);

			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_memory_prefix_00_[i],opcodelen,0x00,RM_0_3);
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}


	int opcode_memory_prefix_00_66[]=
	{
		0xf0380f,0xf1380f,0xe70f,0xb20f,0xb40f,0xb50f,0x2b0f,0x170f,0x130f,0x160f,0x120f,0x2a380f,0x80380f,0x81380f,
	};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_memory_prefix_00_66)/sizeof(opcode_memory_prefix_00_66[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_memory_prefix_00_66[i]&0xffff)==0x380f)||((opcode_memory_prefix_00_66[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_memory_prefix_00_66[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_66.exe",dirname,nameprefix,opcode_memory_prefix_00_66[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_memory_prefix_00_66[i]&0xffff)==0x3a0f)
		{
			
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_memory_prefix_00_66[i],opcodelen,0x66,RM_0_3);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_memory_prefix_00_66[i],opcodelen,0x66,RM_0_3);
			}
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_memory_prefix_00_66[i],opcodelen,0x66,RM_0_3);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_memory_prefix_00_66[i],opcodelen,0x66,RM_0_3);
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_memory_prefix_00_f2_[]=
	{
		0xf00f,
	};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_memory_prefix_00_f2_)/sizeof(opcode_memory_prefix_00_f2_[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_memory_prefix_00_f2_[i]&0xffff)==0x380f)||((opcode_memory_prefix_00_f2_[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_memory_prefix_00_f2_[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_f2.exe",dirname,nameprefix,opcode_memory_prefix_00_f2_[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_memory_prefix_00_f2_[i]&0xffff)==0x3a0f)
		{
			
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_memory_prefix_00_f2_[i],opcodelen,0xf2,RM_0_3);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_memory_prefix_00_f2_[i],opcodelen,0xf2,RM_0_3);
			}
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_memory_prefix_00_f2_[i],opcodelen,0xf2,RM_0_3);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_memory_prefix_00_f2_[i],opcodelen,0xf2,RM_0_3);
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	
	int opcode_reg_prefix_00_[]=
	{
		0x500f,0xd70f,0xf70f,
	};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_reg_prefix_00_)/sizeof(opcode_reg_prefix_00_[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_reg_prefix_00_[i]&0xffff)==0x380f)||((opcode_reg_prefix_00_[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_reg_prefix_00_[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_00.exe",dirname,nameprefix,opcode_reg_prefix_00_[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_reg_prefix_00_[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_reg_prefix_00_[i],opcodelen,0x00,RM_4);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_reg_prefix_00_[i],opcodelen,0x00,RM_4);
			}
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_reg_prefix_00_[i],opcodelen,0x00,RM_4);

			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_reg_prefix_00_[i],opcodelen,0x00,RM_4);
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	int opcode_reg_prefix_66[]=
	{
		0x500f,0xd70f,0xf70f,
	};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_reg_prefix_66)/sizeof(opcode_reg_prefix_66[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_reg_prefix_66[i]&0xffff)==0x380f)||((opcode_reg_prefix_66[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_reg_prefix_66[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_66.exe",dirname,nameprefix,opcode_reg_prefix_66[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_reg_prefix_66[i]&0xffff)==0x3a0f)
		{
			
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_reg_prefix_66[i],opcodelen,0x66,RM_4);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_reg_prefix_66[i],opcodelen,0x66,RM_4);
			}
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_reg_prefix_66[i],opcodelen,0x66,RM_4);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_reg_prefix_66[i],opcodelen,0x66,RM_4);
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	int opcode_reg_prefix_f2_[]=
	{
		0xd60f,
	};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_reg_prefix_f2_)/sizeof(opcode_reg_prefix_f2_[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_reg_prefix_f2_[i]&0xffff)==0x380f)||((opcode_reg_prefix_f2_[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_reg_prefix_f2_[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_f2.exe",dirname,nameprefix,opcode_reg_prefix_f2_[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_reg_prefix_f2_[i]&0xffff)==0x3a0f)
		{
			
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_reg_prefix_f2_[i],opcodelen,0xf2,RM_4);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_reg_prefix_f2_[i],opcodelen,0xf2,RM_4);
			}
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_reg_prefix_f2_[i],opcodelen,0xf2,RM_4);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_reg_prefix_f2_[i],opcodelen,0xf2,RM_4);
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_reg_prefix_f3_[]=
	{
		0xd60f,
	};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_reg_prefix_f3_)/sizeof(opcode_reg_prefix_f3_[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_reg_prefix_f3_[i]&0xffff)==0x380f)||((opcode_reg_prefix_f3_[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_reg_prefix_f3_[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x_f3.exe",dirname,nameprefix,opcode_reg_prefix_f3_[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		if((opcode_reg_prefix_f3_[i]&0xffff)==0x3a0f)
		{
			
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_reg_prefix_f3_[i],opcodelen,0xf3,RM_4);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_reg_prefix_f3_[i],opcodelen,0xf3,RM_4);
			}
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_Normal,opcode_reg_prefix_f3_[i],opcodelen,0xf3,RM_4);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_for_64,opcode_reg_prefix_f3_[i],opcodelen,0xf3,RM_4);
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}


	int opcode_rm_ib_00_[]=
	{
		0x6b,0xc20f,0xc60f,0x700f,0xc50f,0x80,0x82,0x83
	};
	unsigned int opcode_rm_ib_00_prefix[]=
	{
		0x6701,0xf4f36601,0x6701,0xf4f36701,0x6701,0x6701,0x6701,0x6701,
	};
	int opcode_rm_ib_00_rmbyte[]=
	{
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
		(RM_4 << 8)|(RM_4),
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
		(RM_0_4 << 24)|(RM_0_4 << 16)|(RM_0_4 << 8)|(RM_0_4),
	};
	int mask[4]={0xff000000,0xff0000,0xff00,0xff};
	int shift[4]={24,16,8,0};
	totalsize=0;
	for(int i = 0 ; i<sizeof(opcode_rm_ib_00_)/sizeof(opcode_rm_ib_00_[0]);i++)
	{	
		totalsize=0;
		int opcodelen;
		if(((opcode_rm_ib_00_[i]&0xffff)==0x380f)||((opcode_rm_ib_00_[i]&0xffff)==0x3a0f))
			opcodelen=3;
		else if((opcode_rm_ib_00_[i]&0xff)==0x0f)
			opcodelen=2;
		else
			opcodelen=1;
		sprintf(filename,"%s\\%s0x%04x.exe",dirname,nameprefix,opcode_rm_ib_00_[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		unsigned int val;
		unsigned int rmbyte;
		for(int ip=0;ip<4;ip++)
		{
			val=opcode_rm_ib_00_prefix[i];
			val=((val&mask[ip])>>shift[ip])-1;
			if(val==-1)
				continue;
			rmbyte=opcode_rm_ib_00_rmbyte[i];
			rmbyte=((rmbyte&mask[ip])>>shift[ip]);
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_rm_ib_00_[i],opcodelen,0,rmbyte);
			if(mode==WIN_PE64)
			{
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_rm_ib_00_[i],opcodelen,0,rmbyte);
			}
		}
		
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	{
		totalsize=0;
		sprintf(filename,"%s\\%s0xc8-0xcf.exe",dirname,nameprefix);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		for(int i=0xc8;i<0xd0;i++)
		{
			int iii;
			iii=(i<<8)|0x0f;
			
			if(mode==WIN_PE64)
			{
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&iii,2,0);
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&iii,2,0x66);
			}
			else
			{
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&iii,2,0);
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&iii,2,0x66);
			}
		}
		for(int i=0x50;i<0x60;i++)
		{
			
			
			if(mode==WIN_PE64)
			{
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&i,1,0);
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&i,1,0x66);
			}
			else
			{
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&i,1,0);
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&i,1,0x66);
			}
		}
		for(int i=0x90;i<0x98;i++)
		{
			
			
			if(mode==WIN_PE64)
			{
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&i,1,0);
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&i,1,0x66);
				if(i==0x90)
					totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&i,1,0xf3);
				
			}
			else
			{
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&i,1,0);
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&i,1,0x66);
				if(i==0x90)
					totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&i,1,0xf3);

			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	
	{
		totalsize=0;
		sprintf(filename,"%s\\%s0x20-0x25.exe",dirname,nameprefix);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);

		for(int i=0x20;i<0x27;i++)
		{
			if(i==0x25)
				continue;
			for(int ii=0xc0;ii<0x100;ii++)
			{				
				int iii;
				iii=(i<<8)|0x0f|(ii<<16);
			
				if(mode==WIN_PE64)
				{
					totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&iii,3,0);
					totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&iii,3,0x66);
				}
				else
				{
					totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&iii,3,0);
					totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&iii,3,0x66);
				}
			}
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	
	{
		totalsize=0;
		sprintf(filename,"%s\\%s0xb0-0xbf.exe",dirname,nameprefix);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		for(int i=0xb0;i<0xb8;i++)
		{
				if(mode==WIN_PE64)
				{
					totalsize+=OutBinCodeWithPrefix_ib_for_64(Stream,(unsigned char*)&i,1,0);
					totalsize+=OutBinCodeWithPrefix_ib_for_64(Stream,(unsigned char*)&i,1,0x66);
				}
				else
				{
					totalsize+=OutBinCodeWithPrefix_ib_for_Normal(Stream,(unsigned char*)&i,1,0);
					totalsize+=OutBinCodeWithPrefix_ib_for_Normal(Stream,(unsigned char*)&i,1,0x66);
				}
		}
		for(int i=0xb8;i<0xc0;i++)
		{
				if(mode==WIN_PE64)
				{
					totalsize+=OutBinCodeWithPrefix_iv_for_64(Stream,(unsigned char*)&i,1,0);
					totalsize+=OutBinCodeWithPrefix_iv_for_64(Stream,(unsigned char*)&i,1,0x66);
				}
				else
				{
					totalsize+=OutBinCodeWithPrefix_iv_for_Normal(Stream,(unsigned char*)&i,1,0);
					totalsize+=OutBinCodeWithPrefix_iv_for_Normal(Stream,(unsigned char*)&i,1,0x66);
				}
			
		}
		for(int i=0x50;i<0x60;i++)
		{
			if(mode==WIN_PE64)
			{
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&i,1,0);
				totalsize+=OutBinCodeWithPrefix_for_64(Stream,(unsigned char*)&i,1,0x66);
			}
			else
			{
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&i,1,0);
				totalsize+=OutBinCodeWithPrefix_for_Normal(Stream,(unsigned char*)&i,1,0x66);
			}
		}
		int only_Iz[]={0x05,0x15,0x25,0x35,0x0d,0x1d,0x2d,0x3d,0x68,0xa9};
		for(int i=0;i<sizeof(only_Iz)/sizeof(only_Iz[0]);i++)
		{
			if(mode==WIN_PE64)
			{
				totalsize+=OutBinCodeWithPrefix_iz_for_64(Stream,(unsigned char*)&only_Iz[i],1,0);
				totalsize+=OutBinCodeWithPrefix_iz_for_64(Stream,(unsigned char*)&only_Iz[i],1,0x66);
			}
			else
			{
				totalsize+=OutBinCodeWithPrefix_iz_for_Normal(Stream,(unsigned char*)&only_Iz[i],1,0);
				totalsize+=OutBinCodeWithPrefix_iz_for_Normal(Stream,(unsigned char*)&only_Iz[i],1,0x66);
			}
		}
		int only_Ib[]={0x04,0x14,0x24,0x34,0x0c,0x1c,0x2c,0x3c,0x6a,0xa8,0xe4,0xe5,0xe6,0xe7,0xd4,0xd5,0xcd};
		for(int i=0;i<sizeof(only_Ib)/sizeof(only_Ib[0]);i++)
		{
			if(mode==WIN_PE64)
			{
				totalsize+=OutBinCodeWithPrefix_ib_for_64(Stream,(unsigned char*)&only_Ib[i],1,0);
				totalsize+=OutBinCodeWithPrefix_ib_for_64(Stream,(unsigned char*)&only_Ib[i],1,0x66);
			}
			else
			{
				totalsize+=OutBinCodeWithPrefix_ib_for_Normal(Stream,(unsigned char*)&only_Ib[i],1,0);
				totalsize+=OutBinCodeWithPrefix_ib_for_Normal(Stream,(unsigned char*)&only_Ib[i],1,0x66);
			}
		}
		
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
		
	
	int opcode_with_iz_rm[]={
		/*0x69,*/0x81
	};
	for(int i = 0 ; i<sizeof(opcode_with_iz_rm)/sizeof(opcode_with_iz_rm[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_with_iz_rm[i]&0xffff)==0x380f)||((opcode_with_iz_rm[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_with_iz_rm[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_with_iz_rm[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		if((opcode_with_iz_rm[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_iz_for_Normal,opcode_with_iz_rm[i],opcodelen,0x00);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_iz_for_64,opcode_with_iz_rm[i],opcodelen,0x66);
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_iz_for_Normal,opcode_with_iz_rm[i],opcodelen,0x00);
			if(mode==WIN_PE64)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_iz_for_64,opcode_with_iz_rm[i],opcodelen,0x66);
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_with_ib_rm[]={
		/*0x69,*/0x80,0x82,0x83
	};
	for(int i = 0 ; i<sizeof(opcode_with_ib_rm)/sizeof(opcode_with_ib_rm[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_with_ib_rm[i]&0xffff)==0x380f)||((opcode_with_ib_rm[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_with_ib_rm[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_with_ib_rm[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		if((opcode_with_ib_rm[i]&0xffff)==0x3a0f)
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_with_ib_rm[i],opcodelen,0x00);
			if(mode==WIN_PE64 && opcode_with_ib_rm[i]!=0x82)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_with_ib_rm[i],opcodelen,0x66);
		}
		else
		{
			totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_with_ib_rm[i],opcodelen,0x00);
			if(mode==WIN_PE64&& opcode_with_ib_rm[i]!=0x82)
				totalsize += opcode_creater(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_with_ib_rm[i],opcodelen,0x66);
		}
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
	int opcode_f6_f7[]={
		0xf6,0xf7
	};
	for(int i = 0 ; i<sizeof(opcode_f6_f7)/sizeof(opcode_f6_f7[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_f6_f7[i]&0xffff)==0x380f)||((opcode_f6_f7[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_f6_f7[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_f6_f7[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		if(opcode_f6_f7[i]==0xf7)
		{
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_iz_for_Normal,opcode_f6_f7[i],opcodelen,0x00,RM_0_4,0x1ff);
			if(mode==WIN_PE64)
				totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_iz_for_64,opcode_f6_f7[i],opcodelen,0x66,RM_0_4,0x1ff);

		}
		else
		{
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_f6_f7[i],opcodelen,0x00,RM_0_4,0x1ff);
			if(mode==WIN_PE64)
				totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_f6_f7[i],opcodelen,0x66,RM_0_4,0x1ff);
		}
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_f6_f7[i],opcodelen,0x00,RM_0_4,0xfcff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_f6_f7[i],opcodelen,0x66,RM_0_4,0xfcff);
		
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}


	int opcode_fe[]={
		0xfe
	};
	for(int i = 0 ; i<sizeof(opcode_fe)/sizeof(opcode_fe[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_fe[i]&0xffff)==0x380f)||((opcode_fe[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_fe[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_fe[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_fe[i],opcodelen,0x00,RM_0_4,0x3ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_fe[i],opcodelen,0x66,RM_0_4,0x3ff);
		
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_ff[]={
		0xff
	};
	for(int i = 0 ; i<sizeof(opcode_ff)/sizeof(opcode_ff[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_ff[i]&0xffff)==0x380f)||((opcode_ff[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_ff[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_ff[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_ff[i],opcodelen,0x00,RM_0_4,0x57ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_ff[i],opcodelen,0x66,RM_0_4,0x57ff);
		
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_0f00[]={
		0x000f
	};
	for(int i = 0 ; i<sizeof(opcode_0f00)/sizeof(opcode_0f00[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0f00[i]&0xffff)==0x380f)||((opcode_0f00[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0f00[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0f00[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0f00[i],opcodelen,0x00,RM_0_4,0x3fff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0f00[i],opcodelen,0x00,RM_0_4,0x3fff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0f00[i],opcodelen,0x66,RM_0_4,0x3fff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0f00[i],opcodelen,0x66,RM_0_4,0x3fff);
				
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,0x010f,2,0x00,RM_0_3,0xdfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,0x010f,2,0x00,RM_0_3,0xdfff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,0x010f,2,0x66,RM_0_3,0xdfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,0x010f,2,0x66,RM_0_3,0xdfff);

		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,0x010f,2,0x00,RM_4,0x8603);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,0x010f,2,0x00,RM_4,0x8603);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,0x010f,2,0x66,RM_4,0x8603);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,0x010f,2,0x66,RM_4,0x8603);

		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,0x010f,2,0x00,RM_4,0x11e);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,0x010f,2,0x00,RM_4,0x11e);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,0x010f,2,0x66,RM_4,0x11e);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,0x010f,2,0x66,RM_4,0x11e);
		
		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_0fba[]={
		0xba0f
	};
	for(int i = 0 ; i<sizeof(opcode_0fba)/sizeof(opcode_0fba[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0fba[i]&0xffff)==0x380f)||((opcode_0fba[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0fba[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0fba[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_0fba[i],opcodelen,0x00,RM_0_4,0xf0ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_0fba[i],opcodelen,0x00,RM_0_4,0xf0ff);

		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_0fba[i],opcodelen,0x66,RM_0_4,0xf0ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_0fba[i],opcodelen,0x66,RM_0_4,0xf0ff);

		Stream->Write(&totalsize,4,0x1c8);
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}


	int opcode_0fc7[]={
		0xc70f
	};

	for(int i = 0 ; i<sizeof(opcode_0fc7)/sizeof(opcode_0fc7[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0fc7[i]&0xffff)==0x380f)||((opcode_0fc7[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0fc7[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0fc7[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0fc7[i],opcodelen,0x00,RM_0_3,0xc2ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0fc7[i],opcodelen,0x00,RM_0_3,0xc2ff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0fc7[i],opcodelen,0x66,RM_0_3,0x42ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0fc7[i],opcodelen,0x66,RM_0_3,0x42ff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0fc7[i],opcodelen,0xf3,RM_0_3,0x40ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0fc7[i],opcodelen,0xf3,RM_0_3,0x40ff);
		
		Stream->Write(&totalsize,4,0x1c8);	
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_0xc6_0xc7[]={
		0xc6,
	};

	for(int i = 0 ; i<sizeof(opcode_0xc6_0xc7)/sizeof(opcode_0xc6_0xc7[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0xc6_0xc7[i]&0xffff)==0x380f)||((opcode_0xc6_0xc7[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0xc6_0xc7[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0xc6_0xc7[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,0xc6,1,0x00,RM_0_4,0x1ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,0xc6,1,0x00,RM_0_4,0x1ff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,0xc6,1,0x66,RM_0_4,0x1ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,0xc6,1,0x66,RM_0_4,0x1ff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_iz_for_Normal,0xc7,1,0x00,RM_0_4,0x1ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_iz_for_64,0xc7,1,0x00,RM_0_4,0x1ff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_iz_for_Normal,0xc7,1,0x66,RM_0_4,0x1ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_iz_for_64,0xc7,1,0x66,RM_0_4,0x1ff);


		Stream->Write(&totalsize,4,0x1c8);	
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}


	int opcode_0x710f_720f_730f[]={
		0x710f,0x720f,0x730f,
	};
	int opcode_0x710f_720f_730f_mask[]={
		0x54ff,0x54ff,0x44ff,
	};
	int opcode_0x710f_720f_730f_mask_66[]={
		0x54ff,0x54ff,0xccff,
	};
	for(int i = 0 ; i<sizeof(opcode_0x710f_720f_730f)/sizeof(opcode_0x710f_720f_730f[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0x710f_720f_730f[i]&0xffff)==0x380f)||((opcode_0x710f_720f_730f[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0x710f_720f_730f[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0x710f_720f_730f[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_0x710f_720f_730f[i],opcodelen,0x00,RM_4,opcode_0x710f_720f_730f_mask[i]);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_0x710f_720f_730f[i],opcodelen,0x00,RM_4,opcode_0x710f_720f_730f_mask[i]);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_0x710f_720f_730f[i],opcodelen,0x66,RM_4,opcode_0x710f_720f_730f_mask_66[i]);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_0x710f_720f_730f[i],opcodelen,0x66,RM_4,opcode_0x710f_720f_730f_mask_66[i]);
	

		Stream->Write(&totalsize,4,0x1c8);	
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_0xae0f[]={
		0xae0f,
	};

	for(int i = 0 ; i<sizeof(opcode_0xae0f)/sizeof(opcode_0xae0f[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0xae0f[i]&0xffff)==0x380f)||((opcode_0xae0f[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0xae0f[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0xae0f[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0xae0f[i],opcodelen,0x00,RM_0_3,0xbfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0xae0f[i],opcodelen,0x00,RM_0_3,0xbfff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0xae0f[i],opcodelen,0x66,RM_0_3,0xbfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0xae0f[i],opcodelen,0x66,RM_0_3,0xbfff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0xae0f[i],opcodelen,0x00,RM_4,0xe0ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0xae0f[i],opcodelen,0x00,RM_4,0xe0ff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0xae0f[i],opcodelen,0x66,RM_4,0xe0ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0xae0f[i],opcodelen,0x66,RM_4,0xe0ff);
		Stream->Write(&totalsize,4,0x1c8);	
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_0x180f[]={
		0x180f,
	};

	for(int i = 0 ; i<sizeof(opcode_0x180f)/sizeof(opcode_0x180f[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0x180f[i]&0xffff)==0x380f)||((opcode_0x180f[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0x180f[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0x180f[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0x180f[i],opcodelen,0x00,RM_0_3,0xfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0x180f[i],opcodelen,0x00,RM_0_3,0xfff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0x180f[i],opcodelen,0x66,RM_0_3,0xfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0x180f[i],opcodelen,0x66,RM_0_3,0xfff);
		Stream->Write(&totalsize,4,0x1c8);	
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	int opcode_0x8f[]={
		0x8f,
	};

	for(int i = 0 ; i<sizeof(opcode_0x8f)/sizeof(opcode_0x8f[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0x8f[i]&0xffff)==0x380f)||((opcode_0x8f[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0x8f[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0x8f[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0x8f[i],opcodelen,0x00,RM_0_4,0x1ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0x8f[i],opcodelen,0x00,RM_0_4,0x1ff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0x8f[i],opcodelen,0x66,RM_0_4,0x1ff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0x8f[i],opcodelen,0x66,RM_0_4,0x1ff);
		Stream->Write(&totalsize,4,0x1c8);	
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}
#endif

	int opcode_0xc0_0xc1[]={
		0xc0,0xc1,0xd0,0xd1,0xd2,0xd3
	};

	for(int i = 0 ; i<sizeof(opcode_0xc0_0xc1)/sizeof(opcode_0xc0_0xc1[0]);i++)
	{	
		char format[50];
		totalsize=0;
		int opcodelen;
		if(((opcode_0xc0_0xc1[i]&0xffff)==0x380f)||((opcode_0xc0_0xc1[i]&0xffff)==0x3a0f))
		{
			opcodelen=3;
			strcpy(format,"%s\\%s0x%06x.exe");
		}
		else if((opcode_0xc0_0xc1[i]&0xff)==0x0f)
		{	
			opcodelen=2;
			strcpy(format,"%s\\%s0x%04x.exe");
		}
		else
		{
			opcodelen=1;
			strcpy(format,"%s\\%s0x%02x.exe");
		}
		sprintf(filename,format,dirname,nameprefix,opcode_0xc0_0xc1[i]);
		StreamObject* Stream=new CMemoryStream(filename,"wb");
		printf("create %s\n",filename);
		Stream->Write(rawdata,512);
		if(opcode_0xc0_0xc1[i]==0xc0 || opcode_0xc0_0xc1[i]==0xc1)
		{
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_0xc0_0xc1[i],opcodelen,0x00,RM_0_4,0xbfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_0xc0_0xc1[i],opcodelen,0x00,RM_0_4,0xbfff);
		totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_Normal,opcode_0xc0_0xc1[i],opcodelen,0x66,RM_0_4,0xbfff);
		if(mode==WIN_PE64)
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_ib_for_64,opcode_0xc0_0xc1[i],opcodelen,0x66,RM_0_4,0xbfff);
		}
		else
		{
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0xc0_0xc1[i],opcodelen,0x00,RM_0_4,0xbfff);
			if(mode==WIN_PE64)
				totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0xc0_0xc1[i],opcodelen,0x00,RM_0_4,0xbfff);
			totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_Normal,opcode_0xc0_0xc1[i],opcodelen,0x66,RM_0_4,0xbfff);
			if(mode==WIN_PE64)
				totalsize += opcode_creater_2(Stream,OutBinCodeWithPrefix_for_64,opcode_0xc0_0xc1[i],opcodelen,0x66,RM_0_4,0xbfff);

		}
		Stream->Write(&totalsize,4,0x1c8);	
		newvalue=totalsize + 0x1ff -(totalsize+0x1ff)%0x200;
		Stream->Write(&newvalue,4,0x1d0);
		Stream->Write(&newvalue,4,sizecodeoffset);
		newvalue=(totalsize+0x1000-1)-(totalsize+0x1000-1)%0x1000+0x1000;
		Stream->Write(&newvalue,4,imagesizeoffset);
		delete Stream;
	}

	return 0;
}



int OutBinCodeWithPrefix_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	if(Prefix)
		Totals+=Stream->Write(&Prefix,1);
	Totals+=Stream->Write(Buf,Len);
	return Totals;
}


int OutBinCodeWithPrefix_ib_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned char ibyte[]={0,0x7f,0x80,0xff};
	for(int i=0;i<sizeof(ibyte)/sizeof(ibyte[0]);i++)
	{
		if(Prefix)
			Totals+=Stream->Write(&Prefix,1);
		Totals+=Stream->Write(Buf,Len);
		Totals+=Stream->Write(&ibyte[i],1);	
	}
	return Totals;
}

int OutBinCodeWithPrefix_iw_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned short iword[]={0,0x7fff,0x8000,0xffff};
	for(int i=0;i<sizeof(iword)/sizeof(iword[0]);i++)
	{
		if(Prefix)
			Totals+=Stream->Write(&Prefix,1);
		Totals+=Stream->Write(Buf,Len);
		Totals+=Stream->Write(&iword[i],2);	
	}
	return Totals;
}

int OutBinCodeWithPrefix_id_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned int idword[]={0,0x7fffffff,0x80000000,0xffffffff};
	for(int i=0;i<sizeof(idword)/sizeof(idword[0]);i++)
	{
		if(Prefix)
			Totals+=Stream->Write(&Prefix,1);
		Totals+=Stream->Write(Buf,Len);
		Totals+=Stream->Write(&idword[i],4);	
	}
	return Totals;
}

int OutBinCodeWithPrefix_iz_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned int idword[]={0,0x7fffffff,0x80000000,0xffffffff};
	unsigned short iword[]={0,0x7fff,0x8000,0xffff};
	for(int i=0;i<sizeof(idword)/sizeof(idword[0]);i++)
	{
		if(Prefix)
			Totals+=Stream->Write(&Prefix,1);
		Totals+=Stream->Write(Buf,Len);
		if(Prefix==0x66)
			Totals+=Stream->Write(&iword[i],2);	
		else
			Totals+=Stream->Write(&idword[i],4);	
	}
	return Totals;
}

int OutBinCodeWithPrefix_iq_for_Normal(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned __int64 iqword[]={0,0x7fffffffffffffffll,0x8000000000000000ll,0xffffffffffffffffll};
	for(int i=0;i<sizeof(iqword)/sizeof(iqword[0]);i++)
	{
		if(Prefix)
			Totals+=Stream->Write(&Prefix,1);
		Totals+=Stream->Write(Buf,Len);
		Totals+=Stream->Write(&iqword[i],1);	
	}
	return Totals;
}
int OutBinCodeWithPrefix_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	
	for(int j=0x40;j<0x50;j++)
	{
		if(Prefix)
			Totals+=Stream->Write(&Prefix,1);
		Totals+=Stream->Write(&j,1);
		Totals+=Stream->Write(Buf,Len);
	}
	return Totals;
}
int OutBinCodeWithPrefix_ib_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned char ibyte[]={0,0x7f,0x80,0xff};
	for(int i=0;i<sizeof(ibyte)/sizeof(ibyte[0]);i++)
	{
		for(int j=0x40;j<0x50;j++)
		{
			if(Prefix)
				Totals+=Stream->Write(&Prefix,1);
			Totals+=Stream->Write(&j,1);
			Totals+=Stream->Write(Buf,Len);
			Totals+=Stream->Write(&ibyte[i],1);
		}
	}
	return Totals;
}
int OutBinCodeWithPrefix_iw_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{

	int Totals=0;
	unsigned short iword[]={0,0x7fff,0x8000,0xffff};
	for(int i=0;i<sizeof(iword)/sizeof(iword[0]);i++)
	{
		for(int j=0x40;j<0x50;j++)
		{
			if(Prefix)
				Totals+=Stream->Write(&Prefix,1);
			Totals+=Stream->Write(&j,1);
			Totals+=Stream->Write(Buf,Len);
			Totals+=Stream->Write(&iword[i],2);
		}
	}
	return Totals;
}
int OutBinCodeWithPrefix_id_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned int idword[]={0,0x7fffffff,0x80000000,0xffffffff};
	for(int i=0;i<sizeof(idword)/sizeof(idword[0]);i++)
	{
		for(int j=0x40;j<0x50;j++)
		{
			if(Prefix)
				Totals+=Stream->Write(&Prefix,1);
			Totals+=Stream->Write(&j,1);
			Totals+=Stream->Write(Buf,Len);
			Totals+=Stream->Write(&idword[i],4);
		}
	}
	return Totals;
}
int OutBinCodeWithPrefix_iq_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned __int64 iqword[]={0,0x7fffffffffffffffll,0x8000000000000000ll,0xffffffffffffffffll};
	for(int i=0;i<sizeof(iqword)/sizeof(iqword[0]);i++)
	{
		for(int j=0x40;j<0x50;j++)
		{
			if(Prefix)
				Totals+=Stream->Write(&Prefix,1);
			Totals+=Stream->Write(&j,1);
			Totals+=Stream->Write(Buf,Len);
			Totals+=Stream->Write(&iqword[i],8);
		}
	}
	return Totals;
}
int OutBinCodeWithPrefix_iz_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned int idword[]={0,0x7fffffff,0x80000000,0xffffffff};
	unsigned short iword[]={0,0x7fff,0x8000,0xffff};
	for(int i=0;i<sizeof(idword)/sizeof(idword[0]);i++)
	{
		for(int j=0x40;j<0x50;j++)
		{
			if(Prefix)
				Totals+=Stream->Write(&Prefix,1);
			Totals+=Stream->Write(&j,1);
			Totals+=Stream->Write(Buf,Len);
			if(j<0x48)
			{
				if (Prefix==0x66)
					Totals+=Stream->Write(&iword[i],2);
				else
					Totals+=Stream->Write(&idword[i],4);
			}
			else
				Totals+=Stream->Write(&idword[i],4);
		}
	}
	return Totals;
}

int OutBinCodeWithPrefix_iv_for_64(CStream* Stream,unsigned char *Buf,int Len,int Prefix)
{
	int Totals=0;
	unsigned __int64 iqword[]={0,0x7fffffffffffffffll,0x8000000000000000ll,0xffffffffffffffffll};
	unsigned int idword[]={0,0x7fffffff,0x80000000,0xffffffff};
	unsigned short iword[]={0,0x7fff,0x8000,0xffff};
	for(int i=0;i<sizeof(idword)/sizeof(idword[0]);i++)
	{
		for(int j=0x40;j<0x50;j++)
		{
			if(Prefix)
				Totals+=Stream->Write(&Prefix,1);
			Totals+=Stream->Write(&j,1);
			Totals+=Stream->Write(Buf,Len);
			if(j<0x48)
			{
				if (Prefix==0x66)
					Totals+=Stream->Write(&iword[i],2);
				else
					Totals+=Stream->Write(&idword[i],4);
			}
			else
				Totals+=Stream->Write(&iqword[i],8);
		}
	}
	return Totals;
}

int opcode_creater_without_rm(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix)
{
	unsigned char Buf[16];
	int Len=0;
	char* pOpcode=(char*)&Opcode;
	char OpcodeArray[4]={pOpcode[0],pOpcode[1],pOpcode[2],pOpcode[3]};
	unsigned long totals=0;
	if(OpcodeLen>4)
		return 0;
	
	for(int ii = 0; ii < OpcodeLen;ii++)
	{
		Buf[Len++]=OpcodeArray[ii];
	}
	Buf[OpcodeLen]=0;
	totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
	Buf[OpcodeLen]=0x7f;
	totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
	Buf[OpcodeLen]=0x80;
	totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
	Buf[OpcodeLen]=0xff;
	totals+=OutputFunction(Stream,Buf,Len+1,Prefix);

	return totals;
}

int opcode_creater_without_rm_iw(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix)
{
	unsigned char Buf[16];
	int Len=0;
	char* pOpcode=(char*)&Opcode;
	char OpcodeArray[4]={pOpcode[0],pOpcode[1],pOpcode[2],pOpcode[3]};
	unsigned long totals=0;
	if(OpcodeLen>4)
		return 0;
	
	for(int ii = 0; ii < OpcodeLen;ii++)
	{
		Buf[Len++]=OpcodeArray[ii];
	}
	*(int*)&Buf[OpcodeLen]=0;
	totals+=OutputFunction(Stream,Buf,Len+2,Prefix);
	*(int*)&Buf[OpcodeLen]=0x7fff;
	totals+=OutputFunction(Stream,Buf,Len+2,Prefix);
	*(int*)&Buf[OpcodeLen]=0x8000;
	totals+=OutputFunction(Stream,Buf,Len+2,Prefix);
	*(int*)&Buf[OpcodeLen]=0xffff;
	totals+=OutputFunction(Stream,Buf,Len+2,Prefix);

	return totals;
}

int opcode_creater_without_rm_id(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix)
{
	unsigned char Buf[16];
	int Len=0;
	char* pOpcode=(char*)&Opcode;
	char OpcodeArray[4]={pOpcode[0],pOpcode[1],pOpcode[2],pOpcode[3]};
	unsigned long totals=0;
	if(OpcodeLen>4)
		return 0;
	
	for(int ii = 0; ii < OpcodeLen;ii++)
	{
		Buf[Len++]=OpcodeArray[ii];
	}
	*(int*)&Buf[OpcodeLen]=0;
	totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
	*(int*)&Buf[OpcodeLen]=0x7fffffff;
	totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
	*(int*)&Buf[OpcodeLen]=0x80000000;
	totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
	*(int*)&Buf[OpcodeLen]=0xffffffff;
	totals+=OutputFunction(Stream,Buf,Len+4,Prefix);

	return totals;
}

int opcode_creater(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix,int defaulttype)
{
	unsigned char Buf[16];
	int Mod;
	int Reg;
	int Rm;
	int ModRM;
	int Scaled;
	int Index;
	int Base;
	int Sib;
	int Len=0;
	int EndMod;
	char* pOpcode=(char*)&Opcode;
	char OpcodeArray[4]={pOpcode[0],pOpcode[1],pOpcode[2],pOpcode[3]};
	unsigned long totals=0;

	if(OpcodeLen>4)
		return 0;
	
	for(int ii = 0; ii < OpcodeLen;ii++)
	{
		Buf[Len++]=OpcodeArray[ii];
	}
	switch(defaulttype)
	{
	case RM_0_4:
		Mod=0;
		EndMod=4;
		break;
	case RM_0_3:
		Mod=0;
		EndMod=3;
		break;
	case RM_4:
		Mod=3;
		EndMod=4;
		break;
	}
	
	for(;Mod<EndMod;Mod++)
	{
		for(Reg=0;Reg<8;Reg++)
		{
			for(Rm=0;Rm<8;Rm++)
			{
				Len=OpcodeLen;
				ModRM=Rm+(Reg<<3)+(Mod<<6);
				Buf[Len++]=ModRM;

				if(Rm==4 && Mod!=3)
				{
					for(Scaled=0;Scaled<4;Scaled++)
					{
						for(Base=0;Base<8;Base++)
						{
							for(Index=0;Index<8;Index++)
							{
								Len=OpcodeLen+1;
								Sib=Base+(Index<<3)+(Scaled<<6);
								Buf[Len++]=Sib;	
								switch(Mod)
								{
								case 0:
									if(Base==5)
									{
										*(int*)(Buf+Len)=0;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
										*(int*)(Buf+Len)=0x7fffffff;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
										*(int*)(Buf+Len)=0x80000000;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
										*(int*)(Buf+Len)=0xffffffff;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									}
									else
										totals+=OutputFunction(Stream,Buf,Len,Prefix);
									break;
								case 1:
									Buf[Len]=0;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
									Buf[Len]=0x7f;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);		
									Buf[Len]=0x80;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
									Buf[Len]=0xff;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
									break;
								case 2:
									*(int*)(Buf+Len)=0;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									*(int*)(Buf+Len)=0x7fffffff;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									*(int*)(Buf+Len)=0x80000000;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									*(int*)(Buf+Len)=0xffffffff;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									break;
								case 3:
									totals+=OutputFunction(Stream,Buf,Len,Prefix);
									break;
								}//switch
							}//Base
						}//Index
					}//Scaled

				}
				else //if(Rm==4 && Mod!=3)
				{
					switch(Mod)
					{
					case 0:
						if(Rm==5)
						{
							*(int*)(Buf+Len)=0x8000000;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
							*(int*)(Buf+Len)=0x7fffffff;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
							*(int*)(Buf+Len)=0x80000000;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
							*(int*)(Buf+Len)=0x8fffffff;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						}
						else
							totals+=OutputFunction(Stream,Buf,Len,Prefix);
						break;
					case 1:
						Buf[Len]=0;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
						Buf[Len]=0x7f;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);		
						Buf[Len]=0x80;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
						Buf[Len]=0xff;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
						break;
					case 2:
						*(int*)(Buf+Len)=0;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						*(int*)(Buf+Len)=0x7fffffff;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						*(int*)(Buf+Len)=0x80000000;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						*(int*)(Buf+Len)=0xffffffff;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						break;
					case 3:
						totals+=OutputFunction(Stream,Buf,Len,Prefix);
						break;
					}
				}
			}
		}
	}
	
	return totals;
}

int opcode_creater_2(CStream* Stream,OUTPUT_BIN_FP OutputFunction,int Opcode,int OpcodeLen,int Prefix,int defaulttype,unsigned int mask)
{
	unsigned char Buf[16];
	int Mod;
	int Reg;
	int Rm;
	int ModRM;
	int Scaled;
	int Index;
	int Base;
	int Sib;
	int Len=0;
	int EndMod;
	char* pOpcode=(char*)&Opcode;
	char OpcodeArray[4]={pOpcode[0],pOpcode[1],pOpcode[2],pOpcode[3]};
	unsigned long totals=0;
	unsigned char maskvalue[]={1,2,4,8,16,32,64,128};
	unsigned int regmask=(mask>>8);
	unsigned int rmmask=mask&0xff;
	
	if(OpcodeLen>4)
		return 0;
	
	for(int ii = 0; ii < OpcodeLen;ii++)
	{
		Buf[Len++]=OpcodeArray[ii];
	}
	switch(defaulttype)
	{
	case RM_0_4:
		Mod=0;
		EndMod=4;
		break;
	case RM_0_3:
		Mod=0;
		EndMod=3;
		break;
	case RM_4:
		Mod=3;
		EndMod=4;
		break;
	}
	
	for(;Mod<EndMod;Mod++)
	{
		for(Reg=0;Reg<8;Reg++)
		{
			if((maskvalue[Reg]&regmask)==0)
				continue;
			for(Rm=0;Rm<8;Rm++)
			{
				if((maskvalue[Rm]&rmmask)==0)
					continue;
				Len=OpcodeLen;
				ModRM=Rm+(Reg<<3)+(Mod<<6);
				Buf[Len++]=ModRM;

				if(Rm==4 && Mod!=3)
				{
					for(Scaled=0;Scaled<4;Scaled++)
					{
						for(Base=0;Base<8;Base++)
						{
							for(Index=0;Index<8;Index++)
							{
								Len=OpcodeLen+1;
								Sib=Base+(Index<<3)+(Scaled<<6);
								Buf[Len++]=Sib;	
								switch(Mod)
								{
								case 0:
									if(Base==5)
									{
										*(int*)(Buf+Len)=0;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
										*(int*)(Buf+Len)=0x7fffffff;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
										*(int*)(Buf+Len)=0x80000000;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
										*(int*)(Buf+Len)=0xffffffff;
										totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									}
									else
										totals+=OutputFunction(Stream,Buf,Len,Prefix);
									break;
								case 1:
									Buf[Len]=0;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
									Buf[Len]=0x7f;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);		
									Buf[Len]=0x80;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
									Buf[Len]=0xff;
									totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
									break;
								case 2:
									*(int*)(Buf+Len)=0;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									*(int*)(Buf+Len)=0x7fffffff;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									*(int*)(Buf+Len)=0x80000000;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									*(int*)(Buf+Len)=0xffffffff;
									totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
									break;
								case 3:
									totals+=OutputFunction(Stream,Buf,Len,Prefix);
									break;
								}//switch
							}//Base
						}//Index
					}//Scaled

				}
				else //if(Rm==4 && Mod!=3)
				{
					switch(Mod)
					{
					case 0:
						if(Rm==5)
						{
							*(int*)(Buf+Len)=0x8000000;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
							*(int*)(Buf+Len)=0x7fffffff;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
							*(int*)(Buf+Len)=0x80000000;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
							*(int*)(Buf+Len)=0x8fffffff;
							totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						}
						else
							totals+=OutputFunction(Stream,Buf,Len,Prefix);
						break;
					case 1:
						Buf[Len]=0;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
						Buf[Len]=0x7f;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);		
						Buf[Len]=0x80;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
						Buf[Len]=0xff;
						totals+=OutputFunction(Stream,Buf,Len+1,Prefix);
						break;
					case 2:
						*(int*)(Buf+Len)=0;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						*(int*)(Buf+Len)=0x7fffffff;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						*(int*)(Buf+Len)=0x80000000;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						*(int*)(Buf+Len)=0xffffffff;
						totals+=OutputFunction(Stream,Buf,Len+4,Prefix);
						break;
					case 3:
						totals+=OutputFunction(Stream,Buf,Len,Prefix);
						break;
					}
				}
			}
		}
	}
	
	return totals;
}

//    Generated by Webtools from Websense's STR
//    Made by Yanfeng Wu
//    http://sbjstrweb/test_upload.html

//    Source File: nullproj.exe
//           Time: 2010-08-27 08:54
//   Orig. Offset: 0 / 00000000
//         Length: 1024 / 00000400 (bytes)

unsigned char grawData_pe64[512]=
{
	0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 
	0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB8, 0x00, 0x00, 0x00, 
	0x0E, 0x1F, 0xBA, 0x0E, 0x00, 0xB4, 0x09, 0xCD, 0x21, 0xB8, 0x01, 0x4C, 0xCD, 0x21, 0x54, 0x68, 
	0x69, 0x73, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x20, 0x63, 0x61, 0x6E, 0x6E, 0x6F, 
	0x74, 0x20, 0x62, 0x65, 0x20, 0x72, 0x75, 0x6E, 0x20, 0x69, 0x6E, 0x20, 0x44, 0x4F, 0x53, 0x20, 
	0x6D, 0x6F, 0x64, 0x65, 0x2E, 0x0D, 0x0D, 0x0A, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x13, 0x65, 0xF6, 0xD8, 0x57, 0x04, 0x98, 0x8B, 0x57, 0x04, 0x98, 0x8B, 0x57, 0x04, 0x98, 0x8B, 
	0x5E, 0x7C, 0x11, 0x8B, 0x55, 0x04, 0x98, 0x8B, 0x5E, 0x7C, 0x09, 0x8B, 0x56, 0x04, 0x98, 0x8B, 
	0x52, 0x69, 0x63, 0x68, 0x57, 0x04, 0x98, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x45, 0x00, 0x00, 0x64, 0x86, 0x01, 0x00, 
	0x7A, 0x6C, 0x77, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x23, 0x00, 
	0x0B, 0x02, 0x09, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x81, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x2E, 0x74, 0x65, 0x78, 0x74, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	
} ;


// Generated by BreakPoint Software's Hex Workshop v4.20
//   http://www.hexworkshop.com
//   http://www.bpsoft.com
//
//  Source File: nullprj.exe
//         Time: 2010-8-30 21:20
// Orig. Offset: 0 / 0x00000000
//       Length: 512 / 0x00000200 (bytes)
unsigned char grawData_pe32[512] =
{
	0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 
	0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0x00, 
	0x0E, 0x1F, 0xBA, 0x0E, 0x00, 0xB4, 0x09, 0xCD, 0x21, 0xB8, 0x01, 0x4C, 0xCD, 0x21, 0x54, 0x68, 
	0x69, 0x73, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x20, 0x63, 0x61, 0x6E, 0x6E, 0x6F, 
	0x74, 0x20, 0x62, 0x65, 0x20, 0x72, 0x75, 0x6E, 0x20, 0x69, 0x6E, 0x20, 0x44, 0x4F, 0x53, 0x20, 
	0x6D, 0x6F, 0x64, 0x65, 0x2E, 0x0D, 0x0D, 0x0A, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x75, 0x15, 0xD9, 0x45, 0x14, 0x7B, 0x8A, 0x45, 0x14, 0x7B, 0x8A, 0x45, 0x14, 0x7B, 0x8A, 
	0x4C, 0x6C, 0xFF, 0x8A, 0x44, 0x14, 0x7B, 0x8A, 0x4C, 0x6C, 0xEA, 0x8A, 0x44, 0x14, 0x7B, 0x8A, 
	0x52, 0x69, 0x63, 0x68, 0x45, 0x14, 0x7B, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x50, 0x45, 0x00, 0x00, 0x4C, 0x01, 0x01, 0x00, 
	0x32, 0xAF, 0x7B, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x03, 0x01, 
	0x0B, 0x01, 0x09, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 
	0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x85, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x2E, 0x74, 0x65, 0x78, 0x74, 0x00, 0x00, 0x00, 0x16, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x12, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
} ;
