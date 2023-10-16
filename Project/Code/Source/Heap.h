#ifndef _HEAP_H_
#define _HEAP_H_

NAME_SPACE_BEGIN

#define BLOCK_ALIGN					0x10
#define MAX_BLOCK_SIZE				0x400
#define FREE_LIST_COUNT				(MAX_BLOCK_SIZE/BLOCK_ALIGN)
#define FREE_LIST_INDEX(__size)		(((__size)+BLOCK_ALIGN-1)/BLOCK_ALIGN-1)
#define CHUNK_SIZE					0x1000

#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
#define BLOCK_EXT_DATA				(sizeof(ULSIZE)+sizeof(DWORD)*2)
#define BLOCK_EXT_DATA_AHEAD		(sizeof(ULSIZE)+sizeof(DWORD))
#else
#define BLOCK_EXT_DATA				(sizeof(ULSIZE)+sizeof(DWORD))
#define BLOCK_EXT_DATA_AHEAD		sizeof(ULSIZE)
#endif

#define INDEX_BLOCK_SIZE(__index)	(((__index)+1)*BLOCK_ALIGN)

union FREE_LIST
{
	FREE_LIST*pNext;
	struct
	{
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
		DWORD	CheckSign;
#endif
		ULSIZE	BlockSize;
		BYTE	UserData[4];
	}Block;
	BYTE	ChunkBuffer[1];
};

struct ALIGN_PTR_HEAD
{
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
	DWORD	CheckSign;
#endif
	ULSIZE	Offset;
};

class CFixedHeap
{
public:
	CFixedHeap();
	~CFixedHeap();
public:
	virtual void*	AllocSysMem(ULSIZE Size);
	virtual void	FreeSysMem(void*Ptr);
	virtual bool	IsValidMemory(void*Ptr);
	virtual void	ReportMemoryOverflow(void*ptr,ULSIZE Size);
	virtual void	ReportMemoryRedelete(void*ptr,ULSIZE Size);
public:
	bool		Create(ULSIZE Size);
	void		Destroy();
	void*		Allocate(ULSIZE Size);
	bool		Free(void*Ptr);
	void*		AlignAllocate(ULSIZE Size,ULSIZE Align);
	bool		AlignFree(void*Ptr);
	void		Compact();
	bool		Validate();
	ULSIZE		GetFreeChunkCount();
	ULSIZE		GetFreeChunkSpace();
private:
	ULSIZE		InitFreeListBuffer(ULSIZE BlockSize,VOID*ListBuffer,ULSIZE BufferSize);
	bool		InfuseFreeMemory(ULSIZE Index);
	void*		HugeAllocate(ULSIZE Size);
	bool		HugeFree(void*Ptr);
	FREE_LIST*	IsSeriate(FREE_LIST*pList,ULSIZE BlockSize,ULSIZE Count);
public:
	ULSIZE		m_AllocateCount;
	BYTE*		m_HeapBuffer;
	ULSIZE		m_HeapSize;
	ULSIZE		m_MinFreeChunkCount;
	ULSIZE		m_FreeChunkCount;
	FREE_LIST*	m_FreeList[FREE_LIST_COUNT];//Ð¡¿éÄÚ´æ²Û
	FREE_LIST*	m_pFirstFreeChunk;
	FREE_LIST*	m_pLastFreeChunk;
	FREE_LIST*	m_pCacheFreeChunk;
	BYTE*		ChunkAlloc(ULSIZE Size);
	bool		ChunkFree(void*pChunkBuffer,ULSIZE Size);
	bool		IsHeapMemory(void*pData);
};

NAME_SPACE_END

#endif
