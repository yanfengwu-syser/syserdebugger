#include "StdAfx.h"
#include "Heap.h"

NAME_SPACE_BEGIN

#define	HEAP_SIGN					0x77777777
#define	HEAP_ALIGN_SIGN				0x77777778

CFixedHeap::CFixedHeap()
{
	m_HeapBuffer = NULL;
	m_HeapSize = 0;
}

CFixedHeap::~CFixedHeap()
{
	Destroy();
}

bool CFixedHeap::Create(ULSIZE Size)
{
	m_AllocateCount = 0;
	m_HeapSize = ALIGN_SIZE(Size,CHUNK_SIZE);
	m_HeapBuffer = (BYTE*)AllocSysMem(m_HeapSize);
	if(m_HeapBuffer==NULL)
		return false;
	ZeroMemory(m_HeapBuffer,m_HeapSize);
	m_MinFreeChunkCount = m_FreeChunkCount = InitFreeListBuffer(CHUNK_SIZE,m_HeapBuffer,m_HeapSize);
	m_pCacheFreeChunk = m_pFirstFreeChunk = (FREE_LIST*) m_HeapBuffer;
	m_pLastFreeChunk = (FREE_LIST*)&m_HeapBuffer[m_HeapSize-CHUNK_SIZE];
	ZeroMemory(m_FreeList,sizeof(m_FreeList));
	return true;
}

void CFixedHeap::Destroy()
{
	if(m_HeapBuffer)
	{
		FreeSysMem(m_HeapBuffer);
		m_HeapBuffer = NULL;
		m_HeapSize = 0;
	}
}

ULSIZE CFixedHeap::InitFreeListBuffer(ULSIZE BlockSize,void*ListBuffer,ULSIZE BufferSize)
{
	ULSIZE ListSize;
	FREE_LIST*pList,*pPrevList,HeadList;
	pPrevList = &HeadList;
	pList =(FREE_LIST*)ListBuffer;
	for(ListSize=0;ListSize+BlockSize<=BufferSize;ListSize+=BlockSize)
	{
		pPrevList->pNext = pList;
		pList->pNext = NULL;
		pPrevList = pList;
		pList = (FREE_LIST*)((BYTE*)pList+BlockSize);
	}
	return ListSize/BlockSize;
}

bool CFixedHeap::InfuseFreeMemory(ULSIZE Index)
{
	m_FreeList[Index]=(FREE_LIST*) ChunkAlloc(CHUNK_SIZE);
	if(m_FreeList[Index])
	{
		InitFreeListBuffer(INDEX_BLOCK_SIZE(Index),m_FreeList[Index]->ChunkBuffer,CHUNK_SIZE);
		return true;
	}
	ULSIZE Size,LargerIndex;
	Size = INDEX_BLOCK_SIZE(Index);
	for(ULSIZE IndexSize=Size*2;IndexSize<=MAX_BLOCK_SIZE;IndexSize+=Size)
	{
		LargerIndex = FREE_LIST_INDEX(IndexSize);
		if(m_FreeList[LargerIndex])
		{
			m_FreeList[Index] = m_FreeList[LargerIndex];
			m_FreeList[LargerIndex] = m_FreeList[LargerIndex]->pNext;
			InitFreeListBuffer(INDEX_BLOCK_SIZE(Index),m_FreeList[Index]->ChunkBuffer,INDEX_BLOCK_SIZE(LargerIndex));
			return true;
		}
	}
	return false;
}

void*CFixedHeap::Allocate(ULSIZE Size)
{
	if(m_HeapBuffer==NULL)
		return NULL;
	m_AllocateCount++;
	CODE_ASSERT(m_pFirstFreeChunk && m_FreeChunkCount);//堆空间遭到破坏
	if(Size+BLOCK_EXT_DATA>MAX_BLOCK_SIZE)
		return HugeAllocate(Size);
	ULSIZE Index;
	MIN_LIMIT(Size,1);
	Index = FREE_LIST_INDEX(Size+BLOCK_EXT_DATA);
	if(m_FreeList[Index]==NULL && InfuseFreeMemory(Index)==false)
	{
		return NULL;
	}
	if(m_FreeList[Index]==NULL)
		return NULL;
	FREE_LIST*pList = m_FreeList[Index]->pNext;
	m_FreeList[Index]->Block.BlockSize = Size;
	void*Buffer = m_FreeList[Index]->Block.UserData;
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
	m_FreeList[Index]->Block.CheckSign = HEAP_SIGN;
	PUT_DWORD(Buffer,Size,HEAP_SIGN);
#endif
	m_FreeList[Index] = pList;
	return Buffer;
}

