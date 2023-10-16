#include "StdAfx.h"
#include "DebugNewAlloc.h"
#include "NewAlloc.h"

#ifdef CODE_DEBUG_ALLOC


#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

void* __cdecl operator new(size_t size,char*FileName,int Line)
{
	return CodeDebugAlloc(size,FileName,Line);
}

void* __cdecl operator new[](size_t size,char*FileName,int Line)
{
	return CodeDebugAlloc(size,FileName,Line);
}

void __cdecl operator delete(void*p,char*FileName,int Line)
{
	CodeDebugFree(p);
}

void __cdecl operator delete[](void*p,char*FileName,int Line)
{
	CodeDebugFree(p);
}

void  __cdecl operator delete(void*p)
{
	CodeDebugFree(p);
}

void  __cdecl operator delete[](void*p)
{
	CodeDebugFree(p);
}

NAME_SPACE_BEGIN
class CMemoryAllocateMonite
{
	size_t m_MaxMemBytesUsed;
	size_t m_MemBytesUsed;
	struct CODE_MEMORY_BLOCK
	{
		const char*	FileName;
		int		Line;
		size_t	Size;
	};
	typedef TMap<void*,CODE_MEMORY_BLOCK> TMemBlkMap;
	TMemBlkMap m_MemoryBlock;
public:
	CMemoryAllocateMonite();
	~CMemoryAllocateMonite();
public:
	void InsertBlock(const char*FileName,int Line,void*p,size_t size);
	void RemoveBlock(void*p);
	void Report();
};

int	 gNewCount = 0;
extern int gMainHeapSize;
CMemoryAllocateMonite*gpMemoryAllocateMonite = NULL;

void*CodeDebugAlloc(size_t size,char*FileName,int Line)
{
	void*p=CodeAlloc(size);
	if(gMainHeapSize)
	{
		if(gNewCount==0)
			gpMemoryAllocateMonite = new CMemoryAllocateMonite;
		gNewCount++;
		if(gpMemoryAllocateMonite)
			gpMemoryAllocateMonite->InsertBlock(FileName,Line,p,size);
	}
	return p;
}

void CodeDebugFree(void*p)
{
	if(p)
		CodeFree(p);
	if(gpMemoryAllocateMonite && gMainHeapSize)
		gpMemoryAllocateMonite->RemoveBlock(p);
}

void MemoryAllocMoniteReport()
{
	if(gpMemoryAllocateMonite)
	{
		gpMemoryAllocateMonite->Report();
		delete gpMemoryAllocateMonite;
	}
	else
	{
		CODE_DEBUG_OUTPUT("---------------------------------------------------------------------------\n");
		CODE_DEBUG_OUTPUT("程序未调用new\n");
		CODE_DEBUG_OUTPUT("---------------------------------------------------------------------------\n");
	}
}

CMemoryAllocateMonite::CMemoryAllocateMonite()
{
	m_MemBytesUsed = m_MaxMemBytesUsed = 0;
	InitMemoryAllocMonite();
}

CMemoryAllocateMonite::~CMemoryAllocateMonite()
{
	gpMemoryAllocateMonite = NULL;
	ReleaseMemoryAllocMonite();
}

void CMemoryAllocateMonite::InsertBlock(const char*FileName,int Line,void*p,size_t size)
{
	gpMemoryAllocateMonite = NULL;//忽略CMemoryAllocateMonite的new delete
	CODE_MEMORY_BLOCK MemoryBlock;
	MemoryBlock.FileName = FileName;
	MemoryBlock.Size = size;
	MemoryBlock.Line = Line;
	m_MemoryBlock.InsertUnique(p,MemoryBlock);
	m_MemBytesUsed+=size;
	if(m_MemBytesUsed>m_MaxMemBytesUsed)
		m_MaxMemBytesUsed=m_MemBytesUsed;
	gpMemoryAllocateMonite = this;//重新监视所有new delete
}

void CMemoryAllocateMonite::RemoveBlock(void*p)
{
	gpMemoryAllocateMonite = NULL;
	TMemBlkMap::IT Iter = m_MemoryBlock.Find(p);
	if(Iter!=m_MemoryBlock.End())
	{
		m_MemBytesUsed-=Iter->Size;
		m_MemoryBlock.Remove(Iter);
	}
	gpMemoryAllocateMonite = this;
}

void CMemoryAllocateMonite::Report()
{
	char szBuffer[0x200];
	int Count = m_MemoryBlock.Count();
	CODE_DEBUG_OUTPUT("---------------------------------------------------------------------------\n");
	TSPrintf(szBuffer,"内存使用峰值大小 %d 个字节\n",m_MaxMemBytesUsed);
	CODE_DEBUG_OUTPUT(szBuffer);
	if(Count==0)
	{
		CODE_DEBUG_OUTPUT("没有发现内存泄漏！\n");
		TSPrintf(szBuffer,"申请分配%d次内存\n",gNewCount);
		CODE_DEBUG_OUTPUT(szBuffer);
		CODE_DEBUG_OUTPUT(
				"(`----/`)____----^^^^^-__\n"
				" `6__6 )    `-_  (     )_`-___-`)\n"
				" (_Y_ )   __)    |____/  ``-__-/\n"
				"  /--_--_/  /--__/ __/\n"
				"(TT)   (TT)  (T(T_)\n"
				);
	}
	else
	{
		TSPrintf(szBuffer,"发现%d条内存泄漏记录！！！！\n内存泄漏信息列表\n",Count);
		CODE_DEBUG_OUTPUT(szBuffer);
		size_t size=0;
		int Display = 10;
		for(TMemBlkMap::IT Iter = m_MemoryBlock.Begin();Iter!=m_MemoryBlock.End();Iter++)
		{			
			size+=Iter->Size;
			if(Display>0)
			{
				int Length;
				BYTE Buffer[0x10];
				char szBuffer1[0x100],szBuffer2[0x100];
				Length = MIN(0x10,(int)Iter->Size);
				TMemCpy(Buffer,(BYTE*)Iter.Key(),Length);
				THexBytesToASCII(Buffer,szBuffer1,Length);
				THexBytesToStr(Buffer,szBuffer2,Length,1," ");
				TSPrintf(szBuffer,"%s (%d) 大小 [%d],地址 [%p] ASCII [%s] 字节 [%s]\n",Iter->FileName,Iter->Line,Iter->Size,Iter.Key(),szBuffer1,szBuffer2);
				CODE_DEBUG_OUTPUT(szBuffer);
				Display--;
			}
			else if(Display==0)
			{
				CODE_DEBUG_OUTPUT("........显示前10条记录\n");
				Display--;
			}
		}
		TSPrintf(szBuffer,"内存泄漏总大小 %d 个字节\n",size);
		CODE_DEBUG_OUTPUT(szBuffer);
	}
	CODE_DEBUG_OUTPUT("---------------------------------------------------------------------------\n");
}

NAME_SPACE_END

#endif
