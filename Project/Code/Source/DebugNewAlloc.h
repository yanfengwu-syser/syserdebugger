#ifndef _DEBUG_NEW_ALLOC_H_
#define _DEBUG_NEW_ALLOC_H_

#ifdef CODE_DEBUG_ALLOC

void* __cdecl operator new(size_t size,char*FileName,int Line);
void* __cdecl operator new[](size_t size,char*FileName,int Line);
void  __cdecl operator delete(void*p);
void  __cdecl operator delete[](void*p);
void  __cdecl operator delete(void*p,char*FileName,int Line);
void  __cdecl operator delete[](void*p,char*FileName,int Line);

NAME_SPACE_BEGIN
void*	CodeDebugAlloc(size_t size,char*FileName,int Line);
void	CodeDebugFree(void *p);
void	InitMemoryAllocMonite();
void	ReleaseMemoryAllocMonite();
void	MemoryAllocMoniteReport();
NAME_SPACE_END

#endif//CODE_DEBUG_ALLOC

#endif//_DEBUG_NEW_ALLOC_H_
