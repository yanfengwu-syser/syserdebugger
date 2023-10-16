#ifndef _SYSER_MEMORY_READ_WRITE_H_
#define _SYSER_MEMORY_READ_WRITE_H_


bool SafeWriteByte(void* Address,BYTE ByteValue);
bool SafeWriteWord(void* Address,WORD WordValue);
bool SafeWriteDword(void* Address,DWORD DwordValue);

bool WriteByte(void* Address,BYTE ByteValue);
bool WriteWord(void* Address,WORD ByteValue);
bool WriteDword(void* Address,DWORD ByteValue);

bool ReadByte(void* Address,BYTE* ByteValue);
bool ReadWord(void* Address,WORD* WordValue);
bool ReadDword(void* Address,DWORD* DwordValue);

BYTE ReadByte(void* Address,bool* Success=NULL);
WORD ReadWord(void* Address,bool* Success=NULL);
DWORD ReadDword(void* Address,bool* Success=NULL);
 
BYTE ReadByteDefaultValue(void* Address,BYTE DefaultValue=MAX_BYTE);
WORD ReadWordDefaultValue(void* Address,WORD DefaultValue=MAX_WORD);
DWORD ReadDwordDefaultValue(void* Address,DWORD DefaultValue=MAX_DWORD);

BYTE* MemSearch(BYTE* SourceAddrss,DWORD SourceLen,BYTE *DestinationAddress,DWORD DestinationLen,bool* Success);
bool MemSearch(BYTE* SourceAddrss,DWORD SourceLen,BYTE *DestinationAddress,DWORD DestinationLen,BYTE** ErrorAddress);

#ifdef __cplusplus
extern "C" {
#endif


BYTE __stdcall SyserPrivateReadByte(void* Address);
WORD __stdcall SyserPrivateReadWord(void* Address);
DWORD __stdcall SyserPrivateReadDword(void* Address);

VOID __stdcall SyserPrivateReadError();

VOID __stdcall SyserPrivateWriteByte(void* Address,BYTE ByteValue);
VOID __stdcall SyserPrivateWriteWord(void* Address,WORD WordValue);
VOID __stdcall SyserPrivateWriteDword(void* Address,DWORD DwordValue);

VOID __stdcall SyserPrivateSafeWriteByte(void* Address,BYTE ByteValue);
VOID __stdcall SyserPrivateSafeWriteWord(void* Address,WORD WordValue);
VOID __stdcall SyserPrivateSafeWriteDword(void* Address,DWORD DwordValue);

VOID __stdcall SyserPrivateWriteError(VOID);

BYTE* __stdcall SyserPrivateFindDword(BYTE* Address1,DWORD Value,DWORD Len);
BYTE* __stdcall SyserPrivateFindWord(BYTE* Address1,WORD Value,DWORD Len);
BYTE* __stdcall SyserPrivateFindByte(BYTE* Address1,BYTE Value,DWORD Len);
int __stdcall SyserPrivateMemCopy(BYTE* Address1,BYTE* Address2,DWORD Len);
int __stdcall PrivateMemNCmp(DWORD* Address1,DWORD* Address2,DWORD Len);

VOID __stdcall SyserPrivateFindMemoryError(VOID);
VOID __stdcall SyserPrivateMemCopyError(VOID);

BYTE* __stdcall SyserPrivateMemSearch(BYTE* SourceAddrss,DWORD SourceLen,BYTE *DestinationAddress,DWORD DestinationLen);
VOID __stdcall SyserPrivateMemorySearchError(VOID);

int __stdcall SyserPrivatePagePresent(BYTE* Address,DWORD Len);
int __stdcall SyserPrivatePageNotPresent(VOID);

DWORD  __stdcall SyserPrivateMemCmp(BYTE* SourceAddr,BYTE* DestAddr,DWORD Len);
DWORD __stdcall SyserPrivateMemCmpError(VOID);
bool SafeMemCmp(BYTE* SourceAddress,BYTE* DestAddress,DWORD Len,DWORD* ReturnLen);
int SafeMemCopy(BYTE* DestAddress,BYTE* SourceAddress,DWORD Len);
int __stdcall SyserVideoMemCopy(BYTE* DestAddress,BYTE* SourceAddress,DWORD Len);
bool SafeVideoMemCopy(BYTE* DestAddress,BYTE* SourceAddress,DWORD Len);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif /* _SYSERMEMORYREADWRITE_H_ */
