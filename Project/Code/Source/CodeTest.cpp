#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <map>
#include <string>
#include <list>

using namespace std;
struct x_char_traits : public char_traits<char>
{
	static int __cdecl compare(const char *_First1, const char *_First2,size_t _Count)
	{	
		return (::memicmp(_First1, _First2, _Count));
	}
};

typedef basic_string<char,x_char_traits > istring;


typedef map<string,size_t> MAPSTR;
typedef list<string>LISTSTR;
typedef map<istring,MAPSTR> MAPFILE2ID;
typedef map<size_t,string> MAPID2STR;
void SaveFile(const char* filename,MAPFILE2ID& File2IDMap);
void Tr(MAPFILE2ID& File2IDMap);
void LoadFile(const char* filename,MAPFILE2ID& File2IDMap);
void help(char* Name)
{
	char* p=strrchr(Name,'\\');
	if(p==NULL)
		p=Name;
	fprintf(stderr,"usage: %s filename\n\n");
}

map<int,string> k1;

int print3dnow(int argc, char* argv[])
{


		map<int,string> k1;
	k1[0x90]="PFCMPGE";	
	k1[0x94]="PFMIN";	
	k1[0x96]="PFRCP";	
	k1[0x97]="PFRSQRT";	
	k1[0xa0]="PFCMPGT";	
	k1[0xa4]="PFMAX";	
	k1[0xa6]="PFRCPIT1";	
	k1[0xa7]="PFRSQIT1";

	k1[0xb0]="PFCMPEQ";	
	k1[0xb4]="PFMUL";	
	k1[0xb6]="PFRCPIT2";	
	k1[0xb7]="PMULHRW";	

	k1[0x0c]="PI2FW";	
	k1[0x0d]="PI2FD";	
	k1[0x1c]="PF2IW";	
	k1[0x1d]="PF2ID";	
	
	k1[0x8a]="PFNACC";	
	k1[0x8e]="PFPNACC";	

	k1[0x9a]="PFSUB";	
	k1[0x9e]="PFADD";	

	k1[0xaa]="PFSUBR";	
	k1[0xae]="PFACC";	
	k1[0xbb]="PSWAPD";	
	k1[0xbf]="PAVGUSB";	



	for(int i = 0 ;i<256;i++)
	{
		map<int,string>::iterator findit = k1.find(i);
		if(findit!=k1.end())
		{
			printf("{R_M, C_%s,		D__Pq,		D__Qq,		D__NONE,	\"%s\"	,0x0f0f,2|C_GROUP_3DNOW_TYPE|(0x%02x<<16)}, //0x%02x\n",findit->second.c_str(),findit->second.c_str(),i,i);
	
		}
		else
			printf("{R_M, C_NULL,		D__NONE,	D__NONE,	D__NONE,	NULL	,0x0f0f,2|C_GROUP_3DNOW_TYPE}, //0x%02x\n",i);
		if((i%8)==7)
			printf("\n");
	}
	return 0;
}