bool CFixedHeap::Free(void*Ptr)
{
	if(m_HeapBuffer==NULL)
		return false;
	if(IsHeapMemory(Ptr)==false)
		return false;
	if(HugeFree(Ptr))
		return true;
	FREE_LIST*pList = (FREE_LIST*)((BYTE*)Ptr-BLOCK_EXT_DATA_AHEAD);
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
	if(GET_DWORD(Ptr,pList->Block.BlockSize)!=HEAP_SIGN)//内存被覆盖
		ReportMemoryOverflow(Ptr,pList->Block.BlockSize);
	if(pList->Block.CheckSign!=HEAP_SIGN)
		ReportMemoryRedelete(Ptr,pList->Block.BlockSize);
	pList->Block.CheckSign = 0;
#endif
	ULSIZE Index = FREE_LIST_INDEX(pList->Block.BlockSize+BLOCK_EXT_DATA);
	pList->pNext = m_FreeList[Index];
	m_FreeList[Index] = pList;
	return true;
}

void* CFixedHeap::AlignAllocate(ULSIZE Size,ULSIZE Align)
{
	ALIGN_PTR_HEAD*pHead;
	void*Buffer;
	NUM_PTR Ptr;
	Buffer = Allocate(Size+sizeof(ALIGN_PTR_HEAD)+Align);
	if(Buffer==NULL)
		return NULL;
	Ptr = (NUM_PTR)Buffer;
	Ptr += Align-Ptr%Align;
	if(Ptr<(NUM_PTR)Buffer+sizeof(ALIGN_PTR_HEAD))
		Ptr+=Align;
	pHead = (ALIGN_PTR_HEAD*)(Ptr-sizeof(ALIGN_PTR_HEAD));
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
	pHead->CheckSign = HEAP_ALIGN_SIGN;
#endif
	pHead->Offset =(ULSIZE) (Ptr - (NUM_PTR)Buffer);
	Buffer = (void*)Ptr;
	return Buffer;
}

bool CFixedHeap::AlignFree(void*Ptr)
{
	ALIGN_PTR_HEAD*pHead;
	if(Ptr==NULL)
		return false;
	pHead = (ALIGN_PTR_HEAD*)((NUM_PTR)Ptr-sizeof(ALIGN_PTR_HEAD));
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
	if(pHead->CheckSign!=HEAP_ALIGN_SIGN)
	{
		ReportMemoryOverflow(Ptr,0);
		return false;
	}
#endif
	Ptr = (void*)((NUM_PTR)Ptr - pHead->Offset);
	return Free(Ptr);
}

void* CFixedHeap::HugeAllocate(ULSIZE Size)
{
	FREE_LIST*pList =(FREE_LIST*) ChunkAlloc(ALIGN_SIZE(Size+BLOCK_EXT_DATA,CHUNK_SIZE));
	if(pList == NULL)
	{
		return NULL;
	}
	pList->Block.BlockSize = Size;
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
	pList->Block.CheckSign = HEAP_SIGN;
	PUT_DWORD(pList->Block.UserData,Size,HEAP_SIGN);
#endif
	return pList->Block.UserData;
}

bool CFixedHeap::HugeFree(void*Ptr)
{
	FREE_LIST*pList = (FREE_LIST*)((BYTE*)Ptr-BLOCK_EXT_DATA_AHEAD);
	if(pList->Block.BlockSize+BLOCK_EXT_DATA<=MAX_BLOCK_SIZE)
	{
		return false;
	}
#ifdef CODE_ALLOC_USER_HEAP_FREE_CHECK
	if(GET_DWORD(Ptr,pList->Block.BlockSize)!=HEAP_SIGN)
		ReportMemoryOverflow(Ptr,pList->Block.BlockSize);
	if(pList->Block.CheckSign!=HEAP_SIGN)
		ReportMemoryRedelete(Ptr,pList->Block.BlockSize);
	pList->Block.CheckSign = 0;
#endif
	bool Result = ChunkFree(pList,ALIGN_SIZE(pList->Block.BlockSize+BLOCK_EXT_DATA,CHUNK_SIZE));
	return Result;
}

