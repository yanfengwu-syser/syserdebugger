#include "StdAfx.h"
#include "NewAlloc.h"

#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif

#ifdef CODE_ALLOC_USER_HEAP

#include "Heap.h"

CFixedHeap*gpUserHeap = NULL;
bool bInCode = false;

void InitMemoryAllocUserHeap()
{
}

void ReleaseMemoryAllocUserHeap()
{
}

void*CodeAlloc(size_t size)
{
	if(bInCode)
	{
		return malloc(size);
	}
	else
	{
		void*p;
		bInCode = true;
		if(gpUserHeap==NULL)
		{
			InitMemoryAllocUserHeap();
			gpUserHeap = new CFixedHeap;
			gpUserHeap->Create(CODE_ALLOC_USER_HEAP);
		}
		p = gpUserHeap->Allocate(size);
		bInCode = false;
		return p;
	}
}

void CodeFree(void*p)
{
	if(bInCode)
	{
		return free(p);
	}
	else
	{
		bInCode = true;
		gpUserHeap->Free(p);
		bInCode = false;		
	}
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

