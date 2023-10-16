#include "StdAfx.h"
#include "ELFFile.h"

CELFFile::CELFFile()
{
	m_FileType = FILE_TYPE_ELF;
	m_PrgSeg = NULL;
	m_Section = NULL;
	m_SectCount = m_PrgSegCount = 0;
}

CELFFile::~CELFFile()
{

}

bool CELFFile::Open(PCSTR FileName,HANDLE*pHandleOpen)
{
	if(CImageFile::Open(FileName,pHandleOpen)==false)
		goto ErrorExit;
	if(ReadFile(0,&m_ELFHeader,sizeof(m_ELFHeader))==false)
		goto ErrorExit;
	if(m_ELFHeader.e_ehsize!=sizeof(ELF_HEADER))
		goto ErrorExit;
	if(memcmp(m_ELFHeader.e_ident,"\177ELF",4))
		goto ErrorExit;
	m_SectCount = (int)m_ELFHeader.e_shnum;
	MAX_LIMIT(m_SectCount,MAX_SECTION_COUNT);
	if(m_SectCount)
	{
		m_Section = new ELF_SECTION[m_SectCount];
		if(ReadFile(m_ELFHeader.e_shoff,m_Section,sizeof(ELF_SECTION)*m_SectCount)==false)
			goto ErrorExit;
	}
	m_PrgSegCount = (int)m_ELFHeader.e_phnum;
	MAX_LIMIT(m_PrgSegCount,MAX_SEGMENT_COUNT);
	if(m_PrgSegCount)
	{
		m_PrgSeg = new ELF_PRG_SEG[m_PrgSegCount];
		if(ReadFile(m_ELFHeader.e_phoff,m_PrgSeg,sizeof(ELF_PRG_SEG)*m_PrgSegCount)==false)
			goto ErrorExit;
	}
	return true;
ErrorExit:
	Close();
	return false;
}

void CELFFile::Close()
{
	SafeDelete(m_PrgSeg);
	SafeDelete(m_Section);
	m_SectCount = m_PrgSegCount = 0;
	CImageFile::Close();
}

void CELFFile::DumpInfo()
{
	int n;
	printf("FileName %s\n",m_ImageName);
	printf("ELF Header\n");
	printf("e_type      = %04X\n",m_ELFHeader.e_type);
	printf("e_machine   = %04X\n",m_ELFHeader.e_machine);
	printf("e_version   = %08X\n",m_ELFHeader.e_version);
	printf("e_entry     = %08X\n",m_ELFHeader.e_entry);
	printf("e_phoff     = %08X\n",m_ELFHeader.e_phoff);
	printf("e_shoff     = %08X\n",m_ELFHeader.e_shoff);
	printf("e_flags     = %08X\n",m_ELFHeader.e_flags);
	printf("e_ehsize    = %04X\n",m_ELFHeader.e_ehsize);
	printf("e_phentsize = %04X\n",m_ELFHeader.e_phentsize);
	printf("e_phnum     = %04X\n",m_ELFHeader.e_phnum);
	printf("e_shentsize = %04X\n",m_ELFHeader.e_shentsize);
	printf("e_shnum     = %04X\n",m_ELFHeader.e_shnum);
	printf("e_shstrndx  = %04X\n",m_ELFHeader.e_shstrndx);
	printf("Program Segment\n");
	printf("PrgType  PhysAddr VirtAddr FileOff  Size\n");
	for(n=0;n<m_PrgSegCount;n++)
	{
		printf("%08X %08X %08X %08X %08X\n",m_PrgSeg[n].p_type,m_PrgSeg[n].p_paddr,m_PrgSeg[n].p_vaddr,m_PrgSeg[n].p_offset,m_PrgSeg[n].p_filesz);
	}
	printf("Section\n");
	printf("SectType VirtAddr FileOff  Size\n");
	for(n=0;n<m_SectCount;n++)
	{
		printf("%08X %08X %08X %08X\n",m_Section[n].sh_type,m_Section[n].sh_addr,m_Section[n].sh_offset,m_Section[n].sh_size);
	}

}

