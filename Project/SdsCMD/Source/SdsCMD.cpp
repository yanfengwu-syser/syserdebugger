#include "StdAfx.h"
#include "SdsCMD.h"
#include "../../SyserApp/Source/AnalyseCom.h"
#include "../../SyserApp/Source/NoPDBSymbol.h"
CSdsCMD::CSdsCMD()
{

}

CSdsCMD::~CSdsCMD()
{

}

bool CSdsCMD::TranslateSymbolFile(IN PCSTR FileName,OUT PSTR SymbolFileName)
{
	bool bRet=false;
	SymbolFileName[0]=0;
	bRet = m_SourceDebug.TranslateSymbolFile((char*)FileName,(char*)SymbolFileName);
	if(bRet)
	{
		m_SourceDebug.PackedSourceFile(SymbolFileName,NULL);
	}	
	else
	{
		CNoPDBSymbol NoPDBSymbol;
		if(NoPDBSymbol.Init())
			bRet = NoPDBSymbol.TranslateSymbolFile((char*)FileName,(char*)SymbolFileName);
	}
	return bRet;
}
typedef TList<char*> FILENAMELIST;
int main(int argc,char* argv[])
{
	char SymbolFileName[512];
	char* Options[]={"-p","/p","-e","/e","-a","/a","-h","/h","-i","/i"};
	bool pOption=false,eOption=false,aOption=false,hOption=false,iOption=false;
	char* ModuleName;
	CNoPDBSymbol NoPDBSymbol;
	CSdsCMD SdsObject;
	FILENAMELIST FileList;
	FILENAMELIST::IT BeginIT,EndIT;
	int i,NameCount=0;
	if(argc==1)
	{
local_help:
		ModuleName = TStrRChr(argv[0],'\\');
		if(ModuleName==NULL)
			ModuleName=argv[0];
		else 
			ModuleName++;
		cout <<"SyserSoft SDS symbol translator version 1.0.0\n";
		cout <<"(C) SyserSoft Corporation, 2002-2005\n\n";
		cout <<ModuleName<<" "<<"[options] "<<"PE_file_name \n"<<endl;
		cout <<"options:"<<endl;
		cout <<"\t"<<"-p	Package Source with symbol file.\n";
		cout <<"\t"<<"-e	Only export symbol.\n";
		cout <<"\t"<<"-i	Only import symbol.\n";
		cout <<"\t"<<"-a	Analyzer full pdb symbol information.\n";
		cout <<"\t"<<"-h	This help.\n";
		cout <<endl;
		return 1;
	}
	for(i = 1; i < argc;i++)
	{
			if(TStrICmp("/p",argv[i])==0)
				pOption=true,argv[i]=NULL;
			else if(TStrICmp("-p",argv[i])==0)
				pOption=true,argv[i]=NULL;
			else if(TStrICmp("-e",argv[i])==0)
				eOption=true,argv[i]=NULL;
			else if(TStrICmp("/e",argv[i])==0)
				eOption=true,argv[i]=NULL;
			else if(TStrICmp("-i",argv[i])==0)
				iOption=true,argv[i]=NULL;
			else if(TStrICmp("/i",argv[i])==0)
				iOption=true,argv[i]=NULL;
			else if(TStrICmp("-a",argv[i])==0)
				aOption=true,argv[i]=NULL;
			else if(TStrICmp("/a",argv[i])==0)
				aOption=true,argv[i]=NULL;
			else if(TStrICmp("-h",argv[i])==0)
				goto local_help;
			else if(TStrICmp("/h",argv[i])==0)
				goto local_help;
			else 
			{
				FileList.Append(argv[i]);
			}
	}
	if(FileList.Count()==0)
		goto local_help;
	BeginIT = FileList.Begin();
	if(iOption || eOption)
	{
		for(;BeginIT!=FileList.End();BeginIT++)
		{
			NoPDBSymbol.SetImportSymbols(iOption);
			NoPDBSymbol.SetExportSymbols(eOption);
			if(NoPDBSymbol.Init())
				NoPDBSymbol.TranslateSymbolFile(*BeginIT,SymbolFileName);
		}
	}
	else
	{
		for(;BeginIT!=FileList.End();BeginIT++)
		{
			SdsObject.TranslateSymbolFile(*BeginIT,SymbolFileName);
		}
	}
	

	return 0;
}