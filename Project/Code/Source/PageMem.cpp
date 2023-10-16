#include "StdAfx.h"
#include "PageMem.h"

NAME_SPACE_BEGIN
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPageMemory::CPageMemory()
{
	m_PhysMemory=NULL;
	m_PageExistMap=NULL;
	ZeroMemory(m_PageDir,sizeof(m_PageDir));
	m_Style = PMS_NO_PAGE_OUT;
}

CPageMemory::~CPageMemory()
{
}

bool CPageMemory::Init(int PageCount,UINT Style)
{
	m_Style = Style;
	if((m_Style & PMS_DYN_PAGE)==0)
	{
		m_PhysMemory = new BYTE[PageCount*MP_SIZE];
		if(m_PhysMemory==NULL)
			return false;
		m_PageExistMap = new BYTE[PageCount];
		if(m_PageExistMap==NULL)
		{
			SafeDelete(m_PhysMemory);
			return false;
		}
		ZeroMemory(m_PageExistMap,PageCount);
	}
	ZeroMemory(m_PageDir,sizeof(m_PageDir));
	ZeroMemory(&m_PageDataCache1,sizeof(m_PageDataCache1));
	ZeroMemory(&m_PageDataCache2,sizeof(m_PageDataCache2));
	m_PageCount=PageCount;
	m_PageUsedCount = 0;
	m_FreePhysIndex=0;
	m_WriteAccessPageCount = 0;
	return true;
}

void CPageMemory::Release()
{
	if(m_Style & PMS_DYN_PAGE)
	{
		for(DWORD n=0;n<PAGE_DIR_COUNT;n++)
		{
			if(m_PageDir[n]==NULL)
				continue;
			for(DWORD m=0;m<PAGE_DIR_CONTENT;m++)
				SafeDelete(m_PageDir[n][m].PhysAddr);
		}
	}
	else
	{
		SafeDeleteAry(m_PhysMemory);
		SafeDeleteAry(m_PageExistMap);
	}
	for(int n=0;n<PAGE_DIR_COUNT;n++)
		SafeDeleteAry(m_PageDir[n]);
	m_ImageRangeMap.Clear();
}

void CPageMemory::RefreshCache(MEMORY_PAGE*pPage)
{
	if(pPage == m_PageDataCache1.MemoryPage)
		ZeroMemory(&m_PageDataCache1,sizeof(m_PageDataCache1));
	if(pPage == m_PageDataCache2.MemoryPage)
		ZeroMemory(&m_PageDataCache2,sizeof(m_PageDataCache2));
}

bool CPageMemory::ExchangePage()
{
	if(ReleaseClearPage())
		return true;
	if(m_Style & PMS_PAGE_OUT)
		return FlushAllPage()!=0;
	return false;
}

int CPageMemory::FlushAllPage()
{
	int count;
	ULPOS Address;
	MEMORY_PAGE*pPage;
	count=0;
	for(DWORD n=0;n<PAGE_DIR_COUNT;n++)
	{
		if(m_PageDir[n]==NULL)
			continue;
		for(DWORD m=0;m<PAGE_DIR_CONTENT;m++)
		{
			Address = (n<<22)+(m<<12);
			pPage = &m_PageDir[n][m];
			if((pPage->Attribute & MP_DIRTY) && (pPage->Attribute & MP_LOCK)==0 && pPage->PhysAddr)
			{
				if(SavePage(Address,pPage))
					count++;
			}
		}
	}
	return count;
}

CPageImage*CPageMemory::GetImage(PCSTR ModuleName)
{
	for(CImgRangeMap::IT Iter = m_ImageRangeMap.Begin();Iter!=m_ImageRangeMap.End();Iter++)
	{
		if(TCmpModuleName((PCSTR)(*Iter)->m_ImageName,ModuleName))
			return *Iter;
	}
	return NULL;
}

CPageImage*CPageMemory::GetImage(ULPOS ModuleBase)
{
	CImgRangeMap::IT Iter;
	Iter = m_ImageRangeMap.Find(CImgRangeMap::RANGE(ModuleBase));
	if(Iter == m_ImageRangeMap.End())
		return NULL;
	return *Iter;
}