int main(int argc, char* argv[])
{

	float f1=123.876;
	double d2=123456.987;
	long double d3=0.0098423;
	char buffer[1024];
	sprintf(buffer,"%f  %g   %e\n",f1,d2,d3);
	TSPrintf(buffer,"%f  %g   %e\n",f1,d2,d3);
	return 0;
	print3dnow(argc,argv);
	return 0;
	bool bOk;
	CTXTFile TxtFile;
	char* p;
	TTXTStrList::IT BeginIT,EndIT;
	bOk=TxtFile.Open("c:\\1.txt");
	if(bOk==false)
		return 0;
	BeginIT=TxtFile.m_StrList.Begin();
	EndIT=TxtFile.m_StrList.End();
	char tmpchar;
	char*p1,*p2,*p4,*p3;
	int i=0;
	int num;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		p=*BeginIT;
		if(TStrNCmp(p,"DIS_OPCODE_T Group0x",sizeof("DIS_OPCODE_T Group0x")-1)==0)
		{
			p2=p+sizeof("DIS_OPCODE_T Group0x")-1;
			p3=p2;
			while((*p2>='0' && *p2 <='9')||(*p2>='A'&&*p2<='F') || (*p2>='a'&&*p2<='f'))
				p2++;
			tmpchar=*p2;
			*p2=0;
			SHexStrToNum(p3,&num);
			*p2=tmpchar;
			i=0;
		}
		p1=TStrChr(p,'}');
		if(p1==NULL)
			printf("%s\n",p);
		else
		{	
			p3=p1+1;
			while(*p3==' '||*p3=='\t' )p3++;
			if(*p3==';')
			{
				printf("%s\n",p);
				continue;
			}
			p2 = TStrStr(p,"C_NULL");
			if(p2)
			{
				printf("%s\n",p);
				i++;
				continue;
			}
			*p1=0;
			p2=p1;
			p2--;
			while(*p2==' '|| *p2=='\t')p2--;
			if(*p2==',')
				*p2=' ';
			printf("%s|(%d<<16)}%s\n",p,i,p1+1);

			i++;
			*p1='}';
		}
	}
	return 0;
}


int mainQAZ(int argc, char* argv[])
{
	bool bOk;
	CTXTFile TxtFile;
	char* p;
	TTXTStrList::IT BeginIT,EndIT;
	bOk=TxtFile.Open("c:\\1.txt");
	if(bOk==false)
		return 0;
	BeginIT=TxtFile.m_StrList.Begin();
	EndIT=TxtFile.m_StrList.End();
	char tmpchar;
	char*p1,*p2,*p4,*p3;
	int i=0;
	int num;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		p=*BeginIT;
		p1=TStrChr(p,'}');
		if(p1==NULL)
			printf("%s\n",p);
		else
		{	
			p3=p1+1;
			while(*p3==' '||*p3=='\t' )p3++;
			if(*p3==';')
			{
				printf("%s\n",p);
				continue;
			}
			p2 = TStrStr(p,"C_NULL");
			if(p2)
			{
				printf("%s\n",p);
				i++;
				continue;
			}
			*p1=0;
			p2=p1;
			p2--;
			while(*p2==' '|| *p2=='\t')p2--;
			if(*p2==',')
				*p2=' ';
			printf("%s|C_GRP2_GROUP_TYPE|(%d<<16)}%s\n",p,i,p1+1);

			i++;
			*p1='}';
		}
	}
	return 0;
}



int mainrt(int argc, char* argv[])
{
	bool bOk;
	CTXTFile TxtFile;
	char* p;
	TTXTStrList::IT BeginIT,EndIT;
	bOk=TxtFile.Open("c:\\1.txt");
	if(bOk==false)
		return 0;
	BeginIT=TxtFile.m_StrList.Begin();
	EndIT=TxtFile.m_StrList.End();
	char tmpchar;
	char*p1,*p2,*p4,*p3;
	int i=0;
	int num;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		p=*BeginIT;
		if(TStrNCmp(p,"DIS_OPCODE_T Group0x",sizeof("DIS_OPCODE_T Group0x")-1)==0)
		{
			p2=p+sizeof("DIS_OPCODE_T Group0x")-1;
			p3=p2;
			while((*p2>='0' && *p2 <='9')||(*p2>='A'&&*p2<='F') || (*p2>='a'&&*p2<='f'))
				p2++;
			tmpchar=*p2;
			*p2=0;
			SHexStrToNum(p3,&num);
			*p2=tmpchar;
			i=0;
		}
		p1=TStrChr(p,'}');
		if(p1==NULL)
			printf("%s\n",p);
		else
		{	
			p3=p1+1;
			while(*p3==' '||*p3=='\t' )p3++;
			if(*p3==';')
			{
				printf("%s\n",p);
				continue;
			}
			p2 = TStrStr(p,"C_NULL");
			if(p2)
			{
				printf("%s\n",p);
				i++;
				continue;
			}
			*p1=0;
			p2=p1;
			p2--;
			while(*p2==' '|| *p2=='\t')p2--;
			if(*p2==',')
				*p2=' ';
			printf("%s,0x%02x,1}%s\n",p,num&0xff,p1+1);
			
			i++;
			*p1='}';
		}
	}
	return 0;
}

