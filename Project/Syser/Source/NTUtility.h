#ifndef _NT_UTILITY_H_
#define _NT_UTILITY_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef struct seg_descriptor 
{
    WORD	limit_0_15;
    WORD	base_0_15;
    BYTE	base_16_23;
    BYTE    accessed    : 1 ;
    BYTE    readwrite   : 1;
    BYTE    conforming  : 1;
    BYTE    code_data   : 1;
    BYTE    app_system  : 1;
    BYTE    dpl         : 2;
    BYTE    present     : 1;
    BYTE    limit_16_19 : 4;
    BYTE    unused      : 1;
    BYTE    always_0    : 1;
    BYTE    seg_16_32   : 1;
    BYTE	granularity : 1;
    BYTE	base_24_31;
}SEG_DESCRIPTOR;

extern "C"
{
	NTSYSAPI NTSTATUS NTAPI 
	KeI386AllocateGdtSelectors(PUSHORT pSelectorArray,DWORD NumberOfSelectors);
	NTSYSAPI NTSTATUS NTAPI 
	KeI386ReleaseGdtSelectors(PUSHORT pSelectorArray,DWORD NumberOfSelectors);
	NTSYSAPI NTSTATUS NTAPI
	KeI386SetGdtSelector(DWORD Selector,PVOID pDescriptor);
}

enum
{
	DRV_OS_2K = 0,
	DRV_OS_XP,
};

UINT GetOSVer(ULONG* MajorVersion,ULONG* MinorVersion,ULONG* BuildNumber);

#define VGA_BIOS_ROM_ADDRESS			0xC0000
#define ROM_BIOS_ROM_ADDRESS			0xF0000

WORD	NTAllocSelector(DWORD Base,DWORD Limit,BYTE bCodeSeg,BYTE bWritable,BYTE bSeg32,BYTE bDplDwon);
void	NTReleaseSelector(WORD Selectors);

BYTE	ReadVideoCRTRegByte(BYTE Index);
BYTE	ReadCmosRegister(BYTE Index);
VOID	SyserResetSystem(VOID);

bool	IsAddressValid(void*p);
char	WaitForKey();
void	Beep(DWORD Counter=0 ,DWORD frequency=0);

ULSIZE	GetVirtualAddressBlockSize(ULPOS Address);

//PVOID	GetCurrentPEB(VOID);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif

 