bool CPageMemory::MapImage(CPageImage*pImageFile)
{
	CImgRangeMap::IT Iter;
	DWORD DirIndex,PageIndex,PageCount,Address,Size;
	MEMORY_PAGE*pPage;
	Iter = m_ImageRangeMap.Find(CImgRangeMap::RANGE(pImageFile->m_ImageBase));
	if(Iter!=m_ImageRangeMap.End())
		return false;
	Address = pImageFile->m_ImageBase;
	Size = (DWORD)pImageFile->m_ImageSize;
	PageIndex = (Address>>12) & 0x3FF;
	DirIndex = Address>>22;
	PageCount = PAGE_COUNT(Size,MP_SIZE);
	while(DirIndex<PAGE_DIR_COUNT && PageCount)
	{
		if(m_PageDir[DirIndex]==NULL)
		{
			m_PageDir[DirIndex] = new MEMORY_PAGE[PAGE_DIR_CONTENT];
			ZeroMemory(m_PageDir[DirIndex],sizeof(MEMORY_PAGE)*PAGE_DIR_CONTENT);
		}
		while(PageIndex<PAGE_DIR_CONTENT && PageCount)
		{
			pPage = &m_PageDir[DirIndex][PageIndex];
			if(pPage->Attribute!=MP_FREE)
				return false;
			pPage->Attribute = pImageFile->GetPageAttribute(Address) | MP_IMAGE;
			pPage->PhysAddr = NULL;
			pPage->AccessWriteCount = pPage->AccessReadCount = 0;
			PageCount--;
			Address+=MP_SIZE;
			PageIndex++;
		}
		DirIndex++;
		PageIndex = 0;
	}
	m_ImageRangeMap.InsertUnique(CImgRangeMap::RANGE(pImageFile->m_ImageBase,pImageFile->m_ImageHighBase-1),pImageFile);
	return true;
}

bool CPageMemory::UnmapImage(CPageImage*pImageFile)
{
	DWORD DirIndex,PageIndex,Address,PageCount;
	MEMORY_PAGE*pPage;
	CImgRangeMap::IT Iter = m_ImageRangeMap.Find(CImgRangeMap::RANGE(pImageFile->m_ImageBase));
	if(Iter==m_ImageRangeMap.End())
		return false;
	Address = pImageFile->m_ImageBase;
	PageIndex = (Address>>12) & 0x3FF;
	DirIndex = Address>>22;
	PageCount = (DWORD)pImageFile->m_ImageSize / MP_SIZE;
	while(DirIndex<PAGE_DIR_COUNT && PageCount)
	{
		if(m_PageDir[DirIndex]==NULL)
			return false;
		while(PageIndex<PAGE_DIR_CONTENT && PageCount)
		{
			pPage = &m_PageDir[DirIndex][PageIndex];
			DeletePage(pPage);
			ZeroMemory(pPage,sizeof(MEMORY_PAGE));
			Address+=MP_SIZE;
			PageCount--;
		}
		DirIndex++;
		PageIndex = 0;
	}
	m_ImageRangeMap.Remove(Iter);
	return true;
}


bool CPageMemory::AllocatePage(ULPOS Address,UINT Attribute,void* Buffer,ULSIZE Size)
{
	DWORD DirIndex,PageIndex;
	MEMORY_PAGE*pPage;

	if(m_PageUsedCount>=m_PageCount && ExchangePage()==false)
		return false;//无可用的物理页
	PageIndex = (Address>>12) & 0x3FF;
	DirIndex=Address>>22;
	if(m_PageDir[DirIndex]==NULL)
	{
		m_PageDir[DirIndex] = new MEMORY_PAGE[PAGE_DIR_CONTENT];
		ZeroMemory(m_PageDir[DirIndex],sizeof(MEMORY_PAGE)*PAGE_DIR_CONTENT);
	}
	pPage = &m_PageDir[DirIndex][PageIndex];
	if(pPage->Attribute!=MP_FREE)
		return false;
	pPage->Attribute = Attribute;
	if((pPage->Attribute & MP_COMMIT)==0)
	{
		if(NewPage(pPage)==false)
		{
			pPage->Attribute = MP_FREE;
			return false;
		}
		pPage->Attribute |=MP_DIRTY;
	}
	pPage->AccessWriteCount = pPage->AccessReadCount = 0;
	if(Size>MP_SIZE)
		Size=MP_SIZE;
	if((pPage->Attribute & MP_COMMIT)==0)
	{
		if(Buffer)
		{
			if(Size>MP_SIZE)
				Size=MP_SIZE;
			memcpy(pPage->PhysAddr,Buffer,Size);
			if(Size<MP_SIZE)
				ZeroMemory(&pPage->PhysAddr[Size],MP_SIZE-Size);
		}
		else
			ZeroMemory(pPage->PhysAddr,MP_SIZE);
	}
	return true;
}