int mainiuiui(int argc, char* argv[])
{
	bool bOk;
	CTXTFile TxtFile;
	char* p;
	TTXTStrList::IT BeginIT,EndIT;
	bOk=TxtFile.Open("c:\\1.txt");
	if(bOk==false)
		return 0;
	BeginIT=TxtFile.m_StrList.Begin();
	EndIT=TxtFile.m_StrList.End();
	char tmpchar;
	char*p1,*p2,*p4,*p3;
	int i=0;
	int num;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		p=*BeginIT;

		p1=TStrChr(p,'}');
		if(p1==NULL)
			printf("%s\n",p);
		else
		{	
			p3=p1+1;
			while(*p3==' '||*p3=='\t' )p3++;
			if(*p3==';')
			{
				printf("%s\n",p);
				continue;
			}
			p2 = TStrStr(p,"C_NULL");
			if(p2)
			{
				printf("%s\n",p);
				i++;
				continue;
			}
			*p1=0;
			p2=p1;
			p2--;
			while(*p2==' '|| *p2=='\t')p2--;
			if(*p2==',')
				*p2=' ';

			printf("%s,0x%02x380f,3}%s\n",p,i,p1+1);
			i++;
			*p1='}';
		}
	}
	return 0;
}

int main23k(int argc, char* argv[])
{
	bool bOk;
	CTXTFile TxtFile;
	char* p;
	TTXTStrList::IT BeginIT,EndIT;
	bOk=TxtFile.Open("c:\\1.txt");
	if(bOk==false)
		return 0;
	BeginIT=TxtFile.m_StrList.Begin();
	EndIT=TxtFile.m_StrList.End();
	char tmpchar;
	char*p1,*p2,*p4,*p3;
	int i=0;
	int num;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		p=*BeginIT;
		if(TStrNCmp(p,"DIS_OPCODE_T Group0x",sizeof("DIS_OPCODE_T Group0x")-1)==0)
		{
			p2=p+sizeof("DIS_OPCODE_T Group0x")-1;
			p3=p2;
			while((*p2>='0' && *p2 <='9')||(*p2>='A'&&*p2<='F') || (*p2>='a'&&*p2<='f'))
				p2++;
			tmpchar=*p2;
			*p2=0;
			SHexStrToNum(p3,&num);
			*p2=tmpchar;
			i=0;
		}
		p1=TStrChr(p,'}');
		if(p1==NULL)
			printf("%s\n",p);
		else
		{	
			p3=p1+1;
			while(*p3==' '||*p3=='\t' )p3++;
			if(*p3==';')
			{
				printf("%s\n",p);
				continue;
			}
			p2 = TStrStr(p,"C_NULL");
			if(p2)
			{
				printf("%s\n",p);
				i++;
				continue;
			}
			*p1=0;
			p2=p1;
			p2--;
			while(*p2==' '|| *p2=='\t')p2--;
			if(*p2==',')
				*p2=' ';

			printf("%s,0x%02x%02x,2}%s\n",p,num&0xff,(num>>8)&0xff,p1+1);
			i++;
			*p1='}';
		}
	}
	return 0;
}