BYTE*CFixedHeap::ChunkAlloc(ULSIZE Size)
{
	BYTE*pChunkBuffer;
	FREE_LIST*pFreeChunk,*pEndFreeChunk,*pPrevChunk;
	ULSIZE ChunkCount;
	CODE_ASSERT(!(m_pFirstFreeChunk && m_pFirstFreeChunk->pNext ==NULL && m_FreeChunkCount>=1));
	ChunkCount = PAGE_COUNT(Size,CHUNK_SIZE);
	pFreeChunk = m_pFirstFreeChunk;
	while(pFreeChunk)
	{
		if(pEndFreeChunk=IsSeriate(pFreeChunk,CHUNK_SIZE,ChunkCount))
			break;
		pPrevChunk = pFreeChunk;
		pFreeChunk = pFreeChunk->pNext;
	}
	if(pFreeChunk==NULL)
		return NULL;
	pChunkBuffer = pFreeChunk->ChunkBuffer;

	m_FreeChunkCount-=ChunkCount;
	if(m_MinFreeChunkCount>m_FreeChunkCount)
		m_MinFreeChunkCount=m_FreeChunkCount;

	if(m_pFirstFreeChunk==pFreeChunk)
		m_pFirstFreeChunk = pEndFreeChunk->pNext;
	else
		pPrevChunk->pNext = pEndFreeChunk->pNext;

	if(pEndFreeChunk==m_pLastFreeChunk)
		m_pLastFreeChunk = m_pFirstFreeChunk;

	if(m_pCacheFreeChunk>=pFreeChunk && m_pCacheFreeChunk<=pEndFreeChunk)
	{
		m_pCacheFreeChunk = pEndFreeChunk->pNext;
		if(m_pCacheFreeChunk==NULL)
			m_pCacheFreeChunk = m_pFirstFreeChunk;
	}
	return pChunkBuffer;
}

bool CFixedHeap::ChunkFree(void*pChunkBuffer,ULSIZE Size)
{
	ULSIZE ChunkCount;
	FREE_LIST*pFreeList,*pFreeEndList;
	if(((BYTE*)pChunkBuffer - m_HeapBuffer)%CHUNK_SIZE)
		return false;
	Size = ALIGN_SIZE(Size,CHUNK_SIZE);
	ChunkCount = InitFreeListBuffer(CHUNK_SIZE,pChunkBuffer,Size);

	pFreeList=(FREE_LIST*)pChunkBuffer;
	pFreeEndList = (FREE_LIST*)((BYTE*)pChunkBuffer+Size-CHUNK_SIZE);

	CODE_ASSERT(pFreeList!=m_pFirstFreeChunk&&pFreeList!=m_pLastFreeChunk&&pFreeList!=m_pCacheFreeChunk);

	if(m_pFirstFreeChunk==NULL && m_pLastFreeChunk==NULL)
	{
		m_pFirstFreeChunk = pFreeList;
		m_pLastFreeChunk = pFreeEndList;
	}
	else if(pFreeList < m_pFirstFreeChunk)
	{
		pFreeEndList->pNext = m_pFirstFreeChunk;
		m_pFirstFreeChunk = pFreeList;
	}
	else if(pFreeList > m_pLastFreeChunk)
	{
		m_pLastFreeChunk->pNext = pFreeList;
		m_pLastFreeChunk = pFreeEndList;
	}
	else if(pFreeList > m_pFirstFreeChunk  && pFreeList < m_pCacheFreeChunk)
	{
		m_pCacheFreeChunk = m_pFirstFreeChunk;
		while(m_pCacheFreeChunk->pNext < pFreeList)
			m_pCacheFreeChunk = m_pCacheFreeChunk->pNext;
		pFreeEndList->pNext = m_pCacheFreeChunk->pNext;
		m_pCacheFreeChunk->pNext = pFreeList;
	}
	else//if(pFreeList > m_pCacheFreeChunk  && pFreeList < m_pLastFreeChunk)
	{
		while(m_pCacheFreeChunk->pNext < pFreeList)
			m_pCacheFreeChunk = m_pCacheFreeChunk->pNext;
		pFreeEndList->pNext = m_pCacheFreeChunk->pNext;
		m_pCacheFreeChunk->pNext = pFreeList;
	}
	m_FreeChunkCount+=ChunkCount;
	m_pCacheFreeChunk = (FREE_LIST*)pChunkBuffer;
	return true;
}