bool CPageMemory::AllocatePage(ULPOS Address,UINT Attribute,BYTE PageData)
{
	DWORD DirIndex,PageIndex;
	MEMORY_PAGE*pPage;
	PageIndex = (Address>>12) & 0x3FF;
	DirIndex=Address>>22;
	if(m_PageDir[DirIndex]==NULL)
	{
		m_PageDir[DirIndex] = new MEMORY_PAGE[PAGE_DIR_CONTENT];
		ZeroMemory(m_PageDir[DirIndex],sizeof(MEMORY_PAGE)*PAGE_DIR_CONTENT);
	}
	pPage = &m_PageDir[DirIndex][PageIndex];
	if(pPage->Attribute!=MP_FREE)
		return false;
	ZeroMemory(pPage,sizeof(MEMORY_PAGE));
	pPage->Attribute = Attribute|MP_CONST;
	pPage->PageData = PageData;
	return true;
}

bool CPageMemory::ReleasePage(ULPOS Address)
{
	int DirIndex,PageIndex;
	MEMORY_PAGE*pPage;
	Address>>=12;
	PageIndex = Address & 0x3FF;
	DirIndex=Address>>10;

	pPage = m_PageDir[DirIndex];
	if(pPage==NULL || pPage[PageIndex].PhysAddr == NULL)
		return false;

	pPage = &pPage[PageIndex];
	DeletePage(pPage);
	ZeroMemory(pPage,sizeof(MEMORY_PAGE));
	return true;
}

DWORD CPageMemory::ReleaseClearPage()
{
	MEMORY_PAGE*pPage;
	int Count=0;
	for(int n=0;n<PAGE_DIR_COUNT;n++)
	{
		if(m_PageDir[n]==NULL)
			continue;
		for(int p=0;p<PAGE_DIR_CONTENT;p++)
		{
			pPage = &m_PageDir[n][p];
			if((pPage->Attribute&MP_DIRTY)==0&&(pPage->Attribute&MP_LOCK)==0&&pPage->PhysAddr)
			{
				DeletePage(pPage);
				if(pPage->Attribute & MP_IMAGE)
					pPage->PhysAddr=NULL;
				else
					ZeroMemory(pPage,sizeof(MEMORY_PAGE));
				Count++;
				if(m_PageUsedCount<=0)
					return Count;
			}
		}
	}
	return Count;
}

bool CPageMemory::IsPageExist(ULPOS Address)
{
	DWORD DirIndex,PageIndex;
	MEMORY_PAGE*pPage;
	Address>>=12;
	PageIndex = Address & 0x3FF;
	DirIndex=Address>>10;
	pPage = m_PageDir[DirIndex];
	if( pPage==NULL || pPage[PageIndex].Attribute == MP_FREE)
		return false;
	return true;
}

bool CPageMemory::IsPageDirExist(ULPOS Address)
{
	DWORD DirIndex,PageIndex;
	MEMORY_PAGE*pPage;
	Address>>=12;
	PageIndex = Address & 0x3FF;
	DirIndex=Address>>10;
	pPage = m_PageDir[DirIndex];
	if( pPage==NULL )
		return false;
	return true;
}

MEMORY_PAGE*CPageMemory::GetDataPage(ULPOS Address,bool bWrite)
{
	DWORD DirIndex,PageIndex;
	MEMORY_PAGE*pPage;
	Address&=MP_NOT_MASK;
	if(m_PageDataCache1.bExist && Address == m_PageDataCache1.BaseAddr)
	{
		m_PageDataCache1.AccessCount++;
		return m_PageDataCache1.MemoryPage;
	}
	if(m_PageDataCache2.bExist && Address == m_PageDataCache2.BaseAddr)
	{
		m_PageDataCache2.AccessCount++;
		return m_PageDataCache2.MemoryPage;
	}
	PageIndex = (Address>>12) & 0x3FF;
	DirIndex = Address>>22;
	pPage = m_PageDir[DirIndex];
	if(pPage==NULL || pPage[PageIndex].Attribute == MP_FREE)
		return NULL;
	pPage = &pPage[PageIndex];
	if(pPage->Attribute&MP_COMMIT)
	{
		if(NewPage(pPage)==false)
			return NULL;
	}
	else if((pPage->Attribute&MP_IMAGE) && pPage->PhysAddr==NULL && LoadPage(Address,pPage)==false)
		return NULL;
	if(m_PageDataCache1.AccessCount>m_PageDataCache2.AccessCount)
	{
		m_PageDataCache2.bExist = true;
		m_PageDataCache2.BaseAddr = Address;
		m_PageDataCache2.AccessCount = 0;
		m_PageDataCache2.MemoryPage = pPage;
	}
	else
	{
		m_PageDataCache1.bExist = true;
		m_PageDataCache1.BaseAddr = Address;
		m_PageDataCache1.AccessCount = 0;
		m_PageDataCache1.MemoryPage = pPage;
	}
	return pPage;
}