int mainopop(int argc, char* argv[])
{
	bool bOk;
	CTXTFile TxtFile;
	char* p;
	TTXTStrList::IT BeginIT,EndIT;
	bOk=TxtFile.Open("c:\\1.txt");
	if(bOk==false)
		return 0;
	BeginIT=TxtFile.m_StrList.Begin();
	EndIT=TxtFile.m_StrList.End();
	char tmpchar;
	char*p1,*p2,*p4,*p3;
	int i=0;
	int num;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		p=*BeginIT;
		if(TStrNCmp(p,"DIS_OPCODE_T Group0x",sizeof("DIS_OPCODE_T Group0x")-1)==0)
		{
			p2=p+sizeof("DIS_OPCODE_T Group0x")-1;
			p3=p2;
			while((*p2>='0' && *p2 <='9')||(*p2>='A'&&*p2<='F') || (*p2>='a'&&*p2<='f'))
				p2++;
			tmpchar=*p2;
			*p2=0;
			SHexStrToNum(p3,&num);
			*p2=tmpchar;
			i=0;
		}
		p1=TStrChr(p,'}');
		if(p1==NULL)
			printf("%s\n",p);
		else
		{	
			p3=p1+1;
			while(*p3==' '||*p3=='\t' )p3++;
			if(*p3==';')
			{
				printf("%s\n",p);
				continue;
			}
			p2 = TStrStr(p,"C_NULL");
			if(p2)
			{
				printf("%s\n",p);
				i++;
				continue;
			}
				*p1=0;
				p2=p1;
				p2--;
			while(*p2==' '|| *p2=='\t')p2--;
			if(*p2==',')
				*p2=' ';
			switch(i%4)
			{
			case 0:
				printf("%s,0x%02x%02x,2}%s\n",p,num&0xff,(num>>8)&0xff,p1+1);
				break;
			case 1:
				printf("%s,0x%02x%02x66,3}%s\n",p,num&0xff,(num>>8)&0xff,p1+1);
				break;
			case 2:
				printf("%s,0x%02x%02xf2,3}%s\n",p,num&0xff,(num>>8)&0xff,p1+1);
				break;
			case 3:
				printf("%s,0x%02x%02xf3,3}%s\n",p,num&0xff,(num>>8)&0xff,p1+1);
				break;
			}
			i++;
			*p1='}';
		}
	}
	return 0;
}
int main1111(int argc, char* argv[])
{
	int FileID=0; 
	CTXTFile TxtFile;
	bool bOk;
	FILE* fp;
	int j,i;
	size_t m;
	char filename[4096];
	char* p,*p2,*p4,*p5;
	MAPSTR StrMap;
	LISTSTR StrList;
	MAPFILE2ID File2IDMap;
	pair<MAPFILE2ID::iterator,bool> pr1;
	pair<MAPSTR::iterator,bool> pr;
	unsigned char* p1,*p3;
	if(argc!=2)
	{
		help(argv[0]);
		return 1;
	}
	GetModulePath(filename);
	strcat(filename,"tmp.txt");
	fp=fopen(filename,"w");
	TTXTStrList::IT BeginIT,EndIT;
	bOk=TxtFile.Open(argv[1]);
	if(bOk==false)
		return 0;
	BeginIT=TxtFile.m_StrList.Begin();
	EndIT=TxtFile.m_StrList.End();
	char tmpchar;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		p=*BeginIT;
		p4=p;
		for(j=0;j!=2;p++)
		{
			if(*p==0)
				break;
			if(*p==':')
				j++;			
		}
		if(*p==0)
			continue;
		p5=p-1;
		while(*p5!='(')p5--;
		*p5=0;
		if(strncmp(p,"#include",8)==0)
		{			
			continue;
		}
		p1=(unsigned char*)p;
		//for(;*p1;p1++)
		//{
		//	if(*p1>0x7f)
		//		break;
		//}
		//if(*p1==0)
		//{			
		//	continue;
		//}
		while(*p)
		{
local_001:
			while(*p!='"' && *p)p++;
			if(*p==0)
				break;
			p2=p+1;
local_002:
			while(*p2!='"')p2++;		
			p2--;
			i=0;
			while(*p2=='\\')i++,p2--;
			if((i%2)==0)			
			{
				p2=p2+i+2;
				tmpchar=*p2;
				*p2=0;
				//p3=(unsigned char*)p;
				//for(;*p3;p3++)
				//{
				//	if(*p3>0x7f)
				//		break;
				//}
				//if(*p3!=0)
				{
					while((*p4==' ' || *p4=='\t') && *p4)p4++;
					pr1=File2IDMap.insert(MAPFILE2ID::value_type(p4,MAPSTR()));
					pr = pr1.first->second.insert(MAPSTR::value_type(p,1));
					if(pr.second==false)
					{
						pr.first->second++;
						m=pr.first->second;
					}
					pr = StrMap.insert(MAPSTR::value_type(p,0));
					if(pr.second==true)
						StrList.push_back(p);
				}
				*p2=tmpchar;
				p=p2;
				goto local_001;
			}
			else
			{
				p2=p2+i+2;
				goto local_002;
			}
		}			
	}
	LISTSTR::iterator BIT,EIT;
	BIT=StrList.begin();
	EIT=StrList.end();
	for(;BIT!=EIT;BIT++)
	{
		p2=(char*)BIT->c_str();
		fputs(p2,fp);
		fprintf(fp,"\n");
	}
	TxtFile.Close();
	fclose(fp);
	StrList.clear();
	StrMap.clear();
	SaveFile("dump.txt",File2IDMap);
	Tr(File2IDMap);
	return 0;
}

