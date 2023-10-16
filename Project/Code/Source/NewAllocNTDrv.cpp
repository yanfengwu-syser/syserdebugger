#include "stdafx.h"
#include "NewAlloc.h"


NAME_SPACE_BEGIN
#ifdef CODE_OS_NT_DRV

#ifdef CODE_ALLOC_USER_HEAP

CFixedHeap*	gpUserHeap[MAX_USER_HEAP_COUNT];
int	gMainHeapSize = CODE_ALLOC_USER_HEAP;
int	gCurUserHeapIndex = 0;
int	gMaxUserHeapCount = 0;


void InitMemoryAllocUserHeap()
{
}

void ReleaseMemoryAllocUserHeap()
{
	int AllocCount,NeverUsedSizeK;
	if(gMaxUserHeapCount==0)
		return;
	AllocCount = 0;
	NeverUsedSizeK = 0;
	for(int n=0;n<gMaxUserHeapCount;n++)
	{
		if(gpUserHeap[n]==NULL)continue;
		AllocCount+=gpUserHeap[n]->m_AllocateCount;
		NeverUsedSizeK+=gpUserHeap[n]->m_MinFreeChunkCount*CHUNK_SIZE/1024;
	}
	for(int n = gMaxUserHeapCount-1;n>0;n--)
	{
		gMaxUserHeapCount--;
		if(gpUserHeap[n]==NULL)continue;
		gpUserHeap[n]->Destroy();
		delete gpUserHeap[n];
		gpUserHeap[n]=NULL;
	}
#ifdef  CODE_DEBUG_ALLOC
	MemoryAllocMoniteReport();
#endif
	gMaxUserHeapCount--;
	gpUserHeap[0]->Destroy();
	gMainHeapSize = 0;
	delete gpUserHeap[0];
	gpUserHeap[0] = NULL;
}

void*CodeAlloc(size_t size)
{
	if(gMainHeapSize < sizeof(CFixedHeap))
	{
		return ExAllocatePoolWithTag(NonPagedPool,size,'CODE');
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
	void*p = gpUserHeap[gCurUserHeapIndex]->Allocate((ULSIZE)size);
	if(p==NULL)
		KeBugCheckEx('MEMN',size,gCurUserHeapIndex,gMainHeapSize,(ULONG_PTR)&gpUserHeap[0]);
	return p;
}

void CodeFree(void*p)
{
	if(gMainHeapSize < sizeof(CFixedHeap))
	{
		ExFreePool(p);
		return;
	}
	for(int n=0;n<gMaxUserHeapCount;n++)
	{
		if(gpUserHeap[n] && gpUserHeap[n]->Free(p))
			return;
	}
	DbgPrint("************ Invaild Free (%08X) !\n************",p);
}

#else   //CODE_ALLOC_USER_HEAP

void*CodeAlloc(size_t size)
{
	return ExAllocatePool(NonPagedPool, size);
}

void CodeFree(void*p)
{
	ExFreePool(p);
}

#endif   //CODE_ALLOC_USER_HEAP


#endif   //CODE_OS_NT_DRV

NAME_SPACE_END