FREE_LIST*CFixedHeap::IsSeriate(FREE_LIST*pList,ULSIZE BlockSize,ULSIZE Count)
{
	for(ULSIZE n=1;n<Count;n++)
	{
		if(pList==NULL || ((BYTE*)pList->pNext - (BYTE*)pList)!=BlockSize)
			return NULL;
		pList=pList->pNext;
	}
	return pList;
}

bool CFixedHeap::IsHeapMemory(void*pData)
{
	return m_HeapBuffer && (BYTE*)pData>m_HeapBuffer && (BYTE*)pData<m_HeapBuffer+m_HeapSize-1;
}

void CFixedHeap::Compact()
{
	
}

bool CFixedHeap::Validate()
{
	return GetFreeChunkCount()==m_FreeChunkCount;
}

ULSIZE CFixedHeap::GetFreeChunkCount()
{
	ULSIZE Count =0;
	FREE_LIST *pList = m_pFirstFreeChunk;
	while(pList)
	{
		if(pList && pList->pNext && pList->pNext<=pList)
			return 0;
		pList = pList->pNext;
		Count++;
	}
	return Count;
}

ULSIZE CFixedHeap::GetFreeChunkSpace()
{
	ULSIZE Size;
	FREE_LIST*	pFreeChunk;
	pFreeChunk = m_pFirstFreeChunk;
	Size = 0;
	while(pFreeChunk)
	{
		Size+=CHUNK_SIZE;
		pFreeChunk=pFreeChunk->pNext;
	}
	return Size;
}

void* CFixedHeap::AllocSysMem(ULSIZE Size)
{
#ifdef CODE_OS_NT_DRV
	return ExAllocatePoolWithTag(NonPagedPool, Size,'Heap');
#else
	return malloc(Size);
#endif
}

void CFixedHeap::FreeSysMem(void*Ptr)
{
#ifdef CODE_OS_NT_DRV
	ExFreePool(Ptr);
#else
	free(Ptr);
#endif
}

bool CFixedHeap::IsValidMemory(void*Ptr)
{ 
	return true;														
}

void CFixedHeap::ReportMemoryOverflow(void*ptr,ULSIZE Size)
{
	char szBuffer[256];
	TSPrintf(szBuffer,"内存[%p]溢出\n",ptr);
#ifdef CODE_ALLOC_USER_HEAP_OVERFLOW_OUTPUT
	CODE_DEBUG_OUTPUT(szBuffer);
#endif
#ifdef CODE_ALLOC_USER_HEAP_DEBUG_BREAK
	CODE_ASSERT(false);
#endif
	return;
}

void CFixedHeap::ReportMemoryRedelete(void*ptr,ULSIZE Size)
{
	char szBuffer[256];
	TSPrintf(szBuffer,"内存[%p]重复释放或被其它块覆盖\n",ptr);
#ifdef CODE_ALLOC_USER_HEAP_OVERFLOW_OUTPUT
	CODE_DEBUG_OUTPUT(szBuffer);
#endif
#ifdef CODE_ALLOC_USER_HEAP_DEBUG_BREAK
	CODE_ASSERT(false);
#endif
	return;
}

/*
void CFixedHeapTest()
{
	CFixedHeap Heap;
	Heap.Create(0x10000+0x4000);
	void*ptr[0x100],*ptr1,*ptr2;
	ptr1 = Heap.Allocate(0x3FFC);
	ZeroMemory(ptr1,0x3FFC);
	for(int n=0;n<0x100;n++)
	{
		ptr[n]=Heap.Allocate(12);
		ZeroMemory(ptr[n],12);
		printf("ptr[%d] = %p \n",n,ptr[n]);
		if(ptr[n]==NULL)
		{
			printf("Alloc %d Error \n",n);
			return;
		}
	}
	ptr2 = Heap.Allocate(0x3FFC);
	Heap.Free(ptr2);
	for(int n=0;n<0x100;n++)
	{
		if(Heap.Free(ptr[n])==false)
		{
			printf("Free %d Error\n",n);
			return;
		}
	}
	Heap.Free(ptr1);
	printf("Free Chunk Space %X (bytes)\n",Heap.GetFreeChunkSpace());
	Heap.Destroy();
	return;
}
*/

NAME_SPACE_END

