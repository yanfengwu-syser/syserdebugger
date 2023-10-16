#ifndef _MZFILE_H_
#define _MZFILE_H_

#define MZFILE_SIGNATURE (('M'<<8)+'Z')
#define MZFILE_SIGNATURE1 (('Z'<<8)+'M')

typedef struct	_MZHEAD
{
	WORD Signature;		//00  "MZ"
	WORD cbLastPage;	//02  Bytes on last page of file
	WORD nPage;			//04  Pages in file
	WORD nReloc;		//06  Relocations
	WORD cpHead;		//08  Size of header in paragraphs
	WORD Minalloc;		//0A  Minimum extra paragraphs needed
	WORD Maxalloc;		//0C  Maximum extra paragraphs needed
	WORD SS;			//0E  Initial (relative) SS value
	WORD SP;			//10  Initial SP value
	WORD CheckSum;		//12  Checksum
	WORD IP;			//14  Initial IP value
	WORD CS;			//16  Initial (relative) CS value
	WORD fpReloc;		//18  File address of relocation table
	WORD nOverlay;		//1A  Overlay number
	WORD Reserved[4];	//1C  Reserved words
	WORD OemID;			//24  OEM identifier (for e_oeminfo)
	WORD OemInfo;		//26  OEM information; e_oemid specific
	WORD Reserved2[10];	//28  Reserved words
	LONG pfNewHead;		//3C  File address of new exe header
}MZHEAD,*PMZHEAD;

typedef struct	_MZRELOC
{
	WORD Offset;
	WORD Segment;
}MZRELOC;

class CMZFile : public CImageFile
{
public:
	CMZFile();
	bool	Open(PCSTR FileName,HANDLE*pHandleOpen = NULL);
	void	Close();
	ULSIZE	ReadImageMemory(IN ULPOS Address,OUT void* Buffer,IN ULSIZE Size);
public:
	MZHEAD	m_MZHead;
	DWORD	m_ImageBase;
	DWORD	m_ImageSize;
};

#endif


