#include "StdAfx.h"
#include "NewAlloc.h"

#ifdef CODE_ALLOC_OVERLOAD

#ifdef new
#undef new
#endif

void* __cdecl operator new(size_t size)
{
	return CodeAlloc(size);
}

void* __cdecl operator new[](size_t size)
{
	return CodeAlloc(size);
}

#ifndef CODE_DEBUG_ALLOC

#ifdef delete
#undef delete
#endif

void __cdecl operator delete(void*p)
{
	CodeFree(p);
}

void __cdecl operator delete[](void*p)
{
	CodeFree(p);
}


#endif//CODE_DEBUG_ALLOC

#endif//CODE_ALLOC_OVERLOAD

#ifdef CODE_ALLOC_USER_HEAP

void SwitchHeap(int Index)
{
	if(Index < gMaxUserHeapCount)
		gCurUserHeapIndex = Index;
}
int GetCurrentHeapIndex()
{
	return gCurUserHeapIndex;
}
CFixedHeap* GetCurrentHeap()
{
	return gpUserHeap[gCurUserHeapIndex];
}
CFixedHeap* GetHeapByIndex(int Index)
{
	if(Index < gMaxUserHeapCount)
		return gpUserHeap[Index];
	return NULL;
}
#endif//CODE_ALLOC_USER_HEAP