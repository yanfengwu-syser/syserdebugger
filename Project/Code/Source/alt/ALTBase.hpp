///////////////////////////////////////////////////////////////////////////////
//ALT Base Object
//Coded by Finaldoom
//ALT基础对象
//作者：陈俊豪
///////////////////////////////////////////////////////////////////////////////
#ifndef _ALT_BASE_HPP_
#define _ALT_BASE_HPP_

#include "ALTConfig.hpp"

#ifndef NULL
#define NULL	0
#endif

#ifndef PATH_SEPARATOR_CHAR
#define PATH_SEPARATOR_CHAR     '\\'
#endif

#ifndef PATH_SEPARATOR_STR
#define PATH_SEPARATOR_STR      "\\"
#endif

ALT_NAME_SPACE_BEGIN

class ALTFileStream
{
public:
	virtual	int	Puts(void*Buffer,int Size){return 0;}
	virtual	int	Gets(void*Buffer,int Size){return 0;}
};

struct ALT_EMPTY_STRUCT
{
	int	Save(ALTFileStream&Stream){return 0;}
	int	Load(ALTFileStream&Stream){return 0;}
};

class ALTEmptyArchive
{
public:
	int	Save(ALTFileStream&Stream){return 0;}
	int	Load(ALTFileStream&Stream){return 0;}
};

template<class OBJ>
class ALTObj
{
public:
	OBJ* Construct(){return new OBJ;}
	void Destruct(OBJ*pObj){delete pObj;}
	OBJ* ConstructArray(int Count){return new OBJ[Count];}
	void DestructArray(OBJ*pObj){delete[] pObj;}
	void*ConstructPtrArray(int Count){return new void*[Count];}
	void DestructPtrArray(void*Ptr){delete[] (void**)Ptr;}
	int  Save(ALTFileStream&Stream){return 0;}
	int  Load(ALTFileStream&Stream){return 0;}
};

ALT_NAME_SPACE_END

#endif

