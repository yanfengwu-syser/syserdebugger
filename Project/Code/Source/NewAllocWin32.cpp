#include "StdAfx.h"
#include "NewAlloc.h"
#include "Heap.h"

NAME_SPACE_BEGIN

#ifdef CODE_ALLOC_USER_HEAP

CFixedHeap*	gpUserHeap[MAX_USER_HEAP_COUNT];
int	gMainHeapSize = CODE_ALLOC_USER_HEAP;
int	gCurUserHeapIndex = 0;
int	gMaxUserHeapCount = 0;

typedef void (__cdecl *_PVFV)(void);
extern "C"
{
	extern _PVFV *__onexitbegin;
	extern _PVFV *__onexitend;
}

void InitMemoryAllocUserHeap()
{
	atexit(ReleaseMemoryAllocUserHeap);
	_PVFV * pf = __onexitend;
	pf--;
	_PVFV fBackup = *pf;
	while(pf>__onexitbegin)
	{
		pf--;
		pf[1] = pf[0];
	}
	*pf=fBackup;
}

void ReleaseMemoryAllocUserHeap()
{
	char szBuffer[256];
	int AllocCount,NeverUsedSizeK;
	if(gMaxUserHeapCount==0)
		return;
	AllocCount = 0;
	NeverUsedSizeK = 0;
	for(int n=0;n<gMaxUserHeapCount;n++)
	{
		AllocCount+=gpUserHeap[n]->m_AllocateCount;
		NeverUsedSizeK+=gpUserHeap[n]->m_MinFreeChunkCount*CHUNK_SIZE/1024;
	}
	TSPrintf(szBuffer,"分配次数 = %d , 未使用过的堆空间 = %d(k)\n",AllocCount,NeverUsedSizeK);
	CODE_DEBUG_OUTPUT(szBuffer);
	for(int n = gMaxUserHeapCount-1;n>0;n--)
	{
		gMaxUserHeapCount--;
		gpUserHeap[n]->Destroy();
		delete gpUserHeap[n];
		gpUserHeap[n]=NULL;
	}
#ifdef  CODE_DEBUG_ALLOC
	MemoryAllocMoniteReport();
#endif
	gMaxUserHeapCount--;
	gpUserHeap[0]->Destroy();
	delete gpUserHeap[0];
	gpUserHeap[0] = NULL;
}

void*CodeAlloc(size_t size)
{
	if(gMainHeapSize < sizeof(CFixedHeap))
	{
		return malloc(size);
	}
	if(gpUserHeap[gCurUserHeapIndex]==NULL)
	{
		int OldSize;
		InitMemoryAllocUserHeap();
		OldSize = gMainHeapSize;
		gMainHeapSize = 0;
		gpUserHeap[gCurUserHeapIndex] = new CFixedHeap;
		gMainHeapSize = OldSize;
		gpUserHeap[gCurUserHeapIndex]->Create(OldSize);
		gMaxUserHeapCount++;
	}
	return gpUserHeap[gCurUserHeapIndex]->Allocate((ULSIZE)size);
}

void CodeFree(void*p)
{
	if(gMainHeapSize < sizeof(CFixedHeap))
	{
		free(p);
		return;
	}
	for(int n=0;n<gMaxUserHeapCount;n++)
	{
		if(gpUserHeap[n]->Free(p))
			return;
	}
	free(p);
}

#else

void*CodeAlloc(size_t size)
{
	return malloc(size);
}

void CodeFree(void*p)
{
	free(p);
}

#endif//CODE_ALLOC_USER_HEAP

NAME_SPACE_END
