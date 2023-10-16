#ifndef _ELF_FILE_H_
#define _ELF_FILE_H_

#define MAX_SECTION_COUNT		0x100
#define MAX_SEGMENT_COUNT		0x100

struct ELF_HEADER
{
/*00*/	char		e_ident[16];	/* Magic number and other info */
/*10*/	WORD		e_type;			/* Object file type */
/*12*/	WORD		e_machine;		/* Architecture */
/*14*/	DWORD		e_version;		/* Object file version */
/*18*/	DWORD		e_entry;		/* Entry point virtual address */
/*1C*/	DWORD		e_phoff;		/* Program header table file offset */
/*20*/	DWORD		e_shoff;		/* Section header table file offset */
/*24*/	DWORD		e_flags;		/* Processor-specific flags */
/*28*/	WORD		e_ehsize;		/* ELF header size in bytes */
/*2A*/	WORD		e_phentsize;	/* Program header table entry size */
/*2C*/	WORD		e_phnum;		/* Program header table entry count */
/*2E*/	WORD		e_shentsize;	/* Section header table entry size */
/*30*/	WORD		e_shnum;		/* Section header table entry count */
/*32*/	WORD		e_shstrndx;		/* Section header string table index */
};

struct ELF_PRG_SEG
{
	DWORD	p_type;			/* Segment type */
	DWORD	p_offset;		/* Segment file offset */
	DWORD	p_vaddr;		/* Segment virtual address */
	DWORD	p_paddr;		/* Segment physical address */
	DWORD	p_filesz;		/* Segment size in file */
	DWORD	p_memsz;		/* Segment size in memory */
	DWORD	p_flags;		/* Segment flags */
	DWORD	p_align;		/* Segment alignment */
};

struct ELF_SECTION
{	
	DWORD	sh_name;		/* Section name (string tbl index) */
	DWORD	sh_type;		/* Section type */
	DWORD	sh_flags;		/* Section flags */
	DWORD	sh_addr;		/* Section virtual addr at execution */
	DWORD	sh_offset;		/* Section file offset */
	DWORD	sh_size;		/* Section size in bytes */
	DWORD	sh_link;		/* Link to another section */
	DWORD	sh_info;		/* Additional section information */
	DWORD	sh_addralign;	/* Section alignment */
	DWORD	sh_entsize;		/* Entry size if section holds table */
};

class CELFFile : public CImageFile
{
public:
	CELFFile();
	~CELFFile();
public:
	bool	Open(PCSTR FileName,HANDLE*pHandleOpen = NULL);
	void	Close();
	void	DumpInfo();
public:
	ELF_HEADER	m_ELFHeader;
	ELF_SECTION*	m_Section;
	int			m_SectCount;
	ELF_PRG_SEG*	m_PrgSeg;
	int			m_PrgSegCount;
};


#endif

