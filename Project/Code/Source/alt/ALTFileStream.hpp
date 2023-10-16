#ifndef _ALT_FILE_STREAM_HPP
#define _ALT_FILE_STREAM_HPP

#include <stdio.h>

ALT_NAME_SPACE_BEGIN

class CALTFileStream : public ALTFileStream
{
public:
	FILE*m_hFile;
	bool Open(const char*Filename)
	{
#if		_MSC_VER >=1400 
		return 	fopen_s(&m_hFile,Filename,"rb")==0;
#else
		m_hFile = fopen(Filename,"rb");
		return m_hFile!=NULL;
#endif
	}
	bool Create(const char*Filename)
	{
#if		_MSC_VER >=1400 
	return fopen_s(&m_hFile,Filename,"w+b")==0;
#else
		m_hFile = fopen(Filename,"w+b");
		return m_hFile!=NULL;
#endif
	}
	void Close(){fclose(m_hFile);}
	virtual int Seek(LONG FilePtr){ return fseek(m_hFile,FilePtr,SEEK_SET);}
	virtual	int	Puts(void*Buffer,int Size){return (int)fwrite(Buffer,1,Size,m_hFile);}
	virtual	int	Gets(void*Buffer,int Size){return (int)fread(Buffer,1,Size,m_hFile);}
};

ALT_NAME_SPACE_END

#endif