void SaveFile(const char* filename,MAPFILE2ID& File2IDMap)
{
	size_t m;
	FILE*fp;
	char FileName[8192];
	GetModulePath(FileName);
	strcat(FileName,filename);
	fp=fopen(FileName,"w+b");
	MAPFILE2ID::iterator FBIT,FEIT;
	size_t count=File2IDMap.size();
	fwrite(&count,1,sizeof(count),fp);
	MAPSTR::iterator StrBIT,StrEIT;
	FBIT=File2IDMap.begin();
	FEIT=File2IDMap.end();
	for(;FBIT!=FEIT;FBIT++)
	{
		fputs(FBIT->first.c_str(),fp);	
		count=FBIT->second.size();
		fwrite(&count,1,sizeof(count),fp);
		StrBIT=FBIT->second.begin();
		StrEIT=FBIT->second.end();
		for(;StrBIT!=StrEIT;StrBIT++)
		{
			m=StrBIT->second;
			fwrite(&m,1,sizeof(m),fp);
			fputs(StrBIT->first.c_str(),fp);
		}
	}
	fclose(fp);
}
void LoadFile(const char* filename,MAPFILE2ID& File2IDMap)
{
	
	size_t i,j,ii,jj,kk;
	FILE*fp;
	char FileName[8192];
	GetModulePath(FileName);
	char* p;
	pair<MAPFILE2ID::iterator,bool> pr1;
	strcat(FileName,"dump.txt");
	fp=fopen(FileName,"rb");
	i=fread(&ii,1,sizeof(ii),fp);
	for(i=0;i<ii;i++)
	{
		p=fgets(FileName,sizeof(FileName),fp);
		pr1 = File2IDMap.insert(MAPFILE2ID::value_type(p,MAPSTR()));
		fread(&jj,1,sizeof(jj),fp);
		for(j=0;j<jj;j++)
		{
			fread(&kk,1,sizeof(kk),fp);
			p=fgets(FileName,sizeof(FileName),fp);
			pr1.first->second.insert(MAPSTR::value_type(p,kk));
		}
	}
	fclose(fp);
}
typedef struct _POSINFO
{
	unsigned char* pBuf;
	unsigned char* pEnd;
	size_t nLen;
	bool bTr;
}POSINFO,*PPOSINFO;
typedef list<POSINFO> LISTPOSINFO;
typedef list<unsigned char*> LISTDELETE;
void Tr(MAPFILE2ID& File2IDMap)
{
	char ModulePath[4096];
	int ModulePathLen;
	MAPFILE2ID::iterator FBIT,FEIT;
	FBIT=File2IDMap.begin();
	const char* filename;
	size_t m,mm;
	char loadbuf[200]="LoadString(";
	FEIT=File2IDMap.end();
	MAPSTR::iterator BeginIT,EndIT;
	FILE* fp;
	MAPSTR mapstr;
	size_t CurID=101;
	size_t StringID;
	unsigned char* buf,*p2,*p8,*pa,*pb,*pc;
	pair<MAPSTR::iterator,bool> pr;
	LISTPOSINFO PosinfoList;
	POSINFO  PosInfo;
	LISTDELETE DeleteList;
	LISTPOSINFO::iterator PosBeginIT,PosEndIT,OrgBeginIT;
	ModulePathLen=GetModulePath(ModulePath);
	for(;FBIT!=FEIT;FBIT++)
	{		
		filename=FBIT->first.c_str();
		p2=(unsigned char*)strrchr(filename,'\\');
		p2++;
		if(stricmp((char*)p2,"washnote.cpp")==0)
			continue;
		printf("tr %s\n",filename);		
		fp=fopen(filename,"rb");
		if(fp==NULL)
			continue;
		if(fseek(fp,0,SEEK_END)!=0)
			fprintf(stderr,"error: fseek(\"%s\"\n",FBIT->first.c_str());
		long len=ftell(fp);
		buf=new unsigned char[len];
		fseek(fp,0,SEEK_SET);
		size_t readlen=fread(buf,1,len,fp);
		if(readlen!=len)
		{
			fprintf(stderr,"error: fread read bytes [%d],file full size [%d] \"%s\"\n",readlen,len,FBIT->first.c_str());
			len=(long)readlen;
		}
		fclose(fp);
		BeginIT = FBIT->second.begin();
		EndIT=FBIT->second.end();
		/* 插入原始文件内容到列表 */
		PosinfoList.clear();
		PosInfo.pBuf=buf;
		PosInfo.nLen= len;
		PosInfo.bTr=false;
		PosInfo.pEnd=buf+len;
		PosinfoList.push_back(PosInfo);
		bool bInsert;
		for(;BeginIT!=EndIT;BeginIT++)
		{
			const char* matchstr=BeginIT->first.c_str();
			pr=mapstr.insert(MAPSTR::value_type(matchstr,CurID));
			if(pr.second)
			{
				StringID=CurID;
				CurID++;
			}
			else
			{
				StringID=pr.first->second;
			}
			int trlen = sprintf(loadbuf,"LoadString(IDS_STRING_%d)",StringID);
			p8=new unsigned char[trlen+1];			
			strcpy((char*)p8,loadbuf);
			DeleteList.push_back(p8);
			mm = BeginIT->second;
			char* p5=(char*)BeginIT->first.c_str();
			int l= (int)BeginIT->first.length();
			
			PosBeginIT=PosinfoList.begin();
			PosEndIT=PosinfoList.end();
			
			for(m=0;PosBeginIT!=PosinfoList.end();PosBeginIT++)
			{
				if(PosBeginIT->bTr)
					continue;
				char* pk=(char*)PosBeginIT->pBuf;
				size_t nk=PosBeginIT->nLen;
				p2=(unsigned char*)MemSearch(pk,(int)nk,p5,l);
				if(p2==NULL)
					continue;
				m++;
				if(m>mm)
					break;
				OrgBeginIT=PosBeginIT;
				if(p2==PosBeginIT->pBuf)  //如果在串的开始就匹配到则把替换的串插在前面
				{
					bInsert=(p2+l!=PosBeginIT->pEnd);//判断是否为整行替换
					if(bInsert)
					{
						PosInfo.pBuf=p2+l;
						PosInfo.pEnd=PosBeginIT->pEnd;
						PosInfo.bTr=false;
						PosInfo.nLen=*(size_t*)&PosInfo.pEnd-*(size_t*)&PosInfo.pBuf;
					}					
					PosBeginIT->pBuf=p8;
					PosBeginIT->nLen=trlen;
					PosBeginIT->pEnd=p8+trlen;
					PosBeginIT->bTr=true;
					if(bInsert)
					{
						pa=PosBeginIT->pBuf;
						PosBeginIT++;
						PosinfoList.insert(PosBeginIT,PosInfo);						
					}
				}
				else
				{			
					bInsert=(p2+l!=PosBeginIT->pEnd);	
					unsigned char* pEnd;
					pEnd=PosBeginIT->pEnd;
					PosBeginIT->nLen=*(size_t*)&p2-*(size_t*)&PosBeginIT->pBuf;
					PosBeginIT->bTr=false;
					PosInfo.pBuf=p8;
					PosInfo.nLen=trlen;
					PosInfo.pEnd=p8+trlen;
					PosInfo.bTr=true;					
					PosBeginIT++;
					PosinfoList.insert(PosBeginIT,PosInfo);	
					PosBeginIT--;
					if(bInsert)
					{
						PosInfo.pBuf=p2+l;
						PosInfo.pEnd=pEnd;
						PosInfo.nLen=*(size_t*)&PosInfo.pEnd-*(size_t*)&PosInfo.pBuf;
						PosInfo.bTr=false;
						PosBeginIT++;
						PosinfoList.insert(PosBeginIT,PosInfo);
					}					
					OrgBeginIT->pEnd=OrgBeginIT->pBuf+OrgBeginIT->nLen;
				}						
				PosBeginIT = OrgBeginIT;
				if(m==mm)
					break;
			}
			
		}
		PosBeginIT=PosinfoList.begin();
		PosEndIT=PosinfoList.end();
		fp=fopen(FBIT->first.c_str(),"wb");
		for(m=0;PosBeginIT!=PosEndIT;PosBeginIT++)
		{
			fwrite(PosBeginIT->pBuf,1,PosBeginIT->nLen,fp);
		}
		fclose(fp);
		LISTDELETE::iterator DelBIT,DelEIT;// DeleteList;
		DelBIT = DeleteList.begin();
		DelEIT=DeleteList.end();
		for(;DelBIT!=DelEIT;DelBIT++)
		{
			delete []*DelBIT;
		}
		DeleteList.clear();
	}
	
	BeginIT=mapstr.begin();
	EndIT=mapstr.end();
	FILE* fp1;
	strcat(ModulePath,"strtab.rc");
	fp=fopen(ModulePath,"w");	
	fprintf(fp,"STRINGTABLE\nBEGIN\n");
	MAPID2STR Id2String;
	for(;BeginIT!=EndIT;BeginIT++)
	{
		Id2String.insert(MAPID2STR::value_type(BeginIT->second,BeginIT->first.c_str()));				
	}	
	ModulePath[ModulePathLen]=0;
	strcat(ModulePath,"stringtable.h");
	fp1=fopen(ModulePath,"w");
	MAPID2STR::iterator ID2StrBIT,ID2StrEIT;
	ID2StrBIT=Id2String.begin();
	ID2StrEIT=Id2String.end();
	for(m=0;ID2StrBIT!=ID2StrEIT;ID2StrBIT++,m++)
	{		
		if(m==20)
		{
			fprintf(fp,"END\n\nSTRINGTABLE\nBEGIN\n");
			m=0;
		}
		fprintf(fp1,"#define IDS_STRING_%d\t\t\t\t%s\n",ID2StrBIT->first,ID2StrBIT->second.c_str());	
		fprintf(fp,"\tIDS_STRING_%d\t\t%s\n",ID2StrBIT->first,ID2StrBIT->second.c_str());
	}
	fprintf(fp,"END\n");
	fclose(fp);
	fclose(fp1);
}