bool CPageMemory::LoadPage(ULPOS Address,MEMORY_PAGE*pPage)
{
	CPageImage*pImageFile;
	if(m_PageUsedCount>=m_PageCount && ExchangePage()==false)
		return false;
	CImgRangeMap::IT Iter = m_ImageRangeMap.Find(CImgRangeMap::RANGE(Address));
	if(Iter==m_ImageRangeMap.End())
		return false;
	pImageFile = *Iter;
	CODE_ASSERT((pPage->Attribute&MP_COMMIT)==0);
	if(NewPage(pPage)==false)
		return false;
	if(pImageFile->LoadPage(Address,pPage->PhysAddr)==false)
	{
		DeletePage(pPage);
		ZeroMemory(pPage,sizeof(MEMORY_PAGE));
		return false;
	}
	return true;
}

bool CPageMemory::SavePage(ULPOS Address,MEMORY_PAGE*pPage)
{
	if((pPage->Attribute & MP_IMAGE)==0 || (m_Style & PMS_PAGE_OUT)==0 || pPage->PhysAddr==NULL)
		return false;
	CImgRangeMap::IT Iter = m_ImageRangeMap.Find(CImgRangeMap::RANGE(Address));
	if(Iter==m_ImageRangeMap.End())
		return false;
	if((*Iter)->SavePage(Address,pPage->PhysAddr)==false)
		return false;
	DeletePage(pPage);
	pPage->Attribute &= ~MP_DIRTY;
	return true;
}

ULSIZE CPageMemory::ReadMemX(ULPOS Address,void*Buffer,ULSIZE Size)
{
	MEMORY_PAGE*pPage;
	ULSIZE RSize;
	ULPOS RAddr;
	RAddr=Address;
	RSize=MIN(Size,MP_SIZE-Address%MP_SIZE);
	while(Size>0)
	{
		pPage=GetDataPage(RAddr);
		if(pPage==NULL)
			return RAddr - Address;
		if(pPage->Attribute & MP_CONST)
			memset(RT_PBYTE(Buffer,RAddr-Address),(BYTE)pPage->PageData,RSize);
		else
			memcpy(RT_PBYTE(Buffer,RAddr-Address),&pPage->PhysAddr[RAddr&MP_MASK],RSize);
		Size-=RSize;
		RAddr+=RSize;
		RSize=MIN(Size,MP_SIZE);
	}
	return RAddr - Address;
}

ULSIZE CPageMemory::WriteMemX(ULPOS Address,void*Buffer,ULSIZE Size)
{
	MEMORY_PAGE*pPage;
	ULPOS WAddr;
	ULSIZE WSize;
	WAddr=Address;
	WSize=MIN(Size,MP_SIZE-Address%MP_SIZE);
	while(Size>0)
	{
		pPage=GetDataPage(WAddr,true);
		if(pPage==NULL)
			return WAddr - Address;
		if((pPage->Attribute & MP_CONST)==0)
			memcpy(&pPage->PhysAddr[WAddr&MP_MASK],RT_PBYTE(Buffer,WAddr-Address),WSize);
		pPage->Attribute |= MP_DIRTY;
		Size-=WSize;
		WAddr+=WSize;
		WSize=MIN(Size,MP_SIZE);
	}
	return WAddr - Address;
}

