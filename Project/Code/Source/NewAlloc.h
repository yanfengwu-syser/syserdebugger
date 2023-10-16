#ifndef _NEW_ALLOC_H_
#define _NEW_ALLOC_H_

#define	MAX_USER_HEAP_COUNT		16

#ifdef  CODE_ALLOC_OVERLOAD


void* __cdecl operator new(size_t size);
void* __cdecl operator new[](size_t size);

#ifndef CODE_DEBUG_ALLOC

void  __cdecl operator delete(void*p);
void  __cdecl operator delete[](void*p);

#endif//CODE_DEBUG_ALLOC

#endif//CODE_ALLOC_OVERLOAD

NAME_SPACE_BEGIN

void*	CodeAlloc(size_t size);
void	CodeFree(void *p);

#ifdef CODE_ALLOC_USER_HEAP
void InitMemoryAllocUserHeap();
void ReleaseMemoryAllocUserHeap();
class CFixedHeap;
extern CFixedHeap*	gpUserHeap[MAX_USER_HEAP_COUNT];
extern int	gMainHeapSize;
extern int	gCurUserHeapIndex;
extern int	gMaxUserHeapCount;

void SwitchHeap(int Index);
int GetCurrentHeapIndex();
CFixedHeap* GetCurrentHeap();
CFixedHeap* GetHeapByIndex(int Index);
#endif//CODE_ALLOC_USER_HEAP


NAME_SPACE_END

#endif