ULSIZE CPageMemory::ZeroMemX(ULPOS Address,ULSIZE Size)
{
	MEMORY_PAGE*pPage;
	ULPOS WAddr;
	ULSIZE WSize;
	WAddr=Address;
	WSize=MIN(Size,MP_SIZE-Address%MP_SIZE);
	while(Size>0)
	{
		pPage=GetDataPage(WAddr,true);
		if(pPage==NULL)
			return WAddr - Address;
		if((pPage->Attribute & MP_CONST)==0)
			ZeroMemory(&pPage->PhysAddr[WAddr&MP_MASK],WSize);
		pPage->Attribute |= MP_DIRTY;
		Size-=WSize;
		WAddr+=WSize;
		WSize=MIN(Size,MP_SIZE);
	}
	return WAddr - Address;
}

ULSIZE CPageMemory::ReadMemory(ULPOS Address,void* Buffer,ULSIZE Size,CPageMemory*pPageMemory)
{
	return pPageMemory->ReadMemX(Address,Buffer,Size);
}

ULSIZE CPageMemory::WriteMemory(ULPOS Address,void* Buffer,ULSIZE Size,CPageMemory*pPageMemory)
{
	return pPageMemory->WriteMemX(Address,Buffer,Size);
}

ULSIZE CPageMemory::ReadString(ULPOS Address,PSTR Buffer,ULSIZE MaxLen)
{
    ULSIZE Readed;
    BYTE Str;
	MaxLen--;
	for(Readed=0;Readed<MaxLen;Readed++)
	{
		if(ReadMemB(Address+Readed,&Str)==false)
			break;
		if(Buffer)
			Buffer[Readed]=Str;
		if(Str==0)
			return Readed;
	}
	if(Buffer)
		Buffer[Readed]=0;
	return Readed;
}

ULSIZE CPageMemory::WriteString(ULPOS Address,PSTR Buffer,ULSIZE MaxLen)
{
    ULSIZE Written;
    for(Written=0;Written<MaxLen;Written++)
	{
		if(WriteMemB(Address+Written,&Buffer[Written])==false)
			break;
		if(Buffer[Written]==0)
			return Written-1;
	}
	if(Written>=MaxLen)
		WriteMemB(Address+Written-1,(BYTE*)"\x00");
	return Written-1;
}

ULSIZE CPageMemory::ReadString(ULPOS Address,PWORD Buffer,ULSIZE MaxLen)
{
    ULSIZE Readed;
    WORD Str;
	MaxLen--;
	for(Readed=0;Readed<MaxLen;Readed++)
	{
		if(ReadMemW(Address+Readed*2,&Str)==false)
			break;
		if(Buffer)
			Buffer[Readed]=Str;
		if(Str==0)
			return Readed;
	}
	if(Buffer)
		PUT_WORD(Buffer,Readed*2,0);
	return Readed;
}

ULSIZE CPageMemory::WriteString(ULPOS Address,PWORD Buffer,ULSIZE MaxLen)
{
    DWORD Written;
	for(Written=0;Written<MaxLen;Written++)
	{
		if(WriteMemW(Address+Written*2,&Buffer[Written])==false)
			break;
		if(Buffer[Written]==0)
			return Written-1;
	}
	if(Written>=MaxLen)
		WriteMemW(Address+(Written-1)*2,(PWORD)"\x00\x00");
	return Written-1;
}

ULSIZE CPageMemory::ReadString(ULPOS Address,PDSTR Buffer,ULSIZE MaxLen)
{
	ULSIZE Readed;
	WORD Str;
	MaxLen--;
	for(Readed=0;Readed<MaxLen;Readed++)
	{
		if(ReadMemD(Address+Readed*4,&Str)==false)
			break;
		if(Buffer)
			Buffer[Readed]=Str;
		if(Str==0)
			return Readed;
	}
	if(Buffer)
		PUT_DWORD(Buffer,Readed*4,0);
	return Readed;
}

ULSIZE CPageMemory::WriteString(ULPOS Address,PDSTR Buffer,ULSIZE MaxLen)
{
	DWORD Written;
	for(Written=0;Written<MaxLen;Written++)
	{
		if(WriteMemD(Address+Written*4,&Buffer[Written])==false)
			break;
		if(Buffer[Written]==0)
			return Written-1;
	}
	if(Written>=MaxLen)
		WriteMemD(Address+(Written-1)*4,(PDSTR)"\x00\x00\x00\x00");
	return Written-1;
}


bool CPageMemory::ReadMemB(ULPOS Address,void* Buffer)
{
	MEMORY_PAGE*pPage=GetDataPage(Address);
	if(pPage==NULL)
		return false;
	if(pPage->Attribute & MP_CONST)
		*_RT_PBYTE(Buffer)=(BYTE)pPage->PageData;
	else
		*_RT_PBYTE(Buffer)=pPage->PhysAddr[Address & MP_MASK];
	pPage->AccessReadCount++;
	return true;
}

bool CPageMemory::ReadMemW(ULPOS Address,void* Buffer)
{
	MEMORY_PAGE*pPage=GetDataPage(Address);
	if((Address & MP_MASK)<= MP_SIZE-2)
	{
		if(pPage==NULL)
			return false;
		if(pPage->Attribute & MP_CONST)
		{
			_PUT_BYTE(Buffer,(BYTE)pPage->PageData);
			PUT_BYTE(Buffer,1,(BYTE)pPage->PageData);
		}
		else
		{
#ifdef CODE_BUS_ALIGN
			BYTE*VirtualBuffer=&pPage->PhysAddr[Address & MP_MASK];
			PUT_BYTE(Buffer,1,VirtualBuffer[0]);
			_PUT_BYTE(Buffer,VirtualBuffer[1]);
#else
			*_RT_PWORD(Buffer)=GET_WORD(pPage->PhysAddr,Address & MP_MASK);
#endif
		}
		pPage->AccessReadCount++;
		return true;
	}
#ifndef CODE_BIG_ENDIAN
	if(	ReadMemB(Address,Buffer)==false ||
		ReadMemB(Address+1,RT_PVOID(Buffer,1))==false)
		return false;
#else
	if(	ReadMemB(Address,RT_PVOID(Buffer,1))==false ||
		ReadMemB(Address+1,Buffer)==false)
		return false;
#endif
	return true;
}

bool CPageMemory::ReadMemD(ULPOS Address,void* Buffer)
{
	MEMORY_PAGE*pPage=GetDataPage(Address);
	if((Address & MP_SIZE)<= MP_SIZE-4)
	{
		if(pPage==NULL)
			return false;
		if(pPage->Attribute & MP_CONST)
		{
			_PUT_BYTE(Buffer,  (BYTE)pPage->PageData);
			 PUT_BYTE(Buffer,1,(BYTE)pPage->PageData);
			 PUT_BYTE(Buffer,2,(BYTE)pPage->PageData);
			 PUT_BYTE(Buffer,3,(BYTE)pPage->PageData);
		}
		else
		{
#ifdef CODE_BUS_ALIGN
			BYTE*VirtualBuffer=&pPage->PhysAddr[Address & MP_MASK];
			PUT_BYTE(Buffer,3,VirtualBuffer[0]);
			PUT_BYTE(Buffer,2,VirtualBuffer[1]);
			PUT_BYTE(Buffer,1,VirtualBuffer[2]);
			_PUT_BYTE(Buffer,VirtualBuffer[3]);
#else
			*_RT_PDWORD(Buffer)=GET_DWORD(pPage->PhysAddr,Address & MP_MASK);
#endif
		}
		pPage->AccessReadCount++;
		return true;
	}
#ifndef CODE_BIG_ENDIAN
	if(	ReadMemW(Address,Buffer)==false ||
		ReadMemW(Address+2,RT_PVOID(Buffer,2))==false)
		return false;
#else
	if(	ReadMemW(Address,RT_PVOID(Buffer,2))==false ||
		ReadMemW(Address+2,Buffer)==false)
		return false;
#endif
	return true;
}

bool CPageMemory::WriteMemB(ULPOS Address,void* Buffer)
{
	MEMORY_PAGE*pPage=GetDataPage(Address,true);
	if(pPage==NULL)
		return false;
	if((pPage->Attribute & MP_CONST)==0)
		pPage->PhysAddr[Address&MP_MASK]=_GET_BYTE(Buffer);
	if((pPage->Attribute & MP_DIRTY)==0)
	{
		m_WriteAccessPageCount++;
		pPage->Attribute |= MP_DIRTY;
	}
	pPage->AccessWriteCount++;
	return true;
}

bool CPageMemory::WriteMemW(ULPOS Address,void* Buffer)
{
	MEMORY_PAGE*pPage=GetDataPage(Address,true);
	if((Address & MP_MASK)<= MP_SIZE-2)
	{
		if(pPage==NULL)
			return false;
		if((pPage->Attribute & MP_CONST)==0)
		{
#ifdef CODE_BUS_ALIGN
			BYTE*VirtualBuffer=&pPage->PhysAddr[Address & MP_MASK];
			VirtualBuffer[0]=GET_BYTE(Buffer,1);
			VirtualBuffer[1]=_GET_BYTE(Buffer);
#else
			PUT_WORD(pPage->PhysAddr,Address & MP_MASK,*_RT_PWORD(Buffer));
#endif
		}
		if((pPage->Attribute & MP_DIRTY)==0)
		{
			m_WriteAccessPageCount++;
			pPage->Attribute |= MP_DIRTY;
		}
		pPage->AccessWriteCount++;
		return true;
	}
#ifndef CODE_BIG_ENDIAN
	if(	WriteMemB(Address,Buffer)==false ||
		WriteMemB(Address+1,RT_PVOID(Buffer,1)))
		return false;
#else
	if(	WriteMemB(Address,RT_PVOID(Buffer,1))==false ||
		WriteMemB(Address+1,Buffer))
		return false;
#endif
	return true;
}

bool CPageMemory::WriteMemD(ULPOS Address,void* Buffer)
{
	MEMORY_PAGE*pPage=GetDataPage(Address,true);
	/////////////////////数据断点////////////////////////		
	if((Address & MP_MASK)<=MP_SIZE-4)
	{
		if(pPage==NULL)
			return false;
		if((pPage->Attribute & MP_CONST)==0)
		{
#ifdef CODE_BUS_ALIGN
			BYTE*VirtualBuffer=&pPage->PhysAddr[Address & MP_MASK];
			VirtualBuffer[0]=GET_BYTE(Buffer,3);
			VirtualBuffer[1]=GET_BYTE(Buffer,2);
			VirtualBuffer[2]=GET_BYTE(Buffer,1);
			VirtualBuffer[3]=_GET_BYTE(Buffer);
#else
			PUT_DWORD(pPage->PhysAddr,Address & MP_MASK,*_RT_PDWORD(Buffer));
#endif
		}
		if((pPage->Attribute & MP_DIRTY)==0)
		{
			m_WriteAccessPageCount++;
			pPage->Attribute |= MP_DIRTY;
		}
		pPage->AccessWriteCount++;
		return true;
	}
#ifndef CODE_BIG_ENDIAN
	if(	WriteMemW(Address,Buffer)==false ||
		WriteMemW(Address+2,RT_PVOID(Buffer,2))==false)
		return false;
#else
	if(	WriteMemW(Address,RT_PVOID(Buffer,2))==false ||
		WriteMemW(Address+2,Buffer)==false)
		return false;
#endif
	return true;
}

bool CPageMemory::NewPage(MEMORY_PAGE*pPage)
{
	if(m_Style & PMS_DYN_PAGE)
	{
		pPage->PhysAddr = new BYTE[MP_SIZE];
		ZeroMemory(pPage->PhysAddr,MP_SIZE);
	}
	else
	{
		CODE_ASSERT(m_FreePhysIndex>=0);
		if(m_FreePhysIndex>=m_PageCount)
			return false;
		pPage->PhysAddr = RT_PBYTE(m_PhysMemory,m_FreePhysIndex*MP_SIZE);
		m_PageExistMap[m_FreePhysIndex] = PHYS_PAGE_EXIST;
		while(m_FreePhysIndex<m_PageCount)
		{
			if(m_PageExistMap[m_FreePhysIndex]==PHYS_PAGE_NULL)
				break;
			m_FreePhysIndex++;
		}
	}
	pPage->Attribute &= ~MP_COMMIT;
	m_PageUsedCount++;
	return true;
}

bool CPageMemory::DeletePage(MEMORY_PAGE*pPage)
{
	int PhysIndex;
	if((pPage->Attribute&MP_COMMIT)==0 && pPage->PhysAddr)
	{
		if(m_Style & PMS_DYN_PAGE)
		{
			delete pPage->PhysAddr;
			pPage->PhysAddr = NULL;
		}
		else
		{
			CODE_ASSERT(pPage->PhysAddr>=m_PhysMemory);
			PhysIndex = (int)((pPage->PhysAddr-m_PhysMemory) / MP_SIZE);
			m_PageExistMap[PhysIndex] = PHYS_PAGE_NULL;
			pPage->PhysAddr = NULL;
			if(PhysIndex<m_FreePhysIndex)
				m_FreePhysIndex=PhysIndex;
		}
		m_PageUsedCount--;
	}
	RefreshCache(pPage);
	return true;
}
NAME_SPACE_END